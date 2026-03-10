#include <windows.h>
#include <filesystem>
#include <fstream>
#include <map>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

using namespace std;

vtable* caf_champions_league_vtable = new vtable((BYTE*)0x967574, 0xA0);

void caf_champions_league_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(caf_champions_league_vtable->vtable_ptr);
	DWORD x = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
	}
	if ((DWORD*)data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
			}
		}
		sub_9452CA_free(data->f173);
	}
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
		}
	}
	if (data->stages) {
		sub_9452CA_free((BYTE*)(data->stages));
		data->stages = 0;
	}
	if (data->f8) {
		sub_49F450((BYTE*)(data->f8));
		sub_944C94_free((BYTE*)(data->f8));
	}
	DWORD y = -1;
	sub_518690(_this);
}

void caf_champions_league_free(BYTE* _this, BYTE a2) {
	caf_champions_league_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) caf_champions_league_free_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call caf_champions_league_free
		add esp, 0x8
		ret 4
	}
}

DWORD caf_champions_league_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstQualifyingPhase, 0, NoTiebreak_1, AwayGoalsExtraTimePenalties_2, 8, 64, 32, 64, 0, 0, 2, 7, 0, 0, 74349);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 28), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SecondQualifyingPhase, 0, NoTiebreak_1, AwayGoalsExtraTimePenalties_2, 8, 32, 16, 0, 0, 0, 2, 7, 0, 0, 74349);

		return (DWORD)pMem;
	}
	else if (stage_idx < 4) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = AlphabeticGroupStage + stage_idx - 1;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx < 2) {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 22), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 29), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 24), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 31), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 7), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 14), year, Saturday);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 23), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 30), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 25), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 1), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 8), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 15), year, Sunday);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 4) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 16), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 14), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, AwayGoalsExtraTimePenalties_2, 8, 8, 4, 8, 0, 0, 2, 7, 0, 0, 669145);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 22), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 11), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, AwayGoalsExtraTimePenalties_2, 8, 4, 2, 0, 0, 0, 2, 7, 0, 0, 892193);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 15), year, Friday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, NoTiebreak_1, AwayGoalsExtraTimePenalties_2, 8, 2, 1, 0, 0, 0, 2, 9, 0, 4460964, 1486988);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) caf_champions_league_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call caf_champions_league_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int caf_champions_league_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[4];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) caf_champions_league_set_champion_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call caf_champions_league_set_champion
		add esp, 0x4
		ret 0
	}
}

