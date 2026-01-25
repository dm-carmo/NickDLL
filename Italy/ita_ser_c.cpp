#include <windows.h>
#include "Helpers\generic_functions.h"
#include "Helpers\constants.h"
#include "Structures\vtable.h"

vtable* ita_ser_c_vtable = new vtable((BYTE*)0x96E858, 0xB4);

void ita_ser_c_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(ita_ser_c_vtable->vtable_ptr);
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

void ita_ser_c_free(BYTE* _this, BYTE a2) {
	ita_ser_c_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) ita_ser_c_free_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call ita_ser_c_free
		add esp, 0x8
		ret 4
	}
}

void ita_ser_c_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = 1;
	comp_data->tiebreaker_2 = 2;
	comp_data->tiebreaker_3 = 0;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 9;
	comp_data->rele_playoff = 4;
	comp_data->relegations = 2;

	comp_data->promotes_to = *(DWORD*)0x9CF574;
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	//call vtable +3C which is actually add fixtures function
	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) ita_ser_c_subs_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_c_subs
		add esp, 0x4
		ret
	}
}

void ita_ser_c_init_teams(BYTE* _this) {
	vector<cm3_clubs*> orig_clubs = find_clubs_of_comp(Get9CF(0x9CF580), -1);
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(Get9CF(0x9CF58C));
	orig_clubs = find_clubs_of_comp(Get9CF(0x9CF584), -1);
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(Get9CF(0x9CF58C));
	orig_clubs = find_clubs_of_comp(Get9CF(0x9CF588), -1);
	for (cm3_clubs* c : orig_clubs) c->ClubDivision = get_comp(Get9CF(0x9CF58C));
	vector<string> c_a_clubs = {
		"UC AlbinoLeffe",
		"Alcione Milano",
		"Arzignano Valchiampo",
		"Union Brescia",
		"AS Cittadella",
		"Dolomiti Bellunesi",
		"AS Giana Erminio",
		"Inter U23",
		"Calcio Lecco 1912",
		"FC Lumezzane",
		"Novara FC",
		"CPR Ospitaletto",
		"US Pergolettese 1932",
		"Aurora Pro Patria",
		"FC Pro Vercelli 1892",
		"AC Renate",
		"AC Renate",
		"AC Trento",
		"US Triestina",
		"LR Vicenza",
		"Virtusvecomp Verona"
	};
	vector<string> c_b_clubs = {
		"SS Arezzo",
		"Ascoli Calcio",
		"Bra",
		"Campobasso FC",
		"AC Carpi",
		"Forlì FC",
		"AS Gubbio 1910",
		"Guidonia Montecelio 1937 FC",
		"Juventus Next Gen",
		"US Livorno 1915",
		"Milan Futuro",
		"AC Perugia Calcio",
		"US Pianese",
		"Pineto Calcio",
		"US Città di Pontedera",
		"Ravenna FC",
		"US Sambenedettese",
		"Ternana Calcio",
		"SEF Torres 1903",
		"Vis Pesaro 1898"
	};
	vector<string> c_c_clubs = {
		"AZ Picerno",
		"ASD Team Altamura",
		"Atalanta U23",
		"Benevento Calcio",
		"Casarano Calcio",
		"Casertana FC",
		"Catania FC",
		"Cavese 1919",
		"Audace Cerignola",
		"Cosenza Calcio",
		"FC Crotone",
		"Calcio Foggia 1920",
		"Giugliano Calcio 1928",
		"Latina Calcio 1932",
		"SS Monopoli 1966",
		"Potenza Calcio",
		"US Salernitana 1919",
		"Siracusa Calcio",
		"Sorrento 1945",
		"FC Trapani 1905"
	};
	comp_stats* data = (comp_stats*)_this;
	//data->n_teams = 20;
	cm3_club_comps* c_a = get_comp(Get9CF(0x9CF580));
	cm3_club_comps* c_b = get_comp(Get9CF(0x9CF584));
	cm3_club_comps* c_c = get_comp(Get9CF(0x9CF588));
	for (string s : c_a_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = data->competition_db;
		club->ClubReserveDivision = c_a;
	}
	for (string s : c_b_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = data->competition_db;
		club->ClubReserveDivision = c_b;
	}
	for (string s : c_c_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = data->competition_db;
		club->ClubReserveDivision = c_c;
	}
	//data->team_league_table = (DWORD*)sub_944E46_malloc(data->n_teams * league_team_list_sz);
	AddTeamsGroupLeague(_this, Get9CF(0x9CF580));
}

