#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers/new_league_ids.h>

void croatia_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 9;

	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// First Division awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFE5C), 0, 0, Get9CF(0x9CF87C), 1, 0, a2, 1); // before a2, original game uses 2 but not working?
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFE58), 1500, 800, Get9CF(0x9CF87C), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFE60), 1200, 600, Get9CF(0x9CF87C), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Second Division awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFE68), 0, 0, Get9CF(0x9CF880), 1, 0, a2, 1); // before a2, original game uses 2 but not working?
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFE64), 700, 400, Get9CF(0x9CF880), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFE6C), 700, 400, Get9CF(0x9CF880), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Third Division awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, Get9CF(0x9CFE74), 0, 0, cro_third_id, 1, 0, a2, 1); // before a2, original game uses 2 but not working?
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFE70), 400, 200, cro_third_id, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, Get9CF(0x9CFE78), 400, 200, cro_third_id, 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) cro_awards_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call croatia_awards
		add esp, 0x8
		ret 4
	}
}

char cro_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 16, June, *(WORD*)(current_date + 2), (DWORD*)-1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF87C), current_date, awards_list[1], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF87C), current_date, awards_list[2], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF880), current_date, awards_list[4], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, Get9CF(0x9CF880), current_date, awards_list[5], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, cro_third_id, current_date, awards_list[7], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, cro_third_id, current_date, awards_list[8], -1, 0, 2, -1, -1, -1, -1);
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) cro_awards_2_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call cro_awards_2
		add esp, 0x8
		ret 4
	}
}

void cro_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[0]) {
		sub_769C70(_this, Get9CF(0x9CF87C), award_addr);
		return;
	}
	if (award_addr == awards_list[3]) {
		sub_769C70(_this, Get9CF(0x9CF880), award_addr);
		return;
	}
	if (award_addr == awards_list[6]) {
		sub_769C70(_this, cro_third_id, award_addr);
		return;
	}
}

void __declspec(naked) cro_awards_team_of_week_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call cro_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_cro_awards()
{
	PatchFunction(0x517FA0, (DWORD)&cro_awards_c);
	PatchFunction(0x5183A0, (DWORD)&cro_awards_2_c);
	PatchFunction(0x5184D0, (DWORD)&cro_awards_team_of_week_c);
}
