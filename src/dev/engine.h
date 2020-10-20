// MTE MK1 v4.7
// Copyleft 2010, 2011 by The Mojon Twins

// engine.h
// Cointains engine functions (movement, colliding, rendering... )

unsigned int key_1 = 0x01f7;
unsigned int key_2 = 0x02f7;
unsigned int key_3 = 0x04f7;

unsigned char gpit, enit, pad0;

void saca_a_todo_el_mundo_de_aqui () {
	// �Saca a todo el mundo de aqu�!
	sp_MoveSprAbs (sp_player, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);				
	for (gpit = 0; gpit < 3; gpit ++) {
		if (malotes [enoffs + gpit].t != 0)
			sp_MoveSprAbs (sp_moviles [gpit], spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
	}
}

unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	// Secure and dirty box collision.
	unsigned char l1x, l1y, l2x, l2y;
	l1x = (x1 > 13) ? x1 - 13 : 0;
	l2x = x1 + 13;
	l1y = (y1 > 13) ? y1 - 13 : 0;
	l2y = y1 + 13;
	return (x2 >= l1x && x2 <= l2x && y2 >= l1y && y2 <= l2y);
}

void srand (unsigned int new_seed) {
	seed [0] = new_seed;	
}

unsigned char rand () {
	unsigned char res;
	
	#asm
	.rand16
		ld	hl, _seed
		ld	a, (hl)
		ld	e, a
		inc	hl
		ld	a, (hl)
		ld	d, a
		
		;; Ahora DE = [SEED]
					
		ld	a,	d
		ld	h,	e
		ld	l,	253
		or	a
		sbc	hl,	de
		sbc	a, 	0
		sbc	hl,	de
		ld	d, 	0
		sbc	a, 	d
		ld	e,	a
		sbc	hl,	de
		jr	nc,	nextrand
		inc	hl
	.nextrand
		ld	d,	h
		ld	e,	l
		ld	hl, _seed
		ld	a,	e
		ld	(hl), a
		inc	hl
		ld	a,	d
		ld	(hl), a
		
		;; Ahora [SEED] = HL
	
		ld 	hl, _asm_int
		ld	a,	e	
		ld	(hl), a
		inc	hl
		ld	a,	d
		ld	(hl), a
		
		;; Ahora [ASM_INT] = HL
	#endasm
	
	res = asm_int [0];

	return res;
}

unsigned int abs (int n) {
	if (n < 0)
		return (unsigned int) (-n);
	else 
		return (unsigned int) n;
}
	

void step () {
	#asm
		ld a, 16
		out (254), a
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		xor 16
		out (254), a
	#endasm	
}

void cortina () {
	#asm
		;; Antes que nada vamos a limpiar el PAPER de toda la pantalla
		;; para que no queden artefactos feos
		
		ld	de, 22528			; Apuntamos con DE a la zona de atributos
		ld	b,	3				; Procesamos 3 tercios
	.clearb1
		push bc
		
		ld	b, 255				; Procesamos los 256 atributos de cada tercio
	.clearb2
	
		ld	a, (de)				; Nos traemos un atributo
		and	199					; Le hacemos la m�scara 11000111 y dejamos PAPER a 0
		ld	(de), a				; Y lo volvemos a poner
		
		inc de					; Siguiente atributo
	
		djnz clearb2
		
		pop bc
		djnz clearb1
		
		;; Y ahora el c�digo original que escrib� para UWOL:	
	
		ld	a,	8
	
	.repitatodo
		ld	c,	a			; Salvamos el contador de "repitatodo" en 'c'
	
		ld	hl, 16384
		ld	a,	12
	
	.bucle
		ld	b,	a			; Salvamos el contador de "bucle" en 'b'
		ld	a,	255
	
	.bucle1
		sla (hl)
		inc hl
		dec a
		jr	nz, bucle1
			
		ld	a,	255
	.bucle2
		srl (hl)
		inc hl
		dec a
		jr	nz, bucle2
			
		ld	a,	b			; Restituimos el contador de "bucle" a 'a'
		dec a
		jr	nz, bucle
	
		ld	a,	c			; Restituimos el contador de "repitatodo" a 'a'
		dec a
		jr	nz, repitatodo
	#endasm
}

// Game

char espera_activa (int espera) {
	// Waits until "espera" halts have passed 
	// or a key has been pressed.

	#asm 
		ei
	#endasm
	while (espera--)  {
		#asm
			halt
		#endasm
		if (sp_GetKey()) {
			break;
		}
	}
	#asm
		di
	#endasm
}

void game_ending () {
	unsigned char x;
	
	sp_UpdateNow();
	unpack ((unsigned int) (s_ending));
	
	for (x = 0; x < 4; x ++) {
		peta_el_beeper (6);
		peta_el_beeper (3);
	}
	peta_el_beeper (11);
	
	espera_activa (500);
}

void game_over () {
	draw_rectangle (10, 11, 21, 13, 112);		
	draw_text (11, 12, 112, "GAME OVER!");

	sp_UpdateNow ();
		
	for (gpit = 0; gpit < 4; gpit ++) {
		peta_el_beeper (6);
		peta_el_beeper (3);
	}
	peta_el_beeper (10);
	
	espera_activa (500);
}

#ifndef DEACTIVATE_KEYS
void clear_cerrojo (unsigned char x, unsigned char y) {
	// search & toggle
		
	for (gpit = 0; gpit < MAX_CERROJOS; gpit ++) 
		if (cerrojos [gpit].x == x && cerrojos [gpit].y == y && cerrojos [gpit].np == n_pant)
			cerrojos [gpit].st = 0;
}

void init_cerrojos () {
	// Activate all bolts.
	
	for (gpit = 0; gpit < MAX_CERROJOS; gpit ++)
		cerrojos [gpit].st = 1;	
}
#endif

#ifdef PLAYER_CAN_FIRE
	void init_bullets () {
		
		// Initialize bullets
		
		for (gpit = 0; gpit < MAX_BULLETS; gpit ++)	bullets [gpit].estado = 0;
	}
#endif

#if defined(PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE) || defined(BOXES_KILL_ENEMIES)
void init_malotes () {
	
	for (gpit = 0; gpit < MAP_W * MAP_H * 3; gpit ++) {
		malotes [gpit].t = malotes [gpit].t & 15;	
#ifdef PLAYER_CAN_FIRE
		malotes [gpit].life = ENEMIES_LIFE_GAUGE;
#ifdef RANDOM_RESPAWN
		if (malotes [gpit].t == 5)
			malotes [gpit].t |= 16;
#endif
#endif
	}
}
#endif

#ifdef PLAYER_CAN_FIRE
void fire_bullet () {
	
	// Search a free bullet slot...
	
	for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
		if (bullets [gpit].estado == 0) {
			bullets [gpit].estado = 1;
			if (player.facing == 0) {
				bullets [gpit].x = (player.x >> 6) - 4;
				bullets [gpit].mx = -PLAYER_BULLET_SPEED;
			} else {
				bullets [gpit].x = (player.x >> 6) + 12;
				bullets [gpit].mx = PLAYER_BULLET_SPEED;
			}
			bullets [gpit].y = (player.y >> 6) + PLAYER_BULLET_Y_OFFSET;
			peta_el_beeper (9);
#ifdef FIRING_DRAINS_LIFE
			player.life -= FIRING_DRAIN_AMOUNT;
#endif				
			break;	
		}	
	}	
}
#endif

#if defined(RANDOM_RESPAWN) || defined(USE_TYPE_6)
#if defined PLAYER_CAN_HIDE
char player_hidden () {
	unsigned char x, y, xx, yy;
	x = player.x >> 6;
	y = player.y >> 6;
	xx = x >> 4;
	yy = y >> 4;
	if ( (y & 15) == 0 && player.vx == 0 )
		if (attr (xx, yy) == 2 || (attr (1 + xx, yy) == 2 && (x & 15) != 0) )	
			return 1;
		
	
	return 0;
}
#endif
#endif

