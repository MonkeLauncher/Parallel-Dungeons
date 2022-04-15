#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "draw.h"
#include "player.h"

void loadToDraw () {
	
	// setting textures etc.
	wall.loadFromFile("obrazy/bloki/brick_base.png");
	wallDark.loadFromFile("obrazy/bloki/brick_base_dark.png");
	top.loadFromFile("obrazy/bloki/brick_top_base.png");
	topDark.loadFromFile("obrazy/bloki/brick_top_base_dark.png");
	wood.loadFromFile("obrazy/bloki/floor_base.png");
	dark.loadFromFile("obrazy/bloki/shadow.png");
	brickFloor.loadFromFile("obrazy/bloki/wall_bottom_base.png");
	brickFloorDark.loadFromFile("obrazy/bloki/wall_bottom_base_dark.png");
	archway.loadFromFile("obrazy/bloki/door_closed_base.png");
	openDoor.loadFromFile("obrazy/bloki/door_open_base.png");
	crack.loadFromFile("obrazy/bloki/floor_cracked_base.png");
	thing.loadFromFile("obrazy/bloki/the_station.png");
	thingDark.loadFromFile("obrazy/bloki/the_station_dark.png");
	topWide.loadFromFile("obrazy/bloki/big_celling_up.png");
	topHig1.loadFromFile("obrazy/bloki/big_celling_side.png");
	topHig2.loadFromFile("obrazy/bloki/big_celling_side_dark.png");
	
	
	block.setTexture(wall);
	block.setScale(sf::Vector2f(4, 4));
	block.setOrigin(0, block.getLocalBounds().height);
	
	blockDark.setTexture(wallDark);
	blockDark.setScale(sf::Vector2f(4, 4));
	blockDark.setOrigin(0, blockDark.getLocalBounds().height);
	
	celling.setTexture(top);
	celling.setScale(sf::Vector2f(4, 4));
	celling.setOrigin(0, celling.getLocalBounds().height);
	
	cellingDark.setTexture(topDark);
	cellingDark.setScale(sf::Vector2f(4, 4));
	cellingDark.setOrigin(0, cellingDark.getLocalBounds().height);
	
	flor.setTexture(wood);
	flor.setScale(sf::Vector2f(4, 4));
	flor.setOrigin(0, flor.getLocalBounds().height);
	
	shadow.setTexture(dark);
	shadow.setScale(sf::Vector2f(4, 4));
	shadow.setOrigin(0, shadow.getLocalBounds().height);
	
	wallBottom.setTexture(brickFloor);
	wallBottom.setScale(sf::Vector2f(4, 4));
	wallBottom.setOrigin(0, wallBottom.getLocalBounds().height);
	
	wallBottomDark.setTexture(brickFloorDark);
	wallBottomDark.setScale(sf::Vector2f(4, 4));
	wallBottomDark.setOrigin(0, wallBottomDark.getLocalBounds().height);
	
	door.setTexture(archway);
	door.setScale(sf::Vector2f(4, 4));
	door.setOrigin(0, door.getLocalBounds().height);
	
	exitt.setTexture(openDoor);
	exitt.setScale(sf::Vector2f(4, 4));
	exitt.setOrigin(0, exitt.getLocalBounds().height);
	
	jumper.setTexture(crack);
	jumper.setScale(sf::Vector2f(4, 4));
	jumper.setOrigin(0, jumper.getLocalBounds().height);
	
	station.setTexture(thing);
	station.setScale(sf::Vector2f(4, 4));
	station.setOrigin(0, station.getLocalBounds().height);
	
	stationDark.setTexture(thingDark);
	stationDark.setScale(sf::Vector2f(4, 4));
	stationDark.setOrigin(0, stationDark.getLocalBounds().height);
	
	cellWide.setTexture(topWide);
	cellWide.setScale(sf::Vector2f(18, 18));
	cellWide.setOrigin(0, cellWide.getLocalBounds().height);
}

