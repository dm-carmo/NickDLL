#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void rusatia_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 5;

	DWORD* awards_list = (DWORD*)cm0102_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// General awards
	BYTE* pMem = (BYTE*)cm0102_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, RUS_PLAYER_OF_YEAR_9CF(), 4000, 2000, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Premier League awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, RUS_PREMIER_TEAM_OF_WEEK_9CF(), 0, 0, RUS_PREMIER_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, RUS_PREMIER_TEAM_OF_YEAR_9CF(), 0, 0, RUS_PREMIER_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// First League awards
	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, RUS_FIRST_TEAM_OF_WEEK_9CF(), 0, 0, RUS_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, RUS_FIRST_TEAM_OF_YEAR_9CF(), 0, 0, RUS_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) rus_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call rusatia_awards
		add esp, 0x8
		ret 4
	}
}

char rus_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 30, December, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		BYTE* ad9c60_ptr = (BYTE*)*ad9c60;
		yearly_player_award_nominate_769380(_this, current_date, awards_list[0], -1, -1, -1, NATION_RUSSIA_9CF(), -1, 0, 17);
	}
	cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 16, June, *(WORD*)(current_date + 2), -1);
	date_day = *(WORD*)(cm_date);
	date_year = *(WORD*)(cm_date + 2);
	//leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_team_award_nominate_7698F0(_this, RUS_PREMIER_9CF(), awards_list[2]);
		yearly_team_award_nominate_7698F0(_this, RUS_FIRST_9CF(), awards_list[4]);
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) rus_awards_2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call rus_awards_2
		add esp, 0x8
		ret 4
	}
}

void rus_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[1]) {
		sub_769C70(_this, RUS_PREMIER_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[3]) {
		sub_769C70(_this, RUS_FIRST_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) rus_awards_team_of_week_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call rus_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_rus_awards()
{
	PatchFunction(0x7ec2a0, (DWORD)&rus_awards_c);
	PatchFunction(0x7ec600, (DWORD)&rus_awards_2_c);
	PatchFunction(0x7ec6a0, (DWORD)&rus_awards_team_of_week_c);
}
