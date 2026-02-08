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

DWORD bra_setup_c(BYTE* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	*(WORD*)(nation_data + 0x32) = 18;
	*(BYTE*)(nation_data + 0x34) = 0;
	*(WORD*)(nation_data + 0x35) = start_year;
	*(WORD*)(nation_data + 0x37) = 6;
	*(WORD*)(nation_data + 0x41) = 14;
	*(BYTE*)(nation_data + 0x43) = 11;
	*(WORD*)(nation_data + 0x44) = start_year;
	*(WORD*)(nation_data + 0x46) = 6;
	*(DWORD*)(nation_data + 0xc) = 18;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(*(DWORD*)(nation_data + 0xc) * 4);
	*(DWORD*)(nation_data + 0x10) = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Série A
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_first_init(pMem, start_year, &(*club_comps)[BRA_FIRST_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Série B
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_second_init(pMem, start_year, &(*club_comps)[BRA_SECOND_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Série C
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_third_init(pMem, start_year, &(*club_comps)[BRA_THIRD_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Série D
	pMem = (BYTE*)sub_944CF1_operator_new(0xF2);
	bra_fourth_init(pMem, start_year, &(*club_comps)[BRA_FOURTH_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Baiano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_bahia_init(pMem, start_year, &(*club_comps)[BRA_BAHIA_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Carioca
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_rio_init(pMem, start_year, &(*club_comps)[BRA_RIO_DE_JANEIRO_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Catarinense
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_catarina_init(pMem, start_year, &(*club_comps)[BRA_SANTA_CATARINA_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Central
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_central_init(pMem, start_year, &(*club_comps)[BRA_CENTRAL_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Gaúcho
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_gaucho_init(pMem, start_year, &(*club_comps)[BRA_GAUCHO_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Goiano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_goias_init(pMem, start_year, &(*club_comps)[BRA_GOIAS_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Mineiro
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_minas_init(pMem, start_year, &(*club_comps)[BRA_MINAS_GERAIS_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Nordeste
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_northeast_init(pMem, start_year, &(*club_comps)[BRA_NORTHEAST_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Norte
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_north_init(pMem, start_year, &(*club_comps)[BRA_NORTH_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Paranaense
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_parana_init(pMem, start_year, &(*club_comps)[BRA_PARANA_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Paulista
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_paulo_init(pMem, start_year, &(*club_comps)[BRA_SAO_PAULO_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Pernambucano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_pernambuco_init(pMem, start_year, &(*club_comps)[BRA_PERNAMBUCO_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	bra_cup_init(pMem, start_year, &(*club_comps)[BRA_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Champions Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	bra_super_init(pMem, start_year, &(*club_comps)[BRA_CHAMPIONS_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 2, January, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = start_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = (DWORD) & (*club_comps)[BRA_CHAMPIONS_CUP_9CF()];
	return 1;
}

void setup_bra_nation() {
	WriteDWORD(0x667AC7 + 6, (DWORD)&bra_setup_c);
	// move start date forward a bit
	WriteBytes(0x667B17, 1, 30);
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
}