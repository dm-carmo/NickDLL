#include <Windows.h>
#include "generic_functions.h"
#include "Structures\CMHeader.h"
#include "Helper.h"
#include "constants.h"
#include <currency.h>

// Generic function that will add teams to a league competition
int AddTeams(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;

	// Count the number of teams first, as the code really expects us to know up front
	WORD numberOfLeagueTeams = CountNumberOfTeamsInComp(CompID);

	// Now let's add the teams
	comp_data->n_teams = numberOfLeagueTeams; // number of teams
	comp_data->team_league_table = (DWORD*)sub_944E46_malloc(numberOfLeagueTeams * league_team_list_sz); // number of teams * 59 (0x3B)
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == CompID)
			add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

// Generic function that will add teams to a league competition - uses Reserve Division
int AddTeamsReserveDivision(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;

	// Count the number of teams first, as the code really expects us to know up front
	WORD numberOfLeagueTeams = CountNumberOfTeamsInReserveComp(CompID);

	// Now let's add the teams
	comp_data->n_teams = numberOfLeagueTeams; // number of teams
	comp_data->team_league_table = (DWORD*)sub_944E46_malloc(numberOfLeagueTeams * league_team_list_sz); // number of teams * 59 (0x3B)
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubReserveDivision && club->ClubReserveDivision->ClubCompID == CompID)
			add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

// Generic function that will add teams to a league competition that has groups
int AddTeamsGroupLeague(BYTE* _this, DWORD first_group_id)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;

	// Count the number of teams first, as the code really expects us to know up front
	WORD numberOfLeagueTeams = CountNumberOfTeamsInCompWithGroup(CompID, first_group_id);

	// Now let's add the teams
	comp_data->n_teams = numberOfLeagueTeams; // number of teams
	comp_data->team_league_table = (DWORD*)sub_944E46_malloc(numberOfLeagueTeams * league_team_list_sz); // number of teams * 59 (0x3B)
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == CompID
			&& club->ClubReserveDivision && club->ClubReserveDivision->ClubCompID == first_group_id)
			add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

typedef BYTE* (__thiscall* league_init_typedef)(BYTE* _this, __int16 a2, cm3_club_comps* a3);
void AddLeague(BYTE* _this, const char* szLeagueName, int leagueNo, int year, DWORD league_init_addr)
{
	dprintf("Adding (This: %08X) league %s at slot %d for year %d (calling init addr: %08X).\n", (DWORD)_this, szLeagueName, leagueNo, (short)year, league_init_addr);
	cm3_club_comps* comp = find_club_comp(szLeagueName);
	if (comp)
	{
		BYTE* ee_bytes = (BYTE*)sub_944CF1_operator_new(0xEE);
		league_init_typedef init_call = (league_init_typedef)(league_init_addr);
		BYTE* leagueSetupPtr = init_call(ee_bytes, (short)*current_year, comp);
		DWORD* compPtrTable = *(DWORD**)(_this + 0x10);
		compPtrTable[leagueNo] = (DWORD)leagueSetupPtr;
	}
	else
		dprintf("Could not find comp %s!", szLeagueName);
}

// Creates a fixture block with the specified data
void AddFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_fixture_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, timeOfDay, startYear, stadiumType);
}

// Creates a block with the specified data, that defines days to move matches for TV
void AddFixtureTV(BYTE* pMem, int fixture, int tv_id, int num_to_move, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_fixture_tv_days_call(pMem, fixture, tv_id, dayOfWeek, timeOfDay, num_to_move, stadiumType);
}

// Creates a fixture block with the specified data, with a shortcut to add a TV days block with nothing defined
void AddFixtureNoTV(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_fixture_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, timeOfDay, startYear, stadiumType);
	add_fixture_tv_days_call(pMem, fixture, 0, -1, -1, -1, 0);
}

// Creates a cup/playoff fixture block with the specified data
void AddPlayoffFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_playoff_fixture_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, timeOfDay, startYear, stadiumType);
}

// Creates a block with the specified data, that defines days to move matches for TV - playoffs
void AddPlayoffTVFixture(BYTE* pMem, int fixture, int tv_id, int num_to_move, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_playoff_tv_fixture_date_call(pMem, fixture, tv_id, dayOfWeek, timeOfDay, num_to_move, stadiumType);
}

// Creates a cup/playoff draw date block with the specified data
void AddPlayoffDrawFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */)
{
	add_playoff_draw_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, startYear);
}

// Fills in details for cup/playoff fixtures, based on this information: https://champman0102.net/viewtopic.php?p=16076#p16076
void FillFixtureDetails(BYTE* pMem, int fixture, WORD stage_name, WORD draw_type, WORD game_1_tiebreak, WORD game_2_tiebreak, BYTE unk17, WORD teams_in_round,
	WORD num_games, WORD new_teams_in_round, WORD total_teams_in, BYTE replays, BYTE legs, BYTE days_between_games,
	DWORD prize_reach, DWORD prize_win, DWORD prize_lose, WORD game_3_tiebreak)
{
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x7) = stage_name;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x9) = fixture;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0xB) = draw_type;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0xD) = game_1_tiebreak;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0xF) = game_2_tiebreak;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x11) = game_3_tiebreak;
	*(BYTE*)(pMem + (fixture * playoff_dates_sz) + 0x17) = unk17;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x18) = teams_in_round;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x1A) = num_games;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x1C) = new_teams_in_round;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x1E) = total_teams_in;
	*(BYTE*)(pMem + (fixture * playoff_dates_sz) + 0x20) = replays;
	*(BYTE*)(pMem + (fixture * playoff_dates_sz) + 0x21) = legs;
	*(BYTE*)(pMem + (fixture * playoff_dates_sz) + 0x22) = days_between_games;
	*(DWORD*)(pMem + (fixture * playoff_dates_sz) + 0x5C) = (DWORD)(prize_reach / inflation_mult * general_mult);
	*(DWORD*)(pMem + (fixture * playoff_dates_sz) + 0x60) = (DWORD)(prize_win / inflation_mult * general_mult);
	*(DWORD*)(pMem + (fixture * playoff_dates_sz) + 0x64) = (DWORD)(prize_lose / inflation_mult * general_mult);
}

void WriteVTablePtr(DWORD* addr, int pos, DWORD data) {
	WriteDWORD((DWORD)addr + 4 * (pos - 1), data);
}

int SetupPrizeMoney(BYTE* _this, int base_amount) {
	return add_prize_money_682F70(_this, (int)(base_amount / inflation_mult * general_mult));
}

int SetupTVMoney(BYTE* _this, int amount, cm3_club_comps* last_division) {
	return add_tv_money_683010(_this, (int)(amount / inflation_mult * general_mult), last_division);
}

int AddMoneyFromComp(BYTE* _this, BYTE* club, int money, int a4, char position, WORD stage_name_idx, BYTE* a7, char a8) {
	return add_money_to_club_from_comp_48E3E0(_this, club, (int)(money / inflation_mult * general_mult), a4, position, stage_name_idx, a7, a8);
}

int AddToClubIncome(BYTE* _this, int money) {
	return add_to_income_prize_money_5999A0(_this, (int)(money / inflation_mult * general_mult));
}