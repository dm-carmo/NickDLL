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

DWORD* afc_champions_league_elite_vtable = (DWORD*)0x9674D4;

void afc_champions_league_elite_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = afc_champions_league_elite_vtable;
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
	DWORD y = -1;
	sub_518690(_this);
}

void afc_champions_league_elite_free(BYTE* _this, BYTE a2) {
	afc_champions_league_elite_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) afc_champions_league_elite_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call afc_champions_league_elite_free
		add esp, 0x8
		ret 4
	}
}

DWORD afc_champions_league_elite_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 12), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 4, 2, 4, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx < 4) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 5;
		*stage_name_id = AlphabeticGroupStage + stage_idx - 1;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx < 2) {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 30), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 21), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 4), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 25), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 10), year, Tuesday, Evening);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 1), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 22), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 5), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 26), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 11), year, Wednesday, Evening);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 4) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 12), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 3), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, RoundOf16, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 8, 16, 8, 16, 0, 0, 2, 7, prizeMoneyFile.GetInt("afc_cl_elite_r16_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 11), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 16), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 8, 4, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("afc_cl_elite_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 17), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 21), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 4, 2, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("afc_cl_elite_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 22), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("afc_cl_elite_final_win"), prizeMoneyFile.GetInt("afc_cl_elite_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) afc_champions_league_elite_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call afc_champions_league_elite_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int afc_champions_league_elite_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[4];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) afc_champions_league_elite_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call afc_champions_league_elite_set_champion
		add esp, 0x4
		ret 0
	}
}