#ifdef USE_COINS
	void get_coin(unsigned char xx, unsigned char yy) {
		flags [COIN_FLAG] ++;
		draw_coins ();
		map_attr [15 * yy + xx] = 0;
		map_buff [15 * yy + xx] = 0;
		draw_coloured_tile (VIEWPORT_X + xx + xx, VIEWPORT_Y + yy + yy, 0);	
		peta_el_beeper (5);
#ifdef ACTIVATE_SCRIPTING
		// Run f_script #max_screens + 1
		script = f_scripts [max_screens + 1];
		run_script ();
#endif
	}
#endif

#ifdef PLAYER_PUSH_BOXES
void move_tile (unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char act) {
	// Move the tile
	map_attr [15 * y1 + x1] = 8;
	map_buff [15 * y1 + x1] = 14;
	map_attr [15 * y0 + x0] = 0;
	map_buff [15 * y0 + x0] = 0;
	// Draw
	draw_coloured_tile (VIEWPORT_X + x0 + x0, VIEWPORT_Y + y0 + y0, 0);
	draw_coloured_tile (VIEWPORT_X + x1 + x1, VIEWPORT_Y + y1 + y1, 14);
	// Sound
	if (act) {
		peta_el_beeper (8);
#ifdef FALLING_BOXES
		// A�adir al buffer de cajas cayentes.
		fall_box (x1, y1);
#endif
	}
}
#endif

void explode_player (unsigned char x, unsigned char y) {
	player.next_frame = sprite_17_a;
	sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3), x & 7, y & 7);
	player.current_frame = player.next_frame;
	sp_UpdateNow ();
	peta_el_beeper (10);	
}

