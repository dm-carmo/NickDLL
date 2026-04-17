#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>
#include <map>

using namespace std;

DWORD* rus_cup_vtable = (DWORD*)0x96F124;

int rus_cup_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[6];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) rus_cup_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_cup_set_champion
		add esp, 0x4
		ret 0
	}
}

void rus_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = rus_cup_vtable;
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

void rus_cup_free(BYTE* _this, BYTE a2) {
	rus_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) rus_cup_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call rus_cup_free
		add esp, 0x8
		ret 4
	}
}

int rus_cup_all_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 104;
	comp_data->special_nteams_seedings = total_teams;
	//comp_data->f56 = total_teams;

	if (comp_data->special_teams_seedings) sub_9452CA_free(comp_data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);
	comp_data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	WORD main_teams = CountNumberOfTeamsInComp(RUS_PREMIER_9CF()) + CountNumberOfTeamsInCompNoReserve(RUS_FIRST_9CF()) +
		CountNumberOfTeamsInCompNoReserve(RUS_SECOND_A_9CF()) + CountNumberOfTeamsInCompNoReserve(RUS_SECOND_B_9CF());
	WORD lower_teams = total_teams - main_teams;

	// Lower
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_RUSSIA_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	for (unsigned int i = 0; i < lower_teams; i++)
	{
		int availableIdx = rand() % division_clubs.size();
		cm3_clubs* lower_club = division_clubs[availableIdx];

		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)lower_club, &is_main_club, 1);
		if (ret_club && !is_main_club)
			i--;
		else
			vec.push_back(lower_club);

		division_clubs.erase(division_clubs.begin() + availableIdx);
	}
	// Second B
	division_clubs = find_clubs_of_comp(RUS_SECOND_B_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubRepInv);
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) vec.push_back(club);
	}
	// Second A
	division_clubs = find_clubs_of_comp(RUS_SECOND_A_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) vec.push_back(club);
	}
	// First League
	division_clubs = find_clubs_of_comp(RUS_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if (!ret_club || is_main_club) vec.push_back(club);
	}
	// Premier League
	division_clubs = find_clubs_of_comp(RUS_PREMIER_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
	shuffle(division_clubs.begin(), division_clubs.begin() + 4, rng);
	shuffle(division_clubs.begin() + 4, division_clubs.begin() + 8, rng);
	shuffle(division_clubs.begin() + 8, division_clubs.begin() + 12, rng);
	shuffle(division_clubs.begin() + 12, division_clubs.end(), rng);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

void rus_cup_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 88;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	for (WORD i = 0; i < total_teams; i++) {
		teams[i].club = qualifiers[i].club;
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}
}

void rus_cup_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(total_teams * 4);

	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	WORD start = 88;
	DWORD total_count = data->special_nteams_seedings;
	for (WORD i = 0; i < total_teams; i++) {
		cm3_clubs* c = qualifiers[start + idx + i * 4].club;
		*((DWORD*)(&pTeams[i])) = (DWORD)c;
	}

	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	BYTE prom_rel[4] = { 2, 0, 0, 0 };
	BYTE tiebreaks[4] = { CurrentPositionTiebreaker, GamesWonTiebreaker, GoalDifferenceTiebreaker, GoalsForTiebreaker };
	create_league_stage_data(pStage, _this, total_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		3, 1, 2, &tiebreaks[0], &prom_rel[0], year, idx, stage_name_id, data->f81, 1, 0, 0x28, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	sub_684230(pStage);
	data->current_stage = idx;
}

