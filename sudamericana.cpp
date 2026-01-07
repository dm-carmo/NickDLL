#include <windows.h>
#include "CMHeader.h"
#include "Helper.h"
#include <algorithm>
#include "sudamericana_expand.h"
#include <filesystem>
#include <fstream>
#include <string>
#include "conmebol_helper.h"

using namespace std;

// https://champman0102.net/viewtopic.php?f=35&t=2756
// https://champman0102.net/viewtopic.php?p=87269#p87269
/*
This function in NickDLL then selects randomly from the 20 best teams (based on reputation) from the countries in the following order.
4 each from Brazil and Argentina, 2 from Uruguay, Colombia, Chile and Paraguay. 1 from Bolivia, Peru, Ecuador and Venezuela.
(If it can not get the needed teams from any of the countries it just gets more from Brazil and Argentina)
*/
// conmebol_merc == Copa Sudamericana (old Mercosur)
/*
Argentina teams with last position from 6 to 9 and no last division
Brazil teams with last position from 6 to 9 and no last division
Uruguay teams with last position from 5 to 6 and no last division
Colombia teams with last position from 5 to 6 and no last division
Chile teams with last position from 3 to 4 and no last division
Paraguay teams with last position from 3 to 4 and no last division
One Bolivia team with last position 3 and no last division
One Peru team with last position 3 and no last division
One Ecuador team with last position 3 and no last division
One Venezuela team with last position 3 and no last division
*/

DWORD replacement_004C5906_ret;
int replacement_004C5906_counter = 0;
vector<cm3_clubs*> sudamericana_32_clubs;

void AddSudamericanaClubs(vector<cm3_clubs*>& vec, const char* szNation, int numberOfClubs)
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
				dprintf("Club %s is in Libertadores, skipping\n", (club->ClubName));
				i--;
			}
			else if (!vector_contains_club(vec, club)) {
				dprintf("Setting club %s to Sudamericana\n", (club->ClubName));
				vec.push_back(club);
			}
			else
				i--;	// Else do again as the club selected was already picked
		}
	}
	else {
		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubRep);

		int TeamsToSelectFrom = (nation_clubs.size() < 10) ? nation_clubs.size() : 10;

		if (TeamsToSelectFrom < numberOfClubs)
		{
			// If we can't get this countries clubs - then just get some more Argentina or Brazil ones
			AddSudamericanaClubs(vec, ((rand() % 2) == 0) ? "Brazil" : "Argentina", numberOfClubs);
			return;
		}

		for (int i = 0; i < numberOfClubs; i++)
		{
			cm3_clubs* club = nation_clubs[rand() % TeamsToSelectFrom];

			if (club->ClubEuroFlag != -1) {
				dprintf("Club %s is in Libertadores, skipping\n", (club->ClubName));
				i--;
			}
			else if (!vector_contains_club(vec, club)) {
				dprintf("Setting club %s to Sudamericana\n", (club->ClubName));
				vec.push_back(club);
			}
			else
				i--;	// Else do again as the club selected was already picked
		}
	}
}

DWORD replacement_004C5906_full()
{
	if (replacement_004C5906_counter == 0)
	{
		sudamericana_32_clubs.clear();
		if (std::filesystem::exists("Data/conmebol.cfg") && *current_year == (WORD)2025) {
			dprintf("Getting preset teams for Sudamericana\n");
			ifstream in("Data/conmebol.cfg", ios_base::in);
			string name;
			char nation[LONG_TXT_LENGTH];
			int nation_count = -1;
			int required = -1;
			while (std::getline(in, name))
			{
				if (name.size() == 0) {
					if (nation_count >= 0 && nation_count < required) {
						dprintf("Too few clubs from %s (need %d, only found %d), trying to add more\n", nation, required, nation_count);
						AddSudamericanaClubs(sudamericana_32_clubs, nation, required - nation_count);
					}
					continue;
				}
				if (name[0] == '*') {
					strcpy_s(nation, name.substr(1).c_str());
					nation_count = 0;
					required = sudamericana_qual.at(nation);
					continue;
				}
				if (nation_count >= required) continue;
				cm3_clubs* club = find_club(name.c_str());
				if (!club || !club->ClubNation) {
					dprintf("Club %s not found, skipping\n", name);
				}
				else if (club->ClubEuroFlag != -1) {
					dprintf("Club %s is in Libertadores, skipping\n", (club->ClubName));
				}
				else {
					dprintf("Setting club %s to Sudamericana\n", (club->ClubName));
					sudamericana_32_clubs.push_back(club);
					nation_count++;
				}
			}
			in.close();
		}
		else {
			const char* nations_list[] = {
				"Argentina", "Brazil", "Bolivia", "Chile", "Colombia", "Ecuador", "Paraguay", "Peru", "Uruguay", "Venezuela"
			};
			for (const char* nation : nations_list) {
				AddSudamericanaClubs(sudamericana_32_clubs, nation, sudamericana_qual.at(nation));
			}
		}
		dprintf("\n");
	}

	if (replacement_004C5906_counter == 32)
	{
		replacement_004C5906_counter = 0;
		return 0;
	}
	return (DWORD)sudamericana_32_clubs[replacement_004C5906_counter++];
}


extern "C" _declspec(naked) int replacement_004C5906()
{
	_asm
	{
		pushad
	}
	replacement_004C5906_ret = replacement_004C5906_full();
	_asm
	{
		popad
		mov eax, [replacement_004C5906_ret]
		ret 4
	}
}

void setup_sudamericana()
{
	// 004C5906  |.  E8 850F0000              |CALL 004C6890                           ; \cm0102.004C6890
	// Remap function to our function
	DWORD func_addr = (DWORD)replacement_004C5906;
	WriteDWORD(0x004C5906 + 1, func_addr - (0x004C5906 + 5));

	// Change calling function to use our return value
	//004C5919      89348A                    MOV DWORD PTR DS:[ECX*4+EDX],ESI   <--- ESI to EAX
	WriteBytes(0x004C5919 + 1, 1, 4);

	// 004C590D     /74 28                     JZ SHORT 004C5937  <--- This jump changed so if 0 is returned, finish the loop
	WriteBytes(0x004C590D + 1, 1, 0x28);

	setup_sudamericana_expand();
}
