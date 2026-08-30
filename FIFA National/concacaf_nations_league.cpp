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

vtable* concacaf_nations_league_vtable = new vtable((BYTE*)0x96A0D4, 0xB4);

void concacaf_nations_league_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(concacaf_nations_league_vtable->vtable_ptr);
	sub_687970(_this, 0);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
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
	sub_682300(_this);
}

void concacaf_nations_league_free(BYTE* _this, BYTE a2) {
	concacaf_nations_league_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) concacaf_nations_league_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call concacaf_nations_league_free
		add esp, 0x8
		ret 4
	}
}

int concacaf_nations_league_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* final_bytes = (BYTE*)comp_data->stages[9];
	BYTE* third_playoff_bytes = (BYTE*)comp_data->stages[10];
	comp_stats* final_data = (comp_stats*)final_bytes;
	comp_stats* third_playoff_data = (comp_stats*)third_playoff_bytes;
	cm3_clubs* first = 0;
	cm3_clubs* second = 0;
	cm3_clubs* third = 0;
	teams_seeded* teams = (teams_seeded*)third_playoff_data->teams_list;
	for (WORD i = 0; i < third_playoff_data->n_teams; i++) {
		if (teams[i].f6 == 1) third = teams[i].club;
	}
	teams = (teams_seeded*)final_data->teams_list;
	for (WORD i = 0; i < final_data->n_teams; i++) {
		if (teams[i].f6 == 1) first = teams[i].club;
		else if (teams[i].f6 == 2) second = teams[i].club;
	}
	sub_4AFCE0_add_history_entry(_this, first, second, third, 0);

	sub_775420((BYTE*)*b74318, comp_data->competition_db);
	return 0;
}

void __declspec(naked) concacaf_nations_league_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call concacaf_nations_league_set_champion
		add esp, 0x4
		ret 0
	}
}

void concacaf_nations_league_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 0;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f67 = 2;
	comp_data->f196 = 10;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_4 = GoalsForAwayTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 2;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 2;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 23, July, comp_data->year, Thursday);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0xB8)) = 0;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)cm0102_malloc(fixture_dates_sz);
	BYTE* fixtures = (BYTE*)comp_data->fixtures_table;
	*((WORD*)(fixtures)) = *(WORD*)current_date;
	*((WORD*)(fixtures + 2)) = (*current_year) - comp_data->year;
	*((BYTE*)(fixtures + 4)) = 0;
	*((WORD*)(_this + 0xA9)) = 1;
	*((BYTE*)(_this + 0xDD)) = 0;

	return;
}

void __declspec(naked) concacaf_nations_league_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call concacaf_nations_league_subs
		add esp, 0x4
		ret
	}
}

