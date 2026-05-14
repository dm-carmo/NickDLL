#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* por_first_vtable = (DWORD*)0x96E6F0;

void por_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GamesWonTiebreaker;
	comp_data->tiebreaker_4 = GoalsForTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 2;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = POR_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) por_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_first_subs
		add esp, 0x4
		ret
	}
}

void por_first_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* por_second = get_loaded_league(POR_SECOND_9CF());
	v1 = *(DWORD*)por_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(por_second);
	process_promotion_relegation_689C80(_this, _this, por_second, 1, a2, -1, -1);

	BYTE* por_third = get_loaded_league(POR_THIRD_9CF());
	comp_stats* por_third_data = (comp_stats*)por_third;
	v1 = *(DWORD*)por_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(por_third);

	BYTE* por_third_grp = (BYTE*)por_third_data->stages[0];
	v1 = *(DWORD*)por_third_grp;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(por_third_grp);

	process_promotion_relegation_689C80(_this, por_second, por_third, 1, a2, -1, -1);
	process_promotion_relegation_689C80(_this, por_second, por_third_grp, 1, a2, -1, -1);

	BYTE* por_fourth = get_loaded_league(POR_FOURTH_9CF());
	if (por_fourth) {
		comp_stats* por_fourth_data = (comp_stats*)por_fourth;
		v1 = *(DWORD*)por_fourth;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(por_fourth);
		for (int i = 0; i < 3; i++)
		{
			BYTE* por_fourth_grp = (BYTE*)por_fourth_data->stages[i];
			v1 = *(DWORD*)por_fourth_grp;
			(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(por_fourth_grp);
		}

		process_promotion_relegation_689C80(_this, por_third, por_fourth, 1, a2, -1, -1);
		for (int i = 0; i < 3; i++)
		{
			BYTE* por_fourth_grp = (BYTE*)por_fourth_data->stages[i];
			process_promotion_relegation_689C80(_this, por_third, por_fourth_grp, 1, a2, -1, -1);
		}

		process_promotion_relegation_689C80(_this, por_third_grp, por_fourth, 1, a2, -1, -1);
		for (int i = 0; i < 3; i++)
		{
			BYTE* por_fourth_grp = (BYTE*)por_fourth_data->stages[i];
			process_promotion_relegation_689C80(_this, por_third_grp, por_fourth_grp, 1, a2, -1, -1);
		}
	}
}

void __declspec(naked) por_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call por_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall por_liga_3_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(POR_THIRD_9CF());
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
	vector<DWORD> d4_groups = { POR_FOURTH_A_9CF(), POR_FOURTH_B_9CF(), POR_FOURTH_C_9CF(), POR_FOURTH_D_9CF() };
	for (DWORD id : d4_groups) {
		vector<cm3_clubs*> available_clubs = find_clubs_of_comp_reserve_division(id, NATION_PORTUGAL_9CF());
		for (size_t i = 0; i < available_clubs.size(); i++) {
			cm3_clubs* c = available_clubs[i];
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
			if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != POR_FIRST_9CF() && ret_club->ClubDivision->ClubCompID != POR_SECOND_9CF())
			{
				available_clubs.erase(available_clubs.begin() + i);
				i--;
			}
		}
		vector<cm3_clubs*> ret = get_random_weighted_clubs(available_clubs, 1, true);
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

void __fastcall por_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(POR_FOURTH_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 3; al++) {
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

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_PORTUGAL_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != POR_FIRST_9CF() && ret_club->ClubDivision->ClubCompID != POR_SECOND_9CF()
			&& ret_club->ClubDivision->ClubCompID != POR_THIRD_9CF())
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

void __fastcall por_d4_inactive_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;
	vector<DWORD> d4_groups = { POR_FOURTH_A_9CF(), POR_FOURTH_B_9CF(), POR_FOURTH_C_9CF(), POR_FOURTH_D_9CF() };
	for (DWORD id : d4_groups) {
		vector<cm3_clubs*> available_clubs = find_clubs_of_comp_reserve_division(id, NATION_PORTUGAL_9CF());
		vector<cm3_clubs*> ret = get_random_weighted_clubs(available_clubs, 5, false);
		move(ret.begin(), ret.end(), back_inserter(relegated_clubs));
	}

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_PORTUGAL_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != POR_FIRST_9CF() && ret_club->ClubDivision->ClubCompID != POR_SECOND_9CF()
			&& ret_club->ClubDivision->ClubCompID != POR_THIRD_9CF())
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

