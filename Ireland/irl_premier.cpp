#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* irl_premier_vtable = (DWORD*)0x96C014;

void irl_premier_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 4;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = NoTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 1;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = IRL_FIRST_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) irl_premier_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irl_premier_subs
		add esp, 0x4
		ret
	}
}

void irl_premier_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* irl_first = get_loaded_league(IRL_FIRST_9CF());
	v1 = *(DWORD*)irl_first;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(irl_first);
	process_promotion_relegation_689C80(_this, _this, irl_first, 1, a2, -1, -1);
}

void __declspec(naked) irl_premier_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call irl_premier_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall irl_first_relegation()
{
	cm3_clubs* relegate = 0;
	BYTE* comp_bytes = get_loaded_league(IRL_FIRST_9CF());
	comp_stats* comp_data = (comp_stats*)comp_bytes;
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Relegated) {
			relegate = table_pos.club;
			break;
		}
	}

	cm3_clubs* promote = 0;
	comp_stats* playoff_stage = (comp_stats*)comp_data->stages[1];
	WORD promoted_teams = 0;
	for (WORD i = 0; i < playoff_stage->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)playoff_stage->teams_list)[i];
		if (t.f6 == 1) {
			if (t.club->ClubDivision && t.club->ClubDivision != comp_data->competition_db) {
				promote = t.club;
				break;
			}
		}
	}

	if (promote && relegate) {
		cm3_club_comps* relegate_to = promote->ClubDivision;
		promote_club_6830B0((BYTE*)promote, (DWORD)comp_data->competition_db, 1);
		relegate_club_6831A0((BYTE*)relegate, (DWORD)relegate_to, 1);
	}
}

char irl_premier_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* irl_first = get_loaded_league(IRL_FIRST_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be semi-professional
	update_club_pro_status_68A980(irl_first, SemiProfessional, Relegated, -3, 1);
	update_club_pro_status_68A980(irl_first, SemiProfessional, Relegated, -3, 0);
	update_club_pro_status_68A980(irl_first, SemiProfessional, -3, Relegated, 1);
	update_club_pro_status_68A980(irl_first, SemiProfessional, -3, Relegated, 0);

	irl_premier_prom_rel_update(_this, 1);
	if (data->year > 2026) irl_first_relegation();

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
	irl_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("irl_prm_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("irl_prm_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)irl_first;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(irl_first);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) irl_premier_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irl_premier_update
		add esp, 0x4
		ret
	}
}

void irl_premier_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = irl_premier_vtable;
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

void irl_premier_free(BYTE* _this, BYTE a2) {
	irl_premier_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) irl_premier_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call irl_premier_free
		add esp, 0x8
		ret 4
	}
}

DWORD irl_premier_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddFixture(pMem, fixture_id, Date(year, 2, 14), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 2, 21), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 2, 28), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 3), year, Monday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 7), year, Friday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 14), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 28), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 4), year, Friday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 11), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 18), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 21), year, Monday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 25), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 2), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 5), year, Monday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 9), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 16), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 23), year, Friday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 30), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 13), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 20), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 23), year, Monday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 27), year, Friday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 4), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 11), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 25), year, Friday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 1), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 8), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 22), year, Friday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 29), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 12), year, Friday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 19), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 26), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 3), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 17), year, Friday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 24), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 1), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 7), year, Friday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreaker, 5, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) irl_premier_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call irl_premier_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void irl_premier_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = irl_premier_vtable;
	data->year = year;
	data->rules = RulesIreland;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	irl_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("irl_prm_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("irl_prm_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void irl_premier_playoff_under(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
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

	comp_stats* irl_first_data = (comp_stats*)get_loaded_league(IRL_FIRST_9CF());
	total_teams = irl_first_data->n_teams;
	table_teams = (team_league_stats*)(irl_first_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[1])) = (DWORD)tls.club;
			break;
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
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
}

void irl_premier_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		BYTE* irl_first = get_loaded_league(IRL_FIRST_9CF());
		comp_stats* irl_first_data = (comp_stats*)irl_first;
		BYTE* prom_playoff = (BYTE*)irl_first_data->stages[0];
		if (prom_playoff) {
			DWORD v1 = *(DWORD*)prom_playoff;
			char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(prom_playoff, 0, 1);
			if (ret != 0) {
				current++;
				if (current == 0) {
					comp_data->current_stage = current;
					irl_premier_playoff_under(_this);
				}
			}
		}
	}
}

void __declspec(naked) irl_premier_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irl_premier_playoffs_c
		add esp, 0x4
		ret
	}
}

int irl_premier_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* irl_first = get_comp(IRL_FIRST_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club_ptr->ClubDivision == irl_first) {
			comp_stats* irl_first_data = (comp_stats*)get_loaded_league(IRL_FIRST_9CF());
			WORD num_teams = irl_first_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(irl_first_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)irl_first, 0x32);
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

void __declspec(naked) irl_premier_set_table_fate()
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
		call irl_premier_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void irl_premier_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		comp_stats* d2_comp_data = (comp_stats*)get_loaded_league(IRL_FIRST_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == IRL_FIRST_9CF()) {
			ret = (BYTE*)sub_4A4850((BYTE*)d2_comp_data->f8, club);
			if (!ret) return;
			ret_current = 2;
			ret_min = 2;
			ret_max = 2;
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

void __declspec(naked) irl_premier_reputation_calc_c()
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
		call irl_premier_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_irl_premier()
{
	WriteVTablePtr(irl_premier_vtable, VTableSubsRounds, (DWORD)&irl_premier_subs_c);
	WriteVTablePtr(irl_premier_vtable, VTableInitFree, (DWORD)&irl_premier_free_c);
	WriteVTablePtr(irl_premier_vtable, VTableEoSUpdate, (DWORD)&irl_premier_update_c);
	WriteVTablePtr(irl_premier_vtable, VTableFixtures, (DWORD)&irl_premier_fixtures_c);
	WriteVTablePtr(irl_premier_vtable, VTableReputationCalc, (DWORD)&irl_premier_reputation_calc_c);
	WriteVTablePtr(irl_premier_vtable, VTablePlayoffQual, (DWORD)&irl_premier_playoffs_create);
	WriteVTablePtr(irl_premier_vtable, VTableTableFates, (DWORD)&irl_premier_set_table_fate);
	WriteVTablePtr(irl_premier_vtable, VTablePromRelUpdate, (DWORD)&irl_premier_prom_rel_update_c);
	WriteVTablePtr(irl_premier_vtable, VTableLoadCompInfo, 0x48CEB0);
	WriteVTablePtr(irl_premier_vtable, VTableSaveCompInfo, 0x48CEA0);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(irl_premier_vtable, VTableShowThirdInHistory, 0x4110b0);
}
