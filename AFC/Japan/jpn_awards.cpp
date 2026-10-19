#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\9cf_constants.h"

void japan_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 8;

	DWORD* awards_list = (DWORD*)cm0102_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// General awards
	BYTE* pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, JPN_MANAGER_OF_YEAR_9CF(), 5000, 0, -1, 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, JPN_PLAYER_OF_YEAR_9CF(), 5500, 1500, -1, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, JPN_TOP_GOALSCORER_9CF(), 5000, 500, -1, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, JPN_YOUNG_PLAYER_OF_YEAR_9CF(), 3000, 100, -1, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// J1
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, JPN_FIRST_TEAM_OF_WEEK_9CF(), 2000, 0, JPN_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, JPN_FIRST_TEAM_OF_YEAR_9CF(), 3000, 100, JPN_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// J2
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, JPN_SECOND_TEAM_OF_WEEK_9CF(), 1000, 0, JPN_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, JPN_SECOND_TEAM_OF_YEAR_9CF(), 1500, 50, JPN_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) jpn_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call japan_awards
		add esp, 0x8
		ret 4
	}
}

char jpn_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 12, June, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_768CF0(_this, JPN_FIRST_9CF(), current_date, awards_list[1], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, JPN_FIRST_9CF(), current_date, awards_list[2], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, JPN_FIRST_9CF(), current_date, awards_list[3], 21, 0, 17, -1, -1, -1, -1);
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[0], JPN_FIRST_9CF());
		yearly_team_award_nominate_7698F0(_this, JPN_FIRST_9CF(), awards_list[5]);
		yearly_team_award_nominate_7698F0(_this, JPN_SECOND_9CF(), awards_list[7]);
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) jpn_awards_2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call jpn_awards_2
		add esp, 0x8
		ret 4
	}
}

void jpn_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[4]) {
		sub_769C70(_this, JPN_FIRST_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[6]) {
		sub_769C70(_this, JPN_SECOND_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) jpn_awards_team_of_week_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call jpn_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_jpn_awards()
{
	WriteJMP(0x666720, (DWORD)&jpn_awards_c);
	WriteJMP(0x666AB0, (DWORD)&jpn_awards_2_c);
	WriteJMP(0x666BB0, (DWORD)&jpn_awards_team_of_week_c);
}