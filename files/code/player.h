#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;

extern RenderWindow okno;
extern View view;
extern char map0[][50], map1[][50], map2[][50], mobMap1[][50], mobMap2[][50];
extern int mapSize, map1Push, topMap;

class player {
	public:
		// constructor, modecheck & collision
		player ();
		void posModeCheck ();
		void collision ();
		
		// character action functions
		void posMove ();
		void posDash ();
		void posJump ();
		
		// other functions
		void setPosition (int x, int y);
		void cordControll ();
		void posShadow ();
		void drawAll ();
		void drawAsh ();
		
		// return functions
		sf::Vector2f getPosition();
		string getPosMode ();
		
		
		// public varribles
		int cords[2], ashCords[2];    // player coordinates
		char lastDir = 'd', lastMap = '1';
		
		
	private:
		int posAni = 0, posFrame[2] = {0, 0}, speed = 0;    // varrible for frames in animation
		int isBored = 0;    // counts, after what time character becomes bored
		bool sprint = false, stop = false, attackButton = false, hideButton = false, dashButton = false, collide[4] = {false, false, false, false};
		string posMode = "move";      //  {sat, stand, sit, move, jump, protect, attack, dash, hide}
		Sprite pos, ash, pocket, sword;
		Texture skin, air, pocketTxt, swordTxt;
};

#endif

// here you go 
// a free scale to set your zoom while coding 


// / \
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
//  |
// \ /

// this height should match your work space width
