#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void italy_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	BYTE selected = ((cm3_nations*)*(DWORD*)(_this + 0xE))->NationLeagueSelected;
	if ((selected & 4) == 0) {
		// not used for now
		*(WORD*)(_this + 0x8) = 20;
	}
	else {
		*(WORD*)(_this + 0x8) = 20;
	}
	DWORD* awards_list = (DWORD*)cm0102_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// Serie A awards
	BYTE* pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ITA_SERIE_A_TEAM_OF_WEEK_9CF(), 0, 0, ITA_SERIE_A_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ITA_SERIE_A_TEAM_OF_YEAR_9CF(), 6500, 2500, ITA_SERIE_A_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_A_MANAGER_OF_YEAR_9CF(), 7000, 2500, ITA_SERIE_A_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_A_PLAYER_OF_YEAR_9CF(), 8500, 5000, ITA_SERIE_A_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_A_YOUNG_PLAYER_OF_YEAR_9CF(), 7500, 4000, ITA_SERIE_A_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_A_TOP_GOALSCORER_9CF(), 8000, 5000, ITA_SERIE_A_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_A_DEFENDER_OF_YEAR_9CF(), 7500, 5000, ITA_SERIE_A_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_A_GOALKEEPER_OF_YEAR_9CF(), 7500, 5000, ITA_SERIE_A_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_A_ITA_PLAYER_OF_YEAR_9CF(), 7500, 5000, ITA_SERIE_A_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_A_FOREIGN_PLAYER_OF_YEAR_9CF(), 7500, 5000, ITA_SERIE_A_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Serie B awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ITA_SERIE_B_TEAM_OF_WEEK_9CF(), 0, 0, ITA_SERIE_B_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ITA_SERIE_B_TEAM_OF_YEAR_9CF(), 3500, 1750, ITA_SERIE_B_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_B_MANAGER_OF_YEAR_9CF(), 5000, 1500, ITA_SERIE_B_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_B_PLAYER_OF_YEAR_9CF(), 6000, 2000, ITA_SERIE_B_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_B_TOP_GOALSCORER_9CF(), 5500, 2000, ITA_SERIE_B_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;
	// Serie C awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ITA_SERIE_C1_A_TEAM_OF_WEEK_9CF(), 0, 0, ITA_SERIE_C_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ITA_SERIE_C1_A_TEAM_OF_YEAR_9CF(), 1500, 750, ITA_SERIE_C_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_C1_A_MANAGER_OF_YEAR_9CF(), 3000, 1000, ITA_SERIE_C_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_C1_A_PLAYER_OF_YEAR_9CF(), 4500, 1500, ITA_SERIE_C_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ITA_SERIE_C1_A_TOP_GOALSCORER_9CF(), 2000, 1000, ITA_SERIE_C_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) ita_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call italy_awards
		add esp, 0x8
		ret 4
	}
}

char ita_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	BYTE selected = ((cm3_nations*)nation)->NationLeagueSelected;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 10, June, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[2], ITA_SERIE_A_9CF());
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[12], ITA_SERIE_B_9CF());
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[17], ITA_SERIE_C_9CF());
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_A_9CF(), current_date, awards_list[3], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_A_9CF(), current_date, awards_list[4], 23, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_A_9CF(), current_date, awards_list[5], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_A_9CF(), current_date, awards_list[6], -1, 6, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_A_9CF(), current_date, awards_list[7], -1, 1, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_A_9CF(), current_date, awards_list[8], -1, 0, 2, NATION_ITALY_9CF(), -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_A_9CF(), current_date, awards_list[9], -1, 0, 2, -1, -1, NATION_ITALY_9CF(), -1);
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_B_9CF(), current_date, awards_list[13], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_B_9CF(), current_date, awards_list[14], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_C_9CF(), current_date, awards_list[18], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, ITA_SERIE_C_9CF(), current_date, awards_list[19], -1, 0, 2, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, ITA_SERIE_A_9CF(), awards_list[1]);
		yearly_team_award_nominate_7698F0(_this, ITA_SERIE_B_9CF(), awards_list[11]);
		yearly_team_award_nominate_7698F0(_this, ITA_SERIE_C_9CF(), awards_list[16]);
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) ita_awards_2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ita_awards_2
		add esp, 0x8
		ret 4
	}
}

void ita_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	BYTE selected = ((cm3_nations*)nation)->NationLeagueSelected;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[0]) {
		sub_769C70(_this, ITA_SERIE_A_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[10]) {
		sub_769C70(_this, ITA_SERIE_B_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[15]) {
		sub_769C70(_this, ITA_SERIE_C_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) ita_awards_team_of_week_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ita_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_ita_awards()
{
	PatchFunction(0x65FEC0, (DWORD)&ita_awards_c);
	PatchFunction(0x660EC0, (DWORD)&ita_awards_2_c);
	PatchFunction(0x661330, (DWORD)&ita_awards_team_of_week_c);
}
