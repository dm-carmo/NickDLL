#include <Windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\Helper.h"

static int(*sub_543540)() = (int(*)())(0x543540);
static int(*sub_6020A0)() = (int(*)())(0x6020A0);
static int(*sub_90CFC0)() = (int(*)())(0x90CFC0);
static int(*sub_9452CA)() = (int(*)())(0x9452CA);
static int(*sub_6830B0)() = (int(*)())(0x6830B0);
static int(*sub_6831A0)() = (int(*)())(0x6831A0);
static int(*sub_944E46)() = (int(*)())(0x944E46);
static int(*sub_945333)() = (int(*)())(0x945333);
static int(*sub_944CF1)() = (int(*)())(0x944CF1);

void sub_601C2C();
void sub_601B7A();
void sub_601A58();
void sub_602060();
void sub_602148();
void sub_602E38();
void sub_7EBE50();
void sub_601C1A();

void __declspec(naked) sub_601FF0()
{
	__asm
	{
	/*00601FF0*/	pushad
	/*00601FF1*/	movzx ecx,byte ptr ds:[esi+0xC1]
	/*00601FF8*/	jecxz _00602056
	/*00601FFA*/	movzx ebx,word ptr ds:[esi+0x3E]
	/*00601FFE*/	dec ebx
	/*00601FFF*/	jl _00602056
	/*00602001*/	xchg ecx,eax
	/*00602002*/	mov ecx,dword ptr ds:[esi+0x4]
	/*00602005*/	jecxz _00602056
	/*00602007*/	mov ecx,dword ptr ds:[ecx+0x5D]
	/*0060200D*/	jecxz _00602056
	/*0060200F*/	push dword ptr ds:[ecx]
	/*00602011*/	xchg ecx,eax
	/*00602012*/	call sub_7EBE50		/*call <cm0102.sub_7EBE50>*/
	/*00602017*/	test eax,eax
	/*00602019*/	je _00602056
	/*0060201B*/	push eax
	/*0060201C*/	push 0x3
	/*0060201E*/	call sub_90CFC0		/*call <cm0102.sub_90CFC0>*/
	/*00602023*/	test eax,eax
	/*00602025*/	pop eax
	/*00602026*/	pop eax
	/*00602027*/	push eax
	/*00602028*/	jne _00602031
	/*0060202A*/	call sub_6020A0		/*call <cm0102.sub_6020A0>*/
	/*0060202F*/	jmp _00602036
_00602031:
	/*00602031*/	call sub_602060		/*call cm0102.602060*/
_00602036:
	/*00602036*/	imul ebx,ebx,0x3B
	/*00602039*/	add ebx,dword ptr ds:[esi+0xB1]
_0060203F:
	/*0060203F*/	push dword ptr ds:[eax]
	/*00602041*/	push dword ptr ds:[ebx]
	/*00602043*/	call sub_602148		/*call <cm0102.sub_602148>*/
	/*00602048*/	add eax,0x6
	/*0060204B*/	sub ebx,0x3B
	/*0060204E*/	loop _0060203F
	/*00602050*/	call sub_9452CA		/*call <cm0102.sub_9452CA>*/
	/*00602055*/	pop eax
_00602056:
	/*00602056*/	popad
	/*00602057*/	ret
	}
}

