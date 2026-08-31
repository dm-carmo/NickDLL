#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* rus_premier_vtable = (DWORD*)0x96F278;

void rus_premier_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GamesWonTiebreaker;
	comp_data->tiebreaker_3 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_4 = GoalsForTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 2;
	comp_data->relegations = 2;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = RUS_FIRST_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) rus_premier_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_premier_subs
		add esp, 0x4
		ret
	}
}

void __fastcall rus_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(RUS_SECOND_A_9CF());
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

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(RUS_SECOND_B_9CF(), NATION_RUSSIA_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != RUS_PREMIER_9CF()
			&& ret_club->ClubDivision->ClubCompID != RUS_FIRST_9CF())
		{
			available_clubs.erase(available_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size() + (comp_data->year == 2026 ? 3 : 0), true);

	for (cm3_clubs* c : relegated_clubs) {
		cm3_club_comps* bottomDivision = get_comp(RUS_SECOND_B_9CF());
		relegate_club_6831A0((BYTE*)c, (DWORD)bottomDivision, 1);
		c->ClubReserveDivision = 0;
	}

	for (cm3_clubs* c : promoted_clubs) {
		cm3_club_comps* topDivision = get_comp(RUS_SECOND_A_9CF());
		promote_club_6830B0((BYTE*)c, (DWORD)topDivision, 1);
	}
}

