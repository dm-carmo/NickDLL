#include <windows.h>
#include <filesystem>
#include <fstream>
#include <map>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

using namespace std;

DWORD* conmebol_libertadores_vtable = (DWORD*)0x968BF4;

// prize money for group stage win/draw and coefficient updates
int liber_583B10(BYTE* _this, BYTE* a2, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;
	char al, bl, cl;
	cm3_clubs* club_check = 0;
	al = *(char*)(a2 + 0x47);
	bl = *(char*)(a2 + 0x42);
	if (al == -1) {
		al = *(char*)(a2 + 0x43);
		cl = *(char*)(a2 + 0x44);
	}
	else cl = *(char*)(a2 + 0x48);
	if (al > cl) {
		club_check = (cm3_clubs*)*(DWORD*)(a2 + 0x1c);
	}
	else if (al < cl) {
		club_check = (cm3_clubs*)*(DWORD*)(a2 + 0x20);
	}
	// group stage indexes
	if (bl > -1 && bl < 8) {
		if (club_check) {
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club_check);
			add_to_income_prize_money_5999A0((BYTE*)ret, 135000);
			add_money_to_club_from_comp_48E3E0(_this, (BYTE*)club_check, 135000, 0, -1, 0, a2, -2);
		}
	}
	return sub_51A150(_this, a2, a3);
}

void __declspec(naked) liber_583B10_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call liber_583B10
		add esp, 0xc
		ret 8
	}
}

void conmebol_libertadores_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = conmebol_libertadores_vtable;
	DWORD x = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
	}
	if ((DWORD*)data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
			}
		}
		sub_9452CA_free(data->f173);
	}
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
		}
	}
	if (data->stages) {
		sub_9452CA_free((BYTE*)(data->stages));
		data->stages = 0;
	}
	if (data->f8) {
		sub_49F450((BYTE*)(data->f8));
		sub_944C94_free((BYTE*)(data->f8));
	}
	DWORD y = -1;
	sub_518690(_this);
}

void conmebol_libertadores_free(BYTE* _this, BYTE a2) {
	conmebol_libertadores_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) conmebol_libertadores_free_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call conmebol_libertadores_free
		add esp, 0x8
		ret 4
	}
}

DWORD conmebol_libertadores_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 1, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 2, 5), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 4, NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 6, 3, 6, 0, 0, 2, 7, 0, 0, 180000);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 2, 13), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 2, 19), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 4, NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 16, 8, 13, 6, 0, 2, 7, 0, 0, 225000);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 2, 27), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 3, 5), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 4, NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 8, 4, 0, 0, 0, 2, 7, 0, 0, 270000);

		return (DWORD)pMem;
	}
	else if (stage_idx < 8) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = AlphabeticGroupStage + stage_idx - 1;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx < 4) {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 1), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 8), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 22), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 6), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 13), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 27), year, Tuesday, Evening);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 2), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 9), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 23), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 7), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 14), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 28), year, Wednesday, Evening);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 8) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 13), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, EleventhRound, 0, FixedTeamOrderInCup + NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 16, 8, 16, 0, 0, 2, 7, 0, 0, 562500);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 21), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 17), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 8, 4, 0, 0, 0, 2, 7, 0, 0, 765000);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 25), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 22), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 4, 2, 0, 0, 0, 2, 7, 0, 0, 1035000);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 0, 0, 0, 1, 0, 0, 8100000, 3150000);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) conmebol_libertadores_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call conmebol_libertadores_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int conmebol_libertadores_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[8];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) conmebol_libertadores_set_champion_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call conmebol_libertadores_set_champion
		add esp, 0x4
		ret 0
	}
}

