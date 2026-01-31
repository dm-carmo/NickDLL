#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers/new_league_ids.h>

DWORD* cro_first_vtable = (DWORD*)0x9690C4;

void cro_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 4;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = 4;
	comp_data->tiebreaker_2 = 1;
	comp_data->tiebreaker_3 = 2;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 1;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = *(DWORD*)0x9CF880;

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	//call vtable +3C which is actually add fixtures function
	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) cro_first_subs_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call cro_first_subs
		add esp, 0x4
		ret
	}
}

DWORD cro_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 23), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 1), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 22), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 23), year, Saturday);

		if (fixture_id != *num_rounds) {
			string msg = "Wrong number of fixtures: " + to_string(fixture_id);
			create_message_box("Error", msg.c_str(), true);
		}

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) cro_first_fixtures_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call cro_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void cro_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = cro_first_vtable;
	data->year = year;
	data->rules = 0x21;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	cro_first_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_68A850(_this);
}

void __fastcall cro_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(cro_third_id);
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Relegated) {
			relegated_clubs.push_back(table_pos.club);
		}
	}

	vector<cm3_clubs*> available_clubs;
	comp_stats* playoff_stage = (comp_stats*)comp_data->stages[0];
	WORD promoted_teams = 0;
	for (WORD i = 0; i < playoff_stage->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)playoff_stage->teams_list)[i];
		if (t.f6 == 1) {
			cm3_clubs* promote = t.club;
			if (promote->ClubDivision && promote->ClubDivision != comp_data->competition_db) {
				sub_6830B0((BYTE*)promote, (DWORD)comp_data->competition_db, 1);
				promoted_teams++;
			}
		}
	}

	if (promoted_teams != relegated_clubs.size()) create_message_box("Error", "Promoted and relegated club count does not match for cro_third", false);

	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		sub_6831A0((BYTE*)relegated_clubs[i], (DWORD)get_comp(Get9CF(0x9CF888)), 1);
	}
}

void sort_cro_non_league_clubs() {
	vector<cm3_clubs*> available_clubs;

	for (int i = 0; i < get_club_count(); i++)
	{
		cm3_clubs* club = get_club(i);
		if (club)
		{
			if (club->ClubDivision && club->ClubNation)
			{
				DWORD compID = club->ClubDivision->ClubCompID;
				DWORD nationID = club->ClubNation->NationID;
				if (nationID == Get9CF(0x9CF2AC) &&		// Croatia
					(compID == Get9CF(0x9CF884) ||		// Non-leagues
						compID == Get9CF(0x9CF888) ||
						compID == Get9CF(0x9CF88C) ||
						compID == Get9CF(0x9CF890) ||
						compID == Get9CF(0x9CF894)))
				{
					available_clubs.push_back(club);
				}
			}
		}
	}
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);
	sort(available_clubs.begin() + 10, available_clubs.end() - 10, compareClubLongitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 10) available_clubs[i]->ClubDivision = get_comp(Get9CF(0x9CF888));
		else if (i < 20) available_clubs[i]->ClubDivision = get_comp(Get9CF(0x9CF890));
		else if (i < 30) available_clubs[i]->ClubDivision = get_comp(Get9CF(0x9CF884));
		else if (i < 40) available_clubs[i]->ClubDivision = get_comp(Get9CF(0x9CF894));
		else available_clubs[i]->ClubDivision = get_comp(Get9CF(0x9CF88C));
	}
}

char cro_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	DWORD v1 = *(DWORD*)_this;
	(*(void(__thiscall**)(BYTE*, int))(v1 + 0xB0))(_this, 1);
	cro_non_league_promotion(_this);
	sort_cro_non_league_clubs();

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
	cro_first_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	BYTE* cro_second = get_loaded_league(Get9CF(0x9CF880));
	BYTE* cro_third = get_loaded_league(cro_third_id);

	v1 = *(DWORD*)cro_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(cro_second);

	v1 = *(DWORD*)cro_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(cro_third);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) cro_first_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call cro_first_update
		add esp, 0x4
		ret
	}
}

void setup_cro_first()
{
	WriteVTablePtr(cro_first_vtable, VTableSubsRounds, (DWORD)&cro_first_subs_c);
	WriteVTablePtr(cro_first_vtable, VTableFixtures, (DWORD)&cro_first_fixtures_c);
	WriteVTablePtr(cro_first_vtable, VTableEoSUpdate, (DWORD)&cro_first_update_c);
	WriteVTablePtr(cro_first_vtable, VTablePromRelUpdate, (DWORD)0x689C20);
}
