#ifndef _MAP_H_
#define _MAP_H_

#include "mapunit.h"
#include "nonplayer.h"
#include "player.h"
#include "items.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <sstream>
#include <unistd.h>

enum Direction {NO,SO,EA,WE,NW,NE,SW,SE};

class Map {
	MapUnit* realMap[79][25];
	Player* PC;
	int PC_x = -1;
	int PC_y = -1;
	//Stair* stair;
	int floorNo = 1;
	int potionNo;
	int nonPlayerNo;
	int dragonNo;
	int goldNo;
	int gNo = 0;
	int linesbeRead = 0;
	bool loaded = false;
	std::string mapFile; // file that stores the init map
	int nonPlayerPosArray[2][20]; // forget adding pos in it
	std::stringstream action;
	void setRoomNo(int x,int y,int n);
	
public:
	Map(int potionNo, int nonPlayerNo, int goldNo, std::string mapFile);
	~Map();
	// init
	void initMap(); // done
	bool initPC (char c); // done
	bool isLoad();
	void generatePotion(); // done
	void generateGold(); // done
	void generateNonPlayer(); // done
	void generateElse(); // done
	int generatePC();
	void generateStair(int PCroomNo);
	// print part
	void printMap(std::ostream& out); // need fix
	void printInfo(std::ostream& out);
	void printAction(std::ostream& out);
	// player part
	bool player_move(Direction d); // done
	bool player_use(Direction d); // done
	bool player_attack(Direction d); // done
	void setPlayerObservers();
	bool isPCDead();
	// NPC part
	void sortPosArray(); // done
	int moveDirection (int x, int y); // done
	void NPC_action(); // done
	// Floor part
	void clearMap();
	void gotoNextFloor();
	bool isWin();
	// Summary Part
	void deadMsg(std::ostream& out);
	void winMsg(std::ostream& out);
};

#endif
