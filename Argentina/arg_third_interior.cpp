#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

vtable* arg_third_interior_vtable = new vtable((BYTE*)0x970844, 0xB4);

void arg_third_interior_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(arg_third_interior_vtable->vtable_ptr);
	DWORD x = 0;
	sub_687970(_this, 0);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
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
	sub_682300(_this);
}

void arg_third_interior_free(BYTE* _this, BYTE a2) {
	arg_third_interior_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) arg_third_interior_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call arg_third_interior_free
		add esp, 0x8
		ret 4
	}
}

int arg_third_interior_last_positions(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	for (char al = 3; al < 5; al++)
	{
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			tls.club->ClubLastDivision = comp_data->competition_db;
			tls.club->ClubLastPosition = (char)i + 1;
		}
	}

	for (char al = 5; al < 7; al++)
	{
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			tls.club->ClubLastDivision = comp_data->competition_db;
			tls.club->ClubLastPosition = (char)i + 9;
		}
	}
	return 1;
}

void __declspec(naked) arg_third_interior_last_positions_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_third_interior_last_positions
		add esp, 0x4
		ret
	}
}

void arg_third_interior_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 3) {
		ret_current = 1 + 4 * (current - 1);
		ret_min = 1 + 4 * (min - 1);
		ret_max = 1 + 4 * (max - 1);
	}
	else if (stage < 5) {
		ret_current = 1 + 2 * (current - 1);
		ret_min = 1 + 2 * (min - 1);
		ret_max = 1 + 2 * (max - 1);
	}
	else if (stage < 7) {
		ret_current = 17 + 2 * (current - 1);
		ret_min = 17 + 2 * (min - 1);
		ret_max = 17 + 2 * (max - 1);
	}
	else if (stage == 7) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) arg_third_interior_reputation_calc_c()
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
		call arg_third_interior_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void arg_third_interior_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 3; al++) {
			vector<cm3_clubs*> clubs;
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			WORD total_teams = curr_stage->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				clubs.push_back(table_teams[i].club);
			}
			sort(clubs.begin(), clubs.end(), compareClubRep);
			for (size_t i = 0; i < clubs.size(); i++) {
				cm3_clubs* c = clubs[i];
				sub_4A2540((BYTE*)comp_data->f8, c, (char)(i * 2 + 1));
			}
		}
	}
}

void __declspec(naked) arg_third_interior_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_third_interior_reputation_setup
		add esp, 0x4
		ret
	}
}

int arg_third_interior_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[7];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) arg_third_interior_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_third_interior_set_champion
		add esp, 0x4
		ret 0
	}
}

int arg_third_interior_add_teams(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* all_teams = comp_data->teams2;
	if (all_teams) sub_9452CA_free(all_teams);

	vector<cm3_clubs*> champ_clubs = find_clubs_of_comp(comp_data->competition_db->ClubCompID);
	comp_data->teams2 = (DWORD*)sub_944E46_malloc(champ_clubs.size() * 4);
	sort(champ_clubs.begin(), champ_clubs.end(), compareClubLatitude);
	for (DWORD i = 0; i < champ_clubs.size(); i++)
	{
		*((DWORD*)(&comp_data->teams2[i])) = (DWORD)champ_clubs[i];
	}

	comp_data->n_teams = 9; // number of teams per group in this case
	comp_data->team_league_table = (DWORD*)sub_944E46_malloc(10 * league_team_list_sz);
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < comp_data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)(comp_data->teams2[i]);
		add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

void arg_third_interior_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(data->n_teams * 4);
	WORD teams_in_group = 9;
	WORD offset = teams_in_group * (idx + 1);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < teams_in_group; i++)
	{
		cm3_clubs* club = (cm3_clubs*)all_teams[offset + i];
		*((DWORD*)(&pTeams[i])) = (DWORD)club;
	}
	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	BYTE prom_rel[4] = { 0, 4, 5, 0 };
	create_league_stage_data(pStage, _this, teams_in_group, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), &prom_rel[0],
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void arg_third_interior_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 4;
	comp_data->rele_playoff = 5;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x2;
	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) arg_third_interior_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_third_interior_subs
		add esp, 0x4
		ret
	}
}

