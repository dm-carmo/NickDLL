#pragma once
#include <Windows.h>
#include "Structures\CMHeader.h"
#include "Helper.h"
#include "Structures\Date.h"

static int(__thiscall* convert_to_cm_date)(BYTE* _this, WORD day, BYTE month, WORD year, DWORD* a5) =
(int(__thiscall*)(BYTE * _this, WORD day, BYTE month, WORD year, DWORD * a5))(0x549F70);

static int(*add_fixture_date_call)(BYTE* a1, __int16 a2, __int16 a3, unsigned __int8 a4, __int16 a5, int a6, char a7, __int16 a8, int a9) =
(int(*)(BYTE * a1, __int16 a2, __int16 a3, unsigned __int8 a4, __int16 a5, int a6, char a7, __int16 a8, int a9))(0x68A160);
static int(*add_fixture_tv_days_call)(BYTE* a1, __int16 a2, unsigned __int16 a3, __int16 a4, char a5, char a6, int a7) =
(int(*)(BYTE * a1, __int16 a2, unsigned __int16 a3, __int16 a4, char a5, char a6, int a7))(0x68A1C0);

static int(*add_playoff_draw_date_call)(BYTE* a1, __int16 a2, __int16 a3, BYTE a4, __int16 a5, int a6, __int16 a7) =
(int(*)(BYTE * a1, __int16 a2, __int16 a3, unsigned __int8 a4, __int16 a5, int a6, __int16 a7))(0x521E60);
static int(*add_playoff_fixture_date_call)(BYTE* a1, __int16 a2, __int16 a3, BYTE a4, __int16 a5, int a6, char a7, __int16 a8, int a9) =
(int(*)(BYTE * a1, __int16 a2, __int16 a3, unsigned __int8 a4, __int16 a5, int a6, char a7, __int16 a8, int a9))(0x521EB0);
static int(*create_message_box)(const char* title, const char* message, bool show_quit) = (int(*)(const char* title, const char* message, bool show_quit))(0x5E8290);

static int   (*sub_944C9F_sprintf)() = (int(*)())(0x944C9F);
static void* (*sub_944CF1_operator_new)(int size) = (void* (*)(int size))(0x944CF1);
static int   (*sub_944CFF_splitpath)() = (int(*)())(0x944CFF);
static void* (*sub_944E46_malloc)(int size) = (void* (*)(int size))(0x944E46);
static void* (*sub_945501_alloc)(int size, int a2) = (void* (*)(int size, int a2))(0x945501);
static void  (*sub_9452CA_free)(void* ptr) = (void(*)(void* ptr))(0x9452CA);
static void  (*sub_944C94_free)(void* ptr) = (void(*)(void* ptr))(0x944C94);
static char  (*sub_669340)(int a1) = (char(*)(int a1))(0x669340);

static int(__thiscall* add_team_call)(BYTE* _this, BYTE teamNo, cm3_clubs* club, BYTE a3, DWORD* a4) =
(int(__thiscall*)(BYTE * _this, BYTE teamNo, cm3_clubs * club, BYTE a3, DWORD * a4))(0x687430);

static BYTE* (__thiscall* create_cup_stage_data)(BYTE* _this, BYTE* main_comp, __int16 n_teams, DWORD* teamsPtr, __int16 n_rounds, int comp_id, const void* fixturesPtr,
	__int16 year, char stage_num, char a10, __int16 stage_name_id, char a12, int a13, int a14, int a15, BYTE* a16) =
	(BYTE * (__thiscall*)(BYTE * _this, BYTE * main_comp, __int16 n_teams, DWORD * teamsPtr, __int16 n_rounds, int comp_id, const void* fixturesPtr,
		__int16 year, char stage_num, char a10, __int16 stage_name_id, char a12, int a13, int a14, int a15, BYTE * a16))(0x522E00);

static BYTE* (__thiscall* create_league_stage_data)(BYTE* _this, BYTE* main_comp, __int16 n_teams, DWORD* teamsPtr, __int16 n_rounds, int comp_id, const void* fixturesPtr,
	__int16 num_fixtures, char a9, char a10, char a11, BYTE* a12, BYTE* a13, __int16 year, char stage_num,
	__int16 stage_name_id, char a17, char a18, __int16 a19, __int16 a20, __int16 a21, int a22, char a23) =
	(BYTE * (__thiscall*)(BYTE * _this, BYTE * main_comp, __int16 n_teams, DWORD * teamsPtr, __int16 n_rounds, int comp_id, const void* fixturesPtr,
		__int16 num_fixtures, char a9, char a10, char a11, BYTE * a12, BYTE * a13, __int16 year, char stage_num,
		__int16 stage_name_id, char a17, char a18, __int16 a19, __int16 a20, __int16 a21, int a22, char a23))(0x68B100);
static void(__thiscall* sub_4A2540)(BYTE* _this, cm3_clubs* club, char a3) =
(void(__thiscall*)(BYTE * _this, cm3_clubs * club, char a3))(0x4A2540);

