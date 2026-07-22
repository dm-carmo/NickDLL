#include "constants.h"

int playoff_dates_sz = 104;
int fixture_dates_sz = 65;
int league_team_list_sz = 59;

using namespace std;

char* qualified_grp_msg = "{}<%s - Team Name(e.g.Ajax)>{} have guaranteed a place in the league phase of the {}<%s - Competition Name(e.g.Champions League)>{}.";
char* qualified_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for {}<%s - Competition Name(e.g.Champions League)>{} league phase";
char* drop_down_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} drop down to {}<%s - Competition Name(e.g.Champions League)>{}";
char* drop_down_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} drop down to {}<%s - Competition Name(e.g.Champions League)>{} league phase";
char* qualified_r16_msg = "{}<%s - Team Name(e.g.Ajax)>{} have guaranteed a place in the Round of 16 of the {}<%s - Competition Name(e.g.Champions League)>{}.";
char* qualified_r16_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} through to {}<%s - Competition Name(e.g.Champions League)>{} R of 16";
char* qualified_r32_msg = "{}<%s - Team Name(e.g.Ajax)>{} have guaranteed a place in the Round of 32 of the {}<%s - Competition Name(e.g.Champions League)>{}.";
char* qualified_r32_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} through to {}<%s - Competition Name(e.g.Champions League)>{} R of 32";
char* qualified_knockout_msg = "{}<%s - Team Name(e.g.Ajax)>{} have guaranteed a place in the Knockout Phase Playoff of the {}<%s - Competition Name(e.g.Champions League)>{}.";
char* qualified_knockout_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} through to {}<%s - Competition Name(e.g.Champions League)>{} Knockout Playoff";
char* qualified_rd2_msg = "{}<%s - Team Name(e.g.Ajax)>{} have guaranteed a place in the Second Round of the {}<%s - Competition Name(e.g.Champions League)>{}.";
char* qualified_rd2_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} through to {}<%s - Competition Name(e.g.Champions League)>{} 2nd Rnd";
char* qualified_qtr_msg = "{}<%s - Team Name(e.g.Ajax)>{} have guaranteed a place in the Quarter Finals of the {}<%s - Competition Name(e.g.Champions League)>{}.";
char* qualified_qtr_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} through to {}<%s - Competition Name(e.g.Champions League)>{} Qtr Final";
char* qualified_semi_msg = "{}<%s - Team Name(e.g.Ajax)>{} have guaranteed a place in the Semi Finals of the {}<%s - Competition Name(e.g.Champions League)>{}.";
char* qualified_semi_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} through to {}<%s - Competition Name(e.g.Champions League)>{} Semi Final";
char* qualified_playoff_msg = "{}<%s - Team Name(e.g.Ajax)>{} have guaranteed a place in the Playoff of the {}<%s - Competition Name(e.g.Champions League)>{}.";
char* qualified_playoff_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} through to {}<%s - Competition Name(e.g.Champions League)>{} Playoff";
char* qualified_champ_grp_msg = "{}<%s - Team Name(e.g.Ajax)>{} have qualified for the {}<%s - Competition Name(e.g.Champions League)>{} Championship Group.";
char* qualified_champ_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for championship group";
char* qualified_rel_grp_msg = "{}<%s - Team Name(e.g.Ajax)>{} have qualified for the {}<%s - Competition Name(e.g.Champions League)>{} Relegation Group.";
char* qualified_rel_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for relegation group";
char* qualified_gold_grp_msg = "{}<%s - Team Name(e.g.Ajax)>{} have qualified for the {}<%s - Competition Name(e.g.Champions League)>{} Second Stage Gold Group.";
char* qualified_gold_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for gold group";
char* qualified_silver_grp_msg = "{}<%s - Team Name(e.g.Ajax)>{} have qualified for the {}<%s - Competition Name(e.g.Champions League)>{} Second Stage Silver Group.";
char* qualified_silver_grp_title_msg = "{}<%s - Team Name(e.g.Ajax)>{} qualify for silver group";
char* uel_playoff_msg = "{}<%s - Team Name(e.g.Ajax)>{} through to Playoff";
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

char* register_msg1 = "{}<%s - Club Name(e.g.Chelsea)>{} may register one more player to be eligible for the league phase of the {}<%s - Competition Name(e.g.UEFA Cup)>{}.";
char* register_msg2 = "{}<%s - Club Name(e.g.Chelsea)>{} may register <%d - number(e.g.2)> more players to be eligible for the league phase of the {}<%s - Competition Name(e.g.UEFA Cup)>{}.";
char* register_msg3 = "{}<%s - Club Name(e.g.Chelsea)>{} may register <%d - number(e.g.2)> players to be eligible for the league phase of the {}<%s - Competition Name(e.g.UEFA Cup)>{}.";