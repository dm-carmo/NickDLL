#pragma once
#include <windows.h>

// text lengths
#define LONG_TXT_LENGTH 101
#define STANDARD_TXT_LENGTH 51
#define SHORT_TXT_LENGTH 26

#define SI_DOUBLE double

extern WORD FixedTeamOrderInCup;
extern WORD FixedTeamOrderInCup2;
extern WORD FixedTeamOrderInCup3;

enum CompetitionType : char {
	CLUB_DOMESTIC = 1,
	CLUB_INTERNATIONAL = 2,
	NATION_INTERNATIONAL = 4
};

enum CompetitionRules : BYTE {
	RulesInternational,
	RulesEurope,
	RulesSouthAmerica,
	RulesArgentina,
	RulesBelgiumLeague,
	RulesBelgiumCup,
	RulesBrazilNational,
	RulesBrazilRegional,
	RulesDenmark,
	RulesEngland,
	RulesFinlandLeague,
	RulesFinlandCup,
	RulesFrance,
	RulesGermanyLeague,
	RulesGermanyCup,
	RulesHolland,
	RulesIreland,
	RulesItalyLeague,
	RulesItalyCup,
	RulesJapanLeague,
	RulesJapanCup,
	RulesNorwayLeague,
	RulesNorwayCup,
	RulesPortugal,
	RulesScotlandLeague,
	RulesScotlandCup,
	RulesSpainLeague,
	RulesSpainCup,
	RulesSwedenLeague,
	RulesSwedenCup,
	RulesUSA,
	RulesPoland,
	RulesGreece,
	RulesCroatia,
	RulesAustralia,
	RulesOceania,
	RulesNorthernIreland,
	RulesTurkeyLeague,
	RulesTurkeyCup,
	RulesRussia,
	RulesWales,
	RulesAsia,
	RulesSouthKorea,
	RulesCzech,
	RulesAustria,
	RulesSwitzerland,
	RulesSaudi,
	CompetitionRules_LENGTH
};

enum CompetitionTiebreakers : char {
	NoTiebreaker = 0,
	GoalDifferenceTiebreaker = 1,
	GoalsForTiebreaker = 2,
	GamesWonTiebreaker = 3,
	CurrentPositionTiebreaker = 4,
	GoalsForAwayTiebreaker = 5,
	SpecialPlayoffTiebreaker = 6
};

