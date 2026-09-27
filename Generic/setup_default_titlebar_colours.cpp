#include <windows.h>
#include <Helpers\Helper.h>

vector<DWORD> replace_titlebar_bg = {
	0x81BB1A + 3, 0x81CA55 + 3, 0x81D0D3 + 3, 0x81C99C + 2, 0x81CAE6 + 3, 0x81EE2C + 3, 0x81F1EC + 3, 0x81F94F + 3, 0x825D9B + 3, 0x820FB7 + 3, 0x821AD0 + 2, 0x8222B2 + 3, 0x822AF1 + 3, 0x81FF46 + 3, 0x8F4656 + 3, 0x8766E6 + 3, 0x81E932 + 3, 0x8217E9 + 3, 0x821706 + 2, 0x761866 + 2, 0x762720 + 2, 0x7627EA + 3, 0x762946 + 2, 0x762B20 + 3, 0x81C864 + 3, 0x81CBC7 + 3, 0x821834 + 3, 0x821880 + 2, 0x823328 + 2, 0x8389ED + 3, 0x838A24 + 3, 0x88C46C + 3, 0x6AE352 + 3, 0x6B0BAE + 3, 0x8F5174 + 3,
};
vector<DWORD> replace_titlebar_fg = {
	0x81BB13 + 3, 0x81CA61 + 3, 0x81D0CC + 3, 0x81C9BC + 3, 0x81CAED + 3, 0x81EE25 + 3, 0x81F1E6 + 2, 0x81F949 + 2, 0x825D95 + 2, 0x820FB0 + 3, 0x821AC9 + 3, 0x8222AC + 2, 0x822AEA + 3, 0x81FF40 + 2, 0x8F465D + 2, 0x8766DF + 3, 0x81E92B + 3, 0x8217F0 + 2, 0x82170C + 3, 0x76186C + 3, 0x762726 + 3, 0x7627F1 + 3, 0x76294C + 3, 0x762B27 + 3, 0x81C86B + 3, 0x81CBCE + 2, 0x82183B + 2, 0x821886 + 3, 0x82332E + 3, 0x8389F4 + 3, 0x838A2B + 3, 0x88C466 + 2, 0x6AE34C + 2, 0x6B0BA8 + 2, 0x8F516E + 2,
};

