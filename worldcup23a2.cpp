#include "worldcup23a2.h"


world_cup_t::world_cup_t():
        teamsByPlayersAbility(Team::teamSumAbilityBigger, Team::teamSumAbilityEquals),
        teamsById(Team::teamIdBigger, Team::teamIdEquals), playersTable()
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
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Team> DummyTeam = make_shared<Team>(teamId);
    shared_ptr<Team> RealTeamToRemove = *teamsById.find(DummyTeam);
    if (!RealTeamToRemove){
        ///dont exist
        return StatusType::FAILURE;
    }
    teamsByPlayersAbility.remove(RealTeamToRemove);
    teamsById.remove(RealTeamToRemove);
    RealTeamToRemove->setIsActive(false);
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if (playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0){
        return StatusType::INVALID_INPUT;
    }

    //checking if team exists
    shared_ptr<Team> teamOfPlayer = *teamsById.find(make_shared<Team>(teamId));
    if (!teamOfPlayer){
        return StatusType::FAILURE;
    }

    //checking if playerId is taken
    shared_ptr<Player> newPlayer = make_shared<Player>(playerId, teamId, spirit,
                                                       gamesPlayed, ability, cards, goalKeeper);
    int playersCurrIdx = playersTable.insertHash(newPlayer); ////-1 if already exists
    if (playersCurrIdx == -1){
        return StatusType::FAILURE;//taken
    }

    //adding player to team
    shared_ptr<Player_UnionFind_Node> newPlayersNode =
            make_shared<Player_UnionFind_Node>(newPlayer, teamOfPlayer);
    newPlayer->setUnionFindNode(newPlayersNode);
    //updating team
    teamsByPlayersAbility.remove(teamOfPlayer);
    teamOfPlayer->addSumAbility(ability);
    if (teamOfPlayer->getSize() == 0){
        teamOfPlayer->setRootPlayer(newPlayersNode);
    }
    teamOfPlayer->addSize(1);
    teamOfPlayer->addToTeamSpirit(spirit);
    teamOfPlayer->setHasGoalKeeper(goalKeeper);
    //updating team location in playersAbility rank tree
    teamsByPlayersAbility.insert(teamOfPlayer);


	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1<=0||teamId2<=0||teamId1==teamId2){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Team> team1 = *teamsById.find(make_shared<Team>(teamId1));
    shared_ptr<Team> team2 = *teamsById.find(make_shared<Team>(teamId2));
    if(!team1||!team2){
        return StatusType::FAILURE;
    }

    if(!team1->HasGoalKeeper1()||!team2->HasGoalKeeper1()){
        return StatusType::FAILURE;
    }
    int scoreTeam1 = team1->getSumAbility() + team1->getPoints();
    int scoreTeam2 = team2->getSumAbility() + team2->getPoints();

    if(scoreTeam1 > scoreTeam2){
        team1->setPoints(team1->getPoints() + 3);
        team1->getRootPlayer().lock()->setAdditionalGames(1);
        team2->getRootPlayer().lock()->setAdditionalGames(1);
        return 1;

    }
    if(scoreTeam1 < scoreTeam2){
        team2->setPoints(team2->getPoints() + 3);
        team1->getRootPlayer().lock()->setAdditionalGames(1);
        team2->getRootPlayer().lock()->setAdditionalGames(1);
        return 3;
    }
    if(scoreTeam2 == scoreTeam1) {
        permutation_t team1spirit = team1->getTeamSpirit();
        permutation_t team2spirit = team2->getTeamSpirit();
        if (team1spirit.strength() > team2spirit.strength()) {
            team1->setPoints(team1->getPoints() + 3);
            team1->getRootPlayer().lock()->setAdditionalGames(1);
            team2->getRootPlayer().lock()->setAdditionalGames(1);
            return 2;
        }
        if (team1spirit.strength() < team2spirit.strength()) {
            team2->setPoints(team2->getPoints() + 3);
            team1->getRootPlayer().lock()->setAdditionalGames(1);
            team2->getRootPlayer().lock()->setAdditionalGames(1);
            return 4;
        }
        if (team1spirit.strength() == team2spirit.strength()) {
            team1->setPoints(team2->getPoints() + 1);
            team2->setPoints(team2->getPoints() + 1);
            team1->getRootPlayer().lock()->setAdditionalGames(1);
            team2->getRootPlayer().lock()->setAdditionalGames(1);
            return 0;
        }
    }
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    int playerIndex = playersTable.findInHashTable(playerId);/////////////////////////////////////////
    if (playerIndex == -1){
        return StatusType::FAILURE;//there was never a player with this id
    }
    shared_ptr<Player> player = playersTable.getPlayerinIndex(playerIndex,playerId);
    Find(player);
    return player->getGamesPlayed();
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if (playerId <= 0 || cards < 0){
        return StatusType::INVALID_INPUT;
    }
    int playerIndex = playersTable.findInHashTable(playerId);/////////////////////////////////////////
    if (playerIndex == -1){
        return StatusType::FAILURE;//there was never a player with this id
    }
    shared_ptr<Player> player = playersTable.getPlayerinIndex(playerIndex,playerId);
    shared_ptr<Team> playersTeam = Find(player);
    if (!playersTeam->isActive1()){
        return StatusType::FAILURE;//the player is out of the competition
    }
    player->addCards(cards);
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    int playerIndex = playersTable.findInHashTable(playerId);/////////////////////////////////////////
    if (playerIndex == -1){
        return StatusType::FAILURE;//there was never a player with this id
    }
    shared_ptr<Player> player = playersTable.getPlayerinIndex(playerIndex,playerId);
    return player->getCards();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Team> team = *teamsById.find(make_shared<Team>(teamId));
    if (!team){
        return StatusType::FAILURE;
    }
    return team->getPoints();
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if (teamsById.getSize() == 0 || i >= teamsById.getSize() || i < 0){
        return StatusType::FAILURE;
    }
    shared_ptr<Team> teamAtRank = *teamsByPlayersAbility.Select(i+1);//because in the lecture rank was starting from 1, here from 0
    return teamAtRank->getTeamId();
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    int playerIndex = playersTable.findInHashTable(playerId);/////////////////////////////////////////
    if (playerIndex == -1){
        return StatusType::FAILURE;//there was never a player with this id
    }
    shared_ptr<Player> player = playersTable.getPlayerinIndex(playerIndex,playerId);
    shared_ptr<Team> playersTeam = Find(player);
    if (!playersTeam->isActive1()){
        return StatusType::FAILURE;//the player is out of the competition
    }
    return player->getPartialSpirit();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
    if (teamId2 == teamId1 || teamId2 <= 0 || teamId1 <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Team> team1 = *teamsById.find(make_shared<Team>(teamId1));
    shared_ptr<Team> team2 = *teamsById.find(make_shared<Team>(teamId2));
    if (!team1 || !team2){
        return StatusType::FAILURE;
    }
    teamsById.remove(team1);
    teamsById.remove(team2);
    teamsByPlayersAbility.remove(team1);
    teamsByPlayersAbility.remove(team2);
    shared_ptr<Team> newTeam = Union(team1, team2);

    //updating newTeam (spirit is updated in union
    newTeam->setTeamId(teamId1);//buyer
    newTeam->setSumAbility(team1->getSumAbility()+team2->getSumAbility());
    newTeam->setHasGoalKeeper(team1->HasGoalKeeper1() || team2->HasGoalKeeper1());
    newTeam->setSize(team1->getSize() + team2->getSize());
    newTeam->setPoints(team1->getPoints() + team2->getPoints());
    return StatusType::SUCCESS;
}
