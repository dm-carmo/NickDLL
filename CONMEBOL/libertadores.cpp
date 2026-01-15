#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\Helper.h"
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <string>
#include "conmebol_helper.h"
#include "Structures\vtable.h"

using namespace std;

// https://champman0102.net/viewtopic.php?f=35&t=2756
// https://champman0102.net/viewtopic.php?p=87269#p87269
/*
Function to select 32 teams for Copa Libertadores
*/
// conmebol_liber == Copa Libertadores
/*
Last Libertadores winners
Last Sudamericana winners
5 teams from Argentina and Brazil (tries to get cup winners and losers if possible)
3 teams from Chile and Colombia
2 teams from Bolivia, Ecuador, Paraguay, Peru, Uruguay and Venezuela
*/


void ConmebolSeedingLeague(const char* szNation, int numberOfClubs)
{
	cm3_nations* nation = find_country(szNation);

	if (nation->NationLeagueSelected) {
		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro_playable(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubLastDivPos);
		int j = 0;
		for (int i = 0; i < numberOfClubs; i++)
		{
			cm3_clubs* club = nation_clubs[j++];

			if (club->ClubEuroFlag != -1) {
				//dprintf("Club %s is already in Libertadores, skipping\n", (club->ClubName));
				i--; // Else do again as the club selected was already picked
			}
			else {
				//dprintf("Setting club %s to Libertadores\n", (club->ClubName));
				club->ClubEuroFlag = *(DWORD*)0x9CF63C;
			}
		}
	}
	else {
		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubRep);

		int TeamsToSelectFrom = (nation_clubs.size() < 10) ? nation_clubs.size() : 10;

		if (TeamsToSelectFrom < numberOfClubs)
		{
			// If we can't get this countries clubs - then just get some more Argentina or Brazil ones
			ConmebolSeedingLeague(((rand() % 2) == 0) ? "Brazil" : "Argentina", numberOfClubs);
			return;
		}

		for (int i = 0; i < numberOfClubs; i++)
		{
			cm3_clubs* club = nation_clubs[rand() % TeamsToSelectFrom];
			if (club->ClubEuroFlag != -1) {
				//dprintf("Club %s is already in Libertadores, skipping\n", (club->ClubName));
				i--;  // Else do again as the club selected was already picked
			}
			else {
				//dprintf("Setting club %s to Libertadores\n", (club->ClubName));
				club->ClubEuroFlag = *(DWORD*)0x9CF63C;
			}
		}
	}
}

void ConmebolSeedingCompWinner(long comp_id)
{
	cm3_club_comps* comp = &(*club_comps)[comp_id];
	if (!comp) {
		//dprintf("Competition %ld not found, getting backup club\n", comp_id);
		ConmebolSeedingLeague("Brazil", 1);
	}
	else {
		cm3_clubs* last_winner = get_last_comp_winner(comp);
		if (!last_winner || !last_winner->ClubNation) {
			//dprintf("Last winner of %s not found or invalid, getting backup club\n", comp->ClubCompName);
			ConmebolSeedingLeague("Brazil", 1);
		}
		else {
			if (last_winner->ClubEuroFlag != -1) {
				//dprintf("Last winner of %s (%s) is already qualified, getting backup club\n", comp->ClubCompName, (last_winner->ClubName));
				ConmebolSeedingLeague(last_winner->ClubNation->NationName, 1);
			}
			else {
				//dprintf("Setting club %s to Libertadores (last winners of %s)\n", (last_winner->ClubName), comp->ClubCompName);
				last_winner->ClubEuroFlag = *(DWORD*)0x9CF63C;
			}
		}
	}
}

void ConmebolSeedingCupWinner(const char* szNation, long comp_id)
{
	cm3_nations* nation = find_country(szNation);

	if (nation->NationLeagueSelected) {
		cm3_club_comps* comp = &(*club_comps)[comp_id];
		if (!comp) {
			//dprintf("Competition %ld not found, getting backup club\n", comp_id);
			ConmebolSeedingLeague(szNation, 1);
		}
		else {
			cm3_clubs* last_winner = get_last_comp_winner(comp);
			if (!last_winner || !last_winner->ClubNation) {
				//dprintf("Last winner of %s not found or invalid, getting backup club\n", comp->ClubCompName);
				ConmebolSeedingLeague(szNation, 1);
			}
			else {
				if (last_winner->ClubEuroFlag != -1) {
					//dprintf("Last winner of %s (%s) is already qualified, getting backup club\n", comp->ClubCompName, (last_winner->ClubName));
					ConmebolSeedingLeague(szNation, 1);
				}
				else {
					//dprintf("Setting club %s to Libertadores (last winners of %s)\n", (last_winner->ClubName), comp->ClubCompName);
					last_winner->ClubEuroFlag = *(DWORD*)0x9CF63C;
				}
			}
		}
	}
	else {
		//dprintf("Country %s is inactive, getting backup club\n", szNation);
		ConmebolSeedingLeague(szNation, 1);
	}
}

