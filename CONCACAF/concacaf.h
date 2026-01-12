#pragma once
#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\Helper.h"

void AddConcacafClubs(vector<cm3_clubs*>& vec, const char* szNation, int numberOfClubs);
void ConcacafGetCupLoser(vector<cm3_clubs*>& vec, const char* szNation, long comp_id);
void replacement_4c11a0_full();
extern "C" int replacement_4c11a0();
void setup_concacaf();