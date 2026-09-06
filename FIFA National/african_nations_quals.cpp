#include <windows.h>
#include <filesystem>
#include <fstream>
#include <map>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

using namespace std;

vtable* african_nations_quals_vtable = new vtable((BYTE*)0x970C24, 0xA0);

void african_nations_quals_free_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->comp_vtable = (DWORD*)african_nations_quals_vtable->vtable_ptr;
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
	sub_518690(_this);
}

void african_nations_quals_free(BYTE* _this, BYTE a2) {
	african_nations_quals_free_under(_this);
	if (a2 & 1) {
		sub_944C94_free(_this);
	}
}

void __declspec(naked) african_nations_quals_free_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_quals_free
		add esp, 0x8
		ret 4
	}
}

DWORD african_nations_quals_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	comp_stats* data = (comp_stats*)_this;
	if (stage_idx == -1) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year, 11, 28), year, Saturday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 3, 25), year, Thursday, Afternoon);
		FillFixtureDetails(pMem, fixture_id++, PreliminaryRound, 0, NoAwayGoals, Penalties | ExtraTime | NoAwayGoals, 10, 12, 6, 12, 0, 0, 2, 5);

		return (DWORD)pMem;
	}
	else if (stage_idx < 12) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = data->year;
		*num_rounds = 6;
		*stage_name_id = AlphabeticGroupStage + stage_idx - 1;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 9, 24), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 9, 29), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 11, 12), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 11, 17), year, Tuesday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 3, 24), year, Thursday, Afternoon);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 2, 3, 29), year, Tuesday, Afternoon);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) african_nations_quals_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_quals_fixtures
		add esp, 0x14
		ret 0x10
	}
}

char african_nations_quals_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;
	if (data->special_teams_seedings) {
		sub_9452CA_free(data->special_teams_seedings);
		data->special_nteams_seedings = 0;
		data->special_teams_seedings = 0;
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
	data->current_stage = -1;
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	if (data->year < *current_year) data->year += 4;
	data->f171 = 0;
	*((BYTE*)(_this + 0xB1)) = 0;
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
	data->f69 = 0;
	return 1;
}

void __declspec(naked) african_nations_quals_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call african_nations_quals_update
		add esp, 0x4
		ret
	}
}

void african_nations_quals_all_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD year = data->year;

	vector<cm3_clubs*> caf_countries = get_national_teams_of_continent_fifa_members(AFRICA_9CF());
	sort(caf_countries.begin(), caf_countries.end(), compareNationRanking);

	DWORD host1_id, host2_id;
	get_comp_hosts_in_continent(_this, AFCON_9CF(), AFRICA_9CF(), &host1_id, &host2_id);
	WORD total_teams_in_comp = (WORD)caf_countries.size();
	data->special_nteams_seedings = total_teams_in_comp;
	data->f56 = total_teams_in_comp;

	if (data->special_teams_seedings) sub_9452CA_free(data->special_teams_seedings);
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams_in_comp);
	data->special_teams_seedings = (DWORD*)pMem;
	teams_seeded* teams = (teams_seeded*)data->special_teams_seedings;

	for (WORD i = 0; i < total_teams_in_comp; i++) {
		if (caf_countries[i]->ClubNation->NationID == host1_id || caf_countries[i]->ClubNation->NationID == host2_id)
		{
			auto it = caf_countries.begin() + i;
			rotate(caf_countries.begin(), it, it + 1);
		}
		}

	for (size_t i = 0, j = 0; i < caf_countries.size() && j < total_teams_in_comp; i++) {
		teams[j].club = caf_countries[i];
		if (j < 42) teams[j].seeding = 10;
		else teams[j].seeding = 11;
		teams[j].f6 = 0;
		j++;
	}
}

