#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include "Helpers\9cf_constants.h"

vtable* ita_ser_d_vtable = new vtable((BYTE*)0x96E858, 0xB4);

int ita_ser_d_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[12];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) ita_ser_d_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_d_set_champion
		add esp, 0x4
		ret 0
	}
}

void ita_ser_d_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(ita_ser_d_vtable->vtable_ptr);
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

void ita_ser_d_free(BYTE* _this, BYTE a2) {
	ita_ser_d_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) ita_ser_d_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ita_ser_d_free
		add esp, 0x8
		ret 4
	}
}

void ita_ser_d_subs(BYTE* _this)
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
	comp_data->tiebreaker_4 = GamesWonTiebreaker;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 4;
	comp_data->relegations = 2;

	comp_data->promotes_to = ITA_SERIE_C_9CF();
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->f217 = 0x2;
	comp_data->max_bench = 9;
	comp_data->max_subs = 5;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) ita_ser_d_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_d_subs
		add esp, 0x4
		ret
	}
}

DWORD ita_ser_d_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 8) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 18;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 17), year, Wednesday, Evening);
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 7), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 11), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 18), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 25), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 26), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 19), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 3), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 8) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = RelegationPlayoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Final, 1, FixedTeamOrderInCup | ExtraTime | HigherSeedingTiebreak, NoTiebreak, 5, 36, 18, 36, 0, 0, 1, 8);

		return (DWORD)pMem;
	}
	else if (stage_idx < 12) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = SecondRoundAlphabeticGroup + stage_idx - 9;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 14), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Saturday);

		if (fixture_id != 3) {
			string msg = "Wrong number of fixtures: " + to_string(fixture_id);
			create_message_box("Error", msg.c_str(), true);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 12) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 18), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 25), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoAwayGoals, Penalties | NoAwayGoals, 6, 4, 2, 4, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 6, 1), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 6, 8), year, Sunday, Afternoon, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) ita_ser_d_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ita_ser_d_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void ita_ser_d_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	vector<DWORD> d4_groups = {
		ITA_SERIE_D_A_9CF(),
		ITA_SERIE_D_B_9CF(),
		ITA_SERIE_D_C_9CF(),
		ITA_SERIE_D_D_9CF(),
		ITA_SERIE_D_E_9CF(),
		ITA_SERIE_D_F_9CF(),
		ITA_SERIE_D_G_9CF(),
		ITA_SERIE_D_H_9CF(),
		ITA_SERIE_D_I_9CF()
	};
	DWORD group_id = d4_groups[idx + 1];
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

void ita_ser_d_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 8; al++) {
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
				sub_4A2540((BYTE*)comp_data->f8, c, (char)(i * 9 + 1));
			}
		}
	}
}

void __declspec(naked) ita_ser_d_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_d_reputation_setup
		add esp, 0x4
		ret
	}
}

void ita_d_playoffs_rele(BYTE* _this) {
	char stage_num = 8;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 36;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	BYTE team_order[36] = { 0 };
	for (int i = 0; i < 9; i++) {
		team_order[i * 4] = 4 * i;
		team_order[i * 4 + 1] = 4 * i + 2;
		team_order[i * 4 + 2] = 4 * i + 3;
		team_order[i * 4 + 3] = 4 * i + 1;
	}
	BYTE seeds[36] = { 0 };

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 8; al++) {
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
		seeds[team_order[i]] = (BYTE)i;
		*((DWORD*)(&pTeams[team_order[i]])) = (DWORD)clubs[i];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, &seeds[0]);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
}

void ita_d_playoffs_champ(BYTE* _this) {
	char stage_num = 9;
	DWORD v1 = *(DWORD*)_this;

	comp_stats* data = (comp_stats*)_this;
	DWORD* stages_arr = data->stages;
	BYTE playoff_teams = 3;

	char prom_rel[4] = { 0, 1, 0, 0 };

	for (char g = 0; g < 3; g++) {
		vector<cm3_clubs*> clubs;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

		comp_stats* curr_stage = data;
		char start_al = (-1 + g);
		for (char al = start_al; al < 8; al += 3) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(data->stages[al]);
			}
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			clubs.push_back(table_teams[0].club);
		}

		for (size_t i = 0; i < playoff_teams; i++) {
			*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i];
		}

		WORD year = data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, playoff_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
			data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
			year, stage_num, stage_name_id, 0x14, 1, 0, data->f217, -1, 0, 2);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;

		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
	data->current_stage = stage_num - 1;
}

void ita_d_playoffs_final(BYTE* _this) {
	char stage_num = 12;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	vector<cm3_clubs*> clubs;
	vector<team_league_stats> sort_seconds;

	for (char al = 9; al < 12; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		sort_seconds.push_back(table_teams[1]);
	}
	sort(sort_seconds.begin(), sort_seconds.end(), sortTLS);
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	team_league_stats best_second = sort_seconds[0];
	clubs.push_back(best_second.club);
	for (char al = 9; al < 12; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls = table_teams[curr_stage->prom_playoff];
		if (tls.club == best_second.club) {
			table_teams[curr_stage->prom_playoff].league_fate = TopPlayoff;
			curr_stage->prom_playoff++;
			staff_history_qualified_86BDD0(staff_hist_ptr, tls.club, (DWORD)(comp_data->competition_db), None, SemiFinal, 0x1E);
		}
	}

	for (size_t i = 0; i < playoff_teams; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i];
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
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
}

