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

DWORD* ofc_champions_league_vtable = (DWORD*)0x96E018;

DWORD ofc_champions_league_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = PreliminaryRound;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 1, 31), year, Saturday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 2, 3), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 2, 6), year, Friday, Evening);

		return (DWORD)pMem;
	}
	else if (stage_idx < 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = AlphabeticGroupStage + stage_idx - 1;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx == 0) {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 9), year, Sunday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 12), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 15), year, Saturday, Evening);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 10), year, Monday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 13), year, Thursday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 16), year, Sunday, Evening);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 17), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 19), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 4, 2, 4, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("ofc_cl_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 20), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 22), year, Saturday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("ofc_cl_final_win"), prizeMoneyFile.GetInt("ofc_cl_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) ofc_champions_league_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ofc_champions_league_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int ofc_champions_league_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[2];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) ofc_champions_league_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ofc_champions_league_set_champion
		add esp, 0x4
		ret 0
	}
}

void ofc_champions_league_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 8;
	comp_data->comp_type = CLUB_INTERNATIONAL;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->f82 = 3;

	comp_data->promotions = 1;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x28;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) ofc_champions_league_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ofc_champions_league_subs
		add esp, 0x4
		ret
	}
}

void ofc_cl_team_selection() {
	reset_club_euro_flags(OCEANIA_9CF());

	vector<cm3_nations*> ofc_nations = get_countries_of_continent(OCEANIA_9CF());
	vector<DWORD> bottom4 = ofc_bottom_4_nations();
	for (cm3_nations* ofc_nation : ofc_nations) {
		bool in_prelim = find(bottom4.begin(), bottom4.end(), ofc_nation->NationID) != bottom4.end();
		BYTE j = 0;
		if (filesystem::exists("Data/ofc.cfg") && *current_year == (WORD)START_YEAR) {
			ifstream in("Data/ofc.cfg", ios_base::in);
			string name;
			char nation[LONG_TXT_LENGTH];
			cm3_nations* nation_ptr;
			int required = -1;
			while (std::getline(in, name))
			{
				if (name.size() == 0) {
					if (required == -1) continue;
					else break;
				}
				if (name[0] == '*') {
					strcpy_s(nation, name.substr(1).c_str());
					nation_ptr = find_country(nation);
					if (ofc_nation == nation_ptr)
					{
						required = 1;
						//dprintf("[CL] Getting clubs from ofc.cfg: %s - max %d\n", nation, required);
					}
					else {
						required = -1;
					}
					continue;
				}
				if (ofc_nation != nation_ptr) continue;
				if (j >= required) continue;
				cm3_clubs* ofc_club = find_club(name.c_str());
				if (!ofc_club || !ofc_club->ClubNation || ofc_club->ClubNation != ofc_nation) {
					//dprintf("Club %s not found, skipping\n", name.c_str());
				}
				else if (ofc_club->ClubEuroFlag != -1) {
					//dprintf("Club %s is already in a OFC competition, skipping\n", (ofc_club->ClubName));
				}
				else {
					//dprintf("Setting club %s to Champions League\n", (ofc_club->ClubName));
					ofc_club->ClubEuroFlag = OFC_CHAMPIONS_LEAGUE_9CF();
					ofc_club->ClubEuroSeeding = !in_prelim;
					j++;
				}
			}
		}

		//if (j < 1) dprintf("[CL] Getting clubs from database - best\n");
		vector<cm3_clubs*> clubs;
		bool playable = ofc_nation->NationLeagueSelected;
		if (playable) {
			// playable
			clubs = find_clubs_of_country_for_euro_playable(ofc_nation->NationID);
			sort(clubs.begin(), clubs.end(), compareClubLastDivPos);
		}
		else {
			// not playable
			clubs = find_clubs_of_country_for_euro(ofc_nation->NationID);
			sort(clubs.begin(), clubs.end(), compareClubRep);
		}
		size_t max_count = 3 - j;
		if (max_count > clubs.size()) max_count = clubs.size();
		if (j < 1) {
			int idx = 0;
			if (!playable) idx = rand() % max_count;
			cm3_clubs* ofc_club = clubs[idx];
			//dprintf("Setting club %s to Champions League\n", (ofc_club->ClubName));
			ofc_club->ClubEuroFlag = OFC_CHAMPIONS_LEAGUE_9CF();
			ofc_club->ClubEuroSeeding = !in_prelim;
		}
	}
}

void ofc_champions_league_all_teams(BYTE* _this) {
	ofc_cl_team_selection();

	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 11;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	DWORD teams_r1 = 0;
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == OFC_CHAMPIONS_LEAGUE_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			teams[teams_r1].club = club;
			teams[teams_r1].f5 = 3 * seed;
			teams[teams_r1].f6 = 0;
			teams_r1++;
		}
	}
}

void ofc_champions_league_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* pMem = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams);

	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;

	BYTE teamsAdded = 0;
	DWORD total_count = data->special_nteams_seedings;
	for (WORD i = 0; i < total_count; i++) {
		if (qualifiers[i].f5 == 0)
		{
			add_team_call(_this, teamsAdded++, qualifiers[i].club, 0, 0);
		}
	}
}

