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

vtable* asian_cup_quals_vtable = new vtable((BYTE*)0x970C24, 0xA0);

void asian_cup_quals_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)asian_cup_quals_vtable->vtable_ptr;
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

void asian_cup_quals_free(BYTE* _this, BYTE a2) {
	asian_cup_quals_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) asian_cup_quals_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call asian_cup_quals_free
		add esp, 0x8
		ret 4
	}
}

DWORD asian_cup_quals_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 25), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 5), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 4, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 10, 10, 5, 10, 0, 0, 2, 5);

		return (DWORD)pMem;
	}
	else if (stage_idx < 6) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 6;
		*stage_name_id = ThirdRoundAlphabeticGroup + stage_idx;
		if (stage_idx == 3) *stage_name_id = ThirdRoundGroupD;
		if (stage_idx == 4) *stage_name_id = ThirdRoundGroupE;
		if (stage_idx == 5) *stage_name_id = ThirdRoundGroupF;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 25), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 6, 10), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 10, 9), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 10, 14), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 11, 18), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 3, 29), year, Tuesday, Afternoon);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) asian_cup_quals_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call asian_cup_quals_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char asian_cup_quals_update(BYTE* _this) {
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
	if (data->year < *current_year) data->year += 4;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) asian_cup_quals_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call asian_cup_quals_update
		add esp, 0x4
		ret
	}
}

void asian_cup_quals_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	WORD total_teams_in_comp = 29;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;
	WORD count = 0;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	vector<cm3_clubs*> quals_countries;
	quals_countries.push_back(get_national_team(NATION_NORTHERN_MARIANA_9CF()));

	// get losers from first round
	comp_stats* wc_asia_quals = (comp_stats*)get_loaded_league(WORLD_CUP_AFC_QUALIFYING_9CF());
	comp_stats* r1_league = (comp_stats*)wc_asia_quals->stages[0];
	team_league_stats* table = (team_league_stats*)r1_league->team_league_table;
	bool best_team = false;
	for (WORD i = 0; i < r1_league->n_teams; i++) {
		team_league_stats tls = table[i];
		if (tls.league_fate == Qualified1) continue;
		if (best_team) {
			quals_countries.push_back(tls.club);
		}
		else {
			teams[count].club = tls.club;
			teams[count].f5 = 10;
			teams[count].f6 = 0;
			count++;
			best_team = true;
		}
	}

	// get teams from second round
	DWORD host3_id, host4_id;
	get_comp_hosts_in_continent(_this, ASIAN_CUP_9CF(), ASIA_9CF(), &host3_id, &host4_id);

	for (char al = 1; al < 10; al++) {
		vector<cm3_clubs*> clubs_qual, clubs_po;

		comp_stats* curr_stage = (comp_stats*)(wc_asia_quals->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			cm3_clubs* club = table_teams[i].club;
			if (i < 2) clubs_qual.push_back(club);
			else if (club->ClubNation->NationID == host3_id || club->ClubNation->NationID == host4_id) {
				cm3_clubs* popped = clubs_qual[clubs_qual.size()];
				clubs_qual.pop_back();
				clubs_qual.push_back(club);
				clubs_po.push_back(popped);
			}
			else clubs_po.push_back(club);
		}

		for (cm3_clubs* club : clubs_po) {
			teams[count].club = club;
			teams[count].f5 = 10;
			teams[count].f6 = 0;
			count++;
		}
	}

	for (cm3_clubs* club : quals_countries) {
		teams[count].club = club;
		teams[count].f5 = 11;
		teams[count].f6 = 0;
		count++;
	}
}

void asian_cup_quals_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 10;
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
	for (WORD i = 0; i < total_teams_in_comp; i++) {
		if (qualifiers[i].f5 == 11) quals_countries.push_back(qualifiers[i].club);
	}
	sort(quals_countries.begin(), quals_countries.end(), compareNationRanking);
	if (quals_countries.size() != total_teams)
	{
		string msg = "Wrong number of clubs: " + to_string(quals_countries.size());
		create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
	}

	for (WORD i = 0; i < total_teams; i++) {
		teams[i].club = quals_countries[i];
		teams[i].f5 = i >= (total_teams / 2);
		teams[i].f6 = 0;
	}
}

