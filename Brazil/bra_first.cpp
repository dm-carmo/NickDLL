#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

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
	comp_data->tiebreaker_1 = 3;
	comp_data->tiebreaker_2 = 1;
	comp_data->tiebreaker_3 = 0;
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

		if (fixture_id != *num_rounds) {
			string msg = "Wrong number of fixtures: " + to_string(fixture_id);
			create_message_box("Error", msg.c_str(), true);
		}

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

void brazil_restruct_2025() {
	cm3_nations* brazil = find_country("Brazil");
	cm3_club_comps* bra_first = &(*club_comps)[BRA_FIRST_9CF()];
	cm3_club_comps* bra_second = &(*club_comps)[BRA_SECOND_9CF()];
	cm3_club_comps* bra_third = &(*club_comps)[BRA_THIRD_9CF()];
	cm3_club_comps* bra_fourth = &(*club_comps)[BRA_FOURTH_9CF()];
	bra_fourth->ClubCompNation = brazil;
	bra_fourth->ClubCompContinent = find_continent("South America");
	bra_fourth->ClubCompReputation = 3;

	cm3_clubs* penedense = find_club("SC Penedense");
	if (penedense) penedense->ClubNation = brazil;

	vector<cm3_clubs*> bra_clubs = find_clubs_of_country(NATION_BRAZIL_9CF());
	for (cm3_clubs* c : bra_clubs) {
		c->ClubDivision = 0;
		c->ClubReserveDivision = 0;
	}

	vector<string> bra_a_clubs = {
		"Botafogo de Futebol e Regatas",
		"Ceará Sporting Club",
		"Clube Atlético Mineiro",
		"Clube de Regatas do Flamengo",
		"Clube de Regatas Vasco da Gama",
		"Cruzeiro Esporte Clube",
		"Esporte Clube Bahia",
		"Esporte Clube Juventude",
		"Esporte Clube Vitória",
		"Fluminense Football Club",
		"Fortaleza Esporte Clube",
		"Grêmio Foot-Ball Porto-Alegrense",
		"Mirassol Futebol Clube (SP)",
		"Red Bull Bragantino",
		"Santos Futebol Clube",
		"Sociedade Esportiva Palmeiras",
		"Sport Club Corinthians Paulista",
		"Sport Club do Recife",
		"Sport Club Internacional",
		"São Paulo Futebol Clube",
	};
	vector<string> bra_b_clubs = {
		"Amazonas FC",
		"América Futebol Clube (MG)",
		"Associação Chapecoense de Futebol",
		"Athletic Club (MG)",
		"Atlético Clube Goianiense",
		"Avaí Futebol Clube (SC)",
		"Botafogo Futebol Clube (SP)",
		"Clube Atlético Paranaense",
		"Clube de Regatas Brasil (AL)",
		"Clube do Remo (PA)",
		"Coritiba Football Club",
		"Criciúma Esporte Clube",
		"Cuiabá Esporte Clube (MT)",
		"Ferroviária",
		"Goiás Esporte Clube",
		"Grêmio Novorizontino (SP)",
		"Operário Ferroviário Esporte Clube (PR)",
		"Paysandu SC",
		"Vila Nova Futebol Clube (GO)",
		"Volta Redonda Futebol Clube (RJ)",
	};
	vector<string> bra_c_clubs = {
		"ABC Futebol Clube (RN)",
		"AD Confiança",
		"Anápolis FC",
		"Associação Atlética Ponte Preta",
		"Associação Olímpica de Itabaiana (SE)",
		"Botafogo Futebol Clube (PB)",
		"Brusque Futebol Clube (SC)",
		"Centro Sportivo Alagoano (AL)",
		"Clube Náutico Capibaribe",
		"Figueirense Futebol Clube",
		"Floresta Esporte Clube (CE)",
		"Guarani Futebol Clube",
		"Ituano Futebol Clube (SP)",
		"Londrina Esporte Clube (PR)",
		"Maringá FC",
		"Retrô FC Brasil",
		"SER Caxias do Sul (RS)",
		"São Bernardo FC",
		"Tombense Futebol Clube (MG)",
		"Ypiranga FC",
	};
	vector<string> bra_d_clubs = {
		"EC Água Santa (SP)",
		"Águia de Marabá FC",
		"AA Altos",
		"América FC",
		"AA Aparecidense",
		"Agremiação Sportiva Arapiraquense (AL)",
		"Azuriz FC",
		"Barcelona FC (BA)",
		"Barra FC",
		"Boavista SC",
		"Grêmio Esportivo Brasil (RS)",
		"Capital CF",
		"Ceilândia EC",
		"Central SC",
		"Cianorte Futebol Clube (PR)",
		"FC Cascavel (PR)",
		"Ferroviário AC",
		"GA Sampaio (RR)",
		"Porto Velho EC",
		"Goianésia Esporte Clube (GO)",
		"Goiânia EC",
		"Goiatuba EC",
		"Guarany de Bagé FC",
		"Horizonte FC",
		"Rio Branco (AC)", // missing Humaitá, replacement
		"AD Iguatu",
		"Sociedade Imperatriz de Desportos (MA)",
		"Galvez Esporte Clube", // missing Independência, replacement
		"AA Internacional de Limeira",
		"Itabirito FC",
		"AD Jequié",
		"Joinville Esporte Clube (SC)",
		"SD Juazeirense (BA)",
		"Lagarto FC",
		"Luverdense EC (MT)",
		"Princesa do Solimões EC", // missing Manauara, replacement
		"Manaus Futebol Clube",
		"União Rondonópolis EC (MT)", // missing Maracanã, replacement
		"Maranhão AC",
		"Clube Náutico Marcílio Dias (SC)",
		"Olaria Atlético Clube (RJ)", // missing Maricá, replacement
		"Mixto EC (MT)",
		"Atlético Monte Azul (SP)",
		"Nova Iguaçu FC (RJ)",
		"Operário (MS)",
		"River AC",
		"SC Penedense", // missing Parnahyba, replacement
		"Vitória FC", // missing Porto Vitória, replacement
		"Associação Portuguesa de Desportos",
		"Pouso Alegre FC",
		"Rio Branco Atlético Clube (ES)",
		"Sampaio Corrêa FC (MA)",
		"Santa Cruz FC (PE)",
		"Santa Cruz Futebol Clube",
		"Esporte Clube São José (RS)",
		"EC São Luiz",
		"CS Sergipe",
		"Sousa EC",
		"Tocantinópolis EC",
		"Santos Futebol Clube (AP)", // missing Trem, replacement
		"Treze FC",
		"Tuna Luso Brasileira",
		"Uberlândia EC",
		"Araguaia Atlético Clube", // missing União-TO, replacement
	};

	for (string s : bra_a_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bra_first;
	}
	for (string s : bra_b_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bra_second;
	}
	for (string s : bra_c_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bra_third;
	}
	for (string s : bra_d_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bra_fourth;
	}
}

void bra_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = bra_first_vtable;
	data->year = year;
	data->rules = 0x6;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	if (year == 2025 || year == 2026) brazil_restruct_2025();
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	bra_first_subs(_this);
	AddTeams(_this);
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

char bra_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	DWORD v1 = *(DWORD*)_this;
	(*(void(__thiscall**)(BYTE*, int))(v1 + 0xB0))(_this, 1);
	//42b760 - what does this do?
	//42b520 - relegation from lowest division
	//42b130 - prom/rel in state leagues

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
