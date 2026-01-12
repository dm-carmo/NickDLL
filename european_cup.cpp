#pragma warning (disable : 4733)
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "Structures\CMHeader.h"
#include "Helpers\Helper.h"

static int(*cm0102_malloc)() = (int(*)())(0x944E46);
static int(*cm0102_splitpath)() = (int(*)())(0x944CFF);
static int(*cm0102_new)() = (int(*)())(0x944CF1);
static int(*cm0102_GetVersionString)() = (int(*)())(0x90D130);
static int(*cm0102_sprintf)() = (int(*)())(0x944C9F);
static int(*cm0102_maybe_free1)() = (int(*)())(0x944C94);
static int(*cm0102_maybe_free2)() = (int(*)())(0x9452CA);
static int(*cm0102_qsort)() = (int(*)())(0x945333);
static int(*cm0102_exit)() = (int(*)())(0x945934);
static int(*cm0102_rand2)() = (int(*)())(0x90CFC0);
static int(*cm0102_DateConvert)() = (int(*)())(0x549F70);
static int(*cm0102_CreateErrorMsgBox)() = (int(*)())(0x5E8290);
static int(*cm0102_memset14bytesto0)() = (int(*)())(0x68D020);
static int(*cm0102_create_league_68B100)() = (int(*)())(0x68B100);
static int(*cm0102_set_fixture_68A1C0)() = (int(*)())(0x68A1C0);
static int(*cm0102_to_set_date_fixture_68A160)() = (int(*)())(0x68A160);
static int(*cm0102_cup_map_fixture_tree_518790)() = (int(*)())(0x518790);

static int(*sub_768720)() = (int(*)())(0x768720);
static int(*sub_68D040)() = (int(*)())(0x68D040);

static int(*sub_518640)() = (int(*)())(0x518640);
static int(*sub_51FC00)() = (int(*)())(0x51FC00);
static int(*sub_9035A0)() = (int(*)())(0x9035A0);
static int(*sub_49EE70)() = (int(*)())(0x49EE70);


static int(*sub_49F450)() = (int(*)())(0x49F450);
static int(*sub_518690)() = (int(*)())(0x518690);

static int(*sub_9058B0)() = (int(*)())(0x9058B0);
static int(*sub_5A0590)() = (int(*)())(0x5A0590);
static int(*sub_5999A0)() = (int(*)())(0x5999A0);
static int(*sub_48E3E0)() = (int(*)())(0x48E3E0);
static int(*sub_51A150)() = (int(*)())(0x51A150);

static int(*sub_521E60)() = (int(*)())(0x521E60);
static int(*sub_521EB0)() = (int(*)())(0x521EB0);
static int(*sub_54C8E0)() = (int(*)())(0x54C8E0);
static int(*sub_417C10)() = (int(*)())(0x417C10);
static int(*sub_521F10)() = (int(*)())(0x521F10);
static int(*sub_4B0870)() = (int(*)())(0x4B0870);
static int(*sub_66F4E0)() = (int(*)())(0x66F4E0);
static int(*sub_4AE660)() = (int(*)())(0x4AE660);
static int(*sub_4AE8A0)() = (int(*)())(0x4AE8A0);
static int(*sub_48C6D0)() = (int(*)())(0x48C6D0);
static int(*sub_4B4590)() = (int(*)())(0x4B4590);

static int(*sub_4BF850)() = (int(*)())(0x4BF850);
static int(*sub_86BDD0)() = (int(*)())(0x86BDD0);
static int(*sub_86C1D0)() = (int(*)())(0x86C1D0);
static int(*sub_86A800)() = (int(*)())(0x86A800);
static int(*sub_86B0B0)() = (int(*)())(0x86B0B0);
static int(*sub_86C000)() = (int(*)())(0x86C000);

static int(*sub_4A1C50)() = (int(*)())(0x4A1C50);

static int(*sub_945501)() = (int(*)())(0x945501);
static int(*sub_5CC7D0)() = (int(*)())(0x5CC7D0);
static int(*sub_5A8F60)() = (int(*)())(0x5A8F60);

static int(*sub_684230)() = (int(*)())(0x684230);

static int(*sub_6826D0)() = (int(*)())(0x6826D0);
static int(*sub_7E9180)() = (int(*)())(0x7E9180);

static int(*sub_522E00)() = (int(*)())(0x522E00);
static int(*sub_51C800)() = (int(*)())(0x51C800);

static int(*sub_48E1C0)() = (int(*)())(0x48E1C0);

static int(*sub_4C08F0)() = (int(*)())(0x4C08F0);
static int(*sub_4A2540)() = (int(*)())(0x4A2540);

static int(*sub_4B01D0)() = (int(*)())(0x4B01D0);
static int(*sub_4BFFC0)() = (int(*)())(0x4BFFC0);

static int(*sub_77BBE0)() = (int(*)())(0x77BBE0);
static int(*sub_785790)() = (int(*)())(0x785790);
static int(*sub_547770)() = (int(*)())(0x547770);
static int(*sub_62ED70)() = (int(*)())(0x62ED70);
static int(*sub_8972C0)() = (int(*)())(0x8972C0);
static int(*sub_7861E0)() = (int(*)())(0x7861E0);

// All functions defined below
extern "C" void european_cup_june_awards_5836A0();
extern "C" void european_cup_setup_5837C0();
extern "C" void sub_5839D0();
extern "C" void sub_5839E0();
extern "C" void sub_583A00();
extern "C" void sub_583B10();
extern "C" void european_cup_schedule_583C50();
extern "C" void european_cup_get_qualifying_teams_584990();
extern "C" void sub_584AD0();
extern "C" void sub_584AE0();
extern "C" void sub_584D60();
extern "C" void european_cup_select_teams_584FA0();
extern "C" void sub_5851D0();
extern "C" void sub_585290();
extern "C" void sub_585AB0();
extern "C" void sub_586330();
extern "C" void sub_586660();
extern "C" void sub_586900();
extern "C" void sub_586FA0();
extern "C" void sub_5871E0();

/* Call Order:
european_cup_setup_5837C0 Called!
european_cup_select_teams_584FA0 Called!
european_cup_get_qualifying_teams_584990 Called!
european_cup_schedule_583C50 Called!
sub_586900 Called!
european_cup_schedule_583C50 Called!
sub_583B10 Called!
sub_583B10 Called!
sub_583B10 Called!
sub_583B10 Called!
sub_583B10 Called!
sub_583B10 Called!
sub_583B10 Called!
sub_583B10 Called!
sub_583B10 Called!
*/

extern "C" void __declspec(naked) european_cup_june_awards_5836A0()
{
	__asm pushad
	// dprintf("european_cup_june_awards_5836A0 Called!\n"); // commented out as runs every day
	__asm popad

	__asm
	{
	/*005836A0*/	mov eax,dword ptr fs:[0x0]
	/*005836A6*/	push 0xFFFFFFFF
	/*005836A8*/	push 0x958A48		/*push <cm0102.sub_958A48>*/
	/*005836AD*/	push eax
	/*005836AE*/	mov dword ptr fs:[0x0],esp
	/*005836B5*/	sub esp,0x18
	/*005836B8*/	push esi
	/*005836B9*/	push edi
	/*005836BA*/	mov edi,dword ptr ss:[esp+0x30]
	/*005836BE*/	mov esi,ecx
	/*005836C0*/	mov ax,word ptr ds:[edi+0x2]
	/*005836C4*/	cmp ax,0x7D1						/* Check if year is 2001 and don't do anything if it is */
	/*005836C8*/	je _005837AD
	/*005836CE*/	push 0xFFFFFFFF
	/*005836D0*/	push eax			// Year
	/*005836D1*/	push 0x5			// June
	/*005836D3*/	push 0x10			// 16th
	/*005836D5*/	lea ecx,dword ptr ss:[esp+0x28]
	/*005836D9*/	call cm0102_DateConvert		/*call <cm0102.cm0102_DateConvert>*/
	/*005836DE*/	mov ecx,dword ptr ds:[eax]			// Points to the stack which has the June 16th date (i.e. A600D207)
	/*005836E0*/	mov eax,dword ptr ds:[eax+0x4]		// Just has 0 (leap year part?)
	/*005836E3*/	mov dword ptr ss:[esp+0x8],ecx
	/*005836E7*/	mov dx,word ptr ss:[esp+0xA]		// Get Year
	/*005836EC*/	cmp dx,word ptr ds:[edi+0x2]		// edi = 00AE2C90 - Current Year?
	/*005836F0*/	mov dword ptr ss:[esp+0xC],eax
	/*005836F4*/	jne _005837AD
	/*005836FA*/	cmp cx,word ptr ds:[edi]			// Day part of the date (Checking for June 16)
	/*005836FD*/	jne _005837AD
	/*00583703*/	push ebx							// Awards link?
	/*00583704*/	lea ecx,dword ptr ss:[esp+0xC]		// Get pointer to the date
	/*00583708*/	call cm0102_memset14bytesto0		/*call <cm0102.cm0102_memset14bytesto0>*/
	/*0058370D*/	mov eax,dword ptr ds:[0xAD9C60]		// Awards?
	/*00583712*/	mov edx,dword ptr ds:[0x9CFA10]		/* Europe */
	/*00583718*/	lea ecx,dword ptr ss:[esp+0xC]
	/*0058371C*/	mov dword ptr ss:[esp+0x2C],0x0
	/*00583724*/	mov ebx,dword ptr ds:[eax+0x10]
	/*00583727*/	mov eax,dword ptr ds:[esi+0x4]
	/*0058372A*/	push ecx
	/*0058372B*/	push 0x1
	/*0058372D*/	mov ecx,dword ptr ds:[eax]
	/*0058372F*/	push 0x1
	/*00583731*/	push edx
	/*00583732*/	push ebx
	/*00583733*/	push ecx
	/*00583734*/	push edi							// Date
	/*00583735*/	mov ecx,esi
	/*00583737*/	call sub_768720		/*call <cm0102.sub_768720>*/		// nation_awards function
	/*0058373C*/	mov ecx,dword ptr ds:[esi+0x4]
	/*0058373F*/	mov eax,dword ptr ds:[0x9CFA10]		/* Europe */
	/*00583744*/	lea edx,dword ptr ss:[esp+0xC]
	/*00583748*/	push edx
	/*00583749*/	mov edx,dword ptr ds:[ecx+0x4]
	/*0058374C*/	push 0x1
	/*0058374E*/	push 0x6
	/*00583750*/	push eax
	/*00583751*/	push ebx
	/*00583752*/	push edx
	/*00583753*/	push edi
	/*00583754*/	mov ecx,esi
	/*00583756*/	call sub_768720		/*call <cm0102.sub_768720>*/
	/*0058375B*/	mov edx,dword ptr ds:[esi+0x4]
	/*0058375E*/	mov ecx,dword ptr ds:[0x9CFA10]		/* Europe */
	/*00583764*/	lea eax,dword ptr ss:[esp+0xC]
	/*00583768*/	push eax
	/*00583769*/	mov eax,dword ptr ds:[edx+0x8]
	/*0058376C*/	push 0x1
	/*0058376E*/	push 0x38
	/*00583770*/	push ecx
	/*00583771*/	push ebx
	/*00583772*/	push eax
	/*00583773*/	push edi
	/*00583774*/	mov ecx,esi
	/*00583776*/	call sub_768720		/*call <cm0102.sub_768720>*/
	/*0058377B*/	mov eax,dword ptr ds:[esi+0x4]
	/*0058377E*/	mov edx,dword ptr ds:[0x9CFA10]		/* Europe */
	/*00583784*/	lea ecx,dword ptr ss:[esp+0xC]
	/*00583788*/	push ecx
	/*00583789*/	mov ecx,dword ptr ds:[eax+0xC]
	/*0058378C*/	push 0x1
	/*0058378E*/	push 0x40
	/*00583790*/	push edx
	/*00583791*/	push ebx
	/*00583792*/	push ecx
	/*00583793*/	push edi
	/*00583794*/	mov ecx,esi
	/*00583796*/	call sub_768720		/*call <cm0102.sub_768720>*/
	/*0058379B*/	lea ecx,dword ptr ss:[esp+0xC]
	/*0058379F*/	mov dword ptr ss:[esp+0x2C],0xFFFFFFFF
	/*005837A7*/	call sub_68D040		/*call <cm0102.sub_68D040>*/
	/*005837AC*/	pop ebx
_005837AD:
	/*005837AD*/	mov ecx,dword ptr ss:[esp+0x20]
	/*005837B1*/	pop edi
	/*005837B2*/	pop esi
	/*005837B3*/	mov dword ptr fs:[0x0],ecx
	/*005837BA*/	add esp,0x24
	/*005837BD*/	ret 0x4
	}
}

extern "C" void __declspec(naked) european_cup_setup_5837C0() // On Setup: First Function called
{
	__asm pushad
	dprintf("european_cup_setup_5837C0 Called!\n");
	__asm popad


	__asm
	{
	/*005837C0*/	push 0xFFFFFFFF
	/*005837C2*/	push 0x958A79		/*push <cm0102.sub_958A79>*/		// ___CxxFrameHandler stuff
	/*005837C7*/	mov eax,dword ptr fs:[0x0]
	/*005837CD*/	push eax
	/*005837CE*/	mov dword ptr fs:[0x0],esp
	/*005837D5*/	sub esp,0x208
	/*005837DB*/	push ebx
	/*005837DC*/	push esi
	/*005837DD*/	mov esi,ecx
	/*005837DF*/	push edi											/// Pointer to divisions
	/*005837E0*/	mov dword ptr ss:[esp+0x10],esi
	/*005837E4*/	call sub_518640		/*call cm0102.518640*/			/// Initialise a structure (mostly to 0) - in esi
	/*005837E9*/	mov ax,word ptr ss:[esp+0x224]						/// Get the current year into AX
	/*005837F1*/	mov ecx,dword ptr ss:[esp+0x228]					/// ECX will point to European Champions Cup Division
	/*005837F8*/	mov word ptr ds:[esi+0x40],ax						/// AX is the current year (7D1 - 2001)
	/*005837FC*/	xor ebx,ebx
	/*005837FE*/	mov al,0x3
	/*00583800*/	push 0x34											// Allocate 52 bytes
	/*00583802*/	mov dword ptr ss:[esp+0x220],ebx
	/*00583809*/	mov dword ptr ds:[esi],0x96A1D0		/*mov dword ptr ds:[esi],<cm0102.&sub_5839E0> - european_cup function*/
	/*0058380F*/	mov byte ptr ds:[esi+0xAB],bl				// 0
	/*00583815*/	mov byte ptr ds:[esi+0x44],0xFF
	/*00583819*/	mov dword ptr ds:[esi+0x30],0xFFFFFFFF
	/*00583820*/	mov dword ptr ds:[esi+0x2C],0xD				// 13 - The number of stages - reducing this will remove the finals, phase 2, etc
	/*00583827*/	mov dword ptr ds:[esi+0x4],ecx				// Set the division/club comp
	/*0058382A*/	mov byte ptr ds:[esi+0x42],0x2				// 2 - if 2 populates blue schedule boxes next to teams with country abbreviation - blank otherwise
	/*0058382E*/	mov dword ptr ds:[esi+0x1C],0xFFFFFFFF		// Promote to division
	/*00583835*/	mov dword ptr ds:[esi+0x20],0xFFFFFFFF		// Relegate to division
	/*0058383C*/	mov byte ptr ds:[esi+0x52],al		// 3	(changing to 2 made no noticeable diff)
	/*0058383F*/	mov byte ptr ds:[esi+0x49],0x7		// Substitutes
	/*00583843*/	mov byte ptr ds:[esi+0x4A],al		// Substitutes Max Used
	/*00583846*/	mov byte ptr ds:[esi+0x51],0xA		// 10 - ??? changing to 8 does nothing obvious
	/*0058384A*/	mov byte ptr ds:[esi+0x50],0x1		// 1  - ??? changing to 0 does nothing obvious
	/*0058384E*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*00583853*/	add esp,0x4
	/*00583856*/	lea edi,dword ptr ds:[esi+0x3A]		// at esi+0x3A == 0
	/*00583859*/	mov ecx,esi
	/*0058385B*/	mov dword ptr ds:[esi+0xC],eax		// Assign the block of memory to esi+0C
	/*0058385E*/	push 0x1
	/*00583860*/	mov word ptr ds:[edi],bx
	/*00583863*/	mov byte ptr ds:[esi+0xB1],bl
	/*00583869*/	call sub_51FC00		/*call cm0102.51FC00*/		// call into cup.cpp
	/*0058386E*/	test eax,eax
	/*00583870*/	jne _005839B4
	/*00583876*/	mov ecx,dword ptr ds:[0xDE1F58]		//  contains an address of the UEFA Country Rankings
	/*0058387C*/	cmp ecx,ebx
	/*0058387E*/	je _00583886	// if zero jmp over
	/*00583880*/	push ebx
	/*00583881*/	call sub_9035A0		/*call <cm0102.sub_9035A0>*/		// if have seedings - call into uefa_seedings.cpp (param: 0)
_00583886:
	/*00583886*/	mov ecx,esi
	/*00583888*/	call european_cup_select_teams_584FA0		/*call <cm0102.european_cup_select_teams_584FA0>*/		// Call european_cup func - Team Selection?
	/*0058388D*/	mov ecx,esi	
	/*0058388F*/	call european_cup_get_qualifying_teams_584990		/*call <cm0102.european_cup_get_qualifying_teams_584990>*/		// Call european_cup func
	/*00583894*/	test eax,eax
	/*00583896*/	jne _005838C8
	/*00583898*/	lea edx,dword ptr ss:[esp+0x14]
	/*0058389C*/	lea eax,dword ptr ss:[esp+0x114]
	/*005838A3*/	push edx
	/*005838A4*/	push eax
	/*005838A5*/	push ebx
	/*005838A6*/	push ebx
	/*005838A7*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005838AC*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*005838B1*/	add esp,0x14
	/*005838B4*/	lea ecx,dword ptr ss:[esp+0x14]
	/*005838B8*/	lea edx,dword ptr ss:[esp+0x114]
	/*005838BF*/	push 0x74
	/*005838C1*/	push ecx
	/*005838C2*/	push edx
	/*005838C3*/	jmp _0058397D
_005838C8:
	/*005838C8*/	mov eax,dword ptr ds:[esi]
	/*005838CA*/	push ebx
	/*005838CB*/	lea ecx,dword ptr ds:[esi+0x3C]		
	/*005838CE*/	push edi
	/*005838CF*/	push ecx
	/*005838D0*/	push 0xFFFFFFFF
	/*005838D2*/	mov ecx,esi
	/*005838D4*/	call dword ptr ds:[eax+0x3C]		// Calls european_cup_schedule_583C50 (in european_cup.cpp) - Qualifying Phases
	/*005838D7*/	mov ecx,esi
	/*005838D9*/	mov dword ptr ds:[esi+0xA3],eax		// Eax has a pointer to structure - does have some teams in there - first is: Boksit Milici
	/*005838DF*/	call cm0102_cup_map_fixture_tree_518790		/*call cm0102.518790*/
	/*005838E4*/	test eax,eax
	/*005838E6*/	jne _00583918
	/*005838E8*/	lea edx,dword ptr ss:[esp+0x114]
	/*005838EF*/	lea eax,dword ptr ss:[esp+0x14]
	/*005838F3*/	push edx
	/*005838F4*/	push eax
	/*005838F5*/	push ebx
	/*005838F6*/	push ebx
	/*005838F7*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005838FC*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00583901*/	add esp,0x14
	/*00583904*/	lea ecx,dword ptr ss:[esp+0x114]
	/*0058390B*/	lea edx,dword ptr ss:[esp+0x14]
	/*0058390F*/	push 0x82
	/*00583914*/	push ecx
	/*00583915*/	push edx
	/*00583916*/	jmp _0058397D
_00583918:
	/*00583918*/	push 0x5CE			// 1475 bytes 
	/*0058391D*/	call cm0102_new		/*call <cm0102.cm0102_new>*/
	/*00583922*/	add esp,0x4
	/*00583925*/	mov dword ptr ss:[esp+0xC],eax		// Save block onstack
	/*00583929*/	cmp eax,ebx							// Make sure it's not 0
	/*0058392B*/	mov byte ptr ss:[esp+0x21C],0x1
	/*00583933*/	je _0058393F
	/*00583935*/	push esi							// Our league block (i think created by cup.cpp? has the European Champions Cup_326.tmp file referenced in it
	/*00583936*/	mov ecx,eax
	/*00583938*/	call sub_49EE70		/*call cm0102.49EE70*/		// Calls into comp_stats.cpp and references comp records history.tmp
	/*0058393D*/	jmp _00583941
_0058393F:
	/*0058393F*/	xor eax,eax
_00583941:
	/*00583941*/	cmp eax,ebx							// eax is still our memory from new - checks it is still not 0
	/*00583943*/	mov byte ptr ss:[esp+0x21C],bl
	/*0058394A*/	mov dword ptr ds:[esi+0x8],eax
	/*0058394D*/	jne _005839AD						// All good so jne
	/*0058394F*/	lea eax,dword ptr ss:[esp+0x114]
	/*00583956*/	lea ecx,dword ptr ss:[esp+0x14]
	/*0058395A*/	push eax
	/*0058395B*/	push ecx
	/*0058395C*/	push ebx
	/*0058395D*/	push ebx
	/*0058395E*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00583963*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00583968*/	add esp,0x14
	/*0058396B*/	lea edx,dword ptr ss:[esp+0x114]
	/*00583972*/	lea eax,dword ptr ss:[esp+0x14]
	/*00583976*/	push 0x89
	/*0058397B*/	push edx
	/*0058397C*/	push eax
_0058397D:
	/*0058397D*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*00583982*/	push eax
	/*00583983*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*00583988*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*0058398D*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*00583992*/	push ebx
	/*00583993*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00583998*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*0058399D*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*005839A2*/	add esp,0x24
	/*005839A5*/	mov dword ptr ds:[0xB67A34],ebx
	/*005839AB*/	jmp _005839B4
_005839AD:
	/*005839AD*/	mov ecx,esi
	/*005839AF*/	call sub_586900		/*call <cm0102.sub_586900>*/ // in european_cup.cpp
_005839B4:
	/*005839B4*/	mov ecx,dword ptr ss:[esp+0x214]
	/*005839BB*/	mov eax,esi
	/*005839BD*/	pop edi
	/*005839BE*/	pop esi
	/*005839BF*/	pop ebx
	/*005839C0*/	mov dword ptr fs:[0x0],ecx
	/*005839C7*/	add esp,0x214
	/*005839CD*/	ret 0x8
	}
}

extern "C" void __declspec(naked) sub_5839D0()
{
	__asm pushad
	dprintf("sub_5839D0 Called!\n");
	__asm popad


	__asm
	{
	/*005839D0*/	xor eax,eax
	/*005839D2*/	ret 0x8
	}
}

extern "C" void __declspec(naked) sub_5839E0()
{
	__asm pushad
	dprintf("sub_5839E0 Called!\n");
	__asm popad

	__asm
	{
	/*005839E0*/	push esi
	/*005839E1*/	mov esi,ecx
	/*005839E3*/	call sub_583A00		/*call <cm0102.sub_583A00>*/
	/*005839E8*/	test byte ptr ss:[esp+0x8],0x1
	/*005839ED*/	je _005839F8
	/*005839EF*/	push esi
	/*005839F0*/	call cm0102_maybe_free1		/*call <cm0102.cm0102_maybe_free1>*/
	/*005839F5*/	add esp,0x4
_005839F8:
	/*005839F8*/	mov eax,esi
	/*005839FA*/	pop esi
	/*005839FB*/	ret 0x4
	}
}

extern "C" void __declspec(naked) sub_583A00()
{
	__asm pushad
	dprintf("sub_583A00 Called!\n");
	__asm popad

	__asm
	{
	/*00583A00*/	push 0xFFFFFFFF
	/*00583A02*/	push 0x958A98		/*push <cm0102.sub_958A98>*/
	/*00583A07*/	mov eax,dword ptr fs:[0x0]
	/*00583A0D*/	push eax
	/*00583A0E*/	mov dword ptr fs:[0x0],esp
	/*00583A15*/	push ecx
	/*00583A16*/	push esi
	/*00583A17*/	mov esi,ecx
	/*00583A19*/	push edi
	/*00583A1A*/	mov dword ptr ss:[esp+0x8],esi
	/*00583A1E*/	mov dword ptr ds:[esi],0x96A1D0		/*mov dword ptr ds:[esi],<cm0102.&sub_5839E0>*/
	/*00583A24*/	mov eax,dword ptr ds:[esi+0xA7]
	/*00583A2A*/	mov dword ptr ss:[esp+0x14],0x0
	/*00583A32*/	test eax,eax
	/*00583A34*/	je _00583A3F
	/*00583A36*/	push eax
	/*00583A37*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00583A3C*/	add esp,0x4
_00583A3F:
	/*00583A3F*/	mov eax,dword ptr ds:[esi+0xA3]
	/*00583A45*/	test eax,eax
	/*00583A47*/	je _00583A52
	/*00583A49*/	push eax
	/*00583A4A*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00583A4F*/	add esp,0x4
_00583A52:
	/*00583A52*/	mov eax,dword ptr ds:[esi+0xAD]
	/*00583A58*/	test eax,eax
	/*00583A5A*/	je _00583A92
	/*00583A5C*/	xor edi,edi
	/*00583A5E*/	cmp word ptr ds:[esi+0x3C],di
	/*00583A62*/	jle _00583A83
_00583A64:
	/*00583A64*/	mov eax,dword ptr ds:[esi+0xAD]
	/*00583A6A*/	mov eax,dword ptr ds:[eax+edi*0x4]
	/*00583A6D*/	test eax,eax
	/*00583A6F*/	je _00583A7A
	/*00583A71*/	push eax
	/*00583A72*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00583A77*/	add esp,0x4
_00583A7A:
	/*00583A7A*/	movsx ecx,word ptr ds:[esi+0x3C]
	/*00583A7E*/	inc edi
	/*00583A7F*/	cmp edi,ecx
	/*00583A81*/	jl _00583A64
_00583A83:
	/*00583A83*/	mov edx,dword ptr ds:[esi+0xAD]
	/*00583A89*/	push edx
	/*00583A8A*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00583A8F*/	add esp,0x4
_00583A92:
	/*00583A92*/	mov eax,dword ptr ds:[esi+0x30]
	/*00583A95*/	xor edi,edi
	/*00583A97*/	test eax,eax
	/*00583A99*/	jl _00583AB3
_00583A9B:
	/*00583A9B*/	mov eax,dword ptr ds:[esi+0xC]
	/*00583A9E*/	mov ecx,dword ptr ds:[eax+edi*0x4]
	/*00583AA1*/	test ecx,ecx
	/*00583AA3*/	je _00583AAB
	/*00583AA5*/	mov edx,dword ptr ds:[ecx]
	/*00583AA7*/	push 0x1
	/*00583AA9*/	call dword ptr ds:[edx]
_00583AAB:
	/*00583AAB*/	mov eax,dword ptr ds:[esi+0x30]
	/*00583AAE*/	inc edi
	/*00583AAF*/	cmp edi,eax
	/*00583AB1*/	jle _00583A9B
_00583AB3:
	/*00583AB3*/	mov eax,dword ptr ds:[esi+0xC]
	/*00583AB6*/	test eax,eax
	/*00583AB8*/	je _00583ACA
	/*00583ABA*/	push eax
	/*00583ABB*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00583AC0*/	add esp,0x4
	/*00583AC3*/	mov dword ptr ds:[esi+0xC],0x0
_00583ACA:
	/*00583ACA*/	mov edi,dword ptr ds:[esi+0x8]
	/*00583ACD*/	test edi,edi
	/*00583ACF*/	je _00583AE1
	/*00583AD1*/	mov ecx,edi
	/*00583AD3*/	call sub_49F450		/*call cm0102.49F450*/
	/*00583AD8*/	push edi
	/*00583AD9*/	call cm0102_maybe_free1		/*call <cm0102.cm0102_maybe_free1>*/
	/*00583ADE*/	add esp,0x4
_00583AE1:
	/*00583AE1*/	mov ecx,esi
	/*00583AE3*/	mov dword ptr ss:[esp+0x14],0xFFFFFFFF
	/*00583AEB*/	call sub_518690		/*call cm0102.518690*/
	/*00583AF0*/	mov ecx,dword ptr ss:[esp+0xC]
	/*00583AF4*/	pop edi
	/*00583AF5*/	pop esi
	/*00583AF6*/	mov dword ptr fs:[0x0],ecx
	/*00583AFD*/	add esp,0x10
	/*00583B00*/	ret
	}
}

extern "C" void __declspec(naked) sub_583B10()			// Gets called as part of match_day (initially 9 times for the first round results)
{
	__asm pushad
	dprintf("sub_583B10 Called!\n");
	__asm popad

	__asm
	{
	/*00583B10*/	push ebx
	/*00583B11*/	push esi
	/*00583B12*/	mov esi,dword ptr ss:[esp+0xC]		// Competition? First 4 bytes are the ID (46 01 00 00)
	/*00583B16*/	push edi
	/*00583B17*/	xor edi,edi
	/*00583B19*/	mov ebx,ecx
	/*00583B1B*/	mov al,byte ptr ds:[esi+0x47]		// is FF 
	/*00583B1E*/	cmp al,0xFF
	/*00583B20*/	je _00583B27
	/*00583B22*/	mov cl,byte ptr ds:[esi+0x48]		// Would be FF too
	/*00583B25*/	jmp _00583B2D
_00583B27:
	/*00583B27*/	mov al,byte ptr ds:[esi+0x43]		// 02
	/*00583B2A*/	mov cl,byte ptr ds:[esi+0x44]		// 01
_00583B2D:
	/*00583B2D*/	cmp al,cl
	/*00583B2F*/	jle _00583B4A
	/*00583B31*/	mov eax,dword ptr ds:[esi+0x1C]		// Looks to be a team (Avenir Beggen is first)
	/*00583B34*/	push 0x2
	/*00583B36*/	mov ecx,dword ptr ds:[eax+0x53]		// Get the clubs nation
	/*00583B39*/	push ecx
	/*00583B3A*/	mov ecx,dword ptr ds:[0xDE1F58]		//  contains an address of the UEFA Country Rankings
	/*00583B40*/	call sub_9058B0		/*call <cm0102.sub_9058B0>*/
	/*00583B45*/	mov edi,dword ptr ds:[esi+0x1C]
	/*00583B48*/	jmp _00583B8D
_00583B4A:
	/*00583B4A*/	jge _00583B65
	/*00583B4C*/	mov edx,dword ptr ds:[esi+0x20]
	/*00583B4F*/	mov ecx,dword ptr ds:[0xDE1F58]		//  contains an address of the UEFA Country Rankings
	/*00583B55*/	push 0x2
	/*00583B57*/	mov eax,dword ptr ds:[edx+0x53]
	/*00583B5A*/	push eax
	/*00583B5B*/	call sub_9058B0		/*call <cm0102.sub_9058B0>*/
	/*00583B60*/	mov edi,dword ptr ds:[esi+0x20]
	/*00583B63*/	jmp _00583B8D
_00583B65:
	/*00583B65*/	mov ecx,dword ptr ds:[esi+0x1C]
	/*00583B68*/	push 0x1
	/*00583B6A*/	mov edx,dword ptr ds:[ecx+0x53]
	/*00583B6D*/	mov ecx,dword ptr ds:[0xDE1F58]		//  contains an address of the UEFA Country Rankings
	/*00583B73*/	push edx
	/*00583B74*/	call sub_9058B0		/*call <cm0102.sub_9058B0>*/
	/*00583B79*/	mov eax,dword ptr ds:[esi+0x20]
	/*00583B7C*/	push 0x1
	/*00583B7E*/	mov ecx,dword ptr ds:[eax+0x53]
	/*00583B81*/	push ecx
	/*00583B82*/	mov ecx,dword ptr ds:[0xDE1F58]		//  contains an address of the UEFA Country Rankings
	/*00583B88*/	call sub_9058B0		/*call <cm0102.sub_9058B0>*/
_00583B8D:
	/*00583B8D*/	mov al,byte ptr ds:[esi+0x42]		// FF
	/*00583B90*/	cmp al,0xFF
	/*00583B92*/	jle _00583C35						// Actually does this big jmp
	/*00583B98*/	cmp al,0xC							
	/*00583B9A*/	jge _00583C35
	/*00583BA0*/	test edi,edi
	/*00583BA2*/	je _00583BCD
	/*00583BA4*/	mov ecx,dword ptr ds:[0xAE2A38]			// ???
	/*00583BAA*/	push 0x30D40
	/*00583BAF*/	push edi
	/*00583BB0*/	call sub_5A0590		/*call <cm0102.sub_5A0590>*/
	/*00583BB5*/	mov ecx,eax
	/*00583BB7*/	call sub_5999A0		/*call <cm0102.sub_5999A0>*/
	/*00583BBC*/	push 0xFFFFFFFE
	/*00583BBE*/	push esi
	/*00583BBF*/	push 0x0
	/*00583BC1*/	push 0xFFFFFFFF
	/*00583BC3*/	push 0x0
	/*00583BC5*/	push 0x30D40
	/*00583BCA*/	push edi
	/*00583BCB*/	jmp _00583C2E
_00583BCD:
	/*00583BCD*/	mov edx,dword ptr ds:[esi+0x1C]
	/*00583BD0*/	mov ecx,dword ptr ds:[0xAE2A38]			// ???
	/*00583BD6*/	push 0x186A0
	/*00583BDB*/	push edx
	/*00583BDC*/	call sub_5A0590		/*call <cm0102.sub_5A0590>*/
	/*00583BE1*/	mov ecx,eax
	/*00583BE3*/	call sub_5999A0		/*call <cm0102.sub_5999A0>*/
	/*00583BE8*/	mov eax,dword ptr ds:[esi+0x20]
	/*00583BEB*/	mov ecx,dword ptr ds:[0xAE2A38]			// ???
	/*00583BF1*/	push 0x186A0
	/*00583BF6*/	push eax
	/*00583BF7*/	call sub_5A0590		/*call <cm0102.sub_5A0590>*/
	/*00583BFC*/	mov ecx,eax
	/*00583BFE*/	call sub_5999A0		/*call <cm0102.sub_5999A0>*/
	/*00583C03*/	mov ecx,dword ptr ds:[esi+0x1C]
	/*00583C06*/	push 0xFFFFFFFE
	/*00583C08*/	push esi
	/*00583C09*/	push 0x0
	/*00583C0B*/	push 0xFFFFFFFF
	/*00583C0D*/	push 0x0
	/*00583C0F*/	push 0x186A0
	/*00583C14*/	push ecx
	/*00583C15*/	mov ecx,ebx
	/*00583C17*/	call sub_48E3E0		/*call cm0102.48E3E0*/
	/*00583C1C*/	mov edx,dword ptr ds:[esi+0x20]
	/*00583C1F*/	push 0xFFFFFFFE
	/*00583C21*/	push esi
	/*00583C22*/	push 0x0
	/*00583C24*/	push 0xFFFFFFFF
	/*00583C26*/	push 0x0
	/*00583C28*/	push 0x186A0
	/*00583C2D*/	push edx
_00583C2E:
	/*00583C2E*/	mov ecx,ebx
	/*00583C30*/	call sub_48E3E0		/*call cm0102.48E3E0*/		// Part of comp.cpp
_00583C35:
	/*00583C35*/	mov eax,dword ptr ss:[esp+0x14]			// Has the value 430 in it?
	/*00583C39*/	mov ecx,ebx
	/*00583C3B*/	push eax				// 430
	/*00583C3C*/	push esi				// League pointer
	/*00583C3D*/	call sub_51A150		/*call cm0102.51A150*/		// Cup.cpp code
	/*00583C42*/	pop edi
	/*00583C43*/	pop esi
	/*00583C44*/	pop ebx
	/*00583C45*/	ret 0x8
	}
}

