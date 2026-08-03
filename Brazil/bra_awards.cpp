#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "bra_state_league_list.cpp"

void brazil_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 63;

	DWORD* awards_list = (DWORD*)cm0102_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// First Division awards
	BYTE* pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_FIRST_TEAM_OF_WEEK_9CF(), 2000, 0, BRA_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_FIRST_PLAYER_OF_YEAR_9CF(), 6000, 3500, BRA_FIRST_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_FIRST_TOP_GOALSCORER_9CF(), 7000, 3000, BRA_FIRST_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_FIRST_YOUNG_PLAYER_OF_YEAR_9CF(), 5000, 2500, BRA_FIRST_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_FIRST_TEAM_OF_YEAR_9CF(), 5000, 2000, BRA_FIRST_9CF(), 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Second Division awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_SECOND_TEAM_OF_WEEK_9CF(), 1500, 0, BRA_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_SECOND_PLAYER_OF_YEAR_9CF(), 4000, 1000, BRA_SECOND_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_SECOND_TOP_GOALSCORER_9CF(), 4500, 1500, BRA_SECOND_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_SECOND_YOUNG_PLAYER_OF_YEAR_9CF(), 3500, 1500, BRA_SECOND_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_SECOND_TEAM_OF_YEAR_9CF(), 3500, 1000, BRA_SECOND_9CF(), 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Third Division awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_THIRD_TEAM_OF_WEEK_9CF(), 1000, 0, BRA_THIRD_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_THIRD_PLAYER_OF_YEAR_9CF(), 3000, 500, BRA_THIRD_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_THIRD_TOP_GOALSCORER_9CF(), 3500, 500, BRA_THIRD_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_THIRD_YOUNG_PLAYER_OF_YEAR_9CF(), 2500, 1000, BRA_THIRD_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_THIRD_TEAM_OF_YEAR_9CF(), 2500, 500, BRA_THIRD_9CF(), 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Bahia awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_BAHIA_TEAM_OF_WEEK_9CF(), 500, 0, BRA_BAHIA_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_BAHIA_BEST_PLAYER_9CF(), 5000, 1500, BRA_BAHIA_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_BAHIA_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_BAHIA_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_BAHIA_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_BAHIA_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Rio de Janeiro awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_RIO_DE_JANEIRO_TEAM_OF_WEEK_9CF(), 500, 0, BRA_RIO_DE_JANEIRO_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_RIO_DE_JANEIRO_BEST_PLAYER_9CF(), 5000, 1500, BRA_RIO_DE_JANEIRO_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_RIO_DE_JANEIRO_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_RIO_DE_JANEIRO_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_RIO_DE_JANEIRO_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_RIO_DE_JANEIRO_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Santa Catarina awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_SANTA_CATARINA_TEAM_OF_WEEK_9CF(), 500, 0, BRA_SANTA_CATARINA_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_SANTA_CATARINA_BEST_PLAYER_9CF(), 5000, 1500, BRA_SANTA_CATARINA_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_SANTA_CATARINA_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_SANTA_CATARINA_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_SANTA_CATARINA_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_SANTA_CATARINA_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Central awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_CENTRAL_TEAM_OF_WEEK_9CF(), 500, 0, BRA_CENTRAL_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_CENTRAL_BEST_PLAYER_9CF(), 5000, 1500, BRA_CENTRAL_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_CENTRAL_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_CENTRAL_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_CENTRAL_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_CENTRAL_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Rio Grande do Sul awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_GAUCHO_TEAM_OF_WEEK_9CF(), 500, 0, BRA_GAUCHO_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_GAUCHO_BEST_PLAYER_9CF(), 5000, 1500, BRA_GAUCHO_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_GAUCHO_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_GAUCHO_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_GAUCHO_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_GAUCHO_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Goiás awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_GOIAS_TEAM_OF_WEEK_9CF(), 500, 0, BRA_GOIAS_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_GOIAS_BEST_PLAYER_9CF(), 5000, 1500, BRA_GOIAS_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_GOIAS_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_GOIAS_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_GOIAS_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_GOIAS_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Minas Gerais awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_MINAS_GERAIS_TEAM_OF_WEEK_9CF(), 500, 0, BRA_MINAS_GERAIS_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_MINAS_GERAIS_BEST_PLAYER_9CF(), 5000, 1500, BRA_MINAS_GERAIS_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_MINAS_GERAIS_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_MINAS_GERAIS_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_MINAS_GERAIS_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_MINAS_GERAIS_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Northeast awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_NORTHEAST_TEAM_OF_WEEK_9CF(), 500, 0, BRA_NORTHEAST_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_NORTHEAST_BEST_PLAYER_9CF(), 5000, 1500, BRA_NORTHEAST_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_NORTHEAST_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_NORTHEAST_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_NORTHEAST_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_NORTHEAST_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// North awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_NORTH_TEAM_OF_WEEK_9CF(), 500, 0, BRA_NORTH_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_NORTH_BEST_PLAYER_9CF(), 5000, 1500, BRA_NORTH_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_NORTH_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_NORTH_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_NORTH_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_NORTH_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Paraná awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_PARANA_TEAM_OF_WEEK_9CF(), 500, 0, BRA_PARANA_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_PARANA_BEST_PLAYER_9CF(), 5000, 1500, BRA_PARANA_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_PARANA_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_PARANA_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_PARANA_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_PARANA_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// São Paulo awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_SAO_PAULO_TEAM_OF_WEEK_9CF(), 500, 0, BRA_SAO_PAULO_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_SAO_PAULO_BEST_PLAYER_9CF(), 5000, 1500, BRA_SAO_PAULO_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_SAO_PAULO_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_SAO_PAULO_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_SAO_PAULO_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_SAO_PAULO_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Pernambuco awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BRA_PERNAMBUCO_TEAM_OF_WEEK_9CF(), 500, 0, BRA_PERNAMBUCO_STATE_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_PERNAMBUCO_BEST_PLAYER_9CF(), 5000, 1500, BRA_PERNAMBUCO_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_PERNAMBUCO_TOP_GOALSCORER_9CF(), 4500, 1000, BRA_PERNAMBUCO_STATE_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BRA_PERNAMBUCO_BEST_GOALKEEPER_9CF(), 3000, 0, BRA_PERNAMBUCO_STATE_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) bra_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call brazil_awards
		add esp, 0x8
		ret 4
	}
}