enum RoundNames : WORD {
	None = 0,
	FirstRound = 0x0A,
	SecondRound = 0x14,
	ThirdRound = 0x1E,
	FourthRound = 0x28,
	FifthRound = 0x32,
	SixthRound = 0x3C,
	SeventhRound = 0x46,
	EighthRound = 0x50,
	RoundOf64 = 0x5A,
	RoundOf32 = 0x64,
	RoundOf16 = 0x6E,
	QuarterFinal = 0x78,
	SemiFinal = 0x82,
	ThirdPlacePlayoff = 0x8C,
	Final = 0x96,
	Playoff = 0xA0,
	Playout = 0xBE,
	FirstPreliminaryRound = 0xC8,
	SecondPreliminaryRound = 0xD2,
	QualifyingRound = 0xDC,
	PreliminaryRound = 0xE6,
	PromotionFinal = 0xF0,
	FirstQualifyingPhase = 0xFA,
	SecondQualifyingPhase = 0x104,
	ThirdQualifyingPhase = 0x10E,
	Playoff1 = 0x118,
	Playoff2 = 0x122,
	EliminationFinal = 0x140,
	KnockoutPlayoff = 0x14A,
	MajorSemiFinal = 0x154,
	PreliminaryFinal = 0x15E,
	GrandFinal = 0x168,
	InterzonePlayoff = 0x172,
	NumericGroupStage = 0x3E9,
	SecondPlacedTeams = 0x3FC,
	FirstRoundNumericGroup = 0x3FD,
	SecondRoundNumericGroup = 0x407,
	SemiFinalNumericGroup = 0x40C,
	CaribbeanZone = 0x40F,
	CentralAmericanZone = 0x410,
	EasternConference = 0x413,
	WesternConference = 0x414,
	EasternConferencePlayoff = 0x415,
	WesternConferencePlayoff = 0x416,
	MLSCup = 0x417,
	AutumnSeason = 0x419,
	SpringSeason = 0x41A,
	GroupStage = 0x41C,
	NorthernSouthernSection = 0x41E,
	AlphabeticGroupStage = 0x420,
	OceaniaAsiaPlayoff = 0x42F,
	FirstStage = 0x432,
	SecondStage = 0x433,
	AperturaPlayoffs = 0x434,
	ClausuraPlayoffs = 0x435,
	Bayern = 0x436,
	MainPath = 0x437,
	Promotion = 0x438,
	Periods1to4 = 0x439,
	AperturaGroupsAtoB = 0x43D,
	FirstStageGoldSilver = 0x43F,
	SecondStageGoldSilver = 0x441,
	RPLPath = 0x443,
	RegionsPath = 0x444,
	ClausuraGroupsAtoB = 0x445,
	Phase2GroupCtoD = 0x447,
	AperturaGroupStage = 0x449,
	ClausuraGroupStage = 0x44A,
	ChampionshipGroup = 0x44B,
	RelegationGroup = 0x44C,
	PromotionGroupAtoD = 0x44D,
	PromotionGroupStage = 0x451,
	RelegationPlayoff = 0x452,
	North = 0x453,
	Northeast = 0x454,
	Southwest = 0x455,
	South = 0x456,
	Central = 0x457,
	PromotionPlayoff = 0x458,
	FirstPromotionPlayoff = 0x459,
	SecondPromotionPlayoff = 0x45A,
	ThirdPromotionPlayoff = 0x45B,
	RelegationGroupStage = 0x45C,
	EastSvealand = 0x46D,
	WestSvealand = 0x46E,
	EastGotaland = 0x46F,
	WestGotaland = 0x470,
	SouthGotaland = 0x471,
	SecondRoundGroup6 = 0x472,
	CentralAmericanZoneGroup1 = 0x473,
	ClassificationGroup1to5 = 0x475,
	ClassificationGroups = 0x47A,
	CentralConference = 0x47B,
	RelegationGroupAtoB = 0x47C,
	ThirdRoundNumericGroup = 0x47E,
	EastWest = 0x480,
	ChampionsPath = 0x482,
	LeaguePath = 0x483
};

enum Game1Tiebreaks : WORD {
	NoTiebreak_1 = 0,
	PenaltiesNoExtraTime_1 = 1,
	ExtraTimeNoPenalties_1 = 2,
	ExtraTimePenalties_1 = 3,
	Libertadores_1 = 4,
	YardShootout_1 = 0x30,
	GoldenGoal_1 = 0x83
};

enum Game2Tiebreaks : WORD {
	NoTiebreak_2 = 0,
	AwayGoalsPenaltiesNoExtraTime_2 = 1,
	AwayGoalsExtraTimePenalties_2 = 3,
	ExtraTimePenaltiesNoAwayGoals_2 = 7,
	YardShootout_2 = 0x30,
	GoldenGoal_2 = 0x83
};

enum Game3Tiebreaks : WORD {
	NoTiebreak_3 = 0,
	ExtraTimePenalties_3 = 3,
	YardShootout_3 = 0x20
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
	AhAhliKSAStadium = 0x8000
};

enum ClubStatus : char {
	UnknownStatus = 0,
	Professional = 1,
	SemiProfessional = 2,
	Amateur = 3
};

