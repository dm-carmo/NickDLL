#pragma warning (disable : 4996)
#include "Helper.h"
#include <stdio.h>
#include <conio.h>
#include <algorithm>
#include "generic_functions.h"
#include "constants.h"
#include "9cf_constants.h"

char* szDebugFile = "";

Config configFile = Config();
Config prizeMoneyFile = Config();
std::default_random_engine rng = std::default_random_engine{};

void dprintf(const char* fmt, ...)
{
	char printString[1024];
	va_list argp;
	va_start(argp, fmt);
	vsprintf_s(printString, fmt, argp);
	va_end(argp);

	// OutputDebugString(printString);
	printf(printString);

	if (_stricmp(szDebugFile, "") != 0)
	{
		FILE* fout = fopen(szDebugFile, "a+t");
		if (fout)
		{
			fprintf(fout, printString);
			fclose(fout);
		}
	}
}

void WriteBytes(DWORD addr, int bytes, ...)
{
	va_list valist;
	va_start(valist, bytes);

	for (int i = 0; i < bytes; i++)
	{
		unsigned char b = va_arg(valist, unsigned char);

		DWORD dwOldProt, dwOldProt2;
		VirtualProtect((void*)addr, 1, PAGE_EXECUTE_READWRITE, &dwOldProt);
		*((BYTE*)addr) = b;
		VirtualProtect((void*)addr, 1, dwOldProt, &dwOldProt2);

		addr++;
	}
	va_end(valist);
}

void WriteNOP(DWORD addr, int bytes)
{
	for (int i = 0; i < bytes; i++)
	{
		DWORD dwOldProt, dwOldProt2;
		VirtualProtect((void*)addr, 1, PAGE_EXECUTE_READWRITE, &dwOldProt);
		*((BYTE*)addr) = 0x90;
		VirtualProtect((void*)addr, 1, dwOldProt, &dwOldProt2);

		addr++;
	}
}

void WriteWORD(DWORD addr, WORD data)
{
	DWORD dwOldProt, dwOldProt2;
	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &dwOldProt);
	*((WORD*)addr) = data;
	VirtualProtect((void*)addr, 4, dwOldProt, &dwOldProt2);
}

void WriteDWORD(DWORD addr, DWORD data)
{
	DWORD dwOldProt, dwOldProt2;
	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &dwOldProt);
	*((DWORD*)addr) = data;
	VirtualProtect((void*)addr, 4, dwOldProt, &dwOldProt2);
}

void PatchFunction(DWORD addr, DWORD jmpTo)
{
	DWORD relAddr = (jmpTo - addr) - 5;
	WriteBytes(addr, 1, 0xE9);
	WriteDWORD(addr + 1, relAddr);
}

int GetKey()
{
	printf("Press any key...");
	return _getch();
}

DWORD Get9CF(DWORD id)
{
	return *(DWORD*)id;
}

cm3_clubs* get_club(DWORD clubID)
{
	return (clubID != -1L) ? &(*clubs)[clubID] : NULL;
}

cm3_clubs* get_national_team(DWORD nationID)
{
	return (nationID != -1L) ? &(*clubs)[*clubs_count + (nationID - 2 * *nations_count)] : NULL;
}

vector<cm3_clubs*>  get_all_national_teams() {
	vector<cm3_clubs*> ret;
	for (DWORD i = 0; i < *nations_count; i++)
	{
		cm3_clubs* c = &(*clubs)[*clubs_count + (i - 2 * *nations_count)];
		if (c->ClubNation && c->ClubNation->NationContinent)
			ret.push_back(c);
	}
	return ret;
}

BYTE* get_loaded_league(DWORD compID)
{
	return (BYTE*)*&(*comp_stats_list)[compID];
}

cm3_nations* find_country(const char* szCountry)
{
	for (DWORD i = 0; i < *nations_count; i++)
	{
		char* nation_db_name = get_db_nation_name(&(*nations)[i]);
		if (_stricmp(nation_db_name, szCountry) == 0)
			return &(*nations)[i];
	}
	return NULL;
}

cm3_nations* get_country(DWORD countryID)
{
	return (countryID != -1L) ? &(*nations)[countryID] : NULL;
}

