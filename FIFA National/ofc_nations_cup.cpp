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

DWORD* ofc_nations_cup_vtable = (DWORD*)0x96E0CC;

DWORD ofc_nations_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = QualifyingRound;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 20), year, Wednesday, Evening, VenueUnknown_1);
		AddFixtureTV(pMem, fixture_id, 0, 3, Wednesday, Afternoon, LargestStadium8);
		AddFixtureTV(pMem, fixture_id, 1, 3, Wednesday, Evening, LargestStadium9);
		AddFixtureTV(pMem, fixture_id++, 2);
		AddFixture(pMem, fixture_id, Date(year, 3, 23), year, Saturday, Evening, VenueUnknown_1);
		AddFixtureTV(pMem, fixture_id, 0, 3, Saturday, Afternoon, LargestStadium8);
		AddFixtureTV(pMem, fixture_id, 1, 3, Saturday, Morning, LargestStadium7);
		AddFixtureTV(pMem, fixture_id++, 2);
		AddFixture(pMem, fixture_id, Date(year, 3, 26), year, Tuesday, Evening, VenueUnknown_1);
		AddFixtureTV(pMem, fixture_id, 0, 3, Tuesday, Afternoon, LargestStadium7);
		AddFixtureTV(pMem, fixture_id, 1, 3, Tuesday, Evening, LargestStadium9);
		AddFixtureTV(pMem, fixture_id++, 2);

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
			AddFixture(pMem, fixture_id, Date(year, 6, 15), year, Saturday, Evening, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 3, Saturday, Afternoon, LargestStadium2);
			AddFixtureTV(pMem, fixture_id, 1, 3, Saturday, Morning, LargestStadium3);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 18), year, Tuesday, Evening, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 3, Tuesday, Afternoon, LargestStadium4);
			AddFixtureTV(pMem, fixture_id, 1, 3, Tuesday, Evening, NationalStadium);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 21), year, Friday, Evening, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 3, Friday, Afternoon, LargestStadium5);
			AddFixtureTV(pMem, fixture_id, 1, 3, Friday, Evening, LargestStadium1);
			AddFixtureTV(pMem, fixture_id++, 2);
		}
		else {
			AddFixture(pMem, fixture_id, Date(year, 6, 16), year, Sunday, Evening, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 3, Sunday, Afternoon, LargestStadium6);
			AddFixtureTV(pMem, fixture_id, 1, 3, Sunday, Morning, LargestStadium4);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 19), year, Wednesday, Evening, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 3, Wednesday, Afternoon, LargestStadium1);
			AddFixtureTV(pMem, fixture_id, 1, 3, Wednesday, Evening, LargestStadium5);
			AddFixtureTV(pMem, fixture_id++, 2);
			AddFixture(pMem, fixture_id, Date(year, 6, 22), year, Saturday, Evening, VenueUnknown_1);
			AddFixtureTV(pMem, fixture_id, 0, 3, Saturday, Afternoon, LargestStadium3);
			AddFixtureTV(pMem, fixture_id, 1, 3, Saturday, Morning, NationalStadium);
			AddFixtureTV(pMem, fixture_id++, 2);
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 23), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 27), year, Thursday, Evening, VenueUnknown_1);
		AddPlayoffTVFixture(pMem, fixture_id, 0, 3, Thursday, Afternoon, LargestStadium2);
		AddPlayoffTVFixture(pMem, fixture_id, 1, 3, Thursday, Evening, LargestStadium1);
		AddPlayoffTVFixture(pMem, fixture_id, 2);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 | Penalties | ExtraTime, NoTiebreak, 10, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 30), year, Sunday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) ofc_nations_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ofc_nations_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int ofc_nations_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[2];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) ofc_nations_cup_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ofc_nations_cup_set_champion
		add esp, 0x4
		ret 0
	}
}

void ofc_nations_cup_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 10;
	comp_data->comp_type = NATION_INTERNATIONAL;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->f82 = 3;

	comp_data->promotions = 1;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x28;
	comp_data->max_bench = 9;
	comp_data->max_subs = 5;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 3, January, comp_data->year, -1);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) ofc_nations_cup_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ofc_nations_cup_subs
		add esp, 0x4
		ret
	}
}

void ofc_nations_cup_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	vector<cm3_clubs*> ofc_countries = get_national_teams_of_continent_fifa_members(OCEANIA_9CF());
	sort(ofc_countries.begin(), ofc_countries.end(), compareNationRanking);

	WORD total_teams_in_comp = (WORD)ofc_countries.size();
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	for (size_t j = 0; j < total_teams_in_comp; j++) {
		teams[j].club = ofc_countries[j];
		if (j < 7) teams[j].seeding = 3;
		else teams[j].seeding = 10;
		teams[j].f6 = 0;
	}
}

