#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* bel_first_vtable = (DWORD*)0x967940;

void bel_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = bel_first_vtable;
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

void bel_first_free(BYTE* _this, BYTE a2) {
	bel_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) bel_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call bel_first_free
		add esp, 0x8
		ret 4
	}
}

void bel_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	*((DWORD*)(_this + 0xA3)) = 0;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GamesWonTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->tiebreaker_4 = GoalsForAwayTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 2;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = BEL_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) bel_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bel_first_subs
		add esp, 0x4
		ret
	}
}

DWORD bel_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	if (stage_idx < 0) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1 + numberOfLeagueTeams % 2) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 10), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 17), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 24), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 31), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 14), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 21), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 28), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 5), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 19), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 26), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 23), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 30), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 7), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 14), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 21), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 28), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 18), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 25), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 1), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 8), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 15), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 22), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 1), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 15), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 22), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 5), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 26), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 10), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) bel_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call bel_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void __fastcall bel_d2_d3_relegation_2026(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(BEL_SECOND_9CF());

	vector<cm3_clubs*> promoted_clubs;
	comp_stats* comp_data = (comp_stats*)get_loaded_league(BEL_THIRD_VV_9CF());
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Promoted || table_pos.league_fate == Champions) {
			promoted_clubs.push_back(table_pos.club);
		}
	}
	comp_data = (comp_stats*)get_loaded_league(BEL_THIRD_ACFF_9CF());
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Promoted || table_pos.league_fate == Champions) {
			promoted_clubs.push_back(table_pos.club);
		}
	}

	cm3_club_comps* topDivision = get_comp(BEL_SECOND_9CF());
	cm3_club_comps* bottomDivision = get_comp(BEL_THIRD_VV_9CF());
	for (cm3_clubs* club : relegated_clubs) {
		relegate_club_6831A0((BYTE*)club, (DWORD)bottomDivision, 1);
	}
	for (cm3_clubs* club : promoted_clubs) {
		promote_club_6830B0((BYTE*)club, (DWORD)topDivision, 1);
	}
}

void __fastcall bel_d3_d4_relegation_2026(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(BEL_THIRD_VV_9CF());

	vector<cm3_clubs*> promoted_clubs;
	comp_stats* comp_data = (comp_stats*)get_loaded_league(BEL_FOURTH_VV_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Promoted || table_pos.league_fate == Champions) {
				promoted_clubs.push_back(table_pos.club);
			}
		}
	}

	cm3_club_comps* topDivision = get_comp(BEL_THIRD_VV_9CF());
	cm3_club_comps* bottomDivision = get_comp(BEL_FOURTH_VV_9CF());
	for (cm3_clubs* club : relegated_clubs) {
		relegate_club_6831A0((BYTE*)club, (DWORD)bottomDivision, 1);
	}
	for (cm3_clubs* club : promoted_clubs) {
		promote_club_6830B0((BYTE*)club, (DWORD)topDivision, 1);
	}
}

void bel_first_prom_rel_update(BYTE* _this, int a2) {
	comp_stats* data = (comp_stats*)_this;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* bel_second = get_loaded_league(BEL_SECOND_9CF());
	v1 = *(DWORD*)bel_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bel_second);
	process_promotion_relegation_689C80(_this, _this, bel_second, 1, a2, -1, -1);

	BYTE* bel_third_vv = get_loaded_league(BEL_THIRD_VV_9CF());
	v1 = *(DWORD*)bel_third_vv;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bel_third_vv);
	BYTE* bel_third_ac = get_loaded_league(BEL_THIRD_ACFF_9CF());
	v1 = *(DWORD*)bel_third_ac;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bel_third_ac);
	if (data->year == 2026) {
		bel_d2_d3_relegation_2026(_this);
	}
	else {
		process_promotion_relegation_689C80(_this, bel_second, bel_third_vv, 1, a2, -1, -1);
		process_promotion_relegation_689C80(_this, bel_second, bel_third_ac, 1, a2, -1, -1);
	}

	BYTE* bel_fourth_vv = get_loaded_league(BEL_FOURTH_VV_9CF());
	if (bel_fourth_vv) {
		comp_stats* bel_fourth_vv_data = (comp_stats*)bel_fourth_vv;
		v1 = *(DWORD*)bel_fourth_vv;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bel_fourth_vv);
		BYTE* bel_fourth_vv_grp = (BYTE*)bel_fourth_vv_data->stages[0];
		v1 = *(DWORD*)bel_fourth_vv_grp;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bel_fourth_vv_grp);
		if (data->year == 2026) {
			bel_d3_d4_relegation_2026(_this);
		}
		else {
			process_promotion_relegation_689C80(_this, bel_third_vv, bel_fourth_vv, 1, a2, -1, -1);
			process_promotion_relegation_689C80(_this, bel_third_vv, bel_fourth_vv_grp, 1, a2, -1, -1);
		}
	}

	BYTE* bel_fourth_ac = get_loaded_league(BEL_FOURTH_ACFF_9CF());
	if (bel_fourth_ac) {
		comp_stats* bel_fourth_ac_data = (comp_stats*)bel_fourth_ac;
		v1 = *(DWORD*)bel_fourth_ac;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bel_fourth_ac);

		process_promotion_relegation_689C80(_this, bel_third_ac, bel_fourth_ac, 1, a2, -1, -1);
	}
}

