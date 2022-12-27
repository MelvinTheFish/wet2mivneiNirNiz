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
public:
    void setTeamId(int teamId);

private:
    int SumAbility;
public:
    void setSumAbility(int sumAbility);
    void addSumAbility(int sumAbilityAdd);

private:
    weak_ptr<Player_UnionFind_Node> root_player;
    permutation_t team_spirit;
    bool isActive;
    bool hasGoalKeeper;
public:
    bool HasGoalKeeper1() const;

    void setHasGoalKeeper(bool isGoalKeeper);

public:
    void setIsActive(bool isActive);

public:
    bool isActive1() const;

public:
    void setTeamSpirit(const permutation_t &teamSpirit);
    void addToTeamSpirit(const permutation_t &addAfter);

public:
    const permutation_t &getTeamSpirit() const;

public:
    const weak_ptr<Player_UnionFind_Node> &getRootPlayer() const;

    void setRootPlayer(const shared_ptr<Player_UnionFind_Node> &rootPlayer);

    int getSize() const;

    void setSize(int new_size);
    void addSize(int more);

private:
    int size;
    int points;
public:
    int getPoints() const;

    void setPoints(int points);

    void addPoints(int more);

public:
    Team(int teamId, int sumAbility);
    Team(int teamId);
    int getSumAbility() const;
    int getTeamId() const;
    static bool teamIdBigger(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2);
    static bool teamSumAbilityBigger(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2);
    static bool teamIdEquals(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2);
    static bool teamSumAbilityEquals(const shared_ptr<Team>& team1, const shared_ptr<Team>& team2);
    friend shared_ptr<Team> Union(shared_ptr<Team> buyer_team, shared_ptr<Team> sold_team);
};


#endif //WET2MIVNEINIRNIZ_TEAM_H
