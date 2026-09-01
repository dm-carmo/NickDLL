#include "Helpers\Helper.h"
#include "inject_9cf_rename.h"
#include <Helpers\9cf_constants.h>
#include <Helpers\generic_functions.h>
#include <filesystem>
#include <fstream>

map<string, char*> clubs_rename_short = {
	{"SJK Seinäjoki II", "SJK Akatemia"},
};

map<string, char*> clubs_rename_long = {
	{"Dallas Burn", "FC Dallas"},
	{"Kansas City Wizards", "Sporting Kansas City"},
	{"Miami Fusion FC", "Inter Miami CF"},
	{"NY/NJ Metrostars", "New York Red Bulls"},
	{"Tampa Bay Mutiny", "Los Angeles FC"},
	{"Clube Atlético Paranaense", "Club Athletico Paranaense"},
	{"Baskonia C.D.", "CD Basconia"},
	{"Extremadura C.F.", "CD Extremadura"},
	{"Merthyr Tydfil", "Merthyr Town"},
	//{"AZ", "AZ Alkmaar"},
	{"Bor. M'gladbach Amateure", "Borussia M'gladbach II"},
	{"SJK Seinäjoki II", "SJK Seinäjoki Akatemia"},
	{"Associação Lusitano de Évora 1911", "Lusitano de Évora GC"},
};

map<string, DWORD> club_dword_match;
map<string, DWORD> league_dword_match;
map<string, DWORD> award_dword_match;
map<string, DWORD> nation_dword_match;

int setup_9cf_leagues(char* league_name, DWORD league_id) {
	// Fill out 9CF codes
	auto it = league_dword_match.find(string(league_name));
	if (it != league_dword_match.end()) {
		WriteDWORD(it->second, league_id);
	}
	return 1;
}

int setup_9cf_clubs(char* club_name, DWORD club_id) {
	// Fill out 9CF codes
	auto it = club_dword_match.find(string(club_name));
	if (it != club_dword_match.end()) {
		WriteDWORD(it->second, club_id);
	}
	else {
		for (const auto& [key, value] : clubs_rename_long) {
			auto find_name_edited = club_dword_match.find(key);
			if (find_name_edited != club_dword_match.end() && strcmp(value, club_name) == 0) {
				WriteDWORD(find_name_edited->second, club_id);
			}
		}
	}
	return 1;
}

void inject_club_names_full()
{
	for (const auto& [key, value] : clubs_rename_short) {
		cm3_clubs* to_rename = find_club(key.c_str());
		if (to_rename) {
			strcpy_s((*to_rename).ClubNameShort, value);
		}
	}
	for (const auto& [key, value] : clubs_rename_long) {
		cm3_clubs* to_rename = find_club(key.c_str());
		if (to_rename) {
			strcpy_s((*to_rename).ClubName, value);
		}
	}
}

extern "C" _declspec(naked) int inject_club_names()
{
	_asm
	{
		pushad
	}
	inject_club_names_full();
	_asm
	{
		popad
		ret
	}
}

int setup_9cf_awards(char* award_name, DWORD award_id) {
	// Fill out 9CF codes
	auto it = award_dword_match.find(string(award_name));
	if (it != award_dword_match.end()) {
		WriteDWORD(it->second, award_id);
	}
	return 1;
}

int setup_9cf_nations(char* nation_name, DWORD nation_id) {
	// Fill out 9CF codes
	auto it = nation_dword_match.find(string(nation_name));
	if (it != nation_dword_match.end()) {
		WriteDWORD(it->second, nation_id);
	}
	return 1;
}