extern "C" void __declspec(naked) european_cup_schedule_583C50()
{
	__asm pushad
	dprintf("european_cup_schedule_583C50 Called!\n");
	__asm popad

	__asm
	{
	/*00583C50*/	mov eax,dword ptr fs:[0x0]
	/*00583C56*/	push 0xFFFFFFFF
	/*00583C58*/	push 0x958AC6		/*push <cm0102.sub_958AC6>*/
	/*00583C5D*/	push eax
	/*00583C5E*/	mov al,byte ptr ss:[esp+0x10]
	/*00583C62*/	mov dword ptr fs:[0x0],esp
	/*00583C69*/	sub esp,0x418
	/*00583C6F*/	cmp al,0xFF		// is true
	/*00583C71*/	push ebx		// 0
	/*00583C72*/	push ebp		// FFFFFFFF
	/*00583C73*/	push esi		// League Struct (D0 A1 96 00)
	/*00583C74*/	push edi		// League Struct + 3A ??
	/*00583C75*/	mov edi,ecx		// League Struct (same as esi)
	/*00583C77*/	jne _00583EA6
	/*00583C7D*/	mov eax,dword ptr ss:[esp+0x444]	// 0
	/*00583C84*/	xor ebx,ebx
	/*00583C86*/	cmp eax,ebx
	/*00583C88*/	je _00583C8C						// Taken
	/*00583C8A*/	mov dword ptr ds:[eax],ebx
_00583C8C:
	/*00583C8C*/	mov eax,dword ptr ss:[esp+0x43C]
	/*00583C93*/	mov ecx,dword ptr ss:[esp+0x440]	// ecx = League Struct + c4
	/*00583C9A*/	mov ebp,0x3							// Number of qualifying stages!
	/*00583C9F*/	push 0x138							// 312 bytes for the schedule
	/*00583CA4*/	mov word ptr ds:[eax],bp			// make 3 (already was 0)	// Sets the number of qualifying stages
	/*00583CA7*/	mov word ptr ds:[ecx],bx			// make 0 (already was 0)
	/*00583CAA*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*00583CAF*/	mov esi,eax							// New Memory in esi and eax
	/*00583CB1*/	add esp,0x4
	/*00583CB4*/	cmp esi,ebx							// if we have memory 
	/*00583CB6*/	jne _00583CEA						// skip 
	/*00583CB8*/	lea edx,dword ptr ss:[esp+0x28]		
	/*00583CBC*/	lea eax,dword ptr ss:[esp+0x128]
	/*00583CC3*/	push edx
	/*00583CC4*/	push eax
	/*00583CC5*/	push ebx
	/*00583CC6*/	push ebx
	/*00583CC7*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00583CCC*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00583CD1*/	add esp,0x14
	/*00583CD4*/	lea ecx,dword ptr ss:[esp+0x28]
	/*00583CD8*/	lea edx,dword ptr ss:[esp+0x128]
	/*00583CDF*/	push 0x12C
	/*00583CE4*/	push ecx
	/*00583CE5*/	jmp _005842F8
_00583CEA:
	/*00583CEA*/	movsx eax,word ptr ds:[edi+0x40]	// edi = League Struct (D0 A1 96 00) = year		// First Qualifying Phase First Leg
	/*00583CEE*/	push eax		// 2001
	/*00583CEF*/	push 0x2		// 2
	/*00583CF1*/	push ebx		// 0
	/*00583CF2*/	push 0x5		// 5  // Unknown
	/*00583CF4*/	push 0x1C		// 28 // Unknown
	/*00583CF6*/	push ebx		// 0
	/*00583CF7*/	push esi		// our allocated memory
	/*00583CF8*/	call sub_521E60		/*call <cm0102.sub_521E60>*/		// cup.cpp
	/*00583CFD*/	movsx ecx,word ptr ds:[edi+0x40]	// year
	/*00583D01*/	push ebx		// 0
	/*00583D02*/	push ecx		// year
	/*00583D03*/	push 0x2		// 2  // Unknown?
	/*00583D05*/	push 0x2		// 2  // Day of week (Weds)
	/*00583D07*/	push ebx		// 0
	/*00583D08*/	push 0x6		// 6  // July
	/*00583D0A*/	push 0xC		// 12 // Day of Month
	/*00583D0C*/	push ebx		// 0
	/*00583D0D*/	push esi		// our allocated memory
	/*00583D0E*/	call sub_521EB0		/*call <cm0102.sub_521EB0>*/
	/*00583D13*/	mov word ptr ds:[esi+0x7],0xFA		// 250
	/*00583D19*/	mov word ptr ds:[esi+0x9],bx		// 0
	/*00583D1D*/	mov word ptr ds:[esi+0xB],0x4		// 4  // Unknown
	/*00583D23*/	mov word ptr ds:[esi+0xD],bx		// 0
	/*00583D27*/	mov eax,0x12
	/*00583D2C*/	mov byte ptr ds:[esi+0x17],0x8		// 8
	/*00583D30*/	mov word ptr ds:[esi+0x18],ax		// 18
	/*00583D34*/	mov word ptr ds:[esi+0x1A],0x9		// 9
	/*00583D3A*/	mov word ptr ds:[esi+0x1C],ax		// 18
	/*00583D3E*/	mov word ptr ds:[esi+0xF],bp		// 3		// Number of qualifying stages?
	/*00583D42*/	mov word ptr ds:[esi+0x1E],bx		// 0
	/*00583D46*/	mov byte ptr ds:[esi+0x20],bl		// 0
	/*00583D49*/	mov byte ptr ds:[esi+0x21],0x2		// 2		// Number of legs (if set to 1 then it doesn't even list the legs)
	/*00583D4D*/	mov byte ptr ds:[esi+0x22],0x7		// 7		// Number of days until the 2nd leg is played after the first leg
	/*00583D51*/	mov dword ptr ds:[esi+0x5C],ebx		// 0
	/*00583D54*/	mov dword ptr ds:[esi+0x60],ebx		// 0
	/*00583D57*/	mov dword ptr ds:[esi+0x64],ebx		// 0
	/*00583D5A*/	add esp,0x40
	/*00583D5D*/	movsx edx,word ptr ds:[edi+0x40]												// Second Qualifying Phase First Leg
	/*00583D61*/	push edx		// 2001
	/*00583D62*/	push 0x2		// 2
	/*00583D64*/	push ebx		// 0
	/*00583D65*/	push 0x5		// 5
	/*00583D67*/	push 0x1C		// 28
	/*00583D69*/	push 0x1		// 1
	/*00583D6B*/	push esi		// our allocated memory
	/*00583D6C*/	call sub_521E60		/*call <cm0102.sub_521E60>*/
	/*00583D71*/	movsx eax,word ptr ds:[edi+0x40]
	/*00583D75*/	push ebx		// 0
	/*00583D76*/	push eax		// 2001
	/*00583D77*/	push 0x2		// 2
	/*00583D79*/	push 0x2		// 2  // Day of Week (Weds)
	/*00583D7B*/	push ebx		// 0
	/*00583D7C*/	push 0x6		// 6  // July
	/*00583D7E*/	push 0x1A		// 26 // Day of Month
	/*00583D80*/	push 0x1		// 1
	/*00583D82*/	push esi		// our allocated memory
	/*00583D83*/	call sub_521EB0		/*call <cm0102.sub_521EB0>*/
	/*00583D88*/	mov word ptr ds:[esi+0x6F],0x104	// addr: 0x68 + 7 value: 260
	/*00583D8E*/	mov word ptr ds:[esi+0x71],0x1		// addr: 0x68 + 9 value: 1  Round?
	/*00583D94*/	mov word ptr ds:[esi+0x73],0x4		// 4
	/*00583D9A*/	mov word ptr ds:[esi+0x75],0x400	// 1024  // Flags?
	/*00583DA0*/	mov byte ptr ds:[esi+0x7F],0x8		// 8
	/*00583DA4*/	mov word ptr ds:[esi+0x80],0x1C		// 28
	/*00583DAD*/	mov word ptr ds:[esi+0x82],0xE		// 14
	/*00583DB6*/	mov word ptr ds:[esi+0x84],0x13		// 19
	/*00583DBF*/	mov word ptr ds:[esi+0x77],bp		// 3		// Number of qualifying stages?
	/*00583DC3*/	mov word ptr ds:[esi+0x86],0x12		// 18
	/*00583DCC*/	mov byte ptr ds:[esi+0x88],bl		// 0
	/*00583DD2*/	mov byte ptr ds:[esi+0x89],0x2		// 2
	/*00583DD9*/	mov byte ptr ds:[esi+0x8A],0x7		// 7
	/*00583DE0*/	mov dword ptr ds:[esi+0xC4],ebx		// 0
	/*00583DE6*/	mov dword ptr ds:[esi+0xC8],ebx		// 0
	/*00583DEC*/	mov dword ptr ds:[esi+0xCC],ebx		// 0
	/*00583DF2*/	movsx ecx,word ptr ds:[edi+0x40]												// Third Qualifying Phase First Leg
	/*00583DF6*/	add esp,0x40
	/*00583DF9*/	push ecx		// 2001
	/*00583DFA*/	push 0x4		// 4
	/*00583DFC*/	push ebx		// 0
	/*00583DFD*/	push 0x6		// 6
	/*00583DFF*/	push 0x15		// 21
	/*00583E01*/	push 0x2		// 2
	/*00583E03*/	push esi		// our allocated memory
	/*00583E04*/	call sub_521E60		/*call <cm0102.sub_521E60>*/
	/*00583E09*/	movsx edx,word ptr ds:[edi+0x40]
	/*00583E0D*/	push ebx		// 0
	/*00583E0E*/	push edx		// 2001
	/*00583E0F*/	push 0x2		// 2
	/*00583E11*/	push 0x2		// 2
	/*00583E13*/	push ebx		// 0
	/*00583E14*/	push 0x7		// 7
	/*00583E16*/	push 0x9		// 9
	/*00583E18*/	push 0x2		// 2
	/*00583E1A*/	push esi		// our allocated memory
	/*00583E1B*/	call sub_521EB0		/*call <cm0102.sub_521EB0>*/
	/*00583E20*/	add esp,0x40
	/*00583E23*/	mov word ptr ds:[esi+0xD7],0x10E	// 270
	/*00583E2C*/	mov word ptr ds:[esi+0xD9],0x2		// 2  Round?
	/*00583E35*/	mov word ptr ds:[esi+0xDB],0x4		// 4
	/*00583E3E*/	mov word ptr ds:[esi+0xDD],0x400	// 1024
	/*00583E47*/	mov byte ptr ds:[esi+0xE7],0x8		// 8
	/*00583E4E*/	mov word ptr ds:[esi+0xE8],0x20		// 32
	/*00583E57*/	mov word ptr ds:[esi+0xEA],0x10		// 16
	/*00583E60*/	mov word ptr ds:[esi+0xEC],0x12		// 18
	/*00583E69*/	mov word ptr ds:[esi+0xDF],bp		// 3		// Number of qualifying stages?
	/*00583E70*/	mov word ptr ds:[esi+0xEE],0x25		// 37
	/*00583E79*/	mov byte ptr ds:[esi+0xF0],bl		// 0
	/*00583E7F*/	mov byte ptr ds:[esi+0xF1],0x2		// 2
	/*00583E86*/	mov byte ptr ds:[esi+0xF2],0xE		// 14
	/*00583E8D*/	mov dword ptr ds:[esi+0x12C],ebx	// 0
	/*00583E93*/	mov dword ptr ds:[esi+0x130],ebx	// 0
	/*00583E99*/	mov dword ptr ds:[esi+0x134],ebx	// 0
	/*00583E9F*/	mov eax,esi
	/*00583EA1*/	jmp _exit_sub
_00583EA6:
	/*00583EA6*/	cmp al,0x8							// When first called al == 0xC. When called by the Schedule tab it calls 0xC number of times
	/*00583EA8*/	jge _0058406B
	/*00583EAE*/	mov ecx,dword ptr ss:[esp+0x444]
	/*00583EB5*/	xor ebx,ebx
	/*00583EB7*/	cmp ecx,ebx
	/*00583EB9*/	je _00583EC1
	/*00583EBB*/	mov dword ptr ds:[ecx],0x1
_00583EC1:
	/*00583EC1*/	mov ecx,dword ptr ss:[esp+0x43C]
	/*00583EC8*/	push 0x186							// Allocate 390 bytes
	/*00583ECD*/	movsx dx,al
	/*00583ED1*/	mov eax,dword ptr ss:[esp+0x444]
	/*00583ED8*/	add edx,0x43D
	/*00583EDE*/	mov word ptr ds:[ecx],0x6
	/*00583EE3*/	mov word ptr ds:[eax],dx
	/*00583EE6*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*00583EEB*/	mov esi,eax							// 390 bytes into esi
	/*00583EED*/	add esp,0x4
	/*00583EF0*/	cmp esi,ebx
	/*00583EF2*/	jne _00583F27
	/*00583EF4*/	lea ecx,dword ptr ss:[esp+0x128]
	/*00583EFB*/	lea edx,dword ptr ss:[esp+0x28]
	/*00583EFF*/	push ecx
	/*00583F00*/	push edx
	/*00583F01*/	push ebx
	/*00583F02*/	push ebx
	/*00583F03*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00583F08*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00583F0D*/	add esp,0x14
	/*00583F10*/	lea eax,dword ptr ss:[esp+0x128]
	/*00583F17*/	lea ecx,dword ptr ss:[esp+0x28]
	/*00583F1B*/	push 0x17A
	/*00583F20*/	push eax
	/*00583F21*/	push ecx
	/*00583F22*/	jmp _005842F9
_00583F27:			// This schedule is not in the order that you see it in the schedule tab
	/*00583F27*/	mov al,byte ptr ss:[esp+0x438]		// Schedule Part
	/*00583F2E*/	mov dx,word ptr ds:[edi+0x40]		// 2001 (year)
	/*00583F32*/	push ebx							// 0
	/*00583F33*/	cmp al,0x4
	/*00583F35*/	push edx							// 2001 (year )
	/*00583F36*/	push 0x2							// 2
	/*00583F38*/	jge _00583FBF
	/*00583F3E*/	push 0x1							// 1		// Day of Week (Tues)
	/*00583F40*/	push ebx							// 0
	/*00583F41*/	push 0x8							// 8		// Month (Sept)
	/*00583F43*/	push 0xC							// 12		// Day Of Month
	/*00583F45*/	push ebx							// 0		// Round?
	/*00583F46*/	push esi							// Memory Block
	/*00583F47*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00583F4C*/	mov ax,word ptr ds:[edi+0x40]
	/*00583F50*/	push ebx							// 0
	/*00583F51*/	push eax							// 2001 (year)
	/*00583F52*/	push 0x2							// 2
	/*00583F54*/	push 0x2							// 2
	/*00583F56*/	push ebx							// 0
	/*00583F57*/	push 0x8							// 8
	/*00583F59*/	push 0x14							// 20
	/*00583F5B*/	push 0x1							// 1
	/*00583F5D*/	push esi							// Memory Block
	/*00583F5E*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00583F63*/	mov cx,word ptr ds:[edi+0x40]
	/*00583F67*/	add esp,0x48
	/*00583F6A*/	push ebx							// 0
	/*00583F6B*/	push ecx							// 2001 (year)
	/*00583F6C*/	push 0x2							// 2
	/*00583F6E*/	push 0x2							// 2
	/*00583F70*/	push ebx							// 0
	/*00583F71*/	push 0x8							// 8
	/*00583F73*/	push 0x1B							// 27
	/*00583F75*/	push 0x2							// 2
	/*00583F77*/	push esi							// Memory Block
	/*00583F78*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00583F7D*/	mov dx,word ptr ds:[edi+0x40]
	/*00583F81*/	push ebx							// 0 
	/*00583F82*/	push edx							// 2001 (year)
	/*00583F83*/	push 0x2							// 2
	/*00583F85*/	push 0x1							// 1
	/*00583F87*/	push ebx							// 0
	/*00583F88*/	push 0x9							// 9
	/*00583F8A*/	push 0x11							// 17
	/*00583F8C*/	push 0x3							// 3
	/*00583F8E*/	push esi							// Memory Block
	/*00583F8F*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00583F94*/	mov ax,word ptr ds:[edi+0x40]
	/*00583F98*/	add esp,0x48
	/*00583F9B*/	push ebx
	/*00583F9C*/	push eax
	/*00583F9D*/	push 0x2
	/*00583F9F*/	push 0x2
	/*00583FA1*/	push ebx
	/*00583FA2*/	push 0x9
	/*00583FA4*/	push 0x19
	/*00583FA6*/	push 0x4
	/*00583FA8*/	push esi
	/*00583FA9*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00583FAE*/	mov cx,word ptr ds:[edi+0x40]
	/*00583FB2*/	push ebx
	/*00583FB3*/	push ecx
	/*00583FB4*/	push 0x2
	/*00583FB6*/	push 0x1
	/*00583FB8*/	push ebx
	/*00583FB9*/	push 0xA
	/*00583FBB*/	push 0x7
	/*00583FBD*/	jmp _0058403E
_00583FBF:
	/*00583FBF*/	push 0x2
	/*00583FC1*/	push ebx
	/*00583FC2*/	push 0x8
	/*00583FC4*/	push 0xD
	/*00583FC6*/	push ebx
	/*00583FC7*/	push esi
	/*00583FC8*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00583FCD*/	mov ax,word ptr ds:[edi+0x40]
	/*00583FD1*/	push ebx
	/*00583FD2*/	push eax
	/*00583FD3*/	push 0x2
	/*00583FD5*/	push 0x1
	/*00583FD7*/	push ebx
	/*00583FD8*/	push 0x8
	/*00583FDA*/	push 0x13
	/*00583FDC*/	push 0x1
	/*00583FDE*/	push esi
	/*00583FDF*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00583FE4*/	mov cx,word ptr ds:[edi+0x40]
	/*00583FE8*/	add esp,0x48
	/*00583FEB*/	push ebx
	/*00583FEC*/	push ecx
	/*00583FED*/	push 0x2
	/*00583FEF*/	push 0x1
	/*00583FF1*/	push ebx
	/*00583FF2*/	push 0x8
	/*00583FF4*/	push 0x1A
	/*00583FF6*/	push 0x2
	/*00583FF8*/	push esi
	/*00583FF9*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00583FFE*/	mov dx,word ptr ds:[edi+0x40]
	/*00584002*/	push ebx
	/*00584003*/	push edx
	/*00584004*/	push 0x2
	/*00584006*/	push 0x2
	/*00584008*/	push ebx
	/*00584009*/	push 0x9
	/*0058400B*/	push 0x12
	/*0058400D*/	push 0x3
	/*0058400F*/	push esi
	/*00584010*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00584015*/	mov ax,word ptr ds:[edi+0x40]
	/*00584019*/	add esp,0x48
	/*0058401C*/	push ebx
	/*0058401D*/	push eax
	/*0058401E*/	push 0x2
	/*00584020*/	push 0x1
	/*00584022*/	push ebx
	/*00584023*/	push 0x9
	/*00584025*/	push 0x18
	/*00584027*/	push 0x4
	/*00584029*/	push esi
	/*0058402A*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*0058402F*/	mov cx,word ptr ds:[edi+0x40]
	/*00584033*/	push ebx
	/*00584034*/	push ecx
	/*00584035*/	push 0x2
	/*00584037*/	push 0x2
	/*00584039*/	push ebx
	/*0058403A*/	push 0xA
	/*0058403C*/	push 0x8
_0058403E:
	/*0058403E*/	push 0x5
	/*00584040*/	push esi
	/*00584041*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00584046*/	add esp,0x48
	/*00584049*/	xor edi,edi
_0058404B:
	/*0058404B*/	push ebx							// 0
	/*0058404C*/	push 0xFFFFFFFF						// -1
	/*0058404E*/	push 0xFFFFFFFF						// -1
	/*00584050*/	push 0xFFFFFFFF						// -1
	/*00584052*/	push ebx							// 0
	/*00584053*/	push edi							// 0?
	/*00584054*/	push esi							// Memory Block
	/*00584055*/	call cm0102_set_fixture_68A1C0		/*call <cm0102.cm0102_set_fixture_68A1C0>*/
	/*0058405A*/	add esp,0x1C
	/*0058405D*/	inc edi
	/*0058405E*/	cmp di,0x6
	/*00584062*/	jl _0058404B
	/*00584064*/	mov eax,esi
	/*00584066*/	jmp _exit_sub
_0058406B:
	/*0058406B*/	cmp al,0xC						// <--- Second time its called - it does 0xC
	/*0058406D*/	jge _00584284
	/*00584073*/	mov ecx,dword ptr ss:[esp+0x444]
	/*0058407A*/	xor ebx,ebx
	/*0058407C*/	cmp ecx,ebx
	/*0058407E*/	je _00584086
	/*00584080*/	mov dword ptr ds:[ecx],0x1
_00584086:
	/*00584086*/	mov edx,dword ptr ss:[esp+0x43C]
	/*0058408D*/	mov ecx,dword ptr ss:[esp+0x440]
	/*00584094*/	movsx ax,al
	/*00584098*/	add eax,0x43D
	/*0058409D*/	mov word ptr ds:[edx],0x6
	/*005840A2*/	push 0x186
	/*005840A7*/	mov word ptr ds:[ecx],ax
	/*005840AA*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*005840AF*/	mov esi,eax
	/*005840B1*/	add esp,0x4
	/*005840B4*/	cmp esi,ebx
	/*005840B6*/	jne _005840EA
	/*005840B8*/	lea edx,dword ptr ss:[esp+0x128]
	/*005840BF*/	lea eax,dword ptr ss:[esp+0x28]
	/*005840C3*/	push edx
	/*005840C4*/	push eax
	/*005840C5*/	push ebx
	/*005840C6*/	push ebx
	/*005840C7*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005840CC*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*005840D1*/	add esp,0x14
	/*005840D4*/	lea ecx,dword ptr ss:[esp+0x128]
	/*005840DB*/	lea edx,dword ptr ss:[esp+0x28]
	/*005840DF*/	push 0x1AA
	/*005840E4*/	push ecx
	/*005840E5*/	jmp _005842F8
_005840EA:
	/*005840EA*/	mov ax,word ptr ds:[edi+0x40]
	/*005840EE*/	push 0x2
	/*005840F0*/	inc ax
	/*005840F2*/	lea ecx,dword ptr ss:[esp+0x14]
	/*005840F6*/	push eax
	/*005840F7*/	push 0x2
	/*005840F9*/	push 0x1
	/*005840FB*/	call cm0102_DateConvert		/*call <cm0102.cm0102_DateConvert>*/
	/*00584100*/	lea ecx,dword ptr ss:[esp+0x18]
	/*00584104*/	push 0x1
	/*00584106*/	push ecx
	/*00584107*/	lea ecx,dword ptr ss:[esp+0x18]
	/*0058410B*/	mov dword ptr ss:[esp+0x438],ebx
	/*00584112*/	call sub_54C8E0		/*call <cm0102.sub_54C8E0>*/
	/*00584117*/	lea edx,dword ptr ss:[esp+0x20]
	/*0058411B*/	push eax
	/*0058411C*/	push edx
	/*0058411D*/	lea ecx,dword ptr ss:[esp+0x18]
	/*00584121*/	mov byte ptr ss:[esp+0x438],0x1
	/*00584129*/	call sub_417C10		/*call <cm0102.sub_417C10>*/
	/*0058412E*/	mov al,byte ptr ss:[esp+0x438]
	/*00584135*/	push ebx
	/*00584136*/	cmp al,0xA
	/*00584138*/	mov ax,word ptr ds:[edi+0x40]
	/*0058413C*/	push eax
	/*0058413D*/	mov byte ptr ss:[esp+0x438],bl
	/*00584144*/	push 0x2
	/*00584146*/	jge _005841D4
	/*0058414C*/	push 0x1
	/*0058414E*/	push ebx
	/*0058414F*/	push 0xA
	/*00584151*/	push 0x15
	/*00584153*/	push ebx
	/*00584154*/	push esi
	/*00584155*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*0058415A*/	mov cx,word ptr ds:[edi+0x40]
	/*0058415E*/	push ebx
	/*0058415F*/	push ecx
	/*00584160*/	push 0x2
	/*00584162*/	push 0x2
	/*00584164*/	push ebx
	/*00584165*/	push 0xB
	/*00584167*/	push 0x6
	/*00584169*/	push 0x1
	/*0058416B*/	push esi
	/*0058416C*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00584171*/	mov dx,word ptr ds:[edi+0x40]
	/*00584175*/	add esp,0x48
	/*00584178*/	push ebx
	/*00584179*/	push edx
	/*0058417A*/	push 0x2
	/*0058417C*/	push 0x2
	/*0058417E*/	push 0x1
	/*00584180*/	push 0x1
	/*00584182*/	push 0xE
	/*00584184*/	push 0x2
	/*00584186*/	push esi
	/*00584187*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*0058418C*/	mov ax,word ptr ds:[edi+0x40]
	/*00584190*/	push ebx
	/*00584191*/	push eax
	/*00584192*/	push 0x2
	/*00584194*/	push 0x1
	/*00584196*/	push 0x1
	/*00584198*/	push 0x1
	/*0058419A*/	push 0x14
	/*0058419C*/	push 0x3
	/*0058419E*/	push esi
	/*0058419F*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*005841A4*/	mov cx,word ptr ds:[edi+0x40]
	/*005841A8*/	add esp,0x48
	/*005841AB*/	push ebx
	/*005841AC*/	push ecx
	/*005841AD*/	push 0x2
	/*005841AF*/	push 0x2
	/*005841B1*/	push 0x1
	/*005841B3*/	push 0x2
	/*005841B5*/	push 0x7
	/*005841B7*/	push 0x4
	/*005841B9*/	push esi
	/*005841BA*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*005841BF*/	mov dx,word ptr ds:[edi+0x40]
	/*005841C3*/	push ebx
	/*005841C4*/	push edx
	/*005841C5*/	push 0x2
	/*005841C7*/	push 0x1
	/*005841C9*/	push 0x1
	/*005841CB*/	push 0x2
	/*005841CD*/	push 0xD
	/*005841CF*/	jmp _00584257
_005841D4:
	/*005841D4*/	push 0x2
	/*005841D6*/	push ebx
	/*005841D7*/	push 0xA
	/*005841D9*/	push 0x16
	/*005841DB*/	push ebx
	/*005841DC*/	push esi
	/*005841DD*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*005841E2*/	mov cx,word ptr ds:[edi+0x40]
	/*005841E6*/	push ebx
	/*005841E7*/	push ecx
	/*005841E8*/	push 0x2
	/*005841EA*/	push 0x1
	/*005841EC*/	push ebx
	/*005841ED*/	push 0xB
	/*005841EF*/	push 0x5
	/*005841F1*/	push 0x1
	/*005841F3*/	push esi
	/*005841F4*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*005841F9*/	mov dx,word ptr ds:[edi+0x40]
	/*005841FD*/	add esp,0x48
	/*00584200*/	push ebx
	/*00584201*/	push edx
	/*00584202*/	push 0x2
	/*00584204*/	push 0x1
	/*00584206*/	push 0x1
	/*00584208*/	push 0x1
	/*0058420A*/	push 0xD
	/*0058420C*/	push 0x2
	/*0058420E*/	push esi
	/*0058420F*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00584214*/	mov ax,word ptr ds:[edi+0x40]
	/*00584218*/	push ebx
	/*00584219*/	push eax
	/*0058421A*/	push 0x2
	/*0058421C*/	push 0x2
	/*0058421E*/	push 0x1
	/*00584220*/	push 0x1
	/*00584222*/	push 0x15
	/*00584224*/	push 0x3
	/*00584226*/	push esi
	/*00584227*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*0058422C*/	mov cx,word ptr ds:[edi+0x40]
	/*00584230*/	add esp,0x48
	/*00584233*/	push ebx
	/*00584234*/	push ecx
	/*00584235*/	push 0x2
	/*00584237*/	push 0x1
	/*00584239*/	push 0x1
	/*0058423B*/	push 0x2
	/*0058423D*/	push 0x6
	/*0058423F*/	push 0x4
	/*00584241*/	push esi
	/*00584242*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*00584247*/	mov dx,word ptr ds:[edi+0x40]
	/*0058424B*/	push ebx
	/*0058424C*/	push edx
	/*0058424D*/	push 0x2
	/*0058424F*/	push 0x2
	/*00584251*/	push 0x1
	/*00584253*/	push 0x2
	/*00584255*/	push 0xE
_00584257:
	/*00584257*/	push 0x5
	/*00584259*/	push esi
	/*0058425A*/	call cm0102_to_set_date_fixture_68A160		/*call <cm0102.cm0102_to_set_date_fixture_68A160>*/
	/*0058425F*/	add esp,0x48
	/*00584262*/	xor edi,edi
_00584264:
	/*00584264*/	push ebx
	/*00584265*/	push 0xFFFFFFFF
	/*00584267*/	push 0xFFFFFFFF
	/*00584269*/	push 0xFFFFFFFF
	/*0058426B*/	push ebx
	/*0058426C*/	push edi
	/*0058426D*/	push esi
	/*0058426E*/	call cm0102_set_fixture_68A1C0		/*call <cm0102.cm0102_set_fixture_68A1C0>*/
	/*00584273*/	add esp,0x1C
	/*00584276*/	inc edi
	/*00584277*/	cmp di,0x6
	/*0058427B*/	jl _00584264
	/*0058427D*/	mov eax,esi
	/*0058427F*/	jmp _exit_sub
_00584284:
	/*00584284*/	jne _00584327
	/*0058428A*/	mov eax,dword ptr ss:[esp+0x444]		// <---- where it starts when al == 0C
	/*00584291*/	xor ebx,ebx
	/*00584293*/	cmp eax,ebx
	/*00584295*/	je _00584299
	/*00584297*/	mov dword ptr ds:[eax],ebx
_00584299:
	/*00584299*/	mov eax,dword ptr ss:[esp+0x43C]
	/*005842A0*/	mov ecx,dword ptr ss:[esp+0x440]
	/*005842A7*/	mov ebp,0x3								// Rounds of the finals 
	/*005842AC*/	push 0x138								// Allocate 312 bytes
	/*005842B1*/	mov word ptr ds:[eax],bp
	/*005842B4*/	mov word ptr ds:[ecx],bx
	/*005842B7*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*005842BC*/	mov esi,eax
	/*005842BE*/	add esp,0x4
	/*005842C1*/	cmp esi,ebx
	/*005842C3*/	jne _00584344
	/*005842C5*/	lea edx,dword ptr ss:[esp+0x228]
	/*005842CC*/	lea eax,dword ptr ss:[esp+0x328]
	/*005842D3*/	push edx
	/*005842D4*/	push eax
	/*005842D5*/	push ebx
	/*005842D6*/	push ebx
	/*005842D7*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005842DC*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*005842E1*/	add esp,0x14
	/*005842E4*/	lea ecx,dword ptr ss:[esp+0x228]
	/*005842EB*/	lea edx,dword ptr ss:[esp+0x328]
	/*005842F2*/	push 0x1DB
	/*005842F7*/	push ecx
_005842F8:
	/*005842F8*/	push edx
_005842F9:
	/*005842F9*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*005842FE*/	push eax
	/*005842FF*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*00584304*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00584309*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*0058430E*/	push ebx
	/*0058430F*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00584314*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*00584319*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*0058431E*/	add esp,0x24
	/*00584321*/	mov dword ptr ds:[0xB67A34],ebx
_00584327:
	/*00584327*/	xor eax,eax
_exit_sub:
	/*00584329*/	mov ecx,dword ptr ss:[esp+0x428]
	/*00584330*/	pop edi
	/*00584331*/	pop esi
	/*00584332*/	pop ebp
	/*00584333*/	pop ebx
	/*00584334*/	mov dword ptr fs:[0x0],ecx
	/*0058433B*/	add esp,0x424
	/*00584341*/	ret 0x10
_00584344:
	/*00584344*/	movsx eax,word ptr ds:[edi+0x40]
	/*00584348*/	push eax
	/*00584349*/	push ebp
	/*0058434A*/	push 0x1
	/*0058434C*/	push 0x2
	/*0058434E*/	push 0xF
	/*00584350*/	push ebx
	/*00584351*/	push esi
	/*00584352*/	call sub_521E60		/*call <cm0102.sub_521E60>*/
	/*00584357*/	movsx ecx,word ptr ds:[edi+0x40]
	/*0058435B*/	push ebx
	/*0058435C*/	push ecx
	/*0058435D*/	push 0x2
	/*0058435F*/	push 0x2
	/*00584361*/	push 0x1
	/*00584363*/	push ebp
	/*00584364*/	push 0x4
	/*00584366*/	push ebx
	/*00584367*/	push esi
	/*00584368*/	call sub_521EB0		/*call <cm0102.sub_521EB0>*/
	/*0058436D*/	add esp,0x40
	/*00584370*/	push ebx
	/*00584371*/	push 0xFFFFFFFF
	/*00584373*/	push 0xFFFFFFFF
	/*00584375*/	push 0xFFFFFFFF
	/*00584377*/	push ebx
	/*00584378*/	push ebx
	/*00584379*/	push esi
	/*0058437A*/	call sub_521F10		/*call cm0102.521F10*/
	/*0058437F*/	mov word ptr ds:[esi+0x7],0x78
	/*00584385*/	mov word ptr ds:[esi+0x9],bx
	/*00584389*/	mov word ptr ds:[esi+0xB],bx
	/*0058438D*/	mov word ptr ds:[esi+0xD],0x200
	/*00584393*/	mov eax,0x8
	/*00584398*/	mov byte ptr ds:[esi+0x17],0x8
	/*0058439C*/	mov word ptr ds:[esi+0x18],ax
	/*005843A0*/	mov word ptr ds:[esi+0x1A],0x4
	/*005843A6*/	mov word ptr ds:[esi+0x1C],ax
	/*005843AA*/	mov word ptr ds:[esi+0xF],bp
	/*005843AE*/	mov word ptr ds:[esi+0x1E],bx
	/*005843B2*/	mov byte ptr ds:[esi+0x20],bl
	/*005843B5*/	mov byte ptr ds:[esi+0x21],0x2
	/*005843B9*/	mov byte ptr ds:[esi+0x22],0xE
	/*005843BD*/	mov dword ptr ds:[esi+0x5C],0x186A00			// 1.6m - prize money
	/*005843C4*/	mov dword ptr ds:[esi+0x60],ebx
	/*005843C7*/	mov dword ptr ds:[esi+0x64],ebx
	/*005843CA*/	movsx edx,word ptr ds:[edi+0x40]
	/*005843CE*/	push edx
	/*005843CF*/	push 0x4
	/*005843D1*/	push 0x1
	/*005843D3*/	push ebp
	/*005843D4*/	push 0x14
	/*005843D6*/	push 0x1
	/*005843D8*/	push esi
	/*005843D9*/	call sub_521E60		/*call <cm0102.sub_521E60>*/
	/*005843DE*/	movsx eax,word ptr ds:[edi+0x40]
	/*005843E2*/	push ebx
	/*005843E3*/	push eax
	/*005843E4*/	push 0x2
	/*005843E6*/	push 0x2
	/*005843E8*/	push 0x1
	/*005843EA*/	push 0x4
	/*005843EC*/	push 0x2
	/*005843EE*/	push 0x1
	/*005843F0*/	push esi
	/*005843F1*/	call sub_521EB0		/*call <cm0102.sub_521EB0>*/
	/*005843F6*/	add esp,0x5C
	/*005843F9*/	push ebx
	/*005843FA*/	push 0xFFFFFFFF
	/*005843FC*/	push 0xFFFFFFFF
	/*005843FE*/	push 0xFFFFFFFF
	/*00584400*/	push ebx
	/*00584401*/	push 0x1
	/*00584403*/	push esi
	/*00584404*/	call sub_521F10		/*call cm0102.521F10*/
	/*00584409*/	mov word ptr ds:[esi+0x6F],0x82
	/*0058440F*/	mov word ptr ds:[esi+0x71],0x1
	/*00584415*/	mov word ptr ds:[esi+0x73],bx
	/*00584419*/	mov word ptr ds:[esi+0x75],bx
	/*0058441D*/	mov byte ptr ds:[esi+0x7F],0x8
	/*00584421*/	mov word ptr ds:[esi+0x80],0x4
	/*0058442A*/	mov word ptr ds:[esi+0x82],0x2
	/*00584433*/	mov word ptr ds:[esi+0x84],bx
	/*0058443A*/	mov word ptr ds:[esi+0x77],bp
	/*0058443E*/	mov word ptr ds:[esi+0x86],bx
	/*00584445*/	mov byte ptr ds:[esi+0x88],bl
	/*0058444B*/	mov byte ptr ds:[esi+0x89],0x2
	/*00584452*/	mov byte ptr ds:[esi+0x8A],0x7
	/*00584459*/	mov dword ptr ds:[esi+0xC4],0x1E8480		// 2m - prize money
	/*00584463*/	mov dword ptr ds:[esi+0xC8],ebx
	/*00584469*/	mov dword ptr ds:[esi+0xCC],ebx
	/*0058446F*/	movsx ecx,word ptr ds:[edi+0x40]
	/*00584473*/	push ecx
	/*00584474*/	push ebp
	/*00584475*/	push 0x1
	/*00584477*/	push 0x4
	/*00584479*/	push ebp
	/*0058447A*/	push 0x2
	/*0058447C*/	push esi
	/*0058447D*/	call sub_521E60		/*call <cm0102.sub_521E60>*/
	/*00584482*/	mov di,word ptr ds:[edi+0x40]
	/*00584486*/	add esp,0x38
	/*00584489*/	cmp di,0x7D0
	/*0058448E*/	jne _0058449C
	/*00584490*/	push 0x80
	/*00584495*/	push 0x7D0
	/*0058449A*/	jmp _005844A2
_0058449C:
	/*0058449C*/	movsx edx,di
	/*0058449F*/	push 0x4
	/*005844A1*/	push edx
_005844A2:
	/*005844A2*/	push 0x2
	/*005844A4*/	push 0x2
	/*005844A6*/	push 0x1
	/*005844A8*/	push 0x4
	/*005844AA*/	push 0x17
	/*005844AC*/	push 0x2
	/*005844AE*/	push esi
	/*005844AF*/	call sub_521EB0		/*call <cm0102.sub_521EB0>*/
	/*005844B4*/	add esp,0x24
	/*005844B7*/	mov edi,0x2
	/*005844BC*/	push ebx
	/*005844BD*/	push 0xFFFFFFFF
	/*005844BF*/	push 0xFFFFFFFF
	/*005844C1*/	push 0xFFFFFFFF
	/*005844C3*/	push ebx
	/*005844C4*/	push edi
	/*005844C5*/	push esi
	/*005844C6*/	call sub_521F10		/*call cm0102.521F10*/
	/*005844CB*/	add esp,0x1C
	/*005844CE*/	mov word ptr ds:[esi+0xD7],0x96
	/*005844D7*/	mov word ptr ds:[esi+0xD9],di
	/*005844DE*/	mov word ptr ds:[esi+0xDB],bx
	/*005844E5*/	mov word ptr ds:[esi+0xDD],0x83
	/*005844EE*/	mov byte ptr ds:[esi+0xE7],0x8
	/*005844F5*/	mov word ptr ds:[esi+0xE8],di
	/*005844FC*/	mov word ptr ds:[esi+0xEA],0x1
	/*00584505*/	mov word ptr ds:[esi+0xEC],bx
	/*0058450C*/	mov word ptr ds:[esi+0xDF],bx
	/*00584513*/	mov word ptr ds:[esi+0xEE],bx
	/*0058451A*/	mov byte ptr ds:[esi+0xF0],bl
	/*00584520*/	mov byte ptr ds:[esi+0xF1],0x1
	/*00584527*/	mov byte ptr ds:[esi+0xF2],bl
	/*0058452D*/	mov dword ptr ds:[esi+0x12C],ebx
	/*00584533*/	mov dword ptr ds:[esi+0x130],0x3D0900		// 4m - prize money
	/*0058453D*/	mov dword ptr ds:[esi+0x134],0x30D400		// 3.2m - prize money
	/*00584547*/	mov eax,esi
	/*00584549*/	jmp _exit_sub
	/*0058454E*/	nop
	/*0058454F*/	nop
	/*00584550*/	mov al,byte ptr ss:[esp+0xC]
	/*00584554*/	push ebx
	/*00584555*/	push esi
	/*00584556*/	cmp al,0xFF
	/*00584558*/	push edi
	/*00584559*/	mov esi,ecx
	/*0058455B*/	jne _005846DD
	/*00584561*/	mov edi,dword ptr ss:[esp+0x20]
	/*00584565*/	mov ax,word ptr ds:[edi+0x30]
	/*00584569*/	push eax
	/*0058456A*/	call sub_4B0870		/*call <cm0102.sub_4B0870>*/
	/*0058456F*/	add esp,0x4
	/*00584572*/	cmp ax,0xFA
	/*00584576*/	je _005846A8
	/*0058457C*/	mov cx,word ptr ds:[edi+0x30]
	/*00584580*/	push ecx
	/*00584581*/	call sub_4B0870		/*call <cm0102.sub_4B0870>*/
	/*00584586*/	add esp,0x4
	/*00584589*/	cmp ax,0x104
	/*0058458D*/	je _005846A8
	/*00584593*/	mov eax,dword ptr ss:[esp+0x30]
	/*00584597*/	test eax,eax
	/*00584599*/	je _005845BA
	/*0058459B*/	mov edx,dword ptr ss:[esp+0x34]
	/*0058459F*/	mov ecx,dword ptr ss:[esp+0x24]
	/*005845A3*/	push edx
	/*005845A4*/	mov edx,dword ptr ss:[esp+0x20]
	/*005845A8*/	push eax
	/*005845A9*/	mov eax,dword ptr ss:[esp+0x34]
	/*005845AD*/	push eax
	/*005845AE*/	push 0x0
	/*005845B0*/	push ecx
	/*005845B1*/	push edi
	/*005845B2*/	push edx
	/*005845B3*/	push 0xFFFFFFFF
	/*005845B5*/	jmp _00584977
_005845BA:
	/*005845BA*/	cmp byte ptr ss:[esp+0x14],0x1
	/*005845BF*/	jne _005845F9
	/*005845C1*/	mov eax,dword ptr ss:[esp+0x10]
	/*005845C5*/	mov ecx,dword ptr ds:[esi+0x4]
	/*005845C8*/	mov ebx,dword ptr ds:[0xAE23B4]				// Clubs Pointer
	/*005845CE*/	lea edx,dword ptr ds:[eax+eax*0x8]
	/*005845D1*/	shl edx,0x4
	/*005845D4*/	add edx,eax
	/*005845D6*/	add ecx,0x38
	/*005845D9*/	push ecx
	/*005845DA*/	lea edi,dword ptr ds:[eax+edx*0x4]
	/*005845DD*/	movsx eax,byte ptr ds:[ecx+0x1A]
	/*005845E1*/	movsx edx,byte ptr ds:[edi+ebx+0x52]
	/*005845E6*/	lea ecx,dword ptr ds:[edi+ebx+0x38]
	/*005845EA*/	push ecx
	/*005845EB*/	push eax
	/*005845EC*/	push eax
	/*005845ED*/	push edx
	/*005845EE*/	push edx
	/*005845EF*/	push 0x9C4A1C		/*push cm0102.9C4A1C*/
	/*005845F4*/	jmp _00584902
_005845F9:
	/*005845F9*/	mov eax,dword ptr ds:[0x9CF6F0]		/* UEFA Cup */
	/*005845FE*/	mov edx,dword ptr ds:[0xAE23D0]				// Divisions Pointer
	/*00584604*/	mov edi,dword ptr ds:[0xAE23B4]				// Clubs Pointer
	/*0058460A*/	lea ecx,dword ptr ds:[eax+eax*0x2]
	/*0058460D*/	lea ecx,dword ptr ds:[ecx+ecx*0x8]
	/*00584610*/	shl ecx,0x2
	/*00584613*/	sub ecx,eax
	/*00584615*/	mov eax,dword ptr ss:[esp+0x10]
	/*00584619*/	add ecx,edx
	/*0058461B*/	lea edx,dword ptr ds:[eax+eax*0x8]
	/*0058461E*/	add ecx,0x38
	/*00584621*/	shl edx,0x4
	/*00584624*/	add edx,eax
	/*00584626*/	push ecx
	/*00584627*/	lea esi,dword ptr ds:[eax+edx*0x4]
	/*0058462A*/	movsx eax,byte ptr ds:[ecx+0x1A]
	/*0058462E*/	movsx edx,byte ptr ds:[esi+edi+0x52]
	/*00584633*/	lea ecx,dword ptr ds:[esi+edi+0x38]
	/*00584637*/	push ecx
	/*00584638*/	push eax
	/*00584639*/	push eax
	/*0058463A*/	push edx
	/*0058463B*/	push edx
	/*0058463C*/	push 0x9C49C0		/*push cm0102.9C49C0*/
	/*00584641*/	push 0xDE1F64		/*push cm0102.DE1F64*/
	/*00584646*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*0058464B*/	mov edi,dword ptr ss:[esp+0x54]
	/*0058464F*/	add esp,0x20
	/*00584652*/	mov ecx,edi
	/*00584654*/	push 0xDE1F64		/*push cm0102.DE1F64*/
	/*00584659*/	call sub_4AE660		/*call <cm0102.sub_4AE660>*/
	/*0058465E*/	mov edx,dword ptr ds:[0xAE23B4]			// Clubs Pointer
	/*00584664*/	mov ecx,edi
	/*00584666*/	lea eax,dword ptr ds:[esi+edx]
	/*00584669*/	push eax
	/*0058466A*/	add eax,0x38
	/*0058466D*/	push 0x7D5
	/*00584672*/	push eax
	/*00584673*/	call sub_4AE8A0		/*call <cm0102.sub_4AE8A0>*/
	/*00584678*/	mov eax,dword ptr ds:[0x9CF6F0]		/* UEFA Cup */
	/*0058467D*/	mov edx,dword ptr ds:[0xAE23D0]			// Divisions Pointer
	/*00584683*/	lea ecx,dword ptr ds:[eax+eax*0x2]
	/*00584686*/	lea ecx,dword ptr ds:[ecx+ecx*0x8]
	/*00584689*/	shl ecx,0x2
	/*0058468C*/	sub ecx,eax
	/*0058468E*/	lea eax,dword ptr ds:[ecx+edx]
	/*00584691*/	mov ecx,edi
	/*00584693*/	push eax
	/*00584694*/	add eax,0x38
	/*00584697*/	push 0x7D0
	/*0058469C*/	push eax
	/*0058469D*/	call sub_4AE8A0		/*call <cm0102.sub_4AE8A0>*/
	/*005846A2*/	pop edi
	/*005846A3*/	pop esi
	/*005846A4*/	pop ebx
	/*005846A5*/	ret 0x28
_005846A8:
	/*005846A8*/	mov eax,dword ptr ss:[esp+0x34]
	/*005846AC*/	mov ecx,dword ptr ss:[esp+0x30]
	/*005846B0*/	mov edx,dword ptr ss:[esp+0x2C]
	/*005846B4*/	push eax
	/*005846B5*/	mov eax,dword ptr ss:[esp+0x28]
	/*005846B9*/	push ecx
	/*005846BA*/	mov ecx,dword ptr ss:[esp+0x24]
	/*005846BE*/	push edx
	/*005846BF*/	mov edx,dword ptr ss:[esp+0x20]
	/*005846C3*/	push 0x0
	/*005846C5*/	push eax
	/*005846C6*/	mov eax,dword ptr ss:[esp+0x24]
	/*005846CA*/	push edi
	/*005846CB*/	push ecx
	/*005846CC*/	push 0xFFFFFFFF
	/*005846CE*/	push edx
	/*005846CF*/	push eax
	/*005846D0*/	mov ecx,esi
	/*005846D2*/	call sub_48C6D0		/*call <cm0102.sub_48C6D0>*/
	/*005846D7*/	pop edi
	/*005846D8*/	pop esi
	/*005846D9*/	pop ebx
	/*005846DA*/	ret 0x28
_005846DD:
	/*005846DD*/	cmp al,0x8
	/*005846DF*/	jge _0058480D_8_or_greater
	/*005846E5*/	mov al,byte ptr ss:[esp+0x14]
	/*005846E9*/	cmp al,0x6
	/*005846EB*/	jne _00584715
	/*005846ED*/	mov ecx,dword ptr ss:[esp+0x34]
	/*005846F1*/	mov edx,dword ptr ss:[esp+0x30]
	/*005846F5*/	mov eax,dword ptr ds:[esi+0x4]
	/*005846F8*/	push ecx
	/*005846F9*/	mov ecx,dword ptr ss:[esp+0x20]
	/*005846FD*/	push edx
	/*005846FE*/	mov edx,dword ptr ss:[esp+0x18]
	/*00584702*/	push 0x6
	/*00584704*/	push eax
	/*00584705*/	push ecx
	/*00584706*/	push edx
	/*00584707*/	call sub_4B4590		/*call <cm0102.sub_4B4590>*/
	/*0058470C*/	add esp,0x18
	/*0058470F*/	pop edi
	/*00584710*/	pop esi
	/*00584711*/	pop ebx
	/*00584712*/	ret 0x28
_00584715:
	/*00584715*/	cmp al,0xFE
	/*00584717*/	jne _00584988
	/*0058471D*/	mov eax,dword ptr ss:[esp+0x30]
	/*00584721*/	test eax,eax
	/*00584723*/	je _0058475D
	/*00584725*/	mov eax,dword ptr ss:[esp+0x10]
	/*00584729*/	mov ecx,dword ptr ds:[esi+0x4]
	/*0058472C*/	mov ebx,dword ptr ds:[0xAE23B4]		// Clubs Pointer
	/*00584732*/	lea edx,dword ptr ds:[eax+eax*0x8]
	/*00584735*/	shl edx,0x4
	/*00584738*/	add edx,eax
	/*0058473A*/	add ecx,0x4
	/*0058473D*/	push ecx
	/*0058473E*/	lea edi,dword ptr ds:[eax+edx*0x4]
	/*00584741*/	movsx eax,byte ptr ds:[ecx+0x33]
	/*00584745*/	movsx edx,byte ptr ds:[edi+ebx+0x52]
	/*0058474A*/	lea ecx,dword ptr ds:[edi+ebx+0x38]
	/*0058474E*/	push ecx
	/*0058474F*/	push eax
	/*00584750*/	push eax
	/*00584751*/	push edx
	/*00584752*/	push edx
	/*00584753*/	push 0x9C4940		/*push cm0102.9C4940*/
	/*00584758*/	jmp _00584888
_0058475D:
	/*0058475D*/	mov eax,dword ptr ds:[0x9CF6F0]		/* UEFA Cup */
	/*00584762*/	mov edx,dword ptr ds:[0xAE23D0]		// Divisions Pointer
	/*00584768*/	mov ebx,dword ptr ds:[0xAE23B4]		// Clubs Pointer
	/*0058476E*/	lea ecx,dword ptr ds:[eax+eax*0x2]
	/*00584771*/	lea ecx,dword ptr ds:[ecx+ecx*0x8]
	/*00584774*/	shl ecx,0x2
	/*00584777*/	sub ecx,eax
	/*00584779*/	mov eax,dword ptr ss:[esp+0x10]
	/*0058477D*/	add ecx,edx
	/*0058477F*/	lea edx,dword ptr ds:[eax+eax*0x8]
	/*00584782*/	add ecx,0x38
	/*00584785*/	shl edx,0x4
	/*00584788*/	add edx,eax
	/*0058478A*/	push ecx
	/*0058478B*/	lea edi,dword ptr ds:[eax+edx*0x4]
	/*0058478E*/	movsx eax,byte ptr ds:[ecx+0x1A]
	/*00584792*/	movsx edx,byte ptr ds:[edi+ebx+0x52]
	/*00584797*/	lea ecx,dword ptr ds:[edi+ebx+0x38]
	/*0058479B*/	push ecx
	/*0058479C*/	push eax
	/*0058479D*/	push eax
	/*0058479E*/	push edx
	/*0058479F*/	push edx
	/*005847A0*/	push 0x9C49C0		/*push cm0102.9C49C0*/
	/*005847A5*/	push 0xDE1F64		/*push cm0102.DE1F64*/
	/*005847AA*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*005847AF*/	mov ebx,dword ptr ss:[esp+0x54]
	/*005847B3*/	add esp,0x20
	/*005847B6*/	mov ecx,ebx
	/*005847B8*/	push 0xDE1F64		/*push cm0102.DE1F64*/
	/*005847BD*/	call sub_4AE660		/*call <cm0102.sub_4AE660>*/
	/*005847C2*/	mov edx,dword ptr ds:[0xAE23B4]		// Clubs Pointer
	/*005847C8*/	mov ecx,ebx
	/*005847CA*/	lea eax,dword ptr ds:[edi+edx]
	/*005847CD*/	push eax
	/*005847CE*/	add eax,0x38
	/*005847D1*/	push 0x7D5
	/*005847D6*/	push eax
	/*005847D7*/	call sub_4AE8A0		/*call <cm0102.sub_4AE8A0>*/
	/*005847DC*/	mov eax,dword ptr ds:[esi+0x4]
	/*005847DF*/	mov edx,dword ptr ds:[0xAE23D0]		// Divisions Pointer
	/*005847E5*/	push eax
	/*005847E6*/	mov eax,dword ptr ds:[0x9CF6F0]		/* UEFA Cup */
	/*005847EB*/	push 0x7D0
	/*005847F0*/	lea ecx,dword ptr ds:[eax+eax*0x2]
	/*005847F3*/	lea ecx,dword ptr ds:[ecx+ecx*0x8]
	/*005847F6*/	shl ecx,0x2
	/*005847F9*/	sub ecx,eax
	/*005847FB*/	lea eax,dword ptr ds:[ecx+edx+0x38]
	/*005847FF*/	mov ecx,ebx
	/*00584801*/	push eax
	/*00584802*/	call sub_4AE8A0		/*call <cm0102.sub_4AE8A0>*/
	/*00584807*/	pop edi
	/*00584808*/	pop esi
	/*00584809*/	pop ebx
	/*0058480A*/	ret 0x28
_0058480D_8_or_greater:
	/*0058480D*/	cmp al,0xC
	/*0058480F*/	jge _00584953_C_or_greater
	/*00584815*/	mov al,byte ptr ss:[esp+0x14]
	/*00584819*/	cmp al,0x6
	/*0058481B*/	jne _00584845
	/*0058481D*/	mov ecx,dword ptr ss:[esp+0x34]
	/*00584821*/	mov edx,dword ptr ss:[esp+0x30]
	/*00584825*/	mov eax,dword ptr ds:[esi+0x4]
	/*00584828*/	push ecx
	/*00584829*/	mov ecx,dword ptr ss:[esp+0x20]
	/*0058482D*/	push edx
	/*0058482E*/	mov edx,dword ptr ss:[esp+0x18]
	/*00584832*/	push 0x6
	/*00584834*/	push eax
	/*00584835*/	push ecx
	/*00584836*/	push edx
	/*00584837*/	call sub_4B4590		/*call <cm0102.sub_4B4590>*/
	/*0058483C*/	add esp,0x18
	/*0058483F*/	pop edi
	/*00584840*/	pop esi
	/*00584841*/	pop ebx
	/*00584842*/	ret 0x28
_00584845:
	/*00584845*/	cmp al,0xFE
	/*00584847*/	jne _00584988
	/*0058484D*/	mov eax,dword ptr ss:[esp+0x30]
	/*00584851*/	mov ecx,dword ptr ds:[esi+0x4]
	/*00584854*/	test eax,eax
	/*00584856*/	mov eax,dword ptr ss:[esp+0x10]
	/*0058485A*/	lea edx,dword ptr ds:[eax+eax*0x8]
	/*0058485D*/	je _005848D9
	/*0058485F*/	mov ebx,dword ptr ds:[0xAE23B4]		// Clubs Pointer
	/*00584865*/	shl edx,0x4
	/*00584868*/	add edx,eax
	/*0058486A*/	add ecx,0x4
	/*0058486D*/	push ecx
	/*0058486E*/	lea edi,dword ptr ds:[eax+edx*0x4]
	/*00584871*/	movsx eax,byte ptr ds:[ecx+0x33]
	/*00584875*/	movsx edx,byte ptr ds:[edi+ebx+0x52]
	/*0058487A*/	lea ecx,dword ptr ds:[edi+ebx+0x38]
	/*0058487E*/	push ecx
	/*0058487F*/	push eax
	/*00584880*/	push eax
	/*00584881*/	push edx
	/*00584882*/	push edx
	/*00584883*/	push 0x987AE0		/*push cm0102.987AE0*/
_00584888:
	/*00584888*/	push 0xDE1F64		/*push cm0102.DE1F64*/
	/*0058488D*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*00584892*/	mov ebx,dword ptr ss:[esp+0x54]
	/*00584896*/	add esp,0x20
	/*00584899*/	mov ecx,ebx
	/*0058489B*/	push 0xDE1F64		/*push cm0102.DE1F64*/
	/*005848A0*/	call sub_4AE660		/*call <cm0102.sub_4AE660>*/
	/*005848A5*/	mov edx,dword ptr ds:[0xAE23B4]		// Clubs Pointer
	/*005848AB*/	mov ecx,ebx
	/*005848AD*/	lea eax,dword ptr ds:[edi+edx]
	/*005848B0*/	push eax
	/*005848B1*/	add eax,0x38
	/*005848B4*/	push 0x7D5
	/*005848B9*/	push eax
	/*005848BA*/	call sub_4AE8A0		/*call <cm0102.sub_4AE8A0>*/
	/*005848BF*/	mov esi,dword ptr ds:[esi+0x4]
	/*005848C2*/	mov ecx,ebx
	/*005848C4*/	push esi
	/*005848C5*/	add esi,0x4
	/*005848C8*/	push 0x7D0
	/*005848CD*/	push esi
	/*005848CE*/	call sub_4AE8A0		/*call <cm0102.sub_4AE8A0>*/
	/*005848D3*/	pop edi
	/*005848D4*/	pop esi
	/*005848D5*/	pop ebx
	/*005848D6*/	ret 0x28
_005848D9:
	/*005848D9*/	mov ebx,dword ptr ds:[0xAE23B4]		// Clubs Pointer
	/*005848DF*/	shl edx,0x4
	/*005848E2*/	add edx,eax
	/*005848E4*/	add ecx,0x38
	/*005848E7*/	push ecx
	/*005848E8*/	lea edi,dword ptr ds:[eax+edx*0x4]
	/*005848EB*/	movsx eax,byte ptr ds:[ecx+0x1A]
	/*005848EF*/	movsx edx,byte ptr ds:[edi+ebx+0x52]
	/*005848F4*/	lea ecx,dword ptr ds:[edi+ebx+0x38]
	/*005848F8*/	push ecx
	/*005848F9*/	push eax
	/*005848FA*/	push eax
	/*005848FB*/	push edx
	/*005848FC*/	push edx
	/*005848FD*/	push 0x987A80		/*push cm0102.987A80*/
_00584902:
	/*00584902*/	push 0xDE1F64		/*push cm0102.DE1F64*/
	/*00584907*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*0058490C*/	mov ebx,dword ptr ss:[esp+0x54]
	/*00584910*/	add esp,0x20
	/*00584913*/	mov ecx,ebx
	/*00584915*/	push 0xDE1F64		/*push cm0102.DE1F64*/
	/*0058491A*/	call sub_4AE660		/*call <cm0102.sub_4AE660>*/
	/*0058491F*/	mov edx,dword ptr ds:[0xAE23B4]		// Clubs Pointer
	/*00584925*/	mov ecx,ebx
	/*00584927*/	lea eax,dword ptr ds:[edi+edx]
	/*0058492A*/	push eax
	/*0058492B*/	add eax,0x38
	/*0058492E*/	push 0x7D5
	/*00584933*/	push eax
	/*00584934*/	call sub_4AE8A0		/*call <cm0102.sub_4AE8A0>*/
	/*00584939*/	mov esi,dword ptr ds:[esi+0x4]
	/*0058493C*/	mov ecx,ebx
	/*0058493E*/	push esi
	/*0058493F*/	add esi,0x38
	/*00584942*/	push 0x7D0
	/*00584947*/	push esi
	/*00584948*/	call sub_4AE8A0		/*call <cm0102.sub_4AE8A0>*/
	/*0058494D*/	pop edi
	/*0058494E*/	pop esi
	/*0058494F*/	pop ebx
	/*00584950*/	ret 0x28
_00584953_C_or_greater:
	/*00584953*/	jne _00584988
	/*00584955*/	mov eax,dword ptr ss:[esp+0x34]
	/*00584959*/	mov ecx,dword ptr ss:[esp+0x30]
	/*0058495D*/	mov edx,dword ptr ss:[esp+0x2C]
	/*00584961*/	push eax
	/*00584962*/	mov eax,dword ptr ss:[esp+0x28]
	/*00584966*/	push ecx
	/*00584967*/	mov ecx,dword ptr ss:[esp+0x28]
	/*0058496B*/	push edx
	/*0058496C*/	mov edx,dword ptr ss:[esp+0x28]
	/*00584970*/	push 0x0
	/*00584972*/	push eax
	/*00584973*/	push ecx
	/*00584974*/	push edx
	/*00584975*/	push 0xC
_00584977:
	/*00584977*/	mov eax,dword ptr ss:[esp+0x34]
	/*0058497B*/	mov ecx,dword ptr ss:[esp+0x30]
	/*0058497F*/	push eax
	/*00584980*/	push ecx
	/*00584981*/	mov ecx,esi
	/*00584983*/	call sub_48C6D0		/*call <cm0102.sub_48C6D0>*/
_00584988:
	/*00584988*/	pop edi
	/*00584989*/	pop esi
	/*0058498A*/	pop ebx
	/*0058498B*/	ret 0x28
	}
}