void __declspec(naked) bel_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call bel_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall bel_third_vv_relegation(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(BEL_THIRD_VV_9CF());

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(BEL_FOURTH_VV_9CF(), NATION_BELGIUM_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != BEL_FIRST_9CF()
			&& ret_club->ClubDivision->ClubCompID != BEL_SECOND_9CF())
		{
			available_clubs.erase(available_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size(), true);
	for (unsigned int i = 0; i < promoted_clubs.size(); i++)
	{
		cm3_clubs* clubToRelegate = relegated_clubs[i];
		cm3_clubs* available = promoted_clubs[i];
		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = available->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)available, (DWORD)topDivision, 1);
		clubToRelegate->ClubReserveDivision = 0;
	}
}

void __fastcall bel_third_ac_relegation(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(BEL_THIRD_ACFF_9CF());

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(BEL_FOURTH_ACFF_9CF(), NATION_BELGIUM_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != BEL_FIRST_9CF()
			&& ret_club->ClubDivision->ClubCompID != BEL_SECOND_9CF())
		{
			available_clubs.erase(available_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size() + (comp_data->year == 2026 ? 1 : 0), true);

	for (cm3_clubs* c : relegated_clubs) {
		cm3_club_comps* bottomDivision = get_comp(BEL_FOURTH_ACFF_9CF());
		relegate_club_6831A0((BYTE*)c, (DWORD)bottomDivision, 1);
		c->ClubReserveDivision = 0;
	}

	for (cm3_clubs* c : promoted_clubs) {
		cm3_club_comps* topDivision = get_comp(BEL_THIRD_ACFF_9CF());
		promote_club_6830B0((BYTE*)c, (DWORD)topDivision, 1);
	}
}

void __fastcall bel_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs_vv;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(BEL_FOURTH_VV_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				relegated_clubs_vv.push_back(table_pos.club);
			}
		}
	}
	vector<cm3_clubs*> relegated_clubs_ac = get_relegated_teams(BEL_FOURTH_ACFF_9CF());

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_BELGIUM_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != BEL_FIRST_9CF()
			&& ret_club->ClubDivision->ClubCompID != BEL_SECOND_9CF() && ret_club->ClubDivision->ClubCompID != BEL_THIRD_VV_9CF()
			&& ret_club->ClubDivision->ClubCompID != BEL_THIRD_ACFF_9CF())
		{
			available_clubs.erase(available_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs_vv.size() + relegated_clubs_ac.size() + (comp_data->year == 2026 ? 1 : 0), true);

	for (cm3_clubs* c : relegated_clubs_vv) {
		cm3_club_comps* bottomDivision = get_comp(A_LOWER_9CF());
		relegate_club_6831A0((BYTE*)c, (DWORD)bottomDivision, 1);
		c->ClubReserveDivision = 0;
	}

	for (cm3_clubs* c : relegated_clubs_ac) {
		cm3_club_comps* bottomDivision = get_comp(A_LOWER_9CF());
		relegate_club_6831A0((BYTE*)c, (DWORD)bottomDivision, 1);
		c->ClubReserveDivision = 0;
	}

	for (cm3_clubs* c : promoted_clubs) {
		cm3_club_comps* topDivision = comp_data->competition_db;
		promote_club_6830B0((BYTE*)c, (DWORD)topDivision, 1);
	}
}

