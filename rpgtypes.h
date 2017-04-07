#ifndef RPGTYPES_H
#define RPGTYPES_H

#define MAPSIZE 15000 // Test map size
#define MAX_NAME_SIZE 30

#define DIR_UP 0
#define DIR_LEFT 1
#define DIR_DOWN 2
#define DIR_RIGHT 3


typedef struct Dimensions {
    int y, x, h, w;
} Dimensions;

typedef struct Position {
    int y, x;
} Position;

typedef struct Statistics {
    int hp, stamina, strength;
} Statistics;

typedef struct Player {
    char name[MAX_NAME_SIZE]; // Name
    char ch; // ASCII Character used as player
    int color[2]; // Player Color pair 0:foreground;1:background
    Statistics stats; // Player Stats
    Position pos; // position on mapWin
    Position rPos; // real position on map
} Player;

typedef struct Scene {
    int size;
    char name[MAX_NAME_SIZE]; // Level name
    char mapFileName[MAX_NAME_SIZE*3]; // Map file name
    Dimensions dim; // Primary dimensions of Map
    Position pos; // Position on screen
    Position rPos; // Real Position in game
    char scnMap[MAPSIZE]; // character map
    char scnStat[MAPSIZE]; // character map
} Scene;

#endif /* RPGTYPES_H */
