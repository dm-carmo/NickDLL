#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>
#include "bra_state_league_list.h"

DWORD* bra_first_vtable = (DWORD*)0x967D98;

void bra_first_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* bra_second = get_loaded_league(BRA_SECOND_9CF());
	v1 = *(DWORD*)bra_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bra_second);
	sub_689C80(_this, _this, bra_second, 1, a2, -1, -1);

	BYTE* bra_third = get_loaded_league(BRA_THIRD_9CF());
	v1 = *(DWORD*)bra_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bra_third);
	sub_689C80(_this, bra_second, bra_third, 1, a2, -1, -1);

	BYTE* bra_fourth = get_loaded_league(BRA_FOURTH_9CF());
	comp_stats* bra_fourth_data = (comp_stats*)bra_fourth;
	v1 = *(DWORD*)bra_fourth;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bra_fourth);
	for (int i = 0; i < 7; i++)
	{
		BYTE* bra_fourth_grp = (BYTE*)bra_fourth_data->stages[i];
		v1 = *(DWORD*)bra_fourth_grp;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bra_fourth_grp);
	}

	sub_689C80(_this, bra_third, bra_fourth, 1, a2, -1, -1);
	for (int i = 0; i < 7; i++)
	{
		BYTE* bra_fourth_grp = (BYTE*)bra_fourth_data->stages[i];
		sub_689C80(_this, bra_third, bra_fourth_grp, 1, a2, -1, -1);
	}
}

void __declspec(naked) bra_first_prom_rel_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call bra_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void bra_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GamesWonTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->tiebreaker_4 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 4;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = BRA_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	//call vtable +3C which is actually add fixtures function
	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) bra_first_subs_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call bra_first_subs
		add esp, 0x4
		ret
	}
}

DWORD bra_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * ((comp_stats*)_this)->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 12), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 16), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 3), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 10), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 17), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 12), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 12), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 16), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 23), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 1), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 15), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 5), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 19), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 7), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) bra_first_fixtures_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call bra_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void bra_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = bra_first_vtable;
	data->year = year;
	data->rules = 0x7;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_BROWN_2_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_BLUE_1_9CF());
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	bra_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = add_prize_money_682F70(_this, 168750);
	data->f225 = 1;
	add_tv_money_683010(_this, 1912500, 0);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	reputation_setup_generic_68A850(_this);
}

void __fastcall bra_promotion_to_fourth(BYTE* _this) {
	cm3_club_comps* bra_fourth = get_comp(BRA_FOURTH_9CF());
	vector<cm3_clubs*> d_clubs = find_clubs_of_comp(BRA_FOURTH_9CF());
	for (cm3_clubs* c : d_clubs) {
		if (!c->ClubLastDivision || c->ClubLastDivision->ClubCompID != BRA_THIRD_9CF()) {
			c->ClubDivision = get_comp(A_LOWER_9CF());
		}
		//else dprintf("Club %s was relegated from Série C, they will play in Série D next season!\n", c->ClubNameShort);
	}
	BYTE state_counts[12] = { 4,4,4,9,4,4,4,9,6,4,4,4 };
	for (size_t i = 0; i < state_leagues.size(); i++) {
		comp_stats* league = (comp_stats*)get_loaded_league(state_leagues[i]);
		cm3_club_comps* lower = get_comp(state_lower[i]);
		BYTE count = state_counts[i];
		if (league && lower) {
			//dprintf("Getting %d teams from league: %s\n", count, league->competition_db->ClubCompNameShort);
			team_league_stats* table = (team_league_stats*)league->team_league_table;
			for (WORD j = 0; j < league->n_teams && count > 0; j++) {
				cm3_clubs* club = table[j].club;
				if (!club->ClubDivision || club->ClubDivision->ClubCompID == A_LOWER_9CF()) {
					//dprintf("- Club %s has qualified to Série D! (finished %d)\n", club->ClubNameShort, j + 1);
					club->ClubDivision = bra_fourth;
					count--;
				}
			}
			if (count > 0) {
				vector<cm3_clubs*> lower_teams = find_clubs_of_comp_reserve_division(state_lower[i]);
				sort(lower_teams.begin(), lower_teams.end(), compareClubRep);
				for (WORD j = 0; j < lower_teams.size() && count > 0; j++) {
					cm3_clubs* club = lower_teams[j];
					if (!club->ClubDivision || club->ClubDivision->ClubCompID == A_LOWER_9CF()) {
						//dprintf("- Club %s has qualified to Série D! (from lower leagues)\n", club->ClubNameShort);
						club->ClubDivision = bra_fourth;
						count--;
					}
				}
			}
		}
		//else dprintf("State league %d not found!\n", i);
	}
	WORD current_team_count = CountNumberOfTeamsInComp(BRA_FOURTH_9CF());
	sort(d_clubs.begin(), d_clubs.end(), compareClubRep);
	int k = 0;
	while (current_team_count < 64) {
		cm3_clubs* backup = d_clubs[k++];
		if (!backup->ClubDivision || backup->ClubDivision->ClubCompID == A_LOWER_9CF()) {
			//dprintf("Not enough teams from state leagues, club %s was selected to stay in Série D\n", backup->ClubNameShort);
			backup->ClubDivision = bra_fourth;
			current_team_count++;
		}
	}
	for (cm3_clubs* c : d_clubs) {
		if (!c->ClubDivision || c->ClubDivision->ClubCompID == A_LOWER_9CF())
			trigger_relegation_clauses_4CD030((BYTE*)*ae1050, c, bra_fourth);
	}
}

