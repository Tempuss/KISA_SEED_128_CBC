#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KISA_SEED_CBC.h"

// S-BOX
const static DWORD SS0[256] =
{
	0x2989a1a8, 0x05858184, 0x16c6d2d4, 0x13c3d3d0, 0x14445054, 0x1d0d111c, 0x2c8ca0ac, 0x25052124,
	0x1d4d515c, 0x03434340, 0x18081018, 0x1e0e121c, 0x11415150, 0x3cccf0fc, 0x0acac2c8, 0x23436360,
	0x28082028, 0x04444044, 0x20002020, 0x1d8d919c, 0x20c0e0e0, 0x22c2e2e0, 0x08c8c0c8, 0x17071314,
	0x2585a1a4, 0x0f8f838c, 0x03030300, 0x3b4b7378, 0x3b8bb3b8, 0x13031310, 0x12c2d2d0, 0x2ecee2ec,
	0x30407070, 0x0c8c808c, 0x3f0f333c, 0x2888a0a8, 0x32023230, 0x1dcdd1dc, 0x36c6f2f4, 0x34447074,
	0x2ccce0ec, 0x15859194, 0x0b0b0308, 0x17475354, 0x1c4c505c, 0x1b4b5358, 0x3d8db1bc, 0x01010100,
	0x24042024, 0x1c0c101c, 0x33437370, 0x18889098, 0x10001010, 0x0cccc0cc, 0x32c2f2f0, 0x19c9d1d8,
	0x2c0c202c, 0x27c7e3e4, 0x32427270, 0x03838380, 0x1b8b9398, 0x11c1d1d0, 0x06868284, 0x09c9c1c8,
	0x20406060, 0x10405050, 0x2383a3a0, 0x2bcbe3e8, 0x0d0d010c, 0x3686b2b4, 0x1e8e929c, 0x0f4f434c,
	0x3787b3b4, 0x1a4a5258, 0x06c6c2c4, 0x38487078, 0x2686a2a4, 0x12021210, 0x2f8fa3ac, 0x15c5d1d4,
	0x21416160, 0x03c3c3c0, 0x3484b0b4, 0x01414140, 0x12425250, 0x3d4d717c, 0x0d8d818c, 0x08080008,
	0x1f0f131c, 0x19899198, 0x00000000, 0x19091118, 0x04040004, 0x13435350, 0x37c7f3f4, 0x21c1e1e0,
	0x3dcdf1fc, 0x36467274, 0x2f0f232c, 0x27072324, 0x3080b0b0, 0x0b8b8388, 0x0e0e020c, 0x2b8ba3a8,
	0x2282a2a0, 0x2e4e626c, 0x13839390, 0x0d4d414c, 0x29496168, 0x3c4c707c, 0x09090108, 0x0a0a0208,
	0x3f8fb3bc, 0x2fcfe3ec, 0x33c3f3f0, 0x05c5c1c4, 0x07878384, 0x14041014, 0x3ecef2fc, 0x24446064,
	0x1eced2dc, 0x2e0e222c, 0x0b4b4348, 0x1a0a1218, 0x06060204, 0x21012120, 0x2b4b6368, 0x26466264,
	0x02020200, 0x35c5f1f4, 0x12829290, 0x0a8a8288, 0x0c0c000c, 0x3383b3b0, 0x3e4e727c, 0x10c0d0d0,
	0x3a4a7278, 0x07474344, 0x16869294, 0x25c5e1e4, 0x26062224, 0x00808080, 0x2d8da1ac, 0x1fcfd3dc,
	0x2181a1a0, 0x30003030, 0x37073334, 0x2e8ea2ac, 0x36063234, 0x15051114, 0x22022220, 0x38083038,
	0x34c4f0f4, 0x2787a3a4, 0x05454144, 0x0c4c404c, 0x01818180, 0x29c9e1e8, 0x04848084, 0x17879394,
	0x35053134, 0x0bcbc3c8, 0x0ecec2cc, 0x3c0c303c, 0x31417170, 0x11011110, 0x07c7c3c4, 0x09898188,
	0x35457174, 0x3bcbf3f8, 0x1acad2d8, 0x38c8f0f8, 0x14849094, 0x19495158, 0x02828280, 0x04c4c0c4,
	0x3fcff3fc, 0x09494148, 0x39093138, 0x27476364, 0x00c0c0c0, 0x0fcfc3cc, 0x17c7d3d4, 0x3888b0b8,
	0x0f0f030c, 0x0e8e828c, 0x02424240, 0x23032320, 0x11819190, 0x2c4c606c, 0x1bcbd3d8, 0x2484a0a4,
	0x34043034, 0x31c1f1f0, 0x08484048, 0x02c2c2c0, 0x2f4f636c, 0x3d0d313c, 0x2d0d212c, 0x00404040,
	0x3e8eb2bc, 0x3e0e323c, 0x3c8cb0bc, 0x01c1c1c0, 0x2a8aa2a8, 0x3a8ab2b8, 0x0e4e424c, 0x15455154,
	0x3b0b3338, 0x1cccd0dc, 0x28486068, 0x3f4f737c, 0x1c8c909c, 0x18c8d0d8, 0x0a4a4248, 0x16465254,
	0x37477374, 0x2080a0a0, 0x2dcde1ec, 0x06464244, 0x3585b1b4, 0x2b0b2328, 0x25456164, 0x3acaf2f8,
	0x23c3e3e0, 0x3989b1b8, 0x3181b1b0, 0x1f8f939c, 0x1e4e525c, 0x39c9f1f8, 0x26c6e2e4, 0x3282b2b0,
	0x31013130, 0x2acae2e8, 0x2d4d616c, 0x1f4f535c, 0x24c4e0e4, 0x30c0f0f0, 0x0dcdc1cc, 0x08888088,
	0x16061214, 0x3a0a3238, 0x18485058, 0x14c4d0d4, 0x22426260, 0x29092128, 0x07070304, 0x33033330,
	0x28c8e0e8, 0x1b0b1318, 0x05050104, 0x39497178, 0x10809090, 0x2a4a6268, 0x2a0a2228, 0x1a8a9298
};

