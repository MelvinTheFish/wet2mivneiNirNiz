//
// Created by nizni on 12/19/2022.
//
#include <memory>
#include "wet2util.h"


#ifndef WET2MIVNEINIRNIZ_TEAM_H
#define WET2MIVNEINIRNIZ_TEAM_H

class Player_UnionFind_Node;

using namespace std;

class Team {
private:
    int TeamId;
    int SumAbility;
    weak_ptr<Player_UnionFind_Node> root_player;
    permutation_t team_spirit;
public:
    const permutation_t &getTeamSpirit() const;

public:
    const weak_ptr<Player_UnionFind_Node> &getRootPlayer() const;

    void setRootPlayer(const shared_ptr<Player_UnionFind_Node> &rootPlayer);

    int getSize() const;

    void setSize(int new_size);

private:
    int size;

public:
    Team(int teamId, int sumAbility);
    Team(int teamId);
    int getSumAbility() const;
    int getTeamId() const;
    static bool teamIdBigger(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2);
    static bool teamSumAbilityBigger(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2);
    static bool teamIdEquals(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2);
    static bool teamSumAbilityEquals(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2);
};


#endif //WET2MIVNEINIRNIZ_TEAM_H