cm3_continents* get_continent(DWORD continentID)
{
	return (continentID != -1L) ? &(*continents)[continentID] : NULL;
}

cm3_colours* get_colour(DWORD colourID) {
	return (colourID != -1L) ? &(*colours)[colourID] : NULL;
}

cm3_staff* get_staff(DWORD staffID) {
	return (staffID != -1L) ? &(*staff)[staffID] : NULL;
}

cm3_players* get_player(DWORD playerID) {
	return (playerID != -1L) ? &(*players)[playerID] : NULL;
}

cm3_non_players* get_non_player(DWORD nonPlayerID) {
	return (nonPlayerID != -1L) ? &(*non_players)[nonPlayerID] : NULL;
}

cm3_names* get_first_name(DWORD nameID) {
	return (nameID != -1L) ? &(*first_names)[nameID] : NULL;
}

cm3_names* get_second_name(DWORD nameID) {
	return (nameID != -1L) ? &(*second_names)[nameID] : NULL;
}

cm3_names* get_common_name(DWORD nameID) {
	return (nameID != -1L) ? &(*common_names)[nameID] : NULL;
}

vector<cm3_nations*> central_america_countries()
{
	vector<cm3_nations*> ret;
	for (DWORD i = 0; i < *nations_count; i++)
	{
		if ((*nations)[i].NationID == NATION_MEXICO_9CF() ||
			(*nations)[i].NationID == NATION_USA_9CF() ||
			(*nations)[i].NationID == NATION_CANADA_9CF())
			continue;
		if ((*nations)[i].NationContinent != NULL && (*nations)[i].NationRegion == 7)
			ret.push_back(&(*nations)[i]);
	}
	return ret;
}

vector<cm3_nations*> caribbean_countries()
{
	vector<cm3_nations*> ret;
	for (DWORD i = 0; i < *nations_count; i++)
	{
		if ((*nations)[i].NationContinent != NULL && (*nations)[i].NationRegion == 6)
			ret.push_back(&(*nations)[i]);
	}
	return ret;
}

vector<cm3_nations*> get_countries_of_continent(DWORD continentID) {
	vector<cm3_nations*> ret;
	for (DWORD i = 0; i < *nations_count; i++)
	{
		if ((*nations)[i].NationContinent && (*nations)[i].NationContinent->ContinentID == continentID)
			ret.push_back(&(*nations)[i]);
	}
	return ret;
}

cm3_clubs* find_club(const char* szClub)
{
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		char* club_db_name = get_db_club_name(&(*clubs)[i]);
		if (strcmp(club_db_name, szClub) == 0)
			return &(*clubs)[i];
	}
	return NULL;
}

cm3_club_comps* get_comp(DWORD compID)
{
	return (compID != -1L) ? &(*club_comps)[compID] : NULL;
}

vector<cm3_clubs*> find_clubs_of_comp(DWORD comp_id, long nation_id)
{
	vector<cm3_clubs*> ret;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		if (!(*clubs)[i].ClubNation) continue;
		if (!(*clubs)[i].ClubDivision) continue;
		if ((*clubs)[i].ClubDivision->ClubCompID == comp_id && (nation_id == -1 || (*clubs)[i].ClubNation->NationID == nation_id))
			ret.push_back(&(*clubs)[i]);
	}
	return ret;
}

vector<cm3_clubs*> find_clubs_of_comp_reserve_division(DWORD comp_id, long nation_id)
{
	vector<cm3_clubs*> ret;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		if (!(*clubs)[i].ClubNation) continue;
		if (!(*clubs)[i].ClubReserveDivision) continue;
		if ((*clubs)[i].ClubReserveDivision->ClubCompID == comp_id && (nation_id == -1 || (*clubs)[i].ClubNation->NationID == nation_id))
			ret.push_back(&(*clubs)[i]);
	}
	return ret;
}

