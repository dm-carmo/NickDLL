#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* tur_cup_vtable = (DWORD*)0x97048C;

void tur_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = tur_cup_vtable;
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

void tur_cup_free(BYTE* _this, BYTE a2) {
	tur_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) tur_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call tur_cup_free
		add esp, 0x8
		ret 4
	}
}

DWORD tur_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 9;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 16), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, Penalties | ExtraTime, NoTiebreak, 4, 40, 20, 40, 0, 0, 1, 0, prizeMoneyFile.GetInt("tur_cup_r1_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 17), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 7), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, Penalties | ExtraTime, NoTiebreak, 4, 62, 31, 42, 40, 0, 1, 0, prizeMoneyFile.GetInt("tur_cup_r2_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 8), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 28), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 72, 36, 41, 82, 0, 1, 0, prizeMoneyFile.GetInt("tur_cup_r3_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 2), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 54, 27, 18, 123, 0, 1, 0, prizeMoneyFile.GetInt("tur_cup_r4_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 3), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 16), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 0, Penalties | ExtraTime, NoTiebreak, 4, 32, 16, 5, 141, 0, 1, 0, prizeMoneyFile.GetInt("tur_cup_r5_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 17), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 13), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 1, Penalties | ExtraTime, NoTiebreak, 4, 16, 8, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("tur_cup_r16_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 14), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, Penalties | ExtraTime, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("tur_cup_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 6, 4, 2, 0, 0, 0, 2, 49, prizeMoneyFile.GetInt("tur_cup_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 22), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 29), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("tur_cup_final_win"), prizeMoneyFile.GetInt("tur_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) tur_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call tur_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int tur_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	vector<cm3_clubs*> vec_uefa;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 146;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	vector<cm3_clubs*> division_clubs = find_clubs_of_country(NATION_TURKEY_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		if (club->ClubEuroFlag != -1) vec_uefa.push_back(club);
	}
	sort(vec_uefa.begin(), vec_uefa.end(), compareClubLastDivPosInv);

	// Lower
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_TURKEY_9CF());
	for (size_t i = 0; i < lower_clubs.size(); i++) {
		cm3_clubs* c = lower_clubs[i];
		if (vector_contains_element(vec_uefa, c))
		{
			lower_clubs.erase(lower_clubs.begin() + i);
			i--;
		}
	}
	division_clubs = get_random_weighted_clubs(lower_clubs, 18 + (comp_data->year == 2026 ? 1 : 0), true);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// 3. Lig
	division_clubs = find_clubs_of_comp(TUR_FOURTH_9CF());
	BYTE selected = get_country(NATION_TURKEY_9CF())->NationLeagueSelected;
	if ((selected & 4) != 0) sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	else sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_element(vec_uefa, club)) vec.push_back(club);
	}
	// 2. Lig
	division_clubs = find_clubs_of_comp(TUR_THIRD_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_element(vec_uefa, club)) vec.push_back(club);
	}
	// 1. Lig
	division_clubs = find_clubs_of_comp(TUR_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_element(vec_uefa, club)) vec.push_back(club);
	}
	// Super Lig
	division_clubs = find_clubs_of_comp(TUR_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_element(vec_uefa, club)) vec.push_back(club);
	}

	for (cm3_clubs* club : vec_uefa)
	{
		vec.push_back(club);
	}

	while (vec.size() > total_teams) {
		vec.erase(vec.begin());
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

char tur_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
		data->teams_list = 0;
	}
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
	tur_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) tur_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call tur_cup_update
		add esp, 0x4
		ret
	}
}

void tur_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = tur_cup_vtable;
	data->year = year;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesTurkeyCup;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	tur_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	cup_reputation_setup_generic_5223A0(_this);
}

void setup_tur_cup()
{
	WriteVTablePtr(tur_cup_vtable, VTableFixtures, (DWORD)&tur_cup_fixture_caller);
	WriteVTablePtr(tur_cup_vtable, VTableInitFree, (DWORD)&tur_cup_free_c);
	WriteVTablePtr(tur_cup_vtable, VTableEoSUpdate, (DWORD)&tur_cup_update_c);
	WriteVTablePtr(tur_cup_vtable, VTableSubsRounds, 0x858e70);
}
