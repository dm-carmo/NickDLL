#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"

vtable* uru_first_vtable = new vtable((BYTE*)0x969798, 0xB4);

void uru_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(uru_first_vtable->vtable_ptr);
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

void uru_first_free(BYTE* _this, BYTE a2) {
	uru_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) uru_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call uru_first_free
		add esp, 0x8
		ret 4
	}
}

void uru_first_aggregate_relegation(BYTE* _this) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	char aggregate_idx = 4;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	comp_stats* aggregate = (comp_stats*)(data->stages[aggregate_idx]);
	team_league_stats* table_teams = (team_league_stats*)(aggregate->team_league_table);
	WORD nteams = aggregate->n_teams;
	for (WORD i = nteams; i > nteams - 3; i--) {
		table_teams[i - 1].league_fate = Relegated;
		staff_history_relegated_86A1C0(staff_hist_ptr, table_teams[i - 1].club, (DWORD)(data->competition_db));
	}
}

int uru_first_set_champion(BYTE* _this) {
	char aggregate_idx = 4;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	comp_stats* aggregate = (comp_stats*)(data->stages[aggregate_idx]);
	team_league_stats* table_teams = (team_league_stats*)(aggregate->team_league_table);

	cm3_clubs* first = 0;
	cm3_clubs* second = 0;
	cm3_clubs* third = 0;

	// no finals
	if (data->num_stages == 5) {
		for (WORD i = 0; i < aggregate->n_teams; i++) {
			if (table_teams[i].league_fate == Champions) first = table_teams[i].club;
			else if (!second) second = table_teams[i].club;
			else if (!third) third = table_teams[i].club;
			else break;
		}
	}
	// semi-final only
	else if (data->num_stages == 6) {
		comp_stats* elim_final = (comp_stats*)(data->stages[5]);
		teams_seeded* elim_final_teams = (teams_seeded*)(elim_final->teams_list);
		WORD elim_final_nteams = elim_final->n_teams;

		for (WORD j = 0; j < elim_final_nteams; j++) {
			teams_seeded t = elim_final_teams[j];
			if (t.f6 == 1) first = t.club;
			else second = t.club;
		}

		for (WORD i = 0; i < aggregate->n_teams; i++) {
			if (table_teams[i].club != first && table_teams[i].club != second && !third) third = table_teams[i].club;
			else if (third) break;
		}
	}
	// semi-final and final
	else {
		comp_stats* elim_final = (comp_stats*)(data->stages[5]);
		teams_seeded* elim_final_teams = (teams_seeded*)(elim_final->teams_list);
		WORD elim_final_nteams = elim_final->n_teams;

		for (WORD j = 0; j < elim_final_nteams; j++) {
			teams_seeded t = elim_final_teams[j];
			if (t.f6 == 2) third = t.club;
		}

		comp_stats* grand_final = (comp_stats*)(data->stages[6]);
		teams_seeded* grand_final_teams = (teams_seeded*)(grand_final->teams_list);
		WORD grand_final_nteams = grand_final->n_teams;

		for (WORD j = 0; j < grand_final_nteams; j++) {
			teams_seeded t = grand_final_teams[j];
			if (t.f6 == 1) first = t.club;
			else second = t.club;
		}

		if (second == third) {
			third = 0;
			for (WORD i = 0; i < aggregate->n_teams; i++) {
				if (table_teams[i].club != first && table_teams[i].club != second && !third) third = table_teams[i].club;
				else if (third) break;
			}
		}
	}

	sub_4AFCE0_add_history_entry(_this, first, second, third, 0);

	// set relegated teams
	uru_first_aggregate_relegation(_this);

	return 0;
}

void __declspec(naked) uru_first_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_first_set_champion
		add esp, 0x4
		ret 0
	}
}

