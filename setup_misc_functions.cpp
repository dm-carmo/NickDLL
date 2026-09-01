#include <windows.h>
#include <Structures/CMHeader.h>
#include <Helpers/9cf_constants.h>
#include <Helpers/generic_functions.h>
#include "Helpers/Helper.h"
#include <Helpers/constants.h>

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

vector<DWORD> replace_titlebar_bg = {
	0x81BB1A + 3, 0x81CA55 + 3, 0x81D0D3 + 3, 0x81C99C + 2, 0x81CAE6 + 3, 0x81EE2C + 3, 0x81F1EC + 3, 0x81F94F + 3, 0x825D9B + 3, 0x820FB7 + 3, 0x821AD0 + 2, 0x8222B2 + 3, 0x822AF1 + 3, 0x81FF46 + 3, 0x8F4656 + 3, 0x8766E6 + 3, 0x81E932 + 3, 0x8217E9 + 3, 0x821706 + 2, 0x761866 + 2, 0x762720 + 2, 0x7627EA + 3, 0x762946 + 2, 0x762B20 + 3, 0x81C864 + 3, 0x81CBC7 + 3, 0x821834 + 3, 0x821880 + 2, 0x823328 + 2, 0x8389ED + 3, 0x838A24 + 3,
};
vector<DWORD> replace_titlebar_fg = {
	0x81BB13 + 3, 0x81CA61 + 3, 0x81D0CC + 3, 0x81C9BC + 3, 0x81CAED + 3, 0x81EE25 + 3, 0x81F1E6 + 2, 0x81F949 + 2, 0x825D95 + 2, 0x820FB0 + 3, 0x821AC9 + 3, 0x8222AC + 2, 0x822AEA + 3, 0x81FF40 + 2, 0x8F465D + 2, 0x8766DF + 3, 0x81E92B + 3, 0x8217F0 + 2, 0x82170C + 3, 0x76186C + 3, 0x762726 + 3, 0x7627F1 + 3, 0x76294C + 3, 0x762B27 + 3, 0x81C86B + 3, 0x81CBCE + 2, 0x82183B + 2, 0x821886 + 3, 0x82332E + 3, 0x8389F4 + 3, 0x838A2B + 3,
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
	//if (child_stage_id == EasternConference || child_stage_id == WesternConference || child_stage_id == EastLeagueStage) return GroupStage;
	//if (child_stage_id == BestPlacedTeams) return GroupStage;
	if (child_stage_id >= 0x475 && child_stage_id <= 0x478) return LeagueA;
	if (child_stage_id >= 0x459 && child_stage_id <= 0x45C) return LeagueB;
	if (child_stage_id >= 0x40F && child_stage_id <= 0x412) return LeagueC;
	if (child_stage_id >= 0x473 && child_stage_id <= 0x474) return LeagueD;
	if (child_stage_id >= 0x3fd && child_stage_id <= 0x406) return FirstRound;
	if ((child_stage_id >= 0x407 && child_stage_id <= 0x40B) || child_stage_id == SecondRoundGroupF ||
		(child_stage_id >= 0x42f && child_stage_id <= 0x431)) return SecondRound;
	if (child_stage_id >= 0x47e && child_stage_id <= 0x47f) return FourthRound;
	if ((child_stage_id >= 0x40c && child_stage_id <= 0x40e) || child_stage_id == 0xBE || child_stage_id == 0x118 || child_stage_id == 0x122) return ThirdRound;
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
	DWORD pro_status = 0;
	if (club->ClubProfessionalStatus == Professional) {
		pro_status = 0x9904b0;
	}
	else if (club->ClubProfessionalStatus == SemiProfessional) {
		pro_status = 0x99049c;
	}
	else if (club->ClubProfessionalStatus == Amateur) {
		pro_status = 0x990494;
	}
	else {
		pro_status = 0xa16546;
	}
	sub_66F4E0(0xDE1F64, pro_status);
	string pro_status_c((char*)0xDE1F64);
	char ret_str[128];
	sprintf(ret_str, "%s%s", pro_status_c.c_str(), continental_comp);
	sub_66F4E0(0xDE1F64, (DWORD)&ret_str[0]);
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

bool is_continental_qualifiers(cm3_club_comps* comp) {
	if (!comp) return false;
	DWORD id = comp->ClubCompID;
	if (id == WORLD_CUP_AFC_QUALIFYING_9CF()) return true;
	if (id == WORLD_CUP_OFC_QUALIFYING_9CF()) return true;
	if (id == WORLD_CUP_CAF_QUALIFYING_9CF()) return true;
	if (id == WORLD_CUP_CONCACAF_QUALIFYING_9CF()) return true;
	if (id == WORLD_CUP_CONMEBOL_QUALIFYING_9CF()) return true;
	if (id == WORLD_CUP_UEFA_QUALIFYING_9CF()) return true;
	if (id == WORLD_CUP_PLAYOFFS_9CF()) return true;
	if (id == UEFA_EURO_QUALIFYING_9CF()) return true;
	if (id == ASIAN_CUP_QUALIFYING_9CF()) return true;
	if (id == AFRICAN_CUP_OF_NATIONS_QUALIFYING_9CF()) return true;
	return false;
}

bool is_continental_finals(cm3_club_comps* comp) {
	if (!comp) return false;
	DWORD id = comp->ClubCompID;
	if (id == OFC_NATIONS_CUP_9CF()) return true;
	if (id == GOLD_CUP_9CF()) return true;
	if (id == COPA_AMERICA_9CF()) return true;
	if (id == ASIAN_CUP_9CF()) return true;
	if (id == AFRICAN_CUP_OF_NATIONS_9CF()) return true;
	if (id == UEFA_EURO_9CF()) return true;
	return false;
}

bool is_youth_competition(cm3_club_comps* comp) {
	if (!comp) return false;
	DWORD id = comp->ClubCompID;
	if (id == OLYMPIC_GAMES_9CF()) return true;
	if (id == UNDER_21_INTERNATIONAL_9CF()) return true;
	return false;
}

bool is_final_knockout_rounds(WORD main_stage_id, WORD sub_stage_id) {
	return (sub_stage_id == QuarterFinal || sub_stage_id == SemiFinal || sub_stage_id == Final || sub_stage_id == ThirdPlacePlayoff || main_stage_id == ThirdPlacePlayoff);
}

//static __int16(__thiscall* update_ranking)(BYTE* _this, cm3_nations* nation, __int16 a3, BYTE* match_data) =
//(__int16(__thiscall*)(BYTE * _this, cm3_nations * nation, __int16 a3, BYTE * match_data))(0x58DEA0);
void update_fifa_coefficients(BYTE* _this, BYTE* match_data) {
	cm3_club_comps* comp = (cm3_club_comps*)*(DWORD*)(match_data + 0x14);
	if (!comp) return;
	if (is_youth_competition(comp)) return;
	cm3_stadiums* stadium = (cm3_stadiums*)*(DWORD*)(match_data + 0x18);
	cm3_clubs* home_team = (cm3_clubs*)*(DWORD*)(match_data + 0x1C);
	if (!home_team->ClubNation) return;
	if (is_nation_non_fifa(home_team->ClubNation)) return;
	cm3_clubs* away_team = (cm3_clubs*)*(DWORD*)(match_data + 0x20);
	if (!away_team->ClubNation) return;
	if (is_nation_non_fifa(away_team->ClubNation)) return;
	WORD main_stage_id = *(WORD*)(match_data + 0x32);
	WORD sub_stage_id = *(WORD*)(match_data + 0x30);
	char goals_home = *(char*)(match_data + 0x47);
	char goals_away;
	if (goals_home == -1) {
		goals_home = *(char*)(match_data + 0x43);
		goals_away = *(char*)(match_data + 0x44);
	}
	else goals_away = *(char*)(match_data + 0x48);

	int importance = 10;
	// if Nations League && group stage, importance = 15
	// if Nations League && playoffs, importance = 25
	if (comp->ClubCompID == UEFA_NATIONS_LEAGUE_9CF() || comp->ClubCompID == CONCACAF_NATIONS_LEAGUE_9CF()) {
		if (is_final_knockout_rounds(main_stage_id, sub_stage_id)) importance = 25;
		else importance = 15;
	}
	// if World Cup qualifiers or confederation qualifiers, importance = 25
	if (is_continental_qualifiers(comp)) importance = 25;
	// if confederation finals (before quarter-finals), importance = 35
	// if confederation finals (quarter-finals and later), importance = 40
	if (is_continental_finals(comp)) {
		if (is_final_knockout_rounds(main_stage_id, sub_stage_id)) importance = 40;
		else importance = 30;
	}
	// if World Cup (before quarter-finals), importance = 50
	// if World Cup (quarter-finals and later), importance = 60
	if (comp->ClubCompID == FIFA_WORLD_CUP_9CF()) {
		if (is_final_knockout_rounds(main_stage_id, sub_stage_id)) importance = 60;
		else importance = 50;
	}
	float result_home = 0;
	float result_away = 0;
	// if draw or penalty loss, result = 0.5
	if (goals_home == goals_away) {
		result_home = 0.5;
		result_away = 0.5;
	}
	// if penalty win, result = 0.75
	// if win, result = 1
	else {
		result_home = (goals_home > goals_away);
		result_away = (goals_away > goals_home);
	}
	float rating_home = getFIFARankingPoints(home_team->ClubNation);
	float rating_away = getFIFARankingPoints(away_team->ClubNation);
	float diff = rating_home - rating_away;
	// 1 divided by (10 ^ -(rating_diff / 600) + 1)
	float expected_home = (float)(1 / (pow(10, -diff / 600) + 1));
	float expected_away = (float)(1 / (pow(10, diff / 600) + 1));

	// full formula: P = Pbefore + I * (W - We)
	// check if World Cup or main continental comp, and if knockout rounds, don't lower rating
	float new_rating_home = rating_home + importance * (result_home - expected_home);
	if (new_rating_home < 0) new_rating_home = 0;
	float new_rating_away = rating_away + importance * (result_away - expected_away);
	if (new_rating_away < 0) new_rating_away = 0;
	if (is_continental_finals(comp) && is_final_knockout_rounds(main_stage_id, sub_stage_id))
	{
		if (new_rating_home < rating_home) new_rating_home = rating_home;
		if (new_rating_away < rating_away) new_rating_away = rating_away;
	}

	setFIFARankingPoints(home_team->ClubNation, new_rating_home);
	setFIFARankingPoints(away_team->ClubNation, new_rating_away);
}

void __declspec(naked) update_fifa_coefficients_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call update_fifa_coefficients
		add esp, 0x8
		ret 4
	}
}