void __declspec(naked) sub_602060()
{
	__asm
	{
	/*00602060*/	pushad
	/*00602061*/	xor ebp,ebp
	/*00602063*/	movzx ecx,byte ptr ds:[esi+0x3E]
	/*00602067*/	xchg esi,eax
	/*00602068*/	mov edi,esi
_0060206A:
	/*0060206A*/	lodsd
	/*0060206B*/	test eax,eax
	/*0060206D*/	je _00602074
	/*0060206F*/	lodsw
	/*00602071*/	cwde
	/*00602072*/	add ebp,eax
_00602074:
	/*00602074*/	loop _0060206A
_00602076:
	/*00602076*/	mov esi,edi
	/*00602078*/	push ebp
	/*00602079*/	call sub_90CFC0		/*call <cm0102.sub_90CFC0>*/
	/*0060207E*/	xchg edx,eax
	/*0060207F*/	pop eax
_00602080:
	/*00602080*/	lodsd
	/*00602081*/	xchg ebx,eax
	/*00602082*/	lodsw
	/*00602084*/	cwde
	/*00602085*/	sub edx,eax
	/*00602087*/	jg _00602080
	/*00602089*/	xchg dword ptr ds:[edi],ebx
	/*0060208B*/	xchg word ptr ds:[edi+0x4],ax
	/*0060208F*/	mov dword ptr ds:[esi-0x6],ebx
	/*00602092*/	xchg word ptr ds:[esi-0x2],ax
	/*00602096*/	cwde
	/*00602097*/	add edi,0x6
	/*0060209A*/	sub ebp,eax
	/*0060209C*/	jg _00602076
	/*0060209E*/	popad
	/*0060209F*/	nop
	/*006020A0*/	pushad
	/*006020A1*/	xor edx,edx
	/*006020A3*/	movzx ecx,byte ptr ds:[esi+0x3E]
	/*006020A7*/	xchg esi,eax
_006020A8:
	/*006020A8*/	inc edx
	/*006020A9*/	lodsd
	/*006020AA*/	test eax,eax
	/*006020AC*/	je _006020B5
	/*006020AE*/	mov byte ptr ds:[eax+0x5F],dl
	/*006020B1*/	inc esi
	/*006020B2*/	inc esi
	/*006020B3*/	loop _006020A8
_006020B5:
	/*006020B5*/	popad
	/*006020B6*/	ret
	}
}

void __declspec(naked) sub_602148()
{
	__asm
	{
	/*00602148*/	pushad
	/*00602149*/	mov esi,dword ptr ss:[esp+0x24]
	/*0060214D*/	mov edi,dword ptr ss:[esp+0x28]
	/*00602151*/	test esi,esi
	/*00602153*/	je _0060216F
	/*00602155*/	test edi,edi
	/*00602157*/	je _0060216F
	/*00602159*/	push 0x0
	/*0060215B*/	push dword ptr ds:[esi+0x57]
	/*0060215E*/	push edi
	/*0060215F*/	push 0x0
	/*00602161*/	push dword ptr ds:[edi+0x57]
	/*00602164*/	push esi
	/*00602165*/	call sub_6831A0		/*call <cm0102.sub_6831A0>*/
	/*0060216A*/	call sub_6830B0		/*call <cm0102.sub_6830B0>*/
_0060216F:
	/*0060216F*/	popad
	/*00602170*/	ret 0x8
	}
}

void __declspec(naked) sub_601D94()
{
	__asm
	{
	/*00601D94*/	pushad
	/*00601D95*/	mov ebp,esp
	/*00601D97*/	mov edi,dword ptr ds:[0xAE235C]
	/*00601D9D*/	imul ecx,edi,0x6
	/*00601DA0*/	push ecx
	/*00601DA1*/	call sub_944E46		/*call <cm0102.sub_944E46>*/
	/*00601DA6*/	xchg edi,eax
	/*00601DA7*/	xchg ecx,eax
	/*00601DA8*/	pop edx
	/*00601DA9*/	push edi
	/*00601DAA*/	mov edx,dword ptr ds:[0xAE23B4]
	/*00601DB0*/	xor ebx,ebx
_00601DB2:
	/*00601DB2*/	push ecx
	/*00601DB3*/	lea esi,dword ptr ss:[ebp+0x28]
	/*00601DB6*/	mov eax,dword ptr ss:[ebp+0x24]
	/*00601DB9*/	test eax,eax
	/*00601DBB*/	jl _00601DC6
	/*00601DBD*/	mov ecx,dword ptr ds:[edx+0x53]
	/*00601DC0*/	jecxz _00601DDF
	/*00601DC2*/	cmp dword ptr ds:[ecx],eax
	/*00601DC4*/	jne _00601DDF
_00601DC6:
	/*00601DC6*/	lodsd
	/*00601DC7*/	test eax,eax
	/*00601DC9*/	je _00601DDF
	/*00601DCB*/	mov ecx,dword ptr ds:[edx+0x57]
	/*00601DCE*/	jecxz _00601DDF
	/*00601DD0*/	cmp dword ptr ds:[ecx],eax
	/*00601DD2*/	jne _00601DC6
	/*00601DD4*/	mov eax,edx
	/*00601DD6*/	stosd
	/*00601DD7*/	call sub_601C2C		/*call <cm0102.sub_601C2C>*/
	/*00601DDC*/	stosw
	/*00601DDE*/	inc ebx
_00601DDF:
	/*00601DDF*/	add edx,0x245
	/*00601DE5*/	pop ecx
	/*00601DE6*/	loop _00601DB2
	/*00601DE8*/	pop eax
	/*00601DE9*/	mov dword ptr ss:[ebp+0x1C],eax
	/*00601DEC*/	push sub_601C1A		/*push <cm0102.sub_601C1A>*/			// Could be a problem!
	/*00601DF1*/	push 0x6
	/*00601DF3*/	push ebx
	/*00601DF4*/	push eax
	/*00601DF5*/	call sub_945333		/*call <cm0102.sub_945333>*/
	/*00601DFA*/	add esp,0x10
	/*00601DFD*/	popad
	/*00601DFE*/	ret
	}
}

