#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* sco_league_1_vtable = (DWORD*)0x96F6BC;

void sco_league_1_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = sco_league_1_vtable;
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

void sco_league_1_free(BYTE* _this, BYTE a2) {
	sco_league_1_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) sco_league_1_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call sco_league_1_free
		add esp, 0x8
		ret 4
	}
}

void sco_league_1_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 4;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 3;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 1;

	comp_data->promotes_to = SCO_CHAMP_9CF();
	comp_data->relegates_to = SCO_LEAGUE_2_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) sco_league_1_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_league_1_subs
		add esp, 0x4
		ret
	}
}

DWORD sco_league_1_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 3), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 2), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = Playoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 6), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 4, 2, 4, 0, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 13), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 2, 1, 0, 0, 0, 2, 3);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) sco_league_1_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_league_1_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void sco_league_1_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = sco_league_1_vtable;
	data->year = year;
	data->rules = RulesScotlandLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	sco_league_1_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("sco_l1_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("sco_l1_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void sco_league_1_playoff_rele(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == BottomPlayoff) {
			*((DWORD*)(&pTeams[0])) = (DWORD)tls.club;
			break;
		}
	}

	comp_stats* sco_league_2_data = (comp_stats*)get_loaded_league(SCO_LEAGUE_2_9CF());
	total_teams = sco_league_2_data->n_teams;
	table_teams = (team_league_stats*)(sco_league_2_data->team_league_table);
	WORD start_idx = 3;
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[start_idx--])) = (DWORD)tls.club;
		}
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

void sco_champ_playoff_send_teams(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* sco_champ_data = (comp_stats*)get_loaded_league(SCO_CHAMP_9CF());
	comp_stats* playoff_stage = (comp_stats*)sco_champ_data->stages[1];
	if (playoff_stage) {
		teams_seeded* teams = (teams_seeded*)playoff_stage->teams_list;
		if (!teams[1].club) {
			team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
			WORD total_teams = comp_data->n_teams;
			WORD start_idx = 3;
			for (int i = 0; i < total_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.league_fate == TopPlayoff) {
					teams[start_idx--].club = tls.club;
				}
			}
		}
	}
}

void sco_league_1_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		if (current == 0) {
			BYTE* sco_league_2 = get_loaded_league(SCO_LEAGUE_2_9CF());
			DWORD v1 = *(DWORD*)sco_league_2;
			char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(sco_league_2, 0, 1);
			if (ret != 0) {
				(*(void(__thiscall**)(BYTE*))(v1 + 0x94))(sco_league_2);
				comp_data->current_stage = current;
				sco_league_1_playoff_rele(_this);
			}
		}
	}
	comp_stats* sco_champ_data = (comp_stats*)get_loaded_league(SCO_CHAMP_9CF());
	if (current == 0 && sco_champ_data->current_stage == 1) {
		sco_champ_playoff_send_teams(_this);
	}
}

void __declspec(naked) sco_league_1_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_league_1_playoffs_c
		add esp, 0x4
		ret
	}
}

int sco_league_1_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* sco_league_2 = get_comp(SCO_LEAGUE_2_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club_ptr->ClubDivision == sco_league_2) {
			WORD current_round = *(WORD*)(round_data + 0x34);
			comp_stats* sco_league_2_data = (comp_stats*)get_loaded_league(SCO_LEAGUE_2_9CF());
			WORD num_teams = sco_league_2_data->n_teams;
			team_league_stats* table = (team_league_stats*)(sco_league_2_data->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)sco_league_2, 0x32);
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
				case Promoted:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				case TopPlayoff:
					table[i].league_fate = Eliminated;
					return 0;
				default:
					staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					table[i].league_fate = Relegated;
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

void __declspec(naked) sco_league_1_set_table_fate()
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
		call sco_league_1_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

char sco_league_1_update(BYTE* _this) {
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
	sco_league_1_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("sco_l1_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("sco_l1_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) sco_league_1_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_league_1_update
		add esp, 0x4
		ret
	}
}

void sco_league_1_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		comp_stats* d4_comp_data = (comp_stats*)get_loaded_league(SCO_LEAGUE_2_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == SCO_LEAGUE_2_9CF()) {
			ret = (BYTE*)sub_4A4850((BYTE*)d4_comp_data->f8, club);
			if (!ret) return;
			ret_current = 1 + current;
			ret_min = 1 + min;
			ret_max = 1 + max;
		}
		else {
			ret_current = 9;
			ret_min = 9;
			ret_max = 9;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) sco_league_1_reputation_calc_c()
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
		call sco_league_1_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_sco_league_1()
{
	WriteVTablePtr(sco_league_1_vtable, VTableSubsRounds, (DWORD)&sco_league_1_subs_c);
	WriteVTablePtr(sco_league_1_vtable, VTableInitFree, (DWORD)&sco_league_1_free_c);
	WriteVTablePtr(sco_league_1_vtable, VTableEoSUpdate, (DWORD)&sco_league_1_update_c);
	WriteVTablePtr(sco_league_1_vtable, VTableFixtures, (DWORD)&sco_league_1_fixtures_c);
	WriteVTablePtr(sco_league_1_vtable, VTableReputationCalc, (DWORD)&sco_league_1_reputation_calc_c);
	WriteVTablePtr(sco_league_1_vtable, VTablePlayoffQual, (DWORD)&sco_league_1_playoffs_create);
	WriteVTablePtr(sco_league_1_vtable, VTableTableFates, (DWORD)&sco_league_1_set_table_fate);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(sco_league_1_vtable, VTableShowThirdInHistory, 0x4110b0);
}
