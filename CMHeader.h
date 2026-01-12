#pragma once
#include <windows.h>

// text lengths
#define LONG_TXT_LENGTH 101
#define STANDARD_TXT_LENGTH 51
#define SHORT_TXT_LENGTH 26

#define SI_DOUBLE double

enum CompetitionType : char {
	CLUB_DOMESTIC = 1,
	CLUB_INTERNATITONAL = 2,
	NATION_INTERNATIONAL = 4
};

enum RoundNames {
	None = 0,
	FirstRound = 0x0A,
	SecondRound = 0x14,
	ThirdRound = 0x1E,
	FourthRound = 0x28,
	FifthRound = 0x32,
	SixthRound = 0x3C,
	SeventhRound = 0x46,
	EighthRound = 0x50,
	NinthRound = 0x5A,
	TenthRound = 0x64,
	EleventhRound = 0x6E,
	QuarterFinal = 0x78,
	SemiFinal = 0x82,
	ThirdPlacePlayoff = 0x8C,
	Final = 0x96,
	Playoff = 0xA0,
	Playout = 0xBE,
	QualifyingRound = 0xDC,
	PreliminaryRound = 0xE6,
	FirstQualifyingPhase = 0xFA,
	SecondQualifyingPhase = 0x104,
	ThirdQualifyingPhase = 0x10E,
	Playoff1 = 0x118,
	Playoff2 = 0x122,
	NumericGroupStage = 0x3E8,
	CarribeanZone = 0x40F,
	MLSCup = 0x417,
	NorthernSouthernSection = 0x41D,
	AlphabeticGroupStage = 0x420,
	OpeningStage = 0x434,
	ClosingStage = 0x435,
	Promotion = 0x438,
	ChampionshipGroup = 0x44B,
	RelegationGroup = 0x44C,
	RelegationPlayoff = 0x452,
	NorthSouthCentral = 0x453,
	PromotionPlayoff = 0x458,
	SecondPromotionPlayoff = 0x45A,
	ThirdPromotionPlayoff = 0x45B,
	FourthPromotionPlayoff = 0x45C,
	CentralAmericanZoneGroup1 = 0x473,
	ClassificationGroup1 = 0x475,
	EastWest = 0x480
};

enum Game1Tiebreaks {
	NoTiebreak_1 = 0,
	PenaltiesNoExtraTime_1 = 1,
	ExtraTimeNoPenalties_1 = 2,
	ExtraTimePenalties_1 = 3,
	Libertadores_1 = 4,
	GoldenGoal_1 = 83
};

enum Game2Tiebreaks {
	NoTiebreak_2 = 0,
	AwayGoalsPenaltiesNoExtraTime_2 = 1,
	AwayGoalsExtraTimePenalties_2 = 3,
	ExtraTimePenaltiesNoAwayGoals_2 = 7,
	GoldenGoal_2 = 83
};

enum Game3Tiebreaks {
	NoTiebreak_3 = 0,
	ExtraTimePenalties_3 = 3
};

enum StadiumType {
	HomeStadium = 0,
	VenueUnknown_1 = 1,
	Neutral30k_2 = 2,
	Neutral30k_3 = 3,
	NationalStadium = 4,
	LargestStadiumNeutral = 5,
	NeutralStadium = 8,
	VenueUnknown_10 = 0x10,
	Neutral50k_20 = 0x20,
	FACupSemiFinals = 0x2A,
	LargestStadium1 = 0x40,
	LargestStadium2 = 0x80,
	LargestStadium3 = 0x100,
	LargestStadium4 = 0x200,
	LargestStadium5 = 0x400,
	LargestStadium6 = 0x800,
	LargestStadium7 = 0x1000,
	LargestStadium8 = 0x2000,
	LargestStadium9 = 0x4000,
	StadeLouisII = 0x8000
};

typedef struct cm3_continents CM3_CONTINENTS;
typedef struct cm3_club_comps CM3_CLUB_COMPS;
typedef struct cm3_club_comp_history CM3_CLUB_COMP_HISTORY;
typedef struct cm3_nations CM3_NATIONS;
typedef struct cm3_cities CM3_CITIES;
typedef struct cm3_stadiums CM3_STADIUMS;
typedef struct cm3_colours CM3_COLOURS;
typedef struct cm3_clubs CM3_CLUBS;