typedef struct cm3_continents CM3_CONTINENTS;
typedef struct cm3_club_comps CM3_CLUB_COMPS;
typedef struct cm3_club_comp_history CM3_CLUB_COMP_HISTORY;
typedef struct cm3_staff_comps CM3_STAFF_COMPS;
typedef struct cm3_staff_comp_history CM3_STAFF_COMP_HISTORY;
typedef struct cm3_nations CM3_NATIONS;
typedef struct cm3_cities CM3_CITIES;
typedef struct cm3_stadiums CM3_STADIUMS;
typedef struct cm3_colours CM3_COLOURS;
typedef struct cm3_clubs CM3_CLUBS;
typedef struct cm3_staff CM3_STAFF;
typedef struct cm3_non_players CM3_NON_PLAYERS;
typedef struct cm3_players CM3_PLAYERS;
typedef struct cm3_staff_preferences CM3_STAFF_PREFERENCES;

#pragma pack(push, 1)
typedef struct
{
	short day; // days from Jan 1st.
	short year;
	long LeapYear; // =1 if year is a leapyear, 0 otherwise.
} CM_DATE;
#pragma pack(pop)

#pragma pack(push, 1)
struct cm3_players
{
	// original data
	long StaffPlayerID;
	char StaffPlayerSquadNumber;
	short StaffPlayerCurrentAbility;
	short StaffPlayerPotentialAbility;
	short StaffPlayerHomeReputation; // Version 0x02 - Changed char->short
	short StaffPlayerCurrentReputation; // Version 0x02 - Changed char->short
	short StaffPlayerWorldReputation; // Version 0x02 - Changed char->short
	char StaffPlayerGoalkeeper;
	char StaffPlayerSweeper;
	char StaffPlayerDefender;
	char StaffPlayerDefensiveMidfielder;
	char StaffPlayerMidfielder;
	char StaffPlayerAttackingMidfielder;
	char StaffPlayerAttacker;
	char StaffPlayerWingBack;
	char StaffPlayerRightSide;
	char StaffPlayerLeftSide;
	char StaffPlayerCentral;
	char StaffPlayerFreeRole;
	char StaffPlayerAcceleration;
	char StaffPlayerAggression;
	char StaffPlayerAgility;
	char StaffPlayerAnticipation;
	char StaffPlayerBalance;
	char StaffPlayerBravery; // Value
	char StaffPlayerConsistency;
	char StaffPlayerCorners;
	char StaffPlayerCrossing;
	char StaffPlayerDecisions;
	char StaffPlayerDirtiness;
	char StaffPlayerDribbling;
	char StaffPlayerFinishing;
	char StaffPlayerFlair;
	char StaffPlayerFreeKicks;
	char StaffPlayerHandling;
	char StaffPlayerHeading;
	char StaffPlayerImportantMatches;
	char StaffPlayerInjuryProneness;
	char StaffPlayerJumping;
	char StaffPlayerLeadership;
	char StaffPlayerLeftFoot;
	char StaffPlayerLongShots;
	char StaffPlayerMarking;
	char StaffPlayerMovement;
	char StaffPlayerNaturalFitness;
	char StaffPlayerOneOnOnes;
	char StaffPlayerPace;
	char StaffPlayerPassing;
	char StaffPlayerPenalties;
	char StaffPlayerPositioning;
	char StaffPlayerReflexes;
	char StaffPlayerRightFoot;
	char StaffPlayerStamina;
	char StaffPlayerStrength;
	char StaffPlayerTackling;
	char StaffPlayerTeamwork;
	char StaffPlayerTechnique;
	char StaffPlayerThrowIns;
	char StaffPlayerVersatility;
	char StaffPlayerVision;
	char StaffPlayerWorkRate;

