#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void usa_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 7;

	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// MLS awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, MLS_PLAYER_OF_MONTH_9CF(), 3000, 500, USA_MLS_9CF(), February, *current_year, November, *current_year, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, MLS_MANAGER_OF_YEAR_9CF(), 5000, 500, USA_MLS_9CF(), 0, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, MLS_SCORING_CHAMPION_9CF(), 5000, 500, USA_MLS_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, MLS_GOALKEEPER_OF_YEAR_9CF(), 5000, 500, USA_MLS_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, MLS_DEFENDER_OF_YEAR_9CF(), 5000, 500, USA_MLS_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, MLS_ROOKIE_OF_YEAR_9CF(), 4000, 500, USA_MLS_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, MLS_ALL_PRO_TEAM_9CF(), 3500, 100, USA_MLS_9CF(), 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) usa_awards_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call usa_awards
		add esp, 0x8
		ret 4
	}
}

char usa_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 16, December, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[1], USA_MLS_9CF());
		yearly_player_award_nominate_768CF0(_this, USA_MLS_9CF(), current_date, awards_list[2], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, USA_MLS_9CF(), current_date, awards_list[3], -1, 1, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, USA_MLS_9CF(), current_date, awards_list[4], -1, 6, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, USA_MLS_9CF(), current_date, awards_list[5], 21, 0, 17, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, USA_MLS_9CF(), awards_list[6]);
	}
	BYTE sub_669340_ret = sub_669340(nation);
	WORD nation_day = pnd_list[sub_669340_ret].update_day;
	if (*(WORD*)(current_date) == nation_day) {
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[0], *(WORD*)(current_date + 2));
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) usa_awards_2_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call usa_awards_2
		add esp, 0x8
		ret 4
	}
}

void usa_awards_staff_history(BYTE* _this) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	DWORD arg1 = *(DWORD*)(_this + 0xA);
	sub_767150((BYTE*)awards_list[0], arg1, -1);
}

void __declspec(naked) usa_awards_staff_history_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call usa_awards_staff_history
		add esp, 0x4
		ret
	}
}

void setup_usa_awards()
{
	PatchFunction(0x906AC0, (DWORD)&usa_awards_c);
	PatchFunction(0x906E10, (DWORD)&usa_awards_2_c);
	PatchFunction(0x906F60, (DWORD)&usa_awards_staff_history_c);
}
