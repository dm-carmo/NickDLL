#include "CMHeader.h"
#include <algorithm>
#include <Helpers/Helper.h>

WORD FixedTeamOrderInCup = 0x200;
WORD FixedTeamOrderInCup2 = 0x300;
WORD FixedTeamOrderInCup3 = 0x400;

cm3_staff_comps** awards = (cm3_staff_comps**)0xAE23E0;
DWORD* awards_count = (DWORD*)0xAE2388;

cm3_nations** nations = (cm3_nations**)0xAE23A8;
DWORD* nations_count = (DWORD*)0xAE2350;

cm3_clubs** clubs = (cm3_clubs**)0xAE23B4;
DWORD* clubs_count = (DWORD*)0xAE235C;

cm3_continents** continents = (cm3_continents**)0xAE23A4;
DWORD* continents_count = (DWORD*)0xAE234C;

cm3_cities** cities = (cm3_cities**)0xAE23AC;
DWORD* cities_count = (DWORD*)0xAE2354;

cm3_stadiums** stadiums = (cm3_stadiums**)0xAE23B0;
DWORD* stadiums_count = (DWORD*)0xAE2358;

cm3_club_comps** club_comps = (cm3_club_comps**)0xAE23D0;
DWORD* club_comps_count = (DWORD*)0xAE2378;

cm3_club_comp_history** club_comp_histories = (cm3_club_comp_history**)0xAE23D4;
DWORD* club_comp_histories_count = (DWORD*)0xAE237C;

DWORD** comp_stats_list = (DWORD**)0xADADFC;
DWORD* comp_stats_count = (DWORD*)0xADADF8;

cm3_colours** colours = (cm3_colours**)0xAE23EC;
DWORD* colours_count = (DWORD*)0xAE2394;

cm3_staff** staff = (cm3_staff**)0xAE23BC;
DWORD* staff_count = (DWORD*)0xAE2364;

cm3_players** players = (cm3_players**)0xAE23C4;
DWORD* players_count = (DWORD*)0xAE236C;

cm3_non_players** non_players = (cm3_non_players**)0xAE23C0;
DWORD* non_players_count = (DWORD*)0xAE2368;

cm3_names** first_names = (cm3_names**)0xAE23F0;
DWORD* first_names_count = (DWORD*)0xAE2398;

cm3_names** second_names = (cm3_names**)0xAE23F4;
DWORD* second_names_count = (DWORD*)0xAE239C;

cm3_names** common_names = (cm3_names**)0xAE23F8;
DWORD* common_names_count = (DWORD*)0xAE23A0;

DWORD* current_date = (DWORD*)0xAE2C90;
WORD* current_year = (WORD*)0xAE2C92;

DWORD* staff_history = (DWORD*)0xDD7F00;
DWORD* dd6ec8 = (DWORD*)0xDD6EC8;

//const DWORD pnd_count = 36;
const DWORD pnd_count = 42;
playable_nation_data* pnd_list = new playable_nation_data[pnd_count]; //0xB63D60
playable_nation_data** pnd_list_default = (playable_nation_data**)0xB63D60;
BYTE* pnd_order = new BYTE[pnd_count];

uefa_seedings** uefa_seeding_list = (uefa_seedings**)0xDE1F58;

DWORD* b5e134 = (DWORD*)0xB5E134;
DWORD* b74340 = (DWORD*)0xB74340;
DWORD* b74318 = (DWORD*)0xB74318;
DWORD* b67a44 = (DWORD*)0xB67A44;
DWORD* ae1050 = (DWORD*)0xAE1050;
DWORD* ad9c60 = (DWORD*)0xAD9C60;
DWORD* ae2a38 = (DWORD*)0xAE2A38;
DWORD* ae28f0 = (DWORD*)0xAE28F0;