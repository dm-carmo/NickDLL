#pragma once

void eng_conf_fixtures_c();
void eng_conf_set_table_fate();
void eng_conf_playoffs_c();
void eng_conf_init(BYTE* _this, WORD year, cm3_club_comps* comp);
void eng_conf_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max);
void setup_eng_conf();