DWORD concacaf_nations_league_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	if (stage_idx == 5) return 0; // best-placed teams
	if (stage_idx < 9) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 6;
		if (stage_idx < 1) *num_rounds = 4;
		if (stage_idx < 1) *stage_name_id = LeagueA1to4 + stage_idx + 1;
		else if (stage_idx < 5) *stage_name_id = LeagueB1to4 + stage_idx - 1;
		else *stage_name_id = LeagueC1to4 + stage_idx - 6;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 23), year, Wednesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 26), year, Saturday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 29), year, Tuesday, Afternoon);
		if (*num_rounds > 4 && stage_idx > 5) AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 1), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 3), year, Saturday, Afternoon);
		if (*num_rounds > 4 && stage_idx > 5) AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 6), year, Tuesday, Afternoon);
		if (*num_rounds > 4 && stage_idx < 5)
		{
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 11), year, Wednesday, Afternoon);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 14), year, Saturday, Afternoon);
		}

		return (DWORD)pMem;
	}
	// finals
	else if (stage_idx == 9) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 3;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 12), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 10, 8, 4, 8, 0, 0, 2, 5);

		// semi + final to be played at host country eventually
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 18), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 23), year, Thursday, Afternoon);
		AddPlayoffTVFixture(pMem, fixture_id, 0, 3, Wednesday, Afternoon);
		AddPlayoffTVFixture(pMem, fixture_id, 0, 3, Thursday, Afternoon);
		AddPlayoffTVFixture(pMem, fixture_id, 1);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 + ExtraTimePenalties_1, NoTiebreak_2, 10, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 24), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 26), year, Sunday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	// third place
	else if (stage_idx == 10) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = ThirdPlacePlayoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 23), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 26), year, Sunday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, None, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	// B finals
	else if (stage_idx == 11) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 2;
		*stage_name_id = LeagueBFinals;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 15), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 23), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 10, 4, 2, 4, 0, 0, 1, 0);
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 24), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 26), year, Sunday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	// C finals
	else if (stage_idx == 12) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 2;
		*stage_name_id = LeagueCFinals;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 25), year, Saturday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 10, 4, 2, 4, 0, 0, 1, 0);
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 28), year, Tuesday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 10, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) concacaf_nations_league_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call concacaf_nations_league_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void concacaf_nations_league_prom_rel_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	vector<cm3_clubs*> lge_a, lge_b, lge_c;

	comp_stats* final_data = (comp_stats*)data->stages[9];

	teams_seeded* teams = (teams_seeded*)final_data->teams_list;
	for (WORD i = 0; i < final_data->n_teams; i++) {
		lge_a.push_back(teams[i].club);
	}

	// assumes all leagues have 6 teams
	comp_stats* curr_stage = data;
	for (int i = 2; i < 6; i++) {
		for (char al = -1; al < 1; al++) {
			if (al >= 0) curr_stage = (comp_stats*)(data->stages[al]);
			else curr_stage = data;
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			if (table[i].league_fate == Relegated) lge_b.push_back(table[i].club);
			else lge_a.push_back(table[i].club);
		}
	}

	for (int i = 0; i < 4; i++) {
		for (char al = 1; al < 5; al++) {
			curr_stage = (comp_stats*)(data->stages[al]);
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			if (table[i].league_fate == Promoted || table[i].league_fate == Champions) lge_a.push_back(table[i].club);
			else if (table[i].league_fate == Relegated) lge_c.push_back(table[i].club);
			else lge_b.push_back(table[i].club);
		}
	}

	for (int i = 0; i < 3; i++) {
		for (char al = 6; al < 9; al++) {
			curr_stage = (comp_stats*)(data->stages[al]);
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			if (table[i].league_fate == Promoted || table[i].league_fate == Champions) lge_b.push_back(table[i].club);
			else lge_c.push_back(table[i].club);
		}
	}

	if (lge_a.size() != 16)
	{
		string msg = "[A] Wrong number of clubs: " + to_string(lge_a.size()) + ", should be 16";
		create_message_box("Error", msg.c_str(), true);
	}

	if (lge_b.size() != 16)
	{
		string msg = "[B] Wrong number of clubs: " + to_string(lge_a.size()) + ", should be 16";
		create_message_box("Error", msg.c_str(), true);
	}

	if (lge_c.size() != 9)
	{
		string msg = "[C] Wrong number of clubs: " + to_string(lge_a.size()) + ", should be 9";
		create_message_box("Error", msg.c_str(), true);
	}

	sort(lge_a.begin(), lge_a.end(), compareNationRanking);
	shuffle(lge_a.begin(), lge_a.begin() + 4, rng);
	shuffle(lge_a.begin() + 4, lge_a.begin() + 6, rng);
	shuffle(lge_a.begin() + 6, lge_a.begin() + 8, rng);
	shuffle(lge_a.begin() + 8, lge_a.begin() + 10, rng);
	shuffle(lge_a.begin() + 10, lge_a.begin() + 12, rng);
	shuffle(lge_a.begin() + 12, lge_a.begin() + 14, rng);
	shuffle(lge_a.begin() + 14, lge_a.end(), rng);

	sort(lge_b.begin(), lge_b.end(), compareNationRanking);
	shuffle(lge_b.begin(), lge_b.begin() + 4, rng);
	shuffle(lge_b.begin() + 4, lge_b.begin() + 8, rng);
	shuffle(lge_b.begin() + 8, lge_b.begin() + 12, rng);
	shuffle(lge_b.begin() + 12, lge_b.end(), rng);

	sort(lge_c.begin(), lge_c.end(), compareNationRanking);
	shuffle(lge_c.begin(), lge_c.begin() + 3, rng);
	shuffle(lge_c.begin() + 3, lge_c.begin() + 6, rng);
	shuffle(lge_c.begin() + 6, lge_c.end(), rng);

	if (data->special_teams_seedings) {
		sub_9452CA_free(data->special_teams_seedings);
		data->special_teams_seedings = 0;
		data->special_nteams_seedings = 0;
	}

	BYTE* pMem = (BYTE*)cm0102_malloc(6 * 41);
	data->special_teams_seedings = (DWORD*)pMem;
	teams = (teams_seeded*)data->special_teams_seedings;

	data->special_nteams_seedings = 41;
	data->f56 = 41;

	size_t i = 0;
	for (; i < lge_a.size(); i++) {
		teams[i].club = lge_a[i];
		if (i < 4) teams[i].f5 = 3;
		else teams[i].f5 = 10;
		teams[i].f6 = 0;
	}
	size_t j = 0;
	for (; j < lge_b.size(); j++) {
		teams[i + j].club = lge_b[j];
		teams[i + j].f5 = 11;
		teams[i + j].f6 = 0;
	}
	for (size_t k = 0; k < lge_c.size(); k++) {
		teams[i + j + k].club = lge_c[k];
		teams[i + j + k].f5 = 12;
		teams[i + j + k].f6 = 0;
	}
}

char concacaf_nations_league_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	*((WORD*)(_this + 0xA7)) = -1;
	data->f76 = 0;

	concacaf_nations_league_prom_rel_update(_this);

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
	if (data->year < *current_year) data->year += 2;
	data->current_stage = -1;
	concacaf_nations_league_subs(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) concacaf_nations_league_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call concacaf_nations_league_update
		add esp, 0x4
		ret
	}
}

void concacaf_nations_league_reputation_setup(BYTE* _this) {
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
		sort(clubs.begin(), clubs.begin() + 16, compareNationRanking);
		sort(clubs.begin() + 16, clubs.begin() + 32, compareNationRanking);
		sort(clubs.begin() + 32, clubs.end(), compareNationRanking);

		sub_4A2540((BYTE*)comp_data->f8, clubs[0], 1);
		sub_4A2540((BYTE*)comp_data->f8, clubs[1], 2);
		sub_4A2540((BYTE*)comp_data->f8, clubs[2], 3);
		sub_4A2540((BYTE*)comp_data->f8, clubs[3], 4);

		for (int i = 4; i < 8; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 5);
		}
		for (int i = 8; i < 10; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (int i = 10; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 11);
		}
		for (int i = 12; i < 14; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (int i = 14; i < 16; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 15);
		}

		sub_4A2540((BYTE*)comp_data->f8, clubs[16], 17);
		sub_4A2540((BYTE*)comp_data->f8, clubs[17], 18);
		for (int i = 18; i < 20; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 19);
		}
		for (int i = 20; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 21);
		}
		for (int i = 24; i < 28; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25);
		}
		for (int i = 28; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 29);
		}

		sub_4A2540((BYTE*)comp_data->f8, clubs[32], 33);
		sub_4A2540((BYTE*)comp_data->f8, clubs[33], 34);
		for (int i = 34; i < 36; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 35);
		}
		for (int i = 36; i < 38; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 37);
		}
		for (WORD i = 38; i < comp_data->special_nteams_seedings; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 39);
		}
		for (WORD i = 0; i < comp_data->special_nteams_seedings; i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) concacaf_nations_league_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call concacaf_nations_league_reputation_setup
		add esp, 0x4
		ret
	}
}