extern "C" void __stdcall LogTeam(DWORD club)		// will crash if not __stdcall
{
	static int clubCounter = 0;
	cm3_clubs *club_ptr = (cm3_clubs *)club;
	printf("Adding Club (%d): %s\n", clubCounter++, club_ptr->ClubName);
}

// 16 first seeds
// 8 seconds seeds
extern "C" void __declspec(naked) european_cup_get_qualifying_teams_584990()		// Third Function called
{
	__asm pushad
	dprintf("european_cup_get_qualifying_teams_584990 Called!\n");
	__asm popad


	__asm
	{
	/*00584990*/	sub esp,0x200
	/*00584996*/	push ebx
	/*00584997*/	push esi
	/*00584998*/	mov esi,ecx
	/*0058499A*/	push 0x14A							// 330 (55 * 6)
	/*0058499F*/	mov word ptr ds:[esi+0x3E],0x37		// 55					// Set number of teams to 55? 71 - 16 = 55
	/*005849A5*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*005849AA*/	xor ebx,ebx
	/*005849AC*/	add esp,0x4
	/*005849AF*/	cmp eax,ebx
	/*005849B1*/	mov dword ptr ds:[esi+0xA7],eax			// allocate memory for 0xA7 block
	/*005849B7*/	jne _00584A21
	/*005849B9*/	lea eax,dword ptr ss:[esp+0x8]
	/*005849BD*/	lea ecx,dword ptr ss:[esp+0x108]
	/*005849C4*/	push eax
	/*005849C5*/	push ecx
	/*005849C6*/	push ebx
	/*005849C7*/	push ebx
	/*005849C8*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005849CD*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*005849D2*/	add esp,0x14
	/*005849D5*/	lea edx,dword ptr ss:[esp+0x8]
	/*005849D9*/	lea eax,dword ptr ss:[esp+0x108]
	/*005849E0*/	push 0x2F6
	/*005849E5*/	push edx
	/*005849E6*/	push eax
	/*005849E7*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*005849EC*/	push eax
	/*005849ED*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*005849F2*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005849F7*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*005849FC*/	push ebx
	/*005849FD*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00584A02*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*00584A07*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*00584A0C*/	add esp,0x24
	/*00584A0F*/	mov dword ptr ds:[0xB67A34],ebx
	/*00584A15*/	or eax,0xFFFFFFFF
	/*00584A18*/	pop esi
	/*00584A19*/	pop ebx
	/*00584A1A*/	add esp,0x200
	/*00584A20*/	ret
_00584A21:
	/*00584A21*/	push edi
	/*00584A22*/	xor edi,edi
	/*00584A24*/	cmp word ptr ds:[esi+0x3E],bx			// compare with 0 - which obviously isn't as we set it to 55 above
	/*00584A28*/	jle _00584AB2
	/*00584A2E*/	push ebp
	/*00584A2F*/	xor edx,edx
_00584A31:
	/*00584A31*/	mov cx,word ptr ds:[esi+0x36]			// 0x47 = 71 ? teams
	/*00584A35*/	cmp cx,bx
	/*00584A38*/	je _00584A54
	/*00584A3A*/	movsx ecx,cx
	/*00584A3D*/	mov eax,dword ptr ds:[esi+0x14]			// Pointer to the teams
	/*00584A40*/	mov ebp,dword ptr ds:[esi+0xA7]
	/*00584A46*/	sub ecx,edi								// ecx = 0x47 edi = 0
	/*00584A48*/	dec ecx									// ecx--
	/*00584A49*/	lea ecx,dword ptr ds:[ecx+ecx*0x2]
	/*00584A4C*/	mov ecx,dword ptr ds:[eax+ecx*0x2]		// ecx = team - going backwards through the teams (starting at the last)
		
					pushad
					push ecx
					call LogTeam
					popad

	/*00584A4F*/	mov dword ptr ds:[edx+ebp],ecx			// starts filling the table at 0xA7 with the teams
	/*00584A52*/	jmp _00584A5D
_00584A54:
	/*00584A54*/	mov eax,dword ptr ds:[esi+0xA7]
	/*00584A5A*/	mov dword ptr ds:[edx+eax],ebx
_00584A5D:
	/*00584A5D*/	movsx ecx,word ptr ds:[esi+0x36]		// Total Team Count
	/*00584A61*/	mov eax,dword ptr ds:[esi+0x14]			// Pointer to the teams
	/*00584A64*/	sub ecx,edi
	/*00584A66*/	lea ecx,dword ptr ds:[ecx+ecx*0x2]		// 71 * 3
	/*00584A69*/	mov cl,byte ptr ds:[eax+ecx*0x2-0x2]	// The teams are in 6 bytes chunks, this is referencing the byte after the team pointer we just got 
	/*00584A6D*/	cmp cl,0x8
	/*00584A70*/	jne _00584A7F
	/*00584A72*/	mov ecx,dword ptr ds:[esi+0xA7]
	/*00584A78*/	mov byte ptr ds:[edx+ecx+0x4],0x2
	/*00584A7D*/	jmp _00584A9B
_00584A7F:
	/*00584A7F*/	cmp cl,0xD
	/*00584A82*/	jne _00584A91
	/*00584A84*/	mov eax,dword ptr ds:[esi+0xA7]
	/*00584A8A*/	mov byte ptr ds:[edx+eax+0x4],0x1
	/*00584A8F*/	jmp _00584A9B
_00584A91:
	/*00584A91*/	mov ecx,dword ptr ds:[esi+0xA7]
	/*00584A97*/	mov byte ptr ds:[edx+ecx+0x4],bl
_00584A9B:
	/*00584A9B*/	mov eax,dword ptr ds:[esi+0xA7]
	/*00584AA1*/	inc edi
	/*00584AA2*/	mov byte ptr ds:[edx+eax+0x5],bl		// Make the 6th byte 0
	/*00584AA6*/	add edx,0x6
	/*00584AA9*/	movsx ecx,word ptr ds:[esi+0x3E]
	/*00584AAD*/	cmp edi,ecx
	/*00584AAF*/	jl _00584A31
	/*00584AB1*/	pop ebp
_00584AB2:
	/*00584AB2*/	pop edi
	/*00584AB3*/	pop esi
	/*00584AB4*/	mov eax,0x1
	/*00584AB9*/	pop ebx
	/*00584ABA*/	add esp,0x200
	/*00584AC0*/	ret
	}
}

