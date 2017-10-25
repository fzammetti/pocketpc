
#include "../main.h"


namespace ns_LeparLand {


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
void placeTreasure(POINT player_pos);


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Lepar Land"),
														 TEXT(""),
														 TEXT("Who's bright idea was"),
														 TEXT("it to put all the sick"),
														 TEXT("people on one planet?"),
														 TEXT("Now if you want their"),
														 TEXT("gold, your going to"),
														 TEXT("have to risk infection."),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Grab as much of the"),
														 TEXT("Lepar's gold stash as"),
														 TEXT("you can without"),
														 TEXT("getting Lepar-fied"),
														 TEXT("yourself."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move up, down, left or"),
														 TEXT("right to avoid the lepars"),
														 TEXT("and get the gold.  Trees"),
														 TEXT("block you path, mud"),
														 TEXT("slows you down."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	tree                    = NULL;
CGapiSurface*	mud                     = NULL;
CGapiSurface*	dead_lepar              = NULL;
CGapiSurface*	treasure                = NULL;
CGapiSurface*	player_still            = NULL;
CGapiSurface*	lepar[4];
CGapiSurface*	player[4];
hssSound*			sfxDeath                = NULL;
hssSound*			sfxCaching              = NULL;
hssSound*			sfxMoaning              = NULL;
POINT					treasure_pos;
POINT					mud_pos[5];
POINT					tree_pos[35];
POINT					dead_lepar_pos[5];
POINT					live_lepar_pos[5];
bool          moaningPlaying          = false;
bool					obstacles_positioned    = false;
bool					live_lepar_dir_north[5];
bool					live_lepar_dir_south[5];
bool					live_lepar_dir_east[5];
bool					live_lepar_dir_west[5];
int						live_lepar_frame        = 0;
int						live_lepar_frame_delay  = 0;
int						live_lepar_move_delay   = 0;
int						player_frame            = 0;
int						player_frame_delay      = 0;
int           sfxMoaningChannel       = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfLeparLand(CGapiSurface* backbuffer) {

	using namespace ns_LeparLand;

	if (!moaningPlaying) {
		moaningPlaying = true;
		sfxMoaningChannel = sndObj.playSound(sfxMoaning);
	}

	POINT colPoint;
	RECT rect;
	GDBLTFX gdbltfx;

	// Blit mud
	for (int i = 0; i < 3; i++) {
		backbuffer->BltFast(xadj + mud_pos[i].x, yadj + mud_pos[i].y, mud, NULL, GDBLTFAST_KEYSRC, NULL);
	}

	// Blit trees
	for (i = 0; i < 3; i++) {
		backbuffer->BltFast(xadj + tree_pos[i].x, yadj + tree_pos[i].y,	tree,	NULL, GDBLTFAST_KEYSRC, NULL);
	}

	// Blit dead lepars
	for (i = 0; i < 3; i++) {
		backbuffer->BltFast(xadj + dead_lepar_pos[i].x, yadj + dead_lepar_pos[i].y, dead_lepar, NULL, GDBLTFAST_KEYSRC, NULL);
	}

	// Blit treasure
	backbuffer->BltFast(xadj	 + treasure_pos.x, yadj + treasure_pos.y,	treasure,	NULL, GDBLTFAST_KEYSRC, NULL);

	// Blit live lepars
	for (i = 0; i < 3; i++) {
		SetRect(&rect, xadj + live_lepar_pos[i].x, yadj + live_lepar_pos[i].y, xadj + live_lepar_pos[i].x + 18, yadj + live_lepar_pos[i].y + 18);
		if ( (!live_lepar_dir_north[i] && !live_lepar_dir_south[i] && !live_lepar_dir_east[i] && !live_lepar_dir_west[i]) || // No movement
				 (live_lepar_dir_north[i]  && !live_lepar_dir_south[i] && !live_lepar_dir_east[i] && !live_lepar_dir_west[i]) || // North
				 (!live_lepar_dir_north[i] && live_lepar_dir_south[i]  && !live_lepar_dir_east[i] && !live_lepar_dir_west[i]) || // South
				 (!live_lepar_dir_north[i] && !live_lepar_dir_south[i] && live_lepar_dir_east[i]  && !live_lepar_dir_west[i]) || // East
				 (!live_lepar_dir_north[i] && !live_lepar_dir_south[i] && !live_lepar_dir_east[i] && live_lepar_dir_west[i]) ) { // West
			gdbltfx.nRotationAngle = 0;
			backbuffer->Blt(&rect, lepar[live_lepar_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
		}
		if (live_lepar_dir_north[i] && !live_lepar_dir_south[i] && live_lepar_dir_east[i] && !live_lepar_dir_west[i]) { // NorthEast
			gdbltfx.nRotationAngle = -4500;
			backbuffer->Blt(&rect, lepar[live_lepar_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
		}
		if (live_lepar_dir_north[i] && !live_lepar_dir_south[i] && !live_lepar_dir_east[i] && live_lepar_dir_west[i]) { // NorthWest
			gdbltfx.nRotationAngle = 4500;
			backbuffer->Blt(&rect, lepar[live_lepar_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
		}
		if (!live_lepar_dir_north[i] && live_lepar_dir_south[i] && live_lepar_dir_east[i] && !live_lepar_dir_west[i]) { // SouthEast
			gdbltfx.nRotationAngle = 4500;
			backbuffer->Blt(&rect, lepar[live_lepar_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
		}
		if (!live_lepar_dir_north[i] && live_lepar_dir_south[i] && !live_lepar_dir_east[i] && live_lepar_dir_west[i]) { // SouthWest
			gdbltfx.nRotationAngle = -4500;
			backbuffer->Blt(&rect, lepar[live_lepar_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
		}
	}

	// Blit player
	SetRect(&rect, xadj + player_pos.x, yadj + player_pos.y, xadj + player_pos.x + 18, yadj + player_pos.y + 18);
	if ((!player_dir_north && !player_dir_south && !player_dir_east && !player_dir_west)) { // No movement
		backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y, player_still, NULL, GDBLTFAST_KEYSRC, NULL);
	}
	if ( (player_dir_north  && !player_dir_south && !player_dir_east && !player_dir_west) || // North
			 (!player_dir_north && player_dir_south  && !player_dir_east && !player_dir_west) || // South
			 (!player_dir_north && !player_dir_south && player_dir_east  && !player_dir_west) || // East
			 (!player_dir_north && !player_dir_south && !player_dir_east && player_dir_west) ) { // West
		gdbltfx.nRotationAngle = 0;
		backbuffer->Blt(&rect, player[player_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (player_dir_north && !player_dir_south && player_dir_east && !player_dir_west) { // NorthEast
		gdbltfx.nRotationAngle = -4500;
		backbuffer->Blt(&rect, player[player_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (player_dir_north && !player_dir_south && !player_dir_east && player_dir_west) { // NorthWest
		gdbltfx.nRotationAngle = 4500;
		backbuffer->Blt(&rect, player[player_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (!player_dir_north && player_dir_south && player_dir_east && !player_dir_west) { // SouthEast
		gdbltfx.nRotationAngle = 4500;
		backbuffer->Blt(&rect, player[player_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (!player_dir_north && player_dir_south && !player_dir_east && player_dir_west) { // SouthWest
		gdbltfx.nRotationAngle = -4500;
		backbuffer->Blt(&rect, player[player_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}

	// Handle player movements
	bool  do_move			 = false;
	int	  move_vector  = 3;
	POINT prev_pos     = player_pos;

	// North (y-)
	if (player_dir_north && !player_dir_south && !player_dir_east && !player_dir_west) {
		do_move = true;
		// Check for collision with mud.  If one occurs, slow the player down.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + mud_pos[i].x, yadj + mud_pos[i].y,	mud, NULL,
															xadj + player_pos.x, yadj + player_pos.y - move_vector, player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) { move_vector = 1; }
		}
		player_pos.y = player_pos.y - move_vector; // Update player's position
		// Check for collision with trees.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + tree_pos[i].x, yadj + tree_pos[i].y,	tree, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
		// Check for collision with dead lepars.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + dead_lepar_pos[i].x, yadj + dead_lepar_pos[i].y,	dead_lepar, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
	}

	// South (y+)
	if (!player_dir_north && player_dir_south && !player_dir_east && !player_dir_west) {
		do_move = true;
		// Check for collision with mud.  If one occurs, slow the player down.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + mud_pos[i].x, yadj + mud_pos[i].y,	mud, NULL,
															xadj + player_pos.x, yadj + player_pos.y + move_vector, player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) { move_vector = 1; }
		}
		player_pos.y = player_pos.y + move_vector; // Update player's position
		// Check for collision with trees.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + tree_pos[i].x, yadj + tree_pos[i].y,	tree, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
		// Check for collision with dead lepars.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + dead_lepar_pos[i].x, yadj + dead_lepar_pos[i].y,	dead_lepar, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
	}

	// East (x+)
	if (!player_dir_north && !player_dir_south && player_dir_east && !player_dir_west) {
		do_move = true;
		// Check for collision with mud.  If one occurs, slow the player down.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + mud_pos[i].x, yadj + mud_pos[i].y,	mud, NULL,
															xadj + player_pos.x + move_vector, yadj + player_pos.y, player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) { move_vector = 1; }
		}
		player_pos.x = player_pos.x + move_vector; // Update player's position
		// Check for collision with trees.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + tree_pos[i].x, yadj + tree_pos[i].y,	tree, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
		// Check for collision with dead lepars.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + dead_lepar_pos[i].x, yadj + dead_lepar_pos[i].y,	dead_lepar, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
	}

	// West (x-)
	if (!player_dir_north && !player_dir_south && !player_dir_east && player_dir_west) {
		do_move = true;
		// Check for collision with mud.  If one occurs, slow the player down.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + mud_pos[i].x, yadj + mud_pos[i].y,	mud, NULL,
															xadj + player_pos.x - move_vector, yadj + player_pos.y, player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) { move_vector = 1; }
		}
		player_pos.x = player_pos.x - move_vector; // Update player's position
		// Check for collision with trees.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + tree_pos[i].x, yadj + tree_pos[i].y,	tree, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
		// Check for collision with dead lepars.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + dead_lepar_pos[i].x, yadj + dead_lepar_pos[i].y,	dead_lepar, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
	}

	// NorthEast (x+y-)
	if (player_dir_north && !player_dir_south && player_dir_east && !player_dir_west) {
		do_move = true;
		// Check for collision with mud.  If one occurs, slow the player down.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + mud_pos[i].x, yadj + mud_pos[i].y,	mud, NULL,
															xadj + player_pos.x + move_vector, yadj + player_pos.y - move_vector, player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) { move_vector = 1; }
		}
		player_pos.x = player_pos.x + move_vector; // Update player's position
		player_pos.y = player_pos.y - move_vector; // Update player's position
		// Check for collision with trees.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + tree_pos[i].x, yadj + tree_pos[i].y,	tree, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
		// Check for collision with dead lepars.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + dead_lepar_pos[i].x, yadj + dead_lepar_pos[i].y,	dead_lepar, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
	}

	// NorthWest (x-y-)
	if (player_dir_north && !player_dir_south && !player_dir_east && player_dir_west) {
		do_move = true;
		// Check for collision with mud.  If one occurs, slow the player down.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + mud_pos[i].x, yadj + mud_pos[i].y,	mud, NULL,
															xadj + player_pos.x - move_vector, yadj + player_pos.y - move_vector, player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) { move_vector = 1; }
		}
		player_pos.x = player_pos.x - move_vector; // Update player's position
		player_pos.y = player_pos.y - move_vector; // Update player's position
		// Check for collision with trees.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + tree_pos[i].x, yadj + tree_pos[i].y,	tree, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
		// Check for collision with dead lepars.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + dead_lepar_pos[i].x, yadj + dead_lepar_pos[i].y,	dead_lepar, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
	}

	// SouthEast (x+y+)
	if (!player_dir_north && player_dir_south && player_dir_east && !player_dir_west) {
		do_move = true;
		// Check for collision with mud.  If one occurs, slow the player down.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + mud_pos[i].x, yadj + mud_pos[i].y,	mud, NULL,
															xadj + player_pos.x + move_vector, yadj + player_pos.y + move_vector, player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) { move_vector = 1; }
		}
		player_pos.x = player_pos.x + move_vector; // Update player's position
		player_pos.y = player_pos.y + move_vector; // Update player's position
		// Check for collision with trees.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + tree_pos[i].x, yadj + tree_pos[i].y,	tree, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
		// Check for collision with dead lepars.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + dead_lepar_pos[i].x, yadj + dead_lepar_pos[i].y,	dead_lepar, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
	}

	// SouthWest (x-y+)
	if (!player_dir_north && player_dir_south && !player_dir_east && player_dir_west) {
		do_move = true;
		// Check for collision with mud.  If one occurs, slow the player down.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + mud_pos[i].x, yadj + mud_pos[i].y,	mud, NULL,
															xadj + player_pos.x - move_vector, yadj + player_pos.y + move_vector, player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) { move_vector = 1; }
		}
		player_pos.x = player_pos.x - move_vector; // Update player's position
		player_pos.y = player_pos.y + move_vector; // Update player's position
		// Check for collision with trees.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + tree_pos[i].x, yadj + tree_pos[i].y,	tree, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
		// Check for collision with dead lepars.  If one occurs, reverse movement.
		for (i = 0; i < 3; i++) {
			CGapiSurface::Intersect(xadj + dead_lepar_pos[i].x, yadj + dead_lepar_pos[i].y,	dead_lepar, NULL,
															xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {	player_pos = prev_pos; do_move = false;	}
		}
	}

	// If we moved, do bounds checking and update the animation frame.
	if (do_move) {
		if (player_pos.x < 2)		 { player_pos.x = 2;	 }
		if (player_pos.x > 180)  { player_pos.x = 180; }
		if (player_pos.y < 2)		 { player_pos.y = 2;	 }
		if (player_pos.y > 180)  { player_pos.y = 180; }
		player_frame_delay++;
		if (player_frame_delay > 1) {
			player_frame_delay = 0;
			player_frame++;
			if (player_frame > 1) { player_frame = 0; }
		}
	}

	// Check for collision with treasure
	CGapiSurface::Intersect(xadj + treasure_pos.x, yadj + treasure_pos.y,	treasure, NULL,
													xadj + player_pos.x, yadj + player_pos.y,	player[player_frame],
													NULL, &colPoint);
	if (colPoint.x != -1 || colPoint.y != -1) {
		sndObj.playSound(sfxCaching);
		addToScore(50);
		placeTreasure(player_pos);
	}

	// Handle live lepar movement
	live_lepar_move_delay++;
	if (live_lepar_move_delay > 0) { // Time to move yet?
		live_lepar_move_delay = 0;
		POINT prev_pos;
		for (i = 0; i < 3; i++) {
			prev_pos = live_lepar_pos[i]; // Store current position
			// Basic tracking algorithm: accurately track the player, but only if they are within
			// a certain threshold.  If they are outside the threshhold, do a random movement
			if (live_lepar_pos[i].x > player_pos.x && live_lepar_pos[i].x - player_pos.x < 50) {
				live_lepar_pos[i].x--;
			} else {
				if ( (rand() % 10) + 1 <= 5 ) {
					live_lepar_pos[i].x--;
				} else {
					live_lepar_pos[i].x++;
				}
			}
			if (live_lepar_pos[i].x < player_pos.x && player_pos.x - live_lepar_pos[i].x < 50) {
				live_lepar_pos[i].x++;
			} else {
				if ( (rand() % 10) + 1 <= 5 ) {
					live_lepar_pos[i].x++;
				} else {
					live_lepar_pos[i].x--;
				}
			}
			if (live_lepar_pos[i].y > player_pos.y && live_lepar_pos[i].y - player_pos.y < 50) {
				live_lepar_pos[i].y--;
			} else {
				if ( (rand() % 10) + 1 <= 5 ) {
					live_lepar_pos[i].y--;
				} else {
					live_lepar_pos[i].y++;
				}
			}
			if (live_lepar_pos[i].y < player_pos.y && player_pos.y - live_lepar_pos[i].y < 50) {
				live_lepar_pos[i].y++;
			} else {
				if ( (rand() % 10) + 1 <= 5 ) {
					live_lepar_pos[i].y++;
				} else {
					live_lepar_pos[i].y--;
				}
			}
			// Bounds checking
			if (live_lepar_pos[i].x < 2)		 { live_lepar_pos[i].x = 2;	 }
			if (live_lepar_pos[i].x > 180)  { live_lepar_pos[i].x = 180; }
			if (live_lepar_pos[i].y < 2)		 { live_lepar_pos[i].y = 2;	 }
			if (live_lepar_pos[i].y > 180)  { live_lepar_pos[i].y = 180; }
			// Check for collision with trees, reverse move if one occurs
			for (int j = 0; j < 3; j++) {
				CGapiSurface::Intersect(xadj + tree_pos[j].x, yadj + tree_pos[j].y,	tree, NULL,
																xadj + live_lepar_pos[i].x, yadj + live_lepar_pos[i].y,	lepar[live_lepar_frame],
																NULL, &colPoint);
				if (colPoint.x != -1 || colPoint.y != -1) {	live_lepar_pos[i] = prev_pos; }
			}
			// Check for collision with dead lepars, reverse move if one occurs
			for (j = 0; j < 3; j++) {
				CGapiSurface::Intersect(xadj + dead_lepar_pos[j].x, yadj + dead_lepar_pos[j].y,	dead_lepar, NULL,
																xadj + live_lepar_pos[i].x, yadj + live_lepar_pos[i].y,	lepar[live_lepar_frame],
																NULL, &colPoint);
				if (colPoint.x != -1 || colPoint.y != -1) {	live_lepar_pos[i] = prev_pos; }
			}
			// Check for collision with player, end game if one occurs
			CGapiSurface::Intersect(xadj + player_pos.x, yadj + player_pos.y,	player[player_frame], NULL,
															xadj + live_lepar_pos[i].x, yadj + live_lepar_pos[i].y,	lepar[live_lepar_frame],
															NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {
				sndObj.playSound(sfxDeath);
				force_game_over = true;
			}
		}
	}
	// Update animation frame
	live_lepar_frame_delay++;
	if (live_lepar_frame_delay > 3) {
		live_lepar_frame_delay = 0;
		live_lepar_frame++;
		if (live_lepar_frame > 1) { live_lepar_frame = 0; }
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdLeparLand(DWORD dwKey) {

	using namespace ns_LeparLand;

	// Handle up movement events
	if (dwKey == kUp) {
		player_dir_north = true;
		player_dir_south = false;
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_south = true;
		player_dir_north = false;
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west	 = true;
		player_dir_east	 = false;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east	 = true;
		player_dir_west	 = false;
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuLeparLand(DWORD dwKey) {

	using namespace ns_LeparLand;

	// Command button
	if (dwKey == kCommand) {
    hssChannel* c = sndObj.channel(sfxMoaningChannel);
	  if (c->playing()) { c->stop(); }
    moaningPlaying = false;
    miniGameCommandButtonHandler();
	}

	// Handle up movement events
	if (dwKey == kUp) {
		player_dir_north = false;
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_south = false;
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west	 = false;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east	 = false;
	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeLeparLand() {

	using namespace ns_LeparLand;

	// Position player
	player_pos.x			 = 100;
	player_pos.y			 = 100;
	player_frame			 = 0;
	player_frame_delay = 0;
  moaningPlaying     = false;
  sfxMoaningChannel  = NULL;

	int i, j;
	POINT p;

	// Position obstacles
	if (!obstacles_positioned) {

		// Position mud
		doMud:
		for (i = 0; i < 3; i++) {
			posMud:
			mud_pos[i].x = (rand() % 175) + 1;
			mud_pos[i].y = (rand() % 175) + 1;
			if (mud_pos[i].x > 75 && mud_pos[i].x < 119 &&
					mud_pos[i].y > 75 && mud_pos[i].y < 119) {
						goto posMud;
			}
		}
		// If any mud overlaps another, redo them all
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				if (i != j) {
					p.x = mud_pos[i].x; p.y = mud_pos[i].y;
					if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto doMud; }
					p.x = mud_pos[i].x + 24; p.y = mud_pos[i].y;
					if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto doMud; }
					p.x = mud_pos[i].x; p.y = mud_pos[i].y + 24;
					if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto doMud; }
					p.x = mud_pos[i].x + 24; p.y = mud_pos[i].y + 24;
					if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto doMud; }
				}
			}
		}

		// Position trees
		doTrees:
		for (i = 0; i < 3; i++) {
			posTree:
			tree_pos[i].x = (rand() % 175) + 1;
			tree_pos[i].y = (rand() % 163) + 1;
			if (tree_pos[i].x > 75 && tree_pos[i].x < 119 &&
					tree_pos[i].y > 63 && tree_pos[i].y < 119) {
						goto posTree;
			}
			// If this tree overlaps any mud, redo it
			for (j = 0; j < 3; j++) {
				p.x = tree_pos[i].x; p.y = tree_pos[i].y;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posTree; }
				p.x = tree_pos[i].x + 24; p.y = tree_pos[i].y;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posTree; }
				p.x = tree_pos[i].x; p.y = tree_pos[i].y + 36;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posTree; }
				p.x = tree_pos[i].x + 24; p.y = tree_pos[i].y + 36;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posTree; }
			}
		}
		// If any trees overlap another, redo them all
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				if (i != j) {
					p.x = tree_pos[i].x; p.y = tree_pos[i].y;
					if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto doTrees; }
					p.x = tree_pos[i].x + 24; p.y = tree_pos[i].y;
					if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto doTrees; }
					p.x = tree_pos[i].x; p.y = tree_pos[i].y + 36;
					if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto doTrees; }
					p.x = tree_pos[i].x + 24; p.y = tree_pos[i].y + 36;
					if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto doTrees; }
				}
			}
		}

		// Position dead lepars
		doDeadLepars:
		for (i = 0; i < 3; i++) {
			posDeadLepar:
			dead_lepar_pos[i].x = (rand() % 175) + 1;
			dead_lepar_pos[i].y = (rand() % 175) + 1;
			if (dead_lepar_pos[i].x > 81 && dead_lepar_pos[i].x < 119 &&
					dead_lepar_pos[i].y > 81 && dead_lepar_pos[i].y < 119) {
						goto posDeadLepar;
			}
			// If this dead lepar overlaps any mud, redo it
			for (j = 0; j < 3; j++) {
				p.x = dead_lepar_pos[i].x; p.y = dead_lepar_pos[i].y;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto doDeadLepars; }
				p.x = dead_lepar_pos[i].x + 24; p.y = dead_lepar_pos[i].y;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto doDeadLepars; }
				p.x = dead_lepar_pos[i].x; p.y = dead_lepar_pos[i].y + 24;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto doDeadLepars; }
				p.x = dead_lepar_pos[i].x + 24; p.y = dead_lepar_pos[i].y + 24;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto doDeadLepars; }
			}
			// If this dead lepar overlaps any tree, redo it
			for (j = 0; j < 3; j++) {
				p.x = dead_lepar_pos[i].x; p.y = dead_lepar_pos[i].y;
				if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto doDeadLepars; }
				p.x = dead_lepar_pos[i].x + 24; p.y = dead_lepar_pos[i].y;
				if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto doDeadLepars; }
				p.x = dead_lepar_pos[i].x; p.y = dead_lepar_pos[i].y + 24;
				if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto doDeadLepars; }
				p.x = dead_lepar_pos[i].x + 24; p.y = dead_lepar_pos[i].y + 24;
				if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto doDeadLepars; }
			}
		}
		// If any dead lepar overlap another, redo them all
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				if (i != j) {
					p.x = dead_lepar_pos[i].x; p.y = dead_lepar_pos[i].y;
					if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto doDeadLepars; }
					p.x = dead_lepar_pos[i].x + 24; p.y = dead_lepar_pos[i].y;
					if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto doDeadLepars; }
					p.x = dead_lepar_pos[i].x; p.y = dead_lepar_pos[i].y + 24;
					if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto doDeadLepars; }
					p.x = dead_lepar_pos[i].x + 24; p.y = dead_lepar_pos[i].y + 24;
					if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto doDeadLepars; }
				}
			}
		}

		// Position live lepars
		doLiveLepars:
		for (i = 0; i < 3; i++) {
			posLiveLepar:
			live_lepar_pos[i].x = (rand() % 181) + 1;
			live_lepar_pos[i].y = (rand() % 181) + 1;
			if (live_lepar_pos[i].x > 40 && live_lepar_pos[i].x < 160 &&
					live_lepar_pos[i].y > 40 && live_lepar_pos[i].y < 160) {
						goto posLiveLepar;
			}
			for (j = 0; j < 3; j++) {
				p.x = live_lepar_pos[i].x; p.y = live_lepar_pos[i].y;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posLiveLepar; }
				p.x = live_lepar_pos[i].x + 24; p.y = live_lepar_pos[i].y;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posLiveLepar; }
				p.x = live_lepar_pos[i].x; p.y = live_lepar_pos[i].y + 24;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posLiveLepar; }
				p.x = live_lepar_pos[i].x + 24; p.y = live_lepar_pos[i].y + 24;
				if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posLiveLepar; }
			}
			for (j = 0; j < 3; j++) {
				p.x = live_lepar_pos[i].x; p.y = live_lepar_pos[i].y;
				if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto posLiveLepar; }
				p.x = live_lepar_pos[i].x + 24; p.y = live_lepar_pos[i].y;
				if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto posLiveLepar; }
				p.x = live_lepar_pos[i].x; p.y = live_lepar_pos[i].y + 24;
				if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto posLiveLepar; }
				p.x = live_lepar_pos[i].x + 24; p.y = live_lepar_pos[i].y + 24;
				if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto posLiveLepar; }
			}
			for (j = 0; j < 3; j++) {
				p.x = live_lepar_pos[i].x; p.y = live_lepar_pos[i].y;
				if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto posLiveLepar; }
				p.x = live_lepar_pos[i].x + 24; p.y = live_lepar_pos[i].y;
				if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto posLiveLepar; }
				p.x = live_lepar_pos[i].x; p.y = live_lepar_pos[i].y + 24;
				if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto posLiveLepar; }
				p.x = live_lepar_pos[i].x + 24; p.y = live_lepar_pos[i].y + 24;
				if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto posLiveLepar; }
			}
			live_lepar_dir_north[i] = false;
			live_lepar_dir_south[i] = false;
			live_lepar_dir_east[i]  = false;
			live_lepar_dir_west[i]  = false;
		}
		// If any live lepar overlap another, redo them all
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				if (i != j) {
					p.x = live_lepar_pos[i].x; p.y = live_lepar_pos[i].y;
					if (PtInRect(CRect(live_lepar_pos[j].x, live_lepar_pos[j].y, live_lepar_pos[j].x + 24, live_lepar_pos[j].y + 24), p)) { goto doLiveLepars; }
					p.x = live_lepar_pos[i].x + 24; p.y = live_lepar_pos[i].y;
					if (PtInRect(CRect(live_lepar_pos[j].x, live_lepar_pos[j].y, live_lepar_pos[j].x + 24, live_lepar_pos[j].y + 24), p)) { goto doLiveLepars; }
					p.x = live_lepar_pos[i].x; p.y = live_lepar_pos[i].y + 24;
					if (PtInRect(CRect(live_lepar_pos[j].x, live_lepar_pos[j].y, live_lepar_pos[j].x + 24, live_lepar_pos[j].y + 24), p)) { goto doLiveLepars; }
					p.x = live_lepar_pos[i].x + 24; p.y = live_lepar_pos[i].y + 24;
					if (PtInRect(CRect(live_lepar_pos[j].x, live_lepar_pos[j].y, live_lepar_pos[j].x + 24, live_lepar_pos[j].y + 24), p)) { goto doLiveLepars; }
				}
			}
		}

		// Miscellaneous setup
		live_lepar_frame			 = 0;
		live_lepar_frame_delay = 0;
		live_lepar_move_delay  = 0;
		obstacles_positioned   = true;

		// Position treasure
		placeTreasure(player_pos);

	}

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endLeparLand() {

	using namespace ns_LeparLand;

  hssChannel* c = sndObj.channel(sfxMoaningChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadLeparLand(CGapiSurface* backbuffer) {

	using namespace ns_LeparLand;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 2; i++) { lepar[i]  = NULL; }
      for (i = 0; i < 2; i++) { player[i] = NULL; }
      tree         = NULL;
      mud          = NULL;
      dead_lepar   = NULL;
      treasure     = NULL;
      player_still = NULL;
      sfxDeath     = NULL;
      sfxCaching   = NULL;
      sfxMoaning   = NULL;
		break; }

		case 2: {
			tree         = new CGapiSurface(); createSurface(TEXT("lepar_land : GFX_LEPAR_LAND_TREE"),         tree->CreateSurface        (0, m_config.hInstance, GFX_LEPAR_LAND_TREE,         TEXT("GRAPHICS"))); tree->SetColorKey        (RGB(255, 128, 255));
			mud          = new CGapiSurface(); createSurface(TEXT("lepar_land : GFX_LEPAR_LAND_MUD"),          mud->CreateSurface         (0, m_config.hInstance, GFX_LEPAR_LAND_MUD,          TEXT("GRAPHICS"))); mud->SetColorKey         (RGB(255, 128, 255));
			lepar[0]     = new CGapiSurface(); createSurface(TEXT("lepar_land : GFX_LEPAR_LAND_LEPAR_00"),     lepar[0]->CreateSurface    (0, m_config.hInstance, GFX_LEPAR_LAND_LEPAR_00,     TEXT("GRAPHICS"))); lepar[0]->SetColorKey    (RGB(255, 128, 255));
			lepar[1]     = new CGapiSurface(); createSurface(TEXT("lepar_land : GFX_LEPAR_LAND_LEPAR_01"),     lepar[1]->CreateSurface    (0, m_config.hInstance, GFX_LEPAR_LAND_LEPAR_01,     TEXT("GRAPHICS"))); lepar[1]->SetColorKey    (RGB(255, 128, 255));
			dead_lepar   = new CGapiSurface(); createSurface(TEXT("lepar_land : GFX_LEPAR_LAND_DEAD_LEPAR"),   dead_lepar->CreateSurface  (0, m_config.hInstance, GFX_LEPAR_LAND_DEAD_LEPAR,   TEXT("GRAPHICS"))); dead_lepar->SetColorKey  (RGB(255, 128, 255));
			treasure     = new CGapiSurface(); createSurface(TEXT("lepar_land : GFX_LEPAR_LAND_TREASURE"),     treasure->CreateSurface    (0, m_config.hInstance, GFX_LEPAR_LAND_TREASURE,     TEXT("GRAPHICS"))); treasure->SetColorKey    (RGB(255, 128, 255));
			player[0]    = new CGapiSurface(); createSurface(TEXT("lepar_land : GFX_LEPAR_LAND_PLAYER_00"),    player[0]->CreateSurface   (0, m_config.hInstance, GFX_LEPAR_LAND_PLAYER_00,    TEXT("GRAPHICS"))); player[0]->SetColorKey   (RGB(255, 128, 255));
			player[1]    = new CGapiSurface(); createSurface(TEXT("lepar_land : GFX_LEPAR_LAND_PLAYER_01"),    player[1]->CreateSurface   (0, m_config.hInstance, GFX_LEPAR_LAND_PLAYER_01,    TEXT("GRAPHICS"))); player[1]->SetColorKey   (RGB(255, 128, 255));
			player_still = new CGapiSurface(); createSurface(TEXT("lepar_land : GFX_LEPAR_LAND_PLAYER_STILL"), player_still->CreateSurface(0, m_config.hInstance, GFX_LEPAR_LAND_PLAYER_STILL, TEXT("GRAPHICS"))); player_still->SetColorKey(RGB(255, 128, 255));
			sfxDeath     = new hssSound();     loadSFX      (TEXT("lepar_land : SFX_DEATH"),                   sfxDeath->load             (m_config.hInstance,    SFX_DEATH));                                     sfxDeath->loop           (false);
      sfxCaching   = new hssSound();     loadSFX      (TEXT("lepar_land : SFX_CACHING"),                 sfxCaching->load           (m_config.hInstance,    SFX_CACHING));                                   sfxCaching->loop         (false);
      sfxMoaning   = new hssSound();     loadSFX      (TEXT("lepar_land : SFX_LEPAR_LAND_MOANING"),      sfxMoaning->load           (m_config.hInstance,    SFX_LEPAR_LAND_MOANING));                        sfxMoaning->loop         (true);
		break; }

    case 3: {
			initializeLeparLand();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
    break; }

		// End of loading
		default: {
			loading	= false;
			loading_step = 0;
			processEvents = true;
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyLeparLand(CGapiSurface* backbuffer) {

	using namespace ns_LeparLand;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete sfxDeath;
			delete sfxCaching;
			delete tree;
			delete mud;
			delete lepar[0];
			delete lepar[1];
			delete dead_lepar;
			delete sfxMoaning;
		break; }

		case 3: {
			delete player_still;
			delete treasure;
			delete player[0];
			delete player[1];
			obstacles_positioned = false; // So this happens next invocation of this game
		break; }

		default: {
			// All done destroying, start loading the next screen
      if (screen_after_destroy == csNewGameType) { // If we just finished playing mini-game melee mode, we need to do some special tricks to get back there... first, re-load the menu stuff, then set our special flag so that loader knows to go to the new game type screen instead
        screen_after_destroy = csMainMenu;
        jumpBackToNewGameType = true;
      }
      current_screen = screen_after_destroy;
			doLoad();
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************
namespace ns_LeparLand {


void placeTreasure(POINT player_pos) {

	using namespace ns_LeparLand;

	POINT p, point;
	int j;
	posTreasure:
	point.x = (rand() % 175) + 1;
	point.y = (rand() % 175) + 1;
	// If treasure would overlap mud, retry
	for (j = 0; j < 3; j++) {
		p.x = point.x; p.y = point.y;
		if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posTreasure; }
		p.x = point.x + 24; p.y = point.y;
		if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posTreasure; }
		p.x = point.x; p.y = point.y + 24;
		if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posTreasure; }
		p.x = point.x + 24; p.y = point.y + 24;
		if (PtInRect(CRect(mud_pos[j].x, mud_pos[j].y, mud_pos[j].x + 24, mud_pos[j].y + 24), p)) { goto posTreasure; }
	}
	// If treasure would overlap a tree, retry
	for (j = 0; j < 3; j++) {
		p.x = point.x; p.y = point.y;
		if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto posTreasure; }
		p.x = point.x + 24; p.y = point.y;
		if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto posTreasure; }
		p.x = point.x; p.y = point.y + 24;
		if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto posTreasure; }
		p.x = point.x + 24; p.y = point.y + 24;
		if (PtInRect(CRect(tree_pos[j].x, tree_pos[j].y, tree_pos[j].x + 24, tree_pos[j].y + 36), p)) { goto posTreasure; }
	}
	// If treasure would overlap a dead lepar, retry
	for (j = 0; j < 3; j++) {
		p.x = point.x; p.y = point.y;
		if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto posTreasure; }
		p.x = point.x + 24; p.y = point.y;
		if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto posTreasure; }
		p.x = point.x; p.y = point.y + 24;
		if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto posTreasure; }
		p.x = point.x + 24; p.y = point.y + 24;
		if (PtInRect(CRect(dead_lepar_pos[j].x, dead_lepar_pos[j].y, dead_lepar_pos[j].x + 24, dead_lepar_pos[j].y + 24), p)) { goto posTreasure; }
	}
	// If treasure would overlap player, retry
	p.x = point.x; p.y = point.y;
	if (PtInRect(CRect(player_pos.x, player_pos.y, player_pos.x + 18, player_pos.y + 18), p)) { goto posTreasure; }
	p.x = point.x + 24; p.y = point.y;
	if (PtInRect(CRect(player_pos.x, player_pos.y, player_pos.x + 18, player_pos.y + 18), p)) { goto posTreasure; }
	p.x = point.x; p.y = point.y + 24;
	if (PtInRect(CRect(player_pos.x, player_pos.y, player_pos.x + 18, player_pos.y + 18), p)) { goto posTreasure; }
	p.x = point.x + 24; p.y = point.y + 24;
	if (PtInRect(CRect(player_pos.x, player_pos.y, player_pos.x + 18, player_pos.y + 18), p)) { goto posTreasure; }

	treasure_pos = point;

}


} // End of namespace
