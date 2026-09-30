#include "constants.h"

int playoff_dates_sz = 104;
int fixture_dates_sz = 65;
int league_team_list_sz = 59;

using namespace std;

char* qualified_lge_stage_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for {}<%s - Competition Name(e.g.Champions League)>{} league phase";
char* qualified_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for {}<%s - Competition Name(e.g.Champions League)>{} group stage";
char* drop_down_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} drop down to {}<%s - Competition Name(e.g.Champions League)>{}";
char* qualified_champ_grp_msg = "{}<%s - Team Name(e.g.Ajax)>{} have qualified for the {}<%s - Competition Name(e.g.Champions League)>{} Championship Group.";
char* qualified_champ_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for championship group";
char* qualified_rel_grp_msg = "{}<%s - Team Name(e.g.Ajax)>{} have qualified for the {}<%s - Competition Name(e.g.Champions League)>{} Relegation Group.";
char* qualified_rel_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for relegation group";
char* qualified_gold_grp_msg = "{}<%s - Team Name(e.g.Ajax)>{} have qualified for the {}<%s - Competition Name(e.g.Champions League)>{} Second Stage Gold Group.";
char* qualified_gold_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for gold group";
char* qualified_silver_grp_msg = "{}<%s - Team Name(e.g.Ajax)>{} have qualified for the {}<%s - Competition Name(e.g.Champions League)>{} Second Stage Silver Group.";
char* qualified_silver_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for silver group";
char* qualified_wc_playoff_msg = "{}<%s - Team Name(e.g.Ajax)>{} have qualified for the inter-confederation play-offs.";
char* qualified_best3rd_msg = "{}<%s - Team Name(e.g.Ajax)>{} have finished as one of the best third placed teams in the {}<%s - Competition Name(e.g.Champions League)>{} tournament.";
char* qualified_wc_playoffs = "Qualified For Play-Offs";
char* lge_a = "League A";
char* lge_b = "League B";
char* lge_c = "League C";
char* lge_d = "League D";
char* lge_a_short = "Lge A";
char* lge_b_short = "Lge B";
char* lge_c_short = "Lge C";
char* lge_d_short = "Lge D";
char* r3_groups_drawn = "{}<%s - competition name(e.g.Champions League)>{} 3rd round groups drawn";
char* r4_groups_drawn = "{}<%s - competition name(e.g.Champions League)>{} 4th round groups drawn";
char* prom_lge_b = "Promoted From League B";
char* prom_lge_c = "Promoted From League C";
char* rele_lge_a = "Relegated From League A";
char* rele_lge_b = "Relegated From League B";
char* qualify_upper_comp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for {}<%s - Competition Name(e.g.Champions League)>{} playoff";

char* register_msg1 = "{}<%s - Club Name(e.g.Chelsea)>{} may register one more player to be eligible for the league phase of the {}<%s - Competition Name(e.g.UEFA Cup)>{}.";
char* register_msg2 = "{}<%s - Club Name(e.g.Chelsea)>{} may register <%d - number(e.g.2)> more players to be eligible for the league phase of the {}<%s - Competition Name(e.g.UEFA Cup)>{}.";
char* register_msg3 = "{}<%s - Club Name(e.g.Chelsea)>{} may register <%d - number(e.g.2)> players to be eligible for the league phase of the {}<%s - Competition Name(e.g.UEFA Cup)>{}.";

DWORD fourth_round_str = 0x9A7AA0;
DWORD knocked_out_of_comp_msg = 0x98713C;
DWORD through_to_next_round_msg = 0x987198;
DWORD won_in_round_msg = 0x9A3E1C;
DWORD fourth_place_msg = 0x987200;
DWORD third_place_msg = 0x987264;
DWORD runners_up_msg = 0x9872C8;
DWORD comp_winner_msg = 0x98732C;
DWORD win_promotion_msg = 0x9876CC;
DWORD relegated_msg = 0x987784;
DWORD through_to_semis_msg = 0x98A224;
DWORD qual_to_round_2_msg = 0x98AC50;
DWORD through_to_quarters_msg = 0x9A7E9C;
DWORD out_of_comp_msg = 0x9C46B8;
DWORD qualified_for_comp_msg = 0x9C470C;
DWORD qualified_for_world_cup_msg = 0xAD4B78;
DWORD knocked_out_of_wc_qual_msg = 0xAD4BA4;
DWORD qualify_for_playoff_msg = 0xAD4BE0;
DWORD qualified_from_comp_msg = 0xAD4D6C;
DWORD group_stage_str = 0x99B800;
DWORD playoff_str = 0x9A4399;
DWORD third_round_str = 0x9A7B10;
DWORD second_round_str = 0x9A7B94;
DWORD first_round_str = 0x9A7C04;
DWORD qualified_for_finals_str = 0x9C48A4;
DWORD qualified_for_world_cup_str = 0xAD4658;
DWORD league_stage_str = 0xAD4DDC;