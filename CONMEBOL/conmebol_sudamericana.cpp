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

DWORD* conmebol_sudamericana_vtable = (DWORD*)0x968CA8;

// prize money for group stage win/draw and coefficient updates
int sudam_money_after_match(BYTE* _this, BYTE* a2, int a3) {
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
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("conmebol_sudam_groups_win"));
			AddMoneyFromComp(_this, (BYTE*)club_check, prizeMoneyFile.GetInt("conmebol_sudam_groups_win"), 0, -1, 0, a2, -2);
		}
	}
	return sub_51A150(_this, a2, a3);
}

void __declspec(naked) sudam_money_after_match_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sudam_money_after_match
		add esp, 0xc
		ret 8
	}
}

void conmebol_sudamericana_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = conmebol_sudamericana_vtable;
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
			data->stages[i] = 0;
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
	sub_518690(_this);
}

void conmebol_sudamericana_free(BYTE* _this, BYTE a2) {
	conmebol_sudamericana_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) conmebol_sudamericana_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call conmebol_sudamericana_free
		add esp, 0x8
		ret 4
	}
}

DWORD conmebol_sudamericana_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 1, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 3, 5), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, FixedTeamOrderInCup + PenaltiesNoExtraTime_1, NoTiebreak_2, 8, 32, 16, 32, 0, 0, 1, 0, prizeMoneyFile.GetInt("conmebol_sudam_r1_qualify"));

		return (DWORD)pMem;
	}
	else if (stage_idx < 8) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = AlphabeticGroupStage + stage_idx - 1;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

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
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 16), year, Wednesday, Evening);
		AddPlayoffTVFixture(pMem, fixture_id, 0);
		FillFixtureDetails(pMem, fixture_id++, KnockoutPlayoff, 8, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 16, 8, 16, 0, 0, 2, 7, prizeMoneyFile.GetInt("conmebol_sudam_ko_qualify"));

		return (DWORD)pMem;
	}
	else if (stage_idx == 9) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 24), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 13), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 8, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 16, 8, 16, 0, 0, 2, 7, prizeMoneyFile.GetInt("conmebol_sudam_r16_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 21), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 17), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 8, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 8, 4, 0, 0, 0, 2, 7, prizeMoneyFile.GetInt("conmebol_sudam_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 25), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 22), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 8, FixedTeamOrderInCup + Libertadores_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 4, 2, 0, 0, 0, 2, 7, prizeMoneyFile.GetInt("conmebol_sudam_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 29), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("conmebol_sudam_final_win"), prizeMoneyFile.GetInt("conmebol_sudam_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) conmebol_sudamericana_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call conmebol_sudamericana_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int conmebol_sudamericana_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[9];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) conmebol_sudamericana_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call conmebol_sudamericana_set_champion
		add esp, 0x4
		ret 0
	}
}

