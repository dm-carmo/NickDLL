#pragma warning (disable : 4733)
#include <windows.h>
#include "generic_functions.h"
#include "constants.h"

static int(*sub_49EE70)() = (int(*)())(0x49EE70);
static int(*sub_577020)() = (int(*)())(0x577020);
static int(*sub_577F70)() = (int(*)())(0x577F70);
static int(*sub_5780C0)() = (int(*)())(0x5780C0);
static int(*sub_5E8290)() = (int(*)())(0x5E8290);
static int(*sub_682200)() = (int(*)())(0x682200);
static int(*sub_6827D0)() = (int(*)())(0x6827D0);
static int(*sub_6835C0)() = (int(*)())(0x6835C0);
static int(*sub_687B10)() = (int(*)())(0x687B10);
static int(*sub_68A850)() = (int(*)())(0x68A850);
static int(*sub_90D130)() = (int(*)())(0x90D130);
static int(*sub_944C94)() = (int(*)())(0x944C94);
static int(*sub_944C9F)() = (int(*)())(0x944C9F);
static int(*sub_944CF1)() = (int(*)())(0x944CF1);
static int(*sub_944CFF)() = (int(*)())(0x944CFF);
static int(*sub_944E46)() = (int(*)())(0x944E46);
static int(*sub_9452CA)() = (int(*)())(0x9452CA);

int __fastcall eng_conf_subs(BYTE* _this);		// We cheat with a fastcall here (as the one and only param will be passed as ecx). It's really a __thiscall.

int __fastcall eng_conf_subs(BYTE* _this)				// 0x8C
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;
	dprintf("eng_conf_subs - CompID: %08X\n", CompID);

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->tiebreaker_1 = 1;
	comp_data->tiebreaker_2 = 2;
	comp_data->tiebreaker_3 = 3;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 6;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 4;

	comp_data->promotes_to = *(DWORD*)0x9CF5C8;
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->max_bench = 5;
	comp_data->max_subs = 3;

	//call vtable +3C which is actually add fixtures function
	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return 1;
}

