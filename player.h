#ifndef PLAYER_H
#define PLAYER_H

/*
    TODO:
         break move player out into move player discover cell functions
         
*/

#include <ncurses.h>
#include "rpgtypes.h"
#include "scene.h"

// Declare functions
void createTestPlayer(Player *plr); // create a player for test purposes
void drawPlayer(WINDOW *mapWin, Player *plr); // draw Player on map
void movePlayer(int dir, Player *plr, Scene *lMap,  WINDOW *mapWin); // move the player


void drawPlayer(WINDOW *mapWin, Player *plr) {
    mvwprintw(mapWin, plr->pos.y, plr->pos.x, "%c", plr->ch);
}

void movePlayer(int dir, Player *plr, Scene *lMap,  WINDOW *mapWin) {
    Dimensions mapDim;
    mapDim = getWinDim(mapWin);
    char cellCh;
    switch(dir) {
        case DIR_UP:
	    cellCh = mvwinch(mapWin,plr->pos.y-1, plr->pos.x);
	    switch(cellCh) {
		// simple ground corridor areas
	    case '#':
		case '.':
		case '/':
		    if(plr->pos.y<6 && lMap->pos.y<0) {
                        plr->rPos.y--;
                        lMap->pos.y++;
                    }
    	        else if(plr->pos.y > 0) {
    	            plr->pos.y--;
                    plr->rPos.y--;
    	            }
                    break;
	        case '@': 
		        break;
	        case '<':
		        break;
	        case '>':
		        break;
		default:
		    // area discovery by ascii
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
		    break;
	    }
            break;
        case DIR_LEFT:
	    cellCh = mvwinch(mapWin,plr->pos.y, plr->pos.x-1);
	    switch(cellCh) {
            // walk-on-able cells
	        case '.':
	        case '/':
	        case '#':
                    if(plr->pos.x<6 && lMap->pos.x<0) {
                        lMap->pos.x++;
                        plr->rPos.x--;
		    } else if(plr->pos.x > 0) {
                        plr->rPos.x--;
    		        plr->pos.x--;
                    }
		        break;
		    case '@': 
		        break;
	        case '<':
		        break;
	        case '>':
		        break;

                 default:
    		    // area discovery by ascii
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
		    break;
            }
	    break;
        case DIR_DOWN:
	    cellCh = mvwinch(mapWin,plr->pos.y+1, plr->pos.x);
	    switch(cellCh) {
	        // walk-on-able cells
	        case '.':
	        case '/':
	        case '#':
        	    if(plr->pos.y>(mapDim.h-5) && plr->rPos.y<=(lMap->dim.h-5)) {
                        lMap->pos.y--;
                        plr->rPos.y++;
                    }
                    else if(plr->rPos.y < lMap->dim.h-1) {
          		plr->pos.y++;
                        plr->rPos.y++;
                    }
    		    break;
	        case '@': 
		        break;
	        case '<':
		        break;
	        case '>':
		        break;
		default:
    		    // area discovery by ascii
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
		    break;
            }
	    break;
        case DIR_RIGHT:
	    cellCh = mvwinch(mapWin,plr->pos.y, plr->pos.x+1);
	    switch(cellCh) {
            // walk-on-able cells
	        case '.':
	        case '/':
	        case '#':
		    if(plr->pos.x>=(mapDim.w-6) && plr->rPos.x<=(lMap->dim.w-6)) {
        	        lMap->pos.x--;
			plr->rPos.x++;
            		}
           		else if(plr->rPos.x < lMap->dim.w-1){
                	    plr->pos.x++;
                	    plr->rPos.x++;
            		}
	            break;
	        case '@': 
		        break;
	        case '<':
		        break;
	        case '>':
		        break;
                default:
    		    // area discovery by ascii
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
                    break;
                } 
        default:
            break;
    } 
}

// Create a test player
void createTestPlayer(Player *plr) {
     strcpy(plr->name, "test_player");
     plr->ch = '@';
     plr->color[0] = 3;
     plr->color[1] = 1;
     plr->stats.stamina = 25;
     plr->pos.y = 15;
     plr->pos.x = 13;
     plr->rPos.y = 10;
     plr->rPos.x = 10;
     plr->stats.hp = 20;
     plr->stats.hp = 20;
     plr->stats.strength = 5;
}

#endif /* PLAYER_H */