void ofc_nations_cup_qualifier_teams(BYTE* _this) {
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
		if (qualifiers[i].seeding == 10)
		{
			add_team_call(_this, teamsAdded++, qualifiers[i].club, 0, 0);
		}
	}
}

void ofc_nations_cup_group_stage_setup(BYTE* _this) {
	char stage_num = 0;
	DWORD v1 = *(DWORD*)_this;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < 7; i++) clubs.push_back(teams[i].club);

	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == Qualified1) {
			clubs.push_back(tls.club);
		}
	}
	if (clubs.size() != 8)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(comp_data->competition_db->ClubCompName, msg.c_str(), true);
	}

	char prom_rel[4] = { 2, 0, 0, 0 };

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
			3, 1, 10, &comp_data->tiebreaker_1, &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void ofc_nations_cup_final_stage_setup(BYTE* _this) {
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
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
}

void ofc_nations_cup_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			ofc_nations_cup_group_stage_setup(_this);
		}
		else if (current == 2) {
			ofc_nations_cup_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) ofc_nations_cup_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ofc_nations_cup_stages_create
		add esp, 0x4
		ret
	}
}

void ofc_nations_cup_reputation_setup(BYTE* _this) {
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

void __declspec(naked) ofc_nations_cup_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ofc_nations_cup_reputation_setup
		add esp, 0x4
		ret
	}
}

void ofc_nations_cup_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
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

void __declspec(naked) ofc_nations_cup_reputation_calc_c()
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
		call ofc_nations_cup_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

char ofc_nations_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	sub_687970(_this, 0);
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
	if (data->year < *current_year) data->year += 4;
	data->current_stage = -1;
	ofc_nations_cup_subs(_this);
	ofc_nations_cup_all_teams(_this);
	ofc_nations_cup_qualifier_teams(_this);
	sub_6827D0(_this, 0);
	sub_6835C0(_this);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) ofc_nations_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ofc_nations_cup_update
		add esp, 0x4
		ret
	}
}

int ofc_nations_cup_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
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

void __declspec(naked) ofc_nations_cup_stage_news_c()
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
		call ofc_nations_cup_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void ofc_nations_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = ofc_nations_cup_vtable;
	WORD start_year = year;
	while (start_year % 4 != 0) {
		start_year++;
	}
	data->year = start_year;
	data->rules = RulesInternational;
	data->f81 = 0xf;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 3;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	ofc_nations_cup_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void ofc_nations_cup_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		WORD date_day = *(WORD*)(_this + 0xB6);
		if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year) {
			if (a3) {
				ofc_nations_cup_all_teams(_this);
				ofc_nations_cup_qualifier_teams(_this);
				sub_6835C0(_this);
				sub_6827D0(_this, 0);
				ofc_nations_cup_reputation_setup(_this);
				data->f69 = 1;
			}
		}
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) ofc_nations_cup_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ofc_nations_cup_init2
		add esp, 0xc
		ret 8
	}
}

int ofc_nations_cup_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QualifyingRound, 0xF);
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
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) ofc_nations_cup_table_fates_c()
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
		call ofc_nations_cup_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

void setup_ofc_nations_cup() {
	WriteVTablePtr(ofc_nations_cup_vtable, VTableEoSUpdate, (DWORD)&ofc_nations_cup_update_c);
	WriteVTablePtr(ofc_nations_cup_vtable, VTablePlayoffQual, (DWORD)&ofc_nations_cup_stages_create_c);
	WriteVTablePtr(ofc_nations_cup_vtable, VTableSetChampion, (DWORD)&ofc_nations_cup_set_champion_c);
	WriteVTablePtr(ofc_nations_cup_vtable, VTableFixtures, (DWORD)&ofc_nations_cup_fixture_caller);
	WriteVTablePtr(ofc_nations_cup_vtable, VTableTableFates, (DWORD)&ofc_nations_cup_table_fates_c);
	WriteVTablePtr(ofc_nations_cup_vtable, VTableStageNews, (DWORD)&ofc_nations_cup_stage_news_c);
	WriteVTablePtr(ofc_nations_cup_vtable, VTableReputationSetup, (DWORD)&ofc_nations_cup_reputation_setup_c);
	WriteVTablePtr(ofc_nations_cup_vtable, VTableReputationCalc, (DWORD)&ofc_nations_cup_reputation_calc_c);
	WriteVTablePtr(ofc_nations_cup_vtable, VTableSubsRounds, (DWORD)&ofc_nations_cup_subs_c);
	WriteVTablePtr(ofc_nations_cup_vtable, VTableLeagueSplit, (DWORD)&ofc_nations_cup_init2_c);
	// landmarks?
}