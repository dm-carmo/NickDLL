#pragma once
#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\Helper.h"

void add_clubs_for_concacaf_comps(vector<cm3_clubs*>& vec, const char* szNation, int numberOfClubs);
void get_cup_loser_for_concacaf(vector<cm3_clubs*>& vec, const char* szNation, long comp_id);
void replacement_4c11a0_full();
extern "C" int replacement_4c11a0();
void setup_concacaf();