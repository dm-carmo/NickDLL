#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* swe_premier_vtable = (DWORD*)0x970198;

void swe_premier_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 2;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = SWE_FIRST_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) swe_premier_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_premier_subs
		add esp, 0x4
		ret
	}
}

void swe_premier_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* swe_first = get_loaded_league(SWE_FIRST_9CF());
	v1 = *(DWORD*)swe_first;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(swe_first);
	process_promotion_relegation_689C80(_this, _this, swe_first, 1, a2, -1, -1);

	BYTE* swe_second = get_loaded_league(SWE_SECOND_9CF());
	comp_stats* swe_second_data = (comp_stats*)swe_second;
	v1 = *(DWORD*)swe_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(swe_second);

	BYTE* swe_second_grp = (BYTE*)swe_second_data->stages[0];
	v1 = *(DWORD*)swe_second_grp;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(swe_second_grp);

	process_promotion_relegation_689C80(_this, swe_first, swe_second, 1, a2, -1, -1);
	process_promotion_relegation_689C80(_this, swe_first, swe_second_grp, 1, a2, -1, -1);

	BYTE* swe_third = get_loaded_league(SWE_THIRD_9CF());
	if (swe_third) {
		comp_stats* swe_third_data = (comp_stats*)swe_third;
		v1 = *(DWORD*)swe_third;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(swe_third);
		for (int i = 0; i < 5; i++)
		{
			BYTE* swe_third_grp = (BYTE*)swe_third_data->stages[i];
			v1 = *(DWORD*)swe_third_grp;
			(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(swe_third_grp);
		}

		process_promotion_relegation_689C80(_this, swe_second, swe_third, 1, a2, -1, -1);
		for (int i = 0; i < 5; i++)
		{
			BYTE* swe_third_grp = (BYTE*)swe_third_data->stages[i];
			process_promotion_relegation_689C80(_this, swe_second, swe_third_grp, 1, a2, -1, -1);
		}

		process_promotion_relegation_689C80(_this, swe_second_grp, swe_third, 1, a2, -1, -1);
		for (int i = 0; i < 5; i++)
		{
			BYTE* swe_third_grp = (BYTE*)swe_third_data->stages[i];
			process_promotion_relegation_689C80(_this, swe_second_grp, swe_third_grp, 1, a2, -1, -1);
		}
	}
}

void __declspec(naked) swe_premier_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call swe_premier_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall swe_second_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	BYTE* comp_bytes = get_loaded_league(SWE_SECOND_9CF());
	comp_stats* comp_data = (comp_stats*)comp_bytes;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				//dprintf("Relegating club from Ettan: %s\n", table_pos.club->ClubNameShort);
				relegated_clubs.push_back(table_pos.club);
			}
		}
	}

	vector<cm3_clubs*> in_playoffs;
	comp_stats* playoff_stage = (comp_stats*)comp_data->stages[1];
	WORD promoted_teams = 0;
	for (WORD i = 0; i < playoff_stage->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)playoff_stage->teams_list)[i];
		cm3_clubs* promote = t.club;
		if (promote->ClubDivision && promote->ClubDivision != comp_data->competition_db) {
			in_playoffs.push_back(promote);
			if (t.f6 == 1) {
				//dprintf("Promoting club to Ettan (playoff): %s\n", promote->ClubNameShort);
				promote_club_6830B0((BYTE*)promote, (DWORD)comp_data->competition_db, 1);
				promoted_teams++;
			}
		}
	}

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(SWE_THIRD_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	int max_to_check = (available_clubs.size() > 12 ? 12 : available_clubs.size());
	for (int i = 0; i < 6; i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* available = available_clubs[availableIdx];
		if (vector_contains_club(in_playoffs, available))
			i--;
		else {
			promote_club_6830B0((BYTE*)available, (DWORD)comp_data->competition_db, 1);
			promoted_teams++;
		}
		available_clubs.erase(available_clubs.begin() + availableIdx);
	}

	if (promoted_teams != relegated_clubs.size()) create_message_box("Error", "Promoted and relegated club count does not match for swe_second", false);

	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		relegate_club_6831A0((BYTE*)relegated_clubs[i], (DWORD)get_comp(SWE_THIRD_9CF()), 1);
		relegated_clubs[i]->ClubReserveDivision = 0;
	}
}