void sort_por_third_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(POR_THIRD_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 10) available_clubs[i]->ClubReserveDivision = get_comp(POR_THIRD_A_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(POR_THIRD_B_9CF());
	}
}

void sort_por_fourth_clubs(WORD year) {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(POR_FOURTH_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	vector<cm3_clubs*> clubs_madeira;
	vector<cm3_clubs*> clubs_azores;

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		cm3_clubs* club = available_clubs[i];
		if (!club->ClubStadium || !club->ClubStadium->StadiumCity) continue;
		double lat = club->ClubStadium->StadiumCity->CityLatitude;
		double lon = club->ClubStadium->StadiumCity->CityLongitude;
		// Madeira
		if (lat > 32 && lat < 34 && lon > -19 && lon < -16) {
			clubs_madeira.push_back(club);
			available_clubs.erase(available_clubs.begin() + (i--));
		}
		// Azores
		else if (lat > 36 && lat < 40 && lon > -32 && lon < -24) {
			clubs_azores.push_back(club);
			available_clubs.erase(available_clubs.begin() + (i--));
		}
	}

	for (cm3_clubs* c : clubs_madeira) {
		if (year % 2) c->ClubReserveDivision = get_comp(POR_FOURTH_A_9CF());
		else c->ClubReserveDivision = get_comp(POR_FOURTH_B_9CF());
	}

	for (cm3_clubs* c : clubs_azores) {
		if (year % 2) c->ClubReserveDivision = get_comp(POR_FOURTH_C_9CF());
		else c->ClubReserveDivision = get_comp(POR_FOURTH_D_9CF());
	}

	size_t a_size = 14 - (year % 2 ? clubs_madeira.size() : 0);
	size_t b_size = 14 - (year % 2 ? 0 : clubs_madeira.size());
	size_t c_size = 14 - (year % 2 ? clubs_azores.size() : 0);
	size_t d_size = 14 - (year % 2 ? 0 : clubs_azores.size());

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < a_size) available_clubs[i]->ClubReserveDivision = get_comp(POR_FOURTH_A_9CF());
		else if (i < a_size + b_size) available_clubs[i]->ClubReserveDivision = get_comp(POR_FOURTH_B_9CF());
		else if (i < a_size + b_size + c_size) available_clubs[i]->ClubReserveDivision = get_comp(POR_FOURTH_C_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(POR_FOURTH_D_9CF());
	}
}

