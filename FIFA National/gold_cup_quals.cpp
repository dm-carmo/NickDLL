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

vtable* gold_cup_quals_vtable = new vtable((BYTE*)0x970C24, 0xA0);

void gold_cup_quals_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)gold_cup_quals_vtable->vtable_ptr;
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
			data->stages[i] = 0;
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
	sub_518690(_this);
}

void gold_cup_quals_free(BYTE* _this, BYTE a2) {
	gold_cup_quals_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) gold_cup_quals_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_quals_free
		add esp, 0x8
		ret 4
	}
}

DWORD gold_cup_quals_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 12), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 4, NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 10, 8, 4, 8, 0, 0, 2, 5);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 18), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 19), year, Monday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 4, NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 10, 14, 7, 14, 0, 0, 2, 3);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) gold_cup_quals_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_quals_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char gold_cup_quals_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
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
			data->stages[i] = 0;
		}
	}
	data->current_stage = -1;
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	if (data->year < *current_year) data->year += 2;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) gold_cup_quals_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gold_cup_quals_update
		add esp, 0x4
		ret
	}
}

void gold_cup_quals_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	WORD total_teams_in_comp = 18;
	data->special_nteams_seedings = 8;
	data->f56 = total_teams_in_comp;
	WORD count = 0;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	vector<cm3_clubs*> quals_countries;

	comp_stats* concacaf_nl = (comp_stats*)get_loaded_league(CONCACAF_NATIONS_LEAGUE_9CF());
	// League A relegated
	comp_stats* curr_stage = concacaf_nl;
	for (int i = 4; i < 6; i++) {
		for (char al = -1; al < 1; al++) {
			if (al >= 0) curr_stage = (comp_stats*)(concacaf_nl->stages[al]);
			else curr_stage = concacaf_nl;
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			quals_countries.push_back(table[i].club);
		}
	}
	// League C promoted
	for (int i = 0; i < 3; i++) {
		for (char al = 6; al < 9; al++) {
			curr_stage = (comp_stats*)(concacaf_nl->stages[al]);
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			if (table[i].league_fate == Promoted || table[i].league_fate == Champions) quals_countries.push_back(table[i].club);
		}
	}

	if (quals_countries.size() != 8)
	{
		string msg = "Wrong number of clubs: " + to_string(quals_countries.size()) + ", should be 8";
		create_message_box("Error", msg.c_str(), true);
	}

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	for (; count < quals_countries.size(); count++) {
		teams[count].club = quals_countries[count];
		teams[count].seeding = 6;
		teams[count].f6 = 0;
	}
}

void gold_cup_quals_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 8;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	if (data->teams_list) sub_9452CA_free(data->teams_list);
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
			}
		}
		sub_9452CA_free(data->f173);
	}

	WORD year = data->year;
	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	WORD total_teams_in_comp = data->special_nteams_seedings;

	vector<cm3_clubs*> quals_countries;
	for (WORD i = 0; i < total_teams; i++) {
		quals_countries.push_back(qualifiers[i].club);
	}

	if (quals_countries.size() != total_teams)
	{
		string msg = "Wrong number of clubs: " + to_string(quals_countries.size());
		create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
	}

	for (WORD i = 0; i < total_teams; i++) {
		teams[i].club = quals_countries[i];
		teams[i].seeding = i >= (total_teams / 2);
		teams[i].f6 = 0;
	}
}

void gold_cup_quals_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		BYTE* cm_date = new BYTE[8];
		convert_to_cm_date(cm_date, 11, October, data->year, Monday);
		WORD date_day = *(WORD*)(cm_date);
		WORD date_year = *(WORD*)(cm_date + 2);
		if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
			if (a3) {
				sub_775070((BYTE*)*b74318, get_continent(NORTH_AMERICA_9CF()), 0);
				data->f69 = 1;
				gold_cup_quals_all_teams(_this);
				gold_cup_quals_qualifier_teams(_this);
				DWORD v1 = *(DWORD*)_this;
				(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
				(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
				(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
				sub_51C800(_this, 0);
			}
		}
	}
	sub_51F890(_this, current_date, a3);
}

void __declspec(naked) gold_cup_quals_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_quals_init2
		add esp, 0xc
		ret 8
	}
}

