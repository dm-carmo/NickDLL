#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* sco_premier_vtable = (DWORD*)0x96F608;

int sco_premier_7F3220(DWORD a1, DWORD a2) {
	BYTE split_pos = 6;
	WORD stage1_games = 33;
	team_league_stats* tls1 = (team_league_stats*)a1;
	team_league_stats* tls2 = (team_league_stats*)a2;

	BYTE bl = ((BYTE*)tls1->position_history)[stage1_games - 1];
	BYTE al = (bl >= split_pos) + 1;
	bl = ((BYTE*)tls2->position_history)[stage1_games - 1];
	BYTE cl = (bl >= split_pos) + 1;
	return al - cl;
}

void sco_premier_prom_rel_update(BYTE* _this, int a2) {
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(_this);

	BYTE* sco_champ = get_loaded_league(SCO_CHAMP_9CF());
	v1 = *(DWORD*)sco_champ;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(sco_champ);
	process_promotion_relegation_689C80(_this, _this, sco_champ, 1, a2, -1, -1);

	BYTE* sco_league_1 = get_loaded_league(SCO_LEAGUE_1_9CF());
	v1 = *(DWORD*)sco_league_1;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(sco_league_1);
	process_promotion_relegation_689C80(_this, sco_champ, sco_league_1, 1, a2, -1, -1);

	BYTE* sco_league_2 = get_loaded_league(SCO_LEAGUE_2_9CF());
	v1 = *(DWORD*)sco_league_2;
	(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(sco_league_2);
	process_promotion_relegation_689C80(_this, sco_league_1, sco_league_2, 1, a2, -1, -1);

	BYTE* sco_highland = get_loaded_league(SCO_HIGHLAND_9CF());
	if (sco_highland) {
		v1 = *(DWORD*)sco_highland;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(sco_highland);
	}

	BYTE* sco_lowland = get_loaded_league(SCO_LOWLAND_9CF());
	if (sco_lowland) {
		v1 = *(DWORD*)sco_lowland;
		(*(int(__thiscall**)(BYTE*))(v1 + 0xA4))(sco_lowland);
	}
}

void __declspec(naked) sco_premier_prom_rel_update_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x4]
		push ecx
		call sco_premier_prom_rel_update
		add esp, 0x8
		ret 4
	}
}

DWORD sco_premier_fixtures(BYTE* _this, char stage_idx, WORD* num_rounds, WORD* stage_name_id, DWORD* a5)
{
	if (stage_idx == -1) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		*num_rounds = 38;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		int tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 23), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 8, 30), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 9, 27), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 18), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 10, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 10, 29), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 1), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 8), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 22), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 11, 29), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year, 12, 3), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 6), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 13), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year, 12, 20), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		Date boxing_day = Date(year, 12, 27);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		boxing_day.addDays(3);
		AddFixtureNoTV(pMem, fixture_id++, boxing_day, year, (Day)boxing_day.DayOfWeek(), Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 3), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 10), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 24), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 1, 31), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 4), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 2, 11), year, Wednesday, Evening);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 2, 28), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 14), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 3, 21), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 4), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 11), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		// next phase starts here
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 13), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	else if (stage_idx == 0) {
		if (a5)
			*a5 = 0;
		BYTE* pMem = NULL;
		WORD year = ((comp_stats*)_this)->year;
		*num_rounds = 1;
		*stage_name_id = None;

		pMem = (BYTE*)cm0102_malloc(playoff_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddPlayoffDrawFixture(pMem, fixture_id, Date(year + 1, 5, 18), year, Monday);
		AddPlayoffFixture(pMem, fixture_id, Date(year + 1, 5, 21), year, Thursday, Evening);
		FillFixtureDetails(pMem, fixture_id++, Playoff, 0, FixedTeamOrderInCup + NoTiebreak_1, ExtraTimePenaltiesNoAwayGoals_2, 5, 2, 1, 2, 0, 0, 2, 3);

		return (DWORD)pMem;
	}
	else if (stage_idx < 3) {
		if (a5)
			*a5 = 1;
		BYTE* pMem = NULL;
		comp_stats* data = (comp_stats*)_this;
		WORD year = data->year;
		DWORD CompID = data->competition_db->ClubCompID;
		*num_rounds = 5;
		*stage_name_id = ChampionshipGroup + stage_idx - 1;

		pMem = (BYTE*)cm0102_malloc(fixture_dates_sz * (*num_rounds));

		int fixture_id = 0;
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 2), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 9), year, Saturday);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 13), year, Wednesday, Evening);
		AddFixtureNoTV(pMem, fixture_id++, Date(year + 1, 5, 17), year, Sunday);

		check_number_of_fixtures(_this, fixture_id, *num_rounds);

		return (DWORD)pMem;
	}
	return 0;
}

