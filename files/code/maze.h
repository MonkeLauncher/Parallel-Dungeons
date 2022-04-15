#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <algorithm>
#include <time.h>
#include <queue>

#include "player.h"
#include "torch.h"

extern char map0[][50], map1[][50], map2[][50], mobMap1[][50], mobMap2[][50];
extern player gracz;
extern int bigCellDraw;


int maze (int size, int StarterWall);


#endif
