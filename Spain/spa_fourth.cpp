#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include <Helpers\9cf_constants.h>

vtable* spa_fourth_vtable = new vtable((BYTE*)0x96FC84, 0xB4);

int spa_fourth_set_champion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	for (char al = -1; al < 4; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		sub_4AFCE0_add_history_entry(_this, table_teams[0].club, table_teams[1].club, table_teams[2].club, 0);
	}

	return 0;
}

void __declspec(naked) spa_fourth_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call spa_fourth_set_champion
		add esp, 0x4
		ret 0
	}
}

void spa_fourth_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(spa_fourth_vtable->vtable_ptr);
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

void spa_fourth_free(BYTE* _this, BYTE a2) {
	spa_fourth_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) spa_fourth_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call spa_fourth_free
		add esp, 0x8
		ret 4
	}
}

void spa_fourth_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->f82 = 2;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 4;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 5;

	comp_data->promotes_to = SPA_THIRD_9CF();
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) spa_fourth_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call spa_fourth_subs
		add esp, 0x4
		ret
	}
}

DWORD spa_fourth_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 4) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = 18;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = NumericGroupStage + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 21), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 28), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 5), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 19), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 2), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 16), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 23), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 30), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 21), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 4), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 11), year, Sunday);
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 29), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 5), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 19), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 3), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 4) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = PromotionPlayoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 20, 10, 20, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 18), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 24), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 10, 5, 0, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	else if (stage_idx == 5) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = RelegationPlayoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, None, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 4, 2, 4, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) spa_fourth_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call spa_fourth_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void spa_fourth_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD group_id = SPA_FOURTH_G2_9CF();
	if (idx == 1) group_id = SPA_FOURTH_G3_9CF();
	else if (idx == 2) group_id = SPA_FOURTH_G4_9CF();
	else if (idx == 3) group_id = SPA_FOURTH_G5_9CF();
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(data->n_teams * 4);

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
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, 18, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void spa_fourth_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 4; al++) {
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
				sub_4A2540((BYTE*)comp_data->f8, c, (char)(i * 5 + 1));
			}
		}
	}
}

void __declspec(naked) spa_fourth_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call spa_fourth_reputation_setup
		add esp, 0x4
		ret
	}
}

void block_reserve_promotion_spa_fourth(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	for (char al = -1; al < 4; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
			if (ret_club && !is_main_club) {
				if (ret_club->ClubDivision->ClubCompID != SPA_FIRST_9CF() &&
					ret_club->ClubDivision->ClubCompID != SPA_SECOND_9CF())
					table_teams[i].league_fate = CantBePromoted;
			}
		}
	}
}

char spa_fourth_update(BYTE* _this) {
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
	spa_fourth_subs(_this);
	AddTeamsGroupLeague(_this, SPA_FOURTH_G1_9CF());
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 4; i++) {
		spa_fourth_setup_groups(_this, i);
	}
	block_reserve_promotion_spa_fourth(_this);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) spa_fourth_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call spa_fourth_update
		add esp, 0x4
		ret
	}
}

void spa_fourth_playoffs_prom(BYTE* _this) {
	char stage_num = 4;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 20;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	cm3_clubs* tmp[20];

	vector<cm3_clubs*> clubs;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 4; al++) {
		WORD count = 0;
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == TopPlayoff) {
				tmp[1 + al + 5 * count] = tls.club;
				count++;
			}
		}
	}
	for (char i = 0; i < playoff_teams; i++) {
		clubs.push_back(tmp[i]);
	}

	shuffle(clubs.begin(), clubs.begin() + 5, rng);
	shuffle(clubs.begin() + 5, clubs.begin() + 10, rng);
	shuffle(clubs.begin() + 10, clubs.begin() + 15, rng);
	shuffle(clubs.begin() + 15, clubs.end(), rng);

	for (WORD j = 0; j < 10; j++) {
		*((DWORD*)(&pTeams[j * 2])) = (DWORD)clubs[j];
		*((DWORD*)(&pTeams[j * 2 + 1])) = (DWORD)clubs[playoff_teams - j - 1];
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

void spa_fourth_playoffs_rele(BYTE* _this) {
	char stage_num = 5;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	// get worst placeds
	vector<team_league_stats> sort_worst;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 4; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		WORD rel_pl_pos = total_teams - curr_stage->relegations - 1;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls = table_teams[rel_pl_pos];
		sort_worst.push_back(tls);
	}
	sort(sort_worst.begin(), sort_worst.end(), sortTLS);

	vector<cm3_clubs*> clubs;
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	for (int i = 1; i < 5; i++) {
		team_league_stats worst = sort_worst[i];
		clubs.push_back(worst.club);
		curr_stage = comp_data;
		for (char al = -1; al < 4; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			WORD total_teams = curr_stage->n_teams;
			WORD rel_pl_pos = total_teams - curr_stage->relegations - 1;
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			team_league_stats tls = table_teams[rel_pl_pos];
			if (tls.club == worst.club) {
				table_teams[rel_pl_pos].league_fate = BottomPlayoff;
				curr_stage->rele_playoff++;
				staff_history_qualified_86BDD0(staff_hist_ptr, tls.club, (DWORD)(comp_data->competition_db), None, RelegationPlayoff, 0x1E);
			}
		}
	}

	for (BYTE i = 0; i < playoff_teams; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

void spa_fourth_playoffs_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		if (current == 4) {
			comp_data->current_stage = current;
			spa_fourth_playoffs_prom(_this);
			spa_fourth_playoffs_rele(_this);
		}
	}
}