void __fastcall rus_check_reserve_teams(BYTE* _this) {
	comp_stats* rus_first_data = (comp_stats*)get_loaded_league(RUS_FIRST_9CF());
	comp_stats* rus_second_a_data = (comp_stats*)get_loaded_league(RUS_SECOND_A_9CF());
	// Check teams from L3: promoted but main team relegated from L1 - remove promotion + remove one relegation from L2
	// Check teams from L3: main team relegated from L2 - add relegation + remove one relegation
	comp_stats* l3_curr_stage = rus_second_a_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			l3_curr_stage = (comp_stats*)(rus_second_a_data->stages[al]);
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
					if (ret_club->ClubDivision->ClubCompID == RUS_PREMIER_9CF()) {
						team_league_stats* main_club_data = get_team_league_stats(RUS_PREMIER_9CF(), ret_club);
						// If the main team was relegated
						if (main_club_data->league_fate == Relegated) {
							table_teams[num].league_fate = Eliminated;
							// Do not promote the reserve team, and relegate one less team from the second league
							team_league_stats* d2_table = (team_league_stats*)rus_first_data->team_league_table;
							for (WORD i = rus_first_data->n_teams - rus_first_data->relegations - rus_first_data->rele_playoff; i < rus_first_data->n_teams; i++) {
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
					if (ret_club->ClubDivision->ClubCompID == RUS_FIRST_9CF()) {
						team_league_stats* main_club_data = get_team_league_stats(RUS_FIRST_9CF(), ret_club);
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
	// Check teams from L2: main team relegated from L1 - add relegation + remove one relegation
	for (WORD num = 0; num < rus_first_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)rus_first_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			// If reserve team was not relegated
			if (table_teams[num].league_fate != Relegated) {
				// If main team is in the first league
				if (ret_club->ClubDivision->ClubCompID == RUS_PREMIER_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(RUS_PREMIER_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from the second league
						team_league_stats* d2_table = (team_league_stats*)rus_first_data->team_league_table;
						for (WORD i = rus_first_data->n_teams - rus_first_data->relegations - rus_first_data->rele_playoff; i < rus_first_data->n_teams; i++) {
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

void rus_premier_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* rus_first = get_loaded_league(RUS_FIRST_9CF());
	v1 = *(DWORD*)rus_first;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(rus_first);
	process_promotion_relegation_689C80(_this, _this, rus_first, 1, a2, -1, -1);

	BYTE* rus_second_a = get_loaded_league(RUS_SECOND_A_9CF());
	comp_stats* rus_second_a_data = (comp_stats*)rus_second_a;
	v1 = *(DWORD*)rus_second_a;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(rus_second_a);

	process_promotion_relegation_689C80(_this, rus_first, rus_second_a, 1, a2, -1, -1);
	BYTE* rus_second_a_grp = (BYTE*)rus_second_a_data->stages[0];
	process_promotion_relegation_689C80(_this, rus_first, rus_second_a_grp, 1, a2, -1, -1);
}

void __declspec(naked) rus_premier_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call rus_premier_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void sort_rus_second_a_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(RUS_SECOND_A_9CF());

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		cm3_clubs* club = available_clubs[i];
		if (club->ClubLastDivision) {
			if (club->ClubLastDivision->ClubCompID == RUS_FIRST_9CF())
			{
				club->ClubReserveDivision = get_comp(RUS_SECOND_A_GOLD_9CF());
			}
			else if (club->ClubLastDivision->ClubCompID == RUS_SECOND_A_GOLD_9CF())
			{
				if (club->ClubLastPosition < 7) club->ClubReserveDivision = get_comp(RUS_SECOND_A_GOLD_9CF());
				else club->ClubReserveDivision = get_comp(RUS_SECOND_A_SILVER_9CF());
			}
			else if (club->ClubLastDivision->ClubCompID == RUS_SECOND_A_SILVER_9CF())
			{
				if (club->ClubLastPosition < 5) club->ClubReserveDivision = get_comp(RUS_SECOND_A_GOLD_9CF());
				else club->ClubReserveDivision = get_comp(RUS_SECOND_A_SILVER_9CF());
			}
			else club->ClubReserveDivision = get_comp(RUS_SECOND_A_SILVER_9CF());
		}
		else club->ClubReserveDivision = get_comp(RUS_SECOND_A_SILVER_9CF());
	}
}

void __fastcall rus_fake_lower_relegation(BYTE* _this)
{
	vector<cm3_clubs*> d2b_clubs = find_clubs_of_comp(RUS_SECOND_B_9CF(), NATION_RUSSIA_9CF());
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_RUSSIA_9CF());
	unsigned int num_to_swap = d2b_clubs.size() / 8;
	if (lower_clubs.size() < num_to_swap) num_to_swap = lower_clubs.size();

	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(lower_clubs, num_to_swap, true);
	vector<cm3_clubs*> relegated_clubs = get_random_weighted_clubs(d2b_clubs, num_to_swap, false);

	for (unsigned int j = 0; j < num_to_swap; j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}
}

char rus_premier_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* rus_first = get_loaded_league(RUS_FIRST_9CF());
	BYTE* rus_second_a = get_loaded_league(RUS_SECOND_A_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be professional
	update_club_pro_status_68A980(rus_first, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(rus_first, Professional, -3, Relegated, 1);
	// All teams that were not relegated from D3 must be professional
	// All teams that were relegated from D3 must be semi-professional
	update_club_pro_status_68A980(rus_second_a, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(rus_second_a, SemiProfessional, -3, Relegated, 1);
	update_club_pro_status_68A980(rus_second_a, SemiProfessional, -3, Relegated, 0);
	comp_stats* rus_second_a_data = (comp_stats*)rus_second_a;
	BYTE* rus_second_a_grp = (BYTE*)rus_second_a_data->stages[0];
	update_club_pro_status_68A980(rus_second_a_grp, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(rus_second_a_grp, SemiProfessional, -3, Relegated, 1);
	update_club_pro_status_68A980(rus_second_a_grp, SemiProfessional, -3, Relegated, 0);

	rus_check_reserve_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	rus_premier_prom_rel_update(_this, 1);

	rus_non_league_promotion(_this);
	rus_fake_lower_relegation(_this);
	sort_rus_second_a_clubs();

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
	rus_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("rus_prm_prize_money"));
	data->f225 = 1;
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)rus_first;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(rus_first);

	v1 = *(DWORD*)rus_second_a;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(rus_second_a);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) rus_premier_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_premier_update
		add esp, 0x4
		ret
	}
}

void rus_premier_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = rus_premier_vtable;
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
	sub_682300(_this);
}

void rus_premier_free(BYTE* _this, BYTE a2) {
	rus_premier_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) rus_premier_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call rus_premier_free
		add esp, 0x8
		ret 4
	}
}

DWORD rus_premier_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddFixture(pMem, fixture_id, Date(year, 7, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 22), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
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

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 18), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 27), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 4, 2, 4, 0, 0, 2, 3);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) rus_premier_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call rus_premier_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void rus_premier_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = rus_premier_vtable;
	data->year = year;
	data->rules = RulesRussia;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 10000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	rus_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("rus_prm_prize_money"));
	data->f225 = 1;
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void rus_premier_playoff_under(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 4;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	int j = 0;
	for (int i = 0; i < total_teams && j < 3; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == BottomPlayoff) {
			*((DWORD*)(&pTeams[j])) = (DWORD)tls.club;
			j += 2;
		}
	}

	comp_stats* rus_first_data = (comp_stats*)get_loaded_league(RUS_FIRST_9CF());
	total_teams = rus_first_data->n_teams;
	table_teams = (team_league_stats*)(rus_first_data->team_league_table);
	j = 3;
	for (int i = 0; i < total_teams && j > 0; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[j])) = (DWORD)tls.club;
			j -= 2;
		}
	}
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
}