void __declspec(naked) sub_601C2C()
{
	__asm
	{
	/*00601C2C*/	pushad
	/*00601C2D*/	sub esp,0x18
	/*00601C30*/	mov ebp,esp
	/*00601C32*/	push 0x5
	/*00601C34*/	pop ebx
	/*00601C35*/	lea esi,dword ptr ds:[edx+0xD7]
_00601C3B:
	/*00601C3B*/	push 0x130
	/*00601C40*/	call sub_944CF1		/*call <cm0102.sub_944CF1>*/
	/*00601C45*/	add esp,0x4
	/*00601C48*/	mov dword ptr ss:[ebp+ebx*0x4],eax
	/*00601C4C*/	xchg edi,eax
	/*00601C4D*/	push 0x32
	/*00601C4F*/	pop ecx
	/*00601C50*/	call sub_601B7A		/*call <cm0102.sub_601B7A>*/
	/*00601C55*/	push sub_601C1A		/*push <cm0102.sub_601C1A>*/			// Could be a problem!!!
	/*00601C5A*/	push 0x6
	/*00601C5C*/	push 0x32
	/*00601C5E*/	push dword ptr ss:[ebp+ebx*0x4]
	/*00601C62*/	call sub_602E38		/*call <cm0102.sub_602E38>*/
	/*00601C67*/	add esp,0x10
	/*00601C6A*/	dec ebx
	/*00601C6B*/	jge _00601C3B
	/*00601C6D*/	mov esi,ebp
	/*00601C6F*/	lodsd
	/*00601C70*/	movsx edx,word ptr ds:[eax+0x4]
	/*00601C74*/	inc ebx
	/*00601C75*/	movsx ebx,word ptr ds:[eax+0xA]
	/*00601C79*/	sar ebx,0x1
	/*00601C7B*/	add dx,bx
	/*00601C7E*/	lodsd
	/*00601C7F*/	add dx,word ptr ds:[eax+0x4]
	/*00601C83*/	add dx,word ptr ds:[eax+0xA]
	/*00601C87*/	add dx,word ptr ds:[eax+0x10]
	/*00601C8B*/	lodsd
	/*00601C8C*/	add dx,word ptr ds:[eax+0x4]
	/*00601C90*/	movsx ebx,word ptr ds:[eax+0xA]
	/*00601C94*/	sar ebx,0x1
	/*00601C96*/	add dx,bx
	/*00601C99*/	lodsd
	/*00601C9A*/	add dx,word ptr ds:[eax+0x4]
	/*00601C9E*/	add dx,word ptr ds:[eax+0xA]
	/*00601CA2*/	movsx ebx,word ptr ds:[eax+0x10]
	/*00601CA6*/	sar ebx,0x1
	/*00601CA8*/	add dx,bx
	/*00601CAB*/	lodsd
	/*00601CAC*/	add dx,word ptr ds:[eax+0x4]
	/*00601CB0*/	movsx ebx,word ptr ds:[eax+0xA]
	/*00601CB4*/	sar ebx,0x1
	/*00601CB6*/	add dx,bx
	/*00601CB9*/	lodsd
	/*00601CBA*/	add dx,word ptr ds:[eax+0x4]
	/*00601CBE*/	add dx,word ptr ds:[eax+0xA]
	/*00601CC2*/	xchg edx,eax
	/*00601CC3*/	push 0xC
	/*00601CC5*/	pop ebx
	/*00601CC6*/	cdq
	/*00601CC7*/	idiv bx
	/*00601CCA*/	push eax
	/*00601CCB*/	push 0x6
	/*00601CCD*/	pop ecx
	/*00601CCE*/	mov esi,ebp
_00601CD0:
	/*00601CD0*/	lodsd
	/*00601CD1*/	push ecx
	/*00601CD2*/	push eax
	/*00601CD3*/	call sub_9452CA		/*call <cm0102.sub_9452CA>*/
	/*00601CD8*/	pop eax
	/*00601CD9*/	pop ecx
	/*00601CDA*/	loop _00601CD0
	/*00601CDC*/	pop eax
	/*00601CDD*/	add esp,0x18
	/*00601CE0*/	inc eax
	/*00601CE1*/	mov dword ptr ss:[esp+0x1C],eax
	/*00601CE5*/	popad
	/*00601CE6*/	ret
	}
}