extern "C" void __declspec(naked) sub_584AD0()
{
	__asm pushad
	dprintf("sub_584AD0 Called!\n");
	__asm popad

	__asm
	{
	/*00584AD0*/	mov eax,dword ptr ds:[ecx+0xC]
	/*00584AD3*/	mov ecx,dword ptr ds:[eax+0x30]
	/*00584AD6*/	mov edx,dword ptr ds:[ecx]
	/*00584AD8*/	jmp dword ptr ds:[edx+0x30]
	}
}

extern "C" void __declspec(naked) sub_584AE0()
{
	__asm pushad
	dprintf("sub_584AE0 Called!\n");
	__asm popad

	__asm
	{
	/*00584AE0*/	mov al,byte ptr ss:[esp+0xC]
	/*00584AE4*/	push ebx
	/*00584AE5*/	or ebx,0xFFFFFFFF
	/*00584AE8*/	push esi
	/*00584AE9*/	cmp al,bl
	/*00584AEB*/	push edi
	/*00584AEC*/	mov esi,ecx
	/*00584AEE*/	jne _00584BB2
	/*00584AF4*/	mov al,byte ptr ss:[esp+0x14]
	/*00584AF8*/	test al,al
	/*00584AFA*/	je _00584B37
	/*00584AFC*/	cmp al,0x1
	/*00584AFE*/	je _00584B37
	/*00584B00*/	cmp al,bl
	/*00584B02*/	je _00584B0C
	/*00584B04*/	cmp al,0x2
	/*00584B06*/	jne _00584D4E
_00584B0C:
	/*00584B0C*/	mov edi,dword ptr ss:[esp+0x20]
	/*00584B10*/	push 0x2
	/*00584B12*/	mov ax,word ptr ds:[edi+0x34]
	/*00584B16*/	push eax
	/*00584B17*/	push 0x14
	/*00584B19*/	push 0x1
	/*00584B1B*/	call sub_4BF850		/*call <cm0102.sub_4BF850>*/
	/*00584B20*/	mov cx,word ptr ds:[edi+0x30]
	/*00584B24*/	mov dx,word ptr ds:[edi+0x32]
	/*00584B28*/	add esp,0x10
	/*00584B2B*/	push eax
	/*00584B2C*/	mov eax,dword ptr ds:[esi+0x4]
	/*00584B2F*/	push ecx
	/*00584B30*/	push edx
	/*00584B31*/	push eax
	/*00584B32*/	jmp _00584D38
_00584B37:
	/*00584B37*/	mov ecx,dword ptr ss:[esp+0x20]
	/*00584B3B*/	push 0x2
	/*00584B3D*/	mov ax,word ptr ds:[ecx+0x34]
	/*00584B41*/	test ax,ax
	/*00584B44*/	jne _00584B81
	/*00584B46*/	push 0x0
	/*00584B48*/	push 0x14
	/*00584B4A*/	push 0x1
	/*00584B4C*/	call sub_4BF850		/*call <cm0102.sub_4BF850>*/
	/*00584B51*/	mov edx,dword ptr ds:[esi+0xA3]
	/*00584B57*/	mov cx,word ptr ds:[esi+0x3A]
	/*00584B5B*/	add esp,0x10
	/*00584B5E*/	push eax
	/*00584B5F*/	mov ax,word ptr ds:[edx+0x6F]
	/*00584B63*/	mov edx,dword ptr ds:[esi+0x4]
	/*00584B66*/	push eax
	/*00584B67*/	mov eax,dword ptr ss:[esp+0x18]
	/*00584B6B*/	push ecx
	/*00584B6C*/	mov ecx,dword ptr ds:[0xDD7F00]
	/*00584B72*/	push edx
	/*00584B73*/	push eax
	/*00584B74*/	call sub_86BDD0		/*call <cm0102.sub_86BDD0>*/
	/*00584B79*/	pop edi
	/*00584B7A*/	pop esi
	/*00584B7B*/	xor eax,eax
	/*00584B7D*/	pop ebx
	/*00584B7E*/	ret 0x18
_00584B81:
	/*00584B81*/	push eax
	/*00584B82*/	push 0x14
	/*00584B84*/	push 0x1
	/*00584B86*/	call sub_4BF850		/*call <cm0102.sub_4BF850>*/
	/*00584B8B*/	mov ecx,dword ptr ds:[esi+0x4]
	/*00584B8E*/	mov edx,dword ptr ss:[esp+0x20]
	/*00584B92*/	add esp,0x10
	/*00584B95*/	push eax
	/*00584B96*/	push 0x0
	/*00584B98*/	push 0x41C
	/*00584B9D*/	push ecx
	/*00584B9E*/	mov ecx,dword ptr ds:[0xDD7F00]
	/*00584BA4*/	push edx
	/*00584BA5*/	call sub_86BDD0		/*call <cm0102.sub_86BDD0>*/
	/*00584BAA*/	pop edi
	/*00584BAB*/	pop esi
	/*00584BAC*/	xor eax,eax
	/*00584BAE*/	pop ebx
	/*00584BAF*/	ret 0x18
_00584BB2:
	/*00584BB2*/	cmp al,0x8
	/*00584BB4*/	jge _00584C13
	/*00584BB6*/	mov al,byte ptr ss:[esp+0x14]
	/*00584BBA*/	cmp al,0x6
	/*00584BBC*/	jne _00584BE2
	/*00584BBE*/	mov eax,dword ptr ds:[esi+0x4]
	/*00584BC1*/	mov ecx,dword ptr ss:[esp+0x10]
	/*00584BC5*/	push 0x32
	/*00584BC7*/	push ebx
	/*00584BC8*/	push 0x44A
	/*00584BCD*/	push eax
	/*00584BCE*/	push ecx
	/*00584BCF*/	mov ecx,dword ptr ds:[0xDD7F00]
	/*00584BD5*/	call sub_86BDD0		/*call <cm0102.sub_86BDD0>*/
	/*00584BDA*/	pop edi
	/*00584BDB*/	pop esi
	/*00584BDC*/	xor eax,eax
	/*00584BDE*/	pop ebx
	/*00584BDF*/	ret 0x18
_00584BE2:
	/*00584BE2*/	cmp al,0xFE
	/*00584BE4*/	jne _00584D4E
	/*00584BEA*/	mov edx,dword ptr ds:[esi+0x4]
	/*00584BED*/	mov esi,dword ptr ss:[esp+0x10]
	/*00584BF1*/	mov ecx,dword ptr ds:[0xDD7F00]
	/*00584BF7*/	push 0x32
	/*00584BF9*/	push 0x449
	/*00584BFE*/	push edx
	/*00584BFF*/	push esi
	/*00584C00*/	call sub_86C1D0		/*call <cm0102.sub_86C1D0>*/
	/*00584C05*/	mov dword ptr ds:[esi+0x1DB],ebx
	/*00584C0B*/	pop edi
	/*00584C0C*/	pop esi
	/*00584C0D*/	xor eax,eax
	/*00584C0F*/	pop ebx
	/*00584C10*/	ret 0x18
_00584C13:
	/*00584C13*/	cmp al,0xC
	/*00584C15*/	jge _00584C72
	/*00584C17*/	mov al,byte ptr ss:[esp+0x14]
	/*00584C1B*/	cmp al,0x6
	/*00584C1D*/	jne _00584C41
	/*00584C1F*/	push 0x32
	/*00584C21*/	push 0x78
_00584C23:
	/*00584C23*/	mov eax,dword ptr ds:[esi+0x4]
	/*00584C26*/	mov ecx,dword ptr ss:[esp+0x18]
	/*00584C2A*/	push 0x0
	/*00584C2C*/	push eax
	/*00584C2D*/	push ecx
	/*00584C2E*/	mov ecx,dword ptr ds:[0xDD7F00]
	/*00584C34*/	call sub_86BDD0		/*call <cm0102.sub_86BDD0>*/
	/*00584C39*/	pop edi
	/*00584C3A*/	pop esi
	/*00584C3B*/	xor eax,eax
	/*00584C3D*/	pop ebx
	/*00584C3E*/	ret 0x18
_00584C41:
	/*00584C41*/	cmp al,0xFE
	/*00584C43*/	jne _00584D4E
	/*00584C49*/	mov edx,dword ptr ds:[esi+0x4]
	/*00584C4C*/	mov esi,dword ptr ss:[esp+0x10]
	/*00584C50*/	mov ecx,dword ptr ds:[0xDD7F00]
	/*00584C56*/	push 0x32
	/*00584C58*/	push 0x44A
	/*00584C5D*/	push edx
	/*00584C5E*/	push esi
	/*00584C5F*/	call sub_86C1D0		/*call <cm0102.sub_86C1D0>*/
	/*00584C64*/	mov dword ptr ds:[esi+0x1DB],ebx
	/*00584C6A*/	pop edi
	/*00584C6B*/	pop esi
	/*00584C6C*/	xor eax,eax
	/*00584C6E*/	pop ebx
	/*00584C6F*/	ret 0x18
_00584C72:
	/*00584C72*/	jne _00584D4E
	/*00584C78*/	mov al,byte ptr ss:[esp+0x14]
	/*00584C7C*/	cmp al,0x1
	/*00584C7E*/	jne _00584CA8
	/*00584C80*/	mov eax,dword ptr ss:[esp+0x24]
	/*00584C84*/	mov ecx,dword ptr ss:[esp+0x20]
	/*00584C88*/	mov esi,dword ptr ss:[esp+0x10]
	/*00584C8C*/	push eax
	/*00584C8D*/	push ecx
	/*00584C8E*/	mov ecx,dword ptr ds:[0xDD7F00]
	/*00584C94*/	push esi
	/*00584C95*/	call sub_86A800		/*call cm0102.86A800*/
	/*00584C9A*/	mov dword ptr ds:[esi+0x1DB],ebx
	/*00584CA0*/	pop edi
	/*00584CA1*/	pop esi
	/*00584CA2*/	xor eax,eax
	/*00584CA4*/	pop ebx
	/*00584CA5*/	ret 0x18
_00584CA8:
	/*00584CA8*/	cmp al,0x2
	/*00584CAA*/	jne _00584CD4
	/*00584CAC*/	mov edx,dword ptr ss:[esp+0x24]
	/*00584CB0*/	mov eax,dword ptr ss:[esp+0x20]
	/*00584CB4*/	mov esi,dword ptr ss:[esp+0x10]
	/*00584CB8*/	mov ecx,dword ptr ds:[0xDD7F00]
	/*00584CBE*/	push edx
	/*00584CBF*/	push eax
	/*00584CC0*/	push esi
	/*00584CC1*/	call sub_86B0B0		/*call <cm0102.sub_86B0B0>*/
	/*00584CC6*/	mov dword ptr ds:[esi+0x1DB],ebx
	/*00584CCC*/	pop edi
	/*00584CCD*/	pop esi
	/*00584CCE*/	xor eax,eax
	/*00584CD0*/	pop ebx
	/*00584CD1*/	ret 0x18
_00584CD4:
	/*00584CD4*/	test al,al
	/*00584CD6*/	jne _00584D11
	/*00584CD8*/	mov edi,dword ptr ss:[esp+0x20]
	/*00584CDC*/	push 0x2
	/*00584CDE*/	mov cx,word ptr ds:[edi+0x34]
	/*00584CE2*/	push ecx
	/*00584CE3*/	push 0x64
	/*00584CE5*/	push 0x4B
	/*00584CE7*/	call sub_4BF850		/*call <cm0102.sub_4BF850>*/
	/*00584CEC*/	mov edx,dword ptr ds:[esi+0xC]
	/*00584CEF*/	add esp,0x10
	/*00584CF2*/	mov ecx,dword ptr ds:[edx+0x30]
	/*00584CF5*/	push eax
	/*00584CF6*/	movsx eax,word ptr ds:[edi+0x34]
	/*00584CFA*/	mov ecx,dword ptr ds:[ecx+0xA3]
	/*00584D00*/	lea edx,dword ptr ds:[eax+eax*0x2]
	/*00584D03*/	lea eax,dword ptr ds:[eax+edx*0x4]
	/*00584D06*/	mov dx,word ptr ds:[ecx+eax*0x8+0x6F]
	/*00584D0B*/	push edx
	/*00584D0C*/	jmp _00584C23
_00584D11:
	/*00584D11*/	cmp al,bl
	/*00584D13*/	jne _00584D4E
	/*00584D15*/	mov edi,dword ptr ss:[esp+0x20]
	/*00584D19*/	push 0x2
	/*00584D1B*/	mov dx,word ptr ds:[edi+0x34]
	/*00584D1F*/	push edx
	/*00584D20*/	push 0x64
	/*00584D22*/	push 0x4B
	/*00584D24*/	call sub_4BF850		/*call <cm0102.sub_4BF850>*/
	/*00584D29*/	mov ecx,dword ptr ds:[esi+0x4]
	/*00584D2C*/	add esp,0x10
	/*00584D2F*/	push eax
	/*00584D30*/	mov ax,word ptr ds:[edi+0x30]
	/*00584D34*/	push eax
	/*00584D35*/	push 0x0
	/*00584D37*/	push ecx
_00584D38:
	/*00584D38*/	mov esi,dword ptr ss:[esp+0x20]
	/*00584D3C*/	mov ecx,dword ptr ds:[0xDD7F00]
	/*00584D42*/	push esi
	/*00584D43*/	call sub_86C000		/*call <cm0102.sub_86C000>*/
	/*00584D48*/	mov dword ptr ds:[esi+0x1DB],ebx
_00584D4E:
	/*00584D4E*/	pop edi
	/*00584D4F*/	pop esi
	/*00584D50*/	xor eax,eax
	/*00584D52*/	pop ebx
	/*00584D53*/	ret 0x18
	}
}

extern "C" void __declspec(naked) sub_584D60()
{
	__asm pushad
	dprintf("sub_584D60 Called!\n");
	__asm popad

	__asm
	{
	/*00584D60*/	sub esp,0x200
	/*00584D66*/	push ebx
	/*00584D67*/	push esi
	/*00584D68*/	mov esi,ecx
	/*00584D6A*/	xor ebx,ebx
	/*00584D6C*/	mov eax,dword ptr ds:[esi+0xA7]
	/*00584D72*/	mov dword ptr ds:[esi+0x4C],ebx
	/*00584D75*/	cmp eax,ebx
	/*00584D77*/	je _00584D88
	/*00584D79*/	push eax
	/*00584D7A*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00584D7F*/	add esp,0x4
	/*00584D82*/	mov dword ptr ds:[esi+0xA7],ebx
_00584D88:
	/*00584D88*/	mov eax,dword ptr ds:[esi+0x14]
	/*00584D8B*/	cmp eax,ebx
	/*00584D8D*/	je _00584D9B
	/*00584D8F*/	push eax
	/*00584D90*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00584D95*/	add esp,0x4
	/*00584D98*/	mov dword ptr ds:[esi+0x14],ebx
_00584D9B:
	/*00584D9B*/	mov eax,dword ptr ds:[esi+0xA3]
	/*00584DA1*/	cmp eax,ebx
	/*00584DA3*/	je _00584DB4
	/*00584DA5*/	push eax
	/*00584DA6*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00584DAB*/	add esp,0x4
	/*00584DAE*/	mov dword ptr ds:[esi+0xA3],ebx
_00584DB4:
	/*00584DB4*/	mov eax,dword ptr ds:[esi+0xAD]
	/*00584DBA*/	push edi
	/*00584DBB*/	cmp eax,ebx
	/*00584DBD*/	je _00584E04
	/*00584DBF*/	xor edi,edi
	/*00584DC1*/	cmp word ptr ds:[esi+0x3C],bx
	/*00584DC5*/	jle _00584DEF
_00584DC7:
	/*00584DC7*/	mov eax,dword ptr ds:[esi+0xAD]
	/*00584DCD*/	mov eax,dword ptr ds:[eax+edi*0x4]
	/*00584DD0*/	cmp eax,ebx
	/*00584DD2*/	je _00584DE6
	/*00584DD4*/	push eax
	/*00584DD5*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00584DDA*/	mov ecx,dword ptr ds:[esi+0xAD]
	/*00584DE0*/	add esp,0x4
	/*00584DE3*/	mov dword ptr ds:[ecx+edi*0x4],ebx
_00584DE6:
	/*00584DE6*/	movsx edx,word ptr ds:[esi+0x3C]
	/*00584DEA*/	inc edi
	/*00584DEB*/	cmp edi,edx
	/*00584DED*/	jl _00584DC7
_00584DEF:
	/*00584DEF*/	mov eax,dword ptr ds:[esi+0xAD]
	/*00584DF5*/	push eax
	/*00584DF6*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00584DFB*/	add esp,0x4
	/*00584DFE*/	mov dword ptr ds:[esi+0xAD],ebx
_00584E04:
	/*00584E04*/	mov eax,dword ptr ds:[esi+0x30]
	/*00584E07*/	xor edi,edi
	/*00584E09*/	cmp eax,ebx
	/*00584E0B*/	jl _00584E25
_00584E0D:
	/*00584E0D*/	mov ecx,dword ptr ds:[esi+0xC]
	/*00584E10*/	mov ecx,dword ptr ds:[ecx+edi*0x4]
	/*00584E13*/	cmp ecx,ebx
	/*00584E15*/	je _00584E1D
	/*00584E17*/	mov edx,dword ptr ds:[ecx]
	/*00584E19*/	push 0x1
	/*00584E1B*/	call dword ptr ds:[edx]
_00584E1D:
	/*00584E1D*/	mov eax,dword ptr ds:[esi+0x30]
	/*00584E20*/	inc edi
	/*00584E21*/	cmp edi,eax
	/*00584E23*/	jle _00584E0D
_00584E25:
	/*00584E25*/	mov ecx,dword ptr ds:[esi+0x8]
	/*00584E28*/	mov dword ptr ds:[esi+0x30],0xFFFFFFFF
	/*00584E2F*/	cmp ecx,ebx
	/*00584E31*/	pop edi
	/*00584E32*/	je _00584E3B
	/*00584E34*/	push 0x1
	/*00584E36*/	call sub_4A1C50		/*call <cm0102.sub_4A1C50>*/
_00584E3B:
	/*00584E3B*/	inc word ptr ds:[esi+0x40]
	/*00584E3F*/	mov byte ptr ds:[esi+0xAB],bl
	/*00584E45*/	mov byte ptr ds:[esi+0xB1],bl
	/*00584E4B*/	mov ecx,dword ptr ds:[0xDE1F58]		//  contains an address of the UEFA Country Rankings
	/*00584E51*/	cmp ecx,ebx
	/*00584E53*/	je _00584E5B
	/*00584E55*/	push ebx
	/*00584E56*/	call sub_9035A0		/*call <cm0102.sub_9035A0>*/
_00584E5B:
	/*00584E5B*/	mov ecx,esi
	/*00584E5D*/	call european_cup_select_teams_584FA0		/*call <cm0102.european_cup_select_teams_584FA0>*/
	/*00584E62*/	test eax,eax
	/*00584E64*/	jne _00584E98
	/*00584E66*/	lea eax,dword ptr ss:[esp+0x8]
	/*00584E6A*/	lea ecx,dword ptr ss:[esp+0x108]
	/*00584E71*/	push eax
	/*00584E72*/	push ecx
	/*00584E73*/	push ebx
	/*00584E74*/	push ebx
	/*00584E75*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00584E7A*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00584E7F*/	add esp,0x14
	/*00584E82*/	lea edx,dword ptr ss:[esp+0x8]
	/*00584E86*/	lea eax,dword ptr ss:[esp+0x108]
	/*00584E8D*/	push 0x40C
	/*00584E92*/	push edx
	/*00584E93*/	jmp _00584F4B
_00584E98:
	/*00584E98*/	mov ecx,esi
	/*00584E9A*/	call european_cup_get_qualifying_teams_584990		/*call <cm0102.european_cup_get_qualifying_teams_584990>*/
	/*00584E9F*/	test eax,eax
	/*00584EA1*/	jge _00584ED3
	/*00584EA3*/	lea ecx,dword ptr ss:[esp+0x108]
	/*00584EAA*/	lea edx,dword ptr ss:[esp+0x8]
	/*00584EAE*/	push ecx
	/*00584EAF*/	push edx
	/*00584EB0*/	push ebx
	/*00584EB1*/	push ebx
	/*00584EB2*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00584EB7*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00584EBC*/	add esp,0x14
	/*00584EBF*/	lea eax,dword ptr ss:[esp+0x108]
	/*00584EC6*/	lea ecx,dword ptr ss:[esp+0x8]
	/*00584ECA*/	push 0x413
	/*00584ECF*/	push eax
	/*00584ED0*/	push ecx
	/*00584ED1*/	jmp _00584F4C
_00584ED3:
	/*00584ED3*/	mov edx,dword ptr ds:[esi]
	/*00584ED5*/	mov ecx,esi
	/*00584ED7*/	call dword ptr ds:[edx+0x8C]
	/*00584EDD*/	test eax,eax
	/*00584EDF*/	jge _00584F10
	/*00584EE1*/	lea eax,dword ptr ss:[esp+0x108]
	/*00584EE8*/	lea ecx,dword ptr ss:[esp+0x8]
	/*00584EEC*/	push eax
	/*00584EED*/	push ecx
	/*00584EEE*/	push ebx
	/*00584EEF*/	push ebx
	/*00584EF0*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00584EF5*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00584EFA*/	add esp,0x14
	/*00584EFD*/	lea edx,dword ptr ss:[esp+0x108]
	/*00584F04*/	lea eax,dword ptr ss:[esp+0x8]
	/*00584F08*/	push 0x41A
	/*00584F0D*/	push edx
	/*00584F0E*/	jmp _00584F4B
_00584F10:
	/*00584F10*/	mov edx,dword ptr ds:[esi]
	/*00584F12*/	mov ecx,esi
	/*00584F14*/	call dword ptr ds:[edx+0x94]
	/*00584F1A*/	test eax,eax
	/*00584F1C*/	jge _00584F83
	/*00584F1E*/	lea eax,dword ptr ss:[esp+0x108]
	/*00584F25*/	lea ecx,dword ptr ss:[esp+0x8]
	/*00584F29*/	push eax
	/*00584F2A*/	push ecx
	/*00584F2B*/	push ebx
	/*00584F2C*/	push ebx
	/*00584F2D*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00584F32*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00584F37*/	add esp,0x14
	/*00584F3A*/	lea edx,dword ptr ss:[esp+0x108]
	/*00584F41*/	lea eax,dword ptr ss:[esp+0x8]
	/*00584F45*/	push 0x421
	/*00584F4A*/	push edx
_00584F4B:
	/*00584F4B*/	push eax
_00584F4C:
	/*00584F4C*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*00584F51*/	push eax
	/*00584F52*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*00584F57*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00584F5C*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*00584F61*/	push ebx
	/*00584F62*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00584F67*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*00584F6C*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*00584F71*/	add esp,0x24
	/*00584F74*/	mov dword ptr ds:[0xB67A34],ebx
	/*00584F7A*/	pop esi
	/*00584F7B*/	pop ebx
	/*00584F7C*/	add esp,0x200
	/*00584F82*/	ret
_00584F83:
	/*00584F83*/	mov edx,dword ptr ds:[esi]
	/*00584F85*/	mov ecx,esi
	/*00584F87*/	call dword ptr ds:[edx+0x5C]
	/*00584F8A*/	pop esi
	/*00584F8B*/	pop ebx
	/*00584F8C*/	add esp,0x200
	/*00584F92*/	ret
	}
}

extern "C" void __declspec(naked) european_cup_select_teams_584FA0()		// On Seup: Second Function called (once) - Select Teams?
{
	__asm pushad
	dprintf("european_cup_select_teams_584FA0 Called!\n");
	__asm popad

	__asm
	{
	/*00584FA0*/	sub esp,0x214
	/*00584FA6*/	push esi
	/*00584FA7*/	mov esi,ecx
	/*00584FA9*/	mov eax,0x47
	/*00584FAE*/	push edi
	/*00584FAF*/	mov word ptr ds:[esi+0x36],ax
	/*00584FB3*/	mov word ptr ds:[esi+0x38],ax
	/*00584FB7*/	mov eax,dword ptr ds:[esi+0x14]
	/*00584FBA*/	xor edi,edi
	/*00584FBC*/	cmp eax,edi
	/*00584FBE*/	mov dword ptr ss:[esp+0x8],edi
	/*00584FC2*/	mov dword ptr ss:[esp+0x10],edi
	/*00584FC6*/	mov dword ptr ss:[esp+0x14],edi
	/*00584FCA*/	mov dword ptr ss:[esp+0xC],edi
	/*00584FCE*/	je _00584FD9
	/*00584FD0*/	push eax
	/*00584FD1*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00584FD6*/	add esp,0x4
_00584FD9:
	/*00584FD9*/	movsx eax,word ptr ds:[esi+0x36]			// esi: European Champions Cup esi+36 = 0x47 = 71
	/*00584FDD*/	lea eax,dword ptr ds:[eax+eax*0x2]			// 71 * 3 = 213
	/*00584FE0*/	shl eax,0x1									// 213 * 2 = 426 bytes (71  * 6)
	/*00584FE2*/	push eax
	/*00584FE3*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*00584FE8*/	add esp,0x4
	/*00584FEB*/	cmp eax,edi
	/*00584FED*/	mov dword ptr ds:[esi+0x14],eax				// esi+14 = Where the teams will be stored
	/*00584FF0*/	jne _00585059
	/*00584FF2*/	lea ecx,dword ptr ss:[esp+0x1C]
	/*00584FF6*/	lea edx,dword ptr ss:[esp+0x11C]
	/*00584FFD*/	push ecx
	/*00584FFE*/	push edx
	/*00584FFF*/	push edi
	/*00585000*/	push edi
	/*00585001*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00585006*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*0058500B*/	add esp,0x14
	/*0058500E*/	lea eax,dword ptr ss:[esp+0x1C]
	/*00585012*/	lea ecx,dword ptr ss:[esp+0x11C]
	/*00585019*/	push 0x44E
	/*0058501E*/	push eax
	/*0058501F*/	push ecx
	/*00585020*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*00585025*/	push eax
	/*00585026*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*0058502B*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00585030*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*00585035*/	push edi
	/*00585036*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*0058503B*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*00585040*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*00585045*/	add esp,0x24
	/*00585048*/	mov dword ptr ds:[0xB67A34],edi
	/*0058504E*/	xor eax,eax
	/*00585050*/	pop edi
	/*00585051*/	pop esi
	/*00585052*/	add esp,0x214
	/*00585058*/	ret
_00585059:
	/*00585059*/	mov ecx,dword ptr ds:[0xAE235C]		// Number of Clubs
	/*0058505F*/	mov eax,dword ptr ds:[0xAE23B4]		// Clubs Pointer
	/*00585064*/	cmp ecx,edi
	/*00585066*/	push ebx
	/*00585067*/	mov dword ptr ss:[esp+0x1C],edi
	/*0058506B*/	jle _00585186
	/*00585071*/	push ebp
	/*00585072*/	xor edx,edx
	/*00585074*/	xor ecx,ecx
	/*00585076*/	xor ebp,ebp
_00585078:
	/*00585078*/	mov ebx,dword ptr ds:[eax+0x1DB]	// Check if this club has been marked for Euro Champions Cup
	/*0058507E*/	cmp ebx,dword ptr ds:[0x9CF6E8]		/* European Champions Cup */
	/*00585084*/	jne _00585166
	/*0058508A*/	mov bl,byte ptr ds:[eax+0x1DF]		// Seed Number? Ensures the right number in the right order are added to the team block at esi+14
	/*00585090*/	cmp bl,0x1
	/*00585093*/	jne _005850C5
	/*00585095*/	cmp ebp,0x60						// 96 / 6 = 16
	/*00585098*/	jge _00585166
	/*0058509E*/	mov ebx,dword ptr ds:[esi+0x14]
	/*005850A1*/	mov dword ptr ds:[ebx+ebp],eax
	/*005850A4*/	mov ebx,dword ptr ds:[esi+0x14]
	/*005850A7*/	mov byte ptr ds:[ebx+ebp+0x5],0x0
	/*005850AC*/	mov ebx,dword ptr ds:[esi+0x14]
	/*005850AF*/	mov byte ptr ds:[ebx+ebp+0x4],0x7
	/*005850B4*/	mov ebx,dword ptr ss:[esp+0x14]
	/*005850B8*/	inc ebx
	/*005850B9*/	add ebp,0x6
	/*005850BC*/	mov dword ptr ss:[esp+0x14],ebx
	/*005850C0*/	jmp _00585166
_005850C5:
	/*005850C5*/	cmp bl,0x2
	/*005850C8*/	jne _005850F8
	/*005850CA*/	cmp edi,0x6C						// 108 / 6 = 18
	/*005850CD*/	jge _00585166
	/*005850D3*/	mov ebx,dword ptr ds:[esi+0x14]
	/*005850D6*/	mov dword ptr ds:[edi+ebx+0x60],eax
	/*005850DA*/	mov ebx,dword ptr ds:[esi+0x14]
	/*005850DD*/	mov byte ptr ds:[edi+ebx+0x65],0x0
	/*005850E2*/	mov ebx,dword ptr ds:[esi+0x14]
	/*005850E5*/	mov byte ptr ds:[edi+ebx+0x64],0x8
	/*005850EA*/	mov ebx,dword ptr ss:[esp+0x1C]
	/*005850EE*/	inc ebx
	/*005850EF*/	add edi,0x6
	/*005850F2*/	mov dword ptr ss:[esp+0x1C],ebx
	/*005850F6*/	jmp _00585166
_005850F8:
	/*005850F8*/	cmp bl,0x3
	/*005850FB*/	jne _00585130
	/*005850FD*/	cmp ecx,0x72						// 114 / 6 = 19
	/*00585100*/	jge _00585166
	/*00585102*/	mov ebx,dword ptr ds:[esi+0x14]
	/*00585105*/	mov dword ptr ds:[ecx+ebx+0xCC],eax
	/*0058510C*/	mov ebx,dword ptr ds:[esi+0x14]
	/*0058510F*/	mov byte ptr ds:[ecx+ebx+0xD1],0x0
	/*00585117*/	mov ebx,dword ptr ds:[esi+0x14]
	/*0058511A*/	mov byte ptr ds:[ecx+ebx+0xD0],0xD
	/*00585122*/	mov ebx,dword ptr ss:[esp+0x18]
	/*00585126*/	inc ebx
	/*00585127*/	add ecx,0x6
	/*0058512A*/	mov dword ptr ss:[esp+0x18],ebx
	/*0058512E*/	jmp _00585166
_00585130:
	/*00585130*/	cmp bl,0x4
	/*00585133*/	jne _00585166
	/*00585135*/	cmp edx,0x6C						// 108 / 6 = 18 - 16 + 18 + 19 + 18 = 71  https://champman0102.net/viewtopic.php?p=131456#p131456 
	/*00585138*/	jge _00585166
	/*0058513A*/	mov ebx,dword ptr ds:[esi+0x14]
	/*0058513D*/	mov dword ptr ds:[edx+ebx+0x13E],eax
	/*00585144*/	mov ebx,dword ptr ds:[esi+0x14]
	/*00585147*/	mov byte ptr ds:[edx+ebx+0x143],0x0
	/*0058514F*/	mov ebx,dword ptr ds:[esi+0x14]
	/*00585152*/	mov byte ptr ds:[edx+ebx+0x142],0x0
	/*0058515A*/	mov ebx,dword ptr ss:[esp+0x10]
	/*0058515E*/	inc ebx
	/*0058515F*/	add edx,0x6
	/*00585162*/	mov dword ptr ss:[esp+0x10],ebx
_00585166:
	/*00585166*/	mov ebx,dword ptr ss:[esp+0x20]
	/*0058516A*/	add eax,0x245
	/*0058516F*/	inc ebx
	/*00585170*/	mov dword ptr ss:[esp+0x20],ebx
	/*00585174*/	movsx ebx,bx
	/*00585177*/	cmp ebx,dword ptr ds:[0xAE235C]			// Number of Clubs
	/*0058517D*/	jl _00585078
	/*00585183*/	xor edi,edi
	/*00585185*/	pop ebp
_00585186:
	/*00585186*/	mov edx,dword ptr ss:[esp+0x10]
	/*0058518A*/	mov eax,dword ptr ss:[esp+0x18]
	/*0058518E*/	mov ebx,dword ptr ss:[esp+0x14]
	/*00585192*/	mov ecx,dword ptr ss:[esp+0xC]
	/*00585196*/	add edx,eax
	/*00585198*/	add edx,ebx
	/*0058519A*/	pop ebx
	/*0058519B*/	add edx,ecx
	/*0058519D*/	movsx ecx,word ptr ds:[esi+0x36]
	/*005851A1*/	cmp edx,ecx
	/*005851A3*/	je _005851B4
	/*005851A5*/	mov word ptr ds:[esi+0x36],di
	/*005851A9*/	pop edi
	/*005851AA*/	xor eax,eax
	/*005851AC*/	pop esi
	/*005851AD*/	add esp,0x214
	/*005851B3*/	ret
_005851B4:
	/*005851B4*/	pop edi
	/*005851B5*/	mov eax,0x1
	/*005851BA*/	pop esi
	/*005851BB*/	add esp,0x214
	/*005851C1*/	ret
	}
}

