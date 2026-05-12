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
	{"C.D. Ourense", "Ourense CF"}, // remove for April update
	{"C.P. Mérida", "Mérida AD"}, // remove for April update
	{"Baskonia C.D.", "CD Basconia"},
	{"Extremadura C.F.", "CD Extremadura"},
	{"Merthyr Tydfil", "Merthyr Town"},
	{"Bra", "AC Bra"}, // remove for April update
	//{"AZ", "AZ Alkmaar"},
	{"GD Chaves Satelite", "GD Chaves B"}, // remove for April update
	{"Bor. M'gladbach Amateure", "Borussia M'gladbach II"},
	{"SC Paderborn 07 Reserves", "SC Paderborn 07 II"},
	{"SJK Seinäjoki II", "SJK Seinäjoki Akatemia"},
	{"Associação Lusitano de Évora 1911", "Lusitano GC Évora"},
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
	{"German Regionalliga West", 0x9CF554},
	{"German Regionalliga Nordost", 0x9CF558},
	{"German Regionalliga Nord", 0x9CF55C},
	{"German Regionalliga Südwest", 0x9CF560},
	{"German 3. Liga", 0x9CF564},
	{"Dutch Eredivisie", 0x9CF568},
	{"Dutch Eerste Divisie", 0x9CF56C},
	{"Italian Serie A", 0x9CF570},
	{"Italian Serie B", 0x9CF574},
	{"Italian Serie C/A", 0x9CF578},
	{"Italian Serie C/B", 0x9CF57C},
	{"Italian Serie C2/A", 0x9CF580},
	{"Italian Serie C2/B", 0x9CF584},
	{"Italian Serie C2/C", 0x9CF588},
	{"Italian Serie D", 0x9CF58C},
	{"Major League Soccer", 0x9CF590},
	{"American USL Championship", 0x9CF594},
	{"American USL League One", 0x9CF598},
	{"Belgian Pro League", 0x9CF59C},
	{"Belgian Challenger Pro League", 0x9CF5A0},
	{"Belgian Division 1 VV", 0x9CF5A4},
	{"Belgian Division 1 ACFF", 0x9CF5A8},
	{"Danish Superliga", 0x9CF5AC},
	{"Danish First Division", 0x9CF5B0},
	{"Danish Second Division", 0x9CF5B4},
	{"Danish Third Division", 0x9CF5B8},
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
	{"Swedish Ettan South", 0x9CF5F4},
	{"Swedish Ettan North", 0x9CF5F8},
	{"Swedish Division 2 South Svealand", 0x9CF5FC},
	{"Swedish Division 2 North Götaland", 0x9CF600},
	{"Swedish Division 2 Norrland", 0x9CF604},
	{"Swedish Division 2 West Götaland", 0x9CF608},
	{"Liga Portugal 1", 0x9CF60C},
	{"Liga Portugal 2", 0x9CF610},
	{"Liga 3 Série A", 0x9CF614},
	{"Campeonato de Portugal Série A", 0x9CF618},
	{"Liga 3 Série B", 0x9CF61C},
	{"Campeonato de Portugal", 0x9CF620},
	{"Spanish La Liga", 0x9CF624},
	{"Spanish La Liga 2", 0x9CF628},
	{"Spanish Primera Federación Group 1", 0x9CF62C},
	{"Spanish Primera Federación Group 2", 0x9CF630},
	{"Spanish Segunda Federación Group 4", 0x9CF634},
	{"Spanish Segunda Federación Group 5", 0x9CF638},
	{"Copa Libertadores de América", 0x9CF63C},
	{"Campeonato de Portugal Série C", 0x9CF640},
	{"Copa CONMEBOL", 0x9CF644},
	{"Recopa Sudamericana", 0x9CF648},
	{"AFC Champions League Elite", 0x9CF64C},
	{"AFC Champions League Two", 0x9CF650},
	{"Argentine Primera División", 0x9CF654},
	{"Argentine Primera Nacional", 0x9CF658},
	{"Japanese J1 League", 0x9CF65C},
	{"Japanese Emperor's Cup", 0x9CF660},
	{"Japanese J.League Cup", 0x9CF664},
	{"Friendly", 0x9CF668},
	{"Japanese Super Cup", 0x9CF66C},
	{"Japanese Football League", 0x9CF670},
	{"Japanese Regional Championships", 0x9CF674},
	{"Japanese J3 League", 0x9CF678},
	{"Copa Argentina", 0x9CF67C},
	{"Argentine Torneo Federal A", 0x9CF680},
	{"Reserve", 0x9CF684},
	{"Argentine Primera División B", 0x9CF688},
	{"Campeonato Brasileiro Série D", 0x9CF68C},
	{"Swedish Division 2 South Götaland", 0x9CF690},
	{"German DFL-Supercup", 0x9CF694},
	{"Copa Sudamericana", 0x9CF698},
	{"English National League", 0x9CF69C},
	{"English FA Trophy", 0x9CF6A0},
	{"Conference League Cup", 0x9CF6A4},
	{"Trophée des Champions", 0x9CF6A8},
	{"Swedish Division 2", 0x9CF6AC},
	{"Spanish Segunda Federación", 0x9CF6B0},
	{"Supertaça Cândido de Oliveira", 0x9CF6B4},
	{"A Premier Division", 0x9CF6B8},
	{"Norwegian Eliteserien", 0x9CF6BC},
	{"Norwegian 1. Divisjon", 0x9CF6C0},
	{"Norwegian 2. Divisjon Group 1", 0x9CF6C4},
	{"Norwegian 2. Divisjon Group 2", 0x9CF6C8},
	{"Norwegian 3. Divisjon Group 1", 0x9CF6CC},
	{"Norwegian 3. Divisjon Group 2", 0x9CF6D0},
	{"Norwegian 3. Divisjon Group 3", 0x9CF6D4},
	{"Norwegian 3. Divisjon Group 4", 0x9CF6D8},
	{"Norwegian 3. Divisjon Group 5", 0x9CF6DC},
	{"Norwegian 3. Divisjon Group 6", 0x9CF6E0},
	{"Intercontinental Cup", 0x9CF6E4},
	{"UEFA Champions League", 0x9CF6E8},
	{"UEFA Conference League", 0x9CF6EC},
	{"UEFA Europa League", 0x9CF6F0},
	{"UEFA Super Cup", 0x9CF6F4},
	{"UEFA Intertoto Cup", 0x9CF6F8},
	{"Supercoupe de Belgique", 0x9CF6FC},
	{"Coupe de Belgique", 0x9CF700},
	{"Campeonato de Portugal Série B", 0x9CF704},
	{"DBU Pokalen", 0x9CF708},
	{"Coupe de France", 0x9CF70C},
	{"Coupe de la Ligue", 0x9CF710},
	{"German DFB-Pokal", 0x9CF714},
	{"KNVB Beker", 0x9CF718},
	{"Coppa Italia", 0x9CF71C},
	{"Coppa Italia Serie C", 0x9CF720},
	{"Supercoppa Italiana", 0x9CF724},
	{"Lamar Hunt U.S. Open Cup", 0x9CF728},
	{"CONCACAF Champions Cup", 0x9CF72C},
	{"Campeonato de Portugal Série D", 0x9CF730},
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
	{"Gold Cup", 0x9CF78C},
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
	{"Belgian Division 2 VV", 0x9CF7D4},
	{"Belgian Division 2 VV A", 0x9CF7D8},
	{"Belgian Division 2 VV B", 0x9CF7DC},
	{"Belgian Division 2 ACFF", 0x9CF7E0},
	{"Suomen Cup", 0x9CF7E4},
	{"Finnish Veikkausliiga", 0x9CF7E8},
	{"Finnish Ykkönen", 0x9CF7EC},
	{"Finnish Kolmonen", 0x9CF7F0},
	{"Finnish Kakkonen", 0x9CF7F4},
	{"Finnish Ykkösliiga", 0x9CF7F8},
	{"Finnish Kakkonen Group A", 0x9CF7FC},
	{"Finnish Kakkonen Group B", 0x9CF800},
	{"Finnish Kakkonen Group C", 0x9CF804},
	{"Finnish Ykkönen East", 0x9CF808},
	{"League of Ireland Premier Division", 0x9CF80C},
	{"League of Ireland First Division", 0x9CF810},
	{"Irish Group A", 0x9CF814}, // remove
	{"Irish Group B", 0x9CF818}, // remove
	{"Irish Group C", 0x9CF81C}, // remove
	{"Irish Group D", 0x9CF820}, // remove
	{"Irish Group E", 0x9CF824}, // remove
	{"Northern Irish Group A", 0x9CF82C}, // remove
	{"Northern Irish Group B", 0x9CF830}, // remove
	{"Northern Irish Group C", 0x9CF834}, // remove
	{"Northern Irish Group D", 0x9CF838}, // remove
	{"League of Ireland Cup", 0x9CF83C},
	{"FAI Cup", 0x9CF840},
	{"African Cup Winners' Cup", 0x9CF844}, // remove (there are exe references, check)
	{"Irish Connacht Senior League", 0x9CF848},
	{"Irish Ulster Senior League", 0x9CF84C},
	{"Irish Munster Senior League", 0x9CF850},
	{"Irish Leinster Senior League Premier", 0x9CF854},
	{"Polish Ekstraklasa", 0x9CF858},
	{"Polish I Liga", 0x9CF85C},
	{"Polish III Liga", 0x9CF860},
	{"Puchar Polski", 0x9CF864},
	{"Polish II Liga", 0x9CF868},
	{"Greek Super League", 0x9CF86C},
	{"Greek Super League 2", 0x9CF870},
	{"Greek Gamma Ethniki", 0x9CF874},
	{"Kypello Elladas", 0x9CF878},
	{"Croatian HNL", 0x9CF87C},
	{"Croatian Prva NL", 0x9CF880},
	{"Croatian Treca NL", 0x9CF884},
	{"Croatian Druga NL North", 0x9CF888}, // remove
	{"Croatian Druga NL South", 0x9CF88C}, // remove
	{"Croatian Druga NL East", 0x9CF890}, // remove
	{"Croatian Druga NL West", 0x9CF894}, // remove
	{"Hrvatski Kup", 0x9CF898},
	{"Australian A-League", 0x9CF89C},
	{"OFC Nations Cup", 0x9CF8A0},
	{"Croatian Druga NL", 0x9CF8A4},
	{"Croatian Prva NL North", 0x9CF8A8},
	{"Croatian Prva NL South", 0x9CF8AC},
	{"NIFL Premiership", 0x9CF8B0},
	{"NIFL Championship", 0x9CF8B4},
	{"NIFL Premier Intermediate League", 0x9CF8B8},
	{"NIFL Charity Shield", 0x9CF8BC},
	{"Irish Football Association Challenge Cup", 0x9CF8C0},
	{"German Regionalliga Bayern", 0x9CF8C4},
	{"Irish Football League Cup", 0x9CF8C8},
	{"TFF 3. Lig", 0x9CF8CC},
	{"Turkish 2. Division Group 1", 0x9CF8D0},
	//{"Turkish 2. Division Group 2", 0x9CF8D4},
	{"Turkish Süper Lig", 0x9CF8D8},
	{"TFF 1. Lig", 0x9CF8DC},
	{"TFF 2. Lig", 0x9CF8E0},
	{"TFF 2. Lig Group 1", 0x9CF8E4},
	{"TFF 2. Lig Group 2", 0x9CF8E8},
	{"TFF 3. Lig Group 1", 0x9CF8EC},
	{"TFF 3. Lig Group 2", 0x9CF8F0},
	{"TFF 3. Lig Group 3", 0x9CF8F4},
	{"Türkiye Kupasi", 0x9CF8F8},
	{"Turkish Super Cup", 0x9CF8FC},
	{"English National League North", 0x9CF900},
	{"English National League South", 0x9CF904},
	{"Italian Serie C", 0x9CF908},
	{"Italian Serie C/C", 0x9CF90C},
	{"German Regionalliga", 0x9CF910},
	{"Russian Super Cup", 0x9CF914},
	{"Russian Second League Division A", 0x9CF918},
	{"Russian Second League Division B", 0x9CF91C},
	{"Russian Second League Division A Gold", 0x9CF920},
	{"Russian Second League Division A Silver", 0x9CF924},
	{"Russian Second Division - East", 0x9CF928}, // remove
	{"Russian First League", 0x9CF92C},
	{"Russian Premier League", 0x9CF930},
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
	{"Welsh Cymru North", 0x9CF960},
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
	{"Campeonato Brasileiro Série C", 0x9CF9AC},
	{"Brazilian Campeonato Catarinense", 0x9CF9B0},
	{"Brazilian Campeonato Goiano", 0x9CF9B4},
	{"Brazilian Supercopa Rei", 0x9CF9B8},
	{"Brazilian Campeonato Pernambucano", 0x9CF9BC},
	{"Brazilian Campeonato Baiano", 0x9CF9C0},
	{"Brazilian Northeast Regional Cup", 0x9CF9C4},
	{"Brazilian Campeonato Gaúcho", 0x9CF9C8},
	{"Brazilian South-Minas Regional Cup", 0x9CF9CC},
	{"Brazilian Campeonato Paranaense", 0x9CF9D0},
	{"Brazilian Campeonato Mineiro", 0x9CF9D4},
	{"Brazilian Rio-São Paulo Tournement", 0x9CF9D8},
	{"Brazilian Campeonato Carioca", 0x9CF9DC},
	{"Campeonato Brasileiro Série B", 0x9CF9E0},
	{"Brazilian Campeonato Paulista", 0x9CF9E4},
	{"Copa do Brasil", 0x9CF9E8},
	{"Campeonato Brasileiro Série A", 0x9CF9EC},
	{"Irish Munster Senior Cup", 0x9CF9F0},
	{"Irish Leinster Senior Cup", 0x9CF9F4},
	{"K League Super Cup", 0x9CF9F8},
	{"K League 2", 0x9CF9FC},
	{"K League 1", 0x9CFA00},
	{"Korea Cup", 0x9CFA04},
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
	{"English Championship Team of the Year", 0x9CFA40},
	{"English League One Team of the Year", 0x9CFA44},
	{"English League Two Team of the Year", 0x9CFA48},
	{"English Premier League Player of the Month", 0x9CFA4C},
	{"English Championship Player of the Month", 0x9CFA50},
	{"English League One Player of the Month", 0x9CFA54},
	{"English League Two Player of the Month", 0x9CFA58},
	{"English Premier League Young Player of the Month", 0x9CFA5C},
	{"English Championship Young Player of the Month", 0x9CFA60},
	{"English League One Young Player of the Month", 0x9CFA64},
	{"English League Two Young Player of the Month", 0x9CFA68},
	{"English Premier League Team of the Week", 0x9CFA6C},
	{"English Championship Team of the Week", 0x9CFA70},
	{"English League One Team of the Week", 0x9CFA74},
	{"English League Two Team of the Week", 0x9CFA78},
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
	{"Belgian Pro League Player of the Year", 0x9CFAA8},
	{"Belgian Pro League Goalkeeper of the Year", 0x9CFAAC},
	{"Belgian Second Division Player of the Year", 0x9CFAB0},
	{"Danish Player of the Year", 0x9CFAB4},
	{"Danish Superliga Player of the Year", 0x9CFAB8},
	{"Danish Superliga Young Player of the Year", 0x9CFABC},
	{"Danish First Division Player of the Year", 0x9CFAC0},
	{"Danish First Division Young Player of the Year", 0x9CFAC4},
	{"Danish Third Division Player of the Year", 0x9CFAC8},
	{"Danish Second Division Player of the Year", 0x9CFACC},
	{"Danish Third Division Young Player of Year", 0x9CFAD0},
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
	{"Dutch Eerste Divisie Young Player of the Year", 0x9CFB14},
	{"Dutch Eredivisie Player of the Year", 0x9CFB18},
	{"Dutch Eredivisie Top Goalscorer", 0x9CFB1C},
	{"Dutch Eredivisie Manager of the Year", 0x9CFB20},
	{"Dutch Eerste Divisie Player of the Year", 0x9CFB24},
	{"Dutch Eerste Divisie Top Goalscorer", 0x9CFB28},
	{"Dutch Eerste Divisie Manager of the Year", 0x9CFB2C},
	{"Italian Serie A Young Player of the Year", 0x9CFB30},
	{"Italian Serie A Player of the Year", 0x9CFB34},
	{"Italian Serie A Italian Player of the Year", 0x9CFB38},
	{"Italian Serie A Foreign Player of the Year", 0x9CFB3C},
	{"Italian Serie A Defender of the Year", 0x9CFB40},
	{"Italian Serie A Goalkeeper of the Year", 0x9CFB44},
	{"Italian Serie B Player of the Year", 0x9CFB48},
	{"Italian Serie C Player of the Year", 0x9CFB4C},
	{"Italian Serie C1/B Player of the Year", 0x9CFB50},
	{"Norwegian Player of the Year", 0x9CFB54},
	{"Norwegian Goalkeeper of the Year", 0x9CFB58},
	{"Norwegian Defender of the Year", 0x9CFB5C},
	{"Norwegian Midfielder of the Year", 0x9CFB60},
	{"Norwegian Attacker of the Year", 0x9CFB64},
	{"Norwegian Eliteserien Team of the Week", 0x9CFB68},
	{"Norwegian 1. Divisjon Team of the Week", 0x9CFB6C},
	{"Liga Portugal 1 Most Man of the Match", 0x9CFB70},
	{"Liga Portugal 1 Top Goalscorer", 0x9CFB74},
	{"Liga Portugal 2 Player of the Year", 0x9CFB78},
	{"Spanish La Liga Goalkeeper of the Year", 0x9CFB7C},
	{"Spanish Player of the Year", 0x9CFB80},
	{"Spanish La Liga Top Goalscorer", 0x9CFB84},
	{"Swedish Player of the Year", 0x9CFB88},
	{"Swedish Allsvenskan Top Goalscorer", 0x9CFB8C},
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
	{"English Championship Manager of the Year", 0x9CFBDC},
	{"English Championship Manager of the Month", 0x9CFBE0},
	{"English League One Manager of the Year", 0x9CFBE4},
	{"English League One Manager of the Month", 0x9CFBE8},
	{"English League Two Manager of the Year", 0x9CFBEC},
	{"English League Two Manager of the Month", 0x9CFBF0},
	{"French Manager of the Year", 0x9CFBF4},
	{"German Bundesliga Manager of the Year", 0x9CFBF8},
	{"German 2. Bundesliga Manager of the Year", 0x9CFBFC},
	{"Dutch Eredivisie Young Player of the Year", 0x9CFC00},
	{"Italian Serie A Panchina d'Oro", 0x9CFC04},
	{"Italian Serie B Panchina d'Argento", 0x9CFC08},
	{"Italian Serie C Manager of the Year", 0x9CFC0C},
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
	{"Argentine Primera División Team of the Week", 0x9CFC44},
	{"Argentine Primera Nacional Team of the Week", 0x9CFC48},
	{"Japanese Player of the Year", 0x9CFC4C},
	{"Japanese Top Goalscorer", 0x9CFC50},
	{"Japanese Young Player of the Year", 0x9CFC54},
	{"Japanese Manager of the Year", 0x9CFC58},
	{"Japanese J1 League Team of the Year", 0x9CFC5C},
	{"World Cup Golden Boot", 0x9CFC60},
	{"World Cup Dream Team", 0x9CFC64},
	{"German 3. Liga Player of the Month", 0x9CFC68},
	{"English National North Manager of the Year", 0x9CFC6C},
	{"German 3. Liga Manager of the Year", 0x9CFC70},
	{"German 3. Liga Team of the Week", 0x9CFC74},
	{"German 3. Liga Top Goalscorer", 0x9CFC78},
	{"German Bundesliga Top Goalscorer", 0x9CFC7C},
	{"English National South Manager of the Year", 0x9CFC80},
	{"English National League Manager of the Month", 0x9CFC84},
	{"English National League Team of the Year", 0x9CFC88},
	{"English National League Manager of the Year", 0x9CFC8C},
	{"English National League Player of the Month", 0x9CFC90},
	{"English National League Team of the Week", 0x9CFC94},
	{"English National League Young Player of the Month", 0x9CFC98},
	{"Liga Portugal 1 Team of the Year", 0x9CFC9C},
	{"Liga Portugal 2 Team of the Year", 0x9CFCA0},
	{"Liga Portugal 1 Team of the Week", 0x9CFCA4},
	{"Liga Portugal 2 Team of the Week", 0x9CFCA8},
	{"Japanese J1 League Team of the Week", 0x9CFCAC},
	{"Japanese J2 League Team of the Week", 0x9CFCB0},
	{"Swedish Allsvenskan Team of the Week", 0x9CFCB4},
	{"Swedish Superettan Team of the Week", 0x9CFCB8},
	{"Spanish La Liga Team of the Week", 0x9CFCBC},
	{"Spanish La Liga 2 Team of the Week", 0x9CFCC0},
	{"Italian Serie A Team of the Week", 0x9CFCC4},
	{"Italian Serie B Team of the Week", 0x9CFCC8},
	{"Italian Serie C Team of the Week", 0x9CFCCC},
	{"Italian Serie C1/B Team of the Week", 0x9CFCD0},
	{"Dutch Eredivisie Team of the Week", 0x9CFCD4},
	{"Dutch Eerste Divisie Team of the Week", 0x9CFCD8},
	{"German Bundesliga Team of the Week", 0x9CFCDC},
	{"German 2. Bundesliga Team of the Week", 0x9CFCE0},
	{"French Ligue 1 Team of the Week", 0x9CFCE4},
	{"French Ligue 2 Team of the Week", 0x9CFCE8},
	{"Danish Superliga Team of the Week", 0x9CFCEC},
	{"Danish First Division Team of the Week", 0x9CFCF0},
	{"Danish Second Division Team of the Week", 0x9CFCF4},
	{"Belgian Pro League Team of the Week", 0x9CFCF8},
	{"Belgian Challenger League Team of the Week", 0x9CFCFC},
	{"Liga Portugal 1 Player of the Year", 0x9CFD00},
	{"Liga Portugal 2 Most Man of the Match", 0x9CFD04},
	{"Liga Portugal 2 Top Goalscorer", 0x9CFD08},
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
	{"Japanese J2 League Team of the Year", 0x9CFD38},
	{"Spanish La Liga 2 Goalkeeper of the Year", 0x9CFD3C},
	{"Spanish La Liga 2 Top Goalscorer", 0x9CFD40},
	{"Italian Serie C2/B Team of the Week", 0x9CFD44},
	{"Italian Serie C2/C Manager of the Year", 0x9CFD48},
	{"Italian Serie C2/C Player of the Year", 0x9CFD4C},
	{"Italian Serie C2/C Team of the Week", 0x9CFD50},
	{"Belgian Pro League Top Goalscorer", 0x9CFD54},
	{"Belgian Pro League Revelation of the Year", 0x9CFD58},
	{"Belgian Challenger League Top Goalscorer", 0x9CFD5C},
	{"Belgian Division 1 VV Team of the Week", 0x9CFD60},
	{"Belgian Division 1 VV Revelation of the Year", 0x9CFD64},
	{"Belgian Division 1 VV Top Goalscorer", 0x9CFD68},
	{"European Goalkeeper of the Year", 0x9CFD6C},
	{"European Defender of the Year", 0x9CFD70},
	{"European Midfielder of the Year", 0x9CFD74},
	{"European Striker of the Year", 0x9CFD78},
	{"Italian Serie A Team of the Year", 0x9CFD7C},
	{"Italian Serie B Team of the Year", 0x9CFD80},
	{"Italian Serie C Team of the Year", 0x9CFD84},
	{"Italian Serie C1/B Team of the Year", 0x9CFD88},
	{"Italian Serie C2/A Team of the Year", 0x9CFD8C},
	{"Italian Serie C2/B Team of the Year", 0x9CFD90},
	{"Italian Serie C2/C Team of the Year", 0x9CFD94},
	{"Italian Serie A Capocannoniere", 0x9CFD98},
	{"Italian Serie B Top Goalscorer", 0x9CFD9C},
	{"Italian Serie C Top Goalscorer", 0x9CFDA0},
	{"Italian Serie C1/B Top Goalscorer", 0x9CFDA4},
	{"Italian Serie C2/A Top Goalscorer", 0x9CFDA8},
	{"Italian Serie C2/B Top Goalscorer", 0x9CFDAC},
	{"Italian Serie C2/C Top Goalscorer", 0x9CFDB0},
	{"Norwegian Eliteserien Manager of the Month", 0x9CFDB4},
	{"Norwegian Eliteserien Player of the Month", 0x9CFDB8},
	{"Norwegian 1. Divisjon Manager of the Month", 0x9CFDBC},
	{"Norwegian 1. Divisjon Player of the Month", 0x9CFDC0},
	{"Liga Portugal 1 Manager of the Year", 0x9CFDC4},
	{"Liga Portugal 2 Manager of the Year", 0x9CFDC8},
	{"Finnish Player of the Year", 0x9CFDCC},
	{"Finnish Young Player of the Year", 0x9CFDD0},
	{"Finnish Goalkeeper of the Year", 0x9CFDD4},
	{"Finnish Manager of the Year", 0x9CFDD8},
	{"Finnish Veikkausliiga Top Goalscorer", 0x9CFDDC},
	{"Finnish Veikkausliiga Player of the Month", 0x9CFDE0},
	{"Finnish Veikkausliiga Team of the Year", 0x9CFDE4},
	{"Finnish Veikkausliiga Team of the Week", 0x9CFDE8},
	{"Finnish Ykkösliiga Top Goalscorer", 0x9CFDEC},
	{"Finnish Ykkösliiga Team of the Year", 0x9CFDF0},
	{"Finnish Ykkösliiga Team of the Week", 0x9CFDF4},
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
	{"Polish Ekstraklasa Team of the Week", 0x9CFE30},
	{"Polish Ekstraklasa Player of the Year", 0x9CFE34},
	{"Polish Ekstraklasa Young Player of the Year", 0x9CFE38},
	{"Polish Ekstraklasa Manager of the Year", 0x9CFE3C},
	{"Polish Ekstraklasa Team of the Year", 0x9CFE40},
	{"Polish I Liga Team of the Week", 0x9CFE44},
	{"Polish I Liga Player of the Year", 0x9CFE48},
	{"Polish I Liga Young Player of the Year", 0x9CFE4C},
	{"Polish I Liga Manager of the Year", 0x9CFE50},
	{"Polish I Liga Team of the Year", 0x9CFE54},
	{"Croatian HNL Player of the Year", 0x9CFE58},
	{"Croatian HNL Team of the Week", 0x9CFE5C},
	{"Croatian HNL Top Goalscorer", 0x9CFE60},
	{"Croatian 1. NL Player of the Year", 0x9CFE64},
	{"Croatian 1. NL Team of the Week", 0x9CFE68},
	{"Croatian 1. NL Top Goalscorer", 0x9CFE6C},
	{"Croatian 2. NL Player of the Year", 0x9CFE70},
	{"Croatian 2. NL Team of the Week", 0x9CFE74},
	{"Croatian 2. NL Top Goalscorer", 0x9CFE78},
	{"Australian A-League Team of the Week", 0x9CFE7C},
	{"Australian A-League Manager of the Month", 0x9CFE80},
	{"Australian A-League Player of the Month", 0x9CFE84},
	{"Australian A-League Young Player of the Month", 0x9CFE88},
	{"Australian A-League Player of the Year", 0x9CFE8C},
	{"Australian A-League Young Player of the Year", 0x9CFE90},
	{"Australian A-League Goalkeeper of the Year", 0x9CFE94},
	{"Australian A-League Leading Goalscorer", 0x9CFE98},
	{"Australian A-League Manager of the Year", 0x9CFE9C},
	{"Greek Player of the Year", 0x9CFEA0},
	{"Greek Foreign Player of the Year", 0x9CFEA4},
	{"Greek Super League Team of the Week", 0x9CFEA8},
	{"Greek Super League Player of the Year", 0x9CFEAC},
	{"Greek Super League Manager of the Year", 0x9CFEB0},
	{"Greek Super League Top Goalscorer", 0x9CFEB4},
	{"Greek Super League 2 Team of the Week", 0x9CFEB8},
	{"Greek Super League 2 Player of the Year", 0x9CFEBC},
	{"Greek Super League 2 Manager of the Year", 0x9CFEC0},
	{"Greek Super League 2 Top Goalscorer", 0x9CFEC4},
	{"Turkish Player of the Year", 0x9CFEC8},
	{"Turkish Manager of the Year", 0x9CFECC},
	{"Turkish Süper Lig Team of the Week", 0x9CFED0},
	{"Turkish Süper Lig Team of the Year", 0x9CFED4},
	{"TFF 1. Lig Team of the Week", 0x9CFED8},
	{"TFF 1. Lig Team of the Year", 0x9CFEDC},
	{"Russian Player of the Year", 0x9CFEE0},
	{"Russian Premier League Team of the Week", 0x9CFEE4},
	{"Russian Premier League Team of the Year", 0x9CFEE8},
	{"Russian Premier League Player of the Month", 0x9CFEEC},
	{"Russian First League Team of the Week", 0x9CFEF0},
	{"Russian First League Team of the Year", 0x9CFEF4},
	{"Russian First League Player of the Month", 0x9CFEF8},
	{"Irish Personality of the Year", 0x9CFEFC},
	{"NIFL Player of the Year", 0x9CFF00},
	{"NIFL Premiership Team of the Week", 0x9CFF04},
	{"NIFL Premiership Player of the Year", 0x9CFF08},
	{"NIFL Premiership Young Player of the Year", 0x9CFF0C},
	{"NIFL Premiership Top Goalscorer", 0x9CFF10},
	{"NIFL Premiership Manager of the Year", 0x9CFF14},
	{"NIFL Premiership Manager of the Month", 0x9CFF18},
	{"NIFL Championship Team of the Week", 0x9CFF1C},
	{"NIFL Championship Player of the Year", 0x9CFF20},
	{"NIFL Championship Young Player of the Year", 0x9CFF24},
	{"NIFL Championship Top Goalscorer", 0x9CFF28},
	{"NIFL Championship Manager of the Year", 0x9CFF2C},
	{"NIFL Championship Manager of the Month", 0x9CFF30},
	{"Irish League Golden Boot", 0x9CFF34},
	{"Irish League Bronze Boot", 0x9CFF38},
	{"Belgian Challenger League Revelation of the Year", 0x9CFF3C},
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
	{"Finnish Ykkösliiga Player of the Month", 0x9CFF7C},
	{"Finnish Veikkausliiga Manager of the Month", 0x9CFF80},
	{"Finnish Ykkösliiga Manager of the Month", 0x9CFF84},
	{"Brazilian Série A Player of the Year", 0x9CFF88},
	{"Brazilian Série A Team of the Week", 0x9CFF8C},
	{"Brazilian Série A Team of the Year", 0x9CFF90},
	{"Brazilian Série A Top Goalscorer", 0x9CFF94},
	{"Brazilian Série A Young Player of the Year", 0x9CFF98},
	{"Brazilian Série B Player of the Year", 0x9CFF9C},
	{"Brazilian Série B Team of the Week", 0x9CFFA0},
	{"Brazilian Série B Team of the Year", 0x9CFFA4},
	{"Brazilian Série B Top Goalscorer", 0x9CFFA8},
	{"Brazilian Série B Young Player of the Year", 0x9CFFAC},
	{"Brazilian Série C Player of the Year", 0x9CFFB0},
	{"Brazilian Série C Team of the Week", 0x9CFFB4},
	{"Brazilian Série C Team of the Year", 0x9CFFB8},
	{"Brazilian Série C Top Goalscorer", 0x9CFFBC},
	{"Brazilian Série C Young Player of the Year", 0x9CFFC0},
	{"Campeonato Baiano Best Goalkeeper", 0x9CFFC4},
	{"Campeonato Baiano Best Player", 0x9CFFC8},
	{"Campeonato Baiano Team of the Week", 0x9CFFCC},
	{"Campeonato Baiano Top Goalscorer", 0x9CFFD0},
	{"Campeonato Central Best Goalkeeper", 0x9CFFD4},
	{"Campeonato Central Best Player", 0x9CFFD8},
	{"Campeonato Central Team of the Week", 0x9CFFDC},
	{"Campeonato Central Top Goalscorer", 0x9CFFE0},
	{"Campeonato Gaúcho Best Goalkeeper", 0x9CFFE4},
	{"Campeonato Gaúcho Best Player", 0x9CFFE8},
	{"Campeonato Gaúcho Team of the Week", 0x9CFFEC},
	{"Campeonato Gaúcho Top Goalscorer", 0x9CFFF0},
	{"Campeonato Goiano Best Goalkeeper", 0x9CFFF4},
	{"Campeonato Goiano Best Player", 0x9CFFF8},
	{"Campeonato Goiano Team of the Week", 0x9CFFFC},
	{"Campeonato Goiano Top Goalscorer", 0x9D0000},
	{"Campeonato Mineiro Best Goalkeeper", 0x9D0004},
	{"Campeonato Mineiro Best Player", 0x9D0008},
	{"Campeonato Mineiro Team of the Week", 0x9D000C},
	{"Campeonato Mineiro Top Goalscorer", 0x9D0010},
	{"Campeonato do Norte Best Goalkeeper", 0x9D0014},
	{"Campeonato do Norte Best Player", 0x9D0018},
	{"Campeonato do Norte Team of the Week", 0x9D001C},
	{"Campeonato do Norte Top Goalscorer", 0x9D0020},
	{"Campeonato do Nordeste Best Goalkeeper", 0x9D0024},
	{"Campeonato do Nordeste Best Player", 0x9D0028},
	{"Campeonato do Nordeste Team of the Week", 0x9D002C},
	{"Campeonato do Nordeste Top Goalscorer", 0x9D0030},
	{"Campeonato Paranaense Best Goalkeeper", 0x9D0034},
	{"Campeonato Paranaense Best Player", 0x9D0038},
	{"Campeonato Paranaense Team of the Week", 0x9D003C},
	{"Campeonato Paranaense Top Goalscorer", 0x9D0040},
	{"Campeonato Pernambucano Best Goalkeeper", 0x9D0044},
	{"Campeonato Pernambucano Best Player", 0x9D0048},
	{"Campeonato Pernambucano Team of the Week", 0x9D004C},
	{"Campeonato Pernambucano Top Goalscorer", 0x9D0050},
	{"Campeonato Carioca Best Goalkeeper", 0x9D0054},
	{"Campeonato Carioca Best Player", 0x9D0058},
	{"Campeonato Carioca Team of the Week", 0x9D005C},
	{"Campeonato Carioca Top Goalscorer", 0x9D0060},
	{"Campeonato Catarinense Best Goalkeeper", 0x9D0064},
	{"Campeonato Catarinense Best Player", 0x9D0068},
	{"Campeonato Catarinense Team of the Week", 0x9D006C},
	{"Campeonato Catarinense Top Goalscorer", 0x9D0070},
	{"Campeonato Paulista Best Goalkeeper", 0x9D0074},
	{"Campeonato Paulista Best Player", 0x9D0078},
	{"Campeonato Paulista Team of the Week", 0x9D007C},
	{"Campeonato Paulista Top Goalscorer", 0x9D0080},
	{"South Korean Best 11 of the Year", 0x9D0084},
	{"South Korean Manager of the Month", 0x9D0088},
	{"South Korean Manager of the Year", 0x9D008C},
	{"South Korean Most Assisted Player of the Year", 0x9D0090},
	{"South Korean Player of the Month", 0x9D0094},
	{"South Korean Player of the Year", 0x9D0098},
	{"South Korean Top Goal Scorer of the Year", 0x9D009C},
	{"South Korean Young Player of the Year", 0x9D00A0},
};

