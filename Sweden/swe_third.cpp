#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include <map>
#include <Helpers\9cf_constants.h>

vtable* swe_third_vtable = new vtable((BYTE*)0x9702A0, 0xB4);

int swe_third_set_champion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	DWORD comp_ids[6] = { SWE_THIRD_NORRLAND_9CF(), SWE_THIRD_NORTH_SVEALAND_9CF(), SWE_THIRD_SOUTH_SVEALAND_9CF(), SWE_THIRD_NORTH_GOTALAND_9CF(), SWE_THIRD_WEST_GOTALAND_9CF(), SWE_THIRD_SOUTH_GOTALAND_9CF() };
	for (char al = -1; al < 5; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		DWORD tmp[2] = { 0, (DWORD)get_comp(comp_ids[al + 1]) };
		sub_4AFCE0_add_history_entry((BYTE*)tmp, table_teams[0].club, table_teams[1].club, table_teams[2].club, 0);
	}

	return 0;
}

void __declspec(naked) swe_third_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_third_set_champion
		add esp, 0x4
		ret 0
	}
}

void swe_third_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = NoTiebreaker;
	comp_data->f82 = 2;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 1;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 2;

	comp_data->promotes_to = SWE_SECOND_9CF();
	comp_data->relegates_to = -1;

	comp_data->f217 = 0x2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) swe_third_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_third_subs
		add esp, 0x4
		ret
	}
}

void swe_third_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(swe_third_vtable->vtable_ptr);
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

void swe_third_free(BYTE* _this, BYTE a2) {
	swe_third_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) swe_third_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call swe_third_free
		add esp, 0x8
		ret 4
	}
}

void swe_third_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 5; al++) {
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
				sub_4A2540((BYTE*)comp_data->f8, c, (char)(i * 6 + 1));
			}
		}
	}
}

void __declspec(naked) swe_third_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_third_reputation_setup
		add esp, 0x4
		ret
	}
}

DWORD swe_third_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 5) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = 14;
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		if (stage_idx == -1) *stage_name_id = North;
		else *stage_name_id = EastSvealand + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 3, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 5), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 12), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 19), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 26), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 31), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 18), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 23), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx < 7) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = ((comp_stats*)_this);
		WORD year = data->year;
		WORD numberOfLeagueTeams = 3;
		*num_rounds = numberOfLeagueTeams;
		*stage_name_id = PromotionGroupAtoD + (stage_idx - 5);

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 1), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 7) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 19), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 12, 6, 12, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) swe_third_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call swe_third_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void swe_third_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD group_id = SWE_THIRD_NORTH_SVEALAND_9CF();
	if (idx == 1) group_id = SWE_THIRD_SOUTH_SVEALAND_9CF();
	else if (idx == 2) group_id = SWE_THIRD_NORTH_GOTALAND_9CF();
	else if (idx == 3) group_id = SWE_THIRD_WEST_GOTALAND_9CF();
	else if (idx == 4) group_id = SWE_THIRD_SOUTH_GOTALAND_9CF();
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(data->n_teams * 4);

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
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, 14, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

int swe_third_table_indicators(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 5) {
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
	else if (stage < 7) {
		cm3_club_comps* swe_second = get_comp(SWE_SECOND_9CF());
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 5; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case Champions:
					staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					table[i].league_fate = Champions;
					return 0;
				case Promoted:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x32);
					table[i].league_fate = Promoted;
					return 0;
				case TopPlayoff:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(swe_second), None, Playoff, 0x1E);
					table[i].league_fate = TopPlayoff;
					return 0;
				case Eliminated:
					table[i].league_fate = Eliminated;
					return 0;
				case NoFate:
					table[i].league_fate = Eliminated;
					return 0;
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	else if (stage == 7) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 5; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
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
				case NoFate:
					table[i].league_fate = Eliminated;
					return 0;
				case TopPlayoff:
					table[i].league_fate = Eliminated;
					return 0;
				default:
					return 0;
				}
			}
		}
	}
	return 0;
}

void __declspec(naked) swe_third_set_table_fate()
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
		call swe_third_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

char swe_third_update(BYTE* _this) {
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
		}
	}
	data->year++;
	data->current_stage = -1;
	swe_third_subs(_this);
	AddTeamsGroupLeague(_this, SWE_THIRD_NORRLAND_9CF());
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 5; i++) {
		swe_third_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) swe_third_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_third_update
		add esp, 0x4
		ret
	}
}

void swe_third_playoffs_prom(BYTE* _this) {
	char stage_num = 5;
	DWORD v1 = *(DWORD*)_this;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;
	BYTE playoff_teams = 3;

	comp_stats* curr_stage = comp_data;
	BYTE prom_rel[4] = { 0, 1, 0, 0 };

	for (char g = 0; g < 2; g++) {
		vector<cm3_clubs*> clubs;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

		char start_al = (-1 + 3 * g);
		for (char al = start_al; al < start_al + 3; al++) {
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

		for (size_t i = 0; i < playoff_teams; i++) {
			*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i];
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, playoff_teams, pTeams, 1, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), &prom_rel[0],
			year, stage_num, stage_name_id, 0x14, 1, 0, comp_data->f217, -1, 0, 2);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;

		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
	comp_data->current_stage = stage_num - 1;
}

