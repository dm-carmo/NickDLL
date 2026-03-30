#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* nor_premier_vtable = (DWORD*)0x96DED4;

void nor_premier_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 2;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = NOR_FIRST_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) nor_premier_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call nor_premier_subs
		add esp, 0x4
		ret
	}
}

void __fastcall nor_check_reserve_teams(BYTE* _this) {
	comp_stats* nor_premier_data = (comp_stats*)get_loaded_league(NOR_PREMIER_9CF());
	comp_stats* nor_first_data = (comp_stats*)get_loaded_league(NOR_FIRST_9CF());
	comp_stats* nor_second_data = (comp_stats*)get_loaded_league(NOR_SECOND_9CF());
	BYTE* nor_third = get_loaded_league(NOR_THIRD_9CF());
	if (nor_third) {
		// Check teams from D3: main team relegated from D1 - add relegation
		comp_stats* nor_third_data = (comp_stats*)nor_third;
		comp_stats* curr_stage = nor_third_data;
		for (char al = -1; al < 5; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(nor_third_data->stages[al]);
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
						if (ret_club->ClubDivision->ClubCompID == NOR_FIRST_9CF()) {
							team_league_stats* main_club_data = get_team_league_stats(NOR_FIRST_9CF(), ret_club);
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
	// Check teams from D2: main team relegated from PRM - add relegation + remove one relegation
	comp_stats* curr_stage = nor_second_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(nor_second_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats* table_teams = (team_league_stats*)curr_stage->team_league_table;
			DWORD is_main_club;
			cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
			// If it is a reserve team
			if (ret_club && !is_main_club)
			{
				// If reserve team was not relegated
				if (table_teams[num].league_fate != Relegated) {
					// If main team is in the premier league
					if (ret_club->ClubDivision->ClubCompID == NOR_PREMIER_9CF()) {
						team_league_stats* main_club_data = get_team_league_stats(NOR_PREMIER_9CF(), ret_club);
						// If the main team was relegated
						if (main_club_data->league_fate == Relegated) {
							table_teams[num].league_fate = Relegated;
							// Relegate the reserve team, and relegate one less team from the second league
							for (WORD i = curr_stage->n_teams - curr_stage->relegations; i < curr_stage->n_teams; i++) {
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
}

void nor_premier_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* nor_first = get_loaded_league(NOR_FIRST_9CF());
	v1 = *(DWORD*)nor_first;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(nor_first);
	sub_689C80(_this, _this, nor_first, 1, a2, -1, -1);

	BYTE* nor_second = get_loaded_league(NOR_SECOND_9CF());
	comp_stats* nor_second_data = (comp_stats*)nor_second;
	v1 = *(DWORD*)nor_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(nor_second);

	BYTE* nor_second_grp = (BYTE*)nor_second_data->stages[0];
	v1 = *(DWORD*)nor_second_grp;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(nor_second_grp);

	sub_689C80(_this, nor_first, nor_second, 1, a2, -1, -1);
	sub_689C80(_this, nor_first, nor_second_grp, 1, a2, -1, -1);

	BYTE* nor_third = get_loaded_league(NOR_THIRD_9CF());
	if (nor_third) {
		comp_stats* nor_third_data = (comp_stats*)nor_third;
		v1 = *(DWORD*)nor_third;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(nor_third);
		for (int i = 0; i < 3; i++)
		{
			BYTE* nor_third_grp = (BYTE*)nor_third_data->stages[i];
			v1 = *(DWORD*)nor_third_grp;
			(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(nor_third_grp);
		}

		sub_689C80(_this, nor_second, nor_third, 1, a2, -1, -1);
		for (int i = 0; i < 5; i++)
		{
			BYTE* nor_third_grp = (BYTE*)nor_third_data->stages[i];
			sub_689C80(_this, nor_second, nor_third_grp, 1, a2, -1, -1);
		}

		sub_689C80(_this, nor_second_grp, nor_third, 1, a2, -1, -1);
		for (int i = 0; i < 5; i++)
		{
			BYTE* nor_third_grp = (BYTE*)nor_third_data->stages[i];
			sub_689C80(_this, nor_second_grp, nor_third_grp, 1, a2, -1, -1);
		}
	}
}

void __declspec(naked) nor_premier_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call nor_premier_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall nor_second_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	BYTE* comp_bytes = get_loaded_league(NOR_SECOND_9CF());
	comp_stats* comp_data = (comp_stats*)comp_bytes;
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

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(NOR_THIRD_9CF(), NATION_NORWAY_9CF());
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
		if (ret_club && !is_main_club && (!ret_club->ClubDivision || ret_club->ClubDivision->ClubCompID != NOR_PREMIER_9CF()))
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

void __fastcall nor_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	BYTE* comp_bytes = get_loaded_league(NOR_THIRD_9CF());
	comp_stats* comp_data = (comp_stats*)comp_bytes;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 5; al++) {
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

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_NORWAY_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	int max_to_check = (available_clubs.size() > 24 ? 24 : available_clubs.size());
	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* clubToRelegate = relegated_clubs[i];
		cm3_clubs* available = available_clubs[availableIdx];

		//dprintf("Swapping Teams: %s (%s) <-> %s (%s)\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, available->ClubName, available->ClubDivision->ClubCompName);
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)available, &is_main_club, 1);
		if (ret_club && !is_main_club && (!ret_club->ClubDivision || ret_club->ClubDivision->ClubCompID != NOR_PREMIER_9CF()
			|| ret_club->ClubDivision->ClubCompID != NOR_FIRST_9CF()))
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

void sort_nor_second_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(NOR_SECOND_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitudeInv);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 14) available_clubs[i]->ClubReserveDivision = get_comp(NOR_SECOND_G1_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(NOR_SECOND_G2_9CF());
	}
}

void sort_nor_third_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(NOR_THIRD_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 14) available_clubs[i]->ClubReserveDivision = get_comp(NOR_THIRD_G1_9CF());
		else if (i < 28) available_clubs[i]->ClubReserveDivision = get_comp(NOR_THIRD_G2_9CF());
		else if (i < 42) available_clubs[i]->ClubReserveDivision = get_comp(NOR_THIRD_G3_9CF());
		else if (i < 56) available_clubs[i]->ClubReserveDivision = get_comp(NOR_THIRD_G4_9CF());
		else if (i < 70) available_clubs[i]->ClubReserveDivision = get_comp(NOR_THIRD_G5_9CF());
		else available_clubs[i]->ClubReserveDivision = get_comp(NOR_THIRD_G6_9CF());
	}
}

char nor_premier_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;

	BYTE* nor_first = get_loaded_league(NOR_FIRST_9CF());
	BYTE* nor_second = get_loaded_league(NOR_SECOND_9CF());
	BYTE* nor_third = get_loaded_league(NOR_THIRD_9CF());

	// All teams that were in D1 must be professional
	sub_68A980(_this, Professional, Relegated, -3, 1);
	sub_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were not relegated from D2 must be semi-professional or higher
	// All teams that were relegated from D2 must be semi-professional
	sub_68A980(nor_first, SemiProfessional, Relegated, -3, 1);
	sub_68A980(nor_first, SemiProfessional, -3, Relegated, 0);
	// All teams that were not relegated from D3 must be semi-professional
	comp_stats* nor_second_data = (comp_stats*)nor_second;
	BYTE* nor_second_grp = (BYTE*)nor_second_data->stages[0];
	sub_68A980(nor_second, SemiProfessional, Relegated, -3, 1);
	sub_68A980(nor_second, SemiProfessional, Relegated, -3, 0);
	sub_68A980(nor_second_grp, SemiProfessional, Relegated, -3, 1);
	sub_68A980(nor_second_grp, SemiProfessional, Relegated, -3, 0);
	if (nor_third) {
		comp_stats* nor_third_data = (comp_stats*)nor_third;
		// All teams that were relegated from D4 must be amateur
		sub_68A980(nor_third, Amateur, -3, Relegated, 0);
		for (int i = 0; i < 5; i++)
		{
			BYTE* nor_third_grp = (BYTE*)nor_third_data->stages[i];
			sub_68A980(nor_third_grp, Amateur, -3, Relegated, 0);
		}
	}

	nor_check_reserve_teams(_this);
	nor_premier_prom_rel_update(_this, 1);

	if (nor_third) {
		nor_non_league_promotion(_this);
		sort_nor_third_clubs();
	}
	else {
		nor_second_relegation(_this);
	}
	sort_nor_second_clubs();

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
	nor_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, 139266);
	data->f225 = 1;
	SetupTVMoney(_this, 271536, 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)nor_first;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(nor_first);

	v1 = *(DWORD*)nor_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(nor_second);

	if (nor_third) {
		v1 = *(DWORD*)nor_third;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(nor_third);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) nor_premier_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call nor_premier_update
		add esp, 0x4
		ret
	}
}