void __declspec(naked) sub_601B44()
{
	__asm
	{
	/*00601B44*/	cmp byte ptr ds:[edx+0xF],0xF
	/*00601B48*/	ret
	}
}

void __declspec(naked) sub_601B49()
{
	__asm
	{
	/*00601B49*/	cmp byte ptr ds:[edx+0x10],0xF
	/*00601B4D*/	jge _00601B53
	/*00601B4F*/	cmp byte ptr ds:[edx+0x11],0xF
_00601B53:
	/*00601B53*/	ret
	}
}

void __declspec(naked) sub_601B54()
{
	__asm
	{
	/*00601B54*/	cmp byte ptr ds:[edx+0x12],0xF
	/*00601B58*/	jge _00601B64
	/*00601B5A*/	cmp byte ptr ds:[edx+0x13],0xF
	/*00601B5E*/	jge _00601B64
	/*00601B60*/	cmp byte ptr ds:[edx+0x14],0xF
_00601B64:
	/*00601B64*/	ret
	}
}

void __declspec(naked) sub_601B65()
{
	__asm
	{
	/*00601B65*/	cmp byte ptr ds:[edx+0x15],0xF
	/*00601B69*/	ret
	}
}

void __declspec(naked) sub_601B6A()
{
	__asm
	{
	/*00601B6A*/	cmp byte ptr ds:[edx+0x19],0xF
	/*00601B6E*/	ret
	}
}

void __declspec(naked) sub_601B6F()
{
	__asm
	{
	/*00601B6F*/	cmp byte ptr ds:[edx+0x17],0xF
	/*00601B73*/	jge _00601B79
	/*00601B75*/	cmp byte ptr ds:[edx+0x18],0xF
_00601B79:
	/*00601B79*/	ret
	}
}

BYTE Data_601A83[] =
{
	0x89, 0x3D, 0x9C, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xA0, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xA4,
	0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xA8, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xAC, 0xF1, 0x9C, 0x00, 0x89,
	0x3D, 0xB0, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xB4, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xB8, 0xF1, 0x9C,
	0x00, 0x89, 0x3D, 0xBC, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xC0, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xC4,
	0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xC8, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xCC, 0xF1, 0x9C, 0x00, 0x89,
	0x3D, 0xD0, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xD4, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xD8, 0xF1, 0x9C,
	0x00, 0x89, 0x3D, 0xDC, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xE0, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xE4,
	0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xE8, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xEC, 0xF1, 0x9C, 0x00, 0x89,
	0x3D, 0xF0, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xF4, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0xF8, 0xF1, 0x9C,
	0x00, 0x89, 0x3D, 0xFC, 0xF1, 0x9C, 0x00, 0x89, 0x3D, 0x00, 0xF2, 0x9C, 0x00, 0x89, 0x3D, 0x04,
	0xF2, 0x9C, 0x00, 0x89, 0x3D, 0x08, 0xF2, 0x9C, 0x00, 0x89, 0x3D, 0x0C, 0xF2, 0x9C, 0x00, 0x89,
	0x3D, 0x10, 0xF2, 0x9C, 0x00, 0x89, 0x3D, 0x14, 0xF2, 0x9C, 0x00, 0x89, 0x3D, 0x18, 0xF2, 0x9C,
	0x00, 0x89, 0x80, 0x7A, 0x0F, 0x0F, 0xC3, 0x80, 0x7A, 0x10, 0x0F, 0x7D, 0x04, 0x80, 0x7A, 0x11
};