int uru_first_last_positions(BYTE* _this) {
	char aggregate_idx = 4;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	comp_stats* aggregate = (comp_stats*)(data->stages[aggregate_idx]);
	team_league_stats* table_teams = (team_league_stats*)(aggregate->team_league_table);

	cm3_clubs* first_1 = 0;
	cm3_clubs* second_2 = 0;
	cm3_clubs* aggr_3 = 0;
	cm3_clubs* third_4 = 0;
	cm3_clubs* interm_5 = 0;

	// no finals -> second_2 and aggr_3 by aggregate positions
	if (data->num_stages == 5) {
		for (WORD i = 0; i < aggregate->n_teams; i++) {
			if (table_teams[i].league_fate == Champions) first_1 = table_teams[i].club;
			else if (!second_2) second_2 = table_teams[i].club;
			else if (!aggr_3) aggr_3 = table_teams[i].club;
			else break;
		}
	}
	// semi-final only -> aggr_3 by aggregate positions
	else if (data->num_stages == 6) {
		comp_stats* elim_final = (comp_stats*)(data->stages[5]);
		teams_seeded* elim_final_teams = (teams_seeded*)(elim_final->teams_list);
		WORD elim_final_nteams = elim_final->n_teams;

		for (WORD j = 0; j < elim_final_nteams; j++) {
			teams_seeded t = elim_final_teams[j];
			if (t.f6 == 1) first_1 = t.club;
			else second_2 = t.club;
		}

		for (WORD i = 0; i < aggregate->n_teams; i++) {
			if (table_teams[i].club != first_1 && table_teams[i].club != second_2 && !aggr_3) aggr_3 = table_teams[i].club;
			else if (aggr_3) break;
		}
	}
	// semi-final and final -> aggr_3 by aggregate position
	else {
		comp_stats* elim_final = (comp_stats*)(data->stages[5]);
		teams_seeded* elim_final_teams = (teams_seeded*)(elim_final->teams_list);
		WORD elim_final_nteams = elim_final->n_teams;

		for (WORD j = 0; j < elim_final_nteams; j++) {
			teams_seeded t = elim_final_teams[j];
			if (t.f6 == 2) third_4 = t.club;
		}

		comp_stats* grand_final = (comp_stats*)(data->stages[6]);
		teams_seeded* grand_final_teams = (teams_seeded*)(grand_final->teams_list);
		WORD grand_final_nteams = grand_final->n_teams;

		for (WORD j = 0; j < grand_final_nteams; j++) {
			teams_seeded t = grand_final_teams[j];
			if (t.f6 == 1) first_1 = t.club;
			else second_2 = t.club;
		}

		// if final was repeat of final, fill in aggr_3 instead
		if (second_2 == third_4) {
			third_4 = 0;
			for (WORD i = 0; i < aggregate->n_teams; i++) {
				if (table_teams[i].club != first_1 && table_teams[i].club != second_2 && !aggr_3) aggr_3 = table_teams[i].club;
				else if (aggr_3) break;
			}
		}
		// otherwise, check if third_4 is best aggregate and fill appropriately
		else {
			for (WORD i = 0; i < aggregate->n_teams; i++) {
				if (table_teams[i].club != first_1 && table_teams[i].club != second_2 && !aggr_3) aggr_3 = table_teams[i].club;
				if (aggr_3 == third_4) {
					third_4 = 0;
				}
				if (aggr_3) break;
			}
		}
	}

	comp_stats* interm_final = (comp_stats*)(data->stages[3]);
	teams_seeded* interm_final_teams = (teams_seeded*)(interm_final->teams_list);
	WORD interm_final_nteams = interm_final->n_teams;

	cm3_clubs* interm_bak = 0;
	for (WORD j = 0; j < interm_final_nteams; j++) {
		teams_seeded t = interm_final_teams[j];
		if (t.f6 == 1) interm_5 = t.club;
		else interm_bak = t.club;
	}

	vector<cm3_clubs*> clubs;
	if (first_1 && !vector_contains_element(clubs, first_1)) clubs.push_back(first_1);
	if (second_2 && !vector_contains_element(clubs, second_2)) clubs.push_back(second_2);
	if (aggr_3 && !vector_contains_element(clubs, aggr_3)) clubs.push_back(aggr_3);
	if (third_4 && !vector_contains_element(clubs, third_4)) clubs.push_back(third_4);
	if (interm_5 && !vector_contains_element(clubs, interm_5)) clubs.push_back(interm_5);
	for (WORD i = 0; i < aggregate->n_teams; i++) {
		cm3_clubs* aggr_club = table_teams[i].club;
		if (!vector_contains_element(clubs, aggr_club)) clubs.push_back(aggr_club);
	}

	if (clubs.size() != aggregate->n_teams)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
	}

	for (size_t i = 0; i < clubs.size(); i++) {
		clubs[i]->ClubLastDivision = data->competition_db;
		clubs[i]->ClubLastPosition = (char)i + 1;
	}

	comp_stats* uru_super = (comp_stats*)get_loaded_league(URU_SUPER_CUP_9CF());
	teams_seeded* teams = (teams_seeded*)uru_super->teams_list;
	teams[0].club = first_1;
	if (first_1 != interm_5) teams[1].club = interm_5;
	else teams[1].club = interm_bak;

	return 1;
}

