#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\Helper.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include "Helpers\constants.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include <Helpers\9cf_constants.h>

DWORD* concacaf_champions_cup_vtable = (DWORD*)0x968AA0;

DWORD concacaf_champions_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 5;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 1, 14), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 2, 5), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 2, 22, 11, 22, 0, 0, 2, 14);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 2, 27), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 3, 5), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 2, 16, 8, 5, 22, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 3, 13), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 2), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 2, 8, 4, 0, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 10), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 23), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 2, 4, 2, 0, 0, 0, 2, 7, 0, 0, prizeMoneyFile.GetInt("concacaf_cl_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 1), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 1), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 0, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("concacaf_cl_final_win"), prizeMoneyFile.GetInt("concacaf_cl_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) concacaf_champions_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call concacaf_champions_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

// Function that will add numbereOfClubs from szNation to vec
void add_clubs_for_concacaf_comps(long nation_id, int numberOfClubs, char seeding = 0)
{
	cm3_nations* nation = get_country(nation_id);

	// If nation has any active leagues, sort clubs by last division & position and pick top clubs from the list
	// May redo at a later point to better check if we're getting clubs from the top division, currently assumes top division has the highest reputation
	if (nation->NationLeagueSelected) {
		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro_playable(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubLastDivPos);
		int j = 0;
		for (int i = 0; i < numberOfClubs; i++)
		{
			cm3_clubs* club = nation_clubs[j++];

			if (club->ClubEuroFlag == -1) {
				//dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				club->ClubEuroFlag = CONCACAF_CHAMPIONS_CUP_9CF();
				club->ClubEuroSeeding = seeding;
			}
			else
				i--;	// Else do again as the club selected was already picked
		}
	}
	// If country is not playable, pick random clubs from the top 10 by reputation
	else {
		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubRep);

		int TeamsToSelectFrom = (nation_clubs.size() < 10) ? nation_clubs.size() : 10;

		if (TeamsToSelectFrom < numberOfClubs)
		{
			// If we can't get this country's clubs - then just get some more USA or Mexico ones
			add_clubs_for_concacaf_comps(((rand() % 2) == 0) ? NATION_USA_9CF() : NATION_MEXICO_9CF(), numberOfClubs, seeding);
			return;
		}

		for (int i = 0; i < numberOfClubs; i++)
		{
			cm3_clubs* club = nation_clubs[rand() % TeamsToSelectFrom];

			if (club->ClubEuroFlag == -1) {
				//dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				club->ClubEuroFlag = CONCACAF_CHAMPIONS_CUP_9CF();
				club->ClubEuroSeeding = seeding;
			}
			else
				i--;	// Else do again as the club selected was already picked
		}
	}
}

// Similar to add_clubs_for_concacaf_comps, but gets random Central American clubs
void add_central_american_clubs(int numberOfCountries, int clubsPerCountry = 1, char seeding = 0)
{
	vector<cm3_nations*> nations = central_america_countries();
	int sz = nations.size();
	sort(nations.begin(), nations.end(), [](const cm3_nations* n1, const cm3_nations* n2) {
		return n1->NationReputation > n2->NationReputation;
		});

	int CountriesToSelectFrom = (sz < 8) ? sz : 8;
	for (int i = 0; i < numberOfCountries; i++) {
		cm3_nations* nation = nations[rand() % CountriesToSelectFrom];
		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubRep);

		int TeamsToSelectFrom = (nation_clubs.size() < 10) ? nation_clubs.size() : 10;

		if (TeamsToSelectFrom < clubsPerCountry)
		{
			// If we can't get this countries clubs - then just get some more USA or Mexico ones
			add_clubs_for_concacaf_comps(((rand() % 2) == 0) ? NATION_USA_9CF() : NATION_MEXICO_9CF(), clubsPerCountry, seeding);
			return;
		}

		for (int j = 0; j < clubsPerCountry; j++)
		{
			cm3_clubs* club = nation_clubs[rand() % TeamsToSelectFrom];

			if (club->ClubEuroFlag == -1) {
				//dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				club->ClubEuroFlag = CONCACAF_CHAMPIONS_CUP_9CF();
				club->ClubEuroSeeding = seeding;
			}
			else
				j--;	// Else do again as the club selected was already picked
		}
	}
}

