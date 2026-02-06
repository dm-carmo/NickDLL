#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "bra_first.h"
#include "bra_second.h"
#include "bra_third.h"
#include "bra_fourth.h"

static DWORD(__thiscall* bra_reg_bahia_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x42f2d0);
static DWORD(__thiscall* bra_reg_central_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x4304b0);
static DWORD(__thiscall* bra_reg_gaucho_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x4317c0);
static DWORD(__thiscall* bra_reg_goias_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x432b50);
static DWORD(__thiscall* bra_reg_minas_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x433d50);
static DWORD(__thiscall* bra_reg_north_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x435340);
static DWORD(__thiscall* bra_reg_northeast_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x4363f0);
static DWORD(__thiscall* bra_reg_parana_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x437400);
static DWORD(__thiscall* bra_reg_pernambuco_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x4388f0);
static DWORD(__thiscall* bra_reg_rio_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x439a40);
static DWORD(__thiscall* bra_reg_s_catarina_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x43b130);
static DWORD(__thiscall* bra_reg_s_paulo_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x43c280);
static DWORD(__thiscall* bra_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x427430);
static DWORD(__thiscall* bra_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x4259a0);

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
	/*
	// Campeonato Baiano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_bahia_setup(pMem, start_year, &(*club_comps)[BRA_BAHIA_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Carioca
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_rio_setup(pMem, start_year, &(*club_comps)[BRA_RIO_DE_JANEIRO_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Catarinense
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_s_catarina_setup(pMem, start_year, &(*club_comps)[BRA_SANTA_CATARINA_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Central
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_central_setup(pMem, start_year, &(*club_comps)[BRA_CENTRAL_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Gaúcho
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_gaucho_setup(pMem, start_year, &(*club_comps)[BRA_GAUCHO_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Goiano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_goias_setup(pMem, start_year, &(*club_comps)[BRA_GOIAS_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Mineiro
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_minas_setup(pMem, start_year, &(*club_comps)[BRA_MINAS_GERAIS_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Nordeste
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_northeast_setup(pMem, start_year, &(*club_comps)[BRA_NORTHEAST_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Norte
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_north_setup(pMem, start_year, &(*club_comps)[BRA_NORTH_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Paranaense
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_parana_setup(pMem, start_year, &(*club_comps)[BRA_PARANA_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Paulista
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_s_paulo_setup(pMem, start_year, &(*club_comps)[BRA_SAO_PAULO_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Pernambucano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_pernambuco_setup(pMem, start_year, &(*club_comps)[BRA_PERNAMBUCO_STATE_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	bra_cup_setup(pMem, start_year, &(*club_comps)[BRA_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	// Champions Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	bra_super_setup(pMem, start_year, &(*club_comps)[BRA_CHAMPIONS_CUP_9CF()]);
	nation_comps[i++] = (DWORD)pMem;
	*/

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 12, January, 2025, (DWORD*)-1);
	*(WORD*)(nation_data + 0x15) = *(WORD*)cm_date;
	*(WORD*)(nation_data + 0x1B) = start_year;
	*(BYTE*)(nation_data + 0x1D) = 1;
	*(DWORD*)(nation_data + 0x26) = 0;
	return 1;
}

void setup_bra_nation() {
	WriteDWORD(0x667AC7 + 6, (DWORD)&bra_setup_c);
	setup_bra_first();
	setup_bra_second();
	setup_bra_third();
	setup_bra_fourth();
}