void concacaf_nations_league_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;

	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 1) {
		ret_current = 1 + 2 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 2 * (min - 1);
		if (max < 3) ret_max = 5;
		else ret_max = 1 + 2 * (max - 1);
	}
	else if (stage < 5) {
		ret_current = 17 + 4 * (current - 1);
		ret_min = 17 + 4 * (min - 1);
		ret_max = 17 + 4 * (max - 1);
	}
	else if (stage == 5) {
		ret_current = current + 20;
		ret_min = min + 20;
		ret_max = max + 20;
	}
	else if (stage < 9) {
		ret_current = 33 + 3 * (current - 1);
		ret_min = 33 + 3 * (min - 1);
		ret_max = 33 + 3 * (max - 1);
	}
	else if (stage == 9) {
		// do nothing
	}
	else if (stage == 10) {
		ret_current = current + 2;
		ret_min = min + 2;
		ret_max = max + 2;
	}
	else if (stage == 11) {
		ret_current = 16 + current;
		ret_min = 16 + min;
		ret_max = 16 + max;
	}
	else if (stage == 12) {
		ret_current = 32 + current;
		ret_min = 32 + min;
		ret_max = 32 + max;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) concacaf_nations_league_reputation_calc_c()
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
		call concacaf_nations_league_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void concacaf_nations_league_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	WORD base_year = START_YEAR;
	while (base_year % 2 != 0) base_year++;

	if (year > base_year) return;

	// first year only
	vector<cm3_clubs*> countries;
	countries.push_back(get_national_team(NATION_MEXICO_9CF()));
	countries.push_back(get_national_team(NATION_USA_9CF()));
	countries.push_back(get_national_team(NATION_CANADA_9CF()));
	countries.push_back(get_national_team(NATION_PANAMA_9CF()));

	countries.push_back(get_national_team(NATION_COSTA_RICA_9CF()));
	countries.push_back(get_national_team(NATION_HONDURAS_9CF()));
	countries.push_back(get_national_team(NATION_HAITI_9CF()));
	countries.push_back(get_national_team(NATION_JAMAICA_9CF()));
	countries.push_back(get_national_team(NATION_TRINIDAD_TOBAGO_9CF()));
	countries.push_back(get_national_team(NATION_GUATEMALA_9CF()));
	countries.push_back(get_national_team(NATION_CURACAO_9CF()));
	countries.push_back(get_national_team(NATION_SURINAM_9CF()));
	countries.push_back(get_national_team(NATION_NICARAGUA_9CF()));
	countries.push_back(get_national_team(NATION_MARTINIQUE_9CF()));
	countries.push_back(get_national_team(NATION_DOMINICAN_REPUBLIC_9CF()));
	countries.push_back(get_national_team(NATION_EL_SALVADOR_9CF()));
	countries.push_back(get_national_team(NATION_GUYANA_9CF()));
	countries.push_back(get_national_team(NATION_GUADELOUPE_9CF()));
	countries.push_back(get_national_team(NATION_CUBA_9CF()));
	countries.push_back(get_national_team(NATION_FRENCH_GUIANA_9CF()));
	countries.push_back(get_national_team(NATION_PUERTO_RICO_9CF()));
	countries.push_back(get_national_team(NATION_BERMUDA_9CF()));
	countries.push_back(get_national_team(NATION_GRENADA_9CF()));
	countries.push_back(get_national_team(NATION_ST_VINCENT_9CF()));
	countries.push_back(get_national_team(NATION_DOMINICA_9CF()));
	countries.push_back(get_national_team(NATION_ST_LUCIA_9CF()));
	countries.push_back(get_national_team(NATION_ST_KITTS_NEVIS_9CF()));
	countries.push_back(get_national_team(NATION_BELIZE_9CF()));
	countries.push_back(get_national_team(NATION_CAYMAN_ISLANDS_9CF()));
	countries.push_back(get_national_team(NATION_BARBADOS_9CF()));
	countries.push_back(get_national_team(NATION_BONAIRE_9CF()));
	countries.push_back(get_national_team(NATION_SINT_MAARTEN_9CF()));
	countries.push_back(get_national_team(NATION_MONTSERRAT_9CF()));
	countries.push_back(get_national_team(NATION_ANTIGUA_BARBUDA_9CF()));
	countries.push_back(get_national_team(NATION_SAINT_MARTIN_9CF()));
	countries.push_back(get_national_team(NATION_TURKS_AND_CAICOS_9CF()));
	countries.push_back(get_national_team(NATION_ARUBA_9CF()));
	countries.push_back(get_national_team(NATION_BAHAMAS_9CF()));
	countries.push_back(get_national_team(NATION_BRITISH_VIRGIN_ISLANDS_9CF()));
	countries.push_back(get_national_team(NATION_ANGUILLA_9CF()));
	countries.push_back(get_national_team(NATION_US_VIRGIN_ISLANDS_9CF()));

	WORD total_teams_in_comp = (WORD)countries.size();
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	for (BYTE i = 0; i < total_teams_in_comp; i++) {
		teams[i].club = countries[i];
		if (i < 4) teams[i].f5 = 3;
		else if (i < 16) teams[i].f5 = 10;
		else if (i < 32) teams[i].f5 = 11;
		else teams[i].f5 = 12;
		teams[i].f6 = 0;
	}
}

