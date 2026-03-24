#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* arg_first_vtable = (DWORD*)0x967324;

void arg_first_aggregate_relegation(BYTE* _this) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* data = (comp_stats*)_this;
	comp_stats* aggregate = (comp_stats*)(data->stages[5]);
	team_league_stats* table_teams = (team_league_stats*)(aggregate->team_league_table);
	table_teams[0].league_fate = Champions;
	staff_history_champion_868C50(staff_hist_ptr, table_teams[0].club, (DWORD)(data->competition_db));
	WORD nteams = aggregate->n_teams;
	for (WORD i = nteams; i > nteams - 2; i--) {
		table_teams[i - 1].league_fate = Relegated;
		staff_history_relegated_86A1C0(staff_hist_ptr, table_teams[i - 1].club, (DWORD)(data->competition_db));
	}
}

int arg_first_set_champion(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;

	comp_stats* aggregate = (comp_stats*)(data->stages[5]);
	team_league_stats* table_teams = (team_league_stats*)(aggregate->team_league_table);
	sub_4AFCE0_add_history_entry(_this, table_teams[0].club, table_teams[1].club, table_teams[2].club, 0);

	BYTE* stage_data_for_history = (BYTE*)data->stages[4];
	DWORD v1 = *(DWORD*)stage_data_for_history;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);

	stage_data_for_history = (BYTE*)data->stages[3];
	v1 = *(DWORD*)stage_data_for_history;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x30))(stage_data_for_history);

	arg_first_aggregate_relegation(_this);

	return 0;
}

void __declspec(naked) arg_first_set_champion_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_first_set_champion
		add esp, 0x4
		ret 0
	}
}

int arg_first_last_positions(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	vector<cm3_clubs*> clubs;

	comp_stats* open_playoff = (comp_stats*)data->stages[3];
	teams_seeded* open_teams = (teams_seeded*)open_playoff->teams_list;
	for (WORD i = 0; i < open_playoff->n_teams; i++) {
		if (open_teams[i].f6 == 1 && !vector_contains_club(clubs, open_teams[i].club))
		{
			clubs.push_back(open_teams[i].club);
			break;
		}
	}

	comp_stats* close_playoff = (comp_stats*)data->stages[4];
	teams_seeded* close_teams = (teams_seeded*)close_playoff->teams_list;
	for (WORD i = 0; i < close_playoff->n_teams; i++) {
		if (close_teams[i].f6 == 1 && !vector_contains_club(clubs, close_teams[i].club))
		{
			clubs.push_back(close_teams[i].club);
			break;
		}
	}

	comp_stats* aggregate = (comp_stats*)data->stages[5];
	team_league_stats* table_teams = (team_league_stats*)(aggregate->team_league_table);
	for (WORD i = 0; i < aggregate->n_teams; i++)
	{
		if (!vector_contains_club(clubs, table_teams[i].club)) clubs.push_back(table_teams[i].club);
	}

	if (clubs.size() != aggregate->n_teams)
	{
		string msg = "Wrong number of clubs: " + to_string(clubs.size());
		create_message_box(data->competition_db->ClubCompName, msg.c_str(), true);
	}

	for (size_t i = 0; i < clubs.size(); i++) {
		clubs[i]->ClubLastDivision = data->competition_db;
		clubs[i]->ClubLastPosition = (char)i + 1;
	}
	return 1;
}

void __declspec(naked) arg_first_last_positions_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_first_last_positions
		add esp, 0x4
		ret
	}
}

void arg_first_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 1;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 8;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 0;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = ARG_SECOND_9CF();

	comp_data->f217 = 0x2;
	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) arg_first_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_first_subs
		add esp, 0x4
		ret
	}
}

