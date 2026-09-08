#pragma once

DWORD ksa_setup_c(playable_nation_data* nation_data);
BYTE* rb_saudi_init(BYTE* _this, int* a2);

BYTE* setup_saudi_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6);
void setup_ksa_nation();