#define CM3_STAFF DWORD*

struct cm3_continents
{
	// original data
	long ContinentID;
	char ContinentName[SHORT_TXT_LENGTH];
	char ContinentGenderName;
	char ContinentNameThreeLetter[4];
	char ContinentNameContinentality[SHORT_TXT_LENGTH];
	char ContinentFederationName[LONG_TXT_LENGTH];
	char ContinentGenderFederationName;
	char ContinentFederationNameShort[SHORT_TXT_LENGTH];
	char ContinentGenderFederationNameShort;
	SI_DOUBLE ContinentRegionalStrength;
};

#pragma pack(push, 1)
struct cm3_nations
{
	// original data
	long NationID;
	char NationName[STANDARD_TXT_LENGTH];
	char NationGenderName;
	char NationNameShort[SHORT_TXT_LENGTH];
	char NationGenderNameShort;
	char NationNameThreeLetter[4];
	char NationNameNationality[SHORT_TXT_LENGTH];
	CM3_CONTINENTS* NationContinent;
	char NationRegion;
	char NationActualRegion;
	char NationFirstLanguage;
	char NationSecondLanguage;
	char NationThirdLanguage;
	CM3_CITIES* NationCapitalCity;
	char NationStateOfDevelopment;
	char NationGroupMembership;
	CM3_STADIUMS* NationNationalStadium;
	char NationGameImportance;
	char NationLeagueStandard;
	short NationNumberClubs;
	long NationNumberStaff; // Version 0x02 - Added
	short NationSeasonUpdateDay; // Version 0x02 - Added
	short NationReputation; // Version 0x02 - Changed char->short
	CM3_COLOURS* NationForegroundColour1;
	CM3_COLOURS* NationBackgroundColour1;
	CM3_COLOURS* NationForegroundColour2;
	CM3_COLOURS* NationBackgroundColour2;
	CM3_COLOURS* NationForegroundColour3;
	CM3_COLOURS* NationBackgroundColour3;
	SI_DOUBLE NationFIFACoefficient;
	SI_DOUBLE NationFIFACoefficient91;
	SI_DOUBLE NationFIFACoefficient92;
	SI_DOUBLE NationFIFACoefficient93;
	SI_DOUBLE NationFIFACoefficient94;
	SI_DOUBLE NationFIFACoefficient95;
	SI_DOUBLE NationFIFACoefficient96;
	SI_DOUBLE NationUEFACoefficient91;
	SI_DOUBLE NationUEFACoefficient92;
	SI_DOUBLE NationUEFACoefficient93;
	SI_DOUBLE NationUEFACoefficient94;
	SI_DOUBLE NationUEFACoefficient95;
	SI_DOUBLE NationUEFACoefficient96;
	CM3_NATIONS* NationRivals1;
	CM3_NATIONS* NationRivals2;
	CM3_NATIONS* NationRivals3;

	// runtime data
	char NationLeagueSelected;
	long NationShortlistOffset; // Version 0x02 - Added
	char NationGamesPlayed; // Version 0x02 - Moved to runtime

	// char padding[291];  // Padding for other nations table??
};
#pragma pack(pop)

#pragma pack(push, 1)
struct cm3_cities
{
	// original data
	long CityID;
	char CityName[SHORT_TXT_LENGTH];
	char CityGenderName;
	CM3_NATIONS* CityNation;
	SI_DOUBLE CityLatitude;
	SI_DOUBLE CityLongitude;
	char CityAttraction;
	long CityWeather;
	// CITY_WEATHER *CityWeatherCity; // Weather city to use for this cities weather
};
#pragma pack(pop)

