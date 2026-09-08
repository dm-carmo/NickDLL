#pragma once

DWORD eng_setup_c(playable_nation_data* nation_data);

BYTE* setup_england_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6);
void setup_eng_nation();
void england_restructure();