void __declspec(naked) sco_premier_fixtures_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x10]
		push dword ptr[eax + 0xC]
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_premier_fixtures
		add esp, 0x14
		ret 0x10
	}
}

void sco_premier_subs(BYTE* _this)
{
	comp_stats* comp_data = (comp_stats*)_this;

	comp_data->n_rounds = 3;
	*((WORD*)(_this + 0xA7)) = 38; // total number of games each team will play
	*((DWORD*)(_this + 0xA3)) = 0;
	comp_data->pts_for_win = 3;
	comp_data->pts_for_draw = 1;
	comp_data->f196 = 2;
	comp_data->comp_type = CLUB_DOMESTIC;
	comp_data->tiebreaker_1 = GoalDifferenceTiebreaker;
	comp_data->tiebreaker_2 = GoalsForTiebreaker;
	comp_data->tiebreaker_3 = CurrentPositionTiebreaker;
	comp_data->promotions = 0;
	comp_data->prom_playoff = 0;
	comp_data->rele_playoff = 1;
	comp_data->relegations = 1;

	comp_data->promotes_to = -1;
	comp_data->relegates_to = SCO_CHAMP_9CF();

	comp_data->f82 = 2;
	comp_data->max_bench = 7;
	comp_data->max_subs = 3;

	DWORD v1 = *(DWORD*)_this;
	comp_data->fixtures_table = (DWORD*)(*(int(__thiscall**)(BYTE*, int, BYTE*, BYTE*, DWORD))(v1 + 0x3C))(_this, -1, _this + 0xA9, _this + 0x3A, 0);

	return;
}

void __declspec(naked) sco_premier_subs_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_premier_subs
		add esp, 0x4
		ret
	}
}

void __fastcall sco_league_2_relegation()
{
	cm3_clubs* relegate = 0;
	BYTE* comp_bytes = get_loaded_league(SCO_LEAGUE_2_9CF());
	comp_stats* comp_data = (comp_stats*)comp_bytes;
	for (WORD num = 0; num < comp_data->n_teams; num++) {
		team_league_stats table_pos = ((team_league_stats*)comp_data->team_league_table)[num];
		if (table_pos.league_fate == Relegated) {
			relegate = table_pos.club;
			break;
		}
	}

	cm3_clubs* promote = 0;
	comp_stats* playoff_stage = (comp_stats*)comp_data->stages[0];
	WORD promoted_teams = 0;
	for (WORD i = 0; i < playoff_stage->n_teams; i++) {
		teams_seeded t = ((teams_seeded*)playoff_stage->teams_list)[i];
		if (t.f6 == 1) {
			if (t.club->ClubDivision && t.club->ClubDivision != comp_data->competition_db) {
				promote = t.club;
				break;
			}
		}
	}

	if (promote && relegate) {
		cm3_club_comps* relegate_to = promote->ClubDivision;
		promote_club_6830B0((BYTE*)promote, (DWORD)comp_data->competition_db, 1);
		relegate_club_6831A0((BYTE*)relegate, (DWORD)relegate_to, 1);
	}
}

void sort_high_low_clubs() {
	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(SCO_HIGHLAND_9CF());
	vector<cm3_clubs*> lowland_clubs = find_clubs_of_comp(SCO_LOWLAND_9CF());
	move(lowland_clubs.begin(), lowland_clubs.end(), back_inserter(available_clubs));
	sort(available_clubs.begin(), available_clubs.end(), compareClubLatitude);

	for (size_t i = 0; i < available_clubs.size(); i++)
	{
		if (i < 18) available_clubs[i]->ClubDivision = get_comp(SCO_HIGHLAND_9CF());
		else available_clubs[i]->ClubDivision = get_comp(SCO_LOWLAND_9CF());
	}
}

