#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "eng_third.h"
#include "eng_conf.h"
#include "eng_fa_cup.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"

DWORD* eng_fa_cup_vtable = (DWORD*)0x969B28;

void fa_cup_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = eng_fa_cup_vtable;
	DWORD x = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
	}
	if ((DWORD*)data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
			}
		}
		sub_9452CA_free(data->f173);
	}
	if (data->f8) {
		sub_49F450((BYTE*)(data->f8));
		sub_944C94_free((BYTE*)(data->f8));
	}
	DWORD y = -1;
	sub_518690(_this);
}

void eng_fa_cup_free(BYTE* _this, BYTE a2) {
	fa_cup_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) eng_fa_cup_free_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call eng_fa_cup_free
		add esp, 0x8
		ret 4
	}
}

int eng_fa_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	vec.clear();
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 276;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(*(DWORD*)0x9CF764, *(DWORD*)0x9CF2E4);
	vector<cm3_clubs*> lower_clubs2 = find_clubs_of_comp(0x1B1, *(DWORD*)0x9CF2E4);
	move(lower_clubs2.begin(), lower_clubs2.end(), back_inserter(lower_clubs));
	sort(lower_clubs.begin(), lower_clubs.end(), compareClubRep);

	int TeamsToSelectFrom = (lower_clubs.size() < 150) ? lower_clubs.size() : 150;

	for (int i = 0; i < 112; i++)
	{
		cm3_clubs* club = lower_clubs[rand() % TeamsToSelectFrom];

		if (!vector_contains_club(vec, club)) {
			//dprintf("Qualifying club %s to the FA Cup\n", (club->ClubName));
			vec.push_back(club);
		}
		else
			i--;	// Else do again as the club selected was already picked
	}
	// National League North
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(0x168);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// National League South
	division_clubs = find_clubs_of_comp(0x167);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// National League
	division_clubs = find_clubs_of_comp(*(DWORD*)0x9CF69C);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// League 2
	division_clubs = find_clubs_of_comp(*(DWORD*)0x9CF5C8);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// League 1
	division_clubs = find_clubs_of_comp(*(DWORD*)0x9CF5C4);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Championship
	division_clubs = find_clubs_of_comp(*(DWORD*)0x9CF5C0);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// Premier League
	division_clubs = find_clubs_of_comp(*(DWORD*)0x9CF5BC);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

void __declspec(naked) eng_fa_cup_teams_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_fa_cup_teams
		add esp, 0x4
		ret
	}
}

DWORD CreateFACupFixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = *(WORD*)(_this + 0x40);
		*num_rounds = 11;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 1), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QualifyingRound, 0, NoTiebreak_1, AwayGoalsExtraTimePenalties_2, 4, 160, 80, 160, 0, 1, 1, 10, 0, 1350, 450);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 14), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstPreliminaryRound, 0, NoTiebreak_1, AwayGoalsExtraTimePenalties_2, 4, 80, 40, 0, 0, 1, 1, 10, 0, 2250, 750);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 28), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 11), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SecondPreliminaryRound, 0, NoTiebreak_1, AwayGoalsExtraTimePenalties_2, 4, 64, 32, 24, 160, 1, 1, 10, 0, 3750, 1250);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 12), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 80, 40, 48, 184, 0, 1, 0, 0, 18000, 6000);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 2), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 40, 20, 0, 0, 0, 1, 0, 0, 30000, 8000);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 7), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 64, 32, 44, 232, 0, 1, 0, 0, 46000, 10000);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 1, 11), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 2, 14), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 32, 16, 0, 0, 0, 1, 0, 0, 48000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 15), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, FifthRound, 0, ExtraTimePenalties_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 0, 90000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 3, 8), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, 0, 180000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday, Afternoon, FACupSemiFinals);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 4, 2, 0, 0, 0, 1, 0, 0, 400000, 200000);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 16), year, Saturday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, 800000, 400000);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) fa_cup_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call CreateFACupFixtures
		add esp, 0x14
		ret 0x10
	}
}

void eng_fa_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = eng_fa_cup_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->rules = 0x9;
	*((BYTE*)(_this + 0xB1)) = 0;
	//data->f69 = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	eng_fa_cup_teams(_this);
	//*((BYTE*)(_this + 0xB2)) = 0;
	//*((BYTE*)(_this + 0xB3)) = 0;
	//*((BYTE*)(_this + 0xB4)) = 1;
	//data->n_teams = 152;
	//data->teams_list = (DWORD*)sub_945501_alloc(6, data->n_teams);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	//data->max_bench = 7;
	sub_5223A0(_this);
}

void __declspec(naked) eng_fa_cup_init_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_fa_cup_init
		add esp, 0xc
		ret 8
	}
}

char eng_fa_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	if (data->teams_list) {
		sub_9452CA_free(data->teams_list);
		data->teams_list = 0;
	}
	if (data->rounds_list) {
		sub_9452CA_free(data->rounds_list);
		data->rounds_list = 0;
	}
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
				data->f173[i] = 0;
			}
		}
		sub_9452CA_free(data->f173);
		data->f173 = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	eng_fa_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) eng_fa_cup_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_fa_cup_update
		add esp, 0x4
		ret
	}
}

void setup_eng_fa_cup() {
	WriteVTablePtr(eng_fa_cup_vtable, VTableInitFree, (DWORD)&eng_fa_cup_free_c);
	WriteVTablePtr(eng_fa_cup_vtable, VTableEoSUpdate, (DWORD)&eng_fa_cup_update_c);
	WriteVTablePtr(eng_fa_cup_vtable, VTableFixtures, (DWORD)&fa_cup_fixture_caller);
	WriteVTablePtr(eng_fa_cup_vtable, VTable6, 0x51F890);
	//PatchFunction(0x56fab0, (DWORD)&eng_fa_cup_teams_c);
	WriteBytes(0x570944, 1, 0x04);
}