void african_nations_quals_qualifier_teams(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	WORD total_teams = 12;
	BYTE* pMem = (BYTE*)cm0102_malloc(6 * total_teams);

	if (data->teams_list) sub_9452CA_free(data->teams_list);
	if (data->f173) {
		for (WORD i = 0; i < data->n_rounds; i++) {
			DWORD rnd = data->f173[i];
			if (rnd) {
				sub_9452CA_free((DWORD*)rnd);
			}
		}
		sub_9452CA_free(data->f173);
	}

	WORD year = data->year;
	data->n_teams = total_teams;
	data->teams_list = (DWORD*)pMem;

	teams_seeded* teams = (teams_seeded*)data->teams_list;
	teams_seeded* qualifiers = (teams_seeded*)data->special_teams_seedings;
	for (WORD i = 0; i < total_teams; i++) {
		cm3_clubs* club = qualifiers[42 + i].club;
		teams[i].club = club;
		teams[i].seeding = 0;
		teams[i].f6 = 0;
	}
}

void african_nations_quals_init2(BYTE* _this, DWORD current_date, int a3) {
	comp_stats* data = (comp_stats*)_this;
	if (!data->f69) {
		BYTE* cm_date = new BYTE[8];
		convert_to_cm_date(cm_date, 1, December, data->year, -1);
		WORD date_day = *(WORD*)(cm_date);
		WORD date_year = *(WORD*)(cm_date + 2);
		if (date_day == *(WORD*)(current_date) && *(WORD*)(current_date + 2) == date_year) {
			if (a3) {
				sub_775070((BYTE*)*b74318, get_continent(AFRICA_9CF()), 0);
				data->f69 = 1;
				african_nations_quals_all_teams(_this);
				african_nations_quals_qualifier_teams(_this);
				DWORD v1 = *(DWORD*)_this;
				(*(int(__thiscall**)(BYTE*))(v1 + 0x8C))(_this);
				(*(int(__thiscall**)(BYTE*))(v1 + 0x94))(_this);
				(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);
				sub_51C800(_this, 0);
			}
		}
	}
	sub_51F890(_this, current_date, a3);
}

void __declspec(naked) african_nations_quals_init2_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_quals_init2
		add esp, 0xc
		ret 8
	}
}

int african_nations_quals_table_fates(BYTE* _this, cm3_clubs* club, char fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == -1) {
		BYTE* rounds = comp_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		switch (fate) {
		case TopPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0x1E);
			return 0;
		case Promoted:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
				*(WORD*)(rounds + playoff_dates_sz * current_round + 7), 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	else if (stage < 12) {
		switch (fate) {
		case Qualified1:
			qualify_team_for_international_comp(club, AFCON_9CF());
			return 0;
		default:
			staff_history_knocked_out_86C000(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, GroupStage, 0xF);
			break;
		}
		sub_775000((BYTE*)*b74318, club->ClubNation);
		return 0;
	}
	return 0;
}

void __declspec(naked) african_nations_quals_table_fates_c()
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
		call african_nations_quals_table_fates
		add esp, 0x1c
		ret 0x18
	}
}