const static DWORD SS1[256] =
{
	0x38380830, 0xe828c8e0, 0x2c2d0d21, 0xa42686a2, 0xcc0fcfc3, 0xdc1eced2, 0xb03383b3, 0xb83888b0,
	0xac2f8fa3, 0x60204060, 0x54154551, 0xc407c7c3, 0x44044440, 0x6c2f4f63, 0x682b4b63, 0x581b4b53,
	0xc003c3c3, 0x60224262, 0x30330333, 0xb43585b1, 0x28290921, 0xa02080a0, 0xe022c2e2, 0xa42787a3,
	0xd013c3d3, 0x90118191, 0x10110111, 0x04060602, 0x1c1c0c10, 0xbc3c8cb0, 0x34360632, 0x480b4b43,
	0xec2fcfe3, 0x88088880, 0x6c2c4c60, 0xa82888a0, 0x14170713, 0xc404c4c0, 0x14160612, 0xf434c4f0,
	0xc002c2c2, 0x44054541, 0xe021c1e1, 0xd416c6d2, 0x3c3f0f33, 0x3c3d0d31, 0x8c0e8e82, 0x98188890,
	0x28280820, 0x4c0e4e42, 0xf436c6f2, 0x3c3e0e32, 0xa42585a1, 0xf839c9f1, 0x0c0d0d01, 0xdc1fcfd3,
	0xd818c8d0, 0x282b0b23, 0x64264662, 0x783a4a72, 0x24270723, 0x2c2f0f23, 0xf031c1f1, 0x70324272,
	0x40024242, 0xd414c4d0, 0x40014141, 0xc000c0c0, 0x70334373, 0x64274763, 0xac2c8ca0, 0x880b8b83,
	0xf437c7f3, 0xac2d8da1, 0x80008080, 0x1c1f0f13, 0xc80acac2, 0x2c2c0c20, 0xa82a8aa2, 0x34340430,
	0xd012c2d2, 0x080b0b03, 0xec2ecee2, 0xe829c9e1, 0x5c1d4d51, 0x94148490, 0x18180810, 0xf838c8f0,
	0x54174753, 0xac2e8ea2, 0x08080800, 0xc405c5c1, 0x10130313, 0xcc0dcdc1, 0x84068682, 0xb83989b1,
	0xfc3fcff3, 0x7c3d4d71, 0xc001c1c1, 0x30310131, 0xf435c5f1, 0x880a8a82, 0x682a4a62, 0xb03181b1,
	0xd011c1d1, 0x20200020, 0xd417c7d3, 0x00020202, 0x20220222, 0x04040400, 0x68284860, 0x70314171,
	0x04070703, 0xd81bcbd3, 0x9c1d8d91, 0x98198991, 0x60214161, 0xbc3e8eb2, 0xe426c6e2, 0x58194951,
	0xdc1dcdd1, 0x50114151, 0x90108090, 0xdc1cccd0, 0x981a8a92, 0xa02383a3, 0xa82b8ba3, 0xd010c0d0,
	0x80018181, 0x0c0f0f03, 0x44074743, 0x181a0a12, 0xe023c3e3, 0xec2ccce0, 0x8c0d8d81, 0xbc3f8fb3,
	0x94168692, 0x783b4b73, 0x5c1c4c50, 0xa02282a2, 0xa02181a1, 0x60234363, 0x20230323, 0x4c0d4d41,
	0xc808c8c0, 0x9c1e8e92, 0x9c1c8c90, 0x383a0a32, 0x0c0c0c00, 0x2c2e0e22, 0xb83a8ab2, 0x6c2e4e62,
	0x9c1f8f93, 0x581a4a52, 0xf032c2f2, 0x90128292, 0xf033c3f3, 0x48094941, 0x78384870, 0xcc0cccc0,
	0x14150511, 0xf83bcbf3, 0x70304070, 0x74354571, 0x7c3f4f73, 0x34350531, 0x10100010, 0x00030303,
	0x64244460, 0x6c2d4d61, 0xc406c6c2, 0x74344470, 0xd415c5d1, 0xb43484b0, 0xe82acae2, 0x08090901,
	0x74364672, 0x18190911, 0xfc3ecef2, 0x40004040, 0x10120212, 0xe020c0e0, 0xbc3d8db1, 0x04050501,
	0xf83acaf2, 0x00010101, 0xf030c0f0, 0x282a0a22, 0x5c1e4e52, 0xa82989a1, 0x54164652, 0x40034343,
	0x84058581, 0x14140410, 0x88098981, 0x981b8b93, 0xb03080b0, 0xe425c5e1, 0x48084840, 0x78394971,
	0x94178793, 0xfc3cccf0, 0x1c1e0e12, 0x80028282, 0x20210121, 0x8c0c8c80, 0x181b0b13, 0x5c1f4f53,
	0x74374773, 0x54144450, 0xb03282b2, 0x1c1d0d11, 0x24250521, 0x4c0f4f43, 0x00000000, 0x44064642,
	0xec2dcde1, 0x58184850, 0x50124252, 0xe82bcbe3, 0x7c3e4e72, 0xd81acad2, 0xc809c9c1, 0xfc3dcdf1,
	0x30300030, 0x94158591, 0x64254561, 0x3c3c0c30, 0xb43686b2, 0xe424c4e0, 0xb83b8bb3, 0x7c3c4c70,
	0x0c0e0e02, 0x50104050, 0x38390931, 0x24260622, 0x30320232, 0x84048480, 0x68294961, 0x90138393,
	0x34370733, 0xe427c7e3, 0x24240420, 0xa42484a0, 0xc80bcbc3, 0x50134353, 0x080a0a02, 0x84078783,
	0xd819c9d1, 0x4c0c4c40, 0x80038383, 0x8c0f8f83, 0xcc0ecec2, 0x383b0b33, 0x480a4a42, 0xb43787b3
};

