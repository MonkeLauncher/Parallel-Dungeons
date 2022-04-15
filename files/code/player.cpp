
// na koncu kazdej funkcji chwilowej dac zmiana posMode na move jesli skonczyla sie sekwencja animacji
// wyjatkiem jest funkcja sit, ktora zmienia posMode na sat


#include "player.h"

using namespace std;
using namespace sf;

player::player () {
	pos.setPosition (okno.getSize().x / 2 - 30, okno.getSize().y / 2 + 60);
	posMode = "move";
	posAni = 0;

	skin.loadFromFile("obrazy/postac/skin1_move.png");
	pos.setTexture(skin);
	pos.setScale(sf::Vector2f(5, 5));
	pos.setOrigin(0, pos.getLocalBounds().height);
	
	pocketTxt.loadFromFile("obrazy/postac/pocket_move.png");
	pocket.setTexture(pocketTxt);
	pocket.setScale(sf::Vector2f(5, 5));
	pocket.setOrigin(0, pocket.getLocalBounds().height);
	
	ash.setOrigin(0, ash.getLocalBounds().height);
	ash.setPosition(pos.getPosition());
}

void player::posModeCheck () {

	// statement for falling (can't do it right now because of no map)

	// for standing up
	if ((posMode == "sat" && Keyboard::isKeyPressed(Keyboard::Q)) || posMode == "stand") {
		if (posMode == "sat")
			posAni = 0;
		posMode = "stand";
		isBored = 0;
	}

	// for sitting
	else if ((Keyboard::isKeyPressed(Keyboard::Q) && posMode == "move") || posMode == "sit" || isBored >= 18000) {
		if (posMode != "sit")
			posAni = 0;
		posMode = "sit";
		isBored = 0;
	}

	// for being sitting
	else if (posMode == "sat") {
		isBored = 0;
	}

	// for dimensional jumping
	else if ((Keyboard::isKeyPressed(Keyboard::Space) && posMode == "move" && map0[cords[0]][cords[1]] == '-') || posMode == "jump") {
		if (posMode != "jump") {
			posAni = 0;
			if (topMap == 1) lastMap = '1';
			else if (topMap == 2) lastMap = '2';
			
			skin.loadFromFile("obrazy/postac/skin1_jump.png");
			pos.setTexture(skin);
			pos.setScale(sf::Vector2f(5, 5));
			pos.setOrigin(0, pos.getLocalBounds().height);
		}
		
		posMode = "jump";
		isBored = 0;
	}

	// for defense
	else if (Mouse::isButtonPressed(Mouse::Right)) {
		posMode = "protect";
		isBored = 0;
	}

	// for attack
	else if ((Mouse::isButtonPressed(Mouse::Left) && !attackButton && posMode == "move") || posMode == "attack") {
		if (posMode != "attack")
			posAni = 0;
		posMode = "attack";
		isBored = 0;
	}

	// for dash
	else if ((Keyboard::isKeyPressed(Keyboard::LShift)  && !dashButton && posMode == "move") || posMode == "dash") {
		if (posMode != "dash") {
			posAni = 0;
			speed = 4;
			
			skin.loadFromFile("obrazy/postac/skin1_dash.png");
			pos.setTexture(skin);
			pos.setScale(sf::Vector2f(5, 5));
			pos.setOrigin(0, pos.getLocalBounds().height);
			
			ash.setPosition(pos.getPosition());
			
		}

		posMode = "dash";
		isBored = 0;
	}

	// hiding and pulling sword out of the pocket
	else if ((Keyboard::isKeyPressed(Keyboard::X)  && !hideButton && posMode == "move") || posMode == "hide") {
		if (posMode != "hide")
			posAni = 0;
		posMode = "hide";
		isBored = 0;
	}

	// for movement
	else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::W) || posMode == "move") {
		if (posAni == 0 || posMode != "move" || stop) {
			
			skin.loadFromFile("obrazy/postac/skin1_move.png");
			pos.setTexture(skin);
			pos.setScale(sf::Vector2f(5, 5));
			pos.setOrigin(0, pos.getLocalBounds().height);
			
			pocketTxt.loadFromFile("obrazy/postac/pocket_move.png");
			pocket.setTexture(pocketTxt);
			pocket.setScale(sf::Vector2f(5, 5));
			pocket.setOrigin(0, pocket.getLocalBounds().height);

			posAni = 0;
		}
		posMode = "move";
		isBored = 0;
	}

	// if nothing is going on
	else {
		isBored++;
		posMode = "move";
	}


	// checking if some buttons are already pressed -> to pretend stacking dash or attack sequences
	if (Mouse::isButtonPressed(Mouse::Left))
		attackButton = true;
	else
		attackButton = false;

	if (Keyboard::isKeyPressed(Keyboard::X))
		hideButton = true;
	else
		hideButton = false;


	if (Keyboard::isKeyPressed(Keyboard::LShift))
		dashButton = true;
	else
		dashButton = false;
}

