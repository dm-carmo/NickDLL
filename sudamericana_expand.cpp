#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "CMHeader.h"
#include "Helper.h"
#include "generic_functions.h"

static int(*sub_682200)() = (int(*)())(0x682200);
static int(*sub_687B10)() = (int(*)())(0x687B10);
static int(*sub_944E46)() = (int(*)())(0x944E46);
static int(*sub_4C61B0)() = (int(*)())(0x4C61B0);
static int(*sub_4C3890)() = (int(*)())(0x4C3890);
static int(*sub_944CFF)() = (int(*)())(0x944CFF); // splitpath
static int(*sub_944CF1)() = (int(*)())(0x944CF1);
static int(*sub_49EE70)() = (int(*)())(0x49EE70);
static int(*sub_90D130)() = (int(*)())(0x90D130);
static int(*sub_944C9F)() = (int(*)())(0x944C9F);
static int(*sub_5E8290)() = (int(*)())(0x5E8290);

extern "C" void sub_4c46c0();

extern "C" void __declspec(naked) sub_4c46c0() // replace 4c46c0
{
	__asm
	{
		/*004C2F50*/	push 0xFFFFFFFF
		/*004C2F52*/	push 0x956AE9
		/*004C2F57*/	mov eax, dword ptr fs : [0x0]
		/*004C2F5D*/	push eax
		/*004C2F5E*/	mov dword ptr fs : [0x0] , esp
		/*004C2F65*/	sub esp, 0x208
		/*004C2F6B*/	push ebx
		/*004C2F6C*/	push esi
		/*004C2F6D*/	mov esi, ecx
		/*004C2F6F*/	mov dword ptr ss : [esp + 0xC] , esi
		/*004C2F73*/	call sub_682200		/*call cm0102.682200*/
		/*004C2F78*/	mov ecx, dword ptr ss : [esp + 0x224]
		/*004C2F7F*/	mov ax, word ptr ss : [esp + 0x220]
		/*004C2F87*/ xor ebx, ebx
		/*004C2F89*/	mov dword ptr ds : [esi + 0x4] , ecx
		/*004C2F8C*/	push 0x1
		/*004C2F8E*/	mov ecx, esi
		/*004C2F90*/	mov dword ptr ss : [esp + 0x21C] , ebx
		/*004C2F97*/	mov dword ptr ds : [esi] , 0x968CA8
		/*004C2F9D*/	mov word ptr ds : [esi + 0x40] , ax
		/*004C2FA1*/	mov byte ptr ds : [esi + 0x50] , 0x2
		/*004C2FA5*/	mov dword ptr ds : [esi + 0xEE] , ebx
		/*004C2FAB*/	mov byte ptr ds : [esi + 0x51] , 0xF
		/*004C2FAF*/	call sub_687B10		/*call cm0102.687B10*/
		/*004C2FB4*/	test eax, eax
		/*004C2FB6*/	jne _004C30C3
		/*004C2FBC*/ or eax, 0xFFFFFFFF
		/*004C2FBF*/	push 0x20
		/*004C2FC1*/	mov word ptr ds : [esi + 0xD9] , 0x28
		/*004C2FCA*/	mov byte ptr ds : [esi + 0x44] , al
		/*004C2FCD*/	mov dword ptr ds : [esi + 0x30] , eax
		/*004C2FD0*/	mov dword ptr ds : [esi + 0x2C] , 0x8
		/*004C2FD7*/	call sub_944E46		/*call cm0102.944E46*/
		/*004C2FDC*/	add esp, 0x4
		/*004C2FDF*/	mov dword ptr ds : [esi + 0xC] , eax
		/*004C2FE2*/	//mov ecx, dword ptr ds : [0xAE1000]
		/*004C2FE8*/	//push ebx
		/*004C2FE9*/	//call sub_4C61B0		/*call cm0102.4C61B0*/
		/*004C2FEE*/	mov ecx, esi
		/*004C2FF0*/	call sub_4C3890		/*call cm0102.4C3890*/
		/*004C2FF5*/	test eax, eax
		/*004C2FF7*/	jne _004C3026
		/*004C2FF9*/	lea edx, dword ptr ss : [esp + 0x10]
		/*004C2FFD*/	lea eax, dword ptr ss : [esp + 0x110]
		/*004C3004*/	push edx
		/*004C3005*/	push eax
		/*004C3006*/	push ebx
		/*004C3007*/	push ebx
		/*004C3008*/	push 0x9A7DE4		/*push cm0102.9A7DE4*/
		/*004C300D*/	call sub_944CFF		/*call cm0102.944CFF*/
		/*004C3012*/	add esp, 0x14
		/*004C3015*/	lea ecx, dword ptr ss : [esp + 0x10]
		/*004C3019*/	lea edx, dword ptr ss : [esp + 0x110]
		/*004C3020*/	push 0x52
		/*004C3022*/	push ecx
		/*004C3023*/	push edx
		/*004C3024*/	jmp _004C3095
		_004C3026 :
		/*004C3026*/	push 0x5CE
			/*004C302B*/	mov word ptr ds : [esi + 0x3E] , bx
			/*004C302F*/	mov dword ptr ds : [esi + 0xB1] , ebx
			/*004C3035*/	mov dword ptr ds : [esi + 0x45] , ebx
			/*004C3038*/	call sub_944CF1		/*call cm0102.944CF1*/
			/*004C303D*/	add esp, 0x4
			/*004C3040*/	mov dword ptr ss : [esp + 0x8] , eax
			/*004C3044*/	cmp eax, ebx
			/*004C3046*/	mov byte ptr ss : [esp + 0x218] , 0x1
			/*004C304E*/	je _004C305A
			/*004C3050*/	push esi
			/*004C3051*/	mov ecx, eax
			/*004C3053*/	call sub_49EE70		/*call cm0102.49EE70*/
			/*004C3058*/	jmp _004C305C
			_004C305A :
		/*004C305A*/ xor eax, eax
			_004C305C :
		/*004C305C*/	cmp eax, ebx
			/*004C305E*/	mov byte ptr ss : [esp + 0x218] , bl
			/*004C3065*/	mov dword ptr ds : [esi + 0x8] , eax
			/*004C3068*/	jne _004C30C3
			/*004C306A*/	lea eax, dword ptr ss : [esp + 0x110]
			/*004C3071*/	lea ecx, dword ptr ss : [esp + 0x10]
			/*004C3075*/	push eax
			/*004C3076*/	push ecx
			/*004C3077*/	push ebx
			/*004C3078*/	push ebx
			/*004C3079*/	push 0x9A7DE4		/*push cm0102.9A7DE4*/
			/*004C307E*/	call sub_944CFF		/*call cm0102.944CFF*/
			/*004C3083*/	add esp, 0x14
			/*004C3086*/	lea edx, dword ptr ss : [esp + 0x110]
			/*004C308D*/	lea eax, dword ptr ss : [esp + 0x10]
			/*004C3091*/	push 0x60
			/*004C3093*/	push edx
			/*004C3094*/	push eax
			_004C3095 :
		/*004C3095*/	call sub_90D130		/*call cm0102.90D130*/
			/*004C309A*/	push eax
			/*004C309B*/	push 0x9870E8		/*push cm0102.9870E8*/
			/*004C30A0*/	push 0xAE24D0		/*push cm0102.AE24D0*/
			/*004C30A5*/	call sub_944C9F		/*call cm0102.944C9F*/
			/*004C30AA*/	push ebx
			/*004C30AB*/	push 0xAE24D0		/*push cm0102.AE24D0*/
			/*004C30B0*/	push 0x9870E0		/*push cm0102.9870E0*/
			/*004C30B5*/	call sub_5E8290		/*call cm0102.5E8290*/
			/*004C30BA*/	add esp, 0x24
			/*004C30BD*/	mov dword ptr ds : [0xB67A34] , ebx
			_004C30C3 :
		/*004C30C3*/	mov ecx, dword ptr ss : [esp + 0x210]
			/*004C30CA*/	mov eax, esi
			/*004C30CC*/	pop esi
			/*004C30CD*/	pop ebx
			/*004C30CE*/	mov dword ptr fs : [0x0] , ecx
			/*004C30D5*/	add esp, 0x214
			/*004C30DB*/	ret 0x8
	}
}

void setup_sudamericana_expand() {
	PatchFunction(0x4c46c0, (DWORD)&sub_4c46c0);
	WriteFuncPtr(0x968ca8, 11, 0x4c3a80);
	WriteFuncPtr(0x968ca8, 13, 0x637750);
	WriteFuncPtr(0x968ca8, 16, 0x4c31c0);
	WriteFuncPtr(0x968ca8, 18, 0x4c4080);
	WriteFuncPtr(0x968ca8, 19, 0x4c3680);
	WriteFuncPtr(0x968ca8, 24, 0x4c4210);
	WriteFuncPtr(0x968ca8, 27, 0x4c4610);
	WriteFuncPtr(0x968ca8, 36, 0x4c3890);
	WriteBytes(0x4c5864, 1, 0x20);
	WriteBytes(0x4c5e8e, 1, 0x7);
}