vector<cm3_clubs*> find_clubs_of_comp_main_reserve_division(DWORD main_comp_id, DWORD reserve_comp_id, long nation_id)
{
	vector<cm3_clubs*> ret;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		if (!(*clubs)[i].ClubNation) continue;
		if (!(*clubs)[i].ClubDivision) continue;
		if (!(*clubs)[i].ClubReserveDivision) continue;
		if ((*clubs)[i].ClubDivision->ClubCompID == main_comp_id && (*clubs)[i].ClubReserveDivision->ClubCompID == reserve_comp_id &&
			(nation_id == -1 || (*clubs)[i].ClubNation->NationID == nation_id))
			ret.push_back(&(*clubs)[i]);
	}
	return ret;
}

vector<cm3_clubs*> find_clubs_of_comp_last_division(DWORD comp_id, long nation_id)
{
	vector<cm3_clubs*> ret;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		if (!(*clubs)[i].ClubNation) continue;
		if (!(*clubs)[i].ClubLastDivision) continue;
		if ((*clubs)[i].ClubLastDivision->ClubCompID == comp_id && (nation_id == -1 || (*clubs)[i].ClubNation->NationID == nation_id))
			ret.push_back(&(*clubs)[i]);
	}
	return ret;
}

vector<cm3_clubs*> find_clubs_of_continent(DWORD continent_id)
{
	vector<cm3_clubs*> ret;
	for (DWORD i = 0; i < *clubs_count - 2 * *nations_count; i++)
	{
		if ((*clubs)[i].ClubNation && (*clubs)[i].ClubNation->NationContinent && (*clubs)[i].ClubNation->NationContinent->ContinentID == continent_id)
		{
			cm3_clubs* club = &(*clubs)[i];
			ret.push_back(club);
		}
	}
	return ret;
}

vector<cm3_clubs*> find_clubs_of_country(DWORD nation_id)
{
	vector<cm3_clubs*> ret;
	for (DWORD i = 0; i < *clubs_count - 2 * *nations_count; i++)
	{
		if ((*clubs)[i].ClubNation != NULL && (*clubs)[i].ClubNation->NationID == nation_id)
		{
			cm3_clubs* club = &(*clubs)[i];
			ret.push_back(club);
		}
	}
	return ret;
}

// Gets all clubs from the country that do not have a Euro (i.e. continental) competition set, for playable countries as it removes clubs with no last division
vector<cm3_clubs*> find_clubs_of_country_for_euro_playable(DWORD nation_id)
{
	vector<cm3_clubs*> ret;
	for (DWORD i = 0; i < *clubs_count - 2 * *nations_count; i++)
	{
		if ((*clubs)[i].ClubNation != NULL && (*clubs)[i].ClubNation->NationID == nation_id)
		{
			cm3_clubs* club = &(*clubs)[i];

			// Don't add Lower Division Clubs
			if (!club->ClubDivision || club->ClubDivision->ClubCompID != A_LOWER_9CF() || club->ClubDivision->ClubCompID != A_LOWER_B_9CF())
				if (club->ClubEuroFlag == -1 && club->ClubLastDivision)
				{
					DWORD is_main_club;
					cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
					if (!ret_club || is_main_club) ret.push_back(club);
				}
		}
	}
	// Special case: Switzerland
	if (nation_id == NATION_SWITZERLAND_9CF()) {
		if (CLUB_VADUZ_9CF() >= 0)
		{
			cm3_clubs* vaduz = &(*clubs)[CLUB_VADUZ_9CF()];
			auto it = find(ret.begin(), ret.end(), vaduz);
			if (it != ret.end()) ret.erase(it);
		}
		if (CLUB_BALZERS_9CF() >= 0)
		{
			cm3_clubs* balzers = &(*clubs)[CLUB_BALZERS_9CF()];
			auto it = find(ret.begin(), ret.end(), balzers);
			if (it != ret.end()) ret.erase(it);
		}
		if (CLUB_ESCHEN_MAUREN_9CF() >= 0)
		{
			cm3_clubs* eschen = &(*clubs)[CLUB_ESCHEN_MAUREN_9CF()];
			auto it = find(ret.begin(), ret.end(), eschen);
			if (it != ret.end()) ret.erase(it);
		}
	}
	return ret;
}

