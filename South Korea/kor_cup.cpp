#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* kor_cup_vtable = (DWORD*)0x96CD30;

DWORD kor_cup_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 6;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 5), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 15), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SecondRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 32, 16, 32, 0, 0, 1, 0, prizeMoneyFile.GetInt("kor_cup_r2_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 16), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 7, 29), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, ThirdRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 24, 12, 8, 32, 0, 1, 0, prizeMoneyFile.GetInt("kor_cup_r3_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 7, 30), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 8, 19), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, FourthRound, 1, Penalties | ExtraTime, NoTiebreak, 4, 16, 8, 4, 40, 0, 1, 0, prizeMoneyFile.GetInt("kor_cup_r4_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 8, 20), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 19), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 1, Penalties | ExtraTime, NoTiebreak, 6, 8, 4, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("kor_cup_qtr_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 20), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 26), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 1, Penalties | ExtraTime, NoTiebreak, 6, 4, 2, 0, 0, 0, 1, 0, prizeMoneyFile.GetInt("kor_cup_semi_qualify"));

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 27), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 6, 5), year, Saturday, Evening, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, Penalties | ExtraTime, NoTiebreak, 6, 2, 1, 0, 0, 0, 1, 0, 0, prizeMoneyFile.GetInt("kor_cup_final_win"), prizeMoneyFile.GetInt("kor_cup_final_lose"));

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) kor_cup_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call kor_cup_fixtures
		add esp, 0x14
		ret 0x10
	}
}

int kor_cup_teams(BYTE* _this) {
	vector<cm3_clubs*> vec;
	comp_stats* comp_data = (comp_stats*)_this;
	WORD total_teams = 44;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	comp_data->n_teams = total_teams;
	comp_data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)comp_data->teams_list;

	// Lower
	vector<cm3_clubs*> division_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_SOUTH_KOREA_9CF());
	vector<cm3_clubs*> division_clubs2 = find_clubs_of_comp(A_LOWER_B_9CF(), NATION_SOUTH_KOREA_9CF());
	move(division_clubs2.begin(), division_clubs2.end(), back_inserter(division_clubs));
	vector<cm3_clubs*> lower_clubs;
	std::copy_if(division_clubs.begin(), division_clubs.end(), std::back_inserter(lower_clubs),
		[](cm3_clubs* c) {
			string s = string(c->ClubNameShort);
			return s.size() < 5 || s.substr(s.size() - 4) != " (R)";
		});
	for (int i = 0; i < 15; i++)
	{
		int availableIdx = rand() % lower_clubs.size();
		cm3_clubs* lower_club = lower_clubs[availableIdx];
		vec.push_back(lower_club);

		lower_clubs.erase(lower_clubs.begin() + availableIdx);
	}
	// D2
	division_clubs = find_clubs_of_comp(KOR_SECOND_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}
	// D1
	division_clubs = find_clubs_of_comp(KOR_FIRST_9CF());
	sort(division_clubs.begin(), division_clubs.end(), compareClubLastDivPosInv);
	for (cm3_clubs* club : division_clubs)
	{
		vec.push_back(club);
	}

	for (DWORD i = 0; i < vec.size(); i++)
	{
		teams[i].club = vec[i];
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}

	return 1;
}

void kor_cup_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = kor_cup_vtable;
	data->year = year;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	data->comp_type = CLUB_DOMESTIC;
	data->rules = RulesSouthKorea;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	kor_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->max_bench = 9;
	data->max_subs = 5;
	cup_reputation_setup_generic_5223A0(_this);
}

void __declspec(naked) kor_cup_init_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call kor_cup_init
		add esp, 0xc
		ret 8
	}
}

char kor_cup_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
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
	kor_cup_teams(_this);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	return (*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
}

void __declspec(naked) kor_cup_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call kor_cup_update
		add esp, 0x4
		ret
	}
}

void setup_kor_cup()
{
	WriteVTablePtr(kor_cup_vtable, VTableFixtures, (DWORD)&kor_cup_fixture_caller);
	WriteVTablePtr(kor_cup_vtable, VTableEoSUpdate, (DWORD)&kor_cup_update_c);
	WriteVTablePtr(kor_cup_vtable, VTableSubsRounds, 0x858e70);
	WriteVTablePtr(kor_cup_vtable, VTableLeagueSplit, 0x88d8a0); // same as Swedish Cup
}
