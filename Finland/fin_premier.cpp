#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* fin_premier_vtable = (DWORD*)0x96A4C0;

int fin_premier_7F3220(DWORD a1, DWORD a2) {
	BYTE split_pos = 6;
	WORD stage1_games = 22;
	team_league_stats* tls1 = (team_league_stats*)a1;
	team_league_stats* tls2 = (team_league_stats*)a2;

	BYTE bl = ((BYTE*)tls1->position_history)[stage1_games - 1];
	BYTE al = (bl >= split_pos) + 1;
	bl = ((BYTE*)tls2->position_history)[stage1_games - 1];
	BYTE cl = (bl >= split_pos) + 1;
	return al - cl;
}

void __fastcall fin_check_reserve_teams(BYTE* _this) {
	comp_stats* fin_premier_data = (comp_stats*)get_loaded_league(FIN_PREMIER_9CF());
	comp_stats* fin_first_data = (comp_stats*)get_loaded_league(FIN_FIRST_9CF());
	comp_stats* fin_second_data = (comp_stats*)get_loaded_league(FIN_SECOND_9CF());
	BYTE* fin_third = get_loaded_league(FIN_THIRD_9CF());
	if (fin_third) {
		// Check teams from D3: main team relegated from D2 - add relegation
		comp_stats* fin_third_data = (comp_stats*)fin_third;
		comp_stats* curr_stage = fin_third_data;
		for (char al = -1; al < 2; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(fin_third_data->stages[al]);
			}
			for (WORD num = 0; num < curr_stage->n_teams; num++) {
				team_league_stats* table_teams = (team_league_stats*)curr_stage->team_league_table;
				DWORD is_main_club;
				cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
				// If it is a reserve team
				if (ret_club && !is_main_club)
				{
					// If team was not relegated
					if (table_teams[num].league_fate != Relegated) {
						// If main team is in the first league
						if (ret_club->ClubDivision->ClubCompID == FIN_SECOND_9CF()) {
							team_league_stats* main_club_data = get_team_league_stats(FIN_SECOND_9CF(), ret_club);
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
	// Check teams from D2: main team relegated from D1 - add relegation + remove one relegation
	for (WORD num = 0; num < fin_second_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)fin_second_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			// If reserve team was not relegated
			if (table_teams[num].league_fate != Relegated) {
				// If main team is in the premier league
				if (ret_club->ClubDivision->ClubCompID == FIN_FIRST_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(FIN_FIRST_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from the second league
						for (WORD i = fin_second_data->n_teams - fin_second_data->relegations; i < fin_second_data->n_teams; i++) {
							if (i != num && table_teams[i].league_fate == Relegated) {
								table_teams[i].league_fate = Eliminated;
								break;
							}
						}
					}
				}
			}
		}
	}
	// Check teams from D1: main team relegated from PEM - add relegation + remove one relegation
	for (WORD num = 0; num < fin_first_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)fin_first_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			// If reserve team was not relegated
			if (table_teams[num].league_fate != Relegated) {
				// If main team is in the premier league
				if (ret_club->ClubDivision->ClubCompID == FIN_PREMIER_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(FIN_PREMIER_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from the first league
						for (WORD i = fin_first_data->n_teams - fin_first_data->relegations; i < fin_first_data->n_teams; i++) {
							if (i != num && table_teams[i].league_fate == Relegated) {
								table_teams[i].league_fate = Eliminated;
								break;
							}
						}
					}
				}
			}
		}
	}
}

void fin_premier_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* fin_first = get_loaded_league(FIN_FIRST_9CF());
	v1 = *(DWORD*)fin_first;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(fin_first);
	sub_689C80(_this, _this, fin_first, 1, a2, -1, -1);

	BYTE* fin_second = get_loaded_league(FIN_SECOND_9CF());
	comp_stats* fin_second_data = (comp_stats*)fin_second;
	v1 = *(DWORD*)fin_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(fin_second);

	sub_689C80(_this, fin_first, fin_second, 1, a2, -1, -1);

	BYTE* fin_third = get_loaded_league(FIN_THIRD_9CF());
	if (fin_third) {
		comp_stats* fin_third_data = (comp_stats*)fin_third;
		v1 = *(DWORD*)fin_third;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(fin_third);
		for (int i = 0; i < 2; i++)
		{
			BYTE* fin_third_grp = (BYTE*)fin_third_data->stages[i];
			v1 = *(DWORD*)fin_third_grp;
			(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(fin_third_grp);
		}

		sub_689C80(_this, fin_second, fin_third, 1, a2, -1, -1);
		for (int i = 0; i < 2; i++)
		{
			BYTE* fin_third_grp = (BYTE*)fin_third_data->stages[i];
			sub_689C80(_this, fin_second, fin_third_grp, 1, a2, -1, -1);
		}
	}
}

void __declspec(naked) fin_premier_prom_rel_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call fin_premier_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

DWORD fin_premier_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		*num_rounds = 32;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 5), year, Saturday);
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 12), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 19), year, Saturday);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 2), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 10), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 17), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 6, 14), year, Saturday);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 18), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 2), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 13), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 20), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 24), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Sunday);
		// next phase starts here
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 19), year, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 22), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 30), year, Thursday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 3), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Sunday);

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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 10), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 13), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 2, 1, 2, 0, 0, 2, 3);

		return (DWORD)pMem;
	}
	else if (stage_idx < 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		*num_rounds = 10;
		*stage_name_id = ChampionshipGroup + stage_idx - 1;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 19), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 22), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 30), year, Thursday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 3), year, Monday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) fin_premier_fixtures_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fin_premier_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void fin_premier_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	*((DWORD*)(_this + 0xA7)) = 32; // total number of games each team will play
	*((DWORD*)(_this + 0xA3)) = 0;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = 1;
	comp_data->tiebreaker_2 = 2;
	comp_data->tiebreaker_3 = 3;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 1;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = FIN_FIRST_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	//call vtable +3C which is actually add fixtures function
	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) fin_premier_subs_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call fin_premier_subs
		add esp, 0x4
		ret
	}
}