void concacaf_nations_league_create_matchups(BYTE* _this, BYTE* stage, vector<cm3_clubs*> clubs, BYTE idx) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* stage_data = (comp_stats*)stage;
	DWORD v1 = *(DWORD*)_this;

	char matchups[4][6] = {
		{ 6,5,2,3,1,4, },
		{ 2,1,4,5,3,6, },
		{ 4,3,6,2,5,1, },
		{ 3,4,1,2,5,6, },
	};

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	*((WORD*)(stage + 0x3A)) = stage_name_id;
	*((WORD*)(stage + 0xA7)) = num_rounds;

	for (BYTE m = 0; m < 4; m++) {
		BYTE* ptr_last = (BYTE*)(pFixtures + fixture_dates_sz * 5);
		match_data* match = new match_data();
		match->comp_id = data->competition_db->ClubCompID;
		match->f8 = -1;
		match->comp = data->competition_db;
		match->end_year = data->year + *(WORD*)(ptr_last + 2);
		match->end_day = *(WORD*)(ptr_last);
		match->current_year = data->year;
		match->sub_stage_id = 0;
		match->main_stage_id = stage_name_id;
		match->f54_0xdb = data->f219;
		match->f56_0xab = data->f171;
		match->f58_0xc4 = data->f196;
		match->f59 = -1;
		match->f61 = 0;
		match->f62 = 0;
		match->f64 = 1;
		match->f65 = 1;
		match->stage_number = idx;
		match->goals_home2 = -1;
		match->goals_away2 = -1;
		match->f69 = -1;
		match->f70 = -1;
		match->goals_home1 = -1;
		match->goals_away1 = -1;
		match->f73 = -1;
		match->f74 = -1;
		match->f75 = -1;
		match->f76 = -1;
		match->subs = 0x59; // force 9/5 subs

		vector<pair<char, char>> matchup_pairs;
		for (char t = 0; t < 3; t++) {
			char p1 = matchups[m][t * 2];
			char p2 = matchups[m][t * 2 + 1];
			cm3_clubs* home = clubs[p1 - 1];
			cm3_clubs* away = clubs[p2 - 1];
			BYTE* ptr = (BYTE*)(pFixtures + fixture_dates_sz * m);
			match->home_team_id = home->ClubID;
			match->away_team_id = away->ClubID;
			match->home_team = home;
			match->away_team = away;
			match->fixture_year = data->year + *(WORD*)(ptr + 2);
			match->fixture_day = *(WORD*)(ptr);
			match->fixture_number = m;
			match->f63 = *(BYTE*)(ptr + 4);

			sub_85C260((BYTE*)*(DWORD*)0xDD7EF4, *(DWORD*)(ptr + 0x3D), (BYTE*)match, data->f36);
			sub_5AA680((BYTE*)*(DWORD*)0xAE2A58, (BYTE*)match, 1);
		}
	}
	sub_9452CA_free(pFixtures);
}

void concacaf_nations_league_setup_first_group(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 6;
	BYTE* pMem = (BYTE*)cm0102_malloc(league_team_list_sz * total_teams);

	WORD year = data->year;
	data->n_teams = total_teams;
	data->team_league_table = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;

	vector<cm3_clubs*> clubs;
	for (int i = 0; i < total_teams; i++)
	{
		clubs.push_back(qualifiers[4 + 2 * i].club);
		add_team_call(_this, i, qualifiers[4 + 2 * i].club, 0, 0);
	}

	concacaf_nations_league_create_matchups(_this, _this, clubs, -1);

	sub_684230(_this);
}

void concacaf_nations_league_setup_groups_a(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	WORD num_teams = 6;

	DWORD* pTeams = (DWORD*)cm0102_malloc(num_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	vector<cm3_clubs*> clubs;
	for (int i = 0; i < num_teams; i++)
	{
		clubs.push_back(qualifiers[4 + 2 * i + (idx + 1)].club);
		*((DWORD*)(&pTeams[i])) = (DWORD)qualifiers[4 + 2 * i + (idx + 1)].club;
	}

	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, num_teams, pTeams, 0, (DWORD)(data->competition_db), 0, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, idx, stage_name_id, data->f81, 2, 0, data->f217, -1, 0, 2);

	concacaf_nations_league_create_matchups(_this, pStage, clubs, idx);

	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

void concacaf_nations_league_setup_groups_b(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	WORD num_teams = 4;

	DWORD* pTeams = (DWORD*)cm0102_malloc(num_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	vector<cm3_clubs*> clubs;
	for (int i = 0; i < num_teams; i++)
	{
		clubs.push_back(qualifiers[16 + 4 * i + (idx - 1)].club);
		*((DWORD*)(&pTeams[i])) = (DWORD)qualifiers[16 + 4 * i + (idx - 1)].club;
	}

	char prom_rel[4] = { 1, 0, 0, 1 };
	WORD year = data->year;
	WORD f217 = 0x2;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, num_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, idx, stage_name_id, data->f81, 2, 0, f217, -1, 0, 2);

	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

void concacaf_nations_league_setup_groups_c(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	WORD num_teams = 3;

	DWORD* pTeams = (DWORD*)cm0102_malloc(num_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	vector<cm3_clubs*> clubs;
	for (int i = 0; i < num_teams; i++)
	{
		clubs.push_back(qualifiers[32 + 3 * i + (idx - 6)].club);
		*((DWORD*)(&pTeams[i])) = (DWORD)qualifiers[32 + 3 * i + (idx - 6)].club;
	}

	char prom_rel[4] = { 1, 1, 0, 0 };
	WORD year = data->year;
	WORD f217 = 0x2;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, num_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, idx, stage_name_id, data->f81, 2, 0, f217, -1, 0, 2);

	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

void concacaf_nations_league_best_placed_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	char stage_num = 5;

	WORD start_date[4];
	WORD end_date[4];
	DWORD tmp1[2];
	DWORD tmp2[2];
	sub_54A110((BYTE*)start_date);
	sub_54A110((BYTE*)end_date);

	WORD year = data->year;
	WORD num_rounds;
	WORD stage_name_id;
	BYTE* pFixtures = (BYTE*)concacaf_nations_league_fixtures(_this, 1, &num_rounds, &stage_name_id, 0);
	BYTE* cm_date = new BYTE[8];
	sub_549EF0(cm_date, *(WORD*)(pFixtures), year + *(WORD*)(pFixtures + 2));
	sub_417C10((BYTE*)start_date, tmp1, cm_date);
	sub_549EF0(cm_date, *(WORD*)(pFixtures + num_rounds * fixture_dates_sz - fixture_dates_sz),
		year + *(WORD*)(pFixtures + num_rounds * fixture_dates_sz - fixture_dates_sz + 2));
	sub_54C770(cm_date, (BYTE*)tmp1, 1);
	sub_417C10((BYTE*)end_date, tmp2, (BYTE*)tmp1);
	for (char al = 1; al < 5; al++) {
		comp_stats* curr_stage = (comp_stats*)(data->stages[al]);
		sub_6827D0((BYTE*)curr_stage, 0);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls_second = table_teams[1];
		cm3_clubs* second_club = tls_second.club;
		DWORD* pMem = (DWORD*)cm0102_malloc(4 * curr_stage->n_teams);
		for (WORD i = 0; i < curr_stage->n_teams; i++) {
			*((DWORD*)(&pMem[i])) = table_teams[i].club->ClubID;
		}
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		comp_stats* stage_data = (comp_stats*)pStage;
		WORD n = curr_stage->n_teams;
		sub_88C6D0(pStage, n, pMem, -1, -1, start_date, end_date, data->competition_db->ClubCompID, data->pts_for_win, data->pts_for_draw, &data->tiebreaker_1, 9 * (n * (n - 1)), data->f16);
		table_teams = (team_league_stats*)stage_data->team_league_table;
		WORD chk = 0;
		for (; chk < stage_data->n_teams; chk++) {
			if (table_teams[chk].club == second_club) break;
		}
		if (chk < stage_data->n_teams) {
			comp_stats* best_placed_stage = (comp_stats*)(data->stages[stage_num]);
			team_league_stats* best_placed_table = (team_league_stats*)(best_placed_stage->team_league_table);
			memcpy(&best_placed_table[al - 1], &table_teams[chk], league_team_list_sz);
			best_placed_table[al - 1].position_history = 0;
			best_placed_table[al - 1].f4 = 0;
		}
		DWORD v1 = *(DWORD*)pStage;
		(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)pStage, 1);
		sub_9452CA_free((BYTE*)(pMem));
	}
	sub_6827D0((BYTE*)data->stages[stage_num], 0);
}

void concacaf_nations_league_setup_best_placed(BYTE* _this) {
	char stage_num = 5;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 0, 2, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, NoTiebreaker };
	create_league_stage_data(pStage, _this, 4, 0, 0, (DWORD)(data->competition_db), 0, 0,
		data->pts_for_win, data->pts_for_draw, data->f196, &tiebreaks[0], &prom_rel[0],
		year, stage_num, BestPlacedTeams, 0, 1, 0, 0x28, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	data->current_stage = stage_num;
	concacaf_nations_league_best_placed_update(_this);
}

void concacaf_nations_league_final_stage_setup(BYTE* _this) {
	char stage_num = 9;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
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

void concacaf_nations_league_b_finals_setup(BYTE* _this) {
	char stage_num = 11;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
}

void concacaf_nations_league_c_finals_setup(BYTE* _this) {
	char stage_num = 12;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
}

bool concacaf_nations_league_check_a_finals(BYTE* _this) {
	char stage_num = 9;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)comp_data->stages[stage_num];
	if (!playoff) return true;
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;
	for (WORD i = 0; i < playoff_teams; i++)
	{
		if (!teams[i].club) return false;
	}
	return true;
}

bool concacaf_nations_league_check_b_finals(BYTE* _this) {
	char stage_num = 11;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)comp_data->stages[stage_num];
	if (!playoff) return false;
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;
	for (WORD i = 0; i < playoff_teams; i++)
	{
		if (!teams[i].club) return false;
	}
	return true;
}

