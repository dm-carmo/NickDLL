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
	process_promotion_relegation_689C80(_this, _this, bra_second, 1, a2, -1, -1);

	BYTE* bra_third = get_loaded_league(BRA_THIRD_9CF());
	v1 = *(DWORD*)bra_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bra_third);
	process_promotion_relegation_689C80(_this, bra_second, bra_third, 1, a2, -1, -1);

	BYTE* bra_fourth = get_loaded_league(BRA_FOURTH_9CF());
	comp_stats* bra_fourth_data = (comp_stats*)bra_fourth;
	v1 = *(DWORD*)bra_fourth;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bra_fourth);
	for (int i = 0; i < 15; i++)
	{
		BYTE* bra_fourth_grp = (BYTE*)bra_fourth_data->stages[i];
		v1 = *(DWORD*)bra_fourth_grp;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(bra_fourth_grp);
	}

	process_promotion_relegation_689C80(_this, bra_third, bra_fourth, 1, a2, -1, -1);
	for (int i = 0; i < 15; i++)
	{
		BYTE* bra_fourth_grp = (BYTE*)bra_fourth_data->stages[i];
		process_promotion_relegation_689C80(_this, bra_third, bra_fourth_grp, 1, a2, -1, -1);
	}
}

void __declspec(naked) bra_first_prom_rel_update_c()
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

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) bra_first_subs_c()
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
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 1, 28), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 4), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 11), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 25), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 11), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 15), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 18), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 22), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 2), year, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 5), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 12), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 19), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 26), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 3), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 10), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 17), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 24), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 31), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 22), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 26), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 29), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 23), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 6), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 8), year, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 11), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 28), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 4), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 18), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 2), year, Wednesday, Evening);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) bra_first_fixtures_c()
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
	data->rules = RulesBrazilNational;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 12000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	bra_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("bra_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("bra_first_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void __fastcall bra_promotion_to_fourth(BYTE* _this) {
	cm3_club_comps* bra_fourth = get_comp(BRA_FOURTH_9CF());
	vector<cm3_clubs*> d_clubs = find_clubs_of_comp(BRA_FOURTH_9CF());
	comp_stats* comp_data = (comp_stats*)get_loaded_league(BRA_FOURTH_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 15; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < comp_data->n_teams; i++) {
			if (table[i].club->ClubDivision == bra_fourth && (table[i].league_fate == Eliminated || table[i].league_fate == NoFate))
			{
				//dprintf("Club %s will not play in Série D next season!\n", table[i].club->ClubNameShort);
				table[i].club->ClubDivision = get_comp(A_LOWER_9CF());
			}
			//else if (table[i].league_fate == TopPlayoff) dprintf("Club %s will play in Série D next season!\n", table[i].club->ClubNameShort);
		}
	}
	BYTE state_counts[12] = { 4,5,4,9,5,4,5,9,6,4,5,4 };
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
	while (current_team_count < 96) {
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
	vector<DWORD> no_group_leagues = {
		BRA_BAHIA_STATE_9CF(),
		BRA_NORTH_STATE_9CF(),
		BRA_PERNAMBUCO_STATE_9CF(),
	};
	for (size_t i = 0; i < state_leagues.size(); i++) {
		comp_stats* league = (comp_stats*)get_loaded_league(state_leagues[i]);
		if (league) {
			vector<cm3_clubs*> relegated;
			if (find(no_group_leagues.begin(), no_group_leagues.end(), state_leagues[i]) != no_group_leagues.end())
				relegated = get_relegated_teams(state_leagues[i]);
			else {
				comp_stats* curr_stage = league;
				for (char al = -1; al < 1; al++) {
					if (al >= 0) {
						curr_stage = (comp_stats*)(league->stages[al]);
					}
					for (WORD num = 0; num < curr_stage->n_teams; num++) {
						team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
						if (table_pos.league_fate == Relegated) {
							relegated.push_back(table_pos.club);
						}
					}
				}
			}
			vector<cm3_clubs*> lower_teams = find_clubs_of_comp_reserve_division(state_lower[i]);
			vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(lower_teams, relegated.size(), true);

			for (size_t i = 0; i < relegated.size(); i++)
			{
				cm3_clubs* clubToRelegate = relegated[i];
				cm3_clubs* available = promoted_clubs[i];

				cm3_club_comps* topDivision = clubToRelegate->ClubReserveDivision;
				cm3_club_comps* bottomDivision = available->ClubReserveDivision;
				clubToRelegate->ClubReserveDivision = bottomDivision;
				available->ClubReserveDivision = topDivision;

				trigger_relegation_clauses_4CD030((BYTE*)*ae1050, clubToRelegate, topDivision);
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
	vector<DWORD> no_group_leagues = {
		BRA_BAHIA_STATE_9CF(),
		BRA_NORTH_STATE_9CF(),
		BRA_PERNAMBUCO_STATE_9CF(),
	};
	WORD total_teams = 126;
	comp_stats* cup_data = (comp_stats*)get_loaded_league(BRA_CUP_9CF());
	if (!cup_data) return;
	if (cup_data->special_teams_seedings) {
		sub_9452CA_free(cup_data->special_teams_seedings);
		cup_data->special_teams_seedings = 0;
	}
	//cup_data->special_nteams_seedings = total_teams;
	vector<cm3_clubs*> all_clubs;
	// Série D (relegated from C)
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp_last_division(BRA_THIRD_9CF());
	for (cm3_clubs* c : division_clubs) {
		if (c->ClubDivision && c->ClubDivision->ClubCompID == BRA_FOURTH_9CF())
		{
			//dprintf("Club %s has qualified for Copa do Brasil! (from Série D)\n", c->ClubNameShort);
			all_clubs.push_back(c);
		}
	}
	// Série D (from playoffs)
	comp_stats* comp_data = (comp_stats*)get_loaded_league(BRA_FOURTH_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 15; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < comp_data->n_teams; i++) {
			if (table[i].league_fate == TopPlayoff)
			{
				//dprintf("Club %s has qualified for Copa do Brasil! (from Série D)\n", table[i].club->ClubNameShort);
				all_clubs.push_back(table[i].club);
			}
		}
	}
	// Série C
	division_clubs = find_clubs_of_comp(BRA_THIRD_9CF());
	for (WORD i = 0; i < division_clubs.size(); i++) {
		//dprintf("Club %s has qualified for Copa do Brasil! (from Série C)\n", division_clubs[i]->ClubNameShort);
		all_clubs.push_back(division_clubs[i]);
	}
	// Série B
	division_clubs = find_clubs_of_comp(BRA_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (WORD i = 0; i < division_clubs.size(); i++) {
		//dprintf("Club %s has qualified for Copa do Brasil! (from Série B)\n", division_clubs[i]->ClubNameShort);
		all_clubs.push_back(division_clubs[i]);
	}
	// Série A
	division_clubs = find_clubs_of_comp(BRA_FIRST_9CF());
	for (WORD i = 0; i < division_clubs.size(); i++) {
		//dprintf("Club %s has qualified for Copa do Brasil! (from Série A)\n", division_clubs[i]->ClubNameShort);
		all_clubs.push_back(division_clubs[i]);
	}
	// State teams
	vector<cm3_clubs*> first_phase;
	BYTE state_counts[12] = { 2,3,2,6,2,2,2,5,3,2,3,2 };
	for (size_t i = 0; i < state_leagues.size(); i++) {
		comp_stats* league = (comp_stats*)get_loaded_league(state_leagues[i]);
		cm3_club_comps* lower = get_comp(state_lower[i]);
		BYTE count = state_counts[i];
		if (league && lower) {
			//dprintf("Getting %d teams from league: %s\n", count, league->competition_db->ClubCompNameShort);
			if (find(no_group_leagues.begin(), no_group_leagues.end(), state_leagues[i]) != no_group_leagues.end())
			{
				team_league_stats* table = (team_league_stats*)league->team_league_table;
				for (WORD j = 0; j < league->n_teams && count > 0; j++) {
					cm3_clubs* club = table[j].club;
					if (vector_contains_element(all_clubs, club)) continue;
					//dprintf("- Club %s has qualified to Copa do Brasil! (finished %d)\n", club->ClubNameShort, j + 1);
					first_phase.push_back(club);
					count--;
				}
			}
			else {
				vector<cm3_clubs*> grouped_teams;
				comp_stats* finals_data = (comp_stats*)(league->stages[1]);
				teams_seeded* teams = (teams_seeded*)finals_data->teams_list;
				// priority to winner and runner-up
				for (WORD i = 0; i < finals_data->n_teams; i++) {
					if (teams[i].f6 == 1)
					{
						grouped_teams.insert(grouped_teams.begin(), teams[i].club);
					}
					else if (teams[i].f6 == 2)
					{
						grouped_teams.push_back(teams[i].club);
					}
				}
				// get all other teams in order
				comp_stats* league_group = (comp_stats*)(league->stages[0]);
				for (WORD num = 0; num < league->n_teams; num++) {
					cm3_clubs* c1 = ((team_league_stats*)league->team_league_table)[num].club;
					if (!vector_contains_element(grouped_teams, c1))
						grouped_teams.push_back(c1);
					cm3_clubs* c2 = ((team_league_stats*)league_group->team_league_table)[num].club;
					if (!vector_contains_element(grouped_teams, c2))
						grouped_teams.push_back(c2);
				}
				// add the teams
				for (WORD j = 0; j < grouped_teams.size() && count > 0; j++) {
					cm3_clubs* club = grouped_teams[j];
					if (vector_contains_element(all_clubs, club)) continue;
					//dprintf("- Club %s has qualified to Copa do Brasil! (index %d)\n", club->ClubNameShort, j);
					first_phase.push_back(club);
					count--;
				}
			}
			if (count > 0) {
				vector<cm3_clubs*> lower_teams = find_clubs_of_comp_reserve_division(state_lower[i]);
				sort(lower_teams.begin(), lower_teams.end(), compareClubRep);
				for (WORD j = 0; j < lower_teams.size() && count > 0; j++) {
					cm3_clubs* club = lower_teams[j];
					if (vector_contains_element(all_clubs, club)) continue;
					//dprintf("- Club %s has qualified to Copa do Brasil! (from lower leagues)\n", club->ClubNameShort);
					first_phase.push_back(club);
					count--;
				}
			}
		}
	}
	sort(first_phase.begin(), first_phase.end(), compareClubRepInv);

	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);
	cup_data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)cup_data->special_teams_seedings;

	size_t i;
	for (i = 0; i < first_phase.size(); i++)
	{
		teams[i].club = first_phase[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}
	WORD d1_teams = 20;
	for (size_t j = 0; i < total_teams && j < all_clubs.size(); i++, j++)
	{
		teams[i].club = all_clubs[j];
		teams[i].f5 = 0 + 3 * (j >= (all_clubs.size() - d1_teams));
		teams[i].f6 = 0;
	}
}

char bra_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* bra_second = get_loaded_league(BRA_SECOND_9CF());
	BYTE* bra_third = get_loaded_league(BRA_THIRD_9CF());
	BYTE* bra_fourth = get_loaded_league(BRA_FOURTH_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be professional
	update_club_pro_status_68A980(bra_second, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(bra_second, Professional, -3, Relegated, 1);
	// All teams that were in D3 must be professional
	update_club_pro_status_68A980(bra_third, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(bra_third, Professional, -3, Relegated, 1);
	comp_stats* bra_fourth_data = (comp_stats*)bra_fourth;
	// All teams that were in D4 must be professional
	update_club_pro_status_68A980(bra_fourth, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(bra_fourth, Professional, -3, Relegated, 1);
	for (int i = 0; i < 15; i++)
	{
		BYTE* bra_fourth_grp = (BYTE*)bra_fourth_data->stages[i];
		update_club_pro_status_68A980(bra_fourth_grp, Professional, Relegated, -3, 1);
		update_club_pro_status_68A980(bra_fourth_grp, Professional, -3, Relegated, 1);
	}

	DWORD v1 = *(DWORD*)_this;
	bra_first_prom_rel_update(_this, 1);

	bra_qualify_teams_for_cup(_this);
	bra_promotion_to_fourth(_this);
	bra_state_leagues_update(_this);
	bra_update_managers(_this);

	sub_687970(_this, 0);
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
			data->stages[i] = 0;
		}
	}
	data->year++;
	data->current_stage = -1;
	bra_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("bra_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("bra_first_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)bra_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bra_second);

	v1 = *(DWORD*)bra_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bra_third);

	v1 = *(DWORD*)bra_fourth;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(bra_fourth);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) bra_first_update_c()
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
	WriteVTablePtr(bra_first_vtable, VTablePlayoffQual, 0x5a8f60);
	WriteVTablePtr(bra_first_vtable, VTableSetChampion, 0x684640);
	WriteVTablePtr(bra_first_vtable, VTableTableFates, 0x686940);
	WriteVTablePtr(bra_first_vtable, VTableStageNews, 0x48c6d0);
	WriteVTablePtr(bra_first_vtable, VTableReputationCalc, 0x48e380);
	WriteVTablePtr(bra_first_vtable, VTable37, 0x68aad0);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(bra_first_vtable, VTableShowThirdInHistory, 0x4110b0);
}
