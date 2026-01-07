#pragma once
#include <windows.h>

// text lengths
#define LONG_TXT_LENGTH 101
#define STANDARD_TXT_LENGTH 51
#define SHORT_TXT_LENGTH 26

#define SI_DOUBLE double

typedef enum class COMPETITION_TYPE : char {
	CLUB_DOMESTIC = 1,
	CLUB_INTERNATITONAL = 2,
	NATION_INTERNATIONAL = 4
} competition_type;

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
	DWORD* comp_func_ptrs;							//0
	CM3_CLUB_COMPS* competition_db;					//4	
	long f8;										//8
	long f12;										//12
	char pad16[12];									//16
	CM3_CLUB_COMPS* promotes_to;					//28
	CM3_CLUB_COMPS* relegates_to;					//32
	long f36;										//36
	char pad40[18];									//40
	unsigned short n_games;							//58
	unsigned short n_rounds;						//60
	unsigned short n_teams;							//62
	unsigned short year;							//64
	competition_type comp_type;						//66
	char f67;										//67
	char f68;										//68
	char pad73[4];									//69
	char max_bench;									//73
	char max_subs;									//74
	char pad80[5];									//75
	char f80;										//80
	char f81;										//81
	char f82;										//82
	char tmp_file_name[80];							//83
	long f163;										//163
	DWORD* teams_list;								//167
	char f171;										//171
	char f172;										//172
	unsigned int pad173;							//173
	DWORD* team_league_table;						//177
	char pad181[5];									//181
	int f186;										//186
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
	unsigned char lastchar;							//237
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