void __declspec(naked) uru_first_last_positions_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_first_last_positions
		add esp, 0x4
		ret
	}
}

void uru_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 1;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = URU_SECOND_9CF();

	comp_data->f217 = 0x2;
	comp_data->f82 = 2;
	comp_data->max_bench = 9;
	comp_data->max_subs = 5;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) uru_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_first_subs
		add esp, 0x4
		ret
	}
}

int uru_first_add_teams(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;
	DWORD* all_teams = comp_data->teams2;
	if (all_teams) sub_9452CA_free(all_teams);

	// Count the number of teams first, as the code really expects us to know up front
	vector<cm3_clubs*> d1_clubs = find_clubs_of_comp(CompID);
	comp_data->teams2 = (DWORD*)cm0102_malloc(d1_clubs.size() * 4);
	comp_data->n_teams = (WORD)d1_clubs.size();

	for (WORD i = 0; i < comp_data->n_teams; i++)
	{
		*((DWORD*)(&comp_data->teams2[i])) = (DWORD)d1_clubs[i];
	}

	comp_data->team_league_table = (DWORD*)cm0102_malloc(comp_data->n_teams * league_team_list_sz);
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < comp_data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)(comp_data->teams2[i]);
		add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

int uru_first_vtable2(BYTE* _this, BYTE* round_data, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	sub_685D30(_this, round_data, a3);
	char stage_num = 4;
	WORD year = comp_data->year;

	char curr_stage = *(char*)(round_data + 0x42);
	if (curr_stage < 1)
	{
		DWORD* f8 = comp_data->f8;
		comp_data->f8 = 0;
		*(BYTE*)(round_data + 0x42) = stage_num;
		sub_685D30(_this, round_data, a3);
		*(BYTE*)(round_data + 0x42) = curr_stage;
		comp_data->f8 = f8;
	}

	return 1;
}

void __declspec(naked) uru_first_vtable2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uru_first_vtable2
		add esp, 0xc
		ret 0x8
	}
}

DWORD uru_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = Apertura;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 26), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 12), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 3), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 10), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = Clausura;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 27), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 24), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx < 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = ((comp_stats*)_this);
		WORD year = data->year;
		*num_rounds = 7;
		if (stage_idx == 1) *stage_name_id = IntermedioGroupA;
		else *stage_name_id = IntermedioGroupB;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 31), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 12), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 19), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 7, 26), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 3) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		*num_rounds = 1;
		*stage_name_id = IntermedioFinal;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 27), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 2), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, None, 8, FixedTeamOrderInCup | Penalties | ExtraTime, NoTiebreak, 5, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 5) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		*num_rounds = 1;
		*stage_name_id = EliminationFinal;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, None, 8, FixedTeamOrderInCup | Penalties | ExtraTime, NoTiebreak, 5, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 6) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		*num_rounds = 1;
		*stage_name_id = GrandFinal;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, None, 8, FixedTeamOrderInCup | NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 5, 2, 1, 2, 0, 0, 2, 7, 0, prizeMoneyFile.GetInt("uru_first_final_win"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) uru_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uru_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

DWORD uru_first_fixtures_dummy(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	if (stage_idx < 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = ((comp_stats*)_this);
		WORD year = data->year;
		*num_rounds = 1;
		if (stage_idx == 1) *stage_name_id = IntermedioGroupA;
		else *stage_name_id = IntermedioGroupB;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 11), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 17), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, NoTiebreak, NoTiebreak, 5, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}

	return 0;
}

