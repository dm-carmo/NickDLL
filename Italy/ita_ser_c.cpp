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
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 4;

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
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 23), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 15), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 23), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 30), year, Saturday);

		if (fixture_id != 38) {
			string msg = "Wrong number of fixtures: " + to_string(fixture_id);
			create_message_box("Error", msg.c_str(), true);
		}

		return (DWORD)pMem;
	}
	else {
		if (stage_idx != 0) return 0;

		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = Playoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 5, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 6), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 5, 4, 2, 2, 4, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 7), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 0, 2, 1, 0, 0, 0, 1, 0, 0);

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
		for (char al = -1; al < data->num_stages; al++) {
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
	//ita_ser_c_vtable->SetPointer( VTableEoSUpdate, (DWORD)&eng_conf_update_c);
	//ita_ser_c_vtable->SetPointer( VTablePlayoffQual, (DWORD)&eng_playoffs_create);
	ita_ser_c_vtable->SetPointer(VTableFixtures, (DWORD)&ita_ser_c_fixtures_c);
	//ita_ser_c_vtable->SetPointer( VTableTableFates, (DWORD)&eng_conf_set_table_fate);
	ita_ser_c_vtable->SetPointer(VTable24, (DWORD)&ita_7D2CD0_c);
	ita_ser_c_vtable->SetPointer(VTableSubsRounds, (DWORD)&ita_ser_c_subs_c);
	data->year = year;
	data->rules = 0x12;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 2;
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
	for (BYTE i = 0; i < data->num_stages; i++) {
		ita_ser_c_setup_groups(_this, i);
	}
	ita_7D2CD0(_this);
}

void setup_ita_ser_c()
{
}