void __declspec(naked) eng_conf_init()
{
	__asm
	{
		pushad
		//call eng_third_init_additional
		popad

		/*00576DE5*/	sub esp, 0x214
		/*00576DEB*/	push ebx
		/*00576DEC*/	push esi
		/*00576DED*/	mov esi, ecx
		/*00576DEF*/	mov dword ptr ss : [esp + 0xC] , esi
		/*00576DF3*/	call sub_682200		/*call cm0102.682200*/
		/*00576DF8*/	mov ecx, dword ptr ss : [esp + 0x224]
		/*00576DFF*/	mov ax, word ptr ss : [esp + 0x220]
		/*00576E07*/ xor ebx, ebx
		/*00576E09*/	mov dword ptr ds : [esi + 0x4] , ecx
		/*00576E0C*/	push 0x1
		/*00576E0E*/	mov ecx, esi
		/*00576E10*/	mov dword ptr ss : [esp + 0x21C] , ebx
		/*00576E17*/	mov dword ptr ds : [esi] , 0x969A74		/*mov dword ptr ds:[esi],cm0102.969E84*/

		/*push eax
		mov eax, dword ptr[vtable_eng_third.vtable_ptr]
		mov dword ptr ds : [esi] , eax
		pop eax*/

		/*00576E1D*/	mov word ptr ds : [esi + 0x40] , ax
		/*00576E21*/	//mov word ptr ds : [esi + 0xE2] , 0x1770
		/*00576E2A*/	//mov word ptr ds : [esi + 0xE4] , 0x3E8
		/*00576E33*/	mov byte ptr ds : [esi + 0x50] , 0x9
		/*00576E37*/	call sub_687B10		/*call cm0102.687B10*/
		/*00576E3C*/	test eax, eax
		/*00576E3E*/	jne _00576FE3
		/*00576E44*/ or eax, 0xFFFFFFFF
		/*00576E47*/	push 0x4
		/*00576E49*/	mov byte ptr ds : [esi + 0x44] , al
		/*00576E4C*/	mov dword ptr ds : [esi + 0x30] , eax
		/*00576E4F*/	mov dword ptr ds : [esi + 0x2C] , 0x1
		/*00576E56*/	call sub_944E46_malloc		/*call cm0102.944E46*/
		/*00576E5B*/	add esp, 0x4
		/*00576E5E*/	mov ecx, esi
		/*00576E60*/	mov dword ptr ds : [esi + 0xC] , eax
		/*00576E63*/	call eng_conf_subs		/*call cm0102.5780C0*/	// +0x8C
		/*00576E68*/	test eax, eax
		/*00576E6A*/	jne _00576E9C
		/*00576E6C*/	lea edx, dword ptr ss : [esp + 0x10]
		/*00576E70*/	lea eax, dword ptr ss : [esp + 0x110]
		/*00576E77*/	push edx
		/*00576E78*/	push eax
		/*00576E79*/	push ebx
		/*00576E7A*/	push ebx
		/*00576E7B*/	push 0x9C4424		/*push cm0102.9C4424*/
		/*00576E80*/	call sub_944CFF_splitpath		/*call cm0102.944CFF*/
		/*00576E85*/	add esp, 0x14
		/*00576E88*/	lea ecx, dword ptr ss : [esp + 0x10]
		/*00576E8C*/	lea edx, dword ptr ss : [esp + 0x110]
		/*00576E93*/	push 0x4E
		/*00576E95*/	push ecx
		/*00576E96*/	push edx
		/*00576E97*/	jmp _00576FAC
		_00576E9C :
		/*00576E9C*/	mov ecx, esi
			/*00576E9E*/	// call sub_577F70_add_teams		/*call cm0102.577F70*/

			push ecx
			call AddTeams
			add esp, 0x4

			/*00576EA3*/	test eax, eax
			/*00576EA5*/	jne _00576ED6
			/*00576EA7*/	lea eax, dword ptr ss : [esp + 0x110]
			/*00576EAE*/	lea ecx, dword ptr ss : [esp + 0x10]
			/*00576EB2*/	push eax
			/*00576EB3*/	push ecx
			/*00576EB4*/	push ebx
			/*00576EB5*/	push ebx
			/*00576EB6*/	push 0x9C4424		/*push cm0102.9C4424*/
			/*00576EBB*/	call sub_944CFF_splitpath		/*call cm0102.944CFF*/
			/*00576EC0*/	add esp, 0x14
			/*00576EC3*/	lea edx, dword ptr ss : [esp + 0x110]
			/*00576ECA*/	lea eax, dword ptr ss : [esp + 0x10]
			/*00576ECE*/	push 0x55
			/*00576ED0*/	push edx
			/*00576ED1*/	jmp _00576FAB
			_00576ED6 :
		/*00576ED6*/	mov ecx, esi
			/*00576ED8*/	call sub_6835C0		/*call cm0102.6835C0*/
			/*00576EDD*/	test eax, eax
			/*00576EDF*/	jne _00576F11
			/*00576EE1*/	lea ecx, dword ptr ss : [esp + 0x110]
			/*00576EE8*/	lea edx, dword ptr ss : [esp + 0x10]
			/*00576EEC*/	push ecx
			/*00576EED*/	push edx
			/*00576EEE*/	push ebx
			/*00576EEF*/	push ebx
			/*00576EF0*/	push 0x9C4424		/*push cm0102.9C4424*/
			/*00576EF5*/	call sub_944CFF_splitpath		/*call cm0102.944CFF*/
			/*00576EFA*/	add esp, 0x14
			/*00576EFD*/	lea eax, dword ptr ss : [esp + 0x110]
			/*00576F04*/	lea ecx, dword ptr ss : [esp + 0x10]
			/*00576F08*/	push 0x5C
			/*00576F0A*/	push eax
			/*00576F0B*/	push ecx
			/*00576F0C*/	jmp _00576FAC
			_00576F11 :
		/*00576F11*/	push ebx
			/*00576F12*/	mov ecx, esi
			/*00576F14*/	call sub_6827D0		/*call cm0102.6827D0*/
			/*00576F19*/	test eax, eax
			/*00576F1B*/	jne _00576F4A
			/*00576F1D*/	lea edx, dword ptr ss : [esp + 0x110]
			/*00576F24*/	lea eax, dword ptr ss : [esp + 0x10]
			/*00576F28*/	push edx
			/*00576F29*/	push eax
			/*00576F2A*/	push ebx
			/*00576F2B*/	push ebx
			/*00576F2C*/	push 0x9C4424		/*push cm0102.9C4424*/
			/*00576F31*/	call sub_944CFF_splitpath		/*call cm0102.944CFF*/
			/*00576F36*/	add esp, 0x14
			/*00576F39*/	lea ecx, dword ptr ss : [esp + 0x110]
			/*00576F40*/	lea edx, dword ptr ss : [esp + 0x10]
			/*00576F44*/	push 0x65
			/*00576F46*/	push ecx
			/*00576F47*/	push edx
			/*00576F48*/	jmp _00576FAC
			_00576F4A :
		/*00576F4A*/	push 0x5CE
			/*00576F4F*/	call sub_944CF1		/*call cm0102.944CF1*/
			/*00576F54*/	add esp, 0x4
			/*00576F57*/	mov dword ptr ss : [esp + 0x8] , eax
			/*00576F5B*/	cmp eax, ebx
			/*00576F5D*/	mov byte ptr ss : [esp + 0x218] , 0x1
			/*00576F65*/	je _00576F71
			/*00576F67*/	push esi
			/*00576F68*/	mov ecx, eax
			/*00576F6A*/	call sub_49EE70		/*call cm0102.49EE70*/
			/*00576F6F*/	jmp _00576F73
			_00576F71 :
		/*00576F71*/ xor eax, eax
			_00576F73 :
		/*00576F73*/	cmp eax, ebx
			/*00576F75*/	mov byte ptr ss : [esp + 0x218] , bl
			/*00576F7C*/	mov dword ptr ds : [esi + 0x8] , eax
			/*00576F7F*/	jne _00576FDC
			/*00576F81*/	lea eax, dword ptr ss : [esp + 0x110]
			/*00576F88*/	lea ecx, dword ptr ss : [esp + 0x10]
			/*00576F8C*/	push eax
			/*00576F8D*/	push ecx
			/*00576F8E*/	push ebx
			/*00576F8F*/	push ebx
			/*00576F90*/	push 0x9C4424		/*push cm0102.9C4424*/
			/*00576F95*/	call sub_944CFF_splitpath		/*call cm0102.944CFF*/
			/*00576F9A*/	add esp, 0x14
			/*00576F9D*/	lea edx, dword ptr ss : [esp + 0x110]
			/*00576FA4*/	lea eax, dword ptr ss : [esp + 0x10]
			/*00576FA8*/	push 0x6D
			/*00576FAA*/	push edx
			_00576FAB :
		/*00576FAB*/	push eax
			_00576FAC :
		/*00576FAC*/	call sub_90D130		/*call cm0102.90D130*/
			/*00576FB1*/	push eax
			/*00576FB2*/	push 0x9870E8		/*push cm0102.9870E8*/
			/*00576FB7*/	push 0xAE24D0		/*push cm0102.AE24D0*/
			/*00576FBC*/	call sub_944C9F_sprintf		/*call cm0102.944C9F*/
			/*00576FC1*/	push ebx
			/*00576FC2*/	push 0xAE24D0		/*push cm0102.AE24D0*/
			/*00576FC7*/	push 0x9870E0		/*push cm0102.9870E0*/
			/*00576FCC*/	call sub_5E8290		/*call cm0102.5E8290*/
			/*00576FD1*/	add esp, 0x24
			/*00576FD4*/	mov dword ptr ds : [0xB67A34] , ebx
			/*00576FDA*/	jmp _00576FE3
			_00576FDC :
		/*00576FDC*/	mov ecx, esi
			/*00576FDE*/	call sub_68A850		/*call cm0102.68A850*/
			_00576FE3 :
		/*00576FEA*/	mov eax, esi
			/*00576FEC*/	pop esi
			/*00576FED*/	pop ebx
			/*00576FF5*/	add esp, 0x214
			/*00576FFB*/	ret 0x8
	}
}