void ConmebolSeedingCupLoser(const char* szNation, long comp_id)
{
	cm3_nations* nation = find_country(szNation);

	if (nation->NationLeagueSelected) {
		cm3_club_comps* comp = &(*club_comps)[comp_id];
		if (!comp) {
			//dprintf("Competition %ld not found, getting backup club\n", comp_id);
			ConmebolSeedingLeague(szNation, 1);
		}
		else {
			cm3_clubs* last_runner_up = get_last_comp_runner_up(comp);
			if (!last_runner_up || !last_runner_up->ClubNation) {
				//dprintf("Last runner-up of %s not found or invalid, getting backup club\n", comp->ClubCompName);
				ConmebolSeedingLeague(szNation, 1);
			}
			else {
				if (last_runner_up->ClubEuroFlag != -1) {
					//dprintf("Last runner-up of %s (%s) is already qualified, getting backup club\n", comp->ClubCompName, (last_runner_up->ClubName));
					ConmebolSeedingLeague(szNation, 1);
				}
				else {
					//dprintf("Setting club %s to Libertadores (last runner-up of %s)\n", (last_runner_up->ClubName), comp->ClubCompName);
					last_runner_up->ClubEuroFlag = *(DWORD*)0x9CF63C;
				}
			}
		}
	}
	else {
		//dprintf("Country %s is inactive, getting backup club\n", szNation);
		ConmebolSeedingLeague(szNation, 1);
	}
}

void replacement_004C6430_full()
{
	if (std::filesystem::exists("Data/conmebol.cfg") && *current_year == (WORD)2025) {
		//dprintf("Getting preset teams for Libertadores\n");
		ifstream in("Data/conmebol.cfg", ios_base::in);
		string name;
		char nation[LONG_TXT_LENGTH];
		int nation_count = -1;
		int required = -1;
		while (std::getline(in, name))
		{
			if (name.size() == 0) {
				if (nation_count >= 0 && nation_count < required) {
					//dprintf("Too few clubs from %s (need %d, only found %d), trying to add more\n", nation, required, nation_count);
					ConmebolSeedingLeague(nation, required - nation_count);
				}
				continue;
			}
			if (name[0] == '*') {
				strcpy_s(nation, name.substr(1).c_str());
				nation_count = 0;
				required = libertadores_qual.at(nation);
				continue;
			}
			if (nation_count >= required) continue;
			cm3_clubs* club = find_club(name.c_str());
			if (!club || !club->ClubNation) {
				//dprintf("Club %s not found, skipping\n", name.c_str());
			}
			else {
				//dprintf("Setting club %s to Libertadores\n", (club->ClubName));
				club->ClubEuroFlag = *(DWORD*)0x9CF63C;
				nation_count++;
			}
		}
		in.close();
	}
	else {
		//dprintf("Getting teams for Libertadores based on last season performance\n");
		ConmebolSeedingLeague("Argentina", libertadores_qual.at("Argentina") - 3); // minus cup slots and Libertadores winner slot
		ConmebolSeedingCupWinner("Argentina", *(DWORD*)0x9CF67C);
		ConmebolSeedingCupLoser("Argentina", *(DWORD*)0x9CF67C);
		ConmebolSeedingLeague("Brazil", libertadores_qual.at("Brazil") - 3); // minus cup slots and Sudamericana winner slot
		ConmebolSeedingCupWinner("Brazil", *(DWORD*)0x9CF9E8);
		ConmebolSeedingCupLoser("Brazil", *(DWORD*)0x9CF9E8);
		const char* nations_list[] = {
			"Bolivia", "Chile", "Colombia", "Ecuador", "Paraguay", "Peru", "Uruguay", "Venezuela"
		};
		for (const char* nation : nations_list) {
			ConmebolSeedingLeague(nation, libertadores_qual.at(nation));
		}
		ConmebolSeedingCompWinner(*(DWORD*)0x9CF63C);
		ConmebolSeedingCompWinner(*(DWORD*)0x9CF698);
	}
	//dprintf("\n");
}

extern "C" _declspec(naked) int replacement_004C6430()
{
	_asm
	{
		pushad
	}
	replacement_004C6430_full();
	_asm
	{
		popad
		ret 8
	}
}

void setup_libertadores()
{
	// Remap CONMEBOL seeding function to our function, as this controls which teams get picked for Libertadores
	DWORD func_addr = (DWORD)replacement_004C6430;
	WriteDWORD(0x004C625D + 1, func_addr - (0x004C625D + 5));
}
