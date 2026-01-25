#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"

void italy_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	BYTE selected = ((cm3_nations*)*(DWORD*)(_this + 0xE))->NationLeagueSelected;
	if ((selected & 4) == 0) {
		*(WORD*)(_this + 0x8) = 25;
	}
	else {
		*(WORD*)(_this + 0x8) = 15;
	}
	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// Serie A awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFCC4), 0, 0, Get9CF(0x9CF570), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFD7C), 6500, 2500, Get9CF(0x9CF570), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFC04), 7000, 2500, Get9CF(0x9CF570), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFB34), 8500, 5000, Get9CF(0x9CF570), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFB30), 7500, 4000, Get9CF(0x9CF570), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFD98), 8000, 5000, Get9CF(0x9CF570), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFB40), 7500, 5000, Get9CF(0x9CF570), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFB44), 7500, 5000, Get9CF(0x9CF570), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFB38), 7500, 5000, Get9CF(0x9CF570), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFB3C), 7500, 5000, Get9CF(0x9CF570), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Serie B awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFCC8), 0, 0, Get9CF(0x9CF574), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFD80), 3500, 1750, Get9CF(0x9CF574), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFC08), 5000, 1500, Get9CF(0x9CF574), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFB48), 6000, 2000, Get9CF(0x9CF574), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFD9C), 5500, 2000, Get9CF(0x9CF574), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;
	/*
	// Serie C1/A awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFCCC), 0, 0, Get9CF(0x9CF578), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFD84), 1500, 750, Get9CF(0x9CF578), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFC0C), 3000, 1000, Get9CF(0x9CF578), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFB4C), 4500, 1500, Get9CF(0x9CF578), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFDA0), 2000, 1000, Get9CF(0x9CF578), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Serie C1/B awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFCD0), 0, 0, Get9CF(0x9CF57C), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFD88), 1500, 750, Get9CF(0x9CF57C), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFC10), 3000, 1000, Get9CF(0x9CF57C), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFB50), 4500, 1500, Get9CF(0x9CF57C), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFDA4), 2000, 1000, Get9CF(0x9CF57C), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	if ((selected & 4) != 0) {
		// Serie C2/A awards
		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFD2C), 0, 0, Get9CF(0x9CF580), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFD8C), 500, 250, Get9CF(0x9CF580), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFD24), 3000, 1000, Get9CF(0x9CF580), 1, 0, 0, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFD28), 4500, 1500, Get9CF(0x9CF580), 1, 0, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFDA8), 2000, 1000, Get9CF(0x9CF580), 1, 0, 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		// Serie C2/B awards
		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFD44), 0, 0, Get9CF(0x9CF584), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFD90), 500, 250, Get9CF(0x9CF584), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFD30), 3000, 1000, Get9CF(0x9CF584), 1, 0, 0, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFD34), 4500, 1500, Get9CF(0x9CF584), 1, 0, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFDAC), 2000, 1000, Get9CF(0x9CF584), 1, 0, 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		// Serie C2/C awards
		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFD50), 0, 0, Get9CF(0x9CF588), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFD94), 500, 250, Get9CF(0x9CF588), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFD48), 3000, 1000, Get9CF(0x9CF588), 1, 0, 0, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFD4C), 4500, 1500, Get9CF(0x9CF588), 1, 0, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFDB0), 2000, 1000, Get9CF(0x9CF588), 1, 0, 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;
	}
	*/
}

void __declspec(naked) ita_awards_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call italy_awards
		add esp, 0x8
		ret 4
	}
}

char ita_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	BYTE selected = ((cm3_nations*)nation)->NationLeagueSelected;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 6, June, *(WORD*)(current_date + 2), (DWORD*)-1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[2], Get9CF(0x9CF570));
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[12], Get9CF(0x9CF574));
		/*
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[17], Get9CF(0x9CF578));
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[22], Get9CF(0x9CF57C));
		*/
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF570), current_date, awards_list[3], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF570), current_date, awards_list[4], 23, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF570), current_date, awards_list[5], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF570), current_date, awards_list[6], -1, 6, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF570), current_date, awards_list[7], -1, 1, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF570), current_date, awards_list[8], -1, 0, 2, Get9CF(0x9CF360), -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF570), current_date, awards_list[9], -1, 0, 2, -1, -1, Get9CF(0x9CF360), -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF574), current_date, awards_list[13], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF574), current_date, awards_list[14], -1, 0, 2, -1, -1, -1, -1);
		/*
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF578), current_date, awards_list[18], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF578), current_date, awards_list[19], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF57C), current_date, awards_list[23], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF57C), current_date, awards_list[24], -1, 0, 2, -1, -1, -1, -1);
		*/
		yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF570), awards_list[1]);
		yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF574), awards_list[11]);
		/*
		yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF578), awards_list[16]);
		yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF57C), awards_list[21]);
		if ((selected & 4) != 0) {
			yearly_staff_award_nominate_768940(_this, current_date, awards_list[27], Get9CF(0x9CF580));
			yearly_staff_award_nominate_768940(_this, current_date, awards_list[32], Get9CF(0x9CF584));
			yearly_staff_award_nominate_768940(_this, current_date, awards_list[37], Get9CF(0x9CF58C));
			yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF580), current_date, awards_list[28], -1, 0, 17, -1, -1, -1, -1);
			yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF580), current_date, awards_list[29], -1, 0, 2, -1, -1, -1, -1);
			yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF584), current_date, awards_list[33], -1, 0, 17, -1, -1, -1, -1);
			yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF584), current_date, awards_list[34], -1, 0, 2, -1, -1, -1, -1);
			yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF588), current_date, awards_list[38], -1, 0, 17, -1, -1, -1, -1);
			yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF588), current_date, awards_list[39], -1, 0, 2, -1, -1, -1, -1);
			yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF580), awards_list[26]);
			yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF584), awards_list[31]);
			yearly_team_award_nominate_7698F0(_this, Get9CF(0x9CF588), awards_list[36]);
		}
		*/
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) ita_awards_2_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ita_awards_2
		add esp, 0x8
		ret 4
	}
}

void ita_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	BYTE selected = ((cm3_nations*)nation)->NationLeagueSelected;
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[0]) {
		sub_769C70(_this, Get9CF(0x9CF570), award_addr);
		return;
	}
	if (award_addr == awards_list[10]) {
		sub_769C70(_this, Get9CF(0x9CF574), award_addr);
		return;
	}
	/*
	if (award_addr == awards_list[15]) {
		sub_769C70(_this, Get9CF(0x9CF578), award_addr);
		return;
	}
	if (award_addr == awards_list[20]) {
		sub_769C70(_this, Get9CF(0x9CF57C), award_addr);
		return;
	}
	if ((selected & 4) != 0) {
		if (award_addr == awards_list[25]) {
			sub_769C70(_this, Get9CF(0x9CF580), award_addr);
			return;
		}
		if (award_addr == awards_list[30]) {
			sub_769C70(_this, Get9CF(0x9CF584), award_addr);
			return;
		}
		if (award_addr == awards_list[35]) {
			sub_769C70(_this, Get9CF(0x9CF588), award_addr);
			return;
		}
	}
	*/
}

void __declspec(naked) ita_awards_team_of_week_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ita_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_ita_awards()
{
	PatchFunction(0x65FEC0, (DWORD)&ita_awards_c);
	PatchFunction(0x660EC0, (DWORD)&ita_awards_2_c);
	PatchFunction(0x661330, (DWORD)&ita_awards_team_of_week_c);
}
