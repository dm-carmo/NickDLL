#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void poland_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 10;
	DWORD* awards_list = (DWORD*)cm0102_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// D1 awards
	BYTE* pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, POL_FIRST_TEAM_OF_WEEK_9CF(), 0, 0, POL_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POL_FIRST_PLAYER_OF_YEAR_9CF(), 3000, 1500, POL_FIRST_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POL_FIRST_YOUNG_PLAYER_OF_YEAR_9CF(), 2000, 500, POL_FIRST_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POL_FIRST_MANAGER_OF_YEAR_9CF(), 2500, 1250, POL_FIRST_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, POL_FIRST_TEAM_OF_YEAR_9CF(), 2000, 750, POL_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// D2 awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, POL_SECOND_TEAM_OF_WEEK_9CF(), 0, 0, POL_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POL_SECOND_PLAYER_OF_YEAR_9CF(), 2000, 1000, POL_SECOND_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POL_SECOND_YOUNG_PLAYER_OF_YEAR_9CF(), 1000, 250, POL_SECOND_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POL_SECOND_MANAGER_OF_YEAR_9CF(), 1500, 750, POL_SECOND_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, POL_SECOND_TEAM_OF_YEAR_9CF(), 1000, 375, POL_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) pol_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call poland_awards
		add esp, 0x8
		ret 4
	}
}

char pol_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 15, June, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_768CF0(_this, POL_FIRST_9CF(), current_date, awards_list[1], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, POL_FIRST_9CF(), current_date, awards_list[2], 21, 0, 17, -1, -1, -1, -1);
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[3], POL_FIRST_9CF());
		yearly_team_award_nominate_7698F0(_this, POL_FIRST_9CF(), awards_list[4]);
		yearly_player_award_nominate_768CF0(_this, POL_SECOND_9CF(), current_date, awards_list[6], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, POL_SECOND_9CF(), current_date, awards_list[7], 21, 0, 17, -1, -1, -1, -1);
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[8], POL_SECOND_9CF());
		yearly_team_award_nominate_7698F0(_this, POL_SECOND_9CF(), awards_list[9]);
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) pol_awards_2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call pol_awards_2
		add esp, 0x8
		ret 4
	}
}

void pol_awards_staff_history(BYTE* _this) {

}

void __declspec(naked) pol_awards_staff_history_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call pol_awards_staff_history
		add esp, 0x4
		ret
	}
}

void pol_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[0]) {
		sub_769C70(_this, POL_FIRST_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[5]) {
		sub_769C70(_this, POL_SECOND_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) pol_awards_team_of_week_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call pol_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_pol_awards() {
	PatchFunction(0x7CD1C0, (DWORD)&pol_awards_c);
	PatchFunction(0x7CD630, (DWORD)&pol_awards_2_c);
	PatchFunction(0x7CD790, (DWORD)&pol_awards_staff_history_c);
	PatchFunction(0x7CD810, (DWORD)&pol_awards_team_of_week_c);
}