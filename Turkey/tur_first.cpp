#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* tur_first_vtable = (DWORD*)0x97052C;

// prize money for win/draw/loss
int tur_first_money_after_match(BYTE* _this, BYTE* a2, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	char al, bl, cl;
	cm3_clubs* club_win = 0;
	cm3_clubs* club_loss = 0;
	al = *(char*)(a2 + 0x47);
	bl = *(char*)(a2 + 0x42);
	if (al == -1) {
		al = *(char*)(a2 + 0x43);
		cl = *(char*)(a2 + 0x44);
	}
	else cl = *(char*)(a2 + 0x48);
	if (al == cl) {
		cm3_clubs* club1 = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
		cm3_clubs* club2 = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
	}
	else if (al > cl) {
		club_win = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
		club_loss = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
	}
	else {
		club_win = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
		club_loss = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
	}
	if (club_win && club_loss) {
		int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club_win);
		AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("tur_first_prize_per_win"));
		AddMoneyFromComp(_this, (BYTE*)club_win, prizeMoneyFile.GetInt("tur_first_prize_per_win"), 0, -1, 0, a2, -2);
		ret = sub_5A0590(ae2a38_ptr, (BYTE*)club_loss);
		AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("tur_first_prize_per_loss"));
		AddMoneyFromComp(_this, (BYTE*)club_loss, prizeMoneyFile.GetInt("tur_first_prize_per_loss"), 0, -1, 0, a2, -2);
	}
	else {
		cm3_clubs* club1 = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
		int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club1);
		AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("tur_first_prize_per_draw"));
		AddMoneyFromComp(_this, (BYTE*)club1, prizeMoneyFile.GetInt("tur_first_prize_per_draw"), 0, -1, 0, a2, -2);
		cm3_clubs* club2 = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
		ret = sub_5A0590(ae2a38_ptr, (BYTE*)club2);
		AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("tur_first_prize_per_draw"));
		AddMoneyFromComp(_this, (BYTE*)club2, prizeMoneyFile.GetInt("tur_first_prize_per_draw"), 0, -1, 0, a2, -2);
	}
	return sub_685D30(_this, a2, a3);
}

void __declspec(naked) tur_first_money_after_match_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call tur_first_money_after_match
		add esp, 0xc
		ret 8
	}
}

void tur_first_subs(BYTE* _this)
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
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 3;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = TUR_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) tur_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call tur_first_subs
		add esp, 0x4
		ret
	}
}

void __fastcall tur_d3_d4_relegation_2026(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;
	comp_stats* comp_data = (comp_stats*)get_loaded_league(TUR_THIRD_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				relegated_clubs.push_back(table_pos.club);
			}
		}
	}

	vector<cm3_clubs*> promoted_clubs;
	comp_data = (comp_stats*)get_loaded_league(TUR_FOURTH_9CF());
	curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Promoted) {
				promoted_clubs.push_back(table_pos.club);
			}
		}
	}

	cm3_club_comps* topDivision = get_comp(TUR_THIRD_9CF());
	cm3_club_comps* bottomDivision = get_comp(TUR_FOURTH_9CF());
	for (cm3_clubs* club : relegated_clubs) {
		relegate_club_6831A0((BYTE*)club, (DWORD)bottomDivision, 1);
	}
	for (cm3_clubs* club : promoted_clubs) {
		promote_club_6830B0((BYTE*)club, (DWORD)topDivision, 1);
	}
}