void player::posMove () {
	int a = 0;
	
	stop = false;
	
	if (Keyboard::isKeyPressed(Keyboard::LControl)) {
		sprint = true;
		speed = 6;
	}

	else {
		sprint = false;
		speed = 4;
	}
	
	// diagonal speed reduction
	if (Keyboard::isKeyPressed(Keyboard::W)) a++;
	if (Keyboard::isKeyPressed(Keyboard::D)) a++;
	if (Keyboard::isKeyPressed(Keyboard::S)) a++;
	if (Keyboard::isKeyPressed(Keyboard::A)) a++;
	
	if (a > 1) speed--;


	// --== movement ==--
	
	
	// if two buttons are pressed
	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::D) && (!Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::W)))
		stop = true;

	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::S))
		stop = true;
	
	
	// if one button is pressed
	if (!stop) {
		if (Keyboard::isKeyPressed(Keyboard::S)) {
	    	lastDir = 's';
	
	    	if (!collide[2]) pos.move (0, speed);
	    	else if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
	    		stop = true;
	    }
	
	    if (Keyboard::isKeyPressed(Keyboard::W)) {
	        lastDir = 'w';
	
	        if (!collide[0]) pos.move (0, -speed);
	        else if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
	        	stop = true;
	    }
	
	    if (Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A)) {
	    	lastDir = 'd';
	
	        if (!collide[1]) pos.move (speed, 0);
	        else if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S))
	        	stop = true;
	        else {
	        	if (Keyboard::isKeyPressed(Keyboard::W))
	        		lastDir = 'w';
	        	else if (Keyboard::isKeyPressed(Keyboard::S))
	        		lastDir = 's';
			}
	    }
	
	    if (Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D)) {
	        lastDir = 'a';
	
	        if (!collide[3]) pos.move (-speed, 0);
	        else if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S))
	        	stop = true;
	        else {
	        	if (Keyboard::isKeyPressed(Keyboard::W))
	        		lastDir = 'w';
	        	else if (Keyboard::isKeyPressed(Keyboard::S))
	        		lastDir = 's';
			}
	    }
	}
    
    
    // if three buttons are pressed
	if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) {
		lastDir = 'w';

        if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D) && collide[0])
        	stop = true;
    }

	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D)) {
		lastDir = 's';

    	if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D) && collide[2])
    		stop = true;
    }
	    
    
    
    // if four buttons are pressed / stop is set to true
    if ((!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::S) && !Keyboard::isKeyPressed(Keyboard::W)) || stop) {
	    posAni = 60;
	    stop = true;
	}
    
	
	
	// ----==== animations ====----
	if (lastDir == 'w')
		posFrame[1] = 2;

	else if (lastDir == 's')
		posFrame[1] = 3;

	else if (lastDir == 'a')
		posFrame[1] = 1;

	else if (lastDir == 'd')
		posFrame[1] = 0;
		
	posFrame[0] = posAni / 10;
		
	if (sprint && !stop) posFrame[1] += 4;

	else {
		if (posFrame[0] < 3) posFrame[0]++;
		if ((20 <= posAni && posAni <= 29) || posAni >= 50) posFrame[0] = 0;	
	}
	
	
	// loop continuation and end of animation
	if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::W)) {
	    posAni++;

	    if (sprint) 
	    	posAni = posAni % 40;
	    else 
	    	posAni = posAni % 60;
	}

	pos.setTextureRect(IntRect(11 * posFrame[0], 28 * posFrame[1], 11, 28));
}