extern "C" void __declspec(naked) sub_5851D0()
{
	__asm pushad
	dprintf("sub_5851D0 Called!\n");
	__asm popad

	__asm
	{
	/*005851D0*/	mov edx,dword ptr ds:[ecx+0x2C]
	/*005851D3*/	mov eax,dword ptr ds:[ecx+0x30]
	/*005851D6*/	sub esp,0x200
	/*005851DC*/	dec edx
	/*005851DD*/	cmp eax,edx
	/*005851DF*/	jl _0058524B
	/*005851E1*/	lea eax,dword ptr ss:[esp]
	/*005851E5*/	lea ecx,dword ptr ss:[esp+0x100]
	/*005851EC*/	push eax
	/*005851ED*/	push ecx
	/*005851EE*/	push 0x0
	/*005851F0*/	push 0x0
	/*005851F2*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005851F7*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*005851FC*/	add esp,0x14
	/*005851FF*/	lea edx,dword ptr ss:[esp]
	/*00585203*/	lea eax,dword ptr ss:[esp+0x100]
	/*0058520A*/	push 0x495
	/*0058520F*/	push edx
	/*00585210*/	push eax
	/*00585211*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*00585216*/	push eax
	/*00585217*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*0058521C*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00585221*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*00585226*/	push 0x0
	/*00585228*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*0058522D*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*00585232*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*00585237*/	add esp,0x24
	/*0058523A*/	mov dword ptr ds:[0xB67A34],0x0
	/*00585244*/	add esp,0x200
	/*0058524A*/	ret
_0058524B:
	/*0058524B*/	inc eax
	/*0058524C*/	test eax,eax
	/*0058524E*/	mov dword ptr ds:[ecx+0x30],eax
	/*00585251*/	je _00585277
	/*00585253*/	cmp eax,0x8
	/*00585256*/	je _00585269
	/*00585258*/	cmp eax,0xC
	/*0058525B*/	jne _0058527C
	/*0058525D*/	call sub_586330		/*call <cm0102.sub_586330>*/
	/*00585262*/	add esp,0x200
	/*00585268*/	ret
_00585269:
	/*00585269*/	push 0x0
	/*0058526B*/	call sub_585AB0		/*call <cm0102.sub_585AB0>*/
	/*00585270*/	add esp,0x200
	/*00585276*/	ret
_00585277:
	/*00585277*/	call sub_585290		/*call <cm0102.sub_585290>*/
_0058527C:
	/*0058527C*/	add esp,0x200
	/*00585282*/	ret
	}
}

extern "C" void __declspec(naked) sub_585290()
{
	__asm pushad
	dprintf("sub_585290 Called!\n");
	__asm popad

	__asm
	{
	/*00585290*/	push 0xFFFFFFFF
	/*00585292*/	push 0x958ADE		/*push <cm0102.sub_958ADE>*/
	/*00585297*/	mov eax,dword ptr fs:[0x0]
	/*0058529D*/	push eax
	/*0058529E*/	mov dword ptr fs:[0x0],esp
	/*005852A5*/	sub esp,0x434
	/*005852AB*/	push ebx
	/*005852AC*/	push ebp
	/*005852AD*/	push esi
	/*005852AE*/	push edi
	/*005852AF*/	mov edi,ecx
	/*005852B1*/	push 0x9
	/*005852B3*/	push 0x20
	/*005852B5*/	mov dword ptr ss:[esp+0x3C],edi
	/*005852B9*/	mov byte ptr ss:[esp+0x2C],0x4
	/*005852BE*/	mov byte ptr ss:[esp+0x2D],0x1
	/*005852C3*/	mov byte ptr ss:[esp+0x2E],0x2
	/*005852C8*/	mov byte ptr ss:[esp+0x2F],0x0
	/*005852CD*/	mov byte ptr ss:[esp+0x30],0x2
	/*005852D2*/	mov byte ptr ss:[esp+0x31],0x0
	/*005852D7*/	mov byte ptr ss:[esp+0x32],0x0
	/*005852DC*/	mov byte ptr ss:[esp+0x33],0x0
	/*005852E1*/	xor ebp,ebp
	/*005852E3*/	xor esi,esi
	/*005852E5*/	call sub_945501		/*call <cm0102.sub_945501>*/
	/*005852EA*/	mov ebx,eax
	/*005852EC*/	add esp,0x8
	/*005852EF*/	cmp ebx,ebp
	/*005852F1*/	mov dword ptr ss:[esp+0x38],ebx
	/*005852F5*/	jne _00585358
	/*005852F7*/	lea eax,dword ptr ss:[esp+0x144]
	/*005852FE*/	lea ecx,dword ptr ss:[esp+0x44]
	/*00585302*/	push eax
	/*00585303*/	push ecx
	/*00585304*/	push ebp
	/*00585305*/	push ebp
	/*00585306*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*0058530B*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00585310*/	add esp,0x14
	/*00585313*/	lea edx,dword ptr ss:[esp+0x144]
	/*0058531A*/	lea eax,dword ptr ss:[esp+0x44]
	/*0058531E*/	push 0x4CC
	/*00585323*/	push edx
	/*00585324*/	push eax
	/*00585325*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*0058532A*/	push eax
	/*0058532B*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*00585330*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00585335*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*0058533A*/	push ebp
	/*0058533B*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00585340*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*00585345*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*0058534A*/	add esp,0x24
	/*0058534D*/	mov dword ptr ds:[0xB67A34],ebp
	/*00585353*/	jmp _00585A89
_00585358:
	/*00585358*/	xor eax,eax
_0058535A:
	/*0058535A*/	movsx ecx,si
	/*0058535D*/	add eax,0x6
	/*00585360*/	lea edx,dword ptr ds:[ebx+ecx*0x8]
	/*00585363*/	add ecx,edx
	/*00585365*/	mov edx,dword ptr ds:[edi+0x14]
	/*00585368*/	inc esi
	/*00585369*/	cmp eax,0x60
	/*0058536C*/	mov edx,dword ptr ds:[edx+eax-0x6]
	/*00585370*/	mov dword ptr ds:[ecx],edx
	/*00585372*/	mov dword ptr ds:[ecx+0x4],ebp
	/*00585375*/	jl _0058535A
	/*00585377*/	cmp word ptr ds:[edi+0x3E],bp
	/*0058537B*/	mov dword ptr ss:[esp+0x14],ebp
	/*0058537F*/	jle _005853BA
	/*00585381*/	xor edx,edx
_00585383:
	/*00585383*/	mov eax,dword ptr ds:[edi+0xA7]
	/*00585389*/	lea ecx,dword ptr ds:[eax+edx]
	/*0058538C*/	mov al,byte ptr ds:[eax+edx+0x5]
	/*00585390*/	cmp al,0x1
	/*00585392*/	jne _005853A6
	/*00585394*/	movsx eax,si
	/*00585397*/	mov ecx,dword ptr ds:[ecx]
	/*00585399*/	lea ebp,dword ptr ds:[ebx+eax*0x8]
	/*0058539C*/	add eax,ebp
	/*0058539E*/	xor ebp,ebp
	/*005853A0*/	inc esi
	/*005853A1*/	mov dword ptr ds:[eax],ecx
	/*005853A3*/	mov dword ptr ds:[eax+0x4],ebp
_005853A6:
	/*005853A6*/	mov eax,dword ptr ss:[esp+0x14]
	/*005853AA*/	add edx,0x6
	/*005853AD*/	movsx ecx,word ptr ds:[edi+0x3E]
	/*005853B1*/	inc eax
	/*005853B2*/	cmp eax,ecx
	/*005853B4*/	mov dword ptr ss:[esp+0x14],eax
	/*005853B8*/	jl _00585383
_005853BA:
	/*005853BA*/	cmp si,0x20
	/*005853BE*/	jge _00585435
	/*005853C0*/	lea edx,dword ptr ss:[esp+0x44]
	/*005853C4*/	lea eax,dword ptr ss:[esp+0x144]
	/*005853CB*/	push edx
	/*005853CC*/	push eax
	/*005853CD*/	push ebp
	/*005853CE*/	push ebp
	/*005853CF*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005853D4*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*005853D9*/	add esp,0x14
	/*005853DC*/	lea ecx,dword ptr ss:[esp+0x44]
	/*005853E0*/	lea edx,dword ptr ss:[esp+0x144]
	/*005853E7*/	push 0x4EE
	/*005853EC*/	push ecx
	/*005853ED*/	push edx
	/*005853EE*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*005853F3*/	push eax
	/*005853F4*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*005853F9*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005853FE*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*00585403*/	push ebp
	/*00585404*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00585409*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*0058540E*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*00585413*/	mov dword ptr ds:[0xB67A34],ebp
	/*00585419*/	push ebx
	/*0058541A*/	mov dword ptr ds:[edi+0x30],0xFFFFFFFF
	/*00585421*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00585426*/	add esp,0x28
	/*00585429*/	mov byte ptr ds:[edi+0xB1],0x0
	/*00585430*/	jmp _00585A89
_00585435:
	/*00585435*/	push 0x586F60		/*push cm0102.586F60*/		// <--- qsort function to sort by ClubEuroSeeding byte (club+1DF) and failing that reputation word (club+80)
	/*0058543A*/	push 0x9
	/*0058543C*/	push 0x20
	/*0058543E*/	push ebx
	/*0058543F*/	call cm0102_qsort		/*call <cm0102.cm0102_qsort>*/
	/*00585444*/	add esp,0x10
	/*00585447*/	mov esi,0x1
	/*0058544C*/	lea edx,dword ptr ds:[ebx+0x4]
_0058544F:
	/*0058544F*/	cmp dword ptr ds:[edx],0x0
	/*00585452*/	jne _0058548C
	/*00585454*/	cmp esi,0x20
	/*00585457*/	mov eax,esi
	/*00585459*/	jge _0058548C
	/*0058545B*/	lea ecx,dword ptr ds:[edx+0x5]
_0058545E:
	/*0058545E*/	mov edi,dword ptr ds:[ecx+0x4]
	/*00585461*/	test edi,edi
	/*00585463*/	jne _00585472
	/*00585465*/	mov edi,dword ptr ds:[edx-0x4]
	/*00585468*/	mov ebp,dword ptr ds:[ecx]
	/*0058546A*/	mov edi,dword ptr ds:[edi+0x53]
	/*0058546D*/	cmp edi,dword ptr ss:[ebp+0x53]
	/*00585470*/	je _0058547D
_00585472:
	/*00585472*/	inc eax
	/*00585473*/	add ecx,0x9
	/*00585476*/	cmp eax,0x20
	/*00585479*/	jl _0058545E
	/*0058547B*/	jmp _0058548C
_0058547D:
	/*0058547D*/	lea ecx,dword ptr ds:[ebx+eax*0x8]
	/*00585480*/	add eax,ecx
	/*00585482*/	mov ecx,dword ptr ds:[eax]
	/*00585484*/	mov dword ptr ds:[edx],ecx
	/*00585486*/	mov ecx,dword ptr ds:[edx-0x4]
	/*00585489*/	mov dword ptr ds:[eax+0x4],ecx
_0058548C:
	/*0058548C*/	inc esi
	/*0058548D*/	add edx,0x9
	/*00585490*/	lea eax,dword ptr ds:[esi-0x1]
	/*00585493*/	cmp eax,0x20
	/*00585496*/	jl _0058544F
	/*00585498*/	push 0x4
	/*0058549A*/	push 0x20
	/*0058549C*/	call sub_945501		/*call <cm0102.sub_945501>*/
	/*005854A1*/	mov ebp,eax
	/*005854A3*/	xor esi,esi
	/*005854A5*/	add esp,0x8
	/*005854A8*/	cmp ebp,esi
	/*005854AA*/	mov dword ptr ss:[esp+0x1C],ebp
	/*005854AE*/	jne _0058551D
	/*005854B0*/	lea ecx,dword ptr ss:[esp+0x44]
	/*005854B4*/	lea edx,dword ptr ss:[esp+0x144]
	/*005854BB*/	push ecx
	/*005854BC*/	push edx
	/*005854BD*/	push esi
	/*005854BE*/	push esi
	/*005854BF*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005854C4*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*005854C9*/	add esp,0x14
	/*005854CC*/	lea eax,dword ptr ss:[esp+0x44]
	/*005854D0*/	lea ecx,dword ptr ss:[esp+0x144]
	/*005854D7*/	push 0x515
	/*005854DC*/	push eax
	/*005854DD*/	push ecx
	/*005854DE*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*005854E3*/	push eax
	/*005854E4*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*005854E9*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005854EE*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*005854F3*/	push esi
	/*005854F4*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005854F9*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*005854FE*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*00585503*/	add esp,0x24
	/*00585506*/	mov dword ptr ds:[0xB67A34],esi
	/*0058550C*/	call sub_5CC7D0		/*call <cm0102.sub_5CC7D0>*/
	/*00585511*/	call sub_5A8F60		/*call <cm0102.sub_5A8F60>*/
	/*00585516*/	push 0xFFFFFFFF
	/*00585518*/	call cm0102_exit		/*call <cm0102.cm0102_exit>*/
_0058551D:
	/*0058551D*/	mov dword ptr ss:[esp+0x14],esi
	/*00585521*/	mov dword ptr ss:[esp+0x18],esi
	/*00585525*/	lea eax,dword ptr ds:[ebx+0x8]
_00585528:
	/*00585528*/	mov bl,0x4
	/*0058552A*/	mov byte ptr ss:[esp+0x13],0x4
	/*0058552F*/	mov byte ptr ss:[esp+0x12],bl
	/*00585533*/	mov ecx,eax
	/*00585535*/	mov edx,0x8
_0058553A:
	/*0058553A*/	mov al,byte ptr ds:[ecx]
	/*0058553C*/	cmp al,0x2
	/*0058553E*/	jne _00585544
	/*00585540*/	dec bl
	/*00585542*/	jmp _0058554C
_00585544:
	/*00585544*/	cmp al,0x1
	/*00585546*/	jne _0058554C
	/*00585548*/	dec byte ptr ss:[esp+0x13]
_0058554C:
	/*0058554C*/	add ecx,0x9
	/*0058554F*/	dec edx
	/*00585550*/	jne _0058553A
	/*00585552*/	mov dword ptr ss:[esp+0x2C],ecx
	/*00585556*/	mov byte ptr ss:[esp+0x12],bl
	/*0058555A*/	mov dword ptr ss:[esp+0x20],0x8
_00585562:
	/*00585562*/	push 0x8
	/*00585564*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*00585569*/	mov ebx,dword ptr ss:[esp+0x1C]
	/*0058556D*/	mov edi,dword ptr ss:[esp+0x3C]
	/*00585571*/	mov esi,eax
	/*00585573*/	add esp,0x4
	/*00585576*/	add esi,ebx
	/*00585578*/	lea edx,dword ptr ds:[edi+esi*0x8]
	/*0058557B*/	cmp dword ptr ds:[esi+edx],0x0
	/*0058557F*/	jne _00585598
_00585581:
	/*00585581*/	push 0x8
	/*00585583*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*00585588*/	mov esi,eax
	/*0058558A*/	add esp,0x4
	/*0058558D*/	add esi,ebx
	/*0058558F*/	lea eax,dword ptr ds:[edi+esi*0x8]
	/*00585592*/	cmp dword ptr ds:[esi+eax],0x0
	/*00585596*/	je _00585581
_00585598:
	/*00585598*/	lea ecx,dword ptr ds:[edi+esi*0x8]
	/*0058559B*/	mov al,byte ptr ds:[esi+ecx+0x8]
	/*0058559F*/	lea edi,dword ptr ds:[esi+ecx]
	/*005855A2*/	test al,al
	/*005855A4*/	jne _0058565A
	/*005855AA*/	movsx ebx,byte ptr ss:[esp+0x12]
	/*005855AF*/	movsx edx,byte ptr ss:[esp+0x13]
	/*005855B4*/	add edx,ebx
	/*005855B6*/	push edx
	/*005855B7*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*005855BC*/	add esp,0x4
	/*005855BF*/	cmp eax,ebx
	/*005855C1*/	jge _005855D3
	/*005855C3*/	mov al,byte ptr ss:[esp+0x12]
	/*005855C7*/	mov byte ptr ds:[edi+0x8],0x2
	/*005855CB*/	dec al
	/*005855CD*/	mov byte ptr ss:[esp+0x12],al
	/*005855D1*/	jmp _005855E1
_005855D3:
	/*005855D3*/	mov al,byte ptr ss:[esp+0x13]
	/*005855D7*/	mov byte ptr ds:[edi+0x8],0x1
	/*005855DB*/	dec al
	/*005855DD*/	mov byte ptr ss:[esp+0x13],al
_005855E1:
	/*005855E1*/	mov edx,dword ptr ds:[edi+0x4]
	/*005855E4*/	test edx,edx
	/*005855E6*/	je _0058565A
	/*005855E8*/	mov ebx,dword ptr ss:[esp+0x38]
	/*005855EC*/	xor ecx,ecx
	/*005855EE*/	mov eax,ebx
_005855F0:
	/*005855F0*/	cmp dword ptr ds:[eax],edx
	/*005855F2*/	je _005855FF
	/*005855F4*/	inc ecx
	/*005855F5*/	add eax,0x9
	/*005855F8*/	cmp ecx,0x20
	/*005855FB*/	jl _005855F0
	/*005855FD*/	jmp _0058565A
_005855FF:
	/*005855FF*/	mov eax,ecx
	/*00585601*/	cdq
	/*00585602*/	and edx,0x7
	/*00585605*/	add edx,eax
	/*00585607*/	mov eax,esi
	/*00585609*/	sar edx,0x3
	/*0058560C*/	mov dword ptr ss:[esp+0x30],edx
	/*00585610*/	cdq
	/*00585611*/	and edx,0x7
	/*00585614*/	add eax,edx
	/*00585616*/	mov edx,dword ptr ss:[esp+0x30]
	/*0058561A*/	sar eax,0x3
	/*0058561D*/	cmp edx,eax
	/*0058561F*/	jne _0058564A
	/*00585621*/	mov al,byte ptr ds:[edi+0x8]
	/*00585624*/	cmp al,0x2
	/*00585626*/	jne _00585630
	/*00585628*/	mov dl,byte ptr ss:[esp+0x13]
	/*0058562C*/	test dl,dl
	/*0058562E*/	je _0058565A
_00585630:
	/*00585630*/	cmp al,0x1
	/*00585632*/	jne _0058563C
	/*00585634*/	mov dl,byte ptr ss:[esp+0x12]
	/*00585638*/	test dl,dl
	/*0058563A*/	je _0058565A
_0058563C:
	/*0058563C*/	cmp al,0x2
	/*0058563E*/	jne _00585646
	/*00585640*/	dec byte ptr ss:[esp+0x13]
	/*00585644*/	jmp _0058564A
_00585646:
	/*00585646*/	dec byte ptr ss:[esp+0x12]
_0058564A:
	/*0058564A*/	mov al,byte ptr ds:[edi+0x8]
	/*0058564D*/	lea edx,dword ptr ds:[ebx+ecx*0x8]
	/*00585650*/	cmp al,0x2
	/*00585652*/	setne al
	/*00585655*/	inc eax
	/*00585656*/	mov byte ptr ds:[ecx+edx+0x8],al
_0058565A:
	/*0058565A*/	mov al,byte ptr ds:[edi+0x8]
	/*0058565D*/	dec al
	/*0058565F*/	neg al
	/*00585661*/	sbb al,al
	/*00585663*/	and eax,0x4
	/*00585666*/	movsx eax,al
	/*00585669*/	lea edx,dword ptr ds:[eax+0x4]
	/*0058566C*/	cmp eax,edx
	/*0058566E*/	jge _00585699
	/*00585670*/	mov esi,dword ptr ss:[esp+0x14]
	/*00585674*/	lea ecx,dword ptr ds:[esi+eax*0x4]
	/*00585677*/	lea ecx,dword ptr ss:[ebp+ecx*0x4]
_0058567B:
	/*0058567B*/	cmp dword ptr ds:[ecx],0x0
	/*0058567E*/	je _0058568A
	/*00585680*/	inc eax
	/*00585681*/	add ecx,0x10
	/*00585684*/	cmp eax,edx
	/*00585686*/	jl _0058567B
	/*00585688*/	jmp _00585699
_0058568A:
	/*0058568A*/	lea edx,dword ptr ds:[esi+eax*0x4]
	/*0058568D*/	mov eax,dword ptr ds:[edi]
	/*0058568F*/	mov dword ptr ss:[ebp+edx*0x4],eax
	/*00585693*/	mov dword ptr ds:[edi],0x0
_00585699:
	/*00585699*/	mov eax,dword ptr ss:[esp+0x20]
	/*0058569D*/	dec eax
	/*0058569E*/	mov dword ptr ss:[esp+0x20],eax
	/*005856A2*/	jne _00585562
	/*005856A8*/	mov ecx,dword ptr ss:[esp+0x18]
	/*005856AC*/	mov edi,dword ptr ss:[esp+0x14]
	/*005856B0*/	mov eax,dword ptr ss:[esp+0x2C]
	/*005856B4*/	add ecx,0x8
	/*005856B7*/	inc edi
	/*005856B8*/	cmp ecx,0x20
	/*005856BB*/	mov dword ptr ss:[esp+0x14],edi
	/*005856BF*/	mov dword ptr ss:[esp+0x18],ecx
	/*005856C3*/	jl _00585528
	/*005856C9*/	mov ecx,dword ptr ss:[esp+0x38]
	/*005856CD*/	push ecx
	/*005856CE*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*005856D3*/	add esp,0x4
	/*005856D6*/	xor ecx,ecx
	/*005856D8*/	mov dword ptr ss:[esp+0x14],ecx
_005856DC:
	/*005856DC*/	mov al,cl
	/*005856DE*/	xor edi,edi
	/*005856E0*/	shl al,0x2
	/*005856E3*/	lea edx,dword ptr ds:[ecx*0x4+0x4]
	/*005856EA*/	mov byte ptr ss:[esp+0x12],al
	/*005856EE*/	mov dword ptr ss:[esp+0x20],edx
_005856F2:
	/*005856F2*/	movsx esi,al
	/*005856F5*/	cmp esi,edx
	/*005856F7*/	mov byte ptr ss:[esp+0x18],al
	/*005856FB*/	jge _005857AE
_00585701:
	/*00585701*/	xor eax,eax
_00585703:
	/*00585703*/	cmp edi,eax
	/*00585705*/	je _0058571D
	/*00585707*/	lea ebx,dword ptr ds:[edi+esi*0x4]
	/*0058570A*/	lea ecx,dword ptr ds:[eax+esi*0x4]
	/*0058570D*/	mov ebx,dword ptr ss:[ebp+ebx*0x4]
	/*00585711*/	mov ecx,dword ptr ss:[ebp+ecx*0x4]
	/*00585715*/	mov ebx,dword ptr ds:[ebx+0x53]
	/*00585718*/	cmp ebx,dword ptr ds:[ecx+0x53]
	/*0058571B*/	je _00585725
_0058571D:
	/*0058571D*/	inc eax
	/*0058571E*/	cmp eax,0x4
	/*00585721*/	jl _00585703
	/*00585723*/	jmp _00585791
_00585725:
	/*00585725*/	mov bl,byte ptr ss:[esp+0x12]
	/*00585729*/	movsx eax,bl
	/*0058572C*/	cmp eax,edx
	/*0058572E*/	jge _00585791
_00585730:
	/*00585730*/	cmp byte ptr ss:[esp+0x18],bl
	/*00585734*/	je _00585761
	/*00585736*/	lea edx,dword ptr ds:[edi+esi*0x4]
	/*00585739*/	xor ecx,ecx
	/*0058573B*/	shl eax,0x4
	/*0058573E*/	mov edx,dword ptr ss:[ebp+edx*0x4]
	/*00585742*/	add eax,ebp
	/*00585744*/	mov edx,dword ptr ds:[edx+0x53]
_00585747:
	/*00585747*/	mov ebp,dword ptr ds:[eax]
	/*00585749*/	cmp edx,dword ptr ss:[ebp+0x53]
	/*0058574C*/	je _00585759
	/*0058574E*/	inc ecx
	/*0058574F*/	add eax,0x4
	/*00585752*/	cmp ecx,0x4
	/*00585755*/	jge _0058576C
	/*00585757*/	jmp _00585747
_00585759:
	/*00585759*/	mov ebp,dword ptr ss:[esp+0x1C]
	/*0058575D*/	mov edx,dword ptr ss:[esp+0x20]
_00585761:
	/*00585761*/	inc bl
	/*00585763*/	movsx eax,bl
	/*00585766*/	cmp eax,edx
	/*00585768*/	jge _00585791
	/*0058576A*/	jmp _00585730
_0058576C:
	/*0058576C*/	mov ebp,dword ptr ss:[esp+0x1C]
	/*00585770*/	lea eax,dword ptr ds:[edi+esi*0x4]
	/*00585773*/	movsx ecx,bl
	/*00585776*/	mov edx,dword ptr ss:[ebp+eax*0x4]
	/*0058577A*/	lea eax,dword ptr ss:[ebp+eax*0x4]
	/*0058577E*/	lea ecx,dword ptr ds:[edi+ecx*0x4]
	/*00585781*/	mov esi,dword ptr ss:[ebp+ecx*0x4]
	/*00585785*/	lea ecx,dword ptr ss:[ebp+ecx*0x4]
	/*00585789*/	mov dword ptr ds:[eax],esi
	/*0058578B*/	mov dword ptr ds:[ecx],edx
	/*0058578D*/	mov edx,dword ptr ss:[esp+0x20]
_00585791:
	/*00585791*/	mov al,byte ptr ss:[esp+0x18]
	/*00585795*/	inc al
	/*00585797*/	movsx esi,al
	/*0058579A*/	cmp esi,edx
	/*0058579C*/	mov byte ptr ss:[esp+0x18],al
	/*005857A0*/	jl _00585701
	/*005857A6*/	mov al,byte ptr ss:[esp+0x12]
	/*005857AA*/	mov ecx,dword ptr ss:[esp+0x14]
_005857AE:
	/*005857AE*/	inc edi
	/*005857AF*/	cmp edi,0x4
	/*005857B2*/	jl _005856F2
	/*005857B8*/	inc ecx
	/*005857B9*/	cmp ecx,0x2
	/*005857BC*/	mov dword ptr ss:[esp+0x14],ecx
	/*005857C0*/	jl _005856DC
	/*005857C6*/	mov byte ptr ss:[esp+0x18],0x0
_005857CB:
	/*005857CB*/	movsx eax,byte ptr ss:[esp+0x18]
	/*005857D0*/	mov edi,dword ptr ss:[esp+0x34]
	/*005857D4*/	mov dword ptr ss:[esp+0x30],eax
	/*005857D8*/	shl eax,0x4
	/*005857DB*/	mov dword ptr ss:[esp+0x1C],0x4
	/*005857E3*/	lea ebx,dword ptr ds:[eax+ebp]
	/*005857E6*/	mov dword ptr ss:[esp+0x2C],ebx
_005857EA:
	/*005857EA*/	mov esi,dword ptr ds:[ebx]
	/*005857EC*/	mov ecx,dword ptr ds:[0xDE1F58]		//  contains an address of the UEFA Country Rankings
	/*005857F2*/	push 0x1
	/*005857F4*/	mov edx,dword ptr ds:[esi+0x53]
	/*005857F7*/	push edx
	/*005857F8*/	call sub_9058B0		/*call <cm0102.sub_9058B0>*/
	/*005857FD*/	mov ecx,dword ptr ds:[0xAE2A38]		// Countries Pointer
	/*00585803*/	push 0x1B7740
	/*00585808*/	push esi
	/*00585809*/	call sub_5A0590		/*call <cm0102.sub_5A0590>*/
	/*0058580E*/	mov ecx,eax
	/*00585810*/	call sub_5999A0		/*call <cm0102.sub_5999A0>*/
	/*00585815*/	push 0xFFFFFFFE
	/*00585817*/	push 0x0
	/*00585819*/	push 0x449
	/*0058581E*/	push 0xFFFFFFFF
	/*00585820*/	push 0x0
	/*00585822*/	push 0x1B7740
	/*00585827*/	push esi
	/*00585828*/	mov ecx,edi
	/*0058582A*/	call sub_48E3E0		/*call <cm0102.sub_48E3E0>*/
	/*0058582F*/	mov eax,dword ptr ss:[esp+0x1C]
	/*00585833*/	add ebx,0x4
	/*00585836*/	dec eax
	/*00585837*/	mov dword ptr ss:[esp+0x1C],eax
	/*0058583B*/	jne _005857EA
	/*0058583D*/	mov ebx,dword ptr ss:[esp+0x18]
	/*00585841*/	mov eax,dword ptr ds:[edi]
	/*00585843*/	lea ecx,dword ptr ss:[esp+0x40]
	/*00585847*/	push 0x0
	/*00585849*/	lea edx,dword ptr ss:[esp+0x40]
	/*0058584D*/	push ecx
	/*0058584E*/	push edx
	/*0058584F*/	push ebx
	/*00585850*/	mov ecx,edi
	/*00585852*/	call dword ptr ds:[eax+0x3C]
	/*00585855*/	push 0xEE
	/*0058585A*/	mov esi,eax
	/*0058585C*/	call cm0102_new		/*call <cm0102.cm0102_new>*/
	/*00585861*/	add esp,0x4
	/*00585864*/	mov dword ptr ss:[esp+0x1C],eax
	/*00585868*/	test eax,eax
	/*0058586A*/	mov dword ptr ss:[esp+0x44C],0x0
	/*00585875*/	je _005858BD
	/*00585877*/	mov ecx,dword ptr ss:[esp+0x40]
	/*0058587B*/	mov dx,word ptr ds:[edi+0x40]
	/*0058587F*/	push 0x2
	/*00585881*/	push 0x0
	/*00585883*/	push 0xFFFFFFFF
	/*00585885*/	push 0x8
	/*00585887*/	push 0x0
	/*00585889*/	push 0x2
	/*0058588B*/	push 0xF
	/*0058588D*/	push ecx
	/*0058588E*/	push ebx
	/*0058588F*/	push edx
	/*00585890*/	lea ecx,dword ptr ss:[esp+0x50]
	/*00585894*/	lea edx,dword ptr ss:[esp+0x4C]
	/*00585898*/	push ecx
	/*00585899*/	mov ecx,dword ptr ss:[esp+0x68]
	/*0058589D*/	push edx
	/*0058589E*/	mov edx,dword ptr ds:[edi+0x4]
	/*005858A1*/	push 0x8
	/*005858A3*/	push 0x1
	/*005858A5*/	push 0x3
	/*005858A7*/	push ecx
	/*005858A8*/	mov ecx,dword ptr ss:[esp+0x6C]
	/*005858AC*/	push esi
	/*005858AD*/	push edx
	/*005858AE*/	push 0x2
	/*005858B0*/	push ecx
	/*005858B1*/	push 0x4
	/*005858B3*/	push edi
	/*005858B4*/	mov ecx,eax
	/*005858B6*/	call cm0102_create_league_68B100		/*call <cm0102.cm0102_create_league_68B100>*/
	/*005858BB*/	jmp _005858BF
_005858BD:
	/*005858BD*/	xor eax,eax
_005858BF:
	/*005858BF*/	mov edx,dword ptr ds:[edi+0xC]
	/*005858C2*/	mov ebx,dword ptr ss:[esp+0x30]
	/*005858C6*/	mov dword ptr ss:[esp+0x44C],0xFFFFFFFF
	/*005858D1*/	mov dword ptr ds:[edx+ebx*0x4],eax
	/*005858D4*/	mov eax,dword ptr ds:[edi+0xC]
	/*005858D7*/	cmp dword ptr ds:[eax+ebx*0x4],0x0
	/*005858DB*/	je _00585992
	/*005858E1*/	push esi
	/*005858E2*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*005858E7*/	mov ecx,dword ptr ds:[edi+0xC]
	/*005858EA*/	mov dword ptr ds:[edi+0x30],ebx
	/*005858ED*/	add esp,0x4
	/*005858F0*/	mov ecx,dword ptr ds:[ecx+ebx*0x4]
	/*005858F3*/	call sub_684230		/*call <cm0102.sub_684230>*/
	/*005858F8*/	mov al,byte ptr ss:[esp+0x18]
	/*005858FC*/	inc al
	/*005858FE*/	cmp al,0x8
	/*00585900*/	mov byte ptr ss:[esp+0x18],al
	/*00585904*/	jl _005857CB
	/*0058590A*/	push ebp
	/*0058590B*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00585910*/	mov eax,dword ptr ds:[0xADADFC]
	/*00585915*/	mov ecx,dword ptr ds:[0x9CF6F0]			/* UEFA Cup */
	/*0058591B*/	xor edi,edi
	/*0058591D*/	add esp,0x4
	/*00585920*/	mov ecx,dword ptr ds:[eax+ecx*0x4]
	/*00585923*/	cmp ecx,edi
	/*00585925*/	jne _005859FA
	/*0058592B*/	lea edx,dword ptr ss:[esp+0x244]
	/*00585932*/	lea eax,dword ptr ss:[esp+0x344]
	/*00585939*/	push edx
	/*0058593A*/	push eax
	/*0058593B*/	push edi
	/*0058593C*/	push edi
	/*0058593D*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00585942*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00585947*/	add esp,0x14
	/*0058594A*/	lea ecx,dword ptr ss:[esp+0x244]
	/*00585951*/	lea edx,dword ptr ss:[esp+0x344]
	/*00585958*/	push 0x5D8
	/*0058595D*/	push ecx
	/*0058595E*/	push edx
	/*0058595F*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*00585964*/	push eax
	/*00585965*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*0058596A*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*0058596F*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*00585974*/	push edi
	/*00585975*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*0058597A*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*0058597F*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*00585984*/	add esp,0x24
	/*00585987*/	mov dword ptr ds:[0xB67A34],edi
	/*0058598D*/	jmp _00585A89
_00585992:
	/*00585992*/	lea edx,dword ptr ss:[esp+0x44]
	/*00585996*/	lea eax,dword ptr ss:[esp+0x144]
	/*0058599D*/	push edx
	/*0058599E*/	push eax
	/*0058599F*/	push 0x0
	/*005859A1*/	push 0x0
	/*005859A3*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005859A8*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*005859AD*/	add esp,0x14
	/*005859B0*/	lea ecx,dword ptr ss:[esp+0x44]
	/*005859B4*/	lea edx,dword ptr ss:[esp+0x144]
	/*005859BB*/	push 0x5C9
	/*005859C0*/	push ecx
	/*005859C1*/	push edx
	/*005859C2*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*005859C7*/	push eax
	/*005859C8*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*005859CD*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005859D2*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*005859D7*/	push 0x0
	/*005859D9*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005859DE*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*005859E3*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*005859E8*/	add esp,0x24
	/*005859EB*/	mov dword ptr ds:[0xB67A34],0x0
	/*005859F5*/	jmp _00585A89
_005859FA:
	/*005859FA*/	movsx eax,word ptr ds:[ecx+0x3E]
	/*005859FE*/	mov ebx,dword ptr ss:[esp+0x34]
	/*00585A02*/	sub eax,0x18
	/*00585A05*/	mov dword ptr ss:[esp+0x14],edi
	/*00585A09*/	cmp word ptr ds:[ebx+0x3E],di
	/*00585A0D*/	jle _00585A84
	/*00585A0F*/	lea esi,dword ptr ds:[eax+eax*0x2]
	/*00585A12*/	shl esi,0x1
_00585A14:
	/*00585A14*/	mov eax,dword ptr ds:[ebx+0xA7]
	/*00585A1A*/	lea edx,dword ptr ds:[eax+edi]
	/*00585A1D*/	mov al,byte ptr ds:[eax+edi+0x5]
	/*00585A21*/	cmp al,0x2
	/*00585A23*/	jne _00585A70
	/*00585A25*/	mov eax,dword ptr ds:[ecx+0xA7]
	/*00585A2B*/	mov edx,dword ptr ds:[edx]
	/*00585A2D*/	add eax,esi
	/*00585A2F*/	add esi,0x6
	/*00585A32*/	mov dword ptr ds:[eax],edx
	/*00585A34*/	mov ebp,dword ptr ds:[eax]
	/*00585A36*/	mov byte ptr ds:[eax+0x4],0x0
	/*00585A3A*/	mov byte ptr ds:[eax+0x5],0x0
	/*00585A3E*/	movsx edx,word ptr ds:[ecx+0x36]
	/*00585A42*/	mov ebx,dword ptr ds:[ecx+0x14]
	/*00585A45*/	lea edx,dword ptr ds:[edx+edx*0x2]
	/*00585A48*/	mov dword ptr ds:[ebx+edx*0x2],ebp
	/*00585A4B*/	mov ebx,dword ptr ds:[ecx+0x14]
	/*00585A4E*/	movsx edx,word ptr ds:[ecx+0x36]
	/*00585A52*/	lea edx,dword ptr ds:[edx+edx*0x2]
	/*00585A55*/	mov byte ptr ds:[ebx+edx*0x2+0x4],0x5
	/*00585A5A*/	inc word ptr ds:[ecx+0x36]
	/*00585A5E*/	mov eax,dword ptr ds:[eax]
	/*00585A60*/	mov edx,dword ptr ds:[0x9CF6F0]		/* UEFA Cup */
	/*00585A66*/	mov ebx,dword ptr ss:[esp+0x34]
	/*00585A6A*/	mov dword ptr ds:[eax+0x1DB],edx
_00585A70:
	/*00585A70*/	mov eax,dword ptr ss:[esp+0x14]
	/*00585A74*/	add edi,0x6
	/*00585A77*/	movsx edx,word ptr ds:[ebx+0x3E]
	/*00585A7B*/	inc eax
	/*00585A7C*/	cmp eax,edx
	/*00585A7E*/	mov dword ptr ss:[esp+0x14],eax
	/*00585A82*/	jl _00585A14
_00585A84:
	/*00585A84*/	mov eax,dword ptr ds:[ecx]
	/*00585A86*/	call dword ptr ds:[eax+0x5C]
_00585A89:
	/*00585A89*/	mov ecx,dword ptr ss:[esp+0x444]
	/*00585A90*/	pop edi
	/*00585A91*/	pop esi
	/*00585A92*/	pop ebp
	/*00585A93*/	pop ebx
	/*00585A94*/	mov dword ptr fs:[0x0],ecx
	/*00585A9B*/	add esp,0x440
	/*00585AA1*/	ret
	}
}