void __fastcall sco_extra_non_playable_swaps(BYTE* _this)
{
	vector<cm3_clubs*> high_clubs = find_clubs_of_comp(SCO_HIGHLAND_9CF());
	vector<cm3_clubs*> low_clubs = find_clubs_of_comp(SCO_LOWLAND_9CF());
	vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_SCOTLAND_9CF());

	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(lower_clubs, 2, true);
	vector<cm3_clubs*> relegated_clubs = get_random_weighted_clubs(high_clubs, 1, false);
	vector<cm3_clubs*> relegated_clubs2 = get_random_weighted_clubs(low_clubs, 1, false);
	move(relegated_clubs2.begin(), relegated_clubs2.end(), back_inserter(relegated_clubs));

	for (unsigned int j = 0; j < 2; j++) {
		cm3_clubs* clubToRelegate = relegated_clubs[j];
		cm3_clubs* clubToPromote = promoted_clubs[j];

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = clubToPromote->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)clubToPromote, (DWORD)topDivision, 1);
	}
}

void __fastcall sco_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> relegated_clubs = get_relegated_teams(SCO_HIGHLAND_9CF());

	comp_stats* comp_data = (comp_stats*)get_loaded_league(SCO_LOWLAND_9CF());
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

	vector<cm3_clubs*> available_clubs = find_clubs_of_comp(A_LOWER_9CF(), NATION_SCOTLAND_9CF());
	vector<cm3_clubs*> promoted_clubs = get_random_weighted_clubs(available_clubs, relegated_clubs.size() - (comp_data->year == 2026 ? 1 : 0), true);

	for (cm3_clubs* c : relegated_clubs) {
		cm3_club_comps* bottomDivision = get_comp(A_LOWER_9CF());
		relegate_club_6831A0((BYTE*)c, (DWORD)bottomDivision, 1);
		c->ClubReserveDivision = 0;
	}

	for (cm3_clubs* c : promoted_clubs) {
		cm3_club_comps* topDivision = get_comp(SCO_HIGHLAND_9CF());
		promote_club_6830B0((BYTE*)c, (DWORD)topDivision, 1);
	}
}

char sco_premier_update(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	data->f76 = 0;

	BYTE* sco_champ = get_loaded_league(SCO_CHAMP_9CF());
	BYTE* sco_league_1 = get_loaded_league(SCO_LEAGUE_1_9CF());
	BYTE* sco_league_2 = get_loaded_league(SCO_LEAGUE_2_9CF());
	BYTE* sco_highland = get_loaded_league(SCO_HIGHLAND_9CF());
	BYTE* sco_lowland = get_loaded_league(SCO_LOWLAND_9CF());

	// All teams that were in D1 must be professional
	update_club_pro_status_68A980(_this, Professional, Relegated, -3, 1);
	update_club_pro_status_68A980(_this, Professional, -3, Relegated, 1);
	// All teams that were in D2 must be semi-professional or higher
	update_club_pro_status_68A980(sco_champ, SemiProfessional, Relegated, -3, 1);
	update_club_pro_status_68A980(sco_champ, SemiProfessional, -3, Relegated, 1);
	// All teams that were in D3 must be semi-professional or higher
	update_club_pro_status_68A980(sco_league_1, SemiProfessional, Relegated, -3, 1);
	update_club_pro_status_68A980(sco_league_1, SemiProfessional, -3, Relegated, 1);
	// All teams that were not relegated from D4 must be semi-professional or higher
	update_club_pro_status_68A980(sco_league_2, SemiProfessional, Relegated, -3, 1);
	// All teams that were relegated from D4 must be semi-professional or lower
	update_club_pro_status_68A980(sco_league_2, SemiProfessional, -3, Relegated, 0);
	if (sco_highland && sco_lowland)
	{
		// All teams that were relegated from D5 must be amateur
		update_club_pro_status_68A980(sco_highland, Amateur, -3, Relegated, 0);
		update_club_pro_status_68A980(sco_lowland, Amateur, -3, Relegated, 0);
		comp_stats* sco_lowland_data = (comp_stats*)sco_lowland;
		BYTE* sco_lowland_grp = (BYTE*)sco_lowland_data->stages[0];
		update_club_pro_status_68A980(sco_lowland_grp, Amateur, -3, Relegated, 0);
	}

	DWORD v1 = *(DWORD*)_this;
	sco_premier_prom_rel_update(_this, 1);
	if (sco_highland && sco_lowland) {
		sco_non_league_promotion(_this);
	}
	else {
		sco_extra_non_playable_swaps(_this);
	}

	sco_league_2_relegation();
	sort_high_low_clubs();

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
	if (data->f8) sub_4A1C50((BYTE*)(data->f8), 1);
	data->year++;
	data->current_stage = -1;
	sco_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("sco_prm_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("sco_prm_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	v1 = *(DWORD*)sco_champ;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(sco_champ);

	v1 = *(DWORD*)sco_league_1;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(sco_league_1);

	v1 = *(DWORD*)sco_league_2;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(sco_league_2);

	if (sco_highland) {
		v1 = *(DWORD*)sco_highland;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(sco_highland);
	}

	if (sco_lowland) {
		v1 = *(DWORD*)sco_lowland;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(sco_lowland);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) sco_premier_update_c()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_premier_update
		add esp, 0x4
		ret
	}
}