void gold_cup_quals_second_stage_setup(BYTE* _this) {
	char stage_num = 0;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 14;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	vector<cm3_clubs*> quals_countries;
	teams_seeded* qualifiers = (teams_seeded*)comp_data->special_teams_seedings;

	WORD idx = comp_data->special_nteams_seedings;

	comp_stats* concacaf_nl = (comp_stats*)get_loaded_league(CONCACAF_NATIONS_LEAGUE_9CF());
	// get losers from quarter-finals
	comp_stats* finals = (comp_stats*)concacaf_nl->stages[9];
	teams_seeded* teams = (teams_seeded*)finals->teams_list;
	for (WORD i = 0; i < finals->n_teams; i++) {
		if (teams[i].f6 == -1)
		{
			quals_countries.push_back(teams[i].club);
			qualifiers[idx].club = teams[i].club;
			qualifiers[idx].seeding = 6;
			qualifiers[idx].f6 = 0;
			idx++;
		}
	}
	// League A
	comp_stats* curr_stage = concacaf_nl;
	for (int i = 2; i < 4; i++) {
		for (char al = -1; al < 1; al++) {
			if (al >= 0) curr_stage = (comp_stats*)(concacaf_nl->stages[al]);
			else curr_stage = concacaf_nl;
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			quals_countries.push_back(table[i].club);
			qualifiers[idx].club = table[i].club;
			qualifiers[idx].seeding = 6;
			qualifiers[idx].f6 = 0;
			idx++;
		}
	}
	// best placed League B
	curr_stage = (comp_stats*)(concacaf_nl->stages[5]);
	team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
	for (int i = 0; i < 2; i++) {
		quals_countries.push_back(table[i].club);
		qualifiers[idx].club = table[i].club;
		qualifiers[idx].seeding = 6;
		qualifiers[idx].f6 = 0;
		idx++;
	}
	// play-in winners
	teams = (teams_seeded*)comp_data->teams_list;
	WORD total_teams_in_comp = comp_data->n_teams;
	for (WORD i = 0; i < total_teams_in_comp; i++) {
		if (teams[i].f6 == 1) quals_countries.push_back(teams[i].club);
	}

	if (quals_countries.size() != 14)
	{
		string msg = "Wrong number of clubs: " + to_string(quals_countries.size()) + ", should be 14";
		create_message_box("Error", msg.c_str(), true);
	}

	sort(quals_countries.begin(), quals_countries.end(), compareNationRanking);

	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[j])) = (DWORD)quals_countries[j];
	}

	BYTE seeds[14] = { 0,0,0,0,0,0,0,1,1,1,1,1,1,1 };

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, &seeds[0]);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
	comp_data->special_nteams_seedings = idx;

	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void gold_cup_quals_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		if (current == 0) {
			BYTE* cm_date = new BYTE[8];
			convert_to_cm_date(cm_date, 25, November, comp_data->year, Wednesday);
			WORD date_day = *(WORD*)(cm_date);
			WORD date_year = *(WORD*)(cm_date + 2);
			if ((*(WORD*)(current_date) >= date_day && *current_year == date_year) || *current_year > date_year) {
				gold_cup_quals_second_stage_setup(_this);
				comp_data->current_stage = current;
			}
		}
	}
}

void __declspec(naked) gold_cup_quals_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gold_cup_quals_stages_create
		add esp, 0x4
		ret
	}
}

int gold_cup_quals_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 0) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			qualify_team_for_international_comp(club, GOLD_CUP_9CF(), false);
			if (a5) *a5 = 3;
			break;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

void __declspec(naked) gold_cup_quals_table_fates_c()
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
		call gold_cup_quals_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

int gold_cup_quals_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	// REVIEW THIS CASE
	if (stage_id == -1) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			case Promoted:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			default:
				sub_66F4E0(0xDE1F64, 0xAD4BA4, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
	}
	else if (stage_id == 0) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				if (show_body_text) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
				else {
					cm3_club_comps* gold_cup = get_comp(GOLD_CUP_9CF());
					sub_66F4E0(0xDE1F64, 0x9C470C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, gold_cup->ClubCompGenderNameShort, gold_cup->ClubCompGenderNameShort,
						&club_data->ClubNameShort[0], &gold_cup->ClubCompNameShort[0]);
					sub_4AE660(ret_str_ptr, 0xDE1F64);
					sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
					sub_4AE8A0((BYTE*)ret_str_ptr, &gold_cup->ClubCompNameShort[0], 0x7d0, (DWORD)gold_cup);
					return 1;
				}
			case Promoted:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			default:
				sub_66F4E0(0xDE1F64, 0xAD4BA4, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
	}
	return 0;
}

