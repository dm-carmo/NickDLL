#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

vtable* aut_first_vtable = new vtable((BYTE*)0x969798, 0xB4);

void aut_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(aut_first_vtable->vtable_ptr);
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

void aut_first_free(BYTE* _this, BYTE a2) {
	aut_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) aut_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call aut_first_free
		add esp, 0x8
		ret 4
	}
}

int aut_first_7F3220(DWORD a1, DWORD a2) {
	BYTE split_pos = 6;
	WORD stage1_games = 22;
	team_league_stats* tls1 = (team_league_stats*)a1;
	team_league_stats* tls2 = (team_league_stats*)a2;

	BYTE bl = ((BYTE*)tls1->position_history)[stage1_games - 1];
	BYTE al = (bl >= split_pos) + 1;
	bl = ((BYTE*)tls2->position_history)[stage1_games - 1];
	BYTE cl = (bl >= split_pos) + 1;
	return al - cl;
}

DWORD aut_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		*num_rounds = 32;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 28), year, Saturday);
		// next phase starts here
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
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx < 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		*num_rounds = 10;
		*stage_name_id = ChampionshipGroup + stage_idx;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) aut_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call aut_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void aut_first_prom_rel_update(BYTE* _this, int a2) {
	comp_stats* data = (comp_stats*)_this;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* aut_second = get_loaded_league(AUT_SECOND_9CF());
	v1 = *(DWORD*)aut_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(aut_second);
	process_promotion_relegation_689C80(_this, _this, aut_second, 1, a2, -1, -1);
}

void __declspec(naked) aut_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call aut_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall aut_check_reserve_teams(BYTE* _this) {
	comp_stats* aut_second_data = (comp_stats*)get_loaded_league(AUT_SECOND_9CF());
	// Check teams from L2: main team relegated from L1 - add relegation
	for (WORD num = 0; num < aut_second_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)aut_second_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			// If reserve team was not relegated
			if (table_teams[num].league_fate != Relegated) {
				// If main team is in the first league
				if (ret_club->ClubDivision->ClubCompID == AUT_FIRST_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(AUT_FIRST_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from L2
						team_league_stats* d3_table = (team_league_stats*)aut_second_data->team_league_table;
						for (WORD i = aut_second_data->n_teams - aut_second_data->relegations; i < aut_second_data->n_teams; i++) {
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

void __fastcall aut_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(AUT_SECOND_9CF());

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(AUT_REGIONAL_9CF(), NATION_AUSTRIA_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != AUT_FIRST_9CF())
		{
			available_clubs.erase(available_clubs.begin() + i);
			i--;
		}
	}
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

void aut_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	*((WORD*)(_this + 0xA7)) = 32; // total number of games each team will play
	*((DWORD*)(_this + 0xA3)) = 0;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->tiebreaker_4 = GamesWonTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 1;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = AUT_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) aut_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call aut_first_subs
		add esp, 0x4
		ret
	}
}

void __fastcall aut_fake_lower_relegation(BYTE* _this)
{
	vector<cm3_clubs*> reg_clubs = find_clubs_of_comp(AUT_REGIONAL_9CF(), NATION_AUSTRIA_9CF());
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_AUSTRIA_9CF());
	unsigned int num_to_swap = reg_clubs.size() / 8;
	if (lower_clubs.size() < num_to_swap) num_to_swap = lower_clubs.size();

	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(lower_clubs, num_to_swap, true);
	vector<cm3_clubs*> relegated_clubs = get_random_weighted_clubs(reg_clubs, num_to_swap, false);

	for (unsigned int j = 0; j < num_to_swap; j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}
}

char aut_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* aut_second = get_loaded_league(AUT_SECOND_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were relegated from D2 must be semi-professional
	update_club_pro_status_68A980(aut_second, SemiProfessional, -3, Relegated, 1);

	DWORD v1 = *(DWORD*)_this;
	aut_check_reserve_teams(_this);
	aut_first_prom_rel_update(_this, 1);

	aut_non_league_promotion(_this);
	aut_fake_lower_relegation(_this);

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
	data->num_stages = 0;
	data->stages = 0;
	*((WORD*)(_this + 0xA7)) = -1;
	aut_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("aut_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("aut_first_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)aut_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(aut_second);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) aut_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call aut_first_update
		add esp, 0x4
		ret
	}
}

void aut_first_split_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE playoff_teams = 6;
	WORD total_teams = data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(data->team_league_table);

	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	for (int i = 0; i < 6; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)table_teams[i].club;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	DWORD v0 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 0, &num_rounds, &stage_name_id, 0);

	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	short f217 = 3;
	create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, -1, stage_name_id, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v1 = *(DWORD*)pStage;
	(*(int(__thiscall**)(BYTE*, int))(v1))(pStage, 1);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);

	DWORD* pTeams2 = (DWORD*)cm0102_malloc(playoff_teams * 4);
	for (int i = 0; i < 6; i++) {
		*((DWORD*)(&pTeams2[i])) = (DWORD)table_teams[i + 6].club;
	}

	WORD num_rounds2 = 0;
	WORD stage_name_id2 = 0;
	BYTE* pFixtures2 = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 1, &num_rounds2, &stage_name_id2, 0);

	BYTE* pStage2 = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage2, _this, playoff_teams, pTeams2, 2, (DWORD)(data->competition_db), pFixtures2, num_rounds2,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, -1, stage_name_id2, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v2 = *(DWORD*)pStage2;
	(*(int(__thiscall**)(BYTE*, int))(v2))(pStage2, 1);
	sub_9452CA_free(pTeams2);
	sub_9452CA_free(pFixtures2);

	data->n_rounds = 4;
	*((DWORD*)(_this + 0xA3)) = (DWORD)&aut_first_7F3220;
}

char aut_first_table_split(BYTE* _this, DWORD current_date, int a2) {
	if (a2) {
		comp_stats* comp_data = (comp_stats*)_this;
		if (comp_data->n_rounds == 2) {
			WORD num_teams = comp_data->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
			bool is_finished = true;
			for (int i = 0; i < num_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < 22) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				aut_first_split_under(_this);
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) aut_first_table_split_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call aut_first_table_split
		add esp, 0xc
		ret 8
	}
}

void aut_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(aut_first_vtable->vtable_ptr);
	aut_first_vtable->SetPointer(VTableInitFree, (DWORD)&aut_first_free_c);
	aut_first_vtable->SetPointer(VTableSubsRounds, (DWORD)&aut_first_subs_c);
	aut_first_vtable->SetPointer(VTableEoSUpdate, (DWORD)&aut_first_update_c);
	aut_first_vtable->SetPointer(VTableFixtures, (DWORD)&aut_first_fixtures_c);
	aut_first_vtable->SetPointer(VTableLeagueSplit, (DWORD)&aut_first_table_split_c);
	aut_first_vtable->SetPointer(VTablePromRelUpdate, (DWORD)&aut_first_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) aut_first_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	data->year = year;
	data->rules = RulesAustria;
	int loaded = sub_687B10(_this, 1);
	if (loaded) {
		if (data->n_rounds != 4) return;
		*((DWORD*)(_this + 0xA3)) = (DWORD)&aut_first_7F3220;
		return;
	}
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	aut_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("aut_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("aut_first_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void setup_aut_first()
{
}