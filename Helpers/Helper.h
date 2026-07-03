#pragma once
#include <windows.h>
#include <vector>
#include "Structures\CMHeader.h"
#include "Config.h"
#include <random>

using namespace std;

extern char* szDebugFile;
extern Config configFile;
extern Config prizeMoneyFile;
extern std::default_random_engine rng;

void dprintf(const char* fmt, ...);
void WriteBytes(DWORD addr, int bytes, ...);
void WriteNOP(DWORD addr, int bytes);
void WriteWORD(DWORD addr, WORD data);
void WriteDWORD(DWORD addr, DWORD data);
void PatchFunction(DWORD addr, DWORD jmpTo);
int GetKey();

DWORD Get9CF(DWORD id);
WORD get_world_cup_hosts_in_continent(BYTE* _this, DWORD continentID, DWORD* out_host1_id, DWORD* out_host2_id);
cm3_clubs* get_club(DWORD clubID);
cm3_clubs* get_national_team(DWORD nationID);
vector<cm3_clubs*> get_all_national_teams();
vector<cm3_clubs*> get_national_teams_of_continent(DWORD continentID);
BYTE* get_loaded_league(DWORD compID);
cm3_nations* find_country(const char* szCountry);
cm3_nations* get_country(DWORD countryID);
cm3_continents* get_continent(DWORD continentID);
cm3_colours* get_colour(DWORD colourID);
cm3_staff* get_staff(DWORD staffID);
cm3_players* get_player(DWORD playerID);
cm3_non_players* get_non_player(DWORD nonPlayerID);
cm3_names* get_first_name(DWORD nameID);
cm3_names* get_second_name(DWORD nameID);
cm3_names* get_common_name(DWORD nameID);
vector<cm3_nations*> central_america_countries();
vector<cm3_nations*> caribbean_countries();
vector<cm3_nations*> get_countries_of_continent(DWORD continentID);
cm3_clubs* find_club(const char* szClub);
cm3_club_comps* get_comp(DWORD compID);
vector<cm3_clubs*> find_clubs_of_comp(DWORD comp_id, long nation_id = -1);
vector<cm3_clubs*> find_clubs_of_comp_reserve_division(DWORD comp_id, long nation_id = -1);
vector<cm3_clubs*> find_clubs_of_comp_main_reserve_division(DWORD main_comp_id, DWORD reserve_comp_id, long nation_id = -1);
vector<cm3_clubs*> find_clubs_of_comp_last_division(DWORD comp_id, long nation_id = -1);
cm3_club_comps* find_club_comp(const char* szClubComp);
cm3_staff_comps* find_award(const char* szAward);
cm3_cities* find_city(const char* szCity);
cm3_stadiums* find_stadium(const char* szStadium);
DWORD find_club_comp_id(const char* szClubComp, const char* szClubCompAlternative = NULL);
vector<cm3_club_comps*> find_club_comps_of_nation(const char* szNation);
vector<cm3_clubs*> find_clubs_of_continent(DWORD continent_id);
vector<cm3_clubs*> find_clubs_of_country(DWORD nation_id);
vector<cm3_clubs*> find_clubs_of_country_for_euro_playable(DWORD nation_id);
vector<cm3_clubs*> find_clubs_of_country_for_euro(DWORD nation_id);
void reset_club_euro_flags(DWORD continentID);
template <typename T> bool vector_contains_element(vector<T>& vec, T elem);
bool compareClubSeeding(cm3_clubs* c1, cm3_clubs* c2);
bool compareNationRanking(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubRep(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubRepInv(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubLastDivPos(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubLastDivPosInv(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubLatitude(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubLatitudeInv(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubLongitude(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubLongitudeInv(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubEWDiagNS(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubWEDiagNS(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubNation(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubAsiaWestEast(cm3_clubs* c1, cm3_clubs* c2);
cm3_clubs* get_last_comp_winner(cm3_club_comps* comp);
cm3_clubs* get_last_comp_runner_up(cm3_club_comps* comp);
cm3_clubs* get_last_comp_winner_by_year(cm3_club_comps* comp, WORD year);
cm3_clubs* get_last_comp_runner_up_by_year(cm3_club_comps* comp, WORD year);
WORD CountNumberOfTeamsInComp(DWORD CompID);
WORD CountNumberOfTeamsInReserveComp(DWORD CompID);
WORD CountNumberOfTeamsInCompNoReserve(DWORD CompID);
WORD CountNumberOfTeamsInCompWithGroup(DWORD CompID, DWORD GroupID);
team_league_stats* get_team_league_stats(DWORD comp_id, cm3_clubs* club, char stage_num = -1);
void check_number_of_fixtures(BYTE* _this, int created_fixtures, WORD needed_fixtures);
vector<cm3_clubs*> get_relegated_teams(DWORD compID);
bool sortTLS(team_league_stats s1, team_league_stats s2);
bool sortTeamSeeding(teams_seeded s1, teams_seeded s2);
vector<cm3_clubs*> get_random_weighted_clubs(vector<cm3_clubs*> list, unsigned int amount, bool to_promote);
void generic_prom_rel(DWORD nation_id, DWORD promote_from, DWORD relegate_from, int num_child_comps, ...);
int UpdateCountryCoefficient(cm3_clubs* club, char coeff);
void add_team_to_world_cup(cm3_clubs* club, bool send_news = true);
void add_team_to_world_cup_playoffs(cm3_clubs* club);

#include "Helper.tpp"