char* lga_groups_drawn = "{}<%s - competition name(e.g.Champions League)>{} League A groups drawn";
char* lgb_groups_drawn = "{}<%s - competition name(e.g.Champions League)>{} League B groups drawn";
char* lgc_groups_drawn = "{}<%s - competition name(e.g.Champions League)>{} League C groups drawn";
char* lgd_groups_drawn = "{}<%s - competition name(e.g.Champions League)>{} League D groups drawn";
char* st1_groups_drawn = "{}<%s - competition name(e.g.Champions League)>{} 1st stage groups drawn";
char* st2_groups_drawn = "{}<%s - competition name(e.g.Champions League)>{} 2nd stage groups drawn";
void __declspec(naked) fixed_groups_drawn_news_title()
{
	__asm
	{
		cmp eax, LeagueA
		jnz league_b_case
		lea eax, dword ptr ds : [edi + edi * 2]
		lea edx, dword ptr ds : [eax + eax * 8]
		mov eax, dword ptr ds : [0xae23d0]
		shl edx, 2
		sub edx, edi
		add eax, edx
		movsx ecx, byte ptr ds : [eax + 0x52]
		add eax, 0x38
		push eax
		push ecx
		push ecx
		push lga_groups_drawn
		push 0x77fd5a
		ret
		league_b_case :
		cmp eax, LeagueB
			jnz league_c_case
			lea eax, dword ptr ds : [edi + edi * 2]
			lea edx, dword ptr ds : [eax + eax * 8]
			mov eax, dword ptr ds : [0xae23d0]
			shl edx, 2
			sub edx, edi
			add eax, edx
			movsx ecx, byte ptr ds : [eax + 0x52]
			add eax, 0x38
			push eax
			push ecx
			push ecx
			push lgb_groups_drawn
			push 0x77fd5a
			ret
			league_c_case :
		cmp eax, LeagueC
			jnz league_d_case
			lea eax, dword ptr ds : [edi + edi * 2]
			lea edx, dword ptr ds : [eax + eax * 8]
			mov eax, dword ptr ds : [0xae23d0]
			shl edx, 2
			sub edx, edi
			add eax, edx
			movsx ecx, byte ptr ds : [eax + 0x52]
			add eax, 0x38
			push eax
			push ecx
			push ecx
			push lgc_groups_drawn
			push 0x77fd5a
			ret
			league_d_case :
		cmp eax, LeagueD
			jnz stage_1_case
			lea eax, dword ptr ds : [edi + edi * 2]
			lea edx, dword ptr ds : [eax + eax * 8]
			mov eax, dword ptr ds : [0xae23d0]
			shl edx, 2
			sub edx, edi
			add eax, edx
			movsx ecx, byte ptr ds : [eax + 0x52]
			add eax, 0x38
			push eax
			push ecx
			push ecx
			push lgd_groups_drawn
			push 0x77fd5a
			ret
			stage_1_case :
		cmp eax, FirstStage
			jnz stage_2_case
			lea eax, dword ptr ds : [edi + edi * 2]
			lea edx, dword ptr ds : [eax + eax * 8]
			mov eax, dword ptr ds : [0xae23d0]
			shl edx, 2
			sub edx, edi
			add eax, edx
			movsx ecx, byte ptr ds : [eax + 0x52]
			add eax, 0x38
			push eax
			push ecx
			push ecx
			push st1_groups_drawn
			push 0x77fd5a
			ret
			stage_2_case :
		cmp eax, SecondStage
			jnz generic_group_case
			lea eax, dword ptr ds : [edi + edi * 2]
			lea edx, dword ptr ds : [eax + eax * 8]
			mov eax, dword ptr ds : [0xae23d0]
			shl edx, 2
			sub edx, edi
			add eax, edx
			movsx ecx, byte ptr ds : [eax + 0x52]
			add eax, 0x38
			push eax
			push ecx
			push ecx
			push st2_groups_drawn
			push 0x77fd5a
			ret
			generic_group_case :
		push 0x77fc5a
			ret
	}
}

