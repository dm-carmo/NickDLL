#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include "Helpers\9cf_constants.h"

vtable* srb_cup_vtable = new vtable((BYTE*)0x96C8B8, 0xA0);

void srb_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(srb_cup_vtable->vtable_ptr);
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

void srb_cup_free(BYTE* _this, BYTE a2) {
	srb_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) srb_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call srb_cup_free
		add esp, 0x8
		ret 4
	}
}

int srb_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 36;
	if (comp_data->year == 2026) total_teams = 38;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	// Srpske lige
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(SRB_VOJVODINA_9CF());
	vector<cm3_clubs*> division_clubs2 = find_clubs_of_comp(SRB_EAST_9CF());
	vector<cm3_clubs*> division_clubs3 = find_clubs_of_comp(SRB_WEST_9CF());
	vector<cm3_clubs*> division_clubs4 = find_clubs_of_comp(SRB_BELGRADE_9CF());
	BYTE selected = get_country(NATION_SERBIA_9CF())->NationLeagueSelected;
	if ((selected & 4) != 0) {
		sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);
		sort(division_clubs2.begin(), division_clubs2.end(), compareClubLastDivPos);
		sort(division_clubs3.begin(), division_clubs3.end(), compareClubLastDivPos);
		sort(division_clubs4.begin(), division_clubs4.end(), compareClubLastDivPos);
		for (int i = 0; i < 2; i++) {
			vec.push_back(division_clubs[i]);
			vec.push_back(division_clubs2[i]);
			vec.push_back(division_clubs3[i]);
			vec.push_back(division_clubs4[i]);
		}
	}
	else {
		division_clubs = get_random_weighted_clubs(division_clubs, 2, true);
		division_clubs2 = get_random_weighted_clubs(division_clubs2, 2, true);
		division_clubs3 = get_random_weighted_clubs(division_clubs3, 2, true);
		division_clubs4 = get_random_weighted_clubs(division_clubs4, 2, true);
		for (cm3_clubs* club : division_clubs) vec.push_back(club);
		for (cm3_clubs* club : division_clubs2) vec.push_back(club);
		for (cm3_clubs* club : division_clubs3) vec.push_back(club);
		for (cm3_clubs* club : division_clubs4) vec.push_back(club);
	}
	// Prva liga
	division_clubs = find_clubs_of_comp(SRB_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// SuperLiga
	division_clubs = find_clubs_of_comp(SRB_FIRST_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

char srb_cup_update(BYTE* _this) {
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
	srb_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) srb_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call srb_cup_update
		add esp, 0x4
		ret
	}
}

DWORD srb_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		*num_rounds = 6;
		*stage_name_id = None;

		WORD n_teams = data->n_teams;
		WORD r1_teams = 2 * (n_teams - 32);

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 1), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 2), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 1, Penalties, NoTiebreak, 4, r1_teams, r1_teams / 2, r1_teams, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 3), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 28), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, RoundOf32, 1, Penalties, NoTiebreak, 4, 32, 16, n_teams - r1_teams, r1_teams, 0, 1, 0, prizeMoneyFile.GetInt("srb_cup_r32_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 2), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 1, Penalties, NoTiebreak, 4, 16, 8, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("srb_cup_r16_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 3), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, Penalties, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("srb_cup_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 4), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 21), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, Penalties, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("srb_cup_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 22), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 15), year, Thursday, Afternoon, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("srb_cup_final_qualify"), prizeMoneyFile.GetInt("srb_cup_final_win"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) srb_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call srb_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void srb_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(srb_cup_vtable->vtable_ptr);
	srb_cup_vtable->SetPointer(VTableInitFree, (DWORD)&srb_cup_free_c);
	srb_cup_vtable->SetPointer(VTableEoSUpdate, (DWORD)&srb_cup_update_c);
	srb_cup_vtable->SetPointer(VTableFixtures, (DWORD)&srb_cup_fixture_caller);
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesSerbia;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	srb_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	cup_reputation_setup_generic_5223A0(_this);
}

void setup_srb_cup() {

}