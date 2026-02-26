#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* ita_ser_a_vtable = (DWORD*)0x96C3CC;
static DWORD(__thiscall* ita_ser_a_subs)(BYTE* _this) = (DWORD(__thiscall*)(BYTE * _this))(0x641640);

void ita_ser_a_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* ita_ser_b = get_loaded_league(ITA_SERIE_B_9CF());
	v1 = *(DWORD*)ita_ser_b;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(ita_ser_b);
	sub_689C80(_this, _this, ita_ser_b, 1, a2, -1, -1);

	BYTE* ita_ser_c = get_loaded_league(ITA_SERIE_C_9CF());
	comp_stats* ita_ser_c_data = (comp_stats*)ita_ser_c;
	v1 = *(DWORD*)ita_ser_c;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(ita_ser_c);
	BYTE* ita_ser_c_b = (BYTE*)ita_ser_c_data->stages[0];
	v1 = *(DWORD*)ita_ser_c_b;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(ita_ser_c_b);
	BYTE* ita_ser_c_c = (BYTE*)ita_ser_c_data->stages[1];
	v1 = *(DWORD*)ita_ser_c_c;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(ita_ser_c_c);
	sub_689C80(_this, ita_ser_b, ita_ser_c, 1, a2, -1, -1);
	sub_689C80(_this, ita_ser_b, ita_ser_c_b, 1, a2, -1, -1);
	sub_689C80(_this, ita_ser_b, ita_ser_c_c, 1, a2, -1, -1);
}

void __declspec(naked) ita_ser_a_prom_rel_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ita_ser_a_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall serie_d_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(ITA_SERIE_C_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				relegated_clubs.push_back(table_pos.club);
			}
		}
	}

	vector<cm3_clubs*> available_clubs;

	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = get_club(i);
		if (club)
		{
			if (club->ClubDivision && club->ClubNation)
			{
				DWORD compID = club->ClubDivision->ClubCompID;
				DWORD nationID = club->ClubNation->NationID;
				if (nationID == NATION_ITALY_9CF() &&		// Italy
					compID == ITA_SERIE_D_9CF())			// Serie D
				{
					available_clubs.push_back(club);
				}
			}
		}
	}

	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	int max_to_check = (available_clubs.size() > 15 ? 15 : available_clubs.size());
	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* clubToRelegate = relegated_clubs[i];
		cm3_clubs* available = available_clubs[availableIdx];

		//dprintf("Swapping Teams: %s (%s) <-> %s (%s)\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, available->ClubName, available->ClubDivision->ClubCompName);

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = available->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)available, (DWORD)topDivision, 1);
		clubToRelegate->ClubReserveDivision = 0;

		available_clubs.erase(available_clubs.begin() + availableIdx);
	}
}

void sort_serie_c_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(ITA_SERIE_C_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 20) available_clubs[i]->ClubReserveDivision = get_comp(ITA_SERIE_C_A_9CF());
		else if (i < 40) available_clubs[i]->ClubReserveDivision = get_comp(ITA_SERIE_C_B_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(ITA_SERIE_C_C_9CF());
	}
}

char ita_ser_a_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	ita_ser_a_prom_rel_update(_this, 1);
	serie_d_promotion(_this);
	sort_serie_c_clubs();

	sub_687970(_this, ebx);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
		}
	}
	data->year++;
	data->current_stage = -1;
	ita_ser_a_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	BYTE* ita_ser_b = get_loaded_league(ITA_SERIE_B_9CF());
	BYTE* ita_ser_c = get_loaded_league(ITA_SERIE_C_9CF());

	v1 = *(DWORD*)ita_ser_b;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(ita_ser_b);

	v1 = *(DWORD*)ita_ser_c;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(ita_ser_c);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) ita_ser_a_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_a_update
		add esp, 0x4
		ret
	}
}

void setup_ita_ser_a()
{
	WriteVTablePtr(ita_ser_a_vtable, VTableEoSUpdate, (DWORD)&ita_ser_a_update_c);
	WriteVTablePtr(ita_ser_a_vtable, VTablePromRelUpdate, (DWORD)&ita_ser_a_prom_rel_update_c);
}