cm3_names* choose_a_brazil_name(cm3_staff* person) {
	char* first_ch = person->StaffFirstName->Name;
	wstring first(&first_ch[0], &first_ch[strlen(first_ch)]);
	char* second_ch = person->StaffSecondName->Name;
	wstring second(&second_ch[0], &second_ch[strlen(second_ch)]);
	vector<wstring> first_split = split_string_spaces(first);
	vector<wstring> second_split = split_string_spaces(second);
	first_split.erase(remove_if(first_split.begin(), first_split.end(),
		[](wstring s) {
			if (s.size() == 0) return true;
			wstring copy(s);
			transform(copy.begin(), copy.end(), copy.begin(), towlower);
			return s == copy;
		}), first_split.end());
	second_split.erase(remove_if(second_split.begin(), second_split.end(),
		[](wstring s) {
			if (s.size() == 0) return true;
			wstring copy(s);
			transform(copy.begin(), copy.end(), copy.begin(), towlower);
			return s == copy;
		}), second_split.end());
	first_split.insert(first_split.end(), make_move_iterator(second_split.begin()), make_move_iterator(second_split.end()));
	if (first_split.size() > 2) {
		//dprintf("Trying to get common name for person: %s, %s\n", second_ch, first_ch);
		vector<cm3_names*> eligible_names = get_common_names_by_nation(NATION_BRAZIL_9CF());
		eligible_names.erase(remove_if(eligible_names.begin(), eligible_names.end(),
			[first_split](cm3_names* n) {
				char* name = n->Name;
				wstring name_str(&name[0], &name[strlen(name)]);
				for (wstring s : first_split) {
					if (name_str.find(s) != wstring::npos) return false;
				}
				return true;
			}), eligible_names.end());
		if (eligible_names.size() > 0)
		{
			shuffle(eligible_names.begin(), eligible_names.end(), rng);
			//dprintf("- Found: %s\n", eligible_names[0]->Name);
			return eligible_names[0];
		}
	}
	return get_common_name(0);
}

void __declspec(naked) brazil_regens_common_names_1()
{
	__asm
	{
		mov edx, dword ptr ds : [edx]
		cmp edx, dword ptr ds : [0x9cf260]
		jnz normal_regen_behaviour_1
		push esi
		call choose_a_brazil_name
		push 0x7ab3e6
		ret
		normal_regen_behaviour_1 :
		mov edx, dword ptr ds : [esi + 0x1a]
			push edx
			push 0x7ab3e6
			push 0x53a5b0
			ret
	}
}

void __declspec(naked) brazil_regens_common_names_2()
{
	__asm
	{
		mov eax, dword ptr ds : [eax]
		cmp eax, dword ptr ds : [0x9cf260]
		jnz normal_regen_behaviour_2
		push edx
		call choose_a_brazil_name
		push 0x59ebbf
		ret
		normal_regen_behaviour_2 :
		mov eax, dword ptr ds : [edx + 0x1a]
			push eax
			push 0x59ebbf
			push 0x53a5b0
			ret
	}
}

void __declspec(naked) brazil_regens_common_names_3()
{
	__asm
	{
		mov edx, dword ptr ds : [edx]
		cmp edx, dword ptr ds : [0x9cf260]
		jnz normal_regen_behaviour_3
		push esi
		call choose_a_brazil_name
		push 0x7abd96
		ret
		normal_regen_behaviour_3 :
		mov edx, dword ptr ds : [esi + 0x1a]
			push edx
			push 0x7abd96
			push 0x53a5b0
			ret
	}
}

// make positions unclickable on results page to avoid a crash
void __declspec(naked) quick_uefa_fix_1() {
	__asm {
		mov eax, dword ptr ds : [esi + 0x14]
		mov ecx, dword ptr ds : [eax]
		cmp ecx, dword ptr ds : [0x9CF6E8]
		je special_uefa_tables_1
		cmp ecx, dword ptr ds : [0x9CF6F0]
		je special_uefa_tables_1
		cmp ecx, dword ptr ds : [0x9CF6EC]
		je special_uefa_tables_1
		cmp ecx, dword ptr ds : [0x9CF7B4]
		je special_uefa_tables_1
		push 0x49dbe0
		ret
		special_uefa_tables_1 :
		push 0x49DC9B
			ret
	}
}

void __declspec(naked) quick_uefa_fix_2() {
	__asm {
		mov eax, dword ptr ds : [eax + 0x14]
		mov ecx, dword ptr ds : [eax]
		cmp ecx, dword ptr ds : [0x9CF6E8]
		je special_uefa_tables_2
		cmp ecx, dword ptr ds : [0x9CF6F0]
		je special_uefa_tables_2
		cmp ecx, dword ptr ds : [0x9CF6EC]
		je special_uefa_tables_2
		cmp ecx, dword ptr ds : [0x9CF7B4]
		je special_uefa_tables_2
		push 0x49e65a
		ret
		special_uefa_tables_2 :
		push 0x49E75D
			ret
	}
}

char* playoff_winner = "Playoff Winner";
void __declspec(naked) playoff_winner_in_history() {
	__asm {
		push edi
		mov edi, dword ptr ds : [edi + 4]
		mov edi, dword ptr ds : [edi]
		cmp edi, dword ptr ds : [0x9cf794]
		pop edi
		jl show_playoff_str
		push 0x990fc0
		jmp ret_playoff
		show_playoff_str :
		push playoff_winner
			ret_playoff :
		push 0x49953a
			ret
	}
}
//004997FB     66:8B15 8431AE>MOV DX,WORD PTR DS:[AE3184] => this makes the text colour white

