#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>

void england_awards(BYTE* _this, int a2) {
	DWORD edi = *(DWORD*)(_this + 0x13);
	BYTE selected = ((cm3_nations*)*(DWORD*)(_this + 0xE))->NationLeagueSelected;
	if ((selected & 4) == 0) {
		*(WORD*)(_this + 0x8) = 26;
	}
	else {
		*(WORD*)(_this + 0x8) = 44; // was 32
	}
	DWORD* awards_list = (DWORD*)sub_944E46_malloc(*(WORD*)(_this + 0x8) * 4);
	*(DWORD*)(_this + 0x4) = (DWORD)awards_list;
	BYTE i = 0;
	BYTE esi = 0;

	// General awards
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ENG_PLAYER_OF_YEAR_9CF(), 8000, 5000, -1, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ENG_YOUNG_PLAYER_OF_YEAR_9CF(), 7000, 3500, -1, 1, 0, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Premier League awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ENG_PREMIER_TEAM_OF_WEEK_9CF(), 4000, 500, ENG_PREMIER_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_PREMIER_MANAGER_OF_MONTH_9CF(), 5000, 1500, ENG_PREMIER_9CF(), August, *current_year, May, *current_year + 1, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_PREMIER_PLAYER_OF_MONTH_9CF(), 5000, 1500, ENG_PREMIER_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_PREMIER_YOUNG_PLAYER_OF_MONTH_9CF(), 4500, 1000, ENG_PREMIER_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ENG_PREMIER_MANAGER_OF_YEAR_9CF(), 7500, 3500, ENG_PREMIER_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ENG_PREMIER_TEAM_OF_YEAR_9CF(), 6500, 2500, ENG_PREMIER_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// Championship awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ENG_FIRST_TEAM_OF_WEEK_9CF(), 3000, 500, ENG_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_FIRST_MANAGER_OF_MONTH_9CF(), 3000, 500, ENG_FIRST_9CF(), August, *current_year, May, *current_year + 1, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_FIRST_PLAYER_OF_MONTH_9CF(), 3500, 500, ENG_FIRST_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_FIRST_YOUNG_PLAYER_OF_MONTH_9CF(), 3000, 500, ENG_FIRST_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ENG_FIRST_MANAGER_OF_YEAR_9CF(), 5000, 500, ENG_FIRST_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ENG_FIRST_TEAM_OF_YEAR_9CF(), 4500, 500, ENG_FIRST_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// League One awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ENG_SECOND_TEAM_OF_WEEK_9CF(), 2000, 0, ENG_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_SECOND_MANAGER_OF_MONTH_9CF(), 2000, 0, ENG_SECOND_9CF(), August, *current_year, May, *current_year + 1, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_SECOND_PLAYER_OF_MONTH_9CF(), 2500, 0, ENG_SECOND_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_SECOND_YOUNG_PLAYER_OF_MONTH_9CF(), 2000, 0, ENG_SECOND_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ENG_SECOND_MANAGER_OF_YEAR_9CF(), 3000, 0, ENG_SECOND_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ENG_SECOND_TEAM_OF_YEAR_9CF(), 3000, 0, ENG_SECOND_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	// League Two awards
	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ENG_THIRD_TEAM_OF_WEEK_9CF(), 1500, 0, ENG_THIRD_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_THIRD_MANAGER_OF_MONTH_9CF(), 1000, 0, ENG_THIRD_9CF(), August, *current_year, May, *current_year + 1, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_THIRD_PLAYER_OF_MONTH_9CF(), 1750, 0, ENG_THIRD_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
	monthly_person_award_setup_766E10(pMem, edi, i, ENG_THIRD_YOUNG_PLAYER_OF_MONTH_9CF(), 1500, 0, ENG_THIRD_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
	yearly_person_award_setup_92FE80(pMem, edi, i, ENG_THIRD_MANAGER_OF_YEAR_9CF(), 2000, 0, ENG_THIRD_9CF(), 1, 0, 0, a2, 0);
	awards_list[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
	team_award_setup_8AF520(pMem, edi, i, ENG_THIRD_TEAM_OF_YEAR_9CF(), 2000, 0, ENG_THIRD_9CF(), 1, 0, a2, 1);
	awards_list[i++] = (DWORD)pMem;

	if ((selected & 4) != 0) {
		// National League awards
		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, ENG_CONFERENCE_TEAM_OF_WEEK_9CF(), 1500, 0, ENG_CONFERENCE_9CF(), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, ENG_CONFERENCE_MANAGER_OF_MONTH_9CF(), 1000, 0, ENG_CONFERENCE_9CF(), August, *current_year, May, *current_year + 1, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, ENG_CONFERENCE_PLAYER_OF_MONTH_9CF(), 1750, 0, ENG_CONFERENCE_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, ENG_CONFERENCE_YOUNG_PLAYER_OF_MONTH_9CF(), 1500, 0, ENG_CONFERENCE_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, ENG_CONFERENCE_MANAGER_OF_YEAR_9CF(), 2000, 0, ENG_CONFERENCE_9CF(), 1, 0, 0, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, ENG_CONFERENCE_TEAM_OF_YEAR_9CF(), 2000, 0, ENG_CONFERENCE_9CF(), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		// National North awards
		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, ENG_CONFERENCE_N_TEAM_OF_WEEK_9CF(), 1000, 0, ENG_CONFERENCE_NORTH_9CF(), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, ENG_CONFERENCE_N_MANAGER_OF_MONTH_9CF(), 750, 0, ENG_CONFERENCE_NORTH_9CF(), August, *current_year, May, *current_year + 1, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, ENG_CONFERENCE_N_PLAYER_OF_MONTH_9CF(), 1250, 0, ENG_CONFERENCE_NORTH_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, ENG_CONFERENCE_N_YOUNG_PLAYER_OF_MONTH_9CF(), 1000, 0, ENG_CONFERENCE_NORTH_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, ENG_CONFERENCE_N_MANAGER_OF_YEAR_9CF(), 1500, 0, ENG_CONFERENCE_NORTH_9CF(), 1, 0, 0, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, ENG_CONFERENCE_N_TEAM_OF_YEAR_9CF(), 1500, 0, ENG_CONFERENCE_NORTH_9CF(), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		// National South awards
		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, ENG_CONFERENCE_S_TEAM_OF_WEEK_9CF(), 1000, 0, ENG_CONFERENCE_SOUTH_9CF(), 1, 0, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, ENG_CONFERENCE_S_MANAGER_OF_MONTH_9CF(), 750, 0, ENG_CONFERENCE_SOUTH_9CF(), August, *current_year, May, *current_year + 1, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, ENG_CONFERENCE_S_PLAYER_OF_MONTH_9CF(), 1250, 0, ENG_CONFERENCE_SOUTH_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xA2);
		monthly_person_award_setup_766E10(pMem, edi, i, ENG_CONFERENCE_S_YOUNG_PLAYER_OF_MONTH_9CF(), 1000, 0, ENG_CONFERENCE_SOUTH_9CF(), August, *current_year, May, *current_year + 1, a2, 1);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		yearly_person_award_setup_92FE80(pMem, edi, i, ENG_CONFERENCE_S_MANAGER_OF_YEAR_9CF(), 1500, 0, ENG_CONFERENCE_SOUTH_9CF(), 1, 0, 0, a2, 0);
		awards_list[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0x25D);
		team_award_setup_8AF520(pMem, edi, i, ENG_CONFERENCE_S_TEAM_OF_YEAR_9CF(), 1500, 0, ENG_CONFERENCE_SOUTH_9CF(), 1, 0, a2, 1);
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
	convert_to_cm_date(cm_date, 5, April, *(WORD*)(current_date + 2), -1);
	WORD date_day = *(WORD*)(cm_date);
	WORD date_year = *(WORD*)(cm_date + 2);
	//DWORD leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_player_award_nominate_768CF0(_this, ENG_PREMIER_9CF(), current_date, awards_list[0], -1, 0, 17, -1, -1, -1, -1);
		yearly_player_award_nominate_768CF0(_this, ENG_PREMIER_9CF(), current_date, awards_list[1], 21, 0, 17, -1, -1, -1, -1);
		yearly_team_award_nominate_7698F0(_this, ENG_PREMIER_9CF(), awards_list[7]);
		yearly_team_award_nominate_7698F0(_this, ENG_FIRST_9CF(), awards_list[13]);
		yearly_team_award_nominate_7698F0(_this, ENG_SECOND_9CF(), awards_list[19]);
		yearly_team_award_nominate_7698F0(_this, ENG_THIRD_9CF(), awards_list[25]);
		if ((selected & 4) != 0) {
			yearly_team_award_nominate_7698F0(_this, ENG_CONFERENCE_9CF(), awards_list[31]);
			yearly_team_award_nominate_7698F0(_this, ENG_CONFERENCE_NORTH_9CF(), awards_list[37]);
			yearly_team_award_nominate_7698F0(_this, ENG_CONFERENCE_SOUTH_9CF(), awards_list[43]);
		}
	}
	cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 30, May, *(WORD*)(current_date + 2), -1);
	date_day = *(WORD*)(cm_date);
	date_year = *(WORD*)(cm_date + 2);
	//leap = *(DWORD*)(cm_date + 4);
	if (date_year == *(WORD*)(current_date + 2) && date_day == *(WORD*)(current_date)) {
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[6], ENG_PREMIER_9CF());
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[12], ENG_FIRST_9CF());
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[18], ENG_SECOND_9CF());
		yearly_staff_award_nominate_768940(_this, current_date, awards_list[24], ENG_THIRD_9CF());
		if ((selected & 4) != 0) {
			yearly_staff_award_nominate_768940(_this, current_date, awards_list[30], ENG_CONFERENCE_9CF());
			yearly_staff_award_nominate_768940(_this, current_date, awards_list[36], ENG_CONFERENCE_NORTH_9CF());
			yearly_staff_award_nominate_768940(_this, current_date, awards_list[42], ENG_CONFERENCE_SOUTH_9CF());
		}
	}
	BYTE sub_669340_ret = sub_669340(nation);
	WORD nation_day = pnd_list[sub_669340_ret].update_day;
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
			// National North
			monthly_person_award_nominate_7672E0((BYTE*)awards_list[33], *(WORD*)(current_date + 2));
			monthly_person_award_nominate_7672E0((BYTE*)awards_list[34], *(WORD*)(current_date + 2));
			monthly_person_award_nominate_7672E0((BYTE*)awards_list[35], *(WORD*)(current_date + 2));
			// National South
			monthly_person_award_nominate_7672E0((BYTE*)awards_list[39], *(WORD*)(current_date + 2));
			monthly_person_award_nominate_7672E0((BYTE*)awards_list[40], *(WORD*)(current_date + 2));
			monthly_person_award_nominate_7672E0((BYTE*)awards_list[41], *(WORD*)(current_date + 2));
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
	CM3_STAFF* person = sub_86F950(staff_hist_ptr, ENG_PREMIER_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[3], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	person = sub_86F950(staff_hist_ptr, ENG_FIRST_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[9], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	person = sub_86F950(staff_hist_ptr, ENG_SECOND_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[15], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	person = sub_86F950(staff_hist_ptr, ENG_THIRD_9CF());
	if (person) {
		sub_7671C0((BYTE*)awards_list[21], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
	}
	if ((selected & 4) != 0) {
		person = sub_86F950(staff_hist_ptr, ENG_CONFERENCE_9CF());
		if (person) {
			sub_7671C0((BYTE*)awards_list[27], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
		}
		person = sub_86F950(staff_hist_ptr, ENG_CONFERENCE_NORTH_9CF());
		if (person) {
			sub_7671C0((BYTE*)awards_list[33], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
		}
		person = sub_86F950(staff_hist_ptr, ENG_CONFERENCE_SOUTH_9CF());
		if (person) {
			sub_7671C0((BYTE*)awards_list[39], person->StaffID, person->StaffClubContracted->ClubID, *(BYTE*)(staff_hist_ptr + 0x14), *(WORD*)(staff_hist_ptr + 0x16));
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
		sub_767150((BYTE*)awards_list[34], arg1, -1);
		sub_767150((BYTE*)awards_list[35], arg1, 20);
		sub_767150((BYTE*)awards_list[40], arg1, -1);
		sub_767150((BYTE*)awards_list[41], arg1, 20);
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
		sub_769C70(_this, ENG_PREMIER_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[8]) {
		sub_769C70(_this, ENG_FIRST_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[14]) {
		sub_769C70(_this, ENG_SECOND_9CF(), award_addr);
		return;
	}
	if (award_addr == awards_list[20]) {
		sub_769C70(_this, ENG_THIRD_9CF(), award_addr);
		return;
	}
	if ((selected & 4) != 0) {
		if (award_addr == awards_list[26]) {
			sub_769C70(_this, ENG_CONFERENCE_9CF(), award_addr);
			return;
		}
		if (award_addr == awards_list[32]) {
			sub_769C70(_this, ENG_CONFERENCE_NORTH_9CF(), award_addr);
			return;
		}
		if (award_addr == awards_list[38]) {
			sub_769C70(_this, ENG_CONFERENCE_SOUTH_9CF(), award_addr);
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