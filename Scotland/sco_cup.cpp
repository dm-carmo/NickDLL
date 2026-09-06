#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* sco_cup_vtable = (DWORD*)0x96F414;

int sco_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 76;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	// Highland+Lowland
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(SCO_HIGHLAND_9CF());
	vector<cm3_clubs*> division_clubs2 = find_clubs_of_comp(SCO_LOWLAND_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	for (size_t i = 0; i < division_clubs.size(); i++) {
		cm3_clubs* c = division_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club)
		{
			division_clubs.erase(division_clubs.begin() + i);
			i--;
		}
	}
	BYTE selected = get_country(NATION_SCOTLAND_9CF())->NationLeagueSelected;
	if ((selected & 4) != 0) sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	else sort(division_clubs.begin(), division_clubs.end(), compareClubRepInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// League 2
	division_clubs = find_clubs_of_comp(SCO_LEAGUE_2_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// League 1
	division_clubs = find_clubs_of_comp(SCO_LEAGUE_1_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Championshio
	division_clubs = find_clubs_of_comp(SCO_CHAMP_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Premier
	division_clubs = find_clubs_of_comp(SCO_PREMIER_9CF());
	for (cm3_clubs* club : division_clubs)
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

DWORD sco_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 8;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 31), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, Penalties, NoTiebreak, 4, 8, 4, 8, 0, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_r1_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, Penalties, NoTiebreak, 4, 40, 20, 36, 8, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_r2_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, Penalties, NoTiebreak, 4, 40, 20, 20, 44, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_r3_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 30), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 17), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, Penalties, NoTiebreak, 4, 32, 16, 12, 64, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_r4_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 18), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 0, Penalties, NoTiebreak, 4, 16, 8, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_r5_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, Penalties, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Saturday);
		AddPlayoffTVFixture(pMem, fixture_id, 0, 1, Saturday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, 1, 1, Sunday, Afternoon, NationalStadium);
		AddPlayoffTVFixture(pMem, fixture_id, 2);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup2 | Penalties, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("sco_cup_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 20), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 23), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("sco_cup_final_win"), prizeMoneyFile.GetInt("sco_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) sco_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void sco_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = sco_cup_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->rules = RulesScotlandCup;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	sco_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->max_bench = 9;
	data->max_subs = 5;
	cup_reputation_setup_generic_5223A0(_this);
}

void __declspec(naked) sco_cup_init_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_cup_init
		add esp, 0xc
		ret 8
	}
}

char sco_cup_update(BYTE* _this) {
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
	sco_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) sco_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_cup_update
		add esp, 0x4
		ret
	}
}

void setup_sco_cup() {
	WriteVTablePtr(sco_cup_vtable, VTableFixtures, (DWORD)&sco_cup_fixture_caller);
	WriteVTablePtr(sco_cup_vtable, VTableEoSUpdate, (DWORD)&sco_cup_update_c);
	WriteVTablePtr(sco_cup_vtable, VTableSubsRounds, 0x858e70);
}