void asian_cup_quals_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		BYTE* cm_date = new BYTE[8];
		convert_to_cm_date(cm_date, 18, July, data->year, -1);
		WORD date_day = *(WORD*)(cm_date);
		WORD date_year = *(WORD*)(cm_date + 2);
		if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
			if (a3) {
				sub_775070((BYTE*)*b74318, get_continent(ASIA_9CF()), 0);
				data->f69 = 1;
				asian_cup_quals_all_teams(_this);
				asian_cup_quals_qualifier_teams(_this);
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

void __declspec(naked) asian_cup_quals_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call asian_cup_quals_init2
		add esp, 0xc
		ret 8
	}
}

int asian_cup_quals_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, ThirdRound, 0x1E);
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
	else if (stage < 6) {
		switch (fate) {
		case Qualified1:
			qualify_team_for_international_comp(club, ASIAN_CUP_9CF());
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, ThirdRound, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

void __declspec(naked) asian_cup_quals_set_table_fate()
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
		call asian_cup_quals_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int asian_cup_quals_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
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
	else if (stage_id < 6) {
		if (fate == Qualified1)
		{
			if (show_body_text) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
			else {
				cm3_club_comps* afcon = get_comp(ASIAN_CUP_9CF());
				sub_66F4E0(0xDE1F64, 0x9C470C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, afcon->ClubCompGenderNameShort, afcon->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &afcon->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &afcon->ClubCompNameShort[0], 0x7d0, (DWORD)afcon);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	return 0;
}

void __declspec(naked) asian_cup_quals_stage_news_c()
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
		call asian_cup_quals_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void asian_cup_quals_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	if ((main_stage_id >= 0x40c && main_stage_id <= 0x40e) || main_stage_id == 0xBE || main_stage_id == 0x118 || main_stage_id == 0x122)
	{
		if (fate == Qualified1) {
			sub_66F4E0(dest_ptr, 0x9C48A4, club->ClubGenderName, 0xAD9C64);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, 0x99B800);
			return;
		}
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) asian_cup_quals_landmarks_c()
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
		call asian_cup_quals_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

void asian_cup_quals_reputation_setup(BYTE* _this) {
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

		for (DWORD i = 0; i < 6; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 1);
		}
		for (DWORD i = 6; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 7);
		}
		for (DWORD i = 12; i < 18; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (DWORD i = 18; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 19);
		}
		for (DWORD i = 24; i < clubs.size(); i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25);
		}
		for (WORD i = 0; i < clubs.size(); i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) asian_cup_quals_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call asian_cup_quals_reputation_setup
		add esp, 0x4
		ret
	}
}

void asian_cup_quals_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = 23 + current;
		if (ret_min != 1) ret_min = 23 + min;
		ret_max = 23 + max;
	}
	else if (stage < 6) {
		ret_current = 1 + 6 * (current - 1);
		ret_min = 1 + 6 * (min - 1);
		ret_max = 1 + 6 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) asian_cup_quals_reputation_calc_c()
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
		call asian_cup_quals_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void asian_cup_quals_second_stage_setup(BYTE* _this) {
	char stage_num = 0;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	char prom_rel[4] = { 1, 0, 0, 0 };
	char tiebreaks[4] = { CurrentPositionTiebreaker, GoalDifferenceTiebreaker, GoalsForTiebreaker, NoTiebreaker };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	WORD total_teams_in_comp = comp_data->special_nteams_seedings;
	for (WORD i = 0; i < total_teams_in_comp; i++) {
		if (teams[i].f5 == 10) clubs.push_back(teams[i].club);
	}
	teams = (teams_seeded*)comp_data->teams_list;
	for (WORD i = 0; i < comp_data->n_teams; i++) {
		if (teams[i].f6 == 1) clubs.push_back(teams[i].club);
	}

	sort(clubs.begin(), clubs.end(), compareNationRanking);
	shuffle(clubs.begin(), clubs.begin() + 6, rng);
	shuffle(clubs.begin() + 6, clubs.begin() + 12, rng);
	shuffle(clubs.begin() + 12, clubs.begin() + 18, rng);
	shuffle(clubs.begin() + 18, clubs.end(), rng);

	DWORD v1 = *(DWORD*)_this;
	WORD group_teams = 4;
	for (int i = 0; i < 6; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 6 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 10, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void asian_cup_quals_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			asian_cup_quals_second_stage_setup(_this);
		}
	}
}

