#include <Windows.h>
#include <Structures\CMHeader.h>
#include <Helpers\generic_functions.h>
#include <Helpers\9cf_constants.h>
#include "discipline_setup.h"

void replacement_55D420(BYTE* _this, int* a2) {
	DWORD* pMem = (DWORD*)sub_945501_alloc(CompetitionRules_LENGTH, 4);
	*((DWORD*)(_this)) = (DWORD)pMem;
	int idx = 0;

	BYTE* dMem = (BYTE*)sub_944CF1_operator_new(0x23);
	if (dMem) rb_international_setup(dMem, a2);
	pMem[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x23);
	if (dMem) rb_europe_setup(dMem, a2);
	pMem[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x23);
	if (dMem) rb_south_america_setup(dMem, a2);
	pMem[idx++] = (DWORD)dMem;

	if (get_country(NATION_ARGENTINA_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_argentina_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_BELGIUM_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_belgium_league_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_belgium_cup_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_BRAZIL_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_brazil_national_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_brazil_regional_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_DENMARK_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_denmark_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_ENGLAND_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x2B);
		if (dMem) rb_england_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_FINLAND_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_finland_league_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_finland_cup_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_FRANCE_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_france_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_GERMANY_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_germany_league_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_germany_cup_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_HOLLAND_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_holland_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_IRELAND_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_ireland_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_ITALY_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_italy_league_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_italy_cup_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_JAPAN_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_japan_league_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_japan_cup_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_NORWAY_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_norway_league_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_norway_cup_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_PORTUGAL_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_portugal_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_SCOTLAND_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_scotland_league_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_scotland_cup_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_SPAIN_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_spain_league_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_spain_cup_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_SWEDEN_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_sweden_league_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_sweden_cup_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_USA_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_usa_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_POLAND_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_poland_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_GREECE_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_greece_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_CROATIA_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_croatia_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_AUSTRALIA_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_australia_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	dMem = (BYTE*)sub_944CF1_operator_new(0x23);
	if (dMem) rb_oceania_setup(dMem, a2);
	pMem[idx++] = (DWORD)dMem;

	if (get_country(NATION_NORTHERN_IRELAND_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_northern_ireland_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_TURKEY_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_turkey_league_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;

		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_turkey_cup_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
		pMem[idx++] = 0;
	}

	if (get_country(NATION_RUSSIA_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_russia_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_WALES_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_wales_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	dMem = (BYTE*)sub_944CF1_operator_new(0x23);
	if (dMem) rb_asia_setup(dMem, a2);
	pMem[idx++] = (DWORD)dMem;

	if (get_country(NATION_SOUTH_KOREA_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_south_korea_setup(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_CZECH_REPUBLIC_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_czech_init(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_AUSTRIA_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_austria_init(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_SWITZERLAND_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_switzerland_init(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_SAUDI_ARABIA_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_saudi_init(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}

	if (get_country(NATION_CHILE_9CF())->NationLeagueSelected) {
		dMem = (BYTE*)sub_944CF1_operator_new(0x23);
		if (dMem) rb_chile_init(dMem, a2);
		pMem[idx++] = (DWORD)dMem;
	}
	else
	{
		pMem[idx++] = 0;
	}
}

void __declspec(naked) replacement_55D420_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call replacement_55D420
		add esp, 0x8
		ret 4
	}
}

void __declspec(naked) rb_croatia_generic_fix()
{
	__asm
	{
		push eax
		mov eax, dword ptr ss:[esp + 0x14]
		mov al, byte ptr ds : [eax + 5]
		mov byte ptr ss : [esp + 0x30] , al
		pop eax
		push 0x7dc9c0
		ret
	}
}

void __declspec(naked) rb_croatia_generic_fix2()
{
	__asm
	{
		mov edx, dword ptr ss:[esp + 0xc]
		mov dl, byte ptr ds : [edx + 5]
		mov byte ptr ss : [esp + 0x50] , dl
		push 0x7dc8f8
		ret
	}
}

void setup_discipline_setup()
{
	PatchFunction(0x55D420, (DWORD)&replacement_55D420_c);
	WriteDWORD(0x55624c + 1, CompetitionRules_LENGTH);
	WriteDWORD(0x555f2e + 1, CompetitionRules_LENGTH);
	WriteDWORD(0x5557e6 + 1, CompetitionRules_LENGTH);

	// rb_croatia edit
	WriteBytes(0x7dcaab, 5, 0x8b, 0x46, 0x17, 0x90, 0x90);
	PatchFunction(0x7dc9bb, (DWORD)&rb_croatia_generic_fix);
	PatchFunction(0x7dc8f3, (DWORD)&rb_croatia_generic_fix2);
}