void tur_first_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* tur_second = get_loaded_league(TUR_SECOND_9CF());
	v1 = *(DWORD*)tur_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(tur_second);
	process_promotion_relegation_689C80(_this, _this, tur_second, 1, a2, -1, -1);

	BYTE* tur_third = get_loaded_league(TUR_THIRD_9CF());
	comp_stats* tur_third_data = (comp_stats*)tur_third;
	v1 = *(DWORD*)tur_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(tur_third);

	BYTE* tur_third_grp = (BYTE*)tur_third_data->stages[0];

	process_promotion_relegation_689C80(_this, tur_second, tur_third, 1, a2, -1, -1);
	process_promotion_relegation_689C80(_this, tur_second, tur_third_grp, 1, a2, -1, -1);

	BYTE* tur_fourth = get_loaded_league(TUR_FOURTH_9CF());
	if (tur_fourth) {
		comp_stats* tur_fourth_data = (comp_stats*)tur_fourth;
		v1 = *(DWORD*)tur_fourth;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(tur_fourth);
		if (tur_fourth_data->year == 2026) {
			tur_d3_d4_relegation_2026(_this);
		}
		else {
			process_promotion_relegation_689C80(_this, tur_third, tur_fourth, 1, a2, -1, -1);

			for (int i = 0; i < 2; i++)
			{
				BYTE* tur_fourth_grp = (BYTE*)tur_fourth_data->stages[i];
				process_promotion_relegation_689C80(_this, tur_third, tur_fourth_grp, 1, a2, -1, -1);
			}

			process_promotion_relegation_689C80(_this, tur_third_grp, tur_fourth, 1, a2, -1, -1);
			for (int i = 0; i < 2; i++)
			{
				BYTE* tur_fourth_grp = (BYTE*)tur_fourth_data->stages[i];
				process_promotion_relegation_689C80(_this, tur_third_grp, tur_fourth_grp, 1, a2, -1, -1);
			}
		}
	}
}

void __declspec(naked) tur_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call tur_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall tur_third_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(TUR_THIRD_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				relegated_clubs.push_back(table_pos.club);
			}
		}
	}

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(TUR_FOURTH_9CF(), NATION_TURKEY_9CF());
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size() + (comp_data->year == 2026 ? 1 : 0), true);

	for (cm3_clubs* c : relegated_clubs) {
		cm3_club_comps* bottomDivision = get_comp(TUR_FOURTH_9CF());
		relegate_club_6831A0((BYTE*)c, (DWORD)bottomDivision, 1);
		c->ClubReserveDivision = 0;
	}

	for (cm3_clubs* c : promoted_clubs) {
		cm3_club_comps* topDivision = get_comp(TUR_THIRD_9CF());
		promote_club_6830B0((BYTE*)c, (DWORD)topDivision, 1);
	}
}

void __fastcall tur_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(TUR_FOURTH_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				relegated_clubs.push_back(table_pos.club);
			}
		}
	}

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_TURKEY_9CF());
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size() + (comp_data->year == 2026 ? 1 : 0), true);

	for (cm3_clubs* c : relegated_clubs) {
		cm3_club_comps* bottomDivision = get_comp(A_LOWER_9CF());
		relegate_club_6831A0((BYTE*)c, (DWORD)bottomDivision, 1);
		c->ClubReserveDivision = 0;
	}

	for (cm3_clubs* c : promoted_clubs) {
		cm3_club_comps* topDivision = get_comp(TUR_FOURTH_9CF());
		promote_club_6830B0((BYTE*)c, (DWORD)topDivision, 1);
	}
}

void sort_tur_third_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(TUR_THIRD_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubLongitudeInv);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 18) available_clubs[i]->ClubReserveDivision = get_comp(TUR_THIRD_G1_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(TUR_THIRD_G2_9CF());
	}
}

void sort_tur_fourth_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(TUR_FOURTH_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubLongitudeInv);
	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 18) available_clubs[i]->ClubReserveDivision = get_comp(TUR_FOURTH_G1_9CF());
		else if (i < 36) available_clubs[i]->ClubReserveDivision = get_comp(TUR_FOURTH_G2_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(TUR_FOURTH_G3_9CF());
	}
}

void __fastcall tur_fake_lower_relegation(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	vector<cm3_clubs*> d4_clubs = find_clubs_of_comp(TUR_FOURTH_9CF(), NATION_TURKEY_9CF());
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_TURKEY_9CF());

	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(lower_clubs, 12 + (comp_data->year == 2026 ? 1 : 0), true);
	vector<cm3_clubs*> relegated_clubs = get_random_weighted_clubs(d4_clubs, 12, false);

	for (cm3_clubs* c : relegated_clubs) {
		cm3_club_comps* bottomDivision = get_comp(A_LOWER_9CF());
		relegate_club_6831A0((BYTE*)c, (DWORD)bottomDivision, 1);
		c->ClubReserveDivision = 0;
	}

	for (cm3_clubs* c : promoted_clubs) {
		cm3_club_comps* topDivision = get_comp(TUR_FOURTH_9CF());
		promote_club_6830B0((BYTE*)c, (DWORD)topDivision, 1);
	}
}