void __fastcall por_check_reserve_teams(BYTE* _this) {
	comp_stats* por_second_data = (comp_stats*)get_loaded_league(POR_SECOND_9CF());
	comp_stats* por_third_data = (comp_stats*)get_loaded_league(POR_THIRD_9CF());
	BYTE* por_fourth = get_loaded_league(POR_FOURTH_9CF());
	if (por_fourth) {
		// Check teams from L4: promoted but main team relegated from L2 - remove promotion + remove one relegation from L3
		// Check teams from L4: main team relegated from L3 - add relegation
		comp_stats* por_fourth_data = (comp_stats*)por_fourth;
		comp_stats* curr_stage = por_fourth_data;
		for (char al = -1; al < 3; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(por_fourth_data->stages[al]);
			}
			for (WORD num = 0; num < curr_stage->n_teams; num++) {
				team_league_stats* table_teams = (team_league_stats*)curr_stage->team_league_table;
				DWORD is_main_club;
				cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
				// If it is a reserve team
				if (ret_club && !is_main_club)
				{
					team_league_stats* d3_table_a = (team_league_stats*)por_third_data->team_league_table;
					team_league_stats* d3_table_b = (team_league_stats*)((comp_stats*)por_third_data->stages[0])->team_league_table;
					// If reserve team from Regional is promoted
					if (table_teams[num].league_fate == Promoted) {
						// If main team is in the second league
						if (ret_club->ClubDivision->ClubCompID == POR_SECOND_9CF()) {
							team_league_stats* main_club_data = get_team_league_stats(POR_SECOND_9CF(), ret_club);
							// If the main team was relegated
							if (main_club_data->league_fate == Relegated) {
								table_teams[num].league_fate = Eliminated;
								// Do not promote the reserve team, and relegate one less team from the third league
								for (WORD i = por_third_data->n_teams - por_third_data->rele_playoff; i < por_third_data->n_teams; i++) {
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
						if (ret_club->ClubDivision->ClubCompID == POR_THIRD_9CF()) {
							team_league_stats* main_club_data = get_team_league_stats(POR_THIRD_9CF(), ret_club);
							if (!main_club_data) main_club_data = get_team_league_stats(POR_THIRD_9CF(), ret_club, 0);
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
	comp_stats* l3_curr_stage = por_third_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			l3_curr_stage = (comp_stats*)(por_third_data->stages[al]);
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
					if (ret_club->ClubDivision->ClubCompID == POR_FIRST_9CF()) {
						team_league_stats* main_club_data = get_team_league_stats(POR_FIRST_9CF(), ret_club);
						// If the main team was relegated
						if (main_club_data->league_fate == Relegated) {
							table_teams[num].league_fate = Eliminated;
							// Do not promote the reserve team, and relegate one less team from the second league
							team_league_stats* d2_table = (team_league_stats*)por_second_data->team_league_table;
							for (WORD i = por_second_data->n_teams - por_second_data->relegations - por_second_data->rele_playoff; i < por_second_data->n_teams; i++) {
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
					if (ret_club->ClubDivision->ClubCompID == POR_SECOND_9CF()) {
						team_league_stats* main_club_data = get_team_league_stats(POR_SECOND_9CF(), ret_club);
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
	for (WORD num = 0; num < por_second_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)por_second_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			// If reserve team was not relegated
			if (table_teams[num].league_fate != Relegated) {
				// If main team is in the first league
				if (ret_club->ClubDivision->ClubCompID == POR_FIRST_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(POR_FIRST_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from the second league
						team_league_stats* d2_table = (team_league_stats*)por_second_data->team_league_table;
						for (WORD i = por_second_data->n_teams - por_second_data->relegations - por_second_data->rele_playoff; i < por_second_data->n_teams; i++) {
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

char por_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;

	BYTE* por_second = get_loaded_league(POR_SECOND_9CF());
	BYTE* por_third = get_loaded_league(POR_THIRD_9CF());
	BYTE* por_fourth = get_loaded_league(POR_FOURTH_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be professional
	update_club_pro_status_68A980(por_second, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(por_second, Professional, -3, Relegated, 1);
	// All teams that were not relegated from D3 must be professional
	comp_stats* por_third_data = (comp_stats*)por_third;
	BYTE* por_third_grp = (BYTE*)por_third_data->stages[0];
	update_club_pro_status_68A980(por_third, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(por_third_grp, Professional, Relegated, -3, 1);
	if (por_fourth)
	{
		comp_stats* por_fourth_data = (comp_stats*)por_fourth;
		// All teams that were not relegated from D4 must be semi-professional
		// All teams that were relegated from D4 must be amateur
		update_club_pro_status_68A980(por_fourth, SemiProfessional, Promoted, -3, 1);
		update_club_pro_status_68A980(por_fourth, SemiProfessional, Promoted, -3, 0);
		update_club_pro_status_68A980(por_fourth, SemiProfessional, -3, Champions, 1);
		update_club_pro_status_68A980(por_fourth, SemiProfessional, -3, Promoted, 1);
		update_club_pro_status_68A980(por_fourth, Amateur, -3, Relegated, 0);
		for (int i = 0; i < 3; i++)
		{
			BYTE* por_fourth_grp = (BYTE*)por_fourth_data->stages[i];
			update_club_pro_status_68A980(por_fourth_grp, SemiProfessional, Promoted, -3, 1);
			update_club_pro_status_68A980(por_fourth_grp, SemiProfessional, Promoted, -3, 0);
			update_club_pro_status_68A980(por_fourth_grp, SemiProfessional, -3, Champions, 1);
			update_club_pro_status_68A980(por_fourth_grp, SemiProfessional, -3, Promoted, 1);
			update_club_pro_status_68A980(por_fourth_grp, Amateur, -3, Relegated, 0);
		}
	}

	por_check_reserve_teams(_this);
	por_first_prom_rel_update(_this, 1);

	if (por_fourth) {
		por_non_league_promotion(_this);
	}
	else {
		por_liga_3_relegation(_this);
		por_d4_inactive_relegation(_this);
	}
	sort_por_third_clubs();
	sort_por_fourth_clubs(data->year + 1);

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
	por_first_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("por_first_tv_money_normal"), get_comp(POR_FIRST_9CF()));
	SetupTVMoney(_this, prizeMoneyFile.GetInt("por_first_tv_money_promoted"), get_comp(POR_SECOND_9CF()));
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)por_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(por_second);

	v1 = *(DWORD*)por_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(por_third);

	if (por_fourth) {
		v1 = *(DWORD*)por_fourth;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(por_fourth);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) por_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_first_update
		add esp, 0x4
		ret
	}
}

void por_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = por_first_vtable;
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

void por_first_free(BYTE* _this, BYTE a2) {
	por_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) por_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call por_first_free
		add esp, 0x8
		ret 4
	}
}

DWORD por_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 10), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
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
		AddFixture(pMem, fixture_id, Date(year, 12, 28), year, Sunday);
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
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
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
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
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
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 18), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 23), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 2, 1, 2, 0, 0, 2, 6);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) por_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call por_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void por_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = por_first_vtable;
	data->year = year;
	data->rules = RulesPortugal;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 4000;
	data->min_stadium_seats = 4000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	for (int i = 0; i < data->num_stages; i++) data->stages[i] = 0;
	por_first_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("por_first_tv_money_normal"), get_comp(POR_FIRST_9CF()));
	SetupTVMoney(_this, prizeMoneyFile.GetInt("por_first_tv_money_promoted"), get_comp(POR_SECOND_9CF()));
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

void por_first_playoff_under(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);

	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == BottomPlayoff) {
			*((DWORD*)(&pTeams[0])) = (DWORD)tls.club;
			break;
		}
	}

	comp_stats* por_second_data = (comp_stats*)get_loaded_league(POR_SECOND_9CF());
	total_teams = por_second_data->n_teams;
	table_teams = (team_league_stats*)(por_second_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[1])) = (DWORD)tls.club;
			break;
		}
	}
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void por_first_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		BYTE* por_second = get_loaded_league(POR_SECOND_9CF());
		DWORD v1 = *(DWORD*)por_second;
		char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(por_second, 0, 1);
		if (ret != 0) {
			(*(void(__thiscall**)(BYTE*))(v1 + 0x94))(por_second);
			current++;
			comp_data->current_stage = current;
			if (current == 0) {
				por_first_playoff_under(_this);
			}
		}
	}
}

void __declspec(naked) por_first_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call por_first_playoffs_c
		add esp, 0x4
		ret
	}
}

