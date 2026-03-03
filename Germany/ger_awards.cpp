#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void germany_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 13;

	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// General awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, GER_PLAYER_OF_YEAR_9CF(), 7500, 2500, -1, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// First Division awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, GER_FIRST_TEAM_OF_WEEK_9CF(), 0, 0, GER_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, GER_FIRST_PLAYER_OF_MONTH_9CF(), 6000, 2000, GER_FIRST_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, GER_FIRST_MANAGER_OF_YEAR_9CF(), 6000, 2000, GER_FIRST_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, GER_FIRST_TOP_GOALSCORER_9CF(), 5000, 2000, GER_FIRST_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Second Division awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, GER_SECOND_TEAM_OF_WEEK_9CF(), 0, 0, GER_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, GER_SECOND_PLAYER_OF_MONTH_9CF(), 4500, 1000, GER_SECOND_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, GER_SECOND_MANAGER_OF_YEAR_9CF(), 4500, 1000, GER_SECOND_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, GER_SECOND_TOP_GOALSCORER_9CF(), 3000, 1000, GER_SECOND_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Third Division awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, GER_THIRD_TEAM_OF_WEEK_9CF(), 0, 0, GER_THIRD_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, GER_THIRD_PLAYER_OF_MONTH_9CF(), 3000, 500, GER_THIRD_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, GER_THIRD_MANAGER_OF_YEAR_9CF(), 3000, 500, GER_THIRD_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, GER_THIRD_TOP_GOALSCORER_9CF(), 2000, 500, GER_THIRD_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) ger_awards_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call germany_awards
		add esp, 0x8
		ret 4
	}
}

char ger_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 6, June, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_768CF0(_this, GER_FIRST_9CF(), current_date, awards_list[4], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, GER_SECOND_9CF(), current_date, awards_list[8], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, GER_THIRD_9CF(), current_date, awards_list[12], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_769380(_this, current_date, awards_list[0], NATION_GERMANY_9CF(), NATION_GERMANY_9CF(), -1, -1, -1, -1, 17);
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[3], GER_FIRST_9CF());
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[7], GER_SECOND_9CF());
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[11], GER_THIRD_9CF());
	}
	BYTE sub_669340_ret = sub_669340(nation);
	WORD nation_day = pnd_list[sub_669340_ret].update_day; //b6423d germany
	if (*(WORD*)(current_date) == nation_day) {
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[2], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[6], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[10], *(WORD*)(current_date + 2));
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) ger_awards_2_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ger_awards_2
		add esp, 0x8
		ret 4
	}
}

void ger_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[1]) {
		sub_769C70(_this, GER_FIRST_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[5]) {
		sub_769C70(_this, GER_SECOND_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[9]) {
		sub_769C70(_this, GER_THIRD_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) ger_awards_team_of_week_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ger_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void ger_awards_staff_history(BYTE* _this) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	DWORD arg1 = *(DWORD*)(_this + 0xA);
	sub_767150((BYTE*)awards_list[2], arg1, -1);
	sub_767150((BYTE*)awards_list[6], arg1, -1);
	sub_767150((BYTE*)awards_list[10], arg1, -1);
}

void __declspec(naked) ger_awards_staff_history_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call ger_awards_staff_history
		add esp, 0x4
		ret
	}
}

void setup_ger_awards()
{
	PatchFunction(0x5DF790, (DWORD)&ger_awards_c);
	PatchFunction(0x5DFD70, (DWORD)&ger_awards_2_c);
	WriteDWORD(0x96B3C8, (DWORD)&ger_awards_team_of_week_c);
	PatchFunction(0x5DFF40, (DWORD)&ger_awards_staff_history_c);
}
