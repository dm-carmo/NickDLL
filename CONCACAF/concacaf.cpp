#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\Helper.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
#include "Helpers\constants.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"

using namespace std;

DWORD* concacaf_cup_vtable = (DWORD*)0x968AA0;

DWORD CreateConcacafCupFixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = *(WORD*)(_this + 0x40);
		*num_rounds = 5;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 1, 14), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 2, 5), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 2, 22, 11, 22, 0, 0, 2, 14);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 2, 27), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 3, 5), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, EleventhRound, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 2, 16, 8, 5, 22, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 3, 13), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 2), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 2, 8, 4, 0, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 4, 10), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 4, 23), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 2, 4, 2, 0, 0, 0, 2, 7);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 1), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 1), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 0, 2, 1, 0, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	return 0;
}

// Function that will add numbereOfClubs from szNation to vec
void AddConcacafClubs(vector<cm3_clubs*>& vec, const char* szNation, int numberOfClubs)
{
	cm3_nations* nation = find_country(szNation);

	// If nation has any active leagues, sort clubs by last division & position and pick top clubs from the list
	// May redo at a later point to better check if we're getting clubs from the top division, currently assumes top division has the highest reputation
	if (nation->NationLeagueSelected) {
		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro_playable(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubLastDivPos);
		int j = 0;
		for (int i = 0; i < numberOfClubs; i++)
		{
			cm3_clubs* club = nation_clubs[j++];

			if (club->ClubEuroFlag == -1) {
				dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				vec.push_back(club);
				club->ClubEuroFlag = 1;
			}
			else
				i--;	// Else do again as the club selected was already picked
		}
	}
	// If country is not playable, pick random clubs from the top 10 by reputation
	else {
		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubRep);

		int TeamsToSelectFrom = (nation_clubs.size() < 10) ? nation_clubs.size() : 10;

		if (TeamsToSelectFrom < numberOfClubs)
		{
			// If we can't get this country's clubs - then just get some more USA or Mexico ones
			AddConcacafClubs(vec, ((rand() % 2) == 0) ? "United States" : "Mexico", numberOfClubs);
			return;
		}

		for (int i = 0; i < numberOfClubs; i++)
		{
			cm3_clubs* club = nation_clubs[rand() % TeamsToSelectFrom];

			if (club->ClubEuroFlag == -1) {
				dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				vec.push_back(club);
				club->ClubEuroFlag = 1;
			}
			else
				i--;	// Else do again as the club selected was already picked
		}
	}
}

// Similar to AddConcacafClubs, but gets random Central American clubs
void AddCentralAmericaClubs(vector<cm3_clubs*>& vec, int numberOfCountries, int clubsPerCountry = 1)
{
	vector<cm3_nations*> nations = central_america_countries();
	int sz = nations.size();
	sort(nations.begin(), nations.end(), [](const cm3_nations* n1, const cm3_nations* n2) {
		return n1->NationReputation > n2->NationReputation;
		});

	int CountriesToSelectFrom = (sz < 8) ? sz : 8;
	for (int i = 0; i < numberOfCountries; i++) {
		cm3_nations* nation = nations[rand() % CountriesToSelectFrom];
		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubRep);

		int TeamsToSelectFrom = (nation_clubs.size() < 10) ? nation_clubs.size() : 10;

		if (TeamsToSelectFrom < clubsPerCountry)
		{
			// If we can't get this countries clubs - then just get some more USA or Mexico ones
			AddConcacafClubs(vec, ((rand() % 2) == 0) ? "United States" : "Mexico", clubsPerCountry);
			return;
		}

		for (int j = 0; j < clubsPerCountry; j++)
		{
			cm3_clubs* club = nation_clubs[rand() % TeamsToSelectFrom];

			if (club->ClubEuroFlag == -1) {
				dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				vec.push_back(club);
				club->ClubEuroFlag = 1;
			}
			else
				j--;	// Else do again as the club selected was already picked
		}
	}
}

