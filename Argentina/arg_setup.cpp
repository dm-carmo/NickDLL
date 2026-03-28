#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "arg_first.h"
#include "arg_second.h"
#include "arg_third_metro.h"
#include "arg_third_interior.h"
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
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 3;
	}
	else {
		nation_data->num_of_comps = 5;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xF6);
	arg_first_init(pMem, start_year, get_comp(ARG_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xF6);
	arg_second_init(pMem, start_year, get_comp(ARG_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	if ((selected & 4) != 0) {
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		arg_third_metro_init(pMem, start_year, get_comp(ARG_THIRD_METRO_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xF2);
		arg_third_interior_init(pMem, start_year, get_comp(ARG_THIRD_INTERIOR_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

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
	setup_arg_third_metro();
	setup_arg_third_interior();
	setup_arg_cup();

	// transfer window adjustment
	//WriteBytes(0x40a6af, 1, 0xd);
	//WriteBytes(0x40a6b4, 1, 0x0);
	//WriteBytes(0x40a6ca, 1, 0x9);
	//WriteBytes(0x40a6cf, 1, 0x2);
	WriteBytes(0x40a6ae, 1, Saturday);
	WriteBytes(0x40a6af, 1, 0x14);
	WriteBytes(0x40a6b4, 1, 0xb);
	WriteBytes(0x40a6c9, 1, Tuesday);
	WriteBytes(0x40a6ca, 1, 0x1b);
	WriteBytes(0x40a6cf, 1, 0x0);
	WriteBytes(0x40a6e4, 1, 0x6);
	WriteBytes(0x40a6e6, 4, 0xc6, 0x40, 0x4, 0x6);
	WriteBytes(0x40a701, 1, 0x1e);
	WriteBytes(0x40a706, 1, 0x7);
}

void argentina_restructure() {
	cm3_club_comps* arg_first = get_comp(ARG_FIRST_9CF());
	cm3_club_comps* arg_second = get_comp(ARG_SECOND_9CF());
	cm3_club_comps* arg_third_metro = get_comp(ARG_THIRD_METRO_9CF());
	cm3_club_comps* arg_third_int = get_comp(ARG_THIRD_INTERIOR_9CF());
	arg_third_int->ClubCompReputation = 6;
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());

	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(ARG_THIRD_METRO_9CF());
	for (cm3_clubs* c : lower_clubs) c->ClubDivision = a_lower;

	vector<cm3_clubs*> metro_clubs = find_clubs_of_comp_reserve_division(ARG_CUP_9CF());
	for (cm3_clubs* c : metro_clubs) c->ClubReserveDivision = arg_third_metro;

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
	vector<string> d3m_clubs = {
		"CA Acassuso",
		"CA Argentino (Merlo)",
		"CA Argentino de Quilmes",
		"CA Brown (Adrogué)",
		"Club Comunicaciones",
		"Club Deportivo Armenio",
		"CSC Deportivo Laferrere",
		"CS Deportivo Merlo",
		"CS Dock Sud",
		"CA Excursionistas",
		"Club Atlético Fénix",
		"CA Ferrocarril Midland",
		"CSD Flandria",
		"CSD Liniers",
		"Real Pilar FC",
		"Sacachispas FC",
		"CSD San Martín (Burzaco)",
		"Club Sportivo Italiano",
		"CD UAI Urquiza",
		"Club Villa Dálmine",
		"CA Villa San Carlos",
	};
	vector<string> d3f_clubs = {
		"CA 9 de Julio (Rafaela)",
		"CD Argentino (Monte Maíz)",
		"CSB Atenas (Río Cuarto)",
		"Atlético Rafaela",
		"CA Bartolomé Mitre (Posadas)",
		"CS Ben Hur",
		"CA Boca Unidos",
		"Cipolletti de Río Negro",
		"Club Ciudad de Bolivar",
		"CA Costa Brava",
		"CM Crucero del Norte",
		"Círculo Deportivo",
		"CAS Defensores de Belgrano (Villa Ramallo)",
		"Club Deportivo Rincón",
		"Douglas Haig",
		"CA El Linqueño",
		"CA Germinal",
		"CSCD Gimnasia y Esgrima (Chivilcoy)",
		"Gimnasia y Esgrima de Concepción del Uruguay",
		"Club Social y Atlético Guillermo Brown",
		"Gutiérrez SC",
		"CA Huracán Las Heras",
		"CA Independiente (Chivilcoy)",
		"Juventud Antoniana",
		"CA Juventud Unida Universitario",
		"CA Kimberley",
		"Olimpo de Bahía Blanca",
		"CB Ramón Santamarina",
		"San Martín de Mendoza",
		"CS General San Martín (Formosa)",
		"CA Sarmiento (La Banda)",
		"CA Sarmiento (Resistencia)",
		"Club Sol de América (Formosa)",
		"Club Sol de Mayo",
		"Sportivo Belgrano (San Francisco)",
		"CS Estudiantes (San Luis)",
		"Sportivo AC (Las Parejas)",
		"Villa Mitre de Bahía Blanca",
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
	for (string s : d3m_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = arg_third_metro;
		club->ClubReserveDivision = arg_third_metro;
	}
	for (string s : d3f_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = arg_third_int;
		club->ClubReserveDivision = arg_third_int;
	}

}