int arg_first_add_teams(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;
	DWORD* all_teams = comp_data->teams2;
	if (all_teams) sub_9452CA_free(all_teams);

	// Count the number of teams first, as the code really expects us to know up front
	WORD numberOfLeagueTeams = CountNumberOfTeamsInComp(CompID);
	comp_data->teams2 = (DWORD*)sub_944E46_malloc(numberOfLeagueTeams * 4);
	vector<cm3_clubs*> d1_clubs;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = &(*clubs)[i];
		if (club->ClubDivision && club->ClubDivision->ClubCompID == CompID) d1_clubs.push_back(club);
	}
	shuffle(d1_clubs.begin(), d1_clubs.end(), rng);
	for (DWORD i = 0; i < d1_clubs.size(); i++)
	{
		*((DWORD*)(&comp_data->teams2[i])) = (DWORD)d1_clubs[i];
	}

	// Now let's add the teams
	comp_data->n_teams = 15; // number of teams per group in this case
	comp_data->team_league_table = (DWORD*)sub_944E46_malloc(numberOfLeagueTeams * league_team_list_sz); // number of teams * 59 (0x3B) - was 0x2FF
	BYTE teamsAdded = 0;
	for (DWORD i = 0; i < comp_data->n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)(comp_data->teams2[i]);
		add_team_call(_this, teamsAdded++, club, 0, 0);
	}
	return 1;
}

int arg_first_add_teams_close(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;

	vector<cm3_clubs*> d1_clubs;
	for (DWORD i = 0; i < 30; i++)
	{
		cm3_clubs* club = (cm3_clubs*)comp_data->teams2[i];
		d1_clubs.push_back(club);
	}
	shuffle(d1_clubs.begin(), d1_clubs.end(), rng);
	for (DWORD i = 0; i < d1_clubs.size(); i++)
	{
		*((DWORD*)(&comp_data->teams2[i])) = (DWORD)d1_clubs[i];
	}
	return 1;
}

void arg_first_setup_groups_open(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD n_teams = 15;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)all_teams[n_teams * (idx + 1) + i];
		*((DWORD*)(&pTeams[i])) = (DWORD)club;
	}
	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, n_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void arg_first_setup_groups_close(BYTE* _this, BYTE idx) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD n_teams = 15;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < n_teams; i++)
	{
		cm3_clubs* club = (cm3_clubs*)all_teams[n_teams * (idx - 1) + i];
		*((DWORD*)(&pTeams[i])) = (DWORD)club;
	}
	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	create_league_stage_data(pStage, _this, n_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), (BYTE*)(_this + 0xBE),
		year, idx, stage_name_id, data->f81, 1, 0, data->f217, -1, 0, 2);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void arg_first_league_table(BYTE* _this) {
	DWORD v1 = *(DWORD*)_this;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	BYTE idx = 5;
	WORD n_teams = 30;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, idx, &num_rounds, &stage_name_id, 0);
	comp_stats* data = (comp_stats*)_this;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(n_teams * 4);

	DWORD* all_teams = data->teams2;
	for (DWORD i = 0; i < n_teams; i++)
	{
		*((DWORD*)(&pTeams[i])) = all_teams[i];
	}
	WORD year = data->year;
	BYTE* pStage = (BYTE*)sub_944CF1_operator_new(0xEE);
	BYTE prom_rel[4] = { 0, 0, 0, 0 };
	short f217 = 0;
	create_league_stage_data(pStage, _this, n_teams, pTeams, 0, (DWORD)(data->competition_db), pFixtures, 28,
		data->pts_for_win, data->pts_for_draw, data->f196, (BYTE*)(_this + 0xC5), &prom_rel[0],
		year, idx, stage_name_id, data->f81, 1, 0, f217, -1, 0, data->f225);
	DWORD* stages_arr = data->stages;
	*((DWORD*)(&stages_arr[idx])) = (DWORD)pStage;
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
	data->current_stage = idx;
}

void arg_first_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* arg_second = get_loaded_league(ARG_SECOND_9CF());
	comp_stats* arg_second_data = (comp_stats*)arg_second;
	v1 = *(DWORD*)arg_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(arg_second);

	BYTE* arg_second_grp = (BYTE*)arg_second_data->stages[0];
	v1 = *(DWORD*)arg_second_grp;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(arg_second_grp);

	comp_stats* data = (comp_stats*)_this;
	sub_689C80(_this, (BYTE*)data->stages[5], arg_second, 1, a2, -1, -1);
	sub_689C80(_this, (BYTE*)data->stages[5], arg_second_grp, 1, a2, -1, -1);
}

