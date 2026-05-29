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

vtable* fifa_intercontinental_cup_vtable = new vtable((BYTE*)0x971250, 0xA0);

void fifa_intercontinental_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(fifa_intercontinental_cup_vtable->vtable_ptr);
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
	DWORD y = -1;
	sub_518690(_this);
}

void fifa_intercontinental_cup_free(BYTE* _this, BYTE a2) {
	fifa_intercontinental_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) fifa_intercontinental_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call fifa_intercontinental_cup_free
		add esp, 0x8
		ret 4
	}
}

int fifa_intercontinental_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[0];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) fifa_intercontinental_cup_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_intercontinental_cup_set_champion
		add esp, 0x4
		ret 0
	}
}

DWORD fifa_intercontinental_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 9), year, Tuesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 14), year, Sunday, Evening, LargestStadium3);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 2, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("intercontinental_cup_r1_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 15), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 23), year, Tuesday, Evening, LargestStadium2);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 1, 2, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("intercontinental_cup_r2_lose"));

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 10), year, Wednesday, Evening, LargestStadium2);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 2, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("intercontinental_cup_r3_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 11), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday, Evening, LargestStadium1);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 1, 2, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("intercontinental_cup_playoff_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 14), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 17), year, Wednesday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 1, 3, 0, 1, 0, 0, prizeMoneyFile.GetInt("intercontinental_cup_final_win"), prizeMoneyFile.GetInt("intercontinental_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) fifa_intercontinental_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fifa_intercontinental_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void fifa_intercontinental_cup_reputation_setup(BYTE* _this) {
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
		sub_4A2540((BYTE*)comp_data->f8, clubs[2], 3);
		for (int i = 3; i < 5; i++) {
			if (i >= comp_data->special_nteams_seedings) return;
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 4);
		}
		if (5 >= comp_data->special_nteams_seedings) return;
		sub_4A2540((BYTE*)comp_data->f8, clubs[5], 6);
	}
}

void __declspec(naked) fifa_intercontinental_cup_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_intercontinental_cup_reputation_setup
		add esp, 0x4
		ret
	}
}

void fifa_intercontinental_cup_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		switch (current) {
		case 1: ret_current = 1; break;
		case 2: ret_current = 4; break;
		case 3: ret_current = 6; break;
		}
		switch (min) {
		case 1: ret_min = 1; break;
		case 2: ret_min = 4; break;
		case 3: ret_min = 6; break;
		}
		switch (max) {
		case 1: ret_max = 3; break;
		case 2: ret_max = 4; break;
		case 3: ret_max = 6; break;
		}
	}
	else if (stage == 0) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) fifa_intercontinental_cup_reputation_calc_c()
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
		call fifa_intercontinental_cup_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void fifa_intercontinental_cup_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 6;
	data->special_nteams_seedings = 5;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	WORD count = 0;

	cm3_clubs* club = get_last_comp_winner(get_comp(CAF_CHAMPIONS_LEAGUE_9CF()));
	if (!club)
	{
		vector<cm3_clubs*> clubs = find_clubs_of_continent(AFRICA_9CF());
		sort(clubs.begin(), clubs.end(), compareClubRep);
		club = clubs[0];
	}
	teams[count].club = club;
	teams[count].f5 = 0;
	teams[count].f6 = 0;
	count++;

	club = get_last_comp_winner(get_comp(OFC_CHAMPIONS_LEAGUE_9CF()));
	if (!club)
	{
		vector<cm3_clubs*> clubs = find_clubs_of_continent(OCEANIA_9CF());
		sort(clubs.begin(), clubs.end(), compareClubRep);
		club = clubs[0];
	}
	teams[count].club = club;
	teams[count].f5 = 0;
	teams[count].f6 = 0;
	count++;

	club = get_last_comp_winner(get_comp(AFC_CHAMPIONS_LEAGUE_ELITE_9CF()));
	if (!club)
	{
		vector<cm3_clubs*> clubs = find_clubs_of_continent(ASIA_9CF());
		sort(clubs.begin(), clubs.end(), compareClubRep);
		club = clubs[0];
	}
	teams[count].club = club;
	teams[count].f5 = 0;
	teams[count].f6 = 0;
	count++;

	club = get_last_comp_winner(get_comp(CONCACAF_CHAMPIONS_CUP_9CF()));
	if (!club)
	{
		vector<cm3_clubs*> clubs = find_clubs_of_continent(NORTH_AMERICA_9CF());
		sort(clubs.begin(), clubs.end(), compareClubRep);
		club = clubs[0];
	}
	teams[count].club = club;
	teams[count].f5 = 0;
	teams[count].f6 = 0;
	count++;

	club = get_last_comp_winner(get_comp(UEFA_CHAMPIONS_LEAGUE_9CF()));
	if (!club)
	{
		vector<cm3_clubs*> clubs = find_clubs_of_continent(EUROPE_9CF());
		sort(clubs.begin(), clubs.end(), compareClubRep);
		club = clubs[0];
	}
	teams[count].club = club;
	teams[count].f5 = 0;
	teams[count].f6 = 0;
	count++;

	// empty slot, to be filled in later
	teams[count].club = 0;
	teams[count].f5 = 0;
	teams[count].f6 = 0;
}

void fifa_intercontinental_cup_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 3;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	if (data->teams_list) sub_9452CA_free(data->teams_list);

	WORD year = data->year;
	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	for (WORD i = 0; i < 3; i++) {
		teams[i].club = qualifiers[abs(((year + 1) % 2) * 2 - i)].club;
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}
}

