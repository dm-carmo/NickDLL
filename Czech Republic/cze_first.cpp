#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

vtable* cze_first_vtable = new vtable((BYTE*)0x9690C4, 0xB4);

int cze_first_7F3220(DWORD a1, DWORD a2) {
	BYTE split_pos = 8;
	WORD stage1_games = 30;
	team_league_stats* tls1 = (team_league_stats*)a1;
	team_league_stats* tls2 = (team_league_stats*)a2;

	BYTE bl = ((BYTE*)tls1->position_history)[stage1_games - 1];
	BYTE al = (bl >= split_pos) + 1;
	bl = ((BYTE*)tls2->position_history)[stage1_games - 1];
	BYTE cl = (bl >= split_pos) + 1;
	return al - cl;
}

void cze_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(cze_first_vtable->vtable_ptr);
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
	DWORD y = -1;
	sub_682300(_this);
}

void cze_first_free(BYTE* _this, BYTE a2) {
	cze_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) cze_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call cze_first_free
		add esp, 0x8
		ret 4
	}
}

void cze_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	*((DWORD*)(_this + 0xA3)) = 0;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 2;
	comp_data->relegations = 1;
	*((DWORD*)(_this + 0xA7)) = 37; // total number of games each team will play

	comp_data->promotes_to = -1;
	comp_data->relegates_to = CZE_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) cze_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call cze_first_subs
		add esp, 0x4
		ret
	}
}

DWORD cze_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	if (stage_idx < 0) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 37;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
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
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday);
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
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
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
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 17), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		// next phase starts here
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 23), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 24), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 28), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 4, 2, 4, 0, 0, 2, 3);

		return (DWORD)pMem;
	}
	else if (stage_idx < 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		*num_rounds = 7;
		*stage_name_id = ChampionshipGroup + stage_idx - 1;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 23), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) cze_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call cze_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void cze_first_prom_rel_update(BYTE* _this, int a2) {
	comp_stats* data = (comp_stats*)_this;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* cze_second = get_loaded_league(CZE_SECOND_9CF());
	v1 = *(DWORD*)cze_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(cze_second);
	process_promotion_relegation_689C80(_this, _this, cze_second, 1, a2, -1, -1);
}

void __declspec(naked) cze_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call cze_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall cze_check_reserve_teams(BYTE* _this) {
	comp_stats* cze_second_data = (comp_stats*)get_loaded_league(CZE_SECOND_9CF());
	// Check teams from L2: main team relegated from L1 - add relegation
	for (WORD num = 0; num < cze_second_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)cze_second_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			// If reserve team was not relegated
			if (table_teams[num].league_fate != Relegated) {
				// If main team is in the first league
				if (ret_club->ClubDivision->ClubCompID == CZE_FIRST_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(CZE_FIRST_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from L2
						team_league_stats* d3_table = (team_league_stats*)cze_second_data->team_league_table;
						for (WORD i = cze_second_data->n_teams - cze_second_data->relegations; i < cze_second_data->n_teams; i++) {
							if (d3_table[i].league_fate == Relegated) {
								d3_table[i].league_fate = Eliminated;
								break;
							}
						}
					}
				}
			}
		}
	}
}