int african_nations_quals_stage_news(BYTE* _this, int club_idx, char fate, char stage_id, int stage_name_idx, int round_data, __int16 a7, int a8, char a9, int show_body_text, LPVOID* ret_str_ptr) {
	comp_stats* data = (comp_stats*)_this;
	cm3_club_comps* comp_data = data->competition_db;
	cm3_clubs* club_data = get_club(club_idx);
	if (stage_id == -1) {
		if (show_body_text) return sub_4B0B80(club_idx, round_data, a9, fate, a7, ret_str_ptr);
		else {
			switch (fate)
			{
			case TopPlayoff:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			case Promoted:
				sub_66F4E0(0xDE1F64, 0x987198, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, comp_data->ClubCompGenderNameShort, comp_data->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				break;
			default:
				sub_66F4E0(0xDE1F64, 0xAD4BA4, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, &club_data->ClubNameShort[0], &comp_data->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				return 1;
			}
			sub_4AE660(ret_str_ptr, 0xDE1F64);
			sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
			sub_4AE8A0((BYTE*)ret_str_ptr, &comp_data->ClubCompNameShort[0], 0x7d0, (DWORD)comp_data);
			return 1;
		}
	}
	else if (stage_id < 12) {
		if (fate == Qualified1)
		{
			if (show_body_text) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
			else {
				cm3_club_comps* afcon = get_comp(AFCON_9CF());
				sub_66F4E0(0xDE1F64, 0x9C470C, club_data->ClubGenderNameShort, club_data->ClubGenderNameShort, afcon->ClubCompGenderNameShort, afcon->ClubCompGenderNameShort,
					&club_data->ClubNameShort[0], &afcon->ClubCompNameShort[0]);
				sub_4AE660(ret_str_ptr, 0xDE1F64);
				sub_4AE8A0((BYTE*)ret_str_ptr, &club_data->ClubNameShort[0], 0x7d5, (DWORD)club_data);
				sub_4AE8A0((BYTE*)ret_str_ptr, &afcon->ClubCompNameShort[0], 0x7d0, (DWORD)afcon);
				return 1;
			}
		}
		else if (fate == Eliminated) return sub_4B4590(club_idx, (WORD)stage_name_idx, (DWORD)comp_data, fate, show_body_text, ret_str_ptr);
	}
	return 0;
}

void __declspec(naked) african_nations_quals_stage_news_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x28]
		push dword ptr[eax + 0x24]
		push dword ptr[eax + 0x20]
		push dword ptr[eax + 0x1c]
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_quals_stage_news
		add esp, 0x2c
		ret 0x28
	}
}

void african_nations_quals_landmarks(BYTE* _this, DWORD dest_ptr, int a2, WORD main_stage_id, WORD sub_stage_id, char fate, cm3_clubs* club) {
	if (main_stage_id >= 0x41f && main_stage_id <= 0x42e)
	{
		if (fate == CantBePromoted || fate == Qualified1) {
			sub_66F4E0(dest_ptr, 0x9C48A4, club->ClubGenderName, 0xAD9C64);
			return;
		}
		else {
			sub_66F4E0(dest_ptr, 0x99B800);
			return;
		}
	}
	return sub_48CAB0(_this, dest_ptr, a2, main_stage_id, sub_stage_id, fate, club);
}

void __declspec(naked) african_nations_quals_landmarks_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x18]
		push dword ptr[eax + 0x14]
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xc]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_quals_landmarks
		add esp, 0x1c
		ret 0x18
	}
}

void african_nations_quals_reputation_setup(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;

	if (comp_data->f8)
	{
		comp_stats* curr_stage = comp_data;
		teams_seeded* all_teams = (teams_seeded*)comp_data->special_teams_seedings;
		vector<cm3_clubs*> clubs;
		for (int i = 0; i < comp_data->special_nteams_seedings; i++)
		{
			clubs.push_back(all_teams[i].club);
		}
		sort(clubs.begin(), clubs.end(), compareNationRanking);

		for (DWORD i = 0; i < 12; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 1);
		}
		for (DWORD i = 12; i < 24; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 13);
		}
		for (DWORD i = 24; i < 36; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 25);
		}
		for (DWORD i = 36; i < 48; i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 37);
		}
		for (DWORD i = 48; i < clubs.size(); i++) {
			sub_4A2540((BYTE*)comp_data->f8, clubs[i], 49);
		}
		for (WORD i = 0; i < clubs.size(); i++) {
			sub_775220((BYTE*)*b74318, clubs[i]->ClubNation, comp_data->competition_db);
		}
	}
}

void __declspec(naked) african_nations_quals_reputation_setup_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call african_nations_quals_reputation_setup
		add esp, 0x4
		ret
	}
}