bool concacaf_nations_league_check_c_finals(BYTE* _this) {
	char stage_num = 12;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)comp_data->stages[stage_num];
	if (!playoff) return false;
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;
	for (WORD i = 0; i < playoff_teams; i++)
	{
		if (!teams[i].club) return false;
	}
	return true;
}

void concacaf_nations_league_third_place_setup(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	char stage_num = 10;

	BYTE playoff_teams = 2;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(data->competition_db), pFixtures, year, stage_num, 4, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);

	data->current_stage = (long)stage_num;
}

void concacaf_nations_league_finals_teams(BYTE* _this) {
	char stage_num = 9;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)comp_data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	vector<cm3_clubs*> clubs;
	teams_seeded* qualifiers = (teams_seeded*)comp_data->special_teams_seedings;
	for (int i = 0; i < 4; i++)
	{
		clubs.push_back(qualifiers[i].club);
		sub_775000((BYTE*)*b74318, qualifiers[i].club->ClubNation);
	}

	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
		}
	}
	cm3_clubs* tmp = clubs[6];
	clubs[6] = clubs[5];
	clubs[5] = tmp;
	sort(clubs.begin() + 4, clubs.begin() + 6, compareNationRanking);
	sort(clubs.begin() + 6, clubs.end(), compareNationRanking);

	BYTE team_order[8] = { 6,4,2,0,1,3,5,7, };

	for (char i = 0; i < playoff_teams; i++) {
		teams[team_order[i]].club = clubs[i];
	}
}

void concacaf_nations_league_b_finals_teams(BYTE* _this) {
	char stage_num = 11;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)comp_data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	vector<cm3_clubs*> clubs;
	for (char al = 1; al < 5; al++)
	{
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == Promoted) {
				clubs.push_back(tls.club);
			}
		}
	}

	if (clubs.size() != playoff_teams)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size()) + ", should be " + to_string(playoff_teams);
		create_message_box("Error", msg.c_str(), true);
	}

	shuffle(clubs.begin(), clubs.end(), rng);
	BYTE team_order[4] = { 0,2,3,1 };

	for (char i = 0; i < playoff_teams; i++) {
		teams[team_order[i]].club = clubs[i];
	}
}

