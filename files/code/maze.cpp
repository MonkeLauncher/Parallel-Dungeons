#include "maze.h"
#include "player.h"
#include "torch.h"

int maze (int size, int StarterWall) {
	
	int mapI[50][50];
	bool clear;
	int part[16] = {size / 2, 1, size / 2, 1, size / 2 - 1, size / 2 + 1, size / 2, 1, size / 2, 1, size / 2 - 1, size / 2 + 1, size / 2 - 1, size / 2 + 1, size / 2 - 1, size / 2 + 1};
	char dir;
	int x, y;
	int a, b;
	queue <int> pathCord;
	
	
	// setting all maps to one char
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			map0[j][i] = ' ';
			map1[j][i] = '#';
			map2[j][i] = '#';
			mapI[j][i] = 1;
			mobMap1[j][i] = ' ';
			mobMap2[j][i] = ' ';
		}
	}
	
	
	// --== setting outer walls ==--
	for (int i = 0; i < size; i++) {
		map0[i][0] = '#';
		map0[i][size - 1] = '#';
		map0[0][i] = '#';
		map0[size - 1][i] = '#';
	}
		
	
	
	// --== Creating random walls ==--
		
	for (int i = 1; i < (size - 1); i++) {
		for (int j = 1; j < (size - 1); j++) {
			
			// checking if these could be started
			a = rand() % 2;
			
			if (a == 0) {
				x = j;
				y = i;
			}
			
			else {
				x = i;
				y = j;
			}
			
			
			a = 0;
			
			if (map0[x][y - 1] == '#') a++;
			if (map0[x + 1][y] == '#') a++;
			if (map0[x][y + 1] == '#') a++;
			if (map0[x - 1][y] == '#') a++;
			
			if (a == 1) {
				if (map0[x][y - 1] == '#' && map0[x - 1][y + 1] == ' ' && map0[x + 1][y + 1] == ' ')
					a = -1; 
				
				else if (map0[x + 1][y] == '#' && map0[x - 1][y - 1] == ' ' && map0[x - 1][y + 1] == ' ') 
					a = -1; 
				
				else if (map0[x][y + 1] == '#' && map0[x - 1][y - 1] == ' ' && map0[x + 1][y - 1] == ' ') 
					a = -1; 
				
				else if (map0[x - 1][y] == '#' && map0[x + 1][y + 1] == ' ' && map0[x + 1][y - 1] == ' ') 
					a = -1; 
			}
			
			if (a == -1) {
				
				if (map0[x][y - 1] == '#') dir = 's';
				else if (map0[x + 1][y] == '#') dir = 'w';
				else if (map0[x][y + 1] == '#') dir = 'n';
				else if (map0[x - 1][y] == '#') dir = 'e';
				
				map0[x][y] = '#';
				
				
				// the actual creation of the smaller walls
				for (int k = 0; k < (size / 3) * 2; k++) {
					
					// the end - no more possibility
					if (dir == 'n' && map0[x - 2][y - 1] == '#' && (map0[x - 1][y - 2] == '#' || map0[x + 1][y - 2] == '#' || map0[x][y - 2] == '#') && map0[x + 2][y - 1] == '#') 
						break;
						
					if (dir == 'e' && map0[x + 1][y - 2] == '#' && (map0[x + 2][y - 1] == '#' || map0[x + 2][y + 1] == '#' || map0[x + 2][y] == '#') && map0[x + 1][y - 2] == '#')
						break;
					
					if (dir == 's' && map0[x + 2][y + 1] == '#' && (map0[x + 1][y + 2] == '#' || map0[x - 1][y + 2] == '#' || map0[x][y + 2] == '#') && map0[x - 2][y + 1] == '#')
						break;
					
					if (dir == 'w' && map0[x - 1][y + 2] == '#' && (map0[x - 2][y + 1] == '#' || map0[x - 2][y - 1] == '#' || map0[x - 2][y] == '#') && map0[x - 1][y - 2] == '#')
						break;
						
						
					// check if the area is clear
					clear = true;
					
					if (dir == 'n') {
						if (map0[x - 1][y - 1] != ' ' || map0[x - 1][y - 2] != ' ' || map0[x][y - 2] != ' ' || map0[x + 1][y - 2] != ' ' || map0[x + 1][y - 1] != ' ') 
							clear = false;
					}
					
					else if (dir == 'e') {
						if (map0[x + 1][y - 1] != ' ' || map0[x + 2][y - 1] != ' ' || map0[x + 2][y] != ' ' || map0[x + 2][y + 1] != ' ' || map0[x + 1][y + 1] != ' ')
							clear = false;
					}
					
					else if (dir == 's') {
						if (map0[x + 1][y + 1] != ' ' || map0[x + 1][y + 2] != ' ' || map0[x][y + 2] != ' ' || map0[x - 1][y + 2] != ' ' || map0[x - 1][y + 1] != ' ')
							clear = false;
					}
					
					else if (dir == 'w') {
						if (map0[x - 1][y + 1] != ' ' || map0[x - 2][y + 1] != ' ' || map0[x - 2][y] != ' ' || map0[x - 2][y - 1] != ' ' || map0[x - 1][y - 1] != ' ')
							clear = false;
					}
					
					// just a bit of random turning (to break down the pattern)
					if (rand() % (size / 3) == 0) clear = false;
					
					
					// moving forward if it is clear
					if (clear) {
						if (dir == 'n') y--;
						else if (dir == 'e') x++;
						else if (dir == 's') y++;
						else if (dir == 'w') x--;
						
						map0[x][y] = '#';
					}
					
					
					// if it is not clear we turn left or right randomly
					else {
						b = rand() % 2;
						
						if (b == 0) {
							if (dir == 'n') dir = 'e';
							else if (dir == 'e') dir = 's';
							else if (dir == 's') dir = 'w';
							else if (dir == 'w') dir = 'n';
						}
						
						else {
							if (dir == 'n') dir = 'w';
							else if (dir == 'e') dir = 'n';
							else if (dir == 's') dir = 'e';
							else if (dir == 'w') dir = 's';
						}
					}
				}
			}
		}
	}
	
	
	
	// swapping some repetitive blocks
	for (int i = 0; i < (size - 3); i++) {
		for (int j = 0; j < (size - 3); j++) {
			// vertical
			if (map0[j][i] == '#' && map0[j][i + 1] == '#' && map0[j][i + 2] == '#' && map0[j][i + 3] == '#' && map0[j + 3][i] == '#' && map0[j + 3][i + 1] == '#' && map0[j + 3][i + 2] == '#' && map0[j + 3][i + 3] == '#') {
				if (map0[j + 1][i] == '#' && map0[j + 1][i + 1] == ' ' && map0[j + 1][i + 2] == '#' && map0[j + 1][i + 3] == ' ' && map0[j + 2][i] == ' ' && map0[j + 2][i + 1] == ' ' && map0[j + 2][i + 2] == ' ' && map0[j + 2][i + 3] == ' ') 
					swap (map0[j + 1][i + 2], map0[j + 2][i + 2]);
				
				else if (map0[j + 1][i] == ' ' && map0[j + 1][i + 1] == ' ' && map0[j + 1][i + 2] == ' ' && map0[j + 1][i + 3] == ' ' && map0[j + 2][i] == '#' && map0[j + 2][i + 1] == ' ' && map0[j + 2][i + 2] == '#' && map0[j + 2][i + 3] == ' ') 
					swap (map0[j + 1][i + 2], map0[j + 2][i + 2]);
			}
			
			// horizontal
			else if (map0[j][i] == '#' && map0[j + 1][i] == '#' && map0[j + 2][i] == '#' && map0[j + 3][i] == '#' && map0[j][i + 3] == '#' && map0[j + 1][i + 3] == '#' && map0[j + 2][i + 3] == '#' && map0[j + 3][i + 3] == '#') {
				if (map0[j][i + 1] == ' ' && map0[j + 1][i + 1] == ' ' && map0[j + 2][i + 1] == ' ' && map0[j + 3][i + 1] == ' ' && map0[j][i + 2] == '#' && map0[j + 1][i + 2] == ' ' && map0[j + 2][i + 2] == '#' && map0[j + 3][i + 2] == ' ') 
					swap(map0[j + 2][i + 1], map0[j + 2][i + 2]);
				
				else if (map0[j][i + 1] == '#' && map0[j + 1][i + 1] == ' ' && map0[j + 2][i + 1] == '#' && map0[j + 3][i + 1] == ' ' && map0[j][i + 2] == ' ' && map0[j + 1][i + 2] == ' ' && map0[j + 2][i + 2] == ' ' && map0[j + 3][i + 2] == ' ') 
					swap(map0[j + 2][i + 1], map0[j + 2][i + 2]);
			}
		}
	}
	
	
	
	// setting road type (for each block: corner, streight_1, streight_2)
	for (int i = 1; i < (size - 1); i++) {
		for (int j = 1; j < (size - 1); j++) {
			a = 0;
			
			if (map0[j][i - 1] == ' ' || map0[j][i - 1] == 'c') a++;
			if (map0[j + 1][i] == ' ' || map0[j + 1][i] == 'c') a++;
			if (map0[j][i + 1] == ' ' || map0[j][i + 1] == 'c') a++;
			if (map0[j - 1][i] == ' ' || map0[j - 1][i] == 'c') a++;
			
			if (a == 2 && map0[j + 1][i] != map0[j - 1][i] && map0[j][i - 1] != map0[j][i + 1] && map0[j][i] == ' ')
				map0[j][i] = 'c';
			
			else if (a > 2 && map0[j][i] == ' ')
				map0[j][i] = 'c';
		}
	}
	
	
	for (int i = 1; i < size - 1; i++) {
		for (int j = 1; j < size - 1; j++) {
			
			if (map0[j][i] == 'c') {
				
				// push up (No. I don't want you to exercise)
				x = j;
				y = i;
				
				if (map0[x][y - 1] == ' ') {
					a = rand() % 2;
					
					do {
						y--;
						if (a == 0) 
							map0[x][y] = '1';
						else
							map0[x][y] = '2';
					} while (map0[x][y - 1] == ' ');
				}
				
				// push right
				x = j;
				y = i;
				
				if (map0[x + 1][y] == ' ') {
					a = rand() % 2;
					
					do {
						x++;
						if (a == 0) 
							map0[x][y] = '1';
						else
							map0[x][y] = '2';
					} while (map0[x + 1][y] == ' ');
				}
				
				// push down
				x = j;
				y = i;
				
				if (map0[x][y + 1] == ' ') {
					a = rand() % 2;
					
					x = j;
					y = i;
					
					do {
						y++;
						if (a == 0) 
							map0[x][y] = '1';
						else 
							map0[x][y] = '2';
					} while (map0[x][y + 1] == ' ');
				}
				
				// push left
				x = j;
				y = i;
				
				if (map0[x - 1][y] == ' ') {
					a = rand() % 2;
					
					x = j;
					y = i;
					
					do {
						x--;
						if (a == 0) 
							map0[x][y] = '1';
						else 
							map0[x][y] = '2';
					} while (map0[x - 1][y] == ' ');
				}
			}
		}
	}
	
	
	// fixing hole problems
	for (int i = 1; i < size - 1; i++) {
		for (int j = 1; j < size - 1; j++) {
			if (map0[j][i] == ' ') map0[j][i] = '#';
		}
	}
	
	
	// moving data to two separate maps
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (map0[j][i] == '1') 
				map1[j][i] = ' ';
				
			else if (map0[j][i] == '2')
				map2[j][i] = ' ';
				
			else if (map0[j][i] == 'c') {
				map1[j][i] = '-';
				map2[j][i] = '-';
			}
		}
	}	
	
	
	// fixing a horrible problem (sometimes there isn't any corner on the specific wall)
	for (int i = 1; i < size - 1; i++) {
		if (map1[i][1] == ' ' || map2[i][1] == ' ') {
			map1[i][1] = '-';
			map2[i][1] = '-';
			break;
		}
	}
		
	for (int i = 1; i < size - 1; i++) {
		if (map1[i][size - 2] == ' ' || map2[i][size - 2] == ' ') {
			map1[i][size - 2] = '-';
			map2[i][size - 2] = '-';
			break;
		}
	}
		
	for (int i = 1; i < size - 1; i++) {
		if (map1[size - 2][i] == ' ' || map2[size - 2][i] == ' ') {
			map1[size - 2][i] = '-';
			map2[size - 2][i] = '-';
			break;
		}
	}
		
	for (int i = 1; i < size - 1; i++) {
		if (map1[1][i] == ' ' || map2[1][i] == ' ') {
			map1[1][i] = '-';
			map2[1][i] = '-';
			break;
		}
	}
	
	
	
	// making hole for entrance (this will not stay)
	if (StarterWall == 0) y = 0;
	else if (StarterWall == 1) x = size - 1;
	else if (StarterWall == 2) y = size - 1;
	else if (StarterWall == 3) x = 0;
	
	if (StarterWall == 0) {
		do {
			x = rand() % (size - 2) + 1;
		} while (map1[x][y + 1] != '-');
	}
	
	else if (StarterWall == 2) {
		do {
			x = rand() % (size - 2) + 1;
		} while (map1[x][y - 1] != '-');
	}
	
	else if (StarterWall == 1) {
		do {
			y = rand() % (size - 2) + 1;
		} while (map1[x - 1][y] != '-');
	}
	
	else if (StarterWall == 3) {
		do {
			y = rand() % (size - 2) + 1;
		} while (map1[x + 1][y] != '-');
	}
	
	
	// making hole for exit 
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (map0[j][i] == '#') mapI[j][i] = 1;
			else mapI[j][i] = 0;
		}
	}
	
	mapI[x][y] = 2;
	pathCord.push(y * size + x);
	
	a = 2;
	
	while (pathCord.size() > 0) {
		a++;
		
		for (int i = 0; i < pathCord.size(); i++) {
			x = pathCord.front() % size;
			y = pathCord.front() / size;
			
			if (mapI[x][y - 1] == 0) {
				pathCord.push((y - 1) * size + x);
				mapI[x][y - 1] = a;
			}
			
			if (mapI[x + 1][y] == 0) {
				pathCord.push(y * size + (x + 1));
				mapI[x + 1][y] = a;
			}
			
			if (mapI[x][y + 1] == 0) {
				pathCord.push((y + 1) * size + x);
				mapI[x][y + 1] = a;
			}
			
			if (mapI[x - 1][y] == 0) {
				pathCord.push(y * size + (x - 1));
				mapI[x - 1][y] = a;
			}
			
			pathCord.pop();
		}
	}
	
	a = 0;
	for (int i = 1; i < size - 1; i++) {
		if (mapI[i][1] > a) {
			x = i;
			y = 1;
			a = mapI[i][1];
		}
		
		if (mapI[i][size - 2] > a) {
			x = i;
			y = size - 2;
			a = mapI[i][size - 2];
		}
		
		if (mapI[1][i] > a) {
			x = 1;
			y = i;
			a = mapI[1][i];
		}
		
		if (mapI[size - 2][i] > a) {
			x = size - 2;
			y = i;
			a = mapI[size - 2][i];
		}
	}
	
	b = StarterWall;
	
	
	if (x == 1) {
		StarterWall = 1;
		x--;
	}
	
	else if (x == size - 2) {
		StarterWall = 3;
		x++;
	}
	
	else if (y == 1) {
		StarterWall = 2;
		y--;
	}
	
	else if (y == size - 2) {
		StarterWall = 0;
		y++;
	}
	
	map0[x][y] = 'd';
	map1[x][y] = 'd';
	map2[x][y] = 'd';
	
	
	
	// setting hole for entrance (deffinitely)
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (map0[j][i] == '#') mapI[j][i] = 1;
			else mapI[j][i] = 0;
		}
	}
	
	mapI[x][y] = 2;
	pathCord.push(y * size + x);
	
	a = 2;
	
	while (pathCord.size() > 0) {
		a++;
		
		for (int i = 0; i < pathCord.size(); i++) {
			x = pathCord.front() % size;
			y = pathCord.front() / size;
			
			if (mapI[x][y - 1] == 0) {
				pathCord.push((y - 1) * size + x);
				mapI[x][y - 1] = a;
			}
			
			if (mapI[x + 1][y] == 0) {
				pathCord.push(y * size + (x + 1));
				mapI[x + 1][y] = a;
			}
			
			if (mapI[x][y + 1] == 0) {
				pathCord.push((y + 1) * size + x);
				mapI[x][y + 1] = a;
			}
			
			if (mapI[x - 1][y] == 0) {
				pathCord.push(y * size + (x - 1));
				mapI[x - 1][y] = a;
			}
			
			pathCord.pop();
		}
	}
	
	a = 0;
	for (int i = 1; i < size - 1; i++) {
		if (mapI[i][1] > a && b == 0 && map1[i][1] == '-') {
			x = i;
			y = 1;
			a = mapI[i][1];
		}
		
		if (mapI[i][size - 2] > a && b == 2 && map1[i][size - 2] == '-') {
			x = i;
			y = size - 2;
			a = mapI[i][size - 2];
		}
		
		if (mapI[1][i] > a && b == 3 && map1[1][i] == '-') {
			x = 1;
			y = i;
			a = mapI[1][i];
		}
		
		if (mapI[size - 2][i] > a && b == 1 && map1[size - 2][i] == '-') {
			x = size - 2;
			y = i;
			a = mapI[size - 2][i];
		}
	}
	
	if (b == 3) x--;
	else if (b == 1) x++;
	else if (b == 0) y--;
	else if (b == 2) y++;
	
	map0[x][y] = 'D';
	map1[x][y] = 'D';
	map2[x][y] = 'D';
	
	
	// setting the player on the map
	if (y == 0)
		gracz.setPosition(x * 120 + 32, (y + 3) * 120);
	
	else if (x == size - 1)
		gracz.setPosition(x * 120, (y + 3) * 120 - 32);
	
	else if (y == size - 1)
		gracz.setPosition(x * 120 + 32, (y + 1) * 120 + 60);
	
	else if (x == 0)
		gracz.setPosition((x + 1) * 120 + 32, (y + 3) * 120 - 32);	
	
	
	
	// creating small treasure rooms on map2
	a = size / 30;
	if (a == 0) a++;
	
	
	for (int b = 0; b < a; b++) {
		for (int i = 0; i < (size * 8); i++) {
			x = rand() % (size - 4) + 1;
			y = rand() % (size - 4) + 1;
			
			clear = true;
			
			for (int j = y; j <= y + 2; j++) {
				for (int k = x; k <= x + 2; k++) {
					
					if (map2[k][j] != '#') {
						clear = false;
						break;
					}
				}
			}
			
			if (clear) {
				for (int j = y; j <= y + 2; j++) {
					for (int k = x; k <= x + 2; k++) {
						
						map2[k][j] = ' ';
					}
				}
				
				map2[x + 1][y + 1] = 'o';
				
				
				// if room is not connected to any path than draw one
				if (map2[x][y - 1] != '#' || map2[x + 1][y - 1] != '#' || map2[x + 2][y - 1] != '#')
					clear = false;
				else if (map2[x - 1][y] != '#' || map2[x - 1][y + 1] != '#' || map2[x - 1][y + 2] != '#')
					clear = false;
				else if (map2[x + 3][y] != '#' || map2[x + 3][y + 1] != '#' || map2[x + 3][y + 2] != '#')
					clear = false;
				else if (map2[x][y + 3] != '#' || map2[x + 1][y + 3] != '#' || map2[x + 2][y + 3] != '#')
					clear = false;
				
				
				if (clear) {
					
					// set path direction
					a = rand() % 2;
					
					if (x <= size / 2) {
						if (y <= size / 2) {
							
							if (a == 0) dir = 'e';
							else dir = 's';
						}
						
						else {
							
							if (a == 0) dir = 'n';
							else dir = 'e';
						}
					}
					
					else {
						if (y <= size / 2) {
							
							if (a == 0) dir = 's';
							else dir = 'w';
						}
						
						else {
							
							if (a == 0) dir = 'w';
							else dir = 'n';
						}
					}
					
					// drawing the path
					if (dir == 'n') {
						x += 1;
						
						do {
							y--;
							map2[x][y] = ' ';
						} while (map2[x - 1][y] == '#' && map2[x][y - 1] == '#' && map2[x + 1][y] == '#' && y > 1);
					}
					
					else if (dir == 'e') {
						x += 2;
						y += 1;
						
						do {
							x++;
							map2[x][y] = ' ';
						} while (map2[x][y - 1] == '#' && map2[x + 1][y] == '#' && map2[x][y + 1] == '#' && x < size - 1);
					}
					
					else if (dir == 's') {
						x += 1;
						y += 2;
						
						do {
							y++;
							map2[x][y] = ' ';
						} while (map2[x + 1][y] == '#' && map2[x][y + 1] == '#' && map2[x - 1][y] == '#' && y < size - 1);
					}
					
					else if (dir == 'w') {
						y += 1;
						
						do {
							x--;
							map2[x][y] = ' ';
						} while (map2[x][y + 1] == '#' && map2[x - 1][y] == '#' && map2[x][y - 1] == '#' && x > 1);
					}
				}
				
				
				break;
			}
		}
	}
		
	
	
	
	// creating small treasure rooms on map1
	for (int b = 0; b < a; b++) {
		for (int i = 0; i < (size * 8); i++) {
			x = rand() % (size - 4) + 1;
			y = rand() % (size - 4) + 1;
			
			clear = true;
			
			for (int j = y; j <= y + 2; j++) {
				for (int k = x; k <= x + 2; k++) {
					
					if (map1[k][j] != '#') {
						clear = false;
						break;
					}
				}
			}
			
			if (clear) {
				for (int j = y; j <= y + 2; j++) {
					for (int k = x; k <= x + 2; k++) {
						
						map1[k][j] = ' ';
					}
				}
				
				map1[x + 1][y + 1] = 'o';
				
				
				// if room is not connected to any path than draw one
				if (map1[x][y - 1] != '#' || map1[x + 1][y - 1] != '#' || map1[x + 2][y - 1] != '#')
					clear = false;
				else if (map1[x - 1][y] != '#' || map1[x - 1][y + 1] != '#' || map1[x - 1][y + 2] != '#')
					clear = false;
				else if (map1[x + 3][y] != '#' || map1[x + 3][y + 1] != '#' || map1[x + 3][y + 2] != '#')
					clear = false;
				else if (map1[x][y + 3] != '#' || map1[x + 1][y + 3] != '#' || map1[x + 2][y + 3] != '#')
					clear = false;
				
				
				if (clear) {
					
					// set path direction
					a = rand() % 2;
					
					if (x <= size / 2) {
						if (y <= size / 2) {
							
							if (a == 0) dir = 'e';
							else dir = 's';
						}
						
						else {
							
							if (a == 0) dir = 'n';
							else dir = 'e';
						}
					}
					
					else {
						if (y <= size / 2) {
							
							if (a == 0) dir = 's';
							else dir = 'w';
						}
						
						else {
							
							if (a == 0) dir = 'w';
							else dir = 'n';
						}
					}
					
					// drawing the path
					if (dir == 'n') {
						x += 1;
						
						do {
							y--;
							map1[x][y] = ' ';
						} while (map1[x - 1][y] == '#' && map1[x][y - 1] == '#' && map1[x + 1][y] == '#' && y > 1);
					}
					
					else if (dir == 'e') {
						x += 2;
						y += 1;
						
						do {
							x++;
							map1[x][y] = ' ';
						} while (map1[x][y - 1] == '#' && map1[x + 1][y] == '#' && map1[x][y + 1] == '#' && x < size - 1);
					}
					
					else if (dir == 's') {
						x += 1;
						y += 2;
						
						do {
							y++;
							map1[x][y] = ' ';
						} while (map1[x + 1][y] == '#' && map1[x][y + 1] == '#' && map1[x - 1][y] == '#' && y < size - 1);
					}
					
					else if (dir == 'w') {
						y += 1;
						
						do {
							x--;
							map1[x][y] = ' ';
						} while (map1[x][y + 1] == '#' && map1[x - 1][y] == '#' && map1[x][y - 1] == '#' && x > 1);
					}
				}
				
				
				break;
			}
		}
	}
		
	
	
	// putting the same blocks into map (to not swap the same repetitive blocks during the gameplay while jump)
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			map0[j][i] = '.';
		}
	}
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			
			if (map1[j][i] == map2[j][i] && map1[j][i] != ' ') {
				map0[j][i] = map1[j][i];
				map1[j][i] = ' ';
			}
		}
	}
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			
			if (map0[j][i] == '#' || map1[j][i] == '#') 
				mobMap1[j][i] = '0';
			
			if (map2[j][i] == '#')
				mobMap2[j][i] = '0';
		}
	}
	
	
	return StarterWall;
}