// a bit ugly and lengthy but works with no issues
BYTE* check_if_reserve_team_new(cm3_clubs* to_check, DWORD* is_main_club, DWORD a3) {
	if (!to_check) return NULL;
	// Commented to try and avoid issues related to B-teams unlinking
	//if (a3 != 0 && to_check->ClubHasLinkedClub == 0) return NULL;
	if (!to_check->ClubNation) return NULL;
	// Added to try and avoid issues related to B-teams unlinking
	to_check->ClubHasLinkedClub = 1;
	// Main teams check
	if (is_main_club) *is_main_club = 1;
	char* db_club_name = get_db_club_name(to_check);
	if (to_check->ClubNation->NationID == NATION_GERMANY_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_1860_MUNICH_9CF()) return (BYTE*)get_club(CLUB_1860_MUNICH_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AUGSBURG_9CF()) return (BYTE*)get_club(CLUB_AUGSBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BIELEFELD_9CF()) return (BYTE*)get_club(CLUB_BIELEFELD_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BOCHUM_9CF()) return (BYTE*)get_club(CLUB_BOCHUM_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DORTMUND_9CF()) return (BYTE*)get_club(CLUB_DORTMUND_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DUSSELDORF_9CF()) return (BYTE*)get_club(CLUB_DUSSELDORF_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FC_BAYERN_9CF()) return (BYTE*)get_club(CLUB_FC_BAYERN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FRANKFURT_9CF()) return (BYTE*)get_club(CLUB_FRANKFURT_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FREIBURG_9CF()) return (BYTE*)get_club(CLUB_FREIBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FURTH_9CF()) return (BYTE*)get_club(CLUB_FURTH_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HAMBURG_9CF()) return (BYTE*)get_club(CLUB_HAMBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HANNOVER_96_9CF()) return (BYTE*)get_club(CLUB_HANNOVER_96_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HERTHA_BSC_9CF()) return (BYTE*)get_club(CLUB_HERTHA_BSC_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HOFFENHEIM_9CF()) return (BYTE*)get_club(CLUB_HOFFENHEIM_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_INGOLSTADT_9CF()) return (BYTE*)get_club(CLUB_INGOLSTADT_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KAISERSLAUTERN_9CF()) return (BYTE*)get_club(CLUB_KAISERSLAUTERN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KARLSRUHE_9CF()) return (BYTE*)get_club(CLUB_KARLSRUHE_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KIEL_9CF()) return (BYTE*)get_club(CLUB_KIEL_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KOLN_9CF()) return (BYTE*)get_club(CLUB_KOLN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_M_GLADBACH_9CF()) return (BYTE*)get_club(CLUB_M_GLADBACH_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MAINZ_9CF()) return (BYTE*)get_club(CLUB_MAINZ_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NURNBERG_9CF()) return (BYTE*)get_club(CLUB_NURNBERG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PADERBORN_9CF()) return (BYTE*)get_club(CLUB_PADERBORN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REGENSBURG_9CF()) return (BYTE*)get_club(CLUB_REGENSBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROSTOCK_9CF()) return (BYTE*)get_club(CLUB_ROSTOCK_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SCHALKE_04_9CF()) return (BYTE*)get_club(CLUB_SCHALKE_04_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ST_PAULI_9CF()) return (BYTE*)get_club(CLUB_ST_PAULI_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STUTTGART_9CF()) return (BYTE*)get_club(CLUB_STUTTGART_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_UNTERHACHING_9CF()) return (BYTE*)get_club(CLUB_UNTERHACHING_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WERDER_BREMEN_9CF()) return (BYTE*)get_club(CLUB_WERDER_BREMEN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JENA_9CF()) return (BYTE*)get_club(CLUB_JENA_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_COTTBUS_9CF()) return (BYTE*)get_club(CLUB_COTTBUS_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DUISBURG_9CF()) return (BYTE*)get_club(CLUB_DUISBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BAYER_LEVERKUSEN_9CF()) return (BYTE*)get_club(CLUB_BAYER_LEVERKUSEN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MAGDEBURG_9CF()) return (BYTE*)get_club(CLUB_MAGDEBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SAARBRUCKEN_9CF()) return (BYTE*)get_club(CLUB_SAARBRUCKEN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STUTTGARTER_KICKERS_9CF()) return (BYTE*)get_club(CLUB_STUTTGARTER_KICKERS_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WOLFSBURG_9CF()) return (BYTE*)get_club(CLUB_WOLFSBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OBERHAUSEN_9CF()) return (BYTE*)get_club(CLUB_OBERHAUSEN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ULM_9CF()) return (BYTE*)get_club(CLUB_ULM_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WATTENSCHEID_9CF()) return (BYTE*)get_club(CLUB_WATTENSCHEID_II_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_SPAIN_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ALAVES_9CF()) return (BYTE*)get_club(CLUB_ALAVES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALBACETE_9CF()) return (BYTE*)get_club(CLUB_ALBACETE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALCORCON_9CF()) return (BYTE*)get_club(CLUB_ALCORCON_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALMERIA_9CF()) return (BYTE*)get_club(CLUB_ALMERIA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ATHLETIC_BILBAO_9CF()) return (BYTE*)get_club(CLUB_ATHLETIC_BILBAO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ATLETICO_MADRID_9CF()) return (BYTE*)get_club(CLUB_ATLETICO_MADRID_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BARCELONA_9CF()) return (BYTE*)get_club(CLUB_BARCELONA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BETIS_9CF()) return (BYTE*)get_club(CLUB_BETIS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BURGOS_9CF()) return (BYTE*)get_club(CLUB_BURGOS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CADIZ_9CF()) return (BYTE*)get_club(CLUB_CADIZ_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CARTAGENA_9CF()) return (BYTE*)get_club(CLUB_CARTAGENA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CASTELLON_9CF()) return (BYTE*)get_club(CLUB_CASTELLON_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CELTA_9CF()) return (BYTE*)get_club(CLUB_CELTA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CORDOBA_9CF()) return (BYTE*)get_club(CLUB_CORDOBA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CULTURAL_9CF()) return (BYTE*)get_club(CLUB_CULTURAL_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DEPORTIVO_9CF()) return (BYTE*)get_club(CLUB_DEPORTIVO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_EIBAR_9CF()) return (BYTE*)get_club(CLUB_EIBAR_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ELCHE_9CF()) return (BYTE*)get_club(CLUB_ELCHE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ESPANYOL_9CF()) return (BYTE*)get_club(CLUB_ESPANYOL_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GETAFE_9CF()) return (BYTE*)get_club(CLUB_GETAFE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GRANADA_9CF()) return (BYTE*)get_club(CLUB_GRANADA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HUESCA_9CF()) return (BYTE*)get_club(CLUB_HUESCA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LAS_PALMAS_9CF()) return (BYTE*)get_club(CLUB_LAS_PALMAS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LEGANES_9CF()) return (BYTE*)get_club(CLUB_LEGANES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LEVANTE_9CF()) return (BYTE*)get_club(CLUB_LEVANTE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LOGRONES_9CF()) return (BYTE*)get_club(CLUB_LOGRONES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LUGO_9CF()) return (BYTE*)get_club(CLUB_LUGO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MALAGA_9CF()) return (BYTE*)get_club(CLUB_MALAGA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MALLORCA_9CF()) return (BYTE*)get_club(CLUB_MALLORCA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MURCIA_9CF()) return (BYTE*)get_club(CLUB_MURCIA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NUMANCIA_9CF()) return (BYTE*)get_club(CLUB_NUMANCIA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OSASUNA_9CF()) return (BYTE*)get_club(CLUB_OSASUNA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OVIEDO_9CF()) return (BYTE*)get_club(CLUB_OVIEDO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RACING_SANTANDER_9CF()) return (BYTE*)get_club(CLUB_RACING_SANTANDER_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RAYO_9CF()) return (BYTE*)get_club(CLUB_RAYO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REAL_MADRID_9CF()) return (BYTE*)get_club(CLUB_REAL_MADRID_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REAL_SOCIEDAD_9CF()) return (BYTE*)get_club(CLUB_REAL_SOCIEDAD_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RECREATIVO_9CF()) return (BYTE*)get_club(CLUB_RECREATIVO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SEVILLA_9CF()) return (BYTE*)get_club(CLUB_SEVILLA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPORTING_GIJON_9CF()) return (BYTE*)get_club(CLUB_SPORTING_GIJON_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TENERIFE_9CF()) return (BYTE*)get_club(CLUB_TENERIFE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALENCIA_9CF()) return (BYTE*)get_club(CLUB_VALENCIA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALLADOLID_9CF()) return (BYTE*)get_club(CLUB_VALLADOLID_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VILLARREAL_9CF()) return (BYTE*)get_club(CLUB_VILLARREAL_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZARAGOZA_9CF()) return (BYTE*)get_club(CLUB_ZARAGOZA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GIRONA_9CF()) return (BYTE*)get_club(CLUB_GIRONA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SALAMANCA_9CF()) return (BYTE*)get_club(CLUB_SALAMANCA_B_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_PORTUGAL_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ALVERCA_9CF()) return (BYTE*)get_club(CLUB_ALVERCA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BENFICA_9CF()) return (BYTE*)get_club(CLUB_BENFICA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BRAGA_9CF()) return (BYTE*)get_club(CLUB_BRAGA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CHAVES_9CF()) return (BYTE*)get_club(CLUB_CHAVES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MARITIMO_9CF()) return (BYTE*)get_club(CLUB_MARITIMO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PORTO_9CF()) return (BYTE*)get_club(CLUB_PORTO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPORTING_CP_9CF()) return (BYTE*)get_club(CLUB_SPORTING_CP_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VIT_GUIMARAES_9CF()) return (BYTE*)get_club(CLUB_VIT_GUIMARAES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SANTA_CLARA_9CF()) return (BYTE*)get_club(CLUB_SANTA_CLARA_B_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_NORWAY_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_AALESUND_9CF()) return (BYTE*)get_club(CLUB_AALESUND_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ASANE_9CF()) return (BYTE*)get_club(CLUB_ASANE_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BAERUM_9CF()) return (BYTE*)get_club(CLUB_BAERUM_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BODO_GLIMT_9CF()) return (BYTE*)get_club(CLUB_BODO_GLIMT_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BRANN_9CF()) return (BYTE*)get_club(CLUB_BRANN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BRYNE_9CF()) return (BYTE*)get_club(CLUB_BRYNE_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BYASEN_9CF()) return (BYTE*)get_club(CLUB_BYASEN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FOLLO_9CF()) return (BYTE*)get_club(CLUB_FOLLO_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FREDRIKSTAD_9CF()) return (BYTE*)get_club(CLUB_FREDRIKSTAD_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FYLLINGSDALEN_9CF()) return (BYTE*)get_club(CLUB_FYLLINGSDALEN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GJOVIK_LYN_9CF()) return (BYTE*)get_club(CLUB_GJOVIK_LYN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GRORUD_9CF()) return (BYTE*)get_club(CLUB_GRORUD_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HAMKAM_9CF()) return (BYTE*)get_club(CLUB_HAMKAM_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HAUGESUND_9CF()) return (BYTE*)get_club(CLUB_HAUGESUND_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HODD_9CF()) return (BYTE*)get_club(CLUB_HODD_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HONEFOSS_9CF()) return (BYTE*)get_club(CLUB_HONEFOSS_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KFUM_OSLO_9CF()) return (BYTE*)get_club(CLUB_KFUM_OSLO_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KJELSAS_9CF()) return (BYTE*)get_club(CLUB_KJELSAS_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KONGSVINGER_9CF()) return (BYTE*)get_club(CLUB_KONGSVINGER_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KRISTIANSUND_9CF()) return (BYTE*)get_club(CLUB_KRISTIANSUND_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LILLESTROM_9CF()) return (BYTE*)get_club(CLUB_LILLESTROM_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LYN_9CF()) return (BYTE*)get_club(CLUB_LYN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MJONDALEN_9CF()) return (BYTE*)get_club(CLUB_MJONDALEN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MOLDE_9CF()) return (BYTE*)get_club(CLUB_MOLDE_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NARDO_9CF()) return (BYTE*)get_club(CLUB_NARDO_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ODDS_9CF()) return (BYTE*)get_club(CLUB_ODDS_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PORS_9CF()) return (BYTE*)get_club(CLUB_PORS_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RANHEIM_9CF()) return (BYTE*)get_club(CLUB_RANHEIM_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RAUFOSS_9CF()) return (BYTE*)get_club(CLUB_RAUFOSS_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROSENBORG_9CF()) return (BYTE*)get_club(CLUB_ROSENBORG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SANDEFJORD_9CF()) return (BYTE*)get_club(CLUB_SANDEFJORD_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SANDNES_ULF_9CF()) return (BYTE*)get_club(CLUB_SANDNES_ULF_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SARPSBORG_9CF()) return (BYTE*)get_club(CLUB_SARPSBORG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SKEID_9CF()) return (BYTE*)get_club(CLUB_SKEID_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SOGNDAL_9CF()) return (BYTE*)get_club(CLUB_SOGNDAL_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STABAEK_9CF()) return (BYTE*)get_club(CLUB_STABAEK_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_START_9CF()) return (BYTE*)get_club(CLUB_START_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STROMMEN_9CF()) return (BYTE*)get_club(CLUB_STROMMEN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STROMSGODSET_9CF()) return (BYTE*)get_club(CLUB_STROMSGODSET_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TROMSO_9CF()) return (BYTE*)get_club(CLUB_TROMSO_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TRAEFF_9CF()) return (BYTE*)get_club(CLUB_TRAEFF_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ULL_KISA_9CF()) return (BYTE*)get_club(CLUB_ULL_KISA_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VARD_HAUGESUND_9CF()) return (BYTE*)get_club(CLUB_VARD_HAUGESUND_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VIKING_9CF()) return (BYTE*)get_club(CLUB_VIKING_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALERENGA_9CF()) return (BYTE*)get_club(CLUB_VALERENGA_II_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_FINLAND_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ATLANTIS_9CF()) return (BYTE*)get_club(CLUB_ATLANTIS_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HJK_9CF()) return (BYTE*)get_club(CLUB_KLUBI_04_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ESPOO_9CF()) return (BYTE*)get_club(CLUB_ESPOO_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HIFK_9CF()) return (BYTE*)get_club(CLUB_HIFK_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HONKA_9CF()) return (BYTE*)get_club(CLUB_HONKA_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_INTER_TURKU_9CF()) return (BYTE*)get_club(CLUB_INTER_TURKU_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ILVES_9CF()) return (BYTE*)get_club(CLUB_ILVES_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KUPS_9CF()) return (BYTE*)get_club(CLUB_KUPS_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROPS_9CF()) return (BYTE*)get_club(CLUB_ROPS_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VPS_9CF()) return (BYTE*)get_club(CLUB_VPS_II_9CF());

	}
	else if (to_check->ClubNation->NationID == NATION_POLAND_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_CHROBRY_GLOGOW_9CF()) return (BYTE*)get_club(CLUB_CHROBRY_GLOGOW_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CRACOVIA_9CF()) return (BYTE*)get_club(CLUB_CRACOVIA_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GORNIK_ZABRZE_9CF()) return (BYTE*)get_club(CLUB_GORNIK_ZABRZE_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JAGIELLONIA_9CF()) return (BYTE*)get_club(CLUB_JAGIELLONIA_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KIELCE_9CF()) return (BYTE*)get_club(CLUB_KIELCE_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LECH_POZNAN_9CF()) return (BYTE*)get_club(CLUB_LECH_POZNAN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LEGIA_WARSAW_9CF()) return (BYTE*)get_club(CLUB_LEGIA_WARSAW_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LKS_LODZ_9CF()) return (BYTE*)get_club(CLUB_LKS_LODZ_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MIEDZ_LEGNICA_9CF()) return (BYTE*)get_club(CLUB_MIEDZ_LEGNICA_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PIAST_GLIWICE_9CF()) return (BYTE*)get_club(CLUB_PIAST_GLIWICE_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_POGON_SZCZECIN_9CF()) return (BYTE*)get_club(CLUB_POGON_SZCZECIN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RAKOW_9CF()) return (BYTE*)get_club(CLUB_RAKOW_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SLASK_WROCLAW_9CF()) return (BYTE*)get_club(CLUB_SLASK_WROCLAW_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WIDZEW_LODZ_9CF()) return (BYTE*)get_club(CLUB_WIDZEW_LODZ_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WISLA_KRAKOW_9CF()) return (BYTE*)get_club(CLUB_WISLA_KRAKOW_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WISLA_PLOCK_9CF()) return (BYTE*)get_club(CLUB_WISLA_PLOCK_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZAGLEBIE_LUBIN_9CF()) return (BYTE*)get_club(CLUB_ZAGLEBIE_LUBIN_II_9CF());

	}
	else if (to_check->ClubNation->NationID == NATION_SCOTLAND_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_CELTIC_9CF()) return (BYTE*)get_club(CLUB_CELTIC_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HEARTS_9CF()) return (BYTE*)get_club(CLUB_HEARTS_B_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_GREECE_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ASTERAS_AKTOR_9CF()) return (BYTE*)get_club(CLUB_ASTERAS_AKTOR_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AEK_ATHENS_9CF()) return (BYTE*)get_club(CLUB_AEK_ATHENS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OLYMPIACOS_9CF()) return (BYTE*)get_club(CLUB_OLYMPIACOS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PAOK_9CF()) return (BYTE*)get_club(CLUB_PAOK_B_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_NETHERLANDS_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_AZ_9CF()) return (BYTE*)get_club(CLUB_JONG_AZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AJAX_9CF()) return (BYTE*)get_club(CLUB_JONG_AJAX_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALMERE_CITY_9CF()) return (BYTE*)get_club(CLUB_JONG_ALMERE_CITY_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PSV_9CF()) return (BYTE*)get_club(CLUB_JONG_PSV_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPARTA_ROTTERDAM_9CF()) return (BYTE*)get_club(CLUB_JONG_SPARTA_ROTTERDAM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_UTRECHT_9CF()) return (BYTE*)get_club(CLUB_JONG_UTRECHT_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_BELGIUM_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ANDERLECHT_9CF()) return (BYTE*)get_club(CLUB_ANDERLECHT_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ANTWERP_9CF()) return (BYTE*)get_club(CLUB_ANTWERP_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CERCLE_BRUGGE_9CF()) return (BYTE*)get_club(CLUB_CERCLE_BRUGGE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CHARLEROI_9CF()) return (BYTE*)get_club(CLUB_CHARLEROI_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CLUB_BRUGGE_9CF()) return (BYTE*)get_club(CLUB_CLUB_BRUGGE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_EUPEN_9CF()) return (BYTE*)get_club(CLUB_EUPEN_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GENK_9CF()) return (BYTE*)get_club(CLUB_GENK_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GENT_9CF()) return (BYTE*)get_club(CLUB_GENT_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KV_MECHELEN_9CF()) return (BYTE*)get_club(CLUB_KV_MECHELEN_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OH_LEUVEN_9CF()) return (BYTE*)get_club(CLUB_OH_LEUVEN_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SINT_TRUIDEN_9CF()) return (BYTE*)get_club(CLUB_SINT_TRUIDEN_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STANDARD_LIEGE_9CF()) return (BYTE*)get_club(CLUB_STANDARD_LIEGE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_UNION_SG_9CF()) return (BYTE*)get_club(CLUB_UNION_SG_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZULTE_WAREGEM_9CF()) return (BYTE*)get_club(CLUB_ZULTE_WAREGEM_B_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_RUSSIA_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_AKRON_9CF()) return (BYTE*)get_club(CLUB_AKRON_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALANIA_9CF()) return (BYTE*)get_club(CLUB_ALANIA_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ARSENAL_TULA_9CF()) return (BYTE*)get_club(CLUB_ARSENAL_2_TULA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BALTIKA_9CF()) return (BYTE*)get_club(CLUB_BALTIKA_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CSKA_MOSCOW_9CF()) return (BYTE*)get_club(CLUB_CSKA_2_MOSCOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DINAMO_MAKHACHKALA_9CF()) return (BYTE*)get_club(CLUB_DINAMO_2_MAKHACHKALA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DYNAMO_MOSCOW_9CF()) return (BYTE*)get_club(CLUB_DYNAMO_2_MOSCOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ENISEY_9CF()) return (BYTE*)get_club(CLUB_ENISEY_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FAKEL_VORONEZH_9CF()) return (BYTE*)get_club(CLUB_FAKEL_M_VORONEZH_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KHIMKI_9CF()) return (BYTE*)get_club(CLUB_KHIMKI_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ORENBURG_9CF()) return (BYTE*)get_club(CLUB_ORENBURG_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROSTOV_9CF()) return (BYTE*)get_club(CLUB_ROSTOV_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_UFA_9CF()) return (BYTE*)get_club(CLUB_UFA_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KOSMOS_KHIMKI_9CF()) return (BYTE*)get_club(CLUB_KOSMOS_2_DOLGOPRUDNYI_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KRYLYA_SOVETOV_9CF()) return (BYTE*)get_club(CLUB_KRYLYA_SOVETOV_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LOKOMOTIV_MOSCOW_9CF()) return (BYTE*)get_club(CLUB_LOKOMOTIV_KAZANKA_MOSKOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RODINA_MOSCOW_9CF()) return (BYTE*)get_club(CLUB_RODINA_2_MOSCOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROTOR_9CF()) return (BYTE*)get_club(CLUB_ROTOR_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RUBIN_KAZAN_9CF()) return (BYTE*)get_club(CLUB_RUBIN_2_KAZAN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SKA_KHABAROVSK_9CF()) return (BYTE*)get_club(CLUB_SKA_KHABAROVSK_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPARTAK_MOSCOW_9CF()) return (BYTE*)get_club(CLUB_SPARTAK_2_MOSCOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_URAL_9CF()) return (BYTE*)get_club(CLUB_URAL_2_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZENIT_9CF()) return (BYTE*)get_club(CLUB_ZENIT_2_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_CZECH_REPUBLIC_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_SLOVACKO_9CF()) return (BYTE*)get_club(CLUB_SLOVACKO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPARTA_PRAGUE_9CF()) return (BYTE*)get_club(CLUB_SPARTA_PRAGUE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BOHEMIANS_1905_9CF()) return (BYTE*)get_club(CLUB_BOHEMIANS_1905_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BANIK_OSTRAVA_9CF()) return (BYTE*)get_club(CLUB_BANIK_OSTRAVA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HRADEC_KRALOVE_9CF()) return (BYTE*)get_club(CLUB_HRADEC_KRALOVE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TABORSKO_9CF()) return (BYTE*)get_club(CLUB_TABORSKO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SLOVAN_LIBEREC_9CF()) return (BYTE*)get_club(CLUB_SLOVAN_LIBEREC_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VIKTORIA_PLZEN_9CF()) return (BYTE*)get_club(CLUB_VIKTORIA_PLZEN_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BRNO_9CF()) return (BYTE*)get_club(CLUB_BRNO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZLIN_9CF()) return (BYTE*)get_club(CLUB_ZLIN_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DUKLA_PRAGUE_9CF()) return (BYTE*)get_club(CLUB_DUKLA_PRAGUE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JABLONEC_9CF()) return (BYTE*)get_club(CLUB_JABLONEC_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MLADA_BOLESLAV_9CF()) return (BYTE*)get_club(CLUB_MLADA_BOLESLAV_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PARDUBICE_9CF()) return (BYTE*)get_club(CLUB_PARDUBICE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PRIBRAM_9CF()) return (BYTE*)get_club(CLUB_PRIBRAM_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TEPLICE_9CF()) return (BYTE*)get_club(CLUB_TEPLICE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KARVINA_9CF()) return (BYTE*)get_club(CLUB_KARVINA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CESKE_BUDEJOVICE_9CF()) return (BYTE*)get_club(CLUB_CESKE_BUDEJOVICE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SIGMA_OLOMOUC_9CF()) return (BYTE*)get_club(CLUB_SIGMA_OLOMOUC_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SLAVIA_PRAGUE_9CF()) return (BYTE*)get_club(CLUB_SLAVIA_PRAGUE_B_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_AUSTRIA_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ADMIRA_WACKER_9CF()) return (BYTE*)get_club(CLUB_ADMIRA_WACKER_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AUSTRIA_VIENNA_9CF()) return (BYTE*)get_club(CLUB_AUSTRIA_VIENNA_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LASK_9CF()) return (BYTE*)get_club(CLUB_LASK_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RAPID_VIENNA_9CF()) return (BYTE*)get_club(CLUB_RAPID_VIENNA_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RB_SALZBURG_9CF()) return (BYTE*)get_club(CLUB_LIEFERING_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AUSTRIA_LUSTENAU_9CF()) return (BYTE*)get_club(CLUB_AUSTRIA_LUSTENAU_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALTACH_9CF()) return (BYTE*)get_club(CLUB_ALTACH_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STURM_GRAZ_9CF()) return (BYTE*)get_club(CLUB_STURM_GRAZ_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ST_POLTEN_9CF()) return (BYTE*)get_club(CLUB_ST_POLTEN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RIED_9CF()) return (BYTE*)get_club(CLUB_RIED_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WOLFSBERG_9CF()) return (BYTE*)get_club(CLUB_WOLFSBERG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WSG_TIROL_9CF()) return (BYTE*)get_club(CLUB_WSG_TIROL_II_9CF());

	}
	else if (to_check->ClubNation->NationID == NATION_SWITZERLAND_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_YOUNG_BOYS_9CF()) return (BYTE*)get_club(CLUB_YOUNG_BOYS_U21_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GRASSHOPPERS_9CF()) return (BYTE*)get_club(CLUB_GRASSHOPPERS_U21_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BASEL_9CF()) return (BYTE*)get_club(CLUB_BASEL_U21_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LAUSANNE_9CF()) return (BYTE*)get_club(CLUB_LAUSANNE_U21_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LUGANO_9CF()) return (BYTE*)get_club(CLUB_LUGANO_U21_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LUZERN_9CF()) return (BYTE*)get_club(CLUB_LUZERN_U21_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SION_9CF()) return (BYTE*)get_club(CLUB_SION_U21_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ST_GALLEN_9CF()) return (BYTE*)get_club(CLUB_ST_GALLEN_U21_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WINTERTHUR_9CF()) return (BYTE*)get_club(CLUB_WINTERTHUR_U21_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZURICH_9CF()) return (BYTE*)get_club(CLUB_ZURICH_U21_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SERVETTE_9CF()) return (BYTE*)get_club(CLUB_SERVETTE_U21_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_FRANCE_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_AJACCIO_9CF()) return (BYTE*)get_club(CLUB_AJACCIO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LE_HAVRE_9CF()) return (BYTE*)get_club(CLUB_LE_HAVRE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AUXERRE_9CF()) return (BYTE*)get_club(CLUB_AUXERRE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AMIENS_9CF()) return (BYTE*)get_club(CLUB_AMIENS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ANGERS_9CF()) return (BYTE*)get_club(CLUB_ANGERS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MONACO_9CF()) return (BYTE*)get_club(CLUB_MONACO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NANCY_9CF()) return (BYTE*)get_club(CLUB_NANCY_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SAINT_ETIENNE_9CF()) return (BYTE*)get_club(CLUB_SAINT_ETIENNE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BOURGES_9CF()) return (BYTE*)get_club(CLUB_BOURGES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CLERMONT_9CF()) return (BYTE*)get_club(CLUB_CLERMONT_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SEDAN_9CF()) return (BYTE*)get_club(CLUB_SEDAN_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DIJON_9CF()) return (BYTE*)get_club(CLUB_DIJON_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GUINGAMP_9CF()) return (BYTE*)get_club(CLUB_GUINGAMP_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TROYES_9CF()) return (BYTE*)get_club(CLUB_TROYES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BORDEAUX_9CF()) return (BYTE*)get_club(CLUB_BORDEAUX_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LE_MANS_9CF()) return (BYTE*)get_club(CLUB_LE_MANS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LORIENT_9CF()) return (BYTE*)get_club(CLUB_LORIENT_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_METZ_9CF()) return (BYTE*)get_club(CLUB_METZ_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NANTES_9CF()) return (BYTE*)get_club(CLUB_NANTES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SOCHAUX_9CF()) return (BYTE*)get_club(CLUB_SOCHAUX_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CHATEAUROUX_9CF()) return (BYTE*)get_club(CLUB_CHATEAUROUX_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LE_PUY_9CF()) return (BYTE*)get_club(CLUB_LE_PUY_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LES_HERBIERS_9CF()) return (BYTE*)get_club(CLUB_LES_HERBIERS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LILLE_9CF()) return (BYTE*)get_club(CLUB_LILLE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LYON_LA_DUCHERE_9CF()) return (BYTE*)get_club(CLUB_LYON_LA_DUCHERE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MARIGNANE_9CF()) return (BYTE*)get_club(CLUB_MARIGNANE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MONTPELLIER_9CF()) return (BYTE*)get_club(CLUB_MONTPELLIER_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NICE_9CF()) return (BYTE*)get_club(CLUB_NICE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MARSEILLE_9CF()) return (BYTE*)get_club(CLUB_MARSEILLE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LYON_9CF()) return (BYTE*)get_club(CLUB_LYON_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PARIS_FC_9CF()) return (BYTE*)get_club(CLUB_PARIS_FC_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PSG_9CF()) return (BYTE*)get_club(CLUB_PSG_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PAU_9CF()) return (BYTE*)get_club(CLUB_PAU_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_QUEVILLY_ROUEN_9CF()) return (BYTE*)get_club(CLUB_QUEVILLY_ROUEN_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STRASBOURG_9CF()) return (BYTE*)get_club(CLUB_STRASBOURG_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RODEZ_9CF()) return (BYTE*)get_club(CLUB_RODEZ_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BASTIA_9CF()) return (BYTE*)get_club(CLUB_BASTIA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CAEN_9CF()) return (BYTE*)get_club(CLUB_CAEN_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BREST_9CF()) return (BYTE*)get_club(CLUB_BREST_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ST_BRIEUC_9CF()) return (BYTE*)get_club(CLUB_ST_BRIEUC_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LAVAL_9CF()) return (BYTE*)get_club(CLUB_LAVAL_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REIMS_9CF()) return (BYTE*)get_club(CLUB_REIMS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RENNES_9CF()) return (BYTE*)get_club(CLUB_RENNES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TOULOUSE_9CF()) return (BYTE*)get_club(CLUB_TOULOUSE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AVRANCHES_9CF()) return (BYTE*)get_club(CLUB_AVRANCHES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BOULOGNE_9CF()) return (BYTE*)get_club(CLUB_BOULOGNE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ORLEANS_9CF()) return (BYTE*)get_club(CLUB_ORLEANS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALENCIENNES_9CF()) return (BYTE*)get_club(CLUB_VALENCIENNES_B_9CF());
	}

	// Reserve teams check
	if (is_main_club) *is_main_club = 0;
	if (to_check->ClubNation->NationID == NATION_GERMANY_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_1860_MUNICH_II_9CF()) return (BYTE*)get_club(CLUB_1860_MUNICH_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AUGSBURG_II_9CF()) return (BYTE*)get_club(CLUB_AUGSBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BIELEFELD_II_9CF()) return (BYTE*)get_club(CLUB_BIELEFELD_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BOCHUM_II_9CF()) return (BYTE*)get_club(CLUB_BOCHUM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DORTMUND_II_9CF()) return (BYTE*)get_club(CLUB_DORTMUND_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DUSSELDORF_II_9CF()) return (BYTE*)get_club(CLUB_DUSSELDORF_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FC_BAYERN_II_9CF()) return (BYTE*)get_club(CLUB_FC_BAYERN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FRANKFURT_II_9CF()) return (BYTE*)get_club(CLUB_FRANKFURT_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FREIBURG_II_9CF()) return (BYTE*)get_club(CLUB_FREIBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FURTH_II_9CF()) return (BYTE*)get_club(CLUB_FURTH_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HAMBURG_II_9CF()) return (BYTE*)get_club(CLUB_HAMBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HANNOVER_96_II_9CF()) return (BYTE*)get_club(CLUB_HANNOVER_96_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HERTHA_BSC_II_9CF()) return (BYTE*)get_club(CLUB_HERTHA_BSC_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HOFFENHEIM_II_9CF()) return (BYTE*)get_club(CLUB_HOFFENHEIM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_INGOLSTADT_II_9CF()) return (BYTE*)get_club(CLUB_INGOLSTADT_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KAISERSLAUTERN_II_9CF()) return (BYTE*)get_club(CLUB_KAISERSLAUTERN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KARLSRUHE_II_9CF()) return (BYTE*)get_club(CLUB_KARLSRUHE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KIEL_II_9CF()) return (BYTE*)get_club(CLUB_KIEL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KOLN_II_9CF()) return (BYTE*)get_club(CLUB_KOLN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_M_GLADBACH_II_9CF()) return (BYTE*)get_club(CLUB_M_GLADBACH_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MAINZ_II_9CF()) return (BYTE*)get_club(CLUB_MAINZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NURNBERG_II_9CF()) return (BYTE*)get_club(CLUB_NURNBERG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PADERBORN_II_9CF()) return (BYTE*)get_club(CLUB_PADERBORN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REGENSBURG_II_9CF()) return (BYTE*)get_club(CLUB_REGENSBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROSTOCK_II_9CF()) return (BYTE*)get_club(CLUB_ROSTOCK_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SCHALKE_04_II_9CF()) return (BYTE*)get_club(CLUB_SCHALKE_04_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ST_PAULI_II_9CF()) return (BYTE*)get_club(CLUB_ST_PAULI_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STUTTGART_II_9CF()) return (BYTE*)get_club(CLUB_STUTTGART_9CF());
		if ((DWORD)to_check->ClubID == CLUB_UNTERHACHING_II_9CF()) return (BYTE*)get_club(CLUB_UNTERHACHING_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WERDER_BREMEN_II_9CF()) return (BYTE*)get_club(CLUB_WERDER_BREMEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JENA_II_9CF()) return (BYTE*)get_club(CLUB_JENA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_COTTBUS_II_9CF()) return (BYTE*)get_club(CLUB_COTTBUS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DUISBURG_II_9CF()) return (BYTE*)get_club(CLUB_DUISBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BAYER_LEVERKUSEN_II_9CF()) return (BYTE*)get_club(CLUB_BAYER_LEVERKUSEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MAGDEBURG_II_9CF()) return (BYTE*)get_club(CLUB_MAGDEBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SAARBRUCKEN_II_9CF()) return (BYTE*)get_club(CLUB_SAARBRUCKEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STUTTGARTER_KICKERS_II_9CF()) return (BYTE*)get_club(CLUB_STUTTGARTER_KICKERS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WOLFSBURG_II_9CF()) return (BYTE*)get_club(CLUB_WOLFSBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OBERHAUSEN_II_9CF()) return (BYTE*)get_club(CLUB_OBERHAUSEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ULM_II_9CF()) return (BYTE*)get_club(CLUB_ULM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WATTENSCHEID_II_9CF()) return (BYTE*)get_club(CLUB_WATTENSCHEID_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_SPAIN_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ALAVES_B_9CF()) return (BYTE*)get_club(CLUB_ALAVES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALBACETE_B_9CF()) return (BYTE*)get_club(CLUB_ALBACETE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALCORCON_B_9CF()) return (BYTE*)get_club(CLUB_ALCORCON_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALMERIA_B_9CF()) return (BYTE*)get_club(CLUB_ALMERIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ATHLETIC_BILBAO_B_9CF()) return (BYTE*)get_club(CLUB_ATHLETIC_BILBAO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ATLETICO_MADRID_B_9CF()) return (BYTE*)get_club(CLUB_ATLETICO_MADRID_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BARCELONA_B_9CF()) return (BYTE*)get_club(CLUB_BARCELONA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BETIS_B_9CF()) return (BYTE*)get_club(CLUB_BETIS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BURGOS_B_9CF()) return (BYTE*)get_club(CLUB_BURGOS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CADIZ_B_9CF()) return (BYTE*)get_club(CLUB_CADIZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CARTAGENA_B_9CF()) return (BYTE*)get_club(CLUB_CARTAGENA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CASTELLON_B_9CF()) return (BYTE*)get_club(CLUB_CASTELLON_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CELTA_B_9CF()) return (BYTE*)get_club(CLUB_CELTA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CORDOBA_B_9CF()) return (BYTE*)get_club(CLUB_CORDOBA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CULTURAL_B_9CF()) return (BYTE*)get_club(CLUB_CULTURAL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DEPORTIVO_B_9CF()) return (BYTE*)get_club(CLUB_DEPORTIVO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_EIBAR_B_9CF()) return (BYTE*)get_club(CLUB_EIBAR_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ELCHE_B_9CF()) return (BYTE*)get_club(CLUB_ELCHE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ESPANYOL_B_9CF()) return (BYTE*)get_club(CLUB_ESPANYOL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GETAFE_B_9CF()) return (BYTE*)get_club(CLUB_GETAFE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GRANADA_B_9CF()) return (BYTE*)get_club(CLUB_GRANADA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HUESCA_B_9CF()) return (BYTE*)get_club(CLUB_HUESCA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LAS_PALMAS_B_9CF()) return (BYTE*)get_club(CLUB_LAS_PALMAS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LEGANES_B_9CF()) return (BYTE*)get_club(CLUB_LEGANES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LEVANTE_B_9CF()) return (BYTE*)get_club(CLUB_LEVANTE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LOGRONES_B_9CF()) return (BYTE*)get_club(CLUB_LOGRONES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LUGO_B_9CF()) return (BYTE*)get_club(CLUB_LUGO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MALAGA_B_9CF()) return (BYTE*)get_club(CLUB_MALAGA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MALLORCA_B_9CF()) return (BYTE*)get_club(CLUB_MALLORCA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MURCIA_B_9CF()) return (BYTE*)get_club(CLUB_MURCIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NUMANCIA_B_9CF()) return (BYTE*)get_club(CLUB_NUMANCIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OSASUNA_B_9CF()) return (BYTE*)get_club(CLUB_OSASUNA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OVIEDO_B_9CF()) return (BYTE*)get_club(CLUB_OVIEDO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RACING_SANTANDER_B_9CF()) return (BYTE*)get_club(CLUB_RACING_SANTANDER_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RAYO_B_9CF()) return (BYTE*)get_club(CLUB_RAYO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REAL_MADRID_B_9CF()) return (BYTE*)get_club(CLUB_REAL_MADRID_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REAL_SOCIEDAD_B_9CF()) return (BYTE*)get_club(CLUB_REAL_SOCIEDAD_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RECREATIVO_B_9CF()) return (BYTE*)get_club(CLUB_RECREATIVO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SEVILLA_B_9CF()) return (BYTE*)get_club(CLUB_SEVILLA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPORTING_GIJON_B_9CF()) return (BYTE*)get_club(CLUB_SPORTING_GIJON_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TENERIFE_B_9CF()) return (BYTE*)get_club(CLUB_TENERIFE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALENCIA_B_9CF()) return (BYTE*)get_club(CLUB_VALENCIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALLADOLID_B_9CF()) return (BYTE*)get_club(CLUB_VALLADOLID_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VILLARREAL_B_9CF()) return (BYTE*)get_club(CLUB_VILLARREAL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZARAGOZA_B_9CF()) return (BYTE*)get_club(CLUB_ZARAGOZA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GIRONA_B_9CF()) return (BYTE*)get_club(CLUB_GIRONA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SALAMANCA_B_9CF()) return (BYTE*)get_club(CLUB_SALAMANCA_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_PORTUGAL_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ALVERCA_B_9CF()) return (BYTE*)get_club(CLUB_ALVERCA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BENFICA_B_9CF()) return (BYTE*)get_club(CLUB_BENFICA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BRAGA_B_9CF()) return (BYTE*)get_club(CLUB_BRAGA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CHAVES_B_9CF()) return (BYTE*)get_club(CLUB_CHAVES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MARITIMO_B_9CF()) return (BYTE*)get_club(CLUB_MARITIMO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PORTO_B_9CF()) return (BYTE*)get_club(CLUB_PORTO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPORTING_CP_B_9CF()) return (BYTE*)get_club(CLUB_SPORTING_CP_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VIT_GUIMARAES_B_9CF()) return (BYTE*)get_club(CLUB_VIT_GUIMARAES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SANTA_CLARA_B_9CF()) return (BYTE*)get_club(CLUB_SANTA_CLARA_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_NORWAY_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_AALESUND_II_9CF()) return (BYTE*)get_club(CLUB_AALESUND_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ASANE_II_9CF()) return (BYTE*)get_club(CLUB_ASANE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BAERUM_II_9CF()) return (BYTE*)get_club(CLUB_BAERUM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BODO_GLIMT_II_9CF()) return (BYTE*)get_club(CLUB_BODO_GLIMT_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BRANN_II_9CF()) return (BYTE*)get_club(CLUB_BRANN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BRYNE_II_9CF()) return (BYTE*)get_club(CLUB_BRYNE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BYASEN_II_9CF()) return (BYTE*)get_club(CLUB_BYASEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FOLLO_II_9CF()) return (BYTE*)get_club(CLUB_FOLLO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FREDRIKSTAD_II_9CF()) return (BYTE*)get_club(CLUB_FREDRIKSTAD_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FYLLINGSDALEN_II_9CF()) return (BYTE*)get_club(CLUB_FYLLINGSDALEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GJOVIK_LYN_II_9CF()) return (BYTE*)get_club(CLUB_GJOVIK_LYN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GRORUD_II_9CF()) return (BYTE*)get_club(CLUB_GRORUD_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HAMKAM_II_9CF()) return (BYTE*)get_club(CLUB_HAMKAM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HAUGESUND_II_9CF()) return (BYTE*)get_club(CLUB_HAUGESUND_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HODD_II_9CF()) return (BYTE*)get_club(CLUB_HODD_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HONEFOSS_II_9CF()) return (BYTE*)get_club(CLUB_HONEFOSS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KFUM_OSLO_II_9CF()) return (BYTE*)get_club(CLUB_KFUM_OSLO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KJELSAS_II_9CF()) return (BYTE*)get_club(CLUB_KJELSAS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KONGSVINGER_II_9CF()) return (BYTE*)get_club(CLUB_KONGSVINGER_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KRISTIANSUND_II_9CF()) return (BYTE*)get_club(CLUB_KRISTIANSUND_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LILLESTROM_II_9CF()) return (BYTE*)get_club(CLUB_LILLESTROM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LYN_II_9CF()) return (BYTE*)get_club(CLUB_LYN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MJONDALEN_II_9CF()) return (BYTE*)get_club(CLUB_MJONDALEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MOLDE_II_9CF()) return (BYTE*)get_club(CLUB_MOLDE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NARDO_II_9CF()) return (BYTE*)get_club(CLUB_NARDO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ODDS_II_9CF()) return (BYTE*)get_club(CLUB_ODDS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PORS_II_9CF()) return (BYTE*)get_club(CLUB_PORS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RANHEIM_II_9CF()) return (BYTE*)get_club(CLUB_RANHEIM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RAUFOSS_II_9CF()) return (BYTE*)get_club(CLUB_RAUFOSS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROSENBORG_II_9CF()) return (BYTE*)get_club(CLUB_ROSENBORG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SANDEFJORD_II_9CF()) return (BYTE*)get_club(CLUB_SANDEFJORD_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SANDNES_ULF_II_9CF()) return (BYTE*)get_club(CLUB_SANDNES_ULF_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SARPSBORG_II_9CF()) return (BYTE*)get_club(CLUB_SARPSBORG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SKEID_II_9CF()) return (BYTE*)get_club(CLUB_SKEID_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SOGNDAL_II_9CF()) return (BYTE*)get_club(CLUB_SOGNDAL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STABAEK_II_9CF()) return (BYTE*)get_club(CLUB_STABAEK_9CF());
		if ((DWORD)to_check->ClubID == CLUB_START_II_9CF()) return (BYTE*)get_club(CLUB_START_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STROMMEN_II_9CF()) return (BYTE*)get_club(CLUB_STROMMEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STROMSGODSET_II_9CF()) return (BYTE*)get_club(CLUB_STROMSGODSET_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TROMSO_II_9CF()) return (BYTE*)get_club(CLUB_TROMSO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TRAEFF_II_9CF()) return (BYTE*)get_club(CLUB_TRAEFF_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ULL_KISA_II_9CF()) return (BYTE*)get_club(CLUB_ULL_KISA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VARD_HAUGESUND_II_9CF()) return (BYTE*)get_club(CLUB_VARD_HAUGESUND_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VIKING_II_9CF()) return (BYTE*)get_club(CLUB_VIKING_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALERENGA_II_9CF()) return (BYTE*)get_club(CLUB_VALERENGA_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_FINLAND_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ATLANTIS_II_9CF()) return (BYTE*)get_club(CLUB_ATLANTIS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KLUBI_04_9CF()) return (BYTE*)get_club(CLUB_HJK_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ESPOO_II_9CF()) return (BYTE*)get_club(CLUB_ESPOO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HIFK_II_9CF()) return (BYTE*)get_club(CLUB_HIFK_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HONKA_II_9CF()) return (BYTE*)get_club(CLUB_HONKA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_INTER_TURKU_II_9CF()) return (BYTE*)get_club(CLUB_INTER_TURKU_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ILVES_II_9CF()) return (BYTE*)get_club(CLUB_ILVES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KUPS_II_9CF()) return (BYTE*)get_club(CLUB_KUPS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROPS_II_9CF()) return (BYTE*)get_club(CLUB_ROPS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VPS_II_9CF()) return (BYTE*)get_club(CLUB_VPS_9CF());

	}
	else if (to_check->ClubNation->NationID == NATION_POLAND_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_CHROBRY_GLOGOW_II_9CF()) return (BYTE*)get_club(CLUB_CHROBRY_GLOGOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CRACOVIA_II_9CF()) return (BYTE*)get_club(CLUB_CRACOVIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GORNIK_ZABRZE_II_9CF()) return (BYTE*)get_club(CLUB_GORNIK_ZABRZE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JAGIELLONIA_II_9CF()) return (BYTE*)get_club(CLUB_JAGIELLONIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KIELCE_II_9CF()) return (BYTE*)get_club(CLUB_KIELCE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LECH_POZNAN_II_9CF()) return (BYTE*)get_club(CLUB_LECH_POZNAN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LEGIA_WARSAW_II_9CF()) return (BYTE*)get_club(CLUB_LEGIA_WARSAW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LKS_LODZ_II_9CF()) return (BYTE*)get_club(CLUB_LKS_LODZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MIEDZ_LEGNICA_II_9CF()) return (BYTE*)get_club(CLUB_MIEDZ_LEGNICA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PIAST_GLIWICE_II_9CF()) return (BYTE*)get_club(CLUB_PIAST_GLIWICE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_POGON_SZCZECIN_II_9CF()) return (BYTE*)get_club(CLUB_POGON_SZCZECIN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RAKOW_II_9CF()) return (BYTE*)get_club(CLUB_RAKOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SLASK_WROCLAW_II_9CF()) return (BYTE*)get_club(CLUB_SLASK_WROCLAW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WIDZEW_LODZ_II_9CF()) return (BYTE*)get_club(CLUB_WIDZEW_LODZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WISLA_KRAKOW_II_9CF()) return (BYTE*)get_club(CLUB_WISLA_KRAKOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WISLA_PLOCK_II_9CF()) return (BYTE*)get_club(CLUB_WISLA_PLOCK_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZAGLEBIE_LUBIN_II_9CF()) return (BYTE*)get_club(CLUB_ZAGLEBIE_LUBIN_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_SCOTLAND_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_CELTIC_B_9CF()) return (BYTE*)get_club(CLUB_CELTIC_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HEARTS_B_9CF()) return (BYTE*)get_club(CLUB_HEARTS_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_GREECE_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ASTERAS_AKTOR_B_9CF()) return (BYTE*)get_club(CLUB_ASTERAS_AKTOR_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AEK_ATHENS_B_9CF()) return (BYTE*)get_club(CLUB_AEK_ATHENS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OLYMPIACOS_B_9CF()) return (BYTE*)get_club(CLUB_OLYMPIACOS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PAOK_B_9CF()) return (BYTE*)get_club(CLUB_PAOK_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_NETHERLANDS_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_JONG_AZ_9CF()) return (BYTE*)get_club(CLUB_AZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JONG_AJAX_9CF()) return (BYTE*)get_club(CLUB_AJAX_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JONG_ALMERE_CITY_9CF()) return (BYTE*)get_club(CLUB_ALMERE_CITY_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JONG_PSV_9CF()) return (BYTE*)get_club(CLUB_PSV_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JONG_SPARTA_ROTTERDAM_9CF()) return (BYTE*)get_club(CLUB_SPARTA_ROTTERDAM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JONG_UTRECHT_9CF()) return (BYTE*)get_club(CLUB_UTRECHT_9CF());

	}
	else if (to_check->ClubNation->NationID == NATION_BELGIUM_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ANDERLECHT_B_9CF()) return (BYTE*)get_club(CLUB_ANDERLECHT_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ANTWERP_B_9CF()) return (BYTE*)get_club(CLUB_ANTWERP_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CERCLE_BRUGGE_B_9CF()) return (BYTE*)get_club(CLUB_CERCLE_BRUGGE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CHARLEROI_B_9CF()) return (BYTE*)get_club(CLUB_CHARLEROI_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CLUB_BRUGGE_B_9CF()) return (BYTE*)get_club(CLUB_CLUB_BRUGGE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_EUPEN_B_9CF()) return (BYTE*)get_club(CLUB_EUPEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GENK_B_9CF()) return (BYTE*)get_club(CLUB_GENK_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GENT_B_9CF()) return (BYTE*)get_club(CLUB_GENT_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KV_MECHELEN_B_9CF()) return (BYTE*)get_club(CLUB_KV_MECHELEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OH_LEUVEN_B_9CF()) return (BYTE*)get_club(CLUB_OH_LEUVEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SINT_TRUIDEN_B_9CF()) return (BYTE*)get_club(CLUB_SINT_TRUIDEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STANDARD_LIEGE_B_9CF()) return (BYTE*)get_club(CLUB_STANDARD_LIEGE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_UNION_SG_B_9CF()) return (BYTE*)get_club(CLUB_UNION_SG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZULTE_WAREGEM_B_9CF()) return (BYTE*)get_club(CLUB_ZULTE_WAREGEM_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_RUSSIA_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_AKRON_2_9CF()) return (BYTE*)get_club(CLUB_AKRON_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALANIA_2_9CF()) return (BYTE*)get_club(CLUB_ALANIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ARSENAL_2_TULA_9CF()) return (BYTE*)get_club(CLUB_ARSENAL_TULA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BALTIKA_2_9CF()) return (BYTE*)get_club(CLUB_BALTIKA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CSKA_2_MOSCOW_9CF()) return (BYTE*)get_club(CLUB_CSKA_MOSCOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DINAMO_2_MAKHACHKALA_9CF()) return (BYTE*)get_club(CLUB_DINAMO_MAKHACHKALA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DYNAMO_2_MOSCOW_9CF()) return (BYTE*)get_club(CLUB_DYNAMO_MOSCOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ENISEY_2_9CF()) return (BYTE*)get_club(CLUB_ENISEY_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FAKEL_M_VORONEZH_9CF()) return (BYTE*)get_club(CLUB_FAKEL_VORONEZH_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KHIMKI_2_9CF()) return (BYTE*)get_club(CLUB_KHIMKI_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ORENBURG_2_9CF()) return (BYTE*)get_club(CLUB_ORENBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROSTOV_2_9CF()) return (BYTE*)get_club(CLUB_ROSTOV_9CF());
		if ((DWORD)to_check->ClubID == CLUB_UFA_2_9CF()) return (BYTE*)get_club(CLUB_UFA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KOSMOS_2_DOLGOPRUDNYI_9CF()) return (BYTE*)get_club(CLUB_KOSMOS_KHIMKI_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KRYLYA_SOVETOV_2_9CF()) return (BYTE*)get_club(CLUB_KRYLYA_SOVETOV_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LOKOMOTIV_KAZANKA_MOSKOW_9CF()) return (BYTE*)get_club(CLUB_LOKOMOTIV_MOSCOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RODINA_2_MOSCOW_9CF()) return (BYTE*)get_club(CLUB_RODINA_MOSCOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROTOR_2_9CF()) return (BYTE*)get_club(CLUB_ROTOR_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RUBIN_2_KAZAN_9CF()) return (BYTE*)get_club(CLUB_RUBIN_KAZAN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SKA_KHABAROVSK_2_9CF()) return (BYTE*)get_club(CLUB_SKA_KHABAROVSK_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPARTAK_2_MOSCOW_9CF()) return (BYTE*)get_club(CLUB_SPARTAK_MOSCOW_9CF());
		if ((DWORD)to_check->ClubID == CLUB_URAL_2_9CF()) return (BYTE*)get_club(CLUB_URAL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZENIT_2_9CF()) return (BYTE*)get_club(CLUB_ZENIT_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_CZECH_REPUBLIC_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_SLOVACKO_B_9CF()) return (BYTE*)get_club(CLUB_SLOVACKO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPARTA_PRAGUE_B_9CF()) return (BYTE*)get_club(CLUB_SPARTA_PRAGUE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BOHEMIANS_1905_B_9CF()) return (BYTE*)get_club(CLUB_BOHEMIANS_1905_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BANIK_OSTRAVA_B_9CF()) return (BYTE*)get_club(CLUB_BANIK_OSTRAVA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HRADEC_KRALOVE_B_9CF()) return (BYTE*)get_club(CLUB_HRADEC_KRALOVE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TABORSKO_B_9CF()) return (BYTE*)get_club(CLUB_TABORSKO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SLOVAN_LIBEREC_B_9CF()) return (BYTE*)get_club(CLUB_SLOVAN_LIBEREC_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VIKTORIA_PLZEN_B_9CF()) return (BYTE*)get_club(CLUB_VIKTORIA_PLZEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BRNO_B_9CF()) return (BYTE*)get_club(CLUB_BRNO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZLIN_B_9CF()) return (BYTE*)get_club(CLUB_ZLIN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DUKLA_PRAGUE_B_9CF()) return (BYTE*)get_club(CLUB_DUKLA_PRAGUE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_JABLONEC_B_9CF()) return (BYTE*)get_club(CLUB_JABLONEC_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MLADA_BOLESLAV_B_9CF()) return (BYTE*)get_club(CLUB_MLADA_BOLESLAV_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PARDUBICE_B_9CF()) return (BYTE*)get_club(CLUB_PARDUBICE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PRIBRAM_B_9CF()) return (BYTE*)get_club(CLUB_PRIBRAM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TEPLICE_B_9CF()) return (BYTE*)get_club(CLUB_TEPLICE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KARVINA_B_9CF()) return (BYTE*)get_club(CLUB_KARVINA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CESKE_BUDEJOVICE_B_9CF()) return (BYTE*)get_club(CLUB_CESKE_BUDEJOVICE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SIGMA_OLOMOUC_B_9CF()) return (BYTE*)get_club(CLUB_SIGMA_OLOMOUC_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SLAVIA_PRAGUE_B_9CF()) return (BYTE*)get_club(CLUB_SLAVIA_PRAGUE_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_AUSTRIA_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ADMIRA_WACKER_II_9CF()) return (BYTE*)get_club(CLUB_ADMIRA_WACKER_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AUSTRIA_VIENNA_II_9CF()) return (BYTE*)get_club(CLUB_AUSTRIA_VIENNA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LASK_II_9CF()) return (BYTE*)get_club(CLUB_LASK_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RAPID_VIENNA_II_9CF()) return (BYTE*)get_club(CLUB_RAPID_VIENNA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LIEFERING_9CF()) return (BYTE*)get_club(CLUB_RB_SALZBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AUSTRIA_LUSTENAU_II_9CF()) return (BYTE*)get_club(CLUB_AUSTRIA_LUSTENAU_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALTACH_II_9CF()) return (BYTE*)get_club(CLUB_ALTACH_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STURM_GRAZ_II_9CF()) return (BYTE*)get_club(CLUB_STURM_GRAZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ST_POLTEN_II_9CF()) return (BYTE*)get_club(CLUB_ST_POLTEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RIED_II_9CF()) return (BYTE*)get_club(CLUB_RIED_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WOLFSBERG_II_9CF()) return (BYTE*)get_club(CLUB_WOLFSBERG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WSG_TIROL_II_9CF()) return (BYTE*)get_club(CLUB_WSG_TIROL_9CF());

	}
	else if (to_check->ClubNation->NationID == NATION_SWITZERLAND_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_YOUNG_BOYS_U21_9CF()) return (BYTE*)get_club(CLUB_YOUNG_BOYS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GRASSHOPPERS_U21_9CF()) return (BYTE*)get_club(CLUB_GRASSHOPPERS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BASEL_U21_9CF()) return (BYTE*)get_club(CLUB_BASEL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LAUSANNE_U21_9CF()) return (BYTE*)get_club(CLUB_LAUSANNE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LUGANO_U21_9CF()) return (BYTE*)get_club(CLUB_LUGANO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LUZERN_U21_9CF()) return (BYTE*)get_club(CLUB_LUZERN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SION_U21_9CF()) return (BYTE*)get_club(CLUB_SION_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ST_GALLEN_U21_9CF()) return (BYTE*)get_club(CLUB_ST_GALLEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WINTERTHUR_U21_9CF()) return (BYTE*)get_club(CLUB_WINTERTHUR_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZURICH_U21_9CF()) return (BYTE*)get_club(CLUB_ZURICH_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SERVETTE_U21_9CF()) return (BYTE*)get_club(CLUB_SERVETTE_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_FRANCE_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_AJACCIO_B_9CF()) return (BYTE*)get_club(CLUB_AJACCIO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LE_HAVRE_B_9CF()) return (BYTE*)get_club(CLUB_LE_HAVRE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AUXERRE_B_9CF()) return (BYTE*)get_club(CLUB_AUXERRE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AMIENS_B_9CF()) return (BYTE*)get_club(CLUB_AMIENS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ANGERS_B_9CF()) return (BYTE*)get_club(CLUB_ANGERS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MONACO_B_9CF()) return (BYTE*)get_club(CLUB_MONACO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NANCY_B_9CF()) return (BYTE*)get_club(CLUB_NANCY_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SAINT_ETIENNE_B_9CF()) return (BYTE*)get_club(CLUB_SAINT_ETIENNE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BOURGES_B_9CF()) return (BYTE*)get_club(CLUB_BOURGES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CLERMONT_B_9CF()) return (BYTE*)get_club(CLUB_CLERMONT_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SEDAN_B_9CF()) return (BYTE*)get_club(CLUB_SEDAN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DIJON_B_9CF()) return (BYTE*)get_club(CLUB_DIJON_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GUINGAMP_B_9CF()) return (BYTE*)get_club(CLUB_GUINGAMP_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TROYES_B_9CF()) return (BYTE*)get_club(CLUB_TROYES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BORDEAUX_B_9CF()) return (BYTE*)get_club(CLUB_BORDEAUX_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LE_MANS_B_9CF()) return (BYTE*)get_club(CLUB_LE_MANS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LORIENT_B_9CF()) return (BYTE*)get_club(CLUB_LORIENT_9CF());
		if ((DWORD)to_check->ClubID == CLUB_METZ_B_9CF()) return (BYTE*)get_club(CLUB_METZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NANTES_B_9CF()) return (BYTE*)get_club(CLUB_NANTES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SOCHAUX_B_9CF()) return (BYTE*)get_club(CLUB_SOCHAUX_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CHATEAUROUX_B_9CF()) return (BYTE*)get_club(CLUB_CHATEAUROUX_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LE_PUY_B_9CF()) return (BYTE*)get_club(CLUB_LE_PUY_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LES_HERBIERS_B_9CF()) return (BYTE*)get_club(CLUB_LES_HERBIERS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LILLE_B_9CF()) return (BYTE*)get_club(CLUB_LILLE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LYON_LA_DUCHERE_B_9CF()) return (BYTE*)get_club(CLUB_LYON_LA_DUCHERE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MARIGNANE_B_9CF()) return (BYTE*)get_club(CLUB_MARIGNANE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MONTPELLIER_B_9CF()) return (BYTE*)get_club(CLUB_MONTPELLIER_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NICE_B_9CF()) return (BYTE*)get_club(CLUB_NICE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MARSEILLE_B_9CF()) return (BYTE*)get_club(CLUB_MARSEILLE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LYON_B_9CF()) return (BYTE*)get_club(CLUB_LYON_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PARIS_FC_B_9CF()) return (BYTE*)get_club(CLUB_PARIS_FC_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PSG_B_9CF()) return (BYTE*)get_club(CLUB_PSG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PAU_B_9CF()) return (BYTE*)get_club(CLUB_PAU_9CF());
		if ((DWORD)to_check->ClubID == CLUB_QUEVILLY_ROUEN_B_9CF()) return (BYTE*)get_club(CLUB_QUEVILLY_ROUEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STRASBOURG_B_9CF()) return (BYTE*)get_club(CLUB_STRASBOURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RODEZ_B_9CF()) return (BYTE*)get_club(CLUB_RODEZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BASTIA_B_9CF()) return (BYTE*)get_club(CLUB_BASTIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CAEN_B_9CF()) return (BYTE*)get_club(CLUB_CAEN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BREST_B_9CF()) return (BYTE*)get_club(CLUB_BREST_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ST_BRIEUC_B_9CF()) return (BYTE*)get_club(CLUB_ST_BRIEUC_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LAVAL_B_9CF()) return (BYTE*)get_club(CLUB_LAVAL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REIMS_B_9CF()) return (BYTE*)get_club(CLUB_REIMS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RENNES_B_9CF()) return (BYTE*)get_club(CLUB_RENNES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TOULOUSE_B_9CF()) return (BYTE*)get_club(CLUB_TOULOUSE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AVRANCHES_B_9CF()) return (BYTE*)get_club(CLUB_AVRANCHES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BOULOGNE_B_9CF()) return (BYTE*)get_club(CLUB_BOULOGNE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ORLEANS_B_9CF()) return (BYTE*)get_club(CLUB_ORLEANS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALENCIENNES_B_9CF()) return (BYTE*)get_club(CLUB_VALENCIENNES_9CF());
	}

	// default case if none found
	to_check->ClubHasLinkedClub = 0;
	return NULL;
}

