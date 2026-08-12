#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <Helpers\9cf_constants.h>

vtable* sco_pyramid_playoff_vtable = new vtable((BYTE*)0x96C0C8, 0xB4);

void sco_pyramid_playoff_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(sco_pyramid_playoff_vtable->vtable_ptr);
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

void sco_pyramid_playoff_free(BYTE* _this, BYTE a2) {
	sco_pyramid_playoff_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) sco_pyramid_playoff_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call sco_pyramid_playoff_free
		add esp, 0x8
		ret 4
	}
}

void sco_pyramid_playoff_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = NoTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 1;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->f217 = 2;
	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 19, April, comp_data->year + 1, Sunday);
	*((WORD*)(_this + 0xB6)) = *(WORD*)(cm_date);
	*((WORD*)(_this + 0xB8)) = 1;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) sco_pyramid_playoff_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_pyramid_playoff_subs
		add esp, 0x4
		ret
	}
}

char sco_pyramid_playoff_update(BYTE* _this) {
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
	sco_pyramid_playoff_subs(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) sco_pyramid_playoff_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_pyramid_playoff_update
		add esp, 0x4
		ret
	}
}

int sco_pyramid_playoff_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	cm3_club_comps* sco_l2 = get_comp(SCO_LEAGUE_2_9CF());
	if (stage < 0) {
		switch (fate) {
		case Champions:
			return 0;
		case Promoted:
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)sco_l2, None, Playoff, 0x1E);
			return 0;
		case BottomPlayoff:
			return 0;
		case Relegated:
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) sco_pyramid_playoff_set_table_fate()
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
		call sco_pyramid_playoff_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

DWORD sco_pyramid_playoff_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 3;
		*num_rounds = numberOfLeagueTeams * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 28), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 2), year, Saturday);

		if (fixture_id != 3) {
			string msg = "Wrong number of fixtures: " + to_string(fixture_id);
			create_message_box("Error", msg.c_str(), true);
		}

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) sco_pyramid_playoff_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_pyramid_playoff_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int sco_pyramid_playoff_teams(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	WORD playoff_teams = 3;
	BYTE* pMem = (BYTE*)cm0102_malloc(league_team_list_sz * playoff_teams);

	comp_data->n_teams = playoff_teams;
	comp_data->team_league_table = (DWORD*)pMem;

	BYTE teamsAdded = 0;

	comp_stats* sco_highland_data = (comp_stats*)get_loaded_league(SCO_HIGHLAND_9CF());
	WORD total_teams = sco_highland_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(sco_highland_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)tls.club, &is_main_club, 1);
		if (ret_club && !is_main_club) continue;
		add_team_call(_this, teamsAdded++, tls.club, 0, 0);
		break;
	}
	comp_stats* sco_lowland_data = (comp_stats*)get_loaded_league(SCO_LOWLAND_9CF());
	comp_stats* curr_stage = sco_lowland_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(sco_lowland_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)tls.club, &is_main_club, 1);
			if (ret_club && !is_main_club) continue;
			add_team_call(_this, teamsAdded++, tls.club, 0, 0);
			break;
		}
	}

	return 1;
}

void sco_pyramid_playoff_63B300(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		WORD day = *(WORD*)(_this + 0xB6);
		short year = *(short*)(_this + 0xB8);
		if (day >= *(WORD*)(current_date) && *(WORD*)(current_date + 2) == data->year + year) {
			BYTE* sco_highland = get_loaded_league(SCO_HIGHLAND_9CF());
			BYTE* sco_lowland = get_loaded_league(SCO_LOWLAND_9CF());
			comp_stats* sco_lowland_data = (comp_stats*)sco_lowland;
			BYTE* sco_lowland_grp = (BYTE*)sco_lowland_data->stages[0];
			DWORD v1 = *(DWORD*)sco_highland;
			DWORD v2 = *(DWORD*)sco_lowland;
			char ret1 = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(sco_highland, 0, 1);
			char ret2 = (*(int(__thiscall**)(BYTE*, int, int))(v2 + 0x10))(sco_lowland, 0, 1);
			char ret3 = (*(int(__thiscall**)(BYTE*, int, int))(v2 + 0x10))(sco_lowland_grp, 0, 1);
			if (ret1 != 0 && ret2 != 0 && ret3 != 0) {
				if (!a3) {
					(*(void(__thiscall**)(BYTE*))(v1 + 0x94))(sco_highland);
					(*(void(__thiscall**)(BYTE*))(v2 + 0x94))(sco_lowland);
					(*(void(__thiscall**)(BYTE*))(v2 + 0x94))(sco_lowland_grp);
					sco_pyramid_playoff_teams(_this);
					sub_6835C0(_this);
					sub_6827D0(_this, 0);
					DWORD v1 = *(DWORD*)_this;
					(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
					data->f69 = 1;
				}
			}
		}
	}
	sub_6847C0(_this, current_date, a3);
}

void __declspec(naked) sco_pyramid_playoff_63B300_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_pyramid_playoff_63B300
		add esp, 0xc
		ret 8
	}
}

void sco_pyramid_playoff_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(sco_pyramid_playoff_vtable->vtable_ptr);
	sco_pyramid_playoff_vtable->SetPointer(VTableInitFree, (DWORD)&sco_pyramid_playoff_free_c);
	sco_pyramid_playoff_vtable->SetPointer(VTableEoSUpdate, (DWORD)&sco_pyramid_playoff_update_c);
	sco_pyramid_playoff_vtable->SetPointer(VTableLeagueSplit, (DWORD)&sco_pyramid_playoff_63B300_c);
	sco_pyramid_playoff_vtable->SetPointer(VTableFixtures, (DWORD)&sco_pyramid_playoff_fixtures_c);
	sco_pyramid_playoff_vtable->SetPointer(VTableSubsRounds, (DWORD)&sco_pyramid_playoff_subs_c);
	sco_pyramid_playoff_vtable->SetPointer(VTableTableFates, (DWORD)&sco_pyramid_playoff_set_table_fate);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) sco_pyramid_playoff_vtable->SetPointer(VTable21, 0x4110b0);
	data->year = year;
	data->rules = RulesScotlandLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	sco_pyramid_playoff_subs(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void setup_sco_pyramid_playoff()
{
}
