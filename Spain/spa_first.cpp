#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* spa_first_vtable = (DWORD*)0x96FA68;

int spa_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 3;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = SPA_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return 1;
}

void __declspec(naked) spa_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call spa_first_subs
		add esp, 0x4
		ret
	}
}

void spa_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = spa_first_vtable;
	DWORD x = 0;
	sub_687970(_this, 0);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
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
	sub_682300(_this);
}

void spa_first_free(BYTE* _this, BYTE a2) {
	spa_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) spa_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call spa_first_free
		add esp, 0x8
		ret 4
	}
}

void spa_first_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* spa_second = get_loaded_league(SPA_SECOND_9CF());
	v1 = *(DWORD*)spa_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(spa_second);
	process_promotion_relegation_689C80(_this, _this, spa_second, 1, a2, -1, -1);

	BYTE* spa_third = get_loaded_league(SPA_THIRD_9CF());
	comp_stats* spa_third_data = (comp_stats*)spa_third;
	v1 = *(DWORD*)spa_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(spa_third);

	BYTE* spa_third_grp = (BYTE*)spa_third_data->stages[0];
	v1 = *(DWORD*)spa_third_grp;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(spa_third_grp);

	process_promotion_relegation_689C80(_this, spa_second, spa_third, 1, a2, -1, -1);
	process_promotion_relegation_689C80(_this, spa_second, spa_third_grp, 1, a2, -1, -1);

	BYTE* spa_fourth = get_loaded_league(SPA_FOURTH_9CF());
	if (spa_fourth) {
		comp_stats* spa_fourth_data = (comp_stats*)spa_fourth;
		v1 = *(DWORD*)spa_fourth;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(spa_fourth);
		for (int i = 0; i < 4; i++)
		{
			BYTE* spa_fourth_grp = (BYTE*)spa_fourth_data->stages[i];
			v1 = *(DWORD*)spa_fourth_grp;
			(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(spa_fourth_grp);
		}

		process_promotion_relegation_689C80(_this, spa_third, spa_fourth, 1, a2, -1, -1);
		for (int i = 0; i < 4; i++)
		{
			BYTE* spa_fourth_grp = (BYTE*)spa_fourth_data->stages[i];
			process_promotion_relegation_689C80(_this, spa_third, spa_fourth_grp, 1, a2, -1, -1);
		}

		process_promotion_relegation_689C80(_this, spa_third_grp, spa_fourth, 1, a2, -1, -1);
		for (int i = 0; i < 4; i++)
		{
			BYTE* spa_fourth_grp = (BYTE*)spa_fourth_data->stages[i];
			process_promotion_relegation_689C80(_this, spa_third_grp, spa_fourth_grp, 1, a2, -1, -1);
		}
	}
}

void __declspec(naked) spa_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call spa_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall spa_third_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(SPA_THIRD_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				relegated_clubs.push_back(table_pos.club);
			}
		}
	}

	vector<cm3_clubs*> promoted_clubs;
	vector<DWORD> d4_groups = { SPA_FOURTH_G1_9CF(), SPA_FOURTH_G2_9CF(), SPA_FOURTH_G3_9CF(), SPA_FOURTH_G4_9CF(), SPA_FOURTH_G5_9CF() };
	for (DWORD id : d4_groups) {
		vector<cm3_clubs*> available_clubs = find_clubs_of_comp_main_reserve_division(SPA_FOURTH_9CF(), id, NATION_SPAIN_9CF());
		for (size_t i = 0; i < available_clubs.size(); i++) {
			cm3_clubs* c = available_clubs[i];
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
			if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != SPA_FIRST_9CF() && ret_club->ClubDivision->ClubCompID != SPA_SECOND_9CF())
			{
				available_clubs.erase(available_clubs.begin() + i);
				i--;
			}
		}
		vector<cm3_clubs*> ret = get_random_weighted_clubs(available_clubs, 2, true);
		move(ret.begin(), ret.end(), back_inserter(promoted_clubs));
	}

	for (unsigned int j = 0; j < promoted_clubs.size(); j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];
		//dprintf("Swapping Teams: %s (%s) %d <-> %s (%s) %d\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, clubToRelegate->ClubReputation, clubToPromote->ClubName, clubToPromote->ClubDivision->ClubCompName, clubToPromote->ClubReputation);

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
		clubToPromote->ClubReserveDivision = 0;
		clubToRelegate->ClubReserveDivision = 0;
	}
}

