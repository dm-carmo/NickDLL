#include <Windows.h>
#include "generic_functions.h"
#include "CMHeader.h"
#include "Helper.h"
#include "constants.h"


int AddTeams(BYTE* _this)
{
	DWORD CompID = *(DWORD*)(*(DWORD*)(_this + 0x4));

	// Count the number of teams first, as the code really expects us to know up front
	BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);

	// Now let's add the teams
	*((WORD*)(_this + 0x3E)) = numberOfLeagueTeams; // number of teams
	*((DWORD*)(_this + 0xB1)) = (DWORD)sub_944E46_malloc(numberOfLeagueTeams * 59); // number of teams * 59 (0x3B) - was 0x2FF
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == CompID)
			sub_687430_add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}


typedef BYTE*(__thiscall*league_init_typedef)(BYTE* _this, __int16 a2, cm3_club_comps* a3);
void AddLeague(BYTE* _this, const char* szLeagueName, int leagueNo, int year, DWORD league_init_addr)
{
	dprintf("Adding (This: %08X) league %s at slot %d for year %d (calling init addr: %08X).\n", (DWORD)_this, szLeagueName, leagueNo, (short)year, league_init_addr);
	cm3_club_comps* comp = find_club_comp(szLeagueName);
	if (comp)
	{
		BYTE* ee_bytes = (BYTE*)sub_944CF1_operator_new(0xEE);
		league_init_typedef init_call = (league_init_typedef)(league_init_addr);
		BYTE* leagueSetupPtr = init_call(ee_bytes, (short)*current_year, comp);
		DWORD* compPtrTable = *(DWORD**)(_this + 0x10);
		compPtrTable[leagueNo] = (DWORD)leagueSetupPtr;
	}
	else
		dprintf("Could not find comp %s!", szLeagueName);
}

void AddFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_fixture_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, timeOfDay, startYear, stadiumType);
}

void AddFixtureNoTV(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_fixture_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, timeOfDay, startYear, stadiumType);
	add_fixture_tv_days_call(pMem, fixture, 0, -1, -1, -1, 0);
}

void AddPlayoffFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_playoff_fixture_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, timeOfDay, startYear, stadiumType);
}

void AddPlayoffDrawFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */)
{
	add_playoff_draw_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, startYear);
}

void FillFixtureDetails(BYTE* pMem, int fixture, WORD stage_name, WORD draw_type, WORD game_1_tiebreak, WORD game_2_tiebreak, BYTE unk17, WORD teams_in_round, 
	WORD num_games, WORD new_teams_in_round, WORD total_teams_in, BYTE replays, BYTE legs, BYTE days_between_games, 
	DWORD prize_reach, DWORD prize_win, DWORD prize_lose, WORD game_3_tiebreak)
{
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x7) = stage_name;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x9) = fixture;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0xB) = draw_type;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0xD) = game_1_tiebreak;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0xF) = game_2_tiebreak;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x11) = game_3_tiebreak;
	*(BYTE*)(pMem + (fixture * playoff_dates_sz) + 0x17) = unk17;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x18) = teams_in_round;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x1A) = num_games;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x1C) = new_teams_in_round;
	*(WORD*)(pMem + (fixture * playoff_dates_sz) + 0x1E) = total_teams_in;
	*(BYTE*)(pMem + (fixture * playoff_dates_sz) + 0x20) = replays;
	*(BYTE*)(pMem + (fixture * playoff_dates_sz) + 0x21) = legs;
	*(BYTE*)(pMem + (fixture * playoff_dates_sz) + 0x22) = days_between_games;
	*((DWORD*)pMem + (fixture * playoff_dates_sz) + 0x5C) = prize_reach;
	*((DWORD*)pMem + (fixture * playoff_dates_sz) + 0x60) = prize_win;
	*((DWORD*)pMem + (fixture * playoff_dates_sz) + 0x64) = prize_lose;
}

