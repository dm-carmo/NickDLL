#pragma warning (disable : 4733)
#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <Helpers\9cf_constants.h>

vtable* sco_lowland_vtable = new vtable((BYTE*)0x969A74, 0xB4);

void sco_lowland_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(sco_lowland_vtable->vtable_ptr);
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

void sco_lowland_free(BYTE* _this, BYTE a2) {
	sco_lowland_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) sco_lowland_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call sco_lowland_free
		add esp, 0x8
		ret 4
	}
}

void sco_lowland_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
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
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) sco_lowland_reputation_calc_c()
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
		call sco_lowland_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void sco_lowland_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
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
				sub_4A2540((BYTE*)comp_data->f8, c, (char)(i * 2 + 1));
			}
		}
	}
}

void __declspec(naked) sco_lowland_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_lowland_reputation_setup
		add esp, 0x4
		ret
	}
}

int sco_lowland_set_champion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		sub_4AFCE0_add_history_entry(_this, table_teams[0].club, table_teams[1].club, table_teams[2].club, 0);
	}

	return 0;
}

void __declspec(naked) sco_lowland_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_lowland_set_champion
		add esp, 0x4
		ret 0
	}
}

int sco_lowland_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	cm3_club_comps* sco_playoff = get_comp(SCO_PYRAMID_PLAYOFF_9CF());
	if (stage < 1) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)sco_playoff, None, None, 0x1E);
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

void __declspec(naked) sco_lowland_set_table_fate()
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
		call sco_lowland_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int sco_lowland_add_teams(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* all_teams = comp_data->teams2;
	if (all_teams) sub_9452CA_free(all_teams);

	vector<cm3_clubs*> lowland_clubs = find_clubs_of_comp(comp_data->competition_db->ClubCompID);
	comp_data->teams2 = (DWORD*)cm0102_malloc(lowland_clubs.size() * 4);
	sort(lowland_clubs.begin(), lowland_clubs.end(), compareClubLongitude);
	for (DWORD i = 0; i < lowland_clubs.size(); i++)
	{
		*((DWORD*)(&comp_data->teams2[i])) = (DWORD)lowland_clubs[i];
	}

	comp_data->n_teams = 16; // number of teams per group in this case
	comp_data->team_league_table = (DWORD*)cm0102_malloc(16 * league_team_list_sz);
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < comp_data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)(comp_data->teams2[i]);
		add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

void sco_lowland_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	WORD n_teams = 16;
	if (data->year == 2026) n_teams++;
	DWORD* pTeams = (DWORD*)cm0102_malloc(n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)all_teams[data->n_teams * (idx + 1) + i];
		*((DWORD*)(&pTeams[i])) = (DWORD)club;
	}
	WORD year = data->year;
	char prom_rel[4] = { 0,1,0,1 };
	if (data->year == 2026) prom_rel[3]++;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage, _this, n_teams, pTeams, data->n_rounds, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

int sco_lowland_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = NoTiebreaker;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 1;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 1;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x2;
	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return 1;
}

void __declspec(naked) sco_lowland_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_lowland_subs
		add esp, 0x4
		ret
	}
}

DWORD sco_lowland_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = 16;
		if (year == 2026 && stage_idx == 0) numberOfLeagueTeams = 18;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = West + stage_idx;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 26), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 30), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 9), year, Saturday);
		if (numberOfLeagueTeams > 16) AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 20), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 23), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Saturday);
		if (numberOfLeagueTeams > 16) AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 3), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 15), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 1), year, Saturday);
		if (numberOfLeagueTeams > 16) AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 5), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 6), year, Saturday);
		if (numberOfLeagueTeams > 16) AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 10), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) sco_lowland_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_lowland_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void sco_lowland_block_promotion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
			if (ret_club && !is_main_club) {
				table_teams[i].league_fate = CantBePromotedOrRelegated;
			}
		}
	}
}

char sco_lowland_update(BYTE* _this) {
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
	sco_lowland_subs(_this);
	sco_lowland_add_teams(_this);
	sub_6827D0(_this, 0);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		sco_lowland_setup_groups(_this, i);
	}
	sco_lowland_block_promotion(_this);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) sco_lowland_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_lowland_update
		add esp, 0x4
		ret
	}
}

void sco_lowland_awards_teams(BYTE* _this, DWORD** team_list, WORD* total_teams) {

	comp_stats* comp_data = (comp_stats*)_this;
	*total_teams = 33;
	if (comp_data->year > 2026) (*total_teams)--;
	DWORD* pMem = (DWORD*)cm0102_malloc(4 * (*total_teams));
	*team_list = pMem;

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

void __declspec(naked) sco_lowland_awards_teams_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_lowland_awards_teams
		add esp, 0xc
		ret 8
	}
}

void sco_lowland_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(sco_lowland_vtable->vtable_ptr);
	sco_lowland_vtable->SetPointer(VTableInitFree, (DWORD)&sco_lowland_free_c);
	sco_lowland_vtable->SetPointer(VTableEoSUpdate, (DWORD)&sco_lowland_update_c);
	sco_lowland_vtable->SetPointer(VTableFixtures, (DWORD)&sco_lowland_fixtures_c);
	sco_lowland_vtable->SetPointer(VTableSubsRounds, (DWORD)&sco_lowland_subs_c);
	sco_lowland_vtable->SetPointer(VTableReputationSetup, (DWORD)&sco_lowland_reputation_setup_c);
	sco_lowland_vtable->SetPointer(VTableReputationCalc, (DWORD)&sco_lowland_reputation_calc_c);
	sco_lowland_vtable->SetPointer(VTableSetChampion, (DWORD)&sco_lowland_set_champion_c);
	sco_lowland_vtable->SetPointer(VTableTableFates, (DWORD)&sco_lowland_set_table_fate);
	sco_lowland_vtable->SetPointer(VTableAwardTeamsSetup, (DWORD)&sco_lowland_awards_teams_c);
	sco_lowland_vtable->SetPointer(VTableStageNews, 0x48c6d0);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) sco_lowland_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	data->year = year;
	data->rules = RulesScotlandLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	sco_lowland_subs(_this);
	sco_lowland_add_teams(_this);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	for (BYTE i = 0; i < 1; i++) {
		sco_lowland_setup_groups(_this, i);
	}
	sco_lowland_block_promotion(_this);
	sco_lowland_reputation_setup(_this);
}

void setup_sco_lowland() {
}