static int(__thiscall* sub_54BA20) (BYTE* _this, char* a2, __int16 a3, char a4) =
(int(__thiscall*)(BYTE * _this, char* a2, __int16 a3, char a4))(0x54BA20);
void print_country_date_info_start(playable_nation_data* pnd, char* ret_str) {
	BYTE* start_date = pnd->start_date;
	BYTE* cm_date = new BYTE[8];
	sub_549EF0(cm_date, *(WORD*)(start_date)-28, *(WORD*)(start_date + 2));
	char* date_str = new char[96];
	sub_54BA20(cm_date, date_str, 0x7d0, -1);
	char pos = 0;
	while (date_str[pos++] != ' ');
	sprintf(ret_str, "%s\n%s", pnd->nation->NationNameShort, &date_str[pos]);
}

void __declspec(naked) print_country_date_info_start_c()
{
	__asm
	{
		pushad
		push edi
		push eax
		call print_country_date_info_start
		add esp, 0x8
		popad
		push 0x81EA1A
		ret
	}
}

void __declspec(naked) show_playoff_in_menu()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf778]
		je is_wc_comp
		cmp eax, dword ptr ds : [0x9cf928]
		je is_wc_comp
		push 0x669511
		ret
		is_wc_comp :
		push 0x669564
			ret
	}
}

void __declspec(naked) year_offset_in_landmarks()
{
	__asm
	{
		cmp ebx, dword ptr ds : [0x9cf76c]
		je ret_add_2_year
		cmp ebx, dword ptr ds : [0x9cf770]
		je ret_add_3_year
		cmp ebx, dword ptr ds : [0x9cf774]
		je ret_add_3_year
		cmp ebx, dword ptr ds : [0x9cf778]
		je ret_add_3_year
		cmp ebx, dword ptr ds : [0x9cf77c]
		je ret_add_3_year
		cmp ebx, dword ptr ds : [0x9cf780]
		je ret_add_1_year
		cmp ebx, dword ptr ds : [0x9cf784]
		je ret_add_1_year
		cmp ebx, dword ptr ds : [0x9cf928]
		je ret_add_1_year
		cmp ebx, dword ptr ds : [0x9cf890]
		je ret_add_2_year
		cmp ebx, dword ptr ds : [0x9cf788]
		je ret_add_3_year
		cmp ebx, dword ptr ds : [0x9cf964]
		je ret_add_2_year
		push 0x46b441
		ret
		ret_add_1_year :
		mov ax, word ptr ds : [esi + 4]
			add ax, 1
			push 0x46b44f
			ret
			ret_add_2_year :
		mov ax, word ptr ds : [esi + 4]
			add ax, 2
			push 0x46b44f
			ret
			ret_add_3_year :
		mov ax, word ptr ds : [esi + 4]
			add ax, 3
			push 0x46b44f
			ret
	}
}

void __declspec(naked) unknown_check_2()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf778]
		je unknown_2
		cmp eax, dword ptr ds : [0x9cf928]
		je unknown_2
		push 0x669ac6
		ret
		unknown_2 :
		push 0x669acf
			ret
	}
}

void __declspec(naked) unknown_check_3()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf790]
		je unknown_3
		cmp eax, dword ptr ds : [0x9cf78c]
		je unknown_3
		cmp eax, dword ptr ds : [0x9cf788]
		je unknown_3
		cmp eax, dword ptr ds : [0x9cf890]
		je unknown_3
		cmp eax, dword ptr ds : [0x9cf888]
		je unknown_3
		cmp eax, dword ptr ds : [0x9cf88c]
		je unknown_3
		cmp eax, dword ptr ds : [0x9cf95c]
		je unknown_3
		cmp eax, dword ptr ds : [0x9cf964]
		je unknown_3
		push 0x669bae
		ret
		unknown_3 :
		push 0x669bb7
			ret
	}
}

void __declspec(naked) international_comps_to_continent()
{
	__asm
	{
		cmp edx, dword ptr ds : [0x9cf77c]
		je to_africa
		cmp edx, dword ptr ds : [0x9cf7ac]
		je to_africa
		cmp edx, dword ptr ds : [0x9cf890]
		je to_africa
		cmp edx, dword ptr ds : [0x9cf774]
		je to_asia
		cmp edx, dword ptr ds : [0x9cf790]
		je to_asia
		cmp edx, dword ptr ds : [0x9cf788]
		je to_asia
		cmp edx, dword ptr ds : [0x9cf770]
		je to_n_america
		cmp edx, dword ptr ds : [0x9cf78c]
		je to_n_america
		cmp edx, dword ptr ds : [0x9cf88c]
		je to_n_america
		cmp edx, dword ptr ds : [0x9cf95c]
		je to_n_america
		cmp edx, dword ptr ds : [0x9cf780]
		je to_europe
		cmp edx, dword ptr ds : [0x9cf7a4]
		je to_europe
		cmp edx, dword ptr ds : [0x9cf784]
		je to_europe
		cmp edx, dword ptr ds : [0x9cf888]
		je to_europe
		cmp edx, dword ptr ds : [0x9cf76c]
		je to_oceania
		cmp edx, dword ptr ds : [0x9cf8a0]
		je to_oceania
		cmp edx, dword ptr ds : [0x9cf778]
		je to_s_america
		cmp edx, dword ptr ds : [0x9cf7a8]
		je to_s_america
		cmp edx, dword ptr ds : [0x9cf964]
		je to_n_america
		cmp edx, dword ptr ds : [0x9cf7a0]
		je to_world
		push 0x6b63f6
		ret
		to_africa :
		mov ecx, dword ptr ds : [0x9cfa08]
			jmp continent_end
			to_asia :
		mov ecx, dword ptr ds : [0x9cfa0c]
			jmp continent_end
			to_europe :
		mov ecx, dword ptr ds : [0x9cfa10]
			jmp continent_end
			to_oceania :
		mov ecx, dword ptr ds : [0x9cfa18]
			jmp continent_end
			to_n_america :
		mov ecx, dword ptr ds : [0x9cfa14]
			jmp continent_end
			to_s_america :
		mov ecx, dword ptr ds : [0x9cfa1c]
			jmp continent_end
			to_world :
		push 0x6b6400
			ret
			continent_end :
		push 0x6b63d7
			ret
	}
}