DWORD ita_ser_c_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		DWORD CompID = *(DWORD*)(*(DWORD*)(_this + 0x4));
		BYTE numberOfLeagueTeams = 20;
		*num_rounds = (numberOfLeagueTeams - 1) * ((comp_stats*)_this)->n_rounds;
		*stage_name_id = AlphabeticGroupStage + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 24), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 31), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 21), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 25), year, Thursday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 28), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 5), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 19), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 26), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 2), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 9), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 16), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 23), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 30), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 7), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 14), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 21), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 4), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 11), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 18), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 25), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 11), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 18), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 1), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 4), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 8), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 15), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 22), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 29), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 12), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 19), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 26), year, Sunday);

		if (fixture_id != 38) {
			string msg = "Wrong number of fixtures: " + to_string(fixture_id);
			create_message_box("Error", msg.c_str(), true);
		}

		return (DWORD)pMem;
	}
	else if (stage_idx == 2) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = PromotionPlayoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 27), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 5, 18, 9, 18, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 4), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 7), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 5, 12, 6, 3, 18, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 8), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 10, 5, 4, 21, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 15), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 18), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 8, 4, 3, 25, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 19), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 25), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 4, 2, 0, 0, 0, 2, 3);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 26), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 6, 3), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 6, 2, 1, 0, 0, 0, 2, 4);

		return (DWORD)pMem;
	}
	else if (stage_idx == 3) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = RelegationPlayoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 27), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 12, 6, 12, 0, 0, 2, 7);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) ita_ser_c_fixtures_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ita_ser_c_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void ita_ser_c_setup_groups(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD group_id = Get9CF(0x9CF584);
	if (idx > 0) group_id = Get9CF(0x9CF588);
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(data->n_teams * 4);

	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == data->competition_db->ClubCompID
			&& club->ClubReserveDivision && club->ClubReserveDivision->ClubCompID == group_id)
		{
			*((DWORD*)(&pTeams[teamsAdded++])) = (DWORD)club;
		}
	}
	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, 20, pTeams, 2, *(DWORD*)(_this + 0x4), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	//BYTE* _this, BYTE* main_comp, __int16 n_teams, DWORD* teamsPtr, __int16 n_rounds, int comp_id, const void *fixturesPtr, 
	// __int16 num_fixtures, char a9, char a10, char a11, int a12, int a13, __int16 year, char stage_num,
	// __int16 stage_name_id, char a17, char a18, __int16 a19, __int16 a20, __int16 a21, int a22, char a23
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void ita_7D2CD0(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	comp_stats* curr_stage = data;
	DWORD* f8 = data->f8;
	if (f8) {
		vector<cm3_clubs*> clubs;
		for (char al = -1; al < 2; al++) {
			clubs.clear();
			if (al >= 0) {
				curr_stage = (comp_stats*)(data->stages[al]);
			}
			for (WORD num = 0; num < curr_stage->n_teams; num++) {
				clubs.push_back(((team_league_stats*)curr_stage->team_league_table)[num].club);
			}
			sort(clubs.begin(), clubs.end(), compareClubRep);
			for (WORD i = 0; i < curr_stage->n_teams; i++) {
				sub_4A2540((BYTE*)f8, clubs[i], (i * 3 + 1));
			}
		}
	}
}

void __declspec(naked) ita_7D2CD0_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_7D2CD0
		add esp, 0x4
		ret
	}
}

cm3_clubs* SerieCCupLoser(comp_stats* comp_data)
{
	cm3_club_comps* comp = &(*club_comps)[Get9CF(0x9CF720)];
	cm3_clubs* last_runner_up = get_last_comp_runner_up(comp);
	if (!last_runner_up || !last_runner_up->ClubNation || !last_runner_up->ClubDivision || last_runner_up->ClubDivision->ClubCompID != comp_data->competition_db->ClubCompID) {
		return 0;
	}
	else {
		return last_runner_up;
	}
}