void __fastcall fake_bel_non_league_promotion(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	vector<cm3_clubs*> vv_clubs = find_clubs_of_comp(BEL_FOURTH_VV_9CF());
	vector<cm3_clubs*> ac_clubs = find_clubs_of_comp(BEL_FOURTH_ACFF_9CF());

	vector<cm3_clubs*> relegated_clubs = get_random_weighted_clubs(vv_clubs, 6, false);
	vector<cm3_clubs*> relegated_clubs2 = get_random_weighted_clubs(ac_clubs, 3, false);
	move(relegated_clubs2.begin(), relegated_clubs2.end(), back_inserter(relegated_clubs));

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_BELGIUM_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != BEL_FIRST_9CF()
			&& ret_club->ClubDivision->ClubCompID != BEL_SECOND_9CF() && ret_club->ClubDivision->ClubCompID != BEL_THIRD_VV_9CF()
			&& ret_club->ClubDivision->ClubCompID != BEL_THIRD_ACFF_9CF())
		{
			available_clubs.erase(available_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size() + (comp_data->year == 2026 ? 1 : 0), true);

	for (cm3_clubs* c : relegated_clubs) {
		cm3_club_comps* bottomDivision = get_comp(A_LOWER_9CF());
		relegate_club_6831A0((BYTE*)c, (DWORD)bottomDivision, 1);
		c->ClubReserveDivision = 0;
	}

	for (cm3_clubs* c : promoted_clubs) {
		cm3_club_comps* topDivision = get_comp(BEL_FOURTH_VV_9CF());
		promote_club_6830B0((BYTE*)c, (DWORD)topDivision, 1);
	}
}

void sort_bel_third_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(BEL_THIRD_VV_9CF());
	vector<cm3_clubs*> d3_acff_clubs = find_clubs_of_comp(BEL_THIRD_ACFF_9CF());
	move(d3_acff_clubs.begin(), d3_acff_clubs.end(), back_inserter(available_clubs));
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 16) available_clubs[i]->ClubDivision = get_comp(BEL_THIRD_VV_9CF());
		else available_clubs[i]->ClubDivision = get_comp(BEL_THIRD_ACFF_9CF());
	}
}

void sort_bel_fourth_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(BEL_FOURTH_VV_9CF());
	vector<cm3_clubs*> d3_acff_clubs = find_clubs_of_comp(BEL_FOURTH_ACFF_9CF());
	move(d3_acff_clubs.begin(), d3_acff_clubs.end(), back_inserter(available_clubs));
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);
	sort(available_clubs.begin(), available_clubs.begin() + 32, compareClubLongitudeInv);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		available_clubs[i]->ClubReserveDivision = 0;
		if (i < 32)
		{
			available_clubs[i]->ClubDivision = get_comp(BEL_FOURTH_VV_9CF());
			if (i < 16) available_clubs[i]->ClubReserveDivision = get_comp(BEL_FOURTH_VV_A_9CF());
			else available_clubs[i]->ClubReserveDivision = get_comp(BEL_FOURTH_VV_B_9CF());
		}
		else available_clubs[i]->ClubDivision = get_comp(BEL_FOURTH_ACFF_9CF());
	}
}