unsigned char move () {
	unsigned char xx, yy;
	unsigned char x, y;
	unsigned char allpurp;
	int cx, cy;
	
	cx = player.x;
	cy = player.y;

	// Read device (keyboard, joystick ...)
	pad0 = (joyfunc) (&keys); 

	/* Vertical movement. The ecuations used are:

	   1.- vy = vy + g
	   2.- y = y + vy

	*/

#ifdef PLAYER_NO_INERTIA

	if ((pad0 & sp_UP) == 0) player.vy = -PLAYER_CONST_V;
	if ((pad0 & sp_DOWN) == 0) player.vy = PLAYER_CONST_V;
	if ( ! ((pad0 & sp_UP) == 0 || (pad0 & sp_DOWN) == 0)) player.vy = 0;

#else
	
#ifndef PLAYER_MOGGY_STYLE
	// If side view, get affected by gravity:
	
	if (player.vy < PLAYER_MAX_VY_CAYENDO)
		player.vy += player.g;
	else
		player.vy = PLAYER_MAX_VY_CAYENDO;

	if (player.gotten) player.vy = 0;		
#else
	// If top-down view, vertical movement = horizontal movement.
	
	if ( ! ((pad0 & sp_UP) == 0 || (pad0 & sp_DOWN) == 0))
		if (player.vy > 0) {
			player.vy -= player.rx;
			if (player.vy < 0)
				player.vy = 0;
		} else if (player.vy < 0) {
			player.vy += player.rx;
			if (player.vy > 0)
				player.vy = 0;
		}

	if ((pad0 & sp_UP) == 0)
		if (player.vy > -PLAYER_MAX_VX) {
			player.vy -= player.ax;
		}

	if ((pad0 & sp_DOWN) == 0)
		if (player.vy < PLAYER_MAX_VX) {
			player.vy += player.ax;
		}
#endif
#endif	
	//if (player.estado & EST_DIZZY) { player.vy >>= 1; player.vy += (rand () & (PLAYER_CONST_V - 1)) - (PLAYER_CONST_V >> 1); }

	player.y += player.vy;

	// Safe
		
	if (player.y < 0)
		player.y = 0;
		
	if (player.y > 9216)
		player.y = 9216;

	
	/* 
		Check for collisions with obstacles. If so, we have to move
		back until the edge of the tile.
	*/

	x = player.x >> 6;				// Divide / 64 for pixels, then / 16 for tiles.
	y = player.y >> 6;
	xx = x >> 4;
	yy = y >> 4;
	
	// Cool

	if (player.vy < 0) { 			// Going up
		//if (player.y >= 1024)
			if (attr (xx, yy) > 7 || ((x & 15) != 0 && attr (xx + 1, yy) > 7)) {
				// Stop and adjust.
				player.vy = 0;
				player.y = (yy + 1) << 10;
				y = player.y >> 6;
				yy = y >> 4;
			}
	} else if (player.vy > 0 && (y & 15) < 8) { 	// Going down
		if (player.y < 9216)
			if (attr (xx, yy + 1) > 3 || ((x & 15) != 0 && attr (xx + 1, yy + 1) > 3))
			{
				// Stop and adjust.
				player.vy = 0;
				player.y = yy << 10;
				y = player.y >> 6;
				yy = y >> 4;
			}
	}

	/* Jump: Jumping is as easy as giving vy a negative value. Nevertheless, we want
	   a somewhat more controllable jump, so we use the "mario bros" kind of controls:
	   the longer you press jump, the higher you reach.
	*/

#ifdef PLAYER_HAS_JUMP
#ifdef PLAYER_CAN_FIRE
	if (((pad0 & sp_UP) == 0) && ((player.vy == 0 && player.saltando == 0 && (attr (xx, yy + 1) > 3 || ((x & 15) != 0 && attr (xx + 1, yy + 1) > 3))) || player.gotten)) {
		player.saltando = 1;
		player.cont_salto = 0;
		peta_el_beeper (1);
	}

	if ( ((pad0 & sp_UP) == 0) && player.saltando ) {
		player.vy -= (player.salto + PLAYER_INCR_SALTO - (player.cont_salto>>1));
		if (player.vy < -PLAYER_MAX_VY_SALTANDO) player.vy = -PLAYER_MAX_VY_SALTANDO;
		player.cont_salto ++;
		if (player.cont_salto == 8)
			player.saltando = 0;
	}
	
	if ((pad0 & sp_UP) != 0)
		player.saltando = 0;
#else
	if (((pad0 & sp_FIRE) == 0 || (pad0 & sp_UP) == 0) && ((player.vy == 0 && player.saltando == 0 && (attr (xx, yy + 1) > 3 || ((x & 15) != 0 && attr (xx + 1, yy + 1) > 3))) || player.gotten)) {
		player.saltando = 1;
		player.cont_salto = 0;
		peta_el_beeper (1);
	}

	if ( ((pad0 & sp_FIRE) == 0 || (pad0 & sp_UP) == 0) && player.saltando ) {
		player.vy -= (player.salto + PLAYER_INCR_SALTO - (player.cont_salto>>1));
		if (player.vy < -PLAYER_MAX_VY_SALTANDO) player.vy = -PLAYER_MAX_VY_SALTANDO;
		player.cont_salto ++;
		if (player.cont_salto == 8)
			player.saltando = 0;
	}
	
	if ((pad0 & sp_FIRE) != 0 && (pad0 & sp_UP) != 0)
		player.saltando = 0;
#endif
#endif

#ifdef PLAYER_HAS_JETPAC
	if ((pad0 & sp_UP) == 0) {
		player.vy -= PLAYER_INCR_JETPAC;
		if (player.vy < -PLAYER_MAX_VY_JETPAC) player.vy = -PLAYER_MAX_VY_JETPAC;
#ifdef JETPAC_DRAINS_LIFE
		jetpac_frame_counter ++;
		if (jetpac_frame_counter == JETPAC_DRAIN_OFFSET + JETPAC_DRAIN_RATIO) {
			jetpac_frame_counter = JETPAC_DRAIN_OFFSET;
			player.life --;
		}
#endif
	} else {
		jetpac_frame_counter = 0;
	}
#endif

	// Done with vertical movement.

	/* Horizontal movement. Equations are:

	   Direction key pressed:
	   
	   x = x + vx
	   vx = vx + ax

	   Direction key not pressed:

	   x = x + vx
	   vx = vx - rx
	*/
#ifdef PLAYER_NO_INERTIA
	if ((pad0 & sp_LEFT) == 0) player.vx = -PLAYER_CONST_V;
	if ((pad0 & sp_RIGHT) == 0) player.vx = PLAYER_CONST_V;
	if ( ! ((pad0 & sp_LEFT) == 0 || (pad0 & sp_RIGHT) == 0)) player.vx = 0;
#else
	if ( ! ((pad0 & sp_LEFT) == 0 || (pad0 & sp_RIGHT) == 0))
		if (player.vx > 0) {
			player.vx -= player.rx;
			if (player.vx < 0)
				player.vx = 0;
		} else if (player.vx < 0) {
			player.vx += player.rx;
			if (player.vx > 0)
				player.vx = 0;
		}

	if ((pad0 & sp_LEFT) == 0)
		if (player.vx > -PLAYER_MAX_VX) {
			player.facing = 0;
			player.vx -= player.ax;
		}

	if ((pad0 & sp_RIGHT) == 0)
		if (player.vx < PLAYER_MAX_VX) {
			player.vx += player.ax;
			player.facing = 1;
		}
#endif
	//if (player.estado & EST_DIZZY) { player.vx >>= 1; player.vx += (rand () & (PLAYER_CONST_V - 1)) - (PLAYER_CONST_V >> 1); }

	player.x += player.vx;
	
	// Safe
	
	if (player.x < 0)
		player.x = 0;
		
	if (player.x > 14336)
		player.x = 14336;

	x = player.x >> 6;
	xx = x >> 4;
	
	if (player.vx < 0) {
		if (attr (xx, yy) > 7 || ((y & 15) != 0 && attr (xx, yy + 1) > 7)) {
			// Stop and adjust
			player.vx = 0;
			player.x = (xx + 1) << 10;
			x = player.x >> 6;
			xx = x >> 4;
		}
	} else {
		if (attr (xx + 1, yy) > 7 || ((y & 15) != 0 && attr (xx + 1, yy + 1) > 7)) {
			// Stop and adjust
			player.vx = 0;
			player.x = xx << 10;
			x = player.x >> 6;
			xx = x >> 4;
		}
	}
	
	// Shooting engine:
	
#ifdef PLAYER_CAN_FIRE
#ifdef PLAYER_MOGGY_STYLE
	// TODO. Not implemented yet. 
#else
	if ((pad0 & sp_FIRE) == 0 && player.disparando == 0) {
		player.disparando = 1;
		fire_bullet ();
	}
	
	if ((pad0 & sp_FIRE) != 0) 
		player.disparando = 0;
#endif
#endif
	
	// Keys / bolts engine:

#ifndef DEACTIVATE_KEYS
	if ((x & 15) == 0 && (y & 15) == 0) {
		if (qtile (xx + 1, yy) == 15 && player.keys > 0) {
			map_attr [15 * yy + xx + 1] = 0;
			map_buff [15 * yy + xx + 1] = 0;
			clear_cerrojo (xx + 1, yy);
			draw_coloured_tile (VIEWPORT_X + xx + xx + 2, VIEWPORT_Y + yy + yy, 0);
			player.keys --;
			peta_el_beeper (8);
		} else if (qtile (xx - 1, yy) == 15 && player.keys > 0) {
			map_attr [15 * yy + xx - 1] = 0;
			map_buff [15 * yy + xx - 1] = 0;
			clear_cerrojo (xx - 1, yy);
			draw_coloured_tile (VIEWPORT_X + xx + xx - 2, VIEWPORT_Y + yy + yy, 0);
			player.keys --;
			peta_el_beeper (8);
		}
	}
#endif
	
	// Pushing boxes (tile #14) engine

#ifdef PLAYER_PUSH_BOXES
#ifdef PLAYER_MOGGY_STYLE
	if ((pad0 & sp_FIRE) == 0) {
#endif		

#ifdef PLAYER_AUTO_CHANGE_SCREEN
		// In this case, there's nothing in the screen boundaries which will stop
		// the boxes from getting out of the screen, so we have to explicitly 
		// make sure that this won't happen.
		
		// In side-view mode, you can't push boxes vertically.
#ifdef PLAYER_MOGGY_STYLE
		// Vertically, only when player.y is tile-aligned.
		if ((y & 15) == 0) {
			if ((pad0 & sp_UP) == 0 && yy > 1) {
				if (can_move_box (xx, yy - 1, xx, yy - 2))
					move_tile (xx, yy - 1, xx, yy - 2, 1);
				}
				if ((x & 15) != 0) {
					if (can_move_box (xx + 1, yy - 1, xx + 1, yy - 2)) {		
						move_tile (xx + 1, yy - 1, xx + 1, yy - 2, 1);
					}
				}
			} else if ((pad0 & sp_DOWN) == 0 && yy < 8) {
				if (can_move_box (xx + 1, yy + 1, xx, yy + 2)) {
					move_tile (xx, yy + 1, xx, yy + 2, 1);
				}
				if ((x & 15) != 0) {
					if (can_move_box (xx + 1, yy + 1, xx + 1, yy + 2)) {
						move_tile (xx + 1, yy + 1, xx + 1, yy + 2, 1);
					}	
				}
			}
		}
#endif

		// Horizontally, only when player.x is tile-aligned.
		if ((x & 15) == 0) {
			if ((pad0 & sp_RIGHT) == 0 && xx < 14) {
				if (can_move_box (xx + 1, yy, xx + 2, yy)) {
					move_tile (xx + 1, yy, xx + 2, yy, 1);
				}
				if ((y & 15) != 0) {
					if (can_move_box (xx + 1, yy + 1, xx + 2, yy + 1)) {
						move_tile (xx + 1, yy + 1, xx + 2, yy + 1, 1);
					}
				}
			} else if ((pad0 & sp_LEFT) == 0 && xx > 1) {
				if (can_move_box (xx - 1, yy, xx - 2, yy)) {
					move_tile (xx - 1, yy, xx - 2, yy, 1);
				}
				if ((y & 15) != 0) {
					if (can_move_box (xx - 1, yy + 1, xx - 2, yy + 1)) {
						move_tile (xx - 1, yy + 1, xx - 2, yy + 1, 1);
					}
				}
			}	
		}			
#else

		// In side-view mode, you can't push boxes vertically.
#ifdef PLAYER_MOGGY_STYLE
		// Vertically, only when player.y is tile-aligned.
		if ((y & 15) == 0) {
			if ((pad0 & sp_UP) == 0) {
				if (can_move_box (xx, yy - 1, xx, yy - 2)) {
					move_tile (xx, yy - 1, xx, yy - 2, 1);
				}
				if ((x & 15) != 0) {
					if (can_move_box (xx + 1, yy - 1, xx + 1, yy - 2)) {
						move_tile (xx + 1, yy - 1, xx + 1, yy - 2, 1);
					}
				}
			} else if ((pad0 & sp_DOWN) == 0) {
				if (can_move_box (xx, yy + 1, xx, yy + 2)) {
					move_tile (xx, yy + 1, xx, yy + 2, 1);
				}
				if ((x & 15) != 0) {
					if (can_move_box (xx + 1, yy + 1, xx + 1, yy + 2)) {
						move_tile (xx + 1, yy + 1, xx + 1, yy + 2, 1);
					}	
				}
			}
		}
#endif

		// Horizontally, only when player.x is tile-aligned.
		if ((x & 15) == 0) {
			if ((pad0 & sp_RIGHT) == 0) {
				if (can_move_box (xx + 1, yy, xx + 2, yy)) {
					move_tile (xx + 1, yy, xx + 2, yy, 1);
				}
				if ((y & 15) != 0) {
					if (can_move_box (xx + 1, yy + 1, xx + 2, yy + 1)) {
						move_tile (xx + 1, yy + 1, xx + 2, yy + 1, 1);
					}
				}
			} else if ((pad0 & sp_LEFT) == 0) {
				if (can_move_box (xx - 1, yy, xx - 2, yy)) {
					move_tile (xx - 1, yy, xx - 2, yy, 1);
				}
				if ((y & 15) != 0) {
					if (can_move_box (xx - 1, yy + 1, xx - 2, yy + 1)) {
						move_tile (xx - 1, yy + 1, xx - 2, yy + 1, 1);
					}
				}
			}	
		}	
#endif
#ifdef PLAYER_MOGGY_STYLE
	}	
