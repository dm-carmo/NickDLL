#include <Windows.h>
#include "generic_functions.h"
#include "Structures\CMHeader.h"
#include "Helper.h"
#include "constants.h"


// Generic function that will add teams to a league competition
int AddTeams(BYTE* _this)
{
	DWORD CompID = *(DWORD*)(*(DWORD*)(_this + 0x4));

	// Count the number of teams first, as the code really expects us to know up front
	BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);

	// Now let's add the teams
	*((WORD*)(_this + 0x3E)) = numberOfLeagueTeams; // number of teams
	*((DWORD*)(_this + 0xB1)) = (DWORD)sub_944E46_malloc(numberOfLeagueTeams * league_team_list_sz); // number of teams * 59 (0x3B) - was 0x2FF
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == CompID)
			add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}


// Generic function that will add teams to a league competition that has groups
int AddTeamsGroupLeague(BYTE* _this, DWORD first_group_id)
{
	DWORD CompID = *(DWORD*)(*(DWORD*)(_this + 0x4));

	// Count the number of teams first, as the code really expects us to know up front
	BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInCompWithGroup(CompID, first_group_id);

	// Now let's add the teams
	*((WORD*)(_this + 0x3E)) = numberOfLeagueTeams; // number of teams
	*((DWORD*)(_this + 0xB1)) = (DWORD)sub_944E46_malloc(numberOfLeagueTeams * league_team_list_sz); // number of teams * 59 (0x3B) - was 0x2FF
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == CompID
			&& club->ClubReserveDivision && club->ClubReserveDivision->ClubCompID == first_group_id)
			add_team_call(_this, teamsAdded++, club, 0, 0);
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

// Creates a fixture block with the specified data
void AddFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_fixture_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, timeOfDay, startYear, stadiumType);
}

// Creates a block with the specified data, that defines days to move matches for TV
void AddFixtureTV(BYTE* pMem, int fixture, int tv_id, int num_to_move, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_fixture_tv_days_call(pMem, fixture, tv_id, dayOfWeek, timeOfDay, num_to_move, stadiumType);
}

// Creates a fixture block with the specified data, with a shortcut to add a TV days block with nothing defined
void AddFixtureNoTV(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_fixture_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, timeOfDay, startYear, stadiumType);
	add_fixture_tv_days_call(pMem, fixture, 0, -1, -1, -1, 0);
}

// Creates a cup/playoff fixture block with the specified data
void AddPlayoffFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */, int timeOfDay, int stadiumType)
{
	add_playoff_fixture_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, timeOfDay, startYear, stadiumType);
}

// Creates a cup/playoff draw date block with the specified data
void AddPlayoffDrawFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek /* Mon = 0 */)
{
	add_playoff_draw_date_call(pMem, fixture, date.getDay(), date.getMonth() - 1, date.getYear() - startYear, dayOfWeek, startYear);
}

// Fills in details for cup/playoff fixtures, based on this information: https://champman0102.net/viewtopic.php?p=16076#p16076
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
	*(DWORD*)(pMem + (fixture * playoff_dates_sz) + 0x5C) = prize_reach;
	*(DWORD*)(pMem + (fixture * playoff_dates_sz) + 0x60) = prize_win;
	*(DWORD*)(pMem + (fixture * playoff_dates_sz) + 0x64) = prize_lose;
}

// Not part of the Tapani patches but one of the hooks needed to call our relegation code. Standard B0 in vtable for relegation/promotion
static int(*sub_689C80_2)() = (int(*)())(0x689C80);
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
	/*00689C60*/	call sub_689C80_2		/*call <cm0102.sub_689C80>*/
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


void WriteVTablePtr(DWORD* addr, int pos, DWORD data) {
	WriteDWORD((DWORD)addr + 4 * (pos - 1), data);
}