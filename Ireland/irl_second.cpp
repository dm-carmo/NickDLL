#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

vtable* irl_second_vtable = new vtable((BYTE*)0x970844, 0xB4);

void irl_second_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(irl_second_vtable->vtable_ptr);
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

void irl_second_free(BYTE* _this, BYTE a2) {
	irl_second_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) irl_second_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call irl_second_free
		add esp, 0x8
		ret 4
	}
}

void irl_second_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
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
	else if (stage == 2) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) irl_second_reputation_calc_c()
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
		call irl_second_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void irl_second_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		DWORD* all_teams = comp_data->teams2;
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < 15; i++) clubs.push_back((cm3_clubs*)all_teams[i]);
		sort(clubs.begin(), clubs.end(), compareClubRep);

		sub_4A2540((BYTE*)comp_data->f8, clubs[0], 1);
		sub_4A2540((BYTE*)comp_data->f8, clubs[1], 2);
		for (int i = 2; i < 4; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 3);
		}
		for (int i = 4; i < 6; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 5);
		}
		for (int i = 0; i < 3; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[6 + 3 * i], 8 + 3 * i);
			sub_4A2540((BYTE*)comp_data->f8, clubs[7 + 3 * i], 8 + 3 * i);
			sub_4A2540((BYTE*)comp_data->f8, clubs[8 + 3 * i], 8 + 3 * i);
		}
	}
}

void __declspec(naked) irl_second_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irl_second_reputation_setup
		add esp, 0x4
		ret
	}
}

int irl_second_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[2];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) irl_second_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irl_second_set_champion
		add esp, 0x4
		ret 0
	}
}

int irl_second_add_teams(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* all_teams = comp_data->teams2;
	if (all_teams) sub_9452CA_free(all_teams);

	vector<cm3_clubs*> league_clubs = find_clubs_of_comp(comp_data->competition_db->ClubCompID);
	comp_data->teams2 = (DWORD*)cm0102_malloc(league_clubs.size() * 4);
	sort(league_clubs.begin(), league_clubs.end(), compareClubLatitude);
	for (DWORD i = 0; i < league_clubs.size(); i++)
	{
		*((DWORD*)(&comp_data->teams2[i])) = (DWORD)league_clubs[i];
	}

	comp_data->n_teams = 5; // number of teams per group in this case
	comp_data->team_league_table = (DWORD*)cm0102_malloc(comp_data->n_teams * league_team_list_sz);
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < comp_data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)(comp_data->teams2[i]);
		add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

void irl_second_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;

	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)all_teams[data->n_teams * (idx + 1) + i];
		*((DWORD*)(&pTeams[i])) = (DWORD)club;
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

void irl_second_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	if (comp_data->year > 2026) comp_data->n_rounds = 4;
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

	comp_data->f217 = 0x2;
	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) irl_second_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irl_second_subs
		add esp, 0x4
		ret
	}
}

DWORD irl_second_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		BYTE numberOfLeagueTeams = 5;
		*num_rounds = (numberOfLeagueTeams - 1 + numberOfLeagueTeams % 2) * data->n_rounds;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (year > 2026) {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 7), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 21), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 4), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 18), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 2), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 16), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 30), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 13), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 27), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 11), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 25), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 8), year, Saturday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 22), year, Saturday);
		}
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 5), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 12), year, Saturday);
		if (year == 2026) AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 19), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 26), year, Saturday);
		if (year == 2026) AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 17), year, Saturday);
		if (year == 2026) AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 31), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 2;
		*stage_name_id = Playoff;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 1), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, Penalties | ExtraTime, NoTiebreak, 5, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 5, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) irl_second_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call irl_second_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char irl_second_update(BYTE* _this) {
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
	irl_second_subs(_this);
	irl_second_add_teams(_this);
	sub_6827D0(_this, 0);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 2; i++) {
		irl_second_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) irl_second_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irl_second_update
		add esp, 0x4
		ret
	}
}

int irl_second_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
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
	else if (stage == 2) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		comp_stats* curr_stage = comp_data;
		cm3_club_comps* irl_first = get_comp(IRL_FIRST_9CF());
		for (char al = -1; al < 2; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					if (comp_data->year > 2026) staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)irl_first, None, Playoff, 0x1E);
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

void __declspec(naked) irl_second_table_fates_c()
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
		call irl_second_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

void irl_second_playoff_finals(BYTE* _this) {
	char stage_num = 2;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	vector<cm3_clubs*> clubs;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
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

	// get best second placeds
	vector<team_league_stats> sort_seconds;
	curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls = table_teams[curr_stage->prom_playoff];
		sort_seconds.push_back(tls);
	}
	sort(sort_seconds.begin(), sort_seconds.end(), sortTLS);
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	for (int i = 0; i < 1; i++) {
		team_league_stats second = sort_seconds[i];
		clubs.push_back(second.club);
		curr_stage = comp_data;
		for (char al = -1; al < 2; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			team_league_stats tls = table_teams[curr_stage->prom_playoff];
			if (tls.club == second.club) {
				table_teams[curr_stage->prom_playoff].league_fate = TopPlayoff;
				curr_stage->prom_playoff++;
				staff_history_qualified_86BDD0(staff_hist_ptr, tls.club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
			}
		}
	}

	shuffle(clubs.begin(), clubs.end(), rng);
	for (char i = 0; i < playoff_teams; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i];
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

void irl_second_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 2) {
			irl_second_playoff_finals(_this);
		}
	}
}

void __declspec(naked) irl_second_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irl_second_playoffs_c
		add esp, 0x4
		ret
	}
}

void irl_second_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(irl_second_vtable->vtable_ptr);
	irl_second_vtable->SetPointer(VTableInitFree, (DWORD)&irl_second_free_c);
	irl_second_vtable->SetPointer(VTableSubsRounds, (DWORD)&irl_second_subs_c);
	irl_second_vtable->SetPointer(VTableReputationSetup, (DWORD)&irl_second_reputation_setup_c);
	irl_second_vtable->SetPointer(VTableFixtures, (DWORD)&irl_second_fixtures_c);
	irl_second_vtable->SetPointer(VTableEoSUpdate, (DWORD)&irl_second_update_c);
	irl_second_vtable->SetPointer(VTableReputationCalc, (DWORD)&irl_second_reputation_calc_c);
	irl_second_vtable->SetPointer(VTableSetChampion, (DWORD)&irl_second_set_champion_c);
	irl_second_vtable->SetPointer(VTableTableFates, (DWORD)&irl_second_table_fates_c);
	irl_second_vtable->SetPointer(VTableStageNews, 0x48c6d0);
	irl_second_vtable->SetPointer(VTablePlayoffQual, (DWORD)&irl_second_playoffs_create);
	irl_second_vtable->SetPointer(VTablePostMatchUpdate, 0x685d30);
	irl_second_vtable->SetPointer(VTable39, 0x404480);
	data->year = year;
	data->rules = RulesIreland;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 3;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	irl_second_subs(_this);
	irl_second_add_teams(_this);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	for (BYTE i = 0; i < 2; i++) {
		irl_second_setup_groups(_this, i);
	}
	irl_second_reputation_setup(_this);
}

void setup_irl_second() {
}