DWORD AddEng24TeamFixturesWithPlayoffs(BYTE* _this, BYTE stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	dprintf("add_eng_24team_fixtures_with_playoffs called with this=%08X stage_idx=%02X, num_rounds=%08X, stage_name_id=%08X, a5=%08X\n", _this, stage_idx, num_rounds, stage_name_id, a5);

	DWORD CompID = *(DWORD*)*((DWORD*)(_this + 4));
	const char *szCompName = (const char *)(*((DWORD*)(_this + 4))+4);
	int team_count = CountNumberOfTeamsInComp(CompID);
	dprintf("CompID: %08X Name: %s Team Count: %d\n", CompID, szCompName, team_count);

	if (stage_idx == 0xFF)	// -1
	{
		if (a5)
			*a5 = 1;
		*num_rounds = (team_count - 1) * 2;		// Number of Fixtures = 0x22 (34 i.e. (number of teams - 1) * 2) 18 in ser c1/a (23 in nothern prem) (eng third: 24)
		*stage_name_id = 0;
		BYTE* pMem = (BYTE*)sub_944E46_malloc((*num_rounds) * 65);	// Allocate memory for fixtures
		WORD year = *(WORD*)(_this + 0x40);

		int fixture = 0;

		AddFixtureNoTV(pMem, fixture++, Date(year, 8, 12), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 8, 19), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 8, 26), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 8, 28), year, Monday, 2);
		AddFixtureNoTV(pMem, fixture++, Date(year, 9, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 9, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 9, 13), year, Wednesday, 2);
		AddFixtureNoTV(pMem, fixture++, Date(year, 9, 16), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 9, 23), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 9, 30), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 10, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 10, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 10, 17), year, Tuesday, 2);
		AddFixtureNoTV(pMem, fixture++, Date(year, 10, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 10, 24), year, Tuesday, 2);
		AddFixtureNoTV(pMem, fixture++, Date(year, 10, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 11, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 11, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 11, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 11, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 12, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 12, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year, 12, 16), year, Saturday);

		Date FirstDec(year, 12, 1);
		Date Dec16(year, 12, 16);
		int dayDiff = Dec16.DayOfYear() - FirstDec.DayOfYear();

		dprintf("dayDiff: %d\n", dayDiff);
		switch (dayDiff)
		{
		case 12:
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 20), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 27), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 30), year, DontCare, 2);
			AddFixtureNoTV(pMem, fixture++, Date(year + 1, 1, 3), year, DontCare);
			break;
		case 13:
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 21), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 26), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 28), year, DontCare, 2);
			AddFixtureNoTV(pMem, fixture++, Date(year + 1, 1, 1), year, DontCare);
			break;
		case 14:
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 22), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 26), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 29), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year + 1, 1, 1), year, DontCare);
			break;
		case 15:
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 23), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 26), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 30), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year + 1, 1, 1), year, DontCare);
			break;
		case 16:
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 21), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 26), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 31), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year + 1, 1, 4), year, DontCare);
			break;
		case 17:
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 22), year, DontCare, 2);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 26), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 28), year, DontCare, 2);
			AddFixtureNoTV(pMem, fixture++, Date(year + 1, 1, 4), year, DontCare);
			break;
		default:
		case 18:
			if (dayDiff != 18)
				dprintf("SOMETHING WENT WRONG WITH DAY DIFF!!!\n");
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 26), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year, 12, 28), year, DontCare, 2);
			AddFixtureNoTV(pMem, fixture++, Date(year + 1, 1, 2), year, DontCare);
			AddFixtureNoTV(pMem, fixture++, Date(year + 1, 1, 5), year, DontCare);
			break;
		}

		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 1, 12), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 1, 20), year, Saturday);

		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 2, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 2, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 2, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 2, 20), year, Tuesday, 2);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 2, 24), year, Saturday);

		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 3, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 3, 7), year, Tuesday, 2);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 3, 10), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 3, 17), year, Monday, 2);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 3, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 3, 31), year, Saturday);

		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 4, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 4, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 4, 16), year, Monday, 2);
		AddFixtureNoTV(pMem, fixture++, Date(year + 1, 4, 21), year, Saturday);
		

		if (team_count >= 24)
		{
			AddFixtureNoTV(pMem, fixture++, Date(year + 1, 4, 28), year, Saturday);
			AddFixtureNoTV(pMem, fixture++, Date(year + 1, 5, 4), year, Sunday);
		}

		dprintf("fixtures added: %d\n", fixture - 1);

		return (DWORD)pMem;
	}
	else
	{
		BYTE playOffPlaces = _this[0xBF];
		dprintf("Playoff Places: %d\n", playOffPlaces);

		if (stage_idx != 0)
			return 0;
		if (a5)
			*a5 = 0;

		BYTE* pMem = NULL;
		WORD year = *(WORD*)(_this + 0x40);

		if (playOffPlaces == 4)
		{
			*num_rounds = 2;
			*stage_name_id = 160;

			pMem = (BYTE*)sub_944E46_malloc(104 * (*num_rounds));

			add_playoff_draw_date_call(pMem, 0, 7, 4, 1, 0, year);
			add_playoff_fixture_date_call(pMem, 0, 12, 4, 1, 5, 1, year, 0);
			*(WORD*)(pMem + 0x7) = 0x82;		// *10
			*(WORD*)(pMem + 0x9) = 0x0;
			*(WORD*)(pMem + 0xB) = 0x0;
			*(WORD*)(pMem + 0xD) = 0x204;		
			*(BYTE*)(pMem + 0x17) = 0x5;
			*((WORD*)pMem + 0xC) = 0x4;
			*(WORD*)(pMem + 0x1A) = 0x2;
			*(WORD*)(pMem + 0x1C) = 0x4;
			*(WORD*)(pMem + 0xF) = 0x3;
			*(WORD*)(pMem + 0x1E) = 0x0;
			*(BYTE*)(pMem + 0x20) = 0x0;
			*(BYTE*)(pMem + 0x21) = 0x2;		
			*(BYTE*)(pMem + 0x22) = 0x4;
			*((DWORD*)pMem + 0x17) = 0x0;
			*((DWORD*)pMem + 0x18) = 0x0;
			*((DWORD*)pMem + 0x19) = 0x0;

			add_playoff_draw_date_call(pMem, 1, 17, 4, 1, 3, year);
			add_playoff_fixture_date_call(pMem, 1, 26, 4, 1, 5, 1, year, 4);
			*(WORD*)(pMem + 113) = 1;
			*(WORD*)(pMem + 130) = 1;
			*(WORD*)(pMem + 111) = 150;
			*(WORD*)(pMem + 115) = 0;
			*(WORD*)(pMem + 117) = 3;
			*(BYTE*)(pMem + 127) = 5;
			*(WORD*)(pMem + 128) = 2;
			*(WORD*)(pMem + 132) = 0;
			*(WORD*)(pMem + 119) = 0;
			*(WORD*)(pMem + 134) = 0;
			*(BYTE*)(pMem + 136) = 0;
			*(BYTE*)(pMem + 137) = 1;
			*(BYTE*)(pMem + 138) = 0;
			*((DWORD*)pMem + 49) = 0;
			*((DWORD*)pMem + 50) = 0;
			*((DWORD*)pMem + 51) = 0;
		}

		if (playOffPlaces == 6)
		{
			*num_rounds = 3;
			*stage_name_id = 160;
			pMem = (BYTE*)sub_944E46_malloc(104 * (*num_rounds));

			add_playoff_draw_date_call(pMem, 0, 3, 4, 1, 0, year);
			add_playoff_fixture_date_call(pMem, 0, 5, 4, 1, 2, 2, year, 0);
			*(WORD*)(pMem + 7) = 0x78;
			*(WORD*)(pMem + 9) = 0;
			*(WORD*)(pMem + 11) = 0;
			*(WORD*)(pMem + 13) = 0x203;
			pMem[23] = 5;
			*((WORD*)pMem + 12) = 4;
			*((WORD*)pMem + 13) = 2;
			*((WORD*)pMem + 14) = 4;
			*(WORD*)(pMem + 15) = 3;
			*((WORD*)pMem + 15) = 0;
			pMem[32] = 0;
			pMem[33] = 1;
			pMem[34] = 4;
			*((DWORD*)pMem + 23) = 0;
			*((DWORD*)pMem + 24) = 0;
			*((DWORD*)pMem + 25) = 0;

			add_playoff_draw_date_call(pMem, 1, 6, 4, 1, 3, year);
			add_playoff_fixture_date_call(pMem, 1, 8, 4, 1, 5, 1, year, 0);
			*(WORD*)(pMem + 104 + 7) = 0x82;
			*(WORD*)(pMem + 104 + 9) = 1;
			*(WORD*)(pMem + 104 + 11) = 0;
			*(WORD*)(pMem + 104 + 13) = 0x403;
			pMem[127] = 5;
			*((WORD*)pMem + (104/2) + 12) = 4;
			*((WORD*)pMem + (104/2) + 13) = 2;
			*((WORD*)pMem + (104/2) + 14) = 2;
			*(WORD*)(pMem + 104 + 15) = 3;
			*((WORD*)pMem + (104/2) + 15) = 4;
			*(DWORD*)(pMem + 135) = 0x1010000;
			*((DWORD*)pMem + 49) = 0;
			*((DWORD*)pMem + 50) = 0;
			*((DWORD*)pMem + 51) = 0;

			add_playoff_draw_date_call(pMem, 2, 9, 4, 1, 6, year);
			add_playoff_fixture_date_call(pMem, 2, 15, 4, 1, 5, 1, year, 4);
			*(WORD*)(pMem + 217) = 2;
			*((WORD*)pMem + 116) = 2;
			*((WORD*)pMem + 117) = 1;
			*((WORD*)pMem + 118) = 0;
			*(WORD*)(pMem + 215) = 0x96;
			*(WORD*)(pMem + 219) = 0;
			*(WORD*)(pMem + 221) = 3;
			pMem[231] = 5;
			*(WORD*)(pMem + 223) = 0;
			*((WORD*)pMem + 119) = 6;
			pMem[240] = 0;
			pMem[241] = 1;
			pMem[242] = 0;
			*((DWORD*)pMem + 75) = 0;
			*((DWORD*)pMem + 76) = 0;
			*((DWORD*)pMem + 77) = 0;
		}

		return (DWORD)pMem;
	}
	return 0;
}