cm3_clubs* SerieCCupWinner(comp_stats* comp_data)
{
	cm3_club_comps* comp = &(*club_comps)[Get9CF(0x9CF720)];
	cm3_clubs* last_winner = get_last_comp_winner(comp);
	if (!last_winner || !last_winner->ClubNation || !last_winner->ClubDivision || last_winner->ClubDivision->ClubCompID != comp_data->competition_db->ClubCompID) {
		return 0;
	}
	else {
		return last_winner;
	}
}

pair<char, WORD> get_club_group_and_pos(comp_stats* comp_data, cm3_clubs* club) {
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			cm3_clubs* lge_club = ((team_league_stats*)curr_stage->team_league_table)[num].club;
			if (club == lge_club) {
				dprintf("Club: %s, finished in position: %d, in group: %d\n", club->ClubNameShort, num + 1, al + 2);
				return make_pair(al, num);
			}
		}
	}
	return make_pair(-2, 255);
}

void set_playoff_place(BYTE* _this, cm3_clubs* club) {
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (club == table_pos.club && table_pos.league_fate != TopPlayoff) {
				((team_league_stats*)curr_stage->team_league_table)[num].league_fate = TopPlayoff;
				staff_history_qualified_868DD0((BYTE*)*staff_history, (DWORD*)club, *(DWORD*)(_this + 0x4), PromotionPlayoff, None, 0x1E);
				return;
			}
		}
	}
}

