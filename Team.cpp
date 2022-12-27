//
// Created by nizni on 12/19/2022.
//

#include "Team.h"

Team::Team(int teamId, int sumAbility) : TeamId(teamId), SumAbility(sumAbility) {}



Team::Team(int teamId) : TeamId(teamId), SumAbility(0), root_player(), size(0),
team_spirit(permutation_t::neutral()), isActive(true), hasGoalKeeper(false), points(0){
}

int Team::getSumAbility() const {
    return SumAbility;
}

int Team::getTeamId() const {
    return TeamId;
}

bool Team::teamIdBigger(const shared_ptr<Team> &team1, const shared_ptr<Team> &team2) {
    if (team1->TeamId > team2->TeamId){
        return true;
    }
    return false;
}


bool Team::teamSumAbilityBigger(const shared_ptr<Team> &team1, const shared_ptr<Team> &team2) {
    if (team1->SumAbility > team2->SumAbility){
        return true;
    }
    if (team1->SumAbility == team2->SumAbility){
        if (team1->TeamId > team2->TeamId){
            return true;
        }
    }
    return false;
}


bool Team::teamIdEquals(const shared_ptr<Team> &team1, const shared_ptr<Team> &team2) {
    if (team1->TeamId == team2->TeamId){
        return true;
    }
    return false;
}



bool Team::teamSumAbilityEquals(const shared_ptr<Team> &team1, const shared_ptr<Team> &team2) {
    if (team1->SumAbility == team2->SumAbility && team1->TeamId == team2->TeamId){
        return true;
    }
    return false;
}

const weak_ptr<Player_UnionFind_Node> &Team::getRootPlayer() const {
    return root_player;
}

void Team::setRootPlayer(const shared_ptr<Player_UnionFind_Node> &rootPlayer) {
    root_player = rootPlayer;
}

int Team::getSize() const {
    return size;
}

void Team::setSize(int new_size) {
    size = new_size;
}


void Team::addSize(int more) {
    size += more;
}

const permutation_t &Team::getTeamSpirit() const {
    return team_spirit;
}

void Team::setTeamSpirit(const permutation_t &teamSpirit) {
    team_spirit = teamSpirit;
}

void Team::addToTeamSpirit(const permutation_t &addAfter) {
    team_spirit = team_spirit * addAfter;
}

bool Team::isActive1() const {
    return isActive;
}

void Team::setIsActive(bool isActive) {
    Team::isActive = isActive;
}

void Team::addSumAbility(int sumAbilityAdd) {
    SumAbility += sumAbilityAdd;
}
void Team::setSumAbility(int sumAbility) {
    SumAbility += sumAbility;
}

bool Team::HasGoalKeeper1() const {
    return hasGoalKeeper;
}

void Team::setHasGoalKeeper(bool isGoalKeeper) {
    Team::hasGoalKeeper = isGoalKeeper;
}

int Team::getPoints() const {
    return points;
}

void Team::setPoints(int points) {
    Team::points = points;
}

void Team::addPoints(int more) {
    Team::points += more;
}

void Team::setTeamId(int teamId) {
    TeamId = teamId;
}
