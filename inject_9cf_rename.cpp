#include "Helpers\Helper.h"
#include "inject_9cf_rename.h"
#include <Helpers\9cf_constants.h>
#include <Helpers\generic_functions.h>

map<string, char*> clubs_rename_short = {
	{"C.D. Ourense", "Ourense CF"},
	{"SC Paderborn 07 Reserves", "Paderborn II"},
	{"SJK Seinäjoki II", "SJK Akatemia"},
};

map<string, char*> clubs_rename_long = {
	{"Dallas Burn", "FC Dallas"},
	{"Kansas City Wizards", "Sporting Kansas City"},
	{"Miami Fusion FC", "Inter Miami CF"},
	{"NY/NJ Metrostars", "New York Red Bulls"},
	{"Tampa Bay Mutiny", "Los Angeles FC"},
	{"Clube Atlético Paranaense", "Club Athletico Paranaense"},
	{"C.D. Ourense", "Ourense CF"},
	{"C.P. Mérida", "Mérida AD"},
	{"Baskonia C.D.", "CD Basconia"},
	{"Extremadura C.F.", "CD Extremadura"},
	{"Merthyr Tydfil", "Merthyr Town"},
	{"Bra", "AC Bra"},
	{"AZ", "AZ Alkmaar"},
	{"GD Chaves Satelite", "GD Chaves B"},
	{"Bor. M'gladbach Amateure", "Borussia M'gladbach II"},
	{"SC Paderborn 07 Reserves", "SC Paderborn 07 II"},
	{"SJK Seinäjoki II", "SJK Seinäjoki Akatemia"},
};

map<string, char*> leagues_rename_long = {
	{"English Northern Premier League Premier Division", "English National League North"},
	{"English Southern League Premier Division", "English National League South"},
	{"Danish 1st Division", "Danish First Division"},
	{"Danish 2nd Division", "Danish Second Division"},
	{"Danish 3rd Division", "Danish Third Division"},
	{"AFC Champions League", "AFC Champions League Elite"},
	{"Asian Cup Winners' Cup", "AFC Champions League Two"},
	{"Afro-Asian Champions Cup", "AFC Challenge League"},
	{"African CAF Cup", "CAF Confederation Cup"},
	{"Cup Winners' Cup", "UEFA Conference League"},
	{"UEFA Europa League Qualifying", "UEFA Intertoto Cup"},
	{"CONCACAF Champions League", "CONCACAF Champions Cup"},
	{"Cup Winners Cup", "CONCACAF Cup Winners Cup"},
	{"Belgian Fourth Division  A", "Belgian Division 2 A"},
	{"Belgian Fourth Division  B", "Belgian Division 2 B"},
	{"Belgian Fourth Division  C", "Belgian Division 2 C"},
	{"Belgian Fourth Division  D", "Belgian Division 2 D"},
	{"Northern Irish League Lower Division", "NIFL Premier Intermediate League"},
	{"NIFL Cup", "Irish Football League Cup"},
	{"Korean FA Cup", "Korea Cup"},
	{"Korean Super Cup", "K League Super Cup"},
	// temp
	{"Swedish Division 2 North Svealand", "EXTINCT 1"},
	{"Swedish Division 2 South Gotaland", "EXTINCT 2"},
};

map<string, char*> leagues_rename_long_australia = {
	{"Hong Kong Viceroy Cup", "Australia Cup"},
};

map<string, char*> leagues_rename_long_brazil = {
	{"Brazilian Campeonato Série A", "Campeonato Brasileiro Série A"},
	{"Brazilian Campeonato Série B", "Campeonato Brasileiro Série B"},
	{"Brazilian Campeonato Série C", "Campeonato Brasileiro Série C"},
	{"CIS Champions Cup", "Campeonato Brasileiro Série D"},
	{"Brazilian Copa dos Campeões", "Brazilian Supercopa Rei"},
};

map<string, char*> leagues_rename_long_germany = {
	{"Turkish 2. Divison Category B Group 1", "German Regionalliga"},
	{"Indian Guwahati Lower Division", "German Regionalliga Bayern"},
	{"German 3. Liga Süd", "German Regionalliga Südwest"},
	{"German 3. Liga Osten", "German Regionalliga Nordost"},
	{"German 3. Liga Nord", "German Regionalliga Nord"},
	{"German 3. Liga West", "German Regionalliga West"},
};

map<string, char*> leagues_rename_long_greece = {
	{"Swedish Division 2 East Svealand", "Greek Super League 2 North Group"},
	{"Swedish Division 2 West Svealand", "Greek Super League 2 South Group"},
};

map<string, char*> leagues_rename_long_croatia = {
	{"Croatian Treca NL", "Croatian Druga NL"},
	{"Croatian Druga NL Central", "Croatian Treca NL Central"},
	{"Croatian Druga NL North", "Croatian Treca NL North"},
	{"Croatian Druga NL South", "Croatian Treca NL South"},
	{"Croatian Druga NL East", "Croatian Treca NL East"},
	{"Croatian Druga NL West", "Croatian Treca NL West"},
};

map<string, char*> leagues_rename_long_finland = {
	{"Finnish Ykkösliiga North", "Finnish Ykkönen"},
	{"Finnish Ykkösliiga South", "Finnish Kolmonen"},
	{"Finnish Ykkönen North", "Finnish Kakkonen Group A"},
	{"Finnish Ykkönen West", "Finnish Kakkonen Group B"},
	{"Finnish Ykkönen South", "Finnish Kakkonen Group C"},
};

map<string, char*> leagues_rename_long_italy = {
	{"Indian Chennai League", "Italian Serie C"},
	{"Italian Serie C1/A", "Italian Serie C/A"},
	{"Italian Serie C1/B", "Italian Serie C/B"},
	{"Indian Haryana State Championship", "Italian Serie C/C"},
};

map<string, char*> leagues_rename_long_japan = {
	{"Japanese Regional Leagues", "Japanese Football League"},
	{"Japanese University League", "Japanese Regional Championships"},
};

map<string, char*> leagues_rename_long_norway = {
	{"Swedish Fourth Division", "Norwegian 2. Divisjon"},
	{"Norwegian 2. Divisjon Group 3", "Norwegian 3. Divisjon Group 1"},
	{"Norwegian 2. Divisjon Group 4", "Norwegian 3. Divisjon Group 2"},
	{"Norwegian 2. Divisjon Group 5", "Norwegian 3. Divisjon Group 3"},
	{"Norwegian 2. Divisjon Group 6", "Norwegian 3. Divisjon Group 4"},
	{"Norwegian 2. Divisjon Group 7", "Norwegian 3. Divisjon Group 5"},
	{"Norwegian 2. Divisjon Group 8", "Norwegian 3. Divisjon Group 6"},
};

map<string, char*> leagues_rename_long_poland = {
	{"Irish Super Cup", "Polish III Liga"},
};

map<string, char*> leagues_rename_long_portugal = {
	{"Liga 3 North", "Liga 3 Série A"},
	{"Liga 3 South", "Liga 3 Série B"},
	{"Liga 3 Central", "Campeonato de Portugal Série A"},
	{"Korean University League", "Campeonato de Portugal Série B"},
	{"Korean High School League", "Campeonato de Portugal Série C"},
	{"Korean President Cup", "Campeonato de Portugal Série D"},
	{"Singaporean Prime League", "Taça da Liga"},
};

map<string, char*> leagues_rename_long_scotland = {
	{"South African First Division Inland", "Scottish Highland Football League"},
	{"South African First Division Coastal", "Scottish Lowland Football League"},
};

map<string, char*> leagues_rename_long_spain = {
	{"Turkish 2. Division Group 3", "Spanish Segunda Federación Group 1"},
	{"Turkish 2. Division Group 4", "Spanish Segunda Federación Group 2"},
	{"Turkish 2. Division Group 5", "Spanish Segunda Federación Group 3"},
	{"PrepreLibertadores Cup", "Spanish Segunda Federación Group 4"},
	{"PreLibertadores", "Spanish Segunda Federación Group 5"},
};

map<string, char*> leagues_rename_long_sweden = {
	{"Swedish Ettan South Gotaland", "Swedish Ettan South"},
	{"Swedish Lower Division", "Swedish Division 2"},
	{"Swedish Ettan West Svealand", "Swedish Division 2 Norrland"},
	{"Swedish Ettan East Gotaland", "Swedish Division 2 North Götaland"},
	{"Swedish Ettan West Gotaland", "Swedish Division 2 West Götaland"},
	{"Swedish Ettan East Svealand", "Swedish Division 2 South Svealand"},
	{"Turkish 2. Division Group 2", "Swedish Division 2 North Svealand"},
	{"MLS All-Stars", "Swedish Division 2 South Götaland"},
};

map<string, char*> leagues_rename_long_turkey = {
	{"TFF 2. Lig G1", "TFF 2. Lig Group 1"},
	{"TFF 2. Lig G2", "TFF 2. Lig Group 2"},
	{"TFF 2. Lig G3", "TFF 3. Lig Group 1"},
	{"TFF 2. Lig G4", "TFF 3. Lig Group 2"},
	{"TFF 2. Lig G5", "TFF 3. Lig Group 3"},
	{"Turkish 2. Division Group 1", "TFF 3. Lig Group 4"},
	{"Turkish 2. Division", "Turkish Super Cup"},
	{"Turkish Lower Division", "TFF 3. Lig"},
};

map<string, char*> leagues_rename_long_wales = {
	{"Welsh Lower Division", "Welsh Cymru North"},
	{"Irish Shield", "Welsh Cymru South"},
};

map<string, char*> leagues_rename_short = {
	{"English Northern Premier League Premier Division", "National League North"},
	{"English Southern League Premier Division", "National League South"},
	{"Danish 1st Division", "First Division"},
	{"Danish 2nd Division", "Second Division"},
	{"Danish 3rd Division", "Third Division"},
	{"AFC Champions League", "Champions League Elite"},
	{"Asian Cup Winners' Cup", "Champions League Two"},
	{"Afro-Asian Champions Cup", "Challenge League"},
	{"African CAF Cup", "Confederation Cup"},
	{"Cup Winners' Cup", "Conference League"},
	{"UEFA Europa League Qualifying", "Intertoto Cup"},
	{"CONCACAF Champions League", "Champions Cup"},
	{"Belgian Fourth Division  A", "Division 2 A"},
	{"Belgian Fourth Division  B", "Division 2 B"},
	{"Belgian Fourth Division  C", "Division 2 C"},
	{"Belgian Fourth Division  D", "Division 2 D"},
	{"Coppa Italia Serie C", "Coppa Serie C"},
	{"Supercoppa Serie C", "Supercoppa Serie C"},
	{"Korean FA Cup", "Korea Cup"},
};

map<string, char*> leagues_rename_short_australia = {
	{"Hong Kong Viceroy Cup", "Australia Cup"},
};

map<string, char*> leagues_rename_short_brazil = {
	{"CIS Champions Cup", "Série D"},
	{"Brazilian Copa dos Campeões", "Supercopa Rei"},
};

map<string, char*> leagues_rename_short_germany = {
	{"Turkish 2. Divison Category B Group 1", "Regionalliga"},
	{"Indian Guwahati Lower Division", "Regionalliga Bayern"},
	{"German 3. Liga Süd", "Regionalliga Südwest"},
	{"German 3. Liga Osten", "Regionalliga Nordost"},
	{"German 3. Liga Nord", "Regionalliga Nord"},
	{"German 3. Liga West", "Regionalliga West"},
};

map<string, char*> leagues_rename_short_greece = {
	{"Swedish Division 2 East Svealand", "Super League 2 North"},
	{"Swedish Division 2 West Svealand", "Super League 2 South"},
};

map<string, char*> leagues_rename_short_croatia = {
	{"Croatian Treca NL", "2. NL"},
	{"Croatian Druga NL Central", "3. NL Central"},
	{"Croatian Druga NL North", "3. NL North"},
	{"Croatian Druga NL South", "3. NL South"},
	{"Croatian Druga NL East", "3. NL East"},
	{"Croatian Druga NL West", "3. NL West"},
};

map<string, char*> leagues_rename_short_finland = {
	{"Finnish Ykkösliiga North", "Ykkönen"},
	{"Finnish Ykkösliiga South", "Kolmonen"},
	{"Finnish Ykkönen North", "Kakkonen Group A"},
	{"Finnish Ykkönen West", "Kakkonen Group B"},
	{"Finnish Ykkönen South", "Kakkonen Group C"},
};

map<string, char*> leagues_rename_short_italy = {
	{"Indian Chennai League", "Serie C"},
	{"Italian Serie C1/A", "Serie C/A"},
	{"Italian Serie C1/B", "Serie C/B"},
	{"Indian Haryana State Championship", "Serie C/C"},
};

map<string, char*> leagues_rename_short_japan = {
	{"Japanese Regional Leagues", "JFL"},
	{"Japanese University League", "Regional Ch'ships"},
};

map<string, char*> leagues_rename_short_norway = {
	{"Swedish Fourth Division", "2. Divisjon"},
	{"Norwegian 2. Divisjon Group 3", "3. Divisjon Group 1"},
	{"Norwegian 2. Divisjon Group 4", "3. Divisjon Group 2"},
	{"Norwegian 2. Divisjon Group 5", "3. Divisjon Group 3"},
	{"Norwegian 2. Divisjon Group 6", "3. Divisjon Group 4"},
	{"Norwegian 2. Divisjon Group 7", "3. Divisjon Group 5"},
	{"Norwegian 2. Divisjon Group 8", "3. Divisjon Group 6"},
};

map<string, char*> leagues_rename_short_poland = {
	{"Irish Super Cup", "III Liga"},
};

map<string, char*> leagues_rename_short_portugal = {
	{"Liga 3 North", "Liga 3 A"},
	{"Liga 3 South", "Liga 3 B"},
	{"Liga 3 Central", "Campeonato de Portugal A"},
	{"Korean University League", "Campeonato de Portugal B"},
	{"Korean High School League", "Campeonato de Portugal C"},
	{"Korean President Cup", "Campeonato de Portugal D"},
	{"Singaporean Prime League", "Taça da Liga"},
};

map<string, char*> leagues_rename_short_scotland = {
	{"South African First Division Inland", "Highland League"},
	{"South African First Division Coastal", "Lowland League"},
};

map<string, char*> leagues_rename_short_spain = {
	{"Turkish 2. Division Group 3", "Segunda Federación G1"},
	{"Turkish 2. Division Group 4", "Segunda Federación G2"},
	{"Turkish 2. Division Group 5", "Segunda Federación G3"},
	{"PrepreLibertadores Cup", "Segunda Federación G4"},
	{"PreLibertadores", "Segunda Federación G5"},
};

map<string, char*> leagues_rename_short_sweden = {
	{"Swedish Ettan South Gotaland", "Ettan S"},
	{"Swedish Lower Division", "Division 2"},
	{"Swedish Ettan West Svealand", "Division 2 N"},
	{"Swedish Ettan East Gotaland", "Division 2 NG"},
	{"Swedish Ettan West Gotaland", "Division 2 WG"},
	{"Swedish Ettan East Svealand", "Division 2 SS"},
	{"Turkish 2. Division Group 2", "Division 2 NS"},
	{"MLS All-Stars", "Division 2 SG"},
};

map<string, char*> leagues_rename_short_turkey = {
	{"TFF 2. Lig G1", "2. Lig G1"},
	{"TFF 2. Lig G2", "2. Lig G2"},
	{"TFF 2. Lig G3", "3. Lig G1"},
	{"TFF 2. Lig G4", "3. Lig G2"},
	{"TFF 2. Lig G5", "3. Lig G3"},
	{"Turkish 2. Division Group 1", "3. Lig G4"},
	{"Turkish 2. Division", "Super Cup"},
	{"Turkish Lower Division", "3. Lig"},
};

map<string, char*> leagues_rename_short_wales = {
	{"Welsh Lower Division", "Cymru North"},
	{"Irish Shield", "Cymru South"},
};

map<string, char*> leagues_rename_tla = {
	{"English Northern Premier League Premier Division", "NLN"},
	{"English Southern League Premier Division", "NLS"},
	{"Polish Ekstraklasa", "EKS"},
};

map<string, char*> leagues_rename_tla_brazil = {
	{"CIS Champions Cup", "D"},
};

map<string, char*> leagues_rename_tla_germany = {
	{"Turkish 2. Divison Category B Group 1", "Reg"},
	{"Indian Guwahati Lower Division", "Reg"},
	{"German 3. Liga Süd", "Reg"},
	{"German 3. Liga Osten", "Reg"},
	{"German 3. Liga Nord", "Reg"},
	{"German 3. Liga West", "Reg"},
};

map<string, char*> leagues_rename_tla_greece = {
	{"Swedish Division 2 East Svealand", "SL2"},
	{"Swedish Division 2 West Svealand", "SL2"},
};

map<string, char*> leagues_rename_tla_croatia = {
	{"Croatian Treca NL", "2NL"},
	{"Croatian Druga NL Central", "3LC"},
	{"Croatian Druga NL North", "3LN"},
	{"Croatian Druga NL South", "3LS"},
	{"Croatian Druga NL East", "3LE"},
	{"Croatian Druga NL West", "3LW"},
};

map<string, char*> leagues_rename_tla_finland = {
	{"Finnish Ykkösliiga North", "Ykk"},
	{"Finnish Ykkösliiga South", "Kol"},
	{"Finnish Ykkönen North", "Kak"},
	{"Finnish Ykkönen West", "Kak"},
	{"Finnish Ykkönen South", "Kak"},
};

map<string, char*> leagues_rename_tla_italy = {
	{"Indian Chennai League", "C"},
	{"Italian Serie C1/A", "C/A"},
	{"Italian Serie C1/B", "C/B"},
	{"Indian Haryana State Championship", "C/C"},
};

map<string, char*> leagues_rename_tla_japan = {
	{"Japanese Regional Leagues", "JFL"},
	{"Japanese University League", "Reg"},
};

map<string, char*> leagues_rename_tla_norway = {
	{"Swedish Fourth Division", "D2"},
	{"Norwegian 2. Divisjon Group 3", "D3"},
	{"Norwegian 2. Divisjon Group 4", "D3"},
	{"Norwegian 2. Divisjon Group 5", "D3"},
	{"Norwegian 2. Divisjon Group 6", "D3"},
	{"Norwegian 2. Divisjon Group 7", "D3"},
	{"Norwegian 2. Divisjon Group 8", "D3"},
};

map<string, char*> leagues_rename_tla_poland = {
	{"Irish Super Cup", "L3"},
};

map<string, char*> leagues_rename_tla_portugal = {
	{"Liga 3 North", "L3A"},
	{"Liga 3 South", "L3B"},
	{"Liga 3 Central", "CPA"},
	{"Korean University League", "CPB"},
	{"Korean High School League", "CPC"},
	{"Korean President Cup", "CPD"},
};

map<string, char*> leagues_rename_tla_scotland = {
	{"South African First Division Inland", "HFL"},
	{"South African First Division Coastal", "LFL"},
};

map<string, char*> leagues_rename_tla_spain = {
	{"Turkish 2. Division Group 3", "SF1"},
	{"Turkish 2. Division Group 4", "SF2"},
	{"Turkish 2. Division Group 5", "SF3"},
	{"PrepreLibertadores Cup", "SF4"},
	{"PreLibertadores", "SF5"},
};

map<string, char*> leagues_rename_tla_sweden = {
	{"Swedish Lower Division", "D2"},
};

map<string, char*> leagues_rename_tla_wales = {
	{"Welsh Lower Division", "D1N"},
	{"Irish Shield", "D1S"},
};

map<string, char*> awards_rename_short = {
	{"German Defender of the Year", "Manager of the Year"},
	{"German Goalkeeper of the Year", "Player of the Month"},
	{"German Midfielder of the Year", "Team of the Week"},
	{"German Striker of the Year", "Top Goalscorer"},
	{"German Sweeper of the Year", "Manager of the Year"},
	{"English Footballer of the Year", "Manager of the Year"},
	{"Asian Assistant Referee of the Year", "Manager of the Month"}, //200
	{"Asian Referee of the Year", "Manager of the Month"}, //1FF
	{"Belgian Referee of the Year", "Player of the Month"}, //1E9
	{"Chinese Golden Whistle", "Player of the Month"}, //193
	{"Mexican Physio of the Year", "Team of the Week"}, //184
	{"South Korean Referee of the Month", "Team of the Week"}, //20A
	{"South Korean Referee of the Year", "Players Team of the Year"}, //211
	{"South Korean Fair Play of the Month", "Players Team of the Year"}, //20B
	{"South Korean Fair Play of the Year", "Young Player of the Month"}, //20F
	{"South Korean Goalkeeper of the Month", "Manager of the Month"},
	{"South African Young Player of the Year", "Young Player of the Month"}, //1AC
};

