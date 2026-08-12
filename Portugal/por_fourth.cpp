#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include <Helpers\9cf_constants.h>

vtable* por_fourth_vtable = new vtable((BYTE*)0x96E858, 0xB4);

int por_fourth_set_champion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	DWORD comp_ids[4] = { POR_FOURTH_A_9CF(), POR_FOURTH_B_9CF(), POR_FOURTH_C_9CF(), POR_FOURTH_D_9CF() };
	for (char al = -1; al < 3; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		DWORD tmp[2] = { 0, (DWORD)get_comp(comp_ids[al + 1]) };
		sub_4AFCE0_add_history_entry((BYTE*)tmp, table_teams[0].club, table_teams[1].club, table_teams[2].club, 0);
	}

	BYTE* stage_data_for_history = (BYTE*)data->stages[5];
	if (data->year == 2026) stage_data_for_history = (BYTE*)data->stages[6];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) por_fourth_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_fourth_set_champion
		add esp, 0x4
		ret 0
	}
}

void por_fourth_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GamesWonTiebreaker;
	comp_data->tiebreaker_4 = GoalsForTiebreaker;
	comp_data->f82 = 2;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 2;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 5;
	if (comp_data->year == 2026)
	{
		comp_data->rele_playoff = 2;
		comp_data->relegations = 2;
	}

	comp_data->promotes_to = POR_THIRD_9CF();
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) por_fourth_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_fourth_subs
		add esp, 0x4
		ret
	}
}

void por_fourth_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(por_fourth_vtable->vtable_ptr);
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

void por_fourth_free(BYTE* _this, BYTE a2) {
	por_fourth_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) por_fourth_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call por_fourth_free
		add esp, 0x8
		ret 4
	}
}

void por_fourth_reputation_setup(BYTE* _this) {
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
				sub_4A2540((BYTE*)comp_data->f8, c, (char)(i * 4 + 1));
			}
		}
	}
}

void __declspec(naked) por_fourth_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_fourth_reputation_setup
		add esp, 0x4
		ret
	}
}

DWORD por_fourth_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = ((comp_stats*)_this);
	WORD year = data->year;
	if (stage_idx < 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		BYTE numberOfLeagueTeams = 14;
		if (year > 2026) numberOfLeagueTeams = 16;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (numberOfLeagueTeams > 14) AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 10), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 17), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 24), year, Sunday);
		if (numberOfLeagueTeams > 14) AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 28), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 5), year, Sunday);
		if (numberOfLeagueTeams > 14) AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 2), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Sunday);
		if (numberOfLeagueTeams > 14) AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 16), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 21), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 18), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 25), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx < 5) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD numberOfLeagueTeams = 4;
		*num_rounds = (numberOfLeagueTeams - 1) * 2;
		*stage_name_id = PromotionGroupAtoD + (stage_idx - 3);

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 3), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 10), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 23), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 31), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if ((year == 2026 && stage_idx == 6) || (year > 2026 && stage_idx == 5)) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 6, 1), year, Monday);

		Date portugal_day = Date(year + 1, 6, 10);
		AddPlayoffFixture(pMem, fixture_id, portugal_day, year, (Day)portugal_day.DayOfWeek(), Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 5, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (year == 2026 && stage_idx == 5) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = RelegationPlayoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 8, 4, 8, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) por_fourth_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call por_fourth_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void por_fourth_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD group_id = POR_FOURTH_B_9CF();
	if (idx == 1) group_id = POR_FOURTH_C_9CF();
	else if (idx == 2) group_id = POR_FOURTH_D_9CF();
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

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
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, data->n_teams, pTeams, data->n_rounds, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

int por_fourth_table_indicators(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, PromotionPlayoff, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RelegationPlayoff, 0x1E);
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
					if (table[i].league_fate != CantBePromoted) table[i].league_fate = Champions;
					return 0;
				case Promoted:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x32);
					table[i].league_fate = Promoted;
					return 0;
				case TopPlayoff:
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
	else if ((comp_data->year == 2026 && stage == 6) || (comp_data->year > 2026 && stage == 5)) {
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
					if (table[i].league_fate != CantBePromoted) table[i].league_fate = Champions;
					*a5 = 1;
					//return 0;
					break;
				case Promoted:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
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
					if (table[i].league_fate != CantBePromoted) table[i].league_fate = Champions;
					*a5 = 1;
					return 0;
				case Promoted:
					return 0;
				default:
					//table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	else if (comp_data->year == 2026 && stage == 5) {
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
			num_teams = curr_stage->n_teams;
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case BottomPlayoff:
					staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					table[i].league_fate = Relegated;
					*a5 = 1;
					return 0;
				case Relegated:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				case NoFate:
					table[i].league_fate = Eliminated;
					return 0;
				case TopPlayoff:
					table[i].league_fate = Eliminated;
					return 0;
				default:
					return 0;
				}
			}
		}
	}
	return 0;
}

void __declspec(naked) por_fourth_set_table_fate()
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
		call por_fourth_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void block_reserve_promotion_por_fourth(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	for (char al = -1; al < 3; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
			if (ret_club && !is_main_club) {
				if (ret_club->ClubDivision->ClubCompID != POR_FIRST_9CF() &&
					ret_club->ClubDivision->ClubCompID != POR_SECOND_9CF())
					table_teams[i].league_fate = CantBePromoted;
			}
		}
	}
}