void __fastcall spa_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(SPA_FOURTH_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 4; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				relegated_clubs.push_back(table_pos.club);
			}
		}
	}

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_SPAIN_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != SPA_FIRST_9CF() && ret_club->ClubDivision->ClubCompID != SPA_SECOND_9CF()
			&& ret_club->ClubDivision->ClubCompID != SPA_THIRD_9CF())
		{
			available_clubs.erase(available_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size(), true);

	for (unsigned int j = 0; j < promoted_clubs.size(); j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];
		//dprintf("Swapping Teams: %s (%s) %d <-> %s (%s) %d\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, clubToRelegate->ClubReputation, clubToPromote->ClubName, clubToPromote->ClubDivision->ClubCompName, clubToPromote->ClubReputation);

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
		clubToRelegate->ClubReserveDivision = 0;
	}
}

void __fastcall spa_d4_inactive_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;
	vector<DWORD> d4_groups = { SPA_FOURTH_G1_9CF(), SPA_FOURTH_G2_9CF(), SPA_FOURTH_G3_9CF(), SPA_FOURTH_G4_9CF(), SPA_FOURTH_G5_9CF() };
	for (DWORD id : d4_groups) {
		vector<cm3_clubs*> available_clubs = find_clubs_of_comp_main_reserve_division(SPA_FOURTH_9CF(), id, NATION_SPAIN_9CF());
		vector<cm3_clubs*> ret = get_random_weighted_clubs(available_clubs, 5, false);
		move(ret.begin(), ret.end(), back_inserter(relegated_clubs));
	}

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_SPAIN_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != SPA_FIRST_9CF() && ret_club->ClubDivision->ClubCompID != SPA_SECOND_9CF()
			&& ret_club->ClubDivision->ClubCompID != SPA_THIRD_9CF())
		{
			available_clubs.erase(available_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size(), true);

	for (unsigned int j = 0; j < promoted_clubs.size(); j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];
		//dprintf("Swapping Teams: %s (%s) %d <-> %s (%s) %d\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, clubToRelegate->ClubReputation, clubToPromote->ClubName, clubToPromote->ClubDivision->ClubCompName, clubToPromote->ClubReputation);

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
		clubToRelegate->ClubReserveDivision = 0;
	}
}

void sort_spa_third_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(SPA_THIRD_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubWEDiagNS);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 20) available_clubs[i]->ClubReserveDivision = get_comp(SPA_THIRD_G1_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(SPA_THIRD_G2_9CF());
	}
}

void sort_spa_fourth_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(SPA_FOURTH_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubWEDiagNS);
	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 18) available_clubs[i]->ClubReserveDivision = get_comp(SPA_FOURTH_G1_9CF());
		else if (i < 36) available_clubs[i]->ClubReserveDivision = get_comp(SPA_FOURTH_G2_9CF());
		else if (i < 54) available_clubs[i]->ClubReserveDivision = get_comp(SPA_FOURTH_G3_9CF());
		else if (i < 72) available_clubs[i]->ClubReserveDivision = get_comp(SPA_FOURTH_G4_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(SPA_FOURTH_G5_9CF());
	}
}

