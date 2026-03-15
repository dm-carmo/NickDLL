#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void norway_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 11;
	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// General awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, NOR_PLAYER_OF_YEAR_9CF(), 6000, 2500, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, NOR_GOALKEEPER_OF_YEAR_9CF(), 4000, 1000, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, NOR_DEFENDER_OF_YEAR_9CF(), 4000, 1000, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, NOR_MIDFIELDER_OF_YEAR_9CF(), 4000, 1500, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, NOR_ATTACKER_OF_YEAR_9CF(), 4000, 1750, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Eliteserien awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, NOR_PREMIER_TEAM_OF_WEEK_9CF(), 3000, 500, NOR_PREMIER_9CF(), 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, NOR_PREMIER_MANAGER_OF_MONTH_9CF(), 3000, 1500, NOR_PREMIER_9CF(), March, *current_year, November, *current_year, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, NOR_PREMIER_PLAYER_OF_MONTH_9CF(), 3000, 1500, NOR_PREMIER_9CF(), March, *current_year, November, *current_year, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// 1. Divisjon awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, NOR_FIRST_TEAM_OF_WEEK_9CF(), 1000, 100, NOR_FIRST_9CF(), 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, NOR_FIRST_MANAGER_OF_MONTH_9CF(), 1500, 750, NOR_FIRST_9CF(), March, *current_year, November, *current_year, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, NOR_FIRST_PLAYER_OF_MONTH_9CF(), 1500, 750, NOR_FIRST_9CF(), March, *current_year, November, *current_year, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) nor_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call norway_awards
		add esp, 0x8
		ret 4
	}
}

char nor_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 16, December, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_769380(_this, current_date, awards_list[0], -1, -1, -1, NATION_NORWAY_9CF(), -1, 0, 17);
		yearly_player_award_nominate_769380(_this, current_date, awards_list[1], -1, -1, -1, NATION_NORWAY_9CF(), -1, 1, 17);
		yearly_player_award_nominate_769380(_this, current_date, awards_list[2], -1, -1, -1, NATION_NORWAY_9CF(), -1, 6, 17);
		yearly_player_award_nominate_769380(_this, current_date, awards_list[3], -1, -1, -1, NATION_NORWAY_9CF(), -1, 24, 17);
		yearly_player_award_nominate_769380(_this, current_date, awards_list[4], -1, -1, -1, NATION_NORWAY_9CF(), -1, 64, 17);
	}
	BYTE sub_669340_ret = sub_669340(nation);
	WORD nation_day = pnd_list[sub_669340_ret].update_day;
	if (*(WORD*)(current_date) == nation_day) {
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[6], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[7], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[9], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[10], *(WORD*)(current_date + 2));
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) nor_awards_2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call nor_awards_2
		add esp, 0x8
		ret 4
	}
}

void nor_awards_staff_history(BYTE* _this) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	DWORD arg1 = *(DWORD*)(_this + 0xA);
	CM3_STAFF* person = sub_86F950(staff_hist_ptr, NOR_PREMIER_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[6], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	person = sub_86F950(staff_hist_ptr, NOR_FIRST_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[9], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	sub_767150((BYTE*)awards_list[7], arg1, -1);
	sub_767150((BYTE*)awards_list[10], arg1, -1);
}

void __declspec(naked) nor_awards_staff_history_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call nor_awards_staff_history
		add esp, 0x4
		ret
	}
}

void nor_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[5]) {
		sub_769C70(_this, NOR_PREMIER_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[8]) {
		sub_769C70(_this, NOR_FIRST_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) nor_awards_team_of_week_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call nor_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_nor_awards() {
	PatchFunction(0x793A80, (DWORD)&nor_awards_c);
	PatchFunction(0x7942C0, (DWORD)&nor_awards_2_c);
	PatchFunction(0x794430, (DWORD)&nor_awards_staff_history_c);
	PatchFunction(0x7944D0, (DWORD)&nor_awards_team_of_week_c);
}