void sco_premier_init(BYTE* _this, WORD year, cm3_club_comps* comp)
{
	sub_682200(_this);
	comp_stats* data = (comp_stats*)_this;
	data->competition_db = comp;
	data->comp_vtable = sco_premier_vtable;
	data->year = year;
	data->rules = RulesScotlandLeague;
	int loaded = sub_687B10(_this, 1);
	if (loaded) {
		if (data->n_rounds != 4) return;
		*((DWORD*)(_this + 0xA3)) = (DWORD)&sco_premier_7F3220;
		return;
	}
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 1;
	data->stages = (DWORD*)cm0102_malloc(data->num_stages * 4);
	sco_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = SetupPrizeMoney(_this, prizeMoneyFile.GetInt("sco_prm_prize_money"));
	data->f225 = 1;
	SetupTVMoney(_this, prizeMoneyFile.GetInt("sco_prm_tv_money"), 0);
	sub_6835C0(_this);
	sub_6827D0(_this, 0);
	BYTE* pMem2 = (BYTE*)cm0102_new(0x5CE);
	sub_49EE70(pMem2, _this);
	data->f8 = (DWORD*)pMem2;
	league_reputation_setup_generic_68A850(_this);
}

void sco_premier_split_under(BYTE* _this) {
	comp_stats* data = (comp_stats*)_this;
	BYTE playoff_teams = 6;
	WORD total_teams = data->n_teams;
	team_league_stats* table_teams = (team_league_stats*)(data->team_league_table);

	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);
	for (int i = 0; i < 6; i++) {
		*((DWORD*)(&pTeams[i])) = (DWORD)table_teams[i].club;
	}

	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	DWORD v0 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 1, &num_rounds, &stage_name_id, 0);

	WORD year = data->year;
	BYTE* pStage = (BYTE*)cm0102_new(0xEE);
	short f217 = 3;
	create_league_stage_data(pStage, _this, playoff_teams, pTeams, 1, (DWORD)(data->competition_db), pFixtures, num_rounds,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, -1, stage_name_id, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v1 = *(DWORD*)pStage;
	(*(int(__thiscall**)(BYTE*, int))(v1))(pStage, 1);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);

	DWORD* pTeams2 = (DWORD*)cm0102_malloc(playoff_teams * 4);
	for (int i = 0; i < 6; i++) {
		*((DWORD*)(&pTeams2[i])) = (DWORD)table_teams[i + 6].club;
	}

	WORD num_rounds2 = 0;
	WORD stage_name_id2 = 0;
	BYTE* pFixtures2 = (BYTE*)(*(int(__thiscall**)(BYTE*, int, WORD*, WORD*, DWORD))(v0 + 0x3C))(_this, 2, &num_rounds2, &stage_name_id2, 0);

	BYTE* pStage2 = (BYTE*)cm0102_new(0xEE);
	create_league_stage_data(pStage2, _this, playoff_teams, pTeams2, 1, (DWORD)(data->competition_db), pFixtures2, num_rounds2,
		data->pts_for_win, data->pts_for_draw, data->f196, &data->tiebreaker_1, &data->promotions,
		year, -1, stage_name_id2, 0x14, 1, 0, f217, -1, 0, 2);
	DWORD v2 = *(DWORD*)pStage2;
	(*(int(__thiscall**)(BYTE*, int))(v2))(pStage2, 1);
	sub_9452CA_free(pTeams2);
	sub_9452CA_free(pFixtures2);

	data->n_rounds = 4;
	*((DWORD*)(_this + 0xA3)) = (DWORD)&sco_premier_7F3220;
}

