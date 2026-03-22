#include <windows.h>
#include <filesystem>
#include <fstream>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

using namespace std;

vtable* afc_challenge_league_vtable = new vtable((BYTE*)0x967574, 0xA0);

void afc_challenge_league_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(afc_challenge_league_vtable->vtable_ptr);
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

void afc_challenge_league_free(BYTE* _this, BYTE a2) {
	afc_challenge_league_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) afc_challenge_league_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call afc_challenge_league_free
		add esp, 0x8
		ret 4
	}
}

DWORD afc_challenge_league_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 0, FixedTeamOrderInCup + ExtraTimePenalties_1, NoTiebreak_2, 8, 20, 10, 20, 0, 0, 1, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx < 5) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = AlphabeticGroupStage + stage_idx - 1;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		if (stage_idx < 3) {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 28), year, Tuesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 31), year, Friday, Evening);
		}
		else {
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 26), year, Sunday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 29), year, Wednesday, Evening);
			AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 1), year, Saturday, Evening);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 5) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 5), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 8, 4, 8, 0, 0, 2, 7, 59480);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 13), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 9), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 8, 4, 2, 0, 0, 0, 2, 7, 89219);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 17), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 9), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 8, 2, 1, 0, 0, 0, 1, 0, 0, 743494, 371747);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) afc_challenge_league_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call afc_challenge_league_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int afc_challenge_league_set_champion(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* stage_data_for_history = (BYTE*)comp_data->stages[5];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);
}

void __declspec(naked) afc_challenge_league_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call afc_challenge_league_set_champion
		add esp, 0x4
		ret 0
	}
}

void afc_challenge_team_selection() {
	// Groups, 1QR
	BYTE quals_1[2] = { 1,0 };
	BYTE quals_2[2] = { 0,1 };

	for (int a = 0; a < 2; a++) {
		vector<string> v;
		if (a == 0) v = asia_west;
		else v = asia_east;
		for (size_t i = 10; i < v.size(); i++) {
			cm3_nations* afc_nation = find_country(v[i].c_str());

			BYTE* quals;
			if ((a == 0 && i < 15) || (a == 1 && i < 11)) quals = quals_1;
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
			if (filesystem::exists("Data/afc.cfg") && *current_year == (WORD)2025) {
				ifstream in("Data/afc.cfg", ios_base::in);
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
						if (_strcmpi(nation, afc_nation->NationName) == 0)
						{
							required = 1;
							//dprintf("[ChL] Getting clubs from afc.cfg: %s - max %d\n", nation, required);
						}
						else {
							required = -1;
						}
						continue;
					}
					if (_strcmpi(nation, afc_nation->NationName) != 0) continue;
					if (j >= required) continue;
					cm3_clubs* afc_club = find_club(name.c_str());
					if (!afc_club || !afc_club->ClubNation || afc_club->ClubNation != afc_nation) {
						//dprintf("Club %s not found, skipping\n", name.c_str());
					}
					else if (afc_club->ClubEuroFlag != -1) {
						//dprintf("Club %s is already in a AFC competition, skipping\n", (afc_club->ClubName));
					}
					else {
						//dprintf("Setting club %s to Challenge League\n", (afc_club->ClubName));
						afc_club->ClubEuroFlag = AFC_CHALLENGE_LEAGUE_9CF();
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
			else if (i < 12 && afc_nation->NationLeagueSelected) {
				DWORD max_playables = pnd_count;
				for (DWORD i = 0; i < max_playables; i++) {
					playable_nation_data playable = pnd_list[i];
					if (playable.nation == afc_nation && playable.main_cup) {
						cm3_clubs* cup_winner = get_last_comp_winner(playable.main_cup);
						if (cup_winner && cup_winner->ClubNation == afc_nation && cup_winner->ClubEuroFlag == -1) {
							cup_winner->ClubEuroFlag = AFC_CHALLENGE_LEAGUE_9CF();
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
								cup_loser->ClubEuroFlag = AFC_CHALLENGE_LEAGUE_9CF();
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

			required = 1;
			//if (j < required) dprintf("[CL2] Getting clubs from database - best\n");
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
				//dprintf("Setting club %s to Challenge League\n", (afc_club->ClubName));
				afc_club->ClubEuroFlag = AFC_CHALLENGE_LEAGUE_9CF();
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

void afc_challenge_league_all_teams(BYTE* _this) {
	afc_challenge_team_selection();

	comp_stats* data = (comp_stats*)_this;

	WORD total_teams_in_comp = 30;
	data->special_nteams_seedings = 26;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;
	DWORD teams_r1 = 0;
	DWORD teams_r2 = 0;
	for (DWORD i = 0; i < *clubs_count; i++) {
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubEuroFlag == AFC_CHALLENGE_LEAGUE_9CF()) {
			BYTE seed = club->ClubEuroSeeding;
			if (seed == 1 && teams_r1 < 6) {
				teams[teams_r1].club = club;
				teams[teams_r1].f5 = 7;
				teams[teams_r1].f6 = 0;
				teams_r1++;
			}
			else if (seed == 2 && teams_r2 < 20) {
				teams[teams_r2 + 6].club = club;
				teams[teams_r2 + 6].f5 = 8;
				teams[teams_r2 + 6].f6 = 0;
				teams_r2++;
			}
		}
	}
}

void afc_challenge_league_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 20;
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
	shuffle(qual_clubs.begin(), qual_clubs.begin() + 10, rng);
	shuffle(qual_clubs.begin() + 10, qual_clubs.end(), rng);
	for (WORD i = 0; i < qual_clubs.size(); i++) {
		teams[i].club = qual_clubs[i];
		teams[i].f5 = i % 2;
		teams[i].f6 = 0;
	}
}

void afc_challenge_league_reputation_setup(BYTE* _this) {
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
		for (int i = 8; i < 10; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 9);
		}
		for (int i = 10; i < 15; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 11);
		}
		for (int i = 15; i < 20; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 16);
		}
		for (int i = 20; i < 30; i++) {
			if (i >= comp_data->special_nteams_seedings) return;
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 21);
		}
	}
}

void __declspec(naked) afc_challenge_league_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call afc_challenge_league_reputation_setup
		add esp, 0x4
		ret
	}
}