// Not part of the Tapani patches but one of the hooks needed to call our relegation code. Standard B0 in vtable for relegation/promotion
static int(*sub_689C80)() = (int(*)())(0x689C80);
void sub_601FF0();
void __declspec(naked) sub_689C20_relegation_hook()
{
	__asm
	{
	/*00689C20*/	push ebx
	/*00689C21*/	mov ebx,ecx
	/*00689C23*/	push edi
	/*00689C24*/	mov eax,dword ptr ds:[ebx+0x1C]
	/*00689C27*/	test eax,eax
	/*00689C29*/	jge _00689C73
	/*00689C2B*/	mov eax,dword ptr ds:[ebx]
	/*00689C2D*/	mov edi,ebx
	/*00689C2F*/	call dword ptr ds:[eax+0xA4]
	/*00689C35*/	mov eax,dword ptr ds:[ebx+0x20]
	/*00689C38*/	test eax,eax
	/*00689C3A*/	jl _00689C73
	/*00689C3C*/	push ebp
	/*00689C3D*/	mov ebp,dword ptr ss:[esp+0x10]
	/*00689C41*/	push esi
_00689C42:
	/*00689C42*/	mov ecx,dword ptr ds:[0xADADFC]
	/*00689C48*/	mov esi,dword ptr ds:[ecx+eax*0x4]
	/*00689C4B*/	mov ecx,esi
	/*00689C4D*/	mov edx,dword ptr ds:[esi]
	/*00689C4F*/	call dword ptr ds:[edx+0xA4]
	/*00689C55*/	push 0xFFFFFFFF
	/*00689C57*/	push 0xFFFFFFFF
	/*00689C59*/	push ebp
	/*00689C5A*/	push 0x1
	/*00689C5C*/	push esi
	/*00689C5D*/	push edi
	/*00689C5E*/	mov ecx,ebx
	/*00689C60*/	call sub_689C80		/*call <cm0102.sub_689C80>*/
	/*00689C65*/	mov eax,dword ptr ds:[esi+0x20]
	/*00689C68*/	mov edi,esi
	/*00689C6A*/	test eax,eax
	/*00689C6C*/	jge _00689C42
	/*00689C6E*/	call sub_601FF0		/*call <cm0102.sub_601FF0>*/		// <---- additional call added by Tapani
_00689C73:
	/*00689C73*/	pop esi
	/*00689C74*/	pop ebp
	/*00689C75*/	pop edi
	/*00689C76*/	pop ebx
	/*00689C77*/	ret 0x4
	}
}


void WriteFuncPtr(DWORD addr, int pos, DWORD data) {
	WriteDWORD(addr + 4 * (pos - 1), data);
}