void __declspec(naked) asian_cup_quals_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call asian_cup_quals_stages_create
		add esp, 0x4
		ret
	}
}

void __declspec(naked) asian_cup_quals_vtable31_c()
{
	__asm
	{
		mov ecx, dword ptr ds : [0x9cf790]
		lea eax, dword ptr ds : [ecx + ecx * 2]
		lea eax, dword ptr ds : [eax + eax * 8]
		shl eax, 2
		sub eax, ecx
		mov ecx, dword ptr ds : [0xae23d0]
		add eax, ecx
		ret
	}
}

WORD asian_cup_quals_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);
	return (val < 6) - 3;
}

void __declspec(naked) asian_cup_quals_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call asian_cup_quals_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE asian_cup_quals_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	if (al < 6) return (bl < 6) - 1;
	else return (bl < 6);
}

void __declspec(naked) asian_cup_quals_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call asian_cup_quals_vtable30
		add esp, 0x8
		ret 4
	}
}

void asian_cup_quals_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(asian_cup_quals_vtable->vtable_ptr);
	asian_cup_quals_vtable->SetPointer(VTableInitFree, (DWORD)&asian_cup_quals_free_c);
	asian_cup_quals_vtable->SetPointer(VTableEoSUpdate, (DWORD)&asian_cup_quals_update_c);
	asian_cup_quals_vtable->SetPointer(VTableLeagueSplit, (DWORD)&asian_cup_quals_init2_c);
	asian_cup_quals_vtable->SetPointer(VTablePlayoffQual, (DWORD)&asian_cup_quals_stages_create_c);
	asian_cup_quals_vtable->SetPointer(VTableTableFates, (DWORD)&asian_cup_quals_set_table_fate);
	asian_cup_quals_vtable->SetPointer(VTableReputationSetup, (DWORD)&asian_cup_quals_reputation_setup_c);
	asian_cup_quals_vtable->SetPointer(VTableReputationCalc, (DWORD)&asian_cup_quals_reputation_calc_c);
	asian_cup_quals_vtable->SetPointer(VTableFixtures, (DWORD)&asian_cup_quals_fixture_caller);
	asian_cup_quals_vtable->SetPointer(VTableStageNews, (DWORD)&asian_cup_quals_stage_news_c);
	asian_cup_quals_vtable->SetPointer(VTable29, (DWORD)&asian_cup_quals_vtable29_c);
	asian_cup_quals_vtable->SetPointer(VTable30, (DWORD)&asian_cup_quals_vtable30_c);
	asian_cup_quals_vtable->SetPointer(VTable31, (DWORD)&asian_cup_quals_vtable31_c);
	asian_cup_quals_vtable->SetPointer(VTableClubLandmarks, (DWORD)&asian_cup_quals_landmarks_c);
	asian_cup_quals_vtable->SetPointer(VTable9, 0x48CEB0);
	asian_cup_quals_vtable->SetPointer(VTable10, 0x48CEA0);
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->rules = RulesInternational;
	data->f82 = 3;
	data->max_bench = 7;
	data->max_subs = 3;
	data->year = year;
	while (data->year % 4 != 0) data->year++;
	data->f81 = 0xf;
	data->special_nteams_seedings = 0;
	data->f56 = 6;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 6;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);

	data->n_teams = 10;
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

void setup_asian_cup_quals() {
	char* r3_4 = "Third Round Group D";
	char* r3_4_short = "3rd Rnd Grp D";
	char* r3_5 = "Third Round Group E";
	char* r3_5_short = "3rd Rnd Grp E";
	char* r3_6 = "Third Round Group F";
	char* r3_6_short = "3rd Rnd Grp F";
	WriteDWORD(0x4B53a4 + 1, (DWORD)&r3_4[0]);
	WriteDWORD(0x4B845e + 1, (DWORD)&r3_4_short[0]);
	WriteDWORD(0x4B5766 + 1, (DWORD)&r3_5[0]);
	WriteDWORD(0x4B85d2 + 1, (DWORD)&r3_5_short[0]);
	WriteDWORD(0x4B57b4 + 1, (DWORD)&r3_6[0]);
	WriteDWORD(0x4B862f + 1, (DWORD)&r3_6_short[0]);
}