map<string, char*> awards_rename_short_croatia = {

};

map<string, char*> awards_rename_short_holland = {
	{ "Dutch Premier Division Golden Boot", "Manager of the Year" },
	{ "Dutch First Division Golden Boot", "Manager of the Year" },
	{ "Dutch Manager of the Year", "Young Player of the Year" },
};

map<string, char*> awards_rename_short_italy = {

};

map<string, char*> awards_rename_short_portugal = {
	{ "Asian All Star XI", "Manager of the Year" },
};

map<string, char*> awards_rename_short_poland = {
	{ "Polish First Division Manager of the Month", "Team of the Year" },
	{ "Polish Second Division Manager of the Month", "Team of the Year" },
};

map<string, char*> awards_rename_long = {
	{"EFL Championship Team of the Year", "English Championship Team of the Year"},
	{"EFL One Team of the Year", "English League One Team of the Year"},
	{"EFL Two Team of the Year", "English League Two Team of the Year"},
	{"EFL Championship Player of the Month", "English Championship Player of the Month"},
	{"EFL One Player of the Month", "English League One Player of the Month"},
	{"EFL Two Player of the Month", "English League Two Player of the Month"},
	{"EFL Championship Young Player of the Month", "English Championship Young Player of the Month"},
	{"EFL One Young Player of the Month", "English League One Young Player of the Month"},
	{"EFL Two Young Player of the Month", "English League Two Young Player of the Month"},
	{"EFL Championship Team of the Week", "English Championship Team of the Week"},
	{"EFL One Team of the Week", "English League One Team of the Week"},
	{"EFL Two Team of the Week", "English League Two Team of the Week"},
	{"EFL Championship Manager of the Year", "English Championship Manager of the Year"},
	{"EFL Championship Manager of the Month", "English Championship Manager of the Month"},
	{"EFL One Manager of the Year", "English League One Manager of the Year"},
	{"EFL One Manager of the Month", "English League One Manager of the Month"},
	{"EFL Two Manager of the Year", "English League Two Manager of the Year"},
	{"EFL Two Manager of the Month", "English League Two Manager of the Month"},
	{"German Defender of the Year", "German 3. Liga Manager of the Year"},
	{"German Goalkeeper of the Year", "German 3. Liga Player of the Month"},
	{"German Midfielder of the Year", "German 3. Liga Team of the Week"},
	{"German Striker of the Year", "German 3. Liga Top Goalscorer"},
	{"German Sweeper of the Year", "English National North Manager of the Year"},
	{"English Footballer of the Year", "English National South Manager of the Year"},
	{"Asian Assistant Referee of the Year", "English National North Manager of the Month"}, //200
	{"Asian Referee of the Year", "English National South Manager of the Month"}, //1FF
	{"Belgian Referee of the Year", "English National North Player of the Month"}, //1E9
	{"Chinese Golden Whistle", "English National South Player of the Month"}, //193
	{"Mexican Physio of the Year", "English National North Team of the Week"}, //184
	{"South Korean Referee of the Month", "English National South Team of the Week"}, //20A
	{"South Korean Referee of the Year", "English National North Team of the Year"}, //211
	{"South Korean Fair Play of the Month", "English National South Team of the Year"}, //20B
	{"South Korean Fair Play of the Year", "English National North Young Player of the Month"}, //20F
	{"South Korean Goalkeeper of the Month", "South Korean Manager of the Month"},
	{"South African Young Player of the Year", "English National South Young Player of the Month"}, //1AC
	{"Portuguese Premier League Manager of the Year", "Liga Portugal 1 Manager of the Year"},
	{"Portuguese Premier League Most Man of the Match", "Liga Portugal 1 Most Man of the Match"},
	{"Portuguese Premier League Player of the Year", "Liga Portugal 1 Player of the Year"},
	{"Portuguese Premier League Team of the Week", "Liga Portugal 1 Team of the Week"},
	{"Portuguese Premier League Team of the Year", "Liga Portugal 1 Team of the Year"},
	{"Portuguese Premier League Top Goalscorer", "Liga Portugal 1 Top Goalscorer"},
	{"Portuguese Second League Manager of the Year", "Liga Portugal 2 Manager of the Year"},
	{"Portuguese Second League Most Man of the Match", "Liga Portugal 2 Most Man of the Match"},
	{"Portuguese Second League Player of the Year", "Liga Portugal 2 Player of the Year"},
	{"Portuguese Second League Team of the Week", "Liga Portugal 2 Team of the Week"},
	{"Portuguese Second League Team of the Year", "Liga Portugal 2 Team of the Year"},
	{"Portuguese Second League Top Goalscorer", "Liga Portugal 2 Top Goalscorer"},
	{"Brazilian 1st Division Player of the Year", "Brazilian Série A Player of the Year"},
	{"Brazilian 1st Division Team of the Week", "Brazilian Série A Team of the Week"},
	{"Brazilian 1st Division Team of the Year", "Brazilian Série A Team of the Year"},
	{"Brazilian 1st Division Top Goalscorer", "Brazilian Série A Top Goalscorer"},
	{"Brazilian 1st Division Young Player of the Year", "Brazilian Série A Young Player of the Year"},
	{"Brazilian 2nd Division Player of the Year", "Brazilian Série B Player of the Year"},
	{"Brazilian 2nd Division Team of the Week", "Brazilian Série B Team of the Week"},
	{"Brazilian 2nd Division Team of the Year", "Brazilian Série B Team of the Year"},
	{"Brazilian 2nd Division Top Goalscorer", "Brazilian Série B Top Goalscorer"},
	{"Brazilian 2nd Division Young Player of the Year", "Brazilian Série B Young Player of the Year"},
	{"Brazilian 3rd Division Player of the Year", "Brazilian Série C Player of the Year"},
	{"Brazilian 3rd Division Team of the Week", "Brazilian Série C Team of the Week"},
	{"Brazilian 3rd Division Team of the Year", "Brazilian Série C Team of the Year"},
	{"Brazilian 3rd Division Top Goalscorer", "Brazilian Série C Top Goalscorer"},
	{"Brazilian 3rd Division Young Player of the Year", "Série C Division Young Player of the Year"},
	{"Brazilian Bahia Best Goalkeeper", "Campeonato Baiano Best Goalkeeper"},
	{"Brazilian Bahia Best Player", "Campeonato Baiano Best Player"},
	{"Brazilian Bahia Team of the Week", "Campeonato Baiano Team of the Week"},
	{"Brazilian Bahia Top Goalscorer", "Campeonato Baiano Top Goalscorer"},
	{"Brazilian Central Best Goalkeeper", "Campeonato Central Best Goalkeeper"},
	{"Brazilian Central Best Player", "Campeonato Central Best Player"},
	{"Brazilian Central Team of the Week", "Campeonato Central Team of the Week"},
	{"Brazilian Central Top Goalscorer", "Campeonato Central Top Goalscorer"},
	{"Brazilian Gaúcho Best Goalkeeper", "Campeonato Gaúcho Best Goalkeeper"},
	{"Brazilian Gaúcho Best Player", "Campeonato Gaúcho Best Player"},
	{"Brazilian Gaúcho Team of the Week", "Campeonato Gaúcho Team of the Week"},
	{"Brazilian Gaúcho Top Goalscorer", "Campeonato Gaúcho Top Goalscorer"},
	{"Brazilian Goiás Best Goalkeeper", "Campeonato Goiano Best Goalkeeper"},
	{"Brazilian Goiás Best Player", "Campeonato Goiano Best Player"},
	{"Brazilian Goiás Team of the Week", "Campeonato Goiano Team of the Week"},
	{"Brazilian Goiás Top Goalscorer", "Campeonato Goiano Top Goalscorer"},
	{"Brazilian Minas Gerais Best Goalkeeper", "Campeonato Mineiro Best Goalkeeper"},
	{"Brazilian Minas Gerais Best Player", "Campeonato Mineiro Best Player"},
	{"Brazilian Minas Gerais Team of the Week", "Campeonato Mineiro Team of the Week"},
	{"Brazilian Minas Gerais Top Goalscorer", "Campeonato Mineiro Top Goalscorer"},
	{"Brazilian North Best Goalkeeper", "Campeonato do Norte Best Goalkeeper"},
	{"Brazilian North Best Player", "Campeonato do Norte Best Player"},
	{"Brazilian North Team of the Week", "Campeonato do Norte Team of the Week"},
	{"Brazilian North Top Goalscorer", "Campeonato do Norte Top Goalscorer"},
	{"Brazilian Northeast Best Goalkeeper", "Campeonato do Nordeste Best Goalkeeper"},
	{"Brazilian Northeast Best Player", "Campeonato do Nordeste Best Player"},
	{"Brazilian Northeast Team of the Week", "Campeonato do Nordeste Team of the Week"},
	{"Brazilian Northeast Top Goalscorer", "Campeonato do Nordeste Top Goalscorer"},
	{"Brazilian Paraná Best Goalkeeper", "Campeonato Paranaense Best Goalkeeper"},
	{"Brazilian Paraná Best Player", "Campeonato Paranaense Best Player"},
	{"Brazilian Paraná Team of the Week", "Campeonato Paranaense Team of the Week"},
	{"Brazilian Paraná Top Goalscorer", "Campeonato Paranaense Top Goalscorer"},
	{"Brazilian Pernambuco Best Goalkeeper", "Campeonato Pernambucano Best Goalkeeper"},
	{"Brazilian Pernambuco Best Player", "Campeonato Pernambucano Best Player"},
	{"Brazilian Pernambuco Team of the Week", "Campeonato Pernambucano Team of the Week"},
	{"Brazilian Pernambuco Top Goalscorer", "Campeonato Pernambucano Top Goalscorer"},
	{"Brazilian Rio de Janeiro Best Goalkeeper", "Campeonato Carioca Best Goalkeeper"},
	{"Brazilian Rio de Janeiro Best Player", "Campeonato Carioca Best Player"},
	{"Brazilian Rio de Janeiro Team of the Week", "Campeonato Carioca Team of the Week"},
	{"Brazilian Rio de Janeiro Top Goalscorer", "Campeonato Carioca Top Goalscorer"},
	{"Brazilian Santa Catarina Best Goalkeeper", "Campeonato Catarinense Best Goalkeeper"},
	{"Brazilian Santa Catarina Best Player", "Campeonato Catarinense Best Player"},
	{"Brazilian Santa Catarina Team of the Week", "Campeonato Catarinense Team of the Week"},
	{"Brazilian Santa Catarina Top Goalscorer", "Campeonato Catarinense Top Goalscorer"},
	{"Brazilian São Paulo Best Goalkeeper", "Campeonato Paulista Best Goalkeeper"},
	{"Brazilian São Paulo Best Player", "Campeonato Paulista Best Player"},
	{"Brazilian São Paulo Team of the Week", "Campeonato Paulista Team of the Week"},
	{"Brazilian São Paulo Top Goalscorer", "Campeonato Paulista Top Goalscorer"},
	{"Danish Premier Division Player of the Year", "Danish Superliga Player of the Year"},
	{"Danish Premier Division Young Player of the Year", "Danish Superliga Young Player of the Year"},
	{"Danish Kvalifikationsrækken Player of the Year", "Danish Third Division Player of the Year"},
	{"Danish Kvalifikationsrækken Young Player of Year", "Danish Third Division Young Player of Year"},
	{"Danish Premier Division Team of the Week", "Danish Superliga Team of the Week"},
	{ "Finnish Ykkönen Manager of the Month", "Finnish Ykkösliiga Manager of the Month" },
	{ "Finnish Ykkönen Player of the Month", "Finnish Ykkösliiga Player of the Month" },
	{ "Finnish Ykkönen Team of the Week", "Finnish Ykkösliiga Team of the Week" },
	{ "Finnish Ykkönen Team of the Year", "Finnish Ykkösliiga Team of the Year" },
	{ "Finnish Ykkönen Top Goalscorer", "Finnish Ykkösliiga Top Goalscorer" },
	{ "Greek Football League Manager of the Year", "Greek Super League 2 Manager of the Year" },
	{ "Greek Football League Player of the Year", "Greek Super League 2 Player of the Year" },
	{ "Greek Football League Team of the Week", "Greek Super League 2 Team of the Week" },
	{ "Greek Football League Top Goalscorer", "Greek Super League 2 Top Goalscorer" },
	{ "Greek Superleague Manager of the Year", "Greek Super League Manager of the Year" },
	{ "Greek Superleague Player of the Year", "Greek Super League Player of the Year" },
	{ "Greek Superleague Team of the Week", "Greek Super League Team of the Week" },
	{ "Greek Superleague Top Goalscorer", "Greek Super League Top Goalscorer" },
	{ "Swedish First Division Team of the Week", "Swedish Superettan Team of the Week" },
	{ "Swedish Premier Division Team of the Week", "Swedish Allsvenskan Team of the Week" },
	{ "Swedish Premier Division Top Goalscorer", "Swedish Allsvenskan Top Goalscorer" },
	{ "Polish First Division Manager of the Year", "Polish Ekstraklasa Manager of the Year" },
	{ "Polish First Division Player of the Year", "Polish Ekstraklasa Player of the Year" },
	{ "Polish First Division Team of the Week", "Polish Ekstraklasa Team of the Week" },
	{ "Polish First Division Young Player of the Year", "Polish Ekstraklasa Young Player of the Year" },
	{ "Polish Second Division Manager of the Year", "Polish I Liga Manager of the Year" },
	{ "Polish Second Division Player of the Year", "Polish I Liga Player of the Year" },
	{ "Polish Second Division Team of the Week", "Polish I Liga Team of the Week" },
	{ "Polish Second Division Young Player of the Year", "Polish I Liga Young Player of the Year" },
	{ "Norwegian First Division Manager of the Month", "Norwegian 1. Divisjon Manager of the Month" },
	{ "Norwegian First Division Player of the Month", "Norwegian 1. Divisjon Player of the Month" },
	{ "Norwegian First Division Team of the Week", "Norwegian 1. Divisjon Team of the Week" },
	{ "Norwegian Premier Division Manager of the Month", "Norwegian Eliteserien Manager of the Month" },
	{ "Norwegian Premier Division Player of the Month", "Norwegian Eliteserien Player of the Month" },
	{ "Norwegian Premier Division Team of the Week", "Norwegian Eliteserien Team of the Week" },
	{ "Dutch First Division Player of the Year", "Dutch Eerste Divisie Player of the Year" },
	{ "Dutch First Division Team of the Week", "Dutch Eerste Divisie Team of the Week" },
	{ "Dutch First Division Top Goalscorer", "Dutch Eerste Divisie Top Goalscorer" },
	{ "Dutch Premier Division Player of the Year", "Dutch Eredivisie Player of the Year" },
	{ "Dutch Premier Division Team of the Week", "Dutch Eredivisie Team of the Week" },
	{ "Dutch Premier Division Top Goalscorer", "Dutch Eredivisie Top Goalscorer" },
	{ "N. Irish Premier Division Manager of the Month", "NIFL Premiership Manager of the Month" },
	{ "N. Irish Premier Division Manager of the Year", "NIFL Premiership Manager of the Year" },
	{ "N. Irish Premier Division Player of the Year", "NIFL Premiership Player of the Year" },
	{ "N. Irish Premier Division Team of the Week", "NIFL Premiership Team of the Week" },
	{ "N. Irish Premier Division Top Goalscorer", "NIFL Premiership Top Goalscorer" },
	{ "N. Irish Premier Division Young Player of the Year", "NIFL Premiership Young Player of the Year" },
	{ "N. Irish First Division Manager of the Month", "NIFL Championship Manager of the Month" },
	{ "N. Irish First Division Manager of the Year", "NIFL Championship Manager of the Year" },
	{ "N. Irish First Division Player of the Year", "NIFL Championship Player of the Year" },
	{ "N. Irish First Division Team of the Week", "NIFL Championship Team of the Week" },
	{ "N. Irish First Division Top Goalscorer", "NIFL Championship Top Goalscorer" },
	{ "N. Irish First Division Young Player of the Year", "NIFL Championship Young Player of the Year" },
	{ "N. Irish Player of the Year", "NIFL Player of the Year" },
};

map<string, char*> awards_rename_long_croatia = {
	{ "Croatian First Division Player of the Year", "Croatian HNL Player of the Year" },
	{ "Croatian First Division Team of the Week", "Croatian HNL Team of the Week" },
	{ "Croatian First Division Top Goalscorer", "Croatian HNL Top Goalscorer" },
	{ "Croatian Second Division A Player of the Year", "Croatian 1. NL Player of the Year" },
	{ "Croatian Second Division A Team of the Week", "Croatian 1. NL Team of the Week" },
	{ "Croatian Second Division A Top Goalscorer", "Croatian 1. NL Top Goalscorer" },
	{ "Croatian Second Division B Player of the Year", "Croatian 2. NL Player of the Year" },
	{ "Croatian Second Division B Team of the Week", "Croatian 2. NL Team of the Week" },
	{ "Croatian Second Division B Top Goalscorer", "Croatian 2. NL Top Goalscorer" },
};

map<string, char*> awards_rename_long_holland = {
	{ "Dutch Premier Division Golden Boot", "Dutch Eredivisie Manager of the Year" },
	{ "Dutch First Division Golden Boot", "Dutch Eerste Divisie Manager of the Year" },
	{ "Dutch Manager of the Year", "Dutch Eredivisie Young Player of the Year" },
	{ "Dutch Young Player of the Year", "Dutch Eerste Divisie Young Player of the Year" },
};

map<string, char*> awards_rename_long_italy = {
	{ "Italian Serie C1/A Player of the Year", "Italian Serie C Player of the Year" },
	{ "Italian Serie C1/A Manager of the Year", "Italian Serie C Manager of the Year" },
	{ "Italian Serie C1/A Team of the Week", "Italian Serie C Team of the Week" },
	{ "Italian Serie C1/A Team of the Year", "Italian Serie C Team of the Year" },
	{ "Italian Serie C1/A Top Goalscorer", "Italian Serie C Top Goalscorer" },
};

map<string, char*> awards_rename_long_portugal = {
	{ "Portuguese Second Division B Most Man of the Match", "Liga 3 Most Man of the Match" },
	{ "Portuguese Second Division B Player of the Year", "Liga 3 Player of the Year" },
	{ "Portuguese Second Division B Team of the Week", "Liga 3 Team of the Week" },
	{ "Portuguese Second Division B Team of the Year", "Liga 3 Team of the Year" },
	{ "Portuguese Second Division B Top Goalscorer", "Liga 3 Top Goalscorer" },
	{ "Asian All Star XI", "Liga 3 Manager of the Year" },
};

map<string, char*> awards_rename_long_poland = {
	{ "Polish First Division Manager of the Month", "Polish Ekstraklasa Team of the Year" },
	{ "Polish Second Division Manager of the Month", "Polish I Liga Team of the Year" },
};

