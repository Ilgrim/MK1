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
 	{112, 112, 112, 112, 96, 16, -2, -2, 2},
 	{112, 32, 112, 32, 96, 112, -2, 2, 1},
 	{80, 64, 80, 64, 16, 64, -1, 0, 3},

	// Pantalla 1
 	{80, 112, 80, 112, 80, 64, 0, -1, 2},
 	{64, 112, 64, 112, 16, 64, -2, -2, 3},
 	{160, 112, 160, 112, 160, 32, 0, -1, 4},

	// Pantalla 2
 	{32, 112, 32, 112, 176, 112, 2, 0, 3},
 	{192, 16, 192, 16, 192, 96, 0, 1, 1},
 	{80, 80, 80, 80, 112, 80, 1, 0, 2},

	// Pantalla 3
 	{48, 32, 48, 32, 16, 32, -1, 0, 3},
 	{208, 32, 208, 32, 80, 48, -1, 1, 2},
 	{208, 96, 208, 96, 112, 96, -1, 0, 4},

	// Pantalla 4
 	{96, 32, 96, 32, 208, 32, 1, 0, 2},
 	{80, 128, 80, 128, 80, 48, 0, -2, 4},
 	{16, 32, 16, 32, 48, 128, 1, 1, 3},

	// Pantalla 5
 	{80, 16, 80, 16, 80, 128, 0, 1, 3},
 	{64, 64, 64, 64, 16, 128, -2, 2, 2},
 	{64, 32, 64, 32, 16, 32, -1, 0, 1},

	// Pantalla 6
 	{208, 128, 208, 128, 16, 128, -1, 0, 4},
 	{128, 64, 128, 64, 96, 64, -1, 0, 2},
 	{32, 16, 32, 16, 64, 112, 2, 2, 3},

	// Pantalla 7
 	{80, 128, 80, 128, 80, 32, 0, -1, 4},
 	{144, 48, 144, 48, 208, 64, 1, 1, 2},
 	{208, 128, 208, 128, 128, 128, -1, 0, 3},

	// Pantalla 8
 	{80, 96, 80, 96, 80, 16, 0, -1, 1},
 	{112, 48, 112, 48, 224, 112, 2, 2, 2},
 	{128, 128, 128, 128, 112, 128, -1, 0, 3},

	// Pantalla 9
 	{64, 128, 64, 128, 224, 128, 1, 0, 4},
 	{48, 16, 48, 16, 48, 128, 0, 2, 2},
 	{96, 48, 96, 48, 208, 96, 1, 1, 3},

	// Pantalla 10
 	{208, 80, 208, 80, 144, 48, -1, -1, 3},
 	{128, 80, 128, 80, 96, 32, -1, -1, 2},
 	{64, 112, 64, 112, 64, 48, 0, -1, 1},

	// Pantalla 11
 	{48, 48, 48, 48, 192, 48, 2, 0, 2},
 	{192, 80, 192, 80, 64, 80, -1, 0, 3},
 	{80, 112, 80, 112, 208, 112, 1, 0, 1},

	// Pantalla 12
 	{160, 112, 160, 112, 160, 80, 0, -1, 4},
 	{112, 112, 112, 112, 112, 48, 0, -2, 2},
 	{128, 16, 128, 16, 208, 16, 1, 0, 3},

	// Pantalla 13
 	{16, 48, 16, 48, 96, 96, 2, 2, 1},
 	{96, 16, 96, 16, 48, 16, -1, 0, 2},
 	{16, 112, 16, 112, 32, 112, 1, 0, 3},

	// Pantalla 14
 	{192, 112, 192, 112, 192, 16, 0, -1, 4},
 	{32, 16, 32, 16, 144, 16, 1, 0, 2},
 	{160, 64, 160, 64, 80, 64, -1, 0, 3},

	// Pantalla 15
 	{64, 80, 64, 80, 32, 32, -1, -1, 3},
 	{64, 16, 64, 16, 32, 128, -1, 1, 2},
 	{160, 16, 160, 16, 160, 128, 0, 2, 3},

	// Pantalla 16
 	{16, 16, 16, 16, 144, 80, 2, 2, 2},
 	{224, 80, 224, 80, 176, 64, -1, -1, 3},
 	{224, 96, 224, 96, 176, 96, -1, 0, 4},

	// Pantalla 17
 	{80, 128, 80, 128, 80, 48, 0, -1, 1},
 	{64, 128, 64, 128, 64, 64, 0, -2, 2},
 	{48, 32, 48, 32, 48, 128, 0, 1, 3},

	// Pantalla 18
 	{64, 112, 64, 112, 64, 16, 0, -1, 2},
 	{112, 64, 112, 64, 128, 144, 2, 2, 2},
 	{144, 16, 144, 16, 224, 64, 2, 2, 3},

	// Pantalla 19
 	{208, 80, 208, 80, 32, 80, -2, 0, 4},
 	{96, 32, 96, 32, 160, 32, 1, 0, 4},
 	{48, 96, 48, 96, 208, 128, 1, 1, 2},

	// Pantalla 20
 	{208, 64, 208, 64, 96, 64, -1, 0, 1},
 	{80, 128, 80, 128, 80, 16, 0, -1, 4},
 	{208, 112, 208, 112, 160, 112, -1, 0, 2},

	// Pantalla 21
 	{48, 16, 48, 16, 80, 48, 1, 1, 3},
 	{144, 112, 144, 112, 144, 16, 0, -2, 1},
 	{112, 112, 112, 112, 48, 112, -2, 0, 2},

	// Pantalla 22
 	{64, 32, 64, 32, 96, 128, 1, 1, 3},
 	{176, 128, 176, 128, 176, 80, 0, -2, 2},
 	{192, 128, 192, 128, 192, 32, 0, -2, 1},

	// Pantalla 23
 	{208, 64, 208, 64, 128, 64, -2, 0, 2},
 	{48, 96, 48, 96, 192, 112, 1, 1, 3},
 	{16, 32, 16, 32, 64, 32, 1, 0, 1}

};

#define N_ENEMS_TYPE_0 0
#define N_ENEMS_TYPE_1 12
#define N_ENEMS_TYPE_2 25
#define N_ENEMS_TYPE_3 23
#define N_ENEMS_TYPE_5 0
#define N_ENEMS_TYPE_6 0
#define N_ENEMS_TYPE_7 0

// This is output the way it worked originally, please modify if you need
// You may want to add type 5 or 6's below.
#define BADDIES_COUNT (N_ENEMS_TYPE_1+N_ENEMS_TYPE_2+N_ENEMS_TYPE_3)

typedef struct {
	unsigned char xy, tipo, act;
} HOTSPOT;

HOTSPOT hotspots [] = {
	{0, 0, 0}, 
	{0, 0, 0}, 
	{211, 2, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{120, 2, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}, 
	{0, 0, 0}
};

#define N_HOTSPOTS_TYPE_0 22
#define N_HOTSPOTS_TYPE_1 0
#define N_HOTSPOTS_TYPE_2 2
#define N_HOTSPOTS_TYPE_3 0
#define N_HOTSPOTS_TYPE_4 0
#define N_HOTSPOTS_TYPE_5 0
#define N_HOTSPOTS_TYPE_6 0
#define N_HOTSPOTS_TYPE_7 0
