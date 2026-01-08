#pragma once
#include <windows.h>
#include <vector>
#include "CMHeader.h"
#include "Config.h"
#include <random>

using namespace std;

extern char *szDebugFile;
extern Config configFile;
extern std::default_random_engine rng;

void dprintf(const char* fmt, ...);
void WriteBytes(DWORD addr, int bytes, ...);
void WriteDWORD(DWORD addr, DWORD data);
void PatchFunction(DWORD addr, DWORD jmpTo);
int GetKey();

cm3_nations* find_country(const char* szCountry);
vector<cm3_nations*> central_america_countries();
vector<cm3_nations*> caribbean_countries();
cm3_clubs* find_club(const char* szClub);
cm3_club_comps* find_club_comp(const char* szClubComp);
DWORD find_club_comp_id(const char* szClubComp, const char* szClubCompAlternative = NULL);
vector<cm3_club_comps*> find_club_comps_of_nation(const char* szNation);
vector<cm3_clubs*> find_clubs_of_country(DWORD nation_id);
vector<cm3_clubs*> find_clubs_of_country_for_euro_playable(DWORD nation_id);
vector<cm3_clubs*> find_clubs_of_country_for_euro(DWORD nation_id);
bool vector_contains_club(vector<cm3_clubs*> &vec, cm3_clubs* club);
bool compareClubRep(cm3_clubs* c1, cm3_clubs* c2);
bool compareClubLastDivPos(cm3_clubs* c1, cm3_clubs* c2);
cm3_clubs* get_last_comp_winner(cm3_club_comps* comp);
cm3_clubs* get_last_comp_runner_up(cm3_club_comps* comp);
int CountNumberOfTeamsInComp(DWORD CompID);