void ofc_champions_league_group_stage_setup(BYTE* _this) {
	char stage_num = 0;
	DWORD v1 = *(DWORD*)_this;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate != Qualified1) {
			tls.club->ClubEuroFlag = -1;
		}
	}

	char prom_rel[4] = { 2, 0, 0, 0 };
	char tiebreaks[4] = { CurrentPositionTiebreaker, GoalDifferenceTiebreaker, GoalsForTiebreaker, NoTiebreaker };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < comp_data->special_nteams_seedings; i++) {
		if (teams[i].club->ClubEuroFlag == comp_data->competition_db->ClubCompID)
			clubs.push_back(teams[i].club);
	}
	if (clubs.size() != 8)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(comp_data->competition_db->ClubCompName, msg.c_str(), true);
	}

	sort(clubs.begin(), clubs.end(), compareClubSeeding);
	shuffle(clubs.begin(), clubs.begin() + 2, rng);
	shuffle(clubs.begin() + 2, clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 6, rng);
	shuffle(clubs.begin() + 6, clubs.end(), rng);

	WORD group_teams = 4;
	for (int i = 0; i < 2; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 2 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 1, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 8, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void ofc_champions_league_final_stage_setup(BYTE* _this) {
	char stage_num = 2;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	vector<cm3_clubs*> clubs;
	for (char al = 0; al < 2; al++) {
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

	BYTE team_order[4] = { 0,3,2,1 };
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
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	for (char al = 0; al < 2; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate != Qualified1) {
				tls.club->ClubEuroFlag = -1;
			}
		}
	}
}

void ofc_champions_league_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			ofc_champions_league_group_stage_setup(_this);
		}
		else if (current == 2) {
			ofc_champions_league_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) ofc_champions_league_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ofc_champions_league_stages_create
		add esp, 0x4
		ret
	}
}

void ofc_champions_league_reputation_setup(BYTE* _this) {
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
		for (int i = 4; i < 6; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 5);
		}
		for (int i = 6; i < 8; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 7);
		}
		for (int i = 8; i < 11; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], i + 1);
		}
	}
}

void __declspec(naked) ofc_champions_league_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ofc_champions_league_reputation_setup
		add esp, 0x4
		ret
	}
}

void ofc_champions_league_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		if (current != 1) ret_current = 7 + current;
		if (min != 1) ret_min = 7 + min;
		if (max == 1) ret_max = 7;
		else ret_max = 7 + max;
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage < 2) {
		ret_current = 1 + 2 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 2 * (min - 1);
		if (max < 3) ret_max = 5;
		else ret_max = 1 + 2 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 2) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) ofc_champions_league_reputation_calc_c()
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
		call ofc_champions_league_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

char ofc_champions_league_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	sub_687970(_this, ebx);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
			data->stages[i] = 0;
		}
	}
	data->year++;
	data->current_stage = -1;
	ofc_champions_league_subs(_this);
	ofc_champions_league_all_teams(_this);
	ofc_champions_league_qualifier_teams(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	sub_6835C0(_this);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) ofc_champions_league_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ofc_champions_league_update
		add esp, 0x4
		ret
	}
}

int ofc_cl_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id == -1)
	{
		if (fate == Qualified1) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_grp_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 2) {
		if (fate == Qualified1) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_semi_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_semi_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 2) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

	return 0;
}

void __declspec(naked) ofc_cl_stage_news_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x28]
		push dword ptr[eax + 0x24]
		push dword ptr[eax + 0x20]
		push dword ptr[eax + 0x1c]
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ofc_cl_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void ofc_champions_league_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = ofc_champions_league_vtable;
	data->year = year;
	data->rules = RulesOceania;
	data->f81 = 0xf;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 3;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	ofc_champions_league_subs(_this);
	ofc_champions_league_all_teams(_this);
	ofc_champions_league_qualifier_teams(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	ofc_champions_league_reputation_setup(_this);
}

int ofc_champions_league_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, PreliminaryRound, 0xF);
			return 0;
		}
	}
	else if (stage < 2) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SemiFinal, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			return 0;
		}
	}
	else if (stage == 2) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
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

void __declspec(naked) ofc_champions_league_set_table_fate()
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
		call ofc_champions_league_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void setup_ofc_champions_league() {
	WriteVTablePtr(ofc_champions_league_vtable, VTableEoSUpdate, (DWORD)&ofc_champions_league_update_c);
	WriteVTablePtr(ofc_champions_league_vtable, VTablePlayoffQual, (DWORD)&ofc_champions_league_stages_create_c);
	WriteVTablePtr(ofc_champions_league_vtable, VTableSetChampion, (DWORD)&ofc_champions_league_set_champion_c);
	WriteVTablePtr(ofc_champions_league_vtable, VTableFixtures, (DWORD)&ofc_champions_league_fixture_caller);
	WriteVTablePtr(ofc_champions_league_vtable, VTableTableFates, (DWORD)&ofc_champions_league_set_table_fate);
	WriteVTablePtr(ofc_champions_league_vtable, VTableStageNews, (DWORD)&ofc_cl_stage_news_c);
	WriteVTablePtr(ofc_champions_league_vtable, VTableReputationSetup, (DWORD)&ofc_champions_league_reputation_setup_c);
	WriteVTablePtr(ofc_champions_league_vtable, VTableReputationCalc, (DWORD)&ofc_champions_league_reputation_calc_c);
	WriteVTablePtr(ofc_champions_league_vtable, VTableSubsRounds, (DWORD)&ofc_champions_league_subs_c);
	WriteVTablePtr(ofc_champions_league_vtable, VTableLeagueSplit, 0x6847c0);
}