// Similar to add_clubs_for_concacaf_comps, but gets random Caribbean clubs
void add_caribbean_clubs(int numberOfCountries, int clubsPerCountry = 1, char seeding = 0)
{
	vector<cm3_nations*> nations = caribbean_countries();
	int sz = nations.size();
	sort(nations.begin(), nations.end(), [](const cm3_nations* n1, const cm3_nations* n2) {
		return n1->NationReputation > n2->NationReputation;
		});

	int CountriesToSelectFrom = (sz < 6) ? sz : 6;
	for (int i = 0; i < numberOfCountries; i++) {
		cm3_nations* nation = nations[rand() % CountriesToSelectFrom];

		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubRep);

		int TeamsToSelectFrom = (nation_clubs.size() < 10) ? nation_clubs.size() : 10;

		if (TeamsToSelectFrom < clubsPerCountry)
		{
			// If we can't get this countries clubs - then just get some more USA or Mexico ones
			add_clubs_for_concacaf_comps(((rand() % 2) == 0) ? NATION_USA_9CF() : NATION_MEXICO_9CF(), clubsPerCountry, seeding);
			return;
		}

		for (int j = 0; j < clubsPerCountry; j++)
		{
			cm3_clubs* club = nation_clubs[rand() % TeamsToSelectFrom];

			if (club->ClubEuroFlag == -1) {
				//dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				club->ClubEuroFlag = CONCACAF_CHAMPIONS_CUP_9CF();
				club->ClubEuroSeeding = seeding;
			}
			else
				j--;	// Else do again as the club selected was already picked
		}
	}
}

// Similar to get_cup_winner_for_concacaf, but will search for the runner-up instead
void get_cup_loser_for_concacaf(long nation_id, long comp_id, char seeding = 0)
{
	cm3_nations* nation = get_country(nation_id);

	if (nation->NationLeagueSelected) {
		cm3_club_comps* comp = &(*club_comps)[comp_id];
		if (!comp) {
			//dprintf("Competition %ld not found, getting backup club\n", comp_id);
			add_clubs_for_concacaf_comps(nation_id, 1, seeding);
		}
		else {
			cm3_clubs* last_runner_up = get_last_comp_runner_up(comp);
			if (!last_runner_up || !last_runner_up->ClubNation) {
				//dprintf("Last runner-up of %s not found or invalid, getting backup club\n", comp->ClubCompName);
				add_clubs_for_concacaf_comps(nation_id, 1, seeding);
			}
			else {
				if (last_runner_up->ClubEuroFlag != -1) {
					//dprintf("Last runner-up of %s (%s) is already qualified, getting backup club\n", comp->ClubCompName, (last_runner_up->ClubName));
					add_clubs_for_concacaf_comps(nation_id, 1, seeding);
				}
				else {
					//dprintf("Setting club %s to CONCACAF Champions Cup (last runner-up of %s)\n", (last_runner_up->ClubName), comp->ClubCompName);
					last_runner_up->ClubEuroFlag = CONCACAF_CHAMPIONS_CUP_9CF();
					last_runner_up->ClubEuroSeeding = seeding;
				}
			}
		}
	}
	else {
		//dprintf("Country %s is inactive, getting backup club\n", szNation);
		add_clubs_for_concacaf_comps(nation_id, 1, seeding);
	}
}

