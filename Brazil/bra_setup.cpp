#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "bra_first.h"
#include "bra_second.h"
#include "bra_third.h"
#include "bra_fourth.h"
#include "bra_reg_bahia.h"
#include "bra_reg_catarina.h"
#include "bra_reg_gaucho.h"
#include "bra_reg_goias.h"
#include "bra_reg_minas.h"
#include "bra_reg_parana.h"
#include "bra_reg_paulo.h"
#include "bra_reg_pernambuco.h"
#include "bra_reg_rio.h"
#include "bra_reg_central.h"
#include "bra_reg_north.h"
#include "bra_reg_northeast.h"
#include "bra_cup.h"
#include "bra_super.h"
#include "bra_awards.h"
#include "bra_state_league_list.h"

DWORD bra_setup_c(playable_nation_data* nation_data) {
	state_leagues = {
		BRA_BAHIA_STATE_9CF(),
		BRA_RIO_DE_JANEIRO_STATE_9CF(),
		BRA_SANTA_CATARINA_STATE_9CF(),
		BRA_CENTRAL_STATE_9CF(),
		BRA_GAUCHO_STATE_9CF(),
		BRA_GOIAS_STATE_9CF(),
		BRA_MINAS_GERAIS_STATE_9CF(),
		BRA_NORTHEAST_STATE_9CF(),
		BRA_NORTH_STATE_9CF(),
		BRA_PARANA_STATE_9CF(),
		BRA_SAO_PAULO_STATE_9CF(),
		BRA_PERNAMBUCO_STATE_9CF(),
	};
	state_lower = {
		BRA_BAHIA_LOWER_9CF(),
		BRA_RIO_DE_JANEIRO_LOWER_9CF(),
		BRA_SANTA_CATARINA_LOWER_9CF(),
		BRA_CENTRAL_LOWER_9CF(),
		BRA_GAUCHO_LOWER_9CF(),
		BRA_GOIAS_LOWER_9CF(),
		BRA_MINAS_GERAIS_LOWER_9CF(),
		BRA_NORTHEAST_LOWER_9CF(),
		BRA_NORTH_LOWER_9CF(),
		BRA_PARANA_LOWER_9CF(),
		BRA_SAO_PAULO_LOWER_9CF(),
		BRA_PERNAMBUCO_LOWER_9CF(),
	};

	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	// contract start date?
	nation_data->contract_start_day = 3;
	nation_data->contract_start_month = January;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 6;
	// contract end date?
	nation_data->contract_end_day = 14;
	nation_data->contract_end_month = December;
	nation_data->contract_end_year = start_year;
	nation_data->f70 = 6;
	nation_data->num_of_comps = 18;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Série A
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_first_init(pMem, start_year, get_comp(BRA_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Série B
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_second_init(pMem, start_year, get_comp(BRA_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Série C
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_third_init(pMem, start_year, get_comp(BRA_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Série D
	pMem = (BYTE*)sub_944CF1_operator_new(0xF2);
	bra_fourth_init(pMem, start_year, get_comp(BRA_FOURTH_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Baiano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_bahia_init(pMem, start_year, get_comp(BRA_BAHIA_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Carioca
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_rio_init(pMem, start_year, get_comp(BRA_RIO_DE_JANEIRO_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Catarinense
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_catarina_init(pMem, start_year, get_comp(BRA_SANTA_CATARINA_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Central
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_central_init(pMem, start_year, get_comp(BRA_CENTRAL_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Gaúcho
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_gaucho_init(pMem, start_year, get_comp(BRA_GAUCHO_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Goiano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_goias_init(pMem, start_year, get_comp(BRA_GOIAS_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Mineiro
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_minas_init(pMem, start_year, get_comp(BRA_MINAS_GERAIS_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Nordeste
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_northeast_init(pMem, start_year, get_comp(BRA_NORTHEAST_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Norte
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_north_init(pMem, start_year, get_comp(BRA_NORTH_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Paranaense
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_parana_init(pMem, start_year, get_comp(BRA_PARANA_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Paulista
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_paulo_init(pMem, start_year, get_comp(BRA_SAO_PAULO_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Campeonato Pernambucano
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bra_reg_pernambuco_init(pMem, start_year, get_comp(BRA_PERNAMBUCO_STATE_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	bra_cup_init(pMem, start_year, get_comp(BRA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Champions Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	bra_super_init(pMem, start_year, get_comp(BRA_CHAMPIONS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(BRA_CHAMPIONS_CUP_9CF());
	return 1;
}

void setup_bra_nation() {
	WriteDWORD(0x667AC7 + 6, (DWORD)&bra_setup_c);
	// move start date forward a bit
	WriteBytes(0x667B17, 1, 30);
	// minor fix related to state leagues new start/end
	WriteBytes(0x44429C, 1, March);
	WriteBytes(0x44429E, 1, 31);
	setup_bra_first();
	setup_bra_second();
	setup_bra_third();
	setup_bra_fourth();
	setup_bra_reg_bahia();
	setup_bra_reg_catarina();
	setup_bra_reg_gaucho();
	setup_bra_reg_goias();
	setup_bra_reg_minas();
	setup_bra_reg_parana();
	setup_bra_reg_paulo();
	setup_bra_reg_pernambuco();
	setup_bra_reg_rio();
	setup_bra_reg_central();
	setup_bra_reg_north();
	setup_bra_reg_northeast();
	setup_bra_cup();
	setup_bra_super();
	setup_bra_awards();

	// transfer window adjustment
	WriteBytes(0x43f1be, 1, 0x5);
	WriteBytes(0x43f1c8, 1, 0x3);
	WriteBytes(0x43f1c9, 1, 0x2);
	WriteBytes(0x43f1d5, 1, 0x6);
	WriteBytes(0x43f1de, 1, 0xb);
	WriteBytes(0x43f1df, 1, 0x8);
	// foreign player limits
	WriteBytes(0x43f2cb, 1, 0x9);
}

void brazil_restructure() {
	cm3_nations* brazil = get_country(NATION_BRAZIL_9CF());
	cm3_club_comps* bra_first = get_comp(BRA_FIRST_9CF());
	cm3_club_comps* bra_second = get_comp(BRA_SECOND_9CF());
	cm3_club_comps* bra_third = get_comp(BRA_THIRD_9CF());
	cm3_club_comps* bra_fourth = get_comp(BRA_FOURTH_9CF());
	bra_fourth->ClubCompNation = brazil;
	bra_fourth->ClubCompContinent = find_continent("South America");
	bra_fourth->ClubCompReputation = 3;
	cm3_club_comps* bra_reg_bahia = get_comp(BRA_BAHIA_STATE_9CF());
	cm3_club_comps* bra_lower_bahia = get_comp(BRA_BAHIA_LOWER_9CF());
	cm3_club_comps* bra_reg_catarina = get_comp(BRA_SANTA_CATARINA_STATE_9CF());
	cm3_club_comps* bra_lower_catarina = get_comp(BRA_SANTA_CATARINA_LOWER_9CF());
	cm3_club_comps* bra_reg_gaucho = get_comp(BRA_GAUCHO_STATE_9CF());
	cm3_club_comps* bra_lower_gaucho = get_comp(BRA_GAUCHO_LOWER_9CF());
	cm3_club_comps* bra_reg_goias = get_comp(BRA_GOIAS_STATE_9CF());
	cm3_club_comps* bra_lower_goias = get_comp(BRA_GOIAS_LOWER_9CF());
	cm3_club_comps* bra_reg_minas = get_comp(BRA_MINAS_GERAIS_STATE_9CF());
	cm3_club_comps* bra_lower_minas = get_comp(BRA_MINAS_GERAIS_LOWER_9CF());
	cm3_club_comps* bra_reg_parana = get_comp(BRA_PARANA_STATE_9CF());
	cm3_club_comps* bra_lower_parana = get_comp(BRA_PARANA_LOWER_9CF());
	cm3_club_comps* bra_reg_paulo = get_comp(BRA_SAO_PAULO_STATE_9CF());
	cm3_club_comps* bra_lower_paulo = get_comp(BRA_SAO_PAULO_LOWER_9CF());
	cm3_club_comps* bra_reg_pernambuco = get_comp(BRA_PERNAMBUCO_STATE_9CF());
	cm3_club_comps* bra_lower_pernambuco = get_comp(BRA_PERNAMBUCO_LOWER_9CF());
	cm3_club_comps* bra_reg_rio = get_comp(BRA_RIO_DE_JANEIRO_STATE_9CF());
	cm3_club_comps* bra_lower_rio = get_comp(BRA_RIO_DE_JANEIRO_LOWER_9CF());
	cm3_club_comps* bra_reg_central = get_comp(BRA_CENTRAL_STATE_9CF());
	cm3_club_comps* bra_lower_central = get_comp(BRA_CENTRAL_LOWER_9CF());
	cm3_club_comps* bra_reg_north = get_comp(BRA_NORTH_STATE_9CF());
	cm3_club_comps* bra_lower_north = get_comp(BRA_NORTH_LOWER_9CF());
	cm3_club_comps* bra_reg_northeast = get_comp(BRA_NORTHEAST_STATE_9CF());
	cm3_club_comps* bra_lower_northeast = get_comp(BRA_NORTHEAST_LOWER_9CF());

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