// Gets all clubs from the country that do not have a Euro (i.e. continental) competition set
vector<cm3_clubs*> find_clubs_of_country_for_euro(DWORD nation_id)
{
	vector<cm3_clubs*> ret;
	for (DWORD i = 0; i < *clubs_count - 2 * *nations_count; i++)
	{
		if ((*clubs)[i].ClubNation != NULL && (*clubs)[i].ClubNation->NationID == nation_id)
		{
			cm3_clubs* club = &(*clubs)[i];

			if (club->ClubEuroFlag == -1)
			{
				DWORD is_main_club;
				cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
				if (!ret_club || is_main_club) ret.push_back(club);
			}
		}
	}
	// Special case: Switzerland
	if (nation_id == NATION_SWITZERLAND_9CF()) {
		if (CLUB_VADUZ_9CF() >= 0)
		{
			cm3_clubs* vaduz = &(*clubs)[CLUB_VADUZ_9CF()];
			auto it = find(ret.begin(), ret.end(), vaduz);
			if (it != ret.end()) ret.erase(it);
		}
		if (CLUB_BALZERS_9CF() >= 0)
		{
			cm3_clubs* balzers = &(*clubs)[CLUB_BALZERS_9CF()];
			auto it = find(ret.begin(), ret.end(), balzers);
			if (it != ret.end()) ret.erase(it);
		}
		if (CLUB_ESCHEN_MAUREN_9CF() >= 0)
		{
			cm3_clubs* eschen = &(*clubs)[CLUB_ESCHEN_MAUREN_9CF()];
			auto it = find(ret.begin(), ret.end(), eschen);
			if (it != ret.end()) ret.erase(it);
		}
	}
	// Special case: Liechtenstein
	if (nation_id == NATION_LIECHTENSTEIN_9CF()) {
		if (CLUB_VADUZ_9CF() >= 0)
		{
			cm3_clubs* vaduz = &(*clubs)[CLUB_VADUZ_9CF()];
			if (vaduz->ClubEuroFlag == -1) ret.push_back(vaduz);
		}
		if (CLUB_BALZERS_9CF() >= 0)
		{
			cm3_clubs* balzers = &(*clubs)[CLUB_BALZERS_9CF()];
			if (balzers->ClubEuroFlag == -1) ret.push_back(balzers);
		}
		if (CLUB_ESCHEN_MAUREN_9CF() >= 0)
		{
			cm3_clubs* eschen = &(*clubs)[CLUB_ESCHEN_MAUREN_9CF()];
			if (eschen->ClubEuroFlag == -1) ret.push_back(eschen);
		}
	}
	return ret;
}

void reset_club_euro_flags(DWORD continentID) {
	for (DWORD i = 0; i < *clubs_count - 2 * *nations_count; i++)
	{
		if ((*clubs)[i].ClubNation && (*clubs)[i].ClubNation->NationContinent && (*clubs)[i].ClubNation->NationContinent->ContinentID == continentID)
		{
			(&(*clubs)[i])->ClubEuroFlag = -1;
		}
	}
}

cm3_club_comps* find_club_comp(const char* szClubComp)
{
	for (DWORD i = 0; i < *club_comps_count; i++)
	{
		if (_stricmp((*club_comps)[i].ClubCompName, szClubComp) == 0)
			return &(*club_comps)[i];
	}
	return NULL;
}

cm3_staff_comps* find_award(const char* szAward)
{
	for (DWORD i = 0; i < *awards_count; i++)
	{
		if (_stricmp((*awards)[i].StaffCompName, szAward) == 0)
			return &(*awards)[i];
	}
	return NULL;
}

cm3_cities* find_city(const char* szCity)
{
	for (DWORD i = 0; i < *cities_count; i++)
	{
		if (_stricmp((*cities)[i].CityName, szCity) == 0)
			return &(*cities)[i];
	}
	return NULL;
}

cm3_stadiums* find_stadium(const char* szStadium)
{
	for (DWORD i = 0; i < *stadiums_count; i++)
	{
		if (_stricmp((*stadiums)[i].StadiumName, szStadium) == 0)
			return &(*stadiums)[i];
	}
	return NULL;
}

