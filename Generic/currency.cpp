#include "Helpers\Helper.h"

double inflation_mult = 2.5;
double general_mult = 1.;

void setup_currency() {
	general_mult = configFile.GetDouble("prizeMoneyMultiplier", 1.);
	//if (*(BYTE*)0x9196C1 != 0x90) inflation_mult = *(double*)0x9196C1;
	// 1 GBP = 1.16577 EUR;
	WriteDWORD(0x43FF23 + 6, 0x718a86d7);
	WriteDWORD(0x43FF33 + 6, 0x3ff2a6fe);
	WriteDWORD(0x43FF49 + 6, 0);
	WriteDWORD(0x43FF5C + 6, 0x3FF00000);
	// 1 GBP = 1.33947 USD;
	WriteDWORD(0x4413E8 + 6, 0x183f91e6);
	WriteDWORD(0x4413F8 + 6, 0x3ff56e78);
	WriteDWORD(0x44140E + 6, 0);
	WriteDWORD(0x441421 + 6, 0x3FF00000);
	// 1 GBP = 6.86873 BRL;
	WriteDWORD(0x43FB8B + 6, 0x5b6c3761);
	WriteDWORD(0x43FB9B + 6, 0x401b7994);
	// 1 GBP = 1.87666 AUD;
	WriteDWORD(0x43F95F + 6, 0xa2db61bb);
	WriteDWORD(0x43F96F + 6, 0x3ffe06cc);
	WriteDWORD(0x43F985 + 6, 0);
	WriteDWORD(0x43F998 + 6, 0x3FF80000);
}