void concacaf_nations_league_c_finals_teams(BYTE* _this) {
	char stage_num = 12;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)comp_data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	vector<cm3_clubs*> clubs;
	for (char al = 6; al < 9; al++)
	{
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == Promoted) {
				clubs.push_back(tls.club);
			}
		}
	}

	// get best second placed
	vector<team_league_stats> sort_seconds;
	for (char al = 6; al < 9; al++)
	{
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls = table_teams[curr_stage->promotions];
		sort_seconds.push_back(tls);
	}
	sort(sort_seconds.begin(), sort_seconds.end(), sortTLS);
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	for (int i = 0; i < 1; i++) {
		team_league_stats second = sort_seconds[i];
		clubs.push_back(second.club);
		for (char al = 6; al < 9; al++)
		{
			comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			team_league_stats tls = table_teams[curr_stage->promotions];
			if (tls.club == second.club) {
				table_teams[curr_stage->promotions].league_fate = Promoted;
				curr_stage->promotions++;
				curr_stage->prom_playoff--;
				staff_history_qualified_86BDD0(staff_hist_ptr, tls.club, (DWORD)(comp_data->competition_db), None, LeagueB, 0x1E);
				staff_history_qualified_86BDD0(staff_hist_ptr, tls.club, (DWORD)(comp_data->competition_db), None, LeagueCFinals, 0x1E);
			}
		}
	}
	for (size_t i = 1; i < sort_seconds.size(); i++) {
		staff_history_qualified_86BDD0(staff_hist_ptr, sort_seconds[i].club, (DWORD)(comp_data->competition_db), None, LeagueC, 0x1E);
		sub_775000((BYTE*)*b74318, sort_seconds[i].club->ClubNation);
	}
	for (char al = 6; al < 9; al++)
	{
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		if (curr_stage->promotions == 1) {
			table_teams[curr_stage->promotions].league_fate = Eliminated;
			curr_stage->prom_playoff--;
		}
	}

	if (clubs.size() != playoff_teams)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size()) + ", should be " + to_string(playoff_teams);
		create_message_box("Error", msg.c_str(), true);
	}

	shuffle(clubs.begin(), clubs.end(), rng);
	BYTE team_order[4] = { 0,2,3,1 };

	for (char i = 0; i < playoff_teams; i++) {
		teams[team_order[i]].club = clubs[i];
	}
}

void concacaf_nations_league_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	WORD day2 = *(WORD*)(_this + 0xB6);
	short year2 = *(short*)(_this + 0xB8);
	if (day2 == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year2) {
		if (!data->f69 && a3) {
			sub_775070((BYTE*)*b74318, get_continent(NORTH_AMERICA_9CF()), 0);
			data->f69 = 1;
			concacaf_nations_league_all_teams(_this);
			concacaf_nations_league_setup_first_group(_this);
			sub_6835C0(_this);
			sub_6827D0(_this, 0);
			for (BYTE i = 0; i < 1; i++) {
				concacaf_nations_league_setup_groups_a(_this, i);
			}
			for (BYTE i = 0; i < 4; i++) {
				concacaf_nations_league_setup_groups_b(_this, i + 1);
			}
			concacaf_nations_league_setup_best_placed(_this);
			for (BYTE i = 0; i < 3; i++) {
				concacaf_nations_league_setup_groups_c(_this, i + 6);
			}
			concacaf_nations_league_final_stage_setup(_this);
			concacaf_nations_league_third_place_setup(_this);
			concacaf_nations_league_b_finals_setup(_this);
			concacaf_nations_league_c_finals_setup(_this);
			concacaf_nations_league_reputation_setup(_this);
		}
	}
	else if (*(WORD*)(current_date) > day2 || *(WORD*)(current_date + 2) > data->year + year2) {
		char ret = sub_5AE6D0((BYTE*)current_date, data->competition_db->ClubCompID);
		if (ret) concacaf_nations_league_best_placed_update(_this);
		if (ret && a3) {
			comp_stats* curr_stage = data;
			bool a_finals_started = concacaf_nations_league_check_a_finals(_this);
			if (!a_finals_started)
			{
				bool is_finished = true;
				for (char al = -1; al < 1; al++) {
					if (al >= 0) curr_stage = (comp_stats*)(data->stages[al]);
					else curr_stage = data;
					team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
					for (int i = 0; i < curr_stage->n_teams; i++) {
						team_league_stats tls = table[i];
						if (tls.games < 4) {
							is_finished = false;
							break;
						}
					}
				}
				if (is_finished) {
					concacaf_nations_league_finals_teams(_this);
				}
			}

			bool b_finals_started = concacaf_nations_league_check_b_finals(_this);
			if (!b_finals_started)
			{
				bool is_finished = true;
				for (char al = 1; al < 5; al++) {
					curr_stage = (comp_stats*)(data->stages[al]);
					team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
					for (int i = 0; i < curr_stage->n_teams; i++) {
						team_league_stats tls = table[i];
						if (tls.games < 6) {
							is_finished = false;
							break;
						}
					}
				}
				if (is_finished) {
					concacaf_nations_league_b_finals_teams(_this);
				}
			}

			bool c_finals_started = concacaf_nations_league_check_c_finals(_this);
			if (!c_finals_started)
			{
				bool is_finished = true;
				for (char al = 6; al < 9; al++) {
					curr_stage = (comp_stats*)(data->stages[al]);
					team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
					for (int i = 0; i < curr_stage->n_teams; i++) {
						team_league_stats tls = table[i];
						if (tls.games < 4) {
							is_finished = false;
							break;
						}
					}
				}
				if (is_finished) {
					concacaf_nations_league_c_finals_teams(_this);
				}
			}
		}
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) concacaf_nations_league_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call concacaf_nations_league_init2
		add esp, 0xc
		ret 8
	}
}

