#pragma warning (disable : 4733)
#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include "eng_conf.h"

vtable* eng_conf_n_vtable = new vtable((BYTE*)0x969A74, 0xB4);

void eng_conf_n_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(eng_conf_n_vtable->vtable_ptr);
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

void eng_conf_n_free(BYTE* _this, BYTE a2) {
	eng_conf_n_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) eng_conf_n_free_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call eng_conf_n_free
		add esp, 0x8
		ret 4
	}
}

int eng_conf_n_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->tiebreaker_1 = 1;
	comp_data->tiebreaker_2 = 2;
	comp_data->tiebreaker_3 = 3;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 6;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 4;

	comp_data->promotes_to = *(DWORD*)0x9CF69C;
	comp_data->relegates_to = 0x167;

	comp_data->f82 = 2;
	comp_data->max_bench = 5;
	comp_data->max_subs = 3;

	//call vtable +3C which is actually add fixtures function
	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return 1;
}

void eng_conf_n_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	strcpy(comp->ClubCompNameThreeLetter, "NLN");
	strcpy(comp->ClubCompName, "English National League North");
	strcpy(comp->ClubCompNameShort, "National League North");
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(eng_conf_n_vtable->vtable_ptr);
	data->year = year;
	data->rules = 0x9;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	eng_conf_n_subs(_this);
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

void __declspec(naked) eng_conf_n_init_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_conf_n_init
		add esp, 0xc
		ret 8
	}
}

char eng_conf_n_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
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
	eng_conf_n_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) eng_conf_n_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_conf_n_update
		add esp, 0x4
		ret
	}
}

void __declspec(naked) eng_conf_n_subs_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_conf_n_subs
		add esp, 0x4
		ret
	}
}

void setup_eng_conf_n() {
	eng_conf_n_vtable->SetPointer(VTableInitFree, (DWORD)&eng_conf_n_free_c);
	eng_conf_n_vtable->SetPointer(VTableEoSUpdate, (DWORD)&eng_conf_n_update_c);
	eng_conf_n_vtable->SetPointer(VTablePlayoffQual, (DWORD)&eng_playoffs_create);
	eng_conf_n_vtable->SetPointer(VTableFixtures, (DWORD)&eng_conf_fixtures);
	eng_conf_n_vtable->SetPointer(VTableTableFates, (DWORD)&eng_conf_set_table_fate);
	eng_conf_n_vtable->SetPointer(VTableSubsRounds, (DWORD)&eng_conf_n_subs_c);
}