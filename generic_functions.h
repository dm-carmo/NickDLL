#pragma once
#include <Windows.h>
#include "CMHeader.h"
#include "Helper.h"
#include "Date.h"

static int(*convert_to_cm_date)() = (int(*)())(0x549F70);

static int(*add_fixture_date_call)(BYTE* a1, __int16 a2, __int16 a3, unsigned __int8 a4, __int16 a5, int a6, char a7, __int16 a8, int a9) =
(int(*)(BYTE * a1, __int16 a2, __int16 a3, unsigned __int8 a4, __int16 a5, int a6, char a7, __int16 a8, int a9))(0x68A160);
static int(*add_fixture_tv_days_call)(BYTE* a1, __int16 a2, unsigned __int16 a3, __int16 a4, char a5, char a6, int a7) =
(int(*)(BYTE * a1, __int16 a2, unsigned __int16 a3, __int16 a4, char a5, char a6, int a7))(0x68A1C0);

static int(*add_playoff_draw_date_call)(BYTE* a1, __int16 a2, __int16 a3, BYTE a4, __int16 a5, int a6, __int16 a7) =
(int(*)(BYTE * a1, __int16 a2, __int16 a3, unsigned __int8 a4, __int16 a5, int a6, __int16 a7))(0x521E60);
static int(*add_playoff_fixture_date_call)(BYTE* a1, __int16 a2, __int16 a3, BYTE a4, __int16 a5, int a6, char a7, __int16 a8, int a9) =
(int(*)(BYTE * a1, __int16 a2, __int16 a3, unsigned __int8 a4, __int16 a5, int a6, char a7, __int16 a8, int a9))(0x521EB0);

static int   (*sub_944C9F_sprintf)() = (int(*)())(0x944C9F);
static void* (*sub_944CF1_operator_new)(int size) = (void* (*)(int size))(0x944CF1);
static int   (*sub_944CFF_splitpath)() = (int(*)())(0x944CFF);
static void* (*sub_944E46_malloc)(int size) = (void* (*)(int size))(0x944E46);
static void* (*sub_945501_alloc)(int size, int a2) = (void* (*)(int size, int a2))(0x945501);

static int(__thiscall* add_team_call)(BYTE* _this, BYTE teamNo, cm3_clubs* club, BYTE a3, DWORD* a4) =
(int(__thiscall*)(BYTE * _this, BYTE teamNo, cm3_clubs * club, BYTE a3, DWORD * a4))(0x687430);

int AddTeams(BYTE* _this);
void AddLeague(BYTE* _this, const char* szLeagueName, int leagueNo, int year, DWORD league_init_addr);
void sub_689C20_relegation_hook();

void AddFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek, int timeOfDay = 1, int stadiumType = 0);
void AddFixtureTV(BYTE* pMem, int fixture, int tv_id = 0, int num_to_move = -1, Day dayOfWeek = DontCare, int timeOfDay = -1, int stadiumType = 0);
void AddFixtureNoTV(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek, int timeOfDay = 1, int stadiumType = 0);
void AddPlayoffFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek, int timeOfDay = 1, int stadiumType = 0);
void AddPlayoffDrawFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek);
void FillFixtureDetails(BYTE* pMem, int fixture, WORD stage_name, WORD draw_type, WORD game_1_tiebreak, WORD game_2_tiebreak,
	BYTE unk17, WORD teams_in_round, WORD num_games, WORD new_teams_in_round, WORD total_teams_in, BYTE replays, BYTE legs, BYTE days_between_games,
	DWORD prize_reach = 0, DWORD prize_win = 0, DWORD prize_lose = 0, WORD game_3_tiebreak = 0);
void WriteFuncPtr(DWORD addr, int pos, DWORD data);