void __fastcall bra_state_leagues_update(BYTE* _this) {
	for (size_t i = 0; i < state_leagues.size(); i++) {
		comp_stats* league = (comp_stats*)get_loaded_league(state_leagues[i]);
		if (league) {
			vector<cm3_clubs*> relegated = get_relegated_teams(state_leagues[i]);
			vector<cm3_clubs*> lower_teams = find_clubs_of_comp_reserve_division(state_lower[i]);
			sort(lower_teams.begin(), lower_teams.end(), compareClubRep);

			int max_to_check = (lower_teams.size() > 5 ? 5 : lower_teams.size());
			for (size_t i = 0; i < relegated.size(); i++)
			{
				int availableIdx = rand() % (max_to_check - i);
				cm3_clubs* clubToRelegate = relegated[i];
				cm3_clubs* available = lower_teams[availableIdx];
				//dprintf("Swapping Teams: %s (%s) <-> %s (%s)\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, available->ClubName, available->ClubDivision->ClubCompName);

				cm3_club_comps* topDivision = clubToRelegate->ClubReserveDivision;
				cm3_club_comps* bottomDivision = available->ClubReserveDivision;
				clubToRelegate->ClubReserveDivision = bottomDivision;
				available->ClubReserveDivision = topDivision;

				trigger_relegation_clauses_4CD030((BYTE*)*ae1050, clubToRelegate, topDivision);

				lower_teams.erase(lower_teams.begin() + availableIdx);
			}
		}
	}
}

void __fastcall bra_update_managers(BYTE* _this) {
	vector<cm3_clubs*> bra_clubs = find_clubs_of_country(NATION_BRAZIL_9CF());
	int i = 0;
	for (cm3_clubs* c : bra_clubs) {
		if ((!c->ClubDivision || !get_loaded_league(c->ClubDivision->ClubCompID)) &&
			(!c->ClubReserveDivision || !get_loaded_league(c->ClubReserveDivision->ClubCompID))) {
			fire_manager_relegation_to_unplayable_69B790((BYTE*)*b67a44, c, 1, 7, 0);
		}
	}
}