void caf_cl_team_selection() {
	reset_club_euro_flags(AFRICA_9CF());
	// Last winner of Champions League
	cm3_club_comps* caf_cl = get_comp(CAF_CHAMPIONS_LEAGUE_9CF());
	cm3_clubs* caf_cl_winner = get_last_comp_winner(caf_cl);
	caf_cl_winner->ClubEuroFlag = CAF_CHAMPIONS_LEAGUE_9CF();
	caf_cl_winner->ClubEuroSeeding = 1;

	// Remaining teams
	vector<cm3_nations*> caf_nations = get_countries_of_continent(AFRICA_9CF());
	shuffle(caf_nations.begin(), caf_nations.end(), rng);
	BYTE excluded_count = 0;
	for (cm3_nations* caf_nation : caf_nations) {
		BYTE count = 1;
		if (find(caf_top12.begin(), caf_top12.end(), caf_nation->NationName) != caf_top12.end()) {
			count = 2;
		}
		else if (excluded_count < 3 && find(caf_worst.begin(), caf_worst.end(), caf_nation->NationName) != caf_worst.end()) {
			excluded_count++;
			continue;
		}
		BYTE j = 0;
		int required;
		if (filesystem::exists("Data/caf.cfg") && *current_year == (WORD)2025) {
			ifstream in("Data/caf.cfg", ios_base::in);
			string name;
			char nation[LONG_TXT_LENGTH];
			required = -1;
			while (std::getline(in, name))
			{
				if (name.size() == 0) {
					if (required == -1) continue;
					else break;
				}
				if (name[0] == '*') {
					strcpy_s(nation, name.substr(1).c_str());
					if (_strcmpi(nation, caf_nation->NationName) == 0)
					{
						required = count;
						//dprintf("[CL] Getting clubs from caf.cfg: %s - max %d\n", nation, required);
					}
					else {
						required = -1;
					}
					continue;
				}
				if (_strcmpi(nation, caf_nation->NationName) != 0) continue;
				if (j >= required) continue;
				cm3_clubs* caf_club = find_club(name.c_str());
				if (!caf_club || !caf_club->ClubNation || caf_club->ClubNation != caf_nation) {
					//dprintf("Club %s not found, skipping\n", name.c_str());
				}
				else if (caf_club->ClubEuroFlag != -1) {
					//dprintf("Club %s is already in a CAF competition, skipping\n", (caf_club->ClubName));
				}
				else {
					//dprintf("Setting club %s to Champions League\n", (caf_club->ClubName));
					caf_club->ClubEuroFlag = CAF_CHAMPIONS_LEAGUE_9CF();
					caf_club->ClubEuroSeeding = 0;
					j++;
				}
			}
		}

		//if (j < count) dprintf("[CL] Getting clubs from database - best\n");
		vector<cm3_clubs*> clubs;
		bool playable = caf_nation->NationLeagueSelected;
		if (playable) {
			// playable
			clubs = find_clubs_of_country_for_euro_playable(caf_nation->NationID);
			sort(clubs.begin(), clubs.end(), compareClubLastDivPos);
		}
		else {
			// not playable
			clubs = find_clubs_of_country_for_euro(caf_nation->NationID);
			sort(clubs.begin(), clubs.end(), compareClubRep);
		}
		size_t max_count = count + 2 - j;
		if (max_count > clubs.size()) max_count = clubs.size();
		for (; j < count; j++) {
			int idx = 0;
			if (!playable) idx = rand() % max_count;
			cm3_clubs* caf_club = clubs[idx];
			//dprintf("Setting club %s to Champions League\n", (caf_club->ClubName));
			caf_club->ClubEuroFlag = CAF_CHAMPIONS_LEAGUE_9CF();
			caf_club->ClubEuroSeeding = 0;
			clubs.erase(clubs.begin() + idx);
			max_count--;
		}
	}
}

void caf_champions_league_all_teams(BYTE* _this) {
	caf_cl_team_selection();

	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 64;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	DWORD teams_r1 = 0;
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == CAF_CHAMPIONS_LEAGUE_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			teams[teams_r1].club = club;
			teams[teams_r1].f5 = 0;
			teams[teams_r1].f6 = 0;
			teams_r1++;
		}
	}
}

void caf_champions_league_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 64;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	WORD count = 0;
	DWORD total_count = data->special_nteams_seedings;
	for (WORD i = 0; i < total_count; i++) {
		teams[i].club = qualifiers[i].club;
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}
}

void caf_champions_league_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		teams_seeded* all_teams = (teams_seeded*)comp_data->special_teams_seedings;
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < comp_data->special_nteams_seedings; i++)
		{
			clubs.push_back(all_teams[i].club);
		}
		sort(clubs.begin(), clubs.end(), compareClubRep);

		sub_4A2540((BYTE*)comp_data->f8, clubs[0], 1);
		sub_4A2540((BYTE*)comp_data->f8, clubs[1], 2);
		for (int i = 2; i < 4; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 3);
		}
		for (int i = 4; i < 8; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 5);
		}
		for (int i = 8; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (int i = 12; i < 16; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (int i = 16; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 32; i < 64; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
	}
}

void __declspec(naked) caf_champions_league_reputation_setup_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call caf_champions_league_reputation_setup
		add esp, 0x4
		ret
	}
}

void caf_champions_league_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		if (max == 1) ret_max = 13;
	}
	else if (stage < 4) {
		ret_current = 1 + 4 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 4 * (min - 1);
		if (max < 3) ret_max = 5;
		else ret_max = 1 + 4 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 4) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) caf_champions_league_reputation_calc_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call caf_champions_league_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

char caf_champions_league_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
		data->teams_list = 0;
	}
	if (data->special_teams_seedings) {
		sub_9452CA_free(data->special_teams_seedings);
		data->special_nteams_seedings = 0;
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
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
		}
	}
	data->current_stage = -1;
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	caf_champions_league_all_teams(_this);
	caf_champions_league_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) caf_champions_league_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call caf_champions_league_update
		add esp, 0x4
		ret
	}
}