void uru_first_prom_rel_update(BYTE* _this, int a2) {
	comp_stats* data = (comp_stats*)_this;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* uru_second = get_loaded_league(URU_SECOND_9CF());
	comp_stats* uru_second_data = (comp_stats*)uru_second;
	v1 = *(DWORD*)uru_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(uru_second);
	process_promotion_relegation_689C80(_this, (BYTE*)data->stages[4], (BYTE*)uru_second_data->stages[2], 1, a2, -1, -1);
}

void __declspec(naked) uru_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call uru_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void uru_first_setup_close(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE idx = 0;
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < data->n_teams; i++)
	{
		*((DWORD*)(&pTeams[i])) = all_teams[i];
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

void uru_first_intermed_finals_setup(BYTE* _this) {
	char stage_num = 3;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	BYTE playoff_teams = 2;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = stage_num;
}

void uru_first_setup_intermed(BYTE* _this) {
	char stage_num = 1;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE playoff_teams = 2;
	DWORD* stages_arr = comp_data->stages;

	for (int g = 0; g < 2; g++) {
		vector<cm3_clubs*> clubs;
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)uru_first_fixtures_dummy(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
		BYTE* pStage = (BYTE*)cm0102_new(0xB2);
		create_cup_stage_data(pStage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
	uru_first_intermed_finals_setup(_this);
}

void uru_first_league_table(BYTE* _this) {
	BYTE idx = 4;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	DWORD* pTeams = (DWORD*)cm0102_malloc(data->n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < data->n_teams; i++)
	{
		*((DWORD*)(&pTeams[i])) = all_teams[i];
	}
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	char prom_rel[4] = { 0, 0, 0, 0 };
	short f217 = 0;
	create_league_stage_data(pStage, _this, (short)data->n_teams, pTeams, 0, (DWORD)(data->competition_db), pFixtures, 30,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &prom_rel[0],
		year, idx, stage_name_id, data->f81, 1, 0, f217, -1, 0, data->f225);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void __fastcall uru_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(URU_SECOND_9CF());
	comp_stats* curr_stage = (comp_stats*)comp_data->stages[2];
	for (WORD num = 0; num < curr_stage->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
		if (table_pos.league_fate == Relegated) {
			relegated_clubs.push_back(table_pos.club);
		}
	}

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_URUGUAY_9CF());
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size(), true);

	for (unsigned int j = 0; j < promoted_clubs.size(); j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}
}

char uru_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* uru_second = get_loaded_league(URU_SECOND_9CF());
	comp_stats* uru_second_data = (comp_stats*)uru_second;

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980((BYTE*)data->stages[4], Professional, Relegated, -3, 1);
	update_club_pro_status_68A980((BYTE*)data->stages[4], Professional, -3, Relegated, 1);
	// All teams that were relegated from D2 must be semi-professional
	// All teams that were not relegated from D2 must be professional
	update_club_pro_status_68A980((BYTE*)uru_second_data->stages[2], Professional, Relegated, -3, 1);
	update_club_pro_status_68A980((BYTE*)uru_second_data->stages[2], SemiProfessional, -3, Relegated, 0);

	DWORD v1 = *(DWORD*)_this;
	uru_first_prom_rel_update(_this, 1);

	uru_non_league_promotion(_this);

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
	data->num_stages = 7;
	uru_first_subs(_this);
	uru_first_add_teams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("uru_first_tv_money"), 0);
	sub_6835C0(_this);
	uru_first_setup_close(_this);
	uru_first_setup_intermed(_this);
	uru_first_league_table(_this);
	sub_6827D0(_this, 0);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)uru_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(uru_second);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) uru_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_first_update
		add esp, 0x4
		ret
	}
}