void fifa_intercontinental_cup_final_stage_setup(BYTE* _this) {
	char stage_num = 0;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	cm3_clubs* club = get_last_comp_winner(get_comp(COPA_LIBERTADORES_9CF()));
	if (!club)
	{
		vector<cm3_clubs*> clubs = find_clubs_of_continent(SOUTH_AMERICA_9CF());
		sort(clubs.begin(), clubs.end(), compareClubRep);
		club = clubs[0];
	}
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	WORD insert_idx = comp_data->special_nteams_seedings;
	teams[insert_idx].club = club;
	teams[insert_idx].f5 = 0;
	teams[insert_idx].f6 = 0;
	comp_data->special_nteams_seedings++;
	fifa_intercontinental_cup_reputation_setup(_this);

	*((DWORD*)(&pTeams[0])) = (DWORD)teams[3].club;
	*((DWORD*)(&pTeams[1])) = (DWORD)club;
	for (WORD j = 0; j < comp_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)comp_data->teams_list)[j];
		if (t.f6 == 1) {
			*((DWORD*)(&pTeams[2])) = (DWORD)t.club;
			break;
		}
	}
	*((DWORD*)(&pTeams[3])) = (DWORD)teams[4].club;

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
}

int fifa_intercontinental_cup_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* uecl_bytes = get_loaded_league(UEFA_CONFERENCE_LEAGUE_9CF());
	comp_stats* uecl_data = (comp_stats*)uecl_bytes;
	DWORD v3 = *(DWORD*)uecl_bytes;
	if (stage == -1) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
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
			return 0;
		}
	}
	else if (stage == 0) {
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		WORD num_teams = stage_data->n_teams;
		if (num_teams <= 0) return 0;
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
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) fifa_intercontinental_cup_set_table_fate()
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
		call fifa_intercontinental_cup_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

char fifa_intercontinental_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
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
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) fifa_intercontinental_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fifa_intercontinental_cup_update
		add esp, 0x4
		ret
	}
}

void fifa_intercontinental_cup_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		BYTE* cm_date = new BYTE[8];
		convert_to_cm_date(cm_date, 21, June, data->year, -1);
		WORD date_day = *(WORD*)(cm_date);
		WORD date_year = *(WORD*)(cm_date + 2);
		if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year) {
			if (!a3) {
				fifa_intercontinental_cup_all_teams(_this);
				fifa_intercontinental_cup_qualifier_teams(_this);
				fifa_intercontinental_cup_reputation_setup(_this);
				sub_51C800(_this, 0);
				data->f69 = 1;
			}
		}
	}
	else if (data->f69 && data->current_stage < 0) {
		BYTE* liber_bytes = get_loaded_league(COPA_LIBERTADORES_9CF());
		comp_stats* liber_data = (comp_stats*)liber_bytes;
		BYTE* liber_final = (BYTE*)liber_data->stages[8];
		if (liber_final) {
			DWORD v1 = *(DWORD*)liber_final;
			char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(liber_final, 0, 1);
			if (ret != 0) {
				data->current_stage = 0;
				fifa_intercontinental_cup_final_stage_setup(_this);
			}
		}
		// when starting in 2026
		else if (liber_data->year != data->year) {
			BYTE* cm_date = new BYTE[8];
			convert_to_cm_date(cm_date, 1, December, data->year, -1);
			WORD date_day = *(WORD*)(cm_date);
			WORD date_year = *(WORD*)(cm_date + 2);
			if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year) {
				data->current_stage = 0;
				fifa_intercontinental_cup_final_stage_setup(_this);
			}
		}
	}
	sub_51F890(_this, current_date, a3);
}

void __declspec(naked) fifa_intercontinental_cup_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fifa_intercontinental_cup_init2
		add esp, 0xc
		ret 8
	}
}

void fifa_intercontinental_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->year = year;
	data->comp_vtable = (DWORD*)(fifa_intercontinental_cup_vtable->vtable_ptr);
	fifa_intercontinental_cup_vtable->SetPointer(VTableInitFree, (DWORD)&fifa_intercontinental_cup_free_c);
	fifa_intercontinental_cup_vtable->SetPointer(VTableEoSUpdate, (DWORD)&fifa_intercontinental_cup_update_c);
	fifa_intercontinental_cup_vtable->SetPointer(VTableLeagueSplit, (DWORD)&fifa_intercontinental_cup_init2_c);
	fifa_intercontinental_cup_vtable->SetPointer(VTableSetChampion, (DWORD)&fifa_intercontinental_cup_set_champion_c);
	fifa_intercontinental_cup_vtable->SetPointer(VTableFixtures, (DWORD)&fifa_intercontinental_cup_fixture_caller);
	fifa_intercontinental_cup_vtable->SetPointer(VTableTableFates, (DWORD)&fifa_intercontinental_cup_set_table_fate);
	fifa_intercontinental_cup_vtable->SetPointer(VTableReputationSetup, (DWORD)&fifa_intercontinental_cup_reputation_setup_c);
	fifa_intercontinental_cup_vtable->SetPointer(VTableReputationCalc, (DWORD)&fifa_intercontinental_cup_reputation_calc_c);
	data->competition_db = comp;
	data->comp_type = CLUB_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f82 = 3;
	data->max_bench = 7;
	data->max_subs = 3;
	data->rules = RulesInternational;
	data->f81 = 0xf;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void setup_fifa_intercontinental_cup() {
}