void __fastcall spa_check_reserve_teams(BYTE* _this) {
	comp_stats* spa_second_data = (comp_stats*)get_loaded_league(SPA_SECOND_9CF());
	comp_stats* spa_third_data = (comp_stats*)get_loaded_league(SPA_THIRD_9CF());
	BYTE* spa_fourth = get_loaded_league(SPA_FOURTH_9CF());
	if (spa_fourth) {
		// Check teams from L4: promoted but main team relegated from L2 - remove promotion + remove one relegation from L3
		// Check teams from L4: main team relegated from L3 - add relegation
		comp_stats* spa_fourth_data = (comp_stats*)spa_fourth;
		comp_stats* curr_stage = spa_fourth_data;
		for (char al = -1; al < 4; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(spa_fourth_data->stages[al]);
			}
			for (WORD num = 0; num < curr_stage->n_teams; num++) {
				team_league_stats* table_teams = (team_league_stats*)curr_stage->team_league_table;
				DWORD is_main_club;
				cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
				// If it is a reserve team
				if (ret_club && !is_main_club)
				{
					team_league_stats* d3_table_a = (team_league_stats*)spa_third_data->team_league_table;
					team_league_stats* d3_table_b = (team_league_stats*)((comp_stats*)spa_third_data->stages[0])->team_league_table;
					// If reserve team from Regional is promoted
					if (table_teams[num].league_fate == Promoted) {
						// If main team is in the second league
						if (ret_club->ClubDivision->ClubCompID == SPA_SECOND_9CF()) {
							team_league_stats* main_club_data = get_team_league_stats(SPA_SECOND_9CF(), ret_club);
							// If the main team was relegated
							if (main_club_data->league_fate == Relegated) {
								table_teams[num].league_fate = Eliminated;
								// Do not promote the reserve team, and relegate one less team from the third league
								for (WORD i = spa_third_data->n_teams - spa_third_data->rele_playoff; i < spa_third_data->n_teams; i++) {
									if (d3_table_a[i].league_fate == Relegated) {
										d3_table_a[i].league_fate = Eliminated;
										break;
									}
									if (d3_table_b[i].league_fate == Relegated) {
										d3_table_b[i].league_fate = Eliminated;
										break;
									}
								}
							}
						}
					}
					// If team was not relegated
					else if (table_teams[num].league_fate != Relegated) {
						// If main team is in the third league
						if (ret_club->ClubDivision->ClubCompID == SPA_THIRD_9CF()) {
							team_league_stats* main_club_data = get_team_league_stats(SPA_THIRD_9CF(), ret_club);
							if (!main_club_data) main_club_data = get_team_league_stats(SPA_THIRD_9CF(), ret_club, 0);
							// If the main team was relegated
							if (main_club_data->league_fate == Relegated) {
								// Relegate the reserve team
								table_teams[num].league_fate = Relegated;
							}
						}
					}
				}
			}
		}
	}
	// Check teams from L3: promoted but main team relegated from L1 - remove promotion + remove one relegation from L2
	// Check teams from L3: main team relegated from L2 - add relegation + remove one relegation
	comp_stats* l3_curr_stage = spa_third_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			l3_curr_stage = (comp_stats*)(spa_third_data->stages[al]);
		}
		for (WORD num = 0; num < l3_curr_stage->n_teams; num++) {
			team_league_stats* table_teams = (team_league_stats*)l3_curr_stage->team_league_table;
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
			// If it is a reserve team
			if (ret_club && !is_main_club)
			{
				if (table_teams[num].league_fate == Champions || table_teams[num].league_fate == Promoted) {
					// If main team is in the first league
					if (ret_club->ClubDivision->ClubCompID == SPA_FIRST_9CF()) {
						team_league_stats* main_club_data = get_team_league_stats(SPA_FIRST_9CF(), ret_club);
						// If the main team was relegated
						if (main_club_data->league_fate == Relegated) {
							table_teams[num].league_fate = Eliminated;
							// Do not promote the reserve team, and relegate one less team from the second league
							team_league_stats* d2_table = (team_league_stats*)spa_second_data->team_league_table;
							for (WORD i = spa_second_data->n_teams - spa_second_data->relegations - spa_second_data->rele_playoff; i < spa_second_data->n_teams; i++) {
								if (d2_table[i].league_fate == Relegated) {
									d2_table[i].league_fate = Eliminated;
									break;
								}
							}
						}
					}

				}
				// If reserve team was not relegated
				else if (table_teams[num].league_fate != Relegated) {
					// If main team is in the second league
					if (ret_club->ClubDivision->ClubCompID == SPA_SECOND_9CF()) {
						team_league_stats* main_club_data = get_team_league_stats(SPA_SECOND_9CF(), ret_club);
						// If the main team was relegated
						if (main_club_data->league_fate == Relegated) {
							table_teams[num].league_fate = Relegated;
							// Relegate the reserve team, and relegate one less team from the third league
							team_league_stats* d3_table = (team_league_stats*)l3_curr_stage->team_league_table;
							for (WORD i = l3_curr_stage->n_teams - l3_curr_stage->rele_playoff; i < l3_curr_stage->n_teams; i++) {
								if (d3_table[i].league_fate == Relegated) {
									d3_table[i].league_fate = Eliminated;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	// Check teams from L2: main team relegated from L1 - add relegation + remove one relegation
	for (WORD num = 0; num < spa_second_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)spa_second_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			// If reserve team was not relegated
			if (table_teams[num].league_fate != Relegated) {
				// If main team is in the first league
				if (ret_club->ClubDivision->ClubCompID == SPA_FIRST_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(SPA_FIRST_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from the second league
						team_league_stats* d2_table = (team_league_stats*)spa_second_data->team_league_table;
						for (WORD i = spa_second_data->n_teams - spa_second_data->relegations - spa_second_data->rele_playoff; i < spa_second_data->n_teams; i++) {
							if (d2_table[i].league_fate == Relegated) {
								d2_table[i].league_fate = Eliminated;
								break;
							}
						}
					}
				}
			}
		}
	}
}

void __fastcall spa_qualify_teams_for_cup(BYTE* _this) {
	vector<cm3_clubs*> vec;
	WORD total_teams = 116;
	comp_stats* cup_data = (comp_stats*)get_loaded_league(SPA_CUP_9CF());
	if (!cup_data) return;
	if (cup_data->special_teams_seedings) {
		sub_9452CA_free(cup_data->special_teams_seedings);
		cup_data->special_teams_seedings = 0;
	}
	//cup_data->special_nteams_seedings = total_teams;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);
	cup_data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)cup_data->special_teams_seedings;

	// 5x2 from Primera Fed and 5x5 from Segunda Fed
	WORD main_teams = CountNumberOfTeamsInComp(SPA_FIRST_9CF()) + CountNumberOfTeamsInCompNoReserve(SPA_SECOND_9CF()) + 10 + 25;
	WORD lower_teams = total_teams - main_teams;

	vector<cm3_clubs*> vec_super;

	cm3_club_comps* spa_cup = get_comp(SPA_CUP_9CF());
	cm3_clubs* winner = get_last_comp_winner(spa_cup);
	if (winner) vec_super.push_back(winner);
	cm3_clubs* runner_up = get_last_comp_runner_up(spa_cup);
	if (runner_up) vec_super.push_back(runner_up);

	comp_stats* data = (comp_stats*)_this;
	WORD d1_total_teams = data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(data->team_league_table);
	for (int i = 0; i < d1_total_teams; i++) {
		if (!vector_contains_club(vec_super, table_teams[i].club)) vec_super.push_back(table_teams[i].club);
		if (vec_super.size() >= 4) break;
	}

	// Lower
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_SPAIN_9CF());
	for (size_t i = 0; i < lower_clubs.size(); i++) {
		cm3_clubs* c = lower_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club)
		{
			lower_clubs.erase(lower_clubs.begin() + i);
			i--;
		}
		else if (vector_contains_club(vec_super, c))
		{
			lower_clubs.erase(lower_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> division_clubs = get_random_weighted_clubs(lower_clubs, lower_teams, true);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Segunda Federación
	BYTE selected = get_country(NATION_SPAIN_9CF())->NationLeagueSelected;
	if ((selected & 4) != 0) {
		comp_stats* d4_data = (comp_stats*)get_loaded_league(SPA_FOURTH_9CF());
		comp_stats* curr_stage = d4_data;
		for (char al = -1; al < 4; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(d4_data->stages[al]);
			}
			WORD total_teams = curr_stage->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0, j = 0; i < total_teams && j < 5; i++) {
				DWORD is_main_club;
				cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
				if (!ret_club || is_main_club) {
					if (!vector_contains_club(vec_super, table_teams[i].club)) vec.push_back(table_teams[i].club);
					j++;
				}
			}
		}
	}
	else {
		division_clubs = find_clubs_of_comp(SPA_FOURTH_9CF());
		sort(division_clubs.begin(), division_clubs.end(), compareClubRep);
		for (unsigned int i = 0; i < 25; i++)
		{
			int availableIdx = rand() % division_clubs.size();
			cm3_clubs* club = division_clubs[availableIdx];

			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
			if (ret_club && !is_main_club)
				i--;
			else if (!vector_contains_club(vec_super, club))
				vec.push_back(club);

			division_clubs.erase(division_clubs.begin() + availableIdx);
		}
	}
	// Primera Federacion
	comp_stats* d3_data = (comp_stats*)get_loaded_league(SPA_THIRD_9CF());
	comp_stats* curr_stage = d3_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(d3_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0, j = 0; i < total_teams && j < 5; i++) {
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[i].club, &is_main_club, 1);
			if (!ret_club || is_main_club) {
				if (!vector_contains_club(vec_super, table_teams[i].club)) vec.push_back(table_teams[i].club);
				j++;
			}
		}
	}
	// La Liga 2
	division_clubs = find_clubs_of_comp(SPA_SECOND_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)club, &is_main_club, 1);
		if ((!ret_club || is_main_club) && !vector_contains_club(vec_super, club)) vec.push_back(club);
	}
	// La Liga
	division_clubs = find_clubs_of_comp(SPA_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_super, club)) vec.push_back(club);
	}

	for (size_t i = 0; i < vec_super.size(); i++) vec.push_back(vec_super[i]);

	while (vec.size() > total_teams) {
		vec.erase(vec.begin());
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}
}