void ita_c_playoffs_prom(BYTE* _this) {
	char stage_num = 2;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 28;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	char fallback_group = -1;
	bool use_fallback = false;
	BYTE seeds[28] = { 0,1,2,2,1,0,3,4,5,5,4,3,6,7,8,8,7,6,9,10,11,12,13,14,15,16,17,18 };

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs_rnd1;
	vector<cm3_clubs*> clubs_rnd2;
	vector<cm3_clubs*> clubs_rnd3;
	vector<cm3_clubs*> clubs_rnd4;
	clubs_rnd1.clear();
	clubs_rnd2.clear();
	clubs_rnd3.clear();
	clubs_rnd4.clear();
	// clubs for round 4 (2nd places)
	curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		// 0-index so 1 = second place
		cm3_clubs* r4_club = ((team_league_stats*)curr_stage->team_league_table)[1].club;
		clubs_rnd4.push_back(r4_club);
		dprintf("Club in round 4: 2nd place %s\n", r4_club->ClubNameShort);
	}
	// clubs for round 3 (3rd places + cup team)
	curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		// 0-index so 2 = third place
		cm3_clubs* r3_club = ((team_league_stats*)curr_stage->team_league_table)[2].club;
		clubs_rnd3.push_back(r3_club);
		dprintf("Club in round 3: 3rd place %s\n", r3_club->ClubNameShort);
	}
	cm3_clubs* c_winner = SerieCCupWinner(comp_data);
	if (c_winner) {
		pair<char, WORD> winner_grp_pos = get_club_group_and_pos(comp_data, c_winner);
		// if they finished 1st (promoted), 2nd or 3rd (already in later playoffs)
		// or if they are in relegation area
		if (winner_grp_pos.second < 3 || winner_grp_pos.second >= 14) {
			fallback_group = winner_grp_pos.first;
			cm3_clubs* c_loser = SerieCCupLoser(comp_data);
			if (c_loser) {
				pair<char, WORD> loser_grp_pos = get_club_group_and_pos(comp_data, c_loser);
				if (loser_grp_pos.second < 3 || loser_grp_pos.second >= 14) {
					// do not add club here
					use_fallback = true;
				}
				else {
					clubs_rnd3.push_back(c_loser);
					set_playoff_place(_this, c_loser);
					dprintf("Club in round 3: cup loser %s\n", c_loser->ClubNameShort);
				}
			}
			else use_fallback = true;
		}
		else {
			clubs_rnd3.push_back(c_winner);
			set_playoff_place(_this, c_winner);
			dprintf("Club in round 3: cup winner %s\n", c_winner->ClubNameShort);
		}
	}
	else {
		cm3_clubs* c_loser = SerieCCupLoser(comp_data);
		if (c_loser) {
			pair<char, WORD> loser_grp_pos = get_club_group_and_pos(comp_data, c_loser);
			if (loser_grp_pos.second < 3 || loser_grp_pos.second >= 14) {
				// do not add club here
				use_fallback = true;
			}
			else {
				clubs_rnd3.push_back(c_loser);
				set_playoff_place(_this, c_loser);
				dprintf("Club in round 3: cup loser %s\n", c_loser->ClubNameShort);
			}
		}
		else use_fallback = true;
	}
	if (use_fallback) {
		curr_stage = comp_data;
		if (fallback_group >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[fallback_group]);
		}
		// fallback 4th place from same group as winner
		cm3_clubs* fallback_club = ((team_league_stats*)curr_stage->team_league_table)[3].club;
		clubs_rnd3.push_back(fallback_club);
		dprintf("Club in round 3: fallback 4th place %s\n", fallback_club->ClubNameShort);
	}
	// clubs for round 2 (4th places)
	curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		// 0-index so 3 = fourth place
		int start_r2 = 3;
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		bool found_r2 = false;
		while (!found_r2) {
			cm3_clubs* r2_club = ((team_league_stats*)curr_stage->team_league_table)[start_r2++].club;
			if (vector_contains_club(clubs_rnd4, r2_club) || vector_contains_club(clubs_rnd3, r2_club))
				continue;
			else {
				clubs_rnd2.push_back(r2_club);
				found_r2 = true;
				dprintf("Club in round 2: %dth place %s\n", start_r2, r2_club->ClubNameShort);
			}
		}
	}
	// clubs for round 1 (5th to 10th places)
	curr_stage = comp_data;
	for (char al = -1; al < 2; al++) {
		// 0-index so 4 = fifth place
		int start_r1 = 4;
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD found_count = 0;
		while (found_count < 6) {
			cm3_clubs* r1_club = ((team_league_stats*)curr_stage->team_league_table)[start_r1++].club;
			if (vector_contains_club(clubs_rnd4, r1_club) || vector_contains_club(clubs_rnd3, r1_club) || vector_contains_club(clubs_rnd2, r1_club))
				continue;
			else {
				clubs_rnd1.push_back(r1_club);
				if (start_r1 > 10) set_playoff_place(_this, r1_club);
				dprintf("Club in round 1: %dth place %s\n", start_r1, r1_club->ClubNameShort);
				found_count++;
			}
		}
	}
	// add them all now
	int j = 0;
	for (size_t i = 0; i < clubs_rnd1.size(); i++) {
		*((DWORD*)(&pTeams[j++])) = (DWORD)clubs_rnd1[i];
	}
	for (size_t i = 0; i < clubs_rnd2.size(); i++) {
		*((DWORD*)(&pTeams[j++])) = (DWORD)clubs_rnd2[i];
	}
	for (size_t i = 0; i < clubs_rnd3.size(); i++) {
		*((DWORD*)(&pTeams[j++])) = (DWORD)clubs_rnd3[i];
	}
	for (size_t i = 0; i < clubs_rnd4.size(); i++) {
		*((DWORD*)(&pTeams[j++])) = (DWORD)clubs_rnd4[i];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, *(DWORD*)(_this + 0x4), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, seeds);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void ita_c_playoffs_rele(BYTE* _this) {
	char stage_num = 3;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 12;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	BYTE seeds[12] = { 0,1,1,0,2,3,3,2,4,5,5,4 };

	comp_stats* curr_stage = comp_data;
	vector<cm3_clubs*> clubs;
	for (char al = -1; al < 2; al++) {
		// 0-index so 14 = fifteenth place
		int start = 14;
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (int i = 0; i < 4; i++) {
			cm3_clubs* club = ((team_league_stats*)curr_stage->team_league_table)[start + i].club;
			clubs.push_back(club);
		}
	}

	for (size_t i = 0; i < clubs.size(); i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)clubs[i];
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, *(DWORD*)(_this + 0x4), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, seeds);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	comp_data->current_stage = (long)stage_num;
}