DWORD find_club_comp_id(const char* szClubComp, const char* szClubCompAlternative)
{
	DWORD CompID = -1L;
	cm3_club_comps* comp = find_club_comp(szClubComp);
	if (!comp && szClubCompAlternative)
		comp = find_club_comp(szClubCompAlternative);
	if (comp)
		CompID = comp->ClubCompID;
	return CompID;
}

vector<cm3_club_comps*> find_club_comps_of_nation(const char* szNation)
{
	vector<cm3_club_comps*> ret;

	cm3_nations* nation = find_country(szNation);
	if (nation)
	{
		for (DWORD i = 0; i < *club_comps_count; i++)
		{
			if ((*club_comps)[i].ClubCompNation == nation)
				ret.push_back(&(*club_comps)[i]);
		}
	}

	return ret;
}

bool compareClubSeeding(cm3_clubs* c1, cm3_clubs* c2)
{
	if (c1->ClubEuroSeeding == c2->ClubEuroSeeding) return (c1->ClubReputation > c2->ClubReputation);
	return (c1->ClubEuroSeeding > c2->ClubEuroSeeding);
}

bool compareClubRep(cm3_clubs* c1, cm3_clubs* c2)
{
	return (c1->ClubReputation > c2->ClubReputation);
}

bool compareClubRepInv(cm3_clubs* c1, cm3_clubs* c2)
{
	return compareClubRep(c2, c1);
}

bool compareClubLastDivPos(cm3_clubs* c1, cm3_clubs* c2)
{
	short c1_comp_rep = -3;
	short c2_comp_rep = -3;
	if (c1->ClubLastDivision)
	{
		if (c1->ClubLastDivision->ClubCompID == A_PREMIER_9CF()) c1_comp_rep = 0;
		else if (c1->ClubLastDivision->ClubCompID == A_LOWER_9CF()) c1_comp_rep = -1;
		else if (c1->ClubLastDivision->ClubCompID == A_LOWER_B_9CF()) c1_comp_rep = -2;
		else c1_comp_rep = c1->ClubLastDivision->ClubCompReputation;
	}
	if (c2->ClubLastDivision)
	{
		if (c2->ClubLastDivision->ClubCompID == A_PREMIER_9CF()) c2_comp_rep = 0;
		else if (c2->ClubLastDivision->ClubCompID == A_LOWER_9CF()) c2_comp_rep = -1;
		else if (c2->ClubLastDivision->ClubCompID == A_LOWER_B_9CF()) c2_comp_rep = -2;
		else c2_comp_rep = c2->ClubLastDivision->ClubCompReputation;
	}
	if (c1_comp_rep != c2_comp_rep) return (c1_comp_rep > c2_comp_rep);
	return (c1->ClubLastPosition < c2->ClubLastPosition);
}

bool compareClubLastDivPosInv(cm3_clubs* c1, cm3_clubs* c2)
{
	return compareClubLastDivPos(c2, c1);
}

bool compareClubLatitude(cm3_clubs* c1, cm3_clubs* c2)
{
	double l1 = 0, l2 = 0;
	if (c1->ClubStadium && c1->ClubStadium->StadiumCity)
		l1 = c1->ClubStadium->StadiumCity->CityLatitude;
	if (c2->ClubStadium && c2->ClubStadium->StadiumCity)
		l2 = c2->ClubStadium->StadiumCity->CityLatitude;
	return l1 > l2;
}

bool compareClubLatitudeInv(cm3_clubs* c1, cm3_clubs* c2)
{
	return compareClubLatitude(c2, c1);
}

bool compareClubLongitude(cm3_clubs* c1, cm3_clubs* c2)
{
	double l1 = 0, l2 = 0;
	if (c1->ClubStadium && c1->ClubStadium->StadiumCity)
		l1 = c1->ClubStadium->StadiumCity->CityLongitude;
	if (c2->ClubStadium && c2->ClubStadium->StadiumCity)
		l2 = c2->ClubStadium->StadiumCity->CityLongitude;
	return l1 > l2;
}

bool compareClubLongitudeInv(cm3_clubs* c1, cm3_clubs* c2)
{
	return compareClubLongitude(c2, c1);
}

