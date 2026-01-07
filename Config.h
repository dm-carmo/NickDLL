#pragma once
#include <Windows.h>
#include "tiny-json.h"
#include <tuple> 
#include <string>
#include <vector>

class Config
{
public:
    Config();
    ~Config();

    bool LoadConfig(const char* szConfigFile);
    const char* GetValue(const char* szPropertyName, const char* szDefaultValue = nullptr);
    bool GetBool(const char* szPropertyName, bool defaultReturn = false);
    int GetInt(const char* szPropertyName, int defaultReturn = 0);

private:
    void freeJSON();

    char* buffer;
    json_t* jsonMemory;
    const json_t* jsonRoot;
};

int TestConfig();