int por_first_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* por_second = get_comp(POR_SECOND_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club_ptr->ClubDivision == por_second) {
			comp_stats* por_second_data = (comp_stats*)get_loaded_league(POR_SECOND_9CF());
			WORD num_teams = por_second_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(por_second_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)por_second, 0x32);
					table[i].league_fate = Promoted;
					*a5 = 1;
					return 0;
				case Promoted:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
		else {
			WORD num_teams = comp_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case BottomPlayoff:
					staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					table[i].league_fate = Relegated;
					*a5 = 1;
					return 0;
				case Relegated:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	else {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) por_first_set_table_fate()
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
		call por_first_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void por_first_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		comp_stats* d2_comp_data = (comp_stats*)get_loaded_league(POR_SECOND_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == POR_SECOND_9CF()) {
			ret = (BYTE*)sub_4A4850((BYTE*)d2_comp_data->f8, club);
			if (!ret) return;
			ret_current = 3;
			ret_min = 3;
			ret_max = 3;
		}
		else {
			ret_current = 16;
			ret_min = 16;
			ret_max = 16;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) por_first_reputation_calc_c()
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
		call por_first_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_por_first()
{
	WriteVTablePtr(por_first_vtable, VTableSubsRounds, (DWORD)&por_first_subs_c);
	WriteVTablePtr(por_first_vtable, VTableInitFree, (DWORD)&por_first_free_c);
	WriteVTablePtr(por_first_vtable, VTableEoSUpdate, (DWORD)&por_first_update_c);
	WriteVTablePtr(por_first_vtable, VTableFixtures, (DWORD)&por_first_fixtures_c);
	WriteVTablePtr(por_first_vtable, VTableReputationCalc, (DWORD)&por_first_reputation_calc_c);
	WriteVTablePtr(por_first_vtable, VTablePlayoffQual, (DWORD)&por_first_playoffs_create);
	WriteVTablePtr(por_first_vtable, VTableTableFates, (DWORD)&por_first_set_table_fate);
	WriteVTablePtr(por_first_vtable, VTablePromRelUpdate, (DWORD)&por_first_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(por_first_vtable, VTable21, 0x4110b0);
}