DWORD rus_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = QualifyingRound;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 6), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 28, 14, 28, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("rus_cup_r1_win"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 7), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 20), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 56, 28, 42, 28, 0, 1, 0, 0, prizeMoneyFile.GetInt("rus_cup_r2_win"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 21), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 10), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 28, 14, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("rus_cup_r3_win"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 11), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 24), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 18, 70, 0, 1, 0, 0, prizeMoneyFile.GetInt("rus_cup_r4_win"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 25), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 15), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("rus_cup_r5_win"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 16), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SixthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 8, 4, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("rus_cup_r6_win"));

		return (DWORD)pMem;
	}
	else if (stage_idx < 4) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = AlphabeticGroupStage + stage_idx - 1;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 30), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 13), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 27), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 17), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 1), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 22), year, Wednesday, Evening);

		return (DWORD)pMem;
	}
	else if (stage_idx == 4) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = RPLPath;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 23), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 5), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 4, 8, 4, 8, 0, 0, 2, 21, 0, prizeMoneyFile.GetInt("rus_cup_sub_qtr_win"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 27), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 4), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 4, 4, 2, 0, 0, 0, 2, 14, 0, prizeMoneyFile.GetInt("rus_cup_sub_semi_win"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 19), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 9), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 2, 1, 0, 0, 0, 2, 28, 0, prizeMoneyFile.GetInt("rus_cup_sub_final_win"));

		return (DWORD)pMem;
	}
	else if (stage_idx == 5) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = RegionsPath;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 23), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 26), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 4, 8, 4, 8, 0, 0, 2, 98, 0, prizeMoneyFile.GetInt("rus_cup_sub_qtr_win"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 5), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 18), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 4, 4, 2, 0, 0, 0, 2, 21, 0, prizeMoneyFile.GetInt("rus_cup_sub_semi_win"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 9), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 6), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("rus_cup_sub_final_win"));

		return (DWORD)pMem;
	}
	else if (stage_idx == 6) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 8), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 24), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 2, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("rus_cup_final_win"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) rus_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call rus_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void rus_cup_reputation_setup(BYTE* _this) {
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
		for (int i = 2; i < 4; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 3);
		}
		for (int i = 4; i < 8; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 5);
		}
		for (int i = 8; i < 16; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (int i = 16; i < 20; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 20; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 21);
		}
		for (int i = 24; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25);
		}
		for (int i = 32; i < 48; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
		for (int i = 48; i < 62; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 49);
		}
		for (int i = 62; i < 90; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 63);
		}
		for (int i = 90; i < 104; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 91);
		}
		comp_data->special_nteams_seedings = 0;
		sub_9452CA_free(comp_data->special_teams_seedings);
		comp_data->special_teams_seedings = 0;
	}
}

void __declspec(naked) rus_cup_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_cup_reputation_setup
		add esp, 0x4
		ret
	}
}

void rus_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = rus_cup_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 7;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->rules = RulesRussia;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	rus_cup_all_teams(_this);
	rus_cup_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	data->max_bench = 7;
	data->max_subs = 3;
	for (BYTE i = 0; i < 4; i++) {
		rus_cup_setup_groups(_this, i);
	}
	rus_cup_reputation_setup(_this);
}

void __declspec(naked) rus_cup_init_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call rus_cup_init
		add esp, 0xc
		ret 8
	}
}

char rus_cup_update(BYTE* _this) {
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
	rus_cup_all_teams(_this);
	rus_cup_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	for (BYTE i = 0; i < 4; i++) {
		rus_cup_setup_groups(_this, i);
	}
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) rus_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_cup_update
		add esp, 0x4
		ret
	}
}

map<char, char> rus_cup_mappings = {
	{1,9},
	{9,25},
	{17,33},
	{33,49},
	{47,63},
	{75,91},
};

void rus_cup_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = rus_cup_mappings[current];
		if (ret_min != 1) ret_min = rus_cup_mappings[min];
		ret_max = rus_cup_mappings[max];
	}
	else if (stage < 4) {
		ret_current = 1 + 4 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 4 * (min - 1);
		if (max < 3) ret_max = 9;
		else if (max < 4) ret_max = 17;
		else ret_max = 1 + 4 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 4 || stage == 5) {
		// do nothing
		if (current > 1) ret_current = current + (current - 1);
		if (min > 1) ret_min = min + (min - 1);
		if (max > 1) ret_max = max + (max - 1);
		else max = 2;
	}
	else if (stage == 6) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) rus_cup_reputation_calc_c()
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
		call rus_cup_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

int rus_cup_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), RegionsPath, QuarterFinal, 0x1E);
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
	else if (stage < 4) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), RPLPath, QuarterFinal, 0x1E);
			return 0;
		default:
			//staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			return 0;
		}
	}
	else if (stage == 4 || stage == 5) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Final, 0x1E);
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
	else if (stage == 6) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
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

