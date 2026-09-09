#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"

vtable* srb_first_vtable = new vtable((BYTE*)0x969798, 0xB4);

void srb_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(srb_first_vtable->vtable_ptr);
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

void srb_first_free(BYTE* _this, BYTE a2) {
	srb_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) srb_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call srb_first_free
		add esp, 0x8
		ret 4
	}
}

int srb_first_7F3220_year1(DWORD a1, DWORD a2) {
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

int srb_first_7F3220(DWORD a1, DWORD a2) {
	BYTE split_pos = 7;
	WORD stage1_games = 26;
	team_league_stats* tls1 = (team_league_stats*)a1;
	team_league_stats* tls2 = (team_league_stats*)a2;

	BYTE bl = ((BYTE*)tls1->position_history)[stage1_games - 1];
	BYTE al = (bl >= split_pos) + 1;
	bl = ((BYTE*)tls2->position_history)[stage1_games - 1];
	BYTE cl = (bl >= split_pos) + 1;
	return al - cl;
}

DWORD srb_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;
	if (year == 2026)
	{
		if (stage_idx == -1) {
			if (a5)
				*a5 = 1;
			BYTE* pMem = NULL;
			DWORD CompID = data->competition_db->ClubCompID;
			*num_rounds = 33;
			*stage_name_id = None;

			pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

			int fixture_id = 0;
			int tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 7, 18), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 7, 25), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 8, 1), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 8, 8), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 8, 15), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 8, 22), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 8, 29), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 5), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 12), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 19), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 10), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 17), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 24), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 31), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 7), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 21), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 28), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 12, 5), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 6), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 13), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 20), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 27), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 6), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 13), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 20), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 3), year, Sunday);
			// next phase starts here
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 10), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 17), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 24), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 5, 1), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 5, 8), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 5, 15), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 22), year, Sunday);

			check_number_of_fixtures(_this, fixture_id, *num_rounds);

			return (DWORD)pMem;
		}
		else if (stage_idx < 2) {
			if (a5)
				*a5 = 1;
			BYTE* pMem = NULL;
			DWORD CompID = data->competition_db->ClubCompID;
			*num_rounds = 7;
			*stage_name_id = ChampionshipGroup + stage_idx;

			pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

			int fixture_id = 0;
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 10), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 17), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 24), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 1), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 8), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 15), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 22), year, Sunday);

			check_number_of_fixtures(_this, fixture_id, *num_rounds);

			return (DWORD)pMem;
		}
	}
	else {
		if (stage_idx == -1) {
			if (a5)
				*a5 = 1;
			BYTE* pMem = NULL;
			DWORD CompID = data->competition_db->ClubCompID;
			*num_rounds = 32;
			*stage_name_id = None;

			pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

			int fixture_id = 0;
			int tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 7, 18), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 7, 25), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 8, 1), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 8, 8), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 8, 15), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 8, 22), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 8, 29), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 5), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 12), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 19), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 10), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 17), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 24), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 10, 31), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 7), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 21), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 28), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 12, 5), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 6), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 13), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 20), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 27), year, Sunday);
			// next phase starts here
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 13), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 3, 20), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 3), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 10), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 17), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 24), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 5, 1), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 5, 8), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 5, 15), year, Sunday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
			AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 22), year, Sunday);

			check_number_of_fixtures(_this, fixture_id, *num_rounds);

			return (DWORD)pMem;
		}
		else if (stage_idx < 2) {
			if (a5)
				*a5 = 1;
			BYTE* pMem = NULL;
			DWORD CompID = data->competition_db->ClubCompID;
			*num_rounds = 10;
			*stage_name_id = ChampionshipGroup + stage_idx;

			pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

			int fixture_id = 0;
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 13), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 20), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 3), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 10), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 17), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 24), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 1), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 8), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 15), year, Sunday);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 22), year, Sunday);

			check_number_of_fixtures(_this, fixture_id, *num_rounds);

			return (DWORD)pMem;
		}
	}
	return 0;
}

void __declspec(naked) srb_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call srb_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void __fastcall srb_reduce_d1_teams(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(SRB_FIRST_9CF());

	vector<cm3_clubs*> promoted_clubs;
	comp_stats* comp_data = (comp_stats*)get_loaded_league(SRB_SECOND_9CF());
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Promoted || table_pos.league_fate == Champions) {
			promoted_clubs.push_back(table_pos.club);
		}
	}

	cm3_club_comps* topDivision = get_comp(SRB_FIRST_9CF());
	cm3_club_comps* bottomDivision = get_comp(SRB_SECOND_9CF());
	for (cm3_clubs* club : relegated_clubs) {
		relegate_club_6831A0((BYTE*)club, (DWORD)bottomDivision, 1);
	}
	for (cm3_clubs* club : promoted_clubs) {
		promote_club_6830B0((BYTE*)club, (DWORD)topDivision, 1);
	}
}

