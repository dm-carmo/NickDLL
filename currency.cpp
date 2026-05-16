#include <Helpers/Helper.h>

double inflation_mult = 1.;

void setup_currency() {
	inflation_mult = configFile.GetDouble("inflationMultiplier", 0.);
	if (*(BYTE*)0x9196C1 != 0x90) inflation_mult = *(double*)0x9196C1;
	if (inflation_mult == 0.) inflation_mult = 1.;
	// 1 GBP = 1.16 EUR;
	WriteDWORD(0x43FF23 + 6, 0x28F5C28F);
	WriteDWORD(0x43FF33 + 6, 0x3FF28F5C);
	WriteDWORD(0x43FF49 + 6, 0);
	WriteDWORD(0x43FF5C + 6, 0x3FF00000);
	// 1 GBP = 1.35 USD;
	WriteDWORD(0x4413E8 + 6, 0x9999999A);
	WriteDWORD(0x4413F8 + 6, 0x3FF59999);
	WriteDWORD(0x44140E + 6, 0);
	WriteDWORD(0x441421 + 6, 0x3FF00000);
	// 1 GBP = 6.93 BRL;
	WriteDWORD(0x43FB8B + 6, 0xEB851EB8);
	WriteDWORD(0x43FB9B + 6, 0x401BB851);
	// 1 GBP = 1.884 AUD;
	WriteDWORD(0x43F95F + 6, 0x2F1A9FBE);
	WriteDWORD(0x43F96F + 6, 0x3FFE24DD);
	WriteDWORD(0x43F985 + 6, 0);
	WriteDWORD(0x43F998 + 6, 0x3FF80000);
}