void liber_team_selection() {
	reset_club_euro_flags(SOUTH_AMERICA_9CF());
	// Last winner of Copa Libertadores
	cm3_club_comps* liber = get_comp(COPA_LIBERTADORES_9CF());
	cm3_clubs* liber_winner = get_last_comp_winner(liber);
	liber_winner->ClubEuroFlag = COPA_LIBERTADORES_9CF();
	liber_winner->ClubEuroSeeding = 1;

	// Last winner of Copa Sudamericana
	cm3_club_comps* sudam = get_comp(COPA_SUDAMERICANA_9CF());
	cm3_clubs* sudam_winner = get_last_comp_winner(sudam);
	sudam_winner->ClubEuroFlag = COPA_LIBERTADORES_9CF();
	sudam_winner->ClubEuroSeeding = 1;

	// Remaining teams
	// Groups, 3QR, 2QR, 1QR
	vector<cm3_nations*> conmebol_nations = get_countries_of_continent(SOUTH_AMERICA_9CF());
	BYTE quals_1[4] = { 5,0,1,0 };
	BYTE quals_2[4] = { 5,0,2,0 };
	BYTE quals_3[4] = { 2,0,2,0 };
	BYTE quals_4[4] = { 2,0,1,1 };
	for (cm3_nations* conmebol_nation : conmebol_nations) {
		BYTE* quals;
		if (conmebol_nation->NationID == NATION_ARGENTINA_9CF()) quals = quals_1;
		else if (conmebol_nation->NationID == NATION_BRAZIL_9CF()) quals = quals_2;
		else if (conmebol_nation->NationID == NATION_CHILE_9CF() || conmebol_nation->NationID == NATION_COLOMBIA_9CF()) quals = quals_3;
		else quals = quals_4;

		BYTE count = 0;
		BYTE curr_seeding = 0;
		for (int x = 0; x < 4; x++) {
			count += quals[x];
			curr_seeding = x + 1;
			if (quals[x] > 0) break;
		}

		BYTE j = 0;
		int required;
		if (filesystem::exists("Data/conmebol.cfg") && *current_year == (WORD)2025) {
			ifstream in("Data/conmebol.cfg", ios_base::in);
			string name;
			char nation[LONG_TXT_LENGTH];
			required = -1;
			while (std::getline(in, name))
			{
				if (name.size() == 0) {
					if (required == -1) continue;
					else break;
				}
				if (name[0] == '*') {
					strcpy_s(nation, name.substr(1).c_str());
					if (_strcmpi(nation, conmebol_nation->NationName) == 0)
					{
						if (conmebol_nation->NationID == NATION_ARGENTINA_9CF()) required = 6;
						else if (conmebol_nation->NationID == NATION_BRAZIL_9CF()) required = 7;
						else required = 4;
						//dprintf("[Liber] Getting clubs from conmebol.cfg: %s - max %d\n", nation, required);
					}
					else {
						required = -1;
					}
					continue;
				}
				if (_strcmpi(nation, conmebol_nation->NationName) != 0) continue;
				if (j >= required) continue;
				cm3_clubs* conmebol_club = find_club(name.c_str());
				if (!conmebol_club || !conmebol_club->ClubNation || conmebol_club->ClubNation != conmebol_nation) {
					//dprintf("Club %s not found, skipping\n", name.c_str());
				}
				else if (conmebol_club->ClubEuroFlag != -1) {
					//dprintf("Club %s is already in a CONMEBOL competition, skipping\n", (conmebol_club->ClubName));
				}
				else {
					//dprintf("Setting club %s to Copa Libertadores\n", (conmebol_club->ClubName));
					conmebol_club->ClubEuroFlag = COPA_LIBERTADORES_9CF();
					if (j >= count) {
						for (int x = curr_seeding; x < 4; x++) {
							count += quals[x];
							curr_seeding = x + 1;
							if (quals[x] > 0) break;
						}
						if (curr_seeding > 4) break;
					}
					conmebol_club->ClubEuroSeeding = curr_seeding;
					j++;
				}
			}
		}
		else
		{
			// Get cup winners if country is playable, only from second season onwards
			if (conmebol_nation->NationLeagueSelected) {
				DWORD max_playables = pnd_count;
				for (DWORD i = 0; i < max_playables; i++) {
					playable_nation_data playable = pnd_list[i];
					if (playable.nation == conmebol_nation && playable.main_cup) {
						cm3_clubs* cup_winner = get_last_comp_winner(playable.main_cup);
						if (cup_winner && cup_winner->ClubNation == conmebol_nation && cup_winner->ClubEuroFlag == -1) {
							cup_winner->ClubEuroFlag = COPA_LIBERTADORES_9CF();
							if (j >= count) {
								for (int x = curr_seeding; x < 4; x++) {
									count += quals[x];
									curr_seeding = x + 1;
									if (quals[x] > 0) break;
								}
								if (curr_seeding > 4) break;
							}
							cup_winner->ClubEuroSeeding = curr_seeding;
							j++;
						}
						else {
							cm3_clubs* cup_loser = get_last_comp_runner_up(playable.main_cup);
							if (cup_loser && cup_loser->ClubNation == conmebol_nation && cup_loser->ClubEuroFlag == -1) {
								cup_loser->ClubEuroFlag = COPA_LIBERTADORES_9CF();
								if (j >= count) {
									for (int x = curr_seeding; x < 4; x++) {
										count += quals[x];
										curr_seeding = x + 1;
										if (quals[x] > 0) break;
									}
									if (curr_seeding > 4) break;
								}
								cup_loser->ClubEuroSeeding = curr_seeding;
								j++;
							}
						}
					}
				}
			}
		}

		if (conmebol_nation->NationID == NATION_ARGENTINA_9CF()) required = 6;
		else if (conmebol_nation->NationID == NATION_BRAZIL_9CF()) required = 7;
		else required = 4;
		//if (j < required) dprintf("[Liber] Getting clubs from database - best\n");
		vector<cm3_clubs*> clubs;
		bool playable = conmebol_nation->NationLeagueSelected;
		if (playable) {
			// playable
			clubs = find_clubs_of_country_for_euro_playable(conmebol_nation->NationID);
			sort(clubs.begin(), clubs.end(), compareClubLastDivPos);
		}
		else {
			// not playable
			clubs = find_clubs_of_country_for_euro(conmebol_nation->NationID);
			sort(clubs.begin(), clubs.end(), compareClubRep);
		}
		size_t max_count = required + 2 - j;
		if (max_count > clubs.size()) max_count = clubs.size();
		for (; j < required; j++) {
			int idx = 0;
			if (!playable) idx = rand() % max_count;
			cm3_clubs* conmebol_club = clubs[idx];
			//dprintf("Setting club %s to Copa Libertadores\n", (conmebol_club->ClubName));
			conmebol_club->ClubEuroFlag = COPA_LIBERTADORES_9CF();
			if (j >= count) {
				for (int x = curr_seeding; x < 4; x++) {
					count += quals[x];
					curr_seeding = x + 1;
					if (quals[x] > 0) break;
				}
				if (curr_seeding > 4) break;
			}
			conmebol_club->ClubEuroSeeding = curr_seeding;
			clubs.erase(clubs.begin() + idx);
			max_count--;
		}
	}
}

