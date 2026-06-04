#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

vtable* egy_super_vtable = new vtable((BYTE*)0x96C8B8, 0xA0);

char* egy_super_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* playoff_bytes = (BYTE*)comp_data->stages[0];
	comp_stats* playoff_data = (comp_stats*)playoff_bytes;
	cm3_clubs* first = 0;
	cm3_clubs* second = 0;
	cm3_clubs* third = 0;
	teams_seeded* teams = (teams_seeded*)playoff_data->teams_list;
	for (WORD i = 0; i < playoff_data->n_teams; i++) {
		if (teams[i].f6 == 1) third = teams[i].club;
	}
	teams = (teams_seeded*)comp_data->teams_list;
	for (WORD i = 0; i < comp_data->n_teams; i++) {
		if (teams[i].f6 == 1) first = teams[i].club;
		else if (teams[i].f6 == 2) second = teams[i].club;
	}
	return sub_4AFCE0_add_history_entry(_this, first, second, third, 0);
}

void __declspec(naked) egy_super_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call egy_super_set_champion
		add esp, 0x4
		ret 0
	}
}

void egy_super_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(egy_super_vtable->vtable_ptr);
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
	if (data->f8) {
		sub_49F450((BYTE*)(data->f8));
		sub_944C94_free((BYTE*)(data->f8));
	}
	DWORD y = -1;
	sub_518690(_this);
}

void egy_super_free(BYTE* _this, BYTE a2) {
	egy_super_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) egy_super_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call egy_super_free
		add esp, 0x8
		ret 4
	}
}

DWORD egy_super_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 6), year, Thursday, Evening, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 7), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday, Afternoon, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("egy_super_final_win"), prizeMoneyFile.GetInt("egy_super_final_lose"));

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = ThirdPlacePlayoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 7), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday, Afternoon, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, None, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 2, 1, 2, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("egy_super_3rdplace_win"), prizeMoneyFile.GetInt("egy_super_3rdplace_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) egy_super_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call egy_super_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int egy_super_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	if (comp_data->year == 2025) {
		vec.push_back(find_club("Al Ahly FC"));
		vec.push_back(find_club("Cleopatra FC"));
		vec.push_back(find_club("Pyramids FC"));
		vec.push_back(find_club("Zamalek SC"));
	}
	else
	{
		vector<cm3_clubs*> d1_clubs = find_clubs_of_comp_last_division(EGY_FIRST_9CF());
		sort(d1_clubs.begin(), d1_clubs.end(), compareClubLastDivPos);

		cm3_club_comps* egy_cup = get_comp(EGY_CUP_9CF());
		cm3_clubs* winner = get_last_comp_winner(egy_cup);
		if (winner) vec.push_back(winner);
		cm3_clubs* runner_up = get_last_comp_runner_up(egy_cup);
		if (runner_up) vec.push_back(runner_up);
		cm3_club_comps* egy_lge_cup = get_comp(EGY_LEAGUE_CUP_9CF());
		winner = get_last_comp_winner(egy_lge_cup);
		if (winner && !vector_contains_club(vec, winner)) vec.push_back(winner);

		for (cm3_clubs* c : d1_clubs) {
			if (!vector_contains_club(vec, c)) vec.push_back(c);
			if (vec.size() >= 4) break;
		}
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

void egy_super_third_place(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	for (int i = 0; i < playoff_teams; i++) pTeams[i] = 0;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	//sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

char egy_super_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
		data->teams_list = 0;
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
	egy_super_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	int ret = (*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	egy_super_third_place(_this);
	return ret;
}

void __declspec(naked) egy_super_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call egy_super_update
		add esp, 0x4
		ret
	}
}

void egy_super_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		if (max == 3) ret_max = 4;
	}
	else if (stage == 0) {
		ret_current = current + 2;
		ret_min = min + 2;
		ret_max = max + 2;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) egy_super_reputation_calc_c()
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
		call egy_super_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

int egy_super_set_fates(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_third_place_86B710(staff_hist_ptr, club, round_data, a7);
			*a5 = 1;
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			return 0;
		}
	}
	else {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = comp_data->rounds_list;
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
			if (current_round == 0) {
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, ThirdPlacePlayoff, 0xF);
				comp_stats* playoff = (comp_stats*)comp_data->stages[0];
				teams_seeded* teams = (teams_seeded*)playoff->teams_list;
				for (int i = 0; i < playoff->n_teams; i++) {
					if (!teams[i].club) {
						teams[i].club = club;
						break;
					}
				}
			}
			else {
				staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			}
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) egy_super_set_fates_c()
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
		call egy_super_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void egy_super_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(egy_super_vtable->vtable_ptr);
	egy_super_vtable->SetPointer(VTableInitFree, (DWORD)&egy_super_free_c);
	egy_super_vtable->SetPointer(VTableEoSUpdate, (DWORD)&egy_super_update_c);
	egy_super_vtable->SetPointer(VTableFixtures, (DWORD)&egy_super_fixture_caller);
	egy_super_vtable->SetPointer(VTableReputationCalc, (DWORD)&egy_super_reputation_calc_c);
	egy_super_vtable->SetPointer(VTableSetChampion, (DWORD)&egy_super_set_champion_c);
	egy_super_vtable->SetPointer(VTableTableFates, (DWORD)&egy_super_set_fates_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) egy_super_vtable->SetPointer(VTable21, 0x4110b0);
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 7;
	data->max_subs = 3;
	data->rules = RulesEgypt;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	egy_super_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	egy_super_third_place(_this);
}

void setup_egy_super()
{
}
