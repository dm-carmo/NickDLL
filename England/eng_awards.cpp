#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"

void england_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	BYTE selected = ((cm3_nations*)*(DWORD*)(_this + 0xE))->NationLeagueSelected;
	if ((selected & 4) == 0) {
		*(WORD*)(_this + 0x8) = 26;
	}
	else {
		*(WORD*)(_this + 0x8) = 32;
	}
	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// General awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFA34), 8000, 5000, -1, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFA38), 7000, 3500, -1, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Premier League awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFA6C), 4000, 500, Get9CF(0x9CF5BC), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFBD8), 5000, 1500, Get9CF(0x9CF5BC), August, *current_year, May, *current_year + 1, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFA4C), 5000, 1500, Get9CF(0x9CF5BC), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFA5C), 4500, 1000, Get9CF(0x9CF5BC), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFBD4), 7500, 3500, Get9CF(0x9CF5BC), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFA3C), 6500, 2500, Get9CF(0x9CF5BC), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Championship awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFA70), 3000, 500, Get9CF(0x9CF5C0), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFBE0), 3000, 500, Get9CF(0x9CF5C0), August, *current_year, May, *current_year + 1, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFA50), 3500, 500, Get9CF(0x9CF5C0), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFA60), 3000, 500, Get9CF(0x9CF5C0), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFBDC), 5000, 500, Get9CF(0x9CF5C0), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFA40), 4500, 500, Get9CF(0x9CF5C0), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// League One awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFA74), 2000, 0, Get9CF(0x9CF5C4), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFBE8), 2000, 0, Get9CF(0x9CF5C4), August, *current_year, May, *current_year + 1, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFA54), 2500, 0, Get9CF(0x9CF5C4), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFA64), 2000, 0, Get9CF(0x9CF5C4), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFBE4), 3000, 0, Get9CF(0x9CF5C4), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFA44), 3000, 0, Get9CF(0x9CF5C4), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// League Two awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFA78), 1500, 0, Get9CF(0x9CF5C8), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFBF0), 1000, 0, Get9CF(0x9CF5C8), August, *current_year, May, *current_year + 1, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFA58), 1750, 0, Get9CF(0x9CF5C8), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFA68), 1500, 0, Get9CF(0x9CF5C8), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFBEC), 2000, 0, Get9CF(0x9CF5C8), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFA48), 2000, 0, Get9CF(0x9CF5C8), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	if ((selected & 4) != 0) {
		// National League awards
		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFC94), 1500, 0, Get9CF(0x9CF69C), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFC84), 1000, 0, Get9CF(0x9CF69C), August, *current_year, May, *current_year + 1, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFC90), 1750, 0, Get9CF(0x9CF69C), August, *current_year, May, *current_year + 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, Get9CF(0x9CFC98), 1500, 0, Get9CF(0x9CF69C), August, *current_year, May, *current_year + 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFC8C), 2000, 0, Get9CF(0x9CF69C), 1, 0, 0, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFC88), 2000, 0, Get9CF(0x9CF69C), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;
	}
}

void __declspec(naked) eng_awards_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call england_awards
		add esp, 0x8
		ret 4
	}
}

char eng_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	BYTE selected = ((cm3_nations*)nation)->NationLeagueSelected;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 5, April, *(WORD*)(current_date + 2), (DWORD*)-1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF5BC), current_date, awards_list[0], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF5BC), current_date, awards_list[1], 21, 0, 17, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF5BC), awards_list[7]);
		yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF5C0), awards_list[13]);
		yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF5C4), awards_list[19]);
		yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF5C8), awards_list[25]);
		if ((selected & 4) != 0) {
			yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF69C), awards_list[31]);
		}
	}
	cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 30, May, *(WORD*)(current_date + 2), (DWORD*)-1);
	date_day = *(WORD*)(cm_date);
	date_year = *(WORD*)(cm_date + 2);
	//leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[6], Get9CF(0x9CF5BC));
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[12], Get9CF(0x9CF5C0));
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[18], Get9CF(0x9CF5C4));
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[24], Get9CF(0x9CF5C8));
		if ((selected & 4) != 0) {
			yearly_staff_award_nominate_768940(_this, current_date, awards_list[30], Get9CF(0x9CF69C));
		}
	}
	BYTE sub_669340_ret = sub_669340(nation);
	WORD nation_day = *(WORD*)(playable_leagues_table + 0x15 + sub_669340_ret * 72); //b64165 england
	if (*(WORD*)(current_date) == nation_day) {
		// Premier
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[3], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[4], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[5], *(WORD*)(current_date + 2));
		// Championship
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[9], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[10], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[11], *(WORD*)(current_date + 2));
		// League 1
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[15], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[16], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[17], *(WORD*)(current_date + 2));
		// League 2
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[21], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[22], *(WORD*)(current_date + 2));
		monthly_person_award_nominate_7672E0((BYTE*)awards_list[23], *(WORD*)(current_date + 2));
		if ((selected & 4) != 0) {
			// National League
			monthly_person_award_nominate_7672E0((BYTE*)awards_list[27], *(WORD*)(current_date + 2));
			monthly_person_award_nominate_7672E0((BYTE*)awards_list[28], *(WORD*)(current_date + 2));
			monthly_person_award_nominate_7672E0((BYTE*)awards_list[29], *(WORD*)(current_date + 2));
		}
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) eng_awards_2_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call eng_awards_2
		add esp, 0x8
		ret 4
	}
}