// 0076D940
void __declspec(naked) is_international_comp_no_qualifiers() {
	__asm {
		mov eax, dword ptr ss : [esp + 4]
		test eax, eax
		je ret_0_no_quals
		mov eax, dword ptr ds : [eax]
		cmp eax, dword ptr ds : [0x9cf79c]
		je ret_1_quals
		cmp eax, dword ptr ds : [0x9cf7a0]
		je ret_1_quals
		cmp eax, dword ptr ds : [0x9cf7a4]
		je ret_1_quals
		cmp eax, dword ptr ds : [0x9cf7a8]
		je ret_1_quals
		cmp eax, dword ptr ds : [0x9cf7ac]
		je ret_1_quals
		cmp eax, dword ptr ds : [0x9cf790]
		je ret_1_quals
		cmp eax, dword ptr ds : [0x9cf8a0]
		je ret_1_quals
		cmp eax, dword ptr ds : [0x9cf78c]
		je ret_1_quals
		cmp eax, dword ptr ds : [0x9cf888]
		je ret_1_quals
		cmp eax, dword ptr ds : [0x9cf88c]
		je ret_1_quals
		ret_0_no_quals :
		xor eax, eax
			ret 4
			ret_1_quals :
			mov eax, 1
			ret 4
	}
}

// 0076B455
void __declspec(naked) unknown_int_comps_fix_1()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf79c]
		je jmp_true_fix_1
		cmp eax, dword ptr ds : [0x9cf7a0]
		je jmp_true_fix_1
		cmp eax, dword ptr ds : [0x9cf7a4]
		je jmp_true_fix_1
		cmp eax, dword ptr ds : [0x9cf7a8]
		je jmp_true_fix_1
		cmp eax, dword ptr ds : [0x9cf7ac]
		je jmp_true_fix_1
		cmp eax, dword ptr ds : [0x9cf790]
		je jmp_true_fix_1
		cmp eax, dword ptr ds : [0x9cf8a0]
		je jmp_true_fix_1
		cmp eax, dword ptr ds : [0x9cf78c]
		je jmp_true_fix_1
		cmp eax, dword ptr ds : [0x9cf888]
		je jmp_true_fix_1
		cmp eax, dword ptr ds : [0x9cf88c]
		je jmp_true_fix_1
		push 0x76B4C3
		ret
		jmp_true_fix_1 :
		push 0x76B548
			ret
	}
}

// 0076C28F
// do players stay with the international team until the end of the competition (Euros etc) or go back after each match window?
void __declspec(naked) keep_players_in_comp_until_end()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf79c]
		je jmp_true_fix_2
		cmp eax, dword ptr ds : [0x9cf7a0]
		je jmp_true_fix_2
		cmp eax, dword ptr ds : [0x9cf7a4]
		je jmp_true_fix_2
		cmp eax, dword ptr ds : [0x9cf7a8]
		je jmp_true_fix_2
		cmp eax, dword ptr ds : [0x9cf7ac]
		je jmp_true_fix_2
		cmp eax, dword ptr ds : [0x9cf790]
		je jmp_true_fix_2
		cmp eax, dword ptr ds : [0x9cf8a0]
		je jmp_true_fix_2
		cmp eax, dword ptr ds : [0x9cf78c]
		je jmp_true_fix_2
		push 0x76C2DD
		ret
		jmp_true_fix_2 :
		push 0x76C2D9
			ret
	}
}

// 00775293
void __declspec(naked) unknown_int_comps_fix_3()
{
	__asm
	{
		cmp edx, dword ptr ds : [0x9cf79c]
		je jmp_true_fix_3
		cmp edx, dword ptr ds : [0x9cf7a0]
		je jmp_true_fix_3
		cmp edx, dword ptr ds : [0x9cf7a4]
		je jmp_true_fix_3
		cmp edx, dword ptr ds : [0x9cf7a8]
		je jmp_true_fix_3
		cmp edx, dword ptr ds : [0x9cf7ac]
		je jmp_true_fix_3
		cmp edx, dword ptr ds : [0x9cf790]
		je jmp_true_fix_3
		cmp edx, dword ptr ds : [0x9cf8a0]
		je jmp_true_fix_3
		cmp edx, dword ptr ds : [0x9cf78c]
		je jmp_true_fix_3
		cmp edx, dword ptr ds : [0x9cf888]
		je jmp_true_fix_3
		cmp edx, dword ptr ds : [0x9cf88c]
		je jmp_true_fix_3
		push 0x7752EF
		ret
		jmp_true_fix_3 :
		push 0x7752D3
			ret
	}
}

// 007752FC
void __declspec(naked) unknown_int_comps_fix_4()
{
	__asm
	{
		cmp edx, dword ptr ds : [0x9cf79c]
		je jmp_true_fix_4
		cmp edx, dword ptr ds : [0x9cf7a0]
		je jmp_true_fix_4
		cmp edx, dword ptr ds : [0x9cf7a4]
		je jmp_true_fix_4
		cmp edx, dword ptr ds : [0x9cf7a8]
		je jmp_true_fix_4
		cmp edx, dword ptr ds : [0x9cf7ac]
		je jmp_true_fix_4
		cmp edx, dword ptr ds : [0x9cf790]
		je jmp_true_fix_4
		cmp edx, dword ptr ds : [0x9cf8a0]
		je jmp_true_fix_4
		cmp edx, dword ptr ds : [0x9cf78c]
		je jmp_true_fix_4
		cmp edx, dword ptr ds : [0x9cf888]
		je jmp_true_fix_4
		cmp edx, dword ptr ds : [0x9cf88c]
		je jmp_true_fix_4
		push 0x775395
		ret
		jmp_true_fix_4 :
		push 0x77533C
			ret
	}
}

// 0076B31C
void __declspec(naked) unknown_int_comps_fix_5()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf79c]
		je jmp_true_fix_5
		cmp eax, dword ptr ds : [0x9cf7a0]
		je jmp_true_fix_5
		cmp eax, dword ptr ds : [0x9cf7a4]
		je jmp_true_fix_5
		cmp eax, dword ptr ds : [0x9cf7a8]
		je jmp_true_fix_5
		cmp eax, dword ptr ds : [0x9cf7ac]
		je jmp_true_fix_5
		cmp eax, dword ptr ds : [0x9cf790]
		je jmp_true_fix_5
		cmp eax, dword ptr ds : [0x9cf8a0]
		je jmp_true_fix_5
		cmp eax, dword ptr ds : [0x9cf78c]
		je jmp_true_fix_5
		cmp eax, dword ptr ds : [0x9cf888]
		je jmp_true_fix_5
		cmp eax, dword ptr ds : [0x9cf88c]
		je jmp_true_fix_5
		push 0x76B38A
		ret
		jmp_true_fix_5 :
		push 0x76B410
			ret
	}
}