void __fastcall cze_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(CZE_SECOND_9CF());

	vector<cm3_clubs*> available_clubs_a = find_clubs_of_comp(CZE_THIRD_CFL_9CF(), NATION_CZECH_REPUBLIC_9CF());
	for (size_t i = 0; i < available_clubs_a.size(); i++) {
		cm3_clubs* c = available_clubs_a[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != CZE_FIRST_9CF())
		{
			available_clubs_a.erase(available_clubs_a.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> available_clubs_b = find_clubs_of_comp(CZE_THIRD_MFL_9CF(), NATION_CZECH_REPUBLIC_9CF());
	for (size_t i = 0; i < available_clubs_b.size(); i++) {
		cm3_clubs* c = available_clubs_b[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != CZE_FIRST_9CF())
		{
			available_clubs_b.erase(available_clubs_b.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs_a, 1, true);
	vector<cm3_clubs*> promoted_clubs2 = get_random_weighted_clubs(available_clubs_b, 1, true);
	move(promoted_clubs2.begin(), promoted_clubs2.end(), back_inserter(promoted_clubs));

	for (unsigned int j = 0; j < promoted_clubs.size(); j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}
}

void sort_cze_third_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(CZE_THIRD_CFL_9CF());
	vector<cm3_clubs*> d3_mfl_clubs = find_clubs_of_comp(CZE_THIRD_MFL_9CF());
	move(d3_mfl_clubs.begin(), d3_mfl_clubs.end(), back_inserter(available_clubs));
	sort(available_clubs.begin(), available_clubs.end(), compareClubLongitudeInv);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 34) available_clubs[i]->ClubDivision = get_comp(CZE_THIRD_CFL_9CF());
		else available_clubs[i]->ClubDivision = get_comp(CZE_THIRD_MFL_9CF());
	}
}

void __fastcall fake_cze_non_league_relegation(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	vector<cm3_clubs*> cfl_clubs = find_clubs_of_comp(CZE_THIRD_CFL_9CF());
	vector<cm3_clubs*> mfl_clubs = find_clubs_of_comp(CZE_THIRD_MFL_9CF());

	vector<cm3_clubs*> relegated_clubs = get_random_weighted_clubs(cfl_clubs, 6, false);
	vector<cm3_clubs*> relegated_clubs2 = get_random_weighted_clubs(mfl_clubs, 2, false);
	move(relegated_clubs2.begin(), relegated_clubs2.end(), back_inserter(relegated_clubs));

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_CZECH_REPUBLIC_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != CZE_FIRST_9CF()
			&& ret_club->ClubDivision->ClubCompID != CZE_SECOND_9CF())
		{
			available_clubs.erase(available_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size(), true);

	for (cm3_clubs* c : relegated_clubs) {
		cm3_club_comps* bottomDivision = get_comp(A_LOWER_9CF());
		relegate_club_6831A0((BYTE*)c, (DWORD)bottomDivision, 1);
		c->ClubReserveDivision = 0;
	}

	for (cm3_clubs* c : promoted_clubs) {
		cm3_club_comps* topDivision = get_comp(CZE_THIRD_CFL_9CF());
		promote_club_6830B0((BYTE*)c, (DWORD)topDivision, 1);
	}
}

char cze_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;

	BYTE* cze_second = get_loaded_league(CZE_SECOND_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were not relegated from D2 must be professional
	// All teams that were relegated from D2 must be semi-professional
	update_club_pro_status_68A980(cze_second, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(cze_second, SemiProfessional, -3, Relegated, 1);

	DWORD v1 = *(DWORD*)_this;
	cze_check_reserve_teams(_this);
	cze_first_prom_rel_update(_this, 1);

	cze_non_league_promotion(_this);
	fake_cze_non_league_relegation(_this);
	sort_cze_third_clubs();

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
			data->stages[i] = 0;
		}
	}
	data->year++;
	data->current_stage = -1;
	data->num_stages = 0;
	data->stages = 0;
	*((DWORD*)(_this + 0xA7)) = -1;
	cze_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("cze_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("cze_first_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)cze_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(cze_second);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) cze_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call cze_first_update
		add esp, 0x4
		ret
	}
}

void cze_first_split_under(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);

	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	for (int i = 0; i < 8; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)table_teams[i].club;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	DWORD v0 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 1, &num_rounds, &stage_name_id, 0);

	WORD year = comp_data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	short f217 = 3;
	create_league_stage_data(pStage, _this, playoff_teams, pTeams, 1, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
		comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, -1, stage_name_id, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v1 = *(DWORD*)pStage;
	(*(int(__thiscall**)(BYTE*, int))(v1))(pStage, 1);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);

	DWORD* pTeams2 = (DWORD*)cm0102_malloc(playoff_teams * 4);
	for (int i = 0; i < 8; i++) {
		*((DWORD*)(&pTeams2[i])) = (DWORD)table_teams[i + 8].club;
	}

	WORD num_rounds2 = 0;
	WORD stage_name_id2 = 0;
	BYTE* pFixtures2 = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 2, &num_rounds2, &stage_name_id2, 0);

	BYTE* pStage2 = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage2, _this, playoff_teams, pTeams2, 1, (DWORD)(comp_data->competition_db), pFixtures2, num_rounds2,
		comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, -1, stage_name_id2, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v2 = *(DWORD*)pStage2;
	(*(int(__thiscall**)(BYTE*, int))(v2))(pStage2, 1);
	sub_9452CA_free(pTeams2);
	sub_9452CA_free(pFixtures2);

	comp_data->n_rounds = 3;
	*((DWORD*)(_this + 0xA3)) = (DWORD)&cze_first_7F3220;
}

