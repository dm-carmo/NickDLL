#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

vtable* usa_champ_vtable = new vtable((BYTE*)0x970844, 0xB4);

void usa_champ_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(usa_champ_vtable->vtable_ptr);
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

void usa_champ_free(BYTE* _this, BYTE a2) {
	usa_champ_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) usa_champ_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call usa_champ_free
		add esp, 0x8
		ret 4
	}
}

void usa_champ_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
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
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) usa_champ_reputation_calc_c()
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
		call usa_champ_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void usa_champ_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		DWORD* all_teams = comp_data->teams2;
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < 25; i++) clubs.push_back((cm3_clubs*)all_teams[i]);
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
		for (int i = 0; i < 4; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[16 + 2 * i], 17 + 2 * i);
			sub_4A2540((BYTE*)comp_data->f8, clubs[17 + 2 * i], 17 + 2 * i);
		}
		sub_4A2540((BYTE*)comp_data->f8, clubs[24], 25);
	}
}

void __declspec(naked) usa_champ_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call usa_champ_reputation_setup
		add esp, 0x4
		ret
	}
}

int usa_champ_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[1];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) usa_champ_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call usa_champ_set_champion
		add esp, 0x4
		ret 0
	}
}

int usa_champ_add_teams(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* all_teams = comp_data->teams2;
	if (all_teams) sub_9452CA_free(all_teams);

	vector<cm3_clubs*> champ_clubs = find_clubs_of_comp(comp_data->competition_db->ClubCompID);
	comp_data->teams2 = (DWORD*)cm0102_malloc(champ_clubs.size() * 4);
	sort(champ_clubs.begin(), champ_clubs.end(), compareClubLongitude);
	for (DWORD i = 0; i < champ_clubs.size(); i++)
	{
		*((DWORD*)(&comp_data->teams2[i])) = (DWORD)champ_clubs[i];
	}

	comp_data->n_teams = 13; // number of teams per group in this case
	comp_data->team_league_table = (DWORD*)cm0102_malloc(13 * league_team_list_sz);
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < comp_data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)(comp_data->teams2[i]);
		add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

void usa_champ_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	WORD n_teams = 12;
	DWORD* pTeams = (DWORD*)cm0102_malloc(n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)all_teams[data->n_teams * (idx + 1) + i];
		*((DWORD*)(&pTeams[i])) = (DWORD)club;
	}
	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, n_teams, pTeams, data->n_rounds, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void usa_champ_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = GamesWonTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 8;
	comp_data->rele_playoff = 0;
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

void __declspec(naked) usa_champ_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call usa_champ_subs
		add esp, 0x4
		ret
	}
}

DWORD usa_champ_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 12 + abs(stage_idx);
		*num_rounds = (numberOfLeagueTeams - 1 + numberOfLeagueTeams % 2) * data->n_rounds;
		*stage_name_id = EasternConference + (stage_idx + 1);

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 9), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 23), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 30), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 6), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 13), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 20), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 4), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 18), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 25), year, Sunday);
		if(numberOfLeagueTeams > 12) AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 22), year, Sunday);
		if (numberOfLeagueTeams > 12) AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 29), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 6), year, Sunday);
		if (numberOfLeagueTeams > 12) AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 20), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 27), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 3), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 10), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 24), year, Sunday);
		if (numberOfLeagueTeams > 12) AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 31), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 21), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 28), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 5), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 19), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 26), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 27), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 5, 16, 8, 16, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 3), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 5, 8, 4, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 10), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 5, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 17), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 23), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 5, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) usa_champ_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call usa_champ_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char usa_champ_update(BYTE* _this) {
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
	usa_champ_subs(_this);
	usa_champ_add_teams(_this);
	sub_6827D0(_this, 0);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		usa_champ_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) usa_champ_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call usa_champ_update
		add esp, 0x4
		ret
	}
}

int usa_champ_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, FirstRound, 0x1E);
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
	else if (stage == 1) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
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
					return 0;
				case BottomPlayoff:
					staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
					table[i].league_fate = Eliminated;
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
	return 0;
}

void __declspec(naked) usa_champ_set_table_fate()
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
		call usa_champ_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void usa_champ_playoff_finals(BYTE* _this) {
	char stage_num = 1;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	vector<cm3_clubs*> clubs;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
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
	BYTE team_order[16] = { 0,6,4,2,3,5,7,1,8,14,12,10,11,13,15,9 };

	for (char i = 0; i < playoff_teams; i++) {
		*((DWORD*)(&pTeams[team_order[i]])) = (DWORD)clubs[i];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void usa_champ_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 1) {
			usa_champ_playoff_finals(_this);
		}
	}
}

void __declspec(naked) usa_champ_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call usa_champ_playoffs_c
		add esp, 0x4
		ret
	}
}

void usa_d2_awards_teams(BYTE* _this, DWORD** team_list, WORD* total_teams) {
	*total_teams = 25;
	DWORD* pMem = (DWORD*)cm0102_malloc(4 * (*total_teams));
	*team_list = pMem;

	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* curr_stage = comp_data;
	WORD idx = 0;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			cm3_clubs* club = ((team_league_stats*)curr_stage->team_league_table)[num].club;
			pMem[idx++] = (DWORD)club;
		}
	}
}

void __declspec(naked) usa_d2_awards_teams_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call usa_d2_awards_teams
		add esp, 0xc
		ret 8
	}
}

void usa_champ_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(usa_champ_vtable->vtable_ptr);
	usa_champ_vtable->SetPointer(VTableInitFree, (DWORD)&usa_champ_free_c);
	usa_champ_vtable->SetPointer(VTableSubsRounds, (DWORD)&usa_champ_subs_c);
	usa_champ_vtable->SetPointer(VTableReputationSetup, (DWORD)&usa_champ_reputation_setup_c);
	usa_champ_vtable->SetPointer(VTableFixtures, (DWORD)&usa_champ_fixtures_c);
	usa_champ_vtable->SetPointer(VTableEoSUpdate, (DWORD)&usa_champ_update_c);
	usa_champ_vtable->SetPointer(VTableReputationCalc, (DWORD)&usa_champ_reputation_calc_c);
	usa_champ_vtable->SetPointer(VTableSetChampion, (DWORD)&usa_champ_set_champion_c);
	usa_champ_vtable->SetPointer(VTableTableFates, (DWORD)&usa_champ_set_table_fate);
	usa_champ_vtable->SetPointer(VTableStageNews, 0x48c6d0);
	usa_champ_vtable->SetPointer(VTablePlayoffQual, (DWORD)&usa_champ_playoffs_create);
	usa_champ_vtable->SetPointer(VTablePostMatchUpdate, 0x685d30);
	usa_champ_vtable->SetPointer(VTableAwardTeamsSetup, (DWORD)&usa_d2_awards_teams_c);
	data->year = year;
	data->rules = RulesUSA;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 2;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	usa_champ_subs(_this);
	usa_champ_add_teams(_this);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	for (BYTE i = 0; i < 1; i++) {
		usa_champ_setup_groups(_this, i);
	}
	usa_champ_reputation_setup(_this);
}

void setup_usa_champ() {
}