void afc_challenge_league_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		if (current != 1) ret_current = 21;
		if (min != 1) ret_min = 21;
		if (max == 1) ret_max = 16;
		else ret_max = 21;
	}
	else if (stage < 5) {
		ret_current = 1 + 5 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 5 * (min - 1);
		if (max < 3) ret_max = 9;
		else ret_max = 1 + 5 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	else if (stage == 5) {
		// do nothing
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) afc_challenge_league_reputation_calc_c()
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
		call afc_challenge_league_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

char afc_challenge_league_update(BYTE* _this) {
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
	afc_challenge_league_all_teams(_this);
	afc_challenge_league_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) afc_challenge_league_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call afc_challenge_league_update
		add esp, 0x4
		ret
	}
}

void afc_challenge_league_group_stage_setup(BYTE* _this) {
	char stage_num = 0;
	DWORD v1 = *(DWORD*)_this;
	BYTE* ae2a38_ptr = (BYTE*)*ae2a38;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	BYTE prom_rel[4] = { 1, 0, 0, 0 };
	BYTE tiebreaks[4] = { CurrentPositionTiebreaker, GoalDifferenceTiebreaker, GoalsForTiebreaker, NoTiebreaker };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < comp_data->special_nteams_seedings; i++) {
		if (teams[i].club->ClubEuroFlag == comp_data->competition_db->ClubCompID)
			clubs.push_back(teams[i].club);
	}
	if (clubs.size() != 20)
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
	shuffle(clubs.begin() + 16, clubs.end(), rng);

	WORD group_teams = 4;
	for (int i = 0; i < 5; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)sub_944E46_malloc(group_teams * 4);

		int idx = i;
		int mult = 3;
		if (i > 2)
		{
			idx = 12 + (i - 3);
			mult = 2;
			prom_rel[0] = 2;
		}
		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[idx + mult * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
			int ret = sub_5A0590(ae2a38_ptr, (BYTE*)club);
			AddToClubIncome((BYTE*)ret, 74349);
			AddMoneyFromComp(_this, (BYTE*)club, 74349, 0, -1, GroupStage, 0, -2);
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

void afc_challenge_league_final_stage_setup(BYTE* _this) {
	char stage_num = 5;

	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 8;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	vector<cm3_clubs*> clubs;

	// get best second placeds
	vector<team_league_stats> sort_seconds;
	for (char al = 0; al < 3; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		sort_seconds.push_back(table_teams[1]);
	}
	sort(sort_seconds.begin(), sort_seconds.end(), sortTLS);
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	cm3_clubs* second = sort_seconds[0].club;
	for (char al = 0; al < 3; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		team_league_stats tls = table_teams[1];
		if (tls.club == second) {
			table_teams[1].league_fate = Qualified1;
			curr_stage->promotions++;
			staff_history_qualified_86BDD0(staff_hist_ptr, tls.club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
			break;
		}
	}

	for (char al = 0; al < 5; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == Qualified1) {
				clubs.push_back(tls.club);
			}
		}
	}

	BYTE team_order[8] = { 0,2,3,1,4,6,7,5 };
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

	for (char al = 0; al < 5; al++) {
		comp_stats* curr_stage = (comp_stats*)(comp_data->stages[al]);
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate != Qualified1) {
				tls.club->ClubEuroFlag = -1;
			}
		}
	}
}