void __declspec(naked) arg_first_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call arg_first_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void arg_first_open_playoff(BYTE* _this) {
	char stage_num = 3;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	for (int i = 0; i < playoff_teams; i++) pTeams[i] = 0;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void arg_first_close_playoff(BYTE* _this) {
	char stage_num = 4;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 16;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	for (int i = 0; i < playoff_teams; i++) pTeams[i] = 0;
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void __fastcall arg_second_relegation(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs;

	comp_stats* comp_data = (comp_stats*)get_loaded_league(ARG_SECOND_9CF());
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		for (WORD num = 0; num < curr_stage->n_teams; num++) {
			team_league_stats table_pos = ((team_league_stats*)curr_stage->team_league_table)[num];
			if (table_pos.league_fate == Relegated) {
				relegated_clubs.push_back(table_pos.club);
			}
		}
	}

	vector<cm3_clubs*> available_clubs;
	for (DWORD i = 0; i < *clubs_count; i++)
	{
		cm3_clubs* club = get_club(i);
		if (club)
		{
			if (club->ClubDivision && club->ClubNation)
			{
				DWORD compID = club->ClubDivision->ClubCompID;
				DWORD nationID = club->ClubNation->NationID;
				if (nationID == NATION_ARGENTINA_9CF() && compID == ARG_THIRD_9CF())
				{
					available_clubs.push_back(club);
				}
			}
		}
	}

	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	int max_to_check = (available_clubs.size() > 8 ? 8 : available_clubs.size());
	for (unsigned int i = 0; i < relegated_clubs.size(); i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* clubToRelegate = relegated_clubs[i];
		cm3_clubs* available = available_clubs[availableIdx];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = available->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)available, (DWORD)topDivision, 1);
		clubToRelegate->ClubReserveDivision = 0;

		available_clubs.erase(available_clubs.begin() + availableIdx);
	}
}

char arg_first_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE* ebx = 0;
	data->f76 = 0;
	arg_first_prom_rel_update(_this, 1);
	arg_second_relegation(_this);

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
	arg_first_subs(_this);
	arg_first_add_teams(_this);
	SetupTVMoney(_this, 800000, get_comp(ARG_FIRST_9CF()));
	SetupTVMoney(_this, 650000, get_comp(ARG_SECOND_9CF()));
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		arg_first_setup_groups_open(_this, i);
	}
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
	arg_first_add_teams_close(_this);
	for (BYTE i = 1; i < 3; i++) {
		arg_first_setup_groups_close(_this, i);
	}
	arg_first_open_playoff(_this);
	arg_first_close_playoff(_this);
	arg_first_league_table(_this);

	BYTE* arg_second = get_loaded_league(ARG_SECOND_9CF());

	v1 = *(DWORD*)arg_second;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(arg_second);

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) arg_first_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_first_update
		add esp, 0x4
		ret
	}
}

void arg_first_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = arg_first_vtable;
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

void arg_first_free(BYTE* _this, BYTE a2) {
	arg_first_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) arg_first_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call arg_first_free
		add esp, 0x8
		ret 4
	}
}

int arg_first_vtable2(BYTE* _this, BYTE* round_data, int a3) {
	comp_stats* comp_data = (comp_stats*)_this;
	sub_685D30(_this, round_data, a3);

	char curr_stage = *(char*)(round_data + 0x42);
	if (curr_stage < 3)
	{
		DWORD* f8 = comp_data->f8;
		comp_data->f8 = 0;
		*(BYTE*)(round_data + 0x42) = 5;
		sub_685D30(_this, round_data, a3);
		*(BYTE*)(round_data + 0x42) = curr_stage;
		comp_data->f8 = f8;
	}

	return 1;
}

void __declspec(naked) arg_first_vtable2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call arg_first_vtable2
		add esp, 0xc
		ret 0x8
	}
}