void drawMap (int xStart, int xEnd, int yStart, int yEnd, int size) {
	
	
	// -----===== DRAWING THE MAP =====-----
	
	bool cellDraw [8];
	bool wallChoose[8];
	char a;
	int frameChoose[2];
	static int topPush;
	
	
	// for each position just move the same sprite and draw it several times
	for (int i = yStart; i < yEnd + 1; i++) {
		for (int j = xStart; j < xEnd + 1; j++) {
			
			
			
			// Drawing All The floor
			if ((mobMap1[j][i + 1] != '0' && map0[j][i + 1] == '#') || map0[j][i + 1] != '#' || (mobMap2[j][i + 1] != '0' && map2[j][i + 1] == '#') || map2[j][i + 1] != '#') {
				
				
				// setting proper textuers
				if (topMap == 2) {
					flor.setTextureRect(IntRect(0, 30, 30, 30));
					jumper.setTextureRect(IntRect(0, 30, 30, 30));
				}
				
				else {
					flor.setTextureRect(IntRect(0, 0, 30, 30));
					jumper.setTextureRect(IntRect(0, 0, 30, 30));
				}				
				
				
				// drawing normal flor
				if (map0[j][i] == '.' || map0[j][i] == 'D' || map0[j][i] == 'd') {
					flor.setPosition(j * 120, (i + 4) * 120);
					okno.draw(flor);
				}
				
				
				// drawing cracked flor
				if (map0[j][i] == '-') {
					jumper.setPosition(j * 120, (i + 4) * 120);
					okno.draw(jumper);
				}
				
				
				// generaly adding some shade between walls and flor. This is where pope will hide
				if (((map0[j][i - 1] == '#' || (map1[j][i - 1] == '#' && map1Push < 240)) || (map1[j][i - 1] == 'o' && (topMap == 0 || topMap == 1) && map1Push < 240) || (((map2[j][i - 1] == '#' || map2[j][i - 1] == 'o') && (topMap == 2 || topMap == 0) && map1Push > 120)) || (map0[j][i - 1] == 'd' || map0[j][i - 1] == 'D')) && (map0[j][i] == '.' || map0[j][i] == '-') && !(topMap == 2 && map2[j][i] == '#') && !(topMap == 1 && map1[j][i] == '#')) {
					shadow.setPosition(j * 120, (i + 3) * 120 - 60);
					if (map0[j][i - 1] == 'd' || map0[j][i - 1] == 'D') 
						shadow.move (0, -60);
						
					okno.draw(shadow);
				}
			}
			
			
			// controlling trancsparency on mobMap1
			if (topMap != 2) {
				if ((gracz.cords[0] == j && i - 1 == gracz.cords[1] && j != size - 1) || (gracz.cords[0] == j - 1 && i - 1 == gracz.cords[1] && (map0[j - 1][i] == '#' || map1[j - 1][i] == '#') && map0[j][i - 1] != '#' && map1[j][i - 1] != '#' && j != size - 1) || (gracz.cords[1] == i - 2 && gracz.cords[0] == j && mobMap1[j][i - 1] != '0' && (map0[j][i - 1] == '#' || map1[j][i - 1] == '#'))) {
					if (mobMap1[j][i] < '5' && aniCyrculation % 2 == 0) mobMap1[j][i]++;
				}
				
				else {
					if (mobMap1[j][i] > '0' && aniCyrculation % 2 == 0) mobMap1[j][i]--;
				}
			}
				
			
			
			// controlling trancsparency on mobMap2
			if (topMap != 1) {
				if ((gracz.cords[0] == j && i - 1 == gracz.cords[1] && j != size - 1) || (gracz.cords[0] == j - 1 && i - 1 == gracz.cords[1] && map2[j - 1][i] == '#' && map2[j][i - 1] != '#' && j != size - 1) || (gracz.cords[1] == i - 2 && gracz.cords[0] == j && mobMap2[j][i - 1] != '0' && map2[j][i - 1] == '#')) {
					if (mobMap2[j][i] < '5' && aniCyrculation % 2 == 0) mobMap2[j][i]++;
				}
				
				else {
					if (mobMap2[j][i] > '0' && aniCyrculation % 2 == 0) mobMap2[j][i]--;
				}
			} 
				
	
	
	
			// -----===== Drawing all The Map 0 =====-----
			
			if (map0[j][i] == '#' && topMap != 2) {
				block.setPosition(j * 120, (i + 3) * 120);
				wallBottom.setPosition(j * 120, (i + 3) * 120);
				
				// drawing under te wall
				if (mobMap1[j][i] != '0')
					okno.draw(wallBottom);
				
				// setting transparency
				if (0 < j) {
					block.setColor(Color (255, 255, 255, 255 - (28 * ((int)mobMap1[j][i] - (int)'0'))));
					celling.setColor(Color (255, 255, 255, 255 - (28 * ((int)mobMap1[j][i] - (int)'0'))));
				}
					
				
				// the actual wall drawing
				if (((map0[j][i + 1] != '#' && (map1[j][i + 1] != '#' || topMap == 0)) || i == yEnd) && xStart < j) {
					
					for (int i = 0; i < 8; i++)
						wallChoose[i] = false;
					
					// checking neighbouring walls
					if (map0[j - 1][i] == '#') wallChoose[0] = true;
					if (map0[j - 1][i + 1] == '#') wallChoose[1] = true;
					if (map0[j + 1][i] == '#') wallChoose[2] = true;
					
					if (map1[j - 1][i] == '#') wallChoose[4] = true;
					if (map1[j - 1][i + 1] == '#') wallChoose[5] = true;
					if (map1[j + 1][i] == '#') wallChoose[6] = true;
					
					// picking the propper wall
					if (i >= yEnd) 
						block.setTextureRect(IntRect(120, 0, 30, 60));
					else if (((wallChoose[0] || (topMap == 1 && wallChoose[4])) && !(wallChoose[1] || (topMap == 1 && wallChoose[5]))) && ((wallChoose[2] || (topMap == 1 && wallChoose[6])) && !(map0[j + 1][i + 1] == '#' || (topMap == 1 && (map1[j + 1][i + 1] == '#')))))
						block.setTextureRect(IntRect(0, 0, 30, 60));
					else if (((wallChoose[0] || (topMap == 1 && wallChoose[4])) && !(wallChoose[1] || (topMap == 1 && wallChoose[5]))) && (!(wallChoose[2] || (topMap == 1 && wallChoose[6])) || (map0[j + 1][i + 1] == '#' || (topMap == 1 && (map1[j + 1][i + 1] == '#')))))
						block.setTextureRect(IntRect(30, 0, 30, 60));
					else if ((!(wallChoose[0] || (topMap == 1 && wallChoose[4])) || (wallChoose[1] || (topMap == 1 && wallChoose[5]))) && ((wallChoose[2] || (topMap == 1 && wallChoose[6])) && !(map0[j + 1][i + 1] == '#' || (topMap == 1 && (map1[j + 1][i + 1] == '#')))))
						block.setTextureRect(IntRect(60, 0, 30, 60));
					else if ((!(wallChoose[0] || (topMap == 1 && wallChoose[4])) || (wallChoose[1] || (topMap == 1 && wallChoose[5]))) && (!(wallChoose[2] || (topMap == 1 && wallChoose[6])) || (map0[j + 1][i + 1] == '#' || (topMap == 1 && (map1[j + 1][i + 1] == '#')))))
						block.setTextureRect(IntRect(90, 0, 30, 60));
						
					
					okno.draw(block);
				}
				
				else if (map0[j][i + 1] != '#' && j == xStart) {
					
					for (int i = 0; i < 8; i++)
						wallChoose[i] = false;
					
					if (map0[j + 1][i] == '#') wallChoose[2] = true;
					
					if (map1[j + 1][i] == '#') wallChoose[6] = true;
					
					// picking propper wall (but if j == 0 then j - 1 breaks the map0)
					if (i >= yEnd)
						block.setTextureRect(IntRect(120, 0, 30, 60));
					else if ((wallChoose[2] || (topMap == 1 && wallChoose[6])) && !(map0[j + 1][i + 1] == '#' || (topMap == 1 && (map1[j + 1][i + 1] == '#'))))
						block.setTextureRect(IntRect(60, 0, 30, 60));
					else if (!(wallChoose[2] || (topMap == 1 && wallChoose[6])) || (map0[j + 1][i + 1] == '#' || (topMap == 1 && (map1[j + 1][i + 1] == '#'))))
						block.setTextureRect(IntRect(90, 0, 30, 60));
					
					okno.draw(block);
				}
				
				
				
				// the whole drawing - celling thing .. idk I just hate school to much
				
				block.setTextureRect(IntRect(120, 0, 30, 30));
				block.move(0, -120);
				okno.draw(block);
				
				for (int k = 0; k < 8; k++) {
					cellDraw[k] = false;
				}
				
				
				// setting to true if variables don't cross the map "walls" (would mess up the whole memory)
				
				// (walls)
				if (i > yStart) {
					if (!(map0[j][i - 1] == '#' || (topMap == 1 && map1[j][i - 1] == '#'))) {
						cellDraw[1] = true;
						cellDraw[0] = true;
						cellDraw[2] = true;
					}
				}
				
				if (i < yEnd) {
					if (!(map0[j][i + 1] == '#' || (topMap == 1 && map1[j][i + 1] == '#'))) {
						cellDraw[6] = true;
						cellDraw[5] = true;
						cellDraw[7] = true;
					}
				}
				
				if (j > xStart) {
					if (!(map0[j - 1][i] == '#' || (topMap == 1 && map1[j - 1][i] == '#'))) {
						cellDraw[0] = true;
						cellDraw[3] = true;
						cellDraw[5] = true;
					}
				}
				
				if (j < xEnd) {
					if (!(map0[j + 1][i] == '#' || (topMap == 1 && map1[j + 1][i] == '#'))) {
						cellDraw[2] = true;
						cellDraw[4] = true;
						cellDraw[7] = true;
					}
				}
				
				// (corners)
				if (j > xStart && i > yStart) {
					if (!(map0[j - 1][i - 1] == '#' || (topMap == 1 && map1[j - 1][i - 1] == '#')))
						cellDraw[0] = true;
				} 
				
				if (j < xEnd && i > yStart) {
					if (!(map0[j + 1][i - 1] == '#' || (topMap == 1 && map1[j + 1][i - 1] == '#')))
						cellDraw[2] = true;
				}
				
				if (j > xStart && i < yEnd) {
					if (!(map0[j - 1][i + 1] == '#' || (topMap == 1 && map1[j - 1][i + 1] == '#')))
						cellDraw[5] = true;
				}
				
				if (j < xEnd && i < yEnd) {
					if (!(map0[j + 1][i + 1] == '#' || (topMap == 1 && map1[j + 1][i + 1] == '#')))
						cellDraw[7] = true;
				}
				
				
				// the actual drawing
				if (cellDraw[0]) {
					celling.setTextureRect(IntRect(12, 12, 7, 7));
					celling.setPosition(j * 120, (i + 3) * 120 - 284);
					okno.draw(celling);
				}
				
				if (cellDraw[2]) {
					celling.setTextureRect(IntRect(19, 12, 7, 7));
					celling.setPosition(j * 120 + 92, (i + 3) * 120 - 284);
					okno.draw(celling);
				}
				
				if (cellDraw[5]) {
					celling.setTextureRect(IntRect(30, 5, 7, 7));
					celling.setPosition(j * 120, (i + 3) * 120 - 192);
					okno.draw(celling);
				}
				
				if (cellDraw[7]) {
					celling.setTextureRect(IntRect(26, 12, 7, 7));
					celling.setPosition(j * 120 + 92, (i + 3) * 120 - 192);
					okno.draw(celling);
				}
				
				
				if (cellDraw[1]) {
					celling.setTextureRect(IntRect(12, 0, 18, 6));
					celling.setPosition(j * 120 + 24, (i + 3) * 120 - 284);
					okno.draw(celling);
				}
				
				if (cellDraw[6]) {
					celling.setTextureRect(IntRect(12, 6, 18, 6));
					celling.setPosition(j * 120 + 24, (i + 3) * 120 - 188);
					okno.draw(celling);
				}
				
				if (cellDraw[3]) {
					celling.setTextureRect(IntRect(0, 0, 6, 18));
					celling.setPosition(j * 120, (i + 3) * 120 - 260);
					okno.draw(celling);
				}
				
				if (cellDraw[4]) {
					celling.setTextureRect(IntRect(6, 0, 6, 18));
					celling.setPosition(j * 120 + 96, (i + 3) * 120 - 260);
					okno.draw(celling);
				} 
			}
			
			
			// ---=== drawing entrance ===---
			if (map0[j][i] == 'D') {
				door.setPosition(j * 120, (i + 3) * 120);
				
				if (topMap == 2) 
					frameChoose[1] = 1;
				else
					frameChoose[1] = 0;
				
				if (i == yStart) 
					frameChoose[0] = 0;
				if (j == xEnd) 
					frameChoose[0] = 3;
				if (i == yEnd)
					frameChoose[0] = 2;				
				if (j == xStart) 
					frameChoose[0] = 1;
				
				door.setTextureRect(IntRect((frameChoose[0]) * 30, (frameChoose[1]) * 90, 30, 90));
				door.move (0, 360);
				okno.draw(door);
			} 
			
			
			// ---=== drawing exitt ===---
			if (map0[j][i] == 'd') {
				exitt.setPosition(j * 120, (i + 3) * 120);
				
				if (topMap == 2) 
					frameChoose[1] = 1;
				else
					frameChoose[1] = 0;
				
				if (i == yStart) 
					frameChoose[0] = 0;
				if (j == xEnd) 
					frameChoose[0] = 3;
				if (i == yEnd) 
					frameChoose[0] = 2;				
				if (j == xStart) 
					frameChoose[0] = 1;
				
				exitt.setTextureRect(IntRect((frameChoose[0]) * 30, (frameChoose[1]) * 90, 30, 90));
				exitt.move (0, 360);
				okno.draw(exitt);
			}
			
			
			
			
			// -----===== Drawing all The Map 1 =====-----
			
			if (map1[j][i] == '#' && topMap != 2) {
				block.setPosition(j * 120, (i + 3) * 120 + map1Push);
				wallBottom.setPosition(j * 120, (i + 3) * 120 + map1Push);
				
				// drawing under te wall
				if (mobMap1[j][i] != '0')
					okno.draw(wallBottom);
				
				// setting transparency
				if (0 < j) {
					block.setColor(Color (255, 255, 255, 255 - (28 * ((int)mobMap1[j][i] - (int)'0'))));
					celling.setColor(Color (255, 255, 255, 255 - (28 * ((int)mobMap1[j][i] - (int)'0'))));
				}
					
				
				// the actual wall drawing
				if (((map0[j][i + 1] != '#' && map1[j][i + 1] != '#') || i == yEnd) && xStart < j) {
					
					for (int i = 0; i < 8; i++)
						wallChoose[i] = false;
					
					// checking neighbouring walls
					if (map1[j - 1][i] == '#') wallChoose[0] = true;
					if (map1[j - 1][i + 1] == '#') wallChoose[1] = true;
					if (map1[j + 1][i] == '#') wallChoose[2] = true;
					
					if (map0[j - 1][i] == '#') wallChoose[4] = true;
					if (map0[j - 1][i + 1] == '#') wallChoose[5] = true;
					if (map0[j + 1][i] == '#') wallChoose[6] = true;
					
					// picking the propper wall
					if (i >= yEnd)
						block.setTextureRect(IntRect(120, 0, 30, 60));
					else if (((wallChoose[0] || (topMap == 1 && wallChoose[4])) && !(wallChoose[1] || (topMap == 1 && wallChoose[5]))) && ((wallChoose[2] || (topMap == 1 && wallChoose[6])) && !(map1[j + 1][i + 1] == '#' || (topMap == 1 && (map0[j + 1][i + 1] == '#')))))
						block.setTextureRect(IntRect(0, 0, 30, 60));
					else if (((wallChoose[0] || (topMap == 1 && wallChoose[4])) && !(wallChoose[1] || (topMap == 1 && wallChoose[5]))) && (!(wallChoose[2] || (topMap == 1 && wallChoose[6])) || (map1[j + 1][i + 1] == '#' || (topMap == 1 && (map0[j + 1][i + 1] == '#')))))
						block.setTextureRect(IntRect(30, 0, 30, 60));
					else if ((!(wallChoose[0] || (topMap == 1 && wallChoose[4])) || (wallChoose[1] || (topMap == 1 && wallChoose[5]))) && ((wallChoose[2] || (topMap == 1 && wallChoose[6])) && !(map1[j + 1][i + 1] == '#' || (topMap == 1 && (map0[j + 1][i + 1] == '#')))))
						block.setTextureRect(IntRect(60, 0, 30, 60));
					else if ((!(wallChoose[0] || (topMap == 1 && wallChoose[4])) || (wallChoose[1] || (topMap == 1 && wallChoose[5]))) && (!(wallChoose[2] || (topMap == 1 && wallChoose[6])) || (map1[j + 1][i + 1] == '#' || (topMap == 1 && (map0[j + 1][i + 1] == '#')))))
						block.setTextureRect(IntRect(90, 0, 30, 60));
						
					
					okno.draw(block);
				}
				
				else if (map1[j][i + 1] != '#' && j == xStart) {
					
					for (int i = 0; i < 8; i++)
						wallChoose[i] = false;
					
					if (map1[j + 1][i] == '#') wallChoose[2] = true;
					
					if (map0[j + 1][i] == '#') wallChoose[6] = true;
					
					// picking propper wall (but if j == 0 then j - 1 breaks the map0)
					if (i == yEnd)
						block.setTextureRect(IntRect(120, 0, 30, 60));
					else if ((wallChoose[2] || (topMap == 1 && wallChoose[6])) && !(map1[j + 1][i + 1] == '#' || (topMap == 1 && (map0[j + 1][i + 1] == '#'))))
						block.setTextureRect(IntRect(60, 0, 30, 60));
					else if (!(wallChoose[2] || (topMap == 1 && wallChoose[6])) || (map1[j + 1][i + 1] == '#' || (topMap == 1 && (map0[j + 1][i + 1] == '#'))))
						block.setTextureRect(IntRect(90, 0, 30, 60));
					
					okno.draw(block);
				}
				
				
				
				// the whole drawing - celling thing .. idk I just hate school to much (yeah lol the code is coppied for both drawings (it is actually a bit changed))
				
				if (!(map1Push > 239 && (map0[j][i] == '.' || map0[j][i] == '-'))) {
					block.setTextureRect(IntRect(120, 0, 30, 30));
					block.move(0, -120);
					okno.draw(block);
					
					for (int k = 0; k < 8; k++) {
						cellDraw[k] = false;
					}
					
					
					// setting to true if variables don't cross the map "walls" (would mess up the whole memory)
					
					// (walls)
					if (i > yStart) {
						if (!(map1[j][i - 1] == '#' || (topMap == 1 && map0[j][i - 1] == '#'))) {
							cellDraw[1] = true;
							cellDraw[0] = true;
							cellDraw[2] = true;
						}
					}
					
					if (i < yEnd) {
						if (!(map1[j][i + 1] == '#' || (topMap == 1 && map0[j][i + 1] == '#'))) {
							cellDraw[6] = true;
							cellDraw[5] = true;
							cellDraw[7] = true;
						}
					}
					
					if (j > xStart) {
						if (!(map1[j - 1][i] == '#' || (topMap == 1 && map0[j - 1][i] == '#'))) {
							cellDraw[0] = true;
							cellDraw[3] = true;
							cellDraw[5] = true;
						}
					}
					
					if (j < xEnd) {
						if (!(map1[j + 1][i] == '#' || (topMap == 1 && map0[j + 1][i] == '#'))) {
							cellDraw[2] = true;
							cellDraw[4] = true;
							cellDraw[7] = true;
						}
					}
					
					// (corners)
					if (j > xStart && i > yStart) {
						if (!(map1[j - 1][i - 1] == '#' || (topMap == 1 && map0[j - 1][i - 1] == '#')))
							cellDraw[0] = true;
					} 
					
					if (j < xEnd && i > yStart) {
						if (!(map1[j + 1][i - 1] == '#' || (topMap == 1 && map0[j + 1][i - 1] == '#')))
							cellDraw[2] = true;
					}
					
					if (j > xStart && i < yEnd) {
						if (!(map1[j - 1][i + 1] == '#' || (topMap == 1 && map0[j - 1][i + 1] == '#')))
							cellDraw[5] = true;
					}
					
					if (j < xEnd && i < yEnd) {
						if (!(map1[j + 1][i + 1] == '#' || (topMap == 1 && map0[j + 1][i + 1] == '#')))
							cellDraw[7] = true;
					}
					
					
					// the actual drawing
					if (cellDraw[0]) {
						celling.setTextureRect(IntRect(12, 12, 7, 7));
						celling.setPosition(j * 120, (i + 3) * 120 - 284 + map1Push);
						okno.draw(celling);
					}
					
					if (cellDraw[2]) {
						celling.setTextureRect(IntRect(19, 12, 7, 7));
						celling.setPosition(j * 120 + 92, (i + 3) * 120 - 284 + map1Push);
						okno.draw(celling);
					}
					
					if (cellDraw[5]) {
						celling.setTextureRect(IntRect(30, 5, 7, 7));
						celling.setPosition(j * 120, (i + 3) * 120 - 192 + map1Push);
						okno.draw(celling);
					}
					
					if (cellDraw[7]) {
						celling.setTextureRect(IntRect(26, 12, 7, 7));
						celling.setPosition(j * 120 + 92, (i + 3) * 120 - 192 + map1Push);
						okno.draw(celling);
					}
					
					
					if (cellDraw[1]) {
						celling.setTextureRect(IntRect(12, 0, 18, 6));
						celling.setPosition(j * 120 + 24, (i + 3) * 120 - 284 + map1Push);
						okno.draw(celling);
					}
					
					if (cellDraw[6]) {
						celling.setTextureRect(IntRect(12, 6, 18, 6));
						celling.setPosition(j * 120 + 24, (i + 3) * 120 - 188 + map1Push);
						okno.draw(celling);
					}
					
					if (cellDraw[3]) {
						celling.setTextureRect(IntRect(0, 0, 6, 18));
						celling.setPosition(j * 120, (i + 3) * 120 - 260 + map1Push);
						okno.draw(celling);
					}
					
					if (cellDraw[4]) {
						celling.setTextureRect(IntRect(6, 0, 6, 18));
						celling.setPosition(j * 120 + 96, (i + 3) * 120 - 260 + map1Push);
						okno.draw(celling);
					}
				}				
			}
		
		
			// drawing the 'o' station
			if (map1[j][i] == 'o' && topMap != 2) {
				station.setPosition(j * 120, (i + 3) * 120 + map1Push);
				okno.draw(station);
			}
			
			
			
			// ----=== drawing map 2 =====----
			
			if (topMap != 1 && !(topMap == 0 && i == yEnd)) {
				if (map2[j][i] == '#') {
					blockDark.setPosition(j * 120, (i + 6) * 120 - map1Push);
					wallBottomDark.setPosition(j * 120, (i + 6) * 120 - map1Push);
					
					// drawing under te wall
					if (mobMap2[j][i] != '0')
						okno.draw(wallBottomDark);
					
					// setting transparency
					if (0 < j) {
						blockDark.setColor(Color (255, 255, 255, 255 - (28 * ((int)mobMap2[j][i] - (int)'0'))));
						cellingDark.setColor(Color (255, 255, 255, 255 - (28 * ((int)mobMap2[j][i] - (int)'0'))));
					}
						
					
					// the actual wall drawing
					if (!(map2[j][i + 1] == '#' && mobMap1[j][i + 1] == '0' && mobMap2[j][i + 1] == '0') || i == yEnd) {
						
						for (int i = 0; i < 8; i++)
							wallChoose[i] = false;
						
						// checking neighbouring walls
						if (map2[j - 1][i] == '#') wallChoose[0] = true;
						if (map2[j - 1][i + 1] == '#') wallChoose[1] = true;
						if (map2[j + 1][i] == '#') wallChoose[2] = true;
						
						// picking the propper wall
						if (i >= yEnd)
							blockDark.setTextureRect(IntRect(120, 0, 30, 60));
						else if ((map2[j - 1][i] == '#' && map2[j - 1][i + 1] != '#') && (wallChoose[2] && map2[j + 1][i + 1] != '#'))
							blockDark.setTextureRect(IntRect(0, 0, 30, 60));
						else if ((map2[j - 1][i] == '#' && map2[j - 1][i + 1] != '#') && (!wallChoose[2] || (map2[j + 1][i + 1] == '#')))
							blockDark.setTextureRect(IntRect(30, 0, 30, 60));
						else if ((map2[j - 1][i] != '#' || map2[j - 1][i + 1] == '#') && (wallChoose[2] && map2[j + 1][i + 1] != '#'))
							blockDark.setTextureRect(IntRect(60, 0, 30, 60));
						else if ((map2[j - 1][i] != '#' || map2[j - 1][i + 1] == '#') && (!wallChoose[2] || (map2[j + 1][i + 1] == '#')))
							blockDark.setTextureRect(IntRect(90, 0, 30, 60));
							
						
						okno.draw(blockDark);
					}
					
					else if (map2[j][i + 1] != '#' && j == xStart) {
						
						for (int i = 0; i < 8; i++)
							wallChoose[i] = false;
						
						if (map2[j + 1][i] == '#') wallChoose[2] = true;
						
						// picking propper wall (but if j == 0 then j - 1 breaks the map2)
						if (i == yEnd)
							blockDark.setTextureRect(IntRect(120, 0, 30, 60));
						else if (wallChoose[2] && !(map2[j + 1][i + 1] == '#'))
							blockDark.setTextureRect(IntRect(60, 0, 30, 60));
						else if (!wallChoose[2] || map2[j + 1][i + 1] == '#')
							blockDark.setTextureRect(IntRect(90, 0, 30, 60));
						
						okno.draw(blockDark);
					}
					
					
					
					// the whole drawing - celling thing .. idk I just hate school to much (yeah lol the code is coppied for both drawings (it is actually a bit changed))
					
					if (!(topMap != 2 && map0[j][i] == '#') && map1Push > 120) {
						blockDark.setTextureRect(IntRect(120, 0, 30, 30));
						blockDark.move(0, -120);
						okno.draw(blockDark);
						
						for (int k = 0; k < 8; k++) {
							cellDraw[k] = false;
						}
						
						
						// setting to true if variables don't cross the map "walls" (would mess up the whole memory)
						
						// (walls)
						if (i > yStart) {
							if (map2[j][i - 1] != '#') {
								cellDraw[1] = true;
								cellDraw[0] = true;
								cellDraw[2] = true;
							}
						}
						
						if (i < yEnd) {
							if (map2[j][i + 1] != '#') {
								cellDraw[6] = true;
								cellDraw[5] = true;
								cellDraw[7] = true;
							}
						}
						
						if (j > xStart) {
							if (map2[j - 1][i] != '#') {
								cellDraw[0] = true;
								cellDraw[3] = true;
								cellDraw[5] = true;
							}
						}
						
						if (j < xEnd) {
							if (map2[j + 1][i] != '#') {
								cellDraw[2] = true;
								cellDraw[4] = true;
								cellDraw[7] = true;
							}
						}
						
						// (corners)
						if (j > xStart && i > yStart) {
							if (map2[j - 1][i - 1] != '#')
								cellDraw[0] = true;
						} 
						
						if (j < xEnd && i > yStart) {
							if (map2[j + 1][i - 1] != '#')
								cellDraw[2] = true;
						}
						
						if (j > xStart && i < yEnd) {
							if (map2[j - 1][i + 1] != '#')
								cellDraw[5] = true;
						}
						
						if (j < xEnd && i < yEnd) {
							if (map2[j + 1][i + 1] != '#')
								cellDraw[7] = true;
						}
						
						
						// the actual drawing
						if (cellDraw[0]) {
							cellingDark.setTextureRect(IntRect(12, 12, 7, 7));
							cellingDark.setPosition(j * 120, (i + 6) * 120 - 284 - map1Push);
							okno.draw(cellingDark);
						}
						
						if (cellDraw[2]) {
							cellingDark.setTextureRect(IntRect(19, 12, 7, 7));
							cellingDark.setPosition(j * 120 + 92, (i + 6) * 120 - 284 - map1Push);
							okno.draw(cellingDark);
						}
						
						if (cellDraw[5]) {
							cellingDark.setTextureRect(IntRect(30, 5, 7, 7));
							cellingDark.setPosition(j * 120, (i + 6) * 120 - 192 - map1Push);
							okno.draw(cellingDark);
						}
						
						if (cellDraw[7]) {
							cellingDark.setTextureRect(IntRect(26, 12, 7, 7));
							cellingDark.setPosition(j * 120 + 92, (i + 6) * 120 - 192 - map1Push);
							okno.draw(cellingDark);
						}
						
						
						if (cellDraw[1]) {
							cellingDark.setTextureRect(IntRect(12, 0, 18, 6));
							cellingDark.setPosition(j * 120 + 24, (i + 6) * 120 - 284 - map1Push);
							okno.draw(cellingDark);
						}
						
						if (cellDraw[6]) {
							cellingDark.setTextureRect(IntRect(12, 6, 18, 6));
							cellingDark.setPosition(j * 120 + 24, (i + 6) * 120 - 188 - map1Push);
							okno.draw(cellingDark);
						}
						
						if (cellDraw[3]) {
							cellingDark.setTextureRect(IntRect(0, 0, 6, 18));
							cellingDark.setPosition(j * 120, (i + 6) * 120 - 260 - map1Push);
							okno.draw(cellingDark);
						}
						
						if (cellDraw[4]) {
							cellingDark.setTextureRect(IntRect(6, 0, 6, 18));
							cellingDark.setPosition(j * 120 + 96, (i + 6) * 120 - 260 - map1Push);
							okno.draw(cellingDark);
						}
					}				
				}
				
				if (map2[j][i] == 'o' ) {
					stationDark.setPosition(j * 120, (i + 6) * 120 - map1Push);
					okno.draw(stationDark);
				}
			}
		}
		
		
		// ---=== draw the player ===---
		if (gracz.cords[1] == i && gracz.cords[0] >= 0 && gracz.cords[0] < xEnd && gracz.cords[1] < yEnd)
			gracz.drawAll();
		
		if (gracz.ashCords[1] == i && gracz.ashCords[0] >= 0 && gracz.ashCords[0] < xEnd && gracz.ashCords[1] < yEnd)
			gracz.drawAsh();
	}
	
	
	// --== Adding black wall to cover moving maps on the bottom ==--
	block.setTextureRect(IntRect(120, 0, 30, 60));
	
	for (int i = yEnd + 2; i < yEnd + 4; i++) {
		for (int j = xStart; j < xEnd + 1; j++) {
			block.setPosition(j * 120, (i + 3) * 120);
			okno.draw(block);
		}
	}
	
	
	// drawing the celling over the entrance
	if (topMap == 2) 
		frameChoose[0] = 1;
	else
		frameChoose[0] = 0;
	
	cellWide.setTextureRect(IntRect(107 * frameChoose[0], 0, 107, 107));
	if (topMap == 1)
		cellHig.setTexture(topHig1);
	else
		cellHig.setTexture(topHig2);
	cellHig.setScale(sf::Vector2f(18, 18));
	cellHig.setOrigin(0, cellHig.getLocalBounds().height);
	
	
	if (bigCellDraw == 1) {
		if (aniCyrculation == 0)
			topPush = 0;	
		
		cellWide.setPosition(view.getCenter().x - (okno.getSize().x / 2), view.getCenter().y - (okno.getSize().y / 2) + topPush);
		topPush += 96;
	}
	
	else if (bigCellDraw == 2) {
		if (aniCyrculation == 0)
			topPush = 0;	
		
		cellHig.setPosition(view.getCenter().x + (okno.getSize().x / 2) - topPush, view.getCenter().y + (okno.getSize().y / 2));
		topPush += 96;
	}
	
	else if (bigCellDraw == 3) {
		if (aniCyrculation == 0)
			topPush = 0;	
		
		cellWide.setPosition(view.getCenter().x - (okno.getSize().x / 2), view.getCenter().y + (okno.getSize().y / 2) + 1920 - topPush);
		topPush += 96;
	}
	
	else if (bigCellDraw == 4) {
		if (aniCyrculation == 0)
			topPush = 0;	
		
		cellHig.setPosition(view.getCenter().x - ((okno.getSize().x / 2) * 3) + topPush, view.getCenter().y + (okno.getSize().y / 2));
		topPush += 96;
	}
	
	
	if (bigCellDraw == 1 || bigCellDraw == 3) 
		okno.draw(cellWide);
	
	if (bigCellDraw == 2 || bigCellDraw == 4) 
		okno.draw(cellHig);
}

void partyMode () {
	static RectangleShape lights (Vector2f (okno.getSize().x, okno.getSize().y));
	static int colours[3], status = 0;
	
	if (aniCyrculation % 12 == 0) status++;
	status %= 6;
	
	
	// changing colours
	if (status == 0) {
		colours[0] = 255;
		colours[1] = 0;
		colours[2] = 0;
	}
	
	else if (status == 1) {
		colours[0] = 128;
		colours[1] = 128;
	}
	
	else if (status == 2) {
		colours[0] = 0;
		colours[1] = 255;
	}
	
	else if (status == 3) {
		colours[1] = 128;
		colours[2] = 128;
	}
	
	else if (status == 4) {
		colours[1] = 0;
		colours[2] = 255;
	}
	
	else if (status == 5) {
		colours[2] = 128;
		colours[0] = 128;
	}
	
	
	lights.setFillColor (Color (colours[0], colours[1], colours[2], 96));
	lights.setPosition (view.getCenter().x - (okno.getSize().x / 2), view.getCenter().y - (okno.getSize().y / 2));
	
	okno.draw (lights);
}