void sudam_team_selection() {
	// Groups, 1QR
	vector<cm3_nations*> conmebol_nations = get_countries_of_continent(SOUTH_AMERICA_9CF());
	BYTE quals_1[2] = { 6,0 };
	BYTE quals_2[2] = { 0,4 };
	for (cm3_nations* conmebol_nation : conmebol_nations) {
		BYTE* quals;
		if (conmebol_nation->NationID == NATION_ARGENTINA_9CF() || conmebol_nation->NationID == NATION_BRAZIL_9CF()) quals = quals_1;
		else quals = quals_2;

		BYTE count = 0;
		BYTE curr_seeding = 0;
		for (int x = 0; x < 2; x++) {
			count += quals[x];
			curr_seeding = x + 1;
			if (quals[x] > 0) break;
		}

		BYTE j = 0;
		int required;
		if (filesystem::exists("Data/conmebol.cfg") && *current_year == (WORD)START_YEAR) {
			ifstream in("Data/conmebol.cfg", ios_base::in);
			string name;
			char nation[LONG_TXT_LENGTH];
			cm3_nations* nation_ptr;
			required = -1;
			while (std::getline(in, name))
			{
				if (name.size() == 0) {
					if (required == -1) continue;
					else break;
				}
				if (name[0] == '*') {
					strcpy_s(nation, name.substr(1).c_str());
					nation_ptr = find_country(nation);
					if (conmebol_nation == nation_ptr)
					{
						if (conmebol_nation->NationID == NATION_ARGENTINA_9CF() || conmebol_nation->NationID == NATION_BRAZIL_9CF()) required = 6;
						else required = 4;
						//dprintf("[Sudam] Getting clubs from conmebol.cfg: %s - max %d\n", nation, required);
					}
					else {
						required = -1;
					}
					continue;
				}
				if (conmebol_nation != nation_ptr) continue;
				if (j >= required) continue;
				cm3_clubs* conmebol_club = find_club(name.c_str());
				if (!conmebol_club || !conmebol_club->ClubNation || conmebol_club->ClubNation != conmebol_nation) {
					//dprintf("Club %s not found, skipping\n", name.c_str());
				}
				else if (conmebol_club->ClubEuroFlag != -1) {
					//dprintf("Club %s is already in a CONMEBOL competition, skipping\n", (conmebol_club->ClubName));
				}
				else {
					//dprintf("Setting club %s to Copa Sudamericana\n", (conmebol_club->ClubName));
					conmebol_club->ClubEuroFlag = COPA_SUDAMERICANA_9CF();
					if (j >= count) {
						for (int x = curr_seeding; x < 2; x++) {
							count += quals[x];
							curr_seeding = x + 1;
							if (quals[x] > 0) break;
						}
						if (curr_seeding > 2) break;
					}
					conmebol_club->ClubEuroSeeding = curr_seeding;
					j++;
				}
			}
		}
		else
		{
			// Get secondary cup winners if country is playable, only from second season onwards
			if (conmebol_nation->NationLeagueSelected) {
				DWORD max_playables = pnd_count;
				for (DWORD i = 0; i < max_playables; i++) {
					playable_nation_data playable = pnd_list[i];
					if (playable.nation == conmebol_nation && playable.league_cup) {
						cm3_clubs* cup_winner = get_last_comp_winner(playable.league_cup);
						if (cup_winner && cup_winner->ClubNation == conmebol_nation && cup_winner->ClubEuroFlag == -1) {
							cup_winner->ClubEuroFlag = COPA_SUDAMERICANA_9CF();
							if (j >= count) {
								for (int x = curr_seeding; x < 2; x++) {
									count += quals[x];
									curr_seeding = x + 1;
									if (quals[x] > 0) break;
								}
								if (curr_seeding > 2) break;
							}
							cup_winner->ClubEuroSeeding = curr_seeding;
							j++;
						}
						else {
							cm3_clubs* cup_loser = get_last_comp_runner_up(playable.league_cup);
							if (cup_loser && cup_loser->ClubNation == conmebol_nation && cup_loser->ClubEuroFlag == -1) {
								cup_loser->ClubEuroFlag = COPA_SUDAMERICANA_9CF();
								if (j >= count) {
									for (int x = curr_seeding; x < 2; x++) {
										count += quals[x];
										curr_seeding = x + 1;
										if (quals[x] > 0) break;
									}
									if (curr_seeding > 2) break;
								}
								cup_loser->ClubEuroSeeding = curr_seeding;
								j++;
							}
						}
					}
				}
			}
		}

		if (conmebol_nation->NationID == NATION_ARGENTINA_9CF() || conmebol_nation->NationID == NATION_BRAZIL_9CF()) required = 6;
		else required = 4;
		//if (j < required) dprintf("[Sudam] Getting clubs from database - best\n");
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
		for (; j < required && max_count > 0; j++) {
			int idx = 0;
			if (!playable) idx = rand() % max_count;
			cm3_clubs* conmebol_club = clubs[idx];
			//dprintf("Setting club %s to Copa Sudamericana\n", (conmebol_club->ClubName));
			conmebol_club->ClubEuroFlag = COPA_SUDAMERICANA_9CF();
			if (j >= count) {
				for (int x = curr_seeding; x < 2; x++) {
					count += quals[x];
					curr_seeding = x + 1;
					if (quals[x] > 0) break;
				}
				if (curr_seeding > 2) break;
			}
			conmebol_club->ClubEuroSeeding = curr_seeding;
			clubs.erase(clubs.begin() + idx);
			max_count--;
		}
		if (j < required) {
			for (; j < required; j++) {
				DWORD backup_id = (rand() % 2) ? NATION_ARGENTINA_9CF() : NATION_BRAZIL_9CF();
				clubs = find_clubs_of_country_for_euro(backup_id);
				sort(clubs.begin(), clubs.end(), compareClubRep);
				size_t max_count = required + 2 - j;
				if (max_count > clubs.size()) max_count = clubs.size();
				int idx = rand() % max_count;
				cm3_clubs* conmebol_club = clubs[idx];
				//dprintf("Setting backup club %s to Copa Sudamericana\n", (conmebol_club->ClubName));
				conmebol_club->ClubEuroFlag = COPA_SUDAMERICANA_9CF();
				if (j >= count) {
					for (int x = curr_seeding; x < 2; x++) {
						count += quals[x];
						curr_seeding = x + 1;
						if (quals[x] > 0) break;
					}
					if (curr_seeding > 2) break;
				}
				conmebol_club->ClubEuroSeeding = curr_seeding;
			}
		}
	}
}