void eng_awards_staff_history(BYTE* _this) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	DWORD nation = *(DWORD*)(_this + 0xE);
	BYTE selected = ((cm3_nations*)nation)->NationLeagueSelected;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	DWORD arg1 = *(DWORD*)(_this + 0xA);
	CM3_STAFF* person = sub_86F950(staff_hist_ptr, Get9CF(0x9CF5BC));
	if (person) {
		sub_7671C0((BYTE*)awards_list[3], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	person = sub_86F950(staff_hist_ptr, Get9CF(0x9CF5C0));
	if (person) {
		sub_7671C0((BYTE*)awards_list[9], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	person = sub_86F950(staff_hist_ptr, Get9CF(0x9CF5C4));
	if (person) {
		sub_7671C0((BYTE*)awards_list[15], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	person = sub_86F950(staff_hist_ptr, Get9CF(0x9CF5C8));
	if (person) {
		sub_7671C0((BYTE*)awards_list[21], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	if ((selected & 4) != 0) {
		person = sub_86F950(staff_hist_ptr, Get9CF(0x9CF69C));
		if (person) {
			sub_7671C0((BYTE*)awards_list[27], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
		}
	}
	sub_767150((BYTE*)awards_list[4], arg1, -1);
	sub_767150((BYTE*)awards_list[5], arg1, 20);
	sub_767150((BYTE*)awards_list[10], arg1, -1);
	sub_767150((BYTE*)awards_list[11], arg1, 20);
	sub_767150((BYTE*)awards_list[16], arg1, -1);
	sub_767150((BYTE*)awards_list[17], arg1, 20);
	sub_767150((BYTE*)awards_list[22], arg1, -1);
	sub_767150((BYTE*)awards_list[23], arg1, 20);
	if ((selected & 4) != 0) {
		sub_767150((BYTE*)awards_list[28], arg1, -1);
		sub_767150((BYTE*)awards_list[29], arg1, 20);
	}
}

void __declspec(naked) eng_awards_staff_history_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_awards_staff_history
		add esp, 0x4
		ret
	}
}

void eng_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	BYTE selected = ((cm3_nations*)nation)->NationLeagueSelected;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[2]) {
		sub_769C70(_this, Get9CF(0x9CF5BC), award_addr);
		return;
	}
	if (award_addr == awards_list[8]) {
		sub_769C70(_this, Get9CF(0x9CF5C0), award_addr);
		return;
	}
	if (award_addr == awards_list[14]) {
		sub_769C70(_this, Get9CF(0x9CF5C4), award_addr);
		return;
	}
	if (award_addr == awards_list[20]) {
		sub_769C70(_this, Get9CF(0x9CF5C8), award_addr);
		return;
	}
	if ((selected & 4) != 0) {
		if (award_addr == awards_list[26]) {
			sub_769C70(_this, Get9CF(0x9CF69C), award_addr);
			return;
		}
	}
}

void __declspec(naked) eng_awards_team_of_week_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call eng_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_eng_awards() {
	PatchFunction(0x5788C0, (DWORD)&eng_awards_c);
	PatchFunction(0x579610, (DWORD)&eng_awards_2_c);
	PatchFunction(0x579900, (DWORD)&eng_awards_staff_history_c);
	PatchFunction(0x579AF0, (DWORD)&eng_awards_team_of_week_c);
}