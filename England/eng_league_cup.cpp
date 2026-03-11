#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* eng_league_cup_vtable = (DWORD*)0x969934;

int eng_league_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	vector<cm3_clubs*> vec_uefa;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 92;
	BYTE* pMem = (BYTE*)sub_944E46_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	vector<cm3_clubs*> division_clubs = find_clubs_of_country(NATION_ENGLAND_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		if (club->ClubEuroFlag != -1 && club->ClubDivision && (club->ClubDivision->ClubCompID == ENG_PREMIER_9CF()
			|| club->ClubDivision->ClubCompID == ENG_CHAMP_9CF() || club->ClubDivision->ClubCompID == ENG_LEAGUE_1_9CF()
			|| club->ClubDivision->ClubCompID == ENG_LEAGUE_2_9CF()))
			vec_uefa.push_back(club);
	}
	sort(vec_uefa.begin(), vec_uefa.end(), compareClubLastDivPosInv);

	// League 2
	division_clubs = find_clubs_of_comp(ENG_LEAGUE_2_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_uefa, club)) vec.push_back(club);
	}
	// League 1
	division_clubs = find_clubs_of_comp(ENG_LEAGUE_1_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_uefa, club)) vec.push_back(club);
	}
	// Championship
	division_clubs = find_clubs_of_comp(ENG_CHAMP_9CF());
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_uefa, club)) vec.push_back(club);
	}
	// Premier League
	division_clubs = find_clubs_of_comp(ENG_PREMIER_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		if (!vector_contains_club(vec_uefa, club)) vec.push_back(club);
	}

	for (cm3_clubs* club : vec_uefa)
	{
		vec.push_back(club);
	}

	while (vec.size() > total_teams) {
		vec.erase(vec.begin());
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].f5 = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

DWORD eng_league_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 8;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 6, 26), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 5), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 4, 2, 4, 0, 0, 1, 0, 0, 5000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 6), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 12), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FirstRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 70, 35, 68, 4, 0, 1, 0, 0, 5000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 13), year, Friday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 26), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 46, 23, 11, 72, 0, 1, 0, 0, 7000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 27), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 9, 23), year, Tuesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 32, 16, 9, 83, 0, 1, 0, 0, 10000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 9, 24), year, Wednesday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 10, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 4, 16, 8, 0, 0, 0, 1, 0, 0, 15000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 10, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 17), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, PenaltiesNoExtraTime_1, NoTiebreak_2, 6, 8, 4, 0, 0, 0, 1, 0, 0, 25000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 18), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 1, 14), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, NoTiebreak_1, AwayGoalsPenaltiesNoExtraTime_2, 6, 4, 2, 0, 0, 0, 2, 21, 0, 25000, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 2, 5), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 22), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 6, 2, 1, 0, 0, 0, 1, 0, 0, 100000, 50000);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) eng_league_cup_fixture_caller()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_league_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void eng_league_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = eng_league_cup_vtable;
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
	comp->ClubCompBackgroundColour = get_colour(COLOUR_GREEN_1_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	eng_league_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	data->max_bench = 7;
	data->max_subs = 3;
	sub_5223A0(_this);
}

void __declspec(naked) eng_league_cup_init_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_league_cup_init
		add esp, 0xc
		ret 8
	}
}

char eng_league_cup_update(BYTE* _this) {
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
	eng_league_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) eng_league_cup_update_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_league_cup_update
		add esp, 0x4
		ret
	}
}

void setup_eng_league_cup() {
	WriteVTablePtr(eng_league_cup_vtable, VTableEoSUpdate, (DWORD)&eng_league_cup_update_c);
	WriteVTablePtr(eng_league_cup_vtable, VTableFixtures, (DWORD)&eng_league_cup_fixture_caller);
	WriteVTablePtr(eng_league_cup_vtable, VTableLeagueSplit, 0x51F890);
}