// Config.h
// Generado por GameConfig de la churrera
// Copyleft 2010 The Mojon Twins

// ============================================================================
// I. Configuraci�n general del juego
// ============================================================================

// En esta secci�n configuramos las dimensiones del mapa, pantalla y posici�n iniciales,
// pantalla y posici�n finales (si aplica), n�mero de objetos que hay que recoger, etc�tera.

#define MAP_W 					5		//
#define MAP_H					5		// Dimensiones del mapa, en pantallas.
#define SCR_INICIO				15		// Pantalla de inicio
#define PLAYER_INI_X			1		//
#define PLAYER_INI_Y			2		// Coordenadas de inicio del jugador, a nivel de tiles
#define SCR_FIN					99		// Pantalla del final. 99 si da igual.
#define PLAYER_FIN_X			99		//
#define PLAYER_FIN_Y			99		// Posici�n del jugador para terminar, a nivel de tiles
#define PLAYER_NUM_OBJETOS		31		// N�mero de objetos para terminar el juego
#define PLAYER_LIFE				99		// Vida m�xima (con la que empieza, adem�s)
#define PLAYER_REFILL			25		// Recarga de vida.

// ============================================================================
// II. Tipo de motor
// ============================================================================

// En esta secci�n definimos el tipo de motor que ser� compilado con el juego. En esta 
// versi�n 2.0 tenemos dos tipos b�sicos y excluyentes: top-view (MOGGY_STYLE) y de plataformas.
// Para emplear uno u otro deberemos descomentarlo eliminando las marcas /* y */ de principio
// y fin de bloque.

/*
// Motor top-view (MOGGY-STYLE)

#define PLAYER_MOGGY_STYLE				// Vista cenital, movimiento 8-way
#define PLAYER_AUTO_CHANGE_SCREEN		// Si se define, se cambiar� de pantalla sin pulsar una direcci�n.
*/

/*
// Motor de plataformas

#define	PLAYER_HAS_JUMP					// Si se define, el personaje principal SALTA
#define PLAYER_HAS_JETPAC				// Si se define, el personaje principal tiene JET PAC
*/

// Los siguientes defines pueden aplicarse a cualquiera de los dos tipos de motores y definen
// comportamiento extra:

// #define PLAYER_PUSH_BOXES			// Si se define, el jugador podr� empujar los tiles #14

// ============================================================================
// III. Configuraci�n de la pantalla
// ============================================================================

// En esta secci�n colocamos los elementos en la pantalla: la ventana de juego y los tres
// marcadores (vida, objetos y llaves) definiendo su posici�n a nivel de car�cteres.
// Tambi�n definimos si queremos sombreado autom�tico (los tiles obst�culo dejan sombra sobre
// los de segundo plano), y de qu� tipo:

#define VIEWPORT_X				1		//
#define VIEWPORT_Y				0		// Posici�n de la ventana de juego (en car�cteres)
#define LIFE_X					14		//
#define LIFE_Y					21		// Posici�n del marcador de vida (en car�cteres)
#define OBJECTS_X				19		//
#define OBJECTS_Y				21		// Posici�n del marcador de objetos (en car�cteres)
#define KEYS_X					24		//
#define KEYS_Y					21		// Posici�n del marcador de llaves (en car�cteres)

// Sombras: descomentar la que aplique, o ninguna.

//#define USE_AUTO_SHADOWS				// Sombras autom�ticas por atributos
//#define USE_AUTO_TILE_SHADOWS			// Sombras autom�ticas por tiles-

// ============================================================================
// IV. Configuraci�n del movimiento del jugador
// ============================================================================

// En esta secci�n definimos las constantes que gobiernan los par�metros del motor de movimiento.
// En un juego tipo plataformas, definimos por separado el comportamiento en vertical y el compor-
// tamiento en horizontal. Para un juego tipo top-view, los valores definidos en el comportamiento
// horizontal se aplican tambi�n al vertical.

// IV.1. Movimiento vertical, s�lo aplicable al motor de plataformas:

#define PLAYER_MAX_VY_CAYENDO	512		// Velocidad m�xima cuando cae (512/64 = 8 p�xels/frame)
#define PLAYER_G				32		// Aceleraci�n de la gravedad (32/64 = 0.5 p�xeles/frame^2)

#define PLAYER_VY_INICIAL_SALTO	64		// Velocidad inicial al saltar (64/64 = 1 p�xel/frame)
#define PLAYER_MAX_VY_SALTANDO	320		// Velocidad m�xima al saltar (320/64 = 5 p�xels/frame)
#define PLAYER_INCR_SALTO 		48		// Aceleraci�n al pulsar "salto" (48/64 = 0.75 p�xeles/frame^2)

#define PLAYER_INCR_JETPAC		32		// Incremento al usar el jetpac
#define PLAYER_MAX_VY_JETPAC	256		// M�xima velocidad vertical con jetpac

// IV.2. Movimiento horizontal (en motor de plataformas) o general (en motor top-view):

#define PLAYER_MAX_VX			256		// Velocidad m�xima horizontal (192/64 = 3 p�xels/frame)
#define PLAYER_AX				16		// Aceleraci�n horizontal (24/64 = 0,375 p�xels/frame^2)
#define PLAYER_RX				0		// Fricci�n horizontal (32/64 = 0,5 p�xels/frame^2)

// ============================================================================
// V. Comportamiento de los tiles
// ============================================================================

// Indica el comportamiento de cada uno de los 16 tiles. Recuerda que el tile n� 15 (el �ltimo)
// es el cerrojo y debe ser un obst�culo, porque si no, vaya mierda de cerrojo.

// 0 = traspasable.
// 1 = traspasable y mata.
// 2 = obst�culo

unsigned char comportamiento_tiles [] = {
	0, 1, 2, 2, 2, 2, 1, 0, 0, 2, 2, 0, 0, 1, 2, 2
};
