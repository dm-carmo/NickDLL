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

static BYTE* (__thiscall* europe_rules_583280)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x583280);
static BYTE* (__thiscall* argentina_rules_40A580)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x40A580);
static BYTE* (__thiscall* australia_rules_412C80)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x412C80);
static BYTE* (__thiscall* belgium_rules_424B90)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x424B90);
static BYTE* (__thiscall* brazil_rules_43F0E0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x43F0E0);
static BYTE* (__thiscall* croatia_rules_518500)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x518500);
//static BYTE* (__thiscall* denmark_rules_555460)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x555460);
static BYTE* (__thiscall* denmark_rules_555460)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0xDE7A00);
static BYTE* (__thiscall* england_rules_579B30)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x579B30);
static BYTE* (__thiscall* finland_rules_5A9950)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x5A9950);
static BYTE* (__thiscall* france_rules_5C1570)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x5C1570);
static BYTE* (__thiscall* germany_rules_5DFF70)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x5DFF70);
static BYTE* (__thiscall* greece_rules_5ECEB0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x5ECEB0);
static BYTE* (__thiscall* holland_rules_5F9690)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x5F9690);
static BYTE* (__thiscall* ireland_rules_63C210)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x63C210);
static BYTE* (__thiscall* italy_rules_661380)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x661380);
static BYTE* (__thiscall* japan_rules_666BD0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x666BD0);
static BYTE* (__thiscall* norway_rules_7944F0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7944F0);
static BYTE* (__thiscall* n_ireland_rules_7936D0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7936D0);
static BYTE* (__thiscall* poland_rules_7CD830)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7CD830);
static BYTE* (__thiscall* portugal_rules_7D3D80)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7D3D80);
static BYTE* (__thiscall* russia_rules_7EC770)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7EC770);
static BYTE* (__thiscall* scotland_rules_7F6390)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x7F6390);
static BYTE* (__thiscall* spain_rules_859400)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x859400);
static BYTE* (__thiscall* sweden_rules_893D80)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x893D80);
static BYTE* (__thiscall* turkey_rules_9020A0)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x9020A0);
static BYTE* (__thiscall* usa_rules_90B940)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x90B940);
static BYTE* (__thiscall* wales_rules_90F080)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x90F080);
static BYTE* (__thiscall* s_korea_rules_66E630)(BYTE* _this, char a2, int a3, int a4, int a5, int a6) = (BYTE * (__thiscall*)(BYTE * _this, char a2, int a3, int a4, int a5, int a6))(0x66E630);

