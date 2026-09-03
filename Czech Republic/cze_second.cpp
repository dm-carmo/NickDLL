#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

vtable* cze_second_vtable = new vtable((BYTE*)0x96CAF4, 0xB4);

void cze_second_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(cze_second_vtable->vtable_ptr);
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

void cze_second_free(BYTE* _this, BYTE a2) {
	cze_second_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) cze_second_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call cze_second_free
		add esp, 0x8
		ret 4
	}
}

void cze_second_subs(BYTE* _this)
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
	comp_data->promotions = 1;
	comp_data->prom_playoff = 2;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 2;

	comp_data->promotes_to = CZE_FIRST_9CF();
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) cze_second_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call cze_second_subs
		add esp, 0x4
		ret
	}
}

DWORD cze_second_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 25), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 1), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 8), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 15), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 22), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 29), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 5), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 12), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 19), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 10), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 17), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 24), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 31), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 7), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 21), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 28), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 6), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 13), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 20), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 3), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 10), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 14), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 17), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 24), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 1), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 5), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 8), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 15), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 22), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 29), year, Friday, Evening);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) cze_second_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call cze_second_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int cze_second_table_fates(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	cm3_club_comps* cze_first = get_comp(CZE_FIRST_9CF());
	if (stage == -1) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(cze_first), None, Playoff, 0x1E);
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
	return 0;
}

void __declspec(naked) cze_second_table_fates_c()
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
		call cze_second_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

void cze_second_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) cze_second_reputation_calc_c()
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
		call cze_second_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void cze_second_block_promotion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
		if (ret_club && !is_main_club) {
			table_teams[i].league_fate = CantBePromoted;
		}
	}
}

char cze_second_update(BYTE* _this) {
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
	cze_second_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("cze_second_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("cze_second_tv_money"), 0);
	cze_second_block_promotion(_this);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) cze_second_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call cze_second_update
		add esp, 0x4
		ret
	}
}

void cze_second_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(cze_second_vtable->vtable_ptr);
	cze_second_vtable->SetPointer(VTableEoSUpdate, (DWORD)&cze_second_update_c);
	cze_second_vtable->SetPointer(VTableSubsRounds, (DWORD)&cze_second_subs_c);
	cze_second_vtable->SetPointer(VTableFixtures, (DWORD)&cze_second_fixtures_c);
	cze_second_vtable->SetPointer(VTableInitFree, (DWORD)&cze_second_free_c);
	cze_second_vtable->SetPointer(VTableTableFates, (DWORD)&cze_second_table_fates_c);
	cze_second_vtable->SetPointer(VTableReputationCalc, (DWORD)&cze_second_reputation_calc_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) cze_second_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	data->year = year;
	data->rules = RulesCzech;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	cze_second_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("cze_second_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("cze_second_tv_money"), 0);
	cze_second_block_promotion(_this);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void setup_cze_second()
{

}