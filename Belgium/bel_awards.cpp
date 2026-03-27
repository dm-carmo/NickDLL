#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void belgium_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	*(WORD*)(_this + 0x8) = 18;

	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_MANAGER_OF_YEAR_9CF(), 6000, 1500, -1, 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_GOLDEN_BOOT_9CF(), 5000, 2500, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_EBONY_BOOT_9CF(), 4000, 2500, -1, 0, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_PLAYER_OF_YEAR_9CF(), 5000, 2500, -1, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_YOUNG_PLAYER_OF_YEAR_9CF(), 3500, 1500, -1, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// D1 awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BEL_FIRST_TEAM_OF_WEEK_9CF(), 0, 0, BEL_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_FIRST_TOP_GOALSCORER_9CF(), 3000, 1500, BEL_FIRST_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_FIRST_GOALKEEPER_OF_YEAR_9CF(), 5000, 1500, BEL_FIRST_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_FIRST_REVELATION_OF_YEAR_9CF(), 4000, 1500, BEL_FIRST_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// D2 awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BEL_SECOND_TEAM_OF_WEEK_9CF(), 0, 0, BEL_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_SECOND_TOP_GOALSCORER_9CF(), 1500, 750, BEL_SECOND_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_SECOND_REVELATION_OF_YEAR_9CF(), 1000, 700, BEL_SECOND_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// D3 VV awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BEL_THIRD_VV_TEAM_OF_WEEK_9CF(), 0, 0, BEL_THIRD_VV_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_THIRD_VV_TOP_GOALSCORER_9CF(), 750, 350, BEL_THIRD_VV_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_THIRD_VV_REVELATION_OF_YEAR_9CF(), 600, 250, BEL_THIRD_VV_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// D3 AC awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, BEL_THIRD_ACFF_TEAM_OF_WEEK_9CF(), 0, 0, BEL_THIRD_ACFF_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_THIRD_ACFF_TOP_GOALSCORER_9CF(), 750, 350, BEL_THIRD_ACFF_9CF(), 1, 0, 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, BEL_THIRD_ACFF_REVELATION_OF_YEAR_9CF(), 600, 250, BEL_THIRD_ACFF_9CF(), 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;
}

void __declspec(naked) bel_awards_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call belgium_awards
		add esp, 0x8
		ret 4
	}
}

char bel_awards_2(BYTE* _this, DWORD current_date) {
	DWORD nation = *(DWORD*)(_this + 0xE);
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 30, December, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		BYTE* ad9c60_ptr = (BYTE*)*ad9c60;
		yearly_player_award_nominate_7683C0(_this, current_date, awards_list[1], *(DWORD*)(ad9c60_ptr + 0xc), -1, NATION_BELGIUM_9CF(), -1, -1, -1, 0, -1);
		yearly_player_award_nominate_768720(_this, current_date, awards_list[2], *(DWORD*)(ad9c60_ptr + 0xc), AFRICA_9CF(), 0, 1, 0);
	}
	cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 6, June, *(WORD*)(current_date + 2), -1);
	date_day = *(WORD*)(cm_date);
	date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[0], BEL_FIRST_9CF());
		yearly_player_award_nominate_768CF0(_this, BEL_FIRST_9CF(), current_date, awards_list[3], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BEL_FIRST_9CF(), current_date, awards_list[4], 23, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BEL_FIRST_9CF(), current_date, awards_list[6], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BEL_FIRST_9CF(), current_date, awards_list[7], -1, 1, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BEL_FIRST_9CF(), current_date, awards_list[8], 23, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BEL_SECOND_9CF(), current_date, awards_list[10], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BEL_SECOND_9CF(), current_date, awards_list[11], 23, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BEL_THIRD_VV_9CF(), current_date, awards_list[13], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BEL_THIRD_VV_9CF(), current_date, awards_list[14], 23, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BEL_THIRD_ACFF_9CF(), current_date, awards_list[16], -1, 0, 2, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, BEL_THIRD_ACFF_9CF(), current_date, awards_list[17], 23, 0, 17, -1, -1, -1, -1);
	}
	return sub_768310(_this, current_date);
}

void __declspec(naked) bel_awards_2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call bel_awards_2
		add esp, 0x8
		ret 4
	}
}

void bel_awards_team_of_week(BYTE* _this, DWORD award_addr) {
	DWORD* awards_list = (DWORD*)*(DWORD*)(_this + 0x4);
	if (award_addr == awards_list[5]) {
		sub_769C70(_this, BEL_FIRST_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[9]) {
		sub_769C70(_this, BEL_SECOND_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[12]) {
		sub_769C70(_this, BEL_THIRD_VV_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[15]) {
		sub_769C70(_this, BEL_THIRD_ACFF_9CF(), award_addr);
		return;
	}
}

void __declspec(naked) bel_awards_team_of_week_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call bel_awards_team_of_week
		add esp, 0x8
		ret 4
	}
}

void setup_bel_awards()
{
	PatchFunction(0x424510, (DWORD)&bel_awards_c);
	PatchFunction(0x4249c0, (DWORD)&bel_awards_2_c);
	PatchFunction(0x424b60, (DWORD)&bel_awards_team_of_week_c);
}