char cze_first_table_split(BYTE* _this, DWORD current_date, int a2) {
	comp_stats* comp_data = (comp_stats*)_this;
	if (a2) {
		if (comp_data->n_rounds == 2) {
			WORD num_teams = comp_data->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
			bool is_finished = true;
			for (int i = 0; i < num_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < 30) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				cze_first_split_under(_this);
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) cze_first_table_split_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call cze_first_table_split
		add esp, 0xc
		ret 8
	}
}

void cze_first_playoff_under(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	int j = 0;
	for (int i = 0; i < total_teams && j < playoff_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == BottomPlayoff) {
			*((DWORD*)(&pTeams[j])) = (DWORD)tls.club;
			j += 2;
		}
	}

	comp_stats* cze_second_data = (comp_stats*)get_loaded_league(CZE_SECOND_9CF());
	total_teams = cze_second_data->n_teams;
	table_teams = (team_league_stats*)(cze_second_data->team_league_table);
	j = 1;
	for (int i = 0; i < total_teams && j < playoff_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[j])) = (DWORD)tls.club;
			j += 2;
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

void cze_first_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		BYTE* cze_second = get_loaded_league(CZE_SECOND_9CF());
		if (cze_second) {
			DWORD v1 = *(DWORD*)cze_second;
			char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(cze_second, 0, 1);
			if (ret != 0) {
				(*(void(__thiscall**)(BYTE*))(v1 + 0x94))(cze_second);
				current++;
				comp_data->current_stage = current;
				if (current == 0) {
					cze_first_playoff_under(_this);
				}
			}
		}
	}
}

void __declspec(naked) cze_first_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call cze_first_playoffs_c
		add esp, 0x4
		ret
	}
}

int cze_first_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* cze_second = get_comp(CZE_SECOND_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club_ptr->ClubDivision == cze_second) {
			comp_stats* cze_second_data = (comp_stats*)get_loaded_league(CZE_SECOND_9CF());
			WORD num_teams = cze_second_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(cze_second_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)cze_second, 0x32);
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

void __declspec(naked) cze_first_set_table_fate()
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
		call cze_first_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void cze_first_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		comp_stats* d2_comp_data = (comp_stats*)get_loaded_league(CZE_SECOND_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == CZE_SECOND_9CF()) {
			ret = (BYTE*)sub_4A4850((BYTE*)d2_comp_data->f8, club);
			if (!ret) return;
			ret_current = 3;
			ret_min = 3;
			ret_max = 3;
		}
		else {
			ret_current = 16;
			ret_min = 16;
			ret_max = 16;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) cze_first_reputation_calc_c()
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
		call cze_first_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void cze_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(cze_first_vtable->vtable_ptr);
	cze_first_vtable->SetPointer(VTableSubsRounds, (DWORD)&cze_first_subs_c);
	cze_first_vtable->SetPointer(VTableInitFree, (DWORD)&cze_first_free_c);
	cze_first_vtable->SetPointer(VTableEoSUpdate, (DWORD)&cze_first_update_c);
	cze_first_vtable->SetPointer(VTableFixtures, (DWORD)&cze_first_fixtures_c);
	cze_first_vtable->SetPointer(VTableLeagueSplit, (DWORD)&cze_first_table_split_c);
	cze_first_vtable->SetPointer(VTableReputationCalc, (DWORD)&cze_first_reputation_calc_c);
	cze_first_vtable->SetPointer(VTablePlayoffQual, (DWORD)&cze_first_playoffs_create);
	cze_first_vtable->SetPointer(VTableTableFates, (DWORD)&cze_first_set_table_fate);
	cze_first_vtable->SetPointer(VTableStageNews, 0x7f3080); // Scotland stage news contains champ/rel group news
	cze_first_vtable->SetPointer(VTablePromRelUpdate, (DWORD)&cze_first_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) cze_first_vtable->SetPointer(VTable21, 0x4110b0);
	data->year = year;
	data->rules = RulesCzech;
	int loaded = sub_687B10(_this, 1);
	if (loaded) {
		if (data->n_rounds != 3) return;
		*((DWORD*)(_this + 0xA3)) = (DWORD)&cze_first_7F3220;
		return;
	}
	data->min_stadium_capacity = 3500;
	data->min_stadium_seats = 3500;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	cze_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("cze_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("cze_first_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void setup_cze_first()
{
}