void __fastcall fin_second_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	BYTE* comp_bytes = get_loaded_league(FIN_SECOND_9CF());
	comp_stats* comp_data = (comp_stats*)comp_bytes;
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Relegated) {
			relegated_clubs.push_back(table_pos.club);
		}
	}

	vector<cm3_clubs*> available_clubs;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = get_club(i);
		if (club)
		{
			if (club->ClubDivision && club->ClubNation)
			{
				DWORD compID = club->ClubDivision->ClubCompID;
				DWORD nationID = club->ClubNation->NationID;
				if (nationID == NATION_FINLAND_9CF() && compID == FIN_THIRD_9CF())
				{
					available_clubs.push_back(club);
				}
			}
		}
	}

	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	int max_to_check = (available_clubs.size() > 4 ? 4 : available_clubs.size());
	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* clubToRelegate = relegated_clubs[i];
		cm3_clubs* available = available_clubs[availableIdx];

		//dprintf("Swapping Teams: %s (%s) <-> %s (%s)\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, available->ClubName, available->ClubDivision->ClubCompName);
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)available, &is_main_club, 1);
		if (ret_club && !is_main_club && (!ret_club->ClubDivision || ret_club->ClubDivision->ClubCompID != FIN_PREMIER_9CF()
			|| ret_club->ClubDivision->ClubCompID != FIN_FIRST_9CF()))
			i--;
		else
		{
			cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
			cm3_club_comps* bottomDivision = available->ClubDivision;
			relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
			promote_club_6830B0((BYTE*)available, (DWORD)topDivision, 1);
			clubToRelegate->ClubReserveDivision = 0;
		}

		available_clubs.erase(available_clubs.begin() + availableIdx);
	}
}