void __declspec(naked) rus_cup_set_table_fate()
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
		call rus_cup_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void rus_cup_rpl_stage_setup(BYTE* _this) {
	char stage_num = 4;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	vector<cm3_clubs*> clubs;
	for (char al = 0; al < 4; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
	}

	BYTE team_order[8] = { 0,2,4,6,7,5,3,1 };
	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)clubs[j];
	}

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

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	for (char al = 0; al < 4; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats t = ((team_league_stats*)(curr_stage->team_league_table))[2];
		staff_history_qualified_86BDD0(staff_hist_ptr, t.club, (DWORD)(comp_data->competition_db), RegionsPath, QuarterFinal, 0x1E);

		t = ((team_league_stats*)(curr_stage->team_league_table))[3];
		staff_history_knocked_out_86C000(staff_hist_ptr, t.club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
	}
}

void rus_cup_regions_stage_setup(BYTE* _this) {
	char stage_num = 5;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	vector<cm3_clubs*> clubs;
	for (char al = 0; al < 4; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[2].club);
	}
	for (WORD j = 0; j < comp_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)comp_data->teams_list)[j];
		if (t.f6 == 1) clubs.push_back(t.club);
	}

	shuffle(clubs.begin(), clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.end(), rng);
	BYTE team_order[8] = { 0,2,4,6,7,5,3,1 };
	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)clubs[j];
	}

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

void rus_cup_final_stage_setup(BYTE* _this) {
	char stage_num = 6;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	comp_stats* rpl_data = (comp_stats*)comp_data->stages[4];
	for (WORD j = 0; j < rpl_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)rpl_data->teams_list)[j];
		if (t.f6 == 1) {
			*((DWORD*)(&pTeams[0])) = (DWORD)t.club;
			break;
		}
	}
	comp_stats* reg_data = (comp_stats*)comp_data->stages[5];
	for (WORD j = 0; j < reg_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)reg_data->teams_list)[j];
		if (t.f6 == 1) {
			*((DWORD*)(&pTeams[1])) = (DWORD)t.club;
			break;
		}
	}

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

void rus_cup_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 4) {
			rus_cup_rpl_stage_setup(_this);
			rus_cup_regions_stage_setup(_this);
		}
		else if (current == 6) {
			rus_cup_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) rus_cup_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_cup_stages_create
		add esp, 0x4
		ret
	}
}

void setup_rus_cup() {
	WriteVTablePtr(rus_cup_vtable, VTableLeagueSplit, 0x51F890);
	WriteVTablePtr(rus_cup_vtable, VTableInitFree, (DWORD)&rus_cup_free_c);
	WriteVTablePtr(rus_cup_vtable, VTableEoSUpdate, (DWORD)&rus_cup_update_c);
	WriteVTablePtr(rus_cup_vtable, VTableFixtures, (DWORD)&rus_cup_fixture_caller);
	WriteVTablePtr(rus_cup_vtable, VTableReputationSetup, (DWORD)&rus_cup_reputation_setup_c);
	WriteVTablePtr(rus_cup_vtable, VTableReputationCalc, (DWORD)&rus_cup_reputation_calc_c);
	WriteVTablePtr(rus_cup_vtable, VTableTableFates, (DWORD)&rus_cup_set_table_fate);
	WriteVTablePtr(rus_cup_vtable, VTablePlayoffQual, (DWORD)&rus_cup_stages_create_c);
	WriteVTablePtr(rus_cup_vtable, VTableSetChampion, (DWORD)&rus_cup_set_champion_c);
	char* rpl_path_text = "RPL Path";
	char* rpl_path_short = "RPL Path";
	WriteDWORD(0x4B63d0 + 1, (DWORD)&rpl_path_text[0]);
	WriteDWORD(0x4B8ebd + 1, (DWORD)&rpl_path_short[0]);
	char* regions_path_text = "Regions Path";
	char* regions_path_text_short = "Regions Path";
	WriteDWORD(0x4B63ea + 1, (DWORD)&regions_path_text[0]);
	WriteDWORD(0x4B8ed7 + 1, (DWORD)&regions_path_text_short[0]);
}