extern "C" void __declspec(naked) sub_585AB0()
{
	__asm pushad
	dprintf("sub_585AB0 Called!\n");
	__asm popad

	__asm
	{
	/*00585AB0*/	push 0xFFFFFFFF
	/*00585AB2*/	push 0x958AFE		/*push <cm0102.sub_958AFE>*/
	/*00585AB7*/	mov eax,dword ptr fs:[0x0]
	/*00585ABD*/	push eax
	/*00585ABE*/	mov dword ptr fs:[0x0],esp
	/*00585AC5*/	sub esp,0x43C
	/*00585ACB*/	push ebx
	/*00585ACC*/	push ebp
	/*00585ACD*/	push esi
	/*00585ACE*/	push edi
	/*00585ACF*/	mov ebp,ecx
	/*00585AD1*/	push 0x7
	/*00585AD3*/	push 0x10
	/*00585AD5*/	mov dword ptr ss:[esp+0x44],ebp
	/*00585AD9*/	mov byte ptr ss:[esp+0x38],0x4
	/*00585ADE*/	mov byte ptr ss:[esp+0x39],0x1
	/*00585AE3*/	mov byte ptr ss:[esp+0x3A],0x2
	/*00585AE8*/	mov byte ptr ss:[esp+0x3B],0x0
	/*00585AED*/	mov byte ptr ss:[esp+0x40],0x2
	/*00585AF2*/	mov byte ptr ss:[esp+0x41],0x0
	/*00585AF7*/	mov byte ptr ss:[esp+0x42],0x0
	/*00585AFC*/	mov byte ptr ss:[esp+0x43],0x0
	/*00585B01*/	call sub_945501		/*call <cm0102.sub_945501>*/
	/*00585B06*/	add esp,0x8
	/*00585B09*/	mov dword ptr ss:[esp+0x18],eax
	/*00585B0D*/	test eax,eax
	/*00585B0F*/	jne _00585B45
	/*00585B11*/	lea eax,dword ptr ss:[esp+0x14C]
	/*00585B18*/	lea ecx,dword ptr ss:[esp+0x4C]
	/*00585B1C*/	push eax
	/*00585B1D*/	push ecx
	/*00585B1E*/	push 0x0
	/*00585B20*/	push 0x0
	/*00585B22*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00585B27*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00585B2C*/	add esp,0x14
	/*00585B2F*/	lea edx,dword ptr ss:[esp+0x14C]
	/*00585B36*/	lea eax,dword ptr ss:[esp+0x4C]
	/*00585B3A*/	push 0x61C
	/*00585B3F*/	push edx
	/*00585B40*/	jmp _00586217
_00585B45:
	/*00585B45*/	mov esi,dword ptr ss:[esp+0x18]
	/*00585B49*/	xor bl,bl
	/*00585B4B*/	xor edi,edi
_00585B4D:
	/*00585B4D*/	mov ecx,dword ptr ss:[ebp+0xC]
	/*00585B50*/	push 0x0
	/*00585B52*/	mov ecx,dword ptr ds:[edi+ecx]
	/*00585B55*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*00585B5A*/	mov edx,dword ptr ds:[eax]
	/*00585B5C*/	push 0x1
	/*00585B5E*/	mov dword ptr ds:[esi],edx
	/*00585B60*/	mov byte ptr ds:[esi+0x6],0x0
	/*00585B64*/	mov byte ptr ds:[esi+0x5],bl
	/*00585B67*/	mov byte ptr ds:[esi+0x4],0x0
	/*00585B6B*/	mov eax,dword ptr ss:[ebp+0xC]
	/*00585B6E*/	add esi,0x7
	/*00585B71*/	mov ecx,dword ptr ds:[edi+eax]
	/*00585B74*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*00585B79*/	mov ecx,dword ptr ds:[eax]
	/*00585B7B*/	add edi,0x4
	/*00585B7E*/	mov dword ptr ds:[esi],ecx
	/*00585B80*/	mov byte ptr ds:[esi+0x6],0x1
	/*00585B84*/	mov byte ptr ds:[esi+0x5],bl
	/*00585B87*/	mov byte ptr ds:[esi+0x4],0x0
	/*00585B8B*/	add esi,0x7
	/*00585B8E*/	inc bl
	/*00585B90*/	cmp bl,0x8
	/*00585B93*/	jl _00585B4D
	/*00585B95*/	mov ecx,dword ptr ss:[esp+0x18]
	/*00585B99*/	mov esi,0x10
_00585B9E:
	/*00585B9E*/	mov eax,dword ptr ss:[esp+0x18]
	/*00585BA2*/	mov edx,0x10
_00585BA7:
	/*00585BA7*/	mov edi,dword ptr ds:[ecx]
	/*00585BA9*/	mov ebx,dword ptr ds:[eax]
	/*00585BAB*/	mov edi,dword ptr ds:[edi+0x53]
	/*00585BAE*/	cmp edi,dword ptr ds:[ebx+0x53]
	/*00585BB1*/	jne _00585BB6
	/*00585BB3*/	inc byte ptr ds:[ecx+0x4]
_00585BB6:
	/*00585BB6*/	add eax,0x7
	/*00585BB9*/	dec edx
	/*00585BBA*/	jne _00585BA7
	/*00585BBC*/	add ecx,0x7
	/*00585BBF*/	dec esi
	/*00585BC0*/	jne _00585B9E
	/*00585BC2*/	mov esi,dword ptr ss:[esp+0x18]
	/*00585BC6*/	push 0x5871E0		/*push <cm0102.sub_5871E0>*/
	/*00585BCB*/	push 0x7
	/*00585BCD*/	push 0x10
	/*00585BCF*/	push esi
	/*00585BD0*/	call cm0102_qsort		/*call <cm0102.cm0102_qsort>*/
	/*00585BD5*/	add esp,0x10
	/*00585BD8*/	mov ebx,0x10
_00585BDD:
	/*00585BDD*/	mov edx,dword ptr ds:[esi]
	/*00585BDF*/	mov ecx,dword ptr ds:[0xAE28F0]		// ????
	/*00585BE5*/	movsx eax,byte ptr ss:[ebp+0x50]
	/*00585BE9*/	push edx
	/*00585BEA*/	mov edx,dword ptr ds:[ecx]
	/*00585BEC*/	mov ecx,dword ptr ds:[edx+eax*0x4]
	/*00585BEF*/	call sub_7E9180		/*call <cm0102.sub_7E9180>*/
	/*00585BF4*/	add esi,0x7
	/*00585BF7*/	dec ebx
	/*00585BF8*/	jne _00585BDD
	/*00585BFA*/	push 0x7
	/*00585BFC*/	push 0x10
	/*00585BFE*/	call sub_945501		/*call <cm0102.sub_945501>*/
	/*00585C03*/	mov edi,eax
	/*00585C05*/	xor esi,esi
	/*00585C07*/	add esp,0x8
	/*00585C0A*/	cmp edi,esi
	/*00585C0C*/	mov dword ptr ss:[esp+0x24],edi
	/*00585C10*/	jne _00585C42
	/*00585C12*/	lea eax,dword ptr ss:[esp+0x4C]
	/*00585C16*/	lea ecx,dword ptr ss:[esp+0x14C]
	/*00585C1D*/	push eax
	/*00585C1E*/	push ecx
	/*00585C1F*/	push esi
	/*00585C20*/	push esi
	/*00585C21*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00585C26*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00585C2B*/	add esp,0x14
	/*00585C2E*/	lea edx,dword ptr ss:[esp+0x4C]
	/*00585C32*/	lea eax,dword ptr ss:[esp+0x14C]
	/*00585C39*/	push 0x649
	/*00585C3E*/	push edx
	/*00585C3F*/	push eax
	/*00585C40*/	jmp _00585C86
_00585C42:
	/*00585C42*/	push 0x7
	/*00585C44*/	push 0x10
	/*00585C46*/	call sub_945501		/*call <cm0102.sub_945501>*/
	/*00585C4B*/	mov ebp,eax
	/*00585C4D*/	add esp,0x8
	/*00585C50*/	cmp ebp,esi
	/*00585C52*/	mov dword ptr ss:[esp+0x40],ebp
	/*00585C56*/	jne _00585CB9
	/*00585C58*/	lea ecx,dword ptr ss:[esp+0x4C]
	/*00585C5C*/	lea edx,dword ptr ss:[esp+0x14C]
	/*00585C63*/	push ecx
	/*00585C64*/	push edx
	/*00585C65*/	push esi
	/*00585C66*/	push esi
	/*00585C67*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00585C6C*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00585C71*/	add esp,0x14
	/*00585C74*/	lea eax,dword ptr ss:[esp+0x4C]
	/*00585C78*/	lea ecx,dword ptr ss:[esp+0x14C]
	/*00585C7F*/	push 0x651
	/*00585C84*/	push eax
	/*00585C85*/	push ecx
_00585C86:
	/*00585C86*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*00585C8B*/	push eax
	/*00585C8C*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*00585C91*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00585C96*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*00585C9B*/	push esi
	/*00585C9C*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00585CA1*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*00585CA6*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*00585CAB*/	add esp,0x24
	/*00585CAE*/	mov dword ptr ds:[0xB67A34],esi
	/*00585CB4*/	jmp _00586314
_00585CB9:
	/*00585CB9*/	mov esi,dword ptr ss:[esp+0x18]
	/*00585CBD*/	mov dword ptr ss:[esp+0x1C],0x0
	/*00585CC5*/	xor bl,bl
_00585CC7:
	/*00585CC7*/	cmp dword ptr ds:[esi],0x0
	/*00585CCA*/	je _00585DAA
	/*00585CD0*/	mov al,byte ptr ds:[esi+0x6]
	/*00585CD3*/	test al,al
	/*00585CD5*/	movsx ecx,bl
	/*00585CD8*/	jne _00585CE5
	/*00585CDA*/	lea edx,dword ptr ds:[ecx*0x8]
	/*00585CE1*/	sub edx,ecx
	/*00585CE3*/	jmp _00585CF1
_00585CE5:
	/*00585CE5*/	lea eax,dword ptr ds:[ecx+0x1]
	/*00585CE8*/	lea edx,dword ptr ds:[eax*0x8]
	/*00585CEF*/	sub edx,eax
_00585CF1:
	/*00585CF1*/	mov eax,esi
	/*00585CF3*/	add edx,edi
	/*00585CF5*/	mov edi,dword ptr ds:[eax]
	/*00585CF7*/	mov dword ptr ds:[edx],edi
	/*00585CF9*/	mov di,word ptr ds:[eax+0x4]
	/*00585CFD*/	mov word ptr ds:[edx+0x4],di
	/*00585D01*/	mov edi,dword ptr ss:[esp+0x18]
	/*00585D05*/	mov al,byte ptr ds:[eax+0x6]
	/*00585D08*/	mov byte ptr ds:[edx+0x6],al
	/*00585D0B*/	mov dword ptr ds:[esi],0x0
	/*00585D11*/	xor al,al
_00585D13:
	/*00585D13*/	movsx edx,al
	/*00585D16*/	cmp dword ptr ss:[esp+0x1C],edx
	/*00585D1A*/	je _00585D32
	/*00585D1C*/	lea ebp,dword ptr ds:[edx*0x8]
	/*00585D23*/	sub ebp,edx
	/*00585D25*/	mov dl,byte ptr ds:[esi+0x5]
	/*00585D28*/	cmp dl,byte ptr ds:[edi+ebp+0x5]
	/*00585D2C*/	je _00585D3A
	/*00585D2E*/	mov ebp,dword ptr ss:[esp+0x40]
_00585D32:
	/*00585D32*/	inc al
	/*00585D34*/	cmp al,0x10
	/*00585D36*/	jl _00585D13
	/*00585D38*/	jmp _00585DA6
_00585D3A:
	/*00585D3A*/	mov ebp,dword ptr ss:[esp+0x24]
	/*00585D3E*/	lea edx,dword ptr ds:[ecx*0x8]
	/*00585D45*/	sub edx,ecx
	/*00585D47*/	add edx,ebp
	/*00585D49*/	movsx eax,al
	/*00585D4C*/	cmp dword ptr ds:[edx],0x0
	/*00585D4F*/	je _00585D79
	/*00585D51*/	lea edx,dword ptr ds:[eax*0x8]
	/*00585D58*/	sub edx,eax
	/*00585D5A*/	inc ecx
	/*00585D5B*/	lea eax,dword ptr ds:[edx+edi]
	/*00585D5E*/	lea edx,dword ptr ds:[ecx*0x8]
	/*00585D65*/	sub edx,ecx
	/*00585D67*/	mov ecx,eax
	/*00585D69*/	add edx,ebp
	/*00585D6B*/	mov edi,dword ptr ds:[ecx]
	/*00585D6D*/	mov dword ptr ds:[edx],edi
	/*00585D6F*/	mov di,word ptr ds:[ecx+0x4]
	/*00585D73*/	mov word ptr ds:[edx+0x4],di
	/*00585D77*/	jmp _00585D93
_00585D79:
	/*00585D79*/	lea ecx,dword ptr ds:[eax*0x8]
	/*00585D80*/	sub ecx,eax
	/*00585D82*/	lea eax,dword ptr ds:[ecx+edi]
	/*00585D85*/	mov ecx,eax
	/*00585D87*/	mov edi,dword ptr ds:[ecx]
	/*00585D89*/	mov dword ptr ds:[edx],edi
	/*00585D8B*/	mov di,word ptr ds:[ecx+0x4]
	/*00585D8F*/	mov word ptr ds:[edx+0x4],di
_00585D93:
	/*00585D93*/	mov cl,byte ptr ds:[ecx+0x6]
	/*00585D96*/	mov ebp,dword ptr ss:[esp+0x40]
	/*00585D9A*/	mov byte ptr ds:[edx+0x6],cl
	/*00585D9D*/	add bl,0x2
	/*00585DA0*/	mov dword ptr ds:[eax],0x0
_00585DA6:
	/*00585DA6*/	mov edi,dword ptr ss:[esp+0x24]
_00585DAA:
	/*00585DAA*/	mov eax,dword ptr ss:[esp+0x1C]
	/*00585DAE*/	add esi,0x7
	/*00585DB1*/	inc eax
	/*00585DB2*/	cmp eax,0x10
	/*00585DB5*/	mov dword ptr ss:[esp+0x1C],eax
	/*00585DB9*/	jl _00585CC7
	/*00585DBF*/	xor eax,eax
_00585DC1:
	/*00585DC1*/	mov byte ptr ss:[esp+eax+0x34],al
	/*00585DC5*/	inc eax
	/*00585DC6*/	cmp eax,0x4
	/*00585DC9*/	jl _00585DC1
	/*00585DCB*/	mov dword ptr ss:[esp+0x20],edi
	/*00585DCF*/	mov dword ptr ss:[esp+0x28],0x10
_00585DD7:
	/*00585DD7*/	mov edx,dword ptr ss:[esp+0x20]
	/*00585DDB*/	mov byte ptr ss:[esp+0x15],0x4
	/*00585DE0*/	mov byte ptr ss:[esp+0x16],0xFF
	/*00585DE5*/	mov esi,0x5
	/*00585DEA*/	mov bl,byte ptr ds:[edx+0x6]
	/*00585DED*/	neg bl
	/*00585DEF*/	sbb bl,bl
	/*00585DF1*/	and ebx,0x2
	/*00585DF4*/	mov al,bl
	/*00585DF6*/	mov byte ptr ss:[esp+0x13],bl
	/*00585DFA*/	add al,0x2
	/*00585DFC*/	mov byte ptr ss:[esp+0x17],al
_00585E00:
	/*00585E00*/	push 0x4
	/*00585E02*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*00585E07*/	push 0x4
	/*00585E09*/	mov byte ptr ss:[esp+0x1C],al
	/*00585E0D*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*00585E12*/	movsx ecx,byte ptr ss:[esp+0x1C]
	/*00585E17*/	mov dl,byte ptr ss:[esp+ecx+0x3C]
	/*00585E1B*/	add esp,0x8
	/*00585E1E*/	movsx eax,al
	/*00585E21*/	lea ecx,dword ptr ss:[esp+ecx+0x34]
	/*00585E25*/	mov byte ptr ss:[esp+0x14],dl
	/*00585E29*/	mov dl,byte ptr ss:[esp+eax+0x34]
	/*00585E2D*/	lea eax,dword ptr ss:[esp+eax+0x34]
	/*00585E31*/	mov byte ptr ds:[ecx],dl
	/*00585E33*/	mov cl,byte ptr ss:[esp+0x14]
	/*00585E37*/	dec esi
	/*00585E38*/	mov byte ptr ds:[eax],cl
	/*00585E3A*/	jne _00585E00
	/*00585E3C*/	lea edx,dword ptr ss:[esp+0x34]
	/*00585E40*/	mov dword ptr ss:[esp+0x2C],0x4
	/*00585E48*/	mov dword ptr ss:[esp+0x1C],edx
_00585E4C:
	/*00585E4C*/	mov eax,dword ptr ss:[esp+0x1C]
	/*00585E50*/	xor dl,dl
	/*00585E52*/	xor edi,edi
	/*00585E54*/	mov byte ptr ss:[esp+0x14],dl
	/*00585E58*/	mov al,byte ptr ds:[eax]
	/*00585E5A*/	movsx ecx,al
	/*00585E5D*/	shl ecx,0x2
_00585E60:
	/*00585E60*/	movsx eax,dl
	/*00585E63*/	add eax,ecx
	/*00585E65*/	lea esi,dword ptr ds:[eax*0x8]
	/*00585E6C*/	sub esi,eax
	/*00585E6E*/	lea eax,dword ptr ds:[esi+ebp]
	/*00585E71*/	mov esi,dword ptr ds:[esi+ebp]
	/*00585E74*/	test esi,esi
	/*00585E76*/	je _00585E9E
	/*00585E78*/	mov bl,byte ptr ss:[esp+0x14]
	/*00585E7C*/	mov al,byte ptr ds:[eax+0x5]
	/*00585E7F*/	inc bl
	/*00585E81*/	mov byte ptr ss:[esp+0x14],bl
	/*00585E85*/	mov ebx,dword ptr ss:[esp+0x20]
	/*00585E89*/	cmp al,byte ptr ds:[ebx+0x5]
	/*00585E8C*/	je _00585EA7
	/*00585E8E*/	mov esi,dword ptr ds:[esi+0x53]
	/*00585E91*/	mov eax,ebx
	/*00585E93*/	mov eax,dword ptr ds:[eax]
	/*00585E95*/	cmp esi,dword ptr ds:[eax+0x53]
	/*00585E98*/	je _00585EA7
	/*00585E9A*/	mov bl,byte ptr ss:[esp+0x13]
_00585E9E:
	/*00585E9E*/	inc dl
	/*00585EA0*/	cmp dl,0x4
	/*00585EA3*/	jl _00585E60
	/*00585EA5*/	jmp _00585EB0
_00585EA7:
	/*00585EA7*/	mov bl,byte ptr ss:[esp+0x13]
	/*00585EAB*/	mov edi,0x1
_00585EB0:
	/*00585EB0*/	movsx eax,bl
	/*00585EB3*/	add eax,ecx
	/*00585EB5*/	lea edx,dword ptr ds:[eax*0x8]
	/*00585EBC*/	sub edx,eax
	/*00585EBE*/	cmp dword ptr ds:[edx+ebp],0x0
	/*00585EC2*/	je _00585EDC
	/*00585EC4*/	movsx eax,byte ptr ss:[esp+0x17]
	/*00585EC9*/	add eax,ecx
	/*00585ECB*/	lea ecx,dword ptr ds:[eax*0x8]
	/*00585ED2*/	sub ecx,eax
	/*00585ED4*/	mov eax,dword ptr ds:[ecx+ebp-0x7]
	/*00585ED8*/	test eax,eax
	/*00585EDA*/	jne _00585EFA
_00585EDC:
	/*00585EDC*/	test edi,edi
	/*00585EDE*/	jne _00585EFA
	/*00585EE0*/	mov al,byte ptr ss:[esp+0x14]
	/*00585EE4*/	mov cl,byte ptr ss:[esp+0x15]
	/*00585EE8*/	cmp al,cl
	/*00585EEA*/	jge _00585EFA
	/*00585EEC*/	mov edx,dword ptr ss:[esp+0x1C]
	/*00585EF0*/	mov byte ptr ss:[esp+0x15],al
	/*00585EF4*/	mov al,byte ptr ds:[edx]
	/*00585EF6*/	mov byte ptr ss:[esp+0x16],al
_00585EFA:
	/*00585EFA*/	mov ecx,dword ptr ss:[esp+0x1C]
	/*00585EFE*/	mov eax,dword ptr ss:[esp+0x2C]
	/*00585F02*/	inc ecx
	/*00585F03*/	dec eax
	/*00585F04*/	mov dword ptr ss:[esp+0x1C],ecx
	/*00585F08*/	mov dword ptr ss:[esp+0x2C],eax
	/*00585F0C*/	jne _00585E4C
	/*00585F12*/	mov al,byte ptr ss:[esp+0x16]
	/*00585F16*/	cmp al,0xFF
	/*00585F18*/	je _00585F84
	/*00585F1A*/	movsx ecx,al
	/*00585F1D*/	movsx eax,bl
	/*00585F20*/	shl ecx,0x2
	/*00585F23*/	add eax,ecx
	/*00585F25*/	lea edx,dword ptr ds:[eax*0x8]
	/*00585F2C*/	sub edx,eax
	/*00585F2E*/	lea eax,dword ptr ds:[edx+ebp]
	/*00585F31*/	mov edx,dword ptr ds:[edx+ebp]
	/*00585F34*/	test edx,edx
	/*00585F36*/	jne _00585F52
	/*00585F38*/	mov ecx,dword ptr ss:[esp+0x20]
	/*00585F3C*/	mov edx,ecx
	/*00585F3E*/	mov esi,dword ptr ds:[edx]
	/*00585F40*/	mov dword ptr ds:[eax],esi
	/*00585F42*/	mov si,word ptr ds:[edx+0x4]
	/*00585F46*/	mov word ptr ds:[eax+0x4],si
	/*00585F4A*/	mov dl,byte ptr ds:[edx+0x6]
	/*00585F4D*/	mov byte ptr ds:[eax+0x6],dl
	/*00585F50*/	jmp _00585F7E
_00585F52:
	/*00585F52*/	movsx eax,byte ptr ss:[esp+0x17]
	/*00585F57*/	add eax,ecx
	/*00585F59*/	lea ecx,dword ptr ds:[eax*0x8]
	/*00585F60*/	sub ecx,eax
	/*00585F62*/	lea edx,dword ptr ds:[ecx+ebp-0x7]
	/*00585F66*/	mov ecx,dword ptr ss:[esp+0x20]
	/*00585F6A*/	mov eax,ecx
	/*00585F6C*/	mov esi,dword ptr ds:[eax]
	/*00585F6E*/	mov dword ptr ds:[edx],esi
	/*00585F70*/	mov si,word ptr ds:[eax+0x4]
	/*00585F74*/	mov word ptr ds:[edx+0x4],si
	/*00585F78*/	mov al,byte ptr ds:[eax+0x6]
	/*00585F7B*/	mov byte ptr ds:[edx+0x6],al
_00585F7E:
	/*00585F7E*/	mov dword ptr ds:[ecx],0x0
_00585F84:
	/*00585F84*/	mov ecx,dword ptr ss:[esp+0x20]
	/*00585F88*/	mov eax,dword ptr ss:[esp+0x28]
	/*00585F8C*/	add ecx,0x7
	/*00585F8F*/	dec eax
	/*00585F90*/	mov dword ptr ss:[esp+0x20],ecx
	/*00585F94*/	mov dword ptr ss:[esp+0x28],eax
	/*00585F98*/	jne _00585DD7
	/*00585F9E*/	mov edx,dword ptr ss:[esp+0x24]
	/*00585FA2*/	mov bl,byte ptr ss:[esp+0x45C]
	/*00585FA9*/	xor esi,esi
_00585FAB:
	/*00585FAB*/	cmp dword ptr ds:[edx],0x0
	/*00585FAE*/	je _00585FF8
	/*00585FB0*/	cmp bl,0x14
	/*00585FB3*/	jl _00586124
	/*00585FB9*/	xor cl,cl
_00585FBB:
	/*00585FBB*/	movsx eax,cl
	/*00585FBE*/	lea edi,dword ptr ds:[eax*0x8]
	/*00585FC5*/	sub edi,eax
	/*00585FC7*/	cmp dword ptr ds:[edi+ebp],0x0
	/*00585FCB*/	je _00585FD6
	/*00585FCD*/	inc cl
	/*00585FCF*/	cmp cl,0x10
	/*00585FD2*/	jl _00585FBB
	/*00585FD4*/	jmp _00585FF8
_00585FD6:
	/*00585FD6*/	movsx eax,cl
	/*00585FD9*/	lea ecx,dword ptr ds:[eax*0x8]
	/*00585FE0*/	sub ecx,eax
	/*00585FE2*/	mov eax,edx
	/*00585FE4*/	add ecx,ebp
	/*00585FE6*/	mov edi,dword ptr ds:[eax]
	/*00585FE8*/	mov dword ptr ds:[ecx],edi
	/*00585FEA*/	mov di,word ptr ds:[eax+0x4]
	/*00585FEE*/	mov word ptr ds:[ecx+0x4],di
	/*00585FF2*/	mov al,byte ptr ds:[eax+0x6]
	/*00585FF5*/	mov byte ptr ds:[ecx+0x6],al
_00585FF8:
	/*00585FF8*/	inc esi
	/*00585FF9*/	add edx,0x7
	/*00585FFC*/	cmp esi,0x10
	/*00585FFF*/	jl _00585FAB
	/*00586001*/	push 0x40
	/*00586003*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*00586008*/	mov dword ptr ss:[esp+0x30],eax
	/*0058600C*/	mov ecx,eax
	/*0058600E*/	add esp,0x4
	/*00586011*/	mov eax,ebp
	/*00586013*/	mov edx,0x10
_00586018:
	/*00586018*/	mov esi,dword ptr ds:[eax]
	/*0058601A*/	add eax,0x7
	/*0058601D*/	mov dword ptr ds:[ecx],esi
	/*0058601F*/	add ecx,0x4
	/*00586022*/	dec edx
	/*00586023*/	jne _00586018
	/*00586025*/	mov ebp,dword ptr ss:[esp+0x3C]
	/*00586029*/	mov byte ptr ss:[esp+0x13],0x0
_0058602E:
	/*0058602E*/	movsx eax,byte ptr ss:[esp+0x13]
	/*00586033*/	mov edx,dword ptr ss:[esp+0x40]
	/*00586037*/	mov dword ptr ss:[esp+0x28],eax
	/*0058603B*/	lea ecx,dword ptr ds:[eax*0x8]
	/*00586042*/	mov ebx,0x4
	/*00586047*/	sub ecx,eax
	/*00586049*/	lea edi,dword ptr ds:[edx+ecx*0x4]
_0058604C:
	/*0058604C*/	mov esi,dword ptr ds:[edi]
	/*0058604E*/	mov ecx,dword ptr ds:[0xDE1F58]		//  contains an address of the UEFA Country Rankings
	/*00586054*/	push 0x1
	/*00586056*/	mov eax,dword ptr ds:[esi+0x53]
	/*00586059*/	push eax
	/*0058605A*/	call sub_9058B0		/*call <cm0102.sub_9058B0>*/
	/*0058605F*/	mov ecx,dword ptr ds:[0xAE2A38]			// ???
	/*00586065*/	push 0x124F80
	/*0058606A*/	push esi
	/*0058606B*/	call sub_5A0590		/*call <cm0102.sub_5A0590>*/
	/*00586070*/	mov ecx,eax
	/*00586072*/	call sub_5999A0		/*call <cm0102.sub_5999A0>*/
	/*00586077*/	push 0xFFFFFFFE
	/*00586079*/	push 0x0
	/*0058607B*/	push 0x44A
	/*00586080*/	push 0xFFFFFFFF
	/*00586082*/	push 0x0
	/*00586084*/	push 0x124F80
	/*00586089*/	push esi
	/*0058608A*/	mov ecx,ebp
	/*0058608C*/	call sub_48E3E0		/*call <cm0102.sub_48E3E0>*/
	/*00586091*/	add edi,0x7
	/*00586094*/	dec ebx
	/*00586095*/	jne _0058604C
	/*00586097*/	mov bl,byte ptr ss:[esp+0x13]
	/*0058609B*/	mov edx,dword ptr ss:[ebp]
	/*0058609E*/	lea eax,dword ptr ss:[esp+0x44]
	/*005860A2*/	push 0x0
	/*005860A4*/	lea ecx,dword ptr ss:[esp+0x4C]
	/*005860A8*/	add bl,0x8
	/*005860AB*/	push eax
	/*005860AC*/	push ecx
	/*005860AD*/	push ebx
	/*005860AE*/	mov ecx,ebp
	/*005860B0*/	call dword ptr ds:[edx+0x3C]	
	/*005860B3*/	push 0xEE
	/*005860B8*/	mov esi,eax
	/*005860BA*/	call cm0102_new		/*call <cm0102.cm0102_new>*/
	/*005860BF*/	add esp,0x4
	/*005860C2*/	mov dword ptr ss:[esp+0x34],eax
	/*005860C6*/	test eax,eax
	/*005860C8*/	mov dword ptr ss:[esp+0x454],0x0
	/*005860D3*/	je _00586152
	/*005860D5*/	mov edx,dword ptr ss:[esp+0x44]
	/*005860D9*/	mov cx,word ptr ss:[ebp+0x40]
	/*005860DD*/	push 0x2
	/*005860DF*/	push 0x0
	/*005860E1*/	push 0xFFFFFFFF
	/*005860E3*/	push 0x8
	/*005860E5*/	push 0x0
	/*005860E7*/	push 0x2
	/*005860E9*/	push 0xF
	/*005860EB*/	push edx
	/*005860EC*/	push ebx
	/*005860ED*/	push ecx
	/*005860EE*/	lea edx,dword ptr ss:[esp+0x60]
	/*005860F2*/	lea ecx,dword ptr ss:[esp+0x58]
	/*005860F6*/	push edx
	/*005860F7*/	mov edx,dword ptr ss:[esp+0x74]
	/*005860FB*/	mov ebx,dword ptr ss:[esp+0x58]
	/*005860FF*/	push ecx
	/*00586100*/	mov ecx,dword ptr ss:[ebp+0x4]
	/*00586103*/	push 0x8
	/*00586105*/	push 0x1
	/*00586107*/	push 0x3
	/*00586109*/	push edx
	/*0058610A*/	mov edx,dword ptr ss:[esp+0x68]
	/*0058610E*/	shl edx,0x4
	/*00586111*/	push esi
	/*00586112*/	push ecx
	/*00586113*/	add edx,ebx
	/*00586115*/	push 0x2
	/*00586117*/	push edx
	/*00586118*/	push 0x4
	/*0058611A*/	push ebp
	/*0058611B*/	mov ecx,eax
	/*0058611D*/	call cm0102_create_league_68B100		/*call <cm0102.cm0102_create_league_68B100>*/
	/*00586122*/	jmp _00586154
_00586124:
	/*00586124*/	push ebp
	/*00586125*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*0058612A*/	mov ecx,dword ptr ss:[esp+0x28]
	/*0058612E*/	push ecx
	/*0058612F*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00586134*/	mov edx,dword ptr ss:[esp+0x20]
	/*00586138*/	push edx
	/*00586139*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*0058613E*/	mov ecx,dword ptr ss:[esp+0x48]
	/*00586142*/	add esp,0xC
	/*00586145*/	inc bl
	/*00586147*/	push ebx
	/*00586148*/	call sub_585AB0		/*call <cm0102.sub_585AB0>*/
	/*0058614D*/	jmp _00586314
_00586152:
	/*00586152*/	xor eax,eax
_00586154:
	/*00586154*/	mov ecx,dword ptr ss:[esp+0x28]
	/*00586158*/	mov edx,dword ptr ss:[ebp+0xC]
	/*0058615B*/	mov dword ptr ss:[esp+0x454],0xFFFFFFFF
	/*00586166*/	lea edi,dword ptr ds:[ecx+0x8]
	/*00586169*/	mov dword ptr ds:[edx+edi*0x4],eax
	/*0058616C*/	mov eax,dword ptr ss:[ebp+0xC]
	/*0058616F*/	cmp dword ptr ds:[eax+edi*0x4],0x0
	/*00586173*/	je _00586250
	/*00586179*/	push esi
	/*0058617A*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*0058617F*/	mov ecx,dword ptr ss:[ebp+0xC]
	/*00586182*/	mov dword ptr ss:[ebp+0x30],edi
	/*00586185*/	add esp,0x4
	/*00586188*/	mov ecx,dword ptr ds:[ecx+edi*0x4]
	/*0058618B*/	call sub_684230		/*call <cm0102.sub_684230>*/
	/*00586190*/	mov al,byte ptr ss:[esp+0x13]
	/*00586194*/	inc al
	/*00586196*/	cmp al,0x4
	/*00586198*/	mov byte ptr ss:[esp+0x13],al
	/*0058619C*/	jl _0058602E
	/*005861A2*/	mov eax,dword ptr ss:[esp+0x18]
	/*005861A6*/	push eax
	/*005861A7*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*005861AC*/	mov ecx,dword ptr ss:[esp+0x44]
	/*005861B0*/	push ecx
	/*005861B1*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*005861B6*/	mov edx,dword ptr ss:[esp+0x2C]
	/*005861BA*/	push edx
	/*005861BB*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*005861C0*/	mov eax,dword ptr ss:[esp+0x38]
	/*005861C4*/	push eax
	/*005861C5*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*005861CA*/	mov ecx,dword ptr ds:[0xADADFC]
	/*005861D0*/	mov edx,dword ptr ds:[0x9CF6F0]		/* UEFA Cup */
	/*005861D6*/	add esp,0x10
	/*005861D9*/	mov edi,dword ptr ds:[ecx+edx*0x4]
	/*005861DC*/	test edi,edi
	/*005861DE*/	jne _00586282
	/*005861E4*/	lea eax,dword ptr ss:[esp+0x24C]
	/*005861EB*/	lea ecx,dword ptr ss:[esp+0x34C]
	/*005861F2*/	push eax
	/*005861F3*/	push ecx
	/*005861F4*/	push edi
	/*005861F5*/	push edi
	/*005861F6*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005861FB*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00586200*/	add esp,0x14
	/*00586203*/	lea edx,dword ptr ss:[esp+0x24C]
	/*0058620A*/	lea eax,dword ptr ss:[esp+0x34C]
	/*00586211*/	push 0x729
	/*00586216*/	push edx
_00586217:
	/*00586217*/	push eax
_00586218:
	/*00586218*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*0058621D*/	push eax
	/*0058621E*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*00586223*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00586228*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*0058622D*/	push 0x0
	/*0058622F*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00586234*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*00586239*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*0058623E*/	add esp,0x24
	/*00586241*/	mov dword ptr ds:[0xB67A34],0x0
	/*0058624B*/	jmp _00586314
_00586250:
	/*00586250*/	lea edx,dword ptr ss:[esp+0x4C]
	/*00586254*/	lea eax,dword ptr ss:[esp+0x14C]
	/*0058625B*/	push edx
	/*0058625C*/	push eax
	/*0058625D*/	push 0x0
	/*0058625F*/	push 0x0
	/*00586261*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00586266*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*0058626B*/	add esp,0x14
	/*0058626E*/	lea ecx,dword ptr ss:[esp+0x4C]
	/*00586272*/	lea edx,dword ptr ss:[esp+0x14C]
	/*00586279*/	push 0x715
	/*0058627E*/	push ecx
	/*0058627F*/	push edx
	/*00586280*/	jmp _00586218
_00586282:
	/*00586282*/	movsx eax,word ptr ds:[edi+0x3E]
	/*00586286*/	dec eax
	/*00586287*/	xor ebp,ebp
	/*00586289*/	lea ebx,dword ptr ds:[eax+eax*0x2]
	/*0058628C*/	shl ebx,0x1
_0058628E:
	/*0058628E*/	mov ecx,dword ptr ss:[esp+0x3C]
	/*00586292*/	mov eax,dword ptr ds:[edi+0xA7]
	/*00586298*/	mov esi,ebx
	/*0058629A*/	push 0x2
	/*0058629C*/	mov edx,dword ptr ds:[ecx+0xC]
	/*0058629F*/	add esi,eax
	/*005862A1*/	sub ebx,0x6
	/*005862A4*/	mov ecx,dword ptr ds:[edx+ebp]
	/*005862A7*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*005862AC*/	mov eax,dword ptr ds:[eax]
	/*005862AE*/	mov byte ptr ds:[esi+0x4],0x0
	/*005862B2*/	mov dword ptr ds:[esi],eax
	/*005862B4*/	mov byte ptr ds:[esi+0x5],0x0
	/*005862B8*/	movsx eax,word ptr ds:[edi+0x36]
	/*005862BC*/	mov edx,dword ptr ds:[edi+0x14]
	/*005862BF*/	push 0x3
	/*005862C1*/	lea ecx,dword ptr ds:[eax+eax*0x2]
	/*005862C4*/	mov eax,dword ptr ds:[esi]
	/*005862C6*/	mov dword ptr ds:[edx+ecx*0x2],eax
	/*005862C9*/	mov edx,dword ptr ds:[edi+0x14]
	/*005862CC*/	movsx eax,word ptr ds:[edi+0x36]
	/*005862D0*/	lea ecx,dword ptr ds:[eax+eax*0x2]
	/*005862D3*/	mov byte ptr ds:[edx+ecx*0x2+0x4],0x5
	/*005862D8*/	inc word ptr ds:[edi+0x36]
	/*005862DC*/	mov eax,dword ptr ds:[esi]
	/*005862DE*/	mov ecx,dword ptr ds:[0x9CF6F0]		/* UEFA Cup */
	/*005862E4*/	mov edx,dword ptr ss:[esp+0x40]
	/*005862E8*/	mov dword ptr ds:[eax+0x1DB],ecx
	/*005862EE*/	mov eax,dword ptr ds:[edx+0xC]
	/*005862F1*/	mov ecx,dword ptr ds:[eax+ebp]
	/*005862F4*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*005862F9*/	mov ecx,dword ptr ds:[eax]
	/*005862FB*/	add ebp,0x4
	/*005862FE*/	cmp ebp,0x20
	/*00586301*/	mov dword ptr ds:[ecx+0x1DB],0xFFFFFFFF
	/*0058630B*/	jl _0058628E
	/*0058630D*/	mov edx,dword ptr ds:[edi]
	/*0058630F*/	mov ecx,edi
	/*00586311*/	call dword ptr ds:[edx+0x5C]
_00586314:
	/*00586314*/	mov ecx,dword ptr ss:[esp+0x44C]
	/*0058631B*/	pop edi
	/*0058631C*/	pop esi
	/*0058631D*/	pop ebp
	/*0058631E*/	pop ebx
	/*0058631F*/	mov dword ptr fs:[0x0],ecx
	/*00586326*/	add esp,0x448
	/*0058632C*/	ret 0x4
	}
}

