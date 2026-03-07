#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Structures\vtable.h"
#include "Helpers\constants.h"
#include <Helpers\9cf_constants.h>

DWORD* eng_premier_vtable = (DWORD*)0x969D1C;
static DWORD(__thiscall* eng_premier_subs)(BYTE* _this) = (DWORD(__thiscall*)(BYTE * _this))(0x574B70);

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

	sub_689C80(_this, _this, eng_champ, 1, a2, -1, -1);
	sub_689C80(_this, eng_champ, eng_league_1, 1, a2, -1, -1);
	sub_689C80(_this, eng_league_1, eng_league_2, 1, a2, -1, -1);

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

		// To do: stadium capacity validations
		sub_689C80(_this, eng_league_2, eng_conf, 1, a2, -1, -1);
		sub_689C80(_this, eng_conf, eng_conf_n, 1, a2, -1, -1);
		sub_689C80(_this, eng_conf, eng_conf_s, 1, a2, -1, -1);
	}
}

void __declspec(naked) eng_premier_prom_rel_update_c()		// used as a __thiscall -> __cdecl converter
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

void __fastcall eng_non_league_promotion(BYTE* _this)
{
	vector<cm3_clubs*> northern_relegated_clubs = get_relegated_teams(ENG_CONFERENCE_NORTH_9CF());
	vector<cm3_clubs*> southern_relegated_clubs = get_relegated_teams(ENG_CONFERENCE_SOUTH_9CF());
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
				if (nationID == NATION_ENGLAND_9CF() &&		// England
					compID != ENG_PREMIER_9CF() &&		// Premier Division
					compID != ENG_CHAMP_9CF() &&		// First Division
					compID != ENG_LEAGUE_1_9CF() &&		// Second Division
					compID != ENG_LEAGUE_2_9CF() &&		// Third Division
					compID != ENG_CONFERENCE_9CF() &&		// Conference
					compID != A_LOWER_B_9CF() &&		// A Lower Division B
					compID != ENG_CONFERENCE_NORTH_9CF() &&		// Northern Premier
					compID != ENG_CONFERENCE_SOUTH_9CF())		// Southern Premier
				{
					available_clubs.push_back(club);
				}
			}
		}
	}

	sort(available_clubs.begin(), available_clubs.end(), compareClubRep);
	int max_to_check = (available_clubs.size() > 12 ? 12 : available_clubs.size());
	unsigned int i;
	for (i = 0; i < northern_relegated_clubs.size(); i++)
	{
		int availableIdx = rand() % (max_to_check - i);
		cm3_clubs* clubToRelegate = northern_relegated_clubs[i];
		cm3_clubs* available = available_clubs[availableIdx];
		//dprintf("Swapping Teams: %s (%s) <-> %s (%s)\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, available->ClubName, available->ClubDivision->ClubCompName);

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = available->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)available, (DWORD)topDivision, 1);

		available_clubs.erase(available_clubs.begin() + availableIdx);
	}

	for (unsigned int j = 0; j < southern_relegated_clubs.size(); j++)
	{
		int availableIdx = rand() % (max_to_check - i - j);
		cm3_clubs* clubToRelegate = southern_relegated_clubs[j];
		cm3_clubs* available = available_clubs[availableIdx];

		//dprintf("Swapping Teams: %s (%s) <-> %s (%s)\n", clubToRelegate->ClubName, clubToRelegate->ClubDivision->ClubCompName, available->ClubName, available->ClubDivision->ClubCompName);

		cm3_club_comps* topDivision = clubToRelegate->ClubDivision;
		cm3_club_comps* bottomDivision = available->ClubDivision;
		relegate_club_6831A0((BYTE*)clubToRelegate, (DWORD)bottomDivision, 1);
		promote_club_6830B0((BYTE*)available, (DWORD)topDivision, 1);

		available_clubs.erase(available_clubs.begin() + availableIdx);
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
	BYTE* ebx = 0;
	data->f76 = 0;
	eng_premier_prom_rel_update(_this, 1);

	BYTE* eng_conf = get_loaded_league(ENG_CONFERENCE_9CF());
	if (eng_conf) {
		eng_non_league_promotion(_this);
		sort_conf_n_s_clubs();
	}
	else {
		sub_574E60(_this);
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
		}
	}
	data->year++;
	data->current_stage = -1;
	eng_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = add_prize_money_682F70(_this, 869000);
	data->f225 = 1;
	add_tv_money_683010(_this, 36000000, 0);
	sub_6835C0(_this);
	BYTE* edx = 0;
	sub_6827D0(_this, edx);
	DWORD v1 = *(DWORD*)_this;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x5C))(_this);

	BYTE* eng_champ = get_loaded_league(ENG_CHAMP_9CF());
	BYTE* eng_league_1 = get_loaded_league(ENG_LEAGUE_1_9CF());
	BYTE* eng_league_2 = get_loaded_league(ENG_LEAGUE_2_9CF());

	sub_68A980(eng_league_2, 1, 3, -3, 1);
	if (eng_conf) sub_68A980(eng_conf, 2, 0, -3, 1);

	v1 = *(DWORD*)eng_champ;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_champ);

	v1 = *(DWORD*)eng_league_1;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_league_1);

	v1 = *(DWORD*)eng_league_2;
	(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_league_2);

	if (eng_conf) {
		v1 = *(DWORD*)eng_conf;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_conf);

		BYTE* eng_conf_n = get_loaded_league(ENG_CONFERENCE_NORTH_9CF());
		v1 = *(DWORD*)eng_conf_n;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_conf_n);

		BYTE* eng_conf_s = get_loaded_league(ENG_CONFERENCE_SOUTH_9CF());
		v1 = *(DWORD*)eng_conf_s;
		(*(int(__thiscall**)(BYTE*))(v1 + 0x8))(eng_conf_s);
	}

	sub_68AA80(_this);
	return sub_79CEE0((BYTE*)*b74340, (BYTE*)(data->competition_db));
}