void ita_c_playoffs_create_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 2) {
			ita_c_playoffs_prom(_this);
			ita_c_playoffs_rele(_this);
		}
	}
}

void __declspec(naked) ita_c_playoffs_create()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_c_playoffs_create_c
		add esp, 0x4
		ret
	}
}

int SerieCTableIndicators(BYTE* _this, DWORD* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	if (stage == 2) {
		comp_stats* comp_data = (comp_stats*)_this;
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = stage_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 2; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				DWORD* c = (DWORD*)table[i].club;
				if (c != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), 0x32);
					table[i].league_fate = Promoted;
					*a5 = 1;
					return 0;
				case Promoted:
					staff_history_qualified_868DD0(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				case NoFate:
					table[i].league_fate = Eliminated;
					return 0;
				case BottomPlayoff:
					table[i].league_fate = Eliminated;
					return 0;
				default:
					return 0;
				}
			}
		}
	}
	else if (stage == 3) {
		comp_stats* comp_data = (comp_stats*)_this;
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[stage]);
		BYTE* rounds = stage_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 2; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				DWORD* c = (DWORD*)table[i].club;
				if (c != club) continue;
				switch (fate) {
				case BottomPlayoff:
					staff_history_relegated_86A1C0(staff_hist_ptr, club, *(DWORD*)(_this + 0x4));
					table[i].league_fate = Relegated;
					*a5 = 1;
					return 0;
				case Relegated:
					staff_history_qualified_868DD0(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				case NoFate:
					table[i].league_fate = Eliminated;
					return 0;
				case TopPlayoff:
					table[i].league_fate = Eliminated;
					return 0;
				default:
					return 0;
				}
			}
		}
	}
	else {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, *(DWORD*)(_this + 0x4));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_868DD0(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), PromotionPlayoff, None, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_868DD0(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), RelegationPlayoff, None, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, *(DWORD*)(_this + 0x4));
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) ita_ser_c_set_table_fate()		// used as a __thiscall -> __cdecl converter
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
		call SerieCTableIndicators
		add esp, 0x1c
		ret 0x18
	}
}

char ita_ser_c_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
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
	ita_ser_c_subs(_this);
	AddTeamsGroupLeague(_this, Get9CF(0x9CF580));
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 2; i++) {
		ita_ser_c_setup_groups(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(DWORD*)(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) ita_ser_c_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call ita_ser_c_update
		add esp, 0x4
		ret
	}
}

void ita_ser_c_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	strcpy(comp->ClubCompNameThreeLetter, "C");
	strcpy(comp->ClubCompName, "Italian Serie C");
	strcpy(comp->ClubCompNameShort, "Serie C");
	comp->ClubCompNation = find_country("Italy");
	comp->ClubCompContinent = find_continent("Europe");
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(ita_ser_c_vtable->vtable_ptr);
	ita_ser_c_vtable->SetPointer(VTableInitFree, (DWORD)&ita_ser_c_free_c);
	ita_ser_c_vtable->SetPointer(VTableEoSUpdate, (DWORD)&ita_ser_c_update_c);
	ita_ser_c_vtable->SetPointer(VTablePlayoffQual, (DWORD)&ita_c_playoffs_create);
	ita_ser_c_vtable->SetPointer(VTableFixtures, (DWORD)&ita_ser_c_fixtures_c);
	ita_ser_c_vtable->SetPointer(VTableTableFates, (DWORD)&ita_ser_c_set_table_fate);
	ita_ser_c_vtable->SetPointer(VTable24, (DWORD)&ita_7D2CD0_c);
	ita_ser_c_vtable->SetPointer(VTableSubsRounds, (DWORD)&ita_ser_c_subs_c);
	data->year = year;
	data->rules = 0x12;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 4;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	ita_ser_c_subs(_this);
	ita_ser_c_init_teams(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 2; i++) {
		ita_ser_c_setup_groups(_this, i);
	}
	ita_7D2CD0(_this);
}

void setup_ita_ser_c()
{
}