void nor_premier_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = nor_premier_vtable;
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

void nor_premier_free(BYTE* _this, BYTE a2) {
	nor_premier_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) nor_premier_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call nor_premier_free
		add esp, 0x8
		ret 4
	}
}

DWORD nor_premier_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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
		AddFixture(pMem, fixture_id, Date(year, 3, 30), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 6), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 21), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 27), year, Sunday);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 4), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 11), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 16), year, Friday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 25), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 1), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 22), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 29), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 13), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 20), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 3), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 10), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 17), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 24), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 31), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 14), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 21), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 28), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 5), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 19), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 9), year, Sunday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 30), year, Sunday);

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
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 1), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 7), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 2, 1, 2, 0, 0, 2, 4);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) nor_premier_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call nor_premier_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void nor_premier_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = nor_premier_vtable;
	data->year = year;
	data->rules = RulesNorwayLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 3000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	nor_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, 139266);
	data->f225 = 1;
	SetupTVMoney(_this, 271536, 0);
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

void nor_premier_playoff_under(BYTE* _this) {
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

	comp_stats* nor_first_data = (comp_stats*)get_loaded_league(NOR_FIRST_9CF());
	total_teams = nor_first_data->n_teams;
	table_teams = (team_league_stats*)(nor_first_data->team_league_table);
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

void nor_premier_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		BYTE* nor_first = get_loaded_league(NOR_FIRST_9CF());
		comp_stats* nor_first_data = (comp_stats*)nor_first;
		BYTE* prom_playoff = (BYTE*)nor_first_data->stages[0];
		if (prom_playoff) {
			DWORD v1 = *(DWORD*)prom_playoff;
			char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(prom_playoff, 0, 1);
			if (ret != 0) {
				current++;
				comp_data->current_stage = current;
				if (current == 0) {
					nor_premier_playoff_under(_this);
				}
			}
		}
	}
}

