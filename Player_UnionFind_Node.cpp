//
// Created by nizni on 12/21/2022.
//

#include "Player_UnionFind_Node.h"

Player_UnionFind_Node::Player_UnionFind_Node(const shared_ptr<Player> real_player, const shared_ptr<Team> team)
        : player(real_player), father_player_node(nullptr), father_team(nullptr),
        diff_from_father(permutation_t::neutral()), games_played_alone(real_player->getGamesPlayed()),
        additional_games(0), games_of_team_without(0){
    ///creating a new node to add real_player to team.


    //shared_ptr<Player_UnionFind_Node> this_sp(this);///maybe not possible, if so do it in player
    //real_player->setUnionFindNode(this_sp);

    shared_ptr<Player_UnionFind_Node> root_node_sp = team->getRootPlayer().lock();
    if (root_node_sp){///theres a root already
        this->father_player_node = root_node_sp;

        shared_ptr<Player> player_in_root = root_node_sp->player.lock();

        ///spirit:
        permutation_t father_partial_spirit = player_in_root->getPartialSpirit();
        permutation_t teamSpirit = team->getTeamSpirit();///its the root so it has a pointer to a team

        this->diff_from_father = father_partial_spirit.inv() * teamSpirit * real_player->getSpirit();

        ///gamesPlayed:
        this->games_of_team_without = root_node_sp->additional_games;
    }
    else{///no root, so this will be the root and will point to team
        this->father_team = team;
        //team->setRootPlayer(this_sp);
    }
    team->setTeamSpirit(team->getTeamSpirit()*real_player->getSpirit());
    //team->setSize(team->getSize()+1);
}

shared_ptr<Team> Find(shared_ptr<Player> player) {
    return findHelper(player->getUnionFindNode());
}

shared_ptr<Team> findHelper(shared_ptr<Player_UnionFind_Node> current) {
    if (!current->father_player_node) {///is root
        shared_ptr<Player> current_player = current->player.lock();
        current_player->setGamesPlayed(current->games_played_alone + current->additional_games);
        return current->father_team;
    }
    shared_ptr<Team> team = findHelper(current->father_player_node);
    shared_ptr<Player_UnionFind_Node> root_player_node = team->getRootPlayer().lock();

    shared_ptr<Player_UnionFind_Node> current_father = current->father_player_node;
    shared_ptr<Player> current_player = current->player.lock();

    ///updating partial spirits
    current_player->setPartialSpirit(current_father->player.lock()->getPartialSpirit() * current->diff_from_father);
    current->diff_from_father = current_father->diff_from_father * current->diff_from_father;

    ///updating games played
    if (current->father_player_node->father_player_node){///father is not root
        current->additional_games += current_father->additional_games;
        current->games_of_team_without += current_father->games_of_team_without;
    }
    current_player->setGamesPlayed(
            current->games_played_alone
            + current->additional_games
            - current->games_of_team_without
            + root_player_node->additional_games
            - root_player_node->games_of_team_without);


    current->father_player_node = root_player_node;///shrinking path

    return team;
}

shared_ptr<Team> Union(shared_ptr<Team> buyer_team, shared_ptr<Team> sold_team) {

    shared_ptr<Player_UnionFind_Node> smaller_root_player_node, bigger_root_player_node;

    if (buyer_team->size > sold_team->size){///bigger buys smaller

        smaller_root_player_node = sold_team->root_player.lock();
        bigger_root_player_node = buyer_team->root_player.lock();

        shared_ptr<Player_UnionFind_Node> sold_root_node = bigger_root_player_node;
        shared_ptr<Player_UnionFind_Node> buyer_root_node = smaller_root_player_node;

        shared_ptr<Player> sold_root_player = sold_root_node->player.lock();
        shared_ptr<Player> buyer_root_player = buyer_root_node->player.lock();

        smaller_root_player_node->diff_from_father = buyer_root_player->getPartialSpirit().inv()
                * buyer_team->team_spirit
                * buyer_root_player->getPartialSpirit();

    }
    else {///smaller buys bigger (or equals)
        smaller_root_player_node = buyer_team->getRootPlayer().lock();
        bigger_root_player_node = sold_team->getRootPlayer().lock();

        shared_ptr<Player_UnionFind_Node> sold_root_node = bigger_root_player_node;
        shared_ptr<Player_UnionFind_Node> buyer_root_node = smaller_root_player_node;

        shared_ptr<Player> sold_root_player = sold_root_node->player.lock();
        shared_ptr<Player> buyer_root_player = buyer_root_node->player.lock();


        ///spirit
        sold_root_player->setPartialSpirit(buyer_team->getTeamSpirit()
                * sold_root_player->getPartialSpirit());
        buyer_root_node->diff_from_father = sold_root_player->getPartialSpirit().inv()
                * buyer_root_player->getPartialSpirit();
    }
    ///games_played
    smaller_root_player_node->games_of_team_without += bigger_root_player_node->additional_games;

    ///spirits:
    buyer_team->setTeamSpirit(buyer_team->getTeamSpirit() * sold_team->getTeamSpirit());

    ///Union:
    smaller_root_player_node->father_player_node = bigger_root_player_node;
    smaller_root_player_node->father_team = nullptr;///not a root now

    bigger_root_player_node->father_team = buyer_team;
    buyer_team->setRootPlayer(bigger_root_player_node);

    return buyer_team;
}

void Player_UnionFind_Node::setAdditionalGames(int add) {
    this->additional_games = this->additional_games + add;
}

