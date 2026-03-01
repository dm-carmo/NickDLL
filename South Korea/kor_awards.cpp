#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void kormany_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 8;

	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// General awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, KOR_BEST_11_OF_YEAR_9CF(), 2500, 1250, -1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, KOR_MANAGER_OF_MONTH_9CF(), 1500, 750, -1, February, *current_year, November, *current_year, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, KOR_PLAYER_OF_MONTH_9CF(), 1500, 750, -1, February, *current_year, November, *current_year, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, KOR_MANAGER_OF_YEAR_9CF(), 1000, 500, -1, 0, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, KOR_PLAYER_OF_YEAR_9CF(), 1500, 500, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, KOR_TOP_GOAL_SCORER_9CF(), 1000, 500, -1, 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, KOR_YOUNG_PLAYER_OF_YEAR_9CF(), 500, 250, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, KOR_MOST_ASSISTED_9CF(), 1000, 500, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) kor_awards_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call kormany_awards
		add esp, 0x8
		ret 4
	}
}

char kor_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 16, December, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_team_award_nominate_7698F0(_this, KOR_FIRST_9CF(), awards_list[0]);
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[3], KOR_FIRST_9CF());
		yearly_player_award_nominate_769380(_this, current_date, awards_list[4], NATION_SOUTH_KOREA_9CF(), -1, -1, -1, -1, 0, 17);
		yearly_player_award_nominate_769380(_this, current_date, awards_list[5], NATION_SOUTH_KOREA_9CF(), -1, -1, -1, -1, 0, 2);
		yearly_player_award_nominate_769380(_this, current_date, awards_list[6], NATION_SOUTH_KOREA_9CF(), -1, -1, -1, 21, 0, 17);
		yearly_player_award_nominate_769380(_this, current_date, awards_list[7], NATION_SOUTH_KOREA_9CF(), -1, -1, -1, -1, 0, 5);
	}
	BYTE sub_669340_ret = sub_669340(nation);
	WORD nation_day = pnd_list[sub_669340_ret].update_day; //b6423d kormany
	if (*(WORD*)(current_date) == nation_day) {
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[1], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[2], *(WORD*)(current_date + 2));
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) kor_awards_2_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call kor_awards_2
		add esp, 0x8
		ret 4
	}
}

void kor_awards_staff_history(BYTE* _this) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	DWORD nation = *(DWORD*)(_this + 0xE);
	BYTE selected = ((cm3_nations*)nation)->NationLeagueSelected;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	DWORD arg1 = *(DWORD*)(_this + 0xA);
	CM3_STAFF* person = sub_86F950(staff_hist_ptr, KOR_FIRST_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[1], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	sub_767150((BYTE*)awards_list[2], arg1, -1);
}

void __declspec(naked) kor_awards_staff_history_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call kor_awards_staff_history
		add esp, 0x4
		ret
	}
}

void setup_kor_awards()
{
	PatchFunction(0x66E170, (DWORD)&kor_awards_c);
	PatchFunction(0x66E4D0, (DWORD)&kor_awards_2_c);
	PatchFunction(0x66E610, (DWORD)&kor_awards_staff_history_c);
}
