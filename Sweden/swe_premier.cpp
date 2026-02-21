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
	comp_data->tiebreaker_1 = 1;
	comp_data->tiebreaker_2 = 2;
	comp_data->tiebreaker_3 = 0;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 2;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = SWE_FIRST_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	//call vtable +3C which is actually add fixtures function
	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) swe_premier_subs_c()		// used as a __thiscall -> __cdecl converter
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
	sub_689C80(_this, _this, swe_first, 1, a2, -1, -1);

	BYTE* swe_second = get_loaded_league(SWE_SECOND_9CF());
	comp_stats* swe_second_data = (comp_stats*)swe_second;
	v1 = *(DWORD*)swe_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(swe_second);

	BYTE* swe_second_grp = (BYTE*)swe_second_data->stages[0];
	v1 = *(DWORD*)swe_second_grp;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(swe_second_grp);

	sub_689C80(_this, swe_first, swe_second, 1, a2, -1, -1);
	sub_689C80(_this, swe_first, swe_second_grp, 1, a2, -1, -1);

	BYTE* swe_third = get_loaded_league(SWE_THIRD_9CF());
	if (swe_third) {
		comp_stats* swe_third_data = (comp_stats*)swe_third;
		v1 = *(DWORD*)swe_third;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(swe_third);
		for (int i = 0; i < 3; i++)
		{
			BYTE* swe_third_grp = (BYTE*)swe_third_data->stages[i];
			v1 = *(DWORD*)swe_third_grp;
			(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(swe_third_grp);
		}

		sub_689C80(_this, swe_second, swe_third, 1, a2, -1, -1);
		for (int i = 0; i < 5; i++)
		{
			BYTE* swe_third_grp = (BYTE*)swe_third_data->stages[i];
			sub_689C80(_this, swe_second, swe_third_grp, 1, a2, -1, -1);
		}

		sub_689C80(_this, swe_second_grp, swe_third, 1, a2, -1, -1);
		for (int i = 0; i < 5; i++)
		{
			BYTE* swe_third_grp = (BYTE*)swe_third_data->stages[i];
			sub_689C80(_this, swe_second_grp, swe_third_grp, 1, a2, -1, -1);
		}
	}
}

void __declspec(naked) swe_premier_prom_rel_update_c()		// used as a __thiscall -> __cdecl converter
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

	vector<cm3_clubs*> available_clubs;
	comp_stats* playoff_stage = (comp_stats*)comp_data->stages[1];
	WORD promoted_teams = 0;
	for (WORD i = 0; i < playoff_stage->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)playoff_stage->teams_list)[i];
		if (t.f6 == 1) {
			cm3_clubs* promote = t.club;
			if (promote->ClubDivision && promote->ClubDivision != comp_data->competition_db) {
				//dprintf("Promoting club to Ettan (playoff): %s\n", promote->ClubNameShort);
				promote_club_6830B0((BYTE*)promote, (DWORD)comp_data->competition_db, 1);
				promoted_teams++;
			}
		}
	}

	for (int i = 0; i < 6; i++) {
		cm3_clubs* c = get_club(*(DWORD*)(comp_bytes + 0xEE + 4 * i));
		//dprintf("Promoting club to Ettan (simulated winner): %s\n", c->ClubNameShort);
		promote_club_6830B0((BYTE*)c, (DWORD)comp_data->competition_db, 1);
		promoted_teams++;
		*(DWORD*)(comp_bytes + 0xEE + 4 * i) = -1;
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

	vector<cm3_clubs*> available_clubs;
	comp_stats* playoff_stage = (comp_stats*)comp_data->stages[7];
	WORD promoted_teams = 0;
	for (WORD i = 0; i < playoff_stage->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)playoff_stage->teams_list)[i];
		if (t.f6 == 1) {
			cm3_clubs* promote = t.club;
			if (promote->ClubDivision && promote->ClubDivision != comp_data->competition_db) {
				//dprintf("Promoting club to Division 2 (playoff): %s\n", promote->ClubNameShort);
				promote_club_6830B0((BYTE*)promote, (DWORD)comp_data->competition_db, 1);
				promoted_teams++;
			}
		}
	}

	for (int i = 0; i < 12; i++) {
		cm3_clubs* c = get_club(*(DWORD*)(comp_bytes + 0xEE + 4 * i));
		//dprintf("Promoting club to Division 2 (simulated winner): %s\n", c->ClubNameShort);
		promote_club_6830B0((BYTE*)c, (DWORD)comp_data->competition_db, 1);
		promoted_teams++;
		*(DWORD*)(comp_bytes + 0xEE + 4 * i) = -1;
	}

	if (promoted_teams != relegated_clubs.size()) create_message_box("Error", "Promoted and relegated club count does not match for swe_third", false);

	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		relegate_club_6831A0((BYTE*)relegated_clubs[i], (DWORD)get_comp(SWE_LOWER_9CF()), 1);
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
	swe_premier_prom_rel_update(_this, 1);

	BYTE* swe_third = get_loaded_league(SWE_THIRD_9CF());
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
		}
	}
	data->year++;
	data->current_stage = -1;
	swe_premier_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	BYTE* swe_first = get_loaded_league(SWE_FIRST_9CF());
	BYTE* swe_second = get_loaded_league(SWE_SECOND_9CF());

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