void conmebol_libertadores_all_teams(BYTE* _this) {
	liber_team_selection();

	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 47;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	DWORD teams_r1 = 0;
	DWORD teams_r3 = 0;
	DWORD teams_r4 = 0;
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == COPA_LIBERTADORES_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			if (seed == 1 && teams_r1 < 28) {
				teams[teams_r1].club = club;
				teams[teams_r1].f5 = 7;
				teams[teams_r1].f6 = 0;
				teams_r1++;
			}
			else if (seed == 3 && teams_r3 < 13) {
				teams[teams_r3 + 28].club = club;
				teams[teams_r3 + 28].f5 = 8;
				teams[teams_r3 + 28].f6 = 0;
				teams_r3++;
			}
			else if (seed == 4 && teams_r4 < 6) {
				teams[teams_r4 + 41].club = club;
				teams[teams_r4 + 41].f5 = 0;
				teams[teams_r4 + 41].f6 = 0;
				teams_r4++;
			}
		}
	}
}

void conmebol_libertadores_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 19;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	WORD count = 0;
	DWORD total_count = data->special_nteams_seedings;
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 0 || seed == 8) {
			teams[total_teams - count - 1].club = qualifiers[i].club;
			if (seed == 8) {
				teams[total_teams - count - 1].f5 = 1;
			}
			else {
				teams[total_teams - count - 1].f5 = 0;
			}
			teams[total_teams - count - 1].f6 = 0;
			count++;
		}
	}
}

