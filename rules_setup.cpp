#include <Windows.h>
#include <Structures/CMHeader.h>
#include "Helpers/generic_functions.h"
#include <Helpers/9cf_constants.h>
#include "rules_setup.h"

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

static BYTE* (__thiscall* sub_583280)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x583280);
static BYTE* (__thiscall* sub_40A580)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x40A580);
static BYTE* (__thiscall* sub_412C80)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x412C80);
static BYTE* (__thiscall* sub_424B90)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x424B90);
static BYTE* (__thiscall* sub_43F0E0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x43F0E0);
static BYTE* (__thiscall* sub_518500)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x518500);
static BYTE* (__thiscall* sub_555460)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x555460);
static BYTE* (__thiscall* sub_579B30)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x579B30);
static BYTE* (__thiscall* sub_5A9950)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x5A9950);
static BYTE* (__thiscall* sub_5C1570)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x5C1570);
static BYTE* (__thiscall* sub_5DFF70)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x5DFF70);
static BYTE* (__thiscall* sub_5ECEB0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x5ECEB0);
static BYTE* (__thiscall* sub_5F9690)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x5F9690);
static BYTE* (__thiscall* sub_63C210)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x63C210);
static BYTE* (__thiscall* sub_661380)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x661380);
static BYTE* (__thiscall* sub_666BD0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x666BD0);
static BYTE* (__thiscall* sub_7944F0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7944F0);
static BYTE* (__thiscall* sub_7936D0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7936D0);
static BYTE* (__thiscall* sub_7CD830)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7CD830);
static BYTE* (__thiscall* sub_7D3D80)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7D3D80);
static BYTE* (__thiscall* sub_7EC770)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7EC770);
static BYTE* (__thiscall* sub_7F6390)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7F6390);
static BYTE* (__thiscall* sub_859400)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x859400);
static BYTE* (__thiscall* sub_893D80)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x893D80);
static BYTE* (__thiscall* sub_9020A0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x9020A0);
static BYTE* (__thiscall* sub_90B940)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x90B940);
static BYTE* (__thiscall* sub_90F080)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x90F080);
static BYTE* (__thiscall* sub_66E630)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x66E630);

void replacement_8D26B0(BYTE* _this) {
	DWORD rules_count = pnd_count - 8;
	DWORD* rules_array = (DWORD*)sub_944E46_malloc(4 * rules_count);
	int idx = 0;

	BYTE* dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_583280(dMem, idx, -1, EUROPE_9CF(), 2, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_40A580(dMem, idx, NATION_ARGENTINA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_412C80(dMem, idx, NATION_AUSTRALIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_424B90(dMem, idx, NATION_BELGIUM_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_43F0E0(dMem, idx, NATION_BRAZIL_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_518500(dMem, idx, NATION_CROATIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_555460(dMem, idx, NATION_DENMARK_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_579B30(dMem, idx, NATION_ENGLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_5A9950(dMem, idx, NATION_FINLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_5C1570(dMem, idx, NATION_FRANCE_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_5DFF70(dMem, idx, NATION_GERMANY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_5ECEB0(dMem, idx, NATION_GREECE_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_5F9690(dMem, idx, NATION_HOLLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_63C210(dMem, idx, NATION_IRELAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_661380(dMem, idx, NATION_ITALY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_666BD0(dMem, idx, NATION_JAPAN_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_7944F0(dMem, idx, NATION_NORWAY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_7936D0(dMem, idx, NATION_NORTHERN_IRELAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_7CD830(dMem, idx, NATION_POLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_7D3D80(dMem, idx, NATION_PORTUGAL_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_7EC770(dMem, idx, NATION_RUSSIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_7F6390(dMem, idx, NATION_SCOTLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_859400(dMem, idx, NATION_SPAIN_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_893D80(dMem, idx, NATION_SWEDEN_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_9020A0(dMem, idx, NATION_TURKEY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_90B940(dMem, idx, NATION_USA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_90F080(dMem, idx, NATION_WALES_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_66E630(dMem, idx, NATION_SOUTH_KOREA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_518500(dMem, idx, NATION_CZECH_REPUBLIC_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sub_518500(dMem, idx, NATION_AUSTRIA_9CF(), -1, 1, 0);
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

	DWORD* pMem = (DWORD*)sub_944E46_malloc(4 * unknown_8a8);
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
	*((DWORD*)(_this + 0x8a4)) = (DWORD)pMem;

	qsort(pMem, unknown_8a8, 4, sub_8E5590);
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