void player::posDash () {
	
	// --== set speed ==--
	if (posAni == 4)
		speed = 13;
	else if (posAni == 5)
		speed = 22;
	else if (posAni > 5 && (posAni + 1) % 5 == 0)
		speed -= 4;


	// --== animation dirrection ==--
	if (lastDir == 'd') {
		posFrame[1] = 0;

		if (!collide[1])
			pos.move (speed, 0);
		else posAni = 29;
	}

	else if (lastDir == 'a') {
		posFrame[1] = 1;

		if (!collide[3])
			pos.move (-speed, 0);
		else posAni = 29;
	}

	else if (lastDir == 'w') {
		posFrame[1] = 2;

		if (!collide[0])
			pos.move (0, -speed);
		else posAni = 29;
	}

	else if (lastDir == 's') {
		posFrame[1] = 3;

		if (!collide[2])
			pos.move (0, speed);
		else posAni = 29;
	}


	// --== animation frame ==--
	if (0 <= posAni && posAni <= 4)
		posFrame[0] = 0;

	if (5 <= posAni && posAni <= 14)
		posFrame[0] = 1;

	if (15 <= posAni && posAni <= 19)
		posFrame[0] = 2;

	if (20 <= posAni && posAni <= 29)
		posFrame[0] = 3;

	posAni++;

	// if it is the end
	if (posAni == 30) {
		posMode = "move";
		posAni = 0;
	}


	// setting the texture
	pos.setTextureRect(IntRect(11 * posFrame[0], 28 * posFrame[1], 11, 28));
}

void player::posJump () {
	int shakeY;
	
	// sequence 1: the animation
	
	if (posAni == 1) {
		if (lastDir == 'd') posFrame[1] = 0;
		else if (lastDir == 'a') posFrame[1] = 1;
		else if (lastDir == 'w') posFrame[1] = 2;
		else if (lastDir == 's') posFrame[1] = 3;
	}
	
	if (0 == posAni) posFrame[0] = 0;
	if (10 == posAni) posFrame[0] = 1;
	if (18 == posAni) posFrame[0] = 2;
	
	else if (posAni == 40) {
		posFrame[0] = 0;
		
		skin.loadFromFile("obrazy/postac/skin1_move.png");
		pos.setTexture(skin);
		pos.setScale(sf::Vector2f(5, 5));
		pos.setOrigin(0, pos.getLocalBounds().height);
	}
	
	pos.setTextureRect(IntRect(11 * posFrame[0], 28 * posFrame[1], 11, 28));
	
	
	// sequence 2: moving the map
	if (posAni == 20) topMap = 0;
	
	if (20 <= posAni && posAni <= 64) {
		if (lastMap == '1') map1Push += 8;
		else if (lastMap == '2') map1Push -= 8;
	}
	
	posAni++;

	// if it is the end
	if (posAni == 70) {
		
		// setting the topMap
		if (lastMap == '1') topMap = 2;
		else if (lastMap == '2') topMap = 1;
		
		posMode = "move";
		posAni = 0;
	}
	
	// sequance 3: a bit of variation to shake the camera
	if (posAni >= 30) {
		shakeY = rand() % 7 - 3;
		
		if (posAni % 2 == 0 && posAni < 64) 
			view.setCenter(pos.getPosition().x + 38 + 3, pos.getPosition().y - 74 + shakeY);
		if (posAni % 4 == 0 && posAni < 64) 
			view.setCenter(pos.getPosition().x + 38 - 3, pos.getPosition().y - 74 + shakeY);
		
		if (posAni == 64 || posAni == 30) 
			view.setCenter(pos.getPosition().x + 38 - 20, pos.getPosition().y - 74 + shakeY);
		if (posAni == 70 || posAni == 32) 
			view.setCenter(pos.getPosition().x + 38 + 20, pos.getPosition().y - 74 + shakeY);
	}
}

