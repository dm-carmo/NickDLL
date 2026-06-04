#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* wal_premier_vtable = (DWORD*)0x970F80;

int wal_premier_7F3220(DWORD a1, DWORD a2) {
	BYTE split_pos = 6;
	WORD stage1_games = 22;
	team_league_stats* tls1 = (team_league_stats*)a1;
	team_league_stats* tls2 = (team_league_stats*)a2;

	BYTE bl = ((BYTE*)tls1->position_history)[stage1_games - 1];
	BYTE al = (bl >= split_pos) + 1;
	bl = ((BYTE*)tls2->position_history)[stage1_games - 1];
	BYTE cl = (bl >= split_pos) + 1;
	return al - cl;
}

void wal_premier_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* wal_first_n = get_loaded_league(WAL_FIRST_NORTH_9CF());
	v1 = *(DWORD*)wal_first_n;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(wal_first_n);
	BYTE* wal_first_s = get_loaded_league(WAL_FIRST_SOUTH_9CF());
	v1 = *(DWORD*)wal_first_s;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(wal_first_s);

	process_promotion_relegation_689C80(_this, _this, wal_first_n, 1, a2, -1, -1);
	process_promotion_relegation_689C80(_this, _this, wal_first_s, 1, a2, -1, -1);
}

void __declspec(naked) wal_premier_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call wal_premier_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

DWORD wal_premier_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		*num_rounds = 32;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 22), year, Friday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 25), year, Monday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Saturday);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 23), year, Tuesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 7), year, Tuesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 5), year, Friday, Evening);
		Date boxing_day = Date(year, 12, 26);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		boxing_day.addDays(5);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 9), year, Friday, Evening);
		// next phase starts here
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx < 2) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		*num_rounds = 10;
		*stage_name_id = ChampionshipGroup + stage_idx;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) wal_premier_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call wal_premier_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void wal_premier_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	*((DWORD*)(_this + 0xA7)) = 32; // total number of games each team will play
	*((DWORD*)(_this + 0xA3)) = 0;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->tiebreaker_4 = GamesWonTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 2;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = WAL_FIRST_NORTH_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) wal_premier_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call wal_premier_subs
		add esp, 0x4
		ret
	}
}

void sort_first_n_s_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(WAL_FIRST_NORTH_9CF());
	vector<cm3_clubs*> first_s_clubs = find_clubs_of_comp(WAL_FIRST_SOUTH_9CF());
	move(first_s_clubs.begin(), first_s_clubs.end(), back_inserter(available_clubs));
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 16) available_clubs[i]->ClubDivision = get_comp(WAL_FIRST_NORTH_9CF());
		else available_clubs[i]->ClubDivision = get_comp(WAL_FIRST_SOUTH_9CF());
	}
}

char wal_premier_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;

	BYTE* wal_first_n = get_loaded_league(WAL_FIRST_NORTH_9CF());
	BYTE* wal_first_s = get_loaded_league(WAL_FIRST_SOUTH_9CF());

	// All teams that were not relegated from D1 must be semi-professional or higher
	// All teams that were relegated from D1 must be semi-professional
	update_club_pro_status_68A980(_this, SemiProfessional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, SemiProfessional, -3, Relegated, 1);
	update_club_pro_status_68A980(_this, SemiProfessional, -3, Relegated, 0);
	// All teams that were promoted from D2 must be semi-professional
	// All teams that were relegated from D2 must be amateur
	update_club_pro_status_68A980(wal_first_n, SemiProfessional, -3, Champions, 1);
	update_club_pro_status_68A980(wal_first_n, SemiProfessional, -3, Promoted, 1);
	update_club_pro_status_68A980(wal_first_n, Amateur, -3, Relegated, 0);
	update_club_pro_status_68A980(wal_first_s, SemiProfessional, -3, Champions, 1);
	update_club_pro_status_68A980(wal_first_s, SemiProfessional, -3, Promoted, 1);
	update_club_pro_status_68A980(wal_first_s, Amateur, -3, Relegated, 0);

	DWORD v1 = *(DWORD*)_this;
	wal_premier_prom_rel_update(_this, 1);
	generic_prom_rel(NATION_WALES_9CF(), A_LOWER_9CF(), WAL_FIRST_NORTH_9CF(), 1, WAL_FIRST_SOUTH_9CF());
	sort_first_n_s_clubs();

	sub_687970(_this, ebx);
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
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->current_stage = -1;
	wal_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("wal_prm_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("wal_prm_tv_money"), 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)wal_first_n;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(wal_first_n);

	v1 = *(DWORD*)wal_first_s;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(wal_first_s);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) wal_premier_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call wal_premier_update
		add esp, 0x4
		ret
	}
}

