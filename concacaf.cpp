#include <windows.h>
#include "CMHeader.h"
#include "Helper.h"
#include <algorithm>
#include "concacaf.h"
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;

static int(*sub_944E46)() = (int(*)())(0x944E46);
static int(*sub_944CFF)() = (int(*)())(0x944CFF);
static int(*sub_90D130)() = (int(*)())(0x90D130);
static int(*sub_944C9F)() = (int(*)())(0x944C9F);
static int(*sub_5E8290)() = (int(*)())(0x5E8290);
static int(*sub_521E60)() = (int(*)())(0x521E60);
static int(*sub_521EB0)() = (int(*)())(0x521EB0);
static int(*sub_521F10)() = (int(*)())(0x521F10);

extern "C" void sub_4C0F00();
extern "C" void __declspec(naked) sub_4C0F00()
{
	__asm
	{
		mov al, byte ptr ss : [esp + 0x4]
		sub esp, 0x200
		cmp al, 0xFF
		push ebx
		push esi
		push edi
		mov edi, ecx
		jne end_fixtures
		mov eax, dword ptr ss : [esp + 0x21C]
		xor ebx, ebx
		cmp eax, ebx
		je eax_null
		mov dword ptr ds : [eax] , ebx
		eax_null :
		mov eax, dword ptr ss : [esp + 0x214]
			mov ecx, dword ptr ss : [esp + 0x218]
			push 0x208
			mov word ptr ds : [eax] , 0x5
			mov word ptr ds : [ecx] , bx
			call sub_944E46		/*call cm0102.944E46*/
			mov esi, eax
			add esp, 0x4
			cmp esi, ebx
			jne fixtures_no_error
			lea edx, dword ptr ss : [esp + 0xC]
			lea eax, dword ptr ss : [esp + 0x10C]
			push edx
			push eax
			push ebx
			push ebx
			push 0x9A7D30		/*push cm0102.9A7D30*/
			call sub_944CFF		/*call cm0102.944CFF*/
			add esp, 0x14
			lea ecx, dword ptr ss : [esp + 0xC]
			lea edx, dword ptr ss : [esp + 0x10C]
			push 0x97
			push ecx
			push edx
			call sub_90D130		/*call cm0102.90D130*/
			push eax
			push 0x9870E8		/*push cm0102.9870E8*/
			push 0xAE24D0		/*push cm0102.AE24D0*/
			call sub_944C9F		/*call cm0102.944C9F*/
			push ebx
			push 0xAE24D0		/*push cm0102.AE24D0*/
			push 0x9870E0		/*push cm0102.9870E0*/
			call sub_5E8290		/*call cm0102.5E8290*/
			add esp, 0x24
			mov dword ptr ds : [0xB67A34] , ebx
			end_fixtures :
		pop edi
			pop esi
			xor eax, eax
			pop ebx
			add esp, 0x200
			ret 0x10
			fixtures_no_error:
		movsx eax, word ptr ds : [edi + 0x40]
			push eax
			push 0x2
			push ebx
			push 0x0
			push 0x0e
			push ebx
			push esi
			call sub_521E60		/*call cm0102.521E60*/
			movsx ecx, word ptr ds : [edi + 0x40]
			push ebx
			push ecx
			push 0x2
			push 0x2
			push ebx
			push 0x1
			push 0x5
			push ebx
			push esi
			call sub_521EB0		/*call cm0102.521EB0*/
			add esp, 0x40
			mov word ptr ds : [esi + 0x7] , 0xa
			mov word ptr ds : [esi + 0x9] , bx
			mov word ptr ds : [esi + 0xB] , bx
			mov word ptr ds : [esi + 0xD] , bx
			mov word ptr ds : [esi + 0xF] , 0x3
			mov byte ptr ds : [esi + 0x17] , 0x8
			mov word ptr ds : [esi + 0x18] , 0x16
			mov word ptr ds : [esi + 0x1A] , 0xb
			mov word ptr ds : [esi + 0x1C] , 0x16
			mov word ptr ds : [esi + 0x1E] , bx
			mov byte ptr ds : [esi + 0x20] , bl
			mov byte ptr ds : [esi + 0x21] , 0x2
			mov byte ptr ds : [esi + 0x22] , 0xe
			mov dword ptr ds : [esi + 0x5C] , ebx
			mov dword ptr ds : [esi + 0x60] , 0x2
			mov dword ptr ds : [esi + 0x64] , 0xe
			movsx edx, word ptr ds : [edi + 0x40]
			push edx
			push 0x3
			push ebx
			push 0x1
			push 0x1b
			push 0x1
			push esi
			call sub_521E60		/*call cm0102.521E60*/
			movsx eax, word ptr ds : [edi + 0x40]
			push ebx
			push eax
			push 0x2
			push 0x2
			push ebx
			push 0x2
			push 0x5
			push 0x1
			push esi
			call sub_521EB0		/*call cm0102.521EB0*/
			add esp, 0x40
			mov word ptr ds : [esi + 0x6F] , 0x6e
			mov word ptr ds : [esi + 0x71] , 0x1
			mov word ptr ds : [esi + 0x73] , bx
			mov word ptr ds : [esi + 0x75] , bx
			mov word ptr ds : [esi + 0x77] , 0x3
			mov byte ptr ds : [esi + 0x7F] , 0x8
			mov word ptr ds : [esi + 0x80] , 0x10
			mov word ptr ds : [esi + 0x82] , 0x8
			mov word ptr ds : [esi + 0x84] , 0x5
			mov word ptr ds : [esi + 0x86] , 0x16
			mov byte ptr ds : [esi + 0x88] , bl
			mov byte ptr ds : [esi + 0x89] , 0x2
			mov byte ptr ds : [esi + 0x8A] , 0x7
			mov dword ptr ds : [esi + 0xC4] , ebx
			mov dword ptr ds : [esi + 0xC8] , 0xFFFFFFFF
			mov dword ptr ds : [esi + 0xCC] , ebx
			movsx ecx, word ptr ds : [edi + 0x40]
			push ecx
			push 0x3
			push ebx
			push 0x2
			push 0x0d
			push 0x2
			push esi
			call sub_521E60		/*call cm0102.521E60*/
			movsx edx, word ptr ds : [edi + 0x40]
			push ebx
			push edx
			push 0x2
			push 0x2
			push ebx
			push 0x3
			push 0x2
			push 0x2
			push esi
			call sub_521EB0		/*call cm0102.521EB0*/
			add esp, 0x40
			mov word ptr ds : [esi + 0xD7] , 0x78
			mov word ptr ds : [esi + 0xD9] , 0x2
			mov word ptr ds : [esi + 0xDB] , 0x2
			mov word ptr ds : [esi + 0xDD] , bx
			mov word ptr ds : [esi + 0xDF] , 0x3
			mov byte ptr ds : [esi + 0xE7] , 0x8
			mov word ptr ds : [esi + 0xE8] , 0x8
			mov word ptr ds : [esi + 0xEA] , 0x4
			mov word ptr ds : [esi + 0xEC] , bx
			mov word ptr ds : [esi + 0xEE] , bx
			mov byte ptr ds : [esi + 0xF0] , bl
			mov byte ptr ds : [esi + 0xF1] , 0x2
			mov byte ptr ds : [esi + 0xF2] , 0x7
			mov dword ptr ds : [esi + 0x12C] , ebx
			mov dword ptr ds : [esi + 0x130] , 0xFFFFFFFF
			mov dword ptr ds : [esi + 0x134] , ebx
			movsx ecx, word ptr ds : [edi + 0x40]
			push ecx
			push 0x3
			push ebx
			push 0x3
			push 0x9
			push 0x3
			push esi
			call sub_521E60		/*call cm0102.521E60*/
			movsx edx, word ptr ds : [edi + 0x40]
			push ebx
			push edx
			push 0x2
			push 0x2
			push ebx
			push 0x3
			push 0x17
			push 0x3
			push esi
			call sub_521EB0		/*call cm0102.521EB0*/
			add esp, 0x40
			mov word ptr ds : [esi + 0x13F] , 0x82
			mov word ptr ds : [esi + 0x141] , 0x3
			mov word ptr ds : [esi + 0x143] , 0x2
			mov word ptr ds : [esi + 0x145] , bx
			mov word ptr ds : [esi + 0x147] , 0x3
			mov byte ptr ds : [esi + 0x14F] , 0x8
			mov word ptr ds : [esi + 0x150] , 0x4
			mov word ptr ds : [esi + 0x152] , 0x2
			mov word ptr ds : [esi + 0x154] , bx
			mov word ptr ds : [esi + 0x156] , bx
			mov byte ptr ds : [esi + 0x158] , bl
			mov byte ptr ds : [esi + 0x159] , 0x2
			mov byte ptr ds : [esi + 0x15A] , 0x7
			mov dword ptr ds : [esi + 0x194] , ebx
			mov dword ptr ds : [esi + 0x198] , 0xFFFFFFFF
			mov dword ptr ds : [esi + 0x19C] , ebx
			movsx ecx, word ptr ds : [edi + 0x40]
			push ecx
			push 0x3
			push ebx
			push 0x4
			push 0x1
			push 0x4
			push esi
			call sub_521E60		/*call cm0102.521E60*/
			movsx edx, word ptr ds : [edi + 0x40]
			push 0x4
			push edx
			push 0x1
			push 0x6
			push ebx
			push 0x5
			push 0x1
			push 0x4
			push esi
			call sub_521EB0		/*call cm0102.521EB0*/
			add esp, 0x40
			mov word ptr ds : [esi + 0x1A7] , 0x96
			mov word ptr ds : [esi + 0x1A9] , 0x4
			mov word ptr ds : [esi + 0x1AB] , bx
			mov word ptr ds : [esi + 0x1AD] , 0x3
			mov word ptr ds : [esi + 0x1AF] , bx
			mov byte ptr ds : [esi + 0x1B7] , 0x8
			mov word ptr ds : [esi + 0x1B8] , 0x2
			mov word ptr ds : [esi + 0x1BA] , 0x1
			mov word ptr ds : [esi + 0x1BC] , bx
			mov word ptr ds : [esi + 0x1BE] , bx
			mov byte ptr ds : [esi + 0x1C0] , bl
			mov byte ptr ds : [esi + 0x1C1] , 0x1
			mov byte ptr ds : [esi + 0x1C2] , bl
			mov dword ptr ds : [esi + 0x1FC] , ebx
			mov dword ptr ds : [esi + 0x200] , 0xFFFFFFFF
			mov dword ptr ds : [esi + 0x204] , ebx
			mov eax, esi
			pop edi
			pop esi
			pop ebx
			add esp, 0x200
			ret 0x10
	}
}

