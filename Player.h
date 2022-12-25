//
// Created by nizni on 12/21/2022.
//

#ifndef WET2MIVNEINIRNIZ_PLAYER_H
#define WET2MIVNEINIRNIZ_PLAYER_H

#include "wet2util.h"
#include <memory>



class Player_UnionFind_Node;
class Team;

using namespace std;

class Player {
    int player_id;
public:
    int getPlayerId() const;

public:
    explicit Player(int playerId);

private:
    int team_id;
    const permutation_t spirit;
    permutation_t partial_spirit;///not always valid, only right after Find.
public:
    const permutation_t &getPartialSpirit() const;

    void setPartialSpirit(const permutation_t &partialSpirit);

public:
    const permutation_t &getSpirit() const;

private:
    int games_played;
public:
    int getGamesPlayed() const;

    void setGamesPlayed(int gamesPlayed);

public:
    Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards,
           bool goalKeeper);

private:
////think!!

    int ability;
    int cards;
    bool goalKeeper;

    shared_ptr<Player_UnionFind_Node> union_find_node;
public:
    shared_ptr<Player_UnionFind_Node> getUnionFindNode() const;

    void setUnionFindNode(const shared_ptr<Player_UnionFind_Node> &unionFindNode);

    friend shared_ptr<Team> Find(shared_ptr<Player> player);


};


#endif //WET2MIVNEINIRNIZ_PLAYER_H
