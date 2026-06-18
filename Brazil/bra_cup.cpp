#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>
#include "bra_state_league_list.h"

DWORD* bra_cup_vtable = (DWORD*)0x967CF8;

DWORD bra_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 9;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 1, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 2, 19), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 28, 14, 28, 0, 0, 1, 0, prizeMoneyFile.GetInt("bra_cup_r1_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 2, 20), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 2, 26), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 88, 44, 74, 28, 0, 1, 0, prizeMoneyFile.GetInt("bra_cup_r2_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 2, 27), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 3, 12), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 48, 24, 4, 102, 0, 1, 0, prizeMoneyFile.GetInt("bra_cup_r3_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 3, 13), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 3, 19), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 24, 12, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("bra_cup_r4_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 3, 20), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 23), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 4, Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 4, 32, 16, 20, 106, 0, 2, 21, prizeMoneyFile.GetInt("bra_cup_r5_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 15), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 3), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 4, 16, 8, 0, 0, 0, 2, 3, prizeMoneyFile.GetInt("bra_cup_r6_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 7), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 27), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 4, 8, 4, 0, 0, 0, 2, 7, prizeMoneyFile.GetInt("bra_cup_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 4), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 6, 4, 2, 0, 0, 0, 2, 7, prizeMoneyFile.GetInt("bra_cup_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 10), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 7), year, Sunday, Evening, Neutral50k_20);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("bra_cup_final_win"), prizeMoneyFile.GetInt("bra_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) bra_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call bra_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int bra_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 126;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)comp_data->special_teams_seedings;

	for (DWORD i = 0; i < total_teams; i++)
	{
		teams[i].club = qualifiers[i].club;
		teams[i].f5 = qualifiers[i].f5;
		teams[i].f6 = 0;
	}

	sub_9452CA_free(comp_data->special_teams_seedings);
	comp_data->special_teams_seedings = 0;

	return 1;
}

void bra_cup_first_year_teams(BYTE* _this) {
	WORD total_teams = 126;
	comp_stats* cup_data = (comp_stats*)_this;
	if (!cup_data) return;
	//cup_data->special_nteams_seedings = total_teams;
	vector<cm3_clubs*> all_clubs;
	// Série D
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(BRA_FOURTH_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (WORD i = 0; i < 32; i++) {
		//dprintf("Club %s has qualified for Copa do Brasil! (from Série D)\n", division_clubs[i]->ClubNameShort);
		all_clubs.push_back(division_clubs[i]);
	}
	// Série C
	division_clubs = find_clubs_of_comp(BRA_THIRD_9CF());
	for (WORD i = 0; i < division_clubs.size(); i++) {
		//dprintf("Club %s has qualified for Copa do Brasil! (from Série C)\n", division_clubs[i]->ClubNameShort);
		all_clubs.push_back(division_clubs[i]);
	}
	// Série B
	division_clubs = find_clubs_of_comp(BRA_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (WORD i = 0; i < division_clubs.size(); i++) {
		//dprintf("Club %s has qualified for Copa do Brasil! (from Série B)\n", division_clubs[i]->ClubNameShort);
		all_clubs.push_back(division_clubs[i]);
	}
	// Série A
	division_clubs = find_clubs_of_comp(BRA_FIRST_9CF());
	for (WORD i = 0; i < division_clubs.size(); i++) {
		//dprintf("Club %s has qualified for Copa do Brasil! (from Série A)\n", division_clubs[i]->ClubNameShort);
		all_clubs.push_back(division_clubs[i]);
	}
	// State teams
	vector<cm3_clubs*> first_phase;
	BYTE state_counts[12] = { 2,3,2,6,2,2,2,5,3,2,3,2 };
	for (size_t i = 0; i < state_leagues.size(); i++) {
		cm3_club_comps* lower = get_comp(state_lower[i]);
		vector<cm3_clubs*> state_clubs = find_clubs_of_comp_reserve_division(state_leagues[i]);
		sort(state_clubs.begin(), state_clubs.end(), compareClubRep);
		BYTE count = state_counts[i];
		//dprintf("Getting %d teams from league: %s\n", count, get_comp(state_leagues[i])->ClubCompNameShort);
		for (WORD j = 0; j < state_clubs.size() && count > 0; j++) {
			if (vector_contains_element(all_clubs, state_clubs[j])) continue;
			//dprintf("- Club %s has qualified to Copa do Brasil! (from state league)\n", state_clubs[j]->ClubNameShort, j + 1);
			first_phase.push_back(state_clubs[j]);
			count--;
		}
		if (count > 0) {
			state_clubs = find_clubs_of_comp_reserve_division(state_lower[i]);
			sort(state_clubs.begin(), state_clubs.end(), compareClubRep);
			for (WORD j = 0; j < state_clubs.size() && count > 0; j++) {
				if (vector_contains_element(all_clubs, state_clubs[j])) continue;
				//dprintf("- Club %s has qualified to Copa do Brasil! (from lower leagues)\n", state_clubs[j]->ClubNameShort);
				first_phase.push_back(state_clubs[j]);
				count--;
			}
		}
	}
	sort(first_phase.begin(), first_phase.end(), compareClubRepInv);

	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);
	cup_data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)cup_data->special_teams_seedings;

	size_t i;
	for (i = 0; i < first_phase.size(); i++)
	{
		teams[i].club = first_phase[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}
	WORD d1_teams = 20;
	for (size_t j = 0; i < total_teams && j < all_clubs.size(); i++, j++)
	{
		teams[i].club = all_clubs[j];
		teams[i].f5 = 0 + 3 * (j >= (all_clubs.size() - d1_teams));
		teams[i].f6 = 0;
	}
}

void bra_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = bra_cup_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 7;
	data->max_subs = 3;
	data->rules = RulesBrazilNational;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	bra_cup_first_year_teams(_this);
	bra_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	cup_reputation_setup_generic_5223A0(_this);
}

char bra_cup_update(BYTE* _this) {
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
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	bra_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) bra_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bra_cup_update
		add esp, 0x4
		ret
	}
}

void setup_bra_cup()
{
	WriteVTablePtr(bra_cup_vtable, VTableEoSUpdate, (DWORD)&bra_cup_update_c);
	WriteVTablePtr(bra_cup_vtable, VTableFixtures, (DWORD)&bra_cup_fixture_caller);
}