char spa_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;

	BYTE* spa_second = get_loaded_league(SPA_SECOND_9CF());
	BYTE* spa_third = get_loaded_league(SPA_THIRD_9CF());
	comp_stats* spa_third_data = (comp_stats*)spa_third;
	BYTE* spa_fourth = get_loaded_league(SPA_FOURTH_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be professional
	update_club_pro_status_68A980(spa_second, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(spa_second, Professional, -3, Relegated, 1);
	// All teams that were not relegated from D3 must be semi-professional or higher
	BYTE* spa_third_grp = (BYTE*)spa_third_data->stages[0];
	update_club_pro_status_68A980(spa_third, SemiProfessional, Relegated, -3, 1);
	update_club_pro_status_68A980(spa_third_grp, SemiProfessional, Relegated, -3, 1);
	if (spa_fourth)
	{
		comp_stats* spa_fourth_data = (comp_stats*)spa_fourth;
		// All teams that were not relegated from D4 must be semi-professional
		update_club_pro_status_68A980(spa_fourth, SemiProfessional, Relegated, -3, 1);
		update_club_pro_status_68A980(spa_fourth, SemiProfessional, Relegated, -3, 0);
		for (int i = 0; i < 4; i++)
		{
			BYTE* spa_fourth_grp = (BYTE*)spa_fourth_data->stages[i];
			update_club_pro_status_68A980(spa_fourth_grp, SemiProfessional, Relegated, -3, 1);
			update_club_pro_status_68A980(spa_fourth_grp, SemiProfessional, Relegated, -3, 0);
		}
	}

	spa_qualify_teams_for_cup(_this);
	spa_check_reserve_teams(_this);
	spa_first_prom_rel_update(_this, 1);

	if (spa_fourth) {
		spa_non_league_promotion(_this);
	}
	else {
		spa_third_relegation(_this);
		spa_d4_inactive_relegation(_this);
	}
	sort_spa_third_clubs();
	sort_spa_fourth_clubs();

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
			data->stages[i] = 0;
		}
	}
	data->year++;
	data->current_stage = -1;
	spa_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("spa_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("spa_first_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)spa_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(spa_second);

	v1 = *(DWORD*)spa_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(spa_third);

	if (spa_fourth) {
		v1 = *(DWORD*)spa_fourth;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(spa_fourth);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) spa_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call spa_first_update
		add esp, 0x4
		ret
	}
}