void __declspec(naked) gold_cup_quals_stage_news_c()
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
		call gold_cup_quals_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void gold_cup_quals_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	if (main_stage_id == Playoff || sub_stage_id == Playoff)
	{
		if (fate == 1) {
			sub_66F4E0(dest_ptr, 0x9C48A4, club->ClubGenderName, 0xAD9C64);
			return;
		}
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) gold_cup_quals_landmarks_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_quals_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

void gold_cup_quals_reputation_setup(BYTE* _this) {
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
		sort(clubs.begin(), clubs.end(), compareNationRanking);

		for (DWORD i = 0; i < 7; i++) {
			if (i >= clubs.size()) break;
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 1);
		}
		for (DWORD i = 7; i < 14; i++) {
			if (i >= clubs.size()) break;
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 8);
		}
		for (DWORD i = 14; i < 18; i++) {
			if (i >= clubs.size()) break;
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 15);
		}
		for (WORD i = 0; i < clubs.size(); i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) gold_cup_quals_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call gold_cup_quals_reputation_setup
		add esp, 0x4
		ret
	}
}

void gold_cup_quals_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	// REVIEW THIS CASE
	if (stage == -1) {
		ret_current = 7 + current;
		if (ret_min != 1) ret_min = 7 + min;
		ret_max = 7 + max;
	}
	else if (stage == 0) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) gold_cup_quals_reputation_calc_c()
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
		call gold_cup_quals_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void __declspec(naked) gold_cup_quals_vtable31_c()
{
	__asm
	{
		mov ecx, dword ptr ds : [0x9cf78c]
		lea eax, dword ptr ds : [ecx + ecx * 2]
		lea eax, dword ptr ds : [eax + eax * 8]
		shl eax, 2
		sub eax, ecx
		mov ecx, dword ptr ds : [0xae23d0]
		add eax, ecx
		ret
	}
}

WORD gold_cup_quals_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);
	return -4;
}

void __declspec(naked) gold_cup_quals_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_quals_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE gold_cup_quals_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	return (bl < 7);
}

void __declspec(naked) gold_cup_quals_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call gold_cup_quals_vtable30
		add esp, 0x8
		ret 4
	}
}

void gold_cup_quals_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(gold_cup_quals_vtable->vtable_ptr);
	gold_cup_quals_vtable->SetPointer(VTableInitFree, (DWORD)&gold_cup_quals_free_c);
	gold_cup_quals_vtable->SetPointer(VTableEoSUpdate, (DWORD)&gold_cup_quals_update_c);
	gold_cup_quals_vtable->SetPointer(VTableLeagueSplit, (DWORD)&gold_cup_quals_init2_c);
	gold_cup_quals_vtable->SetPointer(VTablePlayoffQual, (DWORD)&gold_cup_quals_stages_create_c);
	gold_cup_quals_vtable->SetPointer(VTableTableFates, (DWORD)&gold_cup_quals_table_fates_c);
	gold_cup_quals_vtable->SetPointer(VTableReputationSetup, (DWORD)&gold_cup_quals_reputation_setup_c);
	gold_cup_quals_vtable->SetPointer(VTableReputationCalc, (DWORD)&gold_cup_quals_reputation_calc_c);
	gold_cup_quals_vtable->SetPointer(VTableFixtures, (DWORD)&gold_cup_quals_fixture_caller);
	gold_cup_quals_vtable->SetPointer(VTableStageNews, (DWORD)&gold_cup_quals_stage_news_c);
	gold_cup_quals_vtable->SetPointer(VTable29, (DWORD)&gold_cup_quals_vtable29_c);
	gold_cup_quals_vtable->SetPointer(VTable30, (DWORD)&gold_cup_quals_vtable30_c);
	gold_cup_quals_vtable->SetPointer(VTableGetFinalsComp, (DWORD)&gold_cup_quals_vtable31_c);
	gold_cup_quals_vtable->SetPointer(VTableClubLandmarks, (DWORD)&gold_cup_quals_landmarks_c);
	gold_cup_quals_vtable->SetPointer(VTableLoadCompInfo, 0x48CEB0);
	gold_cup_quals_vtable->SetPointer(VTableSaveCompInfo, 0x48CEA0);
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->rules = RulesInternational;
	data->f82 = 3;
	data->max_bench = 7;
	data->max_subs = 3;
	data->year = year;
	while (data->year % 2 != 0) data->year++;
	data->f81 = 0xf;
	data->special_nteams_seedings = 0;
	data->f56 = 4;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);

	data->n_teams = 18;
	BYTE* tMem = (BYTE*)cm0102_malloc(6 * data->n_teams);
	data->teams_list = (DWORD*)tMem;

	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void setup_gold_cup_quals() {
}