void conmebol_sudamericana_all_teams(BYTE* _this) {
	sudam_team_selection();

	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 56;
	data->special_nteams_seedings = 44;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	DWORD teams_r1 = 0;
	DWORD teams_r2 = 0;
	DWORD teams_r4 = 0;
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == COPA_SUDAMERICANA_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			if (seed == 1 && teams_r1 < 12) {
				teams[teams_r1].club = club;
				teams[teams_r1].f5 = 7;
				teams[teams_r1].f6 = 0;
				teams_r1++;
			}
			else if (seed == 2 && teams_r2 < 32) {
				teams[teams_r2 + 12].club = club;
				teams[teams_r2 + 12].f5 = 13;
				teams[teams_r2 + 12].f6 = 0;
				teams_r2++;
			}
		}
	}
}

void conmebol_sudamericana_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 32;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	WORD count = 0;
	DWORD total_count = data->special_nteams_seedings;

	vector<cm3_clubs*> qual_clubs;
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 13) {
			qual_clubs.push_back(qualifiers[i].club);
			count++;
		}
	}
	sort(qual_clubs.begin(), qual_clubs.end(), compareClubNationID);
	shuffle(qual_clubs.begin(), qual_clubs.begin() + 4, rng);
	shuffle(qual_clubs.begin() + 4, qual_clubs.begin() + 8, rng);
	shuffle(qual_clubs.begin() + 8, qual_clubs.begin() + 12, rng);
	shuffle(qual_clubs.begin() + 12, qual_clubs.begin() + 16, rng);
	shuffle(qual_clubs.begin() + 16, qual_clubs.begin() + 20, rng);
	shuffle(qual_clubs.begin() + 20, qual_clubs.begin() + 24, rng);
	shuffle(qual_clubs.begin() + 24, qual_clubs.begin() + 28, rng);
	shuffle(qual_clubs.begin() + 28, qual_clubs.end(), rng);

	for (WORD i = 0; i < qual_clubs.size(); i++) {
		teams[i].club = qual_clubs[i];
		teams[i].f5 = i % 2;
		teams[i].f6 = 0;
	}
}

void conmebol_sudamericana_reputation_setup(BYTE* _this) {
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
		for (int i = 32; i < 40; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
		}
		for (int i = 40; i < 56; i++) {
			if (i >= comp_data->special_nteams_seedings) return;
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 41);
		}
	}
}

void __declspec(naked) conmebol_sudamericana_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call conmebol_sudamericana_reputation_setup
		add esp, 0x4
		ret
	}
}

void conmebol_sudamericana_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		if (current != 1) ret_current = 41;
		if (min != 1) ret_min = 41;
		if (max == 1) ret_max = 33;
		else ret_max = 41;
	}
	else if (stage < 8) {
		ret_current = 1 + 8 * (current - 1);
		if (min < 7) ret_min = 1;
		else ret_min = 1 + 8 * (min - 1);
		if (max < 3) ret_max = 9;
		else if (max < 7) ret_max = 17;
		else ret_max = 1 + 8 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 8) {
		if (current != 1) ret_current = 17;
		if (min != 1) ret_min = 17;
		if (max == 1) ret_max = 9;
		else ret_max = 17;
	}
	else if (stage == 9) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) conmebol_sudamericana_reputation_calc_c()
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
		call conmebol_sudamericana_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

char conmebol_sudamericana_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
		data->teams_list = 0;
	}
	if (data->special_teams_seedings) {
		sub_9452CA_free(data->special_teams_seedings);
		data->special_nteams_seedings = 0;
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
			data->stages[i] = 0;
		}
	}
	data->current_stage = -1;
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	conmebol_sudamericana_all_teams(_this);
	conmebol_sudamericana_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) conmebol_sudamericana_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call conmebol_sudamericana_update
		add esp, 0x4
		ret
	}
}