void rus_premier_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		BYTE* rus_first = get_loaded_league(RUS_FIRST_9CF());
		DWORD v1 = *(DWORD*)rus_first;
		char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(rus_first, 0, 1);
		if (ret != 0) {
			(*(void(__thiscall**)(BYTE*))(v1 + 0x94))(rus_first);
			current++;
			comp_data->current_stage = current;
			if (current == 0) {
				rus_premier_playoff_under(_this);
			}
		}
	}
}

void __declspec(naked) rus_premier_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call rus_premier_playoffs_c
		add esp, 0x4
		ret
	}
}

int rus_premier_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_club_comps* rus_first = get_comp(RUS_FIRST_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club->ClubDivision == rus_first) {
			comp_stats* rus_first_data = (comp_stats*)get_loaded_league(RUS_FIRST_9CF());
			WORD num_teams = rus_first_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(rus_first_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)rus_first, 0x32);
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

void __declspec(naked) rus_premier_set_table_fate()
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
		call rus_premier_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void rus_premier_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		comp_stats* d2_comp_data = (comp_stats*)get_loaded_league(RUS_FIRST_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == RUS_FIRST_9CF()) {
			ret = (BYTE*)sub_4A4850((BYTE*)d2_comp_data->f8, club);
			if (!ret) return;
			ret_current = 3;
			ret_min = 3;
			ret_max = 3;
		}
		else {
			ret_current = 13;
			ret_min = 13;
			ret_max = 13;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) rus_premier_reputation_calc_c()
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
		call rus_premier_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_rus_premier()
{
	WriteVTablePtr(rus_premier_vtable, VTableSubsRounds, (DWORD)&rus_premier_subs_c);
	WriteVTablePtr(rus_premier_vtable, VTableInitFree, (DWORD)&rus_premier_free_c);
	WriteVTablePtr(rus_premier_vtable, VTableEoSUpdate, (DWORD)&rus_premier_update_c);
	WriteVTablePtr(rus_premier_vtable, VTableFixtures, (DWORD)&rus_premier_fixtures_c);
	WriteVTablePtr(rus_premier_vtable, VTableReputationCalc, (DWORD)&rus_premier_reputation_calc_c);
	WriteVTablePtr(rus_premier_vtable, VTablePlayoffQual, (DWORD)&rus_premier_playoffs_create);
	WriteVTablePtr(rus_premier_vtable, VTableTableFates, (DWORD)&rus_premier_set_table_fate);
	WriteVTablePtr(rus_premier_vtable, VTablePromRelUpdate, (DWORD)&rus_premier_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(rus_premier_vtable, VTableShowThirdInHistory, 0x4110b0);
}
