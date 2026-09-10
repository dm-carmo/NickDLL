#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include "Helpers\9cf_constants.h"

vtable* irn_first_vtable = new vtable((BYTE*)0x969798, 0xB4);

void irn_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)(irn_first_vtable->vtable_ptr);
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
	sub_682300(_this);
}

void irn_first_free(BYTE* _this, BYTE a2) {
	irn_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) irn_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call irn_first_free
		add esp, 0x8
		ret 4
	}
}

void irn_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

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
	comp_data->relegations = 3;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = IRN_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 9;
	comp_data->max_subs = 5;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) irn_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irn_first_subs
		add esp, 0x4
		ret
	}
}

DWORD irn_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * data->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 13), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 20), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 24), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 27), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 3), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 7), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 11), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 8), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 15), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 19), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 22), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 29), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 5), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 20), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 26), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 3), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 10), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 14), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 4), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 11), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 18), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 25), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 11), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 18), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 1), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 8), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 15), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 19), year, Monday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 22), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 29), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 6), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 13), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 20), year, Thursday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Saturday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 28), year, Thursday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) irn_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call irn_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void irn_first_prom_rel_update(BYTE* _this, int a2) {
	comp_stats* data = (comp_stats*)_this;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* irn_second = get_loaded_league(IRN_SECOND_9CF());
	v1 = *(DWORD*)irn_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(irn_second);
	process_promotion_relegation_689C80(_this, _this, irn_second, 1, a2, -1, -1);
}

void __declspec(naked) irn_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call irn_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall irn_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(IRN_SECOND_9CF());

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_IRAN_9CF());
	for (size_t i = 0; i < available_clubs.size(); i++) {
		cm3_clubs* c = available_clubs[i];
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)c, &is_main_club, 1);
		if (ret_club && !is_main_club && ret_club->ClubDivision->ClubCompID != IRN_FIRST_9CF())
		{
			available_clubs.erase(available_clubs.begin() + i);
			i--;
		}
	}
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size(), true);

	for (unsigned int j = 0; j < promoted_clubs.size(); j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}
}

void __fastcall irn_check_reserve_teams(BYTE* _this) {
	comp_stats* irn_second_data = (comp_stats*)get_loaded_league(IRN_SECOND_9CF());
	// Check teams from L2: main team relegated from L1 - add relegation
	for (WORD num = 0; num < irn_second_data->n_teams; num++) {
		team_league_stats* table_teams = (team_league_stats*)irn_second_data->team_league_table;
		DWORD is_main_club;
		cm3_clubs* ret_club = (cm3_clubs*)check_if_reserve_team_540A50((BYTE*)table_teams[num].club, &is_main_club, 1);
		// If it is a reserve team
		if (ret_club && !is_main_club)
		{
			// If reserve team was not relegated
			if (table_teams[num].league_fate != Relegated) {
				// If main team is in the first league
				if (ret_club->ClubDivision->ClubCompID == IRN_FIRST_9CF()) {
					team_league_stats* main_club_data = get_team_league_stats(IRN_FIRST_9CF(), ret_club);
					// If the main team was relegated
					if (main_club_data->league_fate == Relegated) {
						table_teams[num].league_fate = Relegated;
						// Relegate the reserve team, and relegate one less team from L2
						team_league_stats* d2_table = (team_league_stats*)irn_second_data->team_league_table;
						for (WORD i = irn_second_data->n_teams - irn_second_data->relegations; i < irn_second_data->n_teams; i++) {
							if (d2_table[i].league_fate == Relegated) {
								d2_table[i].league_fate = Eliminated;
								break;
							}
						}
					}
				}
			}
		}
	}
}

char irn_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* irn_second = get_loaded_league(IRN_SECOND_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were relegated from D2 must be semi-professional
	// All teams that were not relegated from D2 must be professional
	update_club_pro_status_68A980(irn_second, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(irn_second, SemiProfessional, -3, Relegated, 0);

	DWORD v1 = *(DWORD*)_this;
	irn_check_reserve_teams(_this);
	irn_first_prom_rel_update(_this, 1);

	irn_non_league_promotion(_this);

	sub_687970(_this, 0);
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
	irn_first_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("irn_first_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)irn_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(irn_second);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) irn_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call irn_first_update
		add esp, 0x4
		ret
	}
}

void irn_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(irn_first_vtable->vtable_ptr);
	irn_first_vtable->SetPointer(VTableSubsRounds, (DWORD)&irn_first_subs_c);
	irn_first_vtable->SetPointer(VTableInitFree, (DWORD)&irn_first_free_c);
	irn_first_vtable->SetPointer(VTableEoSUpdate, (DWORD)&irn_first_update_c);
	irn_first_vtable->SetPointer(VTableFixtures, (DWORD)&irn_first_fixtures_c);
	irn_first_vtable->SetPointer(VTablePromRelUpdate, (DWORD)&irn_first_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) irn_first_vtable->SetPointer(VTableShowThirdInHistory, 0x4110b0);
	data->year = year;
	data->rules = RulesIran;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	irn_first_subs(_this);
	AddTeams(_this);
	SetupTVMoney(_this, prizeMoneyFile.GetInt("irn_first_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void setup_irn_first()
{
}