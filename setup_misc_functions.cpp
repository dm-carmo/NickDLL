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
	/* Unused for now :)
	if (cm3_nation->NationID == NATION_AUSTRALIA_9CF()) {
		league_str = "National Premier Leagues";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_CROATIA_9CF()) {
		league_str = "3. NL";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_DENMARK_9CF()) {
		league_str = "Danmarksserien";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_FRANCE_9CF()) {
		league_str = "National 2";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_GREECE_9CF()) {
		league_str = "Gamma Ethniki";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_HOLLAND_9CF()) {
		league_str = "Tweede Divisie";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_ITALY_9CF()) {
		league_str = "Serie D";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_POLAND_9CF()) {
		league_str = "III liga";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_RUSSIA_9CF()) {
		league_str = "Second League";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_SOUTH_KOREA_9CF()) {
		league_str = "K3 League";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	*/
	return 0;
}

int parent_child_stages(int child_stage_id) {
	if (child_stage_id >= 0x3e8 && child_stage_id <= 0x3fb) return GroupStage;
	if (child_stage_id >= 0x41f && child_stage_id <= 0x42e) return GroupStage;
	if (child_stage_id == EasternConference) return GroupStage;
	if (child_stage_id == WesternConference) return GroupStage;
	if (child_stage_id == CentralConference) return GroupStage;
	if (child_stage_id == SecondPlacedTeams) return GroupStage;
	if (child_stage_id >= 0x473 && child_stage_id <= 0x474) return CentralAmericanZone;
	if (child_stage_id >= 0x475 && child_stage_id <= 0x479) return ClassificationGroup;
	if (child_stage_id >= 0x3fd && child_stage_id <= 0x406) return FirstRound;
	if ((child_stage_id >= 0x407 && child_stage_id <= 0x40B) || child_stage_id == SecondRoundGroup6) return SecondRound;
	if (child_stage_id >= 0x47e && child_stage_id <= 0x47f) return ThirdRound;
	if (child_stage_id >= 0x40c && child_stage_id <= 0x40e) return SemiFinal;
	if (child_stage_id >= 0x43d && child_stage_id <= 0x444) return Phase1;
	if (child_stage_id >= 0x445 && child_stage_id <= 0x448) return Phase2;
	if (child_stage_id >= 0x44d && child_stage_id <= 0x450) return PromotionGroupStage;
	if (configFile.GetBool("applyArgentina", true) && configFile.GetBool("applyPortugal", true))
		if (child_stage_id >= 0x47c && child_stage_id <= 0x47d) return FourthPromotionPlayoff; // Relegation Group Stage
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
	if (club->ClubProfessionalStatus == 1) {
		sprintf(pro_status, "%s%s", "Professional", continental_comp);
	}
	else if (club->ClubProfessionalStatus == 2) {
		sprintf(pro_status, "%s%s", "Semi-Professional", continental_comp);
	}
	else if (club->ClubProfessionalStatus == 3) {
		sprintf(pro_status, "%s%s", "Amateuer", continental_comp);
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

void setup_misc_functions()
{
	if (configFile.GetBool("competitionColoursPatch", true)) PatchFunction(0x53b7c0, (DWORD)&comp_colours_in_header);
	PatchFunction(0x669f50, (DWORD)&show_extra_leagues_in_start);
	PatchFunction(0x4B01D0, (DWORD)&parent_child_stages);
	PatchFunction(0x46B71E, (DWORD)&aus_minor_premier_in_history);
	PatchFunction(0x460ec6, (DWORD)&club_pro_status_with_continental_comp_c);

	// Move August 30's international friendlies forward one week
	for (DWORD d : friendly_aug_30plus4) {
		WriteBytes(d + 4, 1, 9);
	}
	for (DWORD d : friendly_aug_30plus3) {
		WriteBytes(d + 3, 1, 9);
	}
	WriteBytes(0x5cb892 + 1, 1, 9);
	WriteBytes(0x5cb8dc + 1, 1, 9);
	// Move September 3's international friendlies forward one week
	for (DWORD d : friendly_sept_3plus4) {
		WriteBytes(d + 4, 1, 13);
	}
	for (DWORD d : friendly_sept_3plus3) {
		WriteBytes(d + 3, 1, 13);
	}
	WriteBytes(0x5caba1, 7, 0x66, 0xC7, 0x40, 0x01, 0x0D, 0x08, 0x90);
	WriteBytes(0x5cad0e, 7, 0x66, 0xC7, 0x40, 0x01, 0x0D, 0x08, 0x90);
	WriteBytes(0x5cb459, 7, 0x66, 0xC7, 0x40, 0x01, 0x0D, 0x08, 0x90);
	// Move October 4's international friendlies forward one week
	for (DWORD d : friendly_oct_4plus4) {
		WriteBytes(d + 4, 1, 14);
	}
	for (DWORD d : friendly_oct_4plus3) {
		WriteBytes(d + 3, 1, 14);
	}
	// Move March 21's international friendlies forward one week
	for (DWORD d : friendly_march_21plus4) {
		WriteBytes(d + 4, 1, 31);
	}
	for (DWORD d : friendly_march_21plus3) {
		WriteBytes(d + 3, 1, 31);
	}
	WriteBytes(0x5cb872 + 1, 1, 31);
	WriteBytes(0x5cb8b7 + 1, 1, 31);

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
}