map<string, DWORD> club_dword_match = {
	{"MLS All Stars East", 0x9d00a4},
	{"MLS All Stars West", 0x9d00a8},
	{"River Plate", 0x9d00ac},
	{"Vélez Sarsfield", 0x9d00b0},
	{"Independiente", 0x9d00b4},
	{"Independiente Rivadavia de Mendoza", 0x9d00b8},
	{"Racing de Córdoba", 0x9d00bc},
	{"Villa Mitre de Bahía Blanca", 0x9d00c0},
	{"Argentino de Rosario", 0x9d00c4},
	{"Temperley", 0x9d00c8},
	{"Lanús", 0x9d00cc},
	{"Boca Juniors", 0x9d00d0},
	{"Gimnasia y Esgrima de La Plata", 0x9d00d4},
	{"San Lorenzo de Almagro", 0x9d00d8},
	{"Argentinos Juniors", 0x9d00dc},
	{"Rosario Central", 0x9d00e0},
	{"Newell's Old Boys", 0x9d00e4},
	{"Racing Club", 0x9d00e8},
	{"Colón de Santa Fé", 0x9d00ec},
	{"Platense", 0x9d00f0},
	{"Ferro Carril Oeste", 0x9d00f4},
	{"Estudiantes de La Plata", 0x9d00f8},
	{"Gimnasia y Esgrima de Jujuy", 0x9d00fc},
	{"Unión de Santa Fé", 0x9d0100},
	{"Huracán", 0x9d0104},
	{"Talleres de Córdoba", 0x9d0108},
	{"Belgrano de Córdoba", 0x9d010c},
	{"Arsenal", 0x9d0110},
	{"Crystal Palace", 0x9d0114},
	{"Glasgow Celtic", 0x9d0118},
	{"Glasgow Rangers", 0x9d011c},
	{"Athletic Club de Bilbao", 0x9d0120},
	{"C.D. Alavés", 0x9d0124},
	{"Real Sociedad C.F.", 0x9d0128},
	{"Atlético de Madrid", 0x9d012c},
	{"Atlético de Madrid B", 0x9d0130},
	{"Athletic Club de Bilbao B", 0x9d0134},
	{"F.C. Barcelona", 0x9d0138},
	{"F.C. Barcelona B", 0x9d013c},
	{"Real Valladolid", 0x9d0140},
	{"Real Valladolid B", 0x9d0144},
	{"Málaga C.F.", 0x9d0148},
	{"Málaga C.F. B", 0x9d014c},
	{"Real Betis Balompié", 0x9d0150},
	{"Real Betis Balompié B", 0x9d0154},
	{"Real Club Celta de Vigo", 0x9d0158},
	{"Real Club Celta de Vigo B", 0x9d015c},
	{"Deportivo de La Coruña", 0x9d0160},
	{"Deportivo de La Coruña B", 0x9d0164},
	{"R.C.D. Espanyol", 0x9d0168},
	{"R.C.D. Espanyol B", 0x9d016c},
	{"FC Augsburg", 0x9d0170}, // replaced Logroñés
	{"FC Augsburg II", 0x9d0174}, // replaced Logroñés B
	{"R.C.D. Mallorca", 0x9d0178},
	{"R.C.D. Mallorca B", 0x9d017c},
	{"Club Atlético Osasuna", 0x9d0180},
	{"Club Atlético Osasuna B", 0x9d0184},
	{"Real Oviedo C.F.", 0x9d0188},
	{"Real Oviedo C.F. B", 0x9d018c},
	{"Real Madrid C.F.", 0x9d0190},
	{"Real Madrid C.F. B", 0x9d0194},
	{"Sevilla C.F.", 0x9d0198},
	{"Sevilla C.F. B", 0x9d019c},
	{"Real Sociedad C.F. B", 0x9d01a0},
	{"Instituto de Córdoba", 0x9d01a4},
	{"San Martín de San Juan", 0x9d01a8},
	{"Gimnasia y Tiro de Salta", 0x9d01ac},
	{"Atlético Rafaela", 0x9d01b0},
	{"San Martín de Tucumán", 0x9d01b4},
	{"Almirante Brown de Arrecifes", 0x9d01b8},
	{"Atlético Tucumán", 0x9d01bc},
	{"Olimpo de Bahía Blanca", 0x9d01c0},
	{"Huracán de Corrientes", 0x9d01c4},
	{"Aldosivi", 0x9d01c8},
	{"Cipolletti de Río Negro", 0x9d01cc},
	{"San Martín de Mendoza", 0x9d01d0},
	{"Douglas Haig", 0x9d01d4},
	{"Gimnasia y Esgrima de Concepción del Uruguay", 0x9d01d8},
	{"Juventud Antoniana de Salta", 0x9d01dc},
	{"Godoy Cruz de Mendoza", 0x9d01e0},
	{"Banfield", 0x9d01e4},
	{"Los Andes", 0x9d01e8},
	{"Quilmes", 0x9d01ec},
	{"Central Córdoba de Rosario", 0x9d01f0},
	{"Chacarita Juniors", 0x9d01f4},
	{"All Boys", 0x9d01f8},
	{"San Miguel", 0x9d01fc},
	{"Nueva Chicago", 0x9d0200},
	{"Defensa y Justicia", 0x9d0204},
	{"Arsenal de Sarandí", 0x9d0208},
	{"Huracán de Tres Arroyos", 0x9d020c},
	{"Defensores de Belgrano", 0x9d0210},
	{"Deportivo Morón", 0x9d0214},
	{"Estudiantes de Buenos Aires", 0x9d0218},
	{"Almagro", 0x9d021c},
	{"Atlanta", 0x9d0220},
	{"Deportivo Español", 0x9d0224},
	{"El Porvenir", 0x9d0228},
	{"Tigre", 0x9d022c},
	{"Middlesbrough", 0x9d0230},
	{"Newcastle United", 0x9d0234},
	{"Sunderland", 0x9d0238},
	{"Aston Villa", 0x9d023c},
	{"Manchester United", 0x9d0240},
	{"Liverpool", 0x9d0244},
	{"Everton", 0x9d0248},
	{"Tottenham Hotspur", 0x9d024c},
	{"Chelsea", 0x9d0250},
	{"Valencia C.F.", 0x9d0254},
	{"Valencia C.F. B", 0x9d0258},
	{"Brighton and Hove Albion", 0x9d025c},
	{"Southampton", 0x9d0260},
	{"Al-Ahli SFC", 0x9d0264},
	{"FC Metz", 0x9d0268},
	{"Cruzeiro Esporte Clube", 0x9d026c},
	{"São Paulo Futebol Clube", 0x9d0270},
	{"Sociedade Esportiva Palmeiras", 0x9d0274},
	{"Sport Club Corinthians Paulista", 0x9d0278},
	{"Grêmio Foot-Ball Porto-Alegrense", 0x9d027c},
	{"Club Social y Deportivo Colo Colo", 0x9d0280},
	{"Club de Fútbol de la Universidad de Chile", 0x9d0284},
	{"Club Deportivo Universidad Católica", 0x9d0288},
	{"Nacional Montevideo", 0x9d028c},
	{"Club Olimpia", 0x9d0290},
	{"Club Cerro Porteño", 0x9d0294},
	{"Club Atlético Peñarol", 0x9d0298},
	{"Elgin City", 0x9d029c},
	{"Peterhead", 0x9d02a0},
	{"Eintracht Frankfurt", 0x9d02a4},
	{"Eintracht Frankfurt Amateure", 0x9d02a8},
	{"FC Hansa Rostock", 0x9d02ac},
	{"FC Hansa Rostock Amateure", 0x9d02b0},
	{"FC Schalke 04", 0x9d02b4},
	{"FC Schalke 04 Amateure", 0x9d02b8},
	{"SpVgg Greuther Fürth", 0x9d02bc},
	{"SpVgg Greuther Fürth II", 0x9d02c0},
	{"Sport Lisboa e Benfica", 0x9d02c4},
	{"Sport Lisboa e Benfica B", 0x9d02c8},
	{"Sporting Clube de Braga", 0x9d02cc},
	{"Sporting Clube de Braga B", 0x9d02d0},
	{"Clube Sport Marítimo", 0x9d02d4},
	{"Clube Sport Marítimo B", 0x9d02d8},
	{"Futebol Clube do Porto", 0x9d02dc},
	{"Futebol Clube do Porto B", 0x9d02e0},
	{"S.D. Éibar", 0x9d02e4},
	{"Amurrio C.F.", 0x9d02e8},
	{"C.D. Aurrerá Vitoria", 0x9d02ec},
	{"Barakaldo C.F.", 0x9d02f0},
	{"S.D. Beasaín", 0x9d02f4},
	{"Bermeo Club", 0x9d02f8},
	{"Gernika Club", 0x9d02fc},
	{"S.D. Lemona", 0x9d0304},
	{"Elgoibar C.D.", 0x9d0308},
	{"Hernani C.D.", 0x9d030c},
	{"Zalla U.C.", 0x9d0310},
	{"Cultural Durango", 0x9d0314},
	{"S.D. Amorebieta", 0x9d0318},
	{"Arenas Getxo Bilbao", 0x9d031c},
	{"Aurrerá Ondarroa C.D.", 0x9d0320},
	{"Baskonia C.D.", 0x9d0324},
	{"S.D. Éibar B", 0x9d0328},
	{"U.D. San Pedro", 0x9d032c},
	{"Santurtzi C.D.", 0x9d0330},
	{"Sestao River Club", 0x9d0334},
	{"Tolosa C.F.", 0x9d0338},
	{"Coritiba Football Club", 0x9d033c},
	{"Santos Futebol Clube", 0x9d0340},
	{"Sport Club do Recife", 0x9d0344},
	{"Associação Portuguesa de Desportos", 0x9d0348},
	{"Clube Atlético Mineiro", 0x9d0350},
	{"Clube de Regatas Vasco da Gama", 0x9d0354},
	{"Clube de Regatas do Flamengo", 0x9d0358},
	{"Sport Club Internacional", 0x9d035c},
	{"Esporte Clube Vitória", 0x9d0360},
	{"Botafogo de Futebol e Regatas", 0x9d0364},
	{"Clube Atlético Paranaense", 0x9d0368},
	{"Associação Atlética Ponte Preta", 0x9d036c},
	{"Esporte Clube Juventude", 0x9d0370},
	{"Guarani Futebol Clube", 0x9d0374},
	{"Paraná Clube", 0x9d0378},
	{"Chicago Fire", 0x9d037c},
	{"Miami Fusion FC", 0x9d0380},
	{"Washington DC United", 0x9d0384},
	{"Tampa Bay Mutiny", 0x9d0388},
	{"San Jose Earthquakes", 0x9d038c},
	{"New England Revolution", 0x9d0390},
	{"NY/NJ Metrostars", 0x9d0394},
	{"Los Angeles Galaxy", 0x9d0398},
	{"Kansas City Wizards", 0x9d039c},
	{"Dallas Burn", 0x9d03a0},
	{"Columbus Crew", 0x9d03a4},
	{"Colorado Rapids", 0x9d03a8},
	{"Albacete Balompié", 0x9d03ac},
	{"Albacete Balompié B", 0x9d03b0},
	{"TSG 1899 Hoffenheim", 0x9d03b4}, // replaced Badajoz
	{"TSG 1899 Hoffenheim II", 0x9d03b8}, // replaced Badajoz B
	{"C.D. Leganés", 0x9d03bc},
	{"C.D. Leganés B", 0x9d03c0},
	{"C.D. Tenerife", 0x9d03c4},
	{"C.D. Tenerife B", 0x9d03c8},
	{"SC Paderborn 07", 0x9d03cc},
	{"SC Paderborn 07 Reserves", 0x9d03d0},
	{"Deportivo Alavés B", 0x9d03d4},
	{"CD Lugo", 0x9d03d8},
	{"CD Lugo B Polvorín", 0x9d03dc},
	{"Racing Club de Santander", 0x9d03e0},
	{"Rayo Cantabria", 0x9d03e4}, // Racing Santander B
	{"Rayo Vallecano de Madrid", 0x9d03e8},
	{"Rayo Vallecano de Madrid B", 0x9d03ec},
	{"Real Murcia C.F.", 0x9d03f0},
	{"Real Murcia C.F. B", 0x9d03f4},
	{"Real Sporting de Gijón", 0x9d03f8},
	{"Real Sporting de Gijón B", 0x9d03fc},
	{"Real Zaragoza", 0x9d0400},
	{"Real Zaragoza B", 0x9d0404},
	{"Granada CF", 0x9d0408},
	{"Granada CF B", 0x9d040c},
	{"U.D. Las Palmas", 0x9d0410},
	{"U.D. Las Palmas B", 0x9d0414},
	{"Cádiz CF", 0x9d0418},
	{"Cádiz CF Mirandilla", 0x9d041c},
	{"Galatasaray SK", 0x9d0420},
	{"Besiktas JK", 0x9d0424},
	{"Fenerbahçe SK", 0x9d0428},
	{"General Paz Juniors de Córdoba", 0x9d042c},
	{"Swansea City", 0x9d0430},
	{"Cardiff City", 0x9d0434},
	{"Merthyr Tydfil", 0x9d0438},
	{"Wrexham", 0x9d043c},
	{"Sporting Clube de Portugal", 0x9d0440},
	{"Sporting Clube de Portugal B", 0x9d0444},
	{"Arminia Bielefeld", 0x9d0448},
	{"Arminia Bielefeld II", 0x9d044c},
	{"FC Cartagena", 0x9d0450},
	{"FC Cartagena B", 0x9d0454},
	{"Holstein Kiel", 0x9d0458},
	{"Holstein Kiel II", 0x9d045c},
	{"Hannover 96", 0x9d0460},
	{"Hannover 96 Amateure", 0x9d0464},
	{"1.FC Köln", 0x9d0468},
	{"1.FC Köln Amateure", 0x9d046c},
	{"Borussia M'gladbach", 0x9d0470},
	{"Bor. M'gladbach Amateure", 0x9d0474},
	{"1.FC Nürnberg", 0x9d0478},
	{"1.FC Nürnberg Amateure", 0x9d047c},
	{"FC Ingolstadt 04", 0x9d0480},
	{"FC Ingolstadt 04 II", 0x9d0484},
	{"SC Freiburg", 0x9d0488},
	{"SC Freiburg Amateure", 0x9d048c},
	{"SSV Jahn Regensburg", 0x9d0490},
	{"SSV Jahn Regensburg II", 0x9d0494},
	{"Burgos CF", 0x9d0498},
	{"Burgos CF Promesas", 0x9d049c},
	{"SpVgg Unterhaching", 0x9d04a0},
	{"SpVgg Unterhaching II", 0x9d04a4},
	{"Villarreal CF", 0x9d04a8},
	{"Villarreal CF B", 0x9d04ac},
	{"SD Huesca", 0x9d04b0},
	{"SD Huesca B", 0x9d04b4},
	{"C.D. Castellón", 0x9d04b8},
	{"C.D. Castellón B", 0x9d04bc},
	{"Getafe CF", 0x9d04c0},
	{"Getafe CF B", 0x9d04c4},
	{"UD Logroñés", 0x9d04c8},
	{"UD Logroñés Promesas", 0x9d04cc},
	{"UD Almería", 0x9d04d0},
	{"UD Almería B", 0x9d04d4},
	{"Córdoba C.F.", 0x9d04d8},
	{"Córdoba C.F. B", 0x9d04dc},
	{"Cultural Leonesa", 0x9d04e0},
	{"Cultural Leonesa B", 0x9d04e4},
	{"Elche C.F.", 0x9d04e8},
	{"Elche C.F. B", 0x9d04ec},
	{"Levante U.D.", 0x9d04f0},
	{"Levante U.D. B", 0x9d04f4},
	{"GD Chaves", 0x9d04f8},
	{"GD Chaves Satelite", 0x9d04fc},
	{"Recreativo de Huelva", 0x9d0500},
	{"Recreativo de Huelva B", 0x9d0504},
	{"Fortuna Düsseldorf", 0x9d0508},
	{"Fortuna Düsseldorf II", 0x9d050c},
	{"Vitória Guimarães SC", 0x9d0510},
	{"Vitória Guimarães SC B", 0x9d0514},
	{"FSV Mainz 05", 0x9d0518},
	{"FSV Mainz 05 II", 0x9d051c},
	{"CD Numancia", 0x9d0520},
	{"CD Numancia B", 0x9d0524},
	{"1.FC Kaiserslautern Amateure", 0xb63c9c},
	{"AD Alcorcón B", 0xb63ca0},
	{"VfL Bochum Amateure", 0xb63ca4},
	{"Hamburger SV Amateure", 0xb63ca8},
	{"Borussia Dortmund Amateure", 0xb63cac},
	{"FC St. Pauli Amateure", 0xb63cb0},
	{"FC St. Pauli", 0xb63cb4},
	{"FC Alverca B", 0xb63cb8},
	{"AD Alcorcón", 0xb63cbc},
	{"SV Werder Bremen", 0xb63cc0},
	{"VfB Stuttgart", 0xb63cc4},
	{"TSV 1860 München", 0xb63cc8},
	{"TSV 1860 München Amateure", 0xb63ccc},
	{"FC Bayern München Amateure", 0xb63cd0},
	{"Hamburger SV", 0xb63cd4},
	{"FC Bayern München", 0xb63cd8},
	{"1.FC Kaiserslautern", 0xb63cdc},
	{"FC Alverca", 0xb63ce0},
	{"Hertha BSC Berlin", 0xb63ce4},
	{"Borussia Dortmund", 0xb63ce8},
	{"Hertha BSC Amateure", 0xb63cec},
	{"Karlsruher SC", 0xb63cf0},
	{"VfB Stuttgart Amateure", 0xb63cf4},
	{"Karlsruher SC II", 0xb63cf8},
	{"VfL Bochum", 0xb63cfc},
	{"SV Werder Bremen Amateure", 0xb63d00}
};

