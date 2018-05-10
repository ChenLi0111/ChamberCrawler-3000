#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "subject.h"
#include "character.h"
#include "nonplayer.h"
#include <string>
#include <iostream>

class NonPlayer;

class Player: public Subject, public Character {
	int maxHealth;
	int pocket;
	std::string action = "";
	bool dead = false;
public:
	Player(int health, int attack, int defence, int maxHealth);
	virtual ~Player();
	void usePotion (int field, int amount); // print screen here
	// get Info
	int getHP();
	int getATK();
	int getDEF();
	int getPocket();
	// action
	void beStolen(int amount);
	void pickGold (int amount);
	void attack(NonPlayer *);
	// notice
	void notice_nearby();
	void notice_leave();
	// death
	void death();
	bool isDead();
	// print screen
	std::string getAction();
	virtual char getRace()=0;
};

class Human: public Player{
public:
	Human();
	char getRace() override;
};

class Dwarf: public Player{
public:
	Dwarf();
	char getRace() override;
};

class Elves: public Player{
public:
	Elves();
	char getRace() override;
};

class Orc: public Player{
public:
	Orc();
	char getRace() override;
};	

#endif
