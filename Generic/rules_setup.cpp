#include <Windows.h>
#include "Structures\CMHeader.h"
#include "Helpers/generic_functions.h"
#include "Helpers\9cf_constants.h"
#include "rules_setup.h"

/*
* Pointers for foreign player rules (match):
* +0x00 -> max foreign players (Croatia + South Korea?)
* +0x01 -> max foreign players (doesn't show symbol in squad?)
* +0x02 -> max foreign players
* +0x03 -> max non-EU players (Portugal?)
* +0x04 -> max non-EU players (doesn't show symbol in squad?)
* +0x05 -> max non-EU players
* +0x16 -> max age for restriction below
* +0x17 -> max over-age players
* 
* Pointers for foreign player rules (club):
* +0x12 -> max non-EU players, doesn't work? might be +0x14 instead but that doesn't work either
* +0x13 -> max foreign players
*/

vector<DWORD> rules_lea_mov_addr = {
	0x8bbf60,0x8c2424,0x8c263a,0x8c4e2d,0x8c5b19,0x8c942c,0x8cf284,0x8cf304,0x8cf4ca,0x8cf646,0x8cf6fb,0x8d054e,
};

vector<DWORD> rules_count_dword_arr = {
	0x8bbf66,0x8c5b1f,
};

vector<DWORD> rules_count_byte_arr_plus2 = {
	0x8c243a,0x8c2650,0x8c4e3f,0x8c9444,0x8cf299,0x8cf679,0x8cf730,0x8d055f,0x8cc67a,0x8d037a,0x8d0396,0x8d05b8,
};

vector<DWORD> rules_count_byte_arr_plus1 = {
	0x8cffe8,0x8cf4dc,0x8cf31d,0x8cf345,0x8ced63,0x8cc69f,
};

static int(*sub_8E5590)(const void* a1, const void* a2) = (int(*)(const void* a1, const void* a2))(0x8E5590);

static BYTE* (__thiscall* europe_rules_583280)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x583280);