const static DWORD SS2[256] =
{
	0xa1a82989, 0x81840585, 0xd2d416c6, 0xd3d013c3, 0x50541444, 0x111c1d0d, 0xa0ac2c8c, 0x21242505,
	0x515c1d4d, 0x43400343, 0x10181808, 0x121c1e0e, 0x51501141, 0xf0fc3ccc, 0xc2c80aca, 0x63602343,
	0x20282808, 0x40440444, 0x20202000, 0x919c1d8d, 0xe0e020c0, 0xe2e022c2, 0xc0c808c8, 0x13141707,
	0xa1a42585, 0x838c0f8f, 0x03000303, 0x73783b4b, 0xb3b83b8b, 0x13101303, 0xd2d012c2, 0xe2ec2ece,
	0x70703040, 0x808c0c8c, 0x333c3f0f, 0xa0a82888, 0x32303202, 0xd1dc1dcd, 0xf2f436c6, 0x70743444,
	0xe0ec2ccc, 0x91941585, 0x03080b0b, 0x53541747, 0x505c1c4c, 0x53581b4b, 0xb1bc3d8d, 0x01000101,
	0x20242404, 0x101c1c0c, 0x73703343, 0x90981888, 0x10101000, 0xc0cc0ccc, 0xf2f032c2, 0xd1d819c9,
	0x202c2c0c, 0xe3e427c7, 0x72703242, 0x83800383, 0x93981b8b, 0xd1d011c1, 0x82840686, 0xc1c809c9,
	0x60602040, 0x50501040, 0xa3a02383, 0xe3e82bcb, 0x010c0d0d, 0xb2b43686, 0x929c1e8e, 0x434c0f4f,
	0xb3b43787, 0x52581a4a, 0xc2c406c6, 0x70783848, 0xa2a42686, 0x12101202, 0xa3ac2f8f, 0xd1d415c5,
	0x61602141, 0xc3c003c3, 0xb0b43484, 0x41400141, 0x52501242, 0x717c3d4d, 0x818c0d8d, 0x00080808,
	0x131c1f0f, 0x91981989, 0x00000000, 0x11181909, 0x00040404, 0x53501343, 0xf3f437c7, 0xe1e021c1,
	0xf1fc3dcd, 0x72743646, 0x232c2f0f, 0x23242707, 0xb0b03080, 0x83880b8b, 0x020c0e0e, 0xa3a82b8b,
	0xa2a02282, 0x626c2e4e, 0x93901383, 0x414c0d4d, 0x61682949, 0x707c3c4c, 0x01080909, 0x02080a0a,
	0xb3bc3f8f, 0xe3ec2fcf, 0xf3f033c3, 0xc1c405c5, 0x83840787, 0x10141404, 0xf2fc3ece, 0x60642444,
	0xd2dc1ece, 0x222c2e0e, 0x43480b4b, 0x12181a0a, 0x02040606, 0x21202101, 0x63682b4b, 0x62642646,
	0x02000202, 0xf1f435c5, 0x92901282, 0x82880a8a, 0x000c0c0c, 0xb3b03383, 0x727c3e4e, 0xd0d010c0,
	0x72783a4a, 0x43440747, 0x92941686, 0xe1e425c5, 0x22242606, 0x80800080, 0xa1ac2d8d, 0xd3dc1fcf,
	0xa1a02181, 0x30303000, 0x33343707, 0xa2ac2e8e, 0x32343606, 0x11141505, 0x22202202, 0x30383808,
	0xf0f434c4, 0xa3a42787, 0x41440545, 0x404c0c4c, 0x81800181, 0xe1e829c9, 0x80840484, 0x93941787,
	0x31343505, 0xc3c80bcb, 0xc2cc0ece, 0x303c3c0c, 0x71703141, 0x11101101, 0xc3c407c7, 0x81880989,
	0x71743545, 0xf3f83bcb, 0xd2d81aca, 0xf0f838c8, 0x90941484, 0x51581949, 0x82800282, 0xc0c404c4,
	0xf3fc3fcf, 0x41480949, 0x31383909, 0x63642747, 0xc0c000c0, 0xc3cc0fcf, 0xd3d417c7, 0xb0b83888,
	0x030c0f0f, 0x828c0e8e, 0x42400242, 0x23202303, 0x91901181, 0x606c2c4c, 0xd3d81bcb, 0xa0a42484,
	0x30343404, 0xf1f031c1, 0x40480848, 0xc2c002c2, 0x636c2f4f, 0x313c3d0d, 0x212c2d0d, 0x40400040,
	0xb2bc3e8e, 0x323c3e0e, 0xb0bc3c8c, 0xc1c001c1, 0xa2a82a8a, 0xb2b83a8a, 0x424c0e4e, 0x51541545,
	0x33383b0b, 0xd0dc1ccc, 0x60682848, 0x737c3f4f, 0x909c1c8c, 0xd0d818c8, 0x42480a4a, 0x52541646,
	0x73743747, 0xa0a02080, 0xe1ec2dcd, 0x42440646, 0xb1b43585, 0x23282b0b, 0x61642545, 0xf2f83aca,
	0xe3e023c3, 0xb1b83989, 0xb1b03181, 0x939c1f8f, 0x525c1e4e, 0xf1f839c9, 0xe2e426c6, 0xb2b03282,
	0x31303101, 0xe2e82aca, 0x616c2d4d, 0x535c1f4f, 0xe0e424c4, 0xf0f030c0, 0xc1cc0dcd, 0x80880888,
	0x12141606, 0x32383a0a, 0x50581848, 0xd0d414c4, 0x62602242, 0x21282909, 0x03040707, 0x33303303,
	0xe0e828c8, 0x13181b0b, 0x01040505, 0x71783949, 0x90901080, 0x62682a4a, 0x22282a0a, 0x92981a8a
};

const static DWORD SS3[256] =
{
	0x08303838, 0xc8e0e828, 0x0d212c2d, 0x86a2a426, 0xcfc3cc0f, 0xced2dc1e, 0x83b3b033, 0x88b0b838,
	0x8fa3ac2f, 0x40606020, 0x45515415, 0xc7c3c407, 0x44404404, 0x4f636c2f, 0x4b63682b, 0x4b53581b,
	0xc3c3c003, 0x42626022, 0x03333033, 0x85b1b435, 0x09212829, 0x80a0a020, 0xc2e2e022, 0x87a3a427,
	0xc3d3d013, 0x81919011, 0x01111011, 0x06020406, 0x0c101c1c, 0x8cb0bc3c, 0x06323436, 0x4b43480b,
	0xcfe3ec2f, 0x88808808, 0x4c606c2c, 0x88a0a828, 0x07131417, 0xc4c0c404, 0x06121416, 0xc4f0f434,
	0xc2c2c002, 0x45414405, 0xc1e1e021, 0xc6d2d416, 0x0f333c3f, 0x0d313c3d, 0x8e828c0e, 0x88909818,
	0x08202828, 0x4e424c0e, 0xc6f2f436, 0x0e323c3e, 0x85a1a425, 0xc9f1f839, 0x0d010c0d, 0xcfd3dc1f,
	0xc8d0d818, 0x0b23282b, 0x46626426, 0x4a72783a, 0x07232427, 0x0f232c2f, 0xc1f1f031, 0x42727032,
	0x42424002, 0xc4d0d414, 0x41414001, 0xc0c0c000, 0x43737033, 0x47636427, 0x8ca0ac2c, 0x8b83880b,
	0xc7f3f437, 0x8da1ac2d, 0x80808000, 0x0f131c1f, 0xcac2c80a, 0x0c202c2c, 0x8aa2a82a, 0x04303434,
	0xc2d2d012, 0x0b03080b, 0xcee2ec2e, 0xc9e1e829, 0x4d515c1d, 0x84909414, 0x08101818, 0xc8f0f838,
	0x47535417, 0x8ea2ac2e, 0x08000808, 0xc5c1c405, 0x03131013, 0xcdc1cc0d, 0x86828406, 0x89b1b839,
	0xcff3fc3f, 0x4d717c3d, 0xc1c1c001, 0x01313031, 0xc5f1f435, 0x8a82880a, 0x4a62682a, 0x81b1b031,
	0xc1d1d011, 0x00202020, 0xc7d3d417, 0x02020002, 0x02222022, 0x04000404, 0x48606828, 0x41717031,
	0x07030407, 0xcbd3d81b, 0x8d919c1d, 0x89919819, 0x41616021, 0x8eb2bc3e, 0xc6e2e426, 0x49515819,
	0xcdd1dc1d, 0x41515011, 0x80909010, 0xccd0dc1c, 0x8a92981a, 0x83a3a023, 0x8ba3a82b, 0xc0d0d010,
	0x81818001, 0x0f030c0f, 0x47434407, 0x0a12181a, 0xc3e3e023, 0xcce0ec2c, 0x8d818c0d, 0x8fb3bc3f,
	0x86929416, 0x4b73783b, 0x4c505c1c, 0x82a2a022, 0x81a1a021, 0x43636023, 0x03232023, 0x4d414c0d,
	0xc8c0c808, 0x8e929c1e, 0x8c909c1c, 0x0a32383a, 0x0c000c0c, 0x0e222c2e, 0x8ab2b83a, 0x4e626c2e,
	0x8f939c1f, 0x4a52581a, 0xc2f2f032, 0x82929012, 0xc3f3f033, 0x49414809, 0x48707838, 0xccc0cc0c,
	0x05111415, 0xcbf3f83b, 0x40707030, 0x45717435, 0x4f737c3f, 0x05313435, 0x00101010, 0x03030003,
	0x44606424, 0x4d616c2d, 0xc6c2c406, 0x44707434, 0xc5d1d415, 0x84b0b434, 0xcae2e82a, 0x09010809,
	0x46727436, 0x09111819, 0xcef2fc3e, 0x40404000, 0x02121012, 0xc0e0e020, 0x8db1bc3d, 0x05010405,
	0xcaf2f83a, 0x01010001, 0xc0f0f030, 0x0a22282a, 0x4e525c1e, 0x89a1a829, 0x46525416, 0x43434003,
	0x85818405, 0x04101414, 0x89818809, 0x8b93981b, 0x80b0b030, 0xc5e1e425, 0x48404808, 0x49717839,
	0x87939417, 0xccf0fc3c, 0x0e121c1e, 0x82828002, 0x01212021, 0x8c808c0c, 0x0b13181b, 0x4f535c1f,
	0x47737437, 0x44505414, 0x82b2b032, 0x0d111c1d, 0x05212425, 0x4f434c0f, 0x00000000, 0x46424406,
	0xcde1ec2d, 0x48505818, 0x42525012, 0xcbe3e82b, 0x4e727c3e, 0xcad2d81a, 0xc9c1c809, 0xcdf1fc3d,
	0x00303030, 0x85919415, 0x45616425, 0x0c303c3c, 0x86b2b436, 0xc4e0e424, 0x8bb3b83b, 0x4c707c3c,
	0x0e020c0e, 0x40505010, 0x09313839, 0x06222426, 0x02323032, 0x84808404, 0x49616829, 0x83939013,
	0x07333437, 0xc7e3e427, 0x04202424, 0x84a0a424, 0xcbc3c80b, 0x43535013, 0x0a02080a, 0x87838407,
	0xc9d1d819, 0x4c404c0c, 0x83838003, 0x8f838c0f, 0xcec2cc0e, 0x0b33383b, 0x4a42480a, 0x87b3b437
};

