#pragma once
#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\Helper.h"

void get_teams_for_conmebol(const char* szNation, int numberOfClubs);
void replacement_004C6430_full();
extern "C" int replacement_004C6430();
void setup_libertadores();