static int(__thiscall* sub_51C800)(BYTE* _this, int a2) =
(int(__thiscall*)(BYTE * _this, int a2))(0x51C800);
static int(__thiscall* sub_682200)(BYTE* _this) =
(int(__thiscall*)(BYTE * _this))(0x682200);
static int(__thiscall* sub_687B10)(BYTE* _this, char a2) =
(int(__thiscall*)(BYTE * _this, char a2))(0x687B10);
static int(__thiscall* sub_6835C0)(BYTE* _this) =
(int(__thiscall*)(BYTE * _this))(0x6835C0);
static int(__thiscall* sub_6827D0)(BYTE* _this, BYTE* base) =
(int(__thiscall*)(BYTE * _this, BYTE * base))(0x6827D0);
static int(__thiscall* sub_49EE70)(BYTE* _this, BYTE* base) =
(int(__thiscall*)(BYTE * _this, BYTE * base))(0x49EE70);
static int(__thiscall* sub_68A850)(BYTE* _this) =
(int(__thiscall*)(BYTE * _this))(0x68A850);
static int(__thiscall* sub_518640)(BYTE* _this) =
(int(__thiscall*)(BYTE * _this))(0x518640);
static int(__thiscall* sub_51FC00)(BYTE* _this, char a2) =
(int(__thiscall*)(BYTE * _this, char a2))(0x51FC00);
static int(__thiscall* cup_map_fixture_tree)(BYTE* _this) =
(int(__thiscall*)(BYTE * _this))(0x518790);
static int(__thiscall* sub_687970)(BYTE* _this, BYTE* base) =
(int(__thiscall*)(BYTE * _this, BYTE * base))(0x687970);
static int(__thiscall* sub_4A1C50)(BYTE* _this, int a2) =
(int(__thiscall*)(BYTE * _this, int a2))(0x4A1C50);
static short(__thiscall* sub_68AA80)(BYTE* _this) =
(short(__thiscall*)(BYTE * _this))(0x68AA80);
static char(__thiscall* sub_79CEE0)(BYTE* _this, BYTE* base) =
(char(__thiscall*)(BYTE * _this, BYTE * base))(0x79CEE0);
static void(__thiscall* sub_49F450)(BYTE* _this) =
(void(__thiscall*)(BYTE * _this))(0x49F450);
static void(__thiscall* sub_682300)(BYTE* _this) =
(void(__thiscall*)(BYTE * _this))(0x682300);
static void(__thiscall* sub_5223A0)(BYTE* _this) =
(void(__thiscall*)(BYTE * _this))(0x5223A0);
static void(__thiscall* sub_518690)(BYTE* _this) =
(void(__thiscall*)(BYTE * _this))(0x518690);
static void(__thiscall* sub_689C80)(BYTE* _this, BYTE* top, BYTE* btm, int a3, int a4, char a5, char a6) =
(void(__thiscall*)(BYTE * _this, BYTE * top, BYTE * btm, int a3, int a4, char a5, char a6))(0x689C80);
static void(__thiscall* sub_68A980)(BYTE* _this, char a2, char a3, char a4, int a5) =
(void(__thiscall*)(BYTE * _this, char a2, char a3, char a4, int a5))(0x68A980);
static void (*sub_6830B0)(BYTE* club, DWORD league, int a3) = (void(*)(BYTE * club, DWORD league, int a3))(0x6830B0);
static void(__thiscall* sub_574E60)(BYTE* _this) =
(void(__thiscall*)(BYTE * _this))(0x574E60);
static char(__thiscall* sub_768310)(BYTE* _this, DWORD date_addr) =
(char(__thiscall*)(BYTE * _this, DWORD date_addr))(0x768310);

static void(__thiscall* staff_history_qualified_868DD0)(BYTE* _this, DWORD* club, DWORD comp_id, WORD stage_main, DWORD stage_sub, char a6) =
(void(__thiscall*)(BYTE * _this, DWORD * club, DWORD comp_id, WORD stage_main, DWORD stage_sub, char a6))(0x86BDD0);
static void(__thiscall* staff_history_champion_868C50)(BYTE* _this, DWORD* club, DWORD comp_id) =
(void(__thiscall*)(BYTE * _this, DWORD * club, DWORD comp_id))(0x868C50);
static void(__thiscall* staff_history_promoted_869480)(BYTE* _this, DWORD* club, DWORD comp_id, char a4) =
(void(__thiscall*)(BYTE * _this, DWORD * club, DWORD comp_id, char a4))(0x869480);
static void(__thiscall* staff_history_relegated_86A1C0)(BYTE* _this, DWORD* club, DWORD comp_id) =
(void(__thiscall*)(BYTE * _this, DWORD * club, DWORD comp_id))(0x86A1C0);

