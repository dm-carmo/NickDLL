#include "Helper.h"
#include <stdio.h>
#include <conio.h>
#include <algorithm>

char* szDebugFile = "";

Config configFile = Config();
std::default_random_engine rng = std::default_random_engine{};

void dprintf(const char* fmt, ...)
{
	char printString[1024];
	va_list argp;
	va_start(argp, fmt);
	vsprintf(printString, fmt, argp);
	va_end(argp);

	// OutputDebugString(printString);
	printf(printString);

	if (stricmp(szDebugFile, "") != 0)
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
	return getch();
}

cm3_nations* find_country(const char* szCountry)
{
	for (int i = 0; i < *nations_count; i++)
	{
		if (stricmp((*nations)[i].NationName, szCountry) == 0)
			return &(*nations)[i];
	}
	return NULL;
}

vector<cm3_nations*> central_america_countries()
{
	vector<cm3_nations*> ret;
	ret.clear();
	for (int i = 0; i < *nations_count; i++)
	{
		if (stricmp((*nations)[i].NationName, "Mexico") == 0  ||
			stricmp((*nations)[i].NationName, "United States") == 0 ||
			stricmp((*nations)[i].NationName, "Canada") == 0)
			continue;
		if ((*nations)[i].NationContinent != NULL && (*nations)[i].NationRegion == 7)
			ret.push_back(&(*nations)[i]);
	}
	return ret;
}

vector<cm3_nations*> caribbean_countries()
{
	vector<cm3_nations*> ret;
	ret.clear();
	for (int i = 0; i < *nations_count; i++)
	{
		if ((*nations)[i].NationContinent != NULL && (*nations)[i].NationRegion == 6)
			ret.push_back(&(*nations)[i]);
	}
	return ret;
}

cm3_clubs* find_club(const char* szClub)
{
	for (int i = 0; i < *clubs_count; i++)
	{
		if (stricmp((*clubs)[i].ClubName, szClub) == 0)
			return &(*clubs)[i];
	}
	return NULL;
}

vector<cm3_clubs*> find_clubs_of_country(DWORD nation_id)
{
	vector<cm3_clubs*> ret;
	for (int i = 0; i < *clubs_count; i++)
	{
		if ((*clubs)[i].ClubNation != NULL && (*clubs)[i].ClubNation->NationID == nation_id && (*clubs)[i].ClubDivision != 0)  // ClubDivision != 0 to stop us getting the national teams
		{
			cm3_clubs* club = &(*clubs)[i];

			//dprintf("Club Division: %s\n", (club->ClubDivision)->ClubCompName);

			// Don't add Lower Division Clubs
			//if (stricmp((char *)(club->ClubDivision+1), "A Lower Division") != 0)
			ret.push_back(club);
		}
	}
	return ret;
}

vector<cm3_clubs*> find_clubs_of_country_for_euro_playable(DWORD nation_id)
{
	vector<cm3_clubs*> ret;
	for (int i = 0; i < *clubs_count; i++)
	{
		if ((*clubs)[i].ClubNation != NULL && (*clubs)[i].ClubNation->NationID == nation_id && (*clubs)[i].ClubDivision != 0)  // ClubDivision != 0 to stop us getting the national teams
		{
			cm3_clubs* club = &(*clubs)[i];

			//dprintf("Club Division: %s\n", (club->ClubDivision)->ClubCompName);

			// Don't add Lower Division Clubs
			//if (stricmp((char *)(club->ClubDivision+1), "A Lower Division") != 0)
			if (club->ClubEuroFlag == -1 && club->ClubLastDivision)
				ret.push_back(club);
		}
	}
	return ret;
}

vector<cm3_clubs*> find_clubs_of_country_for_euro(DWORD nation_id)
{
	vector<cm3_clubs*> ret;
	for (int i = 0; i < *clubs_count; i++)
	{
		if ((*clubs)[i].ClubNation != NULL && (*clubs)[i].ClubNation->NationID == nation_id && (*clubs)[i].ClubDivision != 0)  // ClubDivision != 0 to stop us getting the national teams
		{
			cm3_clubs* club = &(*clubs)[i];

			//dprintf("Club Division: %s\n", (club->ClubDivision)->ClubCompName);

			if (club->ClubEuroFlag == -1)
				ret.push_back(club);
		}
	}
	return ret;
}

cm3_club_comps* find_club_comp(const char* szClubComp)
{
	for (int i = 0; i < *club_comps_count; i++)
	{
		if (stricmp((*club_comps)[i].ClubCompName, szClubComp) == 0)
			return &(*club_comps)[i];
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
		for (int i = 0; i < *club_comps_count; i++)
		{
			if ((*club_comps)[i].ClubCompNation == nation)
				ret.push_back(&(*club_comps)[i]);
		}
	}

	return ret;
}

bool vector_contains_club(vector<cm3_clubs*>& vec, cm3_clubs* club)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == club)
			return true;
	}
	return false;
}

bool compareClubRep(cm3_clubs* c1, cm3_clubs* c2)
{
	return (c1->ClubReputation > c2->ClubReputation);
}

bool compareClubLastDivPos(cm3_clubs* c1, cm3_clubs* c2)
{
	if (c1->ClubLastDivision->ClubCompReputation != c2->ClubLastDivision->ClubCompReputation)
		return (c1->ClubLastDivision->ClubCompReputation > c2->ClubLastDivision->ClubCompReputation);
	return (c1->ClubLastPosition > 0 && c1->ClubLastPosition < c2->ClubLastPosition);
}

cm3_clubs* get_last_comp_winner(cm3_club_comps* comp)
{
	vector<cm3_club_comp_history*> ret;
	for (int i = 0; i < *club_comp_histories_count; i++) {
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
	for (int i = 0; i < *club_comp_histories_count; i++) {
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

int CountNumberOfTeamsInComp(DWORD CompID)
{
	int numberOfLeagueTeams = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == CompID)
			numberOfLeagueTeams++;
	}
	return numberOfLeagueTeams;
}