void __declspec(naked) eng_premier_update_c()		// used as a __thiscall -> __cdecl converter
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
		*num_rounds = (numberOfLeagueTeams - 1) * ((comp_stats*)_this)->n_rounds;
		*stage_name_id = None;

		pMem = (BYTE*)sub_944E46_malloc(fixture_dates_sz * (*num_rounds));

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
		tv_id = 0;
		AddFixture(pMem, fixture_id, Date(year + 1, 4, 25), year, Saturday);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Friday, Evening);
		AddFixtureTV(pMem, fixture_id, tv_id++, 2, Sunday, Afternoon);
		AddFixtureTV(pMem, fixture_id, tv_id++, 1, Monday, Evening);
		AddFixtureTV(pMem, fixture_id++, tv_id++);
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

void __declspec(naked) eng_premier_fixture_caller()		// used as a __thiscall -> __cdecl converter
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
	data->rules = 0x9;
	int loaded = sub_687B10(_this, 1);
	if (loaded) return;
	comp->ClubCompBackgroundColour = get_colour(COLOUR_PURPLE_2_9CF());
	comp->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	data->f68 = -1;
	data->current_stage = -1;
	data->num_stages = 0;
	eng_premier_subs(_this);
	AddTeams(_this);
	data->prize_money_pool = add_prize_money_682F70(_this, 869000);
	data->f225 = 1;
	add_tv_money_683010(_this, 36000000, 0);
	sub_6835C0(_this);
	BYTE* ebx = 0;
	sub_6827D0(_this, ebx);
	BYTE* pMem2 = (BYTE*)sub_944CF1_operator_new(0x5CE);
	BYTE unk1 = 1;
	sub_49EE70(pMem2, _this);
	unk1 = 0;
	data->f8 = (DWORD*)pMem2;
	reputation_setup_generic_68A850(_this);
}