#endif
#endif


#ifndef DEACTIVATE_EVIL_TILE	
	// Evil tile engine

	if (attr (xx, yy) == 1 || 
		((x & 15) != 0 && attr (xx + 1, yy) == 1) ||
		((y & 15) != 0 && attr (xx, yy + 1) == 1) ||
		((x & 15) != 0 && (y & 15) != 0 && attr (xx + 1, yy + 1) == 1)) {		
		peta_el_beeper (2);
		player.life -= LINEAR_ENEMY_HIT;	
		player.x = cx;
		player.y = cy;
		player.vy = -player.vy;
		//player.vx = -player.vx;
#ifdef PLAYER_FLICKERS
		// Flickers. People seem to like this more than the bouncing behaviour.
		player.estado = EST_PARP;
		player.ct_estado = 50;
#endif			
	}
#endif

#ifndef DEACTIVATE_EVIL_ZONE
	// Evil zone engine

	if (attr (xx, yy) == 3 || 
		((x & 15) != 0 && attr (xx + 1, yy) == 3) ||
		((y & 15) != 0 && attr (xx, yy + 1) == 3) ||
		((x & 15) != 0 && (y & 15) != 0 && attr (xx + 1, yy + 1) == 3)) {
		if (player.killingzone_beepcount >= EVIL_ZONE_BEEPS_COUNT || !scenery_info.evil_kills_slowly) {
			if (!(player.estado & EST_PARP)) {
				player.killingzone_framecount = (player.killingzone_framecount + 1) & 3;
				if (!player.killingzone_framecount) peta_el_beeper (3);
				player.life --;	
			}
		} else {
			if (player.killingzone_framecount > EVIL_ZONE_FRAME_COUNT) {
				player.killingzone_framecount = 0;
				player.killingzone_beepcount ++;
				sp_Border (2);
				peta_el_beeper (4);
				sp_Border (0);
			} else {
				player.killingzone_framecount ++;
			}
		}
	} else {
		if (player.killingzone_beepcount > 0)
			player.killingzone_beepcount --;
	}
#endif

#ifdef USE_COINS
		// Coins interaction
		
		if (qtile (xx, yy) == COIN_TILE)
			get_coin (xx, yy);
		if ((x & 15) != 0 && qtile (xx + 1, yy) == COIN_TILE)
			get_coin (xx + 1, yy);
		if ((y & 15) != 0 && qtile (xx, yy + 1) == COIN_TILE) 
			get_coin (xx, yy + 1);
		if ((x & 15) != 0 && (y & 15) != 0 && qtile (xx + 1, yy + 1) == COIN_TILE)
			get_coin (xx + 1, yy + 1);			
#endif


	// Select next frame to paint...

#ifndef PLAYER_MOGGY_STYLE
	// In this case, the spriteset is:
	// 1  2  3  4  5  6  7  8
	// R1 R2 R3 RJ L1 L2 L3 LJ

	if (player.vy != 0) {
		if (player.facing == 0)
			player.next_frame = sprite_8_a;
		else
			player.next_frame = sprite_4_a;
	} else {
		if (player.vx == 0) {
			if (player.facing == 0)
#ifdef PLAYER_ALTERNATE_ANIMATION
				player.next_frame = sprite_5_a;
#else
				player.next_frame = sprite_6_a;
#endif
			else
#ifdef PLAYER_ALTERNATE_ANIMATION
				player.next_frame = sprite_1_a;
#else
				player.next_frame = sprite_2_a;
#endif
		} else {
			player.subframe ++;
			if (player.subframe == 4) {
				player.subframe = 0;
#ifdef PLAYER_ALTERNATE_ANIMATION
				player.frame ++;
				if (player.frame == 3) 
					player.frame = 0;
#else
				player.frame = (player.frame + 1) & 3;
#endif
				step ();
			}
			
#ifdef PLAYER_ALTERNATE_ANIMATION
			if (player.facing == 0) {
				if (player.frame == 0)
					player.next_frame = sprite_5_a;
				else if (player.frame == 1)
					player.next_frame = sprite_6_a;
				else if (player.frame == 2)
					player.next_frame = sprite_7_a;
			} else {
				if (player.frame == 0)
					player.next_frame = sprite_1_a;
				else if (player.frame == 1)
					player.next_frame = sprite_2_a;
				else if (player.frame == 2)
					player.next_frame = sprite_3_a;	
			}
#else			

			if (player.facing == 0) {
				if (player.frame == 1 || player.frame == 3)
					player.next_frame = sprite_6_a;
				else if (player.frame == 0)
					player.next_frame = sprite_5_a;
				else if (player.frame == 2)
					player.next_frame = sprite_7_a;
			} else {
				if (player.frame == 1 || player.frame == 3)
					player.next_frame = sprite_2_a;
				else if (player.frame == 0)
					player.next_frame = sprite_1_a;
				else if (player.frame == 2)
					player.next_frame = sprite_3_a;
			}
#endif
		}	
	}
#else
	// In this case, the spriteset is
	// 1  2  3  4  5  6  7  8
	// R1 R2 L1 L2 U1 U2 D1 D2
	
	if (player.vx != 0 || player.vy != 0) {
		player.subframe ++;
		if (player.subframe == 4) {
			player.subframe = 0;
			player.frame = !player.frame;
			step (); 
		}
	}
	
	if (player.vx > 0) {
		if (player.frame)
			player.next_frame = sprite_1_a;
		else	
			player.next_frame = sprite_2_a;
	} else if (player.vx < 0) {
		if (player.frame)
			player.next_frame = sprite_3_a;
		else
			player.next_frame = sprite_4_a;
	} else {
		if (player.vy < 0) {
			if (player.frame)
				player.next_frame = sprite_5_a;
			else
				player.next_frame = sprite_6_a;
		} else {
			if (player.frame)
				player.next_frame = sprite_7_a;
			else
				player.next_frame = sprite_8_a;
		}
	}
#endif
}

void init_player_values () {
	player.x = 			PLAYER_INI_X << 10;
	player.y = 			PLAYER_INI_Y << 10;
	player.vy = 		0;
	player.g = 			PLAYER_G; 
	player.vx = 		0;
	player.ax = 		PLAYER_AX;
	player.rx = 		PLAYER_RX;
	player.salto = 		PLAYER_VY_INICIAL_SALTO;
	player.cont_salto = 1;
	player.saltando = 	0;
	player.frame = 		0;
	player.subframe = 	0;
	player.facing = 	1;
	player.estado = 	EST_NORMAL;
	player.ct_estado = 	0;
	player.disparando = 0;
	player.killingzone_beepcount = 0;
	player.killingzone_framecount = 0;	
	player.is_dead =    0;
}

void init_player () {
	// Initialize player with initial values.
	// (hence the initialize thing)
	init_player_values ();
	
	player.life = 		PLAYER_LIFE;
	player.objs =		0;
	player.keys = 		0;
	player.killed = 	0;
#ifndef WIN_ON_SCRIPTING
	#ifdef SCR_FIN
	pant_final = SCR_FIN;
	#endif
#endif
}

#if defined(DEACTIVATE_KEYS) && defined(DEACTIVATE_OBJECTS)
#else
void init_hotspots () {
	for (gpit = 0; gpit < MAP_W * MAP_H; gpit ++)
		hotspots [gpit].act = 1;
}
#endif

void delete_text () {
	for (gpit = 0; gpit < 32 - LINE_OF_TEXT_SUBSTR; gpit ++)
		sp_PrintAtInv (LINE_OF_TEXT, LINE_OF_TEXT_X + gpit, LINE_OF_TEXT_ATTR, 0);
}