#define BLOCK_SIZE_SEED			16
#define BLOCK_SIZE_SEED_INT		4

#define GetB0(A)  ( (BYTE)((A)    ) )
#define GetB1(A)  ( (BYTE)((A)>> 8) )
#define GetB2(A)  ( (BYTE)((A)>>16) )
#define GetB3(A)  ( (BYTE)((A)>>24) )

// Round function F and adding output of F to L.
// L0, L1 : left input values at each round
// R0, R1 : right input values at each round
// K : round keys at each round
#define SeedRound(L0, L1, R0, R1, K) {             \
    T0 = R0 ^ (K)[0];                              \
    T1 = R1 ^ (K)[1];                              \
    T1 ^= T0;                                      \
    T1 = SS0[GetB0(T1)] ^ SS1[GetB1(T1)] ^         \
         SS2[GetB2(T1)] ^ SS3[GetB3(T1)];          \
    T0 += T1;                                      \
    T0 = SS0[GetB0(T0)] ^ SS1[GetB1(T0)] ^         \
         SS2[GetB2(T0)] ^ SS3[GetB3(T0)];          \
    T1 += T0;                                      \
    T1 = SS0[GetB0(T1)] ^ SS1[GetB1(T1)] ^         \
         SS2[GetB2(T1)] ^ SS3[GetB3(T1)];          \
    T0 += T1;                                      \
    L0 ^= T0; L1 ^= T1;                            \
}

#define ROTL(x, n)     (((x) << (n)) | ((x) >> (32-(n))))
#define ROTR(x, n)     (((x) >> (n)) | ((x) << (32-(n))))

#define EndianChange(dwS)								\
	( (ROTL((dwS),  8) & (DWORD)0x00ff00ff) |			\
	(ROTL((dwS), 24) & (DWORD)0xff00ff00) )				\

/************************ Constants for Key schedule **************************/
#define KC0     0x9e3779b9UL
#define KC1     0x3c6ef373UL
#define KC2     0x78dde6e6UL
#define KC3     0xf1bbcdccUL
#define KC4     0xe3779b99UL
#define KC5     0xc6ef3733UL
#define KC6     0x8dde6e67UL
#define KC7     0x1bbcdccfUL
#define KC8     0x3779b99eUL
#define KC9     0x6ef3733cUL
#define KC10    0xdde6e678UL
#define KC11    0xbbcdccf1UL
#define KC12    0x779b99e3UL
#define KC13    0xef3733c6UL
#define KC14    0xde6e678dUL
#define KC15    0xbcdccf1bUL

#define RoundKeyUpdate0(K, A, B, C, D, KC) {	\
    T0 = A + C - KC;                            \
    T1 = B + KC - D;                            \
    (K)[0] = SS0[GetB0(T0)] ^ SS1[GetB1(T0)] ^  \
             SS2[GetB2(T0)] ^ SS3[GetB3(T0)];   \
    (K)[1] = SS0[GetB0(T1)] ^ SS1[GetB1(T1)] ^  \
             SS2[GetB2(T1)] ^ SS3[GetB3(T1)];   \
    T0 = A;                                     \
    A = (A>>8) ^ (B<<24);                       \
    B = (B>>8) ^ (T0<<24);                      \
}

#define RoundKeyUpdate1(K, A, B, C, D, KC) {	\
    T0 = A + C - KC;                            \
    T1 = B + KC - D;                            \
    (K)[0] = SS0[GetB0(T0)] ^ SS1[GetB1(T0)] ^  \
             SS2[GetB2(T0)] ^ SS3[GetB3(T0)];   \
    (K)[1] = SS0[GetB0(T1)] ^ SS1[GetB1(T1)] ^  \
             SS2[GetB2(T1)] ^ SS3[GetB3(T1)];   \
    T0 = C;                                     \
    C = (C<<8) ^ (D>>24);                       \
    D = (D<<8) ^ (T0>>24);                      \
}

#define BLOCK_XOR_CBC( OUT_VALUE, IN_VALUE1, IN_VALUE2 ) {	\
	OUT_VALUE[0] = IN_VALUE1[0] ^ IN_VALUE2[0];			\
	OUT_VALUE[1] = IN_VALUE1[1] ^ IN_VALUE2[1];			\
	OUT_VALUE[2] = IN_VALUE1[2] ^ IN_VALUE2[2];			\
	OUT_VALUE[3] = IN_VALUE1[3] ^ IN_VALUE2[3];			\
}

