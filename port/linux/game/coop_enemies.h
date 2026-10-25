/*
COOP_ENEMIES.H

Network co-op's extra enemies, for its players (coop_enemies.c).
*/

#ifndef __COOP_ENEMIES_H
#define __COOP_ENEMIES_H

/* network_coop.c: a game begins (its EXTRA ENEMIES read), or the host's
game state went back (a cutscene skipped): the dropships' riders kept are
forgotten */
void coop_enemies_new_game(
	void);
void coop_enemies_reset(
	void);

/* encounters.c: how many enemies more a squad of `actor_type` placed with
`count` gets (none but on a co-op host or in a single player game with
extra enemies, for an encounter of the players' enemies) */
short coop_enemies_extra_count(
	long encounter_index,
	short count,
	short actor_type);

/* single player's extra enemies (game.enemies_multiplier,
game.enemies_grunts_only, the console's enemies command): each squad of
the players' enemies placed from then on is `multiplier` times as large
(1: as the level has it), or only the grunts' squads */
void coop_enemies_solo_set(
	long multiplier,
	boolean grunts_only);
short coop_enemies_solo_multiplier(
	void);
boolean coop_enemies_solo_grunts_only(
	void);
/* game.c, as each tick of a single player game begins: the dropships'
riders kept placed once their vehicle's own get out */
void coop_enemies_solo_update(
	void);

/* the places coop_enemies_spread_position tries around a starting location */
#define COOP_ENEMIES_SPREAD_SPOTS 90

/* encounters.c: finds a spot for a squad's `number`th extra enemy
(counting from 1) around the starting location `origin`, on its floor,
clear of walls and objects, with room to stand and nobody there. FALSE if
there's no room. `taken` (COOP_ENEMIES_SPREAD_SPOTS bits, or NULL) marks the
places found taken, which stay so while the squad's enemies are placed: they
aren't tried again. */
boolean coop_enemies_spread_position(
	real_point3d const *origin,
	short number,
	long *taken,
	real_point3d *position);
/* encounters.c: where the `number`th extra enemy (counting from 1) goes
when no starting location has room: a place on rings around `origin` with
the way open and ground below, whoever stands there (as extra enemies were
placed before free ground was looked for), so the squad still gets every
enemy the setting asks for. FALSE if none (the starting location itself
then) */
boolean coop_enemies_fallback_position(
	real_point3d const *origin,
	short number,
	real_point3d *position);

/* units.c's vehicle_scripting_load_magic: a rider seated, and one left
without a seat (the vehicle's seats taken: an extra enemy), which is kept,
off the map, until the vehicle's riders get out (TRUE: kept, the caller
erases it) */
void coop_enemies_rider_seated(
	long vehicle_index,
	long unit_index);
boolean coop_enemies_rider_unseated(
	long vehicle_index,
	long unit_index);

/* network_coop.c, after each of the host's ticks: the riders kept placed
at their vehicle's seats once its own riders get out */
void coop_enemies_update(
	void);

#endif