void draw_scr_background () {
	unsigned char x = 0, y = 0, d, t1, t2;
#ifdef UNPACKED_MAP
	unsigned int idx = n_pant * 150;
#else
	unsigned int idx = n_pant * 75;
#endif
	unsigned char location = 0;
#ifdef TWO_SETS
	unsigned char tileoffset = TWO_SETS_CONDITION;
#endif

#ifdef UNPACKED_MAP
	// UNPACKED map, every byte represents one tile.
	for (gpit = 0; gpit < 150; gpit ++) {
		d = mapa [idx++];
#if defined(USE_COINS) && defined(COINS_DEACTIVABLE)
		if (d == COIN_TILE && !scenery_info.show_coins) d = COIN_TILE_DEACT_SUBS;
#endif
		map_attr [location] = comportamiento_tiles [d];
		map_buff [location] = d;
		draw_coloured_tile (VIEWPORT_X + x, VIEWPORT_Y + y, d);
		location ++;
		x += 2;
		if (x == 30) {
			x = 0;
			y += 2;
		}
	}
#else
#ifdef TWO_SETS
	// TWO_SETS_PACKED map, every byte contains two tiles,
	// plus uses several tilesets
	for (gpit = 0; gpit < 75; gpit ++) {
		location = 15 * (y >> 1) + (x >> 1);
		d = mapa [idx++];
		t1 = d >> 4;
#if defined(USE_COINS) && defined(COINS_DEACTIVABLE)
		if (t1 == COIN_TILE && !scenery_info.show_coins) t1 = COIN_TILE_DEACT_SUBS;
#endif
		t2 = d & 15;
#if defined(USE_COINS) && defined(COINS_DEACTIVABLE)
		if (t2 == COIN_TILE && !scenery_info.show_coins) t2 = COIN_TILE_DEACT_SUBS;
#endif
		map_attr [location] = comportamiento_tiles [tileoffset + t1];
		draw_coloured_tile (VIEWPORT_X + x, VIEWPORT_Y + y, tileoffset + t1);
		map_buff [location] = t1;
		x += 2;
		if (x == 30) {
			x = 0;
			y += 2;
		}
		location ++;
		map_attr [location] = comportamiento_tiles [tileoffset + t2];
		draw_coloured_tile (VIEWPORT_X + x, VIEWPORT_Y + y, tileoffset + t2);
		map_buff [location] = t2;
		x += 2;
		if (x == 30) {
			x = 0;
			y += 2;
		}
	}
	//
#else	
	// PACKED map, every byte contains two tiles, plus admits
	// some special effects (autoshadows, see below).
	for (gpit = 0; gpit < 75; gpit ++) {
		location = 15 * (y >> 1) + (x >> 1);
		d = mapa [idx++];
		t1 = d >> 4;
#if defined(USE_COINS) && defined(COINS_DEACTIVABLE)
		if (t1 == COIN_TILE && !scenery_info.show_coins) t1 = COIN_TILE_DEACT_SUBS;
#endif
		t2 = d & 15;
#if defined(USE_COINS) && defined(COINS_DEACTIVABLE)
		if (t2 == COIN_TILE && !scenery_info.show_coins) t2 = COIN_TILE_DEACT_SUBS;
#endif
		map_attr [location] = comportamiento_tiles [t1];
#ifndef NO_ALT_BG
		if ((rand () & 15) < 2 && t1 == 0 && map_buff [location - 16] == 0)
			t1 = 19;
#endif
		draw_coloured_tile (VIEWPORT_X + x, VIEWPORT_Y + y, t1);
		map_buff [location] = t1;
		x += 2;
		if (x == 30) {
			x = 0;
			y += 2;
		}
		location ++;
		map_attr [location] = comportamiento_tiles [t2];
#ifndef NO_ALT_BG
		if ((rand () & 15) < 2 && t2 == 0 && map_buff [location - 16] == 0)
			t2 = 19;
#endif
		draw_coloured_tile (VIEWPORT_X + x, VIEWPORT_Y + y, t2);
		map_buff [location] = t2;
		x += 2;
		if (x == 30) {
			x = 0;
			y += 2;
		}
	}
#endif	
#endif

#if defined(DEACTIVATE_KEYS) && defined(DEACTIVATE_OBJECTS)
#else
	// Is there an object in this screen?
	
	hotspot_x = hotspot_y = 240;
	if (hotspots [n_pant].act == 1) {
#if defined(ACTIVATE_SCRIPTING) && defined(OBJECTS_ON_VAR)
		if (flags [OBJECTS_ON_VAR] == 1) {
#endif
			if (hotspots [n_pant].tipo != 0) {
				// Calculate tile coordinates
				x = (hotspots [n_pant].xy >> 4);
				y = (hotspots [n_pant].xy & 15);
				// Convert to pixels and store
				hotspot_x = x << 4;
				hotspot_y = y << 4;
				// Remember which tile was there
				orig_tile = map_buff [15 * y + x];
				// Draw the object.
				draw_coloured_tile (VIEWPORT_X + x + x, VIEWPORT_Y + y + y, 16 + hotspots [n_pant].tipo);
			}
#if defined(ACTIVATE_SCRIPTING) && defined(OBJECTS_ON_VAR)
		}
#endif
	}
#ifndef DEACTIVATE_REFILLS
	else if (hotspots [n_pant].act == 0) {
		// Randomly, if there's no active object, we draw a recharge.
		if (rand () % 3 == 2) {
			x = (hotspots [n_pant].xy >> 4);
			y = (hotspots [n_pant].xy & 15);
			hotspot_x = x << 4;
			hotspot_y = y << 4;
			orig_tile = map_buff [15 * y + x];
			draw_coloured_tile (VIEWPORT_X + x + x, VIEWPORT_Y + y + y, 16);	
		}
	}
#endif
#endif
	
#ifndef DEACTIVATE_KEYS
	// Is there a bolt which has been already opened in this screen?
	// If so, delete it:
	for (gpit = 0; gpit < MAX_CERROJOS; gpit ++) {
		if (cerrojos [gpit].np == n_pant && !cerrojos [gpit].st) {
			draw_coloured_tile (VIEWPORT_X + cerrojos [gpit].x + cerrojos [gpit].x, VIEWPORT_Y + cerrojos [gpit].y + cerrojos [gpit].y, 0);
			location = 15 * cerrojos [gpit].y + cerrojos [gpit].x;
			map_attr [location] = 0;
			map_buff [location] = 0;
		}
	}
#endif	
}

