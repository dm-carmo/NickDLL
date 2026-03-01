#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void portugal_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 18;

	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// First Division awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, POR_FIRST_TEAM_OF_WEEK_9CF(), 0, 0, POR_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_FIRST_PLAYER_OF_YEAR_9CF(), 5000, 1750, POR_FIRST_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_FIRST_MOST_MAN_OF_MATCH_9CF(), 5000, 1500, POR_FIRST_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_FIRST_TOP_GOALSCORER_9CF(), 5000, 2000, POR_FIRST_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, POR_FIRST_TEAM_OF_YEAR_9CF(), 4500, 1500, POR_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_FIRST_MANAGER_OF_YEAR_9CF(), 6000, 3000, POR_FIRST_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	// Second Division awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, POR_SECOND_TEAM_OF_WEEK_9CF(), 0, 0, POR_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_SECOND_PLAYER_OF_YEAR_9CF(), 2500, 500, POR_SECOND_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_SECOND_MOST_MAN_OF_MATCH_9CF(), 2500, 500, POR_SECOND_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_SECOND_TOP_GOALSCORER_9CF(), 2500, 750, POR_SECOND_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, POR_SECOND_TEAM_OF_YEAR_9CF(), 2200, 500, POR_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_SECOND_MANAGER_OF_YEAR_9CF(), 3000, 1500, POR_SECOND_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	// Third Division awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, POR_THIRD_TEAM_OF_WEEK_9CF(), 0, 0, POR_THIRD_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_THIRD_PLAYER_OF_YEAR_9CF(), 1000, 200, POR_THIRD_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_THIRD_MOST_MAN_OF_MATCH_9CF(), 1000, 200, POR_THIRD_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_THIRD_TOP_GOALSCORER_9CF(), 1000, 250, POR_THIRD_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, POR_THIRD_TEAM_OF_YEAR_9CF(), 800, 200, POR_THIRD_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, POR_THIRD_MANAGER_OF_YEAR_9CF(), 2000, 1000, POR_THIRD_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) por_awards_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call portugal_awards
		add esp, 0x8
		ret 4
	}
}

char por_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 6, June, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_768CF0(_this, POR_FIRST_9CF(), current_date, awards_list[1], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, POR_FIRST_9CF(), current_date, awards_list[2], -1, 0, 12, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, POR_FIRST_9CF(), current_date, awards_list[3], -1, 0, 2, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, POR_FIRST_9CF(), awards_list[4]);
		yearly_player_award_nominate_768CF0(_this, POR_SECOND_9CF(), current_date, awards_list[7], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, POR_SECOND_9CF(), current_date, awards_list[8], -1, 0, 12, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, POR_SECOND_9CF(), current_date, awards_list[9], -1, 0, 2, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, POR_SECOND_9CF(), awards_list[10]);
		yearly_player_award_nominate_768CF0(_this, POR_THIRD_9CF(), current_date, awards_list[13], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, POR_THIRD_9CF(), current_date, awards_list[14], -1, 0, 12, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, POR_THIRD_9CF(), current_date, awards_list[15], -1, 0, 2, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, POR_THIRD_9CF(), awards_list[16]);
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[5], POR_FIRST_9CF());
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[11], POR_SECOND_9CF());
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[17], POR_THIRD_9CF());
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) por_awards_2_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call por_awards_2
		add esp, 0x8
		ret 4
	}
}

void por_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[0]) {
		sub_769C70(_this, POR_FIRST_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[6]) {
		sub_769C70(_this, POR_SECOND_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[12]) {
		sub_769C70(_this, POR_THIRD_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) por_awards_team_of_week_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call por_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_por_awards()
{
	PatchFunction(0x7D36C0, (DWORD)&por_awards_c);
	PatchFunction(0x7D3BE0, (DWORD)&por_awards_2_c);
	PatchFunction(0x7D3D60, (DWORD)&por_awards_team_of_week_c);
}