void player::posShadow () {


	// ----==== Ash for Dash =====-----
	if (posMode == "dash") {
		air.loadFromFile("obrazy/postac/air_dash.png");
		ash.setTexture(air);
		ash.setScale(sf::Vector2f(5, 5));

		// setting position
		ash.setOrigin(0, ash.getLocalBounds().height);
		if (posAni == 1) {
			ash.setPosition(pos.getPosition().x - 10, pos.getPosition().y);

			if (lastDir == 'd')
				ash.move (36, 0);
			else if (lastDir == 'a')
				ash.move (-36, 0);
			else if (lastDir == 'w')
				ash.move (0, -36);
			else if (lastDir == 's')
				ash.move (0, 36);
		}

		// animation

		ash.setTextureRect(IntRect(20 * posFrame[0], 30 * posFrame[1], 20, 30));

	}
	
	// ----==== Pocket ====----
	pocket.setPosition(pos.getPosition());
	pocket.setOrigin(0, pocket.getLocalBounds().height);
	pocket.setTextureRect(IntRect(11 * posFrame[0], 13 * posFrame[1], 11, 13));
}

void player::drawAll () {
	// draw player
	okno.draw(pos);
	
	// draw pocket
	okno.draw(pocket);
}

void player::drawAsh () {
	// ash if dash
	if (posMode == "dash" && posAni > 1) {
		okno.draw (ash);
	}
}

