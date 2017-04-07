#ifndef SCENE_H
#define SCENE_H

#include <ncurses.h>
#include "rpgtypes.h"
#include "player.h"

// Declare functions
Dimensions getWinDim(WINDOW *win); // get dimensions y,x,h,w of a given window
void drawStatWin(WINDOW *statWin, WINDOW *mapWin, Scene *lMap, Dimensions termSize, Player *plr); // draw statistics window
void drawInvWin(WINDOW *invWin, Dimensions termSize); // draw inventory window
void drawMapWin(WINDOW *mapWin, FILE *mapF, Scene *lMap, Dimensions termSize, Player *plr); // draw map window
void drawScene(WINDOW *mapWin, Scene *lMap, Player *plr); // draw scene
void loadScene(FILE *mapF, Scene *lMap); // load a scene from file
void drawPlayer(WINDOW *mapWin, Player *plr); // draw Player on map

// discover cell
void discoverCell(char *cellCh, char *asc, Scene *lMap) {
    // number discovery
    for(int asc=49; asc < 58; asc++) {
        if ((int)cellCh == asc) {
            for(int i = 0; i < MAPSIZE; i++) {
		        if(lMap->scnMap[i] == asc) {
		            lMap->scnMap[i] = '.';
		        }
		    }
		}
    }
    for(int asc=97; asc < 123; asc++) {
       	if ((int)cellCh == asc) {
       	    for(int i = 0; i < MAPSIZE; i++) {
	    		if(lMap->scnMap[i] == asc) {
	        	    lMap->scnMap[i] = '#';
	    		}
		    }
		}
    }
}

// Get dimmapWin,ensions of a window
Dimensions getWinDim(WINDOW *win) {
    Dimensions winDim;
    getbegyx(win, winDim.y, winDim.x);
    getmaxyx(win, winDim.h, winDim.w);
    return winDim;
}

// Draw the map window
void drawMapWin(WINDOW *mapWin, FILE *mapF, Scene *lMap, Dimensions termSize, Player *plr) {
    werase(mapWin);
    wresize(mapWin, termSize.h-8, termSize.w-19);
    //wborder(mapWin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    drawScene(mapWin, lMap, plr);
    wrefresh(mapWin);
}

// Draw the inventory window
void drawInvWin(WINDOW *invWin, Dimensions termSize) {
    werase(invWin);
    wresize(invWin, termSize.h-8, 19);
    wborder(invWin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    wrefresh(invWin);
}

// Draw the stats window
void drawStatWin(WINDOW *statWin, WINDOW *mapWin, Scene *lMap, Dimensions termSize, Player *plr) {
    werase(statWin);
    mvwin(statWin, termSize.h-8, 0);
    wborder(statWin, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
     // get dimensions of map screen
    //Dimensions mapDim = getWinDim(mapWin);

    mvwprintw(statWin, 1, 1, "Statistics");
    mvwprintw(statWin, 2, 1, " Plr->pos.y: %d", plr->pos.y);
    mvwprintw(statWin, 3, 1, "lMap->pos.y: %d", lMap->pos.y);
    mvwprintw(statWin, 4, 1, "Plr->rPos.y: %d", plr->rPos.y);
    wrefresh(statWin);
}

// Draw the scene on the mapWin
void drawScene(WINDOW *mapWin, Scene *lMap, Player *plr) {
Position mapIndex;
    int mapCount = 0;
    for(mapIndex.y = 0; mapIndex.y < lMap->dim.h; mapIndex.y++) {
        for(mapIndex.x = 0; mapIndex.x < lMap->dim.w; mapIndex.x++) {
            mapCount++;
	    // if cell active print character
	    if(lMap->scnStat[mapCount] == '0') {
	        // cell inactive
                mvwprintw(mapWin, mapIndex.y + lMap->pos.y, mapIndex.x + lMap->pos.x, "%c", ' ');
	    } else {
		// handle active status'
                mvwprintw(mapWin, mapIndex.y + lMap->pos.y, mapIndex.x + lMap->pos.x, "%c", lMap->scnMap[mapCount]);
	    }
        }
    }
    //attron(COLOR_PAIR(1));
    drawPlayer(mapWin, plr);
    //attroff(COLOR_PAIR(1));
}

// load a scene into the scene manager
void loadScene(FILE *mapF, Scene *lMap) {
    Position mapIndex; // Current map parse index
    rewind(mapF); // reset pointer to start of file
    // map chars from file to mapWin including real position co-efficient
    int mapCount = 0;
    for(mapIndex.y = 0; mapIndex.y < lMap->dim.h; mapIndex.y++) {
        for(mapIndex.x = 0; mapIndex.x < lMap->dim.w; mapIndex.x++) {
	    char tempCh = fgetc(mapF);
            lMap->scnMap[mapCount] = tempCh;
	    mapCount++;
        }
    }
}

#endif /* SCENE_H */