void replacement_8D26B0(BYTE* _this) {
	DWORD rules_count = pnd_count - 8;
	DWORD* rules_array = (DWORD*)cm0102_malloc(4 * rules_count);
	int idx = 0;

	BYTE* dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) europe_rules_583280(dMem, idx, -1, EUROPE_9CF(), 2, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_argentina_rules(dMem, idx, NATION_ARGENTINA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_australia_rules(dMem, idx, NATION_AUSTRALIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_belgium_rules(dMem, idx, NATION_BELGIUM_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_brazil_rules(dMem, idx, NATION_BRAZIL_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_croatia_rules(dMem, idx, NATION_CROATIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_denmark_rules(dMem, idx, NATION_DENMARK_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_england_rules(dMem, idx, NATION_ENGLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_finland_rules(dMem, idx, NATION_FINLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_france_rules(dMem, idx, NATION_FRANCE_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_germany_rules(dMem, idx, NATION_GERMANY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_greece_rules(dMem, idx, NATION_GREECE_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_holland_rules(dMem, idx, NATION_NETHERLANDS_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_ireland_rules(dMem, idx, NATION_IRELAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_italy_rules(dMem, idx, NATION_ITALY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_japan_rules(dMem, idx, NATION_JAPAN_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_norway_rules(dMem, idx, NATION_NORWAY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_n_ireland_rules(dMem, idx, NATION_NORTHERN_IRELAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_poland_rules(dMem, idx, NATION_POLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_portugal_rules(dMem, idx, NATION_PORTUGAL_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_russia_rules(dMem, idx, NATION_RUSSIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_scotland_rules(dMem, idx, NATION_SCOTLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_spain_rules(dMem, idx, NATION_SPAIN_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_sweden_rules(dMem, idx, NATION_SWEDEN_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_turkey_rules(dMem, idx, NATION_TURKEY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_usa_rules(dMem, idx, NATION_USA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_wales_rules(dMem, idx, NATION_WALES_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_korea_rules(dMem, idx, NATION_SOUTH_KOREA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_czech_rules(dMem, idx, NATION_CZECH_REPUBLIC_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_austria_rules(dMem, idx, NATION_AUSTRIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_switzerland_rules(dMem, idx, NATION_SWITZERLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_saudi_rules(dMem, idx, NATION_SAUDI_ARABIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_chile_rules(dMem, idx, NATION_CHILE_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_egypt_rules(dMem, idx, NATION_EGYPT_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_serbia_rules(dMem, idx, NATION_SERBIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)cm0102_new(0x19);
	if (dMem) setup_iran_rules(dMem, idx, NATION_IRAN_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	*((DWORD*)(_this + 0x8ac)) = (DWORD)rules_array;

	DWORD unknown_8a8 = 0;
	for (DWORD i = 0; i < rules_count; i++) {
		DWORD tmp = rules_array[i];
		if (tmp) {
			BYTE tmp2 = *((BYTE*)(tmp + 0x8));
			tmp2 *= 2;
			unknown_8a8 += tmp2;
		}
	}
	*((DWORD*)(_this + 0x8a8)) = unknown_8a8;

	DWORD* pMem = (DWORD*)cm0102_malloc(4 * unknown_8a8);
	DWORD b = 0;
	for (DWORD i = 0; i < rules_count; i++) {
		DWORD tmp = rules_array[i];
		if (tmp) {
			BYTE tmp2 = *((BYTE*)(tmp + 0x8));
			for (BYTE j = 0; j < tmp2; j++) {
				DWORD tmp3 = *((DWORD*)(tmp + 0x4));
				pMem[b] = tmp3 + 12 * j;
				b++;
				pMem[b] = tmp3 + 12 * j + 6;
				b++;
			}
		}
	}

	qsort(pMem, unknown_8a8, 4, sub_8E5590);
	*((DWORD*)(_this + 0x8a4)) = (DWORD)pMem;
}

void __declspec(naked) replacement_8D26B0_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call replacement_8D26B0
		add esp, 0x4
		ret
	}
}

void __declspec(naked) jmp_8C6D1C()
{
	__asm
	{
		mov ebx, dword ptr ss : [ebp + 0x8ac]
		mov ecx, dword ptr ds : [ebx + ecx * 4]
		push 0x8c6d23
		ret
	}
}

void __declspec(naked) jmp_8C6D37()
{
	__asm
	{
		mov ebx, dword ptr ss : [ebp + 0x8ac]
		mov ecx, dword ptr ds : [ebx + ecx * 4]
		push 0x8c6d3e
		ret
	}
}

void __declspec(naked) jmp_8C6D48()
{
	__asm
	{
		mov ecx, dword ptr ss : [ebp + 0x8ac]
		mov ecx, dword ptr ds : [ecx + eax * 4]
		push 0x8c6d4f
		ret
	}
}

void __declspec(naked) jmp_8C6D68()
{
	__asm
	{
		mov ebx, dword ptr ss : [ebp + 0x8ac]
		mov ecx, dword ptr ds : [ebx + ecx * 4]
		push 0x8c6d6f
		ret
	}
}

void __declspec(naked) jmp_8E05B5()
{
	__asm
	{
		mov ecx, dword ptr ds : [esi + 0x8ac]
		mov ecx, dword ptr ds : [ecx + eax * 4]
		push 0x8e05bc
		ret
	}
}

void setup_rules_setup()
{
	PatchFunction(0x8D26B0, (DWORD)&replacement_8D26B0_c);
	PatchFunction(0x8C6D1C, (DWORD)&jmp_8C6D1C);
	PatchFunction(0x8C6D37, (DWORD)&jmp_8C6D37);
	PatchFunction(0x8C6D48, (DWORD)&jmp_8C6D48);
	PatchFunction(0x8C6D68, (DWORD)&jmp_8C6D68);
	PatchFunction(0x8E05B5, (DWORD)&jmp_8E05B5);

	DWORD rules_count = pnd_count - 8;

	for (DWORD d : rules_lea_mov_addr) {
		WriteBytes(d, 1, 0x8b);
	}

	WriteBytes(0x8cc662, 2, 0x8b, 0xb6);
	WriteBytes(0x8ced4d, 2, 0x8b, 0x89);
	WriteBytes(0x8cffd2, 2, 0x8b, 0xad);
	WriteBytes(0x8d0366, 2, 0x8b, 0xb6);
	WriteBytes(0x8d0595, 2, 0x8b, 0x89);

	for (DWORD d : rules_count_dword_arr) {
		WriteDWORD(d + 1, rules_count);
	}

	for (DWORD d : rules_count_byte_arr_plus2) {
		WriteBytes(d + 2, 1, (BYTE)rules_count);
	}

	for (DWORD d : rules_count_byte_arr_plus1) {
		WriteBytes(d + 1, 1, (BYTE)rules_count);
	}
}