void __fastcall srb_second_relegation_2026(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(SRB_SECOND_9CF());

	vector<cm3_clubs*> promoted_clubs;
	DWORD comp_ids[4] = { SRB_VOJVODINA_9CF(), SRB_BELGRADE_9CF(), SRB_EAST_9CF(), SRB_WEST_9CF() };
	for (DWORD id : comp_ids) {
		comp_stats* comp_data = (comp_stats*)get_loaded_league(id);
		for (WORD num = 0; num < comp_data->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
			if (table_pos.league_fate == Promoted || table_pos.league_fate == Champions) {
				promoted_clubs.push_back(table_pos.club);
			}
		}
	}

	cm3_club_comps* topDivision = get_comp(SRB_SECOND_9CF());
	cm3_club_comps* bottomDivision = get_comp(SRB_BELGRADE_9CF());
	for (cm3_clubs* club : relegated_clubs) {
		relegate_club_6831A0((BYTE*)club, (DWORD)bottomDivision, 1);
	}
	for (cm3_clubs* club : promoted_clubs) {
		promote_club_6830B0((BYTE*)club, (DWORD)topDivision, 1);
	}
}

void srb_first_prom_rel_update(BYTE* _this, int a2) {
	comp_stats* data = (comp_stats*)_this;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* srb_second = get_loaded_league(SRB_SECOND_9CF());
	v1 = *(DWORD*)srb_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(srb_second);
	if (data->year == 2026) {
		srb_reduce_d1_teams(_this);
	}
	else {
		process_promotion_relegation_689C80(_this, _this, srb_second, 1, a2, -1, -1);
	}

	BYTE* vojvodina = get_loaded_league(SRB_VOJVODINA_9CF());
	BYTE* belgrade = get_loaded_league(SRB_BELGRADE_9CF());
	BYTE* east = get_loaded_league(SRB_EAST_9CF());
	BYTE* west = get_loaded_league(SRB_WEST_9CF());
	if (vojvodina && belgrade && east && west) {
		v1 = *(DWORD*)vojvodina;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(vojvodina);
		v1 = *(DWORD*)belgrade;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(belgrade);
		v1 = *(DWORD*)east;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(east);
		v1 = *(DWORD*)west;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(west);

		if (data->year == 2026) {
			srb_second_relegation_2026(_this);
		}
		else
		{
			process_promotion_relegation_689C80(_this, srb_second, vojvodina, 1, a2, -1, -1);
			process_promotion_relegation_689C80(_this, srb_second, belgrade, 1, a2, -1, -1);
			process_promotion_relegation_689C80(_this, srb_second, east, 1, a2, -1, -1);
			process_promotion_relegation_689C80(_this, srb_second, west, 1, a2, -1, -1);
		}
	}
}

void __declspec(naked) srb_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call srb_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void srb_first_subs(BYTE* _this)
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
	comp_data->tiebreaker_4 = GoalsForAwayTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	if (comp_data->year == 2026) comp_data->relegations = 4;
	else comp_data->relegations = 2;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = SRB_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 9;
	comp_data->max_subs = 5;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) srb_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call srb_first_subs
		add esp, 0x4
		ret
	}
}

void __fastcall srb_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(SRB_SECOND_9CF());
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Relegated) {
			relegated_clubs.push_back(table_pos.club);
		}
	}

	vector<cm3_clubs*> d3v_clubs = find_clubs_of_comp(SRB_VOJVODINA_9CF(), NATION_SERBIA_9CF());
	vector<cm3_clubs*> d3b_clubs = find_clubs_of_comp(SRB_BELGRADE_9CF(), NATION_SERBIA_9CF());
	vector<cm3_clubs*> d3e_clubs = find_clubs_of_comp(SRB_EAST_9CF(), NATION_SERBIA_9CF());
	vector<cm3_clubs*> d3w_clubs = find_clubs_of_comp(SRB_WEST_9CF(), NATION_SERBIA_9CF());

	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(d3v_clubs, 1, true);
	vector<cm3_clubs*> promoted_clubs2 = get_random_weighted_clubs(d3b_clubs, 1, true);
	move(promoted_clubs2.begin(), promoted_clubs2.end(), back_inserter(promoted_clubs));
	promoted_clubs2 = get_random_weighted_clubs(d3e_clubs, 1, true);
	move(promoted_clubs2.begin(), promoted_clubs2.end(), back_inserter(promoted_clubs));
	promoted_clubs2 = get_random_weighted_clubs(d3w_clubs, 1, true);
	move(promoted_clubs2.begin(), promoted_clubs2.end(), back_inserter(promoted_clubs));

	for (unsigned int j = 0; j < promoted_clubs.size(); j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}

	if (comp_data->year == 2026) {
		for (unsigned int j = promoted_clubs.size(); j < relegated_clubs.size(); j++) {
			relegate_club_6831A0((BYTE*)relegated_clubs[j], (DWORD)get_comp(SRB_VOJVODINA_9CF()), 1);
		}
	}
}

