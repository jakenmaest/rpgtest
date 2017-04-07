//
// NCURSES RPG ROGUELIKE - Raymond Mc Cambridge 12th Mar, 2017
//
//   TODO : 
//          Write level start function
//          Write screen resize function (center around player)
//
//

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "rpgtypes.h"
#include "player.h"
#include "scene.h"

// Declare functions
void inputHandle(WINDOW *mapWin, FILE *mapF, Scene *lMap, WINDOW *invWin, WINDOW *statWin, Player *plr); // input handler

// ENTRY POINT
int main(int argc, char **argv){
    // init ncurses
    initscr();
    // start_color();
    raw(); // Change to raw when inputhandler is written
    curs_set(0); // remove blinking cursor
    // start_color(); // start color system
    // init_pair(1, COLOR_GREEN, COLOR_RED); // green on red background
    // init player
    Player *plr = malloc(sizeof(Player)); // create a player in memory
    createTestPlayer(plr); // init test player

    // windows init
    Dimensions termSize = getWinDim(stdscr); // get primary window dimensions
    WINDOW *statWin = newwin(8, termSize.w, termSize.h-9, 0); // create statistics window
    WINDOW *invWin = newwin(termSize.h-8, 18, 0, 0); // create inventory window
    WINDOW *mapWin = newwin(termSize.h-8, termSize.w-19, 0, 19); // create map window

    // open map file or quit if failed
    FILE *mapF = fopen("./lvl1.map","r"); // load map file descriptor
    if(mapF == NULL) {
	    delwin(statWin);
	    delwin(invWin);
	    delwin(mapWin);
	    endwin();
            printf("Couldn't open map file...\n");
	    exit(0);
    }

    /* test scene init */
    Scene *lMap = malloc(sizeof(Scene)); // create scene object 
    lMap->size = 15000; // Total Size of Map
    lMap->dim.h = 50; // Height of 40
    lMap->dim.w = 300; // Height of 40
    lMap->rPos.y = 0; // y position on map
    lMap->rPos.x = 0; // x position on map
    lMap->pos.y = 0; // real y
    lMap->pos.x = 0; // real x
    loadScene(mapF, lMap);
    // refresh
    refresh();

    /* test cell Status */
    int i;
    for(i = 0; i < MAPSIZE; i++) {
        lMap->scnStat[i] = '1';
//	if (i % 2 == 0) {
//            lMap->scnStat[i] = '1';
//	} else {
//	    lMap->scnStat[i] = '0';
//	}
    }

    // MAIN LOOP
    while(1) {
	// get terminal size
        termSize = getWinDim(stdscr);
	// draw stats window
        drawStatWin(statWin, mapWin, lMap, termSize, plr);
	// draw inventory window
        drawInvWin(invWin, termSize);
	// draw map window, scene and player
        drawMapWin(mapWin, mapF, lMap, termSize, plr);
	// handle input
        inputHandle(mapWin, mapF, lMap, invWin, statWin, plr);
    }

    // end game
    getch();
    endwin();
    fclose(mapF);
    return 0;
}

// Input Handler
void inputHandle(WINDOW *mapWin, FILE *mapF, Scene *lMap, WINDOW *invWin, WINDOW *statWin, Player *plr) {
    int ch;
    ch = getch();
    switch(ch) {
        case 'W':
        case 'w':
            movePlayer(DIR_UP, plr, lMap, mapWin);
            break;
        case 'A':
        case 'a':
            movePlayer(DIR_LEFT, plr, lMap, mapWin);
	    break;
        case 'S':
	case 's':
            movePlayer(DIR_DOWN, plr, lMap, mapWin);
	    break;
        case 'D':
        case 'd':
            movePlayer(DIR_RIGHT, plr, lMap, mapWin);
	    break;
        case 'q':
        case 'Q': // Quit
	    delwin(statWin);
	    delwin(invWin);
	    delwin(mapWin);
	    endwin();
            printf("Exit game cleanly...\n");
	    fclose(mapF);
	    exit(0);
	    break;
        default:
	    break;
    }
}
