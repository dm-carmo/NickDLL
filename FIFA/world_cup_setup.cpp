#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "fifa_world_cup.h"
#include "world_cup_quals_afc.h"
#include "world_cup_quals_caf.h"
#include "world_cup_quals_concacaf.h"
#include "world_cup_quals_ofc.h"
#include "world_cup_quals_conmebol.h"
#include "world_cup_quals_uefa.h"
#include "world_cup_playoffs.h"

DWORD world_cup_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 8;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0x192);
	fifa_world_cup_init(pMem, *current_year, get_comp(FIFA_WORLD_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	world_cup_quals_caf_init(pMem, *current_year, get_comp(WORLD_CUP_CAF_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	world_cup_quals_afc_init(pMem, *current_year, get_comp(WORLD_CUP_AFC_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	world_cup_quals_concacaf_init(pMem, *current_year, get_comp(WORLD_CUP_CONCACAF_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	world_cup_quals_uefa_init(pMem, *current_year, get_comp(WORLD_CUP_UEFA_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	world_cup_quals_ofc_init(pMem, *current_year, get_comp(WORLD_CUP_OFC_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	world_cup_quals_conmebol_init(pMem, *current_year, get_comp(WORLD_CUP_CONMEBOL_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	world_cup_playoffs_init(pMem, *current_year, get_comp(WORLD_CUP_PLAYOFFS_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 25, July, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 2;
	nation_data->super_cup = 0;
	return 1;
}

void __declspec(naked) show_playoff_in_menu()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf778]
		je is_wc_comp
		cmp eax, dword ptr ds : [0x9cf928]
		je is_wc_comp
		push 0x669511
		ret
		is_wc_comp :
		push 0x669564
			ret
	}
}

void __declspec(naked) year_offset_in_landmarks()
{
	__asm
	{
		cmp ebx, dword ptr ds : [0x9cf76c]
		je ret_add_2_year
		cmp ebx, dword ptr ds : [0x9cf770]
		je ret_add_3_year
		cmp ebx, dword ptr ds : [0x9cf774]
		je ret_add_3_year
		cmp ebx, dword ptr ds : [0x9cf778]
		je ret_add_3_year
		cmp ebx, dword ptr ds : [0x9cf77c]
		je ret_add_3_year
		cmp ebx, dword ptr ds : [0x9cf780]
		je ret_add_1_year
		cmp ebx, dword ptr ds : [0x9cf784]
		je ret_add_1_year
		cmp ebx, dword ptr ds : [0x9cf928]
		je ret_add_1_year
		cmp ebx, dword ptr ds : [0x9cf890]
		je ret_add_2_year
		cmp ebx, dword ptr ds : [0x9cf788]
		je ret_add_3_year
		ret_dont_add_years :
		push 0x46b441
			ret
			ret_add_1_year :
		mov ax, word ptr ds : [esi + 4]
			add ax, 1
			push 0x46b44f
			ret
			ret_add_2_year :
		mov ax, word ptr ds : [esi + 4]
			add ax, 2
			push 0x46b44f
			ret
			ret_add_3_year :
		mov ax, word ptr ds : [esi + 4]
			add ax, 3
			push 0x46b44f
			ret
	}
}

void __declspec(naked) unknown_check_2()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf778]
		je unknown_2
		cmp eax, dword ptr ds : [0x9cf928]
		je unknown_2
		push 0x669ac6
		ret
		unknown_2 :
		push 0x669acf
			ret
	}
}

void __declspec(naked) unknown_check_3()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf78c]
		je unknown_3
		cmp eax, dword ptr ds : [0x9cf788]
		je unknown_3
		cmp eax, dword ptr ds : [0x9cf890]
		je unknown_3
		push 0x669bb6
		ret
		unknown_3 :
		push 0x669bbf
			ret
	}
}

void __declspec(naked) international_comps_to_continent()
{
	__asm
	{
		cmp edx, dword ptr ds : [0x9cf77c]
		je to_africa
		cmp edx, dword ptr ds : [0x9cf7ac]
		je to_africa
		cmp edx, dword ptr ds : [0x9cf890]
		je to_africa
		cmp edx, dword ptr ds : [0x9cf774]
		je to_asia
		cmp edx, dword ptr ds : [0x9cf790]
		je to_asia
		cmp edx, dword ptr ds : [0x9cf788]
		je to_asia
		cmp edx, dword ptr ds : [0x9cf770]
		je to_n_america
		cmp edx, dword ptr ds : [0x9cf78c]
		je to_n_america
		cmp edx, dword ptr ds : [0x9cf88c]
		je to_n_america
		cmp edx, dword ptr ds : [0x9cf780]
		je to_europe
		cmp edx, dword ptr ds : [0x9cf7a4]
		je to_europe
		cmp edx, dword ptr ds : [0x9cf784]
		je to_europe
		cmp edx, dword ptr ds : [0x9cf888]
		je to_europe
		cmp edx, dword ptr ds : [0x9cf76c]
		je to_oceania
		cmp edx, dword ptr ds : [0x9cf8a0]
		je to_oceania
		cmp edx, dword ptr ds : [0x9cf778]
		je to_s_america
		cmp edx, dword ptr ds : [0x9cf7a8]
		je to_s_america
		cmp edx, dword ptr ds : [0x9cf7a0]
		je to_world
		push 0x6b63f6
		ret
		to_africa :
		mov ecx, dword ptr ds : [0x9cfa08]
			jmp continent_end
			to_asia :
		mov ecx, dword ptr ds : [0x9cfa0c]
			jmp continent_end
			to_europe :
		mov ecx, dword ptr ds : [0x9cfa10]
			jmp continent_end
			to_oceania :
		mov ecx, dword ptr ds : [0x9cfa18]
			jmp continent_end
			to_n_america :
		mov ecx, dword ptr ds : [0x9cfa14]
			jmp continent_end
			to_s_america :
		mov ecx, dword ptr ds : [0x9cfa1c]
			jmp continent_end
			to_world :
		push 0x6b6400
			ret
			continent_end :
		push 0x6b63d7
			ret
	}
}

void setup_world_cup_comps() {
	setup_fifa_world_cup();
	setup_world_cup_quals_afc();
	setup_world_cup_quals_caf();
	setup_world_cup_quals_concacaf();
	setup_world_cup_quals_ofc();
	setup_world_cup_quals_conmebol();
	setup_world_cup_quals_uefa();
	setup_world_cup_playoffs();

	PatchFunction(0x66955c, (DWORD)&show_playoff_in_menu);
	PatchFunction(0x46b409, (DWORD)&year_offset_in_landmarks);
	// tag comp as being part of "World Cup" menu?
	PatchFunction(0x669abe, (DWORD)&unknown_check_2);
	// tag comp as being part of "International" menu?
	PatchFunction(0x669bae, (DWORD)&unknown_check_3);
	PatchFunction(0x6b6358, (DWORD)&international_comps_to_continent);
}