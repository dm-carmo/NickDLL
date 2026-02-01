#pragma once
#include <windows.h>
#include <map>
#include <string>
using namespace std;

int setup_9cf_leagues_sub(char* league_name, DWORD league_id, map<string, char*> new_names_map);
int setup_9cf_awards_sub(char* award_name, DWORD award_id, map<string, char*> new_names_map);
void setup_name_injection();