// 0076D6DF
void __declspec(naked) unknown_int_comps_fix_6()
{
	__asm
	{
		cmp ecx, dword ptr ds : [0x9cf79c]
		je jmp_true_fix_6
		cmp ecx, dword ptr ds : [0x9cf7a0]
		je jmp_true_fix_6
		cmp ecx, dword ptr ds : [0x9cf7a4]
		je jmp_true_fix_6
		cmp ecx, dword ptr ds : [0x9cf7a8]
		je jmp_true_fix_6
		cmp ecx, dword ptr ds : [0x9cf7ac]
		je jmp_true_fix_6
		cmp ecx, dword ptr ds : [0x9cf790]
		je jmp_true_fix_6
		cmp ecx, dword ptr ds : [0x9cf8a0]
		je jmp_true_fix_6
		cmp ecx, dword ptr ds : [0x9cf78c]
		je jmp_true_fix_6
		cmp ecx, dword ptr ds : [0x9cf888]
		je jmp_true_fix_6
		cmp ecx, dword ptr ds : [0x9cf88c]
		je jmp_true_fix_6
		push 0x76D729
		ret
		jmp_true_fix_6 :
		push 0x76D749
			ret
	}
}

// 0076F1EC
void __declspec(naked) unknown_int_comps_fix_7()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf79c]
		je jmp_true_fix_7
		cmp eax, dword ptr ds : [0x9cf7a0]
		je jmp_true_fix_7
		cmp eax, dword ptr ds : [0x9cf7a4]
		je jmp_true_fix_7
		cmp eax, dword ptr ds : [0x9cf7a8]
		je jmp_true_fix_7
		cmp eax, dword ptr ds : [0x9cf7ac]
		je jmp_true_fix_7
		cmp eax, dword ptr ds : [0x9cf790]
		je jmp_true_fix_7
		cmp eax, dword ptr ds : [0x9cf8a0]
		je jmp_true_fix_7
		cmp eax, dword ptr ds : [0x9cf78c]
		je jmp_true_fix_7
		cmp eax, dword ptr ds : [0x9cf888]
		je jmp_true_fix_7
		cmp eax, dword ptr ds : [0x9cf88c]
		je jmp_true_fix_7
		push 0x76F23D
		ret
		jmp_true_fix_7 :
		push 0x76F236
			ret
	}
}

// 0076D466
void __declspec(naked) comps_callup_squad_size()
{
	__asm
	{
		cmp eax, dword ptr ds : [0x9cf79c]
		je callup_size_finals
		cmp eax, dword ptr ds : [0x9cf7a0]
		je callup_size_finals
		cmp eax, dword ptr ds : [0x9cf7a4]
		je callup_size_finals
		cmp eax, dword ptr ds : [0x9cf7a8]
		je callup_size_finals
		cmp eax, dword ptr ds : [0x9cf7ac]
		je callup_size_finals
		cmp eax, dword ptr ds : [0x9cf790]
		je callup_size_finals
		cmp eax, dword ptr ds : [0x9cf8a0]
		je callup_size_finals
		cmp eax, dword ptr ds : [0x9cf78c]
		je callup_size_finals
		cmp eax, dword ptr ds : [0x9cf888]
		je callup_size_finals
		cmp eax, dword ptr ds : [0x9cf88c]
		je callup_size_finals
		push 0x76D4C0
		ret
		callup_size_finals :
		push 0x76D4B0
			ret
	}
}

void __declspec(naked) hosts_force_gold_cup_usa()
{
	__asm
	{
		mov ebp, dword ptr ss : [esp + 0x14]
		cmp ebp, dword ptr ds : [0x9cf78c]
		je usa_gold_cup
		mov di, word ptr ss : [esp + 0x18]
		push 0x5fa74a
		ret
		usa_gold_cup :
		mov ecx, dword ptr ss : [esp + 0x1c]
			mov edx, dword ptr ds : [0x9cf4f8] // USA
			mov dword ptr ds : [ecx] , edx
			mov eax, -1
			mov edx, dword ptr ss : [esp + 0x20]
			mov dword ptr ds : [edx] , eax
			push 0x5fa7b2
			ret
	}
}

char fix_hosts_news_function(BYTE* _this, long comp_id, DWORD* host1_ptr, DWORD* host2_ptr) {
	comp_stats* comp = (comp_stats*)get_loaded_league(comp_id);
	return get_host_ids_5FA730(_this, comp_id, comp->year, host1_ptr, host2_ptr, 1);
}

void __declspec(naked) fix_hosts_news_function_c()
{
	__asm {
		mov edx, dword ptr ds : [0xADADFC]
		test edx, edx
		je no_comp_stats
		push ecx
		mov ecx, dword ptr ds : [esp + 8]
		mov edx, dword ptr ds : [edx + ecx * 4]
		pop ecx
		test edx, edx
		je no_comp_stats
		mov eax, esp
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fix_hosts_news_function
		add esp, 0x10
		ret 0xc
		no_comp_stats:
		mov eax, dword ptr ds : [ecx]
			push esi
			mov si, word ptr ds : [ecx + 4]
			mov ecx, dword ptr ss : [esp + 0x8]
			cmp ecx, dword ptr ds : [0x9cf78c]
			je usa_gold_cup_2
			xor edx, edx
			test si, si
			push 0x5fa7dc
			ret
			usa_gold_cup_2 :
		push edi
			mov ecx, dword ptr ss : [esp + 0x10]
			mov edx, dword ptr ds : [0x9cf4f8] // USA
			mov dword ptr ds : [ecx] , edx
			mov eax, -1
			mov edx, dword ptr ss : [esp + 0x14]
			mov dword ptr ds : [edx] , eax
			push 0x5fa82e
			ret
	}
}