void conmebol_sudamericana_group_stage_setup(BYTE* _this) {
	char stage_num = 0;
	DWORD v1 = *(DWORD*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	char prom_rel[4] = { 1, 1, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker, NoTiebreaker };

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
		DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 8 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("conmebol_sudam_groups_qualify"));
			AddMoneyFromComp(_this, (BYTE*)club, prizeMoneyFile.GetInt("conmebol_sudam_groups_qualify"), 0, -1, GroupStage, 0, -2);
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 8, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void conmebol_sudamericana_playoff_stage_setup(BYTE* _this) {
	char stage_num = 8;

	DWORD v1 = *(DWORD*)_this;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	vector<team_league_stats> sort_first, sort_second;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (char al = 0; al < 8; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		sort_first.push_back(table_teams[1]);
	}

	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* liber_data = (comp_stats*)get_loaded_league(COPA_LIBERTADORES_9CF());
	for (char al = 0; al < 8; al++) {
		curr_stage = (comp_stats*)(liber_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats t = table_teams[2];
		sort_second.push_back(t);
		WORD insert_idx = comp_data->special_nteams_seedings;
		teams[insert_idx].club = t.club;
		teams[insert_idx].f5 = 3;
		teams[insert_idx].f6 = 0;
		comp_data->special_nteams_seedings++;
		t.club->ClubEuroFlag = COPA_SUDAMERICANA_9CF();
		staff_history_qualified_86BDD0(staff_hist_ptr, t.club, (DWORD)(comp_data->competition_db), None, KnockoutPlayoff, 0x1E);
	}
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	sort(sort_first.begin(), sort_first.end(), sortTLS);
	sort(sort_second.begin(), sort_second.end(), sortTLS);

	BYTE first_seed[8] = { 0,1,2,3,4,5,6,7 };
	shuffle(begin(first_seed), end(first_seed), rng);
	BYTE second_seed[8] = { 0,1,2,3,4,5,6,7 };
	shuffle(begin(second_seed), end(second_seed), rng);

	BYTE team_order[16] = { 0 };
	for (WORD j = 0; j < playoff_teams / 2; j++) {
		cm3_clubs* club1 = sort_first[first_seed[j]].club;
		cm3_clubs* club2 = sort_second[second_seed[j]].club;
		*((DWORD*)(&pTeams[j * 2])) = (DWORD)club2;
		*((DWORD*)(&pTeams[j * 2 + 1])) = (DWORD)club1;
		team_order[j * 2] = second_seed[j] + 16;
		team_order[j * 2 + 1] = first_seed[j] + 8;
	}

	// for each team in pteams:
	// call 7e9180(AE28F0_ptr + 4 * comp->rules, team)

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, &team_order[0]);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;

	for (char al = 0; al < 8; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats t = ((team_league_stats*)(curr_stage->team_league_table))[2];
		t.club->ClubEuroFlag = -1;

		t = ((team_league_stats*)(curr_stage->team_league_table))[3];
		t.club->ClubEuroFlag = -1;
	}
}

void conmebol_sudamericana_final_stage_setup(BYTE* _this) {
	char stage_num = 9;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	vector<team_league_stats> sort_first;
	vector<teams_seeded> sort_second;
	for (char al = 0; al < 8; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		sort_first.push_back(table_teams[0]);
	}

	comp_stats* stage8_data = (comp_stats*)comp_data->stages[8];
	for (WORD j = 0; j < stage8_data->n_teams; j++) {
		teams_seeded t = ((teams_seeded*)stage8_data->teams_list)[j];
		if (t.f6 == 1) {
			sort_second.push_back(t);
		}
	}

	sort(sort_first.begin(), sort_first.end(), sortTLS);
	sort(sort_second.begin(), sort_second.end(), sortTeamSeeding);

	BYTE first_seed[8] = { 0,1,2,3,4,5,6,7 };
	shuffle(begin(first_seed), end(first_seed), rng);
	shuffle(begin(sort_second), end(sort_second), rng);

	BYTE team_order[16] = { 0 };
	for (WORD j = 0; j < playoff_teams / 2; j++) {
		cm3_clubs* club1 = sort_first[first_seed[j]].club;
		cm3_clubs* club2 = sort_second[j].club;
		*((DWORD*)(&pTeams[j * 2])) = (DWORD)club2;
		*((DWORD*)(&pTeams[j * 2 + 1])) = (DWORD)club1;
		team_order[j * 2] = sort_second[j].f5;
		team_order[j * 2 + 1] = first_seed[j];
	}

	// for each team in pteams:
	// call 7e9180(AE28F0_ptr + 4 * comp->rules, team)

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, &team_order[0]);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

void conmebol_sudamericana_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		if (current == 0) {
			BYTE* liber_bytes = get_loaded_league(COPA_LIBERTADORES_9CF());
			if (liber_bytes) {
				DWORD v1 = *(DWORD*)liber_bytes;
				char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(liber_bytes, 0, 1);
				if (ret != 0) {
					comp_data->current_stage = current;
					conmebol_sudamericana_group_stage_setup(_this);
				}
			}
		}
		else if (current == 8) {
			comp_data->current_stage = current;
			conmebol_sudamericana_playoff_stage_setup(_this);
		}
		else if (current == 9) {
			comp_data->current_stage = current;
			conmebol_sudamericana_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) conmebol_sudamericana_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call conmebol_sudamericana_stages_create
		add esp, 0x4
		ret
	}
}

