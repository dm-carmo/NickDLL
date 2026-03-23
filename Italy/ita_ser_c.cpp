#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include <Helpers\9cf_constants.h>

vtable* ita_ser_c_vtable = new vtable((BYTE*)0x96E858, 0xB4);

int ita_ser_c_set_champion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		sub_4AFCE0_add_history_entry(_this, table_teams[0].club, table_teams[1].club, table_teams[2].club, 0);
	}

	return 0;
}

void __declspec(naked) ita_ser_c_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_c_set_champion
		add esp, 0x4
		ret 0
	}
}

void ita_ser_c_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(ita_ser_c_vtable->vtable_ptr);
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

void ita_ser_c_free(BYTE* _this, BYTE a2) {
	ita_ser_c_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) ita_ser_c_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ita_ser_c_free
		add esp, 0x8
		ret 4
	}
}

void ita_ser_c_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = NoTiebreaker;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 9;
	comp_data->rele_playoff = 4;
	comp_data->relegations = 1;

	comp_data->promotes_to = ITA_SERIE_B_9CF();
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->f217 = 0x2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) ita_ser_c_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_c_subs
		add esp, 0x4
		ret
	}
}

DWORD ita_ser_c_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 20;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 24), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 31), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 21), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 25), year, Thursday, Evening);
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 11), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 18), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 4), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 29), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 19), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 26), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = PromotionPlayoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 27), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 5, 18, 9, 18, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 7), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 5, 12, 6, 3, 18, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 8), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 10, 5, 4, 21, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 15), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 18), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 8, 4, 3, 25, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 19), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 25), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 4, 2, 0, 0, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 26), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 6, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 2, 1, 0, 0, 0, 2, 4);

		return (DWORD)pMem;
	}
	else if (stage_idx == 3) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = RelegationPlayoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 27), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 12, 6, 12, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) ita_ser_c_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ita_ser_c_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void ita_ser_c_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD group_id = ITA_SERIE_C_B_9CF();
	if (idx > 0) group_id = ITA_SERIE_C_C_9CF();
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
	create_league_stage_data(pStage, _this, 20, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void ita_ser_c_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 2; al++) {
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
				sub_4A2540((BYTE*)comp_data->f8, c, (char)(i * 3 + 1));
			}
		}
	}
}

void __declspec(naked) ita_ser_c_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_c_reputation_setup
		add esp, 0x4
		ret
	}
}

cm3_clubs* get_ita_c_cup_loser(comp_stats* comp_data)
{
	cm3_club_comps* comp = get_comp(ITA_SERIE_C_CUP_9CF());
	cm3_clubs* last_runner_up = get_last_comp_runner_up(comp);
	if (!last_runner_up || !last_runner_up->ClubNation || !last_runner_up->ClubDivision || last_runner_up->ClubDivision->ClubCompID != comp_data->competition_db->ClubCompID) {
		return 0;
	}
	else {
		return last_runner_up;
	}
}

cm3_clubs* get_ita_c_cup_winner(comp_stats* comp_data)
{
	cm3_club_comps* comp = get_comp(ITA_SERIE_C_CUP_9CF());
	cm3_clubs* last_winner = get_last_comp_winner(comp);
	if (!last_winner || !last_winner->ClubNation || !last_winner->ClubDivision || last_winner->ClubDivision->ClubCompID != comp_data->competition_db->ClubCompID) {
		return 0;
	}
	else {
		return last_winner;
	}
}

pair<char, WORD> get_club_group_and_pos(comp_stats* comp_data, cm3_clubs* club) {
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			cm3_clubs* lge_club = ((team_league_stats*)curr_stage->team_league_table)[num].club;
			if (club == lge_club) {
				//dprintf("Club: %s, finished in position: %d, in group: %d\n", club->ClubNameShort, num + 1, al + 2);
				return make_pair(al, num);
			}
		}
	}
	return make_pair(-2, 255);
}

void set_playoff_place(BYTE* _this, cm3_clubs* club) {
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (club == table_pos.club && table_pos.league_fate != TopPlayoff) {
				((team_league_stats*)curr_stage->team_league_table)[num].league_fate = TopPlayoff;
				staff_history_qualified_86BDD0((BYTE*)*staff_history, club, (DWORD)(comp_data->competition_db), PromotionPlayoff, None, 0x1E);
				return;
			}
		}
	}
}