extern "C" void __declspec(naked) sub_586330()
{
	__asm pushad
	dprintf("sub_586330 Called!\n");
	__asm popad

	__asm
	{
	/*00586330*/	mov eax,dword ptr fs:[0x0]
	/*00586336*/	push 0xFFFFFFFF
	/*00586338*/	push 0x958B1E		/*push <cm0102.sub_958B1E>*/
	/*0058633D*/	push eax
	/*0058633E*/	mov dword ptr fs:[0x0],esp
	/*00586345*/	sub esp,0x410
	/*0058634B*/	push ebx
	/*0058634C*/	push ebp
	/*0058634D*/	push esi
	/*0058634E*/	push edi
	/*0058634F*/	push 0x4
	/*00586351*/	mov esi,ecx
	/*00586353*/	push 0x8
	/*00586355*/	call sub_945501		/*call <cm0102.sub_945501>*/
	/*0058635A*/	mov edi,eax
	/*0058635C*/	add esp,0x8
	/*0058635F*/	test edi,edi
	/*00586361*/	jne _00586396
	/*00586363*/	lea eax,dword ptr ss:[esp+0x20]
	/*00586367*/	lea ecx,dword ptr ss:[esp+0x220]
	/*0058636E*/	push eax
	/*0058636F*/	push ecx
	/*00586370*/	push edi
	/*00586371*/	push edi
	/*00586372*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00586377*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*0058637C*/	add esp,0x14
	/*0058637F*/	lea edx,dword ptr ss:[esp+0x20]
	/*00586383*/	lea eax,dword ptr ss:[esp+0x220]
	/*0058638A*/	push 0x762
	/*0058638F*/	push edx
	/*00586390*/	push eax
	/*00586391*/	jmp _005865BE
_00586396:
	/*00586396*/	push 0x4
	/*00586398*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*0058639D*/	add esp,0x4
	/*005863A0*/	mov byte ptr ss:[esp+0x11],al
	/*005863A4*/	mov byte ptr ss:[esp+0x13],al
_005863A8:
	/*005863A8*/	push 0x4
	/*005863AA*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*005863AF*/	mov bl,al
	/*005863B1*/	mov al,byte ptr ss:[esp+0x15]
	/*005863B5*/	add esp,0x4
	/*005863B8*/	cmp bl,al
	/*005863BA*/	je _005863A8
	/*005863BC*/	push 0x4
	/*005863BE*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*005863C3*/	add esp,0x4
	/*005863C6*/	mov byte ptr ss:[esp+0x12],al
_005863CA:
	/*005863CA*/	mov dl,byte ptr ss:[esp+0x12]
	/*005863CE*/	mov al,byte ptr ss:[esp+0x13]
	/*005863D2*/	cmp dl,al
	/*005863D4*/	je _005863DA
	/*005863D6*/	cmp dl,bl
	/*005863D8*/	jne _005863EA
_005863DA:
	/*005863DA*/	push 0x4
	/*005863DC*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*005863E1*/	add esp,0x4
	/*005863E4*/	mov byte ptr ss:[esp+0x12],al
	/*005863E8*/	jmp _005863CA
_005863EA:
	/*005863EA*/	mov cl,byte ptr ss:[esp+0x11]
	/*005863EE*/	cmp cl,al
	/*005863F0*/	je _005863FA
	/*005863F2*/	cmp cl,bl
	/*005863F4*/	je _005863FA
	/*005863F6*/	cmp cl,dl
	/*005863F8*/	jne _00586412
_005863FA:
	/*005863FA*/	push 0x4
	/*005863FC*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*00586401*/	mov dl,byte ptr ss:[esp+0x16]
	/*00586405*/	mov byte ptr ss:[esp+0x15],al
	/*00586409*/	mov al,byte ptr ss:[esp+0x17]
	/*0058640D*/	add esp,0x4
	/*00586410*/	jmp _005863EA
_00586412:
	/*00586412*/	mov edx,dword ptr ds:[esi+0xC]
	/*00586415*/	push 0x0
	/*00586417*/	movsx ecx,al
	/*0058641A*/	lea ebp,dword ptr ds:[ecx*0x4+0x20]
	/*00586421*/	mov ecx,dword ptr ds:[edx+ecx*0x4+0x20]
	/*00586425*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*0058642A*/	mov eax,dword ptr ds:[eax]
	/*0058642C*/	push 0x1
	/*0058642E*/	movsx ecx,bl
	/*00586431*/	mov dword ptr ds:[edi],eax
	/*00586433*/	mov edx,dword ptr ds:[esi+0xC]
	/*00586436*/	lea ebx,dword ptr ds:[ecx*0x4+0x20]
	/*0058643D*/	mov ecx,dword ptr ds:[ebx+edx]
	/*00586440*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*00586445*/	mov eax,dword ptr ds:[eax]
	/*00586447*/	push 0x1
	/*00586449*/	mov dword ptr ds:[edi+0x4],eax
	/*0058644C*/	mov ecx,dword ptr ds:[esi+0xC]
	/*0058644F*/	mov ecx,dword ptr ds:[ecx+ebp]
	/*00586452*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*00586457*/	mov edx,dword ptr ds:[eax]
	/*00586459*/	push 0x0
	/*0058645B*/	mov dword ptr ds:[edi+0x8],edx
	/*0058645E*/	mov eax,dword ptr ds:[esi+0xC]
	/*00586461*/	mov ecx,dword ptr ds:[ebx+eax]
	/*00586464*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*00586469*/	movsx edx,byte ptr ss:[esp+0x12]
	/*0058646E*/	mov ecx,dword ptr ds:[eax]
	/*00586470*/	push 0x0
	/*00586472*/	mov dword ptr ds:[edi+0xC],ecx
	/*00586475*/	mov eax,dword ptr ds:[esi+0xC]
	/*00586478*/	lea ebx,dword ptr ds:[edx*0x4+0x20]
	/*0058647F*/	mov ecx,dword ptr ds:[ebx+eax]
	/*00586482*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*00586487*/	movsx edx,byte ptr ss:[esp+0x11]
	/*0058648C*/	mov ecx,dword ptr ds:[eax]
	/*0058648E*/	push 0x1
	/*00586490*/	mov dword ptr ds:[edi+0x10],ecx
	/*00586493*/	mov eax,dword ptr ds:[esi+0xC]
	/*00586496*/	lea ebp,dword ptr ds:[edx*0x4+0x20]
	/*0058649D*/	mov ecx,dword ptr ds:[eax+ebp]
	/*005864A0*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*005864A5*/	mov ecx,dword ptr ds:[eax]
	/*005864A7*/	push 0x1
	/*005864A9*/	mov dword ptr ds:[edi+0x14],ecx
	/*005864AC*/	mov edx,dword ptr ds:[esi+0xC]
	/*005864AF*/	mov ecx,dword ptr ds:[ebx+edx]
	/*005864B2*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*005864B7*/	mov eax,dword ptr ds:[eax]
	/*005864B9*/	push 0x0
	/*005864BB*/	mov dword ptr ds:[edi+0x18],eax
	/*005864BE*/	mov ecx,dword ptr ds:[esi+0xC]
	/*005864C1*/	mov ecx,dword ptr ds:[ecx+ebp]
	/*005864C4*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*005864C9*/	mov edx,dword ptr ds:[eax]
	/*005864CB*/	mov ebp,edi
	/*005864CD*/	mov dword ptr ds:[edi+0x1C],edx
	/*005864D0*/	mov ebx,0x8
_005864D5:
	/*005864D5*/	mov eax,dword ptr ss:[ebp]
	/*005864D8*/	mov edx,dword ptr ds:[0xAE28F0]			// ???
	/*005864DE*/	movsx ecx,byte ptr ds:[esi+0x50]
	/*005864E2*/	push eax
	/*005864E3*/	mov eax,dword ptr ds:[edx]
	/*005864E5*/	mov ecx,dword ptr ds:[eax+ecx*0x4]
	/*005864E8*/	call sub_7E9180		/*call <cm0102.sub_7E9180>*/
	/*005864ED*/	add ebp,0x4
	/*005864F0*/	dec ebx
	/*005864F1*/	jne _005864D5
	/*005864F3*/	mov edx,dword ptr ds:[esi]
	/*005864F5*/	lea eax,dword ptr ss:[esp+0x18]
	/*005864F9*/	push 0x0
	/*005864FB*/	lea ecx,dword ptr ss:[esp+0x18]
	/*005864FF*/	push eax
	/*00586500*/	push ecx
	/*00586501*/	push 0xC
	/*00586503*/	mov ecx,esi
	/*00586505*/	call dword ptr ds:[edx+0x3C]
	/*00586508*/	push 0xB2
	/*0058650D*/	mov ebx,eax
	/*0058650F*/	call cm0102_new		/*call <cm0102.cm0102_new>*/
	/*00586514*/	add esp,0x4
	/*00586517*/	mov dword ptr ss:[esp+0x1C],eax
	/*0058651B*/	test eax,eax
	/*0058651D*/	mov dword ptr ss:[esp+0x428],0x0
	/*00586528*/	je _0058655D
	/*0058652A*/	mov edx,dword ptr ss:[esp+0x18]
	/*0058652E*/	mov cx,word ptr ds:[esi+0x40]
	/*00586532*/	push 0x0
	/*00586534*/	push 0x0
	/*00586536*/	push 0x0
	/*00586538*/	push 0x1
	/*0058653A*/	push 0x14
	/*0058653C*/	push edx
	/*0058653D*/	mov edx,dword ptr ds:[esi+0x4]
	/*00586540*/	push 0x2
	/*00586542*/	push 0xC
	/*00586544*/	push ecx
	/*00586545*/	mov ecx,dword ptr ss:[esp+0x38]
	/*00586549*/	push ebx
	/*0058654A*/	push edx
	/*0058654B*/	push ecx
	/*0058654C*/	mov ecx,0x8
	/*00586551*/	push edi
	/*00586552*/	push ecx
	/*00586553*/	push esi
	/*00586554*/	mov ecx,eax
	/*00586556*/	call sub_522E00		/*call <cm0102.sub_522E00>*/
	/*0058655B*/	jmp _0058655F
_0058655D:
	/*0058655D*/	xor eax,eax
_0058655F:
	/*0058655F*/	mov edx,dword ptr ds:[esi+0xC]
	/*00586562*/	or ebp,0xFFFFFFFF
	/*00586565*/	push edi
	/*00586566*/	mov dword ptr ss:[esp+0x42C],ebp
	/*0058656D*/	mov dword ptr ds:[edx+0x30],eax
	/*00586570*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00586575*/	push ebx
	/*00586576*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*0058657B*/	mov eax,dword ptr ds:[esi+0xC]
	/*0058657E*/	add esp,0x8
	/*00586581*/	mov ecx,dword ptr ds:[eax+0x30]
	/*00586584*/	test ecx,ecx
	/*00586586*/	jne _005865F3
	/*00586588*/	lea ecx,dword ptr ss:[esp+0x120]
	/*0058658F*/	lea edx,dword ptr ss:[esp+0x320]
	/*00586596*/	push ecx
	/*00586597*/	push edx
	/*00586598*/	push 0x0
	/*0058659A*/	push 0x0
	/*0058659C*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005865A1*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*005865A6*/	add esp,0x14
	/*005865A9*/	lea eax,dword ptr ss:[esp+0x120]
	/*005865B0*/	lea ecx,dword ptr ss:[esp+0x320]
	/*005865B7*/	push 0x78A
	/*005865BC*/	push eax
	/*005865BD*/	push ecx
_005865BE:
	/*005865BE*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*005865C3*/	push eax
	/*005865C4*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*005865C9*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005865CE*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*005865D3*/	push 0x0
	/*005865D5*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005865DA*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*005865DF*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*005865E4*/	add esp,0x24
	/*005865E7*/	mov dword ptr ds:[0xB67A34],0x0
	/*005865F1*/	jmp _00586641
_005865F3:
	/*005865F3*/	mov edi,0x20
	/*005865F8*/	mov ebx,0x4
_005865FD:
	/*005865FD*/	mov edx,dword ptr ds:[esi+0xC]
	/*00586600*/	push 0x2
	/*00586602*/	mov ecx,dword ptr ds:[edi+edx]
	/*00586605*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*0058660A*/	mov eax,dword ptr ds:[eax]
	/*0058660C*/	push 0x3
	/*0058660E*/	mov dword ptr ds:[eax+0x1DB],ebp
	/*00586614*/	mov ecx,dword ptr ds:[esi+0xC]
	/*00586617*/	mov ecx,dword ptr ds:[edi+ecx]
	/*0058661A*/	call sub_6826D0		/*call <cm0102.sub_6826D0>*/
	/*0058661F*/	mov edx,dword ptr ds:[eax]
	/*00586621*/	add edi,0x4
	/*00586624*/	dec ebx
	/*00586625*/	mov dword ptr ds:[edx+0x1DB],ebp
	/*0058662B*/	jne _005865FD
	/*0058662D*/	mov eax,dword ptr ds:[esi+0xC]
	/*00586630*/	push 0x0
	/*00586632*/	mov ecx,dword ptr ds:[eax+0x30]
	/*00586635*/	call sub_51C800		/*call <cm0102.sub_51C800>*/
	/*0058663A*/	mov dword ptr ds:[esi+0x30],0xC
_00586641:
	/*00586641*/	mov ecx,dword ptr ss:[esp+0x420]
	/*00586648*/	pop edi
	/*00586649*/	pop esi
	/*0058664A*/	pop ebp
	/*0058664B*/	pop ebx
	/*0058664C*/	mov dword ptr fs:[0x0],ecx
	/*00586653*/	add esp,0x41C
	/*00586659*/	ret
	}
}

extern "C" void __declspec(naked) sub_586660()
{
	__asm pushad
	dprintf("sub_586660 Called!\n");
	__asm popad

	__asm
	{
	/*00586660*/	mov al,byte ptr ss:[esp+0x8]
	/*00586664*/	sub esp,0x204
	/*0058666A*/	push ebx
	/*0058666B*/	push ebp
	/*0058666C*/	push esi
	/*0058666D*/	push edi
	/*0058666E*/	xor edi,edi
	/*00586670*/	xor ebx,ebx
	/*00586672*/	cmp al,0x1
	/*00586674*/	mov esi,ecx
	/*00586676*/	jne _00586762
	/*0058667C*/	push 0x11C
	/*00586681*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*00586686*/	add esp,0x4
	/*00586689*/	cmp eax,edi
	/*0058668B*/	mov dword ptr ss:[esp+0x10],eax
	/*0058668F*/	jne _00586706
	/*00586691*/	lea eax,dword ptr ss:[esp+0x14]
	/*00586695*/	lea ecx,dword ptr ss:[esp+0x114]
	/*0058669C*/	push eax
	/*0058669D*/	push ecx
	/*0058669E*/	push edi
	/*0058669F*/	push edi
	/*005866A0*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*005866A5*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*005866AA*/	add esp,0x14
	/*005866AD*/	lea edx,dword ptr ss:[esp+0x14]
	/*005866B1*/	lea eax,dword ptr ss:[esp+0x114]
	/*005866B8*/	push 0x7B5
	/*005866BD*/	push edx
	/*005866BE*/	push eax
	/*005866BF*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*005866C4*/	push eax
	/*005866C5*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*005866CA*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005866CF*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*005866D4*/	push edi
	/*005866D5*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005866DA*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*005866DF*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*005866E4*/	mov ecx,dword ptr ss:[esp+0x23C]
	/*005866EB*/	add esp,0x24
	/*005866EE*/	mov dword ptr ds:[0xB67A34],edi
	/*005866F4*/	xor ax,ax
	/*005866F7*/	mov dword ptr ds:[ecx],edi
	/*005866F9*/	pop edi
	/*005866FA*/	pop esi
	/*005866FB*/	pop ebp
	/*005866FC*/	pop ebx
	/*005866FD*/	add esp,0x204
	/*00586703*/	ret 0x8
_00586706:
	/*00586706*/	cmp word ptr ds:[esi+0x38],di
	/*0058670A*/	jle _005868C0
_00586710:
	/*00586710*/	mov eax,dword ptr ds:[esi+0x14]
	/*00586713*/	movsx ecx,di
	/*00586716*/	lea edx,dword ptr ds:[ecx+ecx*0x2]
	/*00586719*/	lea ecx,dword ptr ds:[eax+edx*0x2]
	/*0058671C*/	mov eax,dword ptr ds:[esi+0x4]
	/*0058671F*/	mov edx,dword ptr ds:[ecx]
	/*00586721*/	mov ebp,dword ptr ds:[edx+0x1DB]
	/*00586727*/	cmp ebp,dword ptr ds:[eax]
	/*00586729*/	jne _0058673E
	/*0058672B*/	cmp byte ptr ds:[ecx+0x4],0x7
	/*0058672F*/	je _0058673E
	/*00586731*/	mov eax,dword ptr ss:[esp+0x10]
	/*00586735*/	movsx ecx,bx
	/*00586738*/	inc ebx
	/*00586739*/	mov dword ptr ds:[eax+ecx*0x4],edx
	/*0058673C*/	jmp _00586742
_0058673E:
	/*0058673E*/	mov eax,dword ptr ss:[esp+0x10]
_00586742:
	/*00586742*/	inc edi
	/*00586743*/	cmp di,word ptr ds:[esi+0x38]
	/*00586747*/	jl _00586710
	/*00586749*/	mov edx,dword ptr ss:[esp+0x218]
	/*00586750*/	pop edi
	/*00586751*/	pop esi
	/*00586752*/	pop ebp
	/*00586753*/	mov dword ptr ds:[edx],eax
	/*00586755*/	mov ax,bx
	/*00586758*/	pop ebx
	/*00586759*/	add esp,0x204
	/*0058675F*/	ret 0x8
_00586762:
	/*00586762*/	cmp al,0x2
	/*00586764*/	jne _005867F9
	/*0058676A*/	push 0x11C
	/*0058676F*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*00586774*/	add esp,0x4
	/*00586777*/	cmp eax,edi
	/*00586779*/	jne _005867AD
	/*0058677B*/	lea edx,dword ptr ss:[esp+0x114]
	/*00586782*/	lea eax,dword ptr ss:[esp+0x14]
	/*00586786*/	push edx
	/*00586787*/	push eax
	/*00586788*/	push edi
	/*00586789*/	push edi
	/*0058678A*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*0058678F*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00586794*/	add esp,0x14
	/*00586797*/	lea ecx,dword ptr ss:[esp+0x114]
	/*0058679E*/	lea edx,dword ptr ss:[esp+0x14]
	/*005867A2*/	push 0x7CF
	/*005867A7*/	push ecx
	/*005867A8*/	jmp _00586849
_005867AD:
	/*005867AD*/	xor edx,edx
	/*005867AF*/	cmp word ptr ds:[esi+0x38],di
	/*005867B3*/	jle _005868C0
_005867B9:
	/*005867B9*/	mov edi,dword ptr ds:[esi+0x14]
	/*005867BC*/	movsx ecx,dx
	/*005867BF*/	lea ecx,dword ptr ds:[ecx+ecx*0x2]
	/*005867C2*/	mov ecx,dword ptr ds:[edi+ecx*0x2]
	/*005867C5*/	mov edi,dword ptr ds:[esi+0x4]
	/*005867C8*/	mov ebp,dword ptr ds:[ecx+0x1DB]
	/*005867CE*/	cmp ebp,dword ptr ds:[edi]
	/*005867D0*/	jne _005867D9
	/*005867D2*/	movsx edi,bx
	/*005867D5*/	inc ebx
	/*005867D6*/	mov dword ptr ds:[eax+edi*0x4],ecx
_005867D9:
	/*005867D9*/	inc edx
	/*005867DA*/	cmp dx,word ptr ds:[esi+0x38]
	/*005867DE*/	jl _005867B9
	/*005867E0*/	mov edx,dword ptr ss:[esp+0x218]
	/*005867E7*/	pop edi
	/*005867E8*/	pop esi
	/*005867E9*/	pop ebp
	/*005867EA*/	mov dword ptr ds:[edx],eax
	/*005867EC*/	mov ax,bx
	/*005867EF*/	pop ebx
	/*005867F0*/	add esp,0x204
	/*005867F6*/	ret 0x8
_005867F9:
	/*005867F9*/	cmp al,0x3
	/*005867FB*/	jne _005868D9
	/*00586801*/	cmp dword ptr ds:[esi+0x30],0xB
	/*00586805*/	jne _005868D9
	/*0058680B*/	push 0x11C
	/*00586810*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*00586815*/	add esp,0x4
	/*00586818*/	cmp eax,edi
	/*0058681A*/	jne _00586891
	/*0058681C*/	lea edx,dword ptr ss:[esp+0x114]
	/*00586823*/	lea eax,dword ptr ss:[esp+0x14]
	/*00586827*/	push edx
	/*00586828*/	push eax
	/*00586829*/	push edi
	/*0058682A*/	push edi
	/*0058682B*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00586830*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00586835*/	add esp,0x14
	/*00586838*/	lea ecx,dword ptr ss:[esp+0x114]
	/*0058683F*/	lea edx,dword ptr ss:[esp+0x14]
	/*00586843*/	push 0x7E9
	/*00586848*/	push ecx
_00586849:
	/*00586849*/	push edx
	/*0058684A*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*0058684F*/	push eax
	/*00586850*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*00586855*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*0058685A*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*0058685F*/	push edi
	/*00586860*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00586865*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*0058686A*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*0058686F*/	mov eax,dword ptr ss:[esp+0x23C]
	/*00586876*/	add esp,0x24
	/*00586879*/	mov dword ptr ds:[0xB67A34],edi
	/*0058687F*/	mov dword ptr ds:[eax],edi
	/*00586881*/	pop edi
	/*00586882*/	pop esi
	/*00586883*/	pop ebp
	/*00586884*/	xor ax,ax
	/*00586887*/	pop ebx
	/*00586888*/	add esp,0x204
	/*0058688E*/	ret 0x8
_00586891:
	/*00586891*/	xor edx,edx
	/*00586893*/	cmp word ptr ds:[esi+0x38],di
	/*00586897*/	jle _005868C0
_00586899:
	/*00586899*/	mov edi,dword ptr ds:[esi+0x14]
	/*0058689C*/	movsx ecx,dx
	/*0058689F*/	lea ecx,dword ptr ds:[ecx+ecx*0x2]
	/*005868A2*/	mov ecx,dword ptr ds:[edi+ecx*0x2]
	/*005868A5*/	mov edi,dword ptr ds:[esi+0x4]
	/*005868A8*/	mov ebp,dword ptr ds:[ecx+0x1DB]
	/*005868AE*/	cmp ebp,dword ptr ds:[edi]
	/*005868B0*/	jne _005868B9
	/*005868B2*/	movsx edi,bx
	/*005868B5*/	inc ebx
	/*005868B6*/	mov dword ptr ds:[eax+edi*0x4],ecx
_005868B9:
	/*005868B9*/	inc edx
	/*005868BA*/	cmp dx,word ptr ds:[esi+0x38]
	/*005868BE*/	jl _00586899
_005868C0:
	/*005868C0*/	mov edx,dword ptr ss:[esp+0x218]
	/*005868C7*/	pop edi
	/*005868C8*/	pop esi
	/*005868C9*/	pop ebp
	/*005868CA*/	mov dword ptr ds:[edx],eax
	/*005868CC*/	mov ax,bx
	/*005868CF*/	pop ebx
	/*005868D0*/	add esp,0x204
	/*005868D6*/	ret 0x8
_005868D9:
	/*005868D9*/	mov eax,dword ptr ss:[esp+0x218]
	/*005868E0*/	push edi
	/*005868E1*/	push eax
	/*005868E2*/	mov ecx,esi
	/*005868E4*/	call sub_48E1C0		/*call <cm0102.sub_48E1C0>*/
	/*005868E9*/	pop edi
	/*005868EA*/	pop esi
	/*005868EB*/	pop ebp
	/*005868EC*/	pop ebx
	/*005868ED*/	add esp,0x204
	/*005868F3*/	ret 0x8
	}
}

