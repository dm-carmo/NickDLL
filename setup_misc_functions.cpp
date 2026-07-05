#include <windows.h>
#include <Structures/CMHeader.h>
#include <Helpers/9cf_constants.h>
#include <Helpers/generic_functions.h>
#include "Helpers/Helper.h"

static WORD(*rgb_to_word_5E4800)(unsigned char a1, unsigned char a2, unsigned char a3, DWORD* a4) =
(WORD(*)(unsigned char a1, unsigned char a2, unsigned char a3, DWORD * a4))(0x5E4800);

WORD* default_comp_colour_fg = (WORD*)0xAE3184;
WORD* default_comp_colour_bg = (WORD*)0xAEBE04;

vector<DWORD> friendly_aug_30plus4 = {
	0x5CA5BE, 0x5CA8B3, 0x5CA9FC, 0x5CAA92, 0x5CAB6D, 0x5CADBD, 0x5CAE51, 0x5CAEF9, 0x5CAFC5, 0x5CB0A9, 0x5CB1F6, 0x5CB2A9, 0x5CB4DD,
};
vector<DWORD> friendly_aug_30plus3 = {
	0x5CA64F, 0x5CA77C, 0x5CACD9, 0x5CB427, 0x5CB570, 0x5CB646, 0x5CB751,
};
vector<DWORD> friendly_sept_3plus4 = {
	0x5CA678, 0x5CB596, 0x5CB787,
};
vector<DWORD> friendly_sept_3plus3 = {
	0x5CA8E6, 0x5CAAB7, 0x5CAE75, 0x5CAFF8, 0x5CB0DE, 0x5CB22B, 0x5CB2DE,
};
vector<DWORD> friendly_oct_4plus4 = {
	0x5CA7AF, 0x5CA91B, 0x5CAAE0, 0x5CB261, 0x5CB7BB,
};
vector<DWORD> friendly_oct_4plus3 = {
	0x5CA69D, 0x5CAA21, 0x5CABD6, 0x5CAD42, 0x5CAE9B, 0x5CB02D, 0x5CB136, 0x5CB35A, 0x5CB48E, 0x5CB5BB,
};
vector<DWORD> friendly_march_21plus4 = {
	0x5CA599, 0x5CA609, 0x5CA817, 0x5CAB38, 0x5CAC41, 0x5CAD98, 0x5CAE07, 0x5CAF2A, 0x5CB527, 0x5CB610, 0x5CB6B2,
};
vector<DWORD> friendly_march_21plus3 = {
	0x5CA743, 0x5CA9D6, 0x5CAA6C, 0x5CB083, 0x5CB187, 0x5CB283, 0x5CB393, 0x5CB4B7,
};

