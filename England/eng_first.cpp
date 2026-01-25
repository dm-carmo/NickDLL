#pragma warning (disable : 4733)
#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"

DWORD* eng_first_vtable = (DWORD*)0x969C68;

static DWORD(__thiscall* eng_first_subs)(BYTE* _this) = (DWORD(__thiscall*)(BYTE * _this))(0x572D90);

void eng_first_points_deductions(BYTE* _this, WORD current_year)
{
	if (current_year > 2025) return;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	cm3_clubs* sheff_wed = find_club("Sheffield Wednesday");
	if (sheff_wed) {
		comp_stats* data = (comp_stats*)_this;
		WORD total_teams = data->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(data->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats* tls = &table_teams[i];
			if (tls->club == sheff_wed) {
				tls->points = -18;
				tls->points_away = -18;
				return;
			}
		}
	}
}

void eng_first_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = eng_first_vtable;
	data->year = year;
	data->rules = 0x9;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	eng_first_subs(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_68A850(_this);
	eng_first_points_deductions(_this, year);
}

void setup_eng_first() {

}