extern "C" void __declspec(naked) sub_586900()		// Called at end of setup
{
	__asm pushad
	dprintf("sub_586900 Called!\n");
	__asm popad

	__asm
	{
	/*00586900*/	sub esp,0x220
	/*00586906*/	push ebp
	/*00586907*/	push esi
	/*00586908*/	push edi
	/*00586909*/	mov edi,ecx						// League struct with .tmp file (D0 A1 96 00)
	/*0058690B*/	mov al,0x1
	/*0058690D*/	xor esi,esi
	/*0058690F*/	mov byte ptr ss:[esp+0x14],al
	/*00586913*/	mov byte ptr ss:[esp+0xF],al
	/*00586917*/	cmp dword ptr ds:[edi+0x8],esi	// See if that dword in league struct is 0 (it isn't points to a block?)
	/*0058691A*/	jne _0058694C
	/*0058691C*/	lea eax,dword ptr ss:[esp+0x2C]
	/*00586920*/	lea ecx,dword ptr ss:[esp+0x12C]
	/*00586927*/	push eax
	/*00586928*/	push ecx
	/*00586929*/	push esi
	/*0058692A*/	push esi
	/*0058692B*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00586930*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00586935*/	add esp,0x14
	/*00586938*/	lea edx,dword ptr ss:[esp+0x2C]
	/*0058693C*/	lea eax,dword ptr ss:[esp+0x12C]
	/*00586943*/	push 0x81B
	/*00586948*/	push edx
	/*00586949*/	push eax
	/*0058694A*/	jmp _00586990
_0058694C:
	/*0058694C*/	movsx ecx,word ptr ds:[edi+0x36]		// 0x47 (71) teams
	/*00586950*/	shl ecx,0x2								// 71 * 4 = 284
	/*00586953*/	push ecx
	/*00586954*/	call cm0102_malloc		/*call <cm0102.cm0102_malloc>*/
	/*00586959*/	mov ebp,eax								// ebp and eax have the 284 bytes
	/*0058695B*/	add esp,0x4
	/*0058695E*/	cmp ebp,esi
	/*00586960*/	jne _005869C8							// if malloc worked jne
	/*00586962*/	lea edx,dword ptr ss:[esp+0x12C]
	/*00586969*/	lea eax,dword ptr ss:[esp+0x2C]
	/*0058696D*/	push edx
	/*0058696E*/	push eax
	/*0058696F*/	push esi
	/*00586970*/	push esi
	/*00586971*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00586976*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*0058697B*/	add esp,0x14
	/*0058697E*/	lea ecx,dword ptr ss:[esp+0x12C]
	/*00586985*/	lea edx,dword ptr ss:[esp+0x2C]
	/*00586989*/	push 0x823
	/*0058698E*/	push ecx
	/*0058698F*/	push edx
_00586990:
	/*00586990*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*00586995*/	push eax
	/*00586996*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*0058699B*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005869A0*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*005869A5*/	push esi
	/*005869A6*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*005869AB*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*005869B0*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*005869B5*/	add esp,0x24
	/*005869B8*/	mov dword ptr ds:[0xB67A34],esi
	/*005869BE*/	pop edi
	/*005869BF*/	pop esi
	/*005869C0*/	pop ebp
	/*005869C1*/	add esp,0x220
	/*005869C7*/	ret
_005869C8:
	/*005869C8*/	xor ecx,ecx
	/*005869CA*/	cmp word ptr ds:[edi+0x36],si			// cmp the stored 71 with 0
	/*005869CE*/	push ebx
	/*005869CF*/	jle _005869E8							// don't jmp
_005869D1:
	/*005869D1*/	mov ebx,dword ptr ds:[edi+0x14]			// Link to teams (Arsenal are first) - 6 bytes - extra two are 07 00 to begin with
	/*005869D4*/	movsx eax,cx							// make eax = 0 at start - but counter
	/*005869D7*/	inc ecx
	/*005869D8*/	lea edx,dword ptr ds:[eax+eax*0x2]		
	/*005869DB*/	mov edx,dword ptr ds:[ebx+edx*0x2]		// edx ends up pointer to team (Arsenal)
	/*005869DE*/	mov dword ptr ss:[ebp+eax*0x4],edx		// Copy to the 284 bytes we allocated
	/*005869E2*/	cmp cx,word ptr ds:[edi+0x36]
	/*005869E6*/	jl _005869D1							// Loop till we've copied all 71 teams
_005869E8:
	/*005869E8*/	movsx eax,word ptr ds:[edi+0x36]		// 71 teams into eax
	/*005869EC*/	push eax
	/*005869ED*/	push ebp								// Pointer to the teams in the new block
	/*005869EE*/	call sub_4C08F0		/*call <cm0102.sub_4C08F0>*/		// To comp_utils.cpp
	/*005869F3*/	mov edx,dword ptr ds:[edi]				// League struct with .tmp file - first DWORD is pointer to function sub_5839e0
	/*005869F5*/	add esp,0x8
	/*005869F8*/	lea eax,dword ptr ss:[esp+0x2E]			// block of memory - all CC CC - maybe just a WORD
	/*005869FC*/	lea ecx,dword ptr ss:[esp+0x24]			// block of memory - all CC CC - maybe just a WORD
	/*00586A00*/	push 0x0
	/*00586A02*/	push eax
	/*00586A03*/	push ecx
	/*00586A04*/	push 0xC
	/*00586A06*/	mov ecx,edi
	/*00586A08*/	call dword ptr ds:[edx+0x3C]			// european_cup_schedule_583C50 (european_cup.cpp)	// Second call
	/*00586A0B*/	mov edx,dword ptr ss:[esp+0x24]			// edx = CCCC0003
	/*00586A0F*/	mov ebx,eax								// eax - points to a block beginning 48 00 01 5C
	/*00586A11*/	mov dword ptr ss:[esp+0x28],ebx			// is eax block ^
	/*00586A15*/	lea eax,dword ptr ds:[edx-0x1]			// eax = cccc0002
	/*00586A18*/	test ax,ax
	/*00586A1B*/	jl _00586AE6							// don't jl
	/*00586A21*/	movsx eax,ax							// eax = 2
	/*00586A24*/	mov dword ptr ss:[esp+0x1C],eax			// store 2
	/*00586A28*/	lea ecx,dword ptr ds:[eax+eax*0x2]		// ecx = 6
	/*00586A2B*/	lea edx,dword ptr ds:[eax+ecx*0x4]		// edx = 1A = 26
	/*00586A2E*/	lea ecx,dword ptr ds:[eax+0x1]			// ecx = 3 (2 + 1)
	/*00586A31*/	mov dword ptr ss:[esp+0x14],ecx			// store 3
	/*00586A35*/	lea ebx,dword ptr ds:[ebx+edx*0x8+0x1A] // ebx = block beginning 48 00 01 5C  195F3378 + 8*1A + 1A = 195F3462. So EBX+(1A*9)
_00586A39:
	/*00586A39*/	movsx edx,word ptr ss:[esp+0x24]		// 3 to to edx
	/*00586A3E*/	dec edx									// now 2
	/*00586A3F*/	cmp eax,edx								// eax == 2
	/*00586A41*/	jne _00586A83							// don't jne
	/*00586A43*/	cmp word ptr ds:[ebx],0x0				// contains 1
	/*00586A47*/	mov dword ptr ss:[esp+0x20],0x0			// store 0
	/*00586A4F*/	jle _00586A83							// not taken
_00586A51:
	/*00586A51*/	mov ecx,dword ptr ss:[esp+0x18]			// ecx == cccccc01 - check - probably 01 cc cc cc in the block
	/*00586A55*/	movsx eax,si							// eax = 0
	/*00586A58*/	push ecx
	/*00586A59*/	mov ecx,dword ptr ds:[edi+0x8]			// edi = League struct with .tmp file (D0 A1 96 00)
	/*00586A5C*/	mov eax,dword ptr ss:[ebp+eax*0x4]		// First team in new block (Real Madrid)
	/*00586A60*/	inc esi									// counter++
	/*00586A61*/	push eax								// Push Team
	/*00586A62*/	call sub_4A2540		/*call <cm0102.sub_4A2540>*/	// comp_stats call
	/*00586A67*/	mov al,byte ptr ss:[esp+0x13]			// gets 1 (for Real Madrid)
	/*00586A6B*/	inc al									// increments to 2
	/*00586A6D*/	mov byte ptr ss:[esp+0x13],al			// stores 2
	/*00586A71*/	mov eax,dword ptr ss:[esp+0x20]			// gets the 0 we stored earlier
	/*00586A75*/	inc eax									// increments to 1 
	/*00586A76*/	cmp ax,word ptr ds:[ebx]				// compares to ebx which is pointing to a 1
	/*00586A79*/	mov dword ptr ss:[esp+0x20],eax			// store incremented counter 1
	/*00586A7D*/	jl _00586A51							// don't take jl
	/*00586A7F*/	mov eax,dword ptr ss:[esp+0x1C]			// get 2 (stored earlier)
_00586A83:
	/*00586A83*/	mov dl,byte ptr ss:[esp+0x13]			// get 2 (stored above from Real Madrid)
	/*00586A87*/	cmp word ptr ds:[ebx],0x0				// [ebx] = 01 00 00 00
	/*00586A8B*/	mov byte ptr ss:[esp+0x18],dl			//  02 CC CC CC
	/*00586A8F*/	mov dword ptr ss:[esp+0x20],0x0			// Store 0 back into esp+0x20
	/*00586A97*/	jle _00586ACB							// not taken
_00586A99:
	/*00586A99*/	mov ecx,dword ptr ss:[esp+0x18]			// 02 cc cc cc
	/*00586A9D*/	movsx eax,si							// SI = 1 to EAX
	/*00586AA0*/	push ecx
	/*00586AA1*/	mov ecx,dword ptr ds:[edi+0x8]			// edi = League struct with .tmp file (D0 A1 96 00) + 8 - pointer unknown
	/*00586AA4*/	mov eax,dword ptr ss:[ebp+eax*0x4]		// get team = 1 team (FC Barcelona)
	/*00586AA8*/	inc esi
	/*00586AA9*/	push eax
	/*00586AAA*/	call sub_4A2540		/*call <cm0102.sub_4A2540>*/	// comp_stats call
	/*00586AAF*/	mov al,byte ptr ss:[esp+0x13]
	/*00586AB3*/	inc al
	/*00586AB5*/	mov byte ptr ss:[esp+0x13],al
	/*00586AB9*/	mov eax,dword ptr ss:[esp+0x20]
	/*00586ABD*/	inc eax
	/*00586ABE*/	cmp ax,word ptr ds:[ebx]
	/*00586AC1*/	mov dword ptr ss:[esp+0x20],eax
	/*00586AC5*/	jl _00586A99
	/*00586AC7*/	mov eax,dword ptr ss:[esp+0x1C]
_00586ACB:
	/*00586ACB*/	mov ecx,dword ptr ss:[esp+0x14]
	/*00586ACF*/	dec eax
	/*00586AD0*/	sub ebx,0x68
	/*00586AD3*/	dec ecx
	/*00586AD4*/	mov dword ptr ss:[esp+0x1C],eax
	/*00586AD8*/	mov dword ptr ss:[esp+0x14],ecx
	/*00586ADC*/	jne _00586A39
	/*00586AE2*/	mov ebx,dword ptr ss:[esp+0x28]
_00586AE6:
	/*00586AE6*/	push ebx
	/*00586AE7*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00586AEC*/	add esp,0x4
	/*00586AEF*/	mov dword ptr ss:[esp+0x14],0x2
_00586AF7:
	/*00586AF7*/	mov dl,byte ptr ss:[esp+0x13]
	/*00586AFB*/	mov ebx,0x4
	/*00586B00*/	mov al,dl
	/*00586B02*/	mov byte ptr ss:[esp+0x18],dl
	/*00586B06*/	add al,bl
	/*00586B08*/	mov byte ptr ss:[esp+0x13],al
_00586B0C:
	/*00586B0C*/	mov ecx,dword ptr ss:[esp+0x18]
	/*00586B10*/	movsx eax,si
	/*00586B13*/	push ecx
	/*00586B14*/	mov ecx,dword ptr ds:[edi+0x8]
	/*00586B17*/	mov eax,dword ptr ss:[ebp+eax*0x4]
	/*00586B1B*/	inc esi
	/*00586B1C*/	push eax
	/*00586B1D*/	call sub_4A2540		/*call <cm0102.sub_4A2540>*/
	/*00586B22*/	dec ebx
	/*00586B23*/	jne _00586B0C
	/*00586B25*/	mov eax,dword ptr ss:[esp+0x14]
	/*00586B29*/	dec eax
	/*00586B2A*/	mov dword ptr ss:[esp+0x14],eax
	/*00586B2E*/	jne _00586AF7
	/*00586B30*/	mov dword ptr ss:[esp+0x14],0x2
_00586B38:
	/*00586B38*/	mov dl,byte ptr ss:[esp+0x13]
	/*00586B3C*/	mov ebx,0x8
	/*00586B41*/	mov al,dl
	/*00586B43*/	mov byte ptr ss:[esp+0x18],dl
	/*00586B47*/	add al,bl
	/*00586B49*/	mov byte ptr ss:[esp+0x13],al
_00586B4D:
	/*00586B4D*/	mov ecx,dword ptr ss:[esp+0x18]
	/*00586B51*/	movsx eax,si
	/*00586B54*/	push ecx
	/*00586B55*/	mov ecx,dword ptr ds:[edi+0x8]
	/*00586B58*/	mov eax,dword ptr ss:[ebp+eax*0x4]
	/*00586B5C*/	inc esi
	/*00586B5D*/	push eax
	/*00586B5E*/	call sub_4A2540		/*call <cm0102.sub_4A2540>*/
	/*00586B63*/	dec ebx
	/*00586B64*/	jne _00586B4D
	/*00586B66*/	mov eax,dword ptr ss:[esp+0x14]
	/*00586B6A*/	dec eax
	/*00586B6B*/	mov dword ptr ss:[esp+0x14],eax
	/*00586B6F*/	jne _00586B38
	/*00586B71*/	mov ax,word ptr ds:[edi+0x3C]
	/*00586B75*/	dec ax
	/*00586B77*/	test ax,ax
	/*00586B7A*/	jl _00586BEC
	/*00586B7C*/	movsx ecx,ax
	/*00586B7F*/	lea edx,dword ptr ds:[ecx+ecx*0x2]
	/*00586B82*/	lea eax,dword ptr ds:[ecx+edx*0x4]
	/*00586B85*/	shl eax,0x3
	/*00586B88*/	inc ecx
	/*00586B89*/	mov dword ptr ss:[esp+0x1C],eax
	/*00586B8D*/	mov dword ptr ss:[esp+0x14],ecx
_00586B91:
	/*00586B91*/	mov edx,dword ptr ds:[edi+0xA3]
	/*00586B97*/	mov cl,byte ptr ss:[esp+0x13]
	/*00586B9B*/	xor ebx,ebx
	/*00586B9D*/	mov byte ptr ss:[esp+0x18],cl
	/*00586BA1*/	cmp word ptr ds:[edx+eax+0x1A],bx
	/*00586BA6*/	jle _00586BDA
_00586BA8:
	/*00586BA8*/	mov ecx,dword ptr ss:[esp+0x18]
	/*00586BAC*/	movsx eax,si
	/*00586BAF*/	push ecx
	/*00586BB0*/	mov ecx,dword ptr ds:[edi+0x8]
	/*00586BB3*/	mov eax,dword ptr ss:[ebp+eax*0x4]
	/*00586BB7*/	inc esi
	/*00586BB8*/	push eax
	/*00586BB9*/	call sub_4A2540		/*call <cm0102.sub_4A2540>*/
	/*00586BBE*/	mov al,byte ptr ss:[esp+0x13]
	/*00586BC2*/	mov edx,dword ptr ds:[edi+0xA3]
	/*00586BC8*/	inc al
	/*00586BCA*/	inc ebx
	/*00586BCB*/	mov byte ptr ss:[esp+0x13],al
	/*00586BCF*/	mov eax,dword ptr ss:[esp+0x1C]
	/*00586BD3*/	cmp bx,word ptr ds:[edx+eax+0x1A]
	/*00586BD8*/	jl _00586BA8
_00586BDA:
	/*00586BDA*/	mov ecx,dword ptr ss:[esp+0x14]
	/*00586BDE*/	sub eax,0x68
	/*00586BE1*/	dec ecx
	/*00586BE2*/	mov dword ptr ss:[esp+0x1C],eax
	/*00586BE6*/	mov dword ptr ss:[esp+0x14],ecx
	/*00586BEA*/	jne _00586B91
_00586BEC:
	/*00586BEC*/	push ebp
	/*00586BED*/	call cm0102_maybe_free2		/*call <cm0102.cm0102_maybe_free2>*/
	/*00586BF2*/	add esp,0x4
	/*00586BF5*/	pop ebx
	/*00586BF6*/	pop edi
	/*00586BF7*/	pop esi
	/*00586BF8*/	pop ebp
	/*00586BF9*/	add esp,0x220
	/*00586BFF*/	ret
	}
}

extern "C" void __declspec(naked) sub_586FA0()
{
	__asm pushad
	dprintf("sub_586FA0 Called!\n");
	__asm popad

	__asm
	{
	/*00586FA0*/	sub esp,0x200
	/*00586FA6*/	push ebx
	/*00586FA7*/	mov ebx,dword ptr ss:[esp+0x20C]
	/*00586FAE*/	push esi
	/*00586FAF*/	cmp ebx,0x1E
	/*00586FB2*/	push edi
	/*00586FB3*/	jge _00587024
	/*00586FB5*/	lea eax,dword ptr ss:[esp+0xC]
	/*00586FB9*/	lea ecx,dword ptr ss:[esp+0x10C]
	/*00586FC0*/	push eax
	/*00586FC1*/	push ecx
	/*00586FC2*/	push 0x0
	/*00586FC4*/	push 0x0
	/*00586FC6*/	push 0x9C4900		/*push cm0102.9C4900*/
	/*00586FCB*/	call cm0102_splitpath		/*call <cm0102.cm0102_splitpath>*/
	/*00586FD0*/	add esp,0x14
	/*00586FD3*/	lea edx,dword ptr ss:[esp+0xC]
	/*00586FD7*/	lea eax,dword ptr ss:[esp+0x10C]
	/*00586FDE*/	push 0x950
	/*00586FE3*/	push edx
	/*00586FE4*/	push eax
	/*00586FE5*/	call cm0102_GetVersionString		/*call <cm0102.cm0102_GetVersionString>*/
	/*00586FEA*/	push eax
	/*00586FEB*/	push 0x9870E8		/*push cm0102.9870E8*/
	/*00586FF0*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00586FF5*/	call cm0102_sprintf		/*call <cm0102.cm0102_sprintf>*/
	/*00586FFA*/	push 0x0
	/*00586FFC*/	push 0xAE24D0		/*push cm0102.AE24D0*/
	/*00587001*/	push 0x9870E0		/*push cm0102.9870E0*/
	/*00587006*/	call cm0102_CreateErrorMsgBox		/*call <cm0102.cm0102_CreateErrorMsgBox>*/
	/*0058700B*/	add esp,0x24
	/*0058700E*/	mov dword ptr ds:[0xB67A34],0x0
	/*00587018*/	pop edi
	/*00587019*/	pop esi
	/*0058701A*/	pop ebx
	/*0058701B*/	add esp,0x200
	/*00587021*/	ret 0x18
_00587024:
	/*00587024*/	mov di,word ptr ss:[esp+0x218]
	/*0058702C*/	movsx esi,di
	/*0058702F*/	push esi
	/*00587030*/	call sub_4B01D0		/*call <cm0102.sub_4B01D0>*/
	/*00587035*/	add esp,0x4
	/*00587038*/	cmp eax,0x449
	/*0058703D*/	jne _005870A9
	/*0058703F*/	mov al,byte ptr ss:[esp+0x220]
	/*00587046*/	test al,al
	/*00587048*/	je _00587077
	/*0058704A*/	cmp al,0x6
	/*0058704C*/	je _00587077
	/*0058704E*/	cmp al,0x7
	/*00587050*/	je _00587077
	/*00587052*/	cmp al,0x8
	/*00587054*/	je _00587077
	/*00587056*/	mov ecx,dword ptr ss:[esp+0x210]
	/*0058705D*/	push 0x9A6790		/*push cm0102.9A6790*/
	/*00587062*/	push ecx
	/*00587063*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*00587068*/	add esp,0x8
	/*0058706B*/	pop edi
	/*0058706C*/	pop esi
	/*0058706D*/	pop ebx
	/*0058706E*/	add esp,0x200
	/*00587074*/	ret 0x18
_00587077:
	/*00587077*/	mov edx,dword ptr ss:[esp+0x224]
	/*0058707E*/	mov ecx,dword ptr ss:[esp+0x210]
	/*00587085*/	push 0xAD9C64		/*push cm0102.AD9C64*/
	/*0058708A*/	movsx eax,byte ptr ds:[edx+0x37]
	/*0058708E*/	push eax
	/*0058708F*/	push 0x9C4AAC		/*push cm0102.9C4AAC*/
	/*00587094*/	push ecx
	/*00587095*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*0058709A*/	add esp,0x10
	/*0058709D*/	pop edi
	/*0058709E*/	pop esi
	/*0058709F*/	pop ebx
	/*005870A0*/	add esp,0x200
	/*005870A6*/	ret 0x18
_005870A9:
	/*005870A9*/	push esi
	/*005870AA*/	call sub_4B01D0		/*call <cm0102.sub_4B01D0>*/
	/*005870AF*/	add esp,0x4
	/*005870B2*/	cmp eax,0x44A
	/*005870B7*/	jne _00587123
	/*005870B9*/	mov al,byte ptr ss:[esp+0x220]
	/*005870C0*/	test al,al
	/*005870C2*/	je _005870F1
	/*005870C4*/	cmp al,0x6
	/*005870C6*/	je _005870F1
	/*005870C8*/	cmp al,0x7
	/*005870CA*/	je _005870F1
	/*005870CC*/	cmp al,0x8
	/*005870CE*/	je _005870F1
	/*005870D0*/	mov edx,dword ptr ss:[esp+0x210]
	/*005870D7*/	push 0x9A677C		/*push cm0102.9A677C*/
	/*005870DC*/	push edx
	/*005870DD*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*005870E2*/	add esp,0x8
	/*005870E5*/	pop edi
	/*005870E6*/	pop esi
	/*005870E7*/	pop ebx
	/*005870E8*/	add esp,0x200
	/*005870EE*/	ret 0x18
_005870F1:
	/*005870F1*/	mov eax,dword ptr ss:[esp+0x224]
	/*005870F8*/	mov edx,dword ptr ss:[esp+0x210]
	/*005870FF*/	push 0xAD9C64		/*push cm0102.AD9C64*/
	/*00587104*/	movsx ecx,byte ptr ds:[eax+0x37]
	/*00587108*/	push ecx
	/*00587109*/	push 0x9C4A84		/*push cm0102.9C4A84*/
	/*0058710E*/	push edx
	/*0058710F*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*00587114*/	add esp,0x10
	/*00587117*/	pop edi
	/*00587118*/	pop esi
	/*00587119*/	pop ebx
	/*0058711A*/	add esp,0x200
	/*00587120*/	ret 0x18
_00587123:
	/*00587123*/	mov cl,byte ptr ss:[esp+0x220]
	/*0058712A*/	cmp cl,0x1
	/*0058712D*/	jne _00587150
	/*0058712F*/	mov eax,dword ptr ss:[esp+0x210]
	/*00587136*/	push 0x99B7D0		/*push cm0102.99B7D0*/
	/*0058713B*/	push eax
	/*0058713C*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*00587141*/	add esp,0x8
	/*00587144*/	pop edi
	/*00587145*/	pop esi
	/*00587146*/	pop ebx
	/*00587147*/	add esp,0x200
	/*0058714D*/	ret 0x18
_00587150:
	/*00587150*/	mov ax,word ptr ss:[esp+0x21C]
	/*00587158*/	test di,di
	/*0058715B*/	jne _005871AE
	/*0058715D*/	test ax,ax
	/*00587160*/	jne _005871AE
	/*00587162*/	cmp cl,0x2
	/*00587165*/	jne _00587188
	/*00587167*/	mov ecx,dword ptr ss:[esp+0x210]
	/*0058716E*/	push 0x99B7C4		/*push cm0102.99B7C4*/
	/*00587173*/	push ecx
	/*00587174*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*00587179*/	add esp,0x8
	/*0058717C*/	pop edi
	/*0058717D*/	pop esi
	/*0058717E*/	pop ebx
	/*0058717F*/	add esp,0x200
	/*00587185*/	ret 0x18
_00587188:
	/*00587188*/	cmp cl,0x3
	/*0058718B*/	jne _005871AE
	/*0058718D*/	mov edx,dword ptr ss:[esp+0x210]
	/*00587194*/	push 0x99B7B4		/*push cm0102.99B7B4*/
	/*00587199*/	push edx
	/*0058719A*/	call sub_66F4E0		/*call <cm0102.sub_66F4E0>*/
	/*0058719F*/	add esp,0x8
	/*005871A2*/	pop edi
	/*005871A3*/	pop esi
	/*005871A4*/	pop ebx
	/*005871A5*/	add esp,0x200
	/*005871AB*/	ret 0x18
_005871AE:
	/*005871AE*/	mov ecx,dword ptr ss:[esp+0x210]
	/*005871B5*/	push 0x0
	/*005871B7*/	movsx edx,ax
	/*005871BA*/	push ebx
	/*005871BB*/	push ecx
	/*005871BC*/	push edx
	/*005871BD*/	push esi
	/*005871BE*/	call sub_4BFFC0		/*call <cm0102.sub_4BFFC0>*/
	/*005871C3*/	add esp,0x14
	/*005871C6*/	pop edi
	/*005871C7*/	pop esi
	/*005871C8*/	pop ebx
	/*005871C9*/	add esp,0x200
	/*005871CF*/	ret 0x18
	}
}

extern "C" void __declspec(naked) sub_5871E0()
{
	__asm pushad
	dprintf("sub_5871E0 Called!\n");
	__asm popad

	__asm
	{
	/*005871E0*/	mov ecx,dword ptr ss:[esp+0x4]
	/*005871E4*/	mov edx,dword ptr ss:[esp+0x8]
	/*005871E8*/	push esi
	/*005871E9*/	movsx esi,byte ptr ds:[ecx+0x4]
	/*005871ED*/	movsx eax,byte ptr ds:[edx+0x4]
	/*005871F1*/	sub eax,esi
	/*005871F3*/	jne _0058721B
	/*005871F5*/	mov eax,dword ptr ds:[ecx]
	/*005871F7*/	mov eax,dword ptr ds:[eax+0x53]
	/*005871FA*/	movsx esi,word ptr ds:[eax+0x8E]
	/*00587201*/	mov eax,dword ptr ds:[edx]
	/*00587203*/	mov eax,dword ptr ds:[eax+0x53]
	/*00587206*/	movsx eax,word ptr ds:[eax+0x8E]
	/*0058720D*/	sub eax,esi
	/*0058720F*/	jne _0058721B
	/*00587211*/	movsx eax,byte ptr ds:[ecx+0x6]
	/*00587215*/	movsx ecx,byte ptr ds:[edx+0x6]
	/*00587219*/	sub eax,ecx
_0058721B:
	/*0058721B*/	pop esi
	/*0058721C*/	ret
	}
}


///////////////// Below might not be champions league
extern "C" void __declspec(naked) sub_587220()
{
	__asm pushad
	dprintf("sub_587220 Called!\n");
	__asm popad

	__asm
	{
	/*00587220*/	mov eax,dword ptr fs:[0x0]
	/*00587226*/	push 0xFFFFFFFF
	/*00587228*/	push 0x958B3B		/*push <cm0102.sub_958B3B>*/
	/*0058722D*/	push eax
	/*0058722E*/	mov dword ptr fs:[0x0],esp
	/*00587235*/	sub esp,0xE0
	/*0058723B*/	push esi
	/*0058723C*/	mov esi,dword ptr ss:[esp+0xF4]
	/*00587243*/	test esi,esi
	/*00587245*/	push edi
	/*00587246*/	je _00587356
	/*0058724C*/	mov eax,dword ptr ds:[esi+0x61]
	/*0058724F*/	test eax,eax
	/*00587251*/	je _00587356
	/*00587257*/	mov eax,dword ptr ds:[esi+0x39]
	/*0058725A*/	test eax,eax
	/*0058725C*/	je _00587356
	/*00587262*/	mov edi,dword ptr ss:[esp+0xFC]
	/*00587269*/	test edi,edi
	/*0058726B*/	je _00587356
	/*00587271*/	push ebx
	/*00587272*/	push 0x3
	/*00587274*/	call cm0102_rand2		/*call <cm0102.cm0102_rand2>*/
	/*00587279*/	add esp,0x4
	/*0058727C*/	lea ecx,dword ptr ss:[esp+0xC]
	/*00587280*/	mov ebx,eax
	/*00587282*/	push 0x0
	/*00587284*/	push 0xFBD
	/*00587289*/	call sub_77BBE0		/*call <cm0102.sub_77BBE0>*/
	/*0058728E*/	mov eax,dword ptr ds:[esi]
	/*00587290*/	lea ecx,dword ptr ss:[esp+0xC]
	/*00587294*/	push eax
	/*00587295*/	push 0x0
	/*00587297*/	mov dword ptr ss:[esp+0xFC],0x0
	/*005872A2*/	call sub_785790		/*call <cm0102.sub_785790>*/
	/*005872A7*/	mov ecx,dword ptr ds:[esi+0x4]
	/*005872AA*/	mov edx,dword ptr ds:[ecx+0x33]
	/*005872AD*/	lea ecx,dword ptr ss:[esp+0xC]
	/*005872B1*/	push edx
	/*005872B2*/	push 0x1
	/*005872B4*/	call sub_785790		/*call <cm0102.sub_785790>*/
	/*005872B9*/	mov eax,dword ptr ds:[esi+0x8]
	/*005872BC*/	mov ecx,dword ptr ds:[eax+0x33]
	/*005872BF*/	push ecx
	/*005872C0*/	push 0x2
	/*005872C2*/	lea ecx,dword ptr ss:[esp+0x14]
	/*005872C6*/	call sub_785790		/*call <cm0102.sub_785790>*/
	/*005872CB*/	mov edx,dword ptr ds:[esi+0xC]
	/*005872CE*/	lea ecx,dword ptr ss:[esp+0xC]
	/*005872D2*/	mov eax,dword ptr ds:[edx+0x33]
	/*005872D5*/	push eax
	/*005872D6*/	push 0x3
	/*005872D8*/	call sub_785790		/*call <cm0102.sub_785790>*/
	/*005872DD*/	mov ecx,dword ptr ds:[edi]
	/*005872DF*/	push ecx
	/*005872E0*/	push 0x4
	/*005872E2*/	lea ecx,dword ptr ss:[esp+0x14]
	/*005872E6*/	call sub_785790		/*call <cm0102.sub_785790>*/
	/*005872EB*/	mov edx,dword ptr ds:[esi+0x39]
	/*005872EE*/	lea ecx,dword ptr ss:[esp+0xC]
	/*005872F2*/	mov eax,dword ptr ds:[edx]
	/*005872F4*/	push eax
	/*005872F5*/	push 0x5
	/*005872F7*/	call sub_785790		/*call <cm0102.sub_785790>*/
	/*005872FC*/	push ebx
	/*005872FD*/	push 0x6
	/*005872FF*/	lea ecx,dword ptr ss:[esp+0x14]
	/*00587303*/	call sub_785790		/*call <cm0102.sub_785790>*/
	/*00587308*/	push 0xAE2C90		/*push cm0102.AE2C90*/				// Current Day Of year
	/*0058730D*/	push edi
	/*0058730E*/	call sub_547770		/*call <cm0102.sub_547770>*/
	/*00587313*/	add esp,0x8
	/*00587316*/	test eax,eax
	/*00587318*/	pop ebx
	/*00587319*/	je _00587356
	/*0058731B*/	mov ecx,dword ptr ds:[0xB63D28]
	/*00587321*/	test ecx,ecx
	/*00587323*/	je _0058732F
	/*00587325*/	push esi
	/*00587326*/	call sub_62ED70		/*call <cm0102.sub_62ED70>*/
	/*0058732B*/	test eax,eax
	/*0058732D*/	jne _00587356
_0058732F:
	/*0058732F*/	mov ecx,dword ptr ds:[0xDE1D08]
	/*00587335*/	push 0x0
	/*00587337*/	push esi
	/*00587338*/	push edi
	/*00587339*/	call sub_8972C0		/*call <cm0102.sub_8972C0>*/
	/*0058733E*/	cmp al,0xFF
	/*00587340*/	jle _00587356
	/*00587342*/	mov ecx,dword ptr ds:[esi+0x39]
	/*00587345*/	lea edx,dword ptr ss:[esp+0x8]
	/*00587349*/	push ecx
	/*0058734A*/	mov ecx,dword ptr ds:[0xB7431C]
	/*00587350*/	push edx
	/*00587351*/	call sub_7861E0		/*call <cm0102.sub_7861E0>*/
_00587356:
	/*00587356*/	mov ecx,dword ptr ss:[esp+0xE8]
	/*0058735D*/	pop edi
	/*0058735E*/	pop esi
	/*0058735F*/	mov dword ptr fs:[0x0],ecx
	/*00587366*/	add esp,0xEC
	/*0058736C*/	ret
	}
}

// Hook the malloc function
static void*(*sub_944E58)(int memsize, DWORD de3008) = (void*(*)(int memsize, DWORD de3008))(0x944E58);
extern "C" void* our_malloc(int memSize)
{
	void *ret = sub_944E58(memSize, *((DWORD*)0xDE3008));

	memset(ret, 0x4E, memSize);	// Make the block full of 0x4E 'N' so I can properly spot the block of memory
	return ret;
}

void setup_european_cup()
{
	PatchFunction(0x5836A0, (DWORD)&european_cup_june_awards_5836A0);
	PatchFunction(0x5837C0, (DWORD)&european_cup_setup_5837C0);
	PatchFunction(0x5839D0, (DWORD)&sub_5839D0);
	PatchFunction(0x5839E0, (DWORD)&sub_5839E0);
	PatchFunction(0x583A00, (DWORD)&sub_583A00);
	PatchFunction(0x583B10, (DWORD)&sub_583B10);
	PatchFunction(0x583C50, (DWORD)&european_cup_schedule_583C50);
	PatchFunction(0x584990, (DWORD)&european_cup_get_qualifying_teams_584990);
	PatchFunction(0x584AD0, (DWORD)&sub_584AD0);
	PatchFunction(0x584AE0, (DWORD)&sub_584AE0);
	PatchFunction(0x584D60, (DWORD)&sub_584D60);
	PatchFunction(0x584FA0, (DWORD)&european_cup_select_teams_584FA0);
	PatchFunction(0x5851D0, (DWORD)&sub_5851D0);
	PatchFunction(0x585290, (DWORD)&sub_585290);
	PatchFunction(0x585AB0, (DWORD)&sub_585AB0);
	PatchFunction(0x586330, (DWORD)&sub_586330);
	PatchFunction(0x586660, (DWORD)&sub_586660);
	PatchFunction(0x586900, (DWORD)&sub_586900);
	PatchFunction(0x586FA0, (DWORD)&sub_586FA0);
	PatchFunction(0x5871E0, (DWORD)&sub_5871E0);
	
	PatchFunction(0x944E46, (DWORD)&our_malloc);
}