// Tries to find the latest cup winner from comp_id to add to the competition
// szNation is provided as a backup in case the competition can't be found, or there is no available club in the history
// loser_backup decides if the cup loser can be used when the winner has already been qualified, or if the place should go to the best available club in the league instead
void get_cup_winner_for_concacaf(long nation_id, long comp_id, bool loser_backup = true, char seeding = 0)
{
	cm3_nations* nation = get_country(nation_id);

	// Only search for history if the nation has active competitions, otherwise it will always use the same club
	// May redo at a later point to check if the actual competition is active instead
	if (nation->NationLeagueSelected) {
		cm3_club_comps* comp = &(*club_comps)[comp_id];
		if (!comp) {
			//dprintf("Competition %ld not found, getting backup club\n", comp_id);
			add_clubs_for_concacaf_comps(nation_id, 1, seeding);
		}
		else {
			cm3_clubs* last_winner = get_last_comp_winner(comp);
			if (!last_winner || !last_winner->ClubNation) {
				//dprintf("Last winner of %s not found or invalid, getting backup club\n", comp->ClubCompName);
				add_clubs_for_concacaf_comps(nation_id, 1, seeding);
			}
			else {
				if (last_winner->ClubEuroFlag != -1) {
					//dprintf("Last winner of %s (%s) is already qualified, getting backup club\n", comp->ClubCompName, (last_winner->ClubName));
					if (loser_backup) get_cup_loser_for_concacaf(nation_id, comp_id, seeding);
					else add_clubs_for_concacaf_comps(nation_id, 1, seeding);
				}
				else {
					//dprintf("Setting club %s to CONCACAF Champions Cup (last winners of %s)\n", (last_winner->ClubName), comp->ClubCompName);
					last_winner->ClubEuroFlag = CONCACAF_CHAMPIONS_CUP_9CF();
					last_winner->ClubEuroSeeding = seeding;
				}
			}
		}
	}
	// If nation has no active competitions, get a random top club instead
	else {
		//dprintf("Country %s is inactive, getting backup club\n", szNation);
		add_clubs_for_concacaf_comps(nation_id, 1, seeding);
	}
}

void concacaf_cup_team_selection() {
	reset_club_euro_flags(NORTH_AMERICA_9CF());

	// If there is a .cfg file, uses it to get preset teams for the first year
	// Includes failsafes in case any of the clubs can't be found or are already qualified for some reason
	if (std::filesystem::exists("Data/concacaf.cfg") && *current_year == START_YEAR) {
		//dprintf("Getting preset teams for CONCACAF\n");
		ifstream in("Data/concacaf.cfg", ios_base::in);
		string name;
		char nation[LONG_TXT_LENGTH];
		cm3_nations* nation_ptr;
		int count = 0;
		while (std::getline(in, name))
		{
			if (name.size() == 0) {
				continue;
			}
			if (name[0] == '*') {
				strcpy_s(nation, name.substr(1).c_str());
				nation_ptr = find_country(nation);
				continue;
			}
			cm3_clubs* club = find_club(name.c_str());
			if (!club || !club->ClubNation) {
				//dprintf("Club %s not found, getting backup from %s\n", name.c_str(), nation);
				add_clubs_for_concacaf_comps(nation_ptr->NationID, 1, count >= 22);
			}
			else if (club->ClubEuroFlag != -1) {
				//dprintf("Club %s already qualified, getting backup from %s\n", name.c_str(), nation);
				add_clubs_for_concacaf_comps(nation_ptr->NationID, 1, count >= 22);
			}
			else {
				//dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				club->ClubEuroFlag = CONCACAF_CHAMPIONS_CUP_9CF();
				club->ClubEuroSeeding = count >= 22;
			}
			count++;
		}
		in.close();
	}
	// After the first year, or if there is no .cfg, gets teams based on last league positions, or random top clubs depending on the case
	else {
		//dprintf("Getting teams for CONCACAF based on last season performance\n");
		int rnd = rand() % 2;

		// Since the MLS has playoffs to decide the winner, I used the functions to get cup winners/losers first
		get_cup_winner_for_concacaf(NATION_USA_9CF(), USA_MLS_9CF(), false, 1); // USA champions
		get_cup_loser_for_concacaf(NATION_USA_9CF(), USA_MLS_9CF()); // USA runner-up
		get_cup_winner_for_concacaf(NATION_USA_9CF(), USA_OPEN_CUP_9CF(), true); // USA cup winner
		add_clubs_for_concacaf_comps(NATION_USA_9CF(), 1, 1); // Leagues Cup
		add_clubs_for_concacaf_comps(NATION_USA_9CF(), 3); // USA
		add_clubs_for_concacaf_comps(NATION_USA_9CF(), 1); // Leagues Cup
		add_clubs_for_concacaf_comps(NATION_MEXICO_9CF(), 1, 1); // Mexico champions
		add_clubs_for_concacaf_comps(NATION_MEXICO_9CF(), 1); // Leagues Cup
		add_clubs_for_concacaf_comps(NATION_MEXICO_9CF(), 5); // Mexico
		add_clubs_for_concacaf_comps(NATION_CANADA_9CF(), 3); // Canada
		add_central_american_clubs(1, 1, 1); // Central America winner
		add_central_american_clubs(5, 1); // Central America
		add_caribbean_clubs(1, 1, 1); // Caribbean winner
		add_caribbean_clubs(2, 1); // Caribbean
	}
	//dprintf("\n");
}