// Similar to AddConcacafClubs, but gets random Caribbean clubs
void AddCaribbeanClubs(vector<cm3_clubs*>& vec, int numberOfCountries, int clubsPerCountry = 1)
{
	vector<cm3_nations*> nations = caribbean_countries();
	int sz = nations.size();
	sort(nations.begin(), nations.end(), [](const cm3_nations* n1, const cm3_nations* n2) {
		return n1->NationReputation > n2->NationReputation;
		});

	int CountriesToSelectFrom = (sz < 6) ? sz : 6;
	for (int i = 0; i < numberOfCountries; i++) {
		cm3_nations* nation = nations[rand() % CountriesToSelectFrom];

		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubRep);

		int TeamsToSelectFrom = (nation_clubs.size() < 10) ? nation_clubs.size() : 10;

		if (TeamsToSelectFrom < clubsPerCountry)
		{
			// If we can't get this countries clubs - then just get some more USA or Mexico ones
			AddConcacafClubs(vec, ((rand() % 2) == 0) ? "United States" : "Mexico", clubsPerCountry);
			return;
		}

		for (int j = 0; j < clubsPerCountry; j++)
		{
			cm3_clubs* club = nation_clubs[rand() % TeamsToSelectFrom];

			if (club->ClubEuroFlag == -1) {
				dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				vec.push_back(club);
				club->ClubEuroFlag = 1;
			}
			else
				j--;	// Else do again as the club selected was already picked
		}
	}
}

// Similar to ConcacafGetCupWinner, but will search for the runner-up instead
void ConcacafGetCupLoser(vector<cm3_clubs*>& vec, const char* szNation, long comp_id)
{
	cm3_nations* nation = find_country(szNation);

	if (nation->NationLeagueSelected) {
		cm3_club_comps* comp = &(*club_comps)[comp_id];
		if (!comp) {
			dprintf("Competition %ld not found, getting backup club\n", comp_id);
			AddConcacafClubs(vec, szNation, 1);
		}
		else {
			cm3_clubs* last_runner_up = get_last_comp_runner_up(comp);
			if (!last_runner_up || !last_runner_up->ClubNation) {
				dprintf("Last runner-up of %s not found or invalid, getting backup club\n", comp->ClubCompName);
				AddConcacafClubs(vec, szNation, 1);
			}
			else {
				if (last_runner_up->ClubEuroFlag != -1) {
					dprintf("Last runner-up of %s (%s) is already qualified, getting backup club\n", comp->ClubCompName, (last_runner_up->ClubName));
					AddConcacafClubs(vec, szNation, 1);
				}
				else {
					dprintf("Setting club %s to CONCACAF Champions Cup (last runner-up of %s)\n", (last_runner_up->ClubName), comp->ClubCompName);
					vec.push_back(last_runner_up);
					last_runner_up->ClubEuroFlag = 1;
				}
			}
		}
	}
	else {
		dprintf("Country %s is inactive, getting backup club\n", szNation);
		AddConcacafClubs(vec, szNation, 1);
	}
}

// Tries to find the latest cup winner from comp_id to add to the competition
// szNation is provided as a backup in case the competition can't be found, or there is no available club in the history
// loser_backup decides if the cup loser can be used when the winner has already been qualified, or if the place should go to the best available club in the league instead
void ConcacafGetCupWinner(vector<cm3_clubs*>& vec, const char* szNation, long comp_id, bool loser_backup = true)
{
	cm3_nations* nation = find_country(szNation);

	// Only search for history if the nation has active competitions, otherwise it will always use the same club
	// May redo at a later point to check if the actual competition is active instead
	if (nation->NationLeagueSelected) {
		cm3_club_comps* comp = &(*club_comps)[comp_id];
		if (!comp) {
			dprintf("Competition %ld not found, getting backup club\n", comp_id);
			AddConcacafClubs(vec, szNation, 1);
		}
		else {
			cm3_clubs* last_winner = get_last_comp_winner(comp);
			if (!last_winner || !last_winner->ClubNation) {
				dprintf("Last winner of %s not found or invalid, getting backup club\n", comp->ClubCompName);
				AddConcacafClubs(vec, szNation, 1);
			}
			else {
				if (last_winner->ClubEuroFlag != -1) {
					dprintf("Last winner of %s (%s) is already qualified, getting backup club\n", comp->ClubCompName, (last_winner->ClubName));
					if (loser_backup) ConcacafGetCupLoser(vec, szNation, comp_id);
					else AddConcacafClubs(vec, szNation, 1);
				}
				else {
					dprintf("Setting club %s to CONCACAF Champions Cup (last winners of %s)\n", (last_winner->ClubName), comp->ClubCompName);
					vec.push_back(last_winner);
					last_winner->ClubEuroFlag = 1;
				}
			}
		}
	}
	// If nation has no active competitions, get a random top club instead
	else {
		dprintf("Country %s is inactive, getting backup club\n", szNation);
		AddConcacafClubs(vec, szNation, 1);
	}
}

