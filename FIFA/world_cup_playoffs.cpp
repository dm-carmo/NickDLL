#include <windows.h>
#include <filesystem>
#include <fstream>
#include <map>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

using namespace std;

vtable* world_cup_playoffs_vtable = new vtable((BYTE*)0x970C24, 0xA0);

void world_cup_playoffs_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(world_cup_playoffs_vtable->vtable_ptr);
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
	}
	if ((DWORD*)data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
			}
		}
		sub_9452CA_free(data->f173);
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
	sub_518690(_this);
}

void world_cup_playoffs_free(BYTE* _this, BYTE a2) {
	world_cup_playoffs_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) world_cup_playoffs_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_playoffs_free
		add esp, 0x8
		ret 4
	}
}

DWORD world_cup_playoffs_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 2;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		WORD uefa_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), EUROPE_9CF(), 0, 0);
		WORD num_teams = 6 - (uefa_hosts > 0);
		WORD r1_teams = num_teams - 2 - num_teams % 2;
		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 10), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 24), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup | Penalties | ExtraTime, NoTiebreak, 10, r1_teams, r1_teams / 2, r1_teams, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 25), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 29), year, Tuesday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, FixedTeamOrderInCup3 | Penalties | ExtraTime, NoTiebreak, 10, 4, 2, num_teams - r1_teams, r1_teams, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) world_cup_playoffs_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_playoffs_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char world_cup_playoffs_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	if (data->special_teams_seedings) {
		sub_9452CA_free(data->special_teams_seedings);
		data->special_teams_seedings = 0;
	}
	data->special_nteams_seedings = 0;
	data->f56 = 6;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * 6);
	data->special_teams_seedings = (DWORD*)pMem;
	if (data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
		data->rounds_list = 0;
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
				data->f173[i] = 0;
			}
		}
		sub_9452CA_free(data->f173);
		data->f173 = 0;
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
	data->current_stage = -1;
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	if (data->year < *current_year) data->year += 4;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) world_cup_playoffs_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call world_cup_playoffs_update
		add esp, 0x4
		ret
	}
}

void world_cup_playoffs_get_conmebol_team(BYTE* _this) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* data = (comp_stats*)_this;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	comp_stats* wcq_conmebol_data = (comp_stats*)get_loaded_league(WORLD_CUP_CONMEBOL_QUALIFYING_9CF());
	team_league_stats* table_teams = (team_league_stats*)(wcq_conmebol_data->team_league_table);
	for (WORD i = 0; i < wcq_conmebol_data->n_teams; i++) {
		team_league_stats t = table_teams[i];
		if (t.league_fate == TopPlayoff) {
			WORD insert_idx = data->special_nteams_seedings;
			teams[insert_idx].club = t.club;
			teams[insert_idx].seeding = 6;
			teams[insert_idx].f6 = 0;
			data->special_nteams_seedings++;
			staff_history_qualified_86BDD0(staff_hist_ptr, t.club, (DWORD)(get_comp(WORLD_CUP_PLAYOFFS_9CF())), None, None, 0x1E);
		}
	}
}

void world_cup_playoffs_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = data->special_nteams_seedings;
	WORD uefa_hosts = get_comp_hosts_in_continent(_this, FIFA_WORLD_CUP_9CF(), EUROPE_9CF(), 0, 0);
	if (uefa_hosts > 0) data->f56--;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	if (data->teams_list) sub_9452CA_free(data->teams_list);
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
			}
		}
		sub_9452CA_free(data->f173);
	}

	vector<cm3_clubs*> qualified_teams;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	for (WORD i = 0; i < total_teams; i++) qualified_teams.push_back(qualifiers[i].club);
	sort(qualified_teams.begin(), qualified_teams.end(), compareNationRanking);

	WORD year = data->year;
	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	for (WORD i = 0; i < total_teams; i++) {
		cm3_clubs* club = qualified_teams[data->special_nteams_seedings - i - 1];
		teams[i].club = club;
		teams[i].seeding = data->special_nteams_seedings - i - 1;
		teams[i].f6 = 0;
	}
}