void __fastcall srb_fake_lower_relegation(BYTE* _this)
{
	vector<cm3_clubs*> d3v_clubs = find_clubs_of_comp(SRB_VOJVODINA_9CF(), NATION_SERBIA_9CF());
	vector<cm3_clubs*> d3b_clubs = find_clubs_of_comp(SRB_BELGRADE_9CF(), NATION_SERBIA_9CF());
	vector<cm3_clubs*> d3e_clubs = find_clubs_of_comp(SRB_EAST_9CF(), NATION_SERBIA_9CF());
	vector<cm3_clubs*> d3w_clubs = find_clubs_of_comp(SRB_WEST_9CF(), NATION_SERBIA_9CF());

	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_SERBIA_9CF());
	unsigned int num_to_swap = d3v_clubs.size() / 8;
	if (lower_clubs.size() < num_to_swap) num_to_swap = lower_clubs.size();

	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(lower_clubs, num_to_swap, true);
	vector<cm3_clubs*> relegated_clubs = get_random_weighted_clubs(d3v_clubs, num_to_swap, false);
	vector<cm3_clubs*> relegated_clubs2 = get_random_weighted_clubs(d3b_clubs, 1, false);
	move(relegated_clubs2.begin(), relegated_clubs2.end(), back_inserter(relegated_clubs));
	relegated_clubs2 = get_random_weighted_clubs(d3e_clubs, 1, false);
	move(relegated_clubs2.begin(), relegated_clubs2.end(), back_inserter(relegated_clubs));
	relegated_clubs2 = get_random_weighted_clubs(d3w_clubs, 1, false);
	move(relegated_clubs2.begin(), relegated_clubs2.end(), back_inserter(relegated_clubs));

	for (unsigned int j = 0; j < num_to_swap; j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}
}

void sort_srpska_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(SRB_VOJVODINA_9CF());
	vector<cm3_clubs*> available_clubs2 = find_clubs_of_comp(SRB_BELGRADE_9CF());
	move(available_clubs2.begin(), available_clubs2.end(), back_inserter(available_clubs));
	available_clubs2 = find_clubs_of_comp(SRB_EAST_9CF());
	move(available_clubs2.begin(), available_clubs2.end(), back_inserter(available_clubs));
	available_clubs2 = find_clubs_of_comp(SRB_WEST_9CF());
	move(available_clubs2.begin(), available_clubs2.end(), back_inserter(available_clubs));
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);
	sort(available_clubs.begin() + 32, available_clubs.end(), compareClubLongitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 16) available_clubs[i]->ClubDivision = get_comp(SRB_VOJVODINA_9CF());
		else if (i < 32) available_clubs[i]->ClubDivision = get_comp(SRB_BELGRADE_9CF());
		else if (i < 48) available_clubs[i]->ClubDivision = get_comp(SRB_EAST_9CF());
		else available_clubs[i]->ClubDivision = get_comp(SRB_WEST_9CF());
	}
}