char bra_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, April, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		for (int i = 0; i < 12; i++) {
			yearly_player_award_nominate_768CF0(_this, state_leagues[i], current_date, awards_list[16 + (i * 4)], -1, 0, 17, -1, -1, -1, -1);
			yearly_player_award_nominate_768CF0(_this, state_leagues[i], current_date, awards_list[17 + (i * 4)], -1, 0, 2, -1, -1, -1, -1);
			yearly_player_award_nominate_768CF0(_this, state_leagues[i], current_date, awards_list[18 + (i * 4)], -1, 1, 17, -1, -1, -1, -1);
		}
	}
	cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 16, December, *(WORD*)(current_date + 2), -1);
	date_day = *(WORD*)(cm_date);
	date_year = *(WORD*)(cm_date + 2);
	//leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_768CF0(_this, BRA_FIRST_9CF(), current_date, awards_list[1], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BRA_FIRST_9CF(), current_date, awards_list[2], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BRA_FIRST_9CF(), current_date, awards_list[3], 21, 0, 17, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, BRA_FIRST_9CF(), awards_list[4]);
		yearly_player_award_nominate_768CF0(_this, BRA_SECOND_9CF(), current_date, awards_list[6], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BRA_SECOND_9CF(), current_date, awards_list[7], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BRA_SECOND_9CF(), current_date, awards_list[8], 21, 0, 17, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, BRA_SECOND_9CF(), awards_list[9]);
		yearly_player_award_nominate_768CF0(_this, BRA_THIRD_9CF(), current_date, awards_list[11], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BRA_THIRD_9CF(), current_date, awards_list[12], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BRA_THIRD_9CF(), current_date, awards_list[13], 21, 0, 17, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, BRA_THIRD_9CF(), awards_list[14]);
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) bra_awards_2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call bra_awards_2
		add esp, 0x8
		ret 4
	}
}

void bra_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[0]) {
		sub_769C70(_this, BRA_FIRST_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[5]) {
		sub_769C70(_this, BRA_SECOND_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[10]) {
		sub_769C70(_this, BRA_THIRD_9CF(), award_addr);
		return;
	}
	for (int i = 0; i < 12; i++) {
		if (award_addr == awards_list[15 + (i * 4)]) {
			sub_769C70(_this, state_leagues[i], award_addr);
			return;
		}
	}
}

void __declspec(naked) bra_awards_team_of_week_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call bra_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_bra_awards() {
	PatchFunction(0x43D340, (DWORD)&bra_awards_c);
	PatchFunction(0x43E990, (DWORD)&bra_awards_2_c);
	PatchFunction(0x43F070, (DWORD)&bra_awards_team_of_week_c);
}