void setup_eng_premier()
{
	WriteVTablePtr(eng_premier_vtable, VTableEoSUpdate, (DWORD)&eng_premier_update_c);
	WriteVTablePtr(eng_premier_vtable, VTableFixtures, (DWORD)&eng_premier_fixture_caller);
	WriteVTablePtr(eng_premier_vtable, VTablePromRelUpdate, (DWORD)&eng_premier_prom_rel_update_c);
	// Charity Shield day
	WriteBytes(0x56d718, 1, 10);
}

/*
005753E3   . 66:8B87 E20000>MOV AX,WORD PTR DS:[EDI+E2]
005753EA   . 8B57 04        MOV EDX,DWORD PTR DS:[EDI+4]
005753ED   . 66:8B8F E40000>MOV CX,WORD PTR DS:[EDI+E4]
005753F4   . 6A 01          PUSH 1
005753F6   . 8B12           MOV EDX,DWORD PTR DS:[EDX]
005753F8   . 0FBFC0         MOVSX EAX,AX
005753FB   . 0FBFC9         MOVSX ECX,CX
005753FE   . 52             PUSH EDX
005753FF   . 50             PUSH EAX
00575400   . 51             PUSH ECX
00575401   . 6A 00          PUSH 0
00575403   . 8BCD           MOV ECX,EBP
00575405   . E8 C6D21000    CALL cm0102.006826D0
0057540A   . 8B10           MOV EDX,DWORD PTR DS:[EAX]               ; |
0057540C   . 8B0D 382AAE00  MOV ECX,DWORD PTR DS:[AE2A38]            ; |
00575412   . 52             PUSH EDX                                 ; |/Arg1
00575413   . E8 78B10200    CALL cm0102.005A0590                     ; |\cm0102.005A0590
00575418   . 8BC8           MOV ECX,EAX                              ; |
0057541A   . E8 E1490200    CALL cm0102.00599E00                     ; \cm0102.00599E00
0057541F   . 84C0           TEST AL,AL
00575421   . 75 48          JNZ SHORT cm0102.0057546B
00575423   . 0FBF47 3E      MOVSX EAX,WORD PTR DS:[EDI+3E]
00575427   . 48             DEC EAX
00575428   . 8BCF           MOV ECX,EDI
0057542A   . 50             PUSH EAX
0057542B   . E8 A0D21000    CALL cm0102.006826D0
00575430   . 6A 02          PUSH 2
00575432   . 6A 00          PUSH 0
00575434   . 6A 00          PUSH 0
00575436   . 8BCD           MOV ECX,EBP
00575438   . C640 37 FE     MOV BYTE PTR DS:[EAX+37],0FE
0057543C   . E8 8FD21000    CALL cm0102.006826D0
00575441   . 8B08           MOV ECX,DWORD PTR DS:[EAX]               ; |
00575443   . A1 9CF69C00    MOV EAX,DWORD PTR DS:[9CF69C]            ; |
00575448   . 51             PUSH ECX                                 ; |Arg2
00575449   . 8D0C40         LEA ECX,DWORD PTR DS:[EAX+EAX*2]         ; |
0057544C   . 8D14C9         LEA EDX,DWORD PTR DS:[ECX+ECX*8]         ; |
0057544F   . 8B0D D023AE00  MOV ECX,DWORD PTR DS:[AE23D0]            ; |
00575455   . C1E2 02        SHL EDX,2                                ; |
00575458   . 2BD0           SUB EDX,EAX                              ; |
0057545A   . 03D1           ADD EDX,ECX                              ; |
0057545C   . 8BCF           MOV ECX,EDI                              ; |
0057545E   . 52             PUSH EDX                                 ; |Arg1
0057545F   . E8 7C98F1FF    CALL cm0102.0048ECE0                     ; \cm0102.0048ECE0
00575464   . 5F             POP EDI
00575465   . 5E             POP ESI
00575466   . 5D             POP EBP
00575467   . 5B             POP EBX
00575468   . C2 0400        RET 4
*/