void concacaf_champions_cup_all_teams(BYTE* _this) {
	concacaf_cup_team_selection();

	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 27;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	DWORD teams_r1 = 0;
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == CONCACAF_CHAMPIONS_CUP_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			teams[teams_r1].club = club;
			teams[teams_r1].f5 = 0 + 3 * seed;
			teams[teams_r1].f6 = 0;
			teams_r1++;
		}
	}
}

void concacaf_champions_cup_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 27;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	DWORD count = 0;
	DWORD total_count = data->special_nteams_seedings;
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 0) {
			teams[count].club = qualifiers[i].club;
			teams[count].f5 = 0;
			teams[count].f6 = 0;
			count++;
		}
	}
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 3) {
			teams[count].club = qualifiers[i].club;
			teams[count].f5 = 1;
			teams[count].f6 = 0;
			count++;
		}
	}
}

char concacaf_champions_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
		data->teams_list = 0;
	}
	if (data->special_teams_seedings) {
		sub_9452CA_free(data->special_teams_seedings);
		data->special_teams_seedings = 0;
	}
	if (data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
		data->rounds_list = 0;
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
				data->f173[i] = 0;
			}
		}
		sub_9452CA_free(data->f173);
		data->f173 = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->current_stage = -1;
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	concacaf_champions_cup_all_teams(_this);
	concacaf_champions_cup_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) concacaf_champions_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call concacaf_champions_cup_update
		add esp, 0x4
		ret
	}
}

int concacaf_champions_cup_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			club->ClubEuroFlag = -1;
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			club->ClubEuroFlag = -1;
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) concacaf_champions_cup_set_table_fate()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call concacaf_champions_cup_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void concacaf_champions_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->year = year;
	data->comp_vtable = concacaf_champions_cup_vtable;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->competition_db = comp;
	data->comp_type = CLUB_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f82 = 3;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesSouthAmerica;
	data->f81 = 0xa;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	concacaf_champions_cup_all_teams(_this);
	concacaf_champions_cup_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	cup_reputation_setup_generic_5223A0(_this);
}

void setup_concacaf_champions_cup()
{
	WriteVTablePtr(concacaf_champions_cup_vtable, VTableEoSUpdate, (DWORD)&concacaf_champions_cup_update_c);
	WriteVTablePtr(concacaf_champions_cup_vtable, VTableLeagueSplit, 0x51F890);
	WriteVTablePtr(concacaf_champions_cup_vtable, VTableFixtures, (DWORD)&concacaf_champions_cup_fixture_caller);
	WriteVTablePtr(concacaf_champions_cup_vtable, VTableTableFates, (DWORD)&concacaf_champions_cup_set_table_fate);
	WriteVTablePtr(concacaf_champions_cup_vtable, VTableSubsRounds, 0x858e70);
}