void __fastcall swe_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	BYTE* comp_bytes = get_loaded_league(SWE_THIRD_9CF());
	comp_stats* comp_data = (comp_stats*)comp_bytes;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 5; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				//dprintf("Relegating club from Division 2: %s\n", table_pos.club->ClubNameShort);
				relegated_clubs.push_back(table_pos.club);
			}
		}
	}

	vector<cm3_clubs*> in_playoffs;
	comp_stats* playoff_stage = (comp_stats*)comp_data->stages[7];
	WORD promoted_teams = 0;
	for (WORD i = 0; i < playoff_stage->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)playoff_stage->teams_list)[i];
		cm3_clubs* promote = t.club;
		if (promote->ClubDivision && promote->ClubDivision != comp_data->competition_db) {
			in_playoffs.push_back(promote);
			if (t.f6 == 1) {
				//dprintf("Promoting club to Division 2 (playoff): %s\n", promote->ClubNameShort);
				promote_club_6830B0((BYTE*)promote, (DWORD)comp_data->competition_db, 1);
				promoted_teams++;
			}
		}
	}

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_SWEDEN_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	int max_to_check = (available_clubs.size() > 24 ? 24 : available_clubs.size());
	for (int i = 0; i < 12; i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* available = available_clubs[availableIdx];
		if (vector_contains_club(in_playoffs, available))
			i--;
		else {
			promote_club_6830B0((BYTE*)available, (DWORD)comp_data->competition_db, 1);
			promoted_teams++;
		}
		available_clubs.erase(available_clubs.begin() + availableIdx);
	}

	if (promoted_teams != relegated_clubs.size()) create_message_box("Error", "Promoted and relegated club count does not match for swe_third", false);

	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		relegate_club_6831A0((BYTE*)relegated_clubs[i], (DWORD)get_comp(A_LOWER_9CF()), 1);
		relegated_clubs[i]->ClubReserveDivision = 0;
	}
}

void sort_swe_second_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(SWE_SECOND_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 16) available_clubs[i]->ClubReserveDivision = get_comp(SWE_SECOND_NORTH_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(SWE_SECOND_SOUTH_9CF());
	}
}

void sort_swe_third_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(SWE_THIRD_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 14) available_clubs[i]->ClubReserveDivision = get_comp(SWE_THIRD_NORRLAND_9CF());
		else if (i < 28) available_clubs[i]->ClubReserveDivision = get_comp(SWE_THIRD_NORTH_SVEALAND_9CF());
		else if (i < 42) available_clubs[i]->ClubReserveDivision = get_comp(SWE_THIRD_SOUTH_SVEALAND_9CF());
		else if (i < 56) available_clubs[i]->ClubReserveDivision = get_comp(SWE_THIRD_NORTH_GOTALAND_9CF());
		else if (i < 70) available_clubs[i]->ClubReserveDivision = get_comp(SWE_THIRD_WEST_GOTALAND_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(SWE_THIRD_SOUTH_GOTALAND_9CF());
	}
}

char swe_premier_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;

	BYTE* swe_first = get_loaded_league(SWE_FIRST_9CF());
	BYTE* swe_second = get_loaded_league(SWE_SECOND_9CF());
	BYTE* swe_third = get_loaded_league(SWE_THIRD_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be professional
	update_club_pro_status_68A980(swe_first, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(swe_first, Professional, -3, Relegated, 1);
	// All teams that were in D3 must be semi-professional
	comp_stats* swe_third_data = (comp_stats*)swe_third;
	BYTE* swe_third_grp = (BYTE*)swe_third_data->stages[0];
	update_club_pro_status_68A980(swe_third, SemiProfessional, Relegated, -3, 1);
	update_club_pro_status_68A980(swe_third, SemiProfessional, -3, Relegated, 1);
	update_club_pro_status_68A980(swe_third, SemiProfessional, -3, Relegated, 0);
	update_club_pro_status_68A980(swe_third_grp, SemiProfessional, Relegated, -3, 1);
	update_club_pro_status_68A980(swe_third_grp, SemiProfessional, -3, Relegated, 1);
	update_club_pro_status_68A980(swe_third_grp, SemiProfessional, -3, Relegated, 0);
	if (swe_third)
	{
		comp_stats* swe_third_data = (comp_stats*)swe_third;
		// All teams that were not relegated from D4 must be semi-professional
		// All teams that were relegated from D4 must be amateur
		update_club_pro_status_68A980(swe_third, SemiProfessional, Promoted, -3, 1);
		update_club_pro_status_68A980(swe_third, SemiProfessional, Promoted, -3, 0);
		update_club_pro_status_68A980(swe_third, SemiProfessional, -3, Champions, 1);
		update_club_pro_status_68A980(swe_third, SemiProfessional, -3, Promoted, 1);
		update_club_pro_status_68A980(swe_third, Amateur, -3, Relegated, 0);
		for (int i = 0; i < 5; i++)
		{
			BYTE* swe_third_grp = (BYTE*)swe_third_data->stages[i];
			update_club_pro_status_68A980(swe_third_grp, SemiProfessional, Promoted, -3, 1);
			update_club_pro_status_68A980(swe_third_grp, SemiProfessional, Promoted, -3, 0);
			update_club_pro_status_68A980(swe_third_grp, SemiProfessional, -3, Champions, 1);
			update_club_pro_status_68A980(swe_third_grp, SemiProfessional, -3, Promoted, 1);
			update_club_pro_status_68A980(swe_third_grp, Amateur, -3, Relegated, 0);
		}
	}

	swe_premier_prom_rel_update(_this, 1);

	if (swe_third) {
		swe_non_league_promotion(_this);
		sort_swe_third_clubs();
	}
	else {
		swe_second_relegation(_this);
	}
	sort_swe_second_clubs();

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
	swe_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, 181942);
	data->f225 = 1;
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)swe_first;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(swe_first);

	v1 = *(DWORD*)swe_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(swe_second);

	if (swe_third) {
		v1 = *(DWORD*)swe_third;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(swe_third);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) swe_premier_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_premier_update
		add esp, 0x4
		ret
	}
}