void setup_default_titlebar_colours() {
	const char* titlebar_bg = configFile.GetValue("defaultTitleBackground", "0xAE31A8");
	DWORD titlebar_bg_hex = stoul(titlebar_bg, nullptr, 16);
	const char* titlebar_fg = configFile.GetValue("defaultTitleForeground", "0xAE3184");
	DWORD titlebar_fg_hex = stoul(titlebar_fg, nullptr, 16);

	// change default titlebar colours (menus)
	for (DWORD d : replace_titlebar_bg) {
		WriteDWORD(d, titlebar_bg_hex);
	}
	for (DWORD d : replace_titlebar_fg) {
		WriteDWORD(d, titlebar_fg_hex);
	}
	// fix web sites menu
	WriteNOP(0x513a2e, 10);
	WriteBytes(0x513a2e, 2, 0x66, 0xa1);
	WriteDWORD(0x513a30, titlebar_fg_hex);
	WriteNOP(0x513a39, 10);
	WriteBytes(0x513a39, 2, 0x66, 0xa1);
	WriteDWORD(0x513a3b, titlebar_bg_hex);
	// fix credits menu
	WriteNOP(0x51331d, 5);
	WriteNOP(0x513341, 5);
	WriteNOP(0x5131bc, 10);
	WriteBytes(0x5131bc, 2, 0x66, 0xa1);
	WriteDWORD(0x5131be, titlebar_fg_hex);
	WriteNOP(0x5131c7, 9);
	WriteBytes(0x5131c7, 2, 0x66, 0xa1);
	WriteDWORD(0x5131c9, titlebar_bg_hex);
	// fix nations & clubs menu
	WriteNOP(0x5a0903, 9);
	WriteBytes(0x5a0903, 2, 0x66, 0xa1);
	WriteDWORD(0x5a0905, titlebar_fg_hex);
	WriteNOP(0x5a090d, 10);
	WriteBytes(0x5a090d, 2, 0x66, 0xa1);
	WriteDWORD(0x5a090f, titlebar_bg_hex);
	// fix find menu
	WriteNOP(0x5a2ec1, 9);
	WriteBytes(0x5a2ec1, 2, 0x66, 0xa1);
	WriteDWORD(0x5a2ec3, titlebar_fg_hex);
	WriteNOP(0x5a2ecb, 10);
	WriteBytes(0x5a2ecb, 2, 0x66, 0xa1);
	WriteDWORD(0x5a2ecd, titlebar_bg_hex);
	// fix add nickname menu
	WriteNOP(0x88bcbe, 10);
	WriteBytes(0x88bcbe, 2, 0x66, 0xa1);
	WriteDWORD(0x88bcc0, titlebar_fg_hex);
	WriteNOP(0x88bcc9, 10);
	WriteBytes(0x88bcc9, 2, 0x66, 0xa1);
	WriteDWORD(0x88bccb, titlebar_bg_hex);
	// fix send message menu
	WriteNOP(0x7899d1, 10);
	WriteBytes(0x7899d1, 2, 0x66, 0xa1);
	WriteDWORD(0x7899d3, titlebar_fg_hex);
	WriteNOP(0x7899dc, 10);
	WriteBytes(0x7899dc, 2, 0x66, 0xa1);
	WriteDWORD(0x7899de, titlebar_bg_hex);
	// fix manager chat menu
	WriteNOP(0x76558a, 10);
	WriteBytes(0x76558a, 2, 0x66, 0xa1);
	WriteDWORD(0x76558c, titlebar_fg_hex);
	WriteNOP(0x765595, 10);
	WriteBytes(0x765595, 2, 0x66, 0xa1);
	WriteDWORD(0x765597, titlebar_bg_hex);
	// fix go on holiday menu
	WriteNOP(0x6b2e1d, 10);
	WriteBytes(0x6b2e1d, 2, 0x66, 0xa1);
	WriteDWORD(0x6b2e1f, titlebar_fg_hex);
	WriteNOP(0x6b2e28, 10);
	WriteBytes(0x6b2e28, 2, 0x66, 0xa1);
	WriteDWORD(0x6b2e2a, titlebar_bg_hex);
	// fix restart game menu - backwards
	WriteNOP(0x7642c8, 9);
	WriteBytes(0x7642c8, 2, 0x66, 0xa1);
	WriteDWORD(0x7642ca, titlebar_bg_hex);
	WriteNOP(0x7642d2, 10);
	WriteBytes(0x7642d2, 2, 0x66, 0xa1);
	WriteDWORD(0x7642d4, titlebar_fg_hex);
	// fix exit game menu - backwards
	WriteNOP(0x764371, 9);
	WriteBytes(0x764371, 2, 0x66, 0xa1);
	WriteDWORD(0x764373, titlebar_bg_hex);
	WriteNOP(0x76437b, 10);
	WriteBytes(0x76437b, 2, 0x66, 0xa1);
	WriteDWORD(0x76437d, titlebar_fg_hex);
	// fix save game menu - backwards
	WriteNOP(0x763f5e, 1);
	WriteNOP(0x763f64, 8);
	WriteBytes(0x763f64, 2, 0x66, 0xa1);
	WriteDWORD(0x763f66, titlebar_bg_hex);
	WriteNOP(0x763f6d, 10);
	WriteBytes(0x763f6d, 2, 0x66, 0xa1);
	WriteDWORD(0x763f6f, titlebar_fg_hex);
	// fix save before exit menu - backwards
	WriteNOP(0x762bf1, 1);
	WriteNOP(0x762bfb, 8);
	WriteBytes(0x762bfb, 2, 0x66, 0xa1);
	WriteDWORD(0x762bfd, titlebar_bg_hex);
	WriteNOP(0x762c04, 10);
	WriteBytes(0x762c04, 2, 0x66, 0xa1);
	WriteDWORD(0x762c06, titlebar_fg_hex);
	// fix save before restart menu - backwards
	WriteNOP(0x762a44, 1);
	WriteNOP(0x762a4a, 8);
	WriteBytes(0x762a4a, 2, 0x66, 0xa1);
	WriteDWORD(0x762a4c, titlebar_bg_hex);
	WriteNOP(0x762a53, 10);
	WriteBytes(0x762a53, 2, 0x66, 0xa1);
	WriteDWORD(0x762a55, titlebar_fg_hex);
	// fix auto save game menu - backwards
	WriteNOP(0x761722, 1);
	WriteNOP(0x761728, 8);
	WriteBytes(0x761728, 2, 0x66, 0xa1);
	WriteDWORD(0x76172a, titlebar_bg_hex);
	WriteNOP(0x761731, 10);
	WriteBytes(0x761731, 2, 0x66, 0xa1);
	WriteDWORD(0x761733, titlebar_fg_hex);
}