void african_nations_quals_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == -1) {
		ret_current = 47 + current;
		if (ret_min != 1) ret_min = 47 + min;
		ret_max = 47 + max;
	}
	else if (stage < 12) {
		ret_current = 1 + 12 * (current - 1);
		if (min < 3) ret_min = 1;
		else ret_min = 1 + 12 * (min - 1);
		if (max < 3) ret_max = 25;
		else ret_max = 1 + 12 * (max - 1);
		if (ret_current > ret_max) ret_current = ret_max;
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) african_nations_quals_reputation_calc_c()
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
		call african_nations_quals_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void block_hosts_from_qualifying_afcon(BYTE* stage, DWORD host1_id, DWORD host2_id) {
	comp_stats* comp_data = (comp_stats*)stage;
	WORD total_teams = comp_data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		if (table_teams[i].club->ClubNation->NationID == host1_id ||
			table_teams[i].club->ClubNation->NationID == host2_id) {
			table_teams[i].league_fate = CantBePromoted;
			comp_data->promotions--;
		}
	}
}

void african_nations_quals_second_stage_setup(BYTE* _this) {
	char stage_num = 0;

	comp_stats* comp_data = (comp_stats*)_this;
	DWORD* stages_arr = comp_data->stages;

	char prom_rel[4] = { 2, 0, 0, 0 };
	char tiebreaks[4] = { CurrentPositionTiebreaker, GoalDifferenceTiebreaker, GoalsForTiebreaker, GoalsForAwayTiebreaker };

	vector<cm3_clubs*> clubs;
	teams_seeded* teams = (teams_seeded*)comp_data->special_teams_seedings;
	for (DWORD i = 0; i < 42; i++) clubs.push_back(teams[i].club);
	teams = (teams_seeded*)comp_data->teams_list;
	for (WORD i = 0; i < comp_data->n_teams; i++) {
		if (teams[i].f6 == 1) clubs.push_back(teams[i].club);
	}

	sort(clubs.begin(), clubs.end(), compareNationRanking);
	shuffle(clubs.begin(), clubs.begin() + 12, rng);
	shuffle(clubs.begin() + 12, clubs.begin() + 24, rng);
	shuffle(clubs.begin() + 24, clubs.begin() + 36, rng);
	shuffle(clubs.begin() + 36, clubs.end(), rng);

	DWORD v1 = *(DWORD*)_this;
	WORD group_teams = 4;
	DWORD host1_id, host2_id;
	get_comp_hosts_in_continent(_this, AFCON_9CF(), AFRICA_9CF(), &host1_id, &host2_id);
	for (int i = 0; i < 12; i++) {
		WORD num_rounds = 0;
		WORD stage_name_id = 0;
		BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, i + stage_num, &num_rounds, &stage_name_id, 0);
		DWORD* pTeams = (DWORD*)cm0102_malloc(group_teams * 4);

		for (int j = 0; j < group_teams; j++) {
			cm3_clubs* club = clubs[i + 12 * j];
			*((DWORD*)(&pTeams[j])) = (DWORD)club;
		}

		WORD year = comp_data->year;
		BYTE* pStage = (BYTE*)cm0102_new(0xEE);
		create_league_stage_data(pStage, _this, group_teams, pTeams, 2, (DWORD)(comp_data->competition_db), pFixtures, num_rounds,
			3, 1, 10, &tiebreaks[0], &prom_rel[0], year, i + stage_num, stage_name_id, 0xf, 2, 0, 0x28, -1, 0, 2);
		DWORD* stages_arr = comp_data->stages;
		*((DWORD*)(&stages_arr[i + stage_num])) = (DWORD)pStage;
		sub_684230(pStage);
		block_hosts_from_qualifying_afcon(pStage, host1_id, host2_id);
		sub_9452CA_free(pTeams);
		sub_9452CA_free(pFixtures);
		comp_data->current_stage = i + stage_num;
	}
}

void african_nations_quals_stages_create(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) {
			african_nations_quals_second_stage_setup(_this);
		}
	}
}

void __declspec(naked) african_nations_quals_stages_create_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call african_nations_quals_stages_create
		add esp, 0x4
		ret
	}
}

void __declspec(naked) african_nations_quals_vtable31_c()
{
	__asm
	{
		mov ecx, dword ptr ds : [0x9cf7ac]
		lea eax, dword ptr ds : [ecx + ecx * 2]
		lea eax, dword ptr ds : [eax + eax * 8]
		shl eax, 2
		sub eax, ecx
		mov ecx, dword ptr ds : [0xae23d0]
		add eax, ecx
		ret
	}
}