void __fastcall fin_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	BYTE* comp_bytes = get_loaded_league(FIN_THIRD_9CF());
	comp_stats* comp_data = (comp_stats*)comp_bytes;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				//dprintf("Relegating club from Kakkonen: %s\n", table_pos.club->ClubNameShort);
				relegated_clubs.push_back(table_pos.club);
			}
		}
	}

	vector<cm3_clubs*> available_clubs;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = get_club(i);
		if (club)
		{
			if (club->ClubDivision && club->ClubNation)
			{
				DWORD compID = club->ClubDivision->ClubCompID;
				DWORD nationID = club->ClubNation->NationID;
				if (nationID == NATION_FINLAND_9CF() && compID == FIN_LOWER_9CF())
				{
					available_clubs.push_back(club);
				}
			}
		}
	}

	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	int max_to_check = (available_clubs.size() > 10 ? 10 : available_clubs.size());
	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* clubToRelegate = relegated_clubs[i];
		cm3_clubs* available = available_clubs[availableIdx];

		//dprintf("Swapping Teams: %s (%s) <-> %s (%s)\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, available->ClubName, available->ClubDivision->ClubCompName);
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)available, &is_main_club, 1);
		if (ret_club && !is_main_club && (!ret_club->ClubDivision || ret_club->ClubDivision->ClubCompID != FIN_PREMIER_9CF()
			|| ret_club->ClubDivision->ClubCompID != FIN_FIRST_9CF() || ret_club->ClubDivision->ClubCompID != FIN_SECOND_9CF()))
			i--;
		else
		{
			cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
			cm3_club_comps* bottomDivision = available->ClubDivision;
			relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
			promote_club_6830B0((BYTE*)available, (DWORD)topDivision, 1);
			clubToRelegate->ClubReserveDivision = 0;
		}

		available_clubs.erase(available_clubs.begin() + availableIdx);
	}
}

void sort_fin_third_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(FIN_THIRD_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitudeInv);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 10) available_clubs[i]->ClubReserveDivision = get_comp(FIN_THIRD_A_9CF());
		else if (i < 20) available_clubs[i]->ClubReserveDivision = get_comp(FIN_THIRD_B_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(FIN_THIRD_C_9CF());
	}
}

char fin_premier_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	fin_check_reserve_teams(_this);
	fin_premier_prom_rel_update(_this, 1);

	BYTE* fin_third = get_loaded_league(FIN_THIRD_9CF());
	if (fin_third) {
		fin_non_league_promotion(_this);
		sort_fin_third_clubs();
	}
	else {
		fin_second_relegation(_this);
	}

	sub_687970(_this, ebx);
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
		}
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->current_stage = -1;
	fin_premier_subs(_this);
	AddTeams(_this);
	add_tv_money_683010(_this, 45000, 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	BYTE* fin_first = get_loaded_league(FIN_FIRST_9CF());
	BYTE* fin_second = get_loaded_league(FIN_SECOND_9CF());

	v1 = *(DWORD*)fin_first;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(fin_first);

	v1 = *(DWORD*)fin_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(fin_second);

	if (fin_third) {
		v1 = *(DWORD*)fin_third;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(fin_third);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) fin_premier_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call fin_premier_update
		add esp, 0x4
		ret
	}
}

void fin_premier_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = fin_premier_vtable;
	data->year = year;
	data->rules = 0xa;
	int loaded = sub_687B10(_this, 1);
	if (loaded) {
		if (data->n_rounds != 4) return;
		*((DWORD*)(_this + 0xA3)) = (DWORD)&fin_premier_7F3220;
		return;
	}
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	fin_premier_subs(_this);
	AddTeams(_this);
	add_tv_money_683010(_this, 45000, 0);
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

void fin_premier_split_under(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 6;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);

	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	for (int i = 0; i < 6; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)table_teams[i].club;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	DWORD v0 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 1, &num_rounds, &stage_name_id, 0);

	WORD year = comp_data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	short f217 = 3;
	create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
		comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, -1, stage_name_id, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v1 = *(DWORD*)pStage;
	(*(int(__thiscall**)(BYTE*, int))(v1))(pStage, 1);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);

	DWORD* pTeams2 = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	for (int i = 0; i < 6; i++) {
		*((DWORD*)(&pTeams2[i])) = (DWORD)table_teams[i + 6].club;
	}

	WORD num_rounds2 = 0;
	WORD stage_name_id2 = 0;
	BYTE* pFixtures2 = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 2, &num_rounds2, &stage_name_id2, 0);

	BYTE* pStage2 = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage2, _this, playoff_teams, pTeams2, 2, (DWORD)(comp_data->competition_db), pFixtures2, num_rounds2,
		comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, -1, stage_name_id2, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v2 = *(DWORD*)pStage2;
	(*(int(__thiscall**)(BYTE*, int))(v2))(pStage2, 1);
	sub_9452CA_free(pTeams2);
	sub_9452CA_free(pFixtures2);

	comp_data->n_rounds = 4;
	*((DWORD*)(_this + 0xA3)) = (DWORD)&fin_premier_7F3220;
}