void create_playoffs_c_under(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = comp_data->prom_playoff;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	int j = 0;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams && j < playoff_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[playoff_teams - j - 1])) = (DWORD)tls.club;
			j++;
		}
	}
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, *(DWORD*)(_this + 0x4), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num * 4])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void create_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) create_playoffs_c_under(_this);
	}
}

void __declspec(naked) eng_playoffs_create()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call create_playoffs_c
		add esp, 0x4
		ret
	}
}

DWORD CreateConferenceFixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 0) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		DWORD CompID = *(DWORD*)(*(DWORD*)(_this + 0x4));
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * ((comp_stats*)_this)->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 16), year, Saturday);
		if (*num_rounds == 46) AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 20), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 23), year, Saturday);
		if (*num_rounds == 46) AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 25), year, Monday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 3), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 24), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 1), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 5), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 15), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 26), year, Friday, Evening); // change to always be 26/12?
		if (*num_rounds == 46) AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 30), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 21), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 11), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 25), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 25), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 3), year, Friday, Evening); // change to always be Good Friday?
		if (*num_rounds == 46) AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 6), year, Monday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);

		return (DWORD)pMem;
	}
	else {
		if (stage_idx != 0) return 0;

		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = Playoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 5, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 6), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 5, 4, 2, 2, 4, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 7), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 0, 2, 1, 0, 0, 0, 1, 0, 0);

		return (DWORD)pMem;
	}
	return 0;
}

