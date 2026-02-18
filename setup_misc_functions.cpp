#include <windows.h>
#include <Structures/CMHeader.h>
#include <Helpers/9cf_constants.h>
#include <Helpers/generic_functions.h>
#include "Helpers/Helper.h"

static WORD(*rgb_to_word_5E4800)(unsigned char a1, unsigned char a2, unsigned char a3, DWORD* a4) =
(WORD(*)(unsigned char a1, unsigned char a2, unsigned char a3, DWORD * a4))(0x5E4800);

WORD* default_comp_colour_fg = (WORD*)0xAE3184;
WORD* default_comp_colour_bg = (WORD*)0xAEBE04;

int show_extra_leagues_in_start(BYTE* nation, DWORD dest_ptr, int a3) {
	if (!nation || !dest_ptr || a3 < 20) return 0;
	cm3_nations* cm3_nation = (cm3_nations*)nation;
	char* league_str;
	if (cm3_nation->NationID == NATION_ENGLAND_9CF()) {
		if (configFile.GetBool("applyEngland", true)) league_str = "National Leagues";
		else league_str = "National League";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_GERMANY_9CF()) {
		if (configFile.GetBool("applyGermany", true)) league_str = "Regionalliga";
		else league_str = "3. Liga";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_ITALY_9CF()) {
		if (configFile.GetBool("applyItaly", true)) return 0;
		else league_str = "Serie C2";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_JAPAN_9CF()) {
		if (configFile.GetBool("applyJapan", true)) league_str = "JFL";
		else return 0;
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_PORTUGAL_9CF()) {
		if (configFile.GetBool("applyPortugal", true)) league_str = "Campeonato de Portugal";
		else league_str = "Liga 3";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_SPAIN_9CF()) {
		league_str = "Primera Federación";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_SWEDEN_9CF()) {
		if (configFile.GetBool("applySweden", true)) league_str = "Division 2";
		else league_str = "Ettan";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	/* Unused for now :)
	if (cm3_nation->NationID == NATION_ARGENTINA_9CF()) {
		league_str = "Primera B/Torneo Federal";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_AUSTRALIA_9CF()) {
		league_str = "National Premier Leagues";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_BELGIUM_9CF()) {
		league_str = "Division 2";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_BRAZIL_9CF()) {
		league_str = "Série D";
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
	if (cm3_nation->NationID == NATION_FINLAND_9CF()) {
		league_str = "Kakkonen";
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
	if (cm3_nation->NationID == NATION_NORTHERN_IRELAND_9CF()) {
		league_str = "Intermediate League";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_NORWAY_9CF()) {
		league_str = "2. divisjon";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_POLAND_9CF()) {
		league_str = "III liga";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_IRELAND_9CF()) {
		league_str = "Senior Leagues";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_RUSSIA_9CF()) {
		league_str = "Second League";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_SCOTLAND_9CF()) {
		league_str = "Highland/Lowland";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_SOUTH_KOREA_9CF()) {
		league_str = "K3 League";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_TURKEY_9CF()) {
		league_str = "3. Lig";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_USA_9CF()) {
		league_str = "USL Championship";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	if (cm3_nation->NationID == NATION_WALES_9CF()) {
		league_str = "Cymru North/South";
		sub_66F4E0(dest_ptr, (DWORD)&league_str[0]);
		return 1;
	}
	*/
	return 0;
}

void __declspec(naked) show_extra_leagues_in_start_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call show_extra_leagues_in_start
		add esp, 0x4
		ret 0
	}
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

void setup_misc_functions()
{
	if (configFile.GetBool("competitionColoursPatch", true)) PatchFunction(0x53b7c0, (DWORD)&comp_colours_in_header);
	PatchFunction(0x669f50, (DWORD)&show_extra_leagues_in_start);
}