DWORD arg_first_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		*num_rounds = 15;
		*stage_name_id = Phase1GroupAtoH + stage_idx + 1;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 1, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 12), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 2, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 15), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 3, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 5), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 12), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 4, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 5, 3), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx < 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		*num_rounds = 15;
		*stage_name_id = Phase2GroupAtoD + stage_idx - 1;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 12), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 19), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 7, 26), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
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
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
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
		AddFixture(pMem, fixture_id, Date(year, 10, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 15), year, Saturday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 3) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = OpeningStage;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 4), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 10), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, EleventhRound, 0, FixedTeamOrderInCup + PenaltiesNoExtraTime_1, NoTiebreaker, 5, 16, 8, 16, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 11), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 17), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + PenaltiesNoExtraTime_1, NoTiebreaker, 5, 8, 4, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 18), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 5, 24), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + PenaltiesNoExtraTime_1, NoTiebreaker, 5, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 5, 25), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 6, 1), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, PenaltiesNoExtraTime_1, NoTiebreaker, 5, 2, 1, 0, 0, 0, 1, 0, 0, 373776, 0);

		return (DWORD)pMem;
	}
	else if (stage_idx == 4) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 4;
		*stage_name_id = ClosingStage;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 16), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, EleventhRound, 0, FixedTeamOrderInCup + PenaltiesNoExtraTime_1, NoTiebreaker, 5, 16, 8, 16, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 23), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, FixedTeamOrderInCup + PenaltiesNoExtraTime_1, NoTiebreaker, 5, 8, 4, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 30), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, FixedTeamOrderInCup + PenaltiesNoExtraTime_1, NoTiebreaker, 5, 4, 2, 0, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 12, 7), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, PenaltiesNoExtraTime_1, NoTiebreaker, 5, 2, 1, 0, 0, 0, 1, 0, 0, 373776, 0);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) arg_first_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call arg_first_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void arg_first_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
			vector<cm3_clubs*> clubs;
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			WORD total_teams = curr_stage->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < total_teams; i++) {
				clubs.push_back(table_teams[i].club);
			}
			sort(clubs.begin(), clubs.end(), compareClubRep);
			for (size_t i = 0; i < clubs.size(); i++) {
				cm3_clubs* c = clubs[i];
				sub_4A2540((BYTE*)comp_data->f8, c, (char)(i * 2 + 1));
			}
		}
	}
}

void __declspec(naked) arg_first_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call arg_first_reputation_setup
		add esp, 0x4
		ret
	}
}

void arg_first_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = arg_first_vtable;
	data->year = year;
	data->rules = RulesArgentina;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 6;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	arg_first_subs(_this);
	arg_first_add_teams(_this);
	SetupTVMoney(_this, 800000, get_comp(ARG_FIRST_9CF()));
	SetupTVMoney(_this, 650000, get_comp(ARG_SECOND_9CF()));
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_6835C0(_this);
	for (BYTE i = 0; i < 1; i++) {
		arg_first_setup_groups_open(_this, i);
	}
	arg_first_reputation_setup(_this);
	arg_first_add_teams_close(_this);
	for (BYTE i = 1; i < 3; i++) {
		arg_first_setup_groups_close(_this, i);
	}
	arg_first_open_playoff(_this);
	arg_first_close_playoff(_this);
	arg_first_league_table(_this);
}

void arg_first_open_playoff_teams(BYTE* _this) {
	char stage_num = 3;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)comp_data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	vector<cm3_clubs*> clubs;
	comp_stats* curr_stage = comp_data;
	for (char al = -1; al < 1; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
		}
	}
	BYTE team_order[16] = { 0,6,4,2,3,5,7,1,8,14,12,10,11,13,15,9 };

	for (char i = 0; i < playoff_teams; i++) {
		teams[team_order[i]].club = clubs[i];
	}
}

void arg_first_close_playoff_teams(BYTE* _this) {
	char stage_num = 4;
	comp_stats* comp_data = (comp_stats*)_this;
	comp_stats* playoff = (comp_stats*)comp_data->stages[stage_num];
	teams_seeded* teams = (teams_seeded*)playoff->teams_list;
	WORD playoff_teams = playoff->n_teams;

	vector<cm3_clubs*> clubs;
	comp_stats* curr_stage = comp_data;
	for (char al = 1; al < 3; al++) {
		if (al >= 0) {
			curr_stage = (comp_stats*)(comp_data->stages[al]);
		}
		WORD total_teams = curr_stage->n_teams;
		team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
		for (int i = 0; i < total_teams; i++) {
			team_league_stats tls = table_teams[i];
			if (tls.league_fate == TopPlayoff) {
				clubs.push_back(tls.club);
			}
		}
	}
	BYTE team_order[16] = { 0,6,4,2,3,5,7,1,8,14,12,10,11,13,15,9 };

	for (char i = 0; i < playoff_teams; i++) {
		teams[team_order[i]].club = clubs[i];
	}
}