void ita_c_playoffs_prom(BYTE* _this) {
	char stage_num = 2;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 28;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	char fallback_group = -1;
	bool use_fallback = false;

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs_rnd1;
	vector<cm3_clubs*> clubs_rnd2;
	vector<cm3_clubs*> clubs_rnd3;
	vector<cm3_clubs*> clubs_rnd4;
	// clubs for round 4 (2nd places)
	curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		// 0-index so 1 = second place
		cm3_clubs* r4_club = ((team_league_stats*)curr_stage->team_league_table)[1].club;
		clubs_rnd4.push_back(r4_club);
		//dprintf("Club in round 4: 2nd place %s\n", r4_club->ClubNameShort);
	}
	// clubs for round 3 (3rd places + cup team)
	curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		// 0-index so 2 = third place
		cm3_clubs* r3_club = ((team_league_stats*)curr_stage->team_league_table)[2].club;
		clubs_rnd3.push_back(r3_club);
		//dprintf("Club in round 3: 3rd place %s\n", r3_club->ClubNameShort);
	}
	cm3_clubs* c_winner = get_ita_c_cup_winner(comp_data);
	if (c_winner) {
		pair<char, WORD> winner_grp_pos = get_club_group_and_pos(comp_data, c_winner);
		// if they finished 1st (promoted), 2nd or 3rd (already in later playoffs)
		// or if they are in relegation area
		if (winner_grp_pos.second < 3 || winner_grp_pos.second >= 15) {
			fallback_group = winner_grp_pos.first;
			cm3_clubs* c_loser = get_ita_c_cup_loser(comp_data);
			if (c_loser) {
				pair<char, WORD> loser_grp_pos = get_club_group_and_pos(comp_data, c_loser);
				if (loser_grp_pos.second < 3 || loser_grp_pos.second >= 15) {
					// do not add club here
					use_fallback = true;
				}
				else {
					clubs_rnd3.push_back(c_loser);
					set_playoff_place(_this, c_loser);
					//dprintf("Club in round 3: cup loser %s\n", c_loser->ClubNameShort);
				}
			}
			else use_fallback = true;
		}
		else {
			clubs_rnd3.push_back(c_winner);
			set_playoff_place(_this, c_winner);
			//dprintf("Club in round 3: cup winner %s\n", c_winner->ClubNameShort);
		}
	}
	else {
		cm3_clubs* c_loser = get_ita_c_cup_loser(comp_data);
		if (c_loser) {
			pair<char, WORD> loser_grp_pos = get_club_group_and_pos(comp_data, c_loser);
			if (loser_grp_pos.second < 3 || loser_grp_pos.second >= 15) {
				// do not add club here
				use_fallback = true;
			}
			else {
				clubs_rnd3.push_back(c_loser);
				set_playoff_place(_this, c_loser);
				//dprintf("Club in round 3: cup loser %s\n", c_loser->ClubNameShort);
			}
		}
		else use_fallback = true;
	}
	if (use_fallback) {
		curr_stage = comp_data;
		if (fallback_group >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[fallback_group]);
		}
		// fallback 4th place from same group as winner
		cm3_clubs* fallback_club = ((team_league_stats*)curr_stage->team_league_table)[3].club;
		clubs_rnd3.push_back(fallback_club);
		//dprintf("Club in round 3: fallback 4th place %s\n", fallback_club->ClubNameShort);
	}
	// clubs for round 2 (4th places)
	curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		// 0-index so 3 = fourth place
		int start_r2 = 3;
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		bool found_r2 = false;
		while (!found_r2) {
			cm3_clubs* r2_club = ((team_league_stats*)curr_stage->team_league_table)[start_r2++].club;
			if (vector_contains_club(clubs_rnd4, r2_club) || vector_contains_club(clubs_rnd3, r2_club))
				continue;
			else {
				clubs_rnd2.push_back(r2_club);
				found_r2 = true;
				//dprintf("Club in round 2: %dth place %s\n", start_r2, r2_club->ClubNameShort);
			}
		}
	}
	// clubs for round 1 (5th to 10th places)
	curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		// 0-index so 4 = fifth place
		int start_r1 = 4;
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD found_count = 0;
		while (found_count < 6) {
			cm3_clubs* r1_club = ((team_league_stats*)curr_stage->team_league_table)[start_r1++].club;
			if (vector_contains_club(clubs_rnd4, r1_club) || vector_contains_club(clubs_rnd3, r1_club) || vector_contains_club(clubs_rnd2, r1_club))
				continue;
			else {
				clubs_rnd1.push_back(r1_club);
				if (start_r1 > 10) set_playoff_place(_this, r1_club);
				//dprintf("Club in round 1: %dth place %s\n", start_r1, r1_club->ClubNameShort);
				found_count++;
			}
		}
	}
	// add them all now
	BYTE team_order[18] = { 0,2,4,5,3,1,6,8,10,11,9,7,12,14,16,17,15,13 };
	for (size_t i = 0; i < clubs_rnd1.size(); i++) {
		*((DWORD*)(&pTeams[team_order[i]])) = (DWORD)clubs_rnd1[i];
	}
	size_t j = clubs_rnd1.size();
	for (size_t i = 0; i < clubs_rnd2.size(); i++) {
		*((DWORD*)(&pTeams[j++])) = (DWORD)clubs_rnd2[i];
	}
	for (size_t i = 0; i < clubs_rnd3.size(); i++) {
		*((DWORD*)(&pTeams[j++])) = (DWORD)clubs_rnd3[i];
	}
	for (size_t i = 0; i < clubs_rnd4.size(); i++) {
		*((DWORD*)(&pTeams[j++])) = (DWORD)clubs_rnd4[i];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	BYTE seeds[28] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,2,3,3,3 };
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, seeds);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void ita_c_playoffs_rele(BYTE* _this) {
	char stage_num = 3;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 12;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	BYTE team_order[12] = { 0,3,2,1,4,7,6,5,8,11,10,9 };

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		// 0-index so 15 = sixteenth place
		int start = curr_stage->n_teams - curr_stage->relegations - curr_stage->rele_playoff;
		for (int i = 0; i < 4; i++) {
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
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

void ita_c_playoffs_create_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 2) {
			ita_c_playoffs_prom(_this);
			ita_c_playoffs_rele(_this);
		}
	}
}