char fin_premier_table_split(BYTE* _this, DWORD current_date, int a2) {
	if (a2) {
		comp_stats* comp_data = (comp_stats*)_this;
		if (comp_data->n_rounds == 2) {
			WORD num_teams = comp_data->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
			bool is_finished = true;
			for (int i = 0; i < num_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < 22) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				fin_premier_split_under(_this);
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) fin_premier_table_split_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fin_premier_table_split
		add esp, 0xc
		ret 8
	}
}

void fin_premier_playoff_under(BYTE* _this) {
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

	comp_stats* fin_first_data = (comp_stats*)get_loaded_league(FIN_FIRST_9CF());
	total_teams = fin_first_data->n_teams;
	table_teams = (team_league_stats*)(fin_first_data->team_league_table);
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

void fin_premier_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		BYTE* fin_first = get_loaded_league(FIN_FIRST_9CF());
		DWORD v1 = *(DWORD*)fin_first;
		char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(fin_first, 0, 1);
		if (ret != 0) {
			(*(void(__thiscall**)(BYTE*))(v1 + 0x94))(fin_first);
			current++;
			if (current == 0) {
				comp_data->current_stage = current;
				fin_premier_playoff_under(_this);
			}
		}
	}
}

void __declspec(naked) fin_premier_playoffs_create()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call fin_premier_playoffs_c
		add esp, 0x4
		ret
	}
}

int fin_premier_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* fin_first = get_comp(FIN_FIRST_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club_ptr->ClubDivision == fin_first) {
			comp_stats* fin_first_data = (comp_stats*)get_loaded_league(FIN_FIRST_9CF());
			WORD num_teams = fin_first_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(fin_first_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)fin_first, 0x32);
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

void __declspec(naked) fin_premier_set_table_fate()		// used as a __thiscall -> __cdecl converter
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
		call fin_premier_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void fin_premier_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		comp_stats* d2_comp_data = (comp_stats*)get_loaded_league(FIN_FIRST_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == FIN_FIRST_9CF()) {
			ret = (BYTE*)sub_4A4850((BYTE*)d2_comp_data->f8, club);
			if (!ret) return;
			ret_current = 2;
			ret_min = 2;
			ret_max = 2;
		}
		else {
			ret_current = 11;
			ret_min = 11;
			ret_max = 11;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) fin_premier_reputation_calc_c()		// used as a __thiscall -> __cdecl converter
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
		call fin_premier_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_fin_premier()
{
	WriteVTablePtr(fin_premier_vtable, VTableSubsRounds, (DWORD)&fin_premier_subs_c);
	WriteVTablePtr(fin_premier_vtable, VTableEoSUpdate, (DWORD)&fin_premier_update_c);
	WriteVTablePtr(fin_premier_vtable, VTableFixtures, (DWORD)&fin_premier_fixtures_c);
	WriteVTablePtr(fin_premier_vtable, VTableLeagueSplit, (DWORD)&fin_premier_table_split_c);
	WriteVTablePtr(fin_premier_vtable, VTableStageNews, (DWORD)0x7f3080); // Scotland stage news contains champ/rel group news
	WriteVTablePtr(fin_premier_vtable, VTableReputationCalc, (DWORD)&fin_premier_reputation_calc_c);
	WriteVTablePtr(fin_premier_vtable, VTablePlayoffQual, (DWORD)&fin_premier_playoffs_create);
	WriteVTablePtr(fin_premier_vtable, VTableTableFates, (DWORD)&fin_premier_set_table_fate);
	WriteVTablePtr(fin_premier_vtable, VTablePromRelUpdate, (DWORD)&fin_premier_prom_rel_update_c);
}