void __declspec(naked) swe_premier_update_c()		// used as a __thiscall -> __cdecl converter
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

void __declspec(naked) swe_premier_free_c()		// used as a __thiscall -> __cdecl converter
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
		*num_rounds = (numberOfLeagueTeams - 1) * ((comp_stats*)_this)->n_rounds;
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

void __declspec(naked) swe_premier_fixtures_c()		// used as a __thiscall -> __cdecl converter
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

void swe_restruct_2025() {
	cm3_club_comps* swe_premier = &(*club_comps)[SWE_PREMIER_9CF()];
	cm3_club_comps* swe_first = &(*club_comps)[SWE_FIRST_9CF()];
	cm3_club_comps* swe_second = &(*club_comps)[SWE_SECOND_9CF()];
	swe_second->ClubCompReputation = 4;
	cm3_club_comps* swe_second_n = &(*club_comps)[SWE_SECOND_NORTH_9CF()];
	swe_second_n->ClubCompReputation = 4;
	cm3_club_comps* swe_second_s = &(*club_comps)[SWE_SECOND_SOUTH_9CF()];
	cm3_club_comps* swe_third = &(*club_comps)[SWE_THIRD_9CF()];
	swe_third->ClubCompReputation = 2;
	cm3_club_comps* swe_third_ng = &(*club_comps)[SWE_THIRD_NORTH_GOTALAND_9CF()];
	swe_third_ng->ClubCompReputation = 2;
	cm3_club_comps* swe_third_ns = &(*club_comps)[SWE_THIRD_NORTH_SVEALAND_9CF()];
	swe_third_ns->ClubCompReputation = 2;
	cm3_club_comps* swe_third_n = &(*club_comps)[SWE_THIRD_NORRLAND_9CF()];
	swe_third_n->ClubCompReputation = 2;
	cm3_club_comps* swe_third_sg = &(*club_comps)[SWE_THIRD_SOUTH_GOTALAND_9CF()];
	swe_third_sg->ClubCompReputation = 2;
	cm3_club_comps* swe_third_ss = &(*club_comps)[SWE_THIRD_SOUTH_SVEALAND_9CF()];
	swe_third_ss->ClubCompReputation = 2;
	cm3_club_comps* swe_third_wg = &(*club_comps)[SWE_THIRD_WEST_GOTALAND_9CF()];
	swe_third_wg->ClubCompReputation = 2;
	cm3_club_comps* swe_lower = &(*club_comps)[SWE_LOWER_9CF()];

	vector<string> move_to_lower = {
		"Swedish Division 2 East Svealand",
		"Swedish Division 2 Middle Gotaland",
		"Swedish Division 2 Middle Norrland",
		"Swedish Division 2 North Norrland",
		"Swedish Division 2 North Svealand",
		"Swedish Division 2 Northeast Gotaland",
		"Swedish Division 2 Northwest Gotaland",
		"Swedish Division 2 South Gotaland",
		"Swedish Division 2 South Norrland",
		"Swedish Division 2 Southeast Gotaland",
		"Swedish Division 2 Southwest Gotaland",
		"Swedish Division 2 West Svealand",
		"Swedish Ettan East Gotaland",
		"Swedish Ettan East Svealand",
		"Swedish Ettan North",
		"Swedish Ettan South Gotaland",
		"Swedish Ettan West Gotaland",
		"Swedish Ettan West Svealand",
	};
	for (string s : move_to_lower) {
		cm3_club_comps* comp = find_club_comp(s.c_str());
		if (comp)
		{
			vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(comp->ClubCompID);
			for (cm3_clubs* c : lower_clubs) {
				c->ClubDivision = swe_lower;
			}
		}
	}

	cm3_nations* sweden = find_country("Sweden");
	cm3_clubs* tidaholms_goif = find_club("Tidaholms GoIF");
	if (tidaholms_goif) {
		tidaholms_goif->ClubNation = sweden;
	}

	vector<string> premier_clubs = {
		"Degerfors IF",
		"Östers IF",
	};
	vector<string> first_clubs = {
		"Trelleborgs FF",
		"Utsiktens BK",
	};
	vector<string> second_n_clubs = {
		"Nordic United FC",
		"Hammarby TFF",
		"Vasalunds IF",
		"FC Stockholm",
		"IF Karlstad Fotboll",
		"Assyriska FF",
		"FC Arlanda",
		"AFC Eskilstuna",
		"Karlbergs BK",
		"Sollentuna FK",
		"Enköpings SK",
		"IFK Stocksund",
		"Gefle IF",
		"IFK Haninge",
		"Örebro Syrianska IF",
		"Team TG FF",
	};
	vector<string> second_s_clubs = {
		"Ljungskile SK",
		"Norrby IF",
		"Jönköpings Södra IF",
		"Hässleholms IF",
		"Lunds BK",
		"Ariana FC",
		"FC Trollhättan",
		"BK Olympic",
		"Ängelholms FF",
		"Eskilsminne IF",
		"FC Rosengård",
		"Skövde AIK",
		"Oskarshamns AIK",
		"Torslanda IK",
		"Husqvarna FF",
		"IFK Skövde",
	};
	vector<string> third_ng_clubs = {
		"FBK Karlstad",
		"Motala AIF",
		"Lidköpings FK",
		"Ahlafors IF",
		"IK Kongahälla",
		"Grebbestads IF",
		"Vänersborgs IF",
		"Vänersborgs FK",
		"IK Tord",
		"IFK Kumla",
		"Tidaholms GoIF",
		"IK Gauthiod", // missing Herrestads AIF
		"Säffle FF", // missing Skara FC
		"Stenungsunds IF", // missing IF Haga
	};
	vector<string> third_ns_clubs = {
		"FC Järfälla",
		"Viggbyholms IK",
		"Nacka FC",
		"IK Franke",
		"Täby FK",
		"Kungsängens IF",
		"Skiljebo SK",
		"Korsnäs IF",
		"FC Gute",
		"Ytterhogdals IK",
		"Österåker United FK",
		"Sandvikens AIK", // missing Falu BS
		"Hudiksvalls FF", // missing Bollstanäs SK
		"Dalkurd FF", // missing Sunnersta AIF
	};
	vector<string> third_n_clubs = {
		"Piteå IF",
		"Skellefteå FF",
		"IFK Luleå",
		"Bergnäsets AIK",
		"Bodens BK",
		"Kiruna FF",
		"IFK Östersund",
		"Umeå FC Akademi",
		"Gottne IF",
		"Friska Viljor FC",
		"Lucksta IF",
		"Täfteå IK",
		"Frösö IF", // missing Boden City
		"Älgarna-Härnösand IF", // missing Kubikenborgs IF
	};
	vector<string> third_sg_clubs = {
		"Kristianstad FC",
		"FK Karlskrona",
		"IFK Trelleborg",
		"Sölvesborgs GoIF",
		"Växjö Norra IF",
		"Räppe GoIF",
		"Torns IF",
		"Nosaby IF",
		"IFK Karlshamn",
		"Österlen FF",
		"Högaborgs BK",
		"IFK Hässleholm",
		"FBK Balkan",
		"Lödde IF", // missing Linero IF
	};
	vector<string> third_ss_clubs = {
		"Åtvidabergs FF",
		"Rågsveds IF",
		"IF Sylvia",
		"IK Sleipner",
		"FOC Farsta",
		"Enskede IK",
		"Smedby AIS",
		"Nyköpings BIS",
		"BK Forward",
		"Syrianska FC",
		"IF Eker Örebro",
		"Huddinge IF",
		"Arameisk-Syrianska IF",
		"Syrianska Eskilstuna IF",
	};
	vector<string> third_wg_clubs = {
		"Laholms FK",
		"Tvååkers IF",
		"Åstorps FF",
		"Onsala BK",
		"Västra Frölunda IF",
		"Lindome GIF",
		"Qviding FIF",
		"BK Astrio",
		"Landvetter IS",
		"Hestrafors IF",
		"Varbergs GIF",
		"Sävedalens IF", // missing Jonsereds IF
		"Öckerö IF", // missing IF Böljan
		"Hittarps IK", // missing Bergdalens IK
	};

	for (string s : premier_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_premier;
	}
	for (string s : first_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_first;
	}
	for (string s : second_n_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_second;
		club->ClubReserveDivision = swe_second_n;
	}
	for (string s : second_s_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_second;
		club->ClubReserveDivision = swe_second_s;
	}
	for (string s : third_ng_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_ng;
	}
	for (string s : third_ns_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_ns;
	}
	for (string s : third_n_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_n;
	}
	for (string s : third_sg_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_sg;
	}
	for (string s : third_ss_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_ss;
	}
	for (string s : third_wg_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_wg;
	}
}

