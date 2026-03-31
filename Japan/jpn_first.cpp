#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* jpn_first_vtable = (DWORD*)0x96CA40;

void jpn_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 3;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = JPN_SECOND_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) jpn_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call jpn_first_subs
		add esp, 0x4
		ret
	}
}

void jpn_first_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* jpn_second = get_loaded_league(JPN_SECOND_9CF());
	v1 = *(DWORD*)jpn_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(jpn_second);
	process_promotion_relegation_689C80(_this, _this, jpn_second, 1, a2, -1, -1);

	BYTE* jpn_third = get_loaded_league(JPN_THIRD_9CF());
	v1 = *(DWORD*)jpn_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(jpn_third);
	process_promotion_relegation_689C80(_this, jpn_second, jpn_third, 1, a2, -1, -1);

	BYTE* jpn_jfl = get_loaded_league(JPN_JFL_9CF());
	if (jpn_jfl)
	{
		v1 = *(DWORD*)jpn_jfl;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(jpn_jfl);
		process_promotion_relegation_689C80(_this, jpn_third, jpn_jfl, 1, a2, -1, -1);
	}
}

void __declspec(naked) jpn_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call jpn_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall jpn_jfl_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(JPN_JFL_9CF());
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Relegated) {
			relegated_clubs.push_back(table_pos.club);
		}
	}

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(JPN_REGIONAL_9CF(), NATION_JAPAN_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	int max_to_check = (available_clubs.size() > 5 ? 5 : available_clubs.size());
	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* clubToRelegate = relegated_clubs[i];
		cm3_clubs* available = available_clubs[availableIdx];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = available->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)available, (DWORD)topDivision, 1);

		available_clubs.erase(available_clubs.begin() + availableIdx);
	}
}

void __fastcall jpn_third_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	BYTE* comp_bytes = get_loaded_league(JPN_THIRD_9CF());
	comp_stats* comp_data = (comp_stats*)comp_bytes;
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Relegated) {
			relegated_clubs.push_back(table_pos.club);
		}
	}

	vector<cm3_clubs*> in_playoffs;
	comp_stats* playoff_stage = (comp_stats*)comp_data->stages[1];
	WORD promoted_teams = 0;
	for (WORD i = 0; i < playoff_stage->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)playoff_stage->teams_list)[i];
		cm3_clubs* promote = t.club;
		if (promote->ClubDivision && promote->ClubDivision != comp_data->competition_db) {
			in_playoffs.push_back(promote);
			if (t.f6 == 1) {
				promote_club_6830B0((BYTE*)promote, (DWORD)comp_data->competition_db, 1);
				promoted_teams++;
			}
		}
	}

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(JPN_JFL_9CF(), NATION_JAPAN_9CF());
	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	int max_to_check = (available_clubs.size() > 4 ? 4 : available_clubs.size());
	for (int i = 0; i < 1; i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* available = available_clubs[availableIdx];
		if (vector_contains_club(in_playoffs, available))
			i--;
		else {
			promote_club_6830B0((BYTE*)available, (DWORD)comp_data->competition_db, 1);
			promoted_teams++;
		}
		available_clubs.erase(available_clubs.begin() + availableIdx);
	}

	if (promoted_teams != relegated_clubs.size()) create_message_box("Error", "Promoted and relegated club count does not match for jpn_third", false);

	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		relegate_club_6831A0((BYTE*)relegated_clubs[i], (DWORD)get_comp(JPN_JFL_9CF()), 1);
	}
}

char jpn_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;

	BYTE* jpn_second = get_loaded_league(JPN_SECOND_9CF());
	BYTE* jpn_third = get_loaded_league(JPN_THIRD_9CF());
	BYTE* jpn_jfl = get_loaded_league(JPN_JFL_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be professional
	update_club_pro_status_68A980(jpn_second, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(jpn_second, Professional, -3, Relegated, 1);
	// All teams that were not relegated from D3 must be professional
	update_club_pro_status_68A980(jpn_third, Professional, Relegated, -3, 1);
	if (jpn_jfl) {
		// All teams that were not relegated from D4 must be semi-professional or higher
		// All teams that were relegated from D4 must be semi-professional
		update_club_pro_status_68A980(jpn_jfl, SemiProfessional, Relegated, -3, 1);
		update_club_pro_status_68A980(jpn_jfl, SemiProfessional, -3, Relegated, 1);
		update_club_pro_status_68A980(jpn_jfl, SemiProfessional, -3, Relegated, 0);
	}

	DWORD v1 = *(DWORD*)_this;
	jpn_first_prom_rel_update(_this, 1);

	if (jpn_jfl) {
		jpn_jfl_relegation(_this);
	}
	else {
		jpn_third_relegation(_this);
	}

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
	jpn_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, 117748);
	data->f225 = 1;
	SetupTVMoney(_this, 4474434, 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)jpn_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(jpn_second);

	v1 = *(DWORD*)jpn_third;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(jpn_third);

	if (jpn_jfl) {
		v1 = *(DWORD*)jpn_jfl;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(jpn_jfl);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) jpn_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call jpn_first_update
		add esp, 0x4
		ret
	}
}

DWORD jpn_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
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

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 2, 26), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 2), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 12), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 4, 30), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 3), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 7), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 10), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 17), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 5, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 6, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 24), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 30), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 6), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) jpn_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call jpn_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void jpn_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = jpn_first_vtable;
	data->year = year;
	data->rules = RulesJapanLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 15000;
	data->min_stadium_seats = 10000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	jpn_first_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, 117748);
	data->f225 = 1;
	SetupTVMoney(_this, 4474434, 0);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void setup_jpn_first()
{
	WriteVTablePtr(jpn_first_vtable, VTableSubsRounds, (DWORD)&jpn_first_subs_c);
	WriteVTablePtr(jpn_first_vtable, VTableFixtures, (DWORD)&jpn_first_fixtures_c);
	WriteVTablePtr(jpn_first_vtable, VTableEoSUpdate, (DWORD)&jpn_first_update_c);
	WriteVTablePtr(jpn_first_vtable, VTablePromRelUpdate, (DWORD)&jpn_first_prom_rel_update_c);
	WriteVTablePtr(jpn_first_vtable, VTablePostMatchUpdate, 0x685d30);
	WriteVTablePtr(jpn_first_vtable, VTablePlayoffQual, 0x5a8f60);
	WriteVTablePtr(jpn_first_vtable, VTableSetChampion, 0x684640);
	WriteVTablePtr(jpn_first_vtable, VTableTableFates, 0x686940);
	WriteVTablePtr(jpn_first_vtable, VTableStageNews, 0x48c6d0);
	WriteVTablePtr(jpn_first_vtable, VTableReputationCalc, 0x48e380);
	WriteVTablePtr(jpn_first_vtable, VTable37, 0x68aad0);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(jpn_first_vtable, VTable21, 0x4110b0);
}