map<string, DWORD> league_dword_match = {
	{"French Championnat National 3", 0x9CF548},
	{"German Bundesliga", 0x9CF54C},
	{"German 2. Bundesliga", 0x9CF550},
	{"German 3. Liga West", 0x9CF554},
	{"German 3. Liga Osten", 0x9CF558},
	{"German 3. Liga Nord", 0x9CF55C},
	{"German 3. Liga Süd", 0x9CF560},
	{"German 3. Liga", 0x9CF564},
	{"Dutch Eredivisie", 0x9CF568},
	{"Dutch Eerste Divisie", 0x9CF56C},
	{"Italian Serie A", 0x9CF570},
	{"Italian Serie B", 0x9CF574},
	{"Italian Serie C1/A", 0x9CF578},
	{"Italian Serie C1/B", 0x9CF57C},
	{"Italian Serie C2/A", 0x9CF580},
	{"Italian Serie C2/B", 0x9CF584},
	{"Italian Serie C2/C", 0x9CF588},
	{"Italian Serie D", 0x9CF58C},
	{"Major League Soccer", 0x9CF590},
	{"American USL Championship", 0x9CF594},
	{"American USL League One", 0x9CF598},
	{"Belgian Pro League", 0x9CF59C},
	{"Belgian Challenger Pro League", 0x9CF5A0},
	{"Belgian National Division 1 A", 0x9CF5A4},
	{"Belgian National Division 1 B", 0x9CF5A8},
	{"Danish Superliga", 0x9CF5AC},
	{"Danish 1st Division", 0x9CF5B0},
	{"Danish 2nd Division", 0x9CF5B4},
	{"Danish 3rd Division", 0x9CF5B8},
	{"English Premier League", 0x9CF5BC},
	{"English Football League Championship", 0x9CF5C0},
	{"English Football League One", 0x9CF5C4},
	{"English Football League Two", 0x9CF5C8},
	{"French Ligue 1", 0x9CF5CC},
	{"French Ligue 2", 0x9CF5D0},
	{"French Championnat National 1", 0x9CF5D4},
	{"French Championnat National 2", 0x9CF5D8},
	{"Scottish Premiership", 0x9CF5DC},
	{"Scottish Championship", 0x9CF5E0},
	{"Scottish League One", 0x9CF5E4},
	{"Scottish League Two", 0x9CF5E8},
	{"Swedish Allsvenskan", 0x9CF5EC},
	{"Swedish Superettan", 0x9CF5F0},
	{"Swedish Ettan South Gotaland", 0x9CF5F4},
	{"Swedish Ettan North", 0x9CF5F8},
	{"Swedish Ettan East Svealand", 0x9CF5FC},
	{"Swedish Ettan East Gotaland", 0x9CF600},
	{"Swedish Ettan West Svealand", 0x9CF604},
	{"Swedish Ettan West Gotaland", 0x9CF608},
	{"Liga Portugal 1", 0x9CF60C},
	{"Liga Portugal 2", 0x9CF610},
	{"Liga 3 North", 0x9CF614},
	{"Liga 3 Central", 0x9CF618},
	{"Liga 3 South", 0x9CF61C},
	{"Campeonato de Portugal", 0x9CF620},
	{"Spanish La Liga", 0x9CF624},
	{"Spanish La Liga 2", 0x9CF628},
	{"Spanish Primera Federación Group 1", 0x9CF62C},
	{"Spanish Primera Federación Group 2", 0x9CF630},
	{"PrepreLibertadores Cup", 0x9CF634}, // Segunda Federación group
	{"PreLibertadores", 0x9CF638}, // Segunda Federación group
	{"Copa Libertadores de América", 0x9CF63C},
	{"Korean High School League", 0x9CF640}, // Campeonato de Portugal group
	{"Copa CONMEBOL", 0x9CF644},
	{"Recopa Sudamericana", 0x9CF648},
	{"AFC Champions League", 0x9CF64C},
	{"Asian Cup Winners' Cup", 0x9CF650},
	{"Argentine Primera División", 0x9CF654},
	{"Argentine Primera Nacional", 0x9CF658},
	{"Japanese J1 League", 0x9CF65C},
	{"Japanese Emperor's Cup", 0x9CF660},
	{"Japanese J.League Cup", 0x9CF664},
	{"Friendly", 0x9CF668},
	{"Japanese Super Cup", 0x9CF66C},
	{"Japanese Regional Leagues", 0x9CF670},
	{"Japanese University League", 0x9CF674},
	{"Japanese J3 League", 0x9CF678},
	{"Copa Argentina", 0x9CF67C},
	{"Argentine Interior Zone", 0x9CF680},
	{"Reserve", 0x9CF684},
	{"Argentine Third Division", 0x9CF688},
	{"CIS Champions Cup", 0x9CF68C},
	{"MLS All-Stars", 0x9CF690},
	{"German DFL-Supercup", 0x9CF694},
	{"Copa Sudamericana", 0x9CF698},
	{"English National League", 0x9CF69C},
	{"English FA Trophy", 0x9CF6A0},
	{"Conference League Cup", 0x9CF6A4},
	{"Trophée des Champions", 0x9CF6A8},
	{"Swedish Lower Division", 0x9CF6AC},
	{"Spanish Segunda Federación", 0x9CF6B0},
	{"Supertaça Cândido de Oliveira", 0x9CF6B4},
	{"A Premier Division", 0x9CF6B8},
	{"Norwegian Eliteserien", 0x9CF6BC},
	{"Norwegian 1. Divisjon", 0x9CF6C0},
	{"Norwegian 2. Divisjon Group 1", 0x9CF6C4},
	{"Norwegian 2. Divisjon Group 2", 0x9CF6C8},
	{"Norwegian 2. Divisjon Group 3", 0x9CF6CC},
	{"Norwegian 2. Divisjon Group 4", 0x9CF6D0},
	{"Norwegian 2. Divisjon Group 5", 0x9CF6D4},
	{"Norwegian 2. Divisjon Group 6", 0x9CF6D8},
	{"Norwegian 2. Divisjon Group 7", 0x9CF6DC},
	{"Norwegian 2. Divisjon Group 8", 0x9CF6E0},
	{"Intercontinental Cup", 0x9CF6E4},
	{"UEFA Champions League", 0x9CF6E8},
	{"Cup Winners' Cup", 0x9CF6EC},
	{"UEFA Europa League", 0x9CF6F0},
	{"UEFA Super Cup", 0x9CF6F4},
	{"UEFA Europa League Qualifying", 0x9CF6F8},
	{"Supercoupe de Belgique", 0x9CF6FC},
	{"Coupe de Belgique", 0x9CF700},
	{"Korean University League", 0x9CF704}, // Campeonato de Portugal group
	{"DBU Pokalen", 0x9CF708},
	{"Coupe de France", 0x9CF70C},
	{"Coupe de la Ligue", 0x9CF710},
	{"German DFB-Pokal", 0x9CF714},
	{"KNVB Beker", 0x9CF718},
	{"Coppa Italia", 0x9CF71C},
	{"Coppa Italia Serie C", 0x9CF720},
	{"Supercoppa Italiana", 0x9CF724},
	{"Lamar Hunt U.S. Open Cup", 0x9CF728},
	{"CONCACAF Champions League", 0x9CF72C},
	{"Korean President Cup", 0x9CF730}, // Campeonato de Portugal group
	{"Norwegian Cupen", 0x9CF734},
	{"Norwegian 3. Divisjon", 0x9CF738},
	{"Taça de Portugal", 0x9CF73C},
	{"Spanish Copa del Rey", 0x9CF740},
	{"Supercopa de España", 0x9CF744},
	{"Svenska Cupen", 0x9CF748},
	{"English FA Cup", 0x9CF74C},
	{"English League Cup", 0x9CF750},
	{"English FA Community Shield", 0x9CF754},
	{"English Football League Trophy", 0x9CF758},
	{"Scottish Cup", 0x9CF75C},
	{"Scottish League Cup", 0x9CF760},
	{"A Lower Division", 0x9CF764},
	{"Japanese J2 League", 0x9CF768},
	{"World Cup Oceania Qualifying Section", 0x9CF76C},
	{"World Cup CONCACAF Qualifying Section", 0x9CF770},
	{"World Cup Asian Qualifying Section", 0x9CF774},
	{"World Cup South American Qualifying Section", 0x9CF778},
	{"World Cup African Qualifying Section", 0x9CF77C},
	{"World Cup European Qualifying Section", 0x9CF780},
	{"UEFA European Championship Qualifying", 0x9CF784},
	{"Asian Cup Qualifying", 0x9CF788},
	//{ "Asian Games Football Tournament", 0x9CF78C },
	{ "CONCACAF Gold Cup", 0x9CF78C },
	{"AFC Asian Cup", 0x9CF790},
	{"\'B\' International", 0x9CF794},
	{"Under 21 International", 0x9CF798},
	{"FIFA World Cup", 0x9CF79C},
	{"Olympic Games", 0x9CF7A0},
	{"UEFA European Championship", 0x9CF7A4},
	{"Copa América", 0x9CF7A8},
	{"African Cup of Nations", 0x9CF7AC},
	{"Johan Cruijff Schaal", 0x9CF7B0},
	{"Scottish League Challenge Cup", 0x9CF7B4},
	{"Spanish Primera Federación", 0x9CF7B8},
	{"FIFA Club World Cup", 0x9CF7BC},
	{"Liga 3", 0x9CF7C0},
	{"Belgian National Division 1", 0x9CF7C4},
	{"Swedish Ettan", 0x9CF7C8},
	{"OFC Champions League", 0x9CF7CC},
	{"CAF Super Cup", 0x9CF7D0},
	{"Belgian Fourth Division  A", 0x9CF7D4},
	{"Belgian Fourth Division  B", 0x9CF7D8},
	{"Belgian Fourth Division  C", 0x9CF7DC},
	{"Belgian Fourth Division  D", 0x9CF7E0},
	{"Suomen Cup", 0x9CF7E4},
	{"Finnish Veikkausliiga", 0x9CF7E8},
	{"Finnish Ykkösliiga North", 0x9CF7EC},
	{"Finnish Ykkösliiga South", 0x9CF7F0},
	{"Finnish Kakkonen", 0x9CF7F4},
	{"Finnish Ykkösliiga", 0x9CF7F8},
	{"Finnish Ykkönen North", 0x9CF7FC},
	{"Finnish Ykkönen West", 0x9CF800},
	{"Finnish Ykkönen South", 0x9CF804},
	{"Finnish Ykkönen East", 0x9CF808},
	{"League of Ireland Premier Division", 0x9CF80C},
	{"League of Ireland First Division", 0x9CF810},
	{"Irish Group A", 0x9CF814},
	{"Irish Group B", 0x9CF818},
	{"Irish Group C", 0x9CF81C},
	{"Irish Group D", 0x9CF820},
	{"Irish Group E", 0x9CF824},
	{"Northern Irish Group A", 0x9CF82C},
	{"Northern Irish Group B", 0x9CF830},
	{"Northern Irish Group C", 0x9CF834},
	{"Northern Irish Group D", 0x9CF838},
	{"League of Ireland Cup", 0x9CF83C},
	{"FAI Cup", 0x9CF840},
	{"Korean All-Star Cup", 0x9CF844},
	{"Irish Connacht Senior League", 0x9CF848},
	{"Irish Ulster Senior League", 0x9CF84C},
	{"Irish Munster Senior League", 0x9CF850},
	{"Irish Leinster Senior League Premier", 0x9CF854},
	{"Polish Ekstraklasa", 0x9CF858},
	{"Polish I Liga", 0x9CF85C},
	{"Irish Super Cup", 0x9CF860},
	{"Puchar Polski", 0x9CF864},
	{"Polish II Liga", 0x9CF868},
	{"Greek Super League", 0x9CF86C},
	{"Greek Super League 2", 0x9CF870},
	{"Greek Gamma Ethniki", 0x9CF874},
	{"Kypello Elladas", 0x9CF878},
	{"Croatian HNL", 0x9CF87C},
	{"Croatian Prva NL", 0x9CF880},
	{"Croatian Druga NL Central", 0x9CF884},
	{"Croatian Druga NL North", 0x9CF888},
	{"Croatian Druga NL South", 0x9CF88C},
	{"Croatian Druga NL East", 0x9CF890},
	{"Croatian Druga NL West", 0x9CF894},
	{"Hrvatski Kup", 0x9CF898},
	{"Australian A-League", 0x9CF89C},
	{"OFC Nations Cup", 0x9CF8A0},
	{"Croatian Treca NL", 0x9CF8A4},
	{"Croatian Prva NL North", 0x9CF8A8},
	{"Croatian Prva NL South", 0x9CF8AC},
	{"NIFL Premiership", 0x9CF8B0},
	{"NIFL Championship", 0x9CF8B4},
	{"Northern Irish League Lower Division", 0x9CF8B8},
	{"NIFL Charity Shield", 0x9CF8BC},
	{"Irish Football Association Challenge Cup", 0x9CF8C0},
	{"Indian Guwahati Lower Division", 0x9CF8C4}, // new German Regionalliga Bayern
	{"NIFL Cup", 0x9CF8C8},
	{"Turkish Lower Division", 0x9CF8CC},
	{"Turkish 2. Division Group 1", 0x9CF8D0},
	//{"Turkish 2. Division Group 2", 0x9CF8D4},
	{"Turkish Süper Lig", 0x9CF8D8},
	{"TFF 1. Lig", 0x9CF8DC},
	{"TFF 2. Lig", 0x9CF8E0},
	{"TFF 2. Lig G1", 0x9CF8E4},
	{"TFF 2. Lig G2", 0x9CF8E8},
	{"TFF 2. Lig G3", 0x9CF8EC},
	{"TFF 2. Lig G4", 0x9CF8F0},
	{"TFF 2. Lig G5", 0x9CF8F4},
	{"Türkiye Kupasi", 0x9CF8F8},
	{"Turkish 2. Division", 0x9CF8FC},
	{"English Northern Premier League Premier Division", 0x9CF900},
	{"English Southern League Premier Division", 0x9CF904},
	{"Indian Chennai League", 0x9CF908}, // new Serie C
	{"Indian Haryana State Championship", 0x9CF90C}, // new Serie C/C
	{"Turkish 2. Divison Category B Group 1", 0x9CF910}, // new German Regionalliga
	{"Russian Second Division - West", 0x9CF914},
	{"Russian Second Division - Central", 0x9CF918},
	{"Russian Second Division - South", 0x9CF91C},
	{"Russian Second Division - Volga", 0x9CF920},
	{"Russian Second Division - Ural", 0x9CF924},
	{"Russian Second Division - East", 0x9CF928},
	{"Russian First Division", 0x9CF92C},
	{"Russian Premier Division", 0x9CF930},
	{"Russian Cup", 0x9CF934},
	{"Supercoppa Serie C", 0x9CF938},
	{"Greek Super Cup", 0x9CF93C},
	{"Croatian Super Cup", 0x9CF940},
	{"SuperPuchar Polski", 0x9CF944},
	{"Irish Presidents Cup", 0x9CF948},
	{"Welsh Cymru Premier", 0x9CF94C},
	{"Welsh League Cup", 0x9CF950},
	{"Welsh Cup", 0x9CF954},
	{"Welsh Premier Cup", 0x9CF958},
	{"Copa Interamericana", 0x9CF95C},
	{"Welsh Lower Division", 0x9CF960},
	{"FIFA Confederations Cup", 0x9CF964},
	{"Brazilian Bahia Lower Division", 0x9CF968},
	{"Brazilian Central Lower Division", 0x9CF96C},
	{"Brazilian Santa Catarina Lower Division", 0x9CF970},
	{"Brazilian Pernambuco Lower Division", 0x9CF974},
	{"Brazilian North Lower Division", 0x9CF978},
	{"Brazilian Rio de Janeiro Lower Division", 0x9CF97C},
	{"Brazilian Northeast Lower Division", 0x9CF980},
	{"Brazilian Goiás Lower Division", 0x9CF984},
	{"Brazilian Minas Gerais Lower Division", 0x9CF988},
	{"Brazilian Paraná Lower Division", 0x9CF98C},
	{"Brazilian Gaúcho Lower Division", 0x9CF990},
	{"Brazilian Campeonato Norte", 0x9CF994},
	{"Brazilian Campeonato Central", 0x9CF998},
	{"Brazilian São Paulo Lower Division", 0x9CF99C},
	{"Brazilian Central Regional Cup", 0x9CF9A0},
	{"Brazilian Campeonato Nordeste", 0x9CF9A4},
	{"Brazilian North Regional Cup", 0x9CF9A8},
	{"Brazilian Campeonato Série C", 0x9CF9AC},
	{"Brazilian Campeonato Catarinense", 0x9CF9B0},
	{"Brazilian Campeonato Goiano", 0x9CF9B4},
	{"Brazilian Copa dos Campeões", 0x9CF9B8},
	{"Brazilian Campeonato Pernambucano", 0x9CF9BC},
	{"Brazilian Campeonato Baiano", 0x9CF9C0},
	{"Brazilian Northeast Regional Cup", 0x9CF9C4},
	{"Brazilian Campeonato Gaúcho", 0x9CF9C8},
	{"Brazilian South-Minas Regional Cup", 0x9CF9CC},
	{"Brazilian Campeonato Paranaense", 0x9CF9D0},
	{"Brazilian Campeonato Mineiro", 0x9CF9D4},
	{"Brazilian Rio-São Paulo Tournement", 0x9CF9D8},
	{"Brazilian Campeonato Carioca", 0x9CF9DC},
	{"Brazilian Campeonato Série B", 0x9CF9E0},
	{"Brazilian Campeonato Paulista", 0x9CF9E4},
	{"Copa do Brasil", 0x9CF9E8},
	{"Brazilian Campeonato Série A", 0x9CF9EC},
	{"Irish Munster Senior Cup", 0x9CF9F0},
	{"Irish Leinster Senior Cup", 0x9CF9F4},
	{"Korean Super Cup", 0x9CF9F8},
	{"K League 2", 0x9CF9FC},
	{"K League 1", 0x9CFA00},
	{"Korean FA Cup", 0x9CFA04},
};

