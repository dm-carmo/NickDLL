#pragma once

DWORD sui_setup_c(playable_nation_data* nation_data);
BYTE* rb_switzerland_init(BYTE* _this, int* a2);

BYTE* setup_switzerland_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6);
void setup_sui_nation();