void KISA_SEED_Encrypt_Block_forCBC( unsigned int *in, unsigned int *out, KISA_SEED_KEY *ks )
{
	DWORD L0, L1, R0, R1;		// Iuput/output values at each rounds
	DWORD T0, T1;				// Temporary variables for round function F
	DWORD *K = ks->key_data;	// Pointer of round keys

// Set up input values for first round
	L0 = (((unsigned char*)in)[3] << 24) | (((unsigned char*)in)[2] << 16) | (((unsigned char*)in)[1] << 8) | (((unsigned char*)in)[0]);
	L1 = (((unsigned char*)in)[7] << 24) | (((unsigned char*)in)[6] << 16) | (((unsigned char*)in)[5] << 8) | (((unsigned char*)in)[4]);
	R0 = (((unsigned char*)in)[11] << 24) | (((unsigned char*)in)[10] << 16) | (((unsigned char*)in)[9] << 8) | (((unsigned char*)in)[8]);
	R1 = (((unsigned char*)in)[15] << 24) | (((unsigned char*)in)[14] << 16) | (((unsigned char*)in)[13] << 8) | (((unsigned char*)in)[12]);

// Reorder for big endian
// Because SEED use little endian order in default
#ifdef LITTLE_ENDIAN
    L0 = EndianChange(L0);
    L1 = EndianChange(L1);
    R0 = EndianChange(R0);
    R1 = EndianChange(R1);
#endif

    SeedRound(L0, L1, R0, R1, K   ); 	// Round 1
    SeedRound(R0, R1, L0, L1, K+ 2); 	// Round 2
    SeedRound(L0, L1, R0, R1, K+ 4); 	// Round 3
    SeedRound(R0, R1, L0, L1, K+ 6); 	// Round 4
    SeedRound(L0, L1, R0, R1, K+ 8); 	// Round 5
    SeedRound(R0, R1, L0, L1, K+10); 	// Round 6
    SeedRound(L0, L1, R0, R1, K+12); 	// Round 7
    SeedRound(R0, R1, L0, L1, K+14); 	// Round 8
    SeedRound(L0, L1, R0, R1, K+16); 	// Round 9
    SeedRound(R0, R1, L0, L1, K+18); 	// Round 10
    SeedRound(L0, L1, R0, R1, K+20); 	// Round 11
    SeedRound(R0, R1, L0, L1, K+22); 	// Round 12
    SeedRound(L0, L1, R0, R1, K+24); 	// Round 13
    SeedRound(R0, R1, L0, L1, K+26); 	// Round 14
    SeedRound(L0, L1, R0, R1, K+28); 	// Round 15
    SeedRound(R0, R1, L0, L1, K+30); 	// Round 16

#ifdef LITTLE_ENDIAN
    L0 = EndianChange(L0);
    L1 = EndianChange(L1);
    R0 = EndianChange(R0);
    R1 = EndianChange(R1);
#endif

// Copying output values from last round to pbData
    out[0] = R0;
    out[1] = R1;
    out[2] = L0;
    out[3] = L1;
}

void KISA_SEED_Decrypt_Block_forCBC( unsigned int *in, unsigned int *out, KISA_SEED_KEY *ks )
{
	DWORD L0, L1, R0, R1;		// Iuput/output values at each rounds
	DWORD T0, T1;				// Temporary variables for round function F
	DWORD *K = ks->key_data;		// Pointer of round keys

// Set up input values for first round
	L0 = (((unsigned char*)in)[3] << 24) | (((unsigned char*)in)[2] << 16) | (((unsigned char*)in)[1] << 8) | (((unsigned char*)in)[0]);
	L1 = (((unsigned char*)in)[7] << 24) | (((unsigned char*)in)[6] << 16) | (((unsigned char*)in)[5] << 8) | (((unsigned char*)in)[4]);
	R0 = (((unsigned char*)in)[11] << 24) | (((unsigned char*)in)[10] << 16) | (((unsigned char*)in)[9] << 8) | (((unsigned char*)in)[8]);
	R1 = (((unsigned char*)in)[15] << 24) | (((unsigned char*)in)[14] << 16) | (((unsigned char*)in)[13] << 8) | (((unsigned char*)in)[12]);

// Reorder for big endian
#ifdef LITTLE_ENDIAN
    L0 = EndianChange(L0);
    L1 = EndianChange(L1);
    R0 = EndianChange(R0);
    R1 = EndianChange(R1);
#endif

    SeedRound(L0, L1, R0, R1, K+30); 	// Round 1
    SeedRound(R0, R1, L0, L1, K+28); 	// Round 2
    SeedRound(L0, L1, R0, R1, K+26); 	// Round 3
    SeedRound(R0, R1, L0, L1, K+24); 	// Round 4
    SeedRound(L0, L1, R0, R1, K+22); 	// Round 5
    SeedRound(R0, R1, L0, L1, K+20); 	// Round 6
    SeedRound(L0, L1, R0, R1, K+18); 	// Round 7
    SeedRound(R0, R1, L0, L1, K+16); 	// Round 8
    SeedRound(L0, L1, R0, R1, K+14); 	// Round 9
    SeedRound(R0, R1, L0, L1, K+12); 	// Round 10
    SeedRound(L0, L1, R0, R1, K+10); 	// Round 11
    SeedRound(R0, R1, L0, L1, K+ 8); 	// Round 12
    SeedRound(L0, L1, R0, R1, K+ 6); 	// Round 13
    SeedRound(R0, R1, L0, L1, K+ 4); 	// Round 14
    SeedRound(L0, L1, R0, R1, K+ 2); 	// Round 15
    SeedRound(R0, R1, L0, L1, K+ 0); 	// Round 16

#ifdef LITTLE_ENDIAN
    L0 = EndianChange(L0);
    L1 = EndianChange(L1);
    R0 = EndianChange(R0);
    R1 = EndianChange(R1);
#endif

// Copy output values from last round to pbData
    out[0] = R0;
    out[1] = R1;
    out[2] = L0;
    out[3] = L1;
}

DWORD* chartoint32_for_SEED_CBC( IN BYTE *in, IN int nLen )
{
	unsigned int *data;
	int len,i;

	if(nLen % 4)
		len = (nLen/4)+1;
	else
		len = (nLen/4);

	data = malloc(sizeof(unsigned int) * len);

	for(i=0;i<len;i++)
	{
		data[i] = ((unsigned int*)in)[i];
	}

	return data;
}