map<string, DWORD> award_dword_match = {
	{"Ballon d'Or", 0x9CFA20},
	{"Best FIFA Men's Player", 0x9CFA24},
	{"UEFA Men's Player of the Year", 0x9CFA28},
	{"Rey del Fútbol de América", 0x9CFA2C},
	{"African Footballer of the Year", 0x9CFA30},
	{"English PFA Players' Player of the Year", 0x9CFA34},
	{"English PFA Young Player of the Year", 0x9CFA38},
	{"English Premier League Team of the Year", 0x9CFA3C},
	{"EFL Championship Team of the Year", 0x9CFA40},
	{"EFL One Team of the Year", 0x9CFA44},
	{"EFL Two Team of the Year", 0x9CFA48},
	{"English Premier League Player of the Month", 0x9CFA4C},
	{"EFL Championship Player of the Month", 0x9CFA50},
	{"EFL One Player of the Month", 0x9CFA54},
	{"EFL Two Player of the Month", 0x9CFA58},
	{"English Premier League Young Player of the Month", 0x9CFA5C},
	{"EFL Championship Young Player of the Month", 0x9CFA60},
	{"EFL One Young Player of the Month", 0x9CFA64},
	{"EFL Two Young Player of the Month", 0x9CFA68},
	{"English Premier League Team of the Week", 0x9CFA6C},
	{"EFL Championship Team of the Week", 0x9CFA70},
	{"EFL One Team of the Week", 0x9CFA74},
	{"EFL Two Team of the Week", 0x9CFA78},
	{"PFA Scotland Players' Player of the Year", 0x9CFA7C},
	{"PFA Scotland Young Player of the Year", 0x9CFA80},
	{"SPFL Premiership Player of the Month", 0x9CFA84},
	{"SPFL Championship Player of the Month", 0x9CFA88},
	{"SPFL League One Player of the Month", 0x9CFA8C},
	{"SPFL League Two Player of the Month", 0x9CFA90},
	{"SPFL Premiership Team of the Week", 0x9CFA94},
	{"SPFL Championship Team of the Week", 0x9CFA98},
	{"SPFL League One Team of the Week", 0x9CFA9C},
	{"SPFL League Two Team of the Week", 0x9CFAA0},
	{"Belgian Golden Boot", 0x9CFAA4},
	{"Belgian First Division Player of the Year", 0x9CFAA8},
	{"Belgian First Division Goalkeeper of the Year", 0x9CFAAC},
	{"Belgian Second Division Player of the Year", 0x9CFAB0},
	{"Danish Player of the Year", 0x9CFAB4},
	{"Danish Premier Division Player of the Year", 0x9CFAB8},
	{"Danish Premier Division Young Player of the Year", 0x9CFABC},
	{"Danish First Division Player of the Year", 0x9CFAC0},
	{"Danish First Division Young Player of the Year", 0x9CFAC4},
	{"Danish Kvalifikationsrækken Player of the Year", 0x9CFAC8},
	{"Danish Second Division Player of the Year", 0x9CFACC},
	{"Danish Kvalifikationsrækken Young Player of Year", 0x9CFAD0},
	{"Danish Second Division Young Player of Year", 0x9CFAD4},
	{"French Player of the Year", 0x9CFAD8},
	{"French Foreign Player of the Year", 0x9CFADC},
	{"French Under-23 Player of the Year", 0x9CFAE0},
	{"French Most Popular Player of the Year", 0x9CFAE4},
	{"French Most Unpopular Player of the Year", 0x9CFAE8},
	{"French Ligue 1 Players' Player of the Year", 0x9CFAEC},
	{"French Ligue 1 Player of the Year", 0x9CFAF0},
	{"French Ligue 1 Goalkeeper of the Year", 0x9CFAF4},
	{"French Ligue 2 Players' Player of the Year", 0x9CFAF8},
	{"French Ligue 2 Player of the Year", 0x9CFAFC},
	{"French Ligue 2 Goalkeeper of the Year", 0x9CFB00},
	{"German Player of the Year", 0x9CFB04},
	{"German Bundesliga Player of the Month", 0x9CFB08},
	{"German 2. Bundesliga Player of the Month", 0x9CFB0C},
	{"Dutch Goalkeeper of the Year", 0x9CFB10},
	{"Dutch Young Player of the Year", 0x9CFB14},
	{"Dutch Premier Division Player of the Year", 0x9CFB18},
	{"Dutch Premier Division Top Goalscorer", 0x9CFB1C},
	{"Dutch Premier Division Golden Boot", 0x9CFB20},
	{"Dutch First Division Player of the Year", 0x9CFB24},
	{"Dutch First Division Top Goalscorer", 0x9CFB28},
	{"Dutch First Division Golden Boot", 0x9CFB2C},
	{"Italian Serie A Young Player of the Year", 0x9CFB30},
	{"Italian Serie A Player of the Year", 0x9CFB34},
	{"Italian Serie A Italian Player of the Year", 0x9CFB38},
	{"Italian Serie A Foreign Player of the Year", 0x9CFB3C},
	{"Italian Serie A Defender of the Year", 0x9CFB40},
	{"Italian Serie A Goalkeeper of the Year", 0x9CFB44},
	{"Italian Serie B Player of the Year", 0x9CFB48},
	{"Italian Serie C1/A Player of the Year", 0x9CFB4C},
	{"Italian Serie C1/B Player of the Year", 0x9CFB50},
	{"Norwegian Player of the Year", 0x9CFB54},
	{"Norwegian Goalkeeper of the Year", 0x9CFB58},
	{"Norwegian Defender of the Year", 0x9CFB5C},
	{"Norwegian Midfielder of the Year", 0x9CFB60},
	{"Norwegian Attacker of the Year", 0x9CFB64},
	{"Norwegian Premier Division Team of the Week", 0x9CFB68},
	{"Norwegian First Division Team of the Week", 0x9CFB6C},
	{"Portuguese Premier League Most Man of the Match", 0x9CFB70},
	{"Portuguese Premier League Top Goalscorer", 0x9CFB74},
	{"Portuguese Second League Player of the Year", 0x9CFB78},
	{"Spanish First Division Goalkeeper of the Year", 0x9CFB7C},
	{"Spanish Player of the Year", 0x9CFB80},
	{"Spanish First Division Top Goalscorer", 0x9CFB84},
	{"Swedish Player of the Year", 0x9CFB88},
	{"Swedish Premier Division Top Goalscorer", 0x9CFB8C},
	{"Swedish Fans Player of the Year", 0x9CFB90},
	{"MLS Goalkeeper of the Year", 0x9CFB94},
	{"MLS Defender of the Year", 0x9CFB98},
	{"MLS Rookie of the Year", 0x9CFB9C},
	{"MLS Scoring Champion", 0x9CFBA0},
	{"MLS All-Pro Team", 0x9CFBA4},
	{"MLS Player of the Month", 0x9CFBA8},
	{"SPFL Premiership Team of the Year", 0x9CFBAC},
	{"SPFL Championship Team of the Year", 0x9CFBB0},
	{"SPFL League One Team of the Year", 0x9CFBB4},
	{"SPFL League Two Team of the Year", 0x9CFBB8},
	{"Scottish Top Goalscorer", 0x9CFBBC},
	{"SPFL Premiership Young Player of the Month", 0x9CFBC0},
	{"SPFL Championship Young Player of the Month", 0x9CFBC4},
	{"SPFL League One Young Player of the Month", 0x9CFBC8},
	{"SPFL League Two Young Player of the Month", 0x9CFBCC},
	{"Belgian Manager of the Year", 0x9CFBD0},
	{"English Premier League Manager of the Year", 0x9CFBD4},
	{"English Premier League Manager of the Month", 0x9CFBD8},
	{"EFL Championship Manager of the Year", 0x9CFBDC},
	{"EFL Championship Manager of the Month", 0x9CFBE0},
	{"EFL One Manager of the Year", 0x9CFBE4},
	{"EFL One Manager of the Month", 0x9CFBE8},
	{"EFL Two Manager of the Year", 0x9CFBEC},
	{"EFL Two Manager of the Month", 0x9CFBF0},
	{"French Manager of the Year", 0x9CFBF4},
	{"German Bundesliga Manager of the Year", 0x9CFBF8},
	{"German 2. Bundesliga Manager of the Year", 0x9CFBFC},
	{"Dutch Manager of the Year", 0x9CFC00},
	{"Italian Serie A Panchina d'Oro", 0x9CFC04},
	{"Italian Serie B Panchina d'Argento", 0x9CFC08},
	{"Italian Serie C1/A Manager of the Year", 0x9CFC0C},
	{"Italian Serie C1/B Manager of the Year", 0x9CFC10},
	{"SPFL Premiership Manager of the Year", 0x9CFC14},
	{"SPFL Premiership Manager of the Month", 0x9CFC18},
	{"SPFL Championship Manager of the Year", 0x9CFC1C},
	{"SPFL Championship Manager of the Month", 0x9CFC20},
	{"SPFL League One Manager of the Year", 0x9CFC24},
	{"SPFL League One Manager of the Month", 0x9CFC28},
	{"SPFL League Two Manager of the Year", 0x9CFC2C},
	{"SPFL League Two Manager of the Month", 0x9CFC30},
	{"Spanish Manager of the Year", 0x9CFC34},
	{"Swedish Manager of the Year", 0x9CFC38},
	{"MLS Manager of the Year", 0x9CFC3C},
	{"Belgian Young Player of the Year", 0x9CFC40},
	{"Argentinian Premier Division Team of the Week", 0x9CFC44},
	{"Argentinian Second Division Team of the Week", 0x9CFC48},
	{"Japanese Player of the Year", 0x9CFC4C},
	{"Japanese Top Goalscorer", 0x9CFC50},
	{"Japanese Young Player of the Year", 0x9CFC54},
	{"Japanese Manager of the Year", 0x9CFC58},
	{"Japanese J-League 1 Team of the Year", 0x9CFC5C},
	{"World Cup Golden Boot", 0x9CFC60},
	{"World Cup Dream Team", 0x9CFC64},
	{"German Goalkeeper of the Year", 0x9CFC68},
	{"German Sweeper of the Year", 0x9CFC6C},
	{"German Defender of the Year", 0x9CFC70},
	{"German Midfielder of the Year", 0x9CFC74},
	{"German Striker of the Year", 0x9CFC78},
	{"German Bundesliga Top Goalscorer", 0x9CFC7C},
	{"English Footballer of the Year", 0x9CFC80},
	{"English National League Manager of the Month", 0x9CFC84},
	{"English National League Team of the Year", 0x9CFC88},
	{"English National League Manager of the Year", 0x9CFC8C},
	{"English National League Player of the Month", 0x9CFC90},
	{"English National League Team of the Week", 0x9CFC94},
	{"English National League Young Player of the Month", 0x9CFC98},
	{"Portuguese Premier League Team of the Year", 0x9CFC9C},
	{"Portuguese Second League Team of the Year", 0x9CFCA0},
	{"Portuguese Premier League Team of the Week", 0x9CFCA4},
	{"Portuguese Second League Team of the Week", 0x9CFCA8},
	{"Japanese J-League 1 Team of the Week", 0x9CFCAC},
	{"Japanese J-League 2 Team of the Week", 0x9CFCB0},
	{"Swedish Premier Division Team of the Week", 0x9CFCB4},
	{"Swedish First Division Team of the Week", 0x9CFCB8},
	{"Spanish First Division Team of the Week", 0x9CFCBC},
	{"Spanish Second Division Team of the Week", 0x9CFCC0},
	{"Italian Serie A Team of the Week", 0x9CFCC4},
	{"Italian Serie B Team of the Week", 0x9CFCC8},
	{"Italian Serie C1/A Team of the Week", 0x9CFCCC},
	{"Italian Serie C1/B Team of the Week", 0x9CFCD0},
	{"Dutch Premier Division Team of the Week", 0x9CFCD4},
	{"Dutch First Division Team of the Week", 0x9CFCD8},
	{"German Bundesliga Team of the Week", 0x9CFCDC},
	{"German 2. Bundesliga Team of the Week", 0x9CFCE0},
	{"French Ligue 1 Team of the Week", 0x9CFCE4},
	{"French Ligue 2 Team of the Week", 0x9CFCE8},
	{"Danish Premier Division Team of the Week", 0x9CFCEC},
	{"Danish First Division Team of the Week", 0x9CFCF0},
	{"Danish Second Division Team of the Week", 0x9CFCF4},
	{"Belgian First Division Team of the Week", 0x9CFCF8},
	{"Belgian Second Division Team of the Week", 0x9CFCFC},
	{"Portuguese Premier League Player of the Year", 0x9CFD00},
	{"Portuguese Second League Most Man of the Match", 0x9CFD04},
	{"Portuguese Second League Top Goalscorer", 0x9CFD08},
	{"German 2. Bundesliga Top Goalscorer", 0x9CFD0C},
	{"Swedish Goalkeeper of the Year", 0x9CFD10},
	{"Swedish Defender of the Year", 0x9CFD14},
	{"Swedish Forward of the Year", 0x9CFD18},
	{"Swedish Rookie of the Year", 0x9CFD1C},
	{"Swedish Midfielder of the Year", 0x9CFD20},
	{"Italian Serie C2/A Manager of the Year", 0x9CFD24},
	{"Italian Serie C2/A Player of the Year", 0x9CFD28},
	{"Italian Serie C2/A Team of the Week", 0x9CFD2C},
	{"Italian Serie C2/B Manager of the Year", 0x9CFD30},
	{"Italian Serie C2/B Player of the Year", 0x9CFD34},
	{"Japanese J-League 2 Team of the Year", 0x9CFD38},
	{"Spanish Second Division Goalkeeper of the Year", 0x9CFD3C},
	{"Spanish Second Division Top Goalscorer", 0x9CFD40},
	{"Italian Serie C2/B Team of the Week", 0x9CFD44},
	{"Italian Serie C2/C Manager of the Year", 0x9CFD48},
	{"Italian Serie C2/C Player of the Year", 0x9CFD4C},
	{"Italian Serie C2/C Team of the Week", 0x9CFD50},
	{"Belgian First Division Top Goalscorer", 0x9CFD54},
	{"Belgian First Division Revelation of the Year", 0x9CFD58},
	{"Belgian Second Division Top Goalscorer", 0x9CFD5C},
	{"Belgian Third Division Team of the Week", 0x9CFD60},
	{"Belgian Third Division Player of the Year", 0x9CFD64},
	{"Belgian Third Division Top Goalscorer", 0x9CFD68},
	{"European Goalkeeper of the Year", 0x9CFD6C},
	{"European Defender of the Year", 0x9CFD70},
	{"European Midfielder of the Year", 0x9CFD74},
	{"European Striker of the Year", 0x9CFD78},
	{"Italian Serie A Team of the Year", 0x9CFD7C},
	{"Italian Serie B Team of the Year", 0x9CFD80},
	{"Italian Serie C1/A Team of the Year", 0x9CFD84},
	{"Italian Serie C1/B Team of the Year", 0x9CFD88},
	{"Italian Serie C2/A Team of the Year", 0x9CFD8C},
	{"Italian Serie C2/B Team of the Year", 0x9CFD90},
	{"Italian Serie C2/C Team of the Year", 0x9CFD94},
	{"Italian Serie A Capocannoniere", 0x9CFD98},
	{"Italian Serie B Top Goalscorer", 0x9CFD9C},
	{"Italian Serie C1/A Top Goalscorer", 0x9CFDA0},
	{"Italian Serie C1/B Top Goalscorer", 0x9CFDA4},
	{"Italian Serie C2/A Top Goalscorer", 0x9CFDA8},
	{"Italian Serie C2/B Top Goalscorer", 0x9CFDAC},
	{"Italian Serie C2/C Top Goalscorer", 0x9CFDB0},
	{"Norwegian Premier Division Manager of the Month", 0x9CFDB4},
	{"Norwegian Premier Division Player of the Month", 0x9CFDB8},
	{"Norwegian First Division Manager of the Month", 0x9CFDBC},
	{"Norwegian First Division Player of the Month", 0x9CFDC0},
	{"Portuguese Premier League Manager of the Year", 0x9CFDC4},
	{"Portuguese Second League Manager of the Year", 0x9CFDC8},
	{"Finnish Player of the Year", 0x9CFDCC},
	{"Finnish Young Player of the Year", 0x9CFDD0},
	{"Finnish Goalkeeper of the Year", 0x9CFDD4},
	{"Finnish Manager of the Year", 0x9CFDD8},
	{"Finnish Veikkausliiga Top Goalscorer", 0x9CFDDC},
	{"Finnish Veikkausliiga Player of the Month", 0x9CFDE0},
	{"Finnish Veikkausliiga Team of the Year", 0x9CFDE4},
	{"Finnish Veikkausliiga Team of the Week", 0x9CFDE8},
	{"Finnish Ykkönen Top Goalscorer", 0x9CFDEC},
	{"Finnish Ykkönen Team of the Year", 0x9CFDF0},
	{"Finnish Ykkönen Team of the Week", 0x9CFDF4},
	{"Irish Player of the Year", 0x9CFDF8},
	{"Irish Young Player of the Year", 0x9CFDFC},
	{"Irish Premier Division Team of the Week", 0x9CFE00},
	{"Irish Premier Division Player of the Year", 0x9CFE04},
	{"Irish Premier Division Young Player of the Year", 0x9CFE08},
	{"Irish Premier Division Team of the Year", 0x9CFE0C},
	{"Irish First Division Team of the Week", 0x9CFE10},
	{"Irish First Division Player of the Year", 0x9CFE14},
	{"Irish First Division Young Player of the Year", 0x9CFE18},
	{"Irish First Division Team of the Year", 0x9CFE1C},
	{"Irish Premier Division Manager of the Year", 0x9CFE20},
	{"Irish Premier Division Manager of the Month", 0x9CFE24},
	{"Irish First Division Manager of the Year", 0x9CFE28},
	{"Irish First Division Manager of the Month", 0x9CFE2C},
	{"Polish First Division Team of the Week", 0x9CFE30},
	{"Polish First Division Player of the Year", 0x9CFE34},
	{"Polish First Division Young Player of the Year", 0x9CFE38},
	{"Polish First Division Manager of the Year", 0x9CFE3C},
	{"Polish First Division Manager of the Month", 0x9CFE40},
	{"Polish Second Division Team of the Week", 0x9CFE44},
	{"Polish Second Division Player of the Year", 0x9CFE48},
	{"Polish Second Division Young Player of the Year", 0x9CFE4C},
	{"Polish Second Division Manager of the Year", 0x9CFE50},
	{"Polish Second Division Manager of the Month", 0x9CFE54},
	{"Croatian First Division Player of the Year", 0x9CFE58},
	{"Croatian First Division Team of the Week", 0x9CFE5C},
	{"Croatian First Division Top Goalscorer", 0x9CFE60},
	{"Croatian Second Division A Player of the Year", 0x9CFE64},
	{"Croatian Second Division A Team of the Week", 0x9CFE68},
	{"Croatian Second Division A Top Goalscorer", 0x9CFE6C},
	{"Croatian Second Division B Player of the Year", 0x9CFE70},
	{"Croatian Second Division B Team of the Week", 0x9CFE74},
	{"Croatian Second Division B Top Goalscorer", 0x9CFE78},
	{"Australian NSL Team of the Week", 0x9CFE7C},
	{"Australian NSL Manager of the Month", 0x9CFE80},
	{"Australian NSL Player of the Month", 0x9CFE84},
	{"Australian NSL Young Player of the Month", 0x9CFE88},
	{"Australian NSL Player of the Year", 0x9CFE8C},
	{"Australian NSL Young Player of the Year", 0x9CFE90},
	{"Australian NSL Goalkeeper of the Year", 0x9CFE94},
	{"Australian NSL Leading Goalscorer", 0x9CFE98},
	{"Australian NSL Manager of the Year", 0x9CFE9C},
	{"Greek Player of the Year", 0x9CFEA0},
	{"Greek Foreign Player of the Year", 0x9CFEA4},
	{"Greek Superleague Team of the Week", 0x9CFEA8},
	{"Greek Superleague Player of the Year", 0x9CFEAC},
	{"Greek Superleague Manager of the Year", 0x9CFEB0},
	{"Greek Superleague Top Goalscorer", 0x9CFEB4},
	{"Greek Football League Team of the Week", 0x9CFEB8},
	{"Greek Football League Player of the Year", 0x9CFEBC},
	{"Greek Football League Manager of the Year", 0x9CFEC0},
	{"Greek Football League Top Goalscorer", 0x9CFEC4},
	{"Turkish Player of the Year", 0x9CFEC8},
	{"Turkish Manager of the Year", 0x9CFECC},
	{"Turkish Süper Lig Team of the Week", 0x9CFED0},
	{"Turkish Süper Lig Team of the Year", 0x9CFED4},
	{"TFF 1. Lig Team of the Week", 0x9CFED8},
	{"TFF 1. Lig Team of the Year", 0x9CFEDC},
	{"Russian Player of the Year", 0x9CFEE0},
	{"Russian Premier Division Team of the Week", 0x9CFEE4},
	{"Russian Premier Division Team of the Year", 0x9CFEE8},
	{"Russian Premier Division Player of the Month", 0x9CFEEC},
	{"Russian First Division Team of the Week", 0x9CFEF0},
	{"Russian First Division Team of the Year", 0x9CFEF4},
	{"Russian First Division Player of the Month", 0x9CFEF8},
	{"Irish Personality of the Year", 0x9CFEFC},
	{"N. Irish Player of the Year", 0x9CFF00},
	{"N. Irish Premier Division Team of the Week", 0x9CFF04},
	{"N. Irish Premier Division Player of the Year", 0x9CFF08},
	{"N. Irish Premier Division Young Player of the Year", 0x9CFF0C},
	{"N. Irish Premier Division Top Goalscorer", 0x9CFF10},
	{"N. Irish Premier Division Manager of the Year", 0x9CFF14},
	{"N. Irish Premier Division Manager of the Month", 0x9CFF18},
	{"N. Irish First Division Team of the Week", 0x9CFF1C},
	{"N. Irish First Division Player of the Year", 0x9CFF20},
	{"N. Irish First Division Young Player of the Year", 0x9CFF24},
	{"N. Irish First Division Top Goalscorer", 0x9CFF28},
	{"N. Irish First Division Manager of the Year", 0x9CFF2C},
	{"N. Irish First Division Manager of the Month", 0x9CFF30},
	{"Irish League Golden Boot", 0x9CFF34},
	{"Irish League Bronze Boot", 0x9CFF38},
	{"Belgian Second Division Revelation of the Year", 0x9CFF3C},
	{"Welsh Team of the Week", 0x9CFF40},
	{"Welsh Player of the Year", 0x9CFF44},
	{"Welsh Young Player of the Year", 0x9CFF48},
	{"Welsh Top Goalscorer", 0x9CFF4C},
	{"Welsh Manager of the Year", 0x9CFF50},
	{"Welsh Manager of the Month", 0x9CFF54},
	{"French Ligue 1 Team of the Year", 0x9CFF58},
	{"French Ligue 2 Team of the Year", 0x9CFF5C},
	{"French National Player of the Year", 0x9CFF60},
	{"French National Goalkeeper of the Year", 0x9CFF64},
	{"French National Team of the Week", 0x9CFF68},
	{"French National Team of the Year", 0x9CFF6C},
	{"Irish Player of the Month", 0x9CFF70},
	{"French National Players' Player of the Year", 0x9CFF74},
	{"Oceania Footballer of the Year", 0x9CFF78},
	{"Finnish Ykkönen Player of the Month", 0x9CFF7C},
	{"Finnish Veikkausliiga Manager of the Month", 0x9CFF80},
	{"Finnish Ykkönen Manager of the Month", 0x9CFF84},
	{"Brazilian 1st Division Player of the Year", 0x9CFF88},
	{"Brazilian 1st Division Team of the Week", 0x9CFF8C},
	{"Brazilian 1st Division Team of the Year", 0x9CFF90},
	{"Brazilian 1st Division Top Goalscorer", 0x9CFF94},
	{"Brazilian 1st Division Young Player of the Year", 0x9CFF98},
	{"Brazilian 2nd Division Player of the Year", 0x9CFF9C},
	{"Brazilian 2nd Division Team of the Week", 0x9CFFA0},
	{"Brazilian 2nd Division Team of the Year", 0x9CFFA4},
	{"Brazilian 2nd Division Top Goalscorer", 0x9CFFA8},
	{"Brazilian 2nd Division Young Player of the Year", 0x9CFFAC},
	{"Brazilian 3rd Division Player of the Year", 0x9CFFB0},
	{"Brazilian 3rd Division Team of the Week", 0x9CFFB4},
	{"Brazilian 3rd Division Team of the Year", 0x9CFFB8},
	{"Brazilian 3rd Division Top Goalscorer", 0x9CFFBC},
	{"Brazilian 3rd Division Young Player of the Year", 0x9CFFC0},
	{"Brazilian Bahia Best Goalkeeper", 0x9CFFC4},
	{"Brazilian Bahia Best Player", 0x9CFFC8},
	{"Brazilian Bahia Team of the Week", 0x9CFFCC},
	{"Brazilian Bahia Top Goalscorer", 0x9CFFD0},
	{"Brazilian Central Best Goalkeeper", 0x9CFFD4},
	{"Brazilian Central Best Player", 0x9CFFD8},
	{"Brazilian Central Team of the Week", 0x9CFFDC},
	{"Brazilian Central Top Goalscorer", 0x9CFFE0},
	{"Brazilian Gaúcho Best Goalkeeper", 0x9CFFE4},
	{"Brazilian Gaúcho Best Player", 0x9CFFE8},
	{"Brazilian Gaúcho Team of the Week", 0x9CFFEC},
	{"Brazilian Gaúcho Top Goalscorer", 0x9CFFF0},
	{"Brazilian Goiás Best Goalkeeper", 0x9CFFF4},
	{"Brazilian Goiás Best Player", 0x9CFFF8},
	{"Brazilian Goiás Team of the Week", 0x9CFFFC},
	{"Brazilian Goiás Top Goalscorer", 0x9D0000},
	{"Brazilian Minas Gerais Best Goalkeeper", 0x9D0004},
	{"Brazilian Minas Gerais Best Player", 0x9D0008},
	{"Brazilian Minas Gerais Team of the Week", 0x9D000C},
	{"Brazilian Minas Gerais Top Goalscorer", 0x9D0010},
	{"Brazilian North Best Goalkeeper", 0x9D0014},
	{"Brazilian North Best Player", 0x9D0018},
	{"Brazilian North Team of the Week", 0x9D001C},
	{"Brazilian North Top Goalscorer", 0x9D0020},
	{"Brazilian Northeast Best Goalkeeper", 0x9D0024},
	{"Brazilian Northeast Best Player", 0x9D0028},
	{"Brazilian Northeast Team of the Week", 0x9D002C},
	{"Brazilian Northeast Top Goalscorer", 0x9D0030},
	{"Brazilian Paraná Best Goalkeeper", 0x9D0034},
	{"Brazilian Paraná Best Player", 0x9D0038},
	{"Brazilian Paraná Team of the Week", 0x9D003C},
	{"Brazilian Paraná Top Goalscorer", 0x9D0040},
	{"Brazilian Pernambuco Best Goalkeeper", 0x9D0044},
	{"Brazilian Pernambuco Best Player", 0x9D0048},
	{"Brazilian Pernambuco Team of the Week", 0x9D004C},
	{"Brazilian Pernambuco Top Goalscorer", 0x9D0050},
	{"Brazilian Rio de Janeiro Best Goalkeeper", 0x9D0054},
	{"Brazilian Rio de Janeiro Best Player", 0x9D0058},
	{"Brazilian Rio de Janeiro Team of the Week", 0x9D005C},
	{"Brazilian Rio de Janeiro Top Goalscorer", 0x9D0060},
	{"Brazilian Santa Catarina Best Goalkeeper", 0x9D0064},
	{"Brazilian Santa Catarina Best Player", 0x9D0068},
	{"Brazilian Santa Catarina Team of the Week", 0x9D006C},
	{"Brazilian Santa Catarina Top Goalscorer", 0x9D0070},
	{"Brazilian São Paulo Best Goalkeeper", 0x9D0074},
	{"Brazilian São Paulo Best Player", 0x9D0078},
	{"Brazilian São Paulo Team of the Week", 0x9D007C},
	{"Brazilian São Paulo Top Goalscorer", 0x9D0080},
	{"South Korean Best 11 of the Year", 0x9D0084},
	{"South Korean Goalkeeper of the Month", 0x9D0088},
	{"South Korean Manager of the Year", 0x9D008C},
	{"South Korean Most Assisted Player of the Year", 0x9D0090},
	{"South Korean Player of the Month", 0x9D0094},
	{"South Korean Player of the Year", 0x9D0098},
	{"South Korean Top Goal Scorer of the Year", 0x9D009C},
	{"South Korean Young Player of the Year", 0x9D00A0},
};