char por_fourth_update(BYTE* _this) {
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
	if (data->year == 2026)
	{
		data->num_stages--;
		sub_9452CA_free(data->stages);
		data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	}
	data->year++;
	data->current_stage = -1;
	*((DWORD*)(_this + 0xA7)) = -1;
	por_fourth_subs(_this);
	AddTeamsGroupLeague(_this, POR_FOURTH_A_9CF());
	sub_6827D0(_this, 0);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 3; i++) {
		por_fourth_setup_groups(_this, i);
	}
	block_reserve_promotion_por_fourth(_this);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) por_fourth_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_fourth_update
		add esp, 0x4
		ret
	}
}

void por_fourth_playoffs_rele(BYTE* _this) {
	char stage_num = 5;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	BYTE team_order[8] = { 0,2,3,1,4,6,7,5 };

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 4; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		// 0-index so 15 = sixteenth place
		int start = curr_stage->n_teams - curr_stage->relegations - curr_stage->rele_playoff;
		for (int i = 0; i < 2; i++) {
			cm3_clubs* club = ((team_league_stats*)curr_stage->team_league_table)[start + i].club;
			clubs.push_back(club);
		}
	}

	for (size_t i = 0; i < clubs.size(); i++) {
		*((DWORD*)(&pTeams[team_order[i]])) = (DWORD)clubs[i];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

void por_fourth_playoffs_prom(BYTE* _this) {
	char stage_num = 3;
	DWORD v1 = *(DWORD*)_this;

	comp_stats* data = (comp_stats*)_this;
	DWORD* stages_arr = data->stages;
	BYTE playoff_teams = 4;

	comp_stats* curr_stage = data;
	char prom_rel[4] = { 2, 0, 0, 0 };

	for (char g = 0; g < 2; g++) {
		vector<cm3_clubs*> clubs;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

		char start_al = (-1 + 2 * g);
		for (char al = start_al; al < start_al + 2; al++) {
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
		create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
			data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
			year, stage_num, stage_name_id, 0x14, 1, 0, data->f217, -1, 0, 2);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;

		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
	data->current_stage = stage_num - 1;
}

void por_fourth_playoffs_champ(BYTE* _this) {
	char stage_num = 5;

	comp_stats* comp_data = (comp_stats*)_this;
	if (comp_data->year == 2026) stage_num++;
	BYTE playoff_teams = 2;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	for (char al = 3; al < 5; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		*((DWORD*)(&pTeams[al - 3])) = (DWORD)table_teams[0].club;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

void por_fourth_playoffs_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 3) {
			por_fourth_playoffs_prom(_this);
			if (comp_data->year == 2026) por_fourth_playoffs_rele(_this);
		}
		else if ((comp_data->year == 2026 && current == 6) || (comp_data->year > 2026 && current == 5)) {
			por_fourth_playoffs_champ(_this);
		}
	}
}

void __declspec(naked) por_fourth_playoffs_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_fourth_playoffs_create
		add esp, 0x4
		ret
	}
}

void por_fourth_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
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
	else if ((comp_data->year == 2026 && stage == 6) || (comp_data->year > 2026 && stage == 5)) {
		ret_current = current;
		ret_min = min;
		ret_max = max;
	}
	else if (comp_data->year == 2026 && stage == 5) {
		ret_current = 1 + 3 * (current + 9);
		ret_min = 1 + 3 * (min + 9);
		ret_max = 1 + 3 * (max + 9);
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) por_fourth_reputation_calc_c()
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
		call por_fourth_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void por_fourth_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(por_fourth_vtable->vtable_ptr);
	por_fourth_vtable->SetPointer(VTableInitFree, (DWORD)&por_fourth_free_c);
	por_fourth_vtable->SetPointer(VTableEoSUpdate, (DWORD)&por_fourth_update_c);
	por_fourth_vtable->SetPointer(VTableFixtures, (DWORD)&por_fourth_fixtures_c);
	por_fourth_vtable->SetPointer(VTableSetChampion, (DWORD)&por_fourth_set_champion_c);
	por_fourth_vtable->SetPointer(VTableReputationSetup, (DWORD)&por_fourth_reputation_setup_c);
	por_fourth_vtable->SetPointer(VTableReputationCalc, (DWORD)&por_fourth_reputation_calc_c);
	por_fourth_vtable->SetPointer(VTableSubsRounds, (DWORD)&por_fourth_subs_c);
	por_fourth_vtable->SetPointer(VTableTableFates, (DWORD)&por_fourth_set_table_fate);
	por_fourth_vtable->SetPointer(VTablePlayoffQual, (DWORD)&por_fourth_playoffs_create_c);
	por_fourth_vtable->SetPointer(VTable39, 0x404480);
	data->year = year;
	data->rules = RulesPortugal;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 7;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	por_fourth_subs(_this);
	AddTeamsGroupLeague(_this, POR_FOURTH_A_9CF());
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 3; i++) {
		por_fourth_setup_groups(_this, i);
	}
	block_reserve_promotion_por_fourth(_this);
	por_fourth_reputation_setup(_this);
}

void setup_por_fourth() {

}