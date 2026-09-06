#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "caf_champions_league.h"
#include "caf_confederation_cup.h"
#include "caf_super_cup.h"
#include <Structures/vtable.h>

vtable* caf_discipline_vtable = new vtable((BYTE*)0x96EA14, 0x20);

DWORD caf_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;
	
	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year;
	nation_data->contract_end_day_of_week = 5;
	// call 6699D0 removed so the comps always load
	nation_data->num_of_comps = 3;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xB2);
	caf_champions_league_init(pMem, *current_year, get_comp(CAF_CHAMPIONS_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	caf_confederation_cup_init(pMem, *current_year, get_comp(CAF_CONFEDERATION_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	caf_super_cup_init(pMem, *current_year, get_comp(CAF_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 21, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void rb_africa_ban_text(BYTE* _this, char* ret_str, int a2, int a3) {
	if (a2 >= 20) sub_616F20(Africa, ret_str, a2, 4);
}

void __declspec(naked) rb_africa_ban_text_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call rb_africa_ban_text
		add esp, 0x10
		ret 0xc
	}
}

BYTE* rb_africa_init(BYTE* _this, int* a2) {
	sub_7E7760(_this, a2);
	*((DWORD*)(_this)) = (DWORD)(caf_discipline_vtable->vtable_ptr);
	caf_discipline_vtable->SetPointer(VTableDBanText, (DWORD)&rb_africa_ban_text_c);
	*((BYTE*)(_this + 0x4)) = 2;
	*((BYTE*)(_this + 0x5)) = RulesAfrica;
	*((BYTE*)(_this + 0x6)) = 10;
	*((DWORD*)(_this + 0x17)) = -1;
	*((DWORD*)(_this + 0x1B)) = AFRICA_9CF();
	*((BYTE*)(_this + 0x1F)) = 0xFF;
	*((BYTE*)(_this + 0x20)) = 0xFF;
	*((BYTE*)(_this + 0x21)) = RulesAfrica;
	*((BYTE*)(_this + 0x22)) = 0;
	return _this;
}

void setup_caf_continent() {
	setup_caf_champions_league();
	setup_caf_confederation_cup();
	setup_caf_super_cup();
}