int setup_9cf_leagues_sub(char* league_name, DWORD league_id, map<string, char*> new_names_map) {
	auto it = league_dword_match.find(string(league_name));
	if (it != league_dword_match.end()) {
		WriteDWORD(it->second, league_id);
	}
	else {
		for (const auto& [key, value] : new_names_map) {
			auto find_name_edited = league_dword_match.find(key);
			if (find_name_edited != league_dword_match.end() && _strcmpi(value, league_name) == 0) {
				WriteDWORD(find_name_edited->second, league_id);
			}
		}
	}
	return 1;
}

int setup_9cf_leagues(char* league_name, DWORD league_id) {
	// Change database names
	cm3_club_comps* comp_data = &(*club_comps)[league_id];
	string League_name_str = string(league_name);
	auto new_val_long = leagues_rename_long.find(League_name_str);
	if (new_val_long != leagues_rename_long.end()) {
		strcpy_s(comp_data->ClubCompName, new_val_long->second);
	}
	auto new_val_short = leagues_rename_short.find(League_name_str);
	if (new_val_short != leagues_rename_short.end()) {
		strcpy_s(comp_data->ClubCompNameShort, new_val_short->second);
	}
	auto new_val_tla = leagues_rename_tla.find(League_name_str);
	if (new_val_tla != leagues_rename_tla.end()) {
		strcpy_s(comp_data->ClubCompNameThreeLetter, new_val_tla->second);
	}
	// Fill out 9CF codes
	return setup_9cf_leagues_sub(league_name, league_id, leagues_rename_long);
}

int setup_9cf_clubs(char* club_name, DWORD club_id) {
	// Change database names - done later to avoid issues with Player_setup.cfg
	/*cm3_clubs* club_data = &(*clubs)[club_id];
	string club_name_str = string(club_name);
	auto new_val_long = clubs_rename_long.find(club_name_str);
	if (new_val_long != clubs_rename_long.end()) {
		strcpy_s(club_data->ClubName, new_val_long->Second);
	}
	auto new_val_short = clubs_rename_short.find(club_name_str);
	if (new_val_short != clubs_rename_short.end()) {
		strcpy_s(club_data->ClubNameShort, new_val_short->Second);
	}*/
	// Fill out 9CF codes
	auto it = club_dword_match.find(string(club_name));
	if (it != club_dword_match.end()) {
		WriteDWORD(it->second, club_id);
	}
	else {
		for (const auto& [key, value] : clubs_rename_long) {
			auto find_name_edited = club_dword_match.find(key);
			if (find_name_edited != club_dword_match.end() && _strcmpi(value, club_name) == 0) {
				WriteDWORD(find_name_edited->second, club_id);
			}
		}
	}
	return 1;
}

void inject_club_names_full()
{
	for (const auto& [key, value] : clubs_rename_short) {
		cm3_clubs* to_rename = find_club(key.c_str());
		if (to_rename) {
			strcpy_s((*to_rename).ClubNameShort, value);
		}
	}
	for (const auto& [key, value] : clubs_rename_long) {
		cm3_clubs* to_rename = find_club(key.c_str());
		if (to_rename) {
			strcpy_s((*to_rename).ClubName, value);
		}
	}
}

extern "C" _declspec(naked) int inject_club_names()
{
	_asm
	{
		pushad
	}
	inject_club_names_full();
	_asm
	{
		popad
		ret
	}
}

int setup_9cf_awards_sub(char* award_name, DWORD award_id, map<string, char*> new_names_map) {
	// Fill out 9CF codes
	auto it = award_dword_match.find(string(award_name));
	if (it != award_dword_match.end()) {
		WriteDWORD(it->second, award_id);
	}
	else {
		for (const auto& [key, value] : new_names_map) {
			auto find_name_edited = award_dword_match.find(key);
			if (find_name_edited != award_dword_match.end() && _strcmpi(value, award_name) == 0) {
				WriteDWORD(find_name_edited->second, award_id);
			}
		}
	}
	return 1;
}

int setup_9cf_awards(char* award_name, DWORD award_id) {
	// Change database names
	cm3_staff_comps* comp_data = &(*awards)[award_id];
	string award_name_str = string(award_name);
	auto new_val_long = awards_rename_long.find(award_name_str);
	if (new_val_long != awards_rename_long.end()) {
		strcpy_s(comp_data->StaffCompName, new_val_long->second);
	}
	auto new_val_short = awards_rename_short.find(award_name_str);
	if (new_val_short != awards_rename_short.end()) {
		strcpy_s(comp_data->StaffCompNameShort, new_val_short->second);
	}
	// Fill out 9CF codes
	return setup_9cf_awards_sub(award_name, award_id, awards_rename_long);
}

