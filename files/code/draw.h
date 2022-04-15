#ifndef DRAW_H
#define DRAW_H

#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "player.h"


using namespace std;
using namespace sf;

extern RenderWindow okno;
extern char map0[][50], map1[][50], map2[][50], mobMap1[][50], mobMap2[][50];
extern player gracz;
extern int map1Push, aniCyrculation, bigCellDraw, topMap;

extern Sprite block, blockDark, celling, cellingDark, flor, shadow, wallBottom, wallBottomDark, door, exitt, jumper, station, stationDark, cellWide, cellHig;
extern Texture wall, wallDark, top, topDark, wood, dark, brickFloor, brickFloorDark, archway, openDoor, crack, thing, thingDark, topWide, topHig1, topHig2;


void drawMap (int xStart, int xEnd, int yStart, int yEnd, int size);
void loadToDraw ();
void partyMode ();


#endif
