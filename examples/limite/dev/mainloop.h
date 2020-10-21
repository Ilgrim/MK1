// MTE MK1 v4.7
// Copyleft 2010, 2011 by The Mojon Twins

// mainloop.h
// Cointains initialization stuff and the main game loop.

void main (void) {
	// splib2 initialization
	sp_Initialize (7, 0);
	sp_Border (BLACK);
	sp_AddMemory(0, NUMBLOCKS, 14, AD_FREE);
	// Define keys and default controls

	joyfunc = sp_JoyKeyboard;

	// Load tileset
	gp_gen = tileset;
	gpit = 0; do {
		sp_TileArray (gpit, gp_gen);
		gp_gen += 8;
		gpit ++;
	} while (gpit);

	// Clipping rectangle	
	spritesClip = &spritesClipValues;
	
	// Sprite creation
	#ifdef NO_MASKS
		sp_player = sp_CreateSpr (sp_XOR_SPRITE, 3, sprite_2_a, 1, TRANSPARENT);
		sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
		sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
		player.current_frame = player.next_frame = sprite_2_a;
		
		for (rdi = 0; rdi < 3; rdi ++) {
			sp_moviles [rdi] = sp_CreateSpr(sp_XOR_SPRITE, 3, sprite_9_a, 1, TRANSPARENT);
			sp_AddColSpr (sp_moviles [rdi], sprite_9_b, TRANSPARENT);
			sp_AddColSpr (sp_moviles [rdi], sprite_9_c, TRANSPARENT);	
			en_an [rdi].current_frame = sprite_9_a;
		}
	#else
		sp_player = sp_CreateSpr (sp_MASK_SPRITE, 3, sprite_2_a, 1, TRANSPARENT);
		sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
		sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
		player.current_frame = player.next_frame = sprite_2_a;
		
		for (rdi = 0; rdi < 3; rdi ++) {
			sp_moviles [rdi] = sp_CreateSpr(sp_MASK_SPRITE, 3, sprite_9_a, 2, TRANSPARENT);
			sp_AddColSpr (sp_moviles [rdi], sprite_9_b, TRANSPARENT);
			sp_AddColSpr (sp_moviles [rdi], sprite_9_c, TRANSPARENT);	
			en_an [rdi].current_frame = sprite_9_a;
		}
	#endif

	#ifdef PLAYER_CAN_FIRE
		for (rdi = 0; rdi < MAX_BULLETS; rdi ++) {
			sp_bullets [rdi] = sp_CreateSpr (sp_OR_SPRITE, 2, sprite_19_a, 1, TRANSPARENT);
			sp_AddColSpr (sp_bullets [rdi], sprite_19_b, TRANSPARENT);
		}
	#endif

	while (1) {
		// Here the title screen
		title_screen ();
		
		#ifndef DIRECT_TO_PLAY
			// Clear screen and show game frame
			cortina ();
			sp_UpdateNow();
			unpack ((unsigned int) (s_marco));
		#endif

		// Let's do it.
		playing = 1;

		#ifndef DEACTIVATE_EVIL_ZONE
			scenery_info.evil_kills_slowly = 0;
		#endif

		#ifdef USE_TYPE_6
			scenery_info.make_type_6 = 0;
			scenery_info.allow_type_6 = 1;
		#endif

		init_player ();

		#if defined(DEACTIVATE_KEYS) && defined(DEACTIVATE_OBJECTS)
		#else
			init_hotspots ();
		#endif

		#ifndef DEACTIVATE_KEYS
			init_cerrojos ();
		#endif	

		#if defined(PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE) || defined(BOXES_KILL_ENEMIES)
			init_malotes ();
		#endif
			
		#ifdef PLAYER_CAN_FIRE
			init_bullets ();
		#endif	
			
		n_pant = SCR_INICIO;
		maincounter = 0;
		
		#ifdef ACTIVATE_SCRIPTING		
			script_result = 0;
			msc_init_all ();
			#ifdef OBJECT_COUNT
				flags [OBJECT_COUNT] = 0;
			#endif
		
			// Execute "ENTERING GAME" script
			script = e_scripts [max_screens];
			run_script ();
		#endif
		
		draw_scr ();
		
		#if defined(PLAYER_KILLS_ENEMIES) || defined(PLAYER_CAN_FIRE)
			#ifdef SHOW_KILLED
				draw_killed ();
			#endif
			#ifdef SHOW_TOTAL
				// Show total of enemies next to the killed amount.

				sp_PrintAtInv (KILLED_Y, 2 + KILLED_X, 71, 15);
				sp_PrintAtInv (KILLED_Y, 3 + KILLED_X, 71, 16 + BADDIES_COUNT / 10);
				sp_PrintAtInv (KILLED_Y, 4 + KILLED_X, 71, 16 + BADDIES_COUNT % 10);
			#endif
		#endif
		reentered = 0;
		half_life = 0;
		
		#if defined(FALLING_BOXES) && defined(PLAYER_PUSH_BOXES)
			fall_frame_counter = 0;
		#endif

		objs_old = life_old = keys_old = killed_old = item_old = ezg_old = 0xff;

		while (playing) {

			// Update  HUD

			#ifndef DEACTIVATE_OBJECTS			
				if (player.objs != objs_old) {
					#ifdef ONLY_ONE_OBJECT
						if (player.objs) {
							sp_PrintAtInv (OBJECTS_ICON_Y, OBJECTS_ICON_X, 135, 132);
							sp_PrintAtInv (OBJECTS_ICON_Y, OBJECTS_ICON_X + 1, 135, 133);
							sp_PrintAtInv (OBJECTS_ICON_Y + 1, OBJECTS_ICON_X, 135, 134);
							sp_PrintAtInv (OBJECTS_ICON_Y + 1, OBJECTS_ICON_X + 1, 135, 135);
						} else {
							draw_coloured_tile (OBJECTS_ICON_X, OBJECTS_ICON_Y, 17);
						}
						draw_2_digits (OBJECTS_X, OBJECTS_Y, flags [OBJECT_COUNT]);
					#else
						draw_2_digits (OBJECTS_X, OBJECTS_Y, player.objs);
					#endif
					objs_old = player.objs;
				}
			#endif
			
			if (player.life != life_old) {
				if (player.life > 0) pti = (unsigned char) player.life; else pti = 0;
				#ifdef DRAW_HI_DIGIT
					sp_PrintAtInv (LIFE_H_Y, LIFE_H_X, 71, 16 + pti / 100);
				#endif
				draw_2_digits (LIFE_X, LIFE_Y, pti);
				life_old = player.life;
			}

			#ifndef DEACTIVATE_KEYS
				if (player.keys != keys_old) {
					draw_2_digits (KEYS_X, KEYS_Y, player.keys);
					keys_old = player.keys;
				}
			#endif

			#ifdef PLAYER_KILLS_ENEMIES		
				if (player.killed != killed_old) {
					draw_2_digits (KILLED_X, KILLED_Y, player.killed);
					killed_old = player.killed;	
				}
			#endif

			#ifdef PLAYER_SHOW_ITEM
				if (flags [ITEM_IN_FLAG] != item_old) {
					draw_coloured_tile (ITEM_SHOW_X, ITEM_SHOW_Y, ITEM_FIRST_TILE + flags [ITEM_IN_FLAG] - 1);
					item_old = flags [ITEM_IN_FLAG];
				}
			#endif			

			#ifndef DEACTIVATE_EVIL_ZONE
				if (player.killingzone_beepcount != ezg_old) {
					draw_2_digits (EVIL_GAUGE_X, EVIL_GAUGE_Y, EVIL_ZONE_BEEPS_COUNT - player.killingzone_beepcount);
					ezg_old = player.killingzone_beepcount;
				}
			#endif

			maincounter ++;
			half_life = !half_life;
			
			move ();
			mueve_bicharracos ();

			#ifdef PLAYER_CAN_FIRE
				// Move bullets				
				mueve_bullets ();
			#endif

			#if defined(FALLING_BOXES) && defined(PLAYER_PUSH_BOXES)
				// Move boxes
				animate_boxes ();
			#endif

			// Render		
			for (rdi = 0; rdi < 3; rdi ++) {
				#if defined(RANDOM_RESPAWN) || defined(USE_TYPE_6)
					#ifdef RANDOM_RESPAWN
						if (en_an [rdi].fanty_activo)
					#else
						if (malotes [enoffs + rdi].t == 6 || malotes [enoffs + rdi].t == 0)
					#endif
					{
						rdx = en_an [rdi].x >> 6;
						rdy = en_an [rdi].y >> 6;
					} else 
				#endif
				{
					rdx = malotes [enoffs + rdi].x;
					rdy = malotes [enoffs + rdi].y;
				}
				sp_MoveSprAbs (sp_moviles [rdi], spritesClip, en_an [rdi].next_frame - en_an [rdi].current_frame, VIEWPORT_Y + (rdy >> 3), VIEWPORT_X + (rdx >> 3),rdx & 7, rdy & 7);
				en_an [rdi].current_frame = en_an [rdi].next_frame;
			}

			#ifdef ACTIVATE_SCRIPTING
				if (f_zone_ac == 1) {
					if (gpx >= fzx1 && gpx <= fzx2 && gpy >= fzy1 && gpy <= fzy2) {
						script = f_scripts [n_pant];
						run_script ();
					}	
				}
			#endif
			
			if ( !(player.estado & EST_PARP) || !(half_life) )
				sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, VIEWPORT_Y + (gpy >> 3), VIEWPORT_X + (gpx >> 3), gpx & 7, gpy & 7);
			else
				sp_MoveSprAbs (sp_player, spritesClip, player.next_frame - player.current_frame, -2, -2, 0, 0);
			
			player.current_frame = player.next_frame;
			
			#ifdef PLAYER_CAN_FIRE
				for (rdi = 0; rdi < MAX_BULLETS; rdi ++) {
					if (bullets [rdi].estado == 1) {
						sp_MoveSprAbs (sp_bullets [rdi], spritesClip, 0, VIEWPORT_Y + (bullets [rdi].y >> 3), VIEWPORT_X + (bullets [rdi].x >> 3), bullets [rdi].x & 7, bullets [rdi].y & 7);
					} else {
						sp_MoveSprAbs (sp_bullets [rdi], spritesClip, 0, -2, -2, 0, 0);
					}
				}
			#endif			
			
			// Update to screen
			sp_UpdateNow();
			
			#ifdef PLAYER_CAN_FIRE
				for (rdi = 0; rdi < 3; rdi ++)
					if (en_an [rdi].morido == 1) {
						peta_el_beeper (1);
						en_an [rdi].morido = 0;
					} 	
			#endif

			#if defined(PLAYER_FLICKERS) || defined (RESPAWN_FLICKER)
				// Flickering
				if (player.estado & EST_PARP) {
					player.ct_estado --;
					if (player.ct_estado == 0) {
						player.estado = EST_NORMAL;
					}	
				}
			#endif			
			
			#if defined(DEACTIVATE_KEYS) && defined(DEACTIVATE_OBJECTS)
			#else
				// Hotspot interaction.
				if (gpx >= hotspot_x - 15 && gpx <= hotspot_x + 15 && gpy >= hotspot_y - 15 && gpy <= hotspot_y + 15) {
					// Deactivate hotspot
					draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), orig_tile);
					// Was it an object, key or life boost?
					if (hotspots [n_pant].act == 0) {
						player.life += PLAYER_REFILL;
						if (player.life > PLAYER_LIFE)
							player.life = PLAYER_LIFE;
						hotspots [n_pant].act = 2;
						peta_el_beeper (6);
					}
					#ifndef DEACTIVATE_OBJECTS
						else if (hotspots [n_pant].tipo == 1) {
							#ifdef ONLY_ONE_OBJECT
								if (player.objs == 0) {
									rdi = 1;
									player.objs ++;
									hotspots [n_pant].act = 0;
									peta_el_beeper (6);	
								} else {
									rdi = 0;
									peta_el_beeper (1);	
									draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), 17);
								}
							#else
								player.objs ++;
								hotspots [n_pant].act = 0;
								peta_el_beeper (6);
								#ifdef OBJECT_COUNT
									flags [OBJECT_COUNT] ++;
								#endif
							#endif
						}
					#endif
					#ifndef DEACTIVATE_KEYS
						else if (hotspots [n_pant].tipo == 2) {
							player.keys ++;
							hotspots [n_pant].act = 0;
							peta_el_beeper (6);
						}
					#endif
					// PLOP!!
					hotspot_x = hotspot_y = 240;
				}
			#endif
		
			rdi = (joyfunc) (&keys);

			// Flick screen checks and scripting related stuff
		
			#ifdef ACTIVATE_SCRIPTING		
				#ifdef SCRIPTING_KEY_M			
					if (sp_KeyPressed (key_m) || ((rdi & sp_FIRE) == 0))
				#endif
				#ifdef SCRIPTING_DOWN
					if ((rdi & sp_DOWN) == 0)
				#endif
				{
					script = f_scripts [max_screens];
					run_script ();
					// Any scripts to run in this screen?
					script = f_scripts [n_pant];
					run_script ();
					if (!script_something_done) peta_el_beeper (9);
				}
			#endif

			#ifndef FIXED_SCREENS
				#ifdef PLAYER_AUTO_CHANGE_SCREEN
					if (player.x == 0 && player.vx < 0) {
						n_pant --;
						draw_scr ();
						player.x = 14336;
					}
					if (player.x == 14336 && player.vx > 0) {
						n_pant ++;
						draw_scr ();
						player.x = 0;
					}
				#else
					if (player.x == 0 && ((rdi & sp_LEFT) == 0)) {
						n_pant --;
						draw_scr ();	
						player.x = 14336;
					}
					if (player.x == 14336 && ((rdi & sp_RIGHT) == 0)) {		// 14336 = 224 * 64
						n_pant ++;
						draw_scr ();
						player.x = 0;
					}
				#endif
				if (player.y == 0 && player.vy < 0 && n_pant >= MAP_W) {
					n_pant -= MAP_W;
					draw_scr ();
					player.y = 9216;	
				}
				if (player.y == 9216 && player.vy > 0) {				// 9216 = 144 * 64
					if (n_pant < MAP_W * MAP_H - MAP_W) {
						n_pant += MAP_W;
						draw_scr ();
						player.y = 0;
					} else {
						player.vy = -player.vy;
						peta_el_beeper (2);
						player.life --;	
					}
				}
			#endif
			
			// Win game condition
			
			#ifndef WIN_ON_SCRIPTING
			
				#ifdef ACTIVATE_SCRIPTING
					#ifndef REENTER_ON_ALL_OBJECTS
						if (player.objs == PLAYER_NUM_OBJETOS || script_result == 1 
							#ifdef SCR_FIN
								|| n_pant == SCR_FIN
							#endif
						)
					#else
						if (player.objs == PLAYER_NUM_OBJETOS && !reentered) {
							reentered = 1;
							draw_scr ();	
						} 

						if (script_result == 1 
							#ifdef SCR_FIN
								|| n_pant == SCR_FIN
							#endif
						)
					#endif
				#else			
					if (player.objs == PLAYER_NUM_OBJETOS 
						#ifdef SCR_FIN
							|| n_pant == SCR_FIN
							#endif
						)
				#endif

				{
					#ifdef SCR_FIN
						success = 0;
						if (n_pant == pant_final) {
							if ((player.x >> 10) == PLAYER_FIN_X && (player.y >> 10) == PLAYER_FIN_Y) 
								success = 1;
						} else if (pant_final == 99) {
							success = 1;
						}
						if (success) 
					#endif
					{
						saca_a_todo_el_mundo_de_aqui ();
						cortina ();
						game_ending ();
						playing = 0;
						cortina ();
					}
				}
			#else
				if (script_result) {
					cortina ();
					game_ending ();
					playing = 0;
					cortina ();
				}
			#endif

			// Dead player
			if (player.is_dead) {
				player.is_dead = 0;
				if (player.life > 0) {
					#ifdef RESPAWN_REENTER
						explode_player ();
						#ifdef RESPAWN_SHOW_LEVEL				
							draw_scr ();
							init_player_values ();
							#ifdef FIXED_SCREENS
								player.killed = 0;
								malotes [enoffs].t = malotes [enoffs].t & 15;
								malotes [enoffs + 1].t = malotes [enoffs + 1].t & 15;
								malotes [enoffs + 2].t = malotes [enoffs + 2].t & 15;
							#endif
						#else	
							draw_scr_background ();
							init_player_values ();
						#endif
					#endif
					#ifdef RESPAWN_FLICKER
						player.estado = EST_PARP;
						player.ct_estado = 50;
					#endif
				}
			}

			// Game over condition

			if (player.life <= 0
				#ifdef ACTIVATE_SCRIPTING
					|| script_result == 2
				#endif
			) {
				saca_a_todo_el_mundo_de_aqui ();				
				game_over ();
				playing = 0;
				cortina ();
			}
			
			#ifdef USE_SUICIDE_KEY
				if (sp_KeyPressed (key_s)) {
					player.is_dead = 1;
					player.life --;
				}
			#endif
		}	
	}
}