int setup_9cf_leagues(char* league_name, DWORD league_id) {
	// Fill out 9CF codes
	auto it = league_dword_match.find(string(league_name));
	if (it != league_dword_match.end()) {
		WriteDWORD(it->second, league_id);
	}
	return 1;
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

int setup_9cf_awards(char* award_name, DWORD award_id) {
	// Fill out 9CF codes
	auto it = award_dword_match.find(string(award_name));
	if (it != award_dword_match.end()) {
		WriteDWORD(it->second, award_id);
	}
	return 1;
}

// a bit ugly and lengthy but works with no issues
BYTE* check_if_reserve_team_new(cm3_clubs* to_check, DWORD* is_main_club, DWORD a3) {
	if (!to_check) return NULL;
	if (a3 != 0 && to_check->ClubHasLinkedClub == 0) return NULL;
	if (!to_check->ClubNation) return NULL;
	// Main teams check
	if (is_main_club) *is_main_club = 1;
	char* db_club_name = get_db_club_name(to_check);
	if (to_check->ClubNation->NationID == NATION_GERMANY_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_1860_MUNICH_9CF()) return (BYTE*)get_club(CLUB_1860_MUNICH_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AUGSBURG_9CF()) return (BYTE*)get_club(CLUB_AUGSBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BIELEFELD_9CF()) return (BYTE*)get_club(CLUB_BIELEFELD_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BOCHUM_9CF()) return (BYTE*)get_club(CLUB_BOCHUM_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DORTMUND_9CF()) return (BYTE*)get_club(CLUB_DORTMUND_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DUSSELDORF_9CF()) return (BYTE*)get_club(CLUB_DUSSELDORF_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FC_BAYERN_9CF()) return (BYTE*)get_club(CLUB_FC_BAYERN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FRANKFURT_9CF()) return (BYTE*)get_club(CLUB_FRANKFURT_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FREIBURG_9CF()) return (BYTE*)get_club(CLUB_FREIBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FURTH_9CF()) return (BYTE*)get_club(CLUB_FURTH_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HAMBURG_9CF()) return (BYTE*)get_club(CLUB_HAMBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HANNOVER_96_9CF()) return (BYTE*)get_club(CLUB_HANNOVER_96_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HERTHA_BSC_9CF()) return (BYTE*)get_club(CLUB_HERTHA_BSC_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HOFFENHEIM_9CF()) return (BYTE*)get_club(CLUB_HOFFENHEIM_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_INGOLSTADT_9CF()) return (BYTE*)get_club(CLUB_INGOLSTADT_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KAISERSLAUTERN_9CF()) return (BYTE*)get_club(CLUB_KAISERSLAUTERN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KARLSRUHE_9CF()) return (BYTE*)get_club(CLUB_KARLSRUHE_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KIEL_9CF()) return (BYTE*)get_club(CLUB_KIEL_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KOLN_9CF()) return (BYTE*)get_club(CLUB_KOLN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_M_GLADBACH_9CF()) return (BYTE*)get_club(CLUB_M_GLADBACH_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MAINZ_9CF()) return (BYTE*)get_club(CLUB_MAINZ_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NURNBERG_9CF()) return (BYTE*)get_club(CLUB_NURNBERG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PADERBORN_9CF()) return (BYTE*)get_club(CLUB_PADERBORN_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REGENSBURG_9CF()) return (BYTE*)get_club(CLUB_REGENSBURG_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROSTOCK_9CF()) return (BYTE*)get_club(CLUB_ROSTOCK_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SCHALKE_04_9CF()) return (BYTE*)get_club(CLUB_SCHALKE_04_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ST_PAULI_9CF()) return (BYTE*)get_club(CLUB_ST_PAULI_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STUTTGART_9CF()) return (BYTE*)get_club(CLUB_STUTTGART_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_UNTERHACHING_9CF()) return (BYTE*)get_club(CLUB_UNTERHACHING_II_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WERDER_BREMEN_9CF()) return (BYTE*)get_club(CLUB_WERDER_BREMEN_II_9CF());
		if (_strcmpi(db_club_name, "FC Energie Cottbus") == 0) { cm3_clubs* ret = find_club("FC Energie Cottbus II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "MSV Duisburg") == 0) { cm3_clubs* ret = find_club("MSV Duisburg Amateure"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Bayer 04 Leverkusen") == 0) { cm3_clubs* ret = find_club("Bayer Leverkusen (A)"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "1.FC Saarbrücken") == 0) { cm3_clubs* ret = find_club("1.FC Saarbrücken II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stuttgarter Kickers") == 0) { cm3_clubs* ret = find_club("Stuttgarter Kickers II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "VfL Wolfsburg") == 0) { cm3_clubs* ret = find_club("VfL Wolfsburg Amateure"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_SPAIN_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ALAVES_9CF()) return (BYTE*)get_club(CLUB_ALAVES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALBACETE_9CF()) return (BYTE*)get_club(CLUB_ALBACETE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALCORCON_9CF()) return (BYTE*)get_club(CLUB_ALCORCON_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALMERIA_9CF()) return (BYTE*)get_club(CLUB_ALMERIA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ATHLETIC_BILBAO_9CF()) return (BYTE*)get_club(CLUB_ATHLETIC_BILBAO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ATLETICO_MADRID_9CF()) return (BYTE*)get_club(CLUB_ATLETICO_MADRID_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BARCELONA_9CF()) return (BYTE*)get_club(CLUB_BARCELONA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BETIS_9CF()) return (BYTE*)get_club(CLUB_BETIS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BURGOS_9CF()) return (BYTE*)get_club(CLUB_BURGOS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CADIZ_9CF()) return (BYTE*)get_club(CLUB_CADIZ_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CARTAGENA_9CF()) return (BYTE*)get_club(CLUB_CARTAGENA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CASTELLON_9CF()) return (BYTE*)get_club(CLUB_CASTELLON_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CELTA_9CF()) return (BYTE*)get_club(CLUB_CELTA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CORDOBA_9CF()) return (BYTE*)get_club(CLUB_CORDOBA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CULTURAL_9CF()) return (BYTE*)get_club(CLUB_CULTURAL_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DEPORTIVO_9CF()) return (BYTE*)get_club(CLUB_DEPORTIVO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_EIBAR_9CF()) return (BYTE*)get_club(CLUB_EIBAR_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ELCHE_9CF()) return (BYTE*)get_club(CLUB_ELCHE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ESPANYOL_9CF()) return (BYTE*)get_club(CLUB_ESPANYOL_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GETAFE_9CF()) return (BYTE*)get_club(CLUB_GETAFE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GRANADA_9CF()) return (BYTE*)get_club(CLUB_GRANADA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HUESCA_9CF()) return (BYTE*)get_club(CLUB_HUESCA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LAS_PALMAS_9CF()) return (BYTE*)get_club(CLUB_LAS_PALMAS_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LEGANES_9CF()) return (BYTE*)get_club(CLUB_LEGANES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LEVANTE_9CF()) return (BYTE*)get_club(CLUB_LEVANTE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LOGRONES_9CF()) return (BYTE*)get_club(CLUB_LOGRONES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LUGO_9CF()) return (BYTE*)get_club(CLUB_LUGO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MALAGA_9CF()) return (BYTE*)get_club(CLUB_MALAGA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MALLORCA_9CF()) return (BYTE*)get_club(CLUB_MALLORCA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MURCIA_9CF()) return (BYTE*)get_club(CLUB_MURCIA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NUMANCIA_9CF()) return (BYTE*)get_club(CLUB_NUMANCIA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OSASUNA_9CF()) return (BYTE*)get_club(CLUB_OSASUNA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OVIEDO_9CF()) return (BYTE*)get_club(CLUB_OVIEDO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RACING_SANTANDER_9CF()) return (BYTE*)get_club(CLUB_RACING_SANTANDER_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RAYO_9CF()) return (BYTE*)get_club(CLUB_RAYO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REAL_MADRID_9CF()) return (BYTE*)get_club(CLUB_REAL_MADRID_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REAL_SOCIEDAD_9CF()) return (BYTE*)get_club(CLUB_REAL_SOCIEDAD_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RECREATIVO_9CF()) return (BYTE*)get_club(CLUB_RECREATIVO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SEVILLA_9CF()) return (BYTE*)get_club(CLUB_SEVILLA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPORTING_GIJON_9CF()) return (BYTE*)get_club(CLUB_SPORTING_GIJON_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TENERIFE_9CF()) return (BYTE*)get_club(CLUB_TENERIFE_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALENCIA_9CF()) return (BYTE*)get_club(CLUB_VALENCIA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALLADOLID_9CF()) return (BYTE*)get_club(CLUB_VALLADOLID_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VILLARREAL_9CF()) return (BYTE*)get_club(CLUB_VILLARREAL_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZARAGOZA_9CF()) return (BYTE*)get_club(CLUB_ZARAGOZA_B_9CF());
		if (_strcmpi(db_club_name, "Girona FC") == 0) { cm3_clubs* ret = find_club("Girona FC B"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_PORTUGAL_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ALVERCA_9CF()) return (BYTE*)get_club(CLUB_ALVERCA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BENFICA_9CF()) return (BYTE*)get_club(CLUB_BENFICA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BRAGA_9CF()) return (BYTE*)get_club(CLUB_BRAGA_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CHAVES_9CF()) return (BYTE*)get_club(CLUB_CHAVES_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MARITIMO_9CF()) return (BYTE*)get_club(CLUB_MARITIMO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PORTO_9CF()) return (BYTE*)get_club(CLUB_PORTO_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPORTING_CP_9CF()) return (BYTE*)get_club(CLUB_SPORTING_CP_B_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VIT_GUIMARAES_9CF()) return (BYTE*)get_club(CLUB_VIT_GUIMARAES_B_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_NORWAY_9CF()) {
		if (_strcmpi(db_club_name, "Aalesunds FK") == 0) { cm3_clubs* ret = find_club("Aalesunds FK II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Bærum SK") == 0) { cm3_clubs* ret = find_club("Baerum SK 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Bodø/Glimt") == 0) { cm3_clubs* ret = find_club("FK Bodø/Glimt B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Brann") == 0) { cm3_clubs* ret = find_club("SK Brann 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Bryne FK") == 0) { cm3_clubs* ret = find_club("Bryne FK 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Byåsen TF") == 0) { cm3_clubs* ret = find_club("Byasen Trondheim II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Follo FK") == 0) { cm3_clubs* ret = find_club("Follo FK 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Fredrikstad FK") == 0) { cm3_clubs* ret = find_club("Fredrikstad FK 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Fyllingsdalen") == 0) { cm3_clubs* ret = find_club("Fyllingsdalen FK 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Gjøvik-Lyn") == 0) { cm3_clubs* ret = find_club("SK Gjøvik-Lyn 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Grorud IL") == 0) { cm3_clubs* ret = find_club("Grorud IL 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Hamarkameratene") == 0) { cm3_clubs* ret = find_club("Hamarkameratene 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Haugesund") == 0) { cm3_clubs* ret = find_club("FK Haugesund 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "IL Hødd") == 0) { cm3_clubs* ret = find_club("IL Hødd 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Hønefoss BK") == 0) { cm3_clubs* ret = find_club("Hønefoss BK 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Kjelsås IL") == 0) { cm3_clubs* ret = find_club("Kjelsas IL 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Kongsvinger IL") == 0) { cm3_clubs* ret = find_club("Kongsvinger IL II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Kristiansund BK") == 0) { cm3_clubs* ret = find_club("Kristiansund BK 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Lillestrøm SK") == 0) { cm3_clubs* ret = find_club("Lilleström SK 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Mjøndalen IF") == 0) { cm3_clubs* ret = find_club("Mjøndalen IF 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Molde FK") == 0) { cm3_clubs* ret = find_club("Molde FK II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Nardo FK") == 0) { cm3_clubs* ret = find_club("Nardo FK 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Odds BK") == 0) { cm3_clubs* ret = find_club("Odds BK II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Pors Fotball") == 0) { cm3_clubs* ret = find_club("Pors Fotball II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Ranheim IL") == 0) { cm3_clubs* ret = find_club("Ranheim 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Raufoss IL") == 0) { cm3_clubs* ret = find_club("Raufoss IL 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rosenborg BK") == 0) { cm3_clubs* ret = find_club("Rosenborg BK II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sandefjord Fotball") == 0) { cm3_clubs* ret = find_club("Sandefjord Fotball 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sandnes Ulf") == 0) { cm3_clubs* ret = find_club("Sandnes Ulf 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sarpsborg 08 FF") == 0) { cm3_clubs* ret = find_club("Sarpsborg 08 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Skeid Oslo") == 0) { cm3_clubs* ret = find_club("Skeid Oslo II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sogndal IL") == 0) { cm3_clubs* ret = find_club("Sogndal IL II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stabæk Fotball") == 0) { cm3_clubs* ret = find_club("Stabaek IF II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "IK Start") == 0) { cm3_clubs* ret = find_club("IK Start 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Strømmen IF") == 0) { cm3_clubs* ret = find_club("Strømmen IL 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Strømsgodset IF") == 0) { cm3_clubs* ret = find_club("Strømsgodset IF II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Tromsø IL") == 0) { cm3_clubs* ret = find_club("Tromsø IL II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Træff") == 0) { cm3_clubs* ret = find_club("SK Træff 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Ullensaker/Kisa IL") == 0) { cm3_clubs* ret = find_club("Ullensaker/Kisa IL 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Vard Haugesund") == 0) { cm3_clubs* ret = find_club("SK Vard Haugesund 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Viking FK") == 0) { cm3_clubs* ret = find_club("Viking FK II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Vålerenga Fotball Elite") == 0) { cm3_clubs* ret = find_club("Vålerenga Fotball II"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_FINLAND_9CF()) {
		if (_strcmpi(db_club_name, "HJK Helsinki") == 0) { cm3_clubs* ret = find_club("HJK Klubi 04 Helsinki"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Espoo") == 0) { cm3_clubs* ret = find_club("FC Espoo II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Helsinki IFK") == 0) { cm3_clubs* ret = find_club("Helsinki IFK II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Honka") == 0) { cm3_clubs* ret = find_club("FC Honka II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Ilves Tampere") == 0) { cm3_clubs* ret = find_club("Ilves Tampere II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Kuopion Palloseura") == 0) { cm3_clubs* ret = find_club("Kuopion Palloseura II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rovaniemen Palloseura") == 0) { cm3_clubs* ret = find_club("Rovaniemen Palloseura II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Vaasan Palloseura") == 0) { cm3_clubs* ret = find_club("Vaasan Palloseura II"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_POLAND_9CF()) {
		if (_strcmpi(db_club_name, "Chrobry Glogow") == 0) { cm3_clubs* ret = find_club("Chrobry Glogow II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Cracovia") == 0) { cm3_clubs* ret = find_club("Cracovia II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Górnik Zabrze") == 0) { cm3_clubs* ret = find_club("Gornik Zabrze II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Jagiellonia Bialystok") == 0) { cm3_clubs* ret = find_club("Jagiellonia Bialystok II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Korona Kielce") == 0) { cm3_clubs* ret = find_club("Korona Kielce II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Lech Poznan") == 0) { cm3_clubs* ret = find_club("Lech Poznan II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Legia Warszawa") == 0) { cm3_clubs* ret = find_club("Legia Warsaw II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "LKS Lodz") == 0) { cm3_clubs* ret = find_club("LKS Lodz II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Miedz Legnica") == 0) { cm3_clubs* ret = find_club("Miedz Legnica II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Piast Gliwice") == 0) { cm3_clubs* ret = find_club("Piast Gliwice II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Pogon Szczecin") == 0) { cm3_clubs* ret = find_club("Pogon Szczecin II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Raków Czestochowa") == 0) { cm3_clubs* ret = find_club("Rakow Czestochowa II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Slask Wroclaw") == 0) { cm3_clubs* ret = find_club("Slask Wroclaw II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Widzew Lodz") == 0) { cm3_clubs* ret = find_club("Widzew Lodz II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Wisla Kraków") == 0) { cm3_clubs* ret = find_club("Wisla Krakow II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Wisla Plock") == 0) { cm3_clubs* ret = find_club("Wisla Plock II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Zaglebie Lubin") == 0) { cm3_clubs* ret = find_club("Zaglebie Lubin II"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_SCOTLAND_9CF()) {
		if (_strcmpi(db_club_name, "Glasgow Celtic") == 0) { cm3_clubs* ret = find_club("Glasgow Celtic B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Heart of Midlothian FC") == 0) { cm3_clubs* ret = find_club("Heart of Midlothian FC B"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_GREECE_9CF()) {
		if (_strcmpi(db_club_name, "Asteras Aktor") == 0) { cm3_clubs* ret = find_club("Asteras Aktor B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AEK Athens") == 0) { cm3_clubs* ret = find_club("AEK Athens B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Olympiacos Piraeus") == 0) { cm3_clubs* ret = find_club("Olympiacos Piraeus B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "PAOK Thessaloniki") == 0) { cm3_clubs* ret = find_club("PAOK Thessaloniki B"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_HOLLAND_9CF()) {
		if (_strcmpi(db_club_name, "AZ") == 0) { cm3_clubs* ret = find_club("AZ Alkmaar U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Ajax Amsterdam") == 0) { cm3_clubs* ret = find_club("Ajax Amsterdam U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Almere City FC") == 0) { cm3_clubs* ret = find_club("Jong Almere City FC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "PSV Eindhoven") == 0) { cm3_clubs* ret = find_club("PSV Eindhoven U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sparta Rotterdam") == 0) { cm3_clubs* ret = find_club("Sparta Rotterdam U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Utrecht") == 0) { cm3_clubs* ret = find_club("FC Utrecht U21"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_BELGIUM_9CF()) {
		if (_strcmpi(db_club_name, "RSC Anderlecht") == 0) { cm3_clubs* ret = find_club("RSC Anderlecht B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Royal Antwerp FC") == 0) { cm3_clubs* ret = find_club("Royal Antwerp FC B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Beerschot VA") == 0) { cm3_clubs* ret = find_club("Beerschot VA U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Cercle Brugge") == 0) { cm3_clubs* ret = find_club("Cercle Brugge B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Royal Charleroi SC") == 0) { cm3_clubs* ret = find_club("RSC Charleroi B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Club Brugge KV") == 0) { cm3_clubs* ret = find_club("Club Brugge KV II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "KAS Eupen") == 0) { cm3_clubs* ret = find_club("KAS Eupen U23"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "KRC Genk") == 0) { cm3_clubs* ret = find_club("KRC Genk B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "KAA Gent") == 0) { cm3_clubs* ret = find_club("KAA Gent B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "KV Mechelen") == 0) { cm3_clubs* ret = find_club("KV Mechelen U23"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Oud-Heverlee Leuven") == 0) { cm3_clubs* ret = find_club("Oud-Heverlee Leuven U23"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sint-Truidense VV") == 0) { cm3_clubs* ret = find_club("STVV Youth"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Standard Liège") == 0) { cm3_clubs* ret = find_club("Standard de Liège 16 FC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Union Saint-Gilloise") == 0) { cm3_clubs* ret = find_club("Union Saint-Gilloise U23"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Zulte Waregem") == 0) { cm3_clubs* ret = find_club("Zulte-Waregem B"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_RUSSIA_9CF()) {
		if (_strcmpi(db_club_name, "Akron Togliatti") == 0) { cm3_clubs* ret = find_club("Akron-2 Togliatti"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Alania Vladikavkaz") == 0) { cm3_clubs* ret = find_club("Alania-2 Vladikavkaz"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Arsenal Tula") == 0) { cm3_clubs* ret = find_club("Arsenal-2 Tula"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Baltika Kaliningrad") == 0) { cm3_clubs* ret = find_club("Baltika-2 Kaliningrad"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Chertanovo Moscow") == 0) { cm3_clubs* ret = find_club("Chertanovo Moskau II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "CSKA Moscow") == 0) { cm3_clubs* ret = find_club("CSKA Moscow II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Dinamo Makhachkala") == 0) { cm3_clubs* ret = find_club("Dinamo-2 Makhachkala"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Dynamo Moscow") == 0) { cm3_clubs* ret = find_club("Dynamo 2 Moscow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Enisey Krasnoyarsk") == 0) { cm3_clubs* ret = find_club("Enisey 2 Krasnoyarsk"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Fakel Voronezh") == 0) { cm3_clubs* ret = find_club("Fakel-M Voronezh"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Khimki") == 0) { cm3_clubs* ret = find_club("FC Khimki 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Orenburg") == 0) { cm3_clubs* ret = find_club("FC Orenburg-2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Rostov") == 0) { cm3_clubs* ret = find_club("FC Rostov 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Ufa") == 0) { cm3_clubs* ret = find_club("FK Ufa 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Kosmos Dolgoprudnyi") == 0) { cm3_clubs* ret = find_club("Kosmos-2 Dolgoprudnyi"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Lokomotiv Moscow") == 0) { cm3_clubs* ret = find_club("Lokomotiv-Kazanka Moskow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rodina Moscow") == 0) { cm3_clubs* ret = find_club("Rodina 2 Moscow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rotor Volgograd") == 0) { cm3_clubs* ret = find_club("Rotor 2 Volgograd"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rubin Kazan") == 0) { cm3_clubs* ret = find_club("Rubin 2 Kazan"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SKA Khabarovsk") == 0) { cm3_clubs* ret = find_club("SKA Khabarovsk 2"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Spartak Moscow") == 0) { cm3_clubs* ret = find_club("Spartak 2 Moscow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Torpedo Moscow") == 0) { cm3_clubs* ret = find_club("Torpedo 2 Moskau"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Ural Yekaterinburg") == 0) { cm3_clubs* ret = find_club("Ural 2 Ekaterinburg"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Zenit St. Petersburg") == 0) { cm3_clubs* ret = find_club("Zenit 2 St. Petersburg"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_CZECH_REPUBLIC_9CF()) {
		if (_strcmpi(db_club_name, "1.FC Slovacko") == 0) { cm3_clubs* ret = find_club("1.FC Slovacko B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AC Sparta Prague") == 0) { cm3_clubs* ret = find_club("AC Sparta Prague B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Bohemians Prague 1905") == 0) { cm3_clubs* ret = find_club("Bohemians Prague 1905 B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Banik Ostrava") == 0) { cm3_clubs* ret = find_club("FC Banik Ostrava B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Hradec Kralove") == 0) { cm3_clubs* ret = find_club("FC Hradec Kralove B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC SILON Taborsko") == 0) { cm3_clubs* ret = find_club("FC SILON Taborsko B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Slovan Liberec") == 0) { cm3_clubs* ret = find_club("FC Slovan Liberec B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Viktoria Plzen") == 0) { cm3_clubs* ret = find_club("FC Viktoria Plzen B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Zlin") == 0) { cm3_clubs* ret = find_club("FC Zlin B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Dukla Prague") == 0) { cm3_clubs* ret = find_club("FK Dukla Prague B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Jablonec") == 0) { cm3_clubs* ret = find_club("FK Jablonec B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Mlada Boleslav") == 0) { cm3_clubs* ret = find_club("FK Mlada Boleslav B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Pardubice") == 0) { cm3_clubs* ret = find_club("FK Pardubice B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Pribram") == 0) { cm3_clubs* ret = find_club("1.FK Pribram B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Teplice") == 0) { cm3_clubs* ret = find_club("FK Teplice B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "MFK Karvina") == 0) { cm3_clubs* ret = find_club("MFK Karvina B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Dynamo Ceske Budejovice") == 0) { cm3_clubs* ret = find_club("SK Dynamo Ceske Budejovice B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Sigma Olomouc") == 0) { cm3_clubs* ret = find_club("SK Sigma Olomouc B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Slavia Prague") == 0) { cm3_clubs* ret = find_club("SK Slavia Prague B"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_AUSTRIA_9CF()) {
		if (_strcmpi(db_club_name, "Admira Wacker") == 0) { cm3_clubs* ret = find_club("Admira Wacker Panthers"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Austria Vienna") == 0) { cm3_clubs* ret = find_club("Young Violets Austria Wien"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "LASK Linz") == 0) { cm3_clubs* ret = find_club("LASK Amateure OÖ"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rapid Vienna") == 0) { cm3_clubs* ret = find_club("Rapid Vienna II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Red Bull Salzburg") == 0) { cm3_clubs* ret = find_club("FC Liefering"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SC Austria Lustenau") == 0) { cm3_clubs* ret = find_club("SC Austria Lustenau II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SCR Altach") == 0) { cm3_clubs* ret = find_club("SCR Altach Juniors"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Sturm Graz") == 0) { cm3_clubs* ret = find_club("SK Sturm Graz II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SKN St. Pölten") == 0) { cm3_clubs* ret = find_club("SKN St. Pölten Juniors"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SV Ried") == 0) { cm3_clubs* ret = find_club("SV Ried II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Wolfsberger AC") == 0) { cm3_clubs* ret = find_club("Wolfsberger AC II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "WSG Tirol") == 0) { cm3_clubs* ret = find_club("WSG Tirol II"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_SWITZERLAND_9CF()) {
		if (_strcmpi(db_club_name, "BSC Young Boys") == 0) { cm3_clubs* ret = find_club("BSC Young Boys U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Basel 1893") == 0) { cm3_clubs* ret = find_club("FC Basel 1893 U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Lausanne-Sport") == 0) { cm3_clubs* ret = find_club("FC Lausanne-Sport II "); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Lugano") == 0) { cm3_clubs* ret = find_club("FC Lugano II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Luzern") == 0) { cm3_clubs* ret = find_club("FC Luzern U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sion") == 0) { cm3_clubs* ret = find_club("FC Sion U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC St. Gallen 1879") == 0) { cm3_clubs* ret = find_club("FC St. Gallen 1879 U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Winterthur") == 0) { cm3_clubs* ret = find_club("FC Winterthur U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Zürich") == 0) { cm3_clubs* ret = find_club("FC Zürich U21"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Servette FC") == 0) { cm3_clubs* ret = find_club("Servette FC U21"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_FRANCE_9CF()) {
		if (_strcmpi(db_club_name, "AC Ajaccio") == 0) { cm3_clubs* ret = find_club("AC Ajaccio B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Le Havre AC") == 0) { cm3_clubs* ret = find_club("AC Le Havre B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AJ Auxerre") == 0) { cm3_clubs* ret = find_club("AJ Auxerre B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Amiens SC") == 0) { cm3_clubs* ret = find_club("Amiens SC B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Angers SCO") == 0) { cm3_clubs* ret = find_club("Angers SCO B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AS Monaco") == 0) { cm3_clubs* ret = find_club("AS Monaco B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AS Nancy-Lorraine") == 0) { cm3_clubs* ret = find_club("AS Nancy-Lorraine B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AS Saint-Étienne") == 0) { cm3_clubs* ret = find_club("AS Saint-Étienne B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Bourges Foot 18") == 0) { cm3_clubs* ret = find_club("Bourges Foot 18 B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "C'Chartres Football") == 0) { cm3_clubs* ret = find_club("C'Chartres Football B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Clermont Foot 63") == 0) { cm3_clubs* ret = find_club("Clermont Foot 63 B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "CS Sedan-Ardennes") == 0) { cm3_clubs* ret = find_club("CS Sedan-Ardennes B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Dijon FCO") == 0) { cm3_clubs* ret = find_club("Dijon FCO B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "EA Guingamp") == 0) { cm3_clubs* ret = find_club("EA Guingamp B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "ESTAC Troyes") == 0) { cm3_clubs* ret = find_club("ESTAC Troyes B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Chamois Niortais FC") == 0) { cm3_clubs* ret = find_club("FC Chamois Niort B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Girondins Bordeaux") == 0) { cm3_clubs* ret = find_club("FC Girondins Bordeaux B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Le Mans FC") == 0) { cm3_clubs* ret = find_club("FC Le Mans B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Lorient") == 0) { cm3_clubs* ret = find_club("FC Lorient B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Metz") == 0) { cm3_clubs* ret = find_club("FC Metz B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Nantes") == 0) { cm3_clubs* ret = find_club("FC Nantes B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Sochaux-Montbéliard") == 0) { cm3_clubs* ret = find_club("FC Sochaux-Montbéliard B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "LB Châteauroux") == 0) { cm3_clubs* ret = find_club("LB Châteauroux B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Le Puy Foot 43 Auvergne") == 0) { cm3_clubs* ret = find_club("Le Puy Foot 43 Auvergne B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Les Herbiers VF") == 0) { cm3_clubs* ret = find_club("Les Herbiers VF B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "LOSC Lille") == 0) { cm3_clubs* ret = find_club("LOSC Lille B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Lyon - La Duchère") == 0) { cm3_clubs* ret = find_club("Lyon - La Duchère B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Marignane-Gignac-Côte-Bleue FC") == 0) { cm3_clubs* ret = find_club("Marignane-Gignac-Côte Bleue FC B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Montpellier HSC") == 0) { cm3_clubs* ret = find_club("Montpellier HSC B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "OGC Nice") == 0) { cm3_clubs* ret = find_club("OGC Nice B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Olympique Marseille") == 0) { cm3_clubs* ret = find_club("Olympique de Marseille B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Olympique Lyon") == 0) { cm3_clubs* ret = find_club("Olympique Lyon B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Paris FC") == 0) { cm3_clubs* ret = find_club("Paris FC B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Paris Saint-Germain") == 0) { cm3_clubs* ret = find_club("Paris Saint-Germain B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Pau FC") == 0) { cm3_clubs* ret = find_club("Pau FC B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Quevilly - Rouen Métropole") == 0) { cm3_clubs* ret = find_club("Quevilly - Rouen Métropole B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "RC Strasbourg Alsace") == 0) { cm3_clubs* ret = find_club("Racing Strasbourg B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "RC Lens") == 0) { cm3_clubs* ret = find_club("RC Lens B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rodez AF") == 0) { cm3_clubs* ret = find_club("Rodez Aveyron Football B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SC Bastia") == 0) { cm3_clubs* ret = find_club("SC Bastia B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SM Caen") == 0) { cm3_clubs* ret = find_club("SM Caen B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stade Brestois 29") == 0) { cm3_clubs* ret = find_club("Stade Brest 29 B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stade Briochin") == 0) { cm3_clubs* ret = find_club("Stade Briochin B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stade Lavallois") == 0) { cm3_clubs* ret = find_club("Stade Laval B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stade Reims") == 0) { cm3_clubs* ret = find_club("Stade Reims B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stade Rennais FC") == 0) { cm3_clubs* ret = find_club("Stade Rennais FC B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Toulouse") == 0) { cm3_clubs* ret = find_club("Toulouse FC B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "US Avranches") == 0) { cm3_clubs* ret = find_club("US Avranches B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "US Boulogne") == 0) { cm3_clubs* ret = find_club("US Boulogne II"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "US Orléans") == 0) { cm3_clubs* ret = find_club("US Orléans B"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Valenciennes FC") == 0) { cm3_clubs* ret = find_club("Valenciennes FC B"); if (ret) return (BYTE*)ret; }
	}

	// Reserve teams check
	if (is_main_club) *is_main_club = 0;
	if (to_check->ClubNation->NationID == NATION_GERMANY_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_1860_MUNICH_II_9CF()) return (BYTE*)get_club(CLUB_1860_MUNICH_9CF());
		if ((DWORD)to_check->ClubID == CLUB_AUGSBURG_II_9CF()) return (BYTE*)get_club(CLUB_AUGSBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BIELEFELD_II_9CF()) return (BYTE*)get_club(CLUB_BIELEFELD_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BOCHUM_II_9CF()) return (BYTE*)get_club(CLUB_BOCHUM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DORTMUND_II_9CF()) return (BYTE*)get_club(CLUB_DORTMUND_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DUSSELDORF_II_9CF()) return (BYTE*)get_club(CLUB_DUSSELDORF_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FC_BAYERN_II_9CF()) return (BYTE*)get_club(CLUB_FC_BAYERN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FRANKFURT_II_9CF()) return (BYTE*)get_club(CLUB_FRANKFURT_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FREIBURG_II_9CF()) return (BYTE*)get_club(CLUB_FREIBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_FURTH_II_9CF()) return (BYTE*)get_club(CLUB_FURTH_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HAMBURG_II_9CF()) return (BYTE*)get_club(CLUB_HAMBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HANNOVER_96_II_9CF()) return (BYTE*)get_club(CLUB_HANNOVER_96_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HERTHA_BSC_II_9CF()) return (BYTE*)get_club(CLUB_HERTHA_BSC_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HOFFENHEIM_II_9CF()) return (BYTE*)get_club(CLUB_HOFFENHEIM_9CF());
		if ((DWORD)to_check->ClubID == CLUB_INGOLSTADT_II_9CF()) return (BYTE*)get_club(CLUB_INGOLSTADT_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KAISERSLAUTERN_II_9CF()) return (BYTE*)get_club(CLUB_KAISERSLAUTERN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KARLSRUHE_II_9CF()) return (BYTE*)get_club(CLUB_KARLSRUHE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KIEL_II_9CF()) return (BYTE*)get_club(CLUB_KIEL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_KOLN_II_9CF()) return (BYTE*)get_club(CLUB_KOLN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_M_GLADBACH_II_9CF()) return (BYTE*)get_club(CLUB_M_GLADBACH_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MAINZ_II_9CF()) return (BYTE*)get_club(CLUB_MAINZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NURNBERG_II_9CF()) return (BYTE*)get_club(CLUB_NURNBERG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PADERBORN_II_9CF()) return (BYTE*)get_club(CLUB_PADERBORN_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REGENSBURG_II_9CF()) return (BYTE*)get_club(CLUB_REGENSBURG_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ROSTOCK_II_9CF()) return (BYTE*)get_club(CLUB_ROSTOCK_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SCHALKE_04_II_9CF()) return (BYTE*)get_club(CLUB_SCHALKE_04_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ST_PAULI_II_9CF()) return (BYTE*)get_club(CLUB_ST_PAULI_9CF());
		if ((DWORD)to_check->ClubID == CLUB_STUTTGART_II_9CF()) return (BYTE*)get_club(CLUB_STUTTGART_9CF());
		if ((DWORD)to_check->ClubID == CLUB_UNTERHACHING_II_9CF()) return (BYTE*)get_club(CLUB_UNTERHACHING_9CF());
		if ((DWORD)to_check->ClubID == CLUB_WERDER_BREMEN_II_9CF()) return (BYTE*)get_club(CLUB_WERDER_BREMEN_9CF());
		if (_strcmpi(db_club_name, "FC Energie Cottbus II") == 0) { cm3_clubs* ret = find_club("FC Energie Cottbus"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "MSV Duisburg Amateure") == 0) { cm3_clubs* ret = find_club("MSV Duisburg"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Bayer Leverkusen (A)") == 0) { cm3_clubs* ret = find_club("Bayer 04 Leverkusen"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "1.FC Saarbrücken II") == 0) { cm3_clubs* ret = find_club("1.FC Saarbrücken"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stuttgarter Kickers II") == 0) { cm3_clubs* ret = find_club("Stuttgarter Kickers"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "VfL Wolfsburg Amateure") == 0) { cm3_clubs* ret = find_club("VfL Wolfsburg"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_SPAIN_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ALAVES_B_9CF()) return (BYTE*)get_club(CLUB_ALAVES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALBACETE_B_9CF()) return (BYTE*)get_club(CLUB_ALBACETE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALCORCON_B_9CF()) return (BYTE*)get_club(CLUB_ALCORCON_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ALMERIA_B_9CF()) return (BYTE*)get_club(CLUB_ALMERIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ATHLETIC_BILBAO_B_9CF()) return (BYTE*)get_club(CLUB_ATHLETIC_BILBAO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ATLETICO_MADRID_B_9CF()) return (BYTE*)get_club(CLUB_ATLETICO_MADRID_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BARCELONA_B_9CF()) return (BYTE*)get_club(CLUB_BARCELONA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BETIS_B_9CF()) return (BYTE*)get_club(CLUB_BETIS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BURGOS_B_9CF()) return (BYTE*)get_club(CLUB_BURGOS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CADIZ_B_9CF()) return (BYTE*)get_club(CLUB_CADIZ_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CARTAGENA_B_9CF()) return (BYTE*)get_club(CLUB_CARTAGENA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CASTELLON_B_9CF()) return (BYTE*)get_club(CLUB_CASTELLON_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CELTA_B_9CF()) return (BYTE*)get_club(CLUB_CELTA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CORDOBA_B_9CF()) return (BYTE*)get_club(CLUB_CORDOBA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CULTURAL_B_9CF()) return (BYTE*)get_club(CLUB_CULTURAL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_DEPORTIVO_B_9CF()) return (BYTE*)get_club(CLUB_DEPORTIVO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_EIBAR_B_9CF()) return (BYTE*)get_club(CLUB_EIBAR_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ELCHE_B_9CF()) return (BYTE*)get_club(CLUB_ELCHE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ESPANYOL_B_9CF()) return (BYTE*)get_club(CLUB_ESPANYOL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GETAFE_B_9CF()) return (BYTE*)get_club(CLUB_GETAFE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_GRANADA_B_9CF()) return (BYTE*)get_club(CLUB_GRANADA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_HUESCA_B_9CF()) return (BYTE*)get_club(CLUB_HUESCA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LAS_PALMAS_B_9CF()) return (BYTE*)get_club(CLUB_LAS_PALMAS_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LEGANES_B_9CF()) return (BYTE*)get_club(CLUB_LEGANES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LEVANTE_B_9CF()) return (BYTE*)get_club(CLUB_LEVANTE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LOGRONES_B_9CF()) return (BYTE*)get_club(CLUB_LOGRONES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_LUGO_B_9CF()) return (BYTE*)get_club(CLUB_LUGO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MALAGA_B_9CF()) return (BYTE*)get_club(CLUB_MALAGA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MALLORCA_B_9CF()) return (BYTE*)get_club(CLUB_MALLORCA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MURCIA_B_9CF()) return (BYTE*)get_club(CLUB_MURCIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_NUMANCIA_B_9CF()) return (BYTE*)get_club(CLUB_NUMANCIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OSASUNA_B_9CF()) return (BYTE*)get_club(CLUB_OSASUNA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_OVIEDO_B_9CF()) return (BYTE*)get_club(CLUB_OVIEDO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RACING_SANTANDER_B_9CF()) return (BYTE*)get_club(CLUB_RACING_SANTANDER_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RAYO_B_9CF()) return (BYTE*)get_club(CLUB_RAYO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REAL_MADRID_B_9CF()) return (BYTE*)get_club(CLUB_REAL_MADRID_9CF());
		if ((DWORD)to_check->ClubID == CLUB_REAL_SOCIEDAD_B_9CF()) return (BYTE*)get_club(CLUB_REAL_SOCIEDAD_9CF());
		if ((DWORD)to_check->ClubID == CLUB_RECREATIVO_B_9CF()) return (BYTE*)get_club(CLUB_RECREATIVO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SEVILLA_B_9CF()) return (BYTE*)get_club(CLUB_SEVILLA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPORTING_GIJON_B_9CF()) return (BYTE*)get_club(CLUB_SPORTING_GIJON_9CF());
		if ((DWORD)to_check->ClubID == CLUB_TENERIFE_B_9CF()) return (BYTE*)get_club(CLUB_TENERIFE_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALENCIA_B_9CF()) return (BYTE*)get_club(CLUB_VALENCIA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VALLADOLID_B_9CF()) return (BYTE*)get_club(CLUB_VALLADOLID_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VILLARREAL_B_9CF()) return (BYTE*)get_club(CLUB_VILLARREAL_9CF());
		if ((DWORD)to_check->ClubID == CLUB_ZARAGOZA_B_9CF()) return (BYTE*)get_club(CLUB_ZARAGOZA_9CF());
		if (_strcmpi(db_club_name, "Girona FC B") == 0) { cm3_clubs* ret = find_club("Girona FC"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_PORTUGAL_9CF()) {
		if ((DWORD)to_check->ClubID == CLUB_ALVERCA_B_9CF()) return (BYTE*)get_club(CLUB_ALVERCA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BENFICA_B_9CF()) return (BYTE*)get_club(CLUB_BENFICA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_BRAGA_B_9CF()) return (BYTE*)get_club(CLUB_BRAGA_9CF());
		if ((DWORD)to_check->ClubID == CLUB_CHAVES_B_9CF()) return (BYTE*)get_club(CLUB_CHAVES_9CF());
		if ((DWORD)to_check->ClubID == CLUB_MARITIMO_B_9CF()) return (BYTE*)get_club(CLUB_MARITIMO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_PORTO_B_9CF()) return (BYTE*)get_club(CLUB_PORTO_9CF());
		if ((DWORD)to_check->ClubID == CLUB_SPORTING_CP_B_9CF()) return (BYTE*)get_club(CLUB_SPORTING_CP_9CF());
		if ((DWORD)to_check->ClubID == CLUB_VIT_GUIMARAES_B_9CF()) return (BYTE*)get_club(CLUB_VIT_GUIMARAES_9CF());
	}
	else if (to_check->ClubNation->NationID == NATION_NORWAY_9CF()) {
		if (_strcmpi(db_club_name, "Aalesunds FK II") == 0) { cm3_clubs* ret = find_club("Aalesunds FK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Baerum SK 2") == 0) { cm3_clubs* ret = find_club("Bærum SK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Bodø/Glimt B") == 0) { cm3_clubs* ret = find_club("FK Bodø/Glimt"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Brann 2") == 0) { cm3_clubs* ret = find_club("SK Brann"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Bryne FK 2") == 0) { cm3_clubs* ret = find_club("Bryne FK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Byasen Trondheim II") == 0) { cm3_clubs* ret = find_club("Byåsen TF"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Follo FK 2") == 0) { cm3_clubs* ret = find_club("Follo FK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Fredrikstad FK 2") == 0) { cm3_clubs* ret = find_club("Fredrikstad FK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Fyllingsdalen FK 2") == 0) { cm3_clubs* ret = find_club("FK Fyllingsdalen"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Gjøvik-Lyn 2") == 0) { cm3_clubs* ret = find_club("SK Gjøvik-Lyn"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Grorud IL 2") == 0) { cm3_clubs* ret = find_club("Grorud IL"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Hamarkameratene 2") == 0) { cm3_clubs* ret = find_club("Hamarkameratene"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Haugesund 2") == 0) { cm3_clubs* ret = find_club("FK Haugesund"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "IL Hødd 2") == 0) { cm3_clubs* ret = find_club("IL Hødd"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Hønefoss BK 2") == 0) { cm3_clubs* ret = find_club("Hønefoss BK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Kjelsas IL 2") == 0) { cm3_clubs* ret = find_club("Kjelsås IL"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Kongsvinger IL II") == 0) { cm3_clubs* ret = find_club("Kongsvinger IL"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Kristiansund BK 2") == 0) { cm3_clubs* ret = find_club("Kristiansund BK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Lilleström SK 2") == 0) { cm3_clubs* ret = find_club("Lillestrøm SK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Mjøndalen IF 2") == 0) { cm3_clubs* ret = find_club("Mjøndalen IF"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Molde FK II") == 0) { cm3_clubs* ret = find_club("Molde FK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Nardo FK 2") == 0) { cm3_clubs* ret = find_club("Nardo FK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Odds BK II") == 0) { cm3_clubs* ret = find_club("Odds BK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Pors Fotball II") == 0) { cm3_clubs* ret = find_club("Pors Fotball"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Ranheim 2") == 0) { cm3_clubs* ret = find_club("Ranheim IL"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Raufoss IL 2") == 0) { cm3_clubs* ret = find_club("Raufoss IL"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rosenborg BK II") == 0) { cm3_clubs* ret = find_club("Rosenborg BK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sandefjord Fotball 2") == 0) { cm3_clubs* ret = find_club("Sandefjord Fotball"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sandnes Ulf 2") == 0) { cm3_clubs* ret = find_club("Sandnes Ulf"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sarpsborg 08 2") == 0) { cm3_clubs* ret = find_club("Sarpsborg 08 FF"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Skeid Oslo II") == 0) { cm3_clubs* ret = find_club("Skeid Oslo"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sogndal IL II") == 0) { cm3_clubs* ret = find_club("Sogndal IL"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stabaek IF II") == 0) { cm3_clubs* ret = find_club("Stabæk Fotball"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "IK Start 2") == 0) { cm3_clubs* ret = find_club("IK Start"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Strømmen IL 2") == 0) { cm3_clubs* ret = find_club("Strømmen IF"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Strømsgodset IF II") == 0) { cm3_clubs* ret = find_club("Strømsgodset IF"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Tromsø IL II") == 0) { cm3_clubs* ret = find_club("Tromsø IL"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Træff 2") == 0) { cm3_clubs* ret = find_club("SK Træff"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Ullensaker/Kisa IL 2") == 0) { cm3_clubs* ret = find_club("Ullensaker/Kisa IL"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Vard Haugesund 2") == 0) { cm3_clubs* ret = find_club("SK Vard Haugesund"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Viking FK II") == 0) { cm3_clubs* ret = find_club("Viking FK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Vålerenga Fotball II") == 0) { cm3_clubs* ret = find_club("Vålerenga Fotball Elite"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_FINLAND_9CF()) {
		if (_strcmpi(db_club_name, "HJK Klubi 04 Helsinki") == 0) { cm3_clubs* ret = find_club("HJK Helsinki"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Espoo II") == 0) { cm3_clubs* ret = find_club("FC Espoo"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Helsinki IFK II") == 0) { cm3_clubs* ret = find_club("Helsinki IFK"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Honka II") == 0) { cm3_clubs* ret = find_club("FC Honka"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Ilves Tampere II") == 0) { cm3_clubs* ret = find_club("Ilves Tampere"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Kuopion Palloseura II") == 0) { cm3_clubs* ret = find_club("Kuopion Palloseura"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rovaniemen Palloseura II") == 0) { cm3_clubs* ret = find_club("Rovaniemen Palloseura"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Vaasan Palloseura II") == 0) { cm3_clubs* ret = find_club("Vaasan Palloseura"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_POLAND_9CF()) {
		if (_strcmpi(db_club_name, "Chrobry Glogow II") == 0) { cm3_clubs* ret = find_club("Chrobry Glogow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Cracovia II") == 0) { cm3_clubs* ret = find_club("Cracovia"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Gornik Zabrze II") == 0) { cm3_clubs* ret = find_club("Górnik Zabrze"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Jagiellonia Bialystok II") == 0) { cm3_clubs* ret = find_club("Jagiellonia Bialystok"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Korona Kielce II") == 0) { cm3_clubs* ret = find_club("Korona Kielce"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Lech Poznan II") == 0) { cm3_clubs* ret = find_club("Lech Poznan"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Legia Warsaw II") == 0) { cm3_clubs* ret = find_club("Legia Warszawa"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "LKS Lodz II") == 0) { cm3_clubs* ret = find_club("LKS Lodz"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Miedz Legnica II") == 0) { cm3_clubs* ret = find_club("Miedz Legnica"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Piast Gliwice II") == 0) { cm3_clubs* ret = find_club("Piast Gliwice"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Pogon Szczecin II") == 0) { cm3_clubs* ret = find_club("Pogon Szczecin"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rakow Czestochowa II") == 0) { cm3_clubs* ret = find_club("Raków Czestochowa"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Slask Wroclaw II") == 0) { cm3_clubs* ret = find_club("Slask Wroclaw"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Widzew Lodz II") == 0) { cm3_clubs* ret = find_club("Widzew Lodz"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Wisla Krakow II") == 0) { cm3_clubs* ret = find_club("Wisla Kraków"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Wisla Plock II") == 0) { cm3_clubs* ret = find_club("Wisla Plock"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Zaglebie Lubin II") == 0) { cm3_clubs* ret = find_club("Zaglebie Lubin"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_SCOTLAND_9CF()) {
		if (_strcmpi(db_club_name, "Glasgow Celtic B") == 0) { cm3_clubs* ret = find_club("Glasgow Celtic"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Heart of Midlothian FC B") == 0) { cm3_clubs* ret = find_club("Heart of Midlothian FC"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_GREECE_9CF()) {
		if (_strcmpi(db_club_name, "Asteras Aktor B") == 0) { cm3_clubs* ret = find_club("Asteras Aktor"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AEK Athens B") == 0) { cm3_clubs* ret = find_club("AEK Athens"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Olympiacos Piraeus B") == 0) { cm3_clubs* ret = find_club("Olympiacos Piraeus"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "PAOK Thessaloniki B") == 0) { cm3_clubs* ret = find_club("PAOK Thessaloniki"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_HOLLAND_9CF()) {
		if (_strcmpi(db_club_name, "AZ Alkmaar U21") == 0) { cm3_clubs* ret = find_club("AZ"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Ajax Amsterdam U21") == 0) { cm3_clubs* ret = find_club("Ajax Amsterdam"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Jong Almere City FC") == 0) { cm3_clubs* ret = find_club("Almere City FC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "PSV Eindhoven U21") == 0) { cm3_clubs* ret = find_club("PSV Eindhoven"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Sparta Rotterdam U21") == 0) { cm3_clubs* ret = find_club("Sparta Rotterdam"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Utrecht U21") == 0) { cm3_clubs* ret = find_club("FC Utrecht"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_BELGIUM_9CF()) {
		if (_strcmpi(db_club_name, "RSC Anderlecht B") == 0) { cm3_clubs* ret = find_club("RSC Anderlecht"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Royal Antwerp FC B") == 0) { cm3_clubs* ret = find_club("Royal Antwerp FC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Beerschot VA U21") == 0) { cm3_clubs* ret = find_club("Beerschot VA"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Cercle Brugge B") == 0) { cm3_clubs* ret = find_club("Cercle Brugge"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "RSC Charleroi B") == 0) { cm3_clubs* ret = find_club("Royal Charleroi SC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Club Brugge KV II") == 0) { cm3_clubs* ret = find_club("Club Brugge KV"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "KAS Eupen U23") == 0) { cm3_clubs* ret = find_club("KAS Eupen"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "KRC Genk B") == 0) { cm3_clubs* ret = find_club("KRC Genk"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "KAA Gent B") == 0) { cm3_clubs* ret = find_club("KAA Gent"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "KV Mechelen U23") == 0) { cm3_clubs* ret = find_club("KV Mechelen"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Oud-Heverlee Leuven U23") == 0) { cm3_clubs* ret = find_club("Oud-Heverlee Leuven"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "STVV Youth") == 0) { cm3_clubs* ret = find_club("Sint-Truidense VV"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Standard de Liège 16 FC") == 0) { cm3_clubs* ret = find_club("Standard Liège"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Union Saint-Gilloise U23") == 0) { cm3_clubs* ret = find_club("Union Saint-Gilloise"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Zulte-Waregem B") == 0) { cm3_clubs* ret = find_club("Zulte Waregem"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_RUSSIA_9CF()) {
		if (_strcmpi(db_club_name, "Akron-2 Togliatti") == 0) { cm3_clubs* ret = find_club("Akron Togliatti"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Alania-2 Vladikavkaz") == 0) { cm3_clubs* ret = find_club("Alania Vladikavkaz"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Arsenal-2 Tula") == 0) { cm3_clubs* ret = find_club("Arsenal Tula"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Baltika-2 Kaliningrad") == 0) { cm3_clubs* ret = find_club("Baltika Kaliningrad"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Chertanovo Moskau II") == 0) { cm3_clubs* ret = find_club("Chertanovo Moscow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "CSKA Moscow II") == 0) { cm3_clubs* ret = find_club("CSKA Moscow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Dinamo-2 Makhachkala") == 0) { cm3_clubs* ret = find_club("Dinamo Makhachkala"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Dynamo 2 Moscow") == 0) { cm3_clubs* ret = find_club("Dynamo Moscow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Enisey 2 Krasnoyarsk") == 0) { cm3_clubs* ret = find_club("Enisey Krasnoyarsk"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Fakel-M Voronezh") == 0) { cm3_clubs* ret = find_club("Fakel Voronezh"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Khimki 2") == 0) { cm3_clubs* ret = find_club("FC Khimki"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Orenburg-2") == 0) { cm3_clubs* ret = find_club("FC Orenburg"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Rostov 2") == 0) { cm3_clubs* ret = find_club("FC Rostov"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Ufa 2") == 0) { cm3_clubs* ret = find_club("FC Ufa"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Kosmos-2 Dolgoprudnyi") == 0) { cm3_clubs* ret = find_club("Kosmos Dolgoprudnyi"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Lokomotiv-Kazanka Moskow") == 0) { cm3_clubs* ret = find_club("Lokomotiv Moscow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rodina 2 Moscow") == 0) { cm3_clubs* ret = find_club("Rodina Moscow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rotor 2 Volgograd") == 0) { cm3_clubs* ret = find_club("Rotor Volgograd"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rubin 2 Kazan") == 0) { cm3_clubs* ret = find_club("Rubin Kazan"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SKA Khabarovsk 2") == 0) { cm3_clubs* ret = find_club("SKA Khabarovsk"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Spartak 2 Moscow") == 0) { cm3_clubs* ret = find_club("Spartak Moscow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Torpedo 2 Moskau") == 0) { cm3_clubs* ret = find_club("Torpedo Moscow"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Ural 2 Ekaterinburg") == 0) { cm3_clubs* ret = find_club("Ural Yekaterinburg"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Zenit 2 St. Petersburg") == 0) { cm3_clubs* ret = find_club("Zenit St. Petersburg"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_CZECH_REPUBLIC_9CF()) {
		if (_strcmpi(db_club_name, "1.FC Slovacko B") == 0) { cm3_clubs* ret = find_club("1.FC Slovacko"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AC Sparta Prague B") == 0) { cm3_clubs* ret = find_club("AC Sparta Prague"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Bohemians Prague 1905 B") == 0) { cm3_clubs* ret = find_club("Bohemians Prague 1905"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Banik Ostrava B") == 0) { cm3_clubs* ret = find_club("FC Banik Ostrava"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Hradec Kralove B") == 0) { cm3_clubs* ret = find_club("FC Hradec Kralove"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC SILON Taborsko B") == 0) { cm3_clubs* ret = find_club("FC SILON Taborsko"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Slovan Liberec B") == 0) { cm3_clubs* ret = find_club("FC Slovan Liberec"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Viktoria Plzen B") == 0) { cm3_clubs* ret = find_club("FC Viktoria Plzen"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Zlin B") == 0) { cm3_clubs* ret = find_club("FC Zlin"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Dukla Prague B") == 0) { cm3_clubs* ret = find_club("FK Dukla Prague"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Jablonec B") == 0) { cm3_clubs* ret = find_club("FK Jablonec"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Mlada Boleslav B") == 0) { cm3_clubs* ret = find_club("FK Mlada Boleslav"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Pardubice B") == 0) { cm3_clubs* ret = find_club("FK Pardubice"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "1.FK Pribram B") == 0) { cm3_clubs* ret = find_club("FK Pribram"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FK Teplice B") == 0) { cm3_clubs* ret = find_club("FK Teplice"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "MFK Karvina B") == 0) { cm3_clubs* ret = find_club("MFK Karvina"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Dynamo Ceske Budejovice B") == 0) { cm3_clubs* ret = find_club("SK Dynamo Ceske Budejovice"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Sigma Olomouc B") == 0) { cm3_clubs* ret = find_club("SK Sigma Olomouc"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Slavia Prague B") == 0) { cm3_clubs* ret = find_club("SK Slavia Prague"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_AUSTRIA_9CF()) {
		if (_strcmpi(db_club_name, "Admira Wacker Panthers") == 0) { cm3_clubs* ret = find_club("Admira Wacker"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Young Violets Austria Wien") == 0) { cm3_clubs* ret = find_club("Austria Vienna"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "LASK Amateure OÖ") == 0) { cm3_clubs* ret = find_club("LASK Linz"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rapid Vienna II") == 0) { cm3_clubs* ret = find_club("Rapid Vienna"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Liefering") == 0) { cm3_clubs* ret = find_club("Red Bull Salzburg"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SC Austria Lustenau II") == 0) { cm3_clubs* ret = find_club("SC Austria Lustenau"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SCR Altach Juniors") == 0) { cm3_clubs* ret = find_club("SCR Altach"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SK Sturm Graz II") == 0) { cm3_clubs* ret = find_club("SK Sturm Graz"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SKN St. Pölten Juniors") == 0) { cm3_clubs* ret = find_club("SKN St. Pölten"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SV Ried II") == 0) { cm3_clubs* ret = find_club("SV Ried"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Wolfsberger AC II") == 0) { cm3_clubs* ret = find_club("Wolfsberger AC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "WSG Tirol II") == 0) { cm3_clubs* ret = find_club("WSG Tirol"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_SWITZERLAND_9CF()) {
		if (_strcmpi(db_club_name, "BSC Young Boys U21") == 0) { cm3_clubs* ret = find_club("BSC Young Boys"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Basel 1893 U21") == 0) { cm3_clubs* ret = find_club("FC Basel 1893"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Lausanne-Sport II ") == 0) { cm3_clubs* ret = find_club("FC Lausanne-Sport"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Lugano II") == 0) { cm3_clubs* ret = find_club("FC Lugano"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Luzern U21") == 0) { cm3_clubs* ret = find_club("FC Luzern"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Sion U21") == 0) { cm3_clubs* ret = find_club("Sion"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC St. Gallen 1879 U21") == 0) { cm3_clubs* ret = find_club("FC St. Gallen 1879"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Winterthur U21") == 0) { cm3_clubs* ret = find_club("FC Winterthur"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Zürich U21") == 0) { cm3_clubs* ret = find_club("FC Zürich"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Servette FC U21") == 0) { cm3_clubs* ret = find_club("Servette FC"); if (ret) return (BYTE*)ret; }
	}
	else if (to_check->ClubNation->NationID == NATION_FRANCE_9CF()) {
		if (_strcmpi(db_club_name, "AC Ajaccio B") == 0) { cm3_clubs* ret = find_club("AC Ajaccio"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AC Le Havre B") == 0) { cm3_clubs* ret = find_club("Le Havre AC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AJ Auxerre B") == 0) { cm3_clubs* ret = find_club("AJ Auxerre"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Amiens SC B") == 0) { cm3_clubs* ret = find_club("Amiens SC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Angers SCO B") == 0) { cm3_clubs* ret = find_club("Angers SCO"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AS Monaco B") == 0) { cm3_clubs* ret = find_club("AS Monaco"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AS Nancy-Lorraine B") == 0) { cm3_clubs* ret = find_club("AS Nancy-Lorraine"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "AS Saint-Étienne B") == 0) { cm3_clubs* ret = find_club("AS Saint-Étienne"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Bourges Foot 18 B") == 0) { cm3_clubs* ret = find_club("Bourges Foot 18"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "C'Chartres Football B") == 0) { cm3_clubs* ret = find_club("C'Chartres Football"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Clermont Foot 63 B") == 0) { cm3_clubs* ret = find_club("Clermont Foot 63"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "CS Sedan-Ardennes B") == 0) { cm3_clubs* ret = find_club("CS Sedan-Ardennes"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Dijon FCO B") == 0) { cm3_clubs* ret = find_club("Dijon FCO"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "EA Guingamp B") == 0) { cm3_clubs* ret = find_club("EA Guingamp"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "ESTAC Troyes B") == 0) { cm3_clubs* ret = find_club("ESTAC Troyes"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Chamois Niort B") == 0) { cm3_clubs* ret = find_club("Chamois Niortais FC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Girondins Bordeaux B") == 0) { cm3_clubs* ret = find_club("FC Girondins Bordeaux"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Le Mans B") == 0) { cm3_clubs* ret = find_club("Le Mans FC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Lorient B") == 0) { cm3_clubs* ret = find_club("FC Lorient"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Metz B") == 0) { cm3_clubs* ret = find_club("FC Metz"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Nantes B") == 0) { cm3_clubs* ret = find_club("FC Nantes"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "FC Sochaux-Montbéliard B") == 0) { cm3_clubs* ret = find_club("FC Sochaux-Montbéliard"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "LB Châteauroux B") == 0) { cm3_clubs* ret = find_club("LB Châteauroux"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Le Puy Foot 43 Auvergne B") == 0) { cm3_clubs* ret = find_club("Le Puy Foot 43 Auvergne"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Les Herbiers VF B") == 0) { cm3_clubs* ret = find_club("Les Herbiers VF"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "LOSC Lille B") == 0) { cm3_clubs* ret = find_club("LOSC Lille"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Lyon - La Duchère B") == 0) { cm3_clubs* ret = find_club("Lyon - La Duchère"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Marignane-Gignac-Côte Bleue FC B") == 0) { cm3_clubs* ret = find_club("Marignane-Gignac-Côte-Bleue FC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Montpellier HSC B") == 0) { cm3_clubs* ret = find_club("Montpellier HSC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "OGC Nice B") == 0) { cm3_clubs* ret = find_club("OGC Nice"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Olympique de Marseille B") == 0) { cm3_clubs* ret = find_club("Olympique Marseille"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Olympique Lyon B") == 0) { cm3_clubs* ret = find_club("Olympique Lyon"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Paris FC B") == 0) { cm3_clubs* ret = find_club("Paris FC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Paris Saint-Germain B") == 0) { cm3_clubs* ret = find_club("Paris Saint-Germain"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Pau FC B") == 0) { cm3_clubs* ret = find_club("Pau FC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Quevilly - Rouen Métropole B") == 0) { cm3_clubs* ret = find_club("Quevilly - Rouen Métropole"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Racing Strasbourg B") == 0) { cm3_clubs* ret = find_club("RC Strasbourg Alsace"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "RC Lens B") == 0) { cm3_clubs* ret = find_club("RC Lens"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Rodez Aveyron Football B") == 0) { cm3_clubs* ret = find_club("Rodez AF"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SC Bastia B") == 0) { cm3_clubs* ret = find_club("SC Bastia"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "SM Caen B") == 0) { cm3_clubs* ret = find_club("SM Caen"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stade Brest 29 B") == 0) { cm3_clubs* ret = find_club("Stade Brestois 29"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stade Briochin B") == 0) { cm3_clubs* ret = find_club("Stade Briochin"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stade Laval B") == 0) { cm3_clubs* ret = find_club("Stade Lavallois"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stade Reims B") == 0) { cm3_clubs* ret = find_club("Stade Reims"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Stade Rennais FC B") == 0) { cm3_clubs* ret = find_club("Stade Rennais FC"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Toulouse FC B") == 0) { cm3_clubs* ret = find_club("FC Toulouse"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "US Avranches B") == 0) { cm3_clubs* ret = find_club("US Avranches"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "US Boulogne II") == 0) { cm3_clubs* ret = find_club("US Boulogne"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "US Orléans B") == 0) { cm3_clubs* ret = find_club("US Orléans"); if (ret) return (BYTE*)ret; }
		if (_strcmpi(db_club_name, "Valenciennes FC B") == 0) { cm3_clubs* ret = find_club("Valenciennes FC"); if (ret) return (BYTE*)ret; }
	}

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
}