void __fastcall bel_check_reserve_teams(BYTE* _this) {
	comp_stats* bel_second_data = (comp_stats*)get_loaded_league(BEL_SECOND_9CF());
	comp_stats* bel_third_vv_data = (comp_stats*)get_loaded_league(BEL_THIRD_VV_9CF());
	comp_stats* bel_third_ac_data = (comp_stats*)get_loaded_league(BEL_THIRD_ACFF_9CF());
	BYTE* bel_fourth_vv = get_loaded_league(BEL_FOURTH_VV_9CF());
	if (bel_fourth_vv) {
		// Check teams from L4: promoted but main team relegated from L2 - remove promotion + remove one relegation from L3
		// Check teams from L4: main team relegated from L3 - add relegation
		comp_stats* bel_fourth_vv_data = (comp_stats*)bel_fourth_vv;
		comp_stats* curr_stage = bel_fourth_vv_data;
		for (char al = -1; al < 1; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(bel_fourth_vv_data->stages[al]);
			}
			for (WORD num = 0; num < curr_stage->n_teams; num++) {
				team_league_stats* table_teams = (team_league_stats*)curr_stage->team_league_table;
				DWORD is_main_club;
				cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
				// If it is a reserve team
				if (ret_club && !is_main_club)
				{
					team_league_stats* d3_vv_table = (team_league_stats*)bel_third_vv_data->team_league_table;
					// If reserve team from D4 is promoted
					if (table_teams[num].league_fate == Promoted) {
						// If main team is in D2
						if (ret_club->ClubDivision->ClubCompID == BEL_SECOND_9CF()) {
							team_league_stats* main_club_data = get_team_league_stats(BEL_SECOND_9CF(), ret_club);
							// If the main team was relegated
							if (main_club_data->league_fate == Relegated) {
								table_teams[num].league_fate = Eliminated;
								// Do not promote the reserve team, and relegate one less team from the third league
								for (WORD i = bel_third_vv_data->n_teams - bel_third_vv_data->rele_playoff; i < bel_third_vv_data->n_teams; i++) {
									if (d3_vv_table[i].league_fate == Relegated) {
										d3_vv_table[i].league_fate = Eliminated;
										break;
									}
								}
							}
						}
					}
					// If team was not relegated
					else if (table_teams[num].league_fate != Relegated) {
						// If main team is in the third league
						if (ret_club->ClubDivision->ClubCompID == BEL_THIRD_VV_9CF()) {
							team_league_stats* main_club_data = get_team_league_stats(BEL_THIRD_VV_9CF(), ret_club);
							// If the main team was relegated
							if (main_club_data->league_fate == Relegated) {
								// Relegate the reserve team
								table_teams[num].league_fate = Relegated;
							}
						}
						else if (ret_club->ClubDivision->ClubCompID == BEL_THIRD_ACFF_9CF()) {
							team_league_stats* main_club_data = get_team_league_stats(BEL_THIRD_ACFF_9CF(), ret_club);
							// If the main team was relegated
							if (main_club_data->league_fate == Relegated) {
								// Relegate the reserve team
								table_teams[num].league_fate = Relegated;
							}
						}
					}
				}
			}
		}
	}
	BYTE* bel_fourth_ac = get_loaded_league(BEL_FOURTH_ACFF_9CF());
	if (bel_fourth_ac) {
		// Check teams from L4: promoted but main team relegated from L2 - remove promotion + remove one relegation from L3
		// Check teams from L4: main team relegated from L3 - add relegation
		comp_stats* bel_fourth_ac_data = (comp_stats*)bel_fourth_ac;
		for (WORD num = 0; num < bel_fourth_ac_data->n_teams; num++) {
			team_league_stats* table_teams = (team_league_stats*)bel_fourth_ac_data->team_league_table;
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
			// If it is a reserve team
			if (ret_club && !is_main_club)
			{
				team_league_stats* d3_ac_table = (team_league_stats*)bel_third_ac_data->team_league_table;
				// If reserve team from D4 is promoted
				if (table_teams[num].league_fate == Promoted) {
					// If main team is in D2
					if (ret_club->ClubDivision->ClubCompID == BEL_SECOND_9CF()) {
						team_league_stats* main_club_data = get_team_league_stats(BEL_SECOND_9CF(), ret_club);
						// If the main team was relegated
						if (main_club_data->league_fate == Relegated) {
							table_teams[num].league_fate = Eliminated;
							// Do not promote the reserve team, and relegate one less team from the third league
							for (WORD i = bel_third_ac_data->n_teams - bel_third_ac_data->rele_playoff; i < bel_third_ac_data->n_teams; i++) {
								if (d3_ac_table[i].league_fate == Relegated) {
									d3_ac_table[i].league_fate = Eliminated;
									break;
								}
							}
						}
					}
				}
				// If team was not relegated
				else if (table_teams[num].league_fate != Relegated) {
					// If main team is in the third league
					if (ret_club->ClubDivision->ClubCompID == BEL_THIRD_VV_9CF()) {
						team_league_stats* main_club_data = get_team_league_stats(BEL_THIRD_VV_9CF(), ret_club);
						// If the main team was relegated
						if (main_club_data->league_fate == Relegated) {
							// Relegate the reserve team
							table_teams[num].league_fate = Relegated;
						}
					}
					else if (ret_club->ClubDivision->ClubCompID == BEL_THIRD_ACFF_9CF()) {
						team_league_stats* main_club_data = get_team_league_stats(BEL_THIRD_ACFF_9CF(), ret_club);
						// If the main team was relegated
						if (main_club_data->league_fate == Relegated) {
							// Relegate the reserve team
							table_teams[num].league_fate = Relegated;
						}
					}
				}
			}
		}
	}
	// Check teams from L3: promoted but main team relegated from L1 - remove promotion + remove one relegation from L2
	// Check teams from L3: main team relegated from L2 - add relegation + remove one relegation
	for (WORD num = 0; num < bel_third_vv_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)bel_third_vv_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			if (table_teams[num].league_fate == Champions || table_teams[num].league_fate == Promoted) {
				// If main team is in the first league
				if (ret_club->ClubDivision->ClubCompID == BEL_FIRST_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(BEL_FIRST_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Eliminated;
						// Do not promote the reserve team, and relegate one less team from the second league
						team_league_stats* d2_table = (team_league_stats*)bel_second_data->team_league_table;
						for (WORD i = bel_second_data->n_teams - bel_second_data->relegations - bel_second_data->rele_playoff; i < bel_second_data->n_teams; i++) {
							if (d2_table[i].league_fate == Relegated) {
								d2_table[i].league_fate = Eliminated;
								break;
							}
						}
					}
				}

			}
			// If reserve team was not relegated
			else if (table_teams[num].league_fate != Relegated) {
				// If main team is in the second league
				if (ret_club->ClubDivision->ClubCompID == BEL_SECOND_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(BEL_SECOND_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from the third league
						team_league_stats* d3_table = (team_league_stats*)bel_third_vv_data->team_league_table;
						for (WORD i = bel_third_vv_data->n_teams - bel_third_vv_data->rele_playoff; i < bel_third_vv_data->n_teams; i++) {
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
	for (WORD num = 0; num < bel_third_ac_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)bel_third_ac_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			if (table_teams[num].league_fate == Champions || table_teams[num].league_fate == Promoted) {
				// If main team is in the first league
				if (ret_club->ClubDivision->ClubCompID == BEL_FIRST_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(BEL_FIRST_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Eliminated;
						// Do not promote the reserve team, and relegate one less team from the second league
						team_league_stats* d2_table = (team_league_stats*)bel_second_data->team_league_table;
						for (WORD i = bel_second_data->n_teams - bel_second_data->relegations - bel_second_data->rele_playoff; i < bel_second_data->n_teams; i++) {
							if (d2_table[i].league_fate == Relegated) {
								d2_table[i].league_fate = Eliminated;
								break;
							}
						}
					}
				}

			}
			// If reserve team was not relegated
			else if (table_teams[num].league_fate != Relegated) {
				// If main team is in the second league
				if (ret_club->ClubDivision->ClubCompID == BEL_SECOND_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(BEL_SECOND_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from the third league
						team_league_stats* d3_table = (team_league_stats*)bel_third_ac_data->team_league_table;
						for (WORD i = bel_third_ac_data->n_teams - bel_third_ac_data->rele_playoff; i < bel_third_ac_data->n_teams; i++) {
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
	// Check teams from L2: main team relegated from L1 - add relegation + remove one relegation
	for (WORD num = 0; num < bel_second_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)bel_second_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			// If reserve team was not relegated
			if (table_teams[num].league_fate != Relegated) {
				// If main team is in the first league
				if (ret_club->ClubDivision->ClubCompID == BEL_FIRST_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(BEL_FIRST_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from the second league
						team_league_stats* d2_table = (team_league_stats*)bel_second_data->team_league_table;
						for (WORD i = bel_second_data->n_teams - bel_second_data->relegations - bel_second_data->rele_playoff; i < bel_second_data->n_teams; i++) {
							if (d2_table[i].league_fate == Relegated) {
								d2_table[i].league_fate = Eliminated;
								break;
							}
						}
					}
				}
			}
		}
	}
}

char bel_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;

	BYTE* bel_second = get_loaded_league(BEL_SECOND_9CF());
	BYTE* bel_third_vv = get_loaded_league(BEL_THIRD_VV_9CF());
	BYTE* bel_third_ac = get_loaded_league(BEL_THIRD_ACFF_9CF());
	BYTE* bel_fourth_vv = get_loaded_league(BEL_FOURTH_VV_9CF());
	BYTE* bel_fourth_ac = get_loaded_league(BEL_FOURTH_ACFF_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be professional
	update_club_pro_status_68A980(bel_second, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(bel_second, Professional, -3, Relegated, 1);
	// All teams that were not relegated from D3 must be semi-professional
	update_club_pro_status_68A980(bel_third_vv, SemiProfessional, Relegated, -3, 1);
	update_club_pro_status_68A980(bel_third_vv, SemiProfessional, Relegated, -3, 0);
	update_club_pro_status_68A980(bel_third_ac, SemiProfessional, Relegated, -3, 1);
	update_club_pro_status_68A980(bel_third_ac, SemiProfessional, Relegated, -3, 0);
	if (bel_fourth_vv && bel_fourth_ac) {
		comp_stats* bel_fourth_vv_data = (comp_stats*)bel_fourth_vv;
		BYTE* bel_fourth_vv_grp = (BYTE*)bel_fourth_vv_data->stages[0];
		// All teams that were relegated from D4 must be amateur
		update_club_pro_status_68A980(bel_fourth_vv, Amateur, -3, Relegated, 0);
		update_club_pro_status_68A980(bel_fourth_vv_grp, Amateur, -3, Relegated, 0);
		update_club_pro_status_68A980(bel_fourth_ac, Amateur, -3, Relegated, 0);
	}

	DWORD v1 = *(DWORD*)_this;
	bel_check_reserve_teams(_this);
	bel_first_prom_rel_update(_this, 1);

	if (bel_fourth_vv && bel_fourth_ac) {
		bel_non_league_promotion(_this);
	}
	else {
		bel_third_vv_relegation(_this);
		bel_third_ac_relegation(_this);
		fake_bel_non_league_promotion(_this);
	}
	sort_bel_third_clubs();
	sort_bel_fourth_clubs();

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
	bel_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("bel_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("bel_first_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)bel_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bel_second);

	v1 = *(DWORD*)bel_third_vv;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bel_third_vv);

	v1 = *(DWORD*)bel_third_ac;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bel_third_ac);

	if (bel_fourth_vv) {
		v1 = *(DWORD*)bel_fourth_vv;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bel_fourth_vv);
	}

	if (bel_fourth_ac) {
		v1 = *(DWORD*)bel_fourth_ac;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bel_fourth_ac);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) bel_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call bel_first_update
		add esp, 0x4
		ret
	}
}

void bel_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = bel_first_vtable;
	data->year = year;
	data->rules = RulesBelgiumLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded)  return;
	data->min_stadium_capacity = 8000;
	data->min_stadium_seats = 5000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	bel_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("bel_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("bel_first_tv_money"), 0);
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

void setup_bel_first()
{
	WriteVTablePtr(bel_first_vtable, VTableSubsRounds, (DWORD)&bel_first_subs_c);
	WriteVTablePtr(bel_first_vtable, VTableInitFree, (DWORD)&bel_first_free_c);
	WriteVTablePtr(bel_first_vtable, VTableEoSUpdate, (DWORD)&bel_first_update_c);
	WriteVTablePtr(bel_first_vtable, VTableFixtures, (DWORD)&bel_first_fixtures_c);
	WriteVTablePtr(bel_first_vtable, VTablePromRelUpdate, (DWORD)&bel_first_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(bel_first_vtable, VTable21, 0x4110b0);
}