#pragma pack(push, 1)
struct cm3_colours
{
	long ColourID;
	char ColourName[STANDARD_TXT_LENGTH];
	unsigned char ColourRedIntensity;
	unsigned char ColourGreenIntensity;
	unsigned char ColourBlueIntensity;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct cm3_stadiums
{
	// original data
	long StadiumID;
	char StadiumName[STANDARD_TXT_LENGTH];
	char StadiumGenderName;
	CM3_CITIES* StadiumCity;
	long StadiumCapacity;
	long StadiumSeatingCapacity;
	long StadiumExpansionCapacity;
	CM3_STADIUMS* StadiumNearbyStadium;
	char StadiumCovered;
	char StadiumUnderSoilHeating;
};
#pragma pack(pop)

// club staff table sizes
#define DIRECTOR_SIZE 3
#define SQUAD_SIZE 50
#define SCOUT_SIZE 7
#define COACH_SIZE 5
#define PHYSIO_SIZE 3

// Maximum number of tactics in training at once
#define MAX_TACTIC_TRAINING 4

// Maximum size of a squad for a match
#define TEAM_SZ 20

#pragma pack(push, 1)
struct cm3_clubs
{
	// original data
	long ClubID;
	char ClubName[STANDARD_TXT_LENGTH];
	char ClubGenderName;
	char ClubNameShort[SHORT_TXT_LENGTH];
	char ClubGenderNameShort;
	CM3_NATIONS* ClubNation;
	CM3_CLUB_COMPS* ClubDivision;
	CM3_CLUB_COMPS* ClubLastDivision;
	char ClubLastPosition;
	CM3_CLUB_COMPS* ClubReserveDivision;
	char ClubProfessionalStatus;
	long ClubCash;
	CM3_STADIUMS* ClubStadium;
	char ClubOwnStadium;
	CM3_STADIUMS* ClubReserveStadium;
	char ClubHomeMatchDay;
	long ClubAttendance;
	long ClubMinAttendance;
	long ClubMaxAttendance;
	char ClubTraining;
	short ClubReputation; // Version 0x02 - Changed char->short
	char ClubPLC;
	CM3_COLOURS* ClubForegroundColour1;
	CM3_COLOURS* ClubBackgroundColour1;
	CM3_COLOURS* ClubForegroundColour2;
	CM3_COLOURS* ClubBackgroundColour2;
	CM3_COLOURS* ClubForegroundColour3;
	CM3_COLOURS* ClubBackgroundColour3;
	CM3_STAFF* ClubFavouriteStaff1;
	CM3_STAFF* ClubFavouriteStaff2;
	CM3_STAFF* ClubFavouriteStaff3;
	CM3_STAFF* ClubDislikedStaff1;
	CM3_STAFF* ClubDislikedStaff2;
	CM3_STAFF* ClubDislikedStaff3;
	CM3_CLUBS* ClubRivals1;
	CM3_CLUBS* ClubRivals2;
	CM3_CLUBS* ClubRivals3;
	CM3_STAFF* ClubChairman;
	CM3_STAFF* ClubDirectorList[DIRECTOR_SIZE];
	CM3_STAFF* ClubManager;
	CM3_STAFF* ClubAssistantManager;
	CM3_STAFF* ClubSquadList[SQUAD_SIZE];
	CM3_STAFF* ClubCoachList[COACH_SIZE];
	CM3_STAFF* ClubScoutList[SCOUT_SIZE];
	CM3_STAFF* ClubPhysioList[PHYSIO_SIZE];