BYTE* int32tochar_for_SEED_CBC( IN DWORD *in, IN int nLen )
{
	unsigned char *data;
	int i;

	data = malloc(sizeof(unsigned char) * nLen);

#ifdef LITTLE_ENDIAN
	for(i=0;i<nLen;i++)
	{
		data[i] = (unsigned char)(in[i/4] >> ((i%4)*8));
	}
#else
	for(i=0;i<nLen;i++)
	{
		data[i] = (unsigned char)(in[i/4] >> ((3-(i%4))*8));
	}
#endif

	return data;
}

int SEED_CBC_init( OUT KISA_SEED_INFO *pInfo, IN KISA_ENC_DEC enc, IN BYTE *pbszUserKey, IN BYTE *pbszIV )
{
	DWORD A, B, C, D;							// Iuput/output values at each rounds
	DWORD T0, T1;								// Temporary variable
	DWORD *K;

	if( NULL == pInfo ||
		NULL == pbszUserKey ||
		NULL == pbszIV )
		return 0;

	memset( pInfo, 0, sizeof(KISA_SEED_INFO) );

	K = pInfo->seed_key.key_data;		// Pointer of round keys
	pInfo->encrypt = enc;
	memcpy( pInfo->ivec, pbszIV, 16 );
	pInfo->last_block_flag = pInfo->buffer_length = 0;

// Set up input values for Key Schedule
	A = ((DWORD)pbszUserKey[3] << 24) | ((DWORD)pbszUserKey[2] << 16) | ((DWORD)pbszUserKey[1] << 8) | ((DWORD)pbszUserKey[0]);
	B = ((DWORD)pbszUserKey[7] << 24) | ((DWORD)pbszUserKey[6] << 16) | ((DWORD)pbszUserKey[5] << 8) | ((DWORD)pbszUserKey[4]);
	C = ((DWORD)pbszUserKey[11] << 24) | ((DWORD)pbszUserKey[10] << 16) | ((DWORD)pbszUserKey[9] << 8) | ((DWORD)pbszUserKey[8]);
	D = ((DWORD)pbszUserKey[15] << 24) | ((DWORD)pbszUserKey[14] << 16) | ((DWORD)pbszUserKey[13] << 8) | ((DWORD)pbszUserKey[12]);

// Reorder for big endian
#ifdef LITTLE_ENDIAN
	A = EndianChange(A);
	B = EndianChange(B);
	C = EndianChange(C);
	D = EndianChange(D);
#endif

// i-th round keys( K_i,0 and K_i,1 ) are denoted as K[2*(i-1)] and K[2*i-1], respectively
    RoundKeyUpdate0(K   , A, B, C, D, KC0 );	// K_1,0 and K_1,1
    RoundKeyUpdate1(K+ 2, A, B, C, D, KC1 );	// K_2,0 and K_2,1
    RoundKeyUpdate0(K+ 4, A, B, C, D, KC2 );	// K_3,0 and K_3,1
    RoundKeyUpdate1(K+ 6, A, B, C, D, KC3 );	// K_4,0 and K_4,1
    RoundKeyUpdate0(K+ 8, A, B, C, D, KC4 );	// K_5,0 and K_5,1
    RoundKeyUpdate1(K+10, A, B, C, D, KC5 );	// K_6,0 and K_6,1
    RoundKeyUpdate0(K+12, A, B, C, D, KC6 );	// K_7,0 and K_7,1
    RoundKeyUpdate1(K+14, A, B, C, D, KC7 );	// K_8,0 and K_8,1
    RoundKeyUpdate0(K+16, A, B, C, D, KC8 );	// K_9,0 and K_9,1
    RoundKeyUpdate1(K+18, A, B, C, D, KC9 );	// K_10,0 and K_10,1
    RoundKeyUpdate0(K+20, A, B, C, D, KC10);	// K_11,0 and K_11,1
    RoundKeyUpdate1(K+22, A, B, C, D, KC11);	// K_12,0 and K_12,1
    RoundKeyUpdate0(K+24, A, B, C, D, KC12);	// K_13,0 and K_13,1
    RoundKeyUpdate1(K+26, A, B, C, D, KC13);	// K_14,0 and K_14,1
    RoundKeyUpdate0(K+28, A, B, C, D, KC14);	// K_15,0 and K_15,1

    T0 = A + C - KC15;
    T1 = B - D + KC15;
    K[30] = SS0[GetB0(T0)] ^ SS1[GetB1(T0)] ^	// K_16,0
           SS2[GetB2(T0)] ^ SS3[GetB3(T0)];
    K[31] = SS0[GetB0(T1)] ^ SS1[GetB1(T1)] ^	// K_16,1
           SS2[GetB2(T1)] ^ SS3[GetB3(T1)];

	return 1;
}

int SEED_CBC_Process( OUT KISA_SEED_INFO *pInfo, IN DWORD *in, IN int inLen, OUT DWORD *out, OUT int *outLen )
{
	int nCurrentCount = BLOCK_SIZE_SEED;
	DWORD *pdwXOR;

	if( NULL == pInfo ||
		NULL == in ||
		NULL == out ||
		0 > inLen )
		return 0;

	pInfo->buffer_length = inLen - nCurrentCount;

	if( KISA_ENCRYPT == pInfo->encrypt )
	{
		pdwXOR = pInfo->ivec;

		while( nCurrentCount <= inLen )
		{
			BLOCK_XOR_CBC( out, in, pdwXOR );
			KISA_SEED_Encrypt_Block_forCBC( out, out, &pInfo->seed_key );
			pdwXOR = out;
			nCurrentCount += BLOCK_SIZE_SEED;
			in += BLOCK_SIZE_SEED_INT;
			out += BLOCK_SIZE_SEED_INT;
		}

		*outLen = nCurrentCount - BLOCK_SIZE_SEED;
		pInfo->buffer_length = inLen - *outLen;

		memcpy( pInfo->ivec, pdwXOR, BLOCK_SIZE_SEED );
		memcpy( pInfo->cbc_buffer, in, pInfo->buffer_length );
	}
	else
	{
		pdwXOR = pInfo->ivec;

		while( nCurrentCount <= inLen )
		{
			KISA_SEED_Decrypt_Block_forCBC( in, out, &pInfo->seed_key );

			BLOCK_XOR_CBC( out, out, pdwXOR );

			pdwXOR = in;

			nCurrentCount += BLOCK_SIZE_SEED;
			in += BLOCK_SIZE_SEED_INT;
			out += BLOCK_SIZE_SEED_INT;
		}

		*outLen = nCurrentCount - BLOCK_SIZE_SEED;
		memcpy( pInfo->ivec, pdwXOR, BLOCK_SIZE_SEED );
		memcpy( pInfo->cbc_last_block, out - BLOCK_SIZE_SEED_INT, BLOCK_SIZE_SEED );

	}

	return 1;
}