bool compareClubEWDiagNS(cm3_clubs* c1, cm3_clubs* c2)
{
	double lat1 = 0, lat2 = 0;
	double lon1 = 0, lon2 = 0;
	if (c1->ClubStadium && c1->ClubStadium->StadiumCity)
	{
		lat1 = c1->ClubStadium->StadiumCity->CityLatitude;
		lon1 = c1->ClubStadium->StadiumCity->CityLongitude;
	}
	if (c2->ClubStadium && c2->ClubStadium->StadiumCity)
	{
		lat2 = c2->ClubStadium->StadiumCity->CityLatitude;
		lon2 = c2->ClubStadium->StadiumCity->CityLongitude;
	}
	return atan2(lon1, lat1) > atan2(lon2, lat2);
}

bool compareClubWEDiagNS(cm3_clubs* c1, cm3_clubs* c2)
{
	double lat1 = 0, lat2 = 0;
	double lon1 = 0, lon2 = 0;
	if (c1->ClubStadium && c1->ClubStadium->StadiumCity)
	{
		lat1 = c1->ClubStadium->StadiumCity->CityLatitude;
		lon1 = c1->ClubStadium->StadiumCity->CityLongitude;
	}
	if (c2->ClubStadium && c2->ClubStadium->StadiumCity)
	{
		lat2 = c2->ClubStadium->StadiumCity->CityLatitude;
		lon2 = c2->ClubStadium->StadiumCity->CityLongitude;
	}
	return atan2(-lon1, lat1) > atan2(-lon2, lat2);
}

bool compareClubNation(cm3_clubs* c1, cm3_clubs* c2)
{
	long n1 = -1, n2 = -1;
	if (c1->ClubNation)
	{
		n1 = c1->ClubNation->NationID;
	}
	if (c2->ClubNation)
	{
		n2 = c2->ClubNation->NationID;
	}
	return n1 < n2;
}

bool compareClubAsiaWestEast(cm3_clubs* c1, cm3_clubs* c2)
{
	bool c1_west = false, c2_west = false;
	if (!c1->ClubNation || !c2->ClubNation) return compareClubLongitude(c1, c2);
	c1_west = find(asia_west.begin(), asia_west.end(), get_db_nation_name(c1->ClubNation)) != asia_west.end();
	c2_west = find(asia_west.begin(), asia_west.end(), get_db_nation_name(c2->ClubNation)) != asia_west.end();
	if (c1_west != c2_west) return c1_west;
	else return compareClubLongitude(c1, c2);
}

cm3_clubs* get_last_comp_winner(cm3_club_comps* comp)
{
	vector<cm3_club_comp_history*> ret;
	for (DWORD i = 0; i < *club_comp_histories_count; i++) {
		if ((*club_comp_histories)[i].ClubCompHistoryClubComp == comp)
		{
			cm3_club_comp_history* hist = &(*club_comp_histories)[i];
			ret.push_back(hist);
		}
	}
	if (ret.size() < 1) return nullptr;
	sort(ret.begin(), ret.end(), [](const cm3_club_comp_history* h1, const cm3_club_comp_history* h2)
		{
			return h1->ClubCompHistoryYear > h2->ClubCompHistoryYear;
		});
	return ret[0]->ClubCompHistoryWinners;
}

cm3_clubs* get_last_comp_runner_up(cm3_club_comps* comp)
{
	vector<cm3_club_comp_history*> ret;
	for (DWORD i = 0; i < *club_comp_histories_count; i++) {
		if ((*club_comp_histories)[i].ClubCompHistoryClubComp == comp)
		{
			cm3_club_comp_history* hist = &(*club_comp_histories)[i];
			ret.push_back(hist);
		}
	}
	if (ret.size() < 1) return nullptr;
	sort(ret.begin(), ret.end(), [](const cm3_club_comp_history* h1, const cm3_club_comp_history* h2)
		{
			return h1->ClubCompHistoryYear > h2->ClubCompHistoryYear;
		});
	return ret[0]->ClubCompHistoryRunnersUp;
}

