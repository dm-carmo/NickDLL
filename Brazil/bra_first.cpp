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

void brazil_restruct_2025() {
	cm3_nations* brazil = find_country("Brazil");
	cm3_club_comps* bra_first = &(*club_comps)[BRA_FIRST_9CF()];
	cm3_club_comps* bra_second = &(*club_comps)[BRA_SECOND_9CF()];
	cm3_club_comps* bra_third = &(*club_comps)[BRA_THIRD_9CF()];
	cm3_club_comps* bra_fourth = &(*club_comps)[BRA_FOURTH_9CF()];
	bra_fourth->ClubCompNation = brazil;
	bra_fourth->ClubCompContinent = find_continent("South America");
	bra_fourth->ClubCompReputation = 3;
	cm3_club_comps* bra_reg_bahia = &(*club_comps)[BRA_BAHIA_STATE_9CF()];
	cm3_club_comps* bra_lower_bahia = &(*club_comps)[BRA_BAHIA_LOWER_9CF()];
	cm3_club_comps* bra_reg_catarina = &(*club_comps)[BRA_SANTA_CATARINA_STATE_9CF()];
	cm3_club_comps* bra_lower_catarina = &(*club_comps)[BRA_SANTA_CATARINA_LOWER_9CF()];
	cm3_club_comps* bra_reg_gaucho = &(*club_comps)[BRA_GAUCHO_STATE_9CF()];
	cm3_club_comps* bra_lower_gaucho = &(*club_comps)[BRA_GAUCHO_LOWER_9CF()];
	cm3_club_comps* bra_reg_goias = &(*club_comps)[BRA_GOIAS_STATE_9CF()];
	cm3_club_comps* bra_lower_goias = &(*club_comps)[BRA_GOIAS_LOWER_9CF()];
	cm3_club_comps* bra_reg_minas = &(*club_comps)[BRA_MINAS_GERAIS_STATE_9CF()];
	cm3_club_comps* bra_lower_minas = &(*club_comps)[BRA_MINAS_GERAIS_LOWER_9CF()];
	cm3_club_comps* bra_reg_parana = &(*club_comps)[BRA_PARANA_STATE_9CF()];
	cm3_club_comps* bra_lower_parana = &(*club_comps)[BRA_PARANA_LOWER_9CF()];
	cm3_club_comps* bra_reg_paulo = &(*club_comps)[BRA_SAO_PAULO_STATE_9CF()];
	cm3_club_comps* bra_lower_paulo = &(*club_comps)[BRA_SAO_PAULO_LOWER_9CF()];
	cm3_club_comps* bra_reg_pernambuco = &(*club_comps)[BRA_PERNAMBUCO_STATE_9CF()];
	cm3_club_comps* bra_lower_pernambuco = &(*club_comps)[BRA_PERNAMBUCO_LOWER_9CF()];
	cm3_club_comps* bra_reg_rio = &(*club_comps)[BRA_RIO_DE_JANEIRO_STATE_9CF()];
	cm3_club_comps* bra_lower_rio = &(*club_comps)[BRA_RIO_DE_JANEIRO_LOWER_9CF()];
	cm3_club_comps* bra_reg_central = &(*club_comps)[BRA_CENTRAL_STATE_9CF()];
	cm3_club_comps* bra_lower_central = &(*club_comps)[BRA_CENTRAL_LOWER_9CF()];
	cm3_club_comps* bra_reg_north = &(*club_comps)[BRA_NORTH_STATE_9CF()];
	cm3_club_comps* bra_lower_north = &(*club_comps)[BRA_NORTH_LOWER_9CF()];
	cm3_club_comps* bra_reg_northeast = &(*club_comps)[BRA_NORTHEAST_STATE_9CF()];
	cm3_club_comps* bra_lower_northeast = &(*club_comps)[BRA_NORTHEAST_LOWER_9CF()];

	cm3_clubs* penedense = find_club("SC Penedense");
	if (penedense) penedense->ClubNation = brazil;
	cm3_clubs* inhumas = find_club("Inhumas");
	if (inhumas) inhumas->ClubNation = brazil;
	cm3_clubs* renaux = find_club("Carlos Renaux");
	if (renaux) renaux->ClubNation = brazil;

	vector<cm3_clubs*> bra_clubs = find_clubs_of_country(NATION_BRAZIL_9CF());
	for (cm3_clubs* c : bra_clubs) {
		if (c->ClubDivision && c->ClubDivision->ClubCompID == RESERVE_9CF()) continue;
		c->ClubDivision = get_comp(A_LOWER_9CF());
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

	vector<string> bahia_d1_clubs = {
		"AD Bahia de Feira (BA)", // missing Porto-BA
		"Colo Colo de Futebol e Regatas (BA)",
		"AD Jequié",
		"Alagoinhas AC",
		"Barcelona FC (BA)",
		"Esporte Clube Bahia",
		"Esporte Clube Jacuipense (BA)",
		"Esporte Clube Vitória",
		"Jacobina Esporte Clube",
		"SD Juazeirense (BA)",
	};
	vector<string> bahia_d2_clubs = {
		"Botafogo EC (Jacobina) (BA)",
		"Catuense Futebol",
		"E.C.P.P. Vitória da Conquista (BA)",
		"Esporte Clube Poções",
		"Esporte Clube Ypiranga (BA)",
		"Fluminense de Feira FC",
		"Galícia Esporte Clube (BA)",
		"Itabuna EC",
		"Juazeiro Social Clube",
		"Serrano Sport Club (BA)",
	};
	vector<string> catarina_d1_clubs = {
		"Associação Chapecoense de Futebol",
		"Avaí Futebol Clube (SC)",
		"Barra FC",
		"Brusque Futebol Clube (SC)",
		"Clube Náutico Marcílio Dias (SC)",
		"Concórdia AC",
		"Criciúma Esporte Clube",
		"Figueirense Futebol Clube",
		"Hercílio Luz FC",
		"Joinville Esporte Clube (SC)",
		"Camboriú FC", // Caravaggio missing
		"Carlos Renaux", // Santa Catarina missing
	};
	vector<string> catarina_d2_clubs = {
		"Clube Atlético Catarinense (SC)",
		"Nação Esportes FC",
		"Associação Blumenauense de Futebol",
		"CA Metropolitano",
		"Clube Atlético Hermann Aichinger",
		"Clube Atlético Tubarão (SC)",
		"Esporte Clube Próspera (SC)",
		"Grêmio Esportivo Juventus (SC)",
		"Internacional de Lages",
		"SERC Guarani de Palhoça",
	};
	vector<string> gaucho_d1_clubs = {
		"EC Avenida",
		"EC Novo Hamburgo", // Monsoon missing
		"EC Pelotas",
		"EC São Luiz",
		"Esporte Clube Juventude",
		"Esporte Clube São José (RS)",
		"Grêmio Esportivo Brasil (RS)",
		"Grêmio Foot-Ball Porto-Alegrense",
		"Guarany de Bagé FC",
		"SER Caxias do Sul (RS)",
		"Sport Club Internacional",
		"Ypiranga FC",
	};
	vector<string> gaucho_d2_clubs = {
		"Associação Esportiva Social Riopardense",
		"CE Aimoré",
		"Cerâmica Atlético Clube",
		"Clube Esportivo de Bento Gonçalves (RS)",
		"Clube Esportivo Lajeadense (RS)",
		"EC Cruzeiro",
		"EC Passo Fundo",
		"Esporte Clube Internacional (RS)",
		"Esporte Clube Rio São Paulo",
		"FC Santa Cruz",
		"Grêmio Atlético Farroupilha",
		"Grêmio Esportivo Bagé",
		"Grêmio Esportivo Glória (RS)",
		"Grêmio Foot-Ball Santanense",
		"Porto Alegre",
		"Riograndense Futebol Clube (Santa Maria)",
		"Sport Clube Rio Grande",
		"União Frederiquense de Futebol",
		"Veranópolis EC",
	};
	vector<string> goias_d1_clubs = {
		"AA Aparecidense",
		"Anápolis FC",
		"Atlético Clube Goianiense",
		"Clube Recreativo e Atlético Catalano (GO)",
		"Goianésia Esporte Clube (GO)",
		"Goiatuba EC",
		"Goiás Esporte Clube",
		"Goiânia EC",
		"Vila Nova Futebol Clube (GO)",
		"Inhumas",
		"Associação Atlética Anapolina (GO)", // ABECAT missing
		"Esporte Clube Rio Verde (GO)", // Jataiense missing
	};
	vector<string> goias_d2_clubs = {
		"Grêmio Esportivo Anápolis (GO)",
		"Iporá Esporte Clube",
		"Itumbiara Esporte Clube (GO)",
		"Morrinhos Futebol Clube (GO)",
		"Novo Horizonte Futebol Clube",
		"Caldas Novas Atlético Clube",
		"Jaraguá Esporte Clube (GO)",
		"Mineiros Esporte Clube (GO)",
		"Santa Helena Esporte Clube",
		"Trindade Atlético Clube (GO)",
	};
	vector<string> minas_d1_clubs = {
		"América Futebol Clube (MG)",
		"Athletic Club (MG)",
		"Betim Futebol",
		"Clube Atlético Mineiro",
		"Cruzeiro Esporte Clube",
		"EC Democrata",
		"Itabirito FC",
		"Pouso Alegre FC",
		"Tombense Futebol Clube (MG)",
		"Uberlândia EC",
		"União Recreativa dos Trabalhadores (MG)", // Aymorés missing
		"Villa Nova AC",
	};
	vector<string> minas_d2_clubs = {
		"AA Caldense",
		"América Futebol Clube (Teófilo Otoni)",
		"Boa EC",
		"CA Patrocinense",
		"Clube Atlético Tricordiano",
		"Coimbra Esporte Clube Ltda (MG)",
		"Democrata FC",
		"EC Mamoré",
		"Guarani Esporte Clube (MG)",
		"Ipatinga FC",
		"Montes Claros",
		"Nacional AC",
		"Social Futebol Clube",
		"Tupi FC",
		"Tupynambás Futebol Clube (MG)",
		"Uberaba Sport Club (MG)",
	};
	vector<string> parana_d1_clubs = {
		"Azuriz FC",
		"Cianorte Futebol Clube (PR)",
		"Clube Atlético Paranaense",
		"Coritiba Football Club",
		"FC Cascavel (PR)",
		"Foz do Iguaçu FC", // Andraus missing
		"Independente Futebol São-Joseense (PR)",
		"Londrina Esporte Clube (PR)",
		"Maringá FC",
		"Operário Ferroviário Esporte Clube (PR)",
		"Paraná Clube",
		"Rio Branco SC",
	};
	vector<string> parana_d2_clubs = {
		"Paraná Soccer Technical Center (PR)",
		"AC Paranavaí",
		"Clube Esportivo União",
		"Futebol Clube Cascavel",
		"Grêmio de Esportes Maringá",
		"J.Malucelli Futebol S/A",
		"Junior Team Futebol",
		"Nacional Atlético Clube (PR)",
		"Prudentópolis Esporte Clube (PR",
		"Toledo Esporte Clube (PR)",
	};
	vector<string> paulo_d1_clubs = {
		"AA Internacional de Limeira",
		"AE Velo Clube Rioclarense (SP)",
		"Associação Atlética Ponte Preta",
		"Associação Portuguesa de Desportos",
		"Botafogo Futebol Clube (SP)",
		"EC Água Santa (SP)",
		"Esporte Clube Noroeste (SP)",
		"Grêmio Novorizontino (SP)",
		"Guarani Futebol Clube",
		"Mirassol Futebol Clube (SP)",
		"Red Bull Bragantino",
		"Santos Futebol Clube",
		"Sociedade Esportiva Palmeiras",
		"Sport Club Corinthians Paulista",
		"São Bernardo FC",
		"São Paulo Futebol Clube",
	};
	vector<string> paulo_d2_clubs = {
		"AD São Caetano (SP)",
		"Atlético Monte Azul (SP)",
		"Batatais Futebol Clube",
		"CA Juventus (SP)",
		"Capivariano FC",
		"Clube Atlético Linense (SP)",
		"Clube Atlético Penapolense (SP)",
		"Clube Atlético Votuporanguense",
		"Comercial Futebol Clube (SP)",
		"Desportivo Brasil Ltda (SP)",
		"EC Lemense",
		"EC Primavera",
		"EC Santo André",
		"EC Taubaté",
		"EC XV de Novembro",
		"EC XV de Piracicaba",
		"Esporte Clube São Bento (SP)",
		"Esporte Clube São Bernardo (SP)",
		"Ferroviária (SP)",
		"Ferroviária",
		"Grêmio Barueri Futebol Ltda.",
		"Grêmio Desportivo Prudente (SP)",
		"Grêmio Esportivo Osasco (SP)",
		"Grêmio Osasco Audax (SP)",
		"Ituano Futebol Clube (SP)",
		"Marília Atlético Clube (SP)",
		"Mogi Mirim Esporte Clube (SP)",
		"Nacional Atlético Clube (SP)",
		"Oeste FC",
		"Olímpia Futebol Clube",
		"Paulista Futebol Clube (SP)",
		"Red Bull Brasil (SP)",
		"Rio Branco EC (SP)",
		"Rio Claro Futebol Clube (SP)",
		"Sertãozinho Futebol Clube (SP)",
		"São José Esporte Clube (SP)",
		"União Agrícola Barbarense Futebol Clube",
		"União São João Esporte Clube",
	};
	vector<string> pernambuco_d1_clubs = {
		"Afogados da Ingazeira",
		"Central SC",
		"Clube Náutico Capibaribe",
		"Petrolina Social Futebol Clube (PE)",
		"Retrô FC Brasil",
		"Santa Cruz FC (PE)",
		"Sport Club do Recife",
		"SE Decisão Futebol Clube",
		"AAD Vitória das Tabocas (PE)", // Jaguar missing
		"América Futebol Clube (PE)", // Maguary missing
	};
	vector<string> pernambuco_d2_clubs = {
		"Íbis Sport Club",
		"Clube Atlético do Porto (PE)",
		"Salgueiro Atlético Clube (PE)",
		"Belo Jardim Futebol Clube",
		"Ferroviário Esporte Clube",
		"Pesqueira Futebol Clube",
		"S. E. Ypiranga Futebol Clube (PE)",
		"Serra Talhada Futebol Clube (PE)",
		"Serrano Futebol Clube (PE)",
		"Sete de Setembro Esporte Clube",
		"Vera Cruz Futebol Clube",
	};
	vector<string> rio_d1_clubs = {
		"AA Portuguesa",
		"Bangu Atlético Clube (RJ)",
		"Boavista SC",
		"Botafogo de Futebol e Regatas",
		"Clube de Regatas do Flamengo",
		"Clube de Regatas Vasco da Gama",
		"Fluminense Football Club",
		"Madureira EC",
		"Nova Iguaçu FC (RJ)",
		"Sampaio Corrêa Futebol e Esporte (RJ)",
		"Volta Redonda Futebol Clube (RJ)",
		"Olaria Atlético Clube (RJ)", // Maricá missing
	};
	vector<string> rio_d2_clubs = {
		"Audax Rio de Janeiro EC",
		"Americano Futebol Clube (RJ)",
		"América Football Club (RJ)",
		"Angra dos Reis Esporte Clube (RJ)",
		"Associação Desportiva Cabofriense (RJ)",
		"Bonsucesso Futebol Clube (RJ)",
		"Campo Grande Atlético Clube",
		"Duque de Caxias Futebol Clube (RJ)",
		"Esporte Clube Tigres do Brasil",
		"Friburguense Atlético Clube (RJ)",
		"Gonçalense Futebol Clube (RJ)",
		"Goytacaz Futebol Clube (RJ)",
		"Macaé Esporte Futebol Clube (RJ)",
		"Mesquita Futebol Clube",
		"Resende FC",
		"Serrano Football Club",
		"São Cristóvão de Futebol e Regatas",
	};
	vector<string> central_d1_clubs = {
		"Aquidauanense Futebol Clube",
		"Associação Botafogo Futebol Clube",
		"Brasiliense FC (DF)",
		"Capital CF",
		"Ceilândia EC",
		"Clube Esportivo Dom Bosco (MT)",
		"Cuiabá Esporte Clube (MT)",
		"Luverdense EC (MT)",
		"Mixto EC (MT)",
		"Nova Venécia FC",
		"Novoperário Futebol Clube",
		"Operário FC (MT)",
		"Sobradinho Esporte Clube (DF)",
		"Sociedade Esportiva do Gama (DF)",
		"União Rondonópolis EC (MT)",
		"Vitória FC",
	};
	vector<string> central_d2_clubs = {
		"Araguaia Atlético Clube",
		"Associação Atlética Luziânia",
		"Brasília Futebol Clube",
		"Clube Desportivo Sete de Setembro",
		"Clube Esportivo Naviraiense",
		"Corumbaense Futebol Clube (MS)",
		"Costa Rica EC",
		"Esporte Clube Comercial (MS)",
		"Esporte Clube Águia Negra (MS)",
		"Espírito Santo Futebol Clube",
		"Legião Futebol Clube",
		"Mato Grosso Esporte Clube",
		"Misto Esporte Clube",
		"Operário (MS)",
		"Porto Velho EC",
		"SER Chapadão",
		"Sinop FC (MT)",
		"Sociedade Ação Futebol",
		"Sociedade Esportiva Nova Andradina",
		"Sociedade Esportiva Unaí Itapuã",
		"Taguatinga",
		"Ubiratan Esporte Clube",
	};
	vector<string> north_d1_clubs = {
		"Amazonas FC",
		"Ji-Paraná FC",
		"Manaus Futebol Clube",
		"Nacional FC",
		"Palmas Futebol e Regatas",
		"Paysandu SC",
		"Clube do Remo (PA)",
		"Rio Branco (AC)",
		"São Raimundo Esporte Clube (RR)",
		"Tuna Luso Brasileira",
	};
	vector<string> north_d2_clubs = {
		"Atlético Acreano (AC)",
		"Atlético Clíper Clube",
		"Atlético Rio Negro Clube (AM)",
		"Atlético Roraima Clube",
		"Bragantino Clube do Pará (PA)",
		"Castanhal Esporte Clube (PA)",
		"GA Sampaio (RR)",
		"Galvez Esporte Clube",
		"Independente Atlético Clube (PA)",
		"Nacional Fast Clube (AM)",
		"Náutico Futebol Clube",
		"Paragominas Futebol Clube (PA)",
		"Penarol Atlético Clube",
		"Plácido de Castro Futebol Club",
		"Princesa do Solimões EC",
		"São Francisco Futebol Clube",
		"São Raimundo EC (AM)",
		"São Raimundo Esporte Clube (PA)",
		"Tocantinópolis EC",
		"Vilhena Esporte Clube (RO)",
		"Águia de Marabá FC",
	};
	vector<string> northeast_d1_clubs = {
		"AA Altos",
		"ABC Futebol Clube (RN)",
		"AD Confiança",
		"América FC",
		"Associação Olímpica de Itabaiana (SE)",
		"Botafogo Futebol Clube (PB)",
		"Ceará Sporting Club",
		"Centro Sportivo Alagoano (AL)",
		"Clube de Regatas Brasil (AL)",
		"CS Sergipe",
		"Ferroviário AC",
		"Floresta Esporte Clube (CE)",
		"Fortaleza Esporte Clube",
		"River AC",
		"Sampaio Corrêa FC (MA)",
		"Treze FC",
	};
	vector<string> northeast_d2_clubs = {
		"4 de Julho EC",
		"AA Coruripe",
		"ACD Potiguar (RN)",
		"AD Iguatu",
		"ADRC Icasa",
		"Agremiação Sportiva Arapiraquense (AL)",
		"Alecrim Futebol Clube (RN)",
		"Associação Atlética Santa Rita (AL)",
		"Associação Desportiva Freipaulistano",
		"Associação Esportiva Clube Baraúnas",
		"Associação Esportiva Tiradentes (CE)",
		"Associação Sportiva Sociedade Unida",
		"Atlético Cajazeirense",
		"Auto Esporte Clube",
		"Bacabal Esporte Clube",
		"Campinense Clube (PB)",
		"Caucaia Esporte Clube (CE)",
		"Centro Sportivo Paraibano",
		"Clube Sociedade Esportiva (AL)",
		"Clube Sportivo Miguelense",
		"Cordino Esporte Clube",
		"Falcon FC",
		"FC Atlético Cearense",
		"Fluminense EC",
		"Globo Futebol Clube (RN)",
		"Guarany Sporting Club (CE)",
		"Horizonte FC",
		"Lagarto FC",
		"Maranhão AC",
		"Moto Club (MA)",
		"Murici Futebol Clube (AL)",
		"Nacional Atlético Clube (PB)",
		"Pacajus Esporte Clube",
		"Santa Cruz Futebol Clube",
		"Santos Futebol Clube (AP)",
		"SC Corinthians Alagoano",
		"Serra Branca EC",
		"Sociedade Esportiva Juventude (MA)",
		"Sociedade Imperatriz de Desportos (MA)",
		"Sousa EC",
		"Ypiranga Clube (AP)",
		"Clube Atlético Itapemirim (ES)",
		"Desportiva Ferroviária (ES)",
		"Rio Branco Atlético Clube (ES)",
		"Esporte Clube Aracruz",
		"Estrela do Norte FC",
		"Real Noroeste CFC",
		"Associação Atlética São Mateus",
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

	for (string s : bahia_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_bahia;
	}
	for (string s : bahia_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_bahia;
	}
	for (string s : catarina_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_catarina;
	}
	for (string s : catarina_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_catarina;
	}
	for (string s : gaucho_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_gaucho;
	}
	for (string s : gaucho_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_gaucho;
	}
	for (string s : goias_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_goias;
	}
	for (string s : goias_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_goias;
	}
	for (string s : minas_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_minas;
	}
	for (string s : minas_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_minas;
	}
	for (string s : parana_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_parana;
	}
	for (string s : parana_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_parana;
	}
	for (string s : paulo_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_paulo;
	}
	for (string s : paulo_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_paulo;
	}
	for (string s : pernambuco_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_pernambuco;
	}
	for (string s : pernambuco_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_pernambuco;
	}
	for (string s : rio_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_rio;
	}
	for (string s : rio_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_rio;
	}
	for (string s : central_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_central;
	}
	for (string s : central_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_central;
	}
	for (string s : north_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_north;
	}
	for (string s : north_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_north;
	}
	for (string s : northeast_d1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_reg_northeast;
	}
	for (string s : northeast_d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubReserveDivision = bra_lower_northeast;
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

void __fastcall bra_promotion_to_fourth(BYTE* _this) {
	cm3_club_comps* bra_fourth = &(*club_comps)[BRA_FOURTH_9CF()];
	vector<cm3_clubs*> d_clubs = find_clubs_of_comp(BRA_FOURTH_9CF());
	for (cm3_clubs* c : d_clubs) {
		if (!c->ClubLastDivision || c->ClubLastDivision->ClubCompID != BRA_THIRD_9CF()) {
			c->ClubDivision = get_comp(A_LOWER_9CF());
		}
		//else dprintf("Club %s was relegated from Série C, they will play in Série D next season!\n", c->ClubNameShort);
	}
	vector<DWORD> state_leagues = {
		BRA_BAHIA_STATE_9CF(),
		BRA_CENTRAL_STATE_9CF(),
		BRA_GAUCHO_STATE_9CF(),
		BRA_GOIAS_STATE_9CF(),
		BRA_MINAS_GERAIS_STATE_9CF(),
		BRA_NORTH_STATE_9CF(),
		BRA_NORTHEAST_STATE_9CF(),
		BRA_PARANA_STATE_9CF(),
		BRA_PERNAMBUCO_STATE_9CF(),
		BRA_RIO_DE_JANEIRO_STATE_9CF(),
		BRA_SANTA_CATARINA_STATE_9CF(),
		BRA_SAO_PAULO_STATE_9CF(),
	};
	vector<DWORD> state_lower = {
		BRA_BAHIA_LOWER_9CF(),
		BRA_CENTRAL_LOWER_9CF(),
		BRA_GAUCHO_LOWER_9CF(),
		BRA_GOIAS_LOWER_9CF(),
		BRA_MINAS_GERAIS_LOWER_9CF(),
		BRA_NORTH_LOWER_9CF(),
		BRA_NORTHEAST_LOWER_9CF(),
		BRA_PARANA_LOWER_9CF(),
		BRA_PERNAMBUCO_LOWER_9CF(),
		BRA_RIO_DE_JANEIRO_LOWER_9CF(),
		BRA_SANTA_CATARINA_LOWER_9CF(),
		BRA_SAO_PAULO_LOWER_9CF(),
	};
	BYTE state_counts[12] = { 4,9,4,4,4,6,9,4,4,4,4,4 };
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
	vector<DWORD> state_leagues = {
		BRA_BAHIA_STATE_9CF(),
		BRA_CENTRAL_STATE_9CF(),
		BRA_GAUCHO_STATE_9CF(),
		BRA_GOIAS_STATE_9CF(),
		BRA_MINAS_GERAIS_STATE_9CF(),
		BRA_NORTH_STATE_9CF(),
		BRA_NORTHEAST_STATE_9CF(),
		BRA_PARANA_STATE_9CF(),
		BRA_PERNAMBUCO_STATE_9CF(),
		BRA_RIO_DE_JANEIRO_STATE_9CF(),
		BRA_SANTA_CATARINA_STATE_9CF(),
		BRA_SAO_PAULO_STATE_9CF(),
	};
	vector<DWORD> state_lower = {
		BRA_BAHIA_LOWER_9CF(),
		BRA_CENTRAL_LOWER_9CF(),
		BRA_GAUCHO_LOWER_9CF(),
		BRA_GOIAS_LOWER_9CF(),
		BRA_MINAS_GERAIS_LOWER_9CF(),
		BRA_NORTH_LOWER_9CF(),
		BRA_NORTHEAST_LOWER_9CF(),
		BRA_PARANA_LOWER_9CF(),
		BRA_PERNAMBUCO_LOWER_9CF(),
		BRA_RIO_DE_JANEIRO_LOWER_9CF(),
		BRA_SANTA_CATARINA_LOWER_9CF(),
		BRA_SAO_PAULO_LOWER_9CF(),
	};

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
	if (cup_data->special_teems_seedings) {
		sub_9452CA_free(cup_data->special_teems_seedings);
		cup_data->special_teems_seedings = 0;
	}
	cup_data->special_nteams_seedings = total_teams;
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
	vector<DWORD> state_leagues = {
		BRA_BAHIA_STATE_9CF(),
		BRA_CENTRAL_STATE_9CF(),
		BRA_GAUCHO_STATE_9CF(),
		BRA_GOIAS_STATE_9CF(),
		BRA_MINAS_GERAIS_STATE_9CF(),
		BRA_NORTH_STATE_9CF(),
		BRA_NORTHEAST_STATE_9CF(),
		BRA_PARANA_STATE_9CF(),
		BRA_PERNAMBUCO_STATE_9CF(),
		BRA_RIO_DE_JANEIRO_STATE_9CF(),
		BRA_SANTA_CATARINA_STATE_9CF(),
		BRA_SAO_PAULO_STATE_9CF(),
	};
	vector<DWORD> state_lower = {
		BRA_BAHIA_LOWER_9CF(),
		BRA_CENTRAL_LOWER_9CF(),
		BRA_GAUCHO_LOWER_9CF(),
		BRA_GOIAS_LOWER_9CF(),
		BRA_MINAS_GERAIS_LOWER_9CF(),
		BRA_NORTH_LOWER_9CF(),
		BRA_NORTHEAST_LOWER_9CF(),
		BRA_PARANA_LOWER_9CF(),
		BRA_PERNAMBUCO_LOWER_9CF(),
		BRA_RIO_DE_JANEIRO_LOWER_9CF(),
		BRA_SANTA_CATARINA_LOWER_9CF(),
		BRA_SAO_PAULO_LOWER_9CF(),
	};
	BYTE state_counts[12] = { 2,6,2,2,2,3,5,2,2,2,2,2 };
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
	cup_data->special_teems_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)cup_data->special_teems_seedings;

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