int SEED_CBC_Close( OUT KISA_SEED_INFO *pInfo, IN DWORD *out, IN int *outLen )
{
	unsigned int nPaddngLeng;
	int i;
	BYTE *pOut = (BYTE *)(out);

	*outLen = 0;

	if( NULL == out )
		return 0;

	if( KISA_ENCRYPT == pInfo->encrypt )
	{
		nPaddngLeng = BLOCK_SIZE_SEED - pInfo->buffer_length;
		for( i = pInfo->buffer_length; i<BLOCK_SIZE_SEED; i++ )
			((BYTE *)pInfo->cbc_buffer)[i] = (BYTE)nPaddngLeng;

		BLOCK_XOR_CBC( pInfo->cbc_buffer, pInfo->cbc_buffer, pInfo->ivec );

		KISA_SEED_Encrypt_Block_forCBC( pInfo->cbc_buffer, out, &pInfo->seed_key );
		out += BLOCK_SIZE_SEED_INT;
		*outLen = BLOCK_SIZE_SEED;
	}
	else
	{
		nPaddngLeng = ((BYTE*)pInfo->cbc_last_block)[BLOCK_SIZE_SEED-1];

		if( nPaddngLeng > 0 && nPaddngLeng <= BLOCK_SIZE_SEED )
		{
			for (i = nPaddngLeng; i>0; i--)
			{
				*(pOut - i) = (BYTE)0x00;
			}
			*outLen = nPaddngLeng;
		}
		else
			return 0;
	}

	return 1;
}

int SEED_CBC_Encrypt( IN BYTE *pbszUserKey, IN BYTE *pbszIV, IN BYTE *pbszPlainText, IN int nPlainTextLen, OUT BYTE *pbszCipherText )
{
	KISA_SEED_INFO info;
	unsigned int *outbuf;
	unsigned int *data;
	unsigned char *newpbszPlainText;
	unsigned char *cdata;
	int outlen = 0;
	int nRetOutLeng = 0;
	int nPaddingLeng = 0;
	int i;
	int nPlainTextPadding = (BLOCK_SIZE_SEED - (nPlainTextLen % BLOCK_SIZE_SEED));
	newpbszPlainText = malloc(sizeof(unsigned char) * (nPlainTextLen + nPlainTextPadding));
	memcpy(newpbszPlainText, pbszPlainText, nPlainTextLen);

	SEED_CBC_init( &info, KISA_ENCRYPT, pbszUserKey, pbszIV );

	outlen = ((nPlainTextLen/16) + 1) *4 ;
	outbuf = malloc(sizeof(unsigned int) * outlen);

	data = chartoint32_for_SEED_CBC(newpbszPlainText, nPlainTextLen);
	SEED_CBC_Process( &info, data, nPlainTextLen, outbuf, &nRetOutLeng );

	SEED_CBC_Close( &info, outbuf + (nRetOutLeng)/4, &nPaddingLeng );

	cdata = int32tochar_for_SEED_CBC(outbuf, nRetOutLeng + nPaddingLeng);
	memcpy(pbszCipherText, cdata, nRetOutLeng + nPaddingLeng);

	free(data);
	free(cdata);
	free(outbuf);

	return nRetOutLeng+nPaddingLeng;
}

int SEED_CBC_Decrypt( IN BYTE *pbszUserKey, IN BYTE *pbszIV, IN BYTE *pbszCipherText, IN int nCipherTextLen, OUT BYTE *result )
{
	KISA_SEED_INFO info;
	unsigned int *outbuf;
	unsigned int *data;
	BYTE *newpbszCipherText;
	BYTE *pbszPlainText;
	unsigned char *cdata;
	int outlen = 0;
	int nRetOutLeng = 0;
	int nPaddingLeng = 0;
	int message_length = 0;

	if ((nCipherTextLen % BLOCK_SIZE_SEED) > 0)
	{
		return 0;
	}

	newpbszCipherText = malloc(sizeof(unsigned char) * (nCipherTextLen));
	memcpy(newpbszCipherText, pbszCipherText, nCipherTextLen);

	pbszPlainText = malloc(sizeof(unsigned char) * (nCipherTextLen));

	SEED_CBC_init( &info, KISA_DECRYPT, pbszUserKey, pbszIV );

	outlen = (nCipherTextLen/16) * 4;
	outbuf = malloc(sizeof(unsigned int) * outlen);

	data = chartoint32_for_SEED_CBC(newpbszCipherText, nCipherTextLen);
	SEED_CBC_Process( &info, data, nCipherTextLen, outbuf, &nRetOutLeng );
	if (SEED_CBC_Close( &info, outbuf + (nRetOutLeng)/4, &nPaddingLeng ) > 0)
	{
		cdata = int32tochar_for_SEED_CBC( outbuf, nRetOutLeng - nPaddingLeng );
		memcpy( pbszPlainText, cdata, nRetOutLeng - nPaddingLeng );
		message_length = nRetOutLeng - nPaddingLeng;

		if (message_length < 0)
		{
			message_length = 0;
		}

		memcpy( result, pbszPlainText, message_length);

		free(data);
		free(cdata);
		free(outbuf);

		return message_length;
	}
	else
		return 0;

}
/*
// method 1 start
void main()
{

	BYTE pbszUserKey[16] = {0x088, 0x0e3, 0x04f, 0x08f, 0x008, 0x017, 0x079, 0x0f1, 0x0e9, 0x0f3, 0x094, 0x037, 0x00a, 0x0d4, 0x005, 0x089};
	BYTE pbszIV[16] = {0x026, 0x08d, 0x066, 0x0a7, 0x035, 0x0a8, 0x01a, 0x081, 0x06f, 0x0ba, 0x0d9, 0x0fa, 0x036, 0x016, 0x025, 0x001};
	BYTE plainText[71] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
	BYTE pbszCipherText[80] = {0x00};
	BYTE pbszPlainText[80] = {0x00};
	int i;
	int nPlainTextLen;
	int nCipherTextLen;

	printf ("Key        : ");
	for (i=0;i<16;i++)	{printf("%02X ",pbszUserKey[i]);}

	printf ("\nIV       : ");
	for (i=0;i<16;i++)	{printf("%02X ",pbszIV[i]);}

	printf ("\n\nLength of Plaintext : ");
	scanf("%d", &nPlainTextLen);

	printf ("\nPlaintext(%d)  : ", nPlainTextLen);
	for (i=0;i<nPlainTextLen;i++)	{printf("%02X ",plainText[i]);}

	printf ("\nEncryption....\n");
	// Encryption Algorithm //
	nCipherTextLen = SEED_CBC_Encrypt( pbszUserKey, pbszIV, plainText, nPlainTextLen, pbszCipherText );

	printf ("\nCiphertext(%d) : ", nCipherTextLen);
	for (i=0;i<nCipherTextLen;i++)	{printf("%02X ",pbszCipherText[i]);}

	printf ("\n\nLength of Ciphertext : ");
	scanf("%d", &nCipherTextLen);

	printf ("\nCiphertext(%d) : ", nCipherTextLen);
	for (i=0;i<nCipherTextLen;i++)	{printf("%02X ",pbszCipherText[i]);}

	printf ("\n\nDecryption....");

	// Decryption Algorithm //
	nPlainTextLen = SEED_CBC_Decrypt( pbszUserKey, pbszIV, pbszCipherText, nCipherTextLen, pbszPlainText );

	printf ("\nPlaintext(%d)  : ", nPlainTextLen);
	for (i=0;i<nPlainTextLen;i++)	{printf("%02X ",pbszPlainText[i]);}

	printf ("\n");

}
// method 1 end
*/

