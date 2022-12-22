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

    shared_ptr<Team> findHelper(shared_ptr<Player_UnionFind_Node> current);


public:
    Player_UnionFind_Node(const shared_ptr<Player> &real_player, const shared_ptr<Team> &team);

    shared_ptr<Team> find();
};


#endif //WET2MIVNEINIRNIZ_PLAYER_UNIONFIND_NODE_H
