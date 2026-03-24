#include <Windows.h>
#include <Structures\CMHeader.h>
#include <Helpers\generic_functions.h>
#include <Helpers\9cf_constants.h>
#include <leagues_setup.h>

int replacement_667150() {
	int idx = 0;
	pnd_list[idx].nation = 0;
	pnd_list[idx].continent = 0;
	pnd_list[idx].setup_function_addr = 0x830620;
	convert_to_cm_date(pnd_list[idx].start_date, 1, July, *current_year, -1);
	convert_to_cm_date(pnd_list[idx].end_date, 1, July, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	idx++;

	pnd_list[idx].nation = 0;
	pnd_list[idx].continent = 0;
	pnd_list[idx].setup_function_addr = 0x830AC0;
	convert_to_cm_date(pnd_list[idx].start_date, 1, July, *current_year, -1);
	convert_to_cm_date(pnd_list[idx].end_date, 1, July, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	idx++;

	BYTE* cm_date = new BYTE[8];
	pnd_list[idx].nation = 0;
	pnd_list[idx].continent = 0;
	if (configFile.GetBool("applyFIFAclubs", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&fifa_club_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 1, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 1, July, *current_year, -1);
		pnd_list[idx].updates_in_june = 1;
		convert_to_cm_date(cm_date, 2, January, 2025, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x830FE0;
		convert_to_cm_date(pnd_list[idx].start_date, 22, June, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 20, May, *current_year, -1);
		pnd_list[idx].updates_in_june = 1;
		convert_to_cm_date(cm_date, 21, June, 2025, -1);
	}
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].continent = find_continent("Europe");
	if (configFile.GetBool("applyUEFA", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&uefa_setup_c;
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x8312E0;
	}
	convert_to_cm_date(pnd_list[idx].start_date, 23, June, *current_year, -1);
	convert_to_cm_date(pnd_list[idx].end_date, 20, May, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 21, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(UEFA_CHAMPIONS_LEAGUE_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].continent = find_continent("North America");
	if (configFile.GetBool("applyCONCACAF", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&concacaf_setup_c;
		convert_to_cm_date(cm_date, 2, January, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
		pnd_list[idx].updates_in_june = 0;
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x831650;
		convert_to_cm_date(cm_date, 1, February, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
		pnd_list[idx].updates_in_june = 1;
	}
	convert_to_cm_date(pnd_list[idx].start_date, 1, July, *current_year, -1);
	convert_to_cm_date(pnd_list[idx].end_date, 1, July, *current_year, -1);
	pnd_list[idx].main_cup = get_comp(CONCACAF_CHAMPIONS_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].continent = find_continent("South America");
	if (configFile.GetBool("applyCONMEBOL", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&conmebol_setup_c;
		convert_to_cm_date(cm_date, 2, January, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
		pnd_list[idx].updates_in_june = 0;
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x8318F0;
		convert_to_cm_date(cm_date, 21, December, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
		pnd_list[idx].updates_in_june = 1;
	}
	convert_to_cm_date(pnd_list[idx].start_date, 1, July, *current_year, -1);
	convert_to_cm_date(pnd_list[idx].end_date, 1, July, *current_year, -1);
	pnd_list[idx].main_cup = get_comp(COPA_LIBERTADORES_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].continent = find_continent("Asia");
	if (configFile.GetBool("applyAFC", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&afc_setup_c;
		convert_to_cm_date(cm_date, 21, June, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x831BA0;
		convert_to_cm_date(cm_date, 21, February, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
	}
	convert_to_cm_date(pnd_list[idx].start_date, 1, July, *current_year, -1);
	convert_to_cm_date(pnd_list[idx].end_date, 1, July, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	pnd_list[idx].main_cup = get_comp(AFC_CHAMPIONS_LEAGUE_ELITE_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].continent = find_continent("Oceania");
	if (configFile.GetBool("applyOFC", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&ofc_setup_c;
		convert_to_cm_date(cm_date, 2, January, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
		pnd_list[idx].updates_in_june = 0;
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x831EB0;
		convert_to_cm_date(cm_date, 21, July, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
		pnd_list[idx].updates_in_june = 1;
	}
	convert_to_cm_date(pnd_list[idx].start_date, 1, July, *current_year, -1);
	convert_to_cm_date(pnd_list[idx].end_date, 1, July, *current_year, -1);
	pnd_list[idx].main_cup = get_comp(OFC_CHAMPIONS_LEAGUE_9CF());
	idx++;

	if (configFile.GetBool("applyCAF", true)) {
		cm_date = new BYTE[8];
		pnd_list[idx].continent = find_continent("Africa");
		pnd_list[idx].setup_function_addr = (DWORD)&caf_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 1, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 1, July, *current_year, -1);
		pnd_list[idx].updates_in_june = 1;
		convert_to_cm_date(cm_date, 21, June, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
		pnd_list[idx].main_cup = get_comp(CAF_CHAMPIONS_LEAGUE_9CF());
		idx++;
	}

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_ARGENTINA_9CF());
	if (configFile.GetBool("applyArgentina", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&arg_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 1, February, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 17, December, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 1, January, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
		pnd_list[idx].main_cup = get_comp(ARG_CUP_9CF());
		pnd_list[idx].updates_in_june = 0;
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x832100;
		convert_to_cm_date(pnd_list[idx].start_date, 9, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 19, July, *current_year, -1);
		convert_to_cm_date(cm_date, 1, August, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
		pnd_list[idx].updates_in_june = 1;
	}
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_AUSTRALIA_9CF());
	if (configFile.GetBool("applyAustralia", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&aus_setup_c;
		//convert_to_cm_date(pnd_list[idx].start_date, 18, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 6, June, *current_year, -1);
		convert_to_cm_date(cm_date, 20, June, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
		pnd_list[idx].main_cup = get_comp(AUS_CUP_9CF());
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x832380;
		convert_to_cm_date(pnd_list[idx].start_date, 2, October, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 10, June, *current_year, -1);
		convert_to_cm_date(cm_date, 1, August, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
	}
	pnd_list[idx].updates_in_june = 1;
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_BELGIUM_9CF());
	pnd_list[idx].setup_function_addr = 0x8325D0;
	convert_to_cm_date(pnd_list[idx].start_date, 7, August, *current_year, -1);
	convert_to_cm_date(pnd_list[idx].end_date, 1, June, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(BEL_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_BRAZIL_9CF());
	if (configFile.GetBool("applyBrazil", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&bra_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 31, January, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 17, December, *current_year + 1, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x832980;
		convert_to_cm_date(pnd_list[idx].start_date, 18, January, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 14, December, *current_year + 1, -1);
	}
	pnd_list[idx].updates_in_june = 0;
	convert_to_cm_date(cm_date, 1, January, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(BRA_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_CROATIA_9CF());
	if (configFile.GetBool("applyCroatia", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&cro_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 6, June, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x8330B0;
		convert_to_cm_date(pnd_list[idx].start_date, 24, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 28, May, *current_year, -1);
	}
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(CRO_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_DENMARK_9CF());
	if (configFile.GetBool("applyDenmark", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&den_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 31, May, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x833400;
		convert_to_cm_date(pnd_list[idx].start_date, 27, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 14, June, *current_year, -1);
	}
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(DEN_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_ENGLAND_9CF());
	if (configFile.GetBool("applyEngland", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&eng_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x833750;
		convert_to_cm_date(pnd_list[idx].start_date, 10, August, *current_year, -1);
	}
	convert_to_cm_date(pnd_list[idx].end_date, 31, May, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(ENG_FA_CUP_9CF());
	pnd_list[idx].league_cup = get_comp(ENG_LEAGUE_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_FINLAND_9CF());
	if (configFile.GetBool("applyFinland", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&fin_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 5, April, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 1, January, 2025, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x833CF0;
		convert_to_cm_date(pnd_list[idx].start_date, 29, April, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 27, December, 2025, -1);
	}
	convert_to_cm_date(pnd_list[idx].end_date, 12, November, *current_year + 1, -1);
	pnd_list[idx].updates_in_june = 0;
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(FIN_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_FRANCE_9CF());
	if (configFile.GetBool("applyFrance", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&fra_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x833FF0;
		convert_to_cm_date(pnd_list[idx].start_date, 9, August, *current_year, -1);
	}
	convert_to_cm_date(pnd_list[idx].end_date, 24, May, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(FRA_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_GERMANY_9CF());
	if (configFile.GetBool("applyGermany", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&ger_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 31, May, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x8343F0;
		convert_to_cm_date(pnd_list[idx].start_date, 29, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 26, May, *current_year, -1);
	}
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(GER_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_GREECE_9CF());
	if (configFile.GetBool("applyGreece", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&gre_setup_c;
		//convert_to_cm_date(pnd_list[idx].start_date, 23, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 28, May, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x8347C0;
		convert_to_cm_date(pnd_list[idx].start_date, 15, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 21, May, *current_year, -1);
	}
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(GRE_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_HOLLAND_9CF());
	if (configFile.GetBool("applyHolland", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&hol_setup_c;
		//convert_to_cm_date(pnd_list[idx].start_date, 9, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 28, May, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x834B10;
		convert_to_cm_date(pnd_list[idx].start_date, 16, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 7, June, *current_year, -1);
	}
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(HOL_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_IRELAND_9CF());
	if (configFile.GetBool("applyIreland", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&irl_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 14, February, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 14, November, *current_year + 1, -1);
		pnd_list[idx].updates_in_june = 0;
		convert_to_cm_date(cm_date, 1, January, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x834E60;
		convert_to_cm_date(pnd_list[idx].start_date, 1, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 18, May, *current_year, -1);
		pnd_list[idx].updates_in_june = 1;
		convert_to_cm_date(cm_date, 20, June, 2025, -1);
		pnd_list[idx].update_day = *(WORD*)(cm_date);
	}
	pnd_list[idx].main_cup = get_comp(IRL_CHALLENGE_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_ITALY_9CF());
	if (configFile.GetBool("applyItaly", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&ita_setup_c;
		//convert_to_cm_date(pnd_list[idx].start_date, 16, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 10, June, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x835320;
		convert_to_cm_date(pnd_list[idx].start_date, 25, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 8, June, *current_year, -1);
	}
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(ITA_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_JAPAN_9CF());
	if (configFile.GetBool("applyJapan", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&jpn_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 14, February, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 9, December, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 1, January, 2025, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x835900;
		convert_to_cm_date(pnd_list[idx].start_date, 6, March, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 28, November, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 25, January, 2025, -1);
	}
	pnd_list[idx].updates_in_june = 0;
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(JPN_EMPEROR_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_NORTHERN_IRELAND_9CF());
	if (configFile.GetBool("applyNorthernIreland", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&nir_setup_c;
		//convert_to_cm_date(pnd_list[idx].start_date, 8, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x835C90;
		convert_to_cm_date(pnd_list[idx].start_date, 12, August, *current_year, -1);
	}
	convert_to_cm_date(pnd_list[idx].end_date, 8, May, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(NIR_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_NORWAY_9CF());
	if (configFile.GetBool("applyNorway", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&nor_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 30, March, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 14, December, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 1, January, 2025, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x836050;
		convert_to_cm_date(pnd_list[idx].start_date, 12, April, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 31, October, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 27, November, 2025, -1);
	}
	pnd_list[idx].updates_in_june = 0;
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(NOR_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_POLAND_9CF());
	if (configFile.GetBool("applyPoland", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&pol_setup_c;
		//convert_to_cm_date(pnd_list[idx].start_date, 20, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x836350;
		convert_to_cm_date(pnd_list[idx].start_date, 17, July, *current_year, -1);
	}
	convert_to_cm_date(pnd_list[idx].end_date, 5, June, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(POL_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_PORTUGAL_9CF());
	if (configFile.GetBool("applyPortugal", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&por_setup_c;
		//convert_to_cm_date(pnd_list[idx].start_date, 3, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 10, June, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x8366E0;
		convert_to_cm_date(pnd_list[idx].start_date, 25, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 8, June, *current_year, -1);
	}
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(POR_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_RUSSIA_9CF());
	pnd_list[idx].setup_function_addr = 0x836AC0;
	convert_to_cm_date(pnd_list[idx].start_date, 25, March, *current_year + 1, -1);
	convert_to_cm_date(pnd_list[idx].end_date, 12, November, *current_year + 1, -1);
	pnd_list[idx].updates_in_june = 0;
	convert_to_cm_date(cm_date, 27, December, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(RUS_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_SCOTLAND_9CF());
	if (configFile.GetBool("applyScotland", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&sco_setup_c;
		//convert_to_cm_date(pnd_list[idx].start_date, 2, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 31, May, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x836DC0;
		convert_to_cm_date(pnd_list[idx].start_date, 2, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 24, May, *current_year, -1);
	}
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(SCO_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_SOUTH_KOREA_9CF());
	if (configFile.GetBool("applySouthKorea", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&kor_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 15, February, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 8, December, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 1, January, 2025, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x837200;
		convert_to_cm_date(pnd_list[idx].start_date, 25, March, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 25, November, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 14, January, 2025, -1);
	}
	pnd_list[idx].updates_in_june = 0;
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(KOR_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_SPAIN_9CF());
	if (configFile.GetBool("applySpain", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&spa_setup_c;
		//convert_to_cm_date(pnd_list[idx].start_date, 20, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x837560;
		convert_to_cm_date(pnd_list[idx].start_date, 20, August, *current_year, -1);
	}
	convert_to_cm_date(pnd_list[idx].end_date, 14, June, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(SPA_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_SWEDEN_9CF());
	if (configFile.GetBool("applySweden", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&swe_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 30, March, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 30, November, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 1, January, 2025, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x8379F0;
		convert_to_cm_date(pnd_list[idx].start_date, 6, April, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 26, October, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 27, December, 2025, -1);
	}
	pnd_list[idx].updates_in_june = 0;
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(SWE_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_TURKEY_9CF());
	if (configFile.GetBool("applyTurkey", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&tur_setup_c;
		//convert_to_cm_date(pnd_list[idx].start_date, 8, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 31, May, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x837D70;
		convert_to_cm_date(pnd_list[idx].start_date, 8, August, *current_year, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 20, May, *current_year, -1);
	}
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(TUR_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_USA_9CF());
	if (configFile.GetBool("applyUSA", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&usa_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 22, February, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 10, December, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 1, January, 2025, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x8380C0;
		convert_to_cm_date(pnd_list[idx].start_date, 22, March, *current_year + 1, -1);
		convert_to_cm_date(pnd_list[idx].end_date, 6, January, *current_year + 1, -1);
		convert_to_cm_date(cm_date, 20, February, 2025, -1);
	}
	pnd_list[idx].updates_in_june = 0;
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(USA_OPEN_CUP_9CF());
	idx++;

	cm_date = new BYTE[8];
	pnd_list[idx].nation = get_country(NATION_WALES_9CF());
	if (configFile.GetBool("applyWales", true))
	{
		pnd_list[idx].setup_function_addr = (DWORD)&wal_setup_c;
		convert_to_cm_date(pnd_list[idx].start_date, 25, July, *current_year, -1);
	}
	else
	{
		pnd_list[idx].setup_function_addr = 0x8383B0;
		convert_to_cm_date(pnd_list[idx].start_date, 19, August, *current_year, -1);
	}
	convert_to_cm_date(pnd_list[idx].end_date, 6, May, *current_year, -1);
	pnd_list[idx].updates_in_june = 1;
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	pnd_list[idx].update_day = *(WORD*)(cm_date);
	pnd_list[idx].main_cup = get_comp(WAL_CUP_9CF());
	idx++;

	return 1;
}

vector<DWORD> pnd_order_addr = {
	0x66A0C2 + 1, 0x66A0DD + 1, 0x66A0EF + 1,
};

vector<DWORD> pnd_addr = {
	0x40E7EA + 2, 0x44796E + 3, 0x455330 + 3, 0x45F48F + 3, 0x48DE16 + 3, 0x48DE6B + 3, 0x48DEF5 + 3, 0x48DF5F + 3, 0x49D130 + 3, 0x591F9B + 1, 0x592028 + 1, 0x59CECF + 3, 0x5AF5EF + 3, 0x5C2D74 + 1, 0x5C3084 + 2, 0x5C3124 + 2, 0x5C31A7 + 2, 0x5C31C3 + 2, 0x5C320A + 2, 0x5C37D2 + 1, 0x5C482F + 1, 0x5D5BD0 + 3, 0x6670BE + 1, 0x6670E9 + 1, 0x66934C + 3, 0x6693A0 + 3, 0x66948D + 3, 0x66958D + 2, 0x6695D0 + 1, 0x669609 + 1, 0x66968B + 3, 0x66981A + 3, 0x66998A + 3, 0x6699D5 + 1, 0x669C0E + 1, 0x669C2B + 3, 0x66A13C + 2, 0x66A14D + 2, 0x66A2A8 + 1, 0x66A2E7 + 3, 0x66A2F8 + 3, 0x6AF53A + 3, 0x6B0DFB + 3, 0x6B66B1 + 1, 0x6B6939 + 3, 0x71817A + 3, 0x724097 + 3, 0x75F67F + 3, 0x765232 + 3, 0x7C1417 + 3, 0x7D44C9 + 3, 0x7D7CD9 + 3, 0x7D7CE0 + 3, 0x7E6446 + 1, 0x80958C + 3, 0x80ED1B + 3, 0x80ED56 + 3, 0x810981 + 3, 0x8109A5 + 3, 0x81498C + 3, 0x815B8D + 3, 0x81D72C + 3, 0x81D75E + 3, 0x81E0C4 + 1, 0x81E421 + 1, 0x81E62C + 1, 0x81E99B + 3, 0x81E9A2 + 3, 0x822477 + 3, 0x822513 + 3, 0x83052B + 1, 0x8D302E + 3, 0x8F564C + 3, 0x92B14A + 1,
};
vector<DWORD> pnd_addr_plus4 = {
	0x40E7DC + 2, 0x5ACFC3 + 1, 0x5AD032 + 1, 0x66943F + 3, 0x66959E + 2, 0x66A136 + 2, 0x66A147 + 2, 0x718191 + 3, 0x92AE88 + 1,
};
vector<DWORD> pnd_addr_plus8 = {
	0x669187 + 1, 0x81D9D0 + 3, 0x81DA42 + 3, 0x81DCD4 + 1, 0x827494 + 1, 0x827631 + 1,
};
vector<DWORD> pnd_addr_plus12 = {
	0x669292 + 1, 0x6692F2 + 1, 0x838783 + 1, 0x92B1E9 + 2, 0x92B210 + 2,
};
vector<DWORD> pnd_addr_plus16 = {
	0x40E802 + 3, 0x49D126 + 3, 0x75F686 + 3, 0x92B1F5 + 2, 0x92B223 + 2,
};
vector<DWORD> pnd_addr_plus20 = {
	0x48DCE2 + 3, 0x48DE54 + 3, 0x48DE9A + 3, 0x48DF31 + 3, 0x48DF8A + 3, 0x5AF61A + 3, 0x669149 + 1, 0x6B68E4 + 1,
};
vector<DWORD> pnd_addr_plus21 = {
	0x412BC4 + 4, 0x5797D5 + 4, 0x5A9829 + 4, 0x5D5B2C + 1, 0x5D5BC8 + 4, 0x5DFEFE + 4, 0x63C105 + 4, 0x66E5DC + 4, 0x6848A4 + 4, 0x7935ED + 4, 0x7943C3 + 4, 0x79DC79 + 4, 0x79F445 + 4, 0x7A783F + 3, 0x7A7D7C + 3, 0x7CD749 + 4, 0x7F5F29 + 4, 0x906F29 + 4, 0x90EFF0 + 4,
};
vector<DWORD> pnd_addr_plus23 = {
	0x59B561 + 2, 0x669684 + 3, 0x669813 + 3, 0x669983 + 3, 0x77DF41 + 3, 0x861E6D + 3,
};
vector<DWORD> pnd_addr_plus27 = {
	0x904951 + 4,
};
vector<DWORD> pnd_addr_plus29 = {
	0x7A7861 + 2, 0x7A7889 + 2, 0x7A7D9E + 2, 0x7A7DC6 + 2,
};
vector<DWORD> pnd_addr_plus30 = {
	0x519965 + 3, 0x519C6D + 3, 0x90480A + 3, 0x92AEB4 + 3,
};
vector<DWORD> pnd_addr_plus34 = {
	0x904AFA + 3,
};
vector<DWORD> pnd_addr_plus42 = {
	0x4CB684 + 3, 0x4CB862 + 3, 0x59B5E0 + 2, 0x59B613 + 2, 0x5C30A0 + 2, 0x5C6CEC + 2, 0x6A89AB + 3, 0x7C64BC + 3, 0x830565 + 3, 0x8305FB + 3, 0x83F43E + 2, 0x842A1A + 3, 0x880029 + 3,
};
vector<DWORD> pnd_addr_plus44 = {
	0x4CB68D + 3, 0x4CB696 + 3, 0x4CB86B + 3, 0x4CB874 + 3, 0x59B58F + 3, 0x6A89B4 + 3, 0x6A89BD + 3, 0x7C64C5 + 3, 0x7C64CE + 3, 0x880032 + 3, 0x88003B + 3,
};
vector<DWORD> pnd_addr_plus46 = {
	0x5C30A6 + 2, 0x5C6CF2 + 2, 0x842A25 + 3,
};
vector<DWORD> pnd_addr_plus52 = {
	0x59B589 + 2,
};
vector<DWORD> pnd_addr_plus57 = {
	0x4CB6A3 + 3, 0x4CB881 + 3, 0x5C30E1 + 2, 0x5C6D1C + 2, 0x6A89C6 + 3, 0x6AA33B + 3, 0x7C64D7 + 3, 0x83F48B + 2, 0x880044 + 3, 0x923699 + 3,
};
vector<DWORD> pnd_addr_plus59 = {
	0x4CB6AC + 3, 0x4CB6B5 + 3, 0x4CB88E + 3, 0x6A89CF + 3, 0x6A89D8 + 3, 0x6AA348 + 3, 0x6AA36B + 3, 0x7C64E0 + 3, 0x7C64E9 + 3, 0x88004D + 3, 0x880056 + 3, 0x9236A6 + 3, 0x9236CF + 3,
};
vector<DWORD> pnd_addr_plus61 = {
	0x5C6D22 + 2,
};
vector<DWORD> pnd_addr_end = {
	0x6695E8 + 2, 0x669621 + 2, 0x6699F2 + 2, 0x669C1B + 1, 0x6B66D7 + 2, 0x81E0EC + 2, 0x81E449 + 2, 0x81E656 + 2, 0x830550 + 1, 0x92B16C + 1,
};
vector<DWORD> pnd_addr_endplus4 = {
	0x92AEA8 + 1,
};
vector<DWORD> pnd_addr_endplus8 = {
	0x669207 + 2, 0x81DD5C + 2, 0x82758D + 2, 0x8276D1 + 2,
};
vector<DWORD> pnd_addr_endplus12 = {
	0x6692E3 + 2, 0x669321 + 2, 0x8387B8 + 2,
};
vector<DWORD> pnd_addr_endplus20 = {
	0x66916C + 1, 0x6B68F1 + 2,
};
vector<DWORD> pnd_addr_endplus21 = {
	0x5D5B75 + 2,
};

vector<DWORD> pnd_addr_idx2 = {
	0x777667 + 1,
};

vector<DWORD> pnd_count_dword = {
	0x591FA0 + 4, 0x59202D + 4, 0x5ACFC8 + 1, 0x5AD037 + 1, 0x5C2D88 + 4, 0x5C37D7 + 4, 0x5C4839 + 4, 0x66A2AD + 1, 0x66A2DB + 1, 0x7E6457 + 4, 0x80957E + 4, 0x81497A + 4, 0x815B7B + 4,
};
vector<DWORD> pnd_count_word = {

};
vector<DWORD> pnd_count_byte = {
	0x48DCED + 2, 0x48DE31 + 2, 0x48DE86 + 2, 0x48DF10 + 2, 0x48DF7A + 2, 0x4CB666 + 1, 0x4CB844 + 1, 0x5AF60A + 2, 0x5C37C6 + 1, 0x6670BA + 1, 0x6670E5 + 1, 0x669357 + 1, 0x6693AF + 1, 0x66944C + 1, 0x669498 + 2, 0x6695A8 + 1, 0x66A0CC + 1, 0x66A0DB + 1, 0x6A898F + 1, 0x6AA32A + 1, 0x7A77DE + 1, 0x7A7D1B + 1, 0x7C64A2 + 1, 0x5D5DFB + 2, 0x6AF6F7 + 2, 0x6B0FB7 + 2, 0x75FA65 + 2, 0x765466 + 2, 0x80ED31 + 3, 0x810997 + 3, 0x81D747 + 2, 0x81DB7F + 2, 0x81E8FD + 1, 0x81EA4B + 2, 0x81EAD6 + 1, 0x8224E9 + 2, 0x822575 + 2, 0x83F426 + 1, 0x83F426 + 1, 0x88000F + 1, 0x92368C + 1,
};
vector<DWORD> pnd_countminus2_dword = {
	0x77766C + 4,
};

void league_restructure_init()
{
	if (configFile.GetBool("applyArgentina", true)) argentina_restructure();
	if (configFile.GetBool("applyAustralia", true)) australia_restructure();
	if (configFile.GetBool("applyBrazil", true)) brazil_restructure();
	if (configFile.GetBool("applyCroatia", true)) croatia_restructure();
	if (configFile.GetBool("applyDenmark", true)) denmark_restructure();
	if (configFile.GetBool("applyEngland", true)) england_restructure();
	if (configFile.GetBool("applyFinland", true)) finland_restructure();
	if (configFile.GetBool("applyFrance", true)) france_restructure();
	if (configFile.GetBool("applyGermany", true)) germany_restructure();
	if (configFile.GetBool("applyGreece", true)) greece_restructure();
	if (configFile.GetBool("applyHolland", true)) holland_restructure();
	if (configFile.GetBool("applyIreland", true)) ireland_restructure();
	if (configFile.GetBool("applyItaly", true)) italy_restructure();
	if (configFile.GetBool("applyJapan", true)) japan_restructure();
	if (configFile.GetBool("applyNorthernIreland", true)) n_ireland_restructure();
	if (configFile.GetBool("applyNorway", true)) norway_restructure();
	if (configFile.GetBool("applyPoland", true)) poland_restructure();
	if (configFile.GetBool("applyPortugal", true)) portugal_restructure();
	if (configFile.GetBool("applyScotland", true)) scotland_restructure();
	if (configFile.GetBool("applySouthKorea", true)) korea_restructure();
	if (configFile.GetBool("applySpain", true)) spain_restructure();
	if (configFile.GetBool("applySweden", true)) sweden_restructure();
	if (configFile.GetBool("applyTurkey", true)) turkey_restructure();
	if (configFile.GetBool("applyUSA", true)) usa_restructure();
	if (configFile.GetBool("applyWales", true)) wales_restructure();
}

extern "C" _declspec(naked) void inject_league_restructure_init()
{
	_asm
	{
		pushad
	}
	league_restructure_init();
	_asm
	{
		popad
		push 0x82838e
		push 0x524d70
		ret
	}
}

void setup_leagues_setup() {
	PatchFunction(0x667150, (DWORD)&replacement_667150);
	PatchFunction(0x828389, (DWORD)inject_league_restructure_init);
	// fix if Africa added
	if (configFile.GetBool("applyCAF", true)) {
		WriteBytes(0x48df27, 1, 8);
		WriteBytes(0x5accb2, 1, 9);
		WriteBytes(0x5acccf, 1, 9);
		WriteBytes(0x5accdb, 1, 8);
		WriteBytes(0x718174, 1, 8);
		WriteBytes(0x718175, 1, 0x7e);
		WriteBytes(0x72408C, 1, 6);
		WriteBytes(0x724091, 1, 8);
		WriteBytes(0x724092, 1, 0x7e);
		WriteBytes(0x8d305e, 1, 8);
		WriteBytes(0x8d305f, 1, 0x7e);
	}

	DWORD pnd_count_calc = pnd_count - !(configFile.GetBool("applyCAF", true));

	for (DWORD d : pnd_order_addr) {
		WriteDWORD(d, (DWORD)&pnd_order[0]);
	}

	for (DWORD d : pnd_addr) {
		WriteDWORD(d, (DWORD)&pnd_list[0]);
	}
	for (DWORD d : pnd_addr_plus4) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 4);
	}
	for (DWORD d : pnd_addr_plus8) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 8);
	}
	for (DWORD d : pnd_addr_plus12) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 12);
	}
	for (DWORD d : pnd_addr_plus16) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 16);
	}
	for (DWORD d : pnd_addr_plus20) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 20);
	}
	for (DWORD d : pnd_addr_plus21) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 21);
	}
	for (DWORD d : pnd_addr_plus23) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 23);
	}
	for (DWORD d : pnd_addr_plus27) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 27);
	}
	for (DWORD d : pnd_addr_plus29) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 29);
	}
	for (DWORD d : pnd_addr_plus30) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 30);
	}
	for (DWORD d : pnd_addr_plus34) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 34);
	}
	for (DWORD d : pnd_addr_plus42) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 42);
	}
	for (DWORD d : pnd_addr_plus44) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 44);
	}
	for (DWORD d : pnd_addr_plus46) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 46);
	}
	for (DWORD d : pnd_addr_plus52) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 52);
	}
	for (DWORD d : pnd_addr_plus57) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 57);
	}
	for (DWORD d : pnd_addr_plus59) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 59);
	}
	for (DWORD d : pnd_addr_plus61) {
		WriteDWORD(d, (DWORD)&pnd_list[0] + 61);
	}
	for (DWORD d : pnd_addr_end) {
		WriteDWORD(d, (DWORD)&pnd_list[pnd_count_calc - 1] + sizeof(playable_nation_data));
	}
	for (DWORD d : pnd_addr_endplus4) {
		WriteDWORD(d, (DWORD)&pnd_list[pnd_count_calc - 1] + sizeof(playable_nation_data) + 4);
	}
	for (DWORD d : pnd_addr_endplus8) {
		WriteDWORD(d, (DWORD)&pnd_list[pnd_count_calc - 1] + sizeof(playable_nation_data) + 8);
	}
	for (DWORD d : pnd_addr_endplus12) {
		WriteDWORD(d, (DWORD)&pnd_list[pnd_count_calc - 1] + sizeof(playable_nation_data) + 12);
	}
	for (DWORD d : pnd_addr_endplus20) {
		WriteDWORD(d, (DWORD)&pnd_list[pnd_count_calc - 1] + sizeof(playable_nation_data) + 20);
	}
	for (DWORD d : pnd_addr_endplus21) {
		WriteDWORD(d, (DWORD)&pnd_list[pnd_count_calc - 1] + sizeof(playable_nation_data) + 21);
	}

	for (DWORD d : pnd_addr_idx2) {
		WriteDWORD(d, (DWORD)&pnd_list[2]);
	}

	for (DWORD d : pnd_count_dword) {
		WriteDWORD(d, pnd_count_calc);
	}
	for (DWORD d : pnd_count_word) {
		WriteWORD(d, (WORD)pnd_count_calc);
	}
	for (DWORD d : pnd_count_byte) {
		WriteBytes(d, 1, (BYTE)pnd_count_calc);
	}
	for (DWORD d : pnd_countminus2_dword) {
		WriteDWORD(d, pnd_count_calc - 2);
	}

	dprintf("Added %d playable nations/continents!\n", pnd_count_calc);
}