char tur_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;

	BYTE* tur_second = get_loaded_league(TUR_SECOND_9CF());
	BYTE* tur_third = get_loaded_league(TUR_THIRD_9CF());
	BYTE* tur_fourth = get_loaded_league(TUR_FOURTH_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be professional
	update_club_pro_status_68A980(tur_second, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(tur_second, Professional, -3, Relegated, 1);
	// All teams that were not relegated from D3 must be professional
	comp_stats* tur_third_data = (comp_stats*)tur_third;
	BYTE* tur_third_grp = (BYTE*)tur_third_data->stages[0];
	update_club_pro_status_68A980(tur_third, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(tur_third_grp, Professional, Relegated, -3, 1);
	if (tur_fourth)
	{
		comp_stats* tur_fourth_data = (comp_stats*)tur_fourth;
		// All teams that were not relegated from D4 must be semi-professional
		// All teams that were relegated from D4 must be amateur
		update_club_pro_status_68A980(tur_fourth, SemiProfessional, Promoted, -3, 1);
		update_club_pro_status_68A980(tur_fourth, SemiProfessional, Promoted, -3, 0);
		update_club_pro_status_68A980(tur_fourth, SemiProfessional, -3, Champions, 1);
		update_club_pro_status_68A980(tur_fourth, SemiProfessional, -3, Promoted, 1);
		update_club_pro_status_68A980(tur_fourth, Amateur, -3, Relegated, 0);
		for (int i = 0; i < 2; i++)
		{
			BYTE* tur_fourth_grp = (BYTE*)tur_fourth_data->stages[i];
			update_club_pro_status_68A980(tur_fourth_grp, SemiProfessional, Promoted, -3, 1);
			update_club_pro_status_68A980(tur_fourth_grp, SemiProfessional, Promoted, -3, 0);
			update_club_pro_status_68A980(tur_fourth_grp, SemiProfessional, -3, Champions, 1);
			update_club_pro_status_68A980(tur_fourth_grp, SemiProfessional, -3, Promoted, 1);
			update_club_pro_status_68A980(tur_fourth_grp, Amateur, -3, Relegated, 0);
		}
	}

	tur_first_prom_rel_update(_this, 1);

	if (tur_fourth) {
		tur_non_league_promotion(_this);
		sort_tur_fourth_clubs();
	}
	else {
		tur_third_relegation(_this);
		tur_fake_lower_relegation(_this);
	}
	sort_tur_third_clubs();

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
	tur_first_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)tur_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(tur_second);

	v1 = *(DWORD*)tur_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(tur_third);

	if (tur_fourth) {
		v1 = *(DWORD*)tur_fourth;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(tur_fourth);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) tur_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call tur_first_update
		add esp, 0x4
		ret
	}
}

DWORD tur_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 10), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 17), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 24), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 31), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 14), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 21), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 28), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 5), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 19), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 26), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 23), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 30), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 7), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 14), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 21), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 18), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 25), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 1), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 8), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 15), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 22), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 1), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 15), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 18), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 5), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 26), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else return 0;
}

void __declspec(naked) tur_first_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call tur_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void tur_first_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = tur_first_vtable;
	data->year = year;
	data->rules = RulesTurkeyLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 10000;
	data->min_stadium_seats = 10000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	tur_first_subs(_this);
	AddTeams(_this);
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

void setup_tur_first()
{
	WriteVTablePtr(tur_first_vtable, VTableSubsRounds, (DWORD)&tur_first_subs_c);
	WriteVTablePtr(tur_first_vtable, VTableEoSUpdate, (DWORD)&tur_first_update_c);
	WriteVTablePtr(tur_first_vtable, VTableFixtures, (DWORD)&tur_first_fixture_caller);
	WriteVTablePtr(tur_first_vtable, VTablePromRelUpdate, (DWORD)&tur_first_prom_rel_update_c);
	WriteVTablePtr(tur_first_vtable, VTablePostMatchUpdate, (DWORD)&tur_first_money_after_match_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(tur_first_vtable, VTable21, 0x4110b0);
}