void swe_premier_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = swe_premier_vtable;
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

void swe_premier_free(BYTE* _this, BYTE a2) {
	swe_premier_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) swe_premier_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call swe_premier_free
		add esp, 0x8
		ret 4
	}
}

DWORD swe_premier_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 30), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 6), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 13), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 20), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 23), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 27), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 4), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 11), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 14), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 18), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 25), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 1), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 6), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 13), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 20), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 27), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 3), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 10), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 17), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 24), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 31), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 14), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 21), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 28), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 5), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 19), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 10), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 2, 1, 2, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) swe_premier_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call swe_premier_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void swe_premier_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = swe_premier_vtable;
	data->year = year;
	data->rules = RulesSwedenLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	swe_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, 181942);
	data->f225 = 1;
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void swe_premier_playoff_under(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == BottomPlayoff) {
			*((DWORD*)(&pTeams[0])) = (DWORD)tls.club;
			break;
		}
	}

	comp_stats* swe_first_data = (comp_stats*)get_loaded_league(SWE_FIRST_9CF());
	total_teams = swe_first_data->n_teams;
	table_teams = (team_league_stats*)(swe_first_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[1])) = (DWORD)tls.club;
			break;
		}
	}
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void swe_premier_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		BYTE* swe_first = get_loaded_league(SWE_FIRST_9CF());
		DWORD v1 = *(DWORD*)swe_first;
		char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(swe_first, 0, 1);
		if (ret != 0) {
			(*(void(__thiscall**)(BYTE*))(v1 + 0x94))(swe_first);
			current++;
			comp_data->current_stage = current;
			if (current == 0) {
				swe_premier_playoff_under(_this);
			}
		}
	}
}

void __declspec(naked) swe_premier_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call swe_premier_playoffs_c
		add esp, 0x4
		ret
	}
}

int swe_premier_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* swe_first = get_comp(SWE_FIRST_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club_ptr->ClubDivision == swe_first) {
			comp_stats* swe_first_data = (comp_stats*)get_loaded_league(SWE_FIRST_9CF());
			WORD num_teams = swe_first_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(swe_first_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)swe_first, 0x32);
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

void __declspec(naked) swe_premier_set_table_fate()
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
		call swe_premier_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void swe_premier_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		comp_stats* d2_comp_data = (comp_stats*)get_loaded_league(SWE_FIRST_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == SWE_FIRST_9CF()) {
			ret = (BYTE*)sub_4A4850((BYTE*)d2_comp_data->f8, club);
			if (!ret) return;
			ret_current = 3;
			ret_min = 3;
			ret_max = 3;
		}
		else {
			ret_current = 14;
			ret_min = 14;
			ret_max = 14;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) swe_premier_reputation_calc_c()
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
		call swe_premier_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_swe_premier()
{
	WriteVTablePtr(swe_premier_vtable, VTableSubsRounds, (DWORD)&swe_premier_subs_c);
	WriteVTablePtr(swe_premier_vtable, VTableInitFree, (DWORD)&swe_premier_free_c);
	WriteVTablePtr(swe_premier_vtable, VTableEoSUpdate, (DWORD)&swe_premier_update_c);
	WriteVTablePtr(swe_premier_vtable, VTableFixtures, (DWORD)&swe_premier_fixtures_c);
	WriteVTablePtr(swe_premier_vtable, VTableReputationCalc, (DWORD)&swe_premier_reputation_calc_c);
	WriteVTablePtr(swe_premier_vtable, VTablePlayoffQual, (DWORD)&swe_premier_playoffs_create);
	WriteVTablePtr(swe_premier_vtable, VTableTableFates, (DWORD)&swe_premier_set_table_fate);
	WriteVTablePtr(swe_premier_vtable, VTablePromRelUpdate, (DWORD)&swe_premier_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(swe_premier_vtable, VTable21, 0x4110b0);
}