void __declspec(naked) nor_premier_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call nor_premier_playoffs_c
		add esp, 0x4
		ret
	}
}

int nor_premier_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* nor_first = get_comp(NOR_FIRST_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club_ptr->ClubDivision == nor_first) {
			comp_stats* nor_first_data = (comp_stats*)get_loaded_league(NOR_FIRST_9CF());
			WORD num_teams = nor_first_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(nor_first_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)nor_first, 0x32);
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

void __declspec(naked) nor_premier_set_table_fate()
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
		call nor_premier_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void nor_premier_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		comp_stats* d2_comp_data = (comp_stats*)get_loaded_league(NOR_FIRST_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == NOR_FIRST_9CF()) {
			ret = (BYTE*)sub_4A4850((BYTE*)d2_comp_data->f8, club);
			if (!ret) return;
			ret_current = 3;
			ret_min = 3;
			ret_max = 3;
		}
		else {
			ret_current = 14;
			ret_min = 14;
			ret_max = 14;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) nor_premier_reputation_calc_c()
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
		call nor_premier_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_nor_premier()
{
	WriteVTablePtr(nor_premier_vtable, VTableSubsRounds, (DWORD)&nor_premier_subs_c);
	WriteVTablePtr(nor_premier_vtable, VTableInitFree, (DWORD)&nor_premier_free_c);
	WriteVTablePtr(nor_premier_vtable, VTableEoSUpdate, (DWORD)&nor_premier_update_c);
	WriteVTablePtr(nor_premier_vtable, VTableFixtures, (DWORD)&nor_premier_fixtures_c);
	WriteVTablePtr(nor_premier_vtable, VTableReputationCalc, (DWORD)&nor_premier_reputation_calc_c);
	WriteVTablePtr(nor_premier_vtable, VTablePlayoffQual, (DWORD)&nor_premier_playoffs_create);
	WriteVTablePtr(nor_premier_vtable, VTableTableFates, (DWORD)&nor_premier_set_table_fate);
	WriteVTablePtr(nor_premier_vtable, VTablePromRelUpdate, (DWORD)&nor_premier_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(nor_premier_vtable, VTable21, 0x4110b0);
}