void uru_first_intermed_teams(BYTE* _this) {
	char stage_num = 1;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE playoff_teams = 8;
	char prom_rel[4] = { 0, 1, 0, 0 };
	vector<cm3_clubs*> clubs;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	BYTE group_ids[16] = { 0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0 };

	for (BYTE g = 0; g < 2; g++) {
		comp_stats* stage = (comp_stats*)(comp_data->stages[stage_num]);
		DWORD v2 = *(DWORD*)stage;
		(*(int(__thiscall**)(BYTE*, int a2))(v2))((BYTE*)stage, 1);
		comp_data->stages[stage_num] = 0;

		// Create the new stage
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
		for (size_t i = 0, j = 0; i < total_teams && j < playoff_teams; i++) {
			if (group_ids[i] != g) continue;
			*((DWORD*)(&pTeams[j++])) = (DWORD)table_teams[i].club;
		}

		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, playoff_teams, pTeams, 1, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, &comp_data->tiebreaker_1, &prom_rel[0],
			year, stage_num, stage_name_id, 0x14, 1, 0, comp_data->f217, -1, 0, 2);
		*((DWORD*)(&stages_arr[stage_num])) = (DWORD)pStage;
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		stage_num++;
	}
}

void uru_first_intermed_final_teams(BYTE* _this) {
	char stage_num = 3;
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	comp_stats* playoff = (comp_stats*)data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	vector<cm3_clubs*> clubs;
	for (char al = 1; al < 3; al++) {
		comp_stats* curr_stage = (comp_stats*)(data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == Qualified1 || tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
				break;
			}
		}
	}

	for (char i = 0; i < playoff_teams; i++) {
		teams[i].club = clubs[i];
		teams[i].seeding = i + 1;
	}
}

char uru_first_table_split(BYTE* _this, DWORD current_date, int a2) {
	if (a2) {
		comp_stats* comp_data = (comp_stats*)_this;
		WORD year = comp_data->year;
		// check if can start Intermedio
		char intermed_id = 1;
		char intermed_id2 = 3;
		comp_stats* intermed = (comp_stats*)comp_data->stages[intermed_id];
		bool open_check = false;
		if (*(DWORD*)intermed == 0x969468) { // default cup vtable
			teams_seeded* intermed_teams = (teams_seeded*)intermed->teams_list;
			open_check = !intermed_teams[0].club;
		}
		else {
			team_league_stats* table = (team_league_stats*)(intermed->team_league_table);
			if (!table) open_check = false;
			else open_check = !table[0].club;
		}
		if (open_check) {
			bool is_finished = true;
			WORD total_teams = comp_data->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < 15) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				uru_first_intermed_teams(_this);
			}
		}
		// check if can start Intermedio final
		if (*(DWORD*)intermed == 0x96D0F0) { // default league vtable
			comp_stats* intermed_finals = (comp_stats*)comp_data->stages[intermed_id2];
			teams_seeded* intermed_finals_teams = (teams_seeded*)intermed_finals->teams_list;
			if (!intermed_finals_teams[0].club) {
				bool is_finished = true;
				WORD total_teams = intermed->n_teams;
				team_league_stats* table_teams = (team_league_stats*)(intermed->team_league_table);
				if (table_teams)
				{
					for (int i = 0; i < total_teams; i++) {
						team_league_stats tls = table_teams[i];
						if (tls.games < 7) {
							is_finished = false;
							break;
						}
					}
					if (is_finished)
					{
						comp_stats* intermed2 = (comp_stats*)comp_data->stages[intermed_id + 1];
						total_teams = intermed2->n_teams;
						table_teams = (team_league_stats*)(intermed2->team_league_table);
						for (int i = 0; i < total_teams; i++) {
							team_league_stats tls = table_teams[i];
							if (tls.games < 7) {
								is_finished = false;
								break;
							}
						}
						if (is_finished) {
							uru_first_intermed_final_teams(_this);
						}
					}
				}
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) uru_first_table_split_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uru_first_table_split
		add esp, 0xc
		ret 8
	}
}