int concacaf_nations_league_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 1) {
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueA, 0x1E);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
			return 0;
		case Relegated:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueB, 0x1E);
			break;
		default:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueA, 0x1E);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage < 5) {
		switch (fate) {
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueA, 0x1E);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueBFinals, 0x1E);
			qualify_team_for_international_comp(club, GOLD_CUP_9CF());
			return 0;
		case Relegated:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueC, 0x1E);
			break;
		default:
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 5) {
		//switch (fate) {
		//case Qualified1:
		//	staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
		//	return 0;
		//default:
		//	sub_775000((BYTE*)*b74318, club->ClubNation);
		//	return 0;
		//}
	}
	else if (stage < 9) {
		switch (fate) {
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueB, 0x1E);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueCFinals, 0x1E);
			break;
		case TopPlayoff:
			return 0;
		default:
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 9) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		char c;
		WORD round_name = *(WORD*)(rounds + playoff_dates_sz * current_round + 7);
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			for (char al = -1; al < 1; al++) {
				if (al >= 0) curr_stage = (comp_stats*)(comp_data->stages[al]);
				team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
				for (int i = 0; i < num_teams; i++) {
					if (table[i].club == club)
					{
						table[i].league_fate = Champions;
						break;
					}
				}
			}
			*a5 = 4;
			break;
		case Promoted:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			if (round_name == QuarterFinal) {
				qualify_team_for_international_comp(club, GOLD_CUP_9CF());
				if (comp_data->year % 4 != 0) {
					qualify_team_for_international_comp(club, COPA_AMERICA_9CF());
				}
			}
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			break;
		default:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
			if (round_name == SemiFinal) {
				char third_stage_id = 10;
				comp_stats* stage = (comp_stats*)comp_data->stages[third_stage_id];
				teams_seeded* teams = (teams_seeded*)stage->teams_list;
				if (!teams[0].club) teams[0].club = club;
				else if (!teams[1].club) teams[1].club = club;
			}
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 10) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		char c;
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_third_place_86B710(staff_hist_ptr, club, round_data, a7);
			*a5 = 4;
			break;
		case Promoted:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			return 0;
		case BottomPlayoff:
			break;
		default:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 11) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		char c;
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			for (char al = 1; al < 5; al++) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
				team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
				for (int i = 0; i < num_teams; i++) {
					if (table[i].club == club)
					{
						table[i].league_fate = Champions;
						break;
					}
				}
			}
			*a5 = 4;
			break;
		case Promoted:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			break;
		default:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage == 12) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		char c;
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			for (char al = 6; al < 9; al++) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
				team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
				for (int i = 0; i < num_teams; i++) {
					if (table[i].club == club)
					{
						table[i].league_fate = Champions;
						break;
					}
				}
			}
			*a5 = 4;
			break;
		case Promoted:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), c);
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			break;
		default:
			c = sub_4BF850(40, 100, current_round, 4);
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), c);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

void __declspec(naked) concacaf_nations_league_set_table_fate()
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
		call concacaf_nations_league_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

// review
int concacaf_nations_league_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 1) {
		if (fate == TopPlayoff) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == BottomPlayoff) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Relegated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 5) {
		if (fate == Promoted) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == TopPlayoff) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == BottomPlayoff) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		else if (fate == Relegated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 5) {
		if (fate == TopPlayoff) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 9) {
		if (fate == Promoted) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
		//else if (fate == TopPlayoff) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 9) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else if (stage_id == 10)
	{
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0x987264, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			case BottomPlayoff:
				sub_66F4E0(0xDE1F64, 0x987200, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			case Promoted:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			default:
				sub_66F4E0(0xDE1F64, 0x98713C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			}
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
	}
	else if (stage_id == 11) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else if (stage_id == 12) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	return 0;
}

void __declspec(naked) concacaf_nations_league_stage_news_c()
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
		call concacaf_nations_league_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void concacaf_nations_league_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	if (main_stage_id >= 0x475 && main_stage_id <= 0x478) { // League A
		if (fate == Relegated) {
			sub_66F4E0(dest_ptr, (DWORD)&rele_lge_a[0]);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, (DWORD)&lge_a[0]);
			return;
		}
	}
	if (main_stage_id >= 0x459 && main_stage_id <= 0x45c) { // League B
		if (fate == Promoted) {
			sub_66F4E0(dest_ptr, (DWORD)&prom_lge_b[0]);
			return;
		}
		else if (fate == Relegated) {
			sub_66F4E0(dest_ptr, (DWORD)&rele_lge_b[0]);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, (DWORD)&lge_b[0]);
			return;
		}
	}
	if (main_stage_id >= 0x40F && main_stage_id <= 0x412) { // League C
		if (fate == Promoted) {
			sub_66F4E0(dest_ptr, (DWORD)&prom_lge_c[0]);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, (DWORD)&lge_c[0]);
			return;
		}
	}
	if (main_stage_id == BestPlacedTeams) {
		sub_66F4E0(dest_ptr, 0x99B800);
		return;
	}
	if (main_stage_id == LeagueBFinals || sub_stage_id == LeagueBFinals) return sub_48CAB0(_this, dest_ptr, a2, None, LeagueBFinals, 0, club);
	if (main_stage_id == LeagueCFinals || sub_stage_id == LeagueCFinals) return sub_48CAB0(_this, dest_ptr, a2, None, LeagueCFinals, 0, club);
	if (main_stage_id == None)
	{
		if (sub_stage_id == SemiFinal)
		{
			if (fate == 1) return sub_48CAB0(_this, dest_ptr, a2, None, Final, 0, club);
			else if (fate == 2) return sub_48CAB0(_this, dest_ptr, a2, ThirdPlacePlayoff, None, 0, club);
		}
		else if (sub_stage_id == Final)
		{
			if (fate == 1 || fate == 2) return sub_48CAB0(_this, dest_ptr, a2, None, None, fate, club);
		}
		return sub_48CAB0(_this, dest_ptr, a2, None, sub_stage_id, fate, club);
	}
	if (main_stage_id == ThirdPlacePlayoff && sub_stage_id == None)
	{
		if (fate == 1) return sub_48CAB0(_this, dest_ptr, a2, None, None, 3, club);
		else return sub_48CAB0(_this, dest_ptr, a2, None, SemiFinal, -1, club);
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) concacaf_nations_league_landmarks_c()
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
		call concacaf_nations_league_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

// review - expectations for B/C finals?
WORD concacaf_nations_league_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);
	if (val == 1) return -1;
	else if (val == 2) return Final;
	else if (val < 5) return SemiFinal;
	else if (val < 9) return QuarterFinal;
	else if (val < 21) return LeagueA;
	else if (val < 36) return LeagueB;
	else return LeagueC;
}

void __declspec(naked) concacaf_nations_league_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call concacaf_nations_league_vtable29
		add esp, 0x8
		ret 4
	}
}

