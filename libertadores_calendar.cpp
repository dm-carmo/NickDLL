#include "Helper.h"
#include "generic_functions.h"

static int(*sub_68A160)() = (int(*)())(0x68A160);
static int(*sub_68A1C0)() = (int(*)())(0x68A1C0);
static int(*sub_90D130)() = (int(*)())(0x90D130);
static int(*sub_5E8290)() = (int(*)())(0x5E8290);
static int(*sub_521E60)() = (int(*)())(0x521E60);
static int(*sub_521EB0)() = (int(*)())(0x521EB0);

extern "C" void sub_4C31C0();

extern "C" void __declspec(naked) sub_4C31C0()
{
	__asm
	{
		mov al, byte ptr ss : [esp + 0x4]
		sub esp, 0x200
		cmp al, 0x7
		push ebx
		push ebp
		push esi
		push edi
		mov edi, ecx
		jge knockout_calendar
		mov ecx, dword ptr ss : [esp + 0x220]
		xor ebx, ebx
		cmp ecx, ebx
		je ecx_null
		mov dword ptr ds : [ecx] , 0x1
		ecx_null :
		mov ecx, dword ptr ss : [esp + 0x218]
		push 0x186
		movsx dx, al
		mov eax, dword ptr ss : [esp + 0x220]
		add edx, 0x3E9
		mov word ptr ds : [ecx] , 0x6
		mov word ptr ds : [eax] , dx
		call sub_944E46_malloc		/*call cm0102.944E46*/
		mov esi, eax
		add esp, 0x4
		cmp esi, ebx
		jne malloc_success_1
		lea ecx, dword ptr ss : [esp + 0x10]
		lea edx, dword ptr ss : [esp + 0x110]
		push ecx
		push edx
		push ebx
		push ebx
		push 0x9A7DE4		/*push cm0102.9A7DE4*/
		call sub_944CFF_splitpath		/*call cm0102.944CFF*/
		add esp, 0x14
		lea eax, dword ptr ss : [esp + 0x10]
		lea ecx, dword ptr ss : [esp + 0x110]
		push 0x9F
		push eax
		jmp error_handling
		malloc_success_1 :
		mov dx, word ptr ds : [edi + 0x40]
			push ebx
			push edx
			push 0x2
			push 0x2
			push ebx
			push 0x3
			push 0x2
			push ebx
			push esi
			call sub_68A160		/*call cm0102.68A160*/
			push ebx
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push ebx
			push ebx
			push esi
			call sub_68A1C0		/*call cm0102.68A1C0*/
			mov ax, word ptr ds : [edi + 0x40]
			add esp, 0x40
			mov ebp, 0x4
			push ebx
			push eax
			push 0x2
			push 0x2
			push ebx
			push 0x3
			push 0x9
			push 0x1
			push esi
			call sub_68A160		/*call cm0102.68A160*/
			push ebx
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push ebx
			push 0x1
			push esi
			call sub_68A1C0		/*call cm0102.68A1C0*/
			mov cx, word ptr ds : [edi + 0x40]
			add esp, 0x40
			push ebx
			push ecx
			push 0x2
			push 0x2
			push ebx
			push 0x3
			push 0x17
			push 0x2
			push esi
			call sub_68A160		/*call cm0102.68A160*/
			push ebx
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push ebx
			push 0x2
			push esi
			call sub_68A1C0		/*call cm0102.68A1C0*/
			mov dx, word ptr ds : [edi + 0x40]
			add esp, 0x40
			push ebx
			push edx
			push 0x2
			push 0x2
			push ebx
			push 0x4
			push 0x7
			push 0x3
			push esi
			call sub_68A160		/*call cm0102.68A160*/
			push ebx
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push ebx
			push 0x3
			push esi
			call sub_68A1C0		/*call cm0102.68A1C0*/
			add esp, 0x40
			mov ax, word ptr ds : [edi + 0x40]
			push ebx
			push eax
			push 0x2
			push 0x2
			push ebx
			push 0x4
			push 0xE
			push ebp
			push esi
			call sub_68A160		/*call cm0102.68A160*/
			push ebx
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push ebx
			push ebp
			push esi
			call sub_68A1C0		/*call cm0102.68A1C0*/
			mov cx, word ptr ds : [edi + 0x40]
			add esp, 0x40
			push ebx
			push ecx
			push 0x2
			push 0x2
			push ebx
			push 0x4
			push 0x1C
			push 0x5
			push esi
			call sub_68A160		/*call cm0102.68A160*/
			push ebx
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push 0xFFFFFFFF
			push ebx
			push 0x5
			push esi
			call sub_68A1C0		/*call cm0102.68A1C0*/
			add esp, 0x40
			mov eax, esi
			pop edi
			pop esi
			pop ebp
			pop ebx
			add esp, 0x200
			ret 0x10
			knockout_calendar:
		jne end_of_stages
			mov eax, dword ptr ss : [esp + 0x220]
			xor ebx, ebx
			cmp eax, ebx
			je eax_null
			mov dword ptr ds : [eax] , ebx
			eax_null :
		mov edx, dword ptr ss : [esp + 0x218]
			mov eax, dword ptr ss : [esp + 0x21C]
			mov ebp, 0x4
			push 0x1A0
			mov word ptr ds : [edx] , bp
			mov word ptr ds : [eax] , bx
			call sub_944E46_malloc		/*call cm0102.944E46*/
			mov esi, eax
			add esp, 0x4
			cmp esi, ebx
			jne malloc_success_2
			lea ecx, dword ptr ss : [esp + 0x110]
			lea edx, dword ptr ss : [esp + 0x10]
			push ecx
			push edx
			push ebx
			push ebx
			push 0x9A7DE4		/*push cm0102.9A7DE4*/
			call sub_944CFF_splitpath		/*call cm0102.944CFF*/
			add esp, 0x14
			lea eax, dword ptr ss : [esp + 0x110]
			lea ecx, dword ptr ss : [esp + 0x10]
			push 0xC5
			push eax
			error_handling :
		push ecx
			call sub_90D130		/*call cm0102.90D130*/
			push eax
			push 0x9870E8		/*push cm0102.9870E8*/
			push 0xAE24D0		/*push cm0102.AE24D0*/
			call sub_944C9F_sprintf		/*call cm0102.944C9F*/
			push ebx
			push 0xAE24D0		/*push cm0102.AE24D0*/
			push 0x9870E0		/*push cm0102.9870E0*/
			call sub_5E8290		/*call cm0102.5E8290*/
			add esp, 0x24
			mov dword ptr ds : [0xB67A34] , ebx
			end_of_stages :
		pop edi
			pop esi
			pop ebp
			xor eax, eax
			pop ebx
			add esp, 0x200
			ret 0x10
			malloc_success_2:
		movsx edx, word ptr ds : [edi + 0x40]
			push edx
			push 0x3
			push ebx
			push 0x4
			push 0x1D
			push ebx
			push esi
			call sub_521E60		/*call cm0102.521E60*/
			movsx eax, word ptr ds : [edi + 0x40]
			push ebx
			push eax
			push 0x2
			push 0x2
			push ebx
			push 0x7
			push 0xD
			push ebx
			push esi
			call sub_521EB0		/*call cm0102.521EB0*/
			mov word ptr ds : [esi + 0x7] , 0x6E
			mov word ptr ds : [esi + 0x9] , bx
			mov word ptr ds : [esi + 0xB] , bx
			mov word ptr ds : [esi + 0xD] , bx
			mov eax, 0x10
			mov byte ptr ds : [esi + 0x17] , 0x7
			mov word ptr ds : [esi + 0x18] , ax
			mov word ptr ds : [esi + 0x1A] , 0x8
			mov word ptr ds : [esi + 0x1C] , ax
			mov word ptr ds : [esi + 0xF] , 0x1
			mov word ptr ds : [esi + 0x1E] , bx
			mov byte ptr ds : [esi + 0x20] , bl
			mov byte ptr ds : [esi + 0x21] , 0x2
			mov byte ptr ds : [esi + 0x22] , 0x7
			mov dword ptr ds : [esi + 0x5C] , ebx
			mov dword ptr ds : [esi + 0x60] , 0xFFFFFFFF
			mov dword ptr ds : [esi + 0x64] , ebx
			add esp, 0x40
			movsx ecx, word ptr ds : [edi + 0x40]
			push ecx
			push 0x3
			push ebx
			push 0x7
			push 0x15
			push 0x1
			push esi
			call sub_521E60		/*call cm0102.521E60*/
			movsx edx, word ptr ds : [edi + 0x40]
			push ebx
			push edx
			push 0x2
			push 0x2
			push ebx
			push 0x8
			push 0x11
			push 0x1
			push esi
			call sub_521EB0		/*call cm0102.521EB0*/
			mov eax, 0x1
			mov word ptr ds : [esi + 0x6F] , 0x78
			mov word ptr ds : [esi + 0x71] , ax
			mov word ptr ds : [esi + 0x73] , bx
			mov word ptr ds : [esi + 0x75] , bx
			mov byte ptr ds : [esi + 0x7F] , 0x8
			mov word ptr ds : [esi + 0x80] , 0x8
			mov word ptr ds : [esi + 0x82] , bp
			mov word ptr ds : [esi + 0x84] , bx
			mov word ptr ds : [esi + 0x77] , ax
			mov word ptr ds : [esi + 0x86] , bx
			mov byte ptr ds : [esi + 0x88] , bl
			mov byte ptr ds : [esi + 0x89] , 0x2
			mov byte ptr ds : [esi + 0x8A] , 0x7
			mov dword ptr ds : [esi + 0xC4] , ebx
			mov dword ptr ds : [esi + 0xC8] , 0xFFFFFFFF
			mov dword ptr ds : [esi + 0xCC] , ebx
			add esp, 0x40
			movsx eax, word ptr ds : [edi + 0x40]
			push eax
			push 0x3
			push ebx
			push 0x8
			push 0x19
			push 0x2
			push esi
			call sub_521E60		/*call cm0102.521E60*/
			movsx ecx, word ptr ds : [edi + 0x40]
			push ebx
			push ecx
			push 0x2
			push 0x2
			push ebx
			push 0x9
			push 0x16
			push 0x2
			push esi
			call sub_521EB0		/*call cm0102.521EB0*/
			mov eax, 0x2
			mov word ptr ds : [esi + 0xD7] , 0x82
			mov word ptr ds : [esi + 0xD9] , ax
			mov word ptr ds : [esi + 0xDB] , bx
			mov word ptr ds : [esi + 0xDD] , bx
			mov byte ptr ds : [esi + 0xE7] , 0x8
			mov word ptr ds : [esi + 0xE8] , bp
			mov word ptr ds : [esi + 0xEA] , ax
			mov word ptr ds : [esi + 0xEC] , bx
			mov word ptr ds : [esi + 0xDF] , 0x1
			mov word ptr ds : [esi + 0xEE] , bx
			mov byte ptr ds : [esi + 0xF0] , bl
			mov byte ptr ds : [esi + 0xF1] , al
			mov byte ptr ds : [esi + 0xF2] , 0x7
			mov dword ptr ds : [esi + 0x12C] , ebx
			mov dword ptr ds : [esi + 0x130] , 0xFFFFFFFF
			mov dword ptr ds : [esi + 0x134] , ebx
			add esp, 0x40
			movsx edx, word ptr ds : [edi + 0x40]
			push edx
			push 0x3
			push ebx
			push 0x9
			push 0x1D
			push 0x3
			push esi
			call sub_521E60		/*call cm0102.521E60*/
			movsx eax, word ptr ds : [edi + 0x40]
			push 0x4
			push eax
			push 0x1
			push 0x5
			push ebx
			push 0xA
			push 0x1D
			push 0x3
			push esi
			call sub_521EB0		/*call cm0102.521EB0*/
			add esp, 0x40
			mov eax, 0x1
			mov word ptr ds : [esi + 0x152] , ax
			mov word ptr ds : [esi + 0x147] , bx
			mov dword ptr ds : [esi + 0x13F] , 0x96
			mov word ptr ds : [esi + 0x141] , 3
			mov word ptr ds : [esi + 0x143] , bx
			mov word ptr ds : [esi + 0x145] , 0x3
			mov byte ptr ds : [esi + 0x14F] , 0x8
			mov word ptr ds : [esi + 0x150] , 0x2
			mov word ptr ds : [esi + 0x154] , bx
			mov word ptr ds : [esi + 0x156] , bx
			mov byte ptr ds : [esi + 0x158] , bl
			mov byte ptr ds : [esi + 0x159] , 0x1
			mov byte ptr ds : [esi + 0x15A] , 0x7
			mov dword ptr ds : [esi + 0x194] , ebx
			mov dword ptr ds : [esi + 0x198] , 0x1E8480
			mov dword ptr ds : [esi + 0x19C] , 0xC3500
			mov eax, esi
			pop edi
			pop esi
			pop ebp
			pop ebx
			add esp, 0x200
			ret 0x10
	}
}

void setup_libertadores_calendar()
{
	PatchFunction(0x4c31c0, (DWORD)&sub_4C31C0);
	// Recopa calendar
	WriteBytes(0x6323ff, 1, 0x0);
	WriteBytes(0x632401, 1, 0x19);
	WriteBytes(0x632415, 3, 0x6a, 0x03, 0x53);
	WriteBytes(0x632419, 1, 0x1);
	WriteBytes(0x63241b, 1, 0x14);
	WriteBytes(0x63245e, 1, 0x7);
}