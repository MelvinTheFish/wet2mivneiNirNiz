//
// Created by nizni on 12/21/2022.
//

#include "Player.h"

Player::Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards,
               bool goalKeeper) : player_id(playerId), team_id(teamId), spirit(spirit), games_played(gamesPlayed),
                        ability(ability), cards(cards), goalKeeper(goalKeeper), union_find_node(nullptr),
                        partial_spirit(spirit){
}

const shared_ptr<Player_UnionFind_Node> &Player::getUnionFindNode() const {
    return union_find_node;
}

void Player::setUnionFindNode(const shared_ptr<Player_UnionFind_Node> &unionFindNode) {
    union_find_node = unionFindNode;
}

Player::Player(int playerId) : player_id(playerId) {}

const permutation_t &Player::getSpirit() const {
    return spirit;
}

const permutation_t &Player::getPartialSpirit() const {
    return partial_spirit;
}

void Player::setPartialSpirit(const permutation_t &partialSpirit) {
    partial_spirit = partialSpirit;
}