static int(__thiscall* yearly_person_award_setup_92FE80)(BYTE* _this, int a2, int a3, DWORD award_id, WORD rep1, WORD rep2, DWORD comp_id, char a8, int a9, char a10, int a11, int is_player) =
(int(__thiscall*)(BYTE * _this, int a2, int a3, DWORD award_id, WORD rep1, WORD rep2, DWORD comp_id, char a8, int a9, char a10, int a11, int is_player))(0x92FE80);
static int(__thiscall* team_award_setup_8AF520)(BYTE* _this, int a2, int a3, DWORD award_id, WORD rep1, WORD rep2, DWORD comp_id, char a8, char a9, int a10, int a11) =
(int(__thiscall*)(BYTE * _this, int a2, int a3, DWORD award_id, WORD rep1, WORD rep2, DWORD comp_id, char a8, char a9, int a10, int a11))(0x8AF520);
static char* (__thiscall* monthly_person_award_setup_766E10)(BYTE* _this, int a2, int a3, DWORD award_id, WORD rep1, WORD rep2, DWORD comp_id, BYTE start_month, WORD start_year, BYTE end_month, WORD end_year, int a12, int is_player) =
(char* (__thiscall*)(BYTE * _this, int a2, int a3, DWORD award_id, WORD rep1, WORD rep2, DWORD comp_id, BYTE start_month, WORD start_year, BYTE end_month, WORD end_year, int a12, int is_player))(0x766E10);
static void(__thiscall* yearly_player_award_nominate_768CF0)(BYTE* _this, DWORD comp_id, DWORD date_addr, DWORD award_addr, BYTE max_age, unsigned __int16 a6, char a7, DWORD nation_id, int a9, DWORD nation_id_exclude, int a11) =
(void(__thiscall*)(BYTE * _this, DWORD comp_id, DWORD date_addr, DWORD award_addr, BYTE max_age, unsigned __int16 a6, char a7, DWORD nation_id, int a9, DWORD nation_id_exclude, int a11))(0x768CF0);
static void(__thiscall* yearly_team_award_nominate_7698F0)(BYTE* _this, DWORD comp_id, DWORD award_addr) =
(void(__thiscall*)(BYTE * _this, DWORD comp_id, DWORD award_addr))(0x7698F0);
static void(__thiscall* yearly_staff_award_nominate_768940)(BYTE* _this, DWORD date_addr, DWORD award_addr, DWORD comp_id) =
(void(__thiscall*)(BYTE * _this, DWORD date_addr, DWORD award_addr, DWORD comp_id))(0x768940);
static void(__thiscall* monthly_person_award_nominate_7672E0)(BYTE* _this, WORD year) =
(void(__thiscall*)(BYTE * _this, WORD year))(0x7672E0);

static CM3_STAFF* (__thiscall* sub_86F950)(BYTE* _this, DWORD comp_id) =
(CM3_STAFF * (__thiscall*)(BYTE * _this, DWORD comp_id))(0x86F950);
static void(__thiscall* sub_7671C0)(BYTE* _this, int a2, int a3, BYTE a4, WORD a5) =
(void(__thiscall*)(BYTE * _this, int a2, int a3, BYTE a4, WORD a5))(0x7671C0);
static void(__thiscall* sub_767150)(BYTE* _this, int a2, char a3) =
(void(__thiscall*)(BYTE * _this, int a2, char a3))(0x767150);
static void(__thiscall* sub_769C70)(BYTE* _this, DWORD comp_id, DWORD award_addr) =
(void(__thiscall*)(BYTE * _this, DWORD comp_id, DWORD award_addr))(0x769C70);


int AddTeams(BYTE* _this);
int AddTeamsGroupLeague(BYTE* _this, DWORD first_group_id);
void AddLeague(BYTE* _this, const char* szLeagueName, int leagueNo, int year, DWORD league_init_addr);
void sub_689C20_relegation_hook();

void AddFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek, int timeOfDay = Afternoon, int stadiumType = HomeStadium);
void AddFixtureTV(BYTE* pMem, int fixture, int tv_id = 0, int num_to_move = -1, Day dayOfWeek = DontCare, int timeOfDay = DontCare, int stadiumType = HomeStadium);
void AddFixtureNoTV(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek, int timeOfDay = Afternoon, int stadiumType = HomeStadium);
void AddPlayoffFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek, int timeOfDay = Afternoon, int stadiumType = HomeStadium);
void AddPlayoffDrawFixture(BYTE* pMem, int fixture, Date date, int startYear, Day dayOfWeek);
void FillFixtureDetails(BYTE* pMem, int fixture, WORD stage_name, WORD draw_type, WORD game_1_tiebreak, WORD game_2_tiebreak,
	BYTE unk17, WORD teams_in_round, WORD num_games, WORD new_teams_in_round, WORD total_teams_in, BYTE replays, BYTE legs, BYTE days_between_games,
	DWORD prize_reach = 0, DWORD prize_win = 0, DWORD prize_lose = 0, WORD game_3_tiebreak = 0);
void WriteVTablePtr(DWORD* addr, int pos, DWORD data);