void ita_d_playoffs_create_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 8) {
			ita_d_playoffs_rele(_this);
			ita_d_playoffs_champ(_this);
		}
		else if (current == 12) {
			ita_d_playoffs_final(_this);
		}
	}
}

void __declspec(naked) ita_d_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_d_playoffs_create_c
		add esp, 0x4
		ret
	}
}

int ita_ser_d_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 8) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 8; al++) {
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
	else if (stage < 12) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, SemiFinal, 0x1E);
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 12) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 8; al++) {
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
		for (char al = 9; al < 12; al++) {
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
					return 0;
				default:
					table[i].league_fate = Eliminated;
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), SecondRound, None, 0x1E);
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

void __declspec(naked) ita_ser_d_table_fates_c()
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
		call ita_ser_d_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

char ita_ser_d_update(BYTE* _this) {
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
	ita_ser_d_subs(_this);
	AddTeamsGroupLeague(_this, ITA_SERIE_D_A_9CF());
	sub_6827D0(_this, 0);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 8; i++) {
		ita_ser_d_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) ita_ser_d_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_d_update
		add esp, 0x4
		ret
	}
}

void ita_ser_d_awards(BYTE* _this, DWORD** team_list, WORD* total_teams) {
	*total_teams = 162;
	DWORD* pMem = (DWORD*)cm0102_malloc(4 * (*total_teams));
	*team_list = pMem;

	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* curr_stage = comp_data;
	WORD idx = 0;
	for (char al = -1; al < 8; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			cm3_clubs* club = ((team_league_stats*)curr_stage->team_league_table)[num].club;
			pMem[idx++] = (DWORD)club;
		}
	}
}

void __declspec(naked) ita_ser_d_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ita_ser_d_awards
		add esp, 0xc
		ret 8
	}
}

void ita_ser_d_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 8) {
		ret_current = 1 + 9 * (current - 1);
		ret_min = 1 + 9 * (min - 1);
		ret_max = 1 + 9 * (max - 1);
	}
	else if (stage == 8) {
		ret_current = 1 + 9 * (current + 13);
		ret_min = 1 + 9 * (min + 13);
		ret_max = 1 + 9 * (max + 13);
	}
	else if (stage < 12) {
		ret_current = 1 + 3 * (current - 1);
		ret_min = 1 + 3 * (min - 1);
		ret_max = 1 + 3 * (max - 1);
	}
	else if (stage == 12) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) ita_ser_d_reputation_calc_c()
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
		call ita_ser_d_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

int ita_ser_d_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 8) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else if (stage_id == 8) {
		if (fate == BottomPlayoff && !show_body_text) {
			sub_66F4E0(0xDE1F64, relegated_msg, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			return 1;
		}
		return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 12) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
}

void __declspec(naked) ita_ser_d_stage_news_c()
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
		call ita_ser_d_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void ita_ser_d_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(ita_ser_d_vtable->vtable_ptr);
	ita_ser_d_vtable->SetPointer(VTableInitFree, (DWORD)&ita_ser_d_free_c);
	ita_ser_d_vtable->SetPointer(VTableEoSUpdate, (DWORD)&ita_ser_d_update_c);
	ita_ser_d_vtable->SetPointer(VTablePlayoffQual, (DWORD)&ita_d_playoffs_create);
	ita_ser_d_vtable->SetPointer(VTableFixtures, (DWORD)&ita_ser_d_fixtures_c);
	ita_ser_d_vtable->SetPointer(VTableTableFates, (DWORD)&ita_ser_d_table_fates_c);
	ita_ser_d_vtable->SetPointer(VTableReputationSetup, (DWORD)&ita_ser_d_reputation_setup_c);
	ita_ser_d_vtable->SetPointer(VTableReputationCalc, (DWORD)&ita_ser_d_reputation_calc_c);
	ita_ser_d_vtable->SetPointer(VTableAwardTeamsSetup, (DWORD)&ita_ser_d_awards_c);
	ita_ser_d_vtable->SetPointer(VTableSubsRounds, (DWORD)&ita_ser_d_subs_c);
	ita_ser_d_vtable->SetPointer(VTableSetChampion, (DWORD)&ita_ser_d_set_champion_c);
	ita_ser_d_vtable->SetPointer(VTableStageNews, (DWORD)&ita_ser_d_stage_news_c);
	ita_ser_d_vtable->SetPointer(VTableLoadCompInfo, 0x48CEB0);
	ita_ser_d_vtable->SetPointer(VTableSaveCompInfo, 0x48CEA0);
	data->year = year;
	data->rules = RulesItalyLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 13;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	ita_ser_d_subs(_this);
	AddTeamsGroupLeague(_this, ITA_SERIE_D_A_9CF());
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 8; i++) {
		ita_ser_d_setup_groups(_this, i);
	}
	ita_ser_d_reputation_setup(_this);
}

void setup_ita_ser_d()
{
}
