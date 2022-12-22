//
// Created by nizni on 12/19/2022.
//

#include "Team.h"

Team::Team(int teamId, int sumAbility) : TeamId(teamId), SumAbility(sumAbility) {}



Team::Team(int teamId) : TeamId(teamId), SumAbility(0), root_player(), size(0), team_spirit(permutation_t::neutral()){
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

const permutation_t &Team::getTeamSpirit() const {
    return team_spirit;
}

void Team::setTeamSpirit(const permutation_t &teamSpirit) {
    team_spirit = teamSpirit;
}