void __fastcall bra_qualify_teams_for_cup(BYTE* _this) {
	WORD total_teams = 92;
	comp_stats* cup_data = (comp_stats*)get_loaded_league(BRA_CUP_9CF());
	if (!cup_data) return;
	if (cup_data->special_teams_seedings) {
		sub_9452CA_free(cup_data->special_teams_seedings);
		cup_data->special_teams_seedings = 0;
	}
	//cup_data->special_nteams_seedings = total_teams;
	// third phase: libertadores teams + winner d2 +  winner cup + best d1
	vector<cm3_clubs*> third_phase;
	vector<cm3_clubs*> first_phase;
	vector<cm3_clubs*> bra_clubs = find_clubs_of_country(NATION_BRAZIL_9CF());
	for (cm3_clubs* c : bra_clubs) {
		if (c->ClubEuroFlag == COPA_LIBERTADORES_9CF()) {
			//dprintf("Club %s has qualified for Copa do Brasil third round! (in Libertadores)\n", c->ClubNameShort);
			third_phase.push_back(c);
		}
	}
	cm3_clubs* cup_winner = get_last_comp_winner(get_comp(BRA_CUP_9CF()));
	if (cup_winner && !vector_contains_club(third_phase, cup_winner))
	{
		//dprintf("Club %s has qualified for Copa do Brasil third round! (last cup winner)\n", cup_winner->ClubNameShort);
		third_phase.push_back(cup_winner);
	}
	cm3_clubs* b_winner = get_last_comp_winner(get_comp(BRA_SECOND_9CF()));
	if (b_winner && !vector_contains_club(third_phase, b_winner))
	{
		//dprintf("Club %s has qualified for Copa do Brasil third round! (Série B winner)\n", b_winner->ClubNameShort);
		third_phase.push_back(b_winner);
	}
	// Serie A
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(BRA_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);
	for (WORD i = 0; i < division_clubs.size(); i++) {
		if (vector_contains_club(third_phase, division_clubs[i])) continue;
		if (third_phase.size() < 12)
		{
			//dprintf("Club %s has qualified for Copa do Brasil third round! (from Série A)\n", division_clubs[i]->ClubNameShort);
			third_phase.push_back(division_clubs[i]);
		}
		else
		{
			//dprintf("Club %s has qualified for Copa do Brasil first round! (from Série A)\n", division_clubs[i]->ClubNameShort);
			first_phase.push_back(division_clubs[i]);
		}
	}
	// Serie B
	division_clubs = find_clubs_of_comp(BRA_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);
	for (WORD i = 0; i < division_clubs.size(); i++) {
		if (vector_contains_club(third_phase, division_clubs[i])) continue;
		//dprintf("Club %s has qualified for Copa do Brasil first round! (from Série B)\n", division_clubs[i]->ClubNameShort);
		first_phase.push_back(division_clubs[i]);
	}
	// Serie C
	division_clubs = find_clubs_of_comp(BRA_THIRD_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPos);
	for (WORD i = 0; i < division_clubs.size(); i++) {
		if (vector_contains_club(third_phase, division_clubs[i])) continue;
		//dprintf("Club %s has qualified for Copa do Brasil first round! (from Série C)\n", division_clubs[i]->ClubNameShort);
		first_phase.push_back(division_clubs[i]);
	}
	BYTE state_counts[12] = { 2,2,2,6,2,2,2,5,3,2,2,2 };
	for (size_t i = 0; i < state_leagues.size(); i++) {
		comp_stats* league = (comp_stats*)get_loaded_league(state_leagues[i]);
		cm3_club_comps* lower = get_comp(state_lower[i]);
		BYTE count = state_counts[i];
		if (league && lower) {
			//dprintf("Getting %d teams from league: %s\n", count, league->competition_db->ClubCompNameShort);
			team_league_stats* table = (team_league_stats*)league->team_league_table;
			for (WORD j = 0; j < league->n_teams && count > 0; j++) {
				cm3_clubs* club = table[j].club;
				if (vector_contains_club(third_phase, club) ||
					vector_contains_club(first_phase, club)) continue;
				//dprintf("- Club %s has qualified to Copa do Brasil! (finished %d)\n", club->ClubNameShort, j + 1);
				first_phase.push_back(club);
				count--;
			}
			if (count > 0) {
				vector<cm3_clubs*> lower_teams = find_clubs_of_comp_reserve_division(state_lower[i]);
				sort(lower_teams.begin(), lower_teams.end(), compareClubRep);
				for (WORD j = 0; j < lower_teams.size() && count > 0; j++) {
					cm3_clubs* club = lower_teams[j];
					if (vector_contains_club(third_phase, club) ||
						vector_contains_club(first_phase, club)) continue;
					//dprintf("- Club %s has qualified to Copa do Brasil! (from lower leagues)\n", club->ClubNameShort);
					first_phase.push_back(club);
					count--;
				}
			}
		}
		//else dprintf("State league %d not found!\n", i);
	}
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);
	cup_data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)cup_data->special_teams_seedings;

	size_t i;
	for (i = 0; i < first_phase.size(); i++)
	{
		teams[i].club = first_phase[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}
	for (size_t j = 0; i < total_teams && j < third_phase.size(); i++, j++)
	{
		teams[i].club = third_phase[j];
		teams[i].f5 = 3;
		teams[i].f6 = 0;
	}
}

char bra_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	DWORD v1 = *(DWORD*)_this;
	(*(void(__thiscall**)(BYTE*, int))(v1 + 0xB0))(_this, 1);
	bra_qualify_teams_for_cup(_this);
	bra_promotion_to_fourth(_this);
	bra_state_leagues_update(_this);
	bra_update_managers(_this);

	sub_687970(_this, ebx);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
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
	data->year++;
	data->current_stage = -1;
	bra_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = add_prize_money_682F70(_this, 168750);
	data->f225 = 1;
	add_tv_money_683010(_this, 1912500, 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	BYTE* bra_second = get_loaded_league(BRA_SECOND_9CF());
	BYTE* bra_third = get_loaded_league(BRA_THIRD_9CF());
	BYTE* bra_fourth = get_loaded_league(BRA_FOURTH_9CF());

	v1 = *(DWORD*)bra_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bra_second);

	v1 = *(DWORD*)bra_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bra_third);

	v1 = *(DWORD*)bra_fourth;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bra_fourth);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) bra_first_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call bra_first_update
		add esp, 0x4
		ret
	}
}

void setup_bra_first()
{
	WriteVTablePtr(bra_first_vtable, VTableSubsRounds, (DWORD)&bra_first_subs_c);
	WriteVTablePtr(bra_first_vtable, VTableFixtures, (DWORD)&bra_first_fixtures_c);
	WriteVTablePtr(bra_first_vtable, VTableEoSUpdate, (DWORD)&bra_first_update_c);
	WriteVTablePtr(bra_first_vtable, VTablePromRelUpdate, (DWORD)&bra_first_prom_rel_update_c);
	WriteVTablePtr(bra_first_vtable, VTablePlayoffQual, (DWORD)0x5a8f60);
	WriteVTablePtr(bra_first_vtable, VTableSetChampion, (DWORD)0x684640);
	WriteVTablePtr(bra_first_vtable, VTableTableFates, (DWORD)0x686940);
	WriteVTablePtr(bra_first_vtable, VTableStageNews, (DWORD)0x48c6d0);
	WriteVTablePtr(bra_first_vtable, VTableReputationCalc, (DWORD)0x48e380);
	WriteVTablePtr(bra_first_vtable, VTable37, (DWORD)0x68aad0);
}