// method 2 start
//void main()
//{
//	BYTE pbszUserKey[16] = {0x088, 0x0e3, 0x04f, 0x08f, 0x008, 0x017, 0x079, 0x0f1, 0x0e9, 0x0f3, 0x094, 0x037, 0x00a, 0x0d4, 0x005, 0x089};
//	BYTE pbszIV[16] = {0x026, 0x08d, 0x066, 0x0a7, 0x035, 0x0a8, 0x01a, 0x081, 0x06f, 0x0ba, 0x0d9, 0x0fa, 0x036, 0x016, 0x025, 0x001};
//	BYTE plainText[71] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
//		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
//		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
//		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
//		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
//	BYTE pbszCipherText[80] = {0x00};
//	BYTE pbszPlainText[80] = {0x00};
//	KISA_SEED_INFO info;
//	int i;
//	int nPlainTextLen = 0;
//	int nCipherTextLen = 0;
//	int message_length = 0;
//	int EncryptedMessage_length = 0;
//	#define process_blockLeng	32
//	unsigned int *outbuf;
//	unsigned char *PlainBytes = (BYTE *)(plainText);
//	unsigned char *CipherBytes = (BYTE *)(pbszCipherText);
//	unsigned int *data;
//	unsigned char *cdata;
//	int nRetOutLeng = 0;
//	int remainleng = 0;
//	int nPaddingLeng = 0;
//
//	printf ("Key        : ");
//	for (i=0;i<16;i++)	{printf("%02X ",pbszUserKey[i]);}
//
//	printf ("\nIV       : ");
//	for (i=0;i<16;i++)	{printf("%02X ",pbszIV[i]);}
//
//	printf ("\n\nLength of Plaintext : ");
//	scanf("%d", &nPlainTextLen);
//
//	printf ("\nPlaintext(%d)  : ", nPlainTextLen);
//	for (i=0;i<nPlainTextLen;i++)	{printf("%02X ",plainText[i]);}
//
//	printf ("\nEncryption....\n");
//	// Encryption Algorithm //
//	message_length = nPlainTextLen;
//
//	SEED_CBC_init( &info, KISA_ENCRYPT, pbszUserKey, pbszIV );
//	outbuf = malloc(sizeof(unsigned int) * process_blockLeng);
//	for (i = 0; i < message_length - process_blockLeng; )
//	{
//		memcpy( pbszPlainText, PlainBytes + i, process_blockLeng );
//		data = chartoint32_for_SEED_CBC(pbszPlainText, process_blockLeng);
//		SEED_CBC_Process( &info, data, process_blockLeng, outbuf, &nRetOutLeng );
//		cdata = int32tochar_for_SEED_CBC( outbuf, nRetOutLeng);
//		memcpy( CipherBytes + i, cdata, nRetOutLeng );
//		i += nRetOutLeng;
//	}
//	remainleng = message_length % process_blockLeng;
//	if (remainleng == 0)
//	{
//		remainleng = process_blockLeng;
//	}
//	memcpy( pbszPlainText, PlainBytes + i, remainleng );
//	data = chartoint32_for_SEED_CBC(pbszPlainText, remainleng);
//	SEED_CBC_Process( &info, data, remainleng, outbuf, &nRetOutLeng );
//	cdata = int32tochar_for_SEED_CBC( outbuf, nRetOutLeng);
//	memcpy( CipherBytes + i, cdata, nRetOutLeng );
//	i += nRetOutLeng;
//	free(cdata);
//	SEED_CBC_Close( &info, outbuf, &nPaddingLeng );
//	cdata = int32tochar_for_SEED_CBC(outbuf, nPaddingLeng);
//	memcpy(CipherBytes + i, cdata, nPaddingLeng);
//
//	free(data);
//	free(cdata);
//
//	nCipherTextLen = i + nPaddingLeng;
//
//	printf ("\nCiphertext(%d) : ", nCipherTextLen);
//	for (i=0;i<nCipherTextLen;i++)	{printf("%02X ",CipherBytes[i]);}
//
//	printf ("\n\nLength of Ciphertext : ");
//	scanf("%d", &nCipherTextLen);
//
//	printf ("\nCiphertext(%d) : ", nCipherTextLen);
//	for (i=0;i<nCipherTextLen;i++)	{printf("%02X ",CipherBytes[i]);}
//
//	printf ("\n\nDecryption....");
//
//	// Decryption Algorithm //
//	EncryptedMessage_length = nCipherTextLen;
//	if (EncryptedMessage_length % BLOCK_SIZE_SEED > 0)
//	{
//		nPlainTextLen = 0;
//	}
//	else
//	{
//		SEED_CBC_init( &info, KISA_DECRYPT, pbszUserKey, pbszIV );
//
//		for (i = 0; i < EncryptedMessage_length - process_blockLeng; )
//		{
//			memcpy( pbszCipherText, CipherBytes + i, process_blockLeng );
//			data = chartoint32_for_SEED_CBC(pbszCipherText, process_blockLeng);
//			SEED_CBC_Process( &info, data, process_blockLeng, outbuf, &nRetOutLeng );
//			cdata = int32tochar_for_SEED_CBC( outbuf, nRetOutLeng);
//			memcpy( PlainBytes + i, cdata, nRetOutLeng );
//			i += nRetOutLeng;
//		}
//		remainleng = EncryptedMessage_length % process_blockLeng;
//		if (remainleng == 0)
//		{
//			remainleng = process_blockLeng;
//		}
//		memcpy( pbszCipherText, CipherBytes + i, remainleng );
//		data = chartoint32_for_SEED_CBC(pbszCipherText, remainleng);
//		SEED_CBC_Process( &info, data, remainleng, outbuf, &nRetOutLeng );
//		if (SEED_CBC_Close( &info, outbuf + (nRetOutLeng)/4, &nPaddingLeng ) > 0)
//		{
//			cdata = int32tochar_for_SEED_CBC(outbuf, remainleng - nPaddingLeng);
//			memcpy(PlainBytes + i, cdata, remainleng - nPaddingLeng);
//			message_length = i + remainleng - nPaddingLeng;
//
//			free(data);
//			free(cdata);
//			free(outbuf);
//
//			nPlainTextLen = message_length;
//		}
//		else
//		{
//			nPlainTextLen = 0;
//		}
//	}
//
//	printf ("\nPlaintext(%d)  : ", nPlainTextLen);
//	for (i=0;i<nPlainTextLen;i++)	{printf("%02X ",PlainBytes[i]);}
//
//	printf ("\n");
//
//}
// method 2 end