char sco_premier_table_split(BYTE* _this, DWORD current_date, int a2) {
	if (a2) {
		comp_stats* comp_data = (comp_stats*)_this;
		if (comp_data->n_rounds == 3) {
			WORD num_teams = comp_data->n_teams;
			team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
			bool is_finished = true;
			for (int i = 0; i < num_teams; i++) {
				team_league_stats tls = table_teams[i];
				if (tls.games < 33) {
					is_finished = false;
					break;
				}
			}
			if (is_finished) {
				sco_premier_split_under(_this);
			}
		}
	}
	return sub_6847C0(_this, current_date, a2);
}

void __declspec(naked) sco_premier_table_split_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_premier_table_split
		add esp, 0xc
		ret 8
	}
}

void sco_premier_playoff_under(BYTE* _this) {
	char stage_num = 0;
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE playoff_teams = 2;
	WORD total_teams = comp_data->n_teams;
	DWORD* pTeams = (DWORD*)cm0102_malloc(playoff_teams * 4);

	team_league_stats* table_teams = (team_league_stats*)(comp_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == BottomPlayoff) {
			*((DWORD*)(&pTeams[0])) = (DWORD)tls.club;
			break;
		}
	}

	comp_stats* sco_first_data = (comp_stats*)get_loaded_league(SCO_CHAMP_9CF());
	total_teams = sco_first_data->n_teams;
	table_teams = (team_league_stats*)(sco_first_data->team_league_table);
	for (int i = 0; i < total_teams; i++) {
		team_league_stats tls = table_teams[i];
		if (tls.league_fate == TopPlayoff) {
			*((DWORD*)(&pTeams[1])) = (DWORD)tls.club;
			break;
		}
	}
	WORD num_rounds = 0;
	WORD stage_name_id = 0;
	WORD year = comp_data->year;
	DWORD v1 = *(DWORD*)_this;
	BYTE* pFixtures = (BYTE*)(*(int(__thiscall**)(BYTE*, char, WORD*, WORD*, DWORD))(v1 + 0x3C))(_this, stage_num, &num_rounds, &stage_name_id, 0);
	BYTE* new_stage = (BYTE*)cm0102_new(0xB2);
	create_cup_stage_data(new_stage, _this, playoff_teams, pTeams, num_rounds, (DWORD)comp_data->competition_db, pFixtures, year, stage_num, 1, stage_name_id, 0x14, 0, 0, 0, 0);
	DWORD* stages_arr = comp_data->stages;
	*((DWORD*)(&stages_arr[stage_num])) = (DWORD)new_stage;
	sub_51C800(new_stage, 0);
	sub_9452CA_free(pTeams);
	sub_9452CA_free(pFixtures);
}

void sco_premier_playoffs_c(BYTE* _this) {
	comp_stats* comp_data = (comp_stats*)_this;
	long current = comp_data->current_stage;
	long max = comp_data->num_stages;
	if (current < max - 1) {
		BYTE* sco_champ = get_loaded_league(SCO_CHAMP_9CF());
		comp_stats* sco_champ_data = (comp_stats*)sco_champ;
		BYTE* prom_playoff = (BYTE*)sco_champ_data->stages[0];
		if (prom_playoff) {
			DWORD v1 = *(DWORD*)prom_playoff;
			char ret = (*(int(__thiscall**)(BYTE*, int, int))(v1 + 0x10))(prom_playoff, 0, 1);
			if (ret != 0) {
				current++;
				if (current == 0) {
					comp_data->current_stage = current;
					sco_premier_playoff_under(_this);
				}
			}
		}
	}
}

void __declspec(naked) sco_premier_playoffs_create()
{
	__asm
	{
		mov eax, esp
		push ecx
		call sco_premier_playoffs_c
		add esp, 0x4
		ret
	}
}

