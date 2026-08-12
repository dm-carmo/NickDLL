#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include <Helpers\9cf_constants.h>

vtable* rus_second_a_vtable = new vtable((BYTE*)0x96E858, 0xB4);

int rus_second_a_last_positions(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	for (char al = 1; al < 3; al++) {
		comp_stats* curr_stage = (comp_stats*)(data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			cm3_clubs* club = table_teams[i].club;
			if (al == 1) club->ClubLastDivision = get_comp(RUS_SECOND_A_GOLD_9CF());
			else club->ClubLastDivision = get_comp(RUS_SECOND_A_SILVER_9CF());
			club->ClubLastPosition = (char)(i + 1);
		}
	}
	return 1;
}

void __declspec(naked) rus_second_a_last_positions_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_second_a_last_positions
		add esp, 0x4
		ret
	}
}

void rus_second_a_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(rus_second_a_vtable->vtable_ptr);
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
	sub_682300(_this);
}

void rus_second_a_free(BYTE* _this, BYTE a2) {
	rus_second_a_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) rus_second_a_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call rus_second_a_free
		add esp, 0x8
		ret 4
	}
}

void rus_second_a_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GamesWonTiebreaker;
	comp_data->tiebreaker_3 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_4 = GoalsForTiebreaker;
	comp_data->f82 = 2;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 6;
	comp_data->rele_playoff = 4;
	comp_data->relegations = 0;

	comp_data->promotes_to = RUS_FIRST_9CF();
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) rus_second_a_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_second_a_subs
		add esp, 0x4
		ret
	}
}

DWORD rus_second_a_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 10;
		if (year == 2026 && stage_idx == 0) numberOfLeagueTeams = 8;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = FirstStageGoldSilver + stage_idx + 1;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 20), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 27), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 3), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 10), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 17), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 24), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 31), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 21), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 28), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 5), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 19), year, Sunday);
		if (numberOfLeagueTeams > 8)
		{
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 26), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 2), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 16), year, Sunday);
		}

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx < 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = ((comp_stats*)_this);
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 10;
		if (year == 2026 && stage_idx == 2) numberOfLeagueTeams = 7;
		*num_rounds = (numberOfLeagueTeams - 1) * 2;
		*stage_name_id = SecondStageGoldSilver + stage_idx - 1;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 29), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 5), year, Sunday);
		if (numberOfLeagueTeams > 8) AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 8), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 19), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 3), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 10), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 24), year, Sunday);
		if (numberOfLeagueTeams > 8) AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 27), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 31), year, Sunday);
		if (numberOfLeagueTeams > 8)
		{
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 6, 7), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 6, 14), year, Sunday);
		}

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) rus_second_a_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call rus_second_a_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void rus_second_a_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	DWORD group_id = RUS_SECOND_A_SILVER_9CF();
	WORD num_teams = 10;
	if (year == 2026) num_teams = 7;
	DWORD* pTeams = (DWORD*)cm0102_malloc(num_teams * 4);

	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == data->competition_db->ClubCompID
			&& club->ClubReserveDivision && club->ClubReserveDivision->ClubCompID == group_id)
		{
			*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)club;
		}
	}
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 0, 4, 6, 0 };
	if (year == 2026) prom_rel[2] = 3;
	create_league_stage_data(pStage, _this, num_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void rus_second_a_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
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
				sub_4A2540((BYTE*)comp_data->f8, c, (char)(i + 1 + 10 * (al + 1)));
			}
		}
	}
}

void __declspec(naked) rus_second_a_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_second_a_reputation_setup
		add esp, 0x4
		ret
	}
}

char rus_second_a_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	sub_687970(_this, 0);
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
	rus_second_a_subs(_this);
	AddTeamsGroupLeague(_this, RUS_SECOND_A_GOLD_9CF());
	sub_6827D0(_this, 0);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		rus_second_a_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) rus_second_a_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_second_a_update
		add esp, 0x4
		ret
	}
}

void rus_second_a_block_promotion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	curr_stage = (comp_stats*)(data->stages[1]);
	WORD total_teams = curr_stage->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
		if (ret_club && !is_main_club) {
			if (ret_club->ClubDivision->ClubCompID != RUS_PREMIER_9CF())
				table_teams[i].league_fate = CantBePromoted;
		}
	}
}

void rus_second_a_playoffs_prom(BYTE* _this) {
	char stage_num = 1;
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);

	comp_stats* data = (comp_stats*)_this;
	BYTE playoff_teams = 10;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = data;
	vector<cm3_clubs*> clubs;

	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
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

	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 3, 0, 0, 0 };
	short f217 = 3;
	create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, stage_num, stage_name_id, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
	rus_second_a_block_promotion(_this);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
}

void rus_second_a_playoffs_rele(BYTE* _this) {
	char stage_num = 2;
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);

	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	BYTE playoff_teams = 10;
	if (year == 2026) playoff_teams = 7;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = data;
	vector<cm3_clubs*> clubs;

	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
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

	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 0, 0, 0, 2 };
	create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, stage_num, stage_name_id, 0x14, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;

	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = stage_num;
}