DWORD arg_third_interior_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 10;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = FirstRoundNumericGroup + (stage_idx + 1);

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 1), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 8), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 15), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 5), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 12), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 19), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 26), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 31), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 28), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx < 7) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 10;
		if (stage_idx < 5) numberOfLeagueTeams = 8;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		if (stage_idx < 5) *stage_name_id = PromotionGroupAtoD + (stage_idx - 3);
		else *stage_name_id = RelegationGroupAtoB + (stage_idx - 5);

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx >= 5) AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 12), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 19), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 26), year, Saturday);
		if (stage_idx >= 5) AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 23), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Saturday);
		if (stage_idx >= 5) AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 1), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Saturday);
		if (stage_idx >= 5) AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 15), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 7) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = Playoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 5, 8, 4, 8, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 30), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 5, 4, 2, 0, 0, 0, 2, 4);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 11), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 5, 2, 1, 0, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) arg_third_interior_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call arg_third_interior_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char arg_third_interior_update(BYTE* _this) {
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
	arg_third_interior_subs(_this);
	arg_third_interior_add_teams(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 3; i++) {
		arg_third_interior_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) arg_third_interior_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_third_interior_update
		add esp, 0x4
		ret
	}
}

int arg_third_interior_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 3) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, PromotionGroupStage, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RelegationGroupStage, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	else if (stage < 5) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 3; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case Champions:
					staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					table[i].league_fate = Champions;
					return 0;
				case Promoted:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x32);
					table[i].league_fate = Promoted;
					return 0;
				case TopPlayoff:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
					table[i].league_fate = TopPlayoff;
					return 0;
				case Eliminated:
					table[i].league_fate = Eliminated;
					return 0;
				case NoFate:
					table[i].league_fate = Eliminated;
					return 0;
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	else if (stage < 7) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 3; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case Relegated:
					staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					table[i].league_fate = Relegated;
					return 0;
				case Eliminated:
					table[i].league_fate = Eliminated;
					return 0;
				case NoFate:
					table[i].league_fate = Eliminated;
					return 0;
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	else if (stage == 7) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 3; al++) {
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
					//return 0;
					break;
				case Promoted:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					if (current_round == 1) {
						staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
						table[i].league_fate = Promoted;
					}
					//return 0;
					break;
				case BottomPlayoff:
					staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
					//table[i].league_fate = Eliminated;
					//return 0;
					break;
					//default:
						//table[i].league_fate = Eliminated;
						//return 0;
				}
			}
		}
		for (char al = 3; al < 5; al++) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					table[i].league_fate = Champions;
					*a5 = 1;
					return 0;
				case Promoted:
					if (current_round == 1) table[i].league_fate = Promoted;
					return 0;
				default:
					//table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	return 0;
}

void __declspec(naked) arg_third_interior_set_table_fate()
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
		call arg_third_interior_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void arg_third_interior_playoff_finals(BYTE* _this) {
	char stage_num = 7;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	BYTE team_order[8] = { 0,2,4,6,7,5,3,1 };

	vector<cm3_clubs*> clubs;
	comp_stats* curr_stage = comp_data;
	for (char al = 3; al < 5; al++) {
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
	for (char i = 0; i < playoff_teams; i++) {
		*((DWORD*)(&pTeams[team_order[i]])) = (DWORD)clubs[i];
	}

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

void arg_third_interior_playoffs_prom(BYTE* _this) {
	char stage_num = 3;
	DWORD v1 = *(DWORD*)_this;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;
	BYTE playoff_teams = 8;

	comp_stats* curr_stage = comp_data;
	for (int g = 0; g < 2; g++) {
		vector<cm3_clubs*> clubs;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

		for (char al = (g * 2 - 1); al < (g * 2 + 1); al++)
		{
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
		for (size_t i = 0; i < playoff_teams; i++) {
			*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i];
		}

		BYTE prom_rel[4] = { 0, 4, 0, 0 };
		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), &prom_rel[0],
			year, stage_num, stage_name_id, 0x14, 1, 0, comp_data->f217, -1, 0, 2);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
	comp_data->current_stage = stage_num - 1;
}

void arg_third_interior_playoffs_rele(BYTE* _this) {
	char stage_num = 5;
	DWORD v1 = *(DWORD*)_this;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;
	BYTE playoff_teams = 10;

	comp_stats* curr_stage = comp_data;
	for (int g = 0; g < 2; g++) {
		vector<cm3_clubs*> clubs;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

		for (char al = (g * 2 - 1); al < (g * 2 + 1); al++)
		{
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			WORD total_teams = curr_stage->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.league_fate == BottomPlayoff) {
					clubs.push_back(tls.club);
				}
			}
		}
		for (size_t i = 0; i < playoff_teams; i++) {
			*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i];
		}

		BYTE prom_rel[4] = { 0, 0, 0, 2 };
		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), &prom_rel[0],
			year, stage_num, stage_name_id, 0x14, 1, 0, comp_data->f217, -1, 0, 2);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
	comp_data->current_stage = stage_num - 1;
}