int uru_first_table_fates(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	comp_stats* aggregate = (comp_stats*)(comp_data->stages[4]);
	team_league_stats* aggr_table = (team_league_stats*)(aggregate->team_league_table);
	WORD aggr_teams = aggregate->n_teams;

	if (stage == -1) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		for (int i = 0; i < num_teams; i++) {
			if (aggr_table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), EliminationFinal, None, 0x1E);
				aggr_table[i].league_fate = TopPlayoff;
				return 0;
			default:
				return 0;
			}
		}
	}
	else if (stage == 0) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		for (int i = 0; i < num_teams; i++) {
			if (aggr_table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), EliminationFinal, None, 0x1E);
				aggr_table[i].league_fate = TopPlayoff;
				return 0;
			default:
				return 0;
			}
		}
	}
	else if (stage < 3) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[stage]);
		WORD num_teams = comp_data->n_teams;
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), IntermedioFinal, None, 0x1E);
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 3) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		for (char al = 1; al < 3; al++) {
			comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
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
	else if (stage == 5) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		for (int i = 0; i < aggr_teams; i++) {
			if (aggr_table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), GrandFinal, None, 0x1E);
				*a5 = 1;
				return 0;
			case Promoted:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
				return 0;
			default:
				staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
				return 0;
			}
		}
	}
	else if (stage == 6) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		for (int i = 0; i < aggr_teams; i++) {
			if (aggr_table[i].club != club) continue;
			switch (fate) {
			case TopPlayoff:
				staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
				aggr_table[i].league_fate = Champions;
				*a5 = 1;
				return 0;
			case BottomPlayoff:
				staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
				aggr_table[i].league_fate = Eliminated;
				return 0;
			case Promoted:
				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
				return 0;
			default:
				staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
				aggr_table[i].league_fate = Eliminated;
				return 0;
			}
		}
	}
	return 0;
}

void __declspec(naked) uru_first_table_fates_c()
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
		call uru_first_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

void uru_first_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	WORD year = comp_data->year;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 1) {
		// do nothing
	}
	else if (stage < 3) {
		ret_current = 1 + 2 * (current - 1);
		ret_min = 1 + 2 * (min - 1);
		if (max < 2) ret_max = 2;
		else ret_max = 1 + 2 * (max - 1);
	}
	else if (stage == 3) {
		// do nothing
	}
	else if (stage == 5) {
		// do nothing
	}
	else if (stage == 6) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) uru_first_reputation_calc_c()
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
		call uru_first_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void uru_first_playoffs_part1(BYTE* _this) {
	char stage_num = 5;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;

	comp_stats* aggregate = (comp_stats*)(comp_data->stages[4]);
	team_league_stats* aggr_table = (team_league_stats*)(aggregate->team_league_table);
	WORD aggr_teams = aggregate->n_teams;

	vector<cm3_clubs*> clubs;

	for (WORD i = 0; i < aggr_teams; i++) {
		if (aggr_table[i].league_fate == TopPlayoff) {
			clubs.push_back(aggr_table[i].club);
		}
	}

	// same club won both, so they are champions
	if (clubs.size() < 2) {
		cm3_clubs* club = clubs[0];
		BYTE* staff_hist_ptr = (BYTE*)*staff_history;
		comp_data->num_stages = 5;
		if (comp_data->current_stage >= stage_num) comp_data->current_stage = stage_num - 1;
		staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));

		for (WORD i = 0; i < aggr_teams; i++) {
			if (aggr_table[i].club == club) {
				aggr_table[i].league_fate = Champions;
				// give club the final win money
				int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
				AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("uru_first_final_win"));
				AddMoneyFromComp(_this, (BYTE*)club, prizeMoneyFile.GetInt("uru_first_final_win"), 0, 1, None, 0, -2);
				break;
			}
		}
	}
	else {
		BYTE playoff_teams = 2;
		DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

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
}

void uru_first_playoffs_part2(BYTE* _this) {
	char stage_num = 6;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;

	comp_stats* aggregate = (comp_stats*)(comp_data->stages[4]);
	team_league_stats* aggr_table = (team_league_stats*)(aggregate->team_league_table);
	WORD aggr_teams = aggregate->n_teams;

	comp_stats* grand_final = (comp_stats*)(comp_data->stages[5]);

	if (!grand_final) {
		comp_data->num_stages = 5;
		if (comp_data->current_stage >= stage_num - 1) comp_data->current_stage = stage_num - 2;
		return;
	}

	teams_seeded* grand_final_teams = (teams_seeded*)(grand_final->teams_list);
	WORD grand_final_nteams = grand_final->n_teams;

	vector<cm3_clubs*> clubs;

	for (WORD j = 0; j < grand_final_nteams; j++) {
		teams_seeded t = grand_final_teams[j];
		if (t.f6 == 1) {
			clubs.push_back(t.club);
		}
		else for (WORD i = 0; i < aggr_teams; i++) {
			if (aggr_table[i].club == t.club) {
				aggr_table[i].league_fate = Eliminated;
				break;
			}
		}
	}

	// final winner is top of aggregate table so they are champions
	if (aggr_table[0].club == clubs[0]) {
		cm3_clubs* club = clubs[0];
		BYTE* staff_hist_ptr = (BYTE*)*staff_history;
		comp_data->num_stages = 6;
		if (comp_data->current_stage >= stage_num) comp_data->current_stage = stage_num - 1;
		staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
		aggr_table[0].league_fate = Champions;
		// give club the final win money
		int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
		AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("uru_first_final_win"));
		AddMoneyFromComp(_this, (BYTE*)club, prizeMoneyFile.GetInt("uru_first_final_win"), 0, 1, None, 0, -2);
	}
	else {
		aggr_table[0].league_fate = TopPlayoff;
		clubs.push_back(aggr_table[0].club);

		BYTE playoff_teams = 2;
		DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

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
}

