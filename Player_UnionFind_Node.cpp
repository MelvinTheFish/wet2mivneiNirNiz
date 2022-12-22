//
// Created by nizni on 12/21/2022.
//

#include "Player_UnionFind_Node.h"

Player_UnionFind_Node::Player_UnionFind_Node(const shared_ptr<Player> &real_player, const shared_ptr<Team> &team)
        : player(real_player), father_player_node(nullptr), father_team(nullptr), diff_from_father(permutation_t::neutral()) {
    ///creating a new node to add real_player to team.


    shared_ptr<Player_UnionFind_Node> this_sp(this);
    real_player->setUnionFindNode(this_sp);

    shared_ptr<Player_UnionFind_Node> root_node_sp = team->getRootPlayer().lock();
    if (root_node_sp){///theres a root already
        this->father_player_node = root_node_sp;

        shared_ptr<Player> player_in_root = root_node_sp->player.lock();

        permutation_t father_spirit = player_in_root->getSpirit();
        permutation_t teamSpirit = root_node_sp->father_team->getTeamSpirit();///its the root so it has a pointer to a team

        this->diff_from_father = father_spirit.inv() * teamSpirit * real_player->getSpirit();
    }
    else{///no root, so this will be the root and will point to team
        this->father_team = team;
    }
}

shared_ptr<Team> Player_UnionFind_Node::find() {
    shared_ptr<Player_UnionFind_Node> this_sp(this);
    return findHelper(this_sp);
}

shared_ptr<Team> Player_UnionFind_Node::findHelper(shared_ptr<Player_UnionFind_Node> current) {
    if (!current->father_player_node) {///is root
        return current->father_team;
    }
    shared_ptr<Team> root = findHelper(current->father_player_node);

    shared_ptr<Player_UnionFind_Node> current_father = current->father_player_node;
    current->diff_from_father = current_father->diff_from_father * current->diff_from_father;
    shared_ptr<Player> current_player = current->player.lock();
    current_player->setPartialSpirit(current_father->player.lock()->getPartialSpirit() * current->diff_from_father);
}