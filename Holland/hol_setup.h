#pragma once

DWORD hol_setup_c(playable_nation_data* nation_data);

BYTE* setup_holland_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6);
void setup_hol_nation();