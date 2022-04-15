#ifndef TORCH_H
#define TORCH_H

#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;
using namespace std;

class torch {
	public:
		
		// constructor
		torch (int posX, int posY, int posAni, int ligRad);
		
		// draw torch, torch radius and controll torch
		void draw ();
		
		
		
		// varribles
		int pos[2];
		int posAnimation, lightRadius;
	
	private:
		CircleShape Light;
		Sprite torchS;
		Texture torchTexture;
};

#endif