	// runtime data
	long ClubEuroFlag;			// ID of the Euro Competition?
	char ClubEuroSeeding;
	CM3_STAFF* ClubTeamSelected[TEAM_SZ];
	long ClubTacticTraining[MAX_TACTIC_TRAINING];
	long ClubTacticSelected;
	char ClubHasLinkedClub;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct cm3_club_comps
{
	long ClubCompID;
	char ClubCompName[STANDARD_TXT_LENGTH];
	char ClubCompGenderName;
	char ClubCompNameShort[SHORT_TXT_LENGTH];
	char ClubCompGenderNameShort;
	char ClubCompNameThreeLetter[4];
	char ClubCompScope;
	char ClubCompSelected;
	CM3_CONTINENTS* ClubCompContinent;
	CM3_NATIONS* ClubCompNation;
	CM3_COLOURS* ClubCompForegroundColour;
	CM3_COLOURS* ClubCompBackgroundColour;
	short ClubCompReputation; // Version 0x02 - Changed char->short
};
#pragma pack(pop)

#pragma pack(push, 1)
struct cm3_club_comp_history
{
	long ClubCompHistoryID;
	CM3_CLUB_COMPS* ClubCompHistoryClubComp;
	short ClubCompHistoryYear;
	CM3_CLUBS* ClubCompHistoryWinners;
	CM3_CLUBS* ClubCompHistoryRunnersUp;
	CM3_CLUBS* ClubCompHistoryThirdPlaced;
	CM3_CLUBS* ClubCompHistoryHosts;
};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct comp
{
	DWORD* comp_vtable;								//0
	CM3_CLUB_COMPS* competition_db;					//4	
	DWORD* f8;										//8
	DWORD* stages;									//12
	char pad16[12];									//16
	long promotes_to;								//28
	long relegates_to;								//32
	long f36;										//36
	char pad40[4];									//40
	long num_stages;								//44
	long current_stage;								//48
	char pad48[6];									//52
	WORD n_games;									//58
	WORD n_rounds;									//60
	WORD n_teams;									//62
	WORD year;										//64
	CompetitionType comp_type;						//66
	char f67;										//67
	char f68;										//68
	char pad73[4];									//69
	char max_bench;									//73
	char max_subs;									//74
	char pad80[5];									//75
	char rules;										//80
	char f81;										//81
	char f82;										//82
	char tmp_file_name[80];							//83
	BYTE* rounds_list;								//163
	DWORD* teams_list;								//167
	char f171;										//171
	char f172;										//172
	unsigned int pad173;							//173
	DWORD* team_league_table;						//177
	char pad181[5];									//181
	DWORD* fixtures_table;							//186
	char promotions;								//190
	char prom_playoff;								//191
	char rele_playoff;								//192
	char relegations;								//193
	char pts_for_win;								//194
	char pts_for_draw;								//195
	char f196;										//196
	char tiebreaker_1;								//197
	char tiebreaker_2;								//198
	char tiebreaker_3;								//199
	char pad200[17];								//200
	short f217;										//217
	short f219;										//219
	unsigned int f221;								//221
	char f225;										//225
	short min_stadium_capacity;						//226
	short min_stadium_seats;						//228
	char pad230[7];									//230
	unsigned char f237;								//237
	DWORD* teams2;									//238
	WORD n_teams2;									//242
} comp_stats;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct TEAMS_SEEDED
{
	CM3_CLUBS* club;
	char f5;
	char f6;
} teams_seeded;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct TEAM_LEAGUE_STATS
{
	CM3_CLUBS* club;			// 0
	char current_pos;			// 4
	char pad4[4];				// 5
	DWORD* position_history;	// 9
	char pad13[4];				// 13
	char games;					// 17
	char wins;					// 18
	char draws;					// 19
	char losses;				// 20
	WORD goals_for;				// 21
	WORD goals_against;			// 23
	short points;				// 25
	char pad27[4];				// 27
	char games_home;			// 31
	char wins_home;				// 32
	char draws_home;			// 33
	char losses_home;			// 34
	WORD goals_for_home;		// 35
	WORD goals_against_home;	// 37
	short points_home;			// 39
	char pad41[4];				// 41
	char games_away;			// 45
	char wins_away;				// 46
	char draws_away;			// 47
	char losses_away;			// 48
	WORD goals_for_away;		// 49
	WORD goals_against_away;	// 51
	short points_away;			// 53
	char league_fate;			// 55
	char f56;					// 56
	char highest_possible_pos;	// 57
	char lowest_possible_pos;	// 58
} team_league_stats;
#pragma pack(pop)

enum LeagueFates : BYTE {
	Promoted = 0,
	TopPlayoff = 1,
	BottomPlayoff = 2,
	Relegated = 3,
	Champions = 5,
	Qualified1 = 6,
	Qualified2 = 7,
	Qualified3 = 8,
	CantBePromoted = 0xFC,
	Eliminated = 0xFE,
	NoFate = 0xFF
};

extern cm3_nations** nations;
extern DWORD* nations_count;

extern cm3_clubs** clubs;
extern DWORD* clubs_count;

extern cm3_continents** continents;
extern DWORD* continents_count;

extern cm3_cities** cities;
extern DWORD* cities_count;

extern cm3_club_comps** club_comps;
extern DWORD* club_comps_count;

extern cm3_club_comp_history** club_comp_histories;
extern DWORD* club_comp_histories_count;

extern DWORD** comp_stats_list;
extern DWORD* comp_stats_count;

extern WORD* current_year;

extern DWORD* staff_history;