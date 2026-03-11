#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void ireland_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 18;
	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// General awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_PLAYER_OF_YEAR_9CF(), 0xbb8, 0x5dc, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_YOUNG_PLAYER_OF_YEAR_9CF(), 0x5dc, 0x2ee, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_PERSONALITY_OF_YEAR_9CF(), 0, 0, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, IRL_PLAYER_OF_MONTH_9CF(), 0xbb8, 0x5dc, -1, February, *current_year, October, *current_year, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Premier awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, IRL_PREMIER_TEAM_OF_WEEK_9CF(), 0x3e8, 0x1f4, IRL_PREMIER_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_PREMIER_PLAYER_OF_YEAR_9CF(), 0x5dc, 0x2ee, IRL_PREMIER_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_PREMIER_YOUNG_PLAYER_OF_YEAR_9CF(), 0x1f4, 0xfa, IRL_PREMIER_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_LEAGUE_GOLDEN_BOOT_9CF(), 0x1f4, 0xfa, IRL_PREMIER_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, IRL_PREMIER_TEAM_OF_YEAR_9CF(), 0x5dc, 0x2ee, IRL_PREMIER_9CF(), 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_PREMIER_MANAGER_OF_YEAR_9CF(), 0x9c4, 0x4b0, IRL_PREMIER_9CF(), 0, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, IRL_PREMIER_MANAGER_OF_MONTH_9CF(), 0x7d0, 0x3e8, IRL_PREMIER_9CF(), February, *current_year, October, *current_year, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	// First awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, IRL_FIRST_TEAM_OF_WEEK_9CF(), 0x1f4, 0xfa, IRL_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_FIRST_PLAYER_OF_YEAR_9CF(), 0x2ee, 0x190, IRL_FIRST_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_FIRST_YOUNG_PLAYER_OF_YEAR_9CF(), 0x12c, 0x96, IRL_FIRST_9CF(), 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_LEAGUE_BRONZE_BOOT_9CF(), 0x1f4, 0xfa, IRL_FIRST_9CF(), 0, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, IRL_FIRST_TEAM_OF_YEAR_9CF(), 0x1f4, 0xfa, IRL_FIRST_9CF(), 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, IRL_FIRST_MANAGER_OF_YEAR_9CF(), 0x3e8, 0x1f4, IRL_FIRST_9CF(), 0, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, IRL_FIRST_MANAGER_OF_MONTH_9CF(), 0x3e8, 0x1f4, IRL_FIRST_9CF(), February, *current_year, October, *current_year, a2, 0);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) irl_awards_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ireland_awards
		add esp, 0x8
		ret 4
	}
}

char irl_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 16, November, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		BYTE* ad9c60_ptr = (BYTE*)*ad9c60;
		yearly_player_award_nominate_7683C0(_this, current_date, awards_list[0], *(DWORD*)(ad9c60_ptr + 0x10), NATION_IRELAND_9CF(), -1, -1, -1, -1, 0, -1);
		yearly_player_award_nominate_7683C0(_this, current_date, awards_list[1], *(DWORD*)(ad9c60_ptr + 0x10), NATION_IRELAND_9CF(), -1, -1, -1, -1, 0, 23);
		yearly_player_award_nominate_7683C0(_this, current_date, awards_list[2], *(DWORD*)(ad9c60_ptr + 0x10), -1, -1, -1, NATION_IRELAND_9CF(), -1, 5, -1);
		yearly_player_award_nominate_768CF0(_this, IRL_PREMIER_9CF(), current_date, awards_list[5], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, IRL_PREMIER_9CF(), current_date, awards_list[6], 23, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, IRL_PREMIER_9CF(), current_date, awards_list[7], -1, 0, 2, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, IRL_PREMIER_9CF(), awards_list[8]);
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[9], IRL_PREMIER_9CF());
		yearly_player_award_nominate_768CF0(_this, IRL_FIRST_9CF(), current_date, awards_list[12], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, IRL_FIRST_9CF(), current_date, awards_list[13], 23, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, IRL_FIRST_9CF(), current_date, awards_list[14], -1, 0, 2, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, IRL_FIRST_9CF(), awards_list[15]);
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[16], IRL_FIRST_9CF());
	}
	BYTE sub_669340_ret = sub_669340(nation);
	WORD nation_day = pnd_list[sub_669340_ret].update_day;
	if (*(WORD*)(current_date) == nation_day) {
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[3], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[10], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[17], *(WORD*)(current_date + 2));
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) irl_awards_2_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call irl_awards_2
		add esp, 0x8
		ret 4
	}
}

void irl_awards_staff_history(BYTE* _this) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	DWORD arg1 = *(DWORD*)(_this + 0xA);
	CM3_STAFF* person = sub_86F950(staff_hist_ptr, IRL_PREMIER_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[10], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	person = sub_86F950(staff_hist_ptr, IRL_FIRST_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[17], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	sub_767150((BYTE*)awards_list[3], arg1, -1);
}

void __declspec(naked) irl_awards_staff_history_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call irl_awards_staff_history
		add esp, 0x4
		ret
	}
}

void irl_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[4]) {
		sub_769C70(_this, IRL_PREMIER_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[11]) {
		sub_769C70(_this, IRL_FIRST_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) irl_awards_team_of_week_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call irl_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_irl_awards() {
	PatchFunction(0x63b790, (DWORD)&irl_awards_c);
	PatchFunction(0x63bf10, (DWORD)&irl_awards_2_c);
	PatchFunction(0x63c160, (DWORD)&irl_awards_staff_history_c);
	PatchFunction(0x63c1f0, (DWORD)&irl_awards_team_of_week_c);
}