// review - expectations for B/C finals?
BYTE concacaf_nations_league_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13); // round reached?
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12); // round expectation?

	// Finals
	if (al < 3) {
		if (bl < 2) return 1;
		else if (bl < 3) return 0;
		else if (bl < 5) return 0;
		else return (bl < 9) - 2;
	}
	else if (al < 5) {
		if (bl < 2) return 2;
		else if (bl < 3) return 1;
		else if (bl < 5) return 0;
		else if (bl < 9) return 0;
		else return (bl < 13) - 2;
	}
	else if (al < 9) {
		if (bl < 2) return 3;
		else if (bl < 3) return 2;
		else if (bl < 5) return 1;
		else if (bl < 9) return 0;
		else if (bl < 13) return -1;
		else return -2;
	}
	// rest of League A
	else if (al < 13) {
		if (bl < 3) return 3;
		else if (bl < 5) return 2;
		else if (bl < 9) return 1;
		else if (bl < 13) return 0;
		else return -1;
	}
	else if (al < 17) {
		if (bl < 5) return 3;
		else if (bl < 9) return 2;
		else if (bl < 13) return 1;
		else return 0;
	}
	// League B
	else if (al < 21) {
		if (bl < 21) return 1;
		else if (bl < 25) return 0;
		else if (bl < 29) return -1;
		else return -2;
	}
	else if (al < 25) {
		if (bl < 21) return 1;
		else if (bl < 25) return 0;
		else if (bl < 29) return 0;
		else return -1;
	}
	else if (al < 29) {
		if (bl < 21) return 2;
		else if (bl < 25) return 1;
		else if (bl < 29) return 0;
		else return -1;
	}
	else if (al < 33) {
		if (bl < 21) return 3;
		else if (bl < 25) return 2;
		else if (bl < 29) return 1;
		else return 0;
	}
	// League C
	else if (al < 33) {
		if (bl < 33) return 1;
		else if (bl < 36) return 0;
		else return -1;
	}
	else if (al < 36) {
		if (bl < 33) return 1;
		else if (bl < 36) return 0;
		else return -1;
	}
	else {
		if (bl < 33) return 2;
		else if (bl < 36) return 1;
		else return (bl < 39) * 0;
	}
}

void __declspec(naked) concacaf_nations_league_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call concacaf_nations_league_vtable30
		add esp, 0x8
		ret 4
	}
}

void concacaf_nations_league_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(concacaf_nations_league_vtable->vtable_ptr);
	concacaf_nations_league_vtable->SetPointer(VTableInitFree, (DWORD)&concacaf_nations_league_free_c);
	concacaf_nations_league_vtable->SetPointer(VTableEoSUpdate, (DWORD)&concacaf_nations_league_update_c);
	concacaf_nations_league_vtable->SetPointer(VTableLeagueSplit, (DWORD)&concacaf_nations_league_init2_c);
	concacaf_nations_league_vtable->SetPointer(VTableTableFates, (DWORD)&concacaf_nations_league_set_table_fate);
	concacaf_nations_league_vtable->SetPointer(VTableFixtures, (DWORD)&concacaf_nations_league_fixture_caller);
	concacaf_nations_league_vtable->SetPointer(VTableStageNews, (DWORD)&concacaf_nations_league_stage_news_c);
	concacaf_nations_league_vtable->SetPointer(VTableSetChampion, (DWORD)&concacaf_nations_league_set_champion_c);
	concacaf_nations_league_vtable->SetPointer(VTable29, (DWORD)&concacaf_nations_league_vtable29_c);
	concacaf_nations_league_vtable->SetPointer(VTable30, (DWORD)&concacaf_nations_league_vtable30_c);
	concacaf_nations_league_vtable->SetPointer(VTableClubLandmarks, (DWORD)&concacaf_nations_league_landmarks_c);
	concacaf_nations_league_vtable->SetPointer(VTableLoadCompInfo, 0x48CEB0);
	concacaf_nations_league_vtable->SetPointer(VTableSaveCompInfo, 0x48CEA0);
	concacaf_nations_league_vtable->SetPointer(VTable12, 0x48CE70);
	concacaf_nations_league_vtable->SetPointer(VTableGetFinalsComp, 0x5dce00);
	concacaf_nations_league_vtable->SetPointer(VTableShowHostsInHistory, 0x5dce00);
	concacaf_nations_league_vtable->SetPointer(VTableSubsRounds, (DWORD)&concacaf_nations_league_subs_c);
	concacaf_nations_league_vtable->SetPointer(VTablePostMatchUpdate, 0x685d30); // check?
	//concacaf_nations_league_vtable->SetPointer(VTablePlayoffQual, (DWORD)&concacaf_nations_league_stages_create_c);
	concacaf_nations_league_vtable->SetPointer(VTablePlayoffQual, 0x5a8f60);
	concacaf_nations_league_vtable->SetPointer(VTableReputationSetup, (DWORD)&concacaf_nations_league_reputation_setup_c);
	concacaf_nations_league_vtable->SetPointer(VTableReputationCalc, (DWORD)&concacaf_nations_league_reputation_calc_c);
	concacaf_nations_league_vtable->SetPointer(VTable38, 0x684cd0); // check?
	if (configFile.GetBool("showThirdPlaceInHistory", true)) concacaf_nations_league_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	data->year = year;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->rules = RulesInternational;
	data->f82 = 3;
	data->year = year;
	while (data->year % 2 != 0) data->year++;
	data->f81 = 0xf;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->f217 = 0x28;
	data->current_stage = -1;
	data->num_stages = 13;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	concacaf_nations_league_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void setup_concacaf_nations_league() {

	char* lge_b_finals = "League B Finals";
	char* lge_b_finals_short = "Lge B Finals";
	WriteDWORD(0x4B58B8 + 1, (DWORD)&lge_b_finals[0]);
	WriteDWORD(0x4B8714 + 1, (DWORD)&lge_b_finals_short[0]);
	char* lge_c_finals = "League C Finals";
	char* lge_c_finals_short = "Lge C Finals";
	WriteDWORD(0x4B5906 + 1, (DWORD)&lge_c_finals[0]);
	WriteDWORD(0x4B8732 + 1, (DWORD)&lge_c_finals_short[0]);
}