void __declspec(naked) sub_601B7A()
{
	__asm
	{
	/*00601B7A*/	pushad
_00601B7B:
	/*00601B7B*/	lodsd
	/*00601B7C*/	stosd
	/*00601B7D*/	test eax,eax
	/*00601B7F*/	je _00601BFA
	/*00601B81*/	mov edx,dword ptr ds:[eax+0x61]
	/*00601B84*/	test edx,edx
	/*00601B86*/	je _00601BFA
	/*00601B88*/	cmp bl,0x0
	/*00601B8B*/	jne _00601B94
	/*00601B8D*/	call sub_601B44		/*call <cm0102.sub_601B44>*/
	/*00601B92*/	jge _00601BFC
_00601B94:
	/*00601B94*/	cmp bl,0x1
	/*00601B97*/	jne _00601BA7
	/*00601B99*/	call sub_601B6A		/*call <cm0102.sub_601B6A>*/
	/*00601B9E*/	jl _00601BFA
	/*00601BA0*/	call sub_601B49		/*call <cm0102.sub_601B49>*/
	/*00601BA5*/	jge _00601BFC
_00601BA7:
	/*00601BA7*/	cmp bl,0x2
	/*00601BAA*/	jne _00601BBA
	/*00601BAC*/	call sub_601B6F		/*call <cm0102.sub_601B6F>*/
	/*00601BB1*/	jl _00601BFA
	/*00601BB3*/	call sub_601B49		/*call <cm0102.sub_601B49>*/
	/*00601BB8*/	jge _00601BFC
_00601BBA:
	/*00601BBA*/	cmp bl,0x3
	/*00601BBD*/	jne _00601BCD
	/*00601BBF*/	call sub_601B6A		/*call <cm0102.sub_601B6A>*/
	/*00601BC4*/	jl _00601BFA
	/*00601BC6*/	call sub_601B54		/*call <cm0102.sub_601B54>*/
	/*00601BCB*/	jge _00601BFC
_00601BCD:
	/*00601BCD*/	cmp bl,0x4
	/*00601BD0*/	jne _00601BE7
	/*00601BD2*/	call sub_601B6F		/*call <cm0102.sub_601B6F>*/
	/*00601BD7*/	jl _00601BFA
	/*00601BD9*/	call sub_601B54		/*call <cm0102.sub_601B54>*/
	/*00601BDE*/	jge _00601BFC
	/*00601BE0*/	call sub_601B65		/*call <cm0102.sub_601B65>*/
	/*00601BE5*/	jge _00601BFC
_00601BE7:
	/*00601BE7*/	cmp bl,0x5
	/*00601BEA*/	jne _00601BFA
	/*00601BEC*/	call sub_601B6A		/*call <cm0102.sub_601B6A>*/
	/*00601BF1*/	jl _00601BFA
	/*00601BF3*/	call sub_601B65		/*call <cm0102.sub_601B65>*/
	/*00601BF8*/	jge _00601BFC
_00601BFA:
	/*00601BFA*/	xor eax,eax
_00601BFC:
	/*00601BFC*/	push ebx
	/*00601BFD*/	shl ebx,0x5
	/*00601C00*/	add ebx, OFFSET Data_601A83 //0x601A83		/*add ebx,cm0102.601A83*/				//// Looks like a problem!
	/*00601C06*/	call sub_601A58		/*call <cm0102.sub_601A58>*/				
	/*00601C0B*/	pop ebx
	/*00601C0C*/	sar ax,0x1
	/*00601C0F*/	stosw
	/*00601C11*/	dec ecx
	/*00601C12*/	jne _00601B7B
	/*00601C18*/	popad
	/*00601C19*/	ret
	}
}

void __declspec(naked) sub_601C1A()
{
	__asm
	{
	/*00601C1A*/	mov eax,dword ptr ss:[esp+0x8]
	/*00601C1E*/	mov edx,dword ptr ss:[esp+0x4]
	/*00601C22*/	mov ax,word ptr ds:[eax+0x4]
	/*00601C26*/	sub ax,word ptr ds:[edx+0x4]
	/*00601C2A*/	cwde
	/*00601C2B*/	ret
	}
}

