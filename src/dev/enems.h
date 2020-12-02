// MTE MK1 (la Churrera) v4
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Generated by ene2h.exe from ..\enems\enems.ene
// Copyleft 2010, 2017, 2020 by The Mojon Twins

typedef struct {
	unsigned char x, y;
	unsigned char x1, y1, x2, y2;
	char mx, my;
	char t;
#if defined PLAYER_CAN_FIRE || defined ENABLE_SWORD
	unsigned char life;
#endif
} MALOTE;

MALOTE malotes [] = {
	// Pantalla 0
 	{16, 32, 16, 32, 48, 128, 2, 2, 3},
 	{160, 16, 160, 16, 160, 128, 0, 1, 1},
 	{176, 128, 176, 16, 176, 128, 0, -1, 2},

	// Pantalla 1
 	{128, 128, 16, 128, 128, 128, -1, 0, 4},
 	{144, 16, 144, 16, 144, 80, 0, 1, 2},
 	{48, 16, 48, 16, 48, 80, 0, 1, 3},

	// Pantalla 2
 	{128, 16, 128, 16, 192, 16, 1, 0, 1},
 	{128, 80, 128, 80, 128, 128, 0, 1, 2},
 	{32, 48, 32, 48, 48, 128, 1, 1, 3},

	// Pantalla 3
 	{16, 112, 16, 112, 112, 112, 1, 0, 3},
 	{128, 112, 128, 112, 192, 112, 1, 0, 2},
 	{176, 128, 32, 128, 176, 128, -1, 0, 4},

	// Pantalla 4
 	{208, 16, 208, 16, 208, 128, 0, 1, 1},
 	{128, 80, 128, 48, 128, 80, 0, -1, 2},
 	{16, 112, 16, 112, 64, 112, 1, 0, 4},

	// Pantalla 5
 	{96, 64, 96, 16, 96, 64, 0, -1, 2},
 	{128, 16, 128, 16, 128, 112, 0, 2, 3},
 	{16, 112, 16, 112, 112, 112, 1, 0, 4},

	// Pantalla 6
 	{208, 64, 16, 64, 208, 64, -2, 0, 3},
 	{48, 32, 48, 32, 208, 32, 1, 0, 4},
 	{208, 112, 32, 112, 208, 112, -1, 0, 2},

	// Pantalla 7
 	{128, 128, 128, 16, 128, 128, 0, -1, 3},
 	{160, 32, 160, 32, 160, 128, 0, 1, 2},
 	{48, 32, 48, 16, 48, 32, 0, 0, 4},

	// Pantalla 8
 	{32, 32, 32, 32, 80, 32, 1, 0, 2},
 	{96, 32, 96, 32, 128, 32, 1, 0, 1},
 	{144, 32, 144, 32, 208, 32, 1, 0, 3},

	// Pantalla 9
 	{208, 128, 208, 16, 208, 128, 0, -1, 3},
 	{48, 96, 48, 96, 144, 96, 1, 0, 2},
 	{64, 16, 48, 16, 64, 32, -1, 1, 2},

	// Pantalla 10
 	{208, 48, 64, 48, 208, 48, -1, 0, 1},
 	{16, 96, 16, 96, 192, 96, 1, 0, 2},
 	{16, 16, 16, 16, 32, 16, 0, 0, 3},

	// Pantalla 11
 	{32, 16, 32, 16, 192, 128, 2, 2, 3},
 	{160, 16, 16, 16, 160, 96, -1, 1, 1},
 	{208, 48, 128, 48, 208, 128, -1, 1, 3},

	// Pantalla 12
 	{32, 32, 32, 32, 48, 32, 1, 0, 11},
 	{112, 16, 112, 16, 128, 16, 1, 0, 12},
 	{160, 64, 160, 64, 176, 64, 2, 0, 13},

	// Pantalla 13
 	{80, 16, 80, 16, 80, 128, 0, 1, 1},
 	{128, 112, 128, 32, 128, 112, 0, -1, 4},
 	{176, 16, 176, 16, 176, 112, 0, 1, 2},

	// Pantalla 14
 	{208, 16, 16, 16, 208, 16, -2, 0, 3},
 	{16, 112, 16, 112, 176, 112, 2, 0, 3},
 	{96, 48, 16, 48, 96, 48, -1, 0, 4},

	// Pantalla 15
 	{16, 32, 16, 32, 16, 112, 0, 2, 3},
 	{112, 16, 112, 16, 112, 96, 0, 1, 2},
 	{160, 48, 160, 48, 160, 112, 0, 1, 4},

	// Pantalla 16
 	{128, 16, 128, 16, 128, 128, 0, 2, 1},
 	{96, 16, 96, 16, 96, 128, 0, 2, 2},
 	{16, 64, 16, 64, 96, 112, 1, 1, 3},

	// Pantalla 17
 	{32, 32, 32, 32, 192, 32, 1, 0, 1},
 	{160, 48, 160, 48, 192, 128, 2, 2, 2},
 	{176, 112, 32, 112, 176, 128, -1, 1, 3},

	// Pantalla 18
 	{48, 32, 48, 32, 144, 48, 1, 1, 2},
 	{144, 112, 48, 112, 144, 112, -1, 0, 4},
 	{16, 16, 16, 16, 16, 128, 0, 1, 1},

	// Pantalla 19
 	{48, 16, 48, 16, 80, 80, 1, 1, 1},
 	{32, 80, 32, 80, 48, 80, 1, 0, 2},
 	{32, 112, 32, 112, 32, 112, 0, 0, 4},

	// Pantalla 20
 	{64, 64, 64, 64, 64, 128, 0, 1, 2},
 	{96, 112, 96, 64, 96, 112, 0, -1, 3},
 	{208, 112, 208, 16, 208, 112, 0, -1, 4},

	// Pantalla 21
 	{16, 128, 16, 16, 96, 128, 2, -2, 2},
 	{192, 16, 192, 16, 192, 128, 0, 1, 1},
 	{160, 128, 160, 48, 160, 128, 0, -1, 3},

	// Pantalla 22
 	{32, 16, 32, 16, 96, 128, 1, 1, 4},
 	{128, 16, 128, 16, 128, 128, 0, 1, 2},
 	{192, 16, 192, 16, 192, 112, 0, 1, 3},

	// Pantalla 23
 	{32, 112, 32, 112, 208, 112, 1, 0, 4},
 	{208, 80, 208, 16, 208, 80, 0, -1, 1},
 	{112, 32, 16, 32, 112, 32, -1, 0, 2},

	// Pantalla 24
 	{112, 112, 16, 112, 112, 112, -1, 0, 2},
 	{32, 80, 32, 16, 32, 80, 0, -1, 4},
 	{80, 80, 80, 32, 80, 80, 0, -1, 2}

};