int sco_premier_table_indicators(BYTE* _this, cm3_clubs* club, BYTE fate, char stage, BYTE* a5, BYTE* round_data, int a7) {
	BYTE* staff_hist_ptr = (BYTE*)*staff_history;
	comp_stats* comp_data = (comp_stats*)_this;
	if (stage == 0) {
		cm3_clubs* club_ptr = (cm3_clubs*)club;
		cm3_club_comps* sco_champ = get_comp(SCO_CHAMP_9CF());
		BYTE* rounds = ((comp_stats*)(comp_data->stages[stage]))->rounds_list;
		if (club_ptr->ClubDivision == sco_champ) {
			comp_stats* sco_first_data = (comp_stats*)get_loaded_league(SCO_CHAMP_9CF());
			WORD num_teams = sco_first_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(sco_first_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case TopPlayoff:
					staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)sco_champ, 0x32);
					table[i].league_fate = Promoted;
					*a5 = 1;
					return 0;
				case Promoted:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
		else {
			WORD num_teams = comp_data->n_teams;
			if (num_teams <= 0) return 0;
			team_league_stats* table = (team_league_stats*)(comp_data->team_league_table);
			WORD current_round = *(WORD*)(round_data + 0x34);
			for (int i = 0; i < num_teams; i++) {
				if (table[i].club != club) continue;
				switch (fate) {
				case BottomPlayoff:
					staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
					table[i].league_fate = Relegated;
					*a5 = 1;
					return 0;
				case Relegated:
					staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), *(WORD*)(round_data + 0x32),
						*(WORD*)(rounds + playoff_dates_sz * (current_round + 1) + 7), 0xF);
					return 0;
				default:
					table[i].league_fate = Eliminated;
					return 0;
				}
			}
		}
	}
	else {
		switch (fate) {
		case Champions:
			staff_history_champion_868C50(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		case Promoted:
			staff_history_promoted_869480(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), 0x64);
			return 0;
		case TopPlayoff:
			return 0;
		case BottomPlayoff:
			staff_history_qualified_86BDD0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db), None, Playoff, 0x1E);
			return 0;
		case Relegated:
			staff_history_relegated_86A1C0(staff_hist_ptr, club, (DWORD)(comp_data->competition_db));
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}

void __declspec(naked) sco_premier_set_table_fate()
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
		call sco_premier_table_indicators
		add esp, 0x1c
		ret 0x18
	}
}

void sco_premier_reputation_calc(BYTE* _this, BYTE* club, char stage, char current, char min, char max) {
	comp_stats* comp_data = (comp_stats*)_this;
	BYTE* ret = (BYTE*)sub_4A4850((BYTE*)comp_data->f8, club);
	if (!ret) return;
	char ret_current = current;
	char ret_min = min;
	char ret_max = max;
	if (stage == 0) {
		comp_stats* d2_comp_data = (comp_stats*)get_loaded_league(SCO_CHAMP_9CF());
		cm3_clubs* club_data = (cm3_clubs*)club;
		if (club_data->ClubDivision->ClubCompID == SCO_CHAMP_9CF()) {
			ret = (BYTE*)sub_4A4850((BYTE*)d2_comp_data->f8, club);
			if (!ret) return;
			ret_current = 2;
			ret_min = 2;
			ret_max = 2;
		}
		else {
			ret_current = 11;
			ret_min = 11;
			ret_max = 11;
		}
	}
	ret[0x73] = ret_current;
	ret[0x74] = ret_min;
	ret[0x75] = ret_max;
}

void __declspec(naked) sco_premier_reputation_calc_c()
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
		call sco_premier_reputation_calc
		add esp, 0x18
		ret 0x14
	}
}

void setup_sco_premier()
{
	WriteVTablePtr(sco_premier_vtable, VTableSubsRounds, (DWORD)&sco_premier_subs_c);
	WriteVTablePtr(sco_premier_vtable, VTableEoSUpdate, (DWORD)&sco_premier_update_c);
	WriteVTablePtr(sco_premier_vtable, VTableFixtures, (DWORD)&sco_premier_fixtures_c);
	WriteVTablePtr(sco_premier_vtable, VTableLeagueSplit, (DWORD)&sco_premier_table_split_c);
	WriteVTablePtr(sco_premier_vtable, VTableReputationCalc, (DWORD)&sco_premier_reputation_calc_c);
	WriteVTablePtr(sco_premier_vtable, VTablePlayoffQual, (DWORD)&sco_premier_playoffs_create);
	WriteVTablePtr(sco_premier_vtable, VTableTableFates, (DWORD)&sco_premier_set_table_fate);
	WriteVTablePtr(sco_premier_vtable, VTablePromRelUpdate, (DWORD)&sco_premier_prom_rel_update_c);
	if (configFile.GetBool("showThirdPlaceInHistory", true)) WriteVTablePtr(sco_premier_vtable, VTableShowThirdInHistory, 0x4110b0);
}