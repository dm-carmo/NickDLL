#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include "Helpers\9cf_constants.h"

vtable* qat_amir_cup_vtable = new vtable((BYTE*)0x96C8B8, 0xA0);

void qat_amir_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(qat_amir_cup_vtable->vtable_ptr);
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
	sub_518690(_this);
}

void qat_amir_cup_free(BYTE* _this, BYTE a2) {
	qat_amir_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) qat_amir_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call qat_amir_cup_free
		add esp, 0x8
		ret 4
	}
}

int qat_amir_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 20;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// Lower
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(QAT_QSL_2_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (ret_club && !is_main_club) continue;
		else if (club->ClubID == CLUB_QATAR_U23_9CF()) continue;
		else vec.push_back(club);
	}
	// D1
	division_clubs = find_clubs_of_comp(QAT_QSL_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	for (WORD i = 0; i < total_teams; i++)
	{
		teams[i].club = vec[i];
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

char qat_amir_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
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
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	qat_amir_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) qat_amir_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call qat_amir_cup_update
		add esp, 0x4
		ret
	}
}

DWORD qat_amir_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 5;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 2), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 9), year, Saturday, Evening);
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 0, ExtraTime | Penalties, NoTiebreak, 4, 8, 4, 8, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 11), year, Thursday);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, ExtraTime | Penalties, NoTiebreak, 4, 16, 8, 12, 8, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 12), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 30), year, Friday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTime | Penalties, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 1), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 4), year, Tuesday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTime | Penalties, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 5), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 8), year, Saturday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTime | Penalties, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("qat_amir_cup_final_win"), prizeMoneyFile.GetInt("qat_amir_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) qat_amir_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call qat_amir_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void qat_amir_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(qat_amir_cup_vtable->vtable_ptr);
	qat_amir_cup_vtable->SetPointer(VTableInitFree, (DWORD)&qat_amir_cup_free_c);
	qat_amir_cup_vtable->SetPointer(VTableEoSUpdate, (DWORD)&qat_amir_cup_update_c);
	qat_amir_cup_vtable->SetPointer(VTableFixtures, (DWORD)&qat_amir_cup_fixture_caller);
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesQatar;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	qat_amir_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	cup_reputation_setup_generic_5223A0(_this);
}

void setup_qat_amir_cup() {

}