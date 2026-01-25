#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers/new_league_ids.h>

DWORD* ita_ser_a_vtable = (DWORD*)0x96C3CC;
static DWORD(__thiscall* ita_ser_a_subs)(BYTE* _this) = (DWORD(__thiscall*)(BYTE * _this))(0x641640);

void ita_ser_a_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* ita_ser_b = get_loaded_league(Get9CF(0x9CF574));
	v1 = *(DWORD*)ita_ser_b;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(ita_ser_b);
	sub_689C80(_this, _this, ita_ser_b, 1, a2, -1, -1);

	BYTE* ita_ser_c = get_loaded_league(serie_c_id);
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

	comp_stats* comp_data = (comp_stats*)get_loaded_league(serie_c_id);
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

	for (int i = 0; i < get_club_count(); i++)
	{
		cm3_clubs* club = get_club(i);
		if (club)
		{
			if (club->ClubDivision && club->ClubNation)
			{
				DWORD compID = club->ClubDivision->ClubCompID;
				DWORD nationID = club->ClubNation->NationID;
				if (nationID == Get9CF(0x9CF360) &&		// Italy
					compID == Get9CF(0x9CF58C))			// Serie D
				{
					//dprintf("Available Club: %s (%s)\n", club->ClubName, club->ClubDivision->ClubCompName);
					available_clubs.push_back(club);
				}
			}
		}
	}

	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		int availableIdx = rand() % available_clubs.size();
		cm3_clubs* clubToRelegate = relegated_clubs[i];
		cm3_clubs* available = available_clubs[availableIdx];

		dprintf("Swapping Teams: %s (%s) <-> %s (%s)\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, available->ClubName, available->ClubDivision->ClubCompName);

		cm3_club_comps* tempDivision = available->ClubDivision;
		available->ClubDivision = clubToRelegate->ClubDivision;
		clubToRelegate->ClubDivision = tempDivision;
		clubToRelegate->ClubReserveDivision = 0;

		available_clubs.erase(available_clubs.begin() + availableIdx);
	}
}

void sort_serie_c_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(serie_c_id);
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 20) available_clubs[i]->ClubReserveDivision = get_comp(Get9CF(0x9CF580));
		else if (i < 40) available_clubs[i]->ClubReserveDivision = get_comp(Get9CF(0x9CF584));
		else available_clubs[i]->ClubReserveDivision = get_comp(Get9CF(0x9CF588));
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

	BYTE* ita_ser_b = get_loaded_league(Get9CF(0x9CF574));
	BYTE* ita_ser_c = get_loaded_league(serie_c_id);

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
	WriteVTablePtr(ita_ser_a_vtable, VTablePromRelUpdate, (DWORD)&ita_ser_a_prom_rel_update);
}