void afc_challenge_league_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		if (current == 0) {
			BYTE* cl2_bytes = get_loaded_league(AFC_CHAMPIONS_LEAGUE_TWO_9CF());
			if (cl2_bytes) {
				DWORD v1 = *(DWORD*)cl2_bytes;
				char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(cl2_bytes, 0, 1);
				if (ret != 0) {
					comp_data->current_stage = current;
					afc_challenge_league_group_stage_setup(_this);
				}
			}
		}
		else if (current == 5) {
			comp_data->current_stage = current;
			afc_challenge_league_final_stage_setup(_this);
		}
	}
}

void __declspec(naked) afc_challenge_league_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call afc_challenge_league_stages_create
		add esp, 0x4
		ret
	}
}

int afc_challenge_league_set_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
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
	else if (stage < 5) {
		switch (fate) {
		case Qualified1:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, QuarterFinal, 0x1E);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			return 0;
		}
	}
	else if (stage == 5) {
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

void __declspec(naked) afc_challenge_league_set_table_fate()
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
		call afc_challenge_league_set_fates
		add esp, 0x1c
		ret 0x18
	}
}

int afc_challenge_league_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
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
	else if (stage_id < 5) {
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
	else if (stage_id == 5) return sub_48C6D0(_this, club_idx, fate, stage_id, stage_name_idx, round_data, a7, 0, a9, show_body_text, ret_str_ptr);

	return 0;
}

void __declspec(naked) afc_challenge_league_stage_news_c()
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
		call afc_challenge_league_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void afc_challenge_league_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->year = year;
	data->comp_vtable = (DWORD*)(afc_challenge_league_vtable->vtable_ptr);
	afc_challenge_league_vtable->SetPointer(VTableInitFree, (DWORD)&afc_challenge_league_free_c);
	afc_challenge_league_vtable->SetPointer(VTableEoSUpdate, (DWORD)&afc_challenge_league_update_c);
	afc_challenge_league_vtable->SetPointer(VTablePlayoffQual, (DWORD)&afc_challenge_league_stages_create_c);
	afc_challenge_league_vtable->SetPointer(VTableSetChampion, (DWORD)&afc_challenge_league_set_champion_c);
	afc_challenge_league_vtable->SetPointer(VTableClubLandmarks, 0x48cab0);
	afc_challenge_league_vtable->SetPointer(VTableFixtures, (DWORD)&afc_challenge_league_fixture_caller);
	afc_challenge_league_vtable->SetPointer(VTableTableFates, (DWORD)&afc_challenge_league_set_table_fate);
	afc_challenge_league_vtable->SetPointer(VTableStageNews, (DWORD)&afc_challenge_league_stage_news_c);
	afc_challenge_league_vtable->SetPointer(VTableReputationSetup, (DWORD)&afc_challenge_league_reputation_setup_c);
	afc_challenge_league_vtable->SetPointer(VTableReputationCalc, (DWORD)&afc_challenge_league_reputation_calc_c);
	afc_challenge_league_vtable->SetPointer(VTableSubsRounds, 0x858e70);
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 6;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	data->competition_db = comp;
	data->comp_type = CLUB_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->f82 = 3;
	data->max_bench = 9;
	data->max_subs = 5;
	data->rules = 0x29;
	data->f81 = 0xa;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	comp->ClubCompContinent = find_continent("Asia");
	comp->ClubCompBackgroundColour = get_colour(COLOUR_PURPLE_3_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_ORANGE_1_9CF());
	afc_challenge_league_all_teams(_this);
	afc_challenge_league_qualifier_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	afc_challenge_league_reputation_setup(_this);
}

void setup_afc_challenge_league() {
}