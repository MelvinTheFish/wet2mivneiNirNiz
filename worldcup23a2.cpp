#include "worldcup23a2.h"

world_cup_t::world_cup_t():
        teamsByPlayersAbility(Team::teamSumAbilityBigger, Team::teamSumAbilityEquals),
        teamsById(Team::teamIdBigger, Team::teamIdEquals)
{}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId)
{
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Team> newTeam = make_shared<Team>(teamId);
    shared_ptr<Team> newTeamsFather = *teamsById.insert(newTeam);
    if (!newTeamsFather){
        ///already exists
        return StatusType::FAILURE;
    }
    teamsByPlayersAbility.insert(newTeam);
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Team> DummyTeam = make_shared<Team>(teamId);
    shared_ptr<Team> RealTeamToRemove = *teamsById.find(DummyTeam);
    if (!RealTeamToRemove){
        ///dont exist
        return StatusType::FAILURE;
    }
    teamsByPlayersAbility.insert(newTeam);
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