void draw_scr () {
		
#ifdef SHOW_LEVEL_INFO
	char *cad_level = "LEVEL";

	saca_a_todo_el_mundo_de_aqui ();

	sp_ClearRect (spritesClip, 0, 0, sp_CR_TILES);
	sp_Invalidate (spritesClip, spritesClip);
#ifdef SHOW_LEVEL_SUBLEVEL
	draw_text (VIEWPORT_X + 9, VIEWPORT_Y + 10, 71, cad_level);
	draw_2_digits (VIEWPORT_X + 16, VIEWPORT_Y + 10, 1+(n_pant / MAP_W));
	sp_PrintAtInv (VIEWPORT_Y + 10, VIEWPORT_X + 18, 71, 15);
	draw_2_digits (VIEWPORT_X + 19, VIEWPORT_Y + 10, 1+(n_pant % MAP_W));
#else
	draw_text (VIEWPORT_X + 11, VIEWPORT_Y + 10, 71, cad_level);
	draw_2_digits (VIEWPORT_X + 17, VIEWPORT_Y + 10, (n_pant+1));
#endif
	sp_UpdateNow ();
	peta_el_beeper (6);
	espera_activa (1000);

#ifdef FALLING_BOXES
	init_falling_box_buffer ();
#endif

#ifdef RESET_BODY_COUNT_ON_ENTER
	player.killed = 0;
#endif

#endif
	
	// This function draws and sets up current screen.
	
	draw_scr_background ();
			
	f_zone_ac = 0;

	// Set up enemies.
	
	enoffs = n_pant * 3;

#ifdef COUNT_KILLABLE_ON
	flags [COUNT_KILLABLE_ON] = 0;
#endif

	for (gpit = 0; gpit < 3; gpit ++) {
		en_an [gpit].frame = 0;
		en_an [gpit].count = 0;
#ifdef RANDOM_RESPAWN
		en_an [gpit].fanty_activo = 0;
#endif
		switch (malotes [enoffs + gpit].t) {
#ifdef NO_MAX_ENEMS
			case 0:
	#ifdef USE_TYPE_6
					if (scenery_info.make_type_6) {
						en_an [gpit].next_frame = sprite_13_a;
						en_an [gpit].x = (rand () % 224) << 6;
						en_an [gpit].y = (rand () % 144) << 6;
						en_an [gpit].vx = en_an [gpit].vy = 0;
						en_an [gpit].state = TYPE_6_IDLE;
					} else {
						en_an [gpit].next_frame = sprite_18_a;
					}
	#else
					en_an [gpit].next_frame = sprite_18_a;
	#endif
				break;
#endif
			case 1:
			case 2:
			case 3:
			case 4:
				en_an [gpit].next_frame = sprite_9_a + 288 * (malotes [enoffs + gpit].t - 1);
				break;
#ifdef USE_TYPE_6
			case 6:
				en_an [gpit].next_frame = sprite_13_a;
				en_an [gpit].x = malotes [enoffs + gpit].x << 6;
				en_an [gpit].y = malotes [enoffs + gpit].y << 6;
				en_an [gpit].vx = en_an [gpit].vy = 0;
				en_an [gpit].state = TYPE_6_IDLE;
				break;
#endif
#if defined (PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE)			
			default:
				en_an [gpit].next_frame = sprite_18_a;
#endif
		}
		
#ifdef COUNT_KILLABLE_ON
		
#if defined(BOXES_KILL_ENEMIES) || defined(PLAYER_KILLS_ENEMIES)
#ifdef BOXES_ONLY_KILL_TYPE
		if (malotes [enoffs + gpit].t == BOXES_ONLY_KILL_TYPE) {
			flags [COUNT_KILLABLE_ON] ++;
			continue;
		}
#endif
#ifdef PLAYER_MIN_KILLABLE
		if (malotes [enoffs + gpit].t >= PLAYER_MIN_KILLABLE) {
			flags [COUNT_KILLABLE_ON] ++;
		}
#endif
#if !defined(BOXES_ONLY_KILL_TYPE) && !defined (PLAYER_MIN_KILLABLE)
		flags [COUNT_KILLABLE_ON] ++;

#endif
#endif

#endif

	}
	
#ifdef ACTIVATE_SCRIPTING
	// Delete line of text
	delete_text ();
	// Run "ENTERING ANY" script (if available)
	script = e_scripts [MAP_W * MAP_H + 1];
	run_script ();
	// Run "ENTERING" script for THIS screen (if available)
	script = e_scripts [n_pant];
	run_script ();
#endif

#ifdef PLAYER_CAN_FIRE
		init_bullets ();
#endif	
}

// This function is called from the menu and
// sets up the controlling scheme depending on
// which key is pressed:

// 1 KEYS
// 2 KEMPSTON
// 3 SINCLAIR

void select_joyfunc () {
	unsigned char terminado = 0;
	
	#asm
		; Music generated by beepola
		call musicstart
	#endasm
	
	while (!terminado) {
		
		if (sp_KeyPressed (key_1)) {
			terminado = 1;
			joyfunc = sp_JoyKeyboard;
		} else if (sp_KeyPressed (key_2)) {
			terminado = 1;
			joyfunc = sp_JoyKempston;
		} else if (sp_KeyPressed (key_3)) {
			terminado = 1;
			joyfunc = sp_JoySinclair1;
		}			
	}
	#asm
		di
	#endasm
}

#ifdef PLAYER_CAN_FIRE
void mueve_bullets () {
	unsigned char j;
#ifdef PLAYER_MOGGY_STYLE
	// TODO
#else	
	for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
		bullets [gpit].x += bullets [gpit].mx;
		if (attr (bullets [gpit].x >> 4, bullets [gpit].y >> 4) > 7) {
			bullets [gpit].estado = 0;
		}
		if (bullets [gpit].x < 8 || bullets [gpit].x > 240)
			bullets [gpit].estado = 0;
	}	
#endif
}
#endif	

#ifdef USE_SIGHT_DISTANCE
unsigned char distance (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	// return abs (x2 - x1 + y2 - y1);
	// Better version:
	unsigned char dx = abs (x2 - x1);
	unsigned char dy = abs (y2 - y1);
	unsigned char mn = dx < dy ? dx : dy;
	return (dx + dy - (mn >> 1) - (mn >> 2) + (mn >> 4));
}
#endif