char srb_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* srb_second = get_loaded_league(SRB_SECOND_9CF());
	BYTE* vojvodina = get_loaded_league(SRB_VOJVODINA_9CF());
	BYTE* belgrade = get_loaded_league(SRB_BELGRADE_9CF());
	BYTE* east = get_loaded_league(SRB_EAST_9CF());
	BYTE* west = get_loaded_league(SRB_WEST_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were not relegated from D2 must be professional
	// All teams that were relegated from D2 must be semi-professional
	update_club_pro_status_68A980(srb_second, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(srb_second, SemiProfessional, -3, Relegated, 0);
	// All teams that were relegated from D3 must be amateur
	if (vojvodina && belgrade && east && west) {
		update_club_pro_status_68A980(vojvodina, Amateur, -3, Relegated, 0);
		update_club_pro_status_68A980(belgrade, Amateur, -3, Relegated, 0);
		update_club_pro_status_68A980(east, Amateur, -3, Relegated, 0);
		update_club_pro_status_68A980(west, Amateur, -3, Relegated, 0);
	}

	DWORD v1 = *(DWORD*)_this;
	srb_first_prom_rel_update(_this, 1);

	if (vojvodina && belgrade && east && west) {
		generic_prom_rel(NATION_SERBIA_9CF(), A_LOWER_9CF(), SRB_VOJVODINA_9CF(), 3, SRB_BELGRADE_9CF(), SRB_EAST_9CF(), SRB_WEST_9CF());
	}
	else {
		srb_non_league_promotion(_this);
		srb_fake_lower_relegation(_this);
	}
	sort_srpska_clubs();


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
	srb_first_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("srb_first_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)srb_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(srb_second);

	if (vojvodina && belgrade && east && west) {
		v1 = *(DWORD*)vojvodina;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(vojvodina);

		v1 = *(DWORD*)belgrade;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(belgrade);

		v1 = *(DWORD*)east;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(east);

		v1 = *(DWORD*)west;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(west);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) srb_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call srb_first_update
		add esp, 0x4
		ret
	}
}

void srb_first_split_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE playoff_teams = 6;
	if (data->year == 2026) playoff_teams = 7;
	WORD n_rounds = 2;
	if (data->year == 2026) n_rounds = 1;
	WORD total_teams = data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(data->team_league_table);

	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	for (int i = 0; i < playoff_teams; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)table_teams[i].club;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	DWORD v0 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 0, &num_rounds, &stage_name_id, 0);

	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	short f217 = 3;
	create_league_stage_data(pStage, _this, playoff_teams, pTeams, n_rounds, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, -1, stage_name_id, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v1 = *(DWORD*)pStage;
	(*(int(__thiscall**)(BYTE*, int))(v1))(pStage, 1);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);

	DWORD* pTeams2 = (DWORD*)cm0102_malloc(playoff_teams * 4);
	for (int i = 0; i < playoff_teams; i++) {
		*((DWORD*)(&pTeams2[i])) = (DWORD)table_teams[i + playoff_teams].club;
	}

	WORD num_rounds2 = 0;
	WORD stage_name_id2 = 0;
	BYTE* pFixtures2 = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 1, &num_rounds2, &stage_name_id2, 0);

	BYTE* pStage2 = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage2, _this, playoff_teams, pTeams2, n_rounds, (DWORD)(data->competition_db), pFixtures2, num_rounds2,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, -1, stage_name_id2, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v2 = *(DWORD*)pStage2;
	(*(int(__thiscall**)(BYTE*, int))(v2))(pStage2, 1);
	sub_9452CA_free(pTeams2);
	sub_9452CA_free(pFixtures2);

	data->n_rounds = 4;
	if (data->year == 2026) *((DWORD*)(_this + 0xA3)) = (DWORD)&srb_first_7F3220_year1;
	else *((DWORD*)(_this + 0xA3)) = (DWORD)&srb_first_7F3220;
}

char srb_first_table_split(BYTE* _this, DWORD current_date, int a2) {
	if (a2) {
		comp_stats* comp_data = (comp_stats*)_this;
		WORD n_games = 22;
		if (comp_data->year == 2026) n_games = 26;
		if (comp_data->n_rounds == 2) {
			WORD num_teams = comp_data->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
			bool is_finished = true;
			for (int i = 0; i < num_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < n_games) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				srb_first_split_under(_this);
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) srb_first_table_split_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call srb_first_table_split
		add esp, 0xc
		ret 8
	}
}

void srb_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(srb_first_vtable->vtable_ptr);
	srb_first_vtable->SetPointer(VTableInitFree, (DWORD)&srb_first_free_c);
	srb_first_vtable->SetPointer(VTableSubsRounds, (DWORD)&srb_first_subs_c);
	srb_first_vtable->SetPointer(VTableEoSUpdate, (DWORD)&srb_first_update_c);
	srb_first_vtable->SetPointer(VTableFixtures, (DWORD)&srb_first_fixtures_c);
	srb_first_vtable->SetPointer(VTableLeagueSplit, (DWORD)&srb_first_table_split_c);
	srb_first_vtable->SetPointer(VTablePromRelUpdate, (DWORD)&srb_first_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) srb_first_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	data->year = year;
	data->rules = RulesSerbia;
	int loaded = sub_687B10(_this, 1);
	if (loaded) {
		if (data->n_rounds != 4) return;
		if (data->year == 2026) *((DWORD*)(_this + 0xA3)) = (DWORD)&srb_first_7F3220_year1;
		else *((DWORD*)(_this + 0xA3)) = (DWORD)&srb_first_7F3220;
		return;
	}
	data->min_stadium_capacity = 3000;
	data->min_stadium_seats = 3000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	srb_first_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("srb_first_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void setup_srb_first()
{
}