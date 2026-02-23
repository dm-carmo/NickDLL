#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void finland_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 14;

	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// General awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, FIN_PLAYER_OF_YEAR_9CF(), 3000, 1500, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, FIN_YOUNG_PLAYER_OF_YEAR_9CF(), 1500, 1000, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, FIN_GOALKEEPER_OF_YEAR_9CF(), 1000, 500, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, FIN_MANAGER_OF_YEAR_9CF(), 2000, 1000, -1, 0, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	// Veikkausliiga awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, FIN_PREMIER_TOP_GOALSCORER_9CF(), 2500, 1250, FIN_PREMIER_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, FIN_PREMIER_PLAYER_OF_MONTH_9CF(), 1000, 500, FIN_PREMIER_9CF(), April, *current_year, November, *current_year, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, FIN_PREMIER_MANAGER_OF_MONTH_9CF(), 1000, 500, FIN_PREMIER_9CF(), April, *current_year, November, *current_year, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, FIN_PREMIER_TEAM_OF_YEAR_9CF(), 0, 0, FIN_PREMIER_9CF(), 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, FIN_PREMIER_TEAM_OF_WEEK_9CF(), 0, 0, FIN_PREMIER_9CF(), 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Ykkösliiga awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, FIN_FIRST_TOP_GOALSCORER_9CF(), 1200, 600, FIN_FIRST_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, FIN_FIRST_PLAYER_OF_MONTH_9CF(), 500, 250, FIN_FIRST_9CF(), April, *current_year, October, *current_year, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, FIN_FIRST_MANAGER_OF_MONTH_9CF(), 500, 250, FIN_FIRST_9CF(), April, *current_year, October, *current_year, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, FIN_FIRST_TEAM_OF_YEAR_9CF(), 0, 0, FIN_FIRST_9CF(), 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, FIN_FIRST_TEAM_OF_WEEK_9CF(), 0, 0, FIN_FIRST_9CF(), 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) fin_awards_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call finland_awards
		add esp, 0x8
		ret 4
	}
}

char fin_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 16, December, *(WORD*)(current_date + 2), (DWORD*)-1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_769380(_this, current_date, awards_list[0], -1, -1, -1, NATION_FINLAND_9CF(), -1, 0, 17);
		yearly_player_award_nominate_769380(_this, current_date, awards_list[1], NATION_FINLAND_9CF(), NATION_FINLAND_9CF(), -1, -1, 21, 0, 17);
		yearly_player_award_nominate_769380(_this, current_date, awards_list[2], -1, NATION_FINLAND_9CF(), -1, -1, -1, 1, 17);
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[3], FIN_PREMIER_9CF());
		yearly_player_award_nominate_768CF0(_this, FIN_PREMIER_9CF(), current_date, awards_list[4], -1, 0, 2, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, FIN_PREMIER_9CF(), awards_list[7]);
		yearly_player_award_nominate_768CF0(_this, FIN_FIRST_9CF(), current_date, awards_list[9], -1, 0, 2, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, FIN_FIRST_9CF(), awards_list[12]);
	}
	BYTE sub_669340_ret = sub_669340(nation);
	WORD nation_day = *(WORD*)(playable_leagues_table + 0x15 + sub_669340_ret * 72);
	if (*(WORD*)(current_date) == nation_day) {
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[5], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[6], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[10], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[11], *(WORD*)(current_date + 2));
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) fin_awards_2_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call fin_awards_2
		add esp, 0x8
		ret 4
	}
}

void fin_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[8]) {
		sub_769C70(_this, FIN_PREMIER_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[13]) {
		sub_769C70(_this, FIN_FIRST_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) fin_awards_team_of_week_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call fin_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void fin_awards_staff_history(BYTE* _this) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	DWORD nation = *(DWORD*)(_this + 0xE);
	BYTE selected = ((cm3_nations*)nation)->NationLeagueSelected;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	DWORD arg1 = *(DWORD*)(_this + 0xA);
	CM3_STAFF* person = sub_86F950(staff_hist_ptr, FIN_PREMIER_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[6], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	person = sub_86F950(staff_hist_ptr, FIN_FIRST_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[11], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	sub_767150((BYTE*)awards_list[5], arg1, -1);
	sub_767150((BYTE*)awards_list[10], arg1, -1);
}

void __declspec(naked) fin_awards_staff_history_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call fin_awards_staff_history
		add esp, 0x4
		ret
	}
}

void setup_fin_awards()
{
	PatchFunction(0x5A90B0, (DWORD)&fin_awards_c);
	PatchFunction(0x5A96E0, (DWORD)&fin_awards_2_c);
	PatchFunction(0x5A9930, (DWORD)&fin_awards_team_of_week_c);
	PatchFunction(0x5A9890, (DWORD)&fin_awards_staff_history_c);
}
