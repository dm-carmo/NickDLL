#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* eng_premier_vtable = (DWORD*)0x969D1C;

int eng_premier_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 2;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 0;
	comp_data->relegations = 3;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = ENG_CHAMP_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return 1;
}

void __declspec(naked) eng_premier_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_premier_subs
		add esp, 0x4
		ret
	}
}

void eng_premier_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* eng_champ = get_loaded_league(ENG_CHAMP_9CF());
	v1 = *(DWORD*)eng_champ;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(eng_champ);

	BYTE* eng_league_1 = get_loaded_league(ENG_LEAGUE_1_9CF());
	v1 = *(DWORD*)eng_league_1;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(eng_league_1);

	BYTE* eng_league_2 = get_loaded_league(ENG_LEAGUE_2_9CF());
	v1 = *(DWORD*)eng_league_2;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(eng_league_2);

	process_promotion_relegation_689C80(_this, _this, eng_champ, 1, a2, -1, -1);
	process_promotion_relegation_689C80(_this, eng_champ, eng_league_1, 1, a2, -1, -1);
	process_promotion_relegation_689C80(_this, eng_league_1, eng_league_2, 1, a2, -1, -1);

	BYTE* eng_conf = get_loaded_league(ENG_CONFERENCE_9CF());
	if (eng_conf) {
		v1 = *(DWORD*)eng_conf;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(eng_conf);
		BYTE* eng_conf_n = get_loaded_league(ENG_CONFERENCE_NORTH_9CF());
		v1 = *(DWORD*)eng_conf_n;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(eng_conf_n);
		BYTE* eng_conf_s = get_loaded_league(ENG_CONFERENCE_SOUTH_9CF());
		v1 = *(DWORD*)eng_conf_s;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(eng_conf_s);

		process_promotion_relegation_689C80(_this, eng_league_2, eng_conf, 1, a2, -1, -1);
		process_promotion_relegation_689C80(_this, eng_conf, eng_conf_n, 1, a2, -1, -1);
		process_promotion_relegation_689C80(_this, eng_conf, eng_conf_s, 1, a2, -1, -1);
	}
}

void __declspec(naked) eng_premier_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call eng_premier_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

void __fastcall eng_extra_non_playable_swaps(BYTE* _this)
{
	vector<cm3_clubs*> conf_clubs = find_clubs_of_comp(ENG_CONFERENCE_9CF());
	vector<cm3_clubs*> conf_n_clubs = find_clubs_of_comp(ENG_CONFERENCE_NORTH_9CF());
	vector<cm3_clubs*> conf_s_clubs = find_clubs_of_comp(ENG_CONFERENCE_SOUTH_9CF());

	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(conf_n_clubs, 2, true);
	vector<cm3_clubs*> promoted_clubs2 = get_random_weighted_clubs(conf_s_clubs, 2, true);
	move(promoted_clubs2.begin(), promoted_clubs2.end(), back_inserter(promoted_clubs));
	vector<cm3_clubs*> relegated_clubs = get_random_weighted_clubs(conf_clubs, 4, false);

	for (unsigned int j = 0; j < relegated_clubs.size(); j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}

	conf_n_clubs = find_clubs_of_comp(ENG_CONFERENCE_NORTH_9CF());
	conf_s_clubs = find_clubs_of_comp(ENG_CONFERENCE_SOUTH_9CF());
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_ENGLAND_9CF());

	promoted_clubs = get_random_weighted_clubs(lower_clubs, 8, true);
	relegated_clubs = get_random_weighted_clubs(conf_n_clubs, 4, false);
	vector<cm3_clubs*> relegated_clubs2 = get_random_weighted_clubs(conf_s_clubs, 4, false);
	move(relegated_clubs2.begin(), relegated_clubs2.end(), back_inserter(relegated_clubs));

	for (unsigned int j = 0; j < 8; j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}
}

void __fastcall eng_swap_between_lower_and_lower_b(BYTE* _this)
{
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_ENGLAND_9CF());
	vector<cm3_clubs*> lower_b_clubs = find_clubs_of_comp(A_LOWER_B_9CF(), NATION_ENGLAND_9CF());
	unsigned int num_to_swap = lower_clubs.size() / 8;
	if (lower_b_clubs.size() < num_to_swap) num_to_swap = lower_b_clubs.size();

	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(lower_b_clubs, num_to_swap, true);
	vector<cm3_clubs*> relegated_clubs = get_random_weighted_clubs(lower_clubs, num_to_swap, false);

	for (unsigned int j = 0; j < num_to_swap; j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}
}

void sort_conf_n_s_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(ENG_CONFERENCE_NORTH_9CF());
	vector<cm3_clubs*> conf_s_clubs = find_clubs_of_comp(ENG_CONFERENCE_SOUTH_9CF());
	move(conf_s_clubs.begin(), conf_s_clubs.end(), back_inserter(available_clubs));
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 24) available_clubs[i]->ClubDivision = get_comp(ENG_CONFERENCE_NORTH_9CF());
		else available_clubs[i]->ClubDivision = get_comp(ENG_CONFERENCE_SOUTH_9CF());
	}
}