void arg_third_interior_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 3) {
			arg_third_interior_playoffs_prom(_this);
			arg_third_interior_playoffs_rele(_this);
		}
		else if (current == 7) {
			arg_third_interior_playoff_finals(_this);
		}
	}
}

void __declspec(naked) arg_third_interior_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_third_interior_playoffs_c
		add esp, 0x4
		ret
	}
}

int arg_third_interior_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 3) {
		if (fate == TopPlayoff) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_champ_grp_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_champ_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == BottomPlayoff) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_rel_grp_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_rel_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	}
	else return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
}

void __declspec(naked) arg_third_interior_stage_news_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x28]
		push dword ptr[eax + 0x24]
		push dword ptr[eax + 0x20]
		push dword ptr[eax + 0x1c]
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call arg_third_interior_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void arg_third_interior_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)arg_third_interior_vtable->vtable_ptr;
	arg_third_interior_vtable->SetPointer(VTableInitFree, (DWORD)&arg_third_interior_free_c);
	arg_third_interior_vtable->SetPointer(VTableSubsRounds, (DWORD)&arg_third_interior_subs_c);
	arg_third_interior_vtable->SetPointer(VTableReputationSetup, (DWORD)&arg_third_interior_reputation_setup_c);
	arg_third_interior_vtable->SetPointer(VTableFixtures, (DWORD)&arg_third_interior_fixtures_c);
	arg_third_interior_vtable->SetPointer(VTableEoSUpdate, (DWORD)&arg_third_interior_update_c);
	arg_third_interior_vtable->SetPointer(VTableReputationCalc, (DWORD)&arg_third_interior_reputation_calc_c);
	arg_third_interior_vtable->SetPointer(VTableSetChampion, (DWORD)&arg_third_interior_set_champion_c);
	arg_third_interior_vtable->SetPointer(VTableTableFates, (DWORD)&arg_third_interior_set_table_fate);
	arg_third_interior_vtable->SetPointer(VTableStageNews, (DWORD)&arg_third_interior_stage_news_c);
	arg_third_interior_vtable->SetPointer(VTablePlayoffQual, (DWORD)&arg_third_interior_playoffs_create);
	arg_third_interior_vtable->SetPointer(VTablePostMatchUpdate, 0x685d30);
	arg_third_interior_vtable->SetPointer(VTableAwardTeamsSetup, 0x687a20);
	arg_third_interior_vtable->SetPointer(VTableUpdateLastDivision, (DWORD)&arg_third_interior_last_positions_c);
	data->year = year;
	data->rules = RulesArgentina;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 8;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	arg_third_interior_subs(_this);
	arg_third_interior_add_teams(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	for (BYTE i = 0; i < 3; i++) {
		arg_third_interior_setup_groups(_this, i);
	}
	arg_third_interior_reputation_setup(_this);
}

void setup_arg_third_interior() {
	char* rel_grp_text = "Relegation Group Stage";
	char* rel_grp_text_short = "Rel. Group Stage";
	WriteDWORD(0x4B665F + 1, (DWORD)&rel_grp_text[0]);
	WriteDWORD(0x4B915A + 1, (DWORD)&rel_grp_text_short[0]);
}