// a bit ugly and lengthy but works with no issues
BYTE* check_if_reserve_team_new(cm3_clubs* to_check, DWORD* is_main_club, DWORD a3) {
	if (!to_check) return NULL;
	if (a3 != 0 && to_check->ClubHasLinkedClub == 0) return NULL;
	if (!to_check->ClubNation) return NULL;
	// Main teams check
	if (is_main_club) *is_main_club = 1;
	char* db_club_name = get_db_club_name(to_check);
	if ((DWORD)to_check->ClubID == CLUB_1860_MUNICH_9CF()) return (BYTE*)get_club(CLUB_1860_MUNICH_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ALAVES_9CF()) return (BYTE*)get_club(CLUB_ALAVES_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ALBACETE_9CF()) return (BYTE*)get_club(CLUB_ALBACETE_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ALCORCON_9CF()) return (BYTE*)get_club(CLUB_ALCORCON_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ALMERIA_9CF()) return (BYTE*)get_club(CLUB_ALMERIA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ALVERCA_9CF()) return (BYTE*)get_club(CLUB_ALVERCA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ATHLETIC_BILBAO_9CF()) return (BYTE*)get_club(CLUB_ATHLETIC_BILBAO_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ATLETICO_MADRID_9CF()) return (BYTE*)get_club(CLUB_ATLETICO_MADRID_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_AUGSBURG_9CF()) return (BYTE*)get_club(CLUB_AUGSBURG_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BARCELONA_9CF()) return (BYTE*)get_club(CLUB_BARCELONA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BENFICA_9CF()) return (BYTE*)get_club(CLUB_BENFICA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BETIS_9CF()) return (BYTE*)get_club(CLUB_BETIS_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BIELEFELD_9CF()) return (BYTE*)get_club(CLUB_BIELEFELD_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BOCHUM_9CF()) return (BYTE*)get_club(CLUB_BOCHUM_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BRAGA_9CF()) return (BYTE*)get_club(CLUB_BRAGA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BURGOS_9CF()) return (BYTE*)get_club(CLUB_BURGOS_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CADIZ_9CF()) return (BYTE*)get_club(CLUB_CADIZ_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CARTAGENA_9CF()) return (BYTE*)get_club(CLUB_CARTAGENA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CASTELLON_9CF()) return (BYTE*)get_club(CLUB_CASTELLON_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CELTA_9CF()) return (BYTE*)get_club(CLUB_CELTA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CHAVES_9CF()) return (BYTE*)get_club(CLUB_CHAVES_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CORDOBA_9CF()) return (BYTE*)get_club(CLUB_CORDOBA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CULTURAL_9CF()) return (BYTE*)get_club(CLUB_CULTURAL_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_DEPORTIVO_9CF()) return (BYTE*)get_club(CLUB_DEPORTIVO_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_DORTMUND_9CF()) return (BYTE*)get_club(CLUB_DORTMUND_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_DUSSELDORF_9CF()) return (BYTE*)get_club(CLUB_DUSSELDORF_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_EIBAR_9CF()) return (BYTE*)get_club(CLUB_EIBAR_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ELCHE_9CF()) return (BYTE*)get_club(CLUB_ELCHE_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ESPANYOL_9CF()) return (BYTE*)get_club(CLUB_ESPANYOL_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_FC_BAYERN_9CF()) return (BYTE*)get_club(CLUB_FC_BAYERN_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_FRANKFURT_9CF()) return (BYTE*)get_club(CLUB_FRANKFURT_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_FREIBURG_9CF()) return (BYTE*)get_club(CLUB_FREIBURG_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_FURTH_9CF()) return (BYTE*)get_club(CLUB_FURTH_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_GETAFE_9CF()) return (BYTE*)get_club(CLUB_GETAFE_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_GRANADA_9CF()) return (BYTE*)get_club(CLUB_GRANADA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_HAMBURG_9CF()) return (BYTE*)get_club(CLUB_HAMBURG_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_HANNOVER_96_9CF()) return (BYTE*)get_club(CLUB_HANNOVER_96_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_HERTHA_BSC_9CF()) return (BYTE*)get_club(CLUB_HERTHA_BSC_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_HOFFENHEIM_9CF()) return (BYTE*)get_club(CLUB_HOFFENHEIM_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_HUESCA_9CF()) return (BYTE*)get_club(CLUB_HUESCA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_INGOLSTADT_9CF()) return (BYTE*)get_club(CLUB_INGOLSTADT_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_KAISERSLAUTERN_9CF()) return (BYTE*)get_club(CLUB_KAISERSLAUTERN_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_KARLSRUHE_9CF()) return (BYTE*)get_club(CLUB_KARLSRUHE_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_KIEL_9CF()) return (BYTE*)get_club(CLUB_KIEL_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_KOLN_9CF()) return (BYTE*)get_club(CLUB_KOLN_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_LAS_PALMAS_9CF()) return (BYTE*)get_club(CLUB_LAS_PALMAS_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_LEGANES_9CF()) return (BYTE*)get_club(CLUB_LEGANES_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_LEVANTE_9CF()) return (BYTE*)get_club(CLUB_LEVANTE_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_LOGRONES_9CF()) return (BYTE*)get_club(CLUB_LOGRONES_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_LUGO_9CF()) return (BYTE*)get_club(CLUB_LUGO_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_M_GLADBACH_9CF()) return (BYTE*)get_club(CLUB_M_GLADBACH_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_MAINZ_9CF()) return (BYTE*)get_club(CLUB_MAINZ_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_MALAGA_9CF()) return (BYTE*)get_club(CLUB_MALAGA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_MALLORCA_9CF()) return (BYTE*)get_club(CLUB_MALLORCA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_MARITIMO_9CF()) return (BYTE*)get_club(CLUB_MARITIMO_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_MURCIA_9CF()) return (BYTE*)get_club(CLUB_MURCIA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_NUMANCIA_9CF()) return (BYTE*)get_club(CLUB_NUMANCIA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_NURNBERG_9CF()) return (BYTE*)get_club(CLUB_NURNBERG_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_OSASUNA_9CF()) return (BYTE*)get_club(CLUB_OSASUNA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_OVIEDO_9CF()) return (BYTE*)get_club(CLUB_OVIEDO_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_PORTO_9CF()) return (BYTE*)get_club(CLUB_PORTO_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_RACING_SANTANDER_9CF()) return (BYTE*)get_club(CLUB_RACING_SANTANDER_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_RAYO_9CF()) return (BYTE*)get_club(CLUB_RAYO_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_REAL_MADRID_9CF()) return (BYTE*)get_club(CLUB_REAL_MADRID_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_REAL_SOCIEDAD_9CF()) return (BYTE*)get_club(CLUB_REAL_SOCIEDAD_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_RECREATIVO_9CF()) return (BYTE*)get_club(CLUB_RECREATIVO_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_REGENSBURG_9CF()) return (BYTE*)get_club(CLUB_REGENSBURG_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ROSTOCK_9CF()) return (BYTE*)get_club(CLUB_ROSTOCK_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_SCHALKE_04_9CF()) return (BYTE*)get_club(CLUB_SCHALKE_04_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_SEVILLA_9CF()) return (BYTE*)get_club(CLUB_SEVILLA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_SPORTING_CP_9CF()) return (BYTE*)get_club(CLUB_SPORTING_CP_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_SPORTING_GIJON_9CF()) return (BYTE*)get_club(CLUB_SPORTING_GIJON_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ST_PAULI_9CF()) return (BYTE*)get_club(CLUB_ST_PAULI_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_STUTTGART_9CF()) return (BYTE*)get_club(CLUB_STUTTGART_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_TENERIFE_9CF()) return (BYTE*)get_club(CLUB_TENERIFE_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_UNTERHACHING_9CF()) return (BYTE*)get_club(CLUB_UNTERHACHING_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_VALENCIA_9CF()) return (BYTE*)get_club(CLUB_VALENCIA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_VALLADOLID_9CF()) return (BYTE*)get_club(CLUB_VALLADOLID_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_VILLARREAL_9CF()) return (BYTE*)get_club(CLUB_VILLARREAL_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_VIT_GUIMARAES_9CF()) return (BYTE*)get_club(CLUB_VIT_GUIMARAES_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_WERDER_BREMEN_9CF()) return (BYTE*)get_club(CLUB_WERDER_BREMEN_II_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ZARAGOZA_9CF()) return (BYTE*)get_club(CLUB_ZARAGOZA_B_9CF());
	if ((DWORD)to_check->ClubID == CLUB_PADERBORN_9CF()) return (BYTE*)get_club(CLUB_PADERBORN_II_9CF());
	// non-hardcoded teams
	if (_strcmpi(db_club_name, "Aalesunds FK") == 0 && find_club("Aalesunds FK II")) return (BYTE*)find_club("Aalesunds FK II");
	if (_strcmpi(db_club_name, "Bærum SK") == 0 && find_club("Baerum SK 2")) return (BYTE*)find_club("Baerum SK 2");
	if (_strcmpi(db_club_name, "FK Bodø/Glimt") == 0 && find_club("FK Bodø/Glimt B")) return (BYTE*)find_club("FK Bodø/Glimt B");
	if (_strcmpi(db_club_name, "SK Brann") == 0 && find_club("SK Brann 2")) return (BYTE*)find_club("SK Brann 2");
	if (_strcmpi(db_club_name, "Bryne FK") == 0 && find_club("Bryne FK 2")) return (BYTE*)find_club("Bryne FK 2");
	if (_strcmpi(db_club_name, "Byåsen TF") == 0 && find_club("Byasen Trondheim II")) return (BYTE*)find_club("Byasen Trondheim II");
	if (_strcmpi(db_club_name, "Follo FK") == 0 && find_club("Follo FK 2")) return (BYTE*)find_club("Follo FK 2");
	if (_strcmpi(db_club_name, "Fredrikstad FK") == 0 && find_club("Fredrikstad FK 2")) return (BYTE*)find_club("Fredrikstad FK 2");
	if (_strcmpi(db_club_name, "FK Fyllingsdalen") == 0 && find_club("Fyllingsdalen FK 2")) return (BYTE*)find_club("Fyllingsdalen FK 2");
	if (_strcmpi(db_club_name, "SK Gjøvik-Lyn") == 0 && find_club("SK Gjøvik-Lyn 2")) return (BYTE*)find_club("SK Gjøvik-Lyn 2");
	if (_strcmpi(db_club_name, "Grorud IL") == 0 && find_club("Grorud IL 2")) return (BYTE*)find_club("Grorud IL 2");
	if (_strcmpi(db_club_name, "Hamarkameratene") == 0 && find_club("Hamarkameratene 2")) return (BYTE*)find_club("Hamarkameratene 2");
	if (_strcmpi(db_club_name, "FK Haugesund") == 0 && find_club("FK Haugesund 2")) return (BYTE*)find_club("FK Haugesund 2");
	if (_strcmpi(db_club_name, "IL Hødd") == 0 && find_club("IL Hødd 2")) return (BYTE*)find_club("IL Hødd 2");
	if (_strcmpi(db_club_name, "Hønefoss BK") == 0 && find_club("Hønefoss BK 2")) return (BYTE*)find_club("Hønefoss BK 2");
	if (_strcmpi(db_club_name, "Kjelsås IL") == 0 && find_club("Kjelsas IL 2")) return (BYTE*)find_club("Kjelsas IL 2");
	if (_strcmpi(db_club_name, "Kongsvinger IL") == 0 && find_club("Kongsvinger IL II")) return (BYTE*)find_club("Kongsvinger IL II");
	if (_strcmpi(db_club_name, "Kristiansund BK") == 0 && find_club("Kristiansund BK 2")) return (BYTE*)find_club("Kristiansund BK 2");
	if (_strcmpi(db_club_name, "Lillestrøm SK") == 0 && find_club("Lilleström SK 2")) return (BYTE*)find_club("Lilleström SK 2");
	if (_strcmpi(db_club_name, "Mjøndalen IF") == 0 && find_club("Mjøndalen IF 2")) return (BYTE*)find_club("Mjøndalen IF 2");
	if (_strcmpi(db_club_name, "Molde FK") == 0 && find_club("Molde FK II")) return (BYTE*)find_club("Molde FK II");
	if (_strcmpi(db_club_name, "Nardo FK") == 0 && find_club("Nardo FK 2")) return (BYTE*)find_club("Nardo FK 2");
	if (_strcmpi(db_club_name, "Odds BK") == 0 && find_club("Odds BK II")) return (BYTE*)find_club("Odds BK II");
	if (_strcmpi(db_club_name, "Pors Fotball") == 0 && find_club("Pors Fotball II")) return (BYTE*)find_club("Pors Fotball II");
	if (_strcmpi(db_club_name, "Ranheim IL") == 0 && find_club("Ranheim 2")) return (BYTE*)find_club("Ranheim 2");
	if (_strcmpi(db_club_name, "Raufoss IL") == 0 && find_club("Raufoss IL 2")) return (BYTE*)find_club("Raufoss IL 2");
	if (_strcmpi(db_club_name, "Rosenborg BK") == 0 && find_club("Rosenborg BK II")) return (BYTE*)find_club("Rosenborg BK II");
	if (_strcmpi(db_club_name, "Sandefjord Fotball") == 0 && find_club("Sandefjord Fotball 2")) return (BYTE*)find_club("Sandefjord Fotball 2");
	if (_strcmpi(db_club_name, "Sandnes Ulf") == 0 && find_club("Sandnes Ulf 2")) return (BYTE*)find_club("Sandnes Ulf 2");
	if (_strcmpi(db_club_name, "Sarpsborg 08 FF") == 0 && find_club("Sarpsborg 08 2")) return (BYTE*)find_club("Sarpsborg 08 2");
	if (_strcmpi(db_club_name, "Skeid Oslo") == 0 && find_club("Skeid Oslo II")) return (BYTE*)find_club("Skeid Oslo II");
	if (_strcmpi(db_club_name, "Sogndal IL") == 0 && find_club("Sogndal IL II")) return (BYTE*)find_club("Sogndal IL II");
	if (_strcmpi(db_club_name, "Stabæk Fotball") == 0 && find_club("Stabaek IF II")) return (BYTE*)find_club("Stabaek IF II");
	if (_strcmpi(db_club_name, "IK Start") == 0 && find_club("IK Start 2")) return (BYTE*)find_club("IK Start 2");
	if (_strcmpi(db_club_name, "Strømmen IF") == 0 && find_club("Strømmen IL 2")) return (BYTE*)find_club("Strømmen IL 2");
	if (_strcmpi(db_club_name, "Strømsgodset IF") == 0 && find_club("Strømsgodset IF II")) return (BYTE*)find_club("Strømsgodset IF II");
	if (_strcmpi(db_club_name, "Tromsø IL") == 0 && find_club("Tromsø IL II")) return (BYTE*)find_club("Tromsø IL II");
	if (_strcmpi(db_club_name, "SK Træff") == 0 && find_club("SK Træff 2")) return (BYTE*)find_club("SK Træff 2");
	if (_strcmpi(db_club_name, "Ullensaker/Kisa IL") == 0 && find_club("Ullensaker/Kisa IL 2")) return (BYTE*)find_club("Ullensaker/Kisa IL 2");
	if (_strcmpi(db_club_name, "SK Vard Haugesund") == 0 && find_club("SK Vard Haugesund 2")) return (BYTE*)find_club("SK Vard Haugesund 2");
	if (_strcmpi(db_club_name, "Viking FK") == 0 && find_club("Viking FK II")) return (BYTE*)find_club("Viking FK II");
	if (_strcmpi(db_club_name, "Vålerenga Fotball Elite") == 0 && find_club("Vålerenga Fotball II")) return (BYTE*)find_club("Vålerenga Fotball II");
	if (_strcmpi(db_club_name, "HJK Helsinki") == 0 && find_club("HJK Klubi 04 Helsinki")) return (BYTE*)find_club("HJK Klubi 04 Helsinki");
	if (_strcmpi(db_club_name, "FC Espoo") == 0 && find_club("FC Espoo II")) return (BYTE*)find_club("FC Espoo II");
	if (_strcmpi(db_club_name, "Helsinki IFK") == 0 && find_club("Helsinki IFK II")) return (BYTE*)find_club("Helsinki IFK II");
	if (_strcmpi(db_club_name, "FC Honka") == 0 && find_club("FC Honka II")) return (BYTE*)find_club("FC Honka II");
	if (_strcmpi(db_club_name, "Ilves Tampere") == 0 && find_club("Ilves Tampere II")) return (BYTE*)find_club("Ilves Tampere II");
	if (_strcmpi(db_club_name, "Kuopion Palloseura") == 0 && find_club("Kuopion Palloseura II")) return (BYTE*)find_club("Kuopion Palloseura II");
	if (_strcmpi(db_club_name, "Rovaniemen Palloseura") == 0 && find_club("Rovaniemen Palloseura II")) return (BYTE*)find_club("Rovaniemen Palloseura II");
	if (_strcmpi(db_club_name, "Vaasan Palloseura") == 0 && find_club("Vaasan Palloseura II")) return (BYTE*)find_club("Vaasan Palloseura II");
	if (_strcmpi(db_club_name, "FC Energie Cottbus") == 0 && find_club("FC Energie Cottbus II")) return (BYTE*)find_club("FC Energie Cottbus II");
	if (_strcmpi(db_club_name, "MSV Duisburg") == 0 && find_club("MSV Duisburg Amateure")) return (BYTE*)find_club("MSV Duisburg Amateure");
	if (_strcmpi(db_club_name, "Bayer 04 Leverkusen") == 0 && find_club("Bayer Leverkusen (A)")) return (BYTE*)find_club("Bayer Leverkusen (A)");
	if (_strcmpi(db_club_name, "1.FC Saarbrücken") == 0 && find_club("1.FC Saarbrücken II")) return (BYTE*)find_club("1.FC Saarbrücken II");
	if (_strcmpi(db_club_name, "Stuttgarter Kickers") == 0 && find_club("Stuttgarter Kickers II")) return (BYTE*)find_club("Stuttgarter Kickers II");
	if (_strcmpi(db_club_name, "VfL Wolfsburg") == 0 && find_club("VfL Wolfsburg Amateure")) return (BYTE*)find_club("VfL Wolfsburg Amateure");
	if (_strcmpi(db_club_name, "Chrobry Glogow") == 0 && find_club("Chrobry Glogow II")) return (BYTE*)find_club("Chrobry Glogow II");
	if (_strcmpi(db_club_name, "Cracovia") == 0 && find_club("Cracovia II")) return (BYTE*)find_club("Cracovia II");
	if (_strcmpi(db_club_name, "Górnik Zabrze") == 0 && find_club("Gornik Zabrze II")) return (BYTE*)find_club("Gornik Zabrze II");
	if (_strcmpi(db_club_name, "Jagiellonia Bialystok") == 0 && find_club("Jagiellonia Bialystok II")) return (BYTE*)find_club("Jagiellonia Bialystok II");
	if (_strcmpi(db_club_name, "Korona Kielce") == 0 && find_club("Korona Kielce II")) return (BYTE*)find_club("Korona Kielce II");
	if (_strcmpi(db_club_name, "Lech Poznan") == 0 && find_club("Lech Poznan II")) return (BYTE*)find_club("Lech Poznan II");
	if (_strcmpi(db_club_name, "Legia Warszawa") == 0 && find_club("Legia Warsaw II")) return (BYTE*)find_club("Legia Warsaw II");
	if (_strcmpi(db_club_name, "LKS Lodz") == 0 && find_club("LKS Lodz II")) return (BYTE*)find_club("LKS Lodz II");
	if (_strcmpi(db_club_name, "Miedz Legnica") == 0 && find_club("Miedz Legnica II")) return (BYTE*)find_club("Miedz Legnica II");
	if (_strcmpi(db_club_name, "Piast Gliwice") == 0 && find_club("Piast Gliwice II")) return (BYTE*)find_club("Piast Gliwice II");
	if (_strcmpi(db_club_name, "Pogon Szczecin") == 0 && find_club("Pogon Szczecin II")) return (BYTE*)find_club("Pogon Szczecin II");
	if (_strcmpi(db_club_name, "Raków Czestochowa") == 0 && find_club("Rakow Czestochowa II")) return (BYTE*)find_club("Rakow Czestochowa II");
	if (_strcmpi(db_club_name, "Slask Wroclaw") == 0 && find_club("Slask Wroclaw II")) return (BYTE*)find_club("Slask Wroclaw II");
	if (_strcmpi(db_club_name, "Widzew Lodz") == 0 && find_club("Widzew Lodz II")) return (BYTE*)find_club("Widzew Lodz II");
	if (_strcmpi(db_club_name, "Wisla Kraków") == 0 && find_club("Wisla Krakow II")) return (BYTE*)find_club("Wisla Krakow II");
	if (_strcmpi(db_club_name, "Wisla Plock") == 0 && find_club("Wisla Plock II")) return (BYTE*)find_club("Wisla Plock II");
	if (_strcmpi(db_club_name, "Zaglebie Lubin") == 0 && find_club("Zaglebie Lubin II")) return (BYTE*)find_club("Zaglebie Lubin II");
	if (_strcmpi(db_club_name, "Glasgow Celtic") == 0 && find_club("Glasgow Celtic B")) return (BYTE*)find_club("Glasgow Celtic B");
	if (_strcmpi(db_club_name, "Heart of Midlothian FC") == 0 && find_club("Heart of Midlothian FC B")) return (BYTE*)find_club("Heart of Midlothian FC B");
	if (_strcmpi(db_club_name, "Girona FC") == 0 && find_club("Girona FC B")) return (BYTE*)find_club("Girona FC B");
	if (_strcmpi(db_club_name, "Asteras Aktor") == 0 && find_club("Asteras Aktor B")) return (BYTE*)find_club("Asteras Aktor B");
	if (_strcmpi(db_club_name, "AEK Athens") == 0 && find_club("AEK Athens B")) return (BYTE*)find_club("AEK Athens B");
	if (_strcmpi(db_club_name, "Olympiacos Piraeus") == 0 && find_club("Olympiacos Piraeus B")) return (BYTE*)find_club("Olympiacos Piraeus B");
	if (_strcmpi(db_club_name, "PAOK Thessaloniki") == 0 && find_club("PAOK Thessaloniki B")) return (BYTE*)find_club("PAOK Thessaloniki B");

	// Reserve teams check
	if (is_main_club) *is_main_club = 0;
	if ((DWORD)to_check->ClubID == CLUB_1860_MUNICH_II_9CF()) return (BYTE*)get_club(CLUB_1860_MUNICH_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ALAVES_B_9CF()) return (BYTE*)get_club(CLUB_ALAVES_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ALBACETE_B_9CF()) return (BYTE*)get_club(CLUB_ALBACETE_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ALCORCON_B_9CF()) return (BYTE*)get_club(CLUB_ALCORCON_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ALMERIA_B_9CF()) return (BYTE*)get_club(CLUB_ALMERIA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ALVERCA_B_9CF()) return (BYTE*)get_club(CLUB_ALVERCA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ATHLETIC_BILBAO_B_9CF()) return (BYTE*)get_club(CLUB_ATHLETIC_BILBAO_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ATLETICO_MADRID_B_9CF()) return (BYTE*)get_club(CLUB_ATLETICO_MADRID_9CF());
	if ((DWORD)to_check->ClubID == CLUB_AUGSBURG_II_9CF()) return (BYTE*)get_club(CLUB_AUGSBURG_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BARCELONA_B_9CF()) return (BYTE*)get_club(CLUB_BARCELONA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BENFICA_B_9CF()) return (BYTE*)get_club(CLUB_BENFICA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BETIS_B_9CF()) return (BYTE*)get_club(CLUB_BETIS_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BIELEFELD_II_9CF()) return (BYTE*)get_club(CLUB_BIELEFELD_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BOCHUM_II_9CF()) return (BYTE*)get_club(CLUB_BOCHUM_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BRAGA_B_9CF()) return (BYTE*)get_club(CLUB_BRAGA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_BURGOS_B_9CF()) return (BYTE*)get_club(CLUB_BURGOS_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CADIZ_B_9CF()) return (BYTE*)get_club(CLUB_CADIZ_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CARTAGENA_B_9CF()) return (BYTE*)get_club(CLUB_CARTAGENA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CASTELLON_B_9CF()) return (BYTE*)get_club(CLUB_CASTELLON_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CELTA_B_9CF()) return (BYTE*)get_club(CLUB_CELTA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CHAVES_B_9CF()) return (BYTE*)get_club(CLUB_CHAVES_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CORDOBA_B_9CF()) return (BYTE*)get_club(CLUB_CORDOBA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_CULTURAL_B_9CF()) return (BYTE*)get_club(CLUB_CULTURAL_9CF());
	if ((DWORD)to_check->ClubID == CLUB_DEPORTIVO_B_9CF()) return (BYTE*)get_club(CLUB_DEPORTIVO_9CF());
	if ((DWORD)to_check->ClubID == CLUB_DORTMUND_II_9CF()) return (BYTE*)get_club(CLUB_DORTMUND_9CF());
	if ((DWORD)to_check->ClubID == CLUB_DUSSELDORF_II_9CF()) return (BYTE*)get_club(CLUB_DUSSELDORF_9CF());
	if ((DWORD)to_check->ClubID == CLUB_EIBAR_B_9CF()) return (BYTE*)get_club(CLUB_EIBAR_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ELCHE_B_9CF()) return (BYTE*)get_club(CLUB_ELCHE_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ESPANYOL_B_9CF()) return (BYTE*)get_club(CLUB_ESPANYOL_9CF());
	if ((DWORD)to_check->ClubID == CLUB_FC_BAYERN_II_9CF()) return (BYTE*)get_club(CLUB_FC_BAYERN_9CF());
	if ((DWORD)to_check->ClubID == CLUB_FRANKFURT_II_9CF()) return (BYTE*)get_club(CLUB_FRANKFURT_9CF());
	if ((DWORD)to_check->ClubID == CLUB_FREIBURG_II_9CF()) return (BYTE*)get_club(CLUB_FREIBURG_9CF());
	if ((DWORD)to_check->ClubID == CLUB_FURTH_II_9CF()) return (BYTE*)get_club(CLUB_FURTH_9CF());
	if ((DWORD)to_check->ClubID == CLUB_GETAFE_B_9CF()) return (BYTE*)get_club(CLUB_GETAFE_9CF());
	if ((DWORD)to_check->ClubID == CLUB_GRANADA_B_9CF()) return (BYTE*)get_club(CLUB_GRANADA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_HAMBURG_II_9CF()) return (BYTE*)get_club(CLUB_HAMBURG_9CF());
	if ((DWORD)to_check->ClubID == CLUB_HANNOVER_96_II_9CF()) return (BYTE*)get_club(CLUB_HANNOVER_96_9CF());
	if ((DWORD)to_check->ClubID == CLUB_HERTHA_BSC_II_9CF()) return (BYTE*)get_club(CLUB_HERTHA_BSC_9CF());
	if ((DWORD)to_check->ClubID == CLUB_HOFFENHEIM_II_9CF()) return (BYTE*)get_club(CLUB_HOFFENHEIM_9CF());
	if ((DWORD)to_check->ClubID == CLUB_HUESCA_B_9CF()) return (BYTE*)get_club(CLUB_HUESCA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_INGOLSTADT_II_9CF()) return (BYTE*)get_club(CLUB_INGOLSTADT_9CF());
	if ((DWORD)to_check->ClubID == CLUB_KAISERSLAUTERN_II_9CF()) return (BYTE*)get_club(CLUB_KAISERSLAUTERN_9CF());
	if ((DWORD)to_check->ClubID == CLUB_KARLSRUHE_II_9CF()) return (BYTE*)get_club(CLUB_KARLSRUHE_9CF());
	if ((DWORD)to_check->ClubID == CLUB_KIEL_II_9CF()) return (BYTE*)get_club(CLUB_KIEL_9CF());
	if ((DWORD)to_check->ClubID == CLUB_KOLN_II_9CF()) return (BYTE*)get_club(CLUB_KOLN_9CF());
	if ((DWORD)to_check->ClubID == CLUB_LAS_PALMAS_B_9CF()) return (BYTE*)get_club(CLUB_LAS_PALMAS_9CF());
	if ((DWORD)to_check->ClubID == CLUB_LEGANES_B_9CF()) return (BYTE*)get_club(CLUB_LEGANES_9CF());
	if ((DWORD)to_check->ClubID == CLUB_LEVANTE_B_9CF()) return (BYTE*)get_club(CLUB_LEVANTE_9CF());
	if ((DWORD)to_check->ClubID == CLUB_LOGRONES_B_9CF()) return (BYTE*)get_club(CLUB_LOGRONES_9CF());
	if ((DWORD)to_check->ClubID == CLUB_LUGO_B_9CF()) return (BYTE*)get_club(CLUB_LUGO_9CF());
	if ((DWORD)to_check->ClubID == CLUB_M_GLADBACH_II_9CF()) return (BYTE*)get_club(CLUB_M_GLADBACH_9CF());
	if ((DWORD)to_check->ClubID == CLUB_MAINZ_II_9CF()) return (BYTE*)get_club(CLUB_MAINZ_9CF());
	if ((DWORD)to_check->ClubID == CLUB_MALAGA_B_9CF()) return (BYTE*)get_club(CLUB_MALAGA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_MALLORCA_B_9CF()) return (BYTE*)get_club(CLUB_MALLORCA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_MARITIMO_B_9CF()) return (BYTE*)get_club(CLUB_MARITIMO_9CF());
	if ((DWORD)to_check->ClubID == CLUB_MURCIA_B_9CF()) return (BYTE*)get_club(CLUB_MURCIA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_NUMANCIA_B_9CF()) return (BYTE*)get_club(CLUB_NUMANCIA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_NURNBERG_II_9CF()) return (BYTE*)get_club(CLUB_NURNBERG_9CF());
	if ((DWORD)to_check->ClubID == CLUB_OSASUNA_B_9CF()) return (BYTE*)get_club(CLUB_OSASUNA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_OVIEDO_B_9CF()) return (BYTE*)get_club(CLUB_OVIEDO_9CF());
	if ((DWORD)to_check->ClubID == CLUB_PORTO_B_9CF()) return (BYTE*)get_club(CLUB_PORTO_9CF());
	if ((DWORD)to_check->ClubID == CLUB_RACING_SANTANDER_B_9CF()) return (BYTE*)get_club(CLUB_RACING_SANTANDER_9CF());
	if ((DWORD)to_check->ClubID == CLUB_RAYO_B_9CF()) return (BYTE*)get_club(CLUB_RAYO_9CF());
	if ((DWORD)to_check->ClubID == CLUB_REAL_MADRID_B_9CF()) return (BYTE*)get_club(CLUB_REAL_MADRID_9CF());
	if ((DWORD)to_check->ClubID == CLUB_REAL_SOCIEDAD_B_9CF()) return (BYTE*)get_club(CLUB_REAL_SOCIEDAD_9CF());
	if ((DWORD)to_check->ClubID == CLUB_RECREATIVO_B_9CF()) return (BYTE*)get_club(CLUB_RECREATIVO_9CF());
	if ((DWORD)to_check->ClubID == CLUB_REGENSBURG_II_9CF()) return (BYTE*)get_club(CLUB_REGENSBURG_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ROSTOCK_II_9CF()) return (BYTE*)get_club(CLUB_ROSTOCK_9CF());
	if ((DWORD)to_check->ClubID == CLUB_SCHALKE_04_II_9CF()) return (BYTE*)get_club(CLUB_SCHALKE_04_9CF());
	if ((DWORD)to_check->ClubID == CLUB_SEVILLA_B_9CF()) return (BYTE*)get_club(CLUB_SEVILLA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_SPORTING_CP_B_9CF()) return (BYTE*)get_club(CLUB_SPORTING_CP_9CF());
	if ((DWORD)to_check->ClubID == CLUB_SPORTING_GIJON_B_9CF()) return (BYTE*)get_club(CLUB_SPORTING_GIJON_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ST_PAULI_II_9CF()) return (BYTE*)get_club(CLUB_ST_PAULI_9CF());
	if ((DWORD)to_check->ClubID == CLUB_STUTTGART_II_9CF()) return (BYTE*)get_club(CLUB_STUTTGART_9CF());
	if ((DWORD)to_check->ClubID == CLUB_TENERIFE_B_9CF()) return (BYTE*)get_club(CLUB_TENERIFE_9CF());
	if ((DWORD)to_check->ClubID == CLUB_UNTERHACHING_II_9CF()) return (BYTE*)get_club(CLUB_UNTERHACHING_9CF());
	if ((DWORD)to_check->ClubID == CLUB_VALENCIA_B_9CF()) return (BYTE*)get_club(CLUB_VALENCIA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_VALLADOLID_B_9CF()) return (BYTE*)get_club(CLUB_VALLADOLID_9CF());
	if ((DWORD)to_check->ClubID == CLUB_VILLARREAL_B_9CF()) return (BYTE*)get_club(CLUB_VILLARREAL_9CF());
	if ((DWORD)to_check->ClubID == CLUB_VIT_GUIMARAES_B_9CF()) return (BYTE*)get_club(CLUB_VIT_GUIMARAES_9CF());
	if ((DWORD)to_check->ClubID == CLUB_WERDER_BREMEN_II_9CF()) return (BYTE*)get_club(CLUB_WERDER_BREMEN_9CF());
	if ((DWORD)to_check->ClubID == CLUB_ZARAGOZA_B_9CF()) return (BYTE*)get_club(CLUB_ZARAGOZA_9CF());
	if ((DWORD)to_check->ClubID == CLUB_PADERBORN_II_9CF()) return (BYTE*)get_club(CLUB_PADERBORN_9CF());
	// non-hardcoded teams
	if (_strcmpi(db_club_name, "Aalesunds FK II") == 0 && find_club("Aalesunds FK")) return (BYTE*)find_club("Aalesunds FK");
	if (_strcmpi(db_club_name, "Baerum SK 2") == 0 && find_club("Bærum SK")) return (BYTE*)find_club("Bærum SK");
	if (_strcmpi(db_club_name, "FK Bodø/Glimt B") == 0 && find_club("FK Bodø/Glimt")) return (BYTE*)find_club("FK Bodø/Glimt");
	if (_strcmpi(db_club_name, "SK Brann 2") == 0 && find_club("SK Brann")) return (BYTE*)find_club("SK Brann");
	if (_strcmpi(db_club_name, "Bryne FK 2") == 0 && find_club("Bryne FK")) return (BYTE*)find_club("Bryne FK");
	if (_strcmpi(db_club_name, "Byasen Trondheim II") == 0 && find_club("Byåsen TF")) return (BYTE*)find_club("Byåsen TF");
	if (_strcmpi(db_club_name, "Follo FK 2") == 0 && find_club("Follo FK")) return (BYTE*)find_club("Follo FK");
	if (_strcmpi(db_club_name, "Fredrikstad FK 2") == 0 && find_club("Fredrikstad FK")) return (BYTE*)find_club("Fredrikstad FK");
	if (_strcmpi(db_club_name, "Fyllingsdalen FK 2") == 0 && find_club("FK Fyllingsdalen")) return (BYTE*)find_club("FK Fyllingsdalen");
	if (_strcmpi(db_club_name, "SK Gjøvik-Lyn 2") == 0 && find_club("SK Gjøvik-Lyn")) return (BYTE*)find_club("SK Gjøvik-Lyn");
	if (_strcmpi(db_club_name, "Grorud IL 2") == 0 && find_club("Grorud IL")) return (BYTE*)find_club("Grorud IL");
	if (_strcmpi(db_club_name, "Hamarkameratene 2") == 0 && find_club("Hamarkameratene")) return (BYTE*)find_club("Hamarkameratene");
	if (_strcmpi(db_club_name, "FK Haugesund 2") == 0 && find_club("FK Haugesund")) return (BYTE*)find_club("FK Haugesund");
	if (_strcmpi(db_club_name, "IL Hødd 2") == 0 && find_club("IL Hødd")) return (BYTE*)find_club("IL Hødd");
	if (_strcmpi(db_club_name, "Hønefoss BK 2") == 0 && find_club("Hønefoss BK")) return (BYTE*)find_club("Hønefoss BK");
	if (_strcmpi(db_club_name, "Kjelsas IL 2") == 0 && find_club("Kjelsås IL")) return (BYTE*)find_club("Kjelsås IL");
	if (_strcmpi(db_club_name, "Kongsvinger IL II") == 0 && find_club("Kongsvinger IL")) return (BYTE*)find_club("Kongsvinger IL");
	if (_strcmpi(db_club_name, "Kristiansund BK 2") == 0 && find_club("Kristiansund BK")) return (BYTE*)find_club("Kristiansund BK");
	if (_strcmpi(db_club_name, "Lilleström SK 2") == 0 && find_club("Lillestrøm SK")) return (BYTE*)find_club("Lillestrøm SK");
	if (_strcmpi(db_club_name, "Mjøndalen IF 2") == 0 && find_club("Mjøndalen IF")) return (BYTE*)find_club("Mjøndalen IF");
	if (_strcmpi(db_club_name, "Molde FK II") == 0 && find_club("Molde FK")) return (BYTE*)find_club("Molde FK");
	if (_strcmpi(db_club_name, "Nardo FK 2") == 0 && find_club("Nardo FK")) return (BYTE*)find_club("Nardo FK");
	if (_strcmpi(db_club_name, "Odds BK II") == 0 && find_club("Odds BK")) return (BYTE*)find_club("Odds BK");
	if (_strcmpi(db_club_name, "Pors Fotball II") == 0 && find_club("Pors Fotball")) return (BYTE*)find_club("Pors Fotball");
	if (_strcmpi(db_club_name, "Ranheim 2") == 0 && find_club("Ranheim IL")) return (BYTE*)find_club("Ranheim IL");
	if (_strcmpi(db_club_name, "Raufoss IL 2") == 0 && find_club("Raufoss IL")) return (BYTE*)find_club("Raufoss IL");
	if (_strcmpi(db_club_name, "Rosenborg BK II") == 0 && find_club("Rosenborg BK")) return (BYTE*)find_club("Rosenborg BK");
	if (_strcmpi(db_club_name, "Sandefjord Fotball 2") == 0 && find_club("Sandefjord Fotball")) return (BYTE*)find_club("Sandefjord Fotball");
	if (_strcmpi(db_club_name, "Sandnes Ulf 2") == 0 && find_club("Sandnes Ulf")) return (BYTE*)find_club("Sandnes Ulf");
	if (_strcmpi(db_club_name, "Sarpsborg 08 2") == 0 && find_club("Sarpsborg 08 FF")) return (BYTE*)find_club("Sarpsborg 08 FF");
	if (_strcmpi(db_club_name, "Skeid Oslo II") == 0 && find_club("Skeid Oslo")) return (BYTE*)find_club("Skeid Oslo");
	if (_strcmpi(db_club_name, "Sogndal IL II") == 0 && find_club("Sogndal IL")) return (BYTE*)find_club("Sogndal IL");
	if (_strcmpi(db_club_name, "Stabaek IF II") == 0 && find_club("Stabæk Fotball")) return (BYTE*)find_club("Stabæk Fotball");
	if (_strcmpi(db_club_name, "IK Start 2") == 0 && find_club("IK Start")) return (BYTE*)find_club("IK Start");
	if (_strcmpi(db_club_name, "Strømmen IL 2") == 0 && find_club("Strømmen IF")) return (BYTE*)find_club("Strømmen IF");
	if (_strcmpi(db_club_name, "Strømsgodset IF II") == 0 && find_club("Strømsgodset IF")) return (BYTE*)find_club("Strømsgodset IF");
	if (_strcmpi(db_club_name, "Tromsø IL II") == 0 && find_club("Tromsø IL")) return (BYTE*)find_club("Tromsø IL");
	if (_strcmpi(db_club_name, "SK Træff 2") == 0 && find_club("SK Træff")) return (BYTE*)find_club("SK Træff");
	if (_strcmpi(db_club_name, "Ullensaker/Kisa IL 2") == 0 && find_club("Ullensaker/Kisa IL")) return (BYTE*)find_club("Ullensaker/Kisa IL");
	if (_strcmpi(db_club_name, "SK Vard Haugesund 2") == 0 && find_club("SK Vard Haugesund")) return (BYTE*)find_club("SK Vard Haugesund");
	if (_strcmpi(db_club_name, "Viking FK II") == 0 && find_club("Viking FK")) return (BYTE*)find_club("Viking FK");
	if (_strcmpi(db_club_name, "Vålerenga Fotball II") == 0 && find_club("Vålerenga Fotball Elite")) return (BYTE*)find_club("Vålerenga Fotball Elite");
	if (_strcmpi(db_club_name, "HJK Klubi 04 Helsinki") == 0 && find_club("HJK Helsinki")) return (BYTE*)find_club("HJK Helsinki");
	if (_strcmpi(db_club_name, "FC Espoo II") == 0 && find_club("FC Espoo")) return (BYTE*)find_club("FC Espoo");
	if (_strcmpi(db_club_name, "Helsinki IFK II") == 0 && find_club("Helsinki IFK")) return (BYTE*)find_club("Helsinki IFK");
	if (_strcmpi(db_club_name, "FC Honka II") == 0 && find_club("FC Honka")) return (BYTE*)find_club("FC Honka");
	if (_strcmpi(db_club_name, "Ilves Tampere II") == 0 && find_club("Ilves Tampere")) return (BYTE*)find_club("Ilves Tampere");
	if (_strcmpi(db_club_name, "Kuopion Palloseura II") == 0 && find_club("Kuopion Palloseura")) return (BYTE*)find_club("Kuopion Palloseura");
	if (_strcmpi(db_club_name, "Rovaniemen Palloseura II") == 0 && find_club("Rovaniemen Palloseura")) return (BYTE*)find_club("Rovaniemen Palloseura");
	if (_strcmpi(db_club_name, "Vaasan Palloseura II") == 0 && find_club("Vaasan Palloseura")) return (BYTE*)find_club("Vaasan Palloseura");
	if (_strcmpi(db_club_name, "FC Energie Cottbus II") == 0 && find_club("FC Energie Cottbus")) return (BYTE*)find_club("FC Energie Cottbus");
	if (_strcmpi(db_club_name, "MSV Duisburg Amateure") == 0 && find_club("MSV Duisburg")) return (BYTE*)find_club("MSV Duisburg");
	if (_strcmpi(db_club_name, "Bayer Leverkusen (A)") == 0 && find_club("Bayer 04 Leverkusen")) return (BYTE*)find_club("Bayer 04 Leverkusen");
	if (_strcmpi(db_club_name, "1.FC Saarbrücken II") == 0 && find_club("1.FC Saarbrücken")) return (BYTE*)find_club("1.FC Saarbrücken");
	if (_strcmpi(db_club_name, "Stuttgarter Kickers II") == 0 && find_club("Stuttgarter Kickers")) return (BYTE*)find_club("Stuttgarter Kickers");
	if (_strcmpi(db_club_name, "VfL Wolfsburg Amateure") == 0 && find_club("VfL Wolfsburg")) return (BYTE*)find_club("VfL Wolfsburg");
	if (_strcmpi(db_club_name, "Chrobry Glogow II") == 0 && find_club("Chrobry Glogow")) return (BYTE*)find_club("Chrobry Glogow");
	if (_strcmpi(db_club_name, "Cracovia II") == 0 && find_club("Cracovia")) return (BYTE*)find_club("Cracovia");
	if (_strcmpi(db_club_name, "Gornik Zabrze II") == 0 && find_club("Górnik Zabrze")) return (BYTE*)find_club("Górnik Zabrze");
	if (_strcmpi(db_club_name, "Jagiellonia Bialystok II") == 0 && find_club("Jagiellonia Bialystok")) return (BYTE*)find_club("Jagiellonia Bialystok");
	if (_strcmpi(db_club_name, "Korona Kielce II") == 0 && find_club("Korona Kielce")) return (BYTE*)find_club("Korona Kielce");
	if (_strcmpi(db_club_name, "Lech Poznan II") == 0 && find_club("Lech Poznan")) return (BYTE*)find_club("Lech Poznan");
	if (_strcmpi(db_club_name, "Legia Warsaw II") == 0 && find_club("Legia Warszawa")) return (BYTE*)find_club("Legia Warszawa");
	if (_strcmpi(db_club_name, "LKS Lodz II") == 0 && find_club("LKS Lodz")) return (BYTE*)find_club("LKS Lodz");
	if (_strcmpi(db_club_name, "Miedz Legnica II") == 0 && find_club("Miedz Legnica")) return (BYTE*)find_club("Miedz Legnica");
	if (_strcmpi(db_club_name, "Piast Gliwice II") == 0 && find_club("Piast Gliwice")) return (BYTE*)find_club("Piast Gliwice");
	if (_strcmpi(db_club_name, "Pogon Szczecin II") == 0 && find_club("Pogon Szczecin")) return (BYTE*)find_club("Pogon Szczecin");
	if (_strcmpi(db_club_name, "Rakow Czestochowa II") == 0 && find_club("Raków Czestochowa")) return (BYTE*)find_club("Raków Czestochowa");
	if (_strcmpi(db_club_name, "Slask Wroclaw II") == 0 && find_club("Slask Wroclaw")) return (BYTE*)find_club("Slask Wroclaw");
	if (_strcmpi(db_club_name, "Widzew Lodz II") == 0 && find_club("Widzew Lodz")) return (BYTE*)find_club("Widzew Lodz");
	if (_strcmpi(db_club_name, "Wisla Krakow II") == 0 && find_club("Wisla Kraków")) return (BYTE*)find_club("Wisla Kraków");
	if (_strcmpi(db_club_name, "Wisla Plock II") == 0 && find_club("Wisla Plock")) return (BYTE*)find_club("Wisla Plock");
	if (_strcmpi(db_club_name, "Zaglebie Lubin II") == 0 && find_club("Zaglebie Lubin")) return (BYTE*)find_club("Zaglebie Lubin");
	if (_strcmpi(db_club_name, "Glasgow Celtic B") == 0 && find_club("Glasgow Celtic")) return (BYTE*)find_club("Glasgow Celtic");
	if (_strcmpi(db_club_name, "Heart of Midlothian FC B") == 0 && find_club("Heart of Midlothian FC")) return (BYTE*)find_club("Heart of Midlothian FC");
	if (_strcmpi(db_club_name, "Girona FC B") == 0 && find_club("Girona FC")) return (BYTE*)find_club("Girona FC");
	if (_strcmpi(db_club_name, "Asteras Aktor B") == 0 && find_club("Asteras Aktor")) return (BYTE*)find_club("Asteras Aktor");
	if (_strcmpi(db_club_name, "AEK Athens B") == 0 && find_club("AEK Athens")) return (BYTE*)find_club("AEK Athens");
	if (_strcmpi(db_club_name, "Olympiacos Piraeus B") == 0 && find_club("Olympiacos Piraeus")) return (BYTE*)find_club("Olympiacos Piraeus");
	if (_strcmpi(db_club_name, "PAOK Thessaloniki B") == 0 && find_club("PAOK Thessaloniki")) return (BYTE*)find_club("PAOK Thessaloniki");

	// default case if none found
	to_check->ClubHasLinkedClub = 0;
	return NULL;
}

