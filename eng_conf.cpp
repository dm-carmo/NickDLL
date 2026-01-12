#pragma warning (disable : 4733)
#include <windows.h>
#include "generic_functions.h"
#include "constants.h"

int eng_conf_subs_c(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;
	DWORD CompID = comp_data->competition_db->ClubCompID;
	dprintf("eng_conf_subs - CompID: %08X\n", CompID);

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->tiebreaker_1 = 1;
	comp_data->tiebreaker_2 = 2;
	comp_data->tiebreaker_3 = 3;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->promotions = 1;
	comp_data->prom_playoff = 6;
	comp_data->rele_playoff = 0;
	//comp_data->relegations = 4;
	comp_data->relegations = 3;

	comp_data->promotes_to = *(DWORD*)0x9CF5C8;
	comp_data->relegates_to = -1;

	comp_data->f82 = 2;
	comp_data->max_bench = 5;
	comp_data->max_subs = 3;

	//call vtable +3C which is actually add fixtures function
	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return 1;
}

void eng_conf_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	// Maybe move this somewhere else, as it is done before this function call
	//BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = (DWORD*)0x969A74;
	data->year = year;
	//data->min_stadium_capacity = 0x1770;
	//data->min_stadium_seats = 0x3E8;
	data->rules = 0x9;
	sub_687B10(_this, 1);
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)sub_944E46_malloc(data->num_stages * 4);
	eng_conf_subs_c(_this);
	AddTeams(_this);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	sub_68A850(_this);
	//return (DWORD)_this;
}

void __declspec(naked) eng_conf_init_c()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_conf_init
		add esp, 0xc
		ret 8
	}
}

void create_playoffs_c_under(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = comp_data->prom_playoff;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)sub_944E46_malloc(playoff_teams * 4);
	int j = 0;
	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams && j < playoff_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[playoff_teams - j - 1])) = (DWORD)tls.club;
			j++;
		}
	}
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)sub_944CF1_operator_new(0xB2);
	create_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, *(DWORD*)(_this + 0x4), pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num * 4])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
}

void create_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		current++;
		comp_data->current_stage = current;
		if (current == 0) create_playoffs_c_under(_this);
	}
}

void __declspec(naked) eng_playoffs_create()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call create_playoffs_c
		add esp, 0x4
		ret
	}
}

void __declspec(naked) eng_conf_subs()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_conf_subs_c
		add esp, 0x4
		ret
	}
}

DWORD CreateConferenceFixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 0) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		DWORD CompID = *(DWORD*)(*(DWORD*)(_this + 0x4));
		BYTE numberOfLeagueTeams = (BYTE)CountNumberOfTeamsInComp(CompID);
		*num_rounds = (numberOfLeagueTeams - 1) * ((comp_stats*)_this)->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 16), year, Saturday);
		if (*num_rounds == 46) AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 20), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 23), year, Saturday);
		if (*num_rounds == 46) AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 25), year, Monday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 8, 30), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 3), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 13), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 24), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 9, 27), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 1), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 4), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 5), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 8), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 15), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 22), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 11, 29), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 6), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 20), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 26), year, Friday, Evening); // change to always be 26/12?
		if (*num_rounds == 46) AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 30), year, Tuesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 3), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 17), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 21), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 11), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 25), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 7), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 25), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 3, 28), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 3), year, Friday, Evening); // change to always be Good Friday?
		if (*num_rounds == 46) AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 6), year, Monday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);

		return (DWORD)pMem;
	}
	else {
		if (stage_idx != 0) return 0;

		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 3;
		*stage_name_id = Playoff;

		pMem = (BYTE*)sub_944E46_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 4, 26), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday);
		FillFixtureDetails(pMem, fixture_id++, QuarterFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 5, 4, 2, 4, 0, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 3), year, Sunday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 6), year, Wednesday, Evening);
		FillFixtureDetails(pMem, fixture_id++, SemiFinal, 0, ExtraTimePenalties_1, NoTiebreak_2, 5, 4, 2, 2, 4, 0, 1, 0);

		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 7), year, Thursday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 10), year, Sunday, Afternoon, NationalStadium);
		FillFixtureDetails(pMem, fixture_id++, Final, 0, ExtraTimePenalties_1, NoTiebreak_2, 0, 2, 1, 0, 0, 0, 1, 0, 0);

		return (DWORD)pMem;
	}
	return 0;
}

int ConferenceTableIndicators(BYTE* _this, DWORD* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	if (stage != -1) {
		comp_stats* comp_data = (comp_stats*)_this;
		WORD num_teams = comp_data->n_teams;
		if (num_teams <= 0) return 0;
		team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
		comp_stats* stage_data = (comp_stats*)(comp_data->stages[0]);
		BYTE* rounds = stage_data->rounds_list;
		WORD current_round = *(WORD*)(round_data + 0x34);
		for (int i = 0; i < num_teams; i++) {
			DWORD* c = (DWORD*)table[i].club;
			if (c != club) continue;
			switch (fate) {
			case TopPlayoff:
				add_staff_history_promotion(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), 0x32);
				table[i].league_fate = Promoted;
				*a5 = 1;
				return 0;
			case Promoted:
				add_staff_history_qualified(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), *(WORD*)(round_data + 0x32),
					*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
				return 0;
			case NoFate:
				table[i].league_fate = Eliminated;
				return 0;
			case BottomPlayoff:
				table[i].league_fate = Eliminated;
				return 0;
			default:
				return 0;
			}
		}
	}
	else {
		switch (fate) {
		case Champions:
			add_staff_history_champions(staff_hist_ptr, club, *(DWORD*)(_this + 0x4));
			return 0;
		case Promoted:
			add_staff_history_promotion(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), 0x64);
			return 0;
		case TopPlayoff:
			add_staff_history_qualified(staff_hist_ptr, club, *(DWORD*)(_this + 0x4), Playoff, None, 0x1E);
			return 0;
		case Relegated:
			add_staff_history_relegated(staff_hist_ptr, club, *(DWORD*)(_this + 0x4));
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) eng_conf_set_table_fate()		// used as a __thiscall -> __cdecl converter
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
		call ConferenceTableIndicators
		add esp, 0x1c
		ret 0x18
	}
}

void __declspec(naked) eng_conf_fixtures()		// used as a __thiscall -> __cdecl converter
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call CreateConferenceFixtures
		add esp, 0x14
		ret 0x10
	}
}

void setup_eng_conf() {
	PatchFunction(0x56db60, (DWORD)&eng_conf_init_c);
	WriteFuncPtr(0x969A74, 11, (DWORD)&eng_playoffs_create);
	WriteFuncPtr(0x969A74, 16, (DWORD)&eng_conf_fixtures);
	WriteFuncPtr(0x969A74, 18, (DWORD)&eng_conf_set_table_fate);
	WriteFuncPtr(0x969A74, 36, (DWORD)&eng_conf_subs);
}