void __declspec(naked) sub_602E38()
{
	__asm
	{
	/*00602E38*/	push ebp
	/*00602E39*/	mov ebp,esp
	/*00602E3B*/	cmp dword ptr ss:[ebp+0xC],0x2
	/*00602E3F*/	jl _00602E8E
	/*00602E41*/	push ebx
	/*00602E42*/	push esi
	/*00602E43*/	push edi
	/*00602E44*/	imul ebx,dword ptr ss:[ebp+0xC],0x6
	/*00602E48*/	mov esi,dword ptr ss:[ebp+0x8]
	/*00602E4B*/	add ebx,esi
	/*00602E4D*/	add esi,0x6
_00602E50:
	/*00602E50*/	mov ax,word ptr ds:[esi+0x4]
	/*00602E54*/	push eax
	/*00602E55*/	push dword ptr ds:[esi]
	/*00602E57*/	lea edi,dword ptr ds:[esi-0x6]
_00602E5A:
	/*00602E5A*/	push esp
	/*00602E5B*/	push edi
	/*00602E5C*/	call dword ptr ss:[ebp+0x14]
	/*00602E5F*/	add esp,0x8
	/*00602E62*/	cmp eax,0x0
	/*00602E65*/	jle _00602E7C
	/*00602E67*/	mov eax,dword ptr ds:[edi]
	/*00602E69*/	mov dx,word ptr ds:[edi+0x4]
	/*00602E6D*/	mov dword ptr ds:[edi+0x6],eax
	/*00602E70*/	mov word ptr ds:[edi+0xA],dx
	/*00602E74*/	sub edi,0x6
	/*00602E77*/	cmp edi,dword ptr ss:[ebp+0x8]
	/*00602E7A*/	jge _00602E5A
_00602E7C:
	/*00602E7C*/	pop dword ptr ds:[edi+0x6]
	/*00602E7F*/	pop eax
	/*00602E80*/	mov word ptr ds:[edi+0xA],ax
	/*00602E84*/	add esi,0x6
	/*00602E87*/	cmp esi,ebx
	/*00602E89*/	jl _00602E50
	/*00602E8B*/	pop edi
	/*00602E8C*/	pop esi
	/*00602E8D*/	pop ebx
_00602E8E:
	/*00602E8E*/	leave
	/*00602E8F*/	ret
	}
}

void __declspec(naked) sub_601A58()
{
	__asm
	{
	/*00601A58*/	test eax,eax
	/*00601A5A*/	je _00601A81
	/*00601A5C*/	pushad
	/*00601A5D*/	mov esi,dword ptr ds:[eax+0x61]
	/*00601A60*/	xchg ebp,eax
	/*00601A61*/	xor edi,edi
	/*00601A63*/	test esi,esi
	/*00601A65*/	je _00601A7C
	/*00601A67*/	push 0x1F
	/*00601A69*/	pop ecx
_00601A6A:
	/*00601A6A*/	push ecx
	/*00601A6B*/	push esi
	/*00601A6C*/	push ebp
	/*00601A6D*/	call sub_543540		/*call <cm0102.sub_543540>*/
	/*00601A72*/	pop ebp
	/*00601A73*/	pop esi
	/*00601A74*/	pop ecx
	/*00601A75*/	imul byte ptr ds:[ecx+ebx]
	/*00601A78*/	add edi,eax
	/*00601A7A*/	loop _00601A6A
_00601A7C:
	/*00601A7C*/	mov dword ptr ss:[esp+0x1C],edi
	/*00601A80*/	popad
_00601A81:
	/*00601A81*/	ret
	}
}

void __declspec(naked) sub_7EBE3C()
{
	__asm
	{
	/*007EBE3C*/	push eax
	/*007EBE3D*/	call sub_601D94		/*call <cm0102.sub_601D94>*/
_007EBE42:
	/*007EBE42*/	pop ecx
	/*007EBE43*/	inc ecx
	/*007EBE44*/	loop _007EBE42
	/*007EBE46*/	mov dword ptr ss:[esp+0x1C],eax
	/*007EBE4A*/	popad
	/*007EBE4B*/	ret 0x4
	}
}