void conmebol_libertadores_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		teams_seeded* all_teams = (teams_seeded*)comp_data->special_teams_seedings;
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < comp_data->special_nteams_seedings; i++)
		{
			clubs.push_back(all_teams[i].club);
		}
		sort(clubs.begin(), clubs.end(), compareClubRep);

		sub_4A2540((BYTE*)comp_data->f8, clubs[0], 1);
		sub_4A2540((BYTE*)comp_data->f8, clubs[1], 2);
		for (int i = 2; i < 4; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 3);
		}
		for (int i = 4; i < 8; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 5);
		}
		for (int i = 8; i < 16; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (int i = 16; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 24; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25);
		}
		for (int i = 32; i < 36; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
		for (int i = 36; i < 44; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 37);
		}
		for (int i = 44; i < 47; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 45);
		}
	}
}

void __declspec(naked) conmebol_libertadores_reputation_setup_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call conmebol_libertadores_reputation_setup
		add esp, 0x4
		ret
	}
}

map<char, char> liber_mappings = {
	{1,25},
	{5,33},
	{9,37},
	{17,45},
};

void conmebol_libertadores_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = liber_mappings[current];
		if (ret_min != 1) ret_min = liber_mappings[min];
		ret_max = liber_mappings[max];
	}
	else if (stage < 8) {
		ret_current = 1 + 8 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 8 * (min - 1);
		if (max < 3) ret_max = 17;
		else ret_max = 1 + 8 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 8) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) conmebol_libertadores_reputation_calc_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call conmebol_libertadores_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

char conmebol_libertadores_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->special_teams_seedings) {
		sub_9452CA_free(data->special_teams_seedings);
		data->special_teams_seedings = 0;
	}
	if (data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
		data->rounds_list = 0;
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
				data->f173[i] = 0;
			}
		}
		sub_9452CA_free(data->f173);
		data->f173 = 0;
	}
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
		}
	}
	data->current_stage = -1;
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	conmebol_libertadores_all_teams(_this);
	conmebol_libertadores_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) conmebol_libertadores_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call conmebol_libertadores_update
		add esp, 0x4
		ret
	}
}

void conmebol_libertadores_group_stage_setup(BYTE* _this) {
	char stage_num = 0;
	DWORD v1 = *(DWORD*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 2, 0, 0, 0 };
	BYTE tiebreaks[4] = { 4, 1, 2, 0 };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < comp_data->special_nteams_seedings; i++) {
		if (teams[i].club->ClubEuroFlag == comp_data->competition_db->ClubCompID)
			clubs.push_back(teams[i].club);
	}
	if (clubs.size() != 32)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(comp_data->competition_db->ClubCompName, msg.c_str(), true);
	}

	sort(clubs.begin(), clubs.end(), compareClubSeeding);
	shuffle(clubs.begin(), clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.begin() + 16, rng);
	shuffle(clubs.begin() + 16, clubs.begin() + 24, rng);
	shuffle(clubs.begin() + 24, clubs.end(), rng);

	WORD group_teams = 4;
	for (int i = 0; i < 8; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 8 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			add_to_income_prize_money_5999A0((BYTE*)ret, 1350000);
			add_money_to_club_from_comp_48E3E0(_this, (BYTE*)club, 1350000, 0, -1, GroupStage, 0, -2);
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 8, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 8, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void conmebol_libertadores_final_stage_setup(BYTE* _this) {
	char stage_num = 8;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	vector<cm3_clubs*> clubs;
	for (char al = 0; al < 8; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
	}

	BYTE team_order[16] = { 0,8,2,10,4,12,6,14,15,7,13,5,11,3,9,1 };
	for (WORD j = 0; j < playoff_teams; j++) {
		*((DWORD*)(&pTeams[team_order[j]])) = (DWORD)clubs[j];
	}

	// for each team in pteams:
	// call 7e9180(AE28F0_ptr + 4 * comp->rules, team)

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	for (char al = 0; al < 8; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats t = ((team_league_stats*)(curr_stage->team_league_table))[2];
		staff_history_knocked_out_86C000(staff_hist_ptr, t.club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
		t.club->ClubEuroFlag = -1;

		t = ((team_league_stats*)(curr_stage->team_league_table))[3];
		staff_history_knocked_out_86C000(staff_hist_ptr, t.club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
		t.club->ClubEuroFlag = -1;
	}
}

void conmebol_libertadores_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			conmebol_libertadores_group_stage_setup(_this);
		}
		else if (current == 8) {
			conmebol_libertadores_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) conmebol_libertadores_stages_create_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call conmebol_libertadores_stages_create
		add esp, 0x4
		ret
	}
}