void swe_third_playoffs_rele(BYTE* _this) {
	char stage_num = 7;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 12;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;
	int j = 0;
	for (char al = -1; al < 5; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == BottomPlayoff) {
				*((DWORD*)(&pTeams[2 * j])) = (DWORD)tls.club;
				j++;
			}
		}
	}

	vector<cm3_clubs*> playoff_clubs;
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(SWE_LOWER_9CF());
	vector<cm3_clubs*> promoted;
	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	// Promoted clubs
	int max_to_check = (available_clubs.size() > 24 ? 24 : available_clubs.size());
	for (int i = 0; i < 12; i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* available = available_clubs[availableIdx];
		promoted.push_back(available);
		available_clubs.erase(available_clubs.begin() + availableIdx);
	}
	// Playoff clubs
	max_to_check = (available_clubs.size() > 12 ? 12 : available_clubs.size());
	for (int i = 0; i < 6; i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* available = available_clubs[availableIdx];
		playoff_clubs.push_back(available);
		available_clubs.erase(available_clubs.begin() + availableIdx);
	}

	j = 0;
	shuffle(playoff_clubs.begin(), playoff_clubs.end(), rng);
	for (cm3_clubs* c : playoff_clubs) {
		*((DWORD*)(&pTeams[1 + 2 * j])) = (DWORD)c;
		j++;
	}

	for (int i = 0; i < 12; i++)
	{
		*(DWORD*)(_this + 0xEE + 4 * i) = (DWORD)promoted[i]->ClubID;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

void swe_third_playoffs_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 5) {
			swe_third_playoffs_prom(_this);
			swe_third_playoffs_rele(_this);
		}
	}
}

void __declspec(naked) swe_third_playoffs_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_third_playoffs_create
		add esp, 0x4
		ret
	}
}

void swe_third_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 5) {
		ret_current = 1 + 6 * (current - 1);
		ret_min = 1 + 6 * (min - 1);
		ret_max = 1 + 6 * (max - 1);
	}
	else if (stage < 7) {
		ret_current = 7 + 2 * (current - 1);
		ret_min = 7 + 2 * (min - 1);
		ret_max = 7 + 2 * (max - 1);
	}
	else if (stage == 7) {
		ret_current = 12;
		ret_min = 12;
		ret_max = 12;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) swe_third_reputation_calc_c()
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
		call swe_third_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void swe_third_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(swe_third_vtable->vtable_ptr);
	swe_third_vtable->SetPointer(VTableInitFree, (DWORD)&swe_third_free_c);
	swe_third_vtable->SetPointer(VTableEoSUpdate, (DWORD)&swe_third_update_c);
	swe_third_vtable->SetPointer(VTableFixtures, (DWORD)&swe_third_fixtures_c);
	swe_third_vtable->SetPointer(VTableReputationSetup, (DWORD)&swe_third_reputation_setup_c);
	swe_third_vtable->SetPointer(VTableReputationCalc, (DWORD)&swe_third_reputation_calc_c);
	swe_third_vtable->SetPointer(VTableSubsRounds, (DWORD)&swe_third_subs_c);
	swe_third_vtable->SetPointer(VTableTableFates, (DWORD)&swe_third_set_table_fate);
	swe_third_vtable->SetPointer(VTablePlayoffQual, (DWORD)&swe_third_playoffs_create_c);
	data->year = year;
	data->rules = 0x1c;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 8;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	swe_third_subs(_this);
	AddTeamsGroupLeague(_this, SWE_THIRD_NORRLAND_9CF());
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 5; i++) {
		swe_third_setup_groups(_this, i);
	}
	swe_third_reputation_setup(_this);
}

void setup_swe_third() {
	char* ns_text = "North Svealand";
	char* ns_text_short = "N.S";
	WriteDWORD(0x4B6715 + 1, (DWORD)&ns_text[0]);
	WriteDWORD(0x4B9253 + 1, (DWORD)&ns_text_short[0]);
	char* ss_text = "South Svealand";
	char* ss_text_short = "S.S";
	WriteDWORD(0x4B672F + 1, (DWORD)&ss_text[0]);
	WriteDWORD(0x4B9272 + 1, (DWORD)&ss_text_short[0]);
	char* ng_text = "North Gotaland";
	char* ng_text_short = "N.G";
	WriteDWORD(0x4B6749 + 1, (DWORD)&ng_text[0]);
	WriteDWORD(0x4B9291 + 1, (DWORD)&ng_text_short[0]);
}