void caf_champions_league_group_stage_setup(BYTE* _this) {
	char stage_num = 0;
	DWORD v1 = *(DWORD*)_this;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 2, 0, 0, 0 };
	BYTE tiebreaks[4] = { CurrentPositionTiebreaker, GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < comp_data->special_nteams_seedings; i++) {
		if (teams[i].club->ClubEuroFlag == comp_data->competition_db->ClubCompID)
			clubs.push_back(teams[i].club);
	}
	if (clubs.size() != 16)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(comp_data->competition_db->ClubCompName, msg.c_str(), true);
	}

	sort(clubs.begin(), clubs.end(), compareClubSeeding);
	shuffle(clubs.begin(), clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.begin() + 12, rng);
	shuffle(clubs.begin() + 12, clubs.end(), rng);

	WORD group_teams = 4;
	for (int i = 0; i < 4; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 4 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 8, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 8, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void caf_champions_league_final_stage_setup(BYTE* _this) {
	char stage_num = 4;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	vector<cm3_clubs*> clubs;
	for (char al = 0; al < 4; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == Qualified1) {
				clubs.push_back(tls.club);
			}
		}
	}

	BYTE team_order[8] = { 0,3,4,7,6,5,2,1 };
	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)clubs[j];
	}

	// for each team in pteams:
	// call 7e9180(AE28F0_ptr + 4 * comp->rules, team)

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	for (char al = 0; al < 4; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate != Qualified1) {
				staff_history_knocked_out_86C000(staff_hist_ptr, tls.club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
				tls.club->ClubEuroFlag = -1;
				int ret = sub_5A0590(ae2a38_ptr, (BYTE*)tls.club);
				AddToClubIncome((BYTE*)ret, 520446);
				AddMoneyFromComp(_this, (BYTE*)tls.club, 520446, 0, -1, GroupStage, 0, -2);
			}
		}
	}
}

void caf_champions_league_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			caf_champions_league_group_stage_setup(_this);
		}
		else if (current == 4) {
			caf_champions_league_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) caf_champions_league_stages_create_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call caf_champions_league_stages_create
		add esp, 0x4
		ret
	}
}

int caf_champions_league_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0x1E);
			//*a5 = 1;
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage < 4) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
			return 0;
		case TopPlayoff:
			//staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, TenthRound, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage == 4) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			club->ClubEuroFlag = -1;
			//*a5 = 1;
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

void __declspec(naked) caf_champions_league_set_table_fate()		// used as a __thiscall -> __cdecl converter
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
		call caf_champions_league_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void caf_champions_league_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->year = year;
	data->comp_vtable = (DWORD*)(caf_champions_league_vtable->vtable_ptr);
	caf_champions_league_vtable->SetPointer(VTableInitFree, (DWORD)&caf_champions_league_free_c);
	caf_champions_league_vtable->SetPointer(VTableEoSUpdate, (DWORD)&caf_champions_league_update_c);
	caf_champions_league_vtable->SetPointer(VTablePlayoffQual, (DWORD)&caf_champions_league_stages_create_c);
	caf_champions_league_vtable->SetPointer(VTableSetChampion, (DWORD)&caf_champions_league_set_champion_c);
	caf_champions_league_vtable->SetPointer(VTableClubLandmarks, 0x48cab0);
	caf_champions_league_vtable->SetPointer(VTableFixtures, (DWORD)&caf_champions_league_fixture_caller);
	caf_champions_league_vtable->SetPointer(VTableTableFates, (DWORD)&caf_champions_league_set_table_fate);
	caf_champions_league_vtable->SetPointer(VTableStageNews, 0x48C6D0);
	caf_champions_league_vtable->SetPointer(VTableReputationSetup, (DWORD)&caf_champions_league_reputation_setup_c);
	caf_champions_league_vtable->SetPointer(VTableReputationCalc, (DWORD)&caf_champions_league_reputation_calc_c);
	caf_champions_league_vtable->SetPointer(VTableSubsRounds, 0x858e70);
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 5;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	data->competition_db = comp;
	data->comp_type = CLUB_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f82 = 3;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = 0x29;
	data->f81 = 0xa;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_BROWN_1_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_YELLOW_2_9CF());
	caf_champions_league_all_teams(_this);
	caf_champions_league_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	caf_champions_league_reputation_setup(_this);
}

void setup_caf_champions_league() {
}