	// runtime data
	char StaffPlayerMorale;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct cm3_non_players
{
	long StaffNonPlayerID;
	short StaffNonPlayerCurrentAbility;
	short StaffNonPlayerPotentialAbility;
	short StaffNonPlayerHomeReputation; // Version 0x02 - Changed char->short
	short StaffNonPlayerCurrentReputation; // Version 0x02 - Changed char->short
	short StaffNonPlayerWorldReputation; // Version 0x02 - Changed char->short
	char StaffNonPlayerAttacking;
	char StaffNonPlayerBusiness;
	char StaffNonPlayerCoaching;
	char StaffNonPlayerCoachingGks;
	char StaffNonPlayerCoachingTechnique;
	char StaffNonPlayerDirectness;
	char StaffNonPlayerDiscipline;
	char StaffNonPlayerFreeRoles;
	char StaffNonPlayerInterference;
	char StaffNonPlayerJudgement;
	char StaffNonPlayerJudgingPotential;
	char StaffNonPlayerManHandling;
	char StaffNonPlayerMarking;
	char StaffNonPlayerMotivating;
	char StaffNonPlayerOffside;
	char StaffNonPlayerPatience;
	char StaffNonPlayerPhysiotherapy;
	char StaffNonPlayerPressing;
	char StaffNonPlayerResources;
	char StaffNonPlayerTactics;
	char StaffNonPlayerYoungsters;
	CM3_STAFF* StaffNonPlayerGoalkeeper;
	CM3_STAFF* StaffNonPlayerSweeper;
	CM3_STAFF* StaffNonPlayerDefender;
	CM3_STAFF* StaffNonPlayerDefensiveMidfielder;
	CM3_STAFF* StaffNonPlayerMidfielder;
	CM3_STAFF* StaffNonPlayerAttackingMidfielder;
	CM3_STAFF* StaffNonPlayerAttacker;
	CM3_STAFF* StaffNonPlayerWingBack;
	char StaffNonPlayerFormationPreferred;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct cm3_staff_preferences
{
	long StaffPreferencesID;
	CM3_CLUBS* StaffFavouriteClubs1;
	CM3_CLUBS* StaffFavouriteClubs2;
	CM3_CLUBS* StaffFavouriteClubs3;
	CM3_CLUBS* StaffDislikedClubs1;
	CM3_CLUBS* StaffDislikedClubs2;
	CM3_CLUBS* StaffDislikedClubs3;
	CM3_STAFF* StaffFavouriteStaff1;
	CM3_STAFF* StaffFavouriteStaff2;
	CM3_STAFF* StaffFavouriteStaff3;
	CM3_STAFF* StaffDislikedStaff1;
	CM3_STAFF* StaffDislikedStaff2;
	CM3_STAFF* StaffDislikedStaff3;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct cm3_staff
{
	long StaffID;
	DWORD* StaffFirstName;
	DWORD* StaffSecondName;
	DWORD* StaffCommonName;
	CM_DATE StaffDateOfBirth;
	short StaffYearOfBirth;
	CM3_NATIONS* StaffNation;
	CM3_NATIONS* StaffSecondNation;
	unsigned char StaffInternationalApps;
	unsigned char StaffInternationalGoals;
	CM3_CLUBS* StaffNationContracted;
	char StaffJobForNation;
	CM_DATE StaffDateJoinedNation;
	CM_DATE StaffContractExpiresNation;
	CM3_CLUBS* StaffClubContracted;
	char StaffJobForClub;
	CM_DATE StaffDateJoinedClub;
	CM_DATE StaffContractExpiresClub;
	long StaffEstimatedWage;
	long StaffEstimatedValue;
	char StaffAdaptability;
	char StaffAmbition;
	char StaffDetermination;
	char StaffLoyalty;
	char StaffPressure;
	char StaffProfessionalism;
	char StaffSportsmanship;
	char StaffTemperament;
	char StaffPlayingSquad;
	char StaffClassification;
	char StaffClubValuation;
	CM3_PLAYERS* StaffPlayerData;
	CM3_STAFF_PREFERENCES* StaffPreferences; // Version 0x02 - New ptr type
	CM3_NON_PLAYERS* StaffNonPlayerData;

	// Runtime data //
	char StaffSquadSelectedFor; // should be StaffEuroSquadFlag - Kev
};
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)

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
struct cm3_staff_comps
{
	long StaffCompID;
	char StaffCompName[STANDARD_TXT_LENGTH];
	char StaffCompGenderName;
	char StaffCompNameShort[SHORT_TXT_LENGTH];
	char StaffCompGenderNameShort;
	CM3_CONTINENTS* StaffCompContinent;
	CM3_NATIONS* StaffCompNation;
	CM3_COLOURS* StaffCompForegroundColour;
	CM3_COLOURS* StaffCompBackgroundColour;
	short StaffCompReputation; // Version 0x02 - Changed char->short
};
#pragma pack(pop)

#pragma pack(push, 1)
struct cm3_staff_comp_history
{
	long StaffCompHistoryID;
	CM3_STAFF_COMPS* StaffCompHistoryStaffComp;
	short StaffCompHistoryYear;
	char* StaffCompHistoryFirstPlacedFirstName;
	char* StaffCompHistoryFirstPlacedSecondName;
	CM3_STAFF* StaffCompHistoryFirstPlacedIndex;
	long StaffCompHistoryFirstPlacedInfo;
	char* StaffCompHistorySecondPlacedFirstName;
	char* StaffCompHistorySecondPlacedSecondName;
	CM3_STAFF* StaffCompHistorySecondPlacedIndex;
	long StaffCompHistorySecondPlacedInfo;
	char* StaffCompHistoryThirdPlacedFirstName;
	char* StaffCompHistoryThirdPlacedSecondName;
	CM3_STAFF* StaffCompHistoryThirdPlacedIndex;
	long StaffCompHistoryThirdPlacedInfo;
};
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct COMP_STATS
{
	DWORD* comp_vtable;								//0
	CM3_CLUB_COMPS* competition_db;					//4	
	DWORD* f8;										//8
	DWORD* stages;									//12
	DWORD f16;										//16
	DWORD* special_teams_seedings;					//20
	DWORD* avg_points_table;						//24
	long promotes_to;								//28
	long relegates_to;								//32
	long f36;										//36
	long prize_money_pool;							//40
	long num_stages;								//44
	long current_stage;								//48
	WORD n_teams_avg_table;							//52
	WORD special_nteams_seedings;					//54
	WORD f56;										//56
	WORD n_games;									//58
	WORD n_rounds;									//60
	WORD n_teams;									//62
	WORD year;										//64
	CompetitionType comp_type;						//66
	char f67;										//67
	char f68;										//68
	DWORD f69;										//69
	char max_bench;									//73
	char max_subs;									//74
	char f75;										//75
	DWORD* f76;										//76
	CompetitionRules rules;							//80
	char f81;										//81
	char f82;										//82
	char tmp_file_name[80];							//83
	BYTE* rounds_list;								//163
	DWORD* teams_list;								//167
	char f171;										//171
	char f172;										//172
	DWORD* f173;									//173
	DWORD* team_league_table;						//177
	char pad181;									//181
	char pad182[4];									//182
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
	char tiebreaker_4;								//200
	char pad201[16];								//201
	short f217;										//217
	short f219;										//219
	DWORD f221;										//221
	char f225;										//225
	short min_stadium_capacity;						//226
	short min_stadium_seats;						//228
	char pad230[7];									//230
	unsigned char f237;								//237
	DWORD* teams2;									//238
	DWORD n_teams2;									//242
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
	DWORD position_history;		// 9
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

#pragma pack(push, 1)
typedef struct AVG_POINTS_STATS
{
	CM3_CLUBS* club;
	DWORD f4;
	WORD year;
	WORD pts1;
	BYTE games1;
	WORD pts2;
	BYTE games2;
	WORD pts3;
	BYTE games3;
} avg_points_stats;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct PLAYABLE_NATION_DATA
{
	cm3_nations* nation; // B63D60
	cm3_continents* continent; // B63D64
	DWORD setup_function_addr; // B63D68
	DWORD num_of_comps; // B63D6C
	DWORD comps_list; // B63D70
	BYTE d; // B63D74
	WORD update_day; // B63D75
	DWORD updates_in_june; // B63D77
	WORD update_year; // B63D7B
	BYTE f29; // B63D7D
	cm3_club_comps* main_cup; // B63D7E
	cm3_club_comps* league_cup; // B63D82
	cm3_club_comps* super_cup; // B63D86
	BYTE start_date[8]; // B63D8A
	WORD contract_start_day; // B63D92
	BYTE contract_start_month; // B63D94
	WORD contract_start_year; // B63D95
	WORD f55; // B63D97
	BYTE end_date[8]; // B63D99
	WORD contract_end_day; // B63DA1
	BYTE contract_end_month; // B63DA3
	WORD contract_end_year; // B63DA4
	WORD f70; // B63DA6

	PLAYABLE_NATION_DATA()
	{
		nation = 0;
		continent = 0;
		setup_function_addr = 0;
		num_of_comps = 0;
		comps_list = 0;
		d = 0;
		update_day = 0;
		updates_in_june = 0;
		update_year = 0;
		f29 = 0;
		main_cup = 0;
		league_cup = 0;
		super_cup = 0;
		for (int i = 0; i < 8; i++) start_date[i] = 0;
		contract_start_day = 0;
		contract_start_month = 0;
		contract_start_year = 0;
		f55 = 0;
		for (int i = 0; i < 8; i++) end_date[i] = 0;
		contract_end_day = 0;
		contract_end_month = 0;
		contract_end_year = 0;
		f70 = 0;
	}
} playable_nation_data;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct UEFA_SEEDINGS
{
	DWORD id;
	cm3_nations* nation;
	float coefficient;
	BYTE ucl_spots;
	BYTE uel_spots;
	BYTE uecl_spots;
	WORD current_year_points;
	BYTE num_teams_in_comps;
} uefa_seedings;
#pragma pack(pop)

enum LeagueFates : char {
	Promoted = 0,
	TopPlayoff = 1,
	BottomPlayoff = 2,
	Relegated = 3,
	Champions = 5,
	Qualified1 = 6,
	Qualified2 = 7,
	Qualified3 = 8,
	CantBePromoted = -4, // 0FC
	CantBePromotedOrRelegated = -3, // 0FD
	Eliminated = -2, // 0FE
	NoFate = -1 // 0FF
};

extern cm3_staff_comps** awards;
extern DWORD* awards_count;

extern cm3_nations** nations;
extern DWORD* nations_count;

extern cm3_clubs** clubs;
extern DWORD* clubs_count;

extern cm3_continents** continents;
extern DWORD* continents_count;

extern cm3_cities** cities;
extern DWORD* cities_count;

extern cm3_stadiums** stadiums;
extern DWORD* stadiums_count;

extern cm3_club_comps** club_comps;
extern DWORD* club_comps_count;

extern cm3_club_comp_history** club_comp_histories;
extern DWORD* club_comp_histories_count;

extern DWORD** comp_stats_list;
extern DWORD* comp_stats_count;

extern cm3_colours** colours;
extern DWORD* colours_count;

extern DWORD* current_date;
extern WORD* current_year;

extern DWORD* staff_history;
extern DWORD* dd6ec8;

extern const DWORD pnd_count;
extern playable_nation_data* pnd_list; //0xB63D60
extern playable_nation_data** pnd_list_default;
extern BYTE* pnd_order;

extern uefa_seedings** uefa_seeding_list;

extern DWORD* b5e134;
extern DWORD* b74340;
extern DWORD* b67a44;
extern DWORD* ae1050;
extern DWORD* ad9c60;
extern DWORD* ae2a38;