void setup_misc_functions()
{
	// update game name
	int year = START_YEAR % 2000;
	char name1[6];
	char name2[8];
	sprintf(name1, "%d/%d", year, year + 1);
	sprintf(name2, "%d/%d", START_YEAR, year + 1);
	WriteString(0x9cd33d, 6, name1);
	WriteString(0xa8029d, 8, name2);

	// update version name
	WriteDWORD(0x90d131, (DWORD)&VERSION[0]);
	char* patch_name = "Restructures Patch Version";
	WriteDWORD(0x591215, (DWORD)&patch_name[0]);
	char* patch_name_short = "Restructures\n<%s - version>";
	WriteDWORD(0x75dcba, (DWORD)&patch_name_short[0]);
	char* patch_details_str = "Restructures Patch Version: <%s - version> - Build: <%s - Build Date> <%s - Build Time>";
	WriteDWORD(0x823b63, (DWORD)&patch_details_str[0]);
	WriteNOP(0x823b50, 2);
	WriteDWORD(0x823b58, (DWORD)&__DATE__[0]);
	WriteDWORD(0x823b53, (DWORD)&__TIME__[0]);

	if (configFile.GetBool("competitionColoursPatch", true)) PatchFunction(0x53b7c0, (DWORD)&comp_colours_in_header);
	PatchFunction(0x669f50, (DWORD)&show_extra_leagues_in_start);
	PatchFunction(0x4B01D0, (DWORD)&parent_child_stages);
	PatchFunction(0x46B71E, (DWORD)&aus_minor_premier_in_history);
	PatchFunction(0x499535, (DWORD)&playoff_winner_in_history);
	PatchFunction(0x460ec6, (DWORD)&club_pro_status_with_continental_comp_c);
	PatchFunction(0x460d75, (DWORD)&show_club_country_based);
	PatchFunction(0x8c5bd2, (DWORD)&player_gain_nationality_c);
	PatchFunction(0x58CF70, (DWORD)&update_fifa_coefficients_c);
	PatchFunction(0x49dbcd, (DWORD)&quick_uefa_fix_1);
	PatchFunction(0x49e647, (DWORD)&quick_uefa_fix_2);
	PatchFunction(0x81e9be, (DWORD)&print_country_date_info_start_c);
	char* select_start = "Select Start Date";
	WriteDWORD(0x81e959, (DWORD)&select_start[0]);
	// block the old coefficients update function
	WriteBytes(0x58dfc0, 1, 0xc3);
	WriteDWORD(0x58ddfd + 2, 0x967880);
	WriteNOP(0x58de05, 6);
	if (configFile.GetBool("brazilRegenNames", false)) {
		// point 1
		WriteNOP(0x7ab3e0, 6);
		PatchFunction(0x7ab3e0, (DWORD)&brazil_regens_common_names_1);
		// point 2, needs extra changes
		WriteBytes(0x59eba4, 1, 0xb6);
		WriteBytes(0x59ebaf, 1, 0x8);
		WriteNOP(0x59ebb9, 6);
		PatchFunction(0x59ebb9, (DWORD)&brazil_regens_common_names_2);
		// point 3
		WriteNOP(0x7abd90, 6);
		PatchFunction(0x7abd90, (DWORD)&brazil_regens_common_names_3);
	}

	// hide history button for certain comps -> set VTableShowThirdInHistory to 0x48ce70
	WriteBytes(0x4901c7, 12, 0x8B, 0x45, 0x00, 0xFF, 0x50, 0x50, 0x3C, 0x00, 0x90, 0x90, 0x90, 0x90);

	// club home match day becomes unused, was forcing N.Irish teams to not play on Sundays
	WriteBytes(0x5AA77A, 6, 0xe9, 0x3, 0x1, 0, 0, 0x90);
	WriteNOP(0x5adcf1, 2);

	// Show the hidden wing-back position
	if (configFile.GetBool("showWingBacks", false)) {
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
		WriteBytes(d + 4, 1, 24);
	}
	for (DWORD d : friendly_aug_30plus3) {
		WriteBytes(d + 3, 1, 24);
	}
	WriteBytes(0x5cb892 + 1, 1, 24);
	WriteBytes(0x5cb8dc + 1, 1, 24);
	// Move September 3's international friendlies forward one week
	for (DWORD d : friendly_sept_3plus4) {
		WriteBytes(d + 4, 1, 27);
	}
	for (DWORD d : friendly_sept_3plus3) {
		WriteBytes(d + 3, 1, 27);
	}
	WriteBytes(0x5caba1, 7, 0x66, 0xC7, 0x40, 0x01, 0x1b, 0x08, 0x90);
	WriteBytes(0x5cad0e, 7, 0x66, 0xC7, 0x40, 0x01, 0x1b, 0x08, 0x90);
	WriteBytes(0x5cb459, 7, 0x66, 0xC7, 0x40, 0x01, 0x1b, 0x08, 0x90);
	// Move October 4's international friendlies back 3 days
	for (DWORD d : friendly_oct_4plus4) {
		WriteBytes(d + 4, 1, 1);
	}
	for (DWORD d : friendly_oct_4plus3) {
		WriteBytes(d + 3, 1, 1);
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

	PatchFunction(0x66955c, (DWORD)&show_playoff_in_menu);
	PatchFunction(0x46b409, (DWORD)&year_offset_in_landmarks);
	// tag comp as being part of "World Cup" menu?
	PatchFunction(0x669abe, (DWORD)&unknown_check_2);
	// tag comp as being part of "International" menu?
	PatchFunction(0x669ba6, (DWORD)&unknown_check_3);
	PatchFunction(0x6b6358, (DWORD)&international_comps_to_continent);
	PatchFunction(0x76D940, (DWORD)&is_international_comp_no_qualifiers);
	PatchFunction(0x76b455, (DWORD)&unknown_int_comps_fix_1);
	PatchFunction(0x76C28F, (DWORD)&keep_players_in_comp_until_end);
	PatchFunction(0x775293, (DWORD)&unknown_int_comps_fix_3);
	PatchFunction(0x7752FC, (DWORD)&unknown_int_comps_fix_4);
	PatchFunction(0x76B31C, (DWORD)&unknown_int_comps_fix_5);
	PatchFunction(0x76D6DF, (DWORD)&unknown_int_comps_fix_6);
	PatchFunction(0x76F1EC, (DWORD)&unknown_int_comps_fix_7);
	PatchFunction(0x76D466, (DWORD)&comps_callup_squad_size);

	// Gold Cup always hosted in the USA
	PatchFunction(0x5fa745, (DWORD)&hosts_force_gold_cup_usa);
	PatchFunction(0x5fa7d0, (DWORD)&fix_hosts_news_function_c);

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

	// Fix too many countries to select in player/scout filter, causing a (harmless) error
	WriteBytes(0x80959d, 1, 9);
	WriteNOP(0x8095a8, 2);
	WriteBytes(0x8149a1, 1, 9);
	// Hopefully temporary: hide Area.cpp 507/838 error for other cases
	WriteNOP(0x40344c, 5);
	WriteNOP(0x403c32, 5);

	// temporary: suppresses hall_of_fame 315 error
	WriteNOP(0x5ef93b, 5);
	// hopefully temporary: suppresses discipline 1149 error
	WriteNOP(0x556e20, 5);

	// Enable Bosman signings from all countries
	WriteBytes(0x544677, 1, 0xeb);

	// "groups drawn" news message title adjustment => review this
	WriteDWORD(0x77fcda + 1, ThirdRound);
	WriteDWORD(0x77fcfe + 1, (DWORD)&r3_groups_drawn[0]);
	WriteDWORD(0x77fd05 + 1, FourthRound);
	WriteDWORD(0x77fd28 + 1, (DWORD)&r4_groups_drawn[0]);
	PatchFunction(0x77fd2f, (DWORD)&fixed_groups_drawn_news_title);
	// misspelling
	WriteBytes(0xa0aa2a, 2, 'y', '\'');

	const char* titlebar_bg = configFile.GetValue("defaultTitleBackground", "0xAE31A8");
	DWORD titlebar_bg_hex = stoul(titlebar_bg, nullptr, 16);
	const char* titlebar_fg = configFile.GetValue("defaultTitleForeground", "0xAE3184");
	DWORD titlebar_fg_hex = stoul(titlebar_fg, nullptr, 16);

	// change default colours - clubs with no colours
	WriteDWORD(0x53b642, 0xae317e);
	WriteDWORD(0x53b662, 0xae3154);
	WriteDWORD(0x839598, 0xae317e);
	WriteDWORD(0x8395a0, 0xae3154);

	// change default titlebar colours (menus)
	for (DWORD d : replace_titlebar_bg) {
		WriteDWORD(d, titlebar_bg_hex);
	}
	for (DWORD d : replace_titlebar_fg) {
		WriteDWORD(d, titlebar_fg_hex);
	}
	// fix web sites menu
	WriteNOP(0x513a2e, 10);
	WriteBytes(0x513a2e, 2, 0x66, 0xa1);
	WriteDWORD(0x513a30, titlebar_fg_hex);
	WriteNOP(0x513a39, 10);
	WriteBytes(0x513a39, 2, 0x66, 0xa1);
	WriteDWORD(0x513a3b, titlebar_bg_hex);
	// fix credits menu
	WriteNOP(0x51331d, 5);
	WriteNOP(0x513341, 5);
	WriteNOP(0x5131bc, 10);
	WriteBytes(0x5131bc, 2, 0x66, 0xa1);
	WriteDWORD(0x5131be, titlebar_fg_hex);
	WriteNOP(0x5131c7, 9);
	WriteBytes(0x5131c7, 2, 0x66, 0xa1);
	WriteDWORD(0x5131c9, titlebar_bg_hex);
	// fix nations & clubs menu
	WriteNOP(0x5a0903, 9);
	WriteBytes(0x5a0903, 2, 0x66, 0xa1);
	WriteDWORD(0x5a0905, titlebar_fg_hex);
	WriteNOP(0x5a090d, 10);
	WriteBytes(0x5a090d, 2, 0x66, 0xa1);
	WriteDWORD(0x5a090f, titlebar_bg_hex);
	// fix find menu
	WriteNOP(0x5a2ec1, 9);
	WriteBytes(0x5a2ec1, 2, 0x66, 0xa1);
	WriteDWORD(0x5a2ec3, titlebar_fg_hex);
	WriteNOP(0x5a2ecb, 10);
	WriteBytes(0x5a2ecb, 2, 0x66, 0xa1);
	WriteDWORD(0x5a2ecd, titlebar_bg_hex);
	// fix add nickname menu
	WriteNOP(0x88bcbe, 10);
	WriteBytes(0x88bcbe, 2, 0x66, 0xa1);
	WriteDWORD(0x88bcc0, titlebar_fg_hex);
	WriteNOP(0x88bcc9, 10);
	WriteBytes(0x88bcc9, 2, 0x66, 0xa1);
	WriteDWORD(0x88bccb, titlebar_bg_hex);
	// fix send message menu
	WriteNOP(0x7899d1, 10);
	WriteBytes(0x7899d1, 2, 0x66, 0xa1);
	WriteDWORD(0x7899d3, titlebar_fg_hex);
	WriteNOP(0x7899dc, 10);
	WriteBytes(0x7899dc, 2, 0x66, 0xa1);
	WriteDWORD(0x7899de, titlebar_bg_hex);
	// fix manager chat menu
	WriteNOP(0x76558a, 10);
	WriteBytes(0x76558a, 2, 0x66, 0xa1);
	WriteDWORD(0x76558c, titlebar_fg_hex);
	WriteNOP(0x765595, 10);
	WriteBytes(0x765595, 2, 0x66, 0xa1);
	WriteDWORD(0x765597, titlebar_bg_hex);
	// fix go on holiday menu
	WriteNOP(0x6b2e1d, 10);
	WriteBytes(0x6b2e1d, 2, 0x66, 0xa1);
	WriteDWORD(0x6b2e1f, titlebar_fg_hex);
	WriteNOP(0x6b2e28, 10);
	WriteBytes(0x6b2e28, 2, 0x66, 0xa1);
	WriteDWORD(0x6b2e2a, titlebar_bg_hex);
	// fix restart game menu - backwards
	WriteNOP(0x7642c8, 9);
	WriteBytes(0x7642c8, 2, 0x66, 0xa1);
	WriteDWORD(0x7642ca, titlebar_bg_hex);
	WriteNOP(0x7642d2, 10);
	WriteBytes(0x7642d2, 2, 0x66, 0xa1);
	WriteDWORD(0x7642d4, titlebar_fg_hex);
	// fix exit game menu - backwards
	WriteNOP(0x764371, 9);
	WriteBytes(0x764371, 2, 0x66, 0xa1);
	WriteDWORD(0x764373, titlebar_bg_hex);
	WriteNOP(0x76437b, 10);
	WriteBytes(0x76437b, 2, 0x66, 0xa1);
	WriteDWORD(0x76437d, titlebar_fg_hex);
	// fix save game menu - backwards
	WriteNOP(0x763f5e, 1);
	WriteNOP(0x763f64, 8);
	WriteBytes(0x763f64, 2, 0x66, 0xa1);
	WriteDWORD(0x763f66, titlebar_bg_hex);
	WriteNOP(0x763f6d, 10);
	WriteBytes(0x763f6d, 2, 0x66, 0xa1);
	WriteDWORD(0x763f6f, titlebar_fg_hex);
	// fix save before exit menu - backwards
	WriteNOP(0x762bf1, 1);
	WriteNOP(0x762bfb, 8);
	WriteBytes(0x762bfb, 2, 0x66, 0xa1);
	WriteDWORD(0x762bfd, titlebar_bg_hex);
	WriteNOP(0x762c04, 10);
	WriteBytes(0x762c04, 2, 0x66, 0xa1);
	WriteDWORD(0x762c06, titlebar_fg_hex);
	// fix save before restart menu - backwards
	WriteNOP(0x762a44, 1);
	WriteNOP(0x762a4a, 8);
	WriteBytes(0x762a4a, 2, 0x66, 0xa1);
	WriteDWORD(0x762a4c, titlebar_bg_hex);
	WriteNOP(0x762a53, 10);
	WriteBytes(0x762a53, 2, 0x66, 0xa1);
	WriteDWORD(0x762a55, titlebar_fg_hex);
	// fix auto save game menu - backwards
	WriteNOP(0x761722, 1);
	WriteNOP(0x761728, 8);
	WriteBytes(0x761728, 2, 0x66, 0xa1);
	WriteDWORD(0x76172a, titlebar_bg_hex);
	WriteNOP(0x761731, 10);
	WriteBytes(0x761731, 2, 0x66, 0xa1);
	WriteDWORD(0x761733, titlebar_fg_hex);
}