void __declspec(naked) check_if_reserve_team_new_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call check_if_reserve_team_new
		add esp, 0x0c
		ret
	}
}

int force_load_9cf_clubs(DWORD old_id, DWORD new_id) {
	for (const auto& [key, value] : club_dword_match) {
		if (Get9CF(value) == old_id) {
			WriteDWORD(value, new_id);
			return 1;
		}
	}
	return 0;
}

void check_9cf() {
	for (const auto& [key, value] : club_dword_match) {
		if (Get9CF(value) == -1) {
			string msg = "Could not find club: " + key;
			create_message_box("Error", msg.c_str(), false);
		}
	}
	for (const auto& [key, value] : league_dword_match) {
		if (Get9CF(value) == -1) {
			string msg = "Could not find competition: " + key;
			create_message_box("Error", msg.c_str(), false);
		}
	}
	for (const auto& [key, value] : award_dword_match) {
		if (Get9CF(value) == -1) {
			string msg = "Could not find award: " + key;
			create_message_box("Error", msg.c_str(), false);
		}
	}
	for (const auto& [key, value] : nation_dword_match) {
		if (Get9CF(value) == -1) {
			string msg = "Could not find nation: " + key;
			create_message_box("Error", msg.c_str(), false);
		}
	}
}

extern "C" _declspec(naked) int check_9cf_c()
{
	_asm
	{
		pushad
	}
	check_9cf();
	_asm
	{
		popad
		pop edi
		pop esi
		pop ebp
		mov eax, 1
		pop ebx
		add esp, 0x220
		ret
	}
}

