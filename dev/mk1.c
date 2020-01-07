// MTE MK1 (la Churrera) v3.99.99 (final)
// Copyleft 2010-2017 by the Mojon Twins

// mk1.c
// Esqueleto de juegos de la churrera
// Copyleft 2010-2014 The Mojon Twins

#include <spritepack.h>

// NUMBLOCKS es el n�mero de bloques necesario para mover los sprites
// Configurar bien este n�mero es MUY IMPORTANTE

#define NUMBLOCKS 40

// La regla es esta: cada sprite de 16x16 ocupa 10 bloques.
// Cada proyectil ocupa 5 bloques.

// Si, por ejemplo, tu juego no tiene disparos, s�lo necesitas bloques
// para el sprite principal y tres enemigos, o sea, 4*10 = 40 bloques.

// Si, por ejemplo, tu juego adem�s lleva 3 proyectiles, necesitar�s
// 4*10 + 3*5 = 55 bloques.

// Versi�n para 48K
#pragma output STACKPTR=61952
#define FREEPOOL 61440
#define AD_FREE FREEPOOL - NUMBLOCKS * 15

// Versi�n para 128K
//#pragma output STACKPTR=24199
//#define FREEPOOL 61697
//#define AD_FREE 61440 - NUMBLOCKS * 15

// Optimal place to compile if using COMPRESSED_LEVELS:
// 23296 + MAP_W * MAP_H * (108) + MAX_CERROJOS * 4 + 49

#include "config.h"

// Cosas del juego:

#include "definitions.h"

#ifdef ACTIVATE_SCRIPTING
	#include "msc-config.h"
#endif

#ifdef MODE_128K
	#include "128k.h"
#endif

#include "aplib.h"
#include "pantallas.h"

#ifdef MODE_128K
	#include "librarian.h"
	
	#ifdef COMPRESSED_LEVELS
		#include "levels128.h"
	#else
		#include "mapa.h"
		#include "tileset.h"
		#include "sprites.h"
		#include "extrasprites.h"
		#include "enems.h"
	#endif

#else

	#ifdef COMPRESSED_LEVELS
		#include "levels.h"
	#else
		#include "mapa.h"
	#endif

	#include "tileset.h"
	#include "sprites.h"
	#include "extrasprites.h"
	
	#ifndef COMPRESSED_LEVELS
		#include "enems.h"
	#endif

#endif

#ifdef MODE_128K
	#include "wyzplayer.h"
#else
	#include "beeper.h"
#endif

#include "printer.h"

#ifdef ACTIVATE_SCRIPTING
	#ifdef ENABLE_EXTERN_CODE
		#include "extern.h"
	#endif
	#include "msc.h"
#endif

#include "engine.h"

#ifdef ENABLE_CHECKPOINTS
	#include "savegame.h"
#endif

#include "mainloop.h"

#ifndef MODE_128K
// From beepola. Phaser engine by Shiru.
#include "music.h"
#endif
