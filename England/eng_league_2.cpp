#pragma warning (disable : 4733)
#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <Helpers/9cf_constants.h>

DWORD* eng_league_2_vtable = (DWORD*)0x969E84;

int eng_league_2_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->promotions = 3;
	comp_data->prom_playoff = 4;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 2;

	comp_data->promotes_to = ENG_LEAGUE_1_9CF();
	BYTE selected = get_country(NATION_ENGLAND_9CF())->NationLeagueSelected;
	if ((selected & 4) == 0) {
		comp_data->relegates_to = -1;
	}
	else {
		comp_data->relegates_to = ENG_CONFERENCE_9CF();
	}

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return 1;
}

void __declspec(naked) eng_league_2_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_league_2_subs
		add esp, 0x4
		ret
	}
}

char* eng_league_2_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* playoff_bytes = (BYTE*)comp_data->stages[0];
	comp_stats* playoff_data = (comp_stats*)playoff_bytes;
	cm3_clubs* po_win = 0;
	teams_seeded* teams = (teams_seeded*)playoff_data->teams_list;
	for (WORD i = 0; i < playoff_data->n_teams; i++) {
		if (teams[i].f6 == 1) po_win = teams[i].club;
	}
	team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
	cm3_clubs* first = table[0].club;
	cm3_clubs* second = table[1].club;
	cm3_clubs* third = table[2].club;
	return sub_4AFCE0_add_history_entry(_this, first, second, third, po_win);
}

void __declspec(naked) eng_league_2_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_league_2_set_champion
		add esp, 0x4
		ret 0
	}
}

DWORD eng_league_2_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 0) {
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 23), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 2), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 21), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 1), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 15), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 2), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 20), year, Saturday);
		Date boxing_day = Date(year, 12, 26);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		boxing_day.addDays(3);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		boxing_day.addDays(3);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 20), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 10), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Saturday);
		Date easter_day = Date::easter_gregorian(year + 1);
		Date easter_test = Date(year + 1, 3, 21);
		int diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
		bool easter_done = false;
		if (diff < 4) {
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 20), year, Friday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 23), year, Monday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 28), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 7), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 21), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
			easter_done = true;
		}
		if (!easter_done) {
			easter_test = Date(year + 1, 3, 28);
			diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
			if (diff < 4) {
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 27), year, Friday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 30), year, Monday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 14), year, Tuesday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 28), year, Tuesday, Evening);
				easter_done = true;
			}
		}
		if (!easter_done) {
			easter_test = Date(year + 1, 4, 4);
			diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
			if (diff < 4) {
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 28), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 3), year, Friday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 6), year, Monday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 14), year, Tuesday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 28), year, Tuesday, Evening);
				easter_done = true;
			}
		}
		if (!easter_done) {
			easter_test = Date(year + 1, 4, 11);
			diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
			if (diff < 4) {
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 28), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 10), year, Friday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 13), year, Monday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 21), year, Tuesday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 28), year, Tuesday, Evening);
				easter_done = true;
			}
		}
		if (!easter_done) {
			easter_test = Date(year + 1, 4, 18);
			diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
			if (diff < 4) {
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 28), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 7), year, Tuesday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 17), year, Friday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 20), year, Monday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 28), year, Tuesday, Evening);
				easter_done = true;
			}
		}
		if (!easter_done) {
			easter_test = Date(year + 1, 4, 25);
			diff = abs(easter_test.DayOfYear() - easter_day.DayOfYear());
			if (diff < 4) {
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 28), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 31), year, Tuesday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 14), year, Tuesday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 24), year, Friday, Evening);
				AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 27), year, Monday, Evening);
				easter_done = true;
			}
		}
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 9), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else {
		if (stage_idx != 0) return 0;

		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = Playoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 16), year, Saturday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup3 | NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 5, 4, 2, 4, 0, 0, 2, 6);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 23), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 6, 1), year, Monday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 0, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) eng_league_2_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_league_2_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char eng_league_2_update(BYTE* _this) {
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
	eng_league_2_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("eng_l2_tv_money_relegated"), get_comp(ENG_LEAGUE_1_9CF()));
	SetupTVMoney(_this, prizeMoneyFile.GetInt("eng_l2_tv_money_all"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) eng_league_2_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_league_2_update
		add esp, 0x4
		ret
	}
}

void eng_league_2_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = eng_league_2_vtable;
	data->year = year;
	data->rules = RulesEngland;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 5000;
	data->min_stadium_seats = 1000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	eng_league_2_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("eng_l2_tv_money_relegated"), get_comp(ENG_LEAGUE_1_9CF()));
	SetupTVMoney(_this, prizeMoneyFile.GetInt("eng_l2_tv_money_all"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void __declspec(naked) eng_league_2_init_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_league_2_init
		add esp, 0xc
		ret 8
	}
}

void setup_eng_league_2() {
	WriteVTablePtr(eng_league_2_vtable, VTableEoSUpdate, (DWORD)&eng_league_2_update_c);
	WriteVTablePtr(eng_league_2_vtable, VTableFixtures, (DWORD)&eng_league_2_fixture_caller);
	WriteVTablePtr(eng_league_2_vtable, VTableSetChampion, (DWORD)&eng_league_2_set_champion_c);
	WriteVTablePtr(eng_league_2_vtable, VTableSubsRounds, (DWORD)&eng_league_2_subs_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(eng_league_2_vtable, VTableShowThirdInHistory, 0x4110b0);
	if (configFile.GetBool("showPlayoffWinnerInHistory", true)) WriteVTablePtr(eng_league_2_vtable, VTableShowHostsInHistory, 0x404480);
}