int arg_first_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage < 1) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), OpeningStage, EleventhRound, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RelegationPlayoff, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	else if (stage < 3) {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), ClosingStage, EleventhRound, 0x1E);
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, RelegationPlayoff, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	else if (stage == 3) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		for (char al = -1; al < 1; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
					table[i].league_fate = Champions;
					*a5 = 1;
					return 0;
				case Promoted:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				case BottomPlayoff:
					staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
					table[i].league_fate = Eliminated;
					return 0;
				default:
					staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	else if (stage == 4) {
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		comp_stats* curr_stage = comp_data;
		for (char al = 1; al < 3; al++) {
			if (al >= 0) {
				curr_stage = (comp_stats*)(comp_data->stages[al]);
			}
			team_league_stats* table = (team_league_stats*)(curr_stage->team_league_table);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_comp_winner_86A800(staff_hist_ptr, club, round_data, a7);
					table[i].league_fate = Champions;
					*a5 = 1;
					return 0;
				case Promoted:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				case BottomPlayoff:
					staff_history_comp_runner_up_86B0B0(staff_hist_ptr, club, round_data, a7);
					table[i].league_fate = Eliminated;
					return 0;
				default:
					staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	return 0;
}

void __declspec(naked) arg_first_set_table_fate()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call arg_first_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void arg_first_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage < 3) {
		ret_current = 1 + 2 * (current - 1);
		if (min < 9) ret_min = 1;
		else ret_min = 1 + 2 * (min - 1);
		if (max < 9) ret_max = 9;
		else ret_max = 1 + 2 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) arg_first_reputation_calc_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call arg_first_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

char arg_first_table_split(BYTE* _this, DWORD current_date, int a2) {
	if (a2) {
		comp_stats* comp_data = (comp_stats*)_this;
		comp_stats* open_playoff = (comp_stats*)comp_data->stages[3];
		teams_seeded* open_teams = (teams_seeded*)open_playoff->teams_list;
		if (!open_teams[0].club) {
			comp_stats* curr_stage = comp_data;
			bool is_finished = true;
			for (char al = -1; al < 1; al++) {
				if (al >= 0) {
					curr_stage = (comp_stats*)(comp_data->stages[al]);
				}
				WORD total_teams = curr_stage->n_teams;
				team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
				for (int i = 0; i < total_teams; i++) {
					team_league_stats tls = table_teams[i];
					if (tls.games < 14) {
						is_finished = false;
						break;
					}
				}
			}
			if (is_finished) {
				arg_first_open_playoff_teams(_this);
			}
		}
		comp_stats* close_playoff = (comp_stats*)comp_data->stages[4];
		teams_seeded* close_teams = (teams_seeded*)close_playoff->teams_list;
		if (!close_teams[0].club) {
			comp_stats* curr_stage = comp_data;
			bool is_finished = true;
			for (char al = 1; al < 3; al++) {
				if (al >= 0) {
					curr_stage = (comp_stats*)(comp_data->stages[al]);
				}
				WORD total_teams = curr_stage->n_teams;
				team_league_stats* table_teams = (team_league_stats*)(curr_stage->team_league_table);
				for (int i = 0; i < total_teams; i++) {
					team_league_stats tls = table_teams[i];
					if (tls.games < 14) {
						is_finished = false;
						break;
					}
				}
			}
			if (is_finished) {
				arg_first_close_playoff_teams(_this);
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) arg_first_table_split_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call arg_first_table_split
		add esp, 0xc
		ret 8
	}
}

void setup_arg_first()
{
	WriteVTablePtr(arg_first_vtable, VTableSubsRounds, (DWORD)&arg_first_subs_c);
	WriteVTablePtr(arg_first_vtable, VTableInitFree, (DWORD)&arg_first_free_c);
	// check post match update
	WriteVTablePtr(arg_first_vtable, VTablePostMatchUpdate, (DWORD)&arg_first_vtable2_c);
	WriteVTablePtr(arg_first_vtable, VTableEoSUpdate, (DWORD)&arg_first_update_c);
	WriteVTablePtr(arg_first_vtable, VTableFixtures, (DWORD)&arg_first_fixtures_c);
	// check set champion
	WriteVTablePtr(arg_first_vtable, VTableSetChampion, (DWORD)&arg_first_set_champion_c);
	WriteVTablePtr(arg_first_vtable, VTableUpdateLastDivision, (DWORD)&arg_first_last_positions_c);
	// what does vtable 14 do?
	WriteVTablePtr(arg_first_vtable, VTable14, 0x583470);
	// check stage news
	WriteVTablePtr(arg_first_vtable, VTableStageNews, 0x48c6d0);
	WriteVTablePtr(arg_first_vtable, VTableReputationSetup, (DWORD)&arg_first_reputation_setup_c);
	WriteVTablePtr(arg_first_vtable, VTableReputationCalc, (DWORD)&arg_first_reputation_calc_c);
	WriteVTablePtr(arg_first_vtable, VTableLeagueSplit, (DWORD)&arg_first_table_split_c);
	WriteVTablePtr(arg_first_vtable, VTableTableFates, (DWORD)&arg_first_set_table_fate);
	WriteVTablePtr(arg_first_vtable, VTablePromRelUpdate, (DWORD)&arg_first_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(arg_first_vtable, VTable21, 0x4110b0);
	// 405ef0 average points table

	// hardcoded thing in first division
	WriteBytes(0x444307, 1, 0xeb);

	char* open_grp_stage = "Apertura Group Stage";
	char* open_grp_stage_short = "Aper Grp";
	WriteDWORD(0x4b646c + 1, (DWORD)&open_grp_stage[0]);
	WriteDWORD(0x4b8f59 + 1, (DWORD)&open_grp_stage_short[0]);
	char* open_grp_a = "Apertura Group A";
	char* open_grp_a_short = "Aper Grp A";
	WriteDWORD(0x4b6334 + 1, (DWORD)&open_grp_a[0]);
	WriteDWORD(0x4b8e21 + 1, (DWORD)&open_grp_a_short[0]);
	char* open_grp_b = "Apertura Group B";
	char* open_grp_b_short = "Aper Grp B";
	WriteDWORD(0x4b634e + 1, (DWORD)&open_grp_b[0]);
	WriteDWORD(0x4b8e3b + 1, (DWORD)&open_grp_b_short[0]);
	char* open_p_off = "Apertura Playoffs";
	char* open_p_off_short = "Aper";
	WriteDWORD(0x4b624a + 1, (DWORD)&open_p_off[0]);
	WriteDWORD(0x4b8d37 + 1, (DWORD)&open_p_off_short[0]);
	char* close_grp_stage = "Clausura Group Stage";
	char* close_grp_stage_short = "Clau Grp";
	WriteDWORD(0x4b6486 + 1, (DWORD)&close_grp_stage[0]);
	WriteDWORD(0x4b8f73 + 1, (DWORD)&close_grp_stage_short[0]);
	char* close_grp_a = "Clausura Group A";
	char* close_grp_a_short = "Clau Grp A";
	WriteDWORD(0x4b6404 + 1, (DWORD)&close_grp_a[0]);
	WriteDWORD(0x4b8ef1 + 1, (DWORD)&close_grp_a_short[0]);
	char* close_grp_b = "Clausura Group B";
	char* close_grp_b_short = "Clau Grp B";
	WriteDWORD(0x4b641e + 1, (DWORD)&close_grp_b[0]);
	WriteDWORD(0x4b8f0b + 1, (DWORD)&close_grp_b_short[0]);
	char* close_p_off = "Clausura Playoffs";
	char* close_p_off_short = "Clau";
	WriteDWORD(0x4b6264 + 1, (DWORD)&close_p_off[0]);
	WriteDWORD(0x4b8d51 + 1, (DWORD)&close_p_off_short[0]);
}
