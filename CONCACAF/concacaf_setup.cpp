#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "concacaf_champions_cup.h"
#include "Structures\vtable.h"

vtable* concacaf_discipline_vtable = new vtable((BYTE*)0x96EE34, 0x20);

DWORD concacaf_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = start_year;
	nation_data->contract_start_day_of_week = 5;
	
	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = start_year;
	nation_data->contract_end_day_of_week = 5;
	// call 6699D0 removed so the comps always load
	nation_data->num_of_comps = 1;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xB2);
	concacaf_champions_cup_init(pMem, start_year, get_comp(CONCACAF_CHAMPIONS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 2, January, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void rb_concacaf_ban_text(BYTE* _this, char* ret_str, int a2, int a3) {
	if(a2 >= 20) sub_616F20(NorthAmerica, ret_str, a2, 4);
}

void __declspec(naked) rb_concacaf_ban_text_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call rb_concacaf_ban_text
		add esp, 0x10
		ret 0xc
	}
}

BYTE* rb_concacaf_init(BYTE* _this, int* a2) {
	sub_7E7760(_this, a2);
	*((DWORD*)(_this)) = (DWORD)(concacaf_discipline_vtable->vtable_ptr);
	concacaf_discipline_vtable->SetPointer(VTableDBanText, (DWORD)&rb_concacaf_ban_text_c);
	*((BYTE*)(_this + 0x4)) = 2;
	*((BYTE*)(_this + 0x5)) = RulesNorthAmerica;
	*((BYTE*)(_this + 0x6)) = 10;
	*((DWORD*)(_this + 0x17)) = -1;
	*((DWORD*)(_this + 0x1B)) = NORTH_AMERICA_9CF();
	*((BYTE*)(_this + 0x1F)) = 0xFF;
	*((BYTE*)(_this + 0x20)) = 0xFF;
	*((BYTE*)(_this + 0x21)) = RulesNorthAmerica;
	*((BYTE*)(_this + 0x22)) = 0;
	return _this;
}

void setup_concacaf_continent() {
	setup_concacaf_champions_cup();
}