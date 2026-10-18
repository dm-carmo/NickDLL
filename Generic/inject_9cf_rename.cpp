#include "Helpers\Helper.h"
#include "inject_9cf_rename.h"
#include "Helpers\9cf_constants.h"
#include "Helpers\generic_functions.h"
#include <filesystem>
#include <fstream>

DWORD main_b_team_links_start_offset = 0x540a5c;
DWORD main_b_team_links_count_offset = 0x540a58;

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
	return 1;
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

BYTE* check_if_reserve_team_new(cm3_clubs* to_check, DWORD* is_main_club, DWORD a3) {
	if (!to_check) return NULL;
	// Commented to try and avoid issues related to B-teams unlinking
	//if (a3 != 0 && to_check->ClubHasLinkedClub == 0) return NULL;
	if (!to_check->ClubNation) return NULL;
	if (to_check->ClubID >= (*clubs_count - 2 * *nations_count)) return NULL;
	// Added to try and avoid issues related to B-teams unlinking
	to_check->ClubHasLinkedClub = 1;
	// the full check
	DWORD max = *(DWORD*)main_b_team_links_count_offset;
	for (DWORD i = 0; i < max; i++) {
		DWORD main = *(DWORD*)(main_b_team_links_start_offset + 8 * i);
		DWORD reserve = *(DWORD*)(main_b_team_links_start_offset + 8 * i + 4);
		if (Get9CF(main) == to_check->ClubID) {
			if (is_main_club) *is_main_club = 1;
			return (BYTE*)get_club(Get9CF(reserve));
		}
		if (Get9CF(reserve) == to_check->ClubID) {
			if (is_main_club) *is_main_club = 0;
			return (BYTE*)get_club(Get9CF(main));
		}
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

	// lists for foreign/non-EU player exceptions
	france_overseas = {
		NATION_GUADELOUPE_9CF(),
		NATION_FRENCH_GUIANA_9CF(),
		NATION_MARTINIQUE_9CF(),
		NATION_SAINT_MARTIN_9CF(),
		NATION_REUNION_9CF(),
	};
	england_overseas = {
		NATION_BERMUDA_9CF(),
		NATION_CAYMAN_ISLANDS_9CF(),
		NATION_ANGUILLA_9CF(),
		NATION_BRITISH_VIRGIN_ISLANDS_9CF(),
		NATION_MONTSERRAT_9CF(),
		NATION_TURKS_AND_CAICOS_9CF(),
		NATION_GIBRALTAR_9CF(),
	};
	brazil_fgn = {
		NATION_SYRIA_9CF(),
		NATION_HAITI_9CF(),
		NATION_AFGHANISTAN_9CF(),
	};
	china_fgn = {
		NATION_CHINESE_TAIPEI_9CF(),
		NATION_HONG_KONG_9CF(),
		NATION_MACAU_9CF(),
	};
	russia_fgn = {
		NATION_ARMENIA_9CF(),
		NATION_BELARUS_9CF(),
		NATION_KAZAKHSTAN_9CF(),
		NATION_KYRGYZSTAN_9CF(),
	};
	finland_fgn = {
		NATION_ALGERIA_9CF(),
		NATION_MOROCCO_9CF(),
		NATION_TUNISIA_9CF(),
	};
	czech_fgn = {
		NATION_SERBIA_9CF(),
		NATION_TURKEY_9CF(),
		NATION_ALBANIA_9CF(),
		NATION_MONTENEGRO_9CF(),
		NATION_NORTH_MACEDONIA_9CF(),
	};
	greece_fgn = {
		NATION_SERBIA_9CF(),
		NATION_TURKEY_9CF(),
		NATION_ALBANIA_9CF(),
		NATION_BOSNIA_9CF(),
		NATION_RUSSIA_9CF(),
	};
	france_fgn = {
		NATION_AZERBAIJAN_9CF(),
		NATION_BELARUS_9CF(),
		NATION_KAZAKHSTAN_9CF(),
		NATION_KYRGYZSTAN_9CF(),
		NATION_NEW_CALEDONIA_9CF(),
		NATION_TAHITI_9CF(),
		NATION_UZBEKISTAN_9CF(),
	};
	spain_fgn = {
		NATION_RUSSIA_9CF(),
		NATION_MOLDOVA_9CF(),
		NATION_ARMENIA_9CF(),
		NATION_BOSNIA_9CF(),
		NATION_GEORGIA_9CF(),
	};
	germany_fgn = {
		NATION_AUSTRALIA_9CF(),
		NATION_CANADA_9CF(),
		NATION_ISRAEL_9CF(),
		NATION_JAPAN_9CF(),
		NATION_NEW_ZEALAND_9CF(),
		NATION_SOUTH_KOREA_9CF(),
		NATION_USA_9CF(),
	};
	japan_fgn = {
		NATION_THAILAND_9CF(),
		NATION_VIETNAM_9CF(),
		NATION_MYANMAR_9CF(),
		NATION_CAMBODIA_9CF(),
		NATION_SINGAPORE_9CF(),
		NATION_INDONESIA_9CF(),
		NATION_MALAYSIA_9CF(),
	};
	turkic = {
		NATION_KAZAKHSTAN_9CF(),
		NATION_KYRGYZSTAN_9CF(),
		NATION_AZERBAIJAN_9CF(),
		NATION_UZBEKISTAN_9CF(),
		NATION_TURKEY_9CF(),
		NATION_TURKMENISTAN_9CF(),
	};
	cotonou = {
		NATION_ANGOLA_9CF(),
		NATION_ANTIGUA_BARBUDA_9CF(),
		NATION_BAHAMAS_9CF(),
		NATION_BARBADOS_9CF(),
		NATION_BELIZE_9CF(),
		NATION_BENIN_9CF(),
		NATION_BOTSWANA_9CF(),
		NATION_BURKINA_FASO_9CF(),
		NATION_BURUNDI_9CF(),
		NATION_CAMEROON_9CF(),
		NATION_CAPE_VERDE_9CF(),
		NATION_CENTRAL_AFRICA_9CF(),
		NATION_CHAD_9CF(),
		NATION_COMOROS_9CF(),
		NATION_CONGO_9CF(),
		NATION_COOK_ISLANDS_9CF(),
		NATION_CUBA_9CF(),
		NATION_DJIBOUTI_9CF(),
		NATION_DOMINICA_9CF(),
		NATION_DOMINICAN_REPUBLIC_9CF(),
		NATION_DR_CONGO_9CF(),
		NATION_TIMOR_LESTE_9CF(),
		NATION_EQUATORIAL_GUINEA_9CF(),
		NATION_ERITREA_9CF(),
		NATION_ESWATINI_9CF(),
		NATION_ETHIOPIA_9CF(),
		NATION_FIJI_9CF(),
		NATION_GABON_9CF(),
		NATION_GAMBIA_9CF(),
		NATION_GHANA_9CF(),
		NATION_GRENADA_9CF(),
		NATION_GUINEA_9CF(),
		NATION_GUINEA_BISSAU_9CF(),
		NATION_GUYANA_9CF(),
		NATION_HAITI_9CF(),
		NATION_IVORY_COAST_9CF(),
		NATION_JAMAICA_9CF(),
		NATION_KENYA_9CF(),
		NATION_LESOTHO_9CF(),
		NATION_LIBERIA_9CF(),
		NATION_MADAGASCAR_9CF(),
		NATION_MALAWI_9CF(),
		NATION_MALI_9CF(),
		NATION_MAURITANIA_9CF(),
		NATION_MAURITIUS_9CF(),
		NATION_MOZAMBIQUE_9CF(),
		NATION_NAMIBIA_9CF(),
		NATION_NIGER_9CF(),
		NATION_NIGERIA_9CF(),
		NATION_PAPUA_NEW_GUINEA_9CF(),
		NATION_RWANDA_9CF(),
		NATION_ST_LUCIA_9CF(),
		NATION_ST_KITTS_NEVIS_9CF(),
		NATION_ST_VINCENT_9CF(),
		NATION_SAMOA_9CF(),
		NATION_SAO_TOME_PRINCIPE_9CF(),
		NATION_SENEGAL_9CF(),
		NATION_SEYCHELLES_9CF(),
		NATION_SIERRA_LEONE_9CF(),
		NATION_SOLOMON_ISLANDS_9CF(),
		NATION_SOMALIA_9CF(),
		NATION_SOUTH_AFRICA_9CF(),
		NATION_SUDAN_9CF(),
		NATION_TANZANIA_9CF(),
		NATION_TOGO_9CF(),
		NATION_TONGA_9CF(),
		NATION_TRINIDAD_TOBAGO_9CF(),
		NATION_UGANDA_9CF(),
		NATION_VANUATU_9CF(),
		NATION_ZAMBIA_9CF(),
		NATION_ZIMBABWE_9CF(),
	};

	// lists for player naturalization

	naturalize_never = {
		NATION_AMERICAN_SAMOA_9CF(),
		NATION_ARUBA_9CF(),
		NATION_BRITISH_VIRGIN_ISLANDS_9CF(),
		NATION_US_VIRGIN_ISLANDS_9CF(),
		NATION_CHINA_9CF(),
		NATION_CURACAO_9CF(),
		NATION_FRENCH_GUIANA_9CF(),
		NATION_GUADELOUPE_9CF(),
		NATION_GUAM_9CF(),
		NATION_KUWAIT_9CF(),
		NATION_LEBANON_9CF(),
		NATION_LIBERIA_9CF(),
		NATION_MARTINIQUE_9CF(),
		NATION_MONTSERRAT_9CF(),
		NATION_MYANMAR_9CF(),
		NATION_NEW_CALEDONIA_9CF(),
		NATION_NORTH_KOREA_9CF(),
		NATION_NORTHERN_MARIANA_9CF(),
		NATION_PALESTINE_9CF(),
		NATION_PUERTO_RICO_9CF(),
		NATION_REUNION_9CF(),
		NATION_SAINT_MARTIN_9CF(),
		NATION_SINT_MAARTEN_9CF(),
		NATION_TAHITI_9CF(),
	};
	naturalize_2_years = {
		NATION_ARGENTINA_9CF(),
		NATION_GIBRALTAR_9CF(),
	};
	naturalize_3_years = {
		NATION_ARMENIA_9CF(),
		NATION_BOLIVIA_9CF(),
		NATION_CANADA_9CF(),
		NATION_HONDURAS_9CF(),
		NATION_ISRAEL_9CF(),
		NATION_POLAND_9CF(),
		NATION_SERBIA_9CF(),
	};
	naturalize_4_years = {
		NATION_AUSTRALIA_9CF(),
		NATION_BRAZIL_9CF(),
		NATION_ETHIOPIA_9CF(),
		NATION_NICARAGUA_9CF(),
	};
	naturalize_6_years = {
		NATION_ANTIGUA_BARBUDA_9CF(),
		NATION_BAHAMAS_9CF(),
		NATION_GHANA_9CF(),
		NATION_GUINEA_BISSAU_9CF(),
		NATION_MAURITIUS_9CF(),
	};
	naturalize_7_years = {
		NATION_ALGERIA_9CF(),
		NATION_BELARUS_9CF(),
		NATION_CAMBODIA_9CF(),
		NATION_COSTA_RICA_9CF(),
		NATION_DOMINICA_9CF(),
		NATION_DR_CONGO_9CF(),
		NATION_GREECE_9CF(),
		NATION_GRENADA_9CF(),
		NATION_GUYANA_9CF(),
		NATION_HONG_KONG_9CF(),
		NATION_ICELAND_9CF(),
		NATION_JAMAICA_9CF(),
		NATION_KENYA_9CF(),
		NATION_MACAU_9CF(),
		NATION_MALAWI_9CF(),
		NATION_SOMALIA_9CF(),
		NATION_ST_LUCIA_9CF(),
		NATION_TANZANIA_9CF(),
		NATION_TURKMENISTAN_9CF(),
	};
	naturalize_8_years = {
		NATION_BOSNIA_9CF(),
		NATION_CROATIA_9CF(),
		NATION_ESTONIA_9CF(),
		NATION_FINLAND_9CF(),
		NATION_HUNGARY_9CF(),
		NATION_NORTH_MACEDONIA_9CF(),
		NATION_NORWAY_9CF(),
		NATION_PAPUA_NEW_GUINEA_9CF(),
		NATION_ROMANIA_9CF(),
		NATION_SLOVAKIA_9CF(),
		NATION_TRINIDAD_TOBAGO_9CF(),
	};
	naturalize_9_years = {
		NATION_DENMARK_9CF(),
		NATION_FAROE_ISLANDS_9CF(),
		NATION_ST_VINCENT_9CF(),
	};
	naturalize_10_years = {
		NATION_ANGOLA_9CF(),
		NATION_AUSTRIA_9CF(),
		NATION_BENIN_9CF(),
		NATION_BERMUDA_9CF(),
		NATION_BOTSWANA_9CF(),
		NATION_BURKINA_FASO_9CF(),
		NATION_BURUNDI_9CF(),
		NATION_COMOROS_9CF(),
		NATION_CONGO_9CF(),
		NATION_COOK_ISLANDS_9CF(),
		NATION_DJIBOUTI_9CF(),
		NATION_TIMOR_LESTE_9CF(),
		NATION_EGYPT_9CF(),
		NATION_GEORGIA_9CF(),
		NATION_IRAQ_9CF(),
		NATION_ITALY_9CF(),
		NATION_LAOS_9CF(),
		NATION_LIBYA_9CF(),
		NATION_LIECHTENSTEIN_9CF(),
		NATION_LITHUANIA_9CF(),
		NATION_MALAYSIA_9CF(),
		NATION_MALI_9CF(),
		NATION_MAURITANIA_9CF(),
		NATION_MOLDOVA_9CF(),
		NATION_MONTENEGRO_9CF(),
		NATION_NAMIBIA_9CF(),
		NATION_NIGER_9CF(),
		NATION_PHILIPPINES_9CF(),
		NATION_PORTUGAL_9CF(),
		NATION_SOUTH_SUDAN_9CF(),
		NATION_SAUDI_ARABIA_9CF(),
		NATION_SENEGAL_9CF(),
		NATION_SEYCHELLES_9CF(),
		NATION_SINGAPORE_9CF(),
		NATION_SLOVENIA_9CF(),
		NATION_SPAIN_9CF(),
		NATION_SUDAN_9CF(),
		NATION_SWITZERLAND_9CF(),
		NATION_UGANDA_9CF(),
		NATION_VANUATU_9CF(),
		NATION_VENEZUELA_9CF(),
		NATION_YEMEN_9CF(),
		NATION_ZAMBIA_9CF(),
		NATION_ZIMBABWE_9CF(),
	};
	naturalize_12_years = {
		NATION_INDIA_9CF(),
		NATION_MALDIVES_9CF(),
	};
	naturalize_14_years = {
		NATION_ST_KITTS_NEVIS_9CF(),
	};
	naturalize_15_years = {
		NATION_CHAD_9CF(),
		NATION_GAMBIA_9CF(),
		NATION_JORDAN_9CF(),
		NATION_NEPAL_9CF(),
		NATION_NIGERIA_9CF(),
		NATION_OMAN_9CF(),
		NATION_SIERRA_LEONE_9CF(),
	};
	naturalize_20_years = {
		NATION_ANDORRA_9CF(),
		NATION_BAHRAIN_9CF(),
		NATION_BHUTAN_9CF(),
		NATION_BRUNEI_9CF(),
		NATION_ERITREA_9CF(),
		NATION_SAN_MARINO_9CF(),
	};
	naturalize_25_years = {
		//NATION_QATAR_9CF(),
	};
	naturalize_40_years = {
		NATION_EQUATORIAL_GUINEA_9CF(),
	};
	commonwealth = {
		NATION_ANTIGUA_BARBUDA_9CF(),
		NATION_AUSTRALIA_9CF(),
		NATION_BAHAMAS_9CF(),
		NATION_BANGLADESH_9CF(),
		NATION_BARBADOS_9CF(),
		NATION_BELIZE_9CF(),
		NATION_BOTSWANA_9CF(),
		NATION_BRUNEI_9CF(),
		NATION_CAMEROON_9CF(),
		NATION_CANADA_9CF(),
		NATION_CYPRUS_9CF(),
		NATION_DOMINICA_9CF(),
		NATION_ESWATINI_9CF(),
		NATION_FIJI_9CF(),
		NATION_GABON_9CF(),
		NATION_GAMBIA_9CF(),
		NATION_GHANA_9CF(),
		NATION_GRENADA_9CF(),
		NATION_GUYANA_9CF(),
		NATION_INDIA_9CF(),
		NATION_JAMAICA_9CF(),
		NATION_KENYA_9CF(),
		NATION_LESOTHO_9CF(),
		NATION_MALAWI_9CF(),
		NATION_MALAYSIA_9CF(),
		NATION_MALDIVES_9CF(),
		NATION_MALTA_9CF(),
		NATION_MAURITIUS_9CF(),
		NATION_MOZAMBIQUE_9CF(),
		NATION_NAMIBIA_9CF(),
		NATION_NEW_ZEALAND_9CF(),
		NATION_NIGERIA_9CF(),
		NATION_PAKISTAN_9CF(),
		NATION_PAPUA_NEW_GUINEA_9CF(),
		NATION_RWANDA_9CF(),
		NATION_ST_KITTS_NEVIS_9CF(),
		NATION_ST_LUCIA_9CF(),
		NATION_ST_VINCENT_9CF(),
		NATION_SAMOA_9CF(),
		NATION_SEYCHELLES_9CF(),
		NATION_SIERRA_LEONE_9CF(),
		NATION_SINGAPORE_9CF(),
		NATION_SOLOMON_ISLANDS_9CF(),
		NATION_SOUTH_AFRICA_9CF(),
		NATION_SRI_LANKA_9CF(),
		NATION_TANZANIA_9CF(),
		NATION_TOGO_9CF(),
		NATION_TONGA_9CF(),
		NATION_TRINIDAD_TOBAGO_9CF(),
		NATION_UGANDA_9CF(),
		NATION_ENGLAND_9CF(),
		NATION_SCOTLAND_9CF(),
		NATION_WALES_9CF(),
		NATION_NORTHERN_IRELAND_9CF(),
		NATION_VANUATU_9CF(),
		NATION_ZAMBIA_9CF(),
	};
	hispanic_american = {
		NATION_ARGENTINA_9CF(),
		NATION_BOLIVIA_9CF(),
		NATION_CHILE_9CF(),
		NATION_COLOMBIA_9CF(),
		NATION_COSTA_RICA_9CF(),
		NATION_CUBA_9CF(),
		NATION_DOMINICAN_REPUBLIC_9CF(),
		NATION_ECUADOR_9CF(),
		NATION_EL_SALVADOR_9CF(),
		NATION_GUATEMALA_9CF(),
		NATION_HONDURAS_9CF(),
		NATION_MEXICO_9CF(),
		NATION_NICARAGUA_9CF(),
		NATION_PANAMA_9CF(),
		NATION_PARAGUAY_9CF(),
		NATION_PERU_9CF(),
		NATION_PUERTO_RICO_9CF(),
		NATION_URUGUAY_9CF(),
		NATION_VENEZUELA_9CF(),
	};
	caribbean = {
		NATION_ANGUILLA_9CF(),
		NATION_ANTIGUA_BARBUDA_9CF(),
		NATION_ARUBA_9CF(),
		NATION_BAHAMAS_9CF(),
		NATION_BARBADOS_9CF(),
		NATION_BERMUDA_9CF(),
		NATION_BELIZE_9CF(),
		NATION_BONAIRE_9CF(),
		NATION_BRITISH_VIRGIN_ISLANDS_9CF(),
		NATION_CAYMAN_ISLANDS_9CF(),
		NATION_CUBA_9CF(),
		NATION_CURACAO_9CF(),
		NATION_DOMINICA_9CF(),
		NATION_DOMINICAN_REPUBLIC_9CF(),
		NATION_GRENADA_9CF(),
		NATION_GUADELOUPE_9CF(),
		NATION_GUYANA_9CF(),
		NATION_HAITI_9CF(),
		NATION_JAMAICA_9CF(),
		NATION_MARTINIQUE_9CF(),
		NATION_MONTSERRAT_9CF(),
		NATION_PUERTO_RICO_9CF(),
		NATION_ST_KITTS_NEVIS_9CF(),
		NATION_ST_LUCIA_9CF(),
		NATION_SAINT_MARTIN_9CF(),
		NATION_ST_VINCENT_9CF(),
		NATION_SINT_MAARTEN_9CF(),
		NATION_SURINAM_9CF(),
		NATION_NICARAGUA_9CF(),
		NATION_TRINIDAD_TOBAGO_9CF(),
		NATION_TURKS_AND_CAICOS_9CF(),
		NATION_US_VIRGIN_ISLANDS_9CF(),
	};
	central_america = {
		NATION_COSTA_RICA_9CF(),
		NATION_EL_SALVADOR_9CF(),
		NATION_GUATEMALA_9CF(),
		NATION_HONDURAS_9CF(),
		NATION_MEXICO_9CF(),
		NATION_NICARAGUA_9CF(),
		NATION_PANAMA_9CF(),
	};
	special_spain = {
		NATION_ANDORRA_9CF(),
		NATION_BRAZIL_9CF(),
		NATION_PHILIPPINES_9CF(),
		NATION_PORTUGAL_9CF(),
	};
	special_mexico = {
		NATION_ANDORRA_9CF(),
		NATION_BRAZIL_9CF(),
		NATION_GIBRALTAR_9CF(),
		NATION_PORTUGAL_9CF(),
	};
	special_portugal = {
		NATION_ANGOLA_9CF(),
		NATION_BRAZIL_9CF(),
		NATION_CAPE_VERDE_9CF(),
		NATION_GUINEA_BISSAU_9CF(),
		NATION_EQUATORIAL_GUINEA_9CF(),
		NATION_MOZAMBIQUE_9CF(),
		NATION_PORTUGAL_9CF(),
		NATION_SAO_TOME_PRINCIPE_9CF(),
		NATION_TIMOR_LESTE_9CF(),
	};
	arab = {
		NATION_ALGERIA_9CF(),
		NATION_BAHRAIN_9CF(),
		NATION_COMOROS_9CF(),
		NATION_DJIBOUTI_9CF(),
		NATION_EGYPT_9CF(),
		NATION_IRAQ_9CF(),
		NATION_JORDAN_9CF(),
		NATION_KUWAIT_9CF(),
		NATION_LEBANON_9CF(),
		NATION_LIBYA_9CF(),
		NATION_MAURITANIA_9CF(),
		NATION_MOROCCO_9CF(),
		NATION_OMAN_9CF(),
		NATION_PALESTINE_9CF(),
		NATION_QATAR_9CF(),
		NATION_SAUDI_ARABIA_9CF(),
		NATION_SOMALIA_9CF(),
		NATION_SUDAN_9CF(),
		NATION_SYRIA_9CF(),
		NATION_TUNISIA_9CF(),
		NATION_UAE_9CF(),
		NATION_YEMEN_9CF(),
	};
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
	WriteJMP(0x60D810, (DWORD)setup_9cf_nations);
	WriteJMP(0x60EFD0, (DWORD)setup_9cf_leagues);
	WriteJMP(0x6115E0, (DWORD)setup_9cf_awards);
	WriteJMP(0x6146B0, (DWORD)setup_9cf_clubs);

	WriteJMP(0x605144, (DWORD)check_9cf_c);

	WriteJMP(0x60BA80, (DWORD)force_load_9cf_clubs);

	WriteJMP(0x540A50, (DWORD)check_if_reserve_team_new);

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

	if (filesystem::exists("Data/main_b_team_links.cfg")) {
		ifstream in("Data/main_b_team_links.cfg", ios_base::in);
		string entry;
		DWORD num_entries = 0;
		while (std::getline(in, entry))
		{
			if (entry.size() == 0) {
				continue;
			}
			if (entry[0] == '/') {
				continue;
			}
			int delim = entry.find(";");
			int delim2 = entry.find(" /");
			if (delim2 == string::npos) delim2 = entry.length();
			string main_9cf = entry.substr(0, delim);
			string res_9cf = entry.substr(delim + 1, delim2);
			DWORD ptr_main = stoul(main_9cf, nullptr, 16);
			DWORD ptr_res = stoul(res_9cf, nullptr, 16);
			WriteDWORD(main_b_team_links_start_offset + 8 * num_entries, ptr_main);
			WriteDWORD(main_b_team_links_start_offset + 8 * num_entries + 4, ptr_res);
			num_entries++;
		}
		WriteDWORD(main_b_team_links_count_offset, num_entries);
	}
	else {
		create_message_box("Error", "List of hard-coded reserve team links not found", false);
	}
}