// Full replacement for the function that gets the teams for the competition
void replacement_4c11a0_full() {
	long concacaf_champs_cup_id = *(DWORD*)0x9CF72C;
	comp_stats* comp_data = (comp_stats*)(*comp_stats_list)[concacaf_champs_cup_id];
	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	comp_data->n_teams = 27;
	vector<cm3_clubs*> concacaf_clubs;
	concacaf_clubs.clear();

	// If there is a .cfg file, uses it to get preset teams for the first year
	// Includes failsafes in case any of the clubs can't be found or are already qualified for some reason
	if (std::filesystem::exists("Data/concacaf.cfg") && *current_year == (WORD)2025) {
		dprintf("Getting preset teams for CONCACAF\n");
		ifstream in("Data/concacaf.cfg", ios_base::in);
		string name;
		char nation[LONG_TXT_LENGTH];
		while (std::getline(in, name))
		{
			if (name.size() == 0) {
				continue;
			}
			if (name[0] == '*') {
				strcpy_s(nation, name.substr(1).c_str());
				continue;
			}
			cm3_clubs* club = find_club(name.c_str());
			if (!club || !club->ClubNation) {
				dprintf("Club %s not found, getting backup from %s\n", name.c_str(), nation);
				AddConcacafClubs(concacaf_clubs, nation, 1);
			}
			else if (club->ClubEuroFlag != -1) {
				dprintf("Club %s already qualified, getting backup from %s\n", name.c_str(), nation);
				AddConcacafClubs(concacaf_clubs, nation, 1);
			}
			else {
				dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				concacaf_clubs.push_back(club);
				club->ClubEuroFlag = 1;
			}
		}
		in.close();

		for (int i = 0; i < 27; i++) {
			teams[i].club = concacaf_clubs[i];
			teams[i].club->ClubEuroFlag = -1;
		}
	}
	// After the first year, or if there is no .cfg, gets teams based on last league positions, or random top clubs depending on the case
	else {
		dprintf("Getting teams for CONCACAF based on last season performance\n");
		int rnd = rand() % 2;
		// Second vector to store 5 teams that will start in the second round
		vector<cm3_clubs*> concacaf_clubs_bye;
		concacaf_clubs_bye.clear();

		// Since the MLS has playoffs to decide the winner, I used the functions to get cup winners/losers first
		ConcacafGetCupWinner(concacaf_clubs_bye, "United States", *(DWORD*)0x9CF590, false); // USA champions
		ConcacafGetCupLoser(concacaf_clubs, "United States", *(DWORD*)0x9CF590); // USA runner-up
		ConcacafGetCupWinner(concacaf_clubs, "United States", *(DWORD*)0x9CF728, true); // USA cup winner
		AddConcacafClubs(concacaf_clubs_bye, "United States", 1); // Leagues Cup
		AddConcacafClubs(concacaf_clubs, "United States", 3); // USA
		AddConcacafClubs(concacaf_clubs, "United States", 1); // Leagues Cup
		AddConcacafClubs(concacaf_clubs_bye, "Mexico", 1); // Mexico champions
		AddConcacafClubs(concacaf_clubs, "Mexico", 1); // Leagues Cup
		AddConcacafClubs(concacaf_clubs, "Mexico", 5); // Mexico
		AddConcacafClubs(concacaf_clubs, "Canada", 3); // Canada
		AddCentralAmericaClubs(concacaf_clubs_bye, 1, 1); // Central America winner
		AddCentralAmericaClubs(concacaf_clubs, 5, 1); // Central America
		AddCaribbeanClubs(concacaf_clubs_bye, 1, 1); // Caribbean winner
		AddCaribbeanClubs(concacaf_clubs, 2, 1); // Caribbean

		DWORD i;
		for (i = 0; i < concacaf_clubs.size(); i++) {
			teams[i].club = concacaf_clubs[i];
			teams[i].club->ClubEuroFlag = -1;
		}
		for (DWORD j = 0; j < concacaf_clubs_bye.size(); j++) {
			teams[i].club = concacaf_clubs_bye[j];
			teams[i].club->ClubEuroFlag = -1;
			i++;
		}
	}
	dprintf("\n");
}


extern "C" _declspec(naked) int replacement_4c11a0()
{
	_asm
	{
		pushad
	}
	replacement_4c11a0_full();
	_asm
	{
		popad
		mov eax, 1
		ret
	}
}

void __declspec(naked) concacaf_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call CreateConcacafCupFixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_concacaf()
{
	PatchFunction(0x4c11a0, (DWORD)&replacement_4c11a0);

	WriteBytes(0x4c0cc3, 1, 0x1b);
	WriteBytes(0x4c0cc8, 1, 0x1b);

	WriteBytes(0x4c11b3, 1, 0x1b);

	WriteVTablePtr(concacaf_cup_vtable, VTableFixtures, (DWORD)&concacaf_fixture_caller);
	WriteBytes(0x8318b1, 3, 0x6a, 0x0, 0x53);
	WriteBytes(0x667588, 1, 0x1);
}
