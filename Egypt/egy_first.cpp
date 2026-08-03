#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

vtable* egy_first_vtable = new vtable((BYTE*)0x969798, 0xB4);

void egy_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(egy_first_vtable->vtable_ptr);
	DWORD x = 0;
	sub_687970(_this, 0);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
			data->stages[i] = 0;
		}
	}
	if (data->stages) {
		sub_9452CA_free((BYTE*)(data->stages));
		data->stages = 0;
	}
	if (data->f8) {
		sub_49F450((BYTE*)(data->f8));
		sub_944C94_free((BYTE*)(data->f8));
	}
	DWORD y = -1;
	sub_682300(_this);
}

void egy_first_free(BYTE* _this, BYTE a2) {
	egy_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) egy_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call egy_first_free
		add esp, 0x8
		ret 4
	}
}

void egy_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE d1_teams = (BYTE)CountNumberOfTeamsInComp(EGY_FIRST_9CF());

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_2 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_3 = GoalsForTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	if (d1_teams > 18) comp_data->relegations = 4;
	else comp_data->relegations = 3;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = EGY_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) egy_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call egy_first_subs
		add esp, 0x4
		ret
	}
}

DWORD egy_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1 + numberOfLeagueTeams % 2) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 20), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 17), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		if (numberOfLeagueTeams > 18) {
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
		}
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 24), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		if (numberOfLeagueTeams > 18) {
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
		}
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 21), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 28), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 18), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		if (numberOfLeagueTeams > 18) {
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 2, 21), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
		}
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 25), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 8), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		if (numberOfLeagueTeams > 18) {
			tv_id = 0;
			AddFixture(pMem, fixture_id, Date(year + 1, 4, 11), year, Saturday);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
			AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
			AddFixtureTV(pMem, fixture_id++, tv_id++);
		}
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 15), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 29), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 6), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 13), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 23), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 27), year, Wednesday, Evening);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) egy_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call egy_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void __fastcall egy_reduce_d1_teams(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(EGY_FIRST_9CF());

	vector<cm3_clubs*> promoted_clubs;
	comp_stats* comp_data = (comp_stats*)get_loaded_league(EGY_SECOND_9CF());
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Promoted || table_pos.league_fate == Champions) {
			promoted_clubs.push_back(table_pos.club);
		}
	}

	cm3_club_comps* topDivision = get_comp(EGY_FIRST_9CF());
	cm3_club_comps* bottomDivision = get_comp(EGY_SECOND_9CF());
	for (cm3_clubs* club : relegated_clubs) {
		relegate_club_6831A0((BYTE*)club, (DWORD)bottomDivision, 1);
	}
	for (cm3_clubs* club : promoted_clubs) {
		promote_club_6830B0((BYTE*)club, (DWORD)topDivision, 1);
	}
}

void egy_first_prom_rel_update(BYTE* _this, int a2) {
	comp_stats* data = (comp_stats*)_this;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* egy_second = get_loaded_league(EGY_SECOND_9CF());
	v1 = *(DWORD*)egy_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(egy_second);
	if (data->n_teams > 18) {
		egy_reduce_d1_teams(_this);
	}
	else {
		process_promotion_relegation_689C80(_this, _this, egy_second, 1, a2, -1, -1);
	}
}

void __declspec(naked) egy_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call egy_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall egy_non_league_promotion(BYTE* _this)
{
	comp_stats* data = (comp_stats*)_this;

	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(EGY_SECOND_9CF());

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_EGYPT_9CF());
	unsigned int num_to_promote = 3;

	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, num_to_promote, true);

	cm3_club_comps* topDivision = get_comp(EGY_SECOND_9CF());
	cm3_club_comps* bottomDivision = get_comp(A_LOWER_9CF());

	for (unsigned int j = 0; j < promoted_clubs.size(); j++) {
		cm3_clubs* clubToPromote = promoted_clubs[j];
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}

	for (unsigned int j = 0; j < relegated_clubs.size(); j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
	}
}

char egy_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;

	BYTE* egy_second = get_loaded_league(EGY_SECOND_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were relegated from D2 must be semi-professional
	update_club_pro_status_68A980(egy_second, SemiProfessional, -3, Relegated, 1);

	DWORD v1 = *(DWORD*)_this;
	egy_first_prom_rel_update(_this, 1);

	egy_non_league_promotion(_this);

	sub_687970(_this, ebx);
	if (data->fixtures_table) {
		sub_9452CA_free(data->fixtures_table);
		data->fixtures_table = 0;
	}
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	long current = data->current_stage;
	if (current >= 0) {
		for (long i = 0; i <= current; i++) {
			DWORD stage = data->stages[i];
			if (stage) {
				DWORD v1 = *(DWORD*)stage;
				(DWORD*)(*(int(__thiscall**)(BYTE*, int a2))(v1))((BYTE*)stage, 1);
			}
			data->stages[i] = 0;
		}
	}
	data->year++;
	data->current_stage = -1;
	*((DWORD*)(_this + 0xA7)) = -1;
	egy_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("egy_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("egy_first_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)egy_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(egy_second);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) egy_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call egy_first_update
		add esp, 0x4
		ret
	}
}

void egy_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(egy_first_vtable->vtable_ptr);
	egy_first_vtable->SetPointer(VTableSubsRounds, (DWORD)&egy_first_subs_c);
	egy_first_vtable->SetPointer(VTableInitFree, (DWORD)&egy_first_free_c);
	egy_first_vtable->SetPointer(VTableEoSUpdate, (DWORD)&egy_first_update_c);
	egy_first_vtable->SetPointer(VTableFixtures, (DWORD)&egy_first_fixtures_c);
	egy_first_vtable->SetPointer(VTablePromRelUpdate, (DWORD)&egy_first_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) egy_first_vtable->SetPointer(VTable21, 0x4110b0);
	data->year = year;
	data->rules = RulesEgypt;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	egy_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("egy_first_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("egy_first_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void setup_egy_first()
{
}