void player::collision () {
	for (int i = 0; i < 4; i++) collide[i] = false;
	
	int xModMap = pos.getPosition().x;
	xModMap %= 120;
	
	int yModMap = pos.getPosition().y;
	yModMap %= 120;
	
	int height = pos.getGlobalBounds().height;
	int width = pos.getGlobalBounds().width;
	
	
	
	// Map 1 and 0 collisions
	if (topMap != 2) {
		// top collision
		if (yModMap <= width && ((map0[cords[0]][cords[1] - 1] == '#' || (topMap == 1 && (map1[cords[0]][cords[1] - 1] == '#' || map1[cords[0]][cords[1] - 1] == 'o'))) || ((map0[cords[0] + 1][cords[1] - 1] == '#' || (topMap == 1 && (map1[cords[0] + 1][cords[1] - 1] == '#' || map1[cords[0] + 1][cords[1] - 1] == 'o'))) && xModMap + width - 8 >= 120)))
			collide[0] = true;
		
		// botton collision
		if (yModMap >= 120 - 6 && ((map0[cords[0]][cords[1] + 1] == '#' || (topMap == 1 && (map1[cords[0]][cords[1] + 1] == '#' || map1[cords[0]][cords[1] + 1] == 'o'))) || ((map0[cords[0] + 1][cords[1] + 1] == '#' || (topMap == 1 && (map1[cords[0] + 1][cords[1] + 1] == '#' || map1[cords[0] + 1][cords[1] + 1] == 'o'))) && xModMap + width - 8 >= 120)))
			collide[2] = true;
		
		// right collision
		if (xModMap >= 120 - width && ((map0[cords[0] + 1][cords[1]] == '#' || (topMap == 1 && (map1[cords[0] + 1][cords[1]] == '#' || map1[cords[0] + 1][cords[1]] == 'o'))) || ((map0[cords[0] + 1][cords[1] - 1] == '#' || (topMap == 1 && (map1[cords[0] + 1][cords[1] - 1] == '#' || map1[cords[0] + 1][cords[1] - 1] == 'o'))) && yModMap - width + 8 <= 0)))
			collide[1] = true;
		
		// left collision
		if (xModMap <= 12 && ((map0[cords[0] - 1][cords[1]] == '#' || (topMap == 1 && (map1[cords[0] - 1][cords[1]] == '#' || map1[cords[0] - 1][cords[1]] == 'o'))) || ((map0[cords[0] - 1][cords[1] - 1] == '#' || (topMap == 1 && (map1[cords[0] - 1][cords[1] - 1] == '#' || map1[cords[0] - 1][cords[1] - 1] == 'o'))) && yModMap - width + 8 <= 0)))
			collide[3] = true;
			
		
		
		// Wall Collisions During Dash
		if (((map0[cords[0]][cords[1]] == '#' || (topMap == 1 && map1[cords[0]][cords[1]] == '#')) || map0[cords[0]][cords[1]] == 'D') && posMode == "dash") {
				collide[2] = true;
				collide[3] = true;
		}
	}
	
	
	
	if (topMap != 1) {
		// top collision
		if (yModMap <= width && (((map2[cords[0]][cords[1] - 1] == '#' || map2[cords[0]][cords[1] - 1] == 'o') && map2[cords[0]][cords[1]] != 'd') || ((map2[cords[0] + 1][cords[1] - 1] == '#' || map2[cords[0] + 1][cords[1] - 1] == 'o') && xModMap + width - 8 >= 120)))
			collide[0] = true;
		
		// botton collision
		if (yModMap >= 120 - 6 && (((map2[cords[0]][cords[1] + 1] == '#' || map2[cords[0]][cords[1] + 1] == 'o') && map2[cords[0]][cords[1]] != 'd') || ((map2[cords[0] + 1][cords[1] + 1] == '#' || map2[cords[0] + 1][cords[1] + 1] == 'o') && xModMap + width - 8 >= 120)))
			collide[2] = true;
		
		// right collision
		if (xModMap >= 120 - width && (((map2[cords[0] + 1][cords[1]] == '#' || map2[cords[0] + 1][cords[1]] == 'o') && map2[cords[0]][cords[1]] != 'd') || ((map2[cords[0] + 1][cords[1] - 1] == '#' || map2[cords[0] + 1][cords[1] - 1] == 'o') && yModMap - width + 8 <= 0)))
			collide[1] = true;
		
		// left collision
		if (xModMap <= 12 && (((map2[cords[0] - 1][cords[1]] == '#' || map2[cords[0] - 1][cords[1]] == 'o') && map2[cords[0]][cords[1]] != 'd') || ((map2[cords[0] - 1][cords[1] - 1] == '#' || map2[cords[0] - 1][cords[1] - 1] == 'o') && yModMap - width + 8 <= 0)))
			collide[3] = true;
			
		
		
		// Wall Collisions During Dash
		if ((map2[cords[0]][cords[1]] == '#' || map0[cords[0]][cords[1]] == 'D') && posMode == "dash") {
				collide[2] = true;
				collide[3] = true;
		}
	}
		
	
	
	// If For Some Reason You End Up In Wall
	if (map0[cords[0]][cords[1]] != 'd') {
		
		// top collision
		if (cords[1] == 0)
			collide[0] = true;
		
		// bottom collision
		if (cords[1] == mapSize - 1)
			collide[2] = true;
		
		// right collision
		if (cords[0] == mapSize - 1)
			collide[1] = true;
		
		// left collision
		if (cords[0] == 0)
			collide[3] = true;
	}
	
	
	// Door Collisions
	
	if (map0[cords[0]][cords[1]] == 'D') {
		
		// right collision
		if (cords[0] == mapSize - 1)
			collide[1] = true;
	}
	
	if (map0[cords[0]][cords[1] + 1] == 'D') {
		
		// bottom collision
		if (yModMap >= 110)
			collide[2] = true;
	}
	
	if (map0[cords[0] - 1][cords[1]] == 'D') {
		
		// left collision
		if (xModMap <= 10)
			collide[3] = true;
	}
	
	// top collision
	if (map0[cords[0]][cords[1] - 1] == 'D' && yModMap < width / 3)
		collide[0] = true;
}

string player::getPosMode () {
	return posMode;
}

sf::Vector2f player::getPosition() {
	return pos.getPosition();
}

void player::cordControll () {
	cords[0] = pos.getPosition().x / 120;
	cords[1] = pos.getPosition().y / 120 - 2;
	
	ashCords[0] = ash.getPosition().x / 120;
	ashCords[1] = ash.getPosition().y / 120 - 2;
}

void player::setPosition (int x, int y) {
	pos.setPosition (x, y);
}