void uru_first_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 5) {
			uru_first_playoffs_part1(_this);
		}
		else if (current == 6) {
			uru_first_playoffs_part2(_this);
		}
	}
}

void __declspec(naked) uru_first_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_first_playoffs_c
		add esp, 0x4
		ret
	}
}

void uru_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(uru_first_vtable->vtable_ptr);
	uru_first_vtable->SetPointer(VTableSubsRounds, (DWORD)&uru_first_subs_c);
	uru_first_vtable->SetPointer(VTableInitFree, (DWORD)&uru_first_free_c);
	uru_first_vtable->SetPointer(VTableEoSUpdate, (DWORD)&uru_first_update_c);
	uru_first_vtable->SetPointer(VTableFixtures, (DWORD)&uru_first_fixtures_c);
	uru_first_vtable->SetPointer(VTablePromRelUpdate, (DWORD)&uru_first_prom_rel_update_c);
	uru_first_vtable->SetPointer(VTableSetChampion, (DWORD)&uru_first_set_champion_c);
	uru_first_vtable->SetPointer(VTablePostMatchUpdate, (DWORD)&uru_first_vtable2_c);
	uru_first_vtable->SetPointer(VTableUpdateLastDivision, (DWORD)&uru_first_last_positions_c);
	uru_first_vtable->SetPointer(VTableLeagueSplit, (DWORD)&uru_first_table_split_c);
	uru_first_vtable->SetPointer(VTableReputationCalc, (DWORD)&uru_first_reputation_calc_c);
	uru_first_vtable->SetPointer(VTableTableFates, (DWORD)&uru_first_table_fates_c);
	uru_first_vtable->SetPointer(VTablePlayoffQual, (DWORD)&uru_first_playoffs_create);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) uru_first_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	data->year = year;
	data->rules = RulesUruguay;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 7;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	uru_first_subs(_this);
	uru_first_add_teams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("uru_first_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	uru_first_setup_close(_this);
	uru_first_setup_intermed(_this);
	uru_first_league_table(_this);
	sub_6827D0(_this, 0);
	league_reputation_setup_generic_68A850(_this);
}

void setup_uru_first()
{
	char* interm_a = "Intermediate Group A";
	char* interm_a_short = "Interm Grp A";
	WriteDWORD(0x4B5648 + 1, (DWORD)&interm_a[0]); // f3
	WriteDWORD(0x4B855f + 1, (DWORD)&interm_a_short[0]);

	char* interm_b = "Intermediate Group B";
	char* interm_b_short = "Interm Grp B";
	WriteDWORD(0x4B5662 + 1, (DWORD)&interm_b[0]); // f4
	WriteDWORD(0x4B8569 + 1, (DWORD)&interm_b_short[0]);

	char* interm_final = "Intermediate Final";
	char* interm_final_short = "Interm Final";
	WriteDWORD(0x4B57e8 + 1, (DWORD)&interm_final[0]); // 126
	WriteDWORD(0x4B866d + 1, (DWORD)&interm_final_short[0]);

	char* interm = "Intermediate Stage";
	char* interm_short = "Interm";
	WriteDWORD(0x4B58d2 + 1, (DWORD)&interm[0]); // 157
	WriteDWORD(0x4B871e + 1, (DWORD)&interm_short[0]);
}