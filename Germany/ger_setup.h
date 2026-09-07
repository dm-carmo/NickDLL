#pragma once

DWORD ger_setup_c(playable_nation_data* nation_data);

BYTE* setup_germany_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6);
void setup_ger_nation();
void germany_restructure();