DWORD spa_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 0) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 17), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 24), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 31), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 14), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 21), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 24), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 28), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 5), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 19), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 26), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 23), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 30), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 7), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 14), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 21), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 4), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 11), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 18), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 25), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 1), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 8), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 15), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 22), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 1), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 15), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 22), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 5), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 22), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 26), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 13), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 17), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 24), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else return 0;
}

void __declspec(naked) spa_first_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call spa_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void spa_first_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = spa_first_vtable;
	data->year = year;
	data->rules = RulesSpainLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 15000;
	data->min_stadium_seats = 15000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	spa_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("spa_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("spa_first_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void setup_spa_first()
{
	WriteVTablePtr(spa_first_vtable, VTableEoSUpdate, (DWORD)&spa_first_update_c);
	WriteVTablePtr(spa_first_vtable, VTableInitFree, (DWORD)&spa_first_free_c);
	WriteVTablePtr(spa_first_vtable, VTableFixtures, (DWORD)&spa_first_fixture_caller);
	WriteVTablePtr(spa_first_vtable, VTablePromRelUpdate, (DWORD)&spa_first_prom_rel_update_c);
	WriteVTablePtr(spa_first_vtable, VTable9, 0x48CEB0);
	WriteVTablePtr(spa_first_vtable, VTable10, 0x48CEA0);
	WriteVTablePtr(spa_first_vtable, VTableSubsRounds, (DWORD)&spa_first_subs_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(spa_first_vtable, VTable21, 0x4110b0);
}