cm3_clubs* get_last_comp_winner_by_year(cm3_club_comps* comp, WORD year)
{
	for (DWORD i = 0; i < *club_comp_histories_count; i++) {
		cm3_club_comp_history hist = (*club_comp_histories)[i];
		if (hist.ClubCompHistoryClubComp == comp && hist.ClubCompHistoryYear == year)
		{
			return hist.ClubCompHistoryWinners;
		}
	}
	return NULL;
}

cm3_clubs* get_last_comp_runner_up_by_year(cm3_club_comps* comp, WORD year)
{
	for (DWORD i = 0; i < *club_comp_histories_count; i++) {
		cm3_club_comp_history hist = (*club_comp_histories)[i];
		if (hist.ClubCompHistoryClubComp == comp && hist.ClubCompHistoryYear == year)
		{
			return hist.ClubCompHistoryRunnersUp;
		}
	}
	return NULL;
}

WORD CountNumberOfTeamsInComp(DWORD CompID)
{
	WORD numberOfLeagueTeams = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == CompID)
			numberOfLeagueTeams++;
	}
	return numberOfLeagueTeams;
}

WORD CountNumberOfTeamsInReserveComp(DWORD CompID)
{
	WORD numberOfLeagueTeams = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubReserveDivision && club->ClubReserveDivision->ClubCompID == CompID)
			numberOfLeagueTeams++;
	}
	return numberOfLeagueTeams;
}

WORD CountNumberOfTeamsInCompNoReserve(DWORD CompID)
{
	WORD numberOfLeagueTeams = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == CompID)
		{
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
			if (!ret_club || is_main_club) numberOfLeagueTeams++;
		}
	}
	return numberOfLeagueTeams;
}

WORD CountNumberOfTeamsInCompWithGroup(DWORD CompID, DWORD GroupID)
{
	WORD numberOfLeagueTeams = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == CompID
			&& club->ClubReserveDivision && club->ClubReserveDivision->ClubCompID == GroupID)
			numberOfLeagueTeams++;
	}
	return numberOfLeagueTeams;
}

team_league_stats* get_team_league_stats(DWORD comp_id, cm3_clubs* club, char stage_num)
{
	BYTE* loaded = get_loaded_league(comp_id);
	if (loaded) {
		comp_stats* data = (comp_stats*)loaded;
		if (stage_num >= 0) data = (comp_stats*)data->stages[stage_num];
		WORD num_teams = data->n_teams;
		team_league_stats* table = (team_league_stats*)(data->team_league_table);
		for (int i = 0; i < num_teams; i++) {
			cm3_clubs* c = table[i].club;
			if (c == club) return &table[i];
		}
	}
	return NULL;
}

void check_number_of_fixtures(BYTE* _this, int created_fixtures, WORD needed_fixtures)
{
	if (created_fixtures != needed_fixtures) {
		string comp_name = ((comp_stats*)_this)->competition_db->ClubCompName;
		string msg = "Wrong number of fixtures in " + comp_name + ": created " + to_string(created_fixtures) + " but needed " + to_string(needed_fixtures);
		create_message_box("Error", msg.c_str(), true);
	}
}

vector<cm3_clubs*> get_relegated_teams(DWORD compID)
{
	vector<cm3_clubs*> relegated_clubs;
	comp_stats* league = (comp_stats*)get_loaded_league(compID);

	if (league)
	{
		WORD numberOfTeams = league->n_teams;
		team_league_stats* table = (team_league_stats*)league->team_league_table;

		for (int i = 0; i < numberOfTeams; i++)
		{
			if (table[i].league_fate == Relegated)
				relegated_clubs.push_back(table[i].club);
		}
	}
	else
		dprintf("Can't find relegated clubs at compID: %08X\n", compID);
	return relegated_clubs;
}

bool sortTLS(team_league_stats s1, team_league_stats s2)
{
	if (s1.points != s2.points) return s1.points > s2.points;
	int diff1 = s1.goals_for - s1.goals_against;
	int diff2 = s2.goals_for - s2.goals_against;
	if (diff1 != diff2) return diff1 > diff2;
	if (s1.goals_for != s2.goals_for) return s1.goals_for > s2.goals_for;
	if (s1.goals_against != s2.goals_against) return s1.goals_against < s2.goals_against;
	return s1.club->ClubReputation > s2.club->ClubReputation;
}

