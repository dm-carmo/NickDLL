#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* spa_cup_vtable = (DWORD*)0x96F9C8;

void spa_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = spa_cup_vtable;
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

void spa_cup_free(BYTE* _this, BYTE a2) {
	spa_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) spa_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call spa_cup_free
		add esp, 0x8
		ret 4
	}
}

DWORD spa_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 7;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 112, 56, 112, 0, 0, 1, 0, prizeMoneyFile.GetInt("spa_cup_r1_qualify"), prizeMoneyFile.GetInt("spa_cup_r1_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 56, 28, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("spa_cup_r2_win"), 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 4), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 17), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, RoundOf32, 1, Penalties | ExtraTime, NoTiebreak, 4, 32, 16, 4, 112, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("spa_cup_r3_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 18), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 7), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 1, Penalties | ExtraTime, NoTiebreak, 4, 16, 8, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("spa_cup_r4_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 8), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 14), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, Penalties | ExtraTime, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, 0, 0, prizeMoneyFile.GetInt("spa_cup_qtr_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 15), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 11), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 6, 4, 2, 0, 0, 0, 2, 21, 0, 0, prizeMoneyFile.GetInt("spa_cup_semi_lose"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 5), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday, Afternoon, LargestStadium2);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("spa_cup_final_win"), prizeMoneyFile.GetInt("spa_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) spa_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call spa_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int spa_cup_first_year_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 116;
	//cup_data->special_nteams_seedings = total_teams;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);
	comp_data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;

	// 5x2 from Primera Fed and 5x5 from Segunda Fed
	WORD main_teams = CountNumberOfTeamsInComp(SPA_FIRST_9CF()) + CountNumberOfTeamsInCompNoReserve(SPA_SECOND_9CF()) + 10 + 25;
	WORD lower_teams = total_teams - main_teams;

	vector<cm3_clubs*> vec_super;
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp_last_division(SPA_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);

	cm3_club_comps* spa_cup = get_comp(SPA_CUP_9CF());
	cm3_clubs* winner = get_last_comp_winner(spa_cup);
	if (winner) vec_super.push_back(winner);
	cm3_clubs* runner_up = get_last_comp_runner_up(spa_cup);
	if (runner_up) vec_super.push_back(runner_up);

	for (cm3_clubs* c : division_clubs) {
		if (!vector_contains_element(vec_super, c)) vec_super.push_back(c);
		if (vec_super.size() >= 4) break;
	}

	// Lower
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_SPAIN_9CF());
	for (size_t i = 0; i < lower_clubs.size(); i++) {
		cm3_clubs* c = lower_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if ((ret_club && !is_main_club) || vector_contains_element(vec_super, c))
		{
			lower_clubs.erase(lower_clubs.begin() + i);
			i--;
		}
	}
	division_clubs = get_random_weighted_clubs(lower_clubs, lower_teams, true);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Segunda Federación
	BYTE selected = get_country(NATION_SPAIN_9CF())->NationLeagueSelected;
	division_clubs = find_clubs_of_comp(SPA_FOURTH_9CF());
	if ((selected & 4) != 0) sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	else sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (unsigned int i = 0; i < 25; i++)
	{
		int availableIdx = rand() % division_clubs.size();
		cm3_clubs* club = division_clubs[availableIdx];

		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (ret_club && !is_main_club)
			i--;
		else if (!vector_contains_element(vec_super, club))
			vec.push_back(club);

		division_clubs.erase(division_clubs.begin() + availableIdx);
	}
	// Primera Federacion
	division_clubs = find_clubs_of_comp(SPA_THIRD_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (unsigned int i = 0; i < 10; i++)
	{
		int availableIdx = rand() % division_clubs.size();
		cm3_clubs* club = division_clubs[availableIdx];

		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (ret_club && !is_main_club)
			i--;
		else if (!vector_contains_element(vec_super, club))
			vec.push_back(club);

		division_clubs.erase(division_clubs.begin() + availableIdx);
	}
	// La Liga 2
	division_clubs = find_clubs_of_comp(SPA_SECOND_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if ((!ret_club || is_main_club) && !vector_contains_element(vec_super, club)) vec.push_back(club);
	}
	// La Liga
	division_clubs = find_clubs_of_comp(SPA_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_element(vec_super, club)) vec.push_back(club);
	}

	for (size_t i = 0; i < vec_super.size(); i++) vec.push_back(vec_super[i]);

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

int spa_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 116;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)comp_data->special_teams_seedings;

	for (DWORD i = 0; i < total_teams; i++)
	{
		teams[i].club = qualifiers[i].club;
		teams[i].seeding = qualifiers[i].seeding;
		teams[i].f6 = 0;
	}

	sub_9452CA_free(comp_data->special_teams_seedings);
	comp_data->special_teams_seedings = 0;

	return 1;
}

void spa_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = spa_cup_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesSpainCup;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	spa_cup_first_year_teams(_this);
	spa_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	cup_reputation_setup_generic_5223A0(_this);
}

void __declspec(naked) spa_cup_init_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call spa_cup_init
		add esp, 0xc
		ret 8
	}
}

char spa_cup_update(BYTE* _this) {
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
	spa_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) spa_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call spa_cup_update
		add esp, 0x4
		ret
	}
}

void setup_spa_cup()
{
	WriteVTablePtr(spa_cup_vtable, VTableInitFree, (DWORD)&spa_cup_free_c);
	WriteVTablePtr(spa_cup_vtable, VTableEoSUpdate, (DWORD)&spa_cup_update_c);
	WriteVTablePtr(spa_cup_vtable, VTableFixtures, (DWORD)&spa_cup_fixture_caller);
	WriteVTablePtr(spa_cup_vtable, VTableLeagueSplit, 0x51F890);
	WriteVTablePtr(spa_cup_vtable, VTableSubsRounds, 0x858e70);
}
