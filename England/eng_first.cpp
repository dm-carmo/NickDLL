#pragma warning (disable : 4733)
#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"
#include "eng_first.h"

DWORD* eng_first_vtable = (DWORD*)0x969C68;

void eng_first_points_deductions(BYTE* _this, WORD current_year)
{
	if (current_year > 2025) return;
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

void setup_eng_first() {

}