int show_extra_leagues_in_start(BYTE* nation, DWORD dest_ptr, int a3) {
	if (!nation || !dest_ptr || a3 < 20) return 0;
	cm3_nations* cm3_nation = (cm3_nations*)nation;
	char* league_str;
	if (cm3_nation->NationID == NATION_ARGENTINA_9CF()) {
		league_str = "Primera B/Torneo Federal";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_BELGIUM_9CF()) {
		league_str = "Division 2";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_ENGLAND_9CF()) {
		league_str = "National Leagues";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_FINLAND_9CF()) {
		league_str = "Kakkonen";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_GERMANY_9CF()) {
		league_str = "Regionalliga";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_JAPAN_9CF()) {
		league_str = "JFL";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_NORWAY_9CF()) {
		league_str = "3. Divisjon";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_PORTUGAL_9CF()) {
		league_str = "Campeonato de Portugal";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_SCOTLAND_9CF()) {
		league_str = "Highland/Lowland";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_SPAIN_9CF()) {
		league_str = "Segunda Federación";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_SWEDEN_9CF()) {
		league_str = "Division 2";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_TURKEY_9CF()) {
		league_str = "3. Lig";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	return 0;
}

int parent_child_stages(int child_stage_id) {
	if (child_stage_id >= 0x3e8 && child_stage_id <= 0x3fb) return GroupStage;
	if (child_stage_id >= 0x41f && child_stage_id <= 0x42e) return GroupStage;
	if (child_stage_id == EasternConference || child_stage_id == WesternConference || child_stage_id == CentralConference) return GroupStage;
	//if (child_stage_id == BestPlacedTeams) return GroupStage;
	if (child_stage_id >= 0x475 && child_stage_id <= 0x47A) return LeagueA;
	if (child_stage_id >= 0x459 && child_stage_id <= 0x45C) return LeagueB;
	if (child_stage_id >= 0x40F && child_stage_id <= 0x412) return LeagueC;
	if (child_stage_id >= 0x473 && child_stage_id <= 0x474) return LeagueD;
	if (child_stage_id >= 0x3fd && child_stage_id <= 0x406) return FirstRound;
	if ((child_stage_id >= 0x407 && child_stage_id <= 0x40B) || child_stage_id == SecondRoundGroupF ||
		(child_stage_id >= 0x42f && child_stage_id <= 0x431)) return SecondRound;
	if (child_stage_id >= 0x47e && child_stage_id <= 0x47f) return FourthRound;
	if (child_stage_id >= 0x40c && child_stage_id <= 0x40e) return ThirdRound;
	//if (child_stage_id >= 0x43d && child_stage_id <= 0x43e) return AperturaGroupStage;
	//if (child_stage_id >= 0x445 && child_stage_id <= 0x446) return ClausuraGroupStage;
	if (child_stage_id >= 0x44d && child_stage_id <= 0x450) return PromotionGroupStage;
	if (child_stage_id >= 0x47c && child_stage_id <= 0x47d) return RelegationGroupStage;
	if (child_stage_id >= 0x43f && child_stage_id <= 0x440) return FirstStage;
	if (child_stage_id >= 0x441 && child_stage_id <= 0x442) return SecondStage;
	return -1;
}

int comp_colours_in_header(BYTE* club_comp, WORD* fg_titlebar, WORD* bg_titlebar) {
	*fg_titlebar = *default_comp_colour_fg;
	*bg_titlebar = *default_comp_colour_bg;
	if (club_comp) {
		cm3_club_comps* cm3_comp = (cm3_club_comps*)club_comp;
		cm3_colours* fg = cm3_comp->ClubCompForegroundColour;
		cm3_colours* bg = cm3_comp->ClubCompBackgroundColour;
		if (fg && bg) {
			*fg_titlebar = rgb_to_word_5E4800(fg->ColourRedIntensity, fg->ColourGreenIntensity, fg->ColourBlueIntensity, 0);
			*bg_titlebar = rgb_to_word_5E4800(bg->ColourRedIntensity, bg->ColourGreenIntensity, bg->ColourBlueIntensity, 0);
		}
		else if (cm3_comp->ClubCompNation) {
			fg = cm3_comp->ClubCompNation->NationForegroundColour1;
			bg = cm3_comp->ClubCompNation->NationBackgroundColour1;
			if (fg && bg)
			{
				*fg_titlebar = rgb_to_word_5E4800(fg->ColourRedIntensity, fg->ColourGreenIntensity, fg->ColourBlueIntensity, 0);
				*bg_titlebar = rgb_to_word_5E4800(bg->ColourRedIntensity, bg->ColourGreenIntensity, bg->ColourBlueIntensity, 0);
			}
		}
		return 1;
	}
	else return 0;
}

char* minor_premier = "  Minor Premiers";
void __declspec(naked) aus_minor_premier_in_history()
{
	__asm
	{
		push esi
		mov esi, dword ptr ds : [esi + 4]
		mov esi, dword ptr ds : [esi]
		cmp esi, dword ptr ds : [0x9CF89C]
		pop esi
		jnz not_australia
		push minor_premier
		jmp exit_func
		not_australia :
		push 0x990B6C
			exit_func :
			push 0x46B723
			ret
	}
}

// In club info page, shows nation based on club's stadium if they have one
// based on a post by djole2mcloud: https://champman0102.net/viewtopic.php?p=32799#p32799
void __declspec(naked) show_club_country_based() {
	__asm {
		mov ecx, dword ptr ds : [esi + 0x69]
		test ecx, ecx
		je default_case
		mov ecx, dword ptr ds : [ecx + 0x38]
		test ecx, ecx
		je default_case
		mov ecx, dword ptr ds : [ecx + 0x1f]
		test ecx, ecx
		je default_case
		mov edi, ecx
		push ecx
		push case_continue
		push 0x53B3D0
		ret
		case_continue :
		mov cx, word ptr ds : [0xaebdec]
			add esp, 4
			mov dx, word ptr ds : [0xaebdea]
			push eax
			push 0x7d5
			add edi, 4
			push edi
			push 0x460dc0
			ret
			default_case :
		push 0x460d95
			ret
	}
}

void club_pro_status_with_continental_comp(BYTE* _this) {
	cm3_clubs* club = (cm3_clubs*)_this;
	char continental_comp[64];
	if (club->ClubEuroFlag >= 0) {
		cm3_club_comps* comp = get_comp(club->ClubEuroFlag);
		sprintf(continental_comp, " (%s)", comp->ClubCompName);
	}
	else {
		sprintf(continental_comp, "");
	}
	char pro_status[128];
	if (club->ClubProfessionalStatus == Professional) {
		sprintf(pro_status, "%s%s", "Professional", continental_comp);
	}
	else if (club->ClubProfessionalStatus == SemiProfessional) {
		sprintf(pro_status, "%s%s", "Semi-Professional", continental_comp);
	}
	else if (club->ClubProfessionalStatus == Amateur) {
		sprintf(pro_status, "%s%s", "Amateur", continental_comp);
	}
	else {
		sprintf(pro_status, "%s%s", "Unknown", continental_comp);
	}
	sub_66F4E0(0xDE1F64, (DWORD)&pro_status[0]);
}

void __declspec(naked) club_pro_status_with_continental_comp_c() {
	__asm
	{
		mov eax, esp
		push esi
		call club_pro_status_with_continental_comp
		add esp, 0x4
		push 0x460F28
		ret
	}
}

void player_gain_nationality() {
	vector<DWORD> naturalize_never = {
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
	vector<DWORD> naturalize_2_years = {
		NATION_ARGENTINA_9CF(),
		NATION_GIBRALTAR_9CF(),
	};
	vector<DWORD> naturalize_3_years = {
		NATION_ARMENIA_9CF(),
		NATION_BOLIVIA_9CF(),
		NATION_CANADA_9CF(),
		NATION_HONDURAS_9CF(),
		NATION_ISRAEL_9CF(),
		NATION_POLAND_9CF(),
		NATION_SERBIA_9CF(),
	};
	vector<DWORD> naturalize_4_years = {
		NATION_AUSTRALIA_9CF(),
		NATION_BRAZIL_9CF(),
		NATION_ETHIOPIA_9CF(),
		NATION_NICARAGUA_9CF(),
	};
	vector<DWORD> naturalize_6_years = {
		NATION_ANTIGUA_BARBUDA_9CF(),
		NATION_BAHAMAS_9CF(),
		NATION_GHANA_9CF(),
		NATION_GUINEA_BISSAU_9CF(),
		NATION_MAURITIUS_9CF(),
	};
	vector<DWORD> naturalize_7_years = {
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
	vector<DWORD> naturalize_8_years = {
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
	vector<DWORD> naturalize_9_years = {
		NATION_DENMARK_9CF(),
		NATION_FAROE_ISLANDS_9CF(),
		NATION_ST_VINCENT_9CF(),
	};
	vector<DWORD> naturalize_10_years = {
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
		NATION_TIMOR_9CF(),
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
	vector<DWORD> naturalize_12_years = {
		NATION_INDIA_9CF(),
		NATION_MALDIVES_9CF(),
	};
	vector<DWORD> naturalize_14_years = {
		NATION_ST_KITTS_NEVIS_9CF(),
	};
	vector<DWORD> naturalize_15_years = {
		NATION_CHAD_9CF(),
		NATION_GAMBIA_9CF(),
		NATION_JORDAN_9CF(),
		NATION_NEPAL_9CF(),
		NATION_NIGERIA_9CF(),
		NATION_OMAN_9CF(),
		NATION_SIERRA_LEONE_9CF(),
	};
	vector<DWORD> naturalize_20_years = {
		NATION_ANDORRA_9CF(),
		NATION_BAHRAIN_9CF(),
		NATION_BHUTAN_9CF(),
		NATION_BRUNEI_9CF(),
		NATION_ERITREA_9CF(),
		NATION_SAN_MARINO_9CF(),
	};
	vector<DWORD> naturalize_25_years = {
		//NATION_QATAR_9CF(),
	};
	vector<DWORD> naturalize_40_years = {
		NATION_EQUATORIAL_GUINEA_9CF(),
	};
	vector<DWORD> uk_ireland = {
		NATION_ENGLAND_9CF(),
		NATION_IRELAND_9CF(),
		NATION_NORTHERN_IRELAND_9CF(),
		NATION_SCOTLAND_9CF(),
		NATION_WALES_9CF(),
	};
	vector<DWORD> commonwealth = {
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
	vector<DWORD> hispanic_american = {
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
	vector<DWORD> caribbean = {
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
	vector<DWORD> central_america = {
		NATION_COSTA_RICA_9CF(),
		NATION_EL_SALVADOR_9CF(),
		NATION_GUATEMALA_9CF(),
		NATION_HONDURAS_9CF(),
		NATION_MEXICO_9CF(),
		NATION_NICARAGUA_9CF(),
		NATION_PANAMA_9CF(),
	};
	vector<DWORD> special_spain = {
		NATION_ANDORRA_9CF(),
		NATION_BRAZIL_9CF(),
		NATION_PHILIPPINES_9CF(),
		NATION_PORTUGAL_9CF(),
	};
	vector<DWORD> special_mexico = {
		NATION_ANDORRA_9CF(),
		NATION_BRAZIL_9CF(),
		NATION_GIBRALTAR_9CF(),
		NATION_PORTUGAL_9CF(),
	};
	vector<DWORD> special_portugal = {
		NATION_ANGOLA_9CF(),
		NATION_BRAZIL_9CF(),
		NATION_CAPE_VERDE_9CF(),
		NATION_GUINEA_BISSAU_9CF(),
		NATION_EQUATORIAL_GUINEA_9CF(),
		NATION_MOZAMBIQUE_9CF(),
		NATION_PORTUGAL_9CF(),
		NATION_SAO_TOME_PRINCIPE_9CF(),
		NATION_TIMOR_9CF(),
	};
	vector<DWORD> arab = {
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
	vector<DWORD> eea = {
		NATION_ICELAND_9CF(),
		NATION_LIECHTENSTEIN_9CF(),
		NATION_NORWAY_9CF(),
		NATION_SWITZERLAND_9CF(),
	};
	vector<DWORD> european_union = {
		NATION_AUSTRIA_9CF(),
		NATION_BELGIUM_9CF(),
		NATION_BULGARIA_9CF(),
		NATION_CROATIA_9CF(),
		NATION_CYPRUS_9CF(),
		NATION_CZECH_REPUBLIC_9CF(),
		NATION_DENMARK_9CF(),
		NATION_ESTONIA_9CF(),
		NATION_FINLAND_9CF(),
		NATION_FRANCE_9CF(),
		NATION_GERMANY_9CF(),
		NATION_GREECE_9CF(),
		NATION_HUNGARY_9CF(),
		NATION_IRELAND_9CF(),
		NATION_ITALY_9CF(),
		NATION_LATVIA_9CF(),
		NATION_LITHUANIA_9CF(),
		NATION_LUXEMBOURG_9CF(),
		NATION_MALTA_9CF(),
		NATION_NETHERLANDS_9CF(),
		NATION_POLAND_9CF(),
		NATION_PORTUGAL_9CF(),
		NATION_ROMANIA_9CF(),
		NATION_SLOVAKIA_9CF(),
		NATION_SLOVENIA_9CF(),
		NATION_SPAIN_9CF(),
		NATION_SWEDEN_9CF(),
	};
	vector<DWORD> nordics = {
		NATION_DENMARK_9CF(),
		NATION_FAROE_ISLANDS_9CF(),
		NATION_ICELAND_9CF(),
		NATION_SWEDEN_9CF(),
		NATION_NORWAY_9CF(),
		NATION_FINLAND_9CF(),
	};

	for (DWORD i = 0; i < *staff_count; i++) {
		cm3_staff* person = get_staff(i);
		// if staff already has a second nationality, can't add one
		if (person->StaffSecondNation) continue;
		// don't apply to free agents
		if (!person->StaffClubContracted) continue;
		cm3_nations* club_nation = person->StaffClubContracted->ClubNation;
		// ignore clubs with no nation or continent
		if (!club_nation) continue;
		if (!club_nation->NationContinent) continue;
		WORD join_day = person->StaffDateJoinedClub.day;
		WORD join_year = person->StaffDateJoinedClub.year;
		WORD year = *current_year;
		WORD day = *(WORD*)current_date;
		// get nation from club's stadium, if possible
		if (person->StaffClubContracted->ClubStadium) {
			if (person->StaffClubContracted->ClubStadium->StadiumCity) {
				if (person->StaffClubContracted->ClubStadium->StadiumCity->CityNation) {
					if (person->StaffClubContracted->ClubStadium->StadiumCity->CityNation->NationContinent) {
						club_nation = person->StaffClubContracted->ClubStadium->StadiumCity->CityNation;
					}
				}
			}
		}
		DWORD club_nation_id = club_nation->NationID;
		if (vector_contains_element(naturalize_never, club_nation_id)) continue;
		// don't try to naturalize players in the UK+Ireland, this is done somewhere else?
		if (vector_contains_element(uk_ireland, club_nation_id)) continue;
		WORD min_years = 5;
		if (vector_contains_element(naturalize_2_years, club_nation_id)) min_years = 2;
		else if (vector_contains_element(naturalize_3_years, club_nation_id)) min_years = 3;
		else if (vector_contains_element(naturalize_4_years, club_nation_id)) min_years = 4;
		else if (vector_contains_element(naturalize_6_years, club_nation_id)) min_years = 6;
		else if (vector_contains_element(naturalize_7_years, club_nation_id)) min_years = 7;
		else if (vector_contains_element(naturalize_8_years, club_nation_id)) min_years = 8;
		else if (vector_contains_element(naturalize_9_years, club_nation_id)) min_years = 9;
		else if (vector_contains_element(naturalize_10_years, club_nation_id)) min_years = 10;
		else if (vector_contains_element(naturalize_12_years, club_nation_id)) min_years = 12;
		else if (vector_contains_element(naturalize_14_years, club_nation_id)) min_years = 14;
		else if (vector_contains_element(naturalize_15_years, club_nation_id)) min_years = 15;
		else if (vector_contains_element(naturalize_20_years, club_nation_id)) min_years = 20;
		else if (vector_contains_element(naturalize_25_years, club_nation_id)) min_years = 25;
		else if (vector_contains_element(naturalize_40_years, club_nation_id)) min_years = 40;
		// special case for Spain: some countries can gain nationality after 2 years instead of 10
		if (club_nation_id == NATION_SPAIN_9CF() &&
			(vector_contains_element(special_spain, (DWORD)person->StaffNation->NationID) ||
				vector_contains_element(hispanic_american, (DWORD)person->StaffNation->NationID)))
			min_years = 2;
		// special case for Portugal: some countries can gain nationality after 7 years instead of 10
		if (club_nation_id == NATION_PORTUGAL_9CF() &&
			(vector_contains_element(special_portugal, (DWORD)person->StaffNation->NationID) ||
				vector_contains_element(european_union, (DWORD)person->StaffNation->NationID)))
			min_years = 7;
		// special case for Mexico: some countries can gain nationality after 2 years instead of 5
		if (club_nation_id == NATION_MEXICO_9CF() &&
			(vector_contains_element(special_mexico, (DWORD)person->StaffNation->NationID) ||
				vector_contains_element(hispanic_american, (DWORD)person->StaffNation->NationID)))
			min_years = 2;
		// special case for Costa Rica: some countries can gain nationality after 5 years instead of 7
		if (club_nation_id == NATION_COSTA_RICA_9CF() && (vector_contains_element(hispanic_american, (DWORD)person->StaffNation->NationID) ||
			person->StaffNation->NationID == NATION_SPAIN_9CF()))
			min_years = 5;
		// special case for Venezuela: some countries can gain nationality after 5 years instead of 10
		if (club_nation_id == NATION_VENEZUELA_9CF() && (vector_contains_element(hispanic_american, (DWORD)person->StaffNation->NationID) ||
			vector_contains_element(caribbean, (DWORD)person->StaffNation->NationID) ||
			person->StaffNation->NationID == NATION_SPAIN_9CF() || person->StaffNation->NationID == NATION_PORTUGAL_9CF() ||
			person->StaffNation->NationID == NATION_ITALY_9CF() || person->StaffNation->NationID == NATION_BRAZIL_9CF()))
			min_years = 5;
		// special case for Colombia: some countries can gain nationality after 1 or 2 years instead of 5
		if (club_nation_id == NATION_COLOMBIA_9CF()) {
			if (vector_contains_element(hispanic_american, (DWORD)person->StaffNation->NationID) ||
				vector_contains_element(caribbean, (DWORD)person->StaffNation->NationID))
				min_years = 1;
			if (person->StaffNation->NationID == NATION_SPAIN_9CF())
				min_years = 2;
		}
		// special case for Honduras: some countries can gain nationality after 1 or 2 years instead of 3
		if (club_nation_id == NATION_HONDURAS_9CF()) {
			if (vector_contains_element(hispanic_american, (DWORD)person->StaffNation->NationID) ||
				person->StaffNation->NationID == NATION_SPAIN_9CF())
				min_years = 2;
			if (vector_contains_element(central_america, (DWORD)person->StaffNation->NationID))
				min_years = 1;
		}
		// special case for El Salvador: some countries can gain nationality after 1 year instead of 5
		if (club_nation_id == NATION_EL_SALVADOR_9CF() && vector_contains_element(hispanic_american, (DWORD)person->StaffNation->NationID))
			min_years = 1;
		// special case for Nicaragua: some countries can gain nationality after 2 years instead of 4
		if (club_nation_id == NATION_NICARAGUA_9CF() && (vector_contains_element(central_america, (DWORD)person->StaffNation->NationID) ||
			person->StaffNation->NationID == NATION_SPAIN_9CF() || person->StaffNation->NationID == NATION_ARGENTINA_9CF() ||
			person->StaffNation->NationID == NATION_ITALY_9CF()))
			min_years = 2;
		// special case for Jamaica, Trinidad & Tobago, Guyana: some countries can gain nationality after 5 years instead of 7
		if ((club_nation_id == NATION_JAMAICA_9CF() || club_nation_id == NATION_TRINIDAD_TOBAGO_9CF() || club_nation_id == NATION_GUYANA_9CF()) &&
			(vector_contains_element(commonwealth, (DWORD)person->StaffNation->NationID) ||
				person->StaffNation->NationID == NATION_IRELAND_9CF()))
			min_years = 5;
		// special case for Malawi, Dominica, Grenada: some countries can gain nationality after 5 years instead of 7
		if ((club_nation_id == NATION_MALAWI_9CF() || club_nation_id == NATION_DOMINICA_9CF() || club_nation_id == NATION_GRENADA_9CF()) &&
			vector_contains_element(commonwealth, (DWORD)person->StaffNation->NationID))
			min_years = 5;
		// special case for Bahrain: some countries can gain nationality after 10 year instead of 20
		if (club_nation_id == NATION_BAHRAIN_9CF() && vector_contains_element(arab, (DWORD)person->StaffNation->NationID))
			min_years = 10;
		// special case for Jordan: some countries can gain nationality after 4 year instead of 15
		if (club_nation_id == NATION_JORDAN_9CF() && vector_contains_element(arab, (DWORD)person->StaffNation->NationID))
			min_years = 4;
		// special case for Austria: some countries can gain nationality after 6 years instead of 10
		if (club_nation_id == NATION_AUSTRIA_9CF() && (vector_contains_element(european_union, (DWORD)person->StaffNation->NationID) ||
			vector_contains_element(eea, (DWORD)person->StaffNation->NationID)))
			min_years = 6;
		// special case for Czech Republic: some countries can gain nationality after 3 years instead of 5
		if (club_nation_id == NATION_CZECH_REPUBLIC_9CF() && vector_contains_element(european_union, (DWORD)person->StaffNation->NationID))
			min_years = 3;
		// special case for Denmark, Finland, Sweden: some countries can gain nationality after 2 years instead of 9
		if ((club_nation_id == NATION_DENMARK_9CF() || club_nation_id == NATION_FINLAND_9CF() || club_nation_id == NATION_SWEDEN_9CF()) &&
			vector_contains_element(nordics, (DWORD)person->StaffNation->NationID))
			min_years = 2;
		// special case for Iceland: some countries can gain nationality after 4 years instead of 7
		if (club_nation_id == NATION_ICELAND_9CF() && vector_contains_element(nordics, (DWORD)person->StaffNation->NationID))
			min_years = 4;
		// special case for Norway: some countries can gain nationality after 2 or 3 years instead of 8
		if (club_nation_id == NATION_NORWAY_9CF()) {
			if (vector_contains_element(eea, (DWORD)person->StaffNation->NationID))
				min_years = 3;
			if (vector_contains_element(nordics, (DWORD)person->StaffNation->NationID))
				min_years = 2;
		}
		// special case for Italy: some countries can gain nationality after 4 years instead of 10
		if (club_nation_id == NATION_ITALY_9CF() && vector_contains_element(european_union, (DWORD)person->StaffNation->NationID))
			min_years = 4;
		// if staff has been at the club for long enough, add second nationality
		WORD diff = year - join_year;
		if (diff > min_years || (diff == min_years && join_day <= day))
		{
			//cm3_names* fname = person->StaffFirstName;
			//cm3_names* sname = person->StaffSecondName;
			//cm3_names* cname = person->StaffCommonName;
			//string s = "";
			//if (cname) s = string(cname->Name);
			//if (s.empty()) {
			//	if (sname) s = string(sname->Name);
			//	if (fname) s = s + ", " + string(fname->Name);
			//}
			// if staff's first nation is the same as the club's, can't add it again
			if (person->StaffNation == club_nation) continue;
			// special case: blank join date
			if (join_day == 0 && join_year == 1996) continue;
			//dprintf("Person %s is trying to gain %s nationality (%d years)\n", s.c_str(), club_nation->NationNameNationality, diff);
			person->StaffSecondNation = club_nation;
		}
	}
	//dprintf("--------------------\n");
}

extern "C" _declspec(naked) void player_gain_nationality_c()
{
	_asm
	{
		pushad
	}
	player_gain_nationality();
	_asm
	{
		popad
		push 0x8c5cd5
		ret
	}
}

void __declspec(naked) show_wing_back_position()
{
	__asm
	{
		mov eax, dword ptr ss : [esp + 0x11b8]
		movsx ecx, byte ptr ds : [eax + 0x16]
		cmp ecx, ebp
		jl end_func
		cmp bl, 0x1
		jnz bl_not_1
		lea edi, dword ptr ss : [esp + 0x14]
		or ecx, 0xffffffff
		xor eax, eax
		repne scas byte ptr es : [edi]
		not ecx
		dec ecx
		je ecx_zero_1
		mov edi, 0x9b7630
		or ecx, 0xffffffff
		repne scas byte ptr es : [edi]
		not ecx
		sub edi, ecx
		lea edx, dword ptr ss : [esp + 0x14]
		mov esi, edi
		mov edi, edx
		mov edx, ecx
		or ecx, 0xffffffff
		repne scas byte ptr es : [edi]
		mov ecx, edx
		dec edi
		shr ecx, 0x2
		rep movs dword ptr es : [edi] , dword ptr ds : [esi]
		mov ecx, edx
		and ecx, 0x3
		rep movs byte ptr es : [edi] , byte ptr ds : [esi]
		ecx_zero_1 :
		push 0xad9c64
		push 0x9b75b9
		push 0xde1f64
		push call_1_ret
		push 0x66f4e0
		ret
		call_1_ret :
		add esp, 0x0c
			jmp call_1_jmp
			bl_not_1 :
		cmp bl, 2
			je bl_equal_2
			cmp bl, 3
			je bl_equal_2
			lea edi, dword ptr ss : [esp + 0x14]
			or ecx, 0xffffffff
			xor eax, eax
			repne scas byte ptr es : [edi]
			not ecx
			dec ecx
			jnz end_func
			lea edx, dword ptr ss : [esp + 0x14]
			mov edi, 0x9b75bc
			jmp jump_2
			bl_equal_2 :
		lea edi, dword ptr ss : [esp + 0x14]
			or ecx, 0xffffffff
			xor eax, eax
			repne scas byte ptr es : [edi]
			not ecx
			dec ecx
			je ecx_zero_2
			mov edi, 0x9b7630
			or ecx, 0xffffffff
			repne scas byte ptr es : [edi]
			not ecx
			sub edi, ecx
			lea edx, dword ptr ss : [esp + 0x14]
			mov esi, edi
			mov edi, edx
			mov edx, ecx
			or ecx, 0xffffffff
			repne scas byte ptr es : [edi]
			mov ecx, edx
			dec edi
			shr ecx, 0x2
			rep movs dword ptr es : [edi] , dword ptr ds : [esi]
			mov ecx, edx
			and ecx, 0x3
			rep movs byte ptr es : [edi] , byte ptr ds : [esi]
			ecx_zero_2 :
			push 0xa85892
			push 0xde1f64
			push call_2_ret
			push 0x66f4e0
			ret
			call_2_ret :
		add esp, 0x8
			call_1_jmp :
			lea edx, dword ptr ss : [esp + 0x14]
			mov edi, 0xde1f64
			jump_2 :
			or ecx, 0xffffffff
			xor eax, eax
			repne scas byte ptr es : [edi]
			not ecx
			sub edi, ecx
			mov esi, edi
			mov edi, edx
			mov edx, ecx
			or ecx, 0xffffffff
			repne scas byte ptr es : [edi]
			mov ecx, edx
			dec edi
			shr ecx, 0x2
			rep movs dword ptr es : [edi] , dword ptr ds : [esi]
			mov ecx, edx
			and ecx, 0x3
			rep movs byte ptr es : [edi] , byte ptr ds : [esi]
			end_func :
			mov eax, dword ptr ss : [esp + 0x11b8]
			push 0x53f2d4
			ret
	}
}

void setup_misc_functions()
{
	if (configFile.GetBool("competitionColoursPatch", true)) PatchFunction(0x53b7c0, (DWORD)&comp_colours_in_header);
	PatchFunction(0x669f50, (DWORD)&show_extra_leagues_in_start);
	PatchFunction(0x4B01D0, (DWORD)&parent_child_stages);
	PatchFunction(0x46B71E, (DWORD)&aus_minor_premier_in_history);
	PatchFunction(0x460ec6, (DWORD)&club_pro_status_with_continental_comp_c);
	PatchFunction(0x460d75, (DWORD)&show_club_country_based);
	PatchFunction(0x8c5bd2, (DWORD)&player_gain_nationality_c);

	// Show the hidden wing-back position
	if (configFile.GetBool("showWingBacks", true)) {
		PatchFunction(0x53f2cd, (DWORD)&show_wing_back_position);
		WriteBytes(0x9b75b9, 2, 'W', 'B');
	}

	// Finance changes
	if (configFile.GetBool("financeTweaks", false)) {
		WriteWORD(0x59dc6d, 5000);
		WriteWORD(0x59dcd0, 5000);

		//WriteDWORD(0x59dc89, 1500);

		WriteDWORD(0x59dbf9, 3500);
		WriteDWORD(0x59dca5, 3500);

		WriteBytes(0x59dce0, 1, 3);
		WriteBytes(0x59dce7, 1, 6);
	}

	// Move August 30's international friendlies forward two weeks
	for (DWORD d : friendly_aug_30plus4) {
		WriteBytes(d + 4, 1, 3);
	}
	for (DWORD d : friendly_aug_30plus3) {
		WriteBytes(d + 3, 1, 3);
	}
	WriteBytes(0x5cb892 + 1, 1, 3);
	WriteBytes(0x5cb8dc + 1, 1, 3);
	// Move September 3's international friendlies forward one week
	for (DWORD d : friendly_sept_3plus4) {
		WriteBytes(d + 4, 1, 6);
	}
	for (DWORD d : friendly_sept_3plus3) {
		WriteBytes(d + 3, 1, 6);
	}
	WriteBytes(0x5caba1, 7, 0x66, 0xC7, 0x40, 0x01, 0x06, 0x08, 0x90);
	WriteBytes(0x5cad0e, 7, 0x66, 0xC7, 0x40, 0x01, 0x06, 0x08, 0x90);
	WriteBytes(0x5cb459, 7, 0x66, 0xC7, 0x40, 0x01, 0x06, 0x08, 0x90);
	// Move October 4's international friendlies forward one week
	for (DWORD d : friendly_oct_4plus4) {
		WriteBytes(d + 4, 1, 11);
	}
	for (DWORD d : friendly_oct_4plus3) {
		WriteBytes(d + 3, 1, 11);
	}
	// Move March 21's international friendlies forward one week
	for (DWORD d : friendly_march_21plus4) {
		WriteBytes(d + 4, 1, 28);
	}
	for (DWORD d : friendly_march_21plus3) {
		WriteBytes(d + 3, 1, 28);
	}
	WriteBytes(0x5cb872 + 1, 1, 28);
	WriteBytes(0x5cb8b7 + 1, 1, 28);

	// Change player search filters
	if (configFile.GetBool("changePlayerSearchFilters", true)) {
		WriteBytes(0x80775C + 2, 1, 18);
		WriteBytes(0xA7FFF6, 2, 0x31, 0x38);
		WriteBytes(0x807772 + 2, 1, 19);
		WriteBytes(0xA7FFEC, 2, 0x31, 0x39);
		WriteBytes(0x80777B + 2, 1, 25);
		WriteBytes(0xA7FFEF, 2, 0x32, 0x35);
		WriteBytes(0x807791 + 2, 1, 26);
		WriteBytes(0xA7FFE4, 2, 0x32, 0x36);
		WriteBytes(0x80779A + 2, 1, 30);
		WriteBytes(0xA7FFE7, 2, 0x33, 0x30);
		WriteBytes(0x8077B0 + 2, 1, 31);
		WriteBytes(0xA7FFDC, 2, 0x33, 0x31);
		WriteBytes(0x8077B9 + 2, 1, 35);
		WriteBytes(0xA7FFDF, 2, 0x33, 0x35);
		WriteBytes(0x8077CF + 2, 1, 36);
		WriteBytes(0xA7FFD8, 2, 0x33, 0x36);
	}

	// Show hosts for some other comps
	WriteDWORD(0x96769C, 0x404480); // Asian Cup
	WriteDWORD(0x96B488, 0x404480); // Copa América
	WriteDWORD(0x9672F8, 0x404480); // AFCON

	// Fixes a slight bug where B-teams can't qualify for relegation playoffs if they have the "CantBePromoted" flag set
	WriteBytes(0x68527E, 1, 0xFC);

	// Fix for all clubs appearing in the Select Team screen, when only one league is set as foreground
	WriteNOP(0x822696, 2);

	// Shows more teams in Team Stats, up to 127
	WriteBytes(0x495976, 1, 0x7F);

	// Change manager's starting age
	WriteDWORD(0x820e01, (START_YEAR - 34));
	WriteBytes(0x820e09, 1, July);
	WriteBytes(0x820e0e, 1, 1);

	// Adjust randomized birth dates
	DWORD year_diff = START_YEAR - 2001;
	WriteDWORD(0x527853, 1940 + year_diff);
	WriteDWORD(0x527552, 1940 + year_diff);
	WriteDWORD(0x527B4E, 1940 + year_diff);
	WriteDWORD(0x527DF9, 1940 + year_diff);
	WriteDWORD(0x536878, 1967 + year_diff);
	WriteDWORD(0x53687F, 1980 + year_diff);
	WriteDWORD(0x537CA0, 1940 + year_diff);

	// WC qualifiers calendar changes
	WriteBytes(0x915395, 1, 1);
	WriteBytes(0x915397, 1, 5);
	WriteBytes(0x91539c, 1, 9);
	WriteBytes(0x9153bd, 1, 1);
	WriteBytes(0x9153bf, 1, 5);
	WriteBytes(0x9153c4, 1, 23);
	WriteBytes(0x9153e7, 1, 1);
	WriteBytes(0x9153e9, 1, 5);
	WriteBytes(0x9153ee, 1, 12);

	WriteBytes(0x9207c9, 1, 8);
	WriteBytes(0x9207cb, 1, 6);
	WriteBytes(0x9207f5, 1, 1);
	WriteBytes(0x9207f7, 1, 5);
	WriteBytes(0x920801, 1, 10);
	WriteBytes(0x920950, 1, 1);
	WriteBytes(0x920956, 1, 5);
	WriteBytes(0x92095c, 1, 12);

	// Fix too many countries to select in player/scout filter, causing a (harmless) error
	WriteBytes(0x80959d, 1, 9);
	WriteNOP(0x8095a8, 2);
	WriteBytes(0x8149a1, 1, 9);
	// Hopefully temporary: hide Area.cpp 507/838 error for other cases
	WriteNOP(0x40344c, 5);
	WriteNOP(0x403c32, 5);

	// temporary: suppresses hall_of_fame 315 error
	WriteNOP(0x5ef93b, 5);

	// Enable Bosman signings from all countries
	WriteBytes(0x544677, 1, 0xeb);
}
