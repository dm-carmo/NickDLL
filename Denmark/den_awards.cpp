#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void denmark_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 12;

	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, DEN_PLAYER_OF_YEAR_9CF(), 6000, 2500, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Superliga awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, DEN_PREMIER_TEAM_OF_WEEK_9CF(), 0, 0, DEN_PREMIER_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, DEN_PREMIER_PLAYER_OF_YEAR_9CF(), 5000, 1500, DEN_PREMIER_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, DEN_PREMIER_YOUNG_PLAYER_OF_YEAR_9CF(), 4500, 1000, DEN_PREMIER_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Division 1 awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, DEN_FIRST_TEAM_OF_WEEK_9CF(), 0, 0, DEN_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, DEN_FIRST_PLAYER_OF_YEAR_9CF(), 3000, 0, DEN_FIRST_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, DEN_FIRST_YOUNG_PLAYER_OF_YEAR_9CF(), 2000, 0, DEN_FIRST_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Division 2 awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, DEN_SECOND_TEAM_OF_WEEK_9CF(), 0, 0, DEN_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, DEN_SECOND_PLAYER_OF_YEAR_9CF(), 2000, 0, DEN_SECOND_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, DEN_SECOND_YOUNG_PLAYER_OF_YEAR_9CF(), 1000, 0, DEN_SECOND_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Division 3 awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, DEN_THIRD_PLAYER_OF_YEAR_9CF(), 1000, 0, DEN_THIRD_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, DEN_THIRD_YOUNG_PLAYER_OF_YEAR_9CF(), 500, 0, DEN_THIRD_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) den_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call denmark_awards
		add esp, 0x8
		ret 4
	}
}

char den_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 30, December, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		BYTE* ad9c60_ptr = (BYTE*)*ad9c60;
		yearly_player_award_nominate_7683C0(_this, current_date, awards_list[0], *(DWORD*)(ad9c60_ptr + 0xc), NATION_DENMARK_9CF(), -1, -1, -1, -1, 0, -1);
	}
	cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 15, June, *(WORD*)(current_date + 2), -1);
	date_day = *(WORD*)(cm_date);
	date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_768CF0(_this, DEN_PREMIER_9CF(), current_date, awards_list[2], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, DEN_PREMIER_9CF(), current_date, awards_list[3], 21, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, DEN_FIRST_9CF(), current_date, awards_list[5], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, DEN_FIRST_9CF(), current_date, awards_list[6], 21, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, DEN_SECOND_9CF(), current_date, awards_list[8], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, DEN_SECOND_9CF(), current_date, awards_list[9], 21, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, DEN_THIRD_9CF(), current_date, awards_list[10], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, DEN_THIRD_9CF(), current_date, awards_list[11], 21, 0, 17, -1, -1, -1, -1);
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) den_awards_2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call den_awards_2
		add esp, 0x8
		ret 4
	}
}

void den_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[1]) {
		sub_769C70(_this, DEN_PREMIER_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[4]) {
		sub_769C70(_this, DEN_FIRST_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[7]) {
		sub_769C70(_this, DEN_SECOND_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) den_awards_team_of_week_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call den_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_den_awards()
{
	PatchFunction(0x554E50, (DWORD)&den_awards_c);
	PatchFunction(0x5552A0, (DWORD)&den_awards_2_c);
	PatchFunction(0x555430, (DWORD)&den_awards_team_of_week_c);
}