void afc_cl_elite_team_selection() {
	reset_club_euro_flags(ASIA_9CF());
	// Last winner of Champions League Elite
	cm3_club_comps* cl_elite = get_comp(AFC_CHAMPIONS_LEAGUE_ELITE_9CF());
	cm3_clubs* cl_elite_winner = get_last_comp_winner(cl_elite);
	cl_elite_winner->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
	cl_elite_winner->ClubEuroSeeding = 1;

	// Last winner of Champions League Two
	cm3_club_comps* cl_two = get_comp(AFC_CHAMPIONS_LEAGUE_TWO_9CF());
	cm3_clubs* cl_two_winner = get_last_comp_winner(cl_two);
	cl_two_winner->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
	cl_two_winner->ClubEuroSeeding = 1;

	// Remaining teams
	// Groups, 1QR
	BYTE quals_1[2] = { 3,0 };
	BYTE quals_2[2] = { 2,0 };
	BYTE quals_3[2] = { 2,1 };
	BYTE quals_4[2] = { 1,1 };
	BYTE quals_5[2] = { 1,0 };
	BYTE quals_6[2] = { 0,0 };

	for (int a = 0; a < 2; a++) {
		vector<DWORD> v;
		if (a == 0) v = west_asia_nations();
		else v = east_asia_nations();
		for (size_t i = 0; i < v.size(); i++) {
			if (i >= 6) break;
			cm3_nations* afc_nation = get_country(v[i]);

			BYTE* quals;
			if (i < 1) quals = quals_1;
			else if (i < 2) quals = quals_2;
			else if (i < 3) quals = quals_3;
			else if (i < 4) quals = quals_4;
			else if (i < 6) quals = quals_5;
			else quals = quals_6;

			BYTE count = 0;
			BYTE curr_seeding = 0;
			for (int x = 0; x < 2; x++) {
				count += quals[x];
				curr_seeding = x + 1;
				if (quals[x] > 0) break;
			}
			BYTE j = 0;
			int required;
			if (filesystem::exists("Data/afc.cfg") && *current_year == (WORD)START_YEAR) {
				ifstream in("Data/afc.cfg", ios_base::in);
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
						if (afc_nation == nation_ptr)
						{
							if (i < 1) required = 3;
							else if (i < 2) required = 2;
							else if (i < 3) required = 3;
							else if (i < 4) required = 2;
							else if (i < 6) required = 1;
							else required = 0;
							//dprintf("[CLE] Getting clubs from afc.cfg: %s - max %d\n", nation, required);
						}
						else {
							required = -1;
						}
						continue;
					}
					if (afc_nation != nation_ptr) continue;
					if (j >= required) continue;
					cm3_clubs* afc_club = find_club(name.c_str());
					if (!afc_club || !afc_club->ClubNation || afc_club->ClubNation != afc_nation) {
						//dprintf("Club %s not found, skipping\n", name.c_str());
					}
					else if (afc_club->ClubEuroFlag != -1) {
						//dprintf("Club %s is already in a AFC competition, skipping\n", (afc_club->ClubName));
					}
					else {
						//dprintf("Setting club %s to Champions League Elite\n", (afc_club->ClubName));
						afc_club->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
						if (j >= count) {
							for (int x = curr_seeding; x < 2; x++) {
								count += quals[x];
								curr_seeding = x + 1;
								if (quals[x] > 0) break;
							}
							if (curr_seeding > 2) break;
						}
						afc_club->ClubEuroSeeding = curr_seeding;
						j++;
					}
				}
			}
			else if (i < 4 && afc_nation->NationLeagueSelected) {
				DWORD max_playables = pnd_count;
				for (DWORD i = 0; i < max_playables; i++) {
					playable_nation_data playable = pnd_list[i];
					if (playable.nation == afc_nation && playable.main_cup) {
						cm3_clubs* cup_winner = get_last_comp_winner(playable.main_cup);
						if (cup_winner && cup_winner->ClubNation == afc_nation && cup_winner->ClubEuroFlag == -1) {
							cup_winner->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
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
							cm3_clubs* cup_loser = get_last_comp_runner_up(playable.main_cup);
							if (cup_loser && cup_loser->ClubNation == afc_nation && cup_loser->ClubEuroFlag == -1) {
								cup_loser->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
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

			if (i < 1) required = 3;
			else if (i < 2) required = 2;
			else if (i < 3) required = 3;
			else if (i < 4) required = 2;
			else if (i < 6) required = 1;
			else required = 0;
			//if (j < required) dprintf("[CLE] Getting clubs from database - best\n");
			vector<cm3_clubs*> clubs;
			bool playable = afc_nation->NationLeagueSelected;
			if (playable) {
				// playable
				clubs = find_clubs_of_country_for_euro_playable(afc_nation->NationID);
				sort(clubs.begin(), clubs.end(), compareClubLastDivPos);
			}
			else {
				// not playable
				clubs = find_clubs_of_country_for_euro(afc_nation->NationID);
				sort(clubs.begin(), clubs.end(), compareClubRep);
			}
			size_t max_count = required + 2 - j;
			if (max_count > clubs.size()) max_count = clubs.size();
			for (; j < required; j++) {
				int idx = 0;
				if (!playable) idx = rand() % max_count;
				cm3_clubs* afc_club = clubs[idx];
				//dprintf("Setting club %s to Champions League Elite\n", (afc_club->ClubName));
				afc_club->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
				if (j >= count) {
					for (int x = curr_seeding; x < 2; x++) {
						count += quals[x];
						curr_seeding = x + 1;
						if (quals[x] > 0) break;
					}
					if (curr_seeding > 2) break;
				}
				afc_club->ClubEuroSeeding = curr_seeding;
				clubs.erase(clubs.begin() + idx);
				max_count--;
			}
		}
	}
}

void afc_champions_league_elite_all_teams(BYTE* _this) {
	afc_cl_elite_team_selection();

	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 26;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	DWORD teams_r1 = 0;
	DWORD teams_r2 = 0;
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == AFC_CHAMPIONS_LEAGUE_ELITE_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			if (seed == 1 && teams_r1 < 22) {
				teams[teams_r1].club = club;
				teams[teams_r1].f5 = 7;
				teams[teams_r1].f6 = 0;
				teams_r1++;
			}
			else if (seed == 2 && teams_r2 < 4) {
				teams[teams_r2 + 22].club = club;
				teams[teams_r2 + 22].f5 = 8;
				teams[teams_r2 + 22].f6 = 0;
				teams_r2++;
			}
		}
	}
}

void afc_champions_league_elite_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 4;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	WORD count = 0;
	DWORD total_count = data->special_nteams_seedings;
	vector<cm3_clubs*> qual_clubs;
	for (WORD i = 0; i < total_count; i++) {
		char seed = qualifiers[i].f5;
		if (seed == 8) {
			qual_clubs.push_back(qualifiers[i].club);
			count++;
		}
	}
	sort(qual_clubs.begin(), qual_clubs.end(), compareClubAsiaWestEast);
	for (WORD i = 0; i < qual_clubs.size(); i++) {
		teams[i].club = qual_clubs[i];
		teams[i].f5 = i % 2;
		teams[i].f6 = 0;
	}
}

