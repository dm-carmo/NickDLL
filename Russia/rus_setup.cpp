#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "rus_premier.h"
#include "rus_first.h"
#include "rus_second_a.h"
#include "rus_cup.h"
#include "rus_super.h"
#include "rus_awards.h"
#include <Helpers\9cf_constants.h>

DWORD rus_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	rus_premier_init(pMem, *current_year, get_comp(RUS_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	rus_first_init(pMem, *current_year, get_comp(RUS_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	rus_second_a_init(pMem, *current_year, get_comp(RUS_SECOND_A_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	rus_cup_init(pMem, *current_year, get_comp(RUS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	rus_super_init(pMem, *current_year, get_comp(RUS_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(RUS_SUPER_CUP_9CF());
	return 1;
}

void __declspec(naked) russia_foreign_rules()
{
	__asm
	{
		mov eax, dword ptr ds : [eax]
		cmp eax, dword ptr ds : [0x9CF930]
		je rus_prm_fgn
		cmp eax, 0xc4 // temp for saudi
		je rus_prm_fgn
		cmp eax, 0x179 // temp for saudi
		je rus_prm_fgn
		cmp eax, 0x18d // temp for saudi
		je rus_prm_fgn
		cmp eax, dword ptr ds : [0x9CF92C]
		je rus_first_fgn
		cmp eax, 0x18c // temp for saudi
		je rus_first_fgn
		cmp eax, dword ptr ds : [0x9CF918]
		je rus_second_fgn
		cmp eax, dword ptr ds : [0x9CF934]
		je rus_prm_fgn
		mov byte ptr ds : [edx + 2] , -1
		ret 8
		rus_prm_fgn :
		mov byte ptr ds : [edx + 2] , 8
		ret 8
		rus_first_fgn :
		mov byte ptr ds : [edx + 2] , 4
		ret 8
		rus_second_fgn :
		mov byte ptr ds : [edx + 2] , 0
		ret 8
	}
}

void setup_rus_nation() {
	setup_rus_premier();
	setup_rus_first();
	setup_rus_second_a();
	setup_rus_cup();
	setup_rus_super();
	setup_rus_awards();

	PatchFunction(0x7ec96c, (DWORD)&russia_foreign_rules);
}

void russia_restructure() {
	cm3_club_comps* d2 = get_comp(RUS_SECOND_A_9CF());
	vector<cm3_clubs*> d2_g = find_clubs_of_comp(RUS_SECOND_A_GOLD_9CF());
	for (cm3_clubs* club : d2_g) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d2;
	}
	vector<cm3_clubs*> d2_s = find_clubs_of_comp(RUS_SECOND_A_SILVER_9CF());
	for (cm3_clubs* club : d2_s) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d2;
	}
}