#pragma once

DWORD qat_setup_c(playable_nation_data* nation_data);
BYTE* rb_qatar_init(BYTE* _this, int* a2);

BYTE* setup_qatar_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6);
void setup_qat_nation();