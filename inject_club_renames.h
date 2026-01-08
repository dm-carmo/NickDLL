#pragma once
#include <windows.h>
#include <map>
#include <string>
using namespace std;

extern map<string, string> club_rename_long;
extern map<string, string> club_rename_short;

void inject_names_full();
extern "C" int inject_names();
void setup_name_injection();