int conmebol_sudamericana_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0x1E);
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage < 8) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, KnockoutPlayoff, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage == 9) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
			club->ClubEuroFlag = -1;
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

void __declspec(naked) conmebol_sudamericana_set_table_fate()
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
		call conmebol_sudamericana_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int sudam_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id == -1)
	{
		if (show_body_text) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
		if (fate == 1) {
			sub_66F4E0(0xDE1F64, (DWORD)&qualified_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
				&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
		else return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	}
	else if (stage_id < 8) {
		if (fate == Qualified1) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_r16_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_r16_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (fate == TopPlayoff) {
			if (show_body_text) {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_knockout_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderName, comp_data->ClubCompGenderName,
					&club_data->ClubNameShort[0], &comp_data->ClubCompName[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompName[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
			else {
				sub_66F4E0(0xDE1F64, (DWORD)&qualified_knockout_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 8) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);
	else if (stage_id == 9) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

	return 0;
}

void __declspec(naked) sudam_stage_news_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x28]
		push dword ptr[eax + 0x24]
		push dword ptr[eax + 0x20]
		push dword ptr[eax + 0x1c]
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sudam_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void conmebol_sudamericana_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->year = year;
	data->comp_vtable = conmebol_sudamericana_vtable;
	data->competition_db = comp;
	data->comp_type = CLUB_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f82 = 3;
	data->max_bench = 7;
	data->max_subs = 3;
	data->rules = RulesSouthAmerica;
	data->f81 = 0xa;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 10;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	conmebol_sudamericana_all_teams(_this);
	conmebol_sudamericana_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	conmebol_sudamericana_reputation_setup(_this);
}

void setup_conmebol_sudamericana() {
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableInitFree, (DWORD)&conmebol_sudamericana_free_c);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTablePostMatchUpdate, (DWORD)&sudam_money_after_match_c);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableEoSUpdate, (DWORD)&conmebol_sudamericana_update_c);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTablePlayoffQual, (DWORD)&conmebol_sudamericana_stages_create_c);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableSetChampion, (DWORD)&conmebol_sudamericana_set_champion_c);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableClubLandmarks, 0x48cab0); // review? -> 586fa0
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableFixtures, (DWORD)&conmebol_sudamericana_fixture_caller);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableTableFates, (DWORD)&conmebol_sudamericana_set_table_fate);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableStageNews, (DWORD)&sudam_stage_news_c);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableReputationSetup, (DWORD)&conmebol_sudamericana_reputation_setup_c);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableReputationCalc, (DWORD)&conmebol_sudamericana_reputation_calc_c);

	WriteVTablePtr(conmebol_sudamericana_vtable, VTable5, 0x521E00);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableLeagueSplit, 0x51F890);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable7, 0x51FC00);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable8, 0x5210F0);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable10, 0x48CEA0);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable17, 0x519690);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable22, 0x5221F0);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable33, 0x522910);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable34, 0x522C50);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTableSubsRounds, 0x858e70);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable37, 0x522360);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable38, 0x518790);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable39, 0x51C020);
	WriteVTablePtr(conmebol_sudamericana_vtable, VTable40, 0x51F2F0);
}