void mueve_bicharracos () {
	// This function moves the active enemies.
	
	unsigned char j, enoffsmasi, x, y, xx, yy;
	unsigned char cx, cy;
	unsigned char ccx, ccy;
	// Only one enemy may hurt the player at once, so we need this flag:
	unsigned char tocado = 0; 		

	player.gotten = 0;
	
	for (enit = 0; enit < 3; enit ++) {
		enoffsmasi = enoffs + enit;
		if (malotes [enoffsmasi].t != 0 || scenery_info.make_type_6) {
			cx = malotes [enoffsmasi].x;
			cy = malotes [enoffsmasi].y;
#ifdef RANDOM_RESPAWN
			if (!en_an [enit].fanty_activo) {
				malotes [enoffsmasi].x += malotes [enoffsmasi].mx;
				malotes [enoffsmasi].y += malotes [enoffsmasi].my;
			}
#else
			malotes [enoffsmasi].x += malotes [enoffsmasi].mx;
			malotes [enoffsmasi].y += malotes [enoffsmasi].my;
#endif

#ifdef PLAYER_PUSH_BOXES			
			// Check for collisions.
			x = malotes [enoffsmasi].x >> 4;
			y = malotes [enoffsmasi].y >> 4;

			if (malotes [enoffsmasi].mx != 0) {
				if (attr (x + ctileoff (malotes [enoffsmasi].mx), y) > 7 || 
				((malotes [enoffsmasi].y & 15) != 0 && attr (x + ctileoff (malotes [enoffsmasi].mx), y + 1) > 7)) {
					malotes [enoffsmasi].mx = -malotes [enoffsmasi].mx;
					malotes [enoffsmasi].x = cx;
				}
			}
			if (malotes [enoffsmasi].my != 0) {
				if (attr (x, y + ctileoff (malotes [enoffsmasi].my)) > 7 || 
				((malotes [enoffsmasi].x & 15) != 0 && attr (x + 1, y + ctileoff (malotes [enoffsmasi].mx)) > 7)) {
					malotes [enoffsmasi].my = -malotes [enoffsmasi].my;
					malotes [enoffsmasi].y = cy;
				}
			}
#endif

			en_an [enit].count ++; 
			if (en_an [enit].count == 4) {
				en_an [enit].count = 0;
				en_an [enit].frame = !en_an [enit].frame;

				switch (malotes [enoffsmasi].t) {
					case 1:
						en_an [enit].next_frame = en_an [enit].frame ? sprite_9_a : sprite_10_a;
						break;
					case 2:
						en_an [enit].next_frame = en_an [enit].frame ? sprite_11_a : sprite_12_a;
						break;
					case 3:
					case 6:
					case 0:
						en_an [enit].next_frame = en_an [enit].frame ? sprite_13_a : sprite_14_a;
						break;
					case 4:
						en_an [enit].next_frame = en_an [enit].frame ? sprite_15_a : sprite_16_a;
#ifdef RANDOM_RESPAWN
						break;
					default:
						if (en_an [enit].fanty_activo)
							en_an [enit].next_frame = en_an [enit].frame ? sprite_13_a : sprite_14_a;
#endif					
				}	
			}

			x = player.x >> 6;
			y = player.y >> 6;
			
#ifdef RANDOM_RESPAWN
			if (en_an [enit].fanty_activo) {
				ccx = en_an [enit].x >> 6;
				ccy = en_an [enit].y >> 6;
			} else {
				ccx = malotes [enoffsmasi].x;
				ccy = malotes [enoffsmasi].y;
			}
#else
#ifdef USE_TYPE_6
			if (malotes [enoffsmasi].t == 6 || malotes [enoffsmasi].t == 0) {
				ccx = en_an [enit].x >> 6;
				ccy = en_an [enit].y >> 6;
			} else {
				ccx = malotes [enoffsmasi].x;
				ccy = malotes [enoffsmasi].y;
			}
#else
			ccx = malotes [enoffsmasi].x;
			ccy = malotes [enoffsmasi].y;
#endif
#endif
			
			// Moving platforms engine:

#ifndef PLAYER_MOGGY_STYLE	
			if (malotes [enoffsmasi].t == 4) {
				xx = player.x >> 10;
				// Vertical
				if (malotes [enoffsmasi].my < 0) {
					// Go up.
					if (x >= ccx - 15 && x <= ccx + 15 && y >= ccy - 16 && y <= ccy - 11 && player.vy >= -(PLAYER_INCR_SALTO)) {
						player.gotten = 1;
						player.y = (ccy - 16) << 6;
						player.vy = 0;						
						yy = player.y >> 10;
						// Collide?
						if (player.y > 1024)
							if (attr (xx, yy) > 7 || ((x & 15) != 0 && attr (xx + 1, yy) > 7)) {
								// ajust:
								player.y = (yy + 1) << 10;
							}
					}
				} else if (malotes [enoffsmasi].my > 0) {
					// Go down.
					if (x >= ccx - 15 && x <= ccx + 15 && y >= ccy - 20 && y <= ccy - 14 && player.vy >= 0) {
						player.gotten = 1;
						player.y = (ccy - 16) << 6;
						player.vy = 0;
						yy = player.y >> 10;
						// Collide?
						if (player.y < 9216)
							if (attr (xx, yy + 1) > 7 || ((x & 15) != 0 && attr (xx + 1, yy + 1) > 7)) {
								// ajust:
								player.y = yy << 10;
							}
					}
				}
				y = player.y >> 6;
				yy = player.y >> 10;
				// Horizontal
				if (malotes [enoffsmasi].mx != 0 && x >= ccx - 15 && x <= ccx + 15 && y >= ccy - 16 && y <= ccy - 11 && player.vy >= 0) {
					player.gotten = 1;
					player.y = (ccy - 16) << 6;
					yy = player.y >> 10;
					x = x + malotes [enoffsmasi].mx;
					player.x = x << 6;
					xx = player.x >> 10;
					if (malotes [enoffsmasi].mx < 0) {
						if (attr (xx, yy) > 7 || ((y & 15) != 0 && attr (xx, yy + 1) > 7)) {
							player.vx = 0;
							player.x = (xx + 1) << 10;
						}
					} else if (malotes [enoffsmasi].mx > 0) {
						if (attr (xx + 1, yy) > 7 || ((y & 15) != 0 && attr (xx + 1, yy + 1) > 7)) {
							player.vx = 0;
							player.x = xx << 10;
						}
					}					
				}
				
			// Collision with enemy
			
#ifdef RANDOM_RESPAWN
			} else if (!tocado && collide (x, y, ccx, ccy) && (malotes [enoffsmasi].t < 16 || en_an [enit].fanty_activo == 1) && player.estado == EST_NORMAL) {
#else
			} else if (!tocado && collide (x, y, ccx, ccy) && malotes [enoffsmasi].t < 16 && player.estado == EST_NORMAL) {
#endif
#else
#ifdef RANDOM_RESPAWN
			if (!tocado && collide (x, y, ccx, ccy) && (malotes [enoffsmasi].t < 16 || en_an [enit].fanty_activo == 1) && player.estado == EST_NORMAL) {
#else
			if (!tocado && collide (x, y, ccx, ccy) && malotes [enoffsmasi].t < 16 && player.estado == EST_NORMAL) {
#endif
#endif			

#ifdef PLAYER_KILLS_ENEMIES
				if (y < ccy - 8 && player.vy > 0 && malotes [enoffsmasi].t >= PLAYER_MIN_KILLABLE) {
					// Step on enemy and kill it.
					en_an [enit].next_frame = sprite_17_a;
					sp_MoveSprAbs (sp_moviles [enit], spritesClip, en_an [enit].next_frame - en_an [enit].current_frame, VIEWPORT_Y + (malotes [enoffs + enit].y >> 3), VIEWPORT_X + (malotes [enoffs + enit].x >> 3), malotes [enoffs + enit].x & 7, malotes [enoffs + enit].y & 7);
					en_an [enit].current_frame = en_an [enit].next_frame;
					sp_UpdateNow ();
					peta_el_beeper (10);
					en_an [enit].next_frame = sprite_18_a;
					malotes [enoffsmasi].t |= 16;			// Marked as "dead"
					// Count it
					player.killed ++;
#ifdef ACTIVATE_SCRIPTING
					script = f_scripts [max_screens + 2];
					run_script ();
#endif
				} else {
#else
				{
#endif
					tocado = 1;
					peta_el_beeper (2);
					player.is_dead = 1;
					
					// We decide which kind of life drain we do:
#if defined(RANDOM_RESPAWN) || defined(USE_TYPE_6)
					if (malotes [enoffsmasi].t > 4) {
						player.life -= FLYING_ENEMY_HIT;
					} else {
#endif
						player.life -= LINEAR_ENEMY_HIT;
#if defined(RANDOM_RESPAWN) || defined (USE_TYPE_6)
					}
#endif
					
#ifdef PLAYER_BOUNCES
#ifndef PLAYER_MOGGY_STYLE	
#if defined(RANDOM_RESPAWN) || defined(USE_TYPE_6)
					if (!en_an [enit].fanty_activo) {
						// Bouncing!
						if (malotes [enoffsmasi].mx > 0) player.vx = PLAYER_MAX_VX;
						if (malotes [enoffsmasi].mx < 0) player.vx = -PLAYER_MAX_VX;
						if (malotes [enoffsmasi].my > 0) player.vy = PLAYER_MAX_VX;
						if (malotes [enoffsmasi].my < 0) player.vy = -PLAYER_MAX_VX;
					} else {
						player.vx = en_an [enit].vx + en_an [enit].vx;
						player.vy = en_an [enit].vy + en_an [enit].vy;
					}
#else
					// Bouncing!
					if (malotes [enoffsmasi].mx > 0) player.vx = (PLAYER_MAX_VX + PLAYER_MAX_VX);
					if (malotes [enoffsmasi].mx < 0) player.vx = -(PLAYER_MAX_VX + PLAYER_MAX_VX);
					if (malotes [enoffsmasi].my > 0) player.vy = (PLAYER_MAX_VX + PLAYER_MAX_VX);
					if (malotes [enoffsmasi].my < 0) player.vy = -(PLAYER_MAX_VX + PLAYER_MAX_VX);
#endif
#else
					// Bouncing:
					
					// x
					if (malotes [enoffsmasi].mx != 0) {
						if (x < ccx) {
							player.vx = - (abs (malotes [enoffsmasi].mx + malotes [enoffsmasi].mx) << 7);
						} else {
							player.vx = abs (malotes [enoffsmasi].mx + malotes [enoffsmasi].mx) << 7;
						}
					}
					
					// y
					if (malotes [enoffsmasi].my != 0) {
						if (y < ccy) {
							player.vy = - (abs (malotes [enoffsmasi].my + malotes [enoffsmasi].my) << 7);
						} else {
							player.vy = abs (malotes [enoffsmasi].my + malotes [enoffsmasi].my) << 7;
						}
					}
#endif
#endif

#ifdef PLAYER_FLICKERS
					// Flickers. People seem to like this more than the bouncing behaviour.
					player.estado = EST_PARP;
					player.ct_estado = 50;
#endif
				}
			}
			
			// Trajectory limits for linear enemies
			
#ifdef RANDOM_RESPAWN
			if (en_an [enit].fanty_activo) {
#ifdef PLAYER_CAN_HIDE
				if (player_hidden ()) {
					if (player.x < en_an [enit].x && en_an [enit].vx < FANTY_MAX_V)
						en_an [enit].vx += FANTY_A >> 1;
					else if (player.x > en_an [enit].x && en_an [enit].vx > -FANTY_MAX_V)
						en_an [enit].vx -= FANTY_A >> 1;
					if (player.y < en_an [enit].y && en_an [enit].vy < FANTY_MAX_V)
						en_an [enit].vy += FANTY_A >> 1;
					else if (player.y > en_an [enit].y && en_an [enit].vy > -FANTY_MAX_V)
						en_an [enit].vy -= FANTY_A >> 1;
				} else
#endif 
				if ((rand () & 7) > 1) {
					if (player.x > en_an [enit].x && en_an [enit].vx < FANTY_MAX_V)
						en_an [enit].vx += FANTY_A;
					else if (player.x < en_an [enit].x && en_an [enit].vx > -FANTY_MAX_V)
						en_an [enit].vx -= FANTY_A;
					if (player.y > en_an [enit].y && en_an [enit].vy < FANTY_MAX_V)
						en_an [enit].vy += FANTY_A;
					else if (player.y < en_an [enit].y && en_an [enit].vy > -FANTY_MAX_V)
						en_an [enit].vy -= FANTY_A;
				}
								
				en_an [enit].x += en_an [enit].vx;
				en_an [enit].y += en_an [enit].vy;
				if (en_an [enit].x > 15360) en_an [enit].x = 15360;
				if (en_an [enit].x < -1024) en_an [enit].x = -1024;
				if (en_an [enit].y > 10240) en_an [enit].y = 10240;
				if (en_an [enit].y < -1024) en_an [enit].y = -1024;
			} else {
#endif
#ifdef USE_TYPE_6
			if (malotes [enoffsmasi].t == 6 || malotes [enoffsmasi].t == 0) {
#if defined (USE_SIGHT_DISTANCE) || defined (PLAYER_CAN_HIDE)
				// Idle, retreat or pursue depending on player status (distance or hidden)

				switch (en_an [enit].state) {
					case TYPE_6_IDLE:
#ifdef PLAYER_CAN_HIDE
						if (distance (ccx, ccy, x, y) <= SIGHT_DISTANCE && !player_hidden ()) 
#else
						if (distance (ccx, ccy, x, y) <= SIGHT_DISTANCE) 
#endif
							en_an [enit].state = TYPE_6_PURSUING;
						break;
					case TYPE_6_PURSUING:
						if ((rand () & 7) > 1) {
							if (player.x > en_an [enit].x && en_an [enit].vx < FANTY_MAX_V)
								en_an [enit].vx += FANTY_A;
							else if (player.x < en_an [enit].x && en_an [enit].vx > -FANTY_MAX_V)
								en_an [enit].vx -= FANTY_A;
							if (player.y > en_an [enit].y && en_an [enit].vy < FANTY_MAX_V)
								en_an [enit].vy += FANTY_A;
							else if (player.y < en_an [enit].y && en_an [enit].vy > -FANTY_MAX_V)
								en_an [enit].vy -= FANTY_A;
						}
#ifdef PLAYER_CAN_HIDE
						if (distance (ccx, ccy, x, y) >= SIGHT_DISTANCE || player_hidden ()) 
#else
						if (distance (ccx, ccy, x, y) >= SIGHT_DISTANCE)
#endif
							en_an [enit].state = TYPE_6_RETREATING;
						break;
					case TYPE_6_RETREATING:
						if ((malotes [enoffsmasi].x << 6) > en_an [enit].x && en_an [enit].vx < FANTY_MAX_V)
							en_an [enit].vx += FANTY_A;
						else if ((malotes [enoffsmasi].x << 6) < en_an [enit].x && en_an [enit].vx > -FANTY_MAX_V)
							en_an [enit].vx -= FANTY_A;
						if ((malotes [enoffsmasi].y << 6) > en_an [enit].y && en_an [enit].vy < FANTY_MAX_V)
							en_an [enit].vy += FANTY_A;
						else if ((malotes [enoffsmasi].y << 6) < en_an [enit].y && en_an [enit].vy > -FANTY_MAX_V)
							en_an [enit].vy -= FANTY_A;
#ifdef PLAYER_CAN_HIDE
						if (distance (ccx, ccy, x, y) <= SIGHT_DISTANCE && !player_hidden ()) 
#else
						if (distance (ccx, ccy, x, y) <= SIGHT_DISTANCE) 
#endif
							en_an [enit].state = TYPE_6_PURSUING;
						break;	
				}
#else
				// Always pursue

				if ((rand () & 7) > 1) {
					if (player.x > en_an [enit].x && en_an [enit].vx < FANTY_MAX_V)
						en_an [enit].vx += FANTY_A;
					else if (player.x < en_an [enit].x && en_an [enit].vx > -FANTY_MAX_V)
						en_an [enit].vx -= FANTY_A;
					if (player.y > en_an [enit].y && en_an [enit].vy < FANTY_MAX_V)
						en_an [enit].vy += FANTY_A;
					else if (player.y < en_an [enit].y && en_an [enit].vy > -FANTY_MAX_V)
						en_an [enit].vy -= FANTY_A;
				}
#endif
				if (scenery_info.allow_type_6) {
					en_an [enit].x += en_an [enit].vx;
					en_an [enit].y += en_an [enit].vy;
				}
				if (en_an [enit].x > 15360) en_an [enit].x = 15360;
				if (en_an [enit].x < -1024) en_an [enit].x = -1024;
				if (en_an [enit].y > 10240) en_an [enit].y = 10240;
				if (en_an [enit].y < -1024) en_an [enit].y = -1024;
			} else {
#endif
				if (ccx == malotes [enoffsmasi].x1 || ccx == malotes [enoffsmasi].x2)
					malotes [enoffsmasi].mx = -malotes [enoffsmasi].mx;
				if (ccy == malotes [enoffsmasi].y1 || ccy == malotes [enoffsmasi].y2)
					malotes [enoffsmasi].my = -malotes [enoffsmasi].my;
#if defined(RANDOM_RESPAWN) || defined(USE_TYPE_6)
			}
#endif
							
#ifdef PLAYER_CAN_FIRE
			// Collision with bullets
#ifdef RANDOM_RESPAWN
			if (malotes [enoffsmasi].t < 16 || en_an [enit].fanty_activo == 1) {
#else
			if (malotes [enoffsmasi].t < 16) {
#endif
				for (j = 0; j < MAX_BULLETS; j ++) {		
					if (bullets [j].estado == 1) {
						if (bullets [j].y >= ccy - 4 && bullets [j].y <= ccy + 12 && bullets [j].x >= ccx - 4 && bullets [j].x <= ccx + 12) {
#if defined (RANDOM_RESPAWN) || defined (USE_TYPE_6)	
#ifdef RANDOM_RESPAWN	
							if (en_an [enit].fanty_activo) 
#else
							if (malotes [enoffsmasi].t == 6)
#endif
								en_an [enit].vx += (bullets [enit].mx > 0 ? 128 : -128);
#endif
							en_an [enit].next_frame = sprite_17_a;
							en_an [enit].morido = 1;
							bullets [j].estado = 0;
							if (malotes [enoffsmasi].t != 4)
								malotes [enoffsmasi].life --;
							if (malotes [enoffsmasi].life == 0) {
								// Kill enemy
								sp_MoveSprAbs (sp_moviles [enit], spritesClip, en_an [enit].next_frame - en_an [enit].current_frame, VIEWPORT_Y + (ccy >> 3), VIEWPORT_X + (ccx >> 3), ccx & 7, ccy & 7);
								en_an [enit].current_frame = en_an [enit].next_frame;
								sp_UpdateNow ();
								peta_el_beeper (10);
								en_an [enit].next_frame = sprite_18_a;
								malotes [enoffsmasi].t |= 16;			// dead
								// Count
								player.killed ++;
#ifdef ACTIVATE_SCRIPTING
								script = f_scripts [max_screens + 2];
								run_script ();
#endif								
#ifdef RANDOM_RESPAWN								
								en_an [enit].fanty_activo = 0;
								malotes [enoffsmasi].life = FANTIES_LIFE_GAUGE;
#endif
							}
						}
					}
				}
			}
#endif

#ifdef RANDOM_RESPAWN
			// Activate fanty

			if (malotes [enoffsmasi].t > 15 && en_an [enit].fanty_activo == 0 && (rand () & 31) == 1) {
				en_an [enit].fanty_activo = 1;
				if (player.y > 5120)
					en_an [enit].y = -1024;
				else
					en_an [enit].y = 10240;
				en_an [enit].x = (rand () % 240 - 8) << 6;
				en_an [enit].vx = en_an [enit].vy = 0;
			}
#endif

		}
	}
}
