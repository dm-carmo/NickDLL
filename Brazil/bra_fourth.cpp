#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>
#include <cmath>

DWORD* bra_fourth_vtable = (DWORD*)0x967F00;

int bra_fourth_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[15];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) bra_fourth_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bra_fourth_set_champion
		add esp, 0x4
		ret 0
	}
}

void bra_fourth_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GamesWonTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->tiebreaker_4 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 4;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = BRA_THIRD_9CF();
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x2;
	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) bra_fourth_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bra_fourth_subs
		add esp, 0x4
		ret
	}
}

int bra_fourth_add_teams(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;
	DWORD* all_teams = comp_data->teams2;
	if (all_teams) sub_9452CA_free(all_teams);

	WORD numberOfLeagueTeams = CountNumberOfTeamsInComp(CompID);
	comp_data->teams2 = (DWORD*)sub_944E46_malloc(numberOfLeagueTeams * 4);
	vector<cm3_clubs*> d4_clubs = find_clubs_of_comp(CompID);
	sort(d4_clubs.begin(), d4_clubs.end(), compareClubEWDiagNS);
	for (DWORD i = 0; i < d4_clubs.size(); i++)
	{
		*((DWORD*)(&comp_data->teams2[i])) = (DWORD)d4_clubs[i];
	}

	comp_data->n_teams = 6; // number of teams per group in this case
	comp_data->team_league_table = (DWORD*)sub_944E46_malloc(comp_data->n_teams * league_team_list_sz);
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < comp_data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)(comp_data->teams2[i]);
		add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

void bra_fourth_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(data->n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)all_teams[data->n_teams * (idx + 1) + i];
		*((DWORD*)(&pTeams[i])) = (DWORD)club;
	}
	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, data->n_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void bra_fourth_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 15) {
		ret_current = 1 + 16 * (current - 1);
		if (min < 5) ret_min = 1;
		else ret_min = 1 + 16 * (min - 1);
		if (max < 5) ret_max = 17;
		else ret_max = 1 + 16 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 15) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) bra_fourth_reputation_calc_c()
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
		call bra_fourth_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

DWORD bra_fourth_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 15) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 6;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = NumericGroupStage + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 5), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 19), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 3), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 10), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 17), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 24), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 31), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 14), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 15) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 15), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 21), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 5, 64, 32, 64, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 29), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 5), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 5, 32, 16, 0, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 13), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 19), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 5, 16, 8, 0, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 27), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 9), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 5, 8, 4, 0, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 17), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 23), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 5, 4, 2, 0, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 31), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 6), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 5, 2, 1, 0, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) bra_fourth_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call bra_fourth_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void bra_fourth_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		DWORD* all_teams = comp_data->teams2;
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < 96; i++) clubs.push_back((cm3_clubs*)all_teams[i]);
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
		for (int i = 16; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 32; i < 64; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
		for (int i = 64; i < 80; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 65);
		}
		for (int i = 80; i < 96; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 81);
		}
	}
}

void __declspec(naked) bra_fourth_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bra_fourth_reputation_setup
		add esp, 0x4
		ret
	}
}

void bra_fourth_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = bra_fourth_vtable;
	data->year = year;
	data->rules = RulesBrazilNational;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 16;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	bra_fourth_subs(_this);
	data->teams2 = 0;
	bra_fourth_add_teams(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	for (BYTE i = 0; i < 15; i++) {
		bra_fourth_setup_groups(_this, i);
	}
	bra_fourth_reputation_setup(_this);
}

char bra_fourth_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	sub_687970(_this, ebx);
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
	data->year++;
	data->current_stage = -1;
	bra_fourth_subs(_this);
	bra_fourth_add_teams(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 15; i++) {
		bra_fourth_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) bra_fourth_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bra_fourth_update
		add esp, 0x4
		ret
	}
}

int bra_fourth_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 15) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SecondRound, 0x1E);
			return 0;
		case BottomPlayoff:
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 15) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);

		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 15; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					table[i].league_fate = Champions;
					*a5 = 1;
					return 0;
				case Promoted:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					if (current_round == 0) {
						staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, None, 0x1E);
					}
					else if (current_round == 3) {
						staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
						table[i].league_fate = Promoted;
					}
					return 0;
				case BottomPlayoff:
					staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
					//table[i].league_fate = Eliminated;
					return 0;
				default:
					staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
					if (current_round == 0) {
						table[i].league_fate = Eliminated;
					}
					//table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	return 0;
}

void __declspec(naked) bra_fourth_set_table_fate()
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
		call bra_fourth_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void bra_fourth_playoff_under(BYTE* _this) {
	char stage_num = 15;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 64;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	vector<cm3_clubs*> clubs;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 15; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
		}
	}

	BYTE team_idx = 0;
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[0];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[7];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[13];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[10];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[5];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[2];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[1];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[6];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[12];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[11];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[8];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[15];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[4];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[3];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[9];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[14];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[16];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[23];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[29];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[26];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[21];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[18];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[24];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[31];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[20];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[19];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[25];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[30];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[17];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[22];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[28];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[27];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[32];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[39];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[45];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[42];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[37];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[34];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[33];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[38];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[44];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[43];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[40];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[47];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[36];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[35];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[41];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[46];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[48];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[55];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[61];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[58];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[53];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[50];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[56];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[63];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[52];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[51];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[57];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[62];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[49];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[54];

	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[60];
	*((DWORD*)(&pTeams[team_idx++])) = (DWORD)clubs[59];

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void bra_fourth_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 15) {
			bra_fourth_playoff_under(_this);
		}
	}
}

void __declspec(naked) bra_fourth_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bra_fourth_playoffs_c
		add esp, 0x4
		ret
	}
}

void setup_bra_fourth() {
	WriteVTablePtr(bra_fourth_vtable, VTableSubsRounds, (DWORD)&bra_fourth_subs_c);
	WriteVTablePtr(bra_fourth_vtable, VTableReputationSetup, (DWORD)&bra_fourth_reputation_setup_c);
	WriteVTablePtr(bra_fourth_vtable, VTableFixtures, (DWORD)&bra_fourth_fixtures_c);
	WriteVTablePtr(bra_fourth_vtable, VTableEoSUpdate, (DWORD)&bra_fourth_update_c);
	WriteVTablePtr(bra_fourth_vtable, VTableReputationCalc, (DWORD)&bra_fourth_reputation_calc_c);
	WriteVTablePtr(bra_fourth_vtable, VTableSetChampion, (DWORD)&bra_fourth_set_champion_c);
	WriteVTablePtr(bra_fourth_vtable, VTableTableFates, (DWORD)&bra_fourth_set_table_fate);
	WriteVTablePtr(bra_fourth_vtable, VTableStageNews, 0x48c6d0);
	WriteVTablePtr(bra_fourth_vtable, VTablePlayoffQual, (DWORD)&bra_fourth_playoffs_create);
	WriteVTablePtr(bra_fourth_vtable, VTable37, 0x68aad0);
	WriteVTablePtr(bra_fourth_vtable, VTable39, 0x404480);
}