WORD african_nations_quals_vtable29(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	WORD val = (WORD)sub_4A2E10((BYTE*)f8, club, 0x12);
	return (val < 24) - 3;
}

void __declspec(naked) african_nations_quals_vtable29_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_quals_vtable29
		add esp, 0x8
		ret 4
	}
}

BYTE african_nations_quals_vtable30(BYTE* _this, cm3_clubs* club) {
	comp_stats* data = (comp_stats*)_this;
	DWORD* f8 = data->f8;
	BYTE bl = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x13);
	BYTE al = (BYTE)sub_4A2E10((BYTE*)f8, club, 0x12);

	if (al < 24) return 2 * (bl < 24) - 1;
	else return 2 * (bl < 24);
}

void __declspec(naked) african_nations_quals_vtable30_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call african_nations_quals_vtable30
		add esp, 0x8
		ret 4
	}
}

void african_nations_quals_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_518640(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)(african_nations_quals_vtable->vtable_ptr);
	african_nations_quals_vtable->SetPointer(VTableInitFree, (DWORD)&african_nations_quals_free_c);
	african_nations_quals_vtable->SetPointer(VTableEoSUpdate, (DWORD)&african_nations_quals_update_c);
	african_nations_quals_vtable->SetPointer(VTableLeagueSplit, (DWORD)&african_nations_quals_init2_c);
	african_nations_quals_vtable->SetPointer(VTablePlayoffQual, (DWORD)&african_nations_quals_stages_create_c);
	african_nations_quals_vtable->SetPointer(VTableTableFates, (DWORD)&african_nations_quals_table_fates_c);
	african_nations_quals_vtable->SetPointer(VTableReputationSetup, (DWORD)&african_nations_quals_reputation_setup_c);
	african_nations_quals_vtable->SetPointer(VTableReputationCalc, (DWORD)&african_nations_quals_reputation_calc_c);
	african_nations_quals_vtable->SetPointer(VTableFixtures, (DWORD)&african_nations_quals_fixture_caller);
	african_nations_quals_vtable->SetPointer(VTableStageNews, (DWORD)&african_nations_quals_stage_news_c);
	african_nations_quals_vtable->SetPointer(VTable29, (DWORD)&african_nations_quals_vtable29_c);
	african_nations_quals_vtable->SetPointer(VTable30, (DWORD)&african_nations_quals_vtable30_c);
	african_nations_quals_vtable->SetPointer(VTableGetFinalsComp, (DWORD)&african_nations_quals_vtable31_c);
	african_nations_quals_vtable->SetPointer(VTableClubLandmarks, (DWORD)&african_nations_quals_landmarks_c);
	african_nations_quals_vtable->SetPointer(VTableLoadCompInfo, 0x48CEB0);
	african_nations_quals_vtable->SetPointer(VTableSaveCompInfo, 0x48CEA0);
	data->comp_type = NATION_INTERNATIONAL;
	data->promotes_to = -1;
	data->relegates_to = -1;
	data->rules = RulesInternational;
	data->f82 = 3;
	data->max_bench = 9;
	data->max_subs = 5;
	data->year = year - 1;
	while (data->year % 4 != 2) data->year++;
	data->f81 = 0xf;
	data->special_nteams_seedings = 0;
	data->f56 = 6;
	*((BYTE*)(_this + 0xB1)) = 0;
	int loaded = sub_51FC00(_this, 1);
	if (loaded) return;
	data->f171 = 0;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 12;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);

	data->n_teams = 12;
	BYTE* tMem = (BYTE*)cm0102_malloc(6 * data->n_teams);
	data->teams_list = (DWORD*)tMem;

	DWORD v1 = *(DWORD*)_this;
	*((DWORD*)(_this + 0xA3)) = (DWORD)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0x3c, _this + 0x3a, 0);
	cup_map_fixture_tree_518790(_this);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	data->f69 = 0;
}

void setup_african_nations_quals() {
}