void afc_champions_league_elite_reputation_setup(BYTE* _this) {
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
		for (int i = 16; i < 20; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 17);
		}
		for (int i = 20; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 21);
		}
		for (int i = 24; i < 26; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25);
		}
	}
}

void __declspec(naked) afc_champions_league_elite_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call afc_champions_league_elite_reputation_setup
		add esp, 0x4
		ret
	}
}

void afc_champions_league_elite_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		if (current != 1) ret_current = 25;
		if (min != 1) ret_min = 25;
		if (max == 1) ret_max = 21;
		else ret_max = 25;
	}
	else if (stage < 4) {
		ret_current = 1 + 4 * (current - 1);
		if (min < 5) ret_min = 1;
		else ret_min = 1 + 4 * (min - 1);
		if (max < 5) ret_max = 17;
		else ret_max = 1 + 4 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 4) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) afc_champions_league_elite_reputation_calc_c()
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
		call afc_champions_league_elite_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

char afc_champions_league_elite_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
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
	afc_champions_league_elite_all_teams(_this);
	afc_champions_league_elite_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) afc_champions_league_elite_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call afc_champions_league_elite_update
		add esp, 0x4
		ret
	}
}

void afc_champions_league_elite_group_stage_setup(BYTE* _this) {
	char stage_num = 0;
	DWORD v1 = *(DWORD*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 4, 0, 0, 0 };
	BYTE tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GamesWonTiebreaker, NoTiebreaker };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < comp_data->special_nteams_seedings; i++) {
		if (teams[i].club->ClubEuroFlag == comp_data->competition_db->ClubCompID)
			clubs.push_back(teams[i].club);
	}
	if (clubs.size() != 24)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(comp_data->competition_db->ClubCompName, msg.c_str(), true);
	}

	sort(clubs.begin(), clubs.end(), compareClubAsiaWestEast);
	sort(clubs.begin(), clubs.begin() + 12, compareClubSeeding);
	sort(clubs.begin() + 12, clubs.end(), compareClubSeeding);
	shuffle(clubs.begin(), clubs.begin() + 4, rng);
	shuffle(clubs.begin() + 4, clubs.begin() + 8, rng);
	shuffle(clubs.begin() + 8, clubs.begin() + 12, rng);
	shuffle(clubs.begin() + 12, clubs.begin() + 16, rng);
	shuffle(clubs.begin() + 16, clubs.begin() + 20, rng);
	shuffle(clubs.begin() + 20, clubs.end(), rng);

	WORD group_teams = 6;
	for (int i = 0; i < 4; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(group_teams * 4);

		int idx = i;
		if (i > 1) idx = 12 + (i - 2);
		for (int j = 0; j < 3; j++) {
			cm3_clubs* club = clubs[idx + 4 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("afc_cl_elite_groups_qualify"));
			AddMoneyFromComp(_this, (BYTE*)club, prizeMoneyFile.GetInt("afc_cl_elite_groups_qualify"), 0, -1, GroupStage, 0, -2);

			club = clubs[idx + 4 * j + 2];
			*((DWORD*)(&pTeams[j + 3])) = (DWORD)club;
			ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("afc_cl_elite_groups_qualify"));
			AddMoneyFromComp(_this, (BYTE*)club, prizeMoneyFile.GetInt("afc_cl_elite_groups_qualify"), 0, -1, GroupStage, 0, -2);
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 1, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 8, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void afc_champions_league_elite_final_stage_setup(BYTE* _this) {
	char stage_num = 4;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	vector<cm3_clubs*> clubs;
	for (char al = 0; al < 4; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		clubs.push_back(table_teams[0].club);
		clubs.push_back(table_teams[1].club);
		clubs.push_back(table_teams[2].club);
		clubs.push_back(table_teams[3].club);
	}

	BYTE team_order[16] = { 0,2,4,6,7,5,3,1,8,10,12,14,15,13,11,9 };
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
	for (char al = 0; al < 4; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats t = ((team_league_stats*)(curr_stage->team_league_table))[4];
		t.club->ClubEuroFlag = -1;

		t = ((team_league_stats*)(curr_stage->team_league_table))[5];
		t.club->ClubEuroFlag = -1;
	}
}

void afc_champions_league_elite_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			afc_champions_league_elite_group_stage_setup(_this);
		}
		else if (current == 4) {
			afc_champions_league_elite_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) afc_champions_league_elite_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call afc_champions_league_elite_stages_create
		add esp, 0x4
		ret
	}
}

