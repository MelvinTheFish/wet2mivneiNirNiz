//
// Created by nizni on 12/21/2022.
//

#ifndef WET2MIVNEINIRNIZ_PLAYER_UNIONFIND_NODE_H
#define WET2MIVNEINIRNIZ_PLAYER_UNIONFIND_NODE_H


#include <memory>
#include "wet2util.h"

#include "Player.h"
#include "Team.h"

using namespace std;

class Player_UnionFind_Node {

private:
    weak_ptr<Player> player;
    shared_ptr<Player_UnionFind_Node> father_player_node; ///if its the root, it will be null
    shared_ptr<Team> father_team; ///if its not the root, it will be null
    permutation_t diff_from_father; ///diff_from_father * player.spirit = partial_spirit

    int games_played_alone;
    int additional_games;
    int games_of_team_without;

    friend shared_ptr<Team> findHelper(shared_ptr<Player_UnionFind_Node> current);


public:
    Player_UnionFind_Node(shared_ptr<Player> real_player, shared_ptr<Team> team);

    friend shared_ptr<Team> Find(shared_ptr<Player> player);
    friend shared_ptr<Team> Union(shared_ptr<Team> buyer_team, shared_ptr<Team> sold_team);
};


#endif //WET2MIVNEINIRNIZ_PLAYER_UNIONFIND_NODE_H
