#pragma once

DWORD nor_setup_c(playable_nation_data* nation_data);

BYTE* setup_norway_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6);
void setup_nor_nation();
void norway_restructure();