void setup_name_injection()
{
	// Add call to our name function after all player setups have been loaded
	PatchFunction(0x5CCCC1, (DWORD)inject_club_names);
	PatchFunction(0x60D810, (DWORD)setup_9cf_nations);
	PatchFunction(0x60EFD0, (DWORD)setup_9cf_leagues);
	PatchFunction(0x6115E0, (DWORD)setup_9cf_awards);
	PatchFunction(0x6146B0, (DWORD)setup_9cf_clubs);

	PatchFunction(0x605144, (DWORD)check_9cf_c);

	PatchFunction(0x60BA80, (DWORD)force_load_9cf_clubs);

	PatchFunction(0x540A50, (DWORD)check_if_reserve_team_new);

	if (filesystem::exists("Data/clubs_9cf.cfg")) {
		ifstream in("Data/clubs_9cf.cfg", ios_base::in);
		string entry;
		while (std::getline(in, entry))
		{
			if (entry.size() == 0) {
				continue;
			}
			if (entry[0] == '/') {
				continue;
			}
			int delim = entry.find(";");
			string code = entry.substr(0, delim);
			string name = entry.substr(delim + 1, entry.length());
			DWORD ptr = stoul(code, nullptr, 16);
			club_dword_match.insert({ name, ptr });
			WriteDWORD(ptr, -1);
		}
	}
	else {
		create_message_box("Error", "List of hard-coded clubs not found", false);
	}
	// new nations end at 0xDE9758

	if (filesystem::exists("Data/leagues_9cf.cfg")) {
		ifstream in("Data/leagues_9cf.cfg", ios_base::in);
		string entry;
		while (std::getline(in, entry))
		{
			if (entry.size() == 0) {
				continue;
			}
			if (entry[0] == '/') {
				continue;
			}
			int delim = entry.find(";");
			string code = entry.substr(0, delim);
			string name = entry.substr(delim + 1, entry.length());
			DWORD ptr = stoul(code, nullptr, 16);
			league_dword_match.insert({ name, ptr });
			WriteDWORD(ptr, -1);
		}
	}
	else {
		create_message_box("Error", "List of hard-coded leagues not found", false);
	}

	if (filesystem::exists("Data/awards_9cf.cfg")) {
		ifstream in("Data/awards_9cf.cfg", ios_base::in);
		string entry;
		while (std::getline(in, entry))
		{
			if (entry.size() == 0) {
				continue;
			}
			if (entry[0] == '/') {
				continue;
			}
			int delim = entry.find(";");
			string code = entry.substr(0, delim);
			string name = entry.substr(delim + 1, entry.length());
			DWORD ptr = stoul(code, nullptr, 16);
			award_dword_match.insert({ name, ptr });
			WriteDWORD(ptr, -1);
		}
	}
	else {
		create_message_box("Error", "List of hard-coded awards not found", false);
	}

	if (filesystem::exists("Data/nations_9cf.cfg")) {
		ifstream in("Data/nations_9cf.cfg", ios_base::in);
		string entry;
		while (std::getline(in, entry))
		{
			if (entry.size() == 0) {
				continue;
			}
			if (entry[0] == '/') {
				continue;
			}
			int delim = entry.find(";");
			string code = entry.substr(0, delim);
			string name = entry.substr(delim + 1, entry.length());
			DWORD ptr = stoul(code, nullptr, 16);
			nation_dword_match.insert({ name, ptr });
			WriteDWORD(ptr, -1);
		}
	}
	else {
		create_message_box("Error", "List of hard-coded nations not found", false);
	}
}