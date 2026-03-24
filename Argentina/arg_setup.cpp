#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "arg_first.h"
#include "arg_second.h"
#include "arg_cup.h"

DWORD arg_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);

	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = January;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 6;

	nation_data->contract_end_day = 15;
	nation_data->contract_end_month = December;
	nation_data->contract_end_year = start_year;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 3;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xF6);
	arg_first_init(pMem, start_year, get_comp(ARG_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xF6);
	arg_second_init(pMem, start_year, get_comp(ARG_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	arg_cup_init(pMem, start_year, get_comp(ARG_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_arg_nation() {
	WriteDWORD(0x66785c + 6, (DWORD)&arg_setup_c);
	setup_arg_first();
	setup_arg_second();
	setup_arg_cup();
}

void argentina_restructure() {
	cm3_club_comps* arg_first = get_comp(ARG_FIRST_9CF());
	cm3_club_comps* arg_second = get_comp(ARG_SECOND_9CF());

	vector<string> d1_clubs = {
		"Aldosivi",
		"Atlético Tucumán",
		"Belgrano de Córdoba",
		"CA Barracas Central",
		"CA Central Córdoba (SdE)",
		"CA Sarmiento (Junin)",
		"Club Deportivo Riestra",
		"Instituto de Córdoba",
		"San Martín de San Juan",
		"Unión de Santa Fé",
	};
	vector<string> d2_clubs = {
		"CA Agropecuario",
		"All Boys",
		"Almirante Brown",
		"CA Alvarado",
		"Arsenal de Sarandí",
		"CA Central Norte",
		"CA Chaco For Ever",
		"CA Colegiales",
		"Defensores de Belgrano",
		"CA Defensores Unidos (Zarate)",
		"Club Deportivo Maipú",
		"Deportivo Morón",
		"Gimnasia y Esgrima de Jujuy",
		"Gimnasia y Tiro de Salta",
		"CA Güemes",
		"Los Andes",
		"CA Mitre",
		"Nueva Chicago",
		"CA San Telmo",
		"CA Talleres (Remedios de Escalada)",
		"Temperley",
	};

	for (string s : d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = arg_first;
	}
	for (string s : d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = arg_second;
	}

}