int ConferenceTableIndicators(BYTE* _this, DWORD* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	if (stage != -1) {
		comp_stats* comp_data = (comp_stats*)_this;
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[0]);
		BYTE* rounds = stage_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		for (int i = 0; i < num_teams; i++) {
			DWORD* c = (DWORD*)table[i].club;
			if (c != club) continue;
			switch (fate) {
			case TopPlayoff:
				add_staff_history_promotion(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), 0x32);
				table[i].league_fate = Promoted;
				*a5 = 1;
				return 0;
			case Promoted:
				add_staff_history_qualified(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
				return 0;
			case NoFate:
				table[i].league_fate = Eliminated;
				return 0;
			case BottomPlayoff:
				table[i].league_fate = Eliminated;
				return 0;
			default:
				return 0;
			}
		}
	}
	else {
		switch (fate) {
		case Champions:
			add_staff_history_champions(staff_hist_ptr, club, *(DWORD*)(_this + 0x4));
			return 0;
		case Promoted:
			add_staff_history_promotion(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), 0x64);
			return 0;
		case TopPlayoff:
			add_staff_history_qualified(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), Playoff, None, 0x1E);
			return 0;
		case Relegated:
			add_staff_history_relegated(staff_hist_ptr, club, *(DWORD*)(_this + 0x4));
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}


void __declspec(naked) eng_conf_set_table_fate()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ConferenceTableIndicators
		add esp, 0x1c
		ret 0x18
	}
}

void __declspec(naked) eng_conf_fixtures()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call CreateConferenceFixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_eng_conf() {
	PatchFunction(0x56db60, (DWORD)&eng_conf_init);
	WriteFuncPtr(0x969A74, 11, (DWORD)&eng_playoffs_create);
	WriteFuncPtr(0x969A74, 16, (DWORD)&eng_conf_fixtures);
	WriteFuncPtr(0x969A74, 18, (DWORD)&eng_conf_set_table_fate);
}