void __declspec(naked) check_if_reserve_team_new_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call check_if_reserve_team_new
		add esp, 0x0c
		ret
	}
}

void setup_name_injection()
{
	// Add call to our name function after all player setups have been loaded
	PatchFunction(0x5CCCC1, (DWORD)inject_club_names);
	PatchFunction(0x60EFD0, (DWORD)setup_9cf_leagues);
	PatchFunction(0x6115E0, (DWORD)setup_9cf_awards);
	PatchFunction(0x6146B0, (DWORD)setup_9cf_clubs);

	PatchFunction(0x540A50, (DWORD)check_if_reserve_team_new);

	if (configFile.GetBool("applyAustralia", true)) {
		leagues_rename_long.insert(leagues_rename_long_australia.begin(), leagues_rename_long_australia.end());
		leagues_rename_short.insert(leagues_rename_short_australia.begin(), leagues_rename_short_australia.end());
	}

	if (configFile.GetBool("applyBrazil", true)) {
		leagues_rename_long.insert(leagues_rename_long_brazil.begin(), leagues_rename_long_brazil.end());
		leagues_rename_short.insert(leagues_rename_short_brazil.begin(), leagues_rename_short_brazil.end());
		leagues_rename_tla.insert(leagues_rename_tla_brazil.begin(), leagues_rename_tla_brazil.end());
	}

	if (configFile.GetBool("applyCroatia", true)) {
		awards_rename_long.insert(awards_rename_long_croatia.begin(), awards_rename_long_croatia.end());
		awards_rename_short.insert(awards_rename_short_croatia.begin(), awards_rename_short_croatia.end());
		leagues_rename_long.insert(leagues_rename_long_croatia.begin(), leagues_rename_long_croatia.end());
		leagues_rename_short.insert(leagues_rename_short_croatia.begin(), leagues_rename_short_croatia.end());
		leagues_rename_tla.insert(leagues_rename_tla_croatia.begin(), leagues_rename_tla_croatia.end());
	}

	if (configFile.GetBool("applyGermany", true)) {
		leagues_rename_long.insert(leagues_rename_long_germany.begin(), leagues_rename_long_germany.end());
		leagues_rename_short.insert(leagues_rename_short_germany.begin(), leagues_rename_short_germany.end());
		leagues_rename_tla.insert(leagues_rename_tla_germany.begin(), leagues_rename_tla_germany.end());
	}

	if (configFile.GetBool("applyGreece", true)) {
		leagues_rename_long.insert(leagues_rename_long_greece.begin(), leagues_rename_long_greece.end());
		leagues_rename_short.insert(leagues_rename_short_greece.begin(), leagues_rename_short_greece.end());
		leagues_rename_tla.insert(leagues_rename_tla_greece.begin(), leagues_rename_tla_greece.end());
	}

	if (configFile.GetBool("applyFinland", true)) {
		leagues_rename_long.insert(leagues_rename_long_finland.begin(), leagues_rename_long_finland.end());
		leagues_rename_short.insert(leagues_rename_short_finland.begin(), leagues_rename_short_finland.end());
		leagues_rename_tla.insert(leagues_rename_tla_finland.begin(), leagues_rename_tla_finland.end());
	}

	if (configFile.GetBool("applyHolland", true)) {
		awards_rename_long.insert(awards_rename_long_holland.begin(), awards_rename_long_holland.end());
		awards_rename_short.insert(awards_rename_short_holland.begin(), awards_rename_short_holland.end());
	}

	if (configFile.GetBool("applyItaly", true)) {
		awards_rename_long.insert(awards_rename_long_italy.begin(), awards_rename_long_italy.end());
		awards_rename_short.insert(awards_rename_short_italy.begin(), awards_rename_short_italy.end());
		leagues_rename_long.insert(leagues_rename_long_italy.begin(), leagues_rename_long_italy.end());
		leagues_rename_short.insert(leagues_rename_short_italy.begin(), leagues_rename_short_italy.end());
		leagues_rename_tla.insert(leagues_rename_tla_italy.begin(), leagues_rename_tla_italy.end());
	}

	if (configFile.GetBool("applyJapan", true)) {
		leagues_rename_long.insert(leagues_rename_long_japan.begin(), leagues_rename_long_japan.end());
		leagues_rename_short.insert(leagues_rename_short_japan.begin(), leagues_rename_short_japan.end());
		leagues_rename_tla.insert(leagues_rename_tla_japan.begin(), leagues_rename_tla_japan.end());
	}

	if (configFile.GetBool("applyNorway", true)) {
		leagues_rename_long.insert(leagues_rename_long_norway.begin(), leagues_rename_long_norway.end());
		leagues_rename_short.insert(leagues_rename_short_norway.begin(), leagues_rename_short_norway.end());
		leagues_rename_tla.insert(leagues_rename_tla_norway.begin(), leagues_rename_tla_norway.end());
	}

	if (configFile.GetBool("applyPoland", true)) {
		awards_rename_long.insert(awards_rename_long_poland.begin(), awards_rename_long_poland.end());
		awards_rename_short.insert(awards_rename_short_poland.begin(), awards_rename_short_poland.end());
		leagues_rename_long.insert(leagues_rename_long_poland.begin(), leagues_rename_long_poland.end());
		leagues_rename_short.insert(leagues_rename_short_poland.begin(), leagues_rename_short_poland.end());
		leagues_rename_tla.insert(leagues_rename_tla_poland.begin(), leagues_rename_tla_poland.end());
	}

	if (configFile.GetBool("applyPortugal", true)) {
		awards_rename_long.insert(awards_rename_long_portugal.begin(), awards_rename_long_portugal.end());
		awards_rename_short.insert(awards_rename_short_portugal.begin(), awards_rename_short_portugal.end());
		leagues_rename_long.insert(leagues_rename_long_portugal.begin(), leagues_rename_long_portugal.end());
		leagues_rename_short.insert(leagues_rename_short_portugal.begin(), leagues_rename_short_portugal.end());
		leagues_rename_tla.insert(leagues_rename_tla_portugal.begin(), leagues_rename_tla_portugal.end());
	}

	if (configFile.GetBool("applyScotland", true)) {
		leagues_rename_long.insert(leagues_rename_long_scotland.begin(), leagues_rename_long_scotland.end());
		leagues_rename_short.insert(leagues_rename_short_scotland.begin(), leagues_rename_short_scotland.end());
		leagues_rename_tla.insert(leagues_rename_tla_scotland.begin(), leagues_rename_tla_scotland.end());
	}

	if (configFile.GetBool("applySpain", true)) {
		leagues_rename_long.insert(leagues_rename_long_spain.begin(), leagues_rename_long_spain.end());
		leagues_rename_short.insert(leagues_rename_short_spain.begin(), leagues_rename_short_spain.end());
		leagues_rename_tla.insert(leagues_rename_tla_spain.begin(), leagues_rename_tla_spain.end());
	}

	if (configFile.GetBool("applySweden", true)) {
		leagues_rename_long.insert(leagues_rename_long_sweden.begin(), leagues_rename_long_sweden.end());
		leagues_rename_short.insert(leagues_rename_short_sweden.begin(), leagues_rename_short_sweden.end());
		leagues_rename_tla.insert(leagues_rename_tla_sweden.begin(), leagues_rename_tla_sweden.end());
	}

	if (configFile.GetBool("applyTurkey", true)) {
		leagues_rename_long.insert(leagues_rename_long_turkey.begin(), leagues_rename_long_turkey.end());
		leagues_rename_short.insert(leagues_rename_short_turkey.begin(), leagues_rename_short_turkey.end());
	}

	if (configFile.GetBool("applyWales", true)) {
		leagues_rename_long.insert(leagues_rename_long_wales.begin(), leagues_rename_long_wales.end());
		leagues_rename_short.insert(leagues_rename_short_wales.begin(), leagues_rename_short_wales.end());
		leagues_rename_tla.insert(leagues_rename_tla_wales.begin(), leagues_rename_tla_wales.end());
	}
}