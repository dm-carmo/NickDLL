#define _CRT_SECURE_NO_WARNINGS
#include "config.h"
#include "Helpers\Helper.h"
#include "NString.h"

#define MAX_FIELDS 100

Config::Config()
{
	buffer = nullptr;
	jsonMemory = nullptr;
	jsonRoot = nullptr;
}

Config::~Config()
{
    freeJSON();
}

void Config::freeJSON()
{
	if (buffer)
	{
		delete[] buffer;
		buffer = nullptr;
	}
	if (jsonMemory)
	{
		delete[] jsonMemory;
		jsonMemory = nullptr;
	}
	jsonRoot = nullptr;
}


bool Config::LoadConfig(const char* szConfigFile)
{
    bool bResult = false;

    FILE* fp = fopen(szConfigFile, "rb");
    if (fp)
    {
        freeJSON();

        fseek(fp, 0, SEEK_END);
        long fileSize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (fileSize > 0)
        {
            buffer = new char[fileSize + 1];
            if (buffer)
            {
                size_t bytesRead = fread(buffer, sizeof(char), fileSize, fp);
                if (bytesRead == (size_t)fileSize)
                {
                    buffer[fileSize] = '\0'; // Ensure null-termination

                    jsonMemory = new json_t[MAX_FIELDS];

                    jsonRoot = json_create(buffer, jsonMemory, MAX_FIELDS);
                    if (jsonRoot)
                    {
                        bResult = true; // Successfully parsed JSON
                    }
                }
                else
                {
                    delete[] buffer;
                    buffer = nullptr;
                }
            }
        }
        fclose(fp);
    }

    return bResult;
}

const char* Config::GetValue(const char* szPropertyName, const char *szDefaultValue)
{
    if (jsonRoot)
        return json_getPropertyValue(jsonRoot, szPropertyName);
    return szDefaultValue;
}

bool Config::GetBool(const char* szPropertyName, bool defaultReturn)
{
	bool bResult = defaultReturn;
    if (jsonRoot)
    {
        const char *value = json_getPropertyValue(jsonRoot, szPropertyName);
        if (value)
            bResult = (_stricmp(value, "true") == 0);
    }
    return bResult;
}

int Config::GetInt(const char* szPropertyName, int defaultReturn)
{
    int nResult = defaultReturn;
    if (jsonRoot)
    {
        const char* value = json_getPropertyValue(jsonRoot, szPropertyName);
        if (value)
        {
			nResult = atoi(value);
        }
    }
    return nResult;
}

int TestConfig()
{
    Config config;
	char szDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, szDir);
	printf("Current Directory: %s\n", szDir);
    bool loaded = config.LoadConfig("version.json");
    if (loaded) 
    {
        const char *exeFile = config.GetValue("exeFile");
        if (exeFile)
            printf("Executable File: %s\n", exeFile);
        else
			printf("Executable File not found in configuration.\n");    

        const char *logging = config.GetValue("logging");
        if (logging)
            printf("logging: %s\n", logging);
	}
    else
        printf("Failed to load configuration file.\n");

    return 0;
}