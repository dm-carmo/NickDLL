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

// Credits to tafo for the initial research on how to have a realistic league phase
DWORD* afc_champions_league_elite_vtable = (DWORD*)0x9674D4;

void afc_champions_league_elite_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = afc_champions_league_elite_vtable;
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

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 28), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 12), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 8, 4, 8, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx < 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 8;
		if (stage_idx == 0) *stage_name_id = WestLeagueStage;
		else *stage_name_id = EastLeagueStage;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx == 0) {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 16), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 14), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 28), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 4), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 25), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 9), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 10), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 17), year, Tuesday, Evening);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 17), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 15), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 29), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 5), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 26), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 10), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 11), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 18), year, Wednesday, Evening);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 19), year, Thursday);
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
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[2];
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
	vector<DWORD> asia_west = west_asia_nations();
	// Last winner of Champions League Elite
	cm3_club_comps* cl_elite = get_comp(AFC_CHAMPIONS_LEAGUE_ELITE_9CF());
	cm3_clubs* cl_elite_winner = get_last_comp_winner(cl_elite);
	cl_elite_winner->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
	cl_elite_winner->ClubEuroSeeding = 1;
	int extra_v1 = find(asia_west.begin(), asia_west.end(), cl_elite_winner->ClubNation->NationID) == asia_west.end();

	// Last winner of Champions League Two
	cm3_club_comps* cl_two = get_comp(AFC_CHAMPIONS_LEAGUE_TWO_9CF());
	cm3_clubs* cl_two_winner = get_last_comp_winner(cl_two);
	cl_two_winner->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
	cl_two_winner->ClubEuroSeeding = 2;
	int extra_v2 = find(asia_west.begin(), asia_west.end(), cl_two_winner->ClubNation->NationID) == asia_west.end();

	// Remaining teams
	// Groups, 1QR
	BYTE quals_1[2] = { 3,1 };
	BYTE quals_2[2] = { 3,0 };
	BYTE quals_3[2] = { 2,0 };
	BYTE quals_4[2] = { 1,1 };
	BYTE quals_5[2] = { 1,0 };
	BYTE quals_6[2] = { 0,1 };
	BYTE quals_7[2] = { 0,0 };

	for (int a = 0; a < 2; a++) {
		vector<DWORD> v;
		if (a == 0) v = west_asia_nations();
		else v = east_asia_nations();
		size_t tmp;
		int extra_quals1;
		int extra_quals_same0 = v.size();
		bool extra_top = false;

		// used to add an extra direct slot to the CL2 winner's country (the winner takes the original playoff slot)
		if (extra_v2 == a) tmp = distance(v.begin(), find(v.begin(), v.end(), cl_two_winner->ClubNation->NationID));
		else tmp = v.size();
		// for nations with no playoff slots originally, need to move a slot from top-ranked nation to direct instead - flag number as negative
		if (tmp == 2 || tmp == 3 || tmp == 5 || (tmp > 6 && tmp < v.size())) extra_quals1 = tmp * -1;
		else extra_quals1 = tmp;
		// if both clubs are from the same region
		if (extra_v1 == extra_v2) {
			// highest rated nation in the opposite region gains 1 extra spot
			extra_top = (extra_v1 != a);
			// checking inside the same region
			if (!extra_top) {
				extra_quals_same0 = distance(v.begin(), find(v.begin(), v.end(), cl_elite_winner->ClubNation->NationID));
				// if winners are from the same country, need to remove 1 direct slot from them
				if (extra_quals_same0 == abs(extra_quals1));
				// else remove 1 slot from winner's nation
				else
				{
					// if winner's nation has no direct slots (can't remove), then remove from top rated nation
					if (extra_quals_same0 > 5) extra_quals_same0 = 0;
				}
			}
		}

		for (size_t i = 0; i < v.size(); i++) {
			if (i > 6) break;
			cm3_nations* afc_nation = get_country(v[i]);

			BYTE quals[2];
			if (i < 2) copy(begin(quals_1), end(quals_1), begin(quals));
			else if (i < 3) copy(begin(quals_2), end(quals_2), begin(quals));
			else if (i < 4) copy(begin(quals_3), end(quals_3), begin(quals));
			else if (i < 5) copy(begin(quals_4), end(quals_4), begin(quals));
			else if (i < 6) copy(begin(quals_5), end(quals_5), begin(quals));
			else if (i < 7) copy(begin(quals_6), end(quals_6), begin(quals));
			else copy(begin(quals_7), end(quals_7), begin(quals));
			if (extra_top && i == 0) quals[0]++;
			if (extra_quals1 < 0 && i == 0) {
				quals[0]++;
				quals[1]--;
			}
			else if (i == extra_quals1)
			{
				quals[0]++;
				quals[1]--;
			}
			if (i == extra_quals_same0) quals[0]--;

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
							if (i < 2) required = 4;
							else if (i < 3) required = 3;
							else if (i < 5) required = 2;
							else if (i < 7) required = 1;
							else required = 0;
							if (extra_top && i == 0) required++;
							if (i == extra_quals_same0) required--;
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
						bool valid = false;
						if (cup_winner && cup_winner->ClubNation == afc_nation) {
							int old_count = count;
							int old_seeding = curr_seeding;
							if (j >= count) {
								for (int x = curr_seeding; x < 2; x++) {
									count += quals[x];
									curr_seeding = x + 1;
									if (quals[x] > 0) break;
								}
								if (curr_seeding > 2) break;
							}
							if (cup_winner->ClubEuroFlag == -1 || (cup_winner->ClubEuroFlag == AFC_CHAMPIONS_LEAGUE_ELITE_9CF() && cup_winner->ClubEuroSeeding > curr_seeding))
							{
								//dprintf("Setting club %s to Champions League Elite (cup winner)\n", (cup_winner->ClubName));
								if (cup_winner->ClubEuroFlag != -1) quals[1]++;
								cup_winner->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
								cup_winner->ClubEuroSeeding = curr_seeding;
								j++;
								valid = true;
							}
							else {
								count = old_count;
								curr_seeding = old_seeding;
							}
						}
						if (!valid) {
							cm3_clubs* cup_loser = get_last_comp_runner_up(playable.main_cup);
							if (cup_loser && cup_loser->ClubNation == afc_nation) {
								int old_count = count;
								int old_seeding = curr_seeding;
								if (j >= count) {
									for (int x = curr_seeding; x < 2; x++) {
										count += quals[x];
										curr_seeding = x + 1;
										if (quals[x] > 0) break;
									}
									if (curr_seeding > 2) break;
								}
								if (cup_loser->ClubEuroFlag == -1 || (cup_loser->ClubEuroFlag == AFC_CHAMPIONS_LEAGUE_ELITE_9CF() && cup_loser->ClubEuroSeeding > curr_seeding))
								{
									//dprintf("Setting club %s to Champions League Elite (cup loser)\n", (cup_loser->ClubName));
									if (cup_loser->ClubEuroFlag != -1) quals[1]++;
									cup_loser->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
									cup_loser->ClubEuroSeeding = curr_seeding;
									j++;
									valid = true;
								}
								else {
									count = old_count;
									curr_seeding = old_seeding;
								}
							}
						}
					}
				}
			}

			//dprintf("[CLE] (%s) seeds: [%d, %d]\n", afc_nation->NationNameShort, quals[0], quals[1]);
			required = quals[0] + quals[1];
			//if (j < required) dprintf("[CLE] (%s) Getting clubs from database - best\n", afc_nation->NationNameShort);
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
				int old_count = count;
				int old_seeding = curr_seeding;
				if (j >= count) {
					for (int x = curr_seeding; x < 2; x++) {
						count += quals[x];
						curr_seeding = x + 1;
						if (quals[x] > 0) break;
					}
					if (curr_seeding > 2) break;
				}
				if (afc_club->ClubEuroFlag == -1 || (afc_club->ClubEuroFlag == AFC_CHAMPIONS_LEAGUE_ELITE_9CF() && afc_club->ClubEuroSeeding > curr_seeding))
				{
					//dprintf("Setting club %s to Champions League Elite, seed=%d\n", (afc_club->ClubName), curr_seeding);
					if (afc_club->ClubEuroFlag != -1) 
					{
						quals[1]++;
						required++;
					}
					afc_club->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
					afc_club->ClubEuroSeeding = curr_seeding;
				}
				else {
					count = old_count;
					curr_seeding = old_seeding;
					j--;
				}
				//dprintf("Setting club %s to Champions League Elite, seed=%d\n", (afc_club->ClubName), curr_seeding);
				//afc_club->ClubEuroFlag = AFC_CHAMPIONS_LEAGUE_ELITE_9CF();
				//afc_club->ClubEuroSeeding = curr_seeding;
				clubs.erase(clubs.begin() + idx);
				max_count--;
			}
		}
	}
}