void __declspec(naked) spa_fourth_playoffs_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call spa_fourth_playoffs_create
		add esp, 0x4
		ret
	}
}

int spa_fourth_table_indicators(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 4) {
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
	else if (stage == 4) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;

		for (char al = -1; al < 4; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x32);
					table[i].league_fate = Promoted;
					*a5 = 1;
					return 0;
				case Promoted:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				default:
					staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	else if (stage == 5) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;

		for (char al = -1; al < 4; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
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
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	return 0;
}

void __declspec(naked) spa_fourth_set_table_fate()
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
		call spa_fourth_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void spa_fourth_awards(BYTE* _this, DWORD** team_list, WORD* total_teams) {
	*total_teams = 90;
	DWORD* pMem = (DWORD*)sub_944E46_malloc(4 * (*total_teams));
	*team_list = pMem;

	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* curr_stage = comp_data;
	WORD idx = 0;
	for (char al = -1; al < 4; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			cm3_clubs* club = ((team_league_stats*)curr_stage->team_league_table)[num].club;
			pMem[idx++] = (DWORD)club;
		}
	}
}

void __declspec(naked) spa_fourth_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call spa_fourth_awards
		add esp, 0xc
		ret 8
	}
}

void spa_fourth_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 4) {
		ret_current = 1 + 5 * (current - 1);
		ret_min = 1 + 5 * (min - 1);
		ret_max = 1 + 5 * (max - 1);
	}
	else if (stage == 4) {
		ret_current = 5 + current;
		ret_min = 5 + min;
		ret_max = 5 + max;
	}
	else if (stage == 5) {
		ret_current = (13 * 5) + current;
		ret_min = (13 * 5) + min;
		ret_max = (13 * 5) + max;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) spa_fourth_reputation_calc_c()
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
		call spa_fourth_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void spa_fourth_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(spa_fourth_vtable->vtable_ptr);
	spa_fourth_vtable->SetPointer(VTableInitFree, (DWORD)&spa_fourth_free_c);
	spa_fourth_vtable->SetPointer(VTableEoSUpdate, (DWORD)&spa_fourth_update_c);
	spa_fourth_vtable->SetPointer(VTableFixtures, (DWORD)&spa_fourth_fixtures_c);
	spa_fourth_vtable->SetPointer(VTableReputationSetup, (DWORD)&spa_fourth_reputation_setup_c);
	spa_fourth_vtable->SetPointer(VTableReputationCalc, (DWORD)&spa_fourth_reputation_calc_c);
	spa_fourth_vtable->SetPointer(VTableAwardTeamsSetup, (DWORD)&spa_fourth_awards_c);
	spa_fourth_vtable->SetPointer(VTableSubsRounds, (DWORD)&spa_fourth_subs_c);
	spa_fourth_vtable->SetPointer(VTableTableFates, (DWORD)&spa_fourth_set_table_fate);
	spa_fourth_vtable->SetPointer(VTablePlayoffQual, (DWORD)&spa_fourth_playoffs_create_c);
	spa_fourth_vtable->SetPointer(VTableSetChampion, (DWORD)&spa_fourth_set_champion_c);
	spa_fourth_vtable->SetPointer(VTableStageNews, 0x48c6d0);
	data->year = year;
	data->rules = 0x1a;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 6;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	spa_fourth_subs(_this);
	AddTeamsGroupLeague(_this, SPA_FOURTH_G1_9CF());
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 4; i++) {
		spa_fourth_setup_groups(_this, i);
	}
	block_reserve_promotion_spa_fourth(_this);
	spa_fourth_reputation_setup(_this);
}

void setup_spa_fourth()
{
}