void __declspec(naked) sub_7EBE50()		// called by sub_601FF0
{
	__asm
	{
	/*007EBE50*/	pushad
	/*007EBE51*/	mov eax,dword ptr ss:[esp+0x24]
	/*007EBE55*/	push 0x0
	/*007EBE57*/	push 0x165								// A Lower Division
	/*007EBE5C*/	cmp eax,dword ptr ds:[0x9CF448]			// [9cf448] = Russia
	/*007EBE62*/	jne _007EBE8A
	/*007EBE64*/	push dword ptr ds:[0x9CF914]			// [9cf914] = Russian Second Division West
	/*007EBE6A*/	push dword ptr ds:[0x9CF918]			// [9cf918] = Russian Second Division Central
	/*007EBE70*/	push dword ptr ds:[0x9CF91C]			// [9cf91c] = Russian Second Division South
	/*007EBE76*/	push dword ptr ds:[0x9CF920]			// [9cf920] = Russian Second Division Volga
	/*007EBE7C*/	push dword ptr ds:[0x9CF924]			// [9cf924] = Russian Second Division Ural
	/*007EBE82*/	push dword ptr ds:[0x9CF928]			// [9cf928] = Russian Second Division East
	/*007EBE88*/	jmp sub_7EBE3C
_007EBE8A:
	/*007EBE8A*/	cmp eax,dword ptr ds:[0x9CF2DC]			// [9cf2dc] = Republic of Ireland
	/*007EBE90*/	jne _007EBEAC
	/*007EBE92*/	push dword ptr ds:[0x9CF850]			// [9cf850] = Irish Munster Senior League
	/*007EBE98*/	push dword ptr ds:[0x9CF854]			// [9cf854] = Irish Leinster Senior League
	/*007EBE9E*/	push dword ptr ds:[0x9CF84C]			// [9cf84c] = Irish Ulster Senior League
	/*007EBEA4*/	push dword ptr ds:[0x9CF848]			// [9cf848] = Irish Connacht Senior League
	/*007EBEAA*/	jmp sub_7EBE3C
_007EBEAC:
	/*007EBEAC*/	cmp eax,dword ptr ds:[0x9CF3E4]			// [9cf3e4] = Northern Ireland
	/*007EBEB2*/	jne _007EBEBC
	/*007EBEB4*/	push dword ptr ds:[0x9CF8B8]			// [9cf8b8] = Northern Ireland Lower Division
_007EBEBA:
	/*007EBEBA*/	jmp sub_7EBE3C
_007EBEBC:
	/*007EBEBC*/	cmp eax,dword ptr ds:[0x9CF510]			// [9cf510] = Wales
	/*007EBEC2*/	jne _007EBECC
	/*007EBEC4*/	push dword ptr ds:[0x9CF960]			// [9cf960] = Welsh Lower Division
	/*007EBECA*/	jmp _007EBEBA
_007EBECC:
	/*007EBECC*/	cmp eax,dword ptr ds:[0x9CF2E4]			// [9cf2e4] = England
	/*007EBED2*/	jne _007EBEE3
	/*007EBED4*/	push 0x166								// English Isthmian League Premier Division
	/*007EBED9*/	push 0x167								// English Southern League Premier Division
	/*007EBEDE*/	jmp _007EBEBA
	/*007EBEE0*/	nop
	/*007EBEE1*/	nop
	/*007EBEE2*/	nop
_007EBEE3:
	/*007EBEE3*/	cmp eax,dword ptr ds:[0x9CF45C]			// [9cf45c] = Scotland
	/*007EBEE9*/	je _007EBEBA
	/*007EBEEB*/	cmp eax,dword ptr ds:[0x9CF36C]			// [9cf36c] = Japan
	/*007EBEF1*/	jne _007EBEFB
	/*007EBEF3*/	push dword ptr ds:[0x9CF678]			// [9cf678] = Japanese Administrative Division
	/*007EBEF9*/	jmp _007EBEBA
_007EBEFB:
	/*007EBEFB*/	cmp eax,dword ptr ds:[0x9CF484]			// [9cf484] = South Korea
	/*007EBF01*/	je _007EBEBA
	/*007EBF03*/	xor eax,eax
	/*007EBF05*/	//jmp _007EBE42
_local_007EBE42:
	/*007EBE42*/	pop ecx
	/*007EBE43*/	inc ecx
	/*007EBE44*/	loop _local_007EBE42
	/*007EBE46*/	mov dword ptr ss:[esp+0x1C],eax
	/*007EBE4A*/	popad
	/*007EBE4B*/	ret 0x4
	}
}


