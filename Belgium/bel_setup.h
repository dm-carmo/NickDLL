#pragma once

DWORD bel_setup_c(playable_nation_data* nation_data);

BYTE* setup_belgium_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6);
void setup_bel_nation();
void belgium_restructure();