void swe_premier_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = swe_premier_vtable;
	data->year = year;
	data->rules = 0x1c;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	if (year == 2025 || year == 2026) swe_restruct_2025();
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	swe_premier_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	reputation_setup_generic_68A850(_this);
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

void __declspec(naked) swe_premier_playoffs_create()		// used as a __thiscall -> __cdecl converter
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

int swe_premier_table_indicators(BYTE* _this, DWORD* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* swe_first = &(*club_comps)[SWE_FIRST_9CF()];
		if (club_ptr->ClubDivision == swe_first) {
			comp_stats* swe_first_data = (comp_stats*)get_loaded_league(SWE_FIRST_9CF());
			WORD num_teams = swe_first_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(swe_first_data->team_league_table);
			comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
			BYTE* rounds = stage_data->rounds_list;
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				DWORD* c = (DWORD*)table[i].club;
				if (c != club) continue;
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
			comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
			BYTE* rounds = stage_data->rounds_list;
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				DWORD* c = (DWORD*)table[i].club;
				if (c != club) continue;
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

void __declspec(naked) swe_premier_set_table_fate()		// used as a __thiscall -> __cdecl converter
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
			ret_current = 16;
			ret_min = 16;
			ret_max = 16;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) swe_premier_reputation_calc_c()		// used as a __thiscall -> __cdecl converter
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
}