void world_cup_playoffs_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		BYTE* cm_date = new BYTE[8];
		convert_to_cm_date(cm_date, 3, December, data->year, -1);
		WORD date_day = *(WORD*)(cm_date);
		WORD date_year = *(WORD*)(cm_date + 2);
		if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
			if (a3) {
				data->f69 = 1;
				world_cup_playoffs_get_conmebol_team(_this);
				world_cup_playoffs_qualifier_teams(_this);
				DWORD v1 = *(DWORD*)_this;
				(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
				(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
				(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
				sub_51C800(_this, 0);
			}
		}
	}
	sub_51F890(_this, current_date, a3);
}

void __declspec(naked) world_cup_playoffs_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_playoffs_init2
		add esp, 0xc
		ret 8
	}
}

int world_cup_playoffs_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			qualify_team_for_international_comp(club, FIFA_WORLD_CUP_9CF(), false);
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

void __declspec(naked) world_cup_playoffs_table_fates_c()
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
		call world_cup_playoffs_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

int world_cup_playoffs_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id == -1) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0xAD4B78, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			case Promoted:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			default:
				sub_66F4E0(0xDE1F64, 0xAD4BA4, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
	}
	return 0;
}

void __declspec(naked) world_cup_playoffs_stage_news_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x28]
		push dword ptr[eax + 0x24]
		push dword ptr[eax + 0x20]
		push dword ptr[eax + 0x1c]
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_playoffs_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void world_cup_playoffs_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	if (main_stage_id == None) {
		if (fate == TopPlayoff) {
			sub_66F4E0(dest_ptr, 0xAD4658, club->ClubGenderName, 0xAD9C64);
			return;
		}
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) world_cup_playoffs_landmarks_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_playoffs_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

WORD world_cup_playoffs_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);
	if (val < 2) return -3;
	else return -5;
}

void __declspec(naked) world_cup_playoffs_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_playoffs_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE world_cup_playoffs_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	if (al < 2) return 2 * (bl < 2) - 1;
	else return (bl < 2) - 1;
}

void __declspec(naked) world_cup_playoffs_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call world_cup_playoffs_vtable30
		add esp, 0x8
		ret 4
	}
}

void world_cup_playoffs_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(world_cup_playoffs_vtable->vtable_ptr);
	world_cup_playoffs_vtable->SetPointer(VTableInitFree, (DWORD)&world_cup_playoffs_free_c);
	world_cup_playoffs_vtable->SetPointer(VTableEoSUpdate, (DWORD)&world_cup_playoffs_update_c);
	world_cup_playoffs_vtable->SetPointer(VTableLeagueSplit, (DWORD)&world_cup_playoffs_init2_c);
	world_cup_playoffs_vtable->SetPointer(VTablePlayoffQual, 0x5a8f60);
	world_cup_playoffs_vtable->SetPointer(VTableTableFates, (DWORD)&world_cup_playoffs_table_fates_c);
	world_cup_playoffs_vtable->SetPointer(VTableReputationSetup, 0x5223a0);
	world_cup_playoffs_vtable->SetPointer(VTableReputationCalc, 0x48e380);
	world_cup_playoffs_vtable->SetPointer(VTableFixtures, (DWORD)&world_cup_playoffs_fixture_caller);
	world_cup_playoffs_vtable->SetPointer(VTableStageNews, (DWORD)&world_cup_playoffs_stage_news_c);
	world_cup_playoffs_vtable->SetPointer(VTable29, (DWORD)&world_cup_playoffs_vtable29_c);
	world_cup_playoffs_vtable->SetPointer(VTable30, (DWORD)&world_cup_playoffs_vtable30_c);
	world_cup_playoffs_vtable->SetPointer(VTableClubLandmarks, (DWORD)&world_cup_playoffs_landmarks_c);
	world_cup_playoffs_vtable->SetPointer(VTableLoadCompInfo, 0x48CEB0);
	world_cup_playoffs_vtable->SetPointer(VTableSaveCompInfo, 0x48CEA0);
	data->year = year;
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->rules = RulesInternational;
	data->f82 = 3;
	data->max_bench = 7;
	data->max_subs = 3;
	data->year = year + 1;
	while (data->year % 4 != 1) data->year++;
	data->f81 = 0xf;
	data->special_nteams_seedings = 0;
	data->f56 = 6;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * 6);
	data->special_teams_seedings = (DWORD*)pMem;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;

	data->n_teams = 6;
	BYTE* tMem = (BYTE*)cm0102_malloc(6 * data->n_teams);
	data->teams_list = (DWORD*)tMem;

	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void setup_world_cup_playoffs() {
}