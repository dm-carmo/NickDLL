#pragma once

DWORD rsa_setup_c(playable_nation_data* nation_data);
BYTE* rb_south_africa_init(BYTE* _this, int* a2);

BYTE* setup_south_africa_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6);
void setup_rsa_nation();