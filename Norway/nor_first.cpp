#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* nor_first_vtable = (DWORD*)0x96DE20;

char* nor_first_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* playoff_bytes = (BYTE*)comp_data->stages[0];
	comp_stats* playoff_data = (comp_stats*)playoff_bytes;
	cm3_clubs* third = 0;
	teams_seeded* teams = (teams_seeded*)playoff_data->teams_list;
	for (WORD i = 0; i < playoff_data->n_teams; i++) {
		if (teams[i].f6 == 1) third = teams[i].club;
	}
	team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
	cm3_clubs* first = table[0].club;
	cm3_clubs* second = table[1].club;
	return sub_4AFCE0_add_history_entry(_this, first, second, third, 0);
}

void __declspec(naked) nor_first_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call nor_first_set_champion
		add esp, 0x4
		ret 0
	}
}

void nor_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = nor_first_vtable;
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

void nor_first_free(BYTE* _this, BYTE a2) {
	nor_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) nor_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call nor_first_free
		add esp, 0x8
		ret 4
	}
}

void nor_first_subs(BYTE* _this)
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
	comp_data->promotions = 2;
	comp_data->prom_playoff = 4;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 2;

	comp_data->promotes_to = NOR_PREMIER_9CF();
	comp_data->relegates_to = NOR_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) nor_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call nor_first_subs
		add esp, 0x4
		ret
	}
}

DWORD nor_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 31), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 21), year, Monday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 28), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 3), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 11), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 16), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 15), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 18), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 26), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 30), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 6), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 10), year, Sunday);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 18), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 23), year, Saturday);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 29), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 22), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = PromotionPlayoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 5, 2, 1, 2, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 23), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 26), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 5, 2, 1, 1, 2, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 27), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 30), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 5, 2, 1, 1, 3, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 23), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 2, 1, 2, 0, 0, 2, 6);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) nor_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call nor_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void nor_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = nor_first_vtable;
	data->year = year;
	data->rules = RulesNorwayLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 800;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 2;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	data->stages[1] = 0;
	nor_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, 29839);
	data->f225 = 1;
	SetupTVMoney(_this, 139647, 0);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void nor_first_playoff_prom(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = comp_data->prom_playoff;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = comp_data->promotions, j = playoff_teams; i < total_teams && j > 0; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[j - 1])) = (DWORD)tls.club;
			j--;
		}
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

void nor_first_playoff_rele(BYTE* _this) {
	char stage_num = 1;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	int j = 0;
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == BottomPlayoff) {
			*((DWORD*)(&pTeams[0])) = (DWORD)tls.club;
			*((DWORD*)(&pTeams[1])) = 0;
			break;
		}
	}

	comp_stats* nor_second_data = (comp_stats*)get_loaded_league(NOR_SECOND_9CF());
	BYTE* prom_playoff = (BYTE*)(nor_second_data->stages[1]);

	if (prom_playoff)
	{
		DWORD v1 = *(DWORD*)prom_playoff;
		char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(prom_playoff, 0, 1);
		if (ret != 0) {
			comp_stats* playoff_stage = (comp_stats*)prom_playoff;
			for (WORD i = 0; i < playoff_stage->n_teams; i++) {
				teams_seeded t = ((teams_seeded*)playoff_stage->teams_list)[i];
				if (t.f6 == 1) {
					*((DWORD*)(&pTeams[1])) = (DWORD)t.club;
					break;
				}
			}
			comp_data->current_stage = stage_num;
		}
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

void nor_first_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		if (current == 0) {
			comp_data->current_stage = current;
			nor_first_playoff_prom(_this);
			nor_first_playoff_rele(_this);
		}
		/*else if (current == 1)
		{
			BYTE* nor_second = get_loaded_league(NOR_SECOND_9CF());
			comp_stats* nor_second_data = (comp_stats*)nor_second;
			BYTE* prom_playoff = (BYTE*)nor_second_data->stages[1];
			if (prom_playoff) {
				DWORD v1 = *(DWORD*)prom_playoff;
				char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(prom_playoff, 0, 1);
				if (ret != 0) {
					(*(void(__thiscall**)(BYTE*))(v1 + 0x94))(prom_playoff);
					comp_data->current_stage = current;
					dprintf("NOR_FIRST playoff create: relegation playoff creation\n", current, max);
					nor_first_playoff_rele(_this);
				}
			}
		}*/
	}
}

void __declspec(naked) nor_first_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call nor_first_playoffs_c
		add esp, 0x4
		ret
	}
}

int nor_first_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_club_comps* nor_premier = get_comp(NOR_PREMIER_9CF());
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		for (int i = 0; i < num_teams; i++) {
			if (table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)nor_premier, None, Playoff, 0xF);
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
	else if (stage == 1) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* nor_second = get_comp(NOR_SECOND_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club_ptr->ClubDivision == nor_second) {
			WORD current_round = *(WORD*)(round_data + 0x34);
			comp_stats* nor_second_data = (comp_stats*)get_loaded_league(NOR_SECOND_9CF());
			comp_stats* curr_stage = nor_second_data;
			for (char al = -1; al < 1; al++) {
				if (al >= 0) {
					curr_stage = (comp_stats*)(nor_second_data->stages[al]);
				}
				WORD num_teams = curr_stage->n_teams;
				team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
				for (int i = 0; i < num_teams; i++) {
					if (table[i].club != club) continue;
					switch (fate) {
					case TopPlayoff:
						staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)nor_second, 0x32);
						table[i].league_fate = Promoted;
						*a5 = 1;
						return 0;
					case Promoted:
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
		else {
			WORD num_teams = comp_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
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
	else {
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
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

void __declspec(naked) nor_first_set_table_fate()
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
		call nor_first_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

char nor_first_update(BYTE* _this) {
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
	nor_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, 29839);
	data->f225 = 1;
	SetupTVMoney(_this, 139647, 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) nor_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call nor_first_update
		add esp, 0x4
		ret
	}
}

void nor_first_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		ret_current = 2 + current;
		ret_min = 2 + min;
		ret_max = 2 + max;
	}
	else if (stage == 1) {
		comp_stats* d3_comp_data = (comp_stats*)get_loaded_league(NOR_SECOND_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == NOR_SECOND_9CF()) {
			ret = (BYTE*)sub_4A4850((BYTE*)d3_comp_data->f8, club);
			if (!ret) return;
			ret_current = 2;
			ret_min = 2;
			ret_max = 2;
		}
		else {
			ret_current = 14;
			ret_min = 14;
			ret_max = 14;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) nor_first_reputation_calc_c()
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
		call nor_first_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_nor_first()
{
	WriteVTablePtr(nor_first_vtable, VTableSubsRounds, (DWORD)&nor_first_subs_c);
	WriteVTablePtr(nor_first_vtable, VTableInitFree, (DWORD)&nor_first_free_c);
	WriteVTablePtr(nor_first_vtable, VTableEoSUpdate, (DWORD)&nor_first_update_c);
	WriteVTablePtr(nor_first_vtable, VTableFixtures, (DWORD)&nor_first_fixtures_c);
	WriteVTablePtr(nor_first_vtable, VTableReputationCalc, (DWORD)&nor_first_reputation_calc_c);
	WriteVTablePtr(nor_first_vtable, VTablePlayoffQual, (DWORD)&nor_first_playoffs_create);
	WriteVTablePtr(nor_first_vtable, VTableTableFates, (DWORD)&nor_first_set_table_fate);
	WriteVTablePtr(nor_first_vtable, VTableSetChampion, (DWORD)&nor_first_set_champion_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(nor_first_vtable, VTable21, 0x4110b0);
}