void AddConcacafClubs(vector<cm3_clubs*>& vec, const char* szNation, int numberOfClubs)
{
	cm3_nations* nation = find_country(szNation);

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
	else {
		vector<cm3_clubs*> nation_clubs = find_clubs_of_country_for_euro(nation->NationID);
		sort(nation_clubs.begin(), nation_clubs.end(), compareClubRep);

		int TeamsToSelectFrom = (nation_clubs.size() < 10) ? nation_clubs.size() : 10;

		if (TeamsToSelectFrom < numberOfClubs)
		{
			// If we can't get this countries clubs - then just get some more USA or Mexico ones
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

void AddCentralAmericaClubs(vector<cm3_clubs*>& vec, int numberOfCountries, int clubsPerCountry = 1)
{
	vector<cm3_nations*> nations = central_america_countries();
	int sz = nations.size();
	sort(nations.begin(), nations.end(), [](const cm3_nations* n1, const cm3_nations* n2) {
		return n1->NationReputation < n2->NationReputation;
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

void AddCaribbeanClubs(vector<cm3_clubs*>& vec, int numberOfCountries, int clubsPerCountry = 1)
{
	vector<cm3_nations*> nations = caribbean_countries();
	int sz = nations.size();
	sort(nations.begin(), nations.end(), [](const cm3_nations* n1, const cm3_nations* n2) {
		return n1->NationReputation < n2->NationReputation;
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

void ConcacafGetCupWinner(vector<cm3_clubs*>& vec, const char* szNation, long comp_id, bool loser_backup = true)
{
	cm3_nations* nation = find_country(szNation);

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
	else {
		dprintf("Country %s is inactive, getting backup club\n", szNation);
		AddConcacafClubs(vec, szNation, 1);
	}
}

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

void replacement_4c11a0_full() {
	long concacaf_champs_cup_id = *(DWORD*)0x9CF72C;
	comp_stats* comp_data = (comp_stats*)(*comp_stats_list)[concacaf_champs_cup_id];
	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	comp_data->n_teams = 27;
	vector<cm3_clubs*> concacaf_clubs;
	concacaf_clubs.clear();

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
				dprintf("Club %s not found, getting backup from %s\n", name, nation);
				AddConcacafClubs(concacaf_clubs, nation, 1);
			}
			else {
				dprintf("Setting club %s to CONCACAF Champions Cup\n", (club->ClubName));
				concacaf_clubs.push_back(club);
			}
		}
		in.close();

		for (int i = 0; i < 27; i++) {
			teams[i].club = concacaf_clubs[i];
			teams[i].club->ClubEuroFlag = -1;
		}
	}
	else {
		dprintf("Getting teams for CONCACAF based on last season performance\n");
		int rnd = rand() % 2;
		vector<cm3_clubs*> concacaf_clubs_bye;
		concacaf_clubs_bye.clear();

		ConcacafGetCupWinner(concacaf_clubs_bye, "United States", *(DWORD*)0x9CF590, false); // USA champions
		ConcacafGetCupLoser(concacaf_clubs_bye, "United States", *(DWORD*)0x9CF590); // USA runner-up
		ConcacafGetCupWinner(concacaf_clubs_bye, "United States", *(DWORD*)0x9CF728, true); // USA cup winner
		AddConcacafClubs(concacaf_clubs_bye, "United States", 1); // Leagues Cup
		AddConcacafClubs(concacaf_clubs, "United States", 3); // USA
		AddConcacafClubs(concacaf_clubs, "United States", 1); // Leagues Cup
		AddConcacafClubs(concacaf_clubs_bye, "Mexico", 1); // Mexico champions
		AddConcacafClubs(concacaf_clubs, "Mexico", 1); // Leagues Cup
		AddConcacafClubs(concacaf_clubs, "Mexico", 5); // Mexico
		AddConcacafClubs(concacaf_clubs, "Canada", 3); // Canada
		AddConcacafClubs(concacaf_clubs_bye, "Costa Rica", 1); // Central America
		AddCentralAmericaClubs(concacaf_clubs, 5, 1); // Central America
		AddCaribbeanClubs(concacaf_clubs, 3, 1); // Caribbean

		int i;
		for (i = 0; i < concacaf_clubs.size(); i++) {
			teams[i].club = concacaf_clubs[i];
			teams[i].club->ClubEuroFlag = -1;
		}
		for (int j = 0; j < concacaf_clubs_bye.size(); j++) {
			teams[i].club = concacaf_clubs_bye[j];
			teams[i].club->ClubEuroFlag = -1;
			i++;
		}
		/*
		AddConcacafClubs(concacaf_clubs_bye, "Jamaica", 1); // Caribbean
		AddConcacafClubs(concacaf_clubs, "Dominican Republic", 1); // Caribbean
		AddConcacafClubs(concacaf_clubs, "Haiti", 1); // Caribbean
		AddConcacafClubs(concacaf_clubs, "Nicaragua", 1); // Central America
		AddConcacafClubs(concacaf_clubs, "Guatemala", 1); // Central America
		AddConcacafClubs(concacaf_clubs, "Costa Rica", 2); // Central America
		AddConcacafClubs(concacaf_clubs, "Honduras", 1); // Central America
		*/
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

void setup_concacaf()
{
	PatchFunction(0x4c11a0, (DWORD)&replacement_4c11a0);

	WriteBytes(0x4c0cc3, 1, 0x1b);
	WriteBytes(0x4c0cc8, 1, 0x1b);

	WriteBytes(0x4c11b3, 1, 0x1b);

	//WriteBytes(0x4c0f35, 2, 0xa0, 0x1);
	//WriteBytes(0x4c0f3d, 1, 0x4);
	PatchFunction(0x4C0F00, (DWORD)&sub_4C0F00);
	WriteBytes(0x8318b1, 3, 0x6a, 0x0, 0x53);
	WriteBytes(0x667588, 1, 0x1);
}
