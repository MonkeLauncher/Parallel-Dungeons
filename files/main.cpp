// Well ... it appears that you see this code
// I have a warning for you:
// If you want to read it
// Don't do it.

// you will end up with scrambled eggs instead of your brain
// it is painful to read.
// Even for me.

// Have fun!

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <time.h>

#include "code/player.h"

#include "code/maze.h"
#include "code/draw.h"

using namespace sf;
using namespace std;


// general variables
RenderWindow okno(sf::VideoMode::getDesktopMode(), "Parallel Dungeons", Style::Fullscreen);		// yeah why do I even name this window when I set Fullscreen
View view (sf::Vector2f(0, 0), sf::Vector2f(okno.getSize()));
player gracz;    // player declaration

int topMap = 1;
int map1Push = 0;
int StarterWall = 1;
int mapSize;
int aniCyrculation = 0;
string mapType = "grinder";
int drawSize[4];
int bigCellDraw = 1;

// map varibles
char map0[50][50], map1[50][50], map2[50][50], mobMap1[50][50], mobMap2[50][50];


Sprite block, blockDark, celling, cellingDark, flor, shadow, wallBottom, wallBottomDark, door, exitt, jumper, station, stationDark, cellWide, cellHig;
Texture wall, wallDark, top, topDark, wood, dark, brickFloor, brickFloorDark, archway, openDoor, crack, thing, thingDark, topWide, topHig1, topHig2;



// -----===== Int Main =====-----
int main () {

    // ---=== Creating the window ===---
    Event zdazenie;
    srand(time(NULL));
    okno.setFramerateLimit(60);
    okno.setVerticalSyncEnabled(true);
    
    gracz.cords[0] = -2;
    StarterWall = rand() % 4;
    loadToDraw();


    // -----===== programe loop =====-----
    while (okno.isOpen()) {


        // --== if there is an event ==--
        while (okno.pollEvent(zdazenie)) {

            // ---=== closing window ===---
            if (zdazenie.type == zdazenie.Closed) okno.close();
            if (Keyboard::isKeyPressed(Keyboard::Escape)) okno.close();
        }
        
        
        aniCyrculation++;
        aniCyrculation %= 5040;
        
        
        // ---=== set of functions that have to run when we generate the new map ===---
	    if (map0[gracz.cords[0]][gracz.cords[1]] == 'd' && (gracz.cords[0] <= 0 || gracz.cords[0] >= mapSize || gracz.cords[1] <= 0 || gracz.cords[1] >= mapSize - 1)) {
	    	if (bigCellDraw == 0)
	    	    aniCyrculation = 0;
	    	
	    	if (gracz.cords[0] <= 0) 
	    		bigCellDraw = 4;
			
			else if (gracz.cords[0] >= mapSize) 
				bigCellDraw = 2;
			
			else if (gracz.cords[1] <= 0) 
				bigCellDraw = 1;
			
			else if (gracz.cords[1] >= mapSize - 1) 
				bigCellDraw = 3;
		} 
		
		
		if (aniCyrculation == 21 && bigCellDraw != 0) {
			
			// create maze
	    	if (mapType == "grinder") {
		    	mapSize = rand() % 16 + 15;
		    	StarterWall = maze(mapSize, StarterWall);
			}
		}
		
		if (aniCyrculation == 40 && bigCellDraw != 0) bigCellDraw = 0;
		


        // ---=== character actions ===---
        view.setCenter(gracz.getPosition().x + 38, gracz.getPosition().y - 74);
        
        gracz.posModeCheck();
        gracz.cordControll();
        gracz.collision();

        if (gracz.getPosMode() == "move")
            gracz.posMove ();
        else if (gracz.getPosMode() == "dash")
            gracz.posDash ();
        else if (gracz.getPosMode() == "jump")
        	gracz.posJump ();

        gracz.posShadow ();


        // ---=== drawing ===---
        okno.clear(Color::Black);
        
        okno.setView(view);
        
        
        drawSize[0] = gracz.cords[0] - ((okno.getSize().x / 120 + 2) / 2);
        drawSize[1] = gracz.cords[0] + ((okno.getSize().x / 120 + 2) / 2);
        drawSize[2] = gracz.cords[1] - ((okno.getSize().y / 120 + 4) / 2);
        drawSize[3] = gracz.cords[1] + ((okno.getSize().y / 120 + 6) / 2);
        
        for (int i = 0; i < 4; i++) {
        	if (drawSize[i] < 0) drawSize[i] = 0;
        	if (drawSize[i] > mapSize - 1) drawSize[i] = mapSize - 1;
		}
        
        drawMap(drawSize[0], drawSize[1], drawSize[2], drawSize[3], mapSize);
//        partyMode();
        
        okno.display();
    }
}


// ps
// you are not even crazy enough to go into maze.cpp
