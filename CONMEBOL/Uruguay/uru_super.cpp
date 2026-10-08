#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"

vtable* uru_super_vtable = new vtable((BYTE*)0x96C8B8, 0xA0);

void uru_super_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(uru_super_vtable->vtable_ptr);
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
	if (data->f8) {
		sub_49F450((BYTE*)(data->f8));
		sub_944C94_free((BYTE*)(data->f8));
	}
	sub_518690(_this);
}

void uru_super_free(BYTE* _this, BYTE a2) {
	uru_super_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) uru_super_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call uru_super_free
		add esp, 0x8
		ret 4
	}
}

DWORD uru_super_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 1, 5), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 2, 1), year, Sunday, Afternoon, NeutralStadium);
		FillFixtureDetails(pMem, fixture_id++, None, 8, ExtraTime | Penalties, NoTiebreak, 6, 2, 1, 2, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) uru_super_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uru_super_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int uru_super_teams(BYTE* _this, bool first_year) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE total_teams = 2;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	if (first_year) {
		vec.push_back(find_club("Nacional Montevideo"));
		vec.push_back(find_club("Club Atlético Peñarol"));

		for (BYTE i = 0; i < total_teams; i++)
		{
			teams[i].club = vec[i];
			teams[i].seeding = 1 - i;
			teams[i].f6 = 0;
		}

		return 1;
	}

	for (BYTE i = 0; i < total_teams; i++)
	{
		teams[i].club = 0;
		teams[i].seeding = 1 - i;
		teams[i].f6 = 0;
	}

	return 1;
}

char uru_super_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
		data->teams_list = 0;
	}
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
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	uru_super_teams(_this, false);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
}

void __declspec(naked) uru_super_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call uru_super_update
		add esp, 0x4
		ret
	}
}

void uru_super_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (a3) {
		DWORD v1 = *(DWORD*)_this;
		if ((*(short(__thiscall**)(BYTE*))(v1 + 0xC))(_this)) {
			BYTE* cm_date = new BYTE[8];
			// this competition needs to reset at a different time
			convert_to_cm_date(cm_date, 30, December, data->year, -1);
			WORD date_day = *(WORD*)(cm_date);
			WORD date_year = *(WORD*)(cm_date + 2);
			if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
				(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(_this);
			}
		}
	}
	sub_51F890(_this, current_date, a3);
}

void __declspec(naked) uru_super_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uru_super_init2
		add esp, 0xc
		ret 8
	}
}

void uru_super_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(uru_super_vtable->vtable_ptr);
	uru_super_vtable->SetPointer(VTableInitFree, (DWORD)&uru_super_free_c);
	uru_super_vtable->SetPointer(VTableEoSUpdate, (DWORD)&uru_super_update_c);
	uru_super_vtable->SetPointer(VTableFixtures, (DWORD)&uru_super_fixture_caller);
	uru_super_vtable->SetPointer(VTableLeagueSplit, (DWORD)&uru_super_init2_c);
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = RulesUruguay;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	uru_super_teams(_this, true);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
}

void setup_uru_super()
{
}
