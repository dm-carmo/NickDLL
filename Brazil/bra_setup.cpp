#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "bra_first.h"
#include "bra_second.h"
#include "bra_third.h"
#include "bra_fourth.h"
#include "bra_reg_bahia.h"
#include "bra_reg_catarina.h"
#include "bra_reg_gaucho.h"
#include "bra_reg_goias.h"
#include "bra_reg_minas.h"
#include "bra_reg_parana.h"
#include "bra_reg_paulo.h"
#include "bra_reg_pernambuco.h"
#include "bra_reg_rio.h"
#include "bra_reg_central.h"
#include "bra_reg_north.h"
#include "bra_reg_northeast.h"
#include "bra_cup.h"
#include "bra_super.h"
#include "bra_awards.h"
#include "bra_state_league_list.h"

DWORD bra_setup_c(playable_nation_data* nation_data) {
	state_leagues = {
		BRA_BAHIA_STATE_9CF(),
		BRA_RIO_DE_JANEIRO_STATE_9CF(),
		BRA_SANTA_CATARINA_STATE_9CF(),
		BRA_CENTRAL_STATE_9CF(),
		BRA_GAUCHO_STATE_9CF(),
		BRA_GOIAS_STATE_9CF(),
		BRA_MINAS_GERAIS_STATE_9CF(),
		BRA_NORTHEAST_STATE_9CF(),
		BRA_NORTH_STATE_9CF(),
		BRA_PARANA_STATE_9CF(),
		BRA_SAO_PAULO_STATE_9CF(),
		BRA_PERNAMBUCO_STATE_9CF(),
	};
	state_lower = {
		BRA_BAHIA_LOWER_9CF(),
		BRA_RIO_DE_JANEIRO_LOWER_9CF(),
		BRA_SANTA_CATARINA_LOWER_9CF(),
		BRA_CENTRAL_LOWER_9CF(),
		BRA_GAUCHO_LOWER_9CF(),
		BRA_GOIAS_LOWER_9CF(),
		BRA_MINAS_GERAIS_LOWER_9CF(),
		BRA_NORTHEAST_LOWER_9CF(),
		BRA_NORTH_LOWER_9CF(),
		BRA_PARANA_LOWER_9CF(),
		BRA_SAO_PAULO_LOWER_9CF(),
		BRA_PERNAMBUCO_LOWER_9CF(),
	};

	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	
	nation_data->contract_start_day = 3;
	nation_data->contract_start_month = January;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 6;
	
	nation_data->contract_end_day = 14;
	nation_data->contract_end_month = December;
	nation_data->contract_end_year = start_year;
	nation_data->f70 = 6;
	nation_data->num_of_comps = 18;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Série A
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_first_init(pMem, start_year, get_comp(BRA_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Série B
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_second_init(pMem, start_year, get_comp(BRA_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Série C
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_third_init(pMem, start_year, get_comp(BRA_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Série D
	pMem = (BYTE*)sub_944CF1_operator_new(0xF2);
	bra_fourth_init(pMem, start_year, get_comp(BRA_FOURTH_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Baiano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_bahia_init(pMem, start_year, get_comp(BRA_BAHIA_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Carioca
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_rio_init(pMem, start_year, get_comp(BRA_RIO_DE_JANEIRO_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Catarinense
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_catarina_init(pMem, start_year, get_comp(BRA_SANTA_CATARINA_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Central
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_central_init(pMem, start_year, get_comp(BRA_CENTRAL_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Gaúcho
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_gaucho_init(pMem, start_year, get_comp(BRA_GAUCHO_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Goiano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_goias_init(pMem, start_year, get_comp(BRA_GOIAS_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Mineiro
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_minas_init(pMem, start_year, get_comp(BRA_MINAS_GERAIS_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Nordeste
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_northeast_init(pMem, start_year, get_comp(BRA_NORTHEAST_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Norte
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_north_init(pMem, start_year, get_comp(BRA_NORTH_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Paranaense
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_parana_init(pMem, start_year, get_comp(BRA_PARANA_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Paulista
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_paulo_init(pMem, start_year, get_comp(BRA_SAO_PAULO_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Pernambucano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_pernambuco_init(pMem, start_year, get_comp(BRA_PERNAMBUCO_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	bra_cup_init(pMem, start_year, get_comp(BRA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Champions Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	bra_super_init(pMem, start_year, get_comp(BRA_CHAMPIONS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(BRA_CHAMPIONS_CUP_9CF());
	return 1;
}

void setup_bra_nation() {
	// minor fix related to state leagues new start/end
	WriteBytes(0x44429C, 1, March);
	WriteBytes(0x44429E, 1, 31);
	setup_bra_first();
	setup_bra_second();
	setup_bra_third();
	setup_bra_fourth();
	setup_bra_reg_bahia();
	setup_bra_reg_catarina();
	setup_bra_reg_gaucho();
	setup_bra_reg_goias();
	setup_bra_reg_minas();
	setup_bra_reg_parana();
	setup_bra_reg_paulo();
	setup_bra_reg_pernambuco();
	setup_bra_reg_rio();
	setup_bra_reg_central();
	setup_bra_reg_north();
	setup_bra_reg_northeast();
	setup_bra_cup();
	setup_bra_super();
	setup_bra_awards();

	// transfer window adjustment
	WriteBytes(0x43f1be, 1, 0x5);
	WriteBytes(0x43f1c8, 1, 0x3);
	WriteBytes(0x43f1c9, 1, 0x2);
	WriteBytes(0x43f1d5, 1, 0x6);
	WriteBytes(0x43f1de, 1, 0xb);
	WriteBytes(0x43f1df, 1, 0x8);
	// foreign player limits
	WriteBytes(0x43f2cb, 1, 0x9);
}