void rus_second_a_playoffs_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 1) {
			rus_second_a_playoffs_prom(_this);
			rus_second_a_playoffs_rele(_this);
		}
	}
}

void __declspec(naked) rus_second_a_playoffs_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_second_a_playoffs_create
		add esp, 0x4
		ret
	}
}

int rus_second_a_table_indicators(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 1) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SecondStageGoldSilver, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SecondStageGoldSilver + 1, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 1) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case Champions:
					staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					if (table[i].league_fate != CantBePromoted) table[i].league_fate = Champions;
					return 0;
				case Promoted:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x32);
					table[i].league_fate = Promoted;
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
	else if (stage == 2) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
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
	return 0;
}

void __declspec(naked) rus_second_a_set_table_fate()
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
		call rus_second_a_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

int rus_second_a_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[1];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) rus_second_a_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_second_a_set_champion
		add esp, 0x4
		ret 0
	}
}

void rus_second_a_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 1) {
		ret_current = 1 + 2 * (current - 1);
		ret_min = 1 + 2 * (min - 1);
		ret_max = 1 + 2 * (max - 1);
	}
	else if (stage == 1) {
		ret_current = current;
		ret_min = min;
		ret_max = max;
	}
	else if (stage == 2) {
		ret_current = current + 10;
		ret_min = min + 10;
		ret_max = max + 10;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) rus_second_a_reputation_calc_c()
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
		call rus_second_a_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

int rus_second_a_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 1) {
		if (fate == TopPlayoff) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_gold_grp_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_gold_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else if (fate == BottomPlayoff) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_silver_grp_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_silver_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
		}
		else return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	}
	else return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
}

void __declspec(naked) rus_second_a_stage_news_c()
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
		call rus_second_a_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void rus_second_a_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(rus_second_a_vtable->vtable_ptr);
	rus_second_a_vtable->SetPointer(VTableInitFree, (DWORD)&rus_second_a_free_c);
	rus_second_a_vtable->SetPointer(VTableEoSUpdate, (DWORD)&rus_second_a_update_c);
	rus_second_a_vtable->SetPointer(VTableFixtures, (DWORD)&rus_second_a_fixtures_c);
	rus_second_a_vtable->SetPointer(VTableSetChampion, (DWORD)&rus_second_a_set_champion_c);
	rus_second_a_vtable->SetPointer(VTableReputationSetup, (DWORD)&rus_second_a_reputation_setup_c);
	rus_second_a_vtable->SetPointer(VTableReputationCalc, (DWORD)&rus_second_a_reputation_calc_c);
	rus_second_a_vtable->SetPointer(VTableSubsRounds, (DWORD)&rus_second_a_subs_c);
	rus_second_a_vtable->SetPointer(VTableTableFates, (DWORD)&rus_second_a_set_table_fate);
	rus_second_a_vtable->SetPointer(VTablePlayoffQual, (DWORD)&rus_second_a_playoffs_create_c);
	rus_second_a_vtable->SetPointer(VTableUpdateLastDivision, (DWORD)&rus_second_a_last_positions_c);
	rus_second_a_vtable->SetPointer(VTable39, 0x404480);
	rus_second_a_vtable->SetPointer(VTable40, 0x404480);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) rus_second_a_vtable->SetPointer(VTable21, 0x4110b0);
	data->year = year;
	data->rules = RulesRussia;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 3;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	rus_second_a_subs(_this);
	AddTeamsGroupLeague(_this, RUS_SECOND_A_GOLD_9CF());
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		rus_second_a_setup_groups(_this, i);
	}
	rus_second_a_reputation_setup(_this);
}

void setup_rus_second_a()
{
	char* r1_gold_text = "First Stage Gold Group";
	char* r1_gold_text_short = "1st Stage Gold Grp";
	WriteDWORD(0x4B6368 + 1, (DWORD)&r1_gold_text[0]);
	WriteDWORD(0x4B8e55 + 1, (DWORD)&r1_gold_text_short[0]);
	char* r1_silver_text = "First Stage Silver Group";
	char* r1_silver_text_short = "1st Stage Silver Grp";
	WriteDWORD(0x4B6382 + 1, (DWORD)&r1_silver_text[0]);
	WriteDWORD(0x4B8e6f + 1, (DWORD)&r1_silver_text_short[0]);
	char* r2_gold_text = "Second Stage Gold Group";
	char* r2_gold_text_short = "2nd Stage Gold Grp";
	WriteDWORD(0x4B639c + 1, (DWORD)&r2_gold_text[0]);
	WriteDWORD(0x4B8e89 + 1, (DWORD)&r2_gold_text_short[0]);
	char* r2_silver_text = "Second Stage Silver Group";
	char* r2_silver_text_short = "2nd Stage Silver Grp";
	WriteDWORD(0x4B63b6 + 1, (DWORD)&r2_silver_text[0]);
	WriteDWORD(0x4B8ea3 + 1, (DWORD)&r2_silver_text_short[0]);
}