bool sortTeamSeeding(teams_seeded s1, teams_seeded s2)
{
	if (s1.f5 != s2.f5) return s1.f5 < s2.f5;
	return s1.club->ClubReputation > s2.club->ClubReputation;
}

vector<cm3_clubs*> weighted_reservoir_sampling(vector<cm3_clubs*> population, unsigned int sample_size) {
	unsigned int i = 0;
	vector<cm3_clubs*> reservoir;
	if (sample_size < 1) return reservoir;
	vector<double> keys;
	for (; i < sample_size; i++) {
		cm3_clubs* c = population[i];
		reservoir.push_back(c);
		keys.push_back(pow(((double)rand() / (RAND_MAX)), 1.0f / c->ClubReputation));
	}
	for (; i < population.size(); i++) {
		cm3_clubs* c = population[i];
		auto threshold = min_element(keys.begin(), keys.end());
		int member_idx = distance(begin(keys), threshold);
		double new_key = pow(((double)rand() / (RAND_MAX)), 1.0f / c->ClubReputation);
		if (new_key > *threshold) {
			keys[member_idx] = new_key;
			reservoir[member_idx] = c;
		}
	}
	return reservoir;
}

vector<cm3_clubs*> weighted_reservoir_sampling_invert_weights(vector<cm3_clubs*> population, unsigned int sample_size) {
	unsigned int i = 0;
	vector<cm3_clubs*> reservoir;
	if (sample_size < 1) return reservoir;
	vector<double> keys;
	for (; i < sample_size; i++) {
		cm3_clubs* c = population[i];
		reservoir.push_back(c);
		keys.push_back(pow(((double)rand() / (RAND_MAX)), 1.0f / (10000 - c->ClubReputation)));
	}
	for (; i < population.size(); i++) {
		cm3_clubs* c = population[i];
		auto threshold = min_element(keys.begin(), keys.end());
		int member_idx = distance(begin(keys), threshold);
		double new_key = pow(((double)rand() / (RAND_MAX)), 1.0f / (10000 - c->ClubReputation));
		if (new_key > *threshold) {
			keys[member_idx] = new_key;
			reservoir[member_idx] = c;
		}
	}
	return reservoir;
}

vector<cm3_clubs*> get_random_weighted_clubs(vector<cm3_clubs*> list, unsigned int amount, bool to_promote) {
	if (to_promote) return weighted_reservoir_sampling(list, amount);
	else return weighted_reservoir_sampling_invert_weights(list, amount);
}

void generic_prom_rel(DWORD nation_id, DWORD promote_from, DWORD relegate_from, int num_child_comps, ...) {
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(relegate_from);

	va_list valist;
	va_start(valist, num_child_comps);
	for (int i = 0; i < num_child_comps; i++)
	{
		DWORD comp_id = va_arg(valist, DWORD);
		vector<cm3_clubs*> relegated_clubs2 = get_relegated_teams(comp_id);
		move(relegated_clubs2.begin(), relegated_clubs2.end(), back_inserter(relegated_clubs));
	}
	va_end(valist);

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(promote_from, nation_id);
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size(), true);

	for (unsigned int j = 0; j < promoted_clubs.size(); j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];
		//dprintf("Swapping Teams: %s (%s) %d <-> %s (%s) %d\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, clubToRelegate->ClubReputation, clubToPromote->ClubName, clubToPromote->ClubDivision->ClubCompName, clubToPromote->ClubReputation);

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}
}

int UpdateCountryCoefficient(cm3_clubs* club, char coeff) {
	cm3_nations* nation = club->ClubNation;
	if (club->ClubID == CLUB_VADUZ_9CF() || club->ClubID == CLUB_ESCHEN_MAUREN_9CF() || club->ClubID == CLUB_BALZERS_9CF())
		nation = get_country(NATION_LIECHTENSTEIN_9CF());
	return sub_9058B0((BYTE*)*uefa_seeding_list, nation, coeff);
}