int conmebol_libertadores_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* sudam_bytes = get_loaded_league(COPA_SUDAMERICANA_9CF());
	comp_stats* sudam_data = (comp_stats*)sudam_bytes;
	DWORD v2 = *(DWORD*)sudam_bytes;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0x1E);
			//*a5 = 1;
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			WORD round_idx = *(WORD*)(rounds + playoff_dates_sz * current_round + 9);
			// Third Round to Copa Sudamericana groups (handled in Copa Sudamericana)
			if (round_idx == 2) {
				club->ClubEuroFlag = COPA_SUDAMERICANA_9CF();
				teams_seeded* qualifiers = (teams_seeded*)sudam_data->special_teams_seedings;
				WORD insert_idx = sudam_data->special_nteams_seedings;
				qualifiers[insert_idx].club = club;
				qualifiers[insert_idx].f5 = 3;
				qualifiers[insert_idx].f6 = 0;
				sudam_data->special_nteams_seedings++;

				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(sudam_data->competition_db), None, GroupStage, 0x1E);
				(*(int(__thiscall**)(BYTE*))(v2 + 0x5C))(sudam_bytes);
			}
			else club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage < 8) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, EleventhRound, 0x1E);
			return 0;
		case TopPlayoff:
			//staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, TenthRound, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage == 8) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			club->ClubEuroFlag = -1;
			//*a5 = 1;
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		case BottomPlayoff:
			staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
			club->ClubEuroFlag = -1;
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) conmebol_libertadores_set_table_fate()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call conmebol_libertadores_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

void conmebol_libertadores_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->year = year;
	data->comp_vtable = conmebol_libertadores_vtable;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 9;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	data->competition_db = comp;
	data->comp_type = CLUB_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f82 = 3;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = 0x2;
	data->f81 = 0xa;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_BLACK_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_ORANGE_2_9CF());
	conmebol_libertadores_all_teams(_this);
	conmebol_libertadores_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	conmebol_libertadores_reputation_setup(_this);
}

void setup_conmebol_libertadores() {
	WriteVTablePtr(conmebol_libertadores_vtable, VTableInitFree, (DWORD)&conmebol_libertadores_free_c);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable2, (DWORD)&liber_583B10_c);
	WriteVTablePtr(conmebol_libertadores_vtable, VTableEoSUpdate, (DWORD)&conmebol_libertadores_update_c);
	WriteVTablePtr(conmebol_libertadores_vtable, VTablePlayoffQual, (DWORD)&conmebol_libertadores_stages_create_c);
	WriteVTablePtr(conmebol_libertadores_vtable, VTableSetChampion, (DWORD)&conmebol_libertadores_set_champion_c);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable15, 0x48cab0); // review? -> 586fa0
	WriteVTablePtr(conmebol_libertadores_vtable, VTableFixtures, (DWORD)&conmebol_libertadores_fixture_caller);
	WriteVTablePtr(conmebol_libertadores_vtable, VTableTableFates, (DWORD)&conmebol_libertadores_set_table_fate);
	WriteVTablePtr(conmebol_libertadores_vtable, VTableStageNews, 0x48C6D0); // review? -> 584550
	WriteVTablePtr(conmebol_libertadores_vtable, VTableReputationSetup, (DWORD)&conmebol_libertadores_reputation_setup_c);
	WriteVTablePtr(conmebol_libertadores_vtable, VTableReputationCalc, (DWORD)&conmebol_libertadores_reputation_calc_c);

	WriteVTablePtr(conmebol_libertadores_vtable, VTable5, 0x521E00);
	WriteVTablePtr(conmebol_libertadores_vtable, VTableLeagueSplit, 0x51F890);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable7, 0x51FC00);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable8, 0x5210F0);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable10, 0x48CEA0);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable17, 0x519690);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable22, 0x5221F0);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable33, 0x522910);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable34, 0x522C50);
	WriteVTablePtr(conmebol_libertadores_vtable, VTableSubsRounds, 0x858e70);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable37, 0x522360);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable38, 0x518790);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable39, 0x51C020);
	WriteVTablePtr(conmebol_libertadores_vtable, VTable40, 0x51F2F0);
}