void replacement_8D26B0(BYTE* _this) {
	DWORD rules_count = pnd_count - 8;
	DWORD* rules_array = (DWORD*)sub_944E46_malloc(4 * rules_count);
	int idx = 0;

	BYTE* dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) europe_rules_583280(dMem, idx, -1, EUROPE_9CF(), 2, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) argentina_rules_40A580(dMem, idx, NATION_ARGENTINA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) australia_rules_412C80(dMem, idx, NATION_AUSTRALIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) belgium_rules_424B90(dMem, idx, NATION_BELGIUM_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) brazil_rules_43F0E0(dMem, idx, NATION_BRAZIL_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) croatia_rules_518500(dMem, idx, NATION_CROATIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) denmark_rules_555460(dMem, idx, NATION_DENMARK_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) england_rules_579B30(dMem, idx, NATION_ENGLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) finland_rules_5A9950(dMem, idx, NATION_FINLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) france_rules_5C1570(dMem, idx, NATION_FRANCE_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) germany_rules_5DFF70(dMem, idx, NATION_GERMANY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) greece_rules_5ECEB0(dMem, idx, NATION_GREECE_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) holland_rules_5F9690(dMem, idx, NATION_NETHERLANDS_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) ireland_rules_63C210(dMem, idx, NATION_IRELAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) italy_rules_661380(dMem, idx, NATION_ITALY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) japan_rules_666BD0(dMem, idx, NATION_JAPAN_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) norway_rules_7944F0(dMem, idx, NATION_NORWAY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) n_ireland_rules_7936D0(dMem, idx, NATION_NORTHERN_IRELAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) poland_rules_7CD830(dMem, idx, NATION_POLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) portugal_rules_7D3D80(dMem, idx, NATION_PORTUGAL_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) russia_rules_7EC770(dMem, idx, NATION_RUSSIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) scotland_rules_7F6390(dMem, idx, NATION_SCOTLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) spain_rules_859400(dMem, idx, NATION_SPAIN_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) sweden_rules_893D80(dMem, idx, NATION_SWEDEN_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) turkey_rules_9020A0(dMem, idx, NATION_TURKEY_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) usa_rules_90B940(dMem, idx, NATION_USA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) wales_rules_90F080(dMem, idx, NATION_WALES_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) s_korea_rules_66E630(dMem, idx, NATION_SOUTH_KOREA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) croatia_rules_518500(dMem, idx, NATION_CZECH_REPUBLIC_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) germany_rules_5DFF70(dMem, idx, NATION_AUSTRIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) germany_rules_5DFF70(dMem, idx, NATION_SWITZERLAND_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) russia_rules_7EC770(dMem, idx, NATION_SAUDI_ARABIA_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) argentina_rules_40A580(dMem, idx, NATION_CHILE_9CF(), -1, 1, 0);
	rules_array[idx++] = (DWORD)dMem;

	dMem = (BYTE*)sub_944CF1_operator_new(0x19);
	if (dMem) s_korea_rules_66E630(dMem, idx, NATION_EGYPT_9CF(), -1, 1, 0);
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

	// Temporary: Denmark transfer window
	WriteBytes(0xDE7A00, 280, 0x6A, 0xFF, 0x68, 0x9B, 0xC8, 0x95, 0x00, 0x64, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x50, 0x64, 0x89, 0x25, 0x00, 0x00, 0x00, 0x00, 0x81, 0xEC, 0x04, 0x02, 0x00, 0x00, 0x8B, 0x84, 0x24, 0x24, 0x02, 0x00, 0x00, 0x8B, 0x94, 0x24, 0x1C, 0x02, 0x00, 0x00, 0x53, 0x56, 0x8B, 0xF1, 0x50, 0x8B, 0x8C, 0x24, 0x2C, 0x02, 0x00, 0x00, 0x8B, 0x84, 0x24, 0x24, 0x02, 0x00, 0x00, 0x51, 0x8B, 0x8C, 0x24, 0x24, 0x02, 0x00, 0x00, 0x52, 0x50, 0x51, 0x8B, 0xCE, 0x89, 0x74, 0x24, 0x1C, 0xE8, 0x4E, 0x0A, 0xB0, 0xFF, 0x33, 0xDB, 0x6A, 0x18, 0x89, 0x9C, 0x24, 0x18, 0x02, 0x00, 0x00, 0xC7, 0x06, 0x60, 0x98, 0x96, 0x00, 0xC6, 0x46, 0x08, 0x02, 0xE8, 0xDA, 0xD3, 0xB5, 0xFF, 0x83, 0xC4, 0x04, 0x3B, 0xC3, 0x89, 0x46, 0x04, 0x75, 0x5B, 0x8D, 0x54, 0x24, 0x0C, 0x8D, 0x84, 0x24, 0x0C, 0x01, 0x00, 0x00, 0x52, 0x50, 0x53, 0x53, 0x68, 0x0C, 0xB2, 0x9E, 0x00, 0xE8, 0x70, 0xD2, 0xB5, 0xFF, 0x83, 0xC4, 0x14, 0x8D, 0x4C, 0x24, 0x0C, 0x8D, 0x94, 0x24, 0x0C, 0x01, 0x00, 0x00, 0x6A, 0x51, 0x51, 0x52, 0xE8, 0x8A, 0x56, 0xB2, 0xFF, 0x50, 0x68, 0xE8, 0x70, 0x98, 0x00, 0x68, 0xD0, 0x24, 0xAE, 0x00, 0xE8, 0xE9, 0xD1, 0xB5, 0xFF, 0x53, 0x68, 0xD0, 0x24, 0xAE, 0x00, 0x68, 0xE0, 0x70, 0x98, 0x00, 0xE8, 0xCA, 0x07, 0x80, 0xFF, 0x83, 0xC4, 0x24, 0x89, 0x1D, 0x34, 0x7A, 0xB6, 0x00, 0xEB, 0x2C, 0x6A, 0x06, 0x59, 0x89, 0x08, 0xC7, 0x40, 0x02, 0xFF, 0x01, 0x06, 0x01, 0x89, 0x48, 0x06, 0xC7, 0x40, 0x08, 0xFF, 0x1F, 0x07, 0x00, 0xB5, 0x01, 0x89, 0x48, 0x0C, 0xC7, 0x40, 0x0E, 0xFF, 0x01, 0x00, 0x01, 0x89, 0x48, 0x12, 0xC7, 0x40, 0x14, 0xFF, 0x1F, 0x00, 0x00, 0x8B, 0x8C, 0x24, 0x0C, 0x02, 0x00, 0x00, 0x8B, 0xC6, 0x5E, 0x5B, 0x64, 0x89, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x81, 0xC4, 0x10, 0x02, 0x00, 0x00, 0xC2, 0x14, 0x00);
}