void wal_premier_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = wal_premier_vtable;
	data->year = year;
	data->rules = RulesWales;
	int loaded = sub_687B10(_this, 1);
	if (loaded) {
		if (data->n_rounds != 4) return;
		*((DWORD*)(_this + 0xA3)) = (DWORD)&wal_premier_7F3220;
		return;
	}
	data->min_stadium_capacity = 1500;
	data->min_stadium_seats = 500;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	wal_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("wal_prm_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("wal_prm_tv_money"), 0);
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

void wal_premier_split_under(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 6;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);

	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	for (int i = 0; i < 6; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)table_teams[i].club;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	DWORD v0 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 0, &num_rounds, &stage_name_id, 0);

	WORD year = comp_data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	short f217 = 3;
	create_league_stage_data(pStage, _this, playoff_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
		comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, -1, stage_name_id, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v1 = *(DWORD*)pStage;
	(*(int(__thiscall**)(BYTE*, int))(v1))(pStage, 1);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);

	DWORD* pTeams2 = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	for (int i = 0; i < 6; i++) {
		*((DWORD*)(&pTeams2[i])) = (DWORD)table_teams[i + 6].club;
	}

	WORD num_rounds2 = 0;
	WORD stage_name_id2 = 0;
	BYTE* pFixtures2 = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 1, &num_rounds2, &stage_name_id2, 0);

	BYTE* pStage2 = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage2, _this, playoff_teams, pTeams2, 2, (DWORD)(comp_data->competition_db), pFixtures2, num_rounds2,
		comp_data->pts_for_win, comp_data->pts_for_draw, comp_data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, -1, stage_name_id2, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v2 = *(DWORD*)pStage2;
	(*(int(__thiscall**)(BYTE*, int))(v2))(pStage2, 1);
	sub_9452CA_free(pTeams2);
	sub_9452CA_free(pFixtures2);

	comp_data->n_rounds = 4;
	*((DWORD*)(_this + 0xA3)) = (DWORD)&wal_premier_7F3220;
}

char wal_premier_table_split(BYTE* _this, DWORD current_date, int a2) {
	if (a2) {
		comp_stats* comp_data = (comp_stats*)_this;
		if (comp_data->n_rounds == 2) {
			WORD num_teams = comp_data->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
			bool is_finished = true;
			for (int i = 0; i < num_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < 22) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				wal_premier_split_under(_this);
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) wal_premier_table_split_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call wal_premier_table_split
		add esp, 0xc
		ret 8
	}
}

void setup_wal_premier()
{
	WriteVTablePtr(wal_premier_vtable, VTableSubsRounds, (DWORD)&wal_premier_subs_c);
	WriteVTablePtr(wal_premier_vtable, VTableEoSUpdate, (DWORD)&wal_premier_update_c);
	WriteVTablePtr(wal_premier_vtable, VTableFixtures, (DWORD)&wal_premier_fixtures_c);
	WriteVTablePtr(wal_premier_vtable, VTableLeagueSplit, (DWORD)&wal_premier_table_split_c);
	WriteVTablePtr(wal_premier_vtable, VTableStageNews, 0x7f3080); // Scotland stage news contains champ/rel group news
	WriteVTablePtr(wal_premier_vtable, VTablePromRelUpdate, (DWORD)&wal_premier_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(wal_premier_vtable, VTable21, 0x4110b0);
}