#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include "Helpers\9cf_constants.h"

vtable* fra_national_vtable = new vtable((BYTE*)0x970694, 0xB4);

int fra_national_set_champion(BYTE* _this) {
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

void __declspec(naked) fra_national_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fra_national_set_champion
		add esp, 0x4
		ret 0
	}
}

int fra_national_last_positions(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < curr_stage->n_teams; i++) {
			team_league_stats tls = table_teams[i];
			tls.club->ClubLastDivision = data->competition_db;
			tls.club->ClubLastPosition = i + 1;
		}
	}
	return 1;
}

void __declspec(naked) fra_national_last_positions_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fra_national_last_positions
		add esp, 0x4
		ret
	}
}

void fra_national_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(fra_national_vtable->vtable_ptr);
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

void fra_national_free(BYTE* _this, BYTE a2) {
	fra_national_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) fra_national_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call fra_national_free
		add esp, 0x8
		ret 4
	}
}

void fra_national_subs(BYTE* _this)
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
	comp_data->f82 = 2;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 3;

	comp_data->promotes_to = FRA_THIRD_9CF();
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x2;
	comp_data->max_bench = 9;
	comp_data->max_subs = 5;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) fra_national_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fra_national_subs
		add esp, 0x4
		ret
	}
}

DWORD fra_national_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = 16;
		if (stage_idx == 1 && year == 2026) numberOfLeagueTeams = 18;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 5), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 12), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 19), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 31), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 7), year, Saturday);
		if (numberOfLeagueTeams > 16) AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 5), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 12), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 23), year, Saturday);
		if (numberOfLeagueTeams > 16) AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 30), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 20), year, Saturday);
		if (numberOfLeagueTeams > 16) AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 1), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 8), year, Saturday);
		if (numberOfLeagueTeams > 16) AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 15), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 29), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) fra_national_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fra_national_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void fra_national_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD group_id = FRA_NATIONAL_1_B_9CF();
	if (idx == 1) group_id = FRA_NATIONAL_1_C_9CF();
	WORD n_teams = data->n_teams;
	if (idx == 1 && data->year == 2026) n_teams++;
	DWORD* pTeams = (DWORD*)cm0102_malloc(n_teams * 4);

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
	create_league_stage_data(pStage, _this, n_teams, pTeams, data->n_rounds, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	if (idx == 1 && data->year == 2026) {
		comp_stats* stage = (comp_stats*)pStage;
		stage->relegations++;
	}
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void fra_national_reputation_setup(BYTE* _this) {
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

void __declspec(naked) fra_national_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fra_national_reputation_setup
		add esp, 0x4
		ret
	}
}

void fra_national_block_promotion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
			if (ret_club && !is_main_club) table_teams[i].league_fate = CantBePromoted;
		}
	}
}

char fra_national_update(BYTE* _this) {
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
	fra_national_subs(_this);
	AddTeamsGroupLeague(_this, FRA_NATIONAL_1_A_9CF());
	sub_6827D0(_this, 0);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 2; i++) {
		fra_national_setup_groups(_this, i);
	}
	fra_national_block_promotion(_this);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) fra_national_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call fra_national_update
		add esp, 0x4
		ret
	}
}

int fra_national_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 2) {
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RelegationPlayoff, 0x1E);
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

void __declspec(naked) fra_national_table_fates_c()
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
		call fra_national_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

void fra_national_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 2) {
		ret_current = 1 + 3 * (current - 1);
		ret_min = 1 + 3 * (min - 1);
		ret_max = 1 + 3 * (max - 1);
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) fra_national_reputation_calc_c()
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
		call fra_national_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

int fra_national_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id < 2) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
}

void __declspec(naked) fra_national_stage_news_c()
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
		call fra_national_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void fra_national_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(fra_national_vtable->vtable_ptr);
	fra_national_vtable->SetPointer(VTableInitFree, (DWORD)&fra_national_free_c);
	fra_national_vtable->SetPointer(VTableEoSUpdate, (DWORD)&fra_national_update_c);
	fra_national_vtable->SetPointer(VTableFixtures, (DWORD)&fra_national_fixtures_c);
	fra_national_vtable->SetPointer(VTableReputationSetup, (DWORD)&fra_national_reputation_setup_c);
	fra_national_vtable->SetPointer(VTableReputationCalc, (DWORD)&fra_national_reputation_calc_c);
	fra_national_vtable->SetPointer(VTableSubsRounds, (DWORD)&fra_national_subs_c);
	fra_national_vtable->SetPointer(VTableTableFates, (DWORD)&fra_national_table_fates_c);
	fra_national_vtable->SetPointer(VTableSetChampion, (DWORD)&fra_national_set_champion_c);
	fra_national_vtable->SetPointer(VTableUpdateLastDivision, (DWORD)&fra_national_last_positions_c);
	fra_national_vtable->SetPointer(VTableStageNews, (DWORD)&fra_national_stage_news_c);
	data->year = year;
	data->rules = RulesFrance;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 2;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	fra_national_subs(_this);
	AddTeamsGroupLeague(_this, FRA_NATIONAL_1_A_9CF());
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 2; i++) {
		fra_national_setup_groups(_this, i);
	}
	fra_national_block_promotion(_this);
	fra_national_reputation_setup(_this);
}

void setup_fra_national()
{
}