void __declspec(naked) ita_c_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_c_playoffs_create_c
		add esp, 0x4
		ret
	}
}

int ita_ser_c_table_indicators(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 2) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 2; al++) {
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
	else if (stage == 3) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 2; al++) {
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
	else {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), PromotionPlayoff, None, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), RelegationPlayoff, None, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) ita_ser_c_set_table_fate()
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
		call ita_ser_c_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

char ita_ser_c_update(BYTE* _this) {
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
	ita_ser_c_subs(_this);
	AddTeamsGroupLeague(_this, ITA_SERIE_C_A_9CF());
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 2; i++) {
		ita_ser_c_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) ita_ser_c_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_c_update
		add esp, 0x4
		ret
	}
}

void ita_ser_c_points_deductions(BYTE* _this, WORD current_year)
{
	if (current_year > 2025) return;
	map<cm3_clubs*, short> point_deduction_map = {
		{find_club("US Triestina"), -23},
		{find_club("Campobasso FC"), -2},
		{find_club("Ternana Calcio"), -5},
		{find_club("FC Trapani 1905"), -15}
	};
	comp_stats* data = (comp_stats*)_this;


	comp_stats* curr_stage = data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < curr_stage->n_teams; i++) {
			team_league_stats* tls = &table_teams[i];
			auto find_club = point_deduction_map.find(tls->club);
			if (find_club != point_deduction_map.end()) {
				tls->points = find_club->second;
				tls->points_away = find_club->second;
			}
		}
	}
}

void ita_7D2B80(BYTE* _this, DWORD** team_list, WORD* total_teams) {
	*total_teams = 60;
	DWORD* pMem = (DWORD*)sub_944E46_malloc(4 * (*total_teams));
	*team_list = pMem;

	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* curr_stage = comp_data;
	WORD idx = 0;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			cm3_clubs* club = ((team_league_stats*)curr_stage->team_league_table)[num].club;
			pMem[idx++] = (DWORD)club;
		}
	}
}

void __declspec(naked) ita_7D2B80_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ita_7D2B80
		add esp, 0xc
		ret 8
	}
}

void ita_ser_c_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 2) {
		ret_current = 1 + 5 * (current - 1);
		ret_min = 1 + 5 * (min - 1);
		ret_max = 1 + 5 * (max - 1);
	}
	else if (stage == 2) {
		ret_current = 1 + 5 * (current);
		ret_min = 1 + 5 * (min);
		ret_max = 1 + 5 * (max);
	}
	else if (stage == 3) {
		ret_current = 1 + 5 * (current + 14);
		ret_min = 1 + 5 * (min + 14);
		ret_max = 1 + 5 * (max + 14);
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) ita_ser_c_reputation_calc_c()
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
		call ita_ser_c_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void ita_ser_c_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(ita_ser_c_vtable->vtable_ptr);
	ita_ser_c_vtable->SetPointer(VTableInitFree, (DWORD)&ita_ser_c_free_c);
	ita_ser_c_vtable->SetPointer(VTableEoSUpdate, (DWORD)&ita_ser_c_update_c);
	ita_ser_c_vtable->SetPointer(VTablePlayoffQual, (DWORD)&ita_c_playoffs_create);
	ita_ser_c_vtable->SetPointer(VTableFixtures, (DWORD)&ita_ser_c_fixtures_c);
	ita_ser_c_vtable->SetPointer(VTableTableFates, (DWORD)&ita_ser_c_set_table_fate);
	ita_ser_c_vtable->SetPointer(VTableReputationSetup, (DWORD)&ita_ser_c_reputation_setup_c);
	ita_ser_c_vtable->SetPointer(VTableReputationCalc, (DWORD)&ita_ser_c_reputation_calc_c);
	ita_ser_c_vtable->SetPointer(VTableAwardTeamsSetup, (DWORD)&ita_7D2B80_c);
	ita_ser_c_vtable->SetPointer(VTableSubsRounds, (DWORD)&ita_ser_c_subs_c);
	ita_ser_c_vtable->SetPointer(VTableSetChampion, (DWORD)&ita_ser_c_set_champion_c);
	data->year = year;
	data->rules = RulesItalyLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_PURPLE_2_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_GOLD_9CF());
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 4;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	ita_ser_c_subs(_this);
	AddTeamsGroupLeague(_this, ITA_SERIE_C_A_9CF());
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 2; i++) {
		ita_ser_c_setup_groups(_this, i);
	}
	ita_ser_c_reputation_setup(_this);
	ita_ser_c_points_deductions(_this, year);
}

void setup_ita_ser_c()
{
}