#define N_ENEMS_TYPE_0 0
#define N_ENEMS_TYPE_1 13
#define N_ENEMS_TYPE_2 24
#define N_ENEMS_TYPE_3 20
#define N_ENEMS_TYPE_5 0
#define N_ENEMS_TYPE_6 0
#define N_ENEMS_TYPE_7 0
#define N_ENEMS_TYPE_11 1
#define N_ENEMS_TYPE_12 1
#define N_ENEMS_TYPE_13 1

// This is output the way it worked originally, please modify if you need
// You may want to add type 5 or 6's below.
#define BADDIES_COUNT (N_ENEMS_TYPE_1+N_ENEMS_TYPE_2+N_ENEMS_TYPE_3)

typedef struct {
	unsigned char xy, tipo, act;
} HOTSPOT;

HOTSPOT hotspots [] = {
	{17, 2, 0}, 
	{85, 1, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{113, 1, 0}, 
	{0, 0, 0}, 
	{151, 1, 0}, 
	{18, 1, 0}, 
	{33, 1, 0}, 
	{214, 1, 0}, 
	{209, 1, 0}, 
	{0, 0, 0}, 
	{212, 1, 0}, 
	{210, 1, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{72, 2, 0}, 
	{49, 1, 0}, 
	{114, 1, 0}, 
	{23, 1, 0}, 
	{102, 1, 0}, 
	{210, 2, 0}, 
	{130, 1, 0}, 
	{0, 0, 0}
};

#define N_HOTSPOTS_TYPE_0 8
#define N_HOTSPOTS_TYPE_1 14
#define N_HOTSPOTS_TYPE_2 3
#define N_HOTSPOTS_TYPE_3 0
#define N_HOTSPOTS_TYPE_4 0
#define N_HOTSPOTS_TYPE_5 0
#define N_HOTSPOTS_TYPE_6 0
#define N_HOTSPOTS_TYPE_7 0