void afc_champions_league_elite_all_teams(BYTE* _this) {
	afc_cl_elite_team_selection();

	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 36;
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	DWORD teams_r1 = 0;
	DWORD teams_r2 = 0;
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == AFC_CHAMPIONS_LEAGUE_ELITE_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			if (seed == 1 && teams_r1 < 28) {
				teams[teams_r1].club = club;
				teams[teams_r1].f5 = 7;
				teams[teams_r1].f6 = 0;
				teams_r1++;
			}
			else if (seed == 2 && teams_r2 < 8) {
				teams[teams_r2 + 28].club = club;
				teams[teams_r2 + 28].f5 = 8;
				teams[teams_r2 + 28].f6 = 0;
				teams_r2++;
			}
		}
	}
}

void afc_champions_league_elite_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 8;
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
		for (int i = 16; i < 32; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], i + (i + 1) % 2);
		}
		for (int i = 32; i < 36; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 33);
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
		if (current != 1) ret_current = 33;
		if (min != 1) ret_min = 33;
		if (max == 1) ret_max = 32;
		else ret_max = 33;
	}
	else if (stage < 2) {
		ret_current = 1 + 2 * (current - 1);
		if (min < 9) ret_min = 1;
		else ret_min = 1 + 2 * (min - 1);
		if (max < 9) ret_max = 9;
		else ret_max = 1 + 2 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 2) {
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

	char prom_rel[4] = { 8, 0, 0, 0 };
	char tiebreaks[4] = { GoalDifferenceTiebreaker, GoalsForTiebreaker, GamesWonTiebreaker, NoTiebreaker };

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

	sort(clubs.begin(), clubs.end(), compareClubAsiaWestEast);

	char matchups[16][8] = {
		{7, 15, -11, 6, -15, -10, -2, 2},
		{-6, 12, -10, 7, -14, 10, 0, -4},
		{6, -14, -12, 4, 15, -9, 3, -1},
		{4, -15, -9, -6, 12, 11, -3, 1},
		{-4, -9, 15, -3, 11, 13, 6, -6},
		{1, -12, -14, 3, -10, 12, -8, 4},
		{-3, 10, 14, -1, 8, -16, -5, 7},
		{-1, 9, 12, -2, 10, -15, 5, -7},
		{-13, 4, 3, -16, -7, 2, -12, 9},
		{13, -8, 1, -13, 5, 0, -11, -9},
		{14, -7, 0, 13, -8, -2, 9, -12},
		{-16, 5, 2, -15, -5, -4, 8, 10},
		{8, -2, -8, 9, -4, -6, 15, 14},
		{-10, 2, 5, -11, 1, -5, 14, -16},
		{-11, 3, -7, 11, 0, 7, -14, -13},
		{11, -1, -5, 8, -3, 6, -13, 13},
	};

	WORD group_teams = 16;
	for (char al = 0; al < 2; al++) {
		//dprintf("-- SETUP GROUP %d --\n", al + 1);
		int start = group_teams * al;
		int end = group_teams * (al + 1);
		sort(clubs.begin() + start, clubs.begin() + end, compareClubAFCElite);
		//for (int i = start; i < end; i++) dprintf("POT %d: %s\n", (i - start) / 4 + 1, clubs[i]->ClubNameShort);

		map<cm3_nations*, vector<cm3_clubs*>> pot_nations;
		map<cm3_nations*, int> pot_nations_c;
		vector<cm3_nations*> pot_nations_list;
		for (size_t t = 0; t < group_teams; t++) {
			cm3_clubs* club = clubs[start + t];
			if (pot_nations.find(club->ClubNation) == pot_nations.end()) {
				pot_nations_c[club->ClubNation] = 0;
				pot_nations[club->ClubNation] = vector<cm3_clubs*>();
				pot_nations_list.push_back(club->ClubNation);
			}
			pot_nations[club->ClubNation].push_back(club);
			pot_nations_c[club->ClubNation]++;
		}
		for (size_t i = 0; i < pot_nations_list.size(); i++) {
			cm3_nations* n1 = pot_nations_list[i];
			//dprintf("Checking nation: %s, list size=%d\n", n1->NationNameShort, pot_nations[n1].size());
			if (pot_nations[n1].size() > 4 || (pot_nations[n1].size() > 0 && pot_nations[n1].size() < 3)) {
				cm3_clubs* popped = pot_nations[n1][pot_nations[n1].size() - 1];
				pot_nations[n1].pop_back();
				for (size_t j = 0; j < pot_nations_list.size(); j++) {
					if (j == i) continue;
					cm3_nations* n2 = pot_nations_list[j];
					//dprintf("Trying to add to nation: %s, list size=%d\n", n2->NationNameShort, pot_nations[n2].size());
					if (pot_nations[n2].size() > 0 && pot_nations[n2].size() < 4) {
						pot_nations[n2].push_back(popped);
						i = 0;
						break;
					}
				}
			}
		}
		vector<cm3_clubs*> clubs_tmp;
		for (size_t i = 0; i < pot_nations_list.size(); i++) {
			cm3_nations* n1 = pot_nations_list[i];
			//dprintf("-- %s\n", n1->NationNameShort);
			vector<cm3_clubs*> cv = pot_nations[n1];
			for (size_t j = 0; j < cv.size(); j++)
			{
				//dprintf("* %s\n", cv[j]->ClubNameShort);
				clubs_tmp.push_back(cv[j]);
			}
		}

		vector<cm3_clubs*> clubs_pots;
		for (int i = 0; i < 4; i++)
		{
			clubs_pots.push_back(clubs_tmp[i]);
			clubs_pots.push_back(clubs_tmp[i + 4]);
			clubs_pots.push_back(clubs_tmp[i + 8]);
			clubs_pots.push_back(clubs_tmp[i + 12]);
		}
		shuffle(clubs_pots.begin(), clubs_pots.begin() + 4, rng);
		shuffle(clubs_pots.begin() + 4, clubs_pots.begin() + 8, rng);
		shuffle(clubs_pots.begin() + 8, clubs_pots.begin() + 12, rng);
		shuffle(clubs_pots.begin() + 12, clubs_pots.end(), rng);

		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, al + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

		//dprintf("-- POTS GROUP %d --\n", al + 1);
		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs_pots[j];
			//dprintf("POT %d: %s [%s]\n", j / 4 + 1, club->ClubNameShort, club->ClubNation->NationNameThreeLetter);
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			AddToClubIncome((BYTE*)ret, prizeMoneyFile.GetInt("afc_cl_elite_groups_qualify"));
			AddMoneyFromComp(_this, (BYTE*)club, prizeMoneyFile.GetInt("afc_cl_elite_groups_qualify"), 0, -1, LeagueStage, 0, -2);
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 0, (DWORD)(comp_data->competition_db), 0, num_rounds,
			3, 1, 8, &tiebreaks[0], &prom_rel[0], year, al + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);

		*((WORD*)(pStage + 0xA7)) = num_rounds;
		comp_stats* stage_data = (comp_stats*)pStage;

		int n_tries = 0;
		for (BYTE t = 0; t < group_teams; t++) {
			cm3_clubs* club = clubs_pots[t];
			map<cm3_nations*, int> counts;
			for (BYTE m = 0; m < num_rounds; m++) {
				char idx = matchups[t][m];
				if (idx < 0) idx = abs(idx) - 1;
				cm3_clubs* opp = clubs_pots[idx];
				bool multiple = false;
				if (n_tries > 255)
				{
					//if (n_tries == 512 && m == 0) dprintf("[CLE] Tried to make draw without teams from the same country facing each other, but failed.\n");
					multiple = pot_nations_c[club->ClubNation] > 2;
				}
				if (n_tries > 511)
				{
					//if (n_tries == 1024 && m == 0) dprintf("[CLE] Tried to make draw without teams from the same country facing each other, but failed.\n");
					multiple = pot_nations_c[club->ClubNation] > 1;
				}

				if (!multiple)
				{
					if (opp->ClubNation == club->ClubNation) {
						//if (n_tries > 255) dprintf("** FAILED ** clubs: %s [%d] vs %s [%d]\n", club->ClubNameShort, t, opp->ClubNameShort, idx);
						if (idx % 4 < 3) {
							iter_swap(clubs_pots.begin() + idx, clubs_pots.begin() + idx + 1);
						}
						else {
							auto it = clubs_pots.begin() + idx;
							rotate(clubs_pots.begin() + idx / 4 * 4, it, it + 1);
						}
						t = -1;
						n_tries++;
						break;
					}
				}
				if (counts.find(opp->ClubNation) != counts.end()) {
					int count = counts[opp->ClubNation];
					if (opp->ClubNation == club->ClubNation && count > 0 + multiple) {
						shuffle(clubs_pots.begin(), clubs_pots.begin() + 4, rng);
						if (idx > 3) shuffle(clubs_pots.begin() + 4, clubs_pots.begin() + 8, rng);
						if (idx > 7) shuffle(clubs_pots.begin() + 8, clubs_pots.begin() + 12, rng);
						if (idx > 11) shuffle(clubs_pots.begin() + 12, clubs_pots.end(), rng);
						t = -1;
						n_tries++;
						break;
					}
					else counts[opp->ClubNation] = count + 1;
				}
				else counts[opp->ClubNation] = 1;
			}
		}

		for (BYTE m = 0; m < num_rounds; m++) {
			BYTE* ptr_last = (BYTE*)(pFixtures + fixture_dates_sz * 7);
			match_data* match = new match_data();
			match->comp_id = comp_data->competition_db->ClubCompID;
			match->f8 = -1;
			match->comp = comp_data->competition_db;
			match->end_year = year + *(WORD*)(ptr_last + 2);
			match->end_day = *(WORD*)(ptr_last);
			match->current_year = year;
			match->sub_stage_id = 0;
			match->main_stage_id = stage_name_id;
			match->f54_0xdb = stage_data->f219;
			match->f56_0xab = stage_data->f171;
			match->f58_0xc4 = stage_data->f196;
			match->f59 = -1;
			match->f61 = 0;
			match->f62 = 0;
			match->f64 = 1;
			match->f65 = 1;
			match->stage_number = al + stage_num;
			match->goals_home2 = -1;
			match->goals_away2 = -1;
			match->f69 = -1;
			match->f70 = -1;
			match->goals_home1 = -1;
			match->goals_away1 = -1;
			match->f73 = -1;
			match->f74 = -1;
			match->f75 = -1;
			match->f76 = -1;
			match->subs = 0x59; // force 9/5 subs

			vector<pair<char, char>> matchup_pairs;
			for (char t = 0; t < group_teams; t++) {
				char p1 = t;
				char p2 = matchups[t][m];
				if (p2 < 0) {
					p1 = abs(p2) - 1;
					p2 = t;
				}
				pair<char, char> match = make_pair(p1, p2);
				if (find(matchup_pairs.begin(), matchup_pairs.end(), match) == matchup_pairs.end())
					matchup_pairs.push_back(match);
			}

			for (int t = 0; t < group_teams / 2; t++) {
				cm3_clubs* home = clubs_pots[matchup_pairs[t].first];
				cm3_clubs* away = clubs_pots[matchup_pairs[t].second];
				BYTE* ptr = (BYTE*)(pFixtures + fixture_dates_sz * m);
				match->home_team_id = home->ClubID;
				match->away_team_id = away->ClubID;
				match->home_team = home;
				match->away_team = away;
				match->fixture_year = year + *(WORD*)(ptr + 2);
				match->fixture_day = *(WORD*)(ptr);
				match->fixture_number = m;
				match->f63 = *(BYTE*)(ptr + 4);

				sub_85C260((BYTE*)*(DWORD*)0xDD7EF4, *(DWORD*)(ptr + 0x3D), (BYTE*)match, comp_data->f36);
				sub_5AA680((BYTE*)*(DWORD*)0xAE2A58, (BYTE*)match, 1);
			}
		}

		*((DWORD*)(&stages_arr[al + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = al + stage_num;
	}
}

void afc_champions_league_elite_final_stage_setup(BYTE* _this) {
	char stage_num = 2;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	comp_stats* curr_stage = comp_data;

	vector<cm3_clubs*> clubs;
	for (char al = 0; al < 2; al++) {
		curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < curr_stage->n_teams; i++) {
			if (table_teams[i].league_fate == Qualified1) clubs.push_back(table_teams[i].club);
		}
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
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)(comp_data->competition_db), pFixtures, year, stage_num, 2, stage_name_id, 0x14, 1, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	comp_data->current_stage = (long)stage_num;
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
		else if (current == 2) {
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
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueStage, 0x1E);
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

				staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(cl2_data->competition_db), None, LeagueStage, 0x1E);
				(*(int(__thiscall**)(BYTE*))(v2 + 0x5C))(cl2_bytes);
			}
			else club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage < 2) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RoundOf16, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, LeagueStage, 0xF);
			club->ClubEuroFlag = -1;
			return 0;
		}
	}
	else if (stage == 2) {
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
	else if (stage_id < 2) {
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
	else if (stage_id == 2) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

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
	data->num_stages = 3;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	afc_champions_league_elite_all_teams(_this);
	afc_champions_league_elite_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
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

	char* west_league = "West League Phase";
	char* west_league_short = "W Lge Phase";
	WriteDWORD(0x4B562E + 1, (DWORD)&west_league[0]);
	WriteDWORD(0x4B8555 + 1, (DWORD)&west_league_short[0]);
	char* east_league = "East League Phase";
	char* east_league_short = "E Lge Phase";
	WriteDWORD(0x4B6881 + 1, (DWORD)&east_league[0]);
	WriteDWORD(0x4B93D3 + 1, (DWORD)&east_league_short[0]);
}