int afc_champions_league_elite_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* cl2_bytes = get_loaded_league(AFC_CHAMPIONS_LEAGUE_TWO_9CF());
	comp_stats* cl2_data = (comp_stats*)cl2_bytes;
	DWORD v2 = *(DWORD*)cl2_bytes;
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
			WORD round_idx = *(WORD*)(rounds + playoff_dates_sz * current_round + 9);
			// losers to Champions League 2 groups (handled in Champions League 2)
			if (round_idx == 0) {
				club->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_TWO_9CF();
				teams_seeded* qualifiers = (teams_seeded*)cl2_data->special_teams_seedings;
				WORD insert_idx = cl2_data->special_nteams_seedings;
				qualifiers[insert_idx].club = club;
				qualifiers[insert_idx].f5 = 3;
				qualifiers[insert_idx].f6 = 0;
				cl2_data->special_nteams_seedings++;

				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(cl2_data->competition_db), None, GroupStage, 0x1E);
				(*(int(__thiscall**)(BYTE*))(v2 + 0x5C))(cl2_bytes);
			}
			else club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage < 4) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			return 0;
		}
	}
	else if (stage == 4) {
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

void __declspec(naked) afc_champions_league_elite_set_table_fate()
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
		call afc_champions_league_elite_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int afc_cl_elite_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
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
		else {
			comp_data = get_comp(AFC_CHAMPIONS_LEAGUE_TWO_9CF());
			sub_66F4E0(0xDE1F64, (DWORD)&drop_down_grp_title_msg[0], club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
				&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
	}
	else if (stage_id < 4) {
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
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	else if (stage_id == 4) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

	return 0;
}

void __declspec(naked) afc_cl_elite_stage_news_c()
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
		call afc_cl_elite_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void afc_champions_league_elite_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->year = year;
	data->comp_vtable = afc_champions_league_elite_vtable;
	data->competition_db = comp;
	data->comp_type = CLUB_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f82 = 3;
	data->max_bench = 7;
	data->max_subs = 3;
	data->rules = RulesAsia;
	data->f81 = 0xa;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 5;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	afc_champions_league_elite_all_teams(_this);
	afc_champions_league_elite_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	afc_champions_league_elite_reputation_setup(_this);
}

void setup_afc_champions_league_elite() {
	WriteVTablePtr(afc_champions_league_elite_vtable, VTableInitFree, (DWORD)&afc_champions_league_elite_free_c);
	WriteVTablePtr(afc_champions_league_elite_vtable, VTableEoSUpdate, (DWORD)&afc_champions_league_elite_update_c);
	WriteVTablePtr(afc_champions_league_elite_vtable, VTablePlayoffQual, (DWORD)&afc_champions_league_elite_stages_create_c);
	WriteVTablePtr(afc_champions_league_elite_vtable, VTableSetChampion, (DWORD)&afc_champions_league_elite_set_champion_c);
	WriteVTablePtr(afc_champions_league_elite_vtable, VTableClubLandmarks, 0x48cab0);
	WriteVTablePtr(afc_champions_league_elite_vtable, VTableFixtures, (DWORD)&afc_champions_league_elite_fixture_caller);
	WriteVTablePtr(afc_champions_league_elite_vtable, VTableTableFates, (DWORD)&afc_champions_league_elite_set_table_fate);
	WriteVTablePtr(afc_champions_league_elite_vtable, VTableStageNews, (DWORD)&afc_cl_elite_stage_news_c);
	WriteVTablePtr(afc_champions_league_elite_vtable, VTableReputationSetup, (DWORD)&afc_champions_league_elite_reputation_setup_c);
	WriteVTablePtr(afc_champions_league_elite_vtable, VTableReputationCalc, (DWORD)&afc_champions_league_elite_reputation_calc_c);
	WriteVTablePtr(afc_champions_league_elite_vtable, VTableSubsRounds, 0x858e70);
}