char eng_premier_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* eng_champ = get_loaded_league(ENG_CHAMP_9CF());
	BYTE* eng_league_1 = get_loaded_league(ENG_LEAGUE_1_9CF());
	BYTE* eng_league_2 = get_loaded_league(ENG_LEAGUE_2_9CF());
	BYTE* eng_conf = get_loaded_league(ENG_CONFERENCE_9CF());
	BYTE* eng_conf_n = get_loaded_league(ENG_CONFERENCE_NORTH_9CF());
	BYTE* eng_conf_s = get_loaded_league(ENG_CONFERENCE_SOUTH_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be professional
	update_club_pro_status_68A980(eng_champ, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(eng_champ, Professional, -3, Relegated, 1);
	// All teams that were in D3 must be professional
	update_club_pro_status_68A980(eng_league_1, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(eng_league_1, Professional, -3, Relegated, 1);
	// All teams that were in D4 must be professional
	update_club_pro_status_68A980(eng_league_2, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(eng_league_2, Professional, -3, Relegated, 1);
	if (eng_conf)
	{
		// All teams that were not relegated from D5 must be semi-professional or higher
		update_club_pro_status_68A980(eng_conf, SemiProfessional, Relegated, -3, 1);
		// All teams that were in D6 must be semi-professional
		update_club_pro_status_68A980(eng_conf_n, SemiProfessional, Relegated, -3, 1);
		update_club_pro_status_68A980(eng_conf_n, SemiProfessional, -3, Relegated, 1);
		update_club_pro_status_68A980(eng_conf_n, SemiProfessional, -3, Relegated, 0);
		update_club_pro_status_68A980(eng_conf_s, SemiProfessional, Relegated, -3, 1);
		update_club_pro_status_68A980(eng_conf_s, SemiProfessional, -3, Relegated, 1);
		update_club_pro_status_68A980(eng_conf_s, SemiProfessional, -3, Relegated, 0);
	}

	eng_premier_prom_rel_update(_this, 1);

	if (eng_conf) {
		generic_prom_rel(NATION_ENGLAND_9CF(), A_LOWER_9CF(), ENG_CONFERENCE_NORTH_9CF(), 1, ENG_CONFERENCE_SOUTH_9CF());
	}
	else {
		generic_prom_rel(NATION_ENGLAND_9CF(), ENG_CONFERENCE_9CF(), ENG_LEAGUE_2_9CF(), 0);
		eng_extra_non_playable_swaps(_this);
	}
	eng_swap_between_lower_and_lower_b(_this);
	sort_conf_n_s_clubs();

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
	eng_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("eng_prm_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("eng_prm_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)eng_champ;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_champ);

	v1 = *(DWORD*)eng_league_1;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_league_1);

	v1 = *(DWORD*)eng_league_2;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_league_2);

	if (eng_conf) {
		v1 = *(DWORD*)eng_conf;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_conf);

		v1 = *(DWORD*)eng_conf_n;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_conf_n);

		v1 = *(DWORD*)eng_conf_s;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_conf_s);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) eng_premier_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call eng_premier_update
		add esp, 0x4
		ret
	}
}

DWORD eng_premier_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx < 0) {
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
		AddFixture(pMem, fixture_id, Date(year, 8, 16), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday); // doesn't work with CM0102 schedule
		//AddFixture(pMem, fixture_id, Date(year, 9, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 3), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		Date boxing_day = Date(year, 12, 26);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		boxing_day.addDays(4);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 3), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 7), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 17), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 7), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 11), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 4), year, Wednesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Tuesday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Thursday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 24), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else return 0;
}

void __declspec(naked) eng_premier_fixture_caller()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call eng_premier_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void eng_premier_init(BYTE* _this, WORD year, cm3_club_comps* comp) {
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = eng_premier_vtable;
	data->year = year;
	data->rules = RulesEngland;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	data->min_stadium_capacity = 5000;
	data->min_stadium_seats = 5000;
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	eng_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("eng_prm_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("eng_prm_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void setup_eng_premier()
{
	WriteVTablePtr(eng_premier_vtable, VTableEoSUpdate, (DWORD)&eng_premier_update_c);
	WriteVTablePtr(eng_premier_vtable, VTableFixtures, (DWORD)&eng_premier_fixture_caller);
	WriteVTablePtr(eng_premier_vtable, VTablePromRelUpdate, (DWORD)&eng_premier_prom_rel_update_c);
	WriteVTablePtr(eng_premier_vtable, VTableSubsRounds, (DWORD)&eng_premier_subs_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(eng_premier_vtable, VTable21, 0x4110b0);
	// Charity Shield day
	WriteBytes(0x56d718, 1, 10);
}