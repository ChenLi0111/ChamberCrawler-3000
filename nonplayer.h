#ifndef _NONPLAYER_H_
#define _NONPLAYER_H_
#include "observer.h"
#include "character.h"
#include "player.h"
#include <cstdlib>
#include <time.h>
#include <iostream>

class Player;

class NonPlayer:public Character, public Observer{
protected:
	Player* player;
	bool canBeMove;
	bool attackPC = false;
	bool dead = false;
public:
	NonPlayer(int health, int attack, int defence, Player* player, bool canBeMove);
	// get Status
	int getHP();
	bool getAttackPC();
	bool getCanBeMove();
	bool isDone () override; // for map
	bool canBeSteppedOn() override;
	void death() override;
	virtual void attack();
	// get notified inheriented from observer
	void be_notified_nearby() override;
	virtual void be_notified_leave() override;
        virtual std::string getAction() = 0;
	virtual std::string getRace();
};


class Dragon: public NonPlayer{
	Observer * observer;
public:
	Dragon(Player* player);
	void be_notified_leave() override;
	char getTypeID() override;
	void death() override;
	void setObserver(Observer * observer);
	std::string getAction();
	std::string getRace();

};

class Phoenix: public NonPlayer{
	int life = 1;
	void nirvana();
public:
	Phoenix(Player* player);
	char getTypeID() override;
	int be_attacked(int attack) override;
	std::string getAction();
	std::string getRace();
};

class Merchant: public NonPlayer{
	static bool Hostile;
public: 
	Merchant(Player* player);
	void attack () override;
	int be_attacked(int attack) override;
	char getTypeID() override;
	void death() override;
	std::string getAction();
	std::string getRace();
};

class Goblin: public NonPlayer{
	int pocket = 0;
public:
	Goblin(Player* player);
	void attack () override;
	void amountToSteal();
	char getTypeID() override;
	//void escape();
	void death() override;
	std::string getAction();
	std::string getRace();
};

class Troll: public NonPlayer{

public:
	Troll(Player* player);
	char getTypeID() override;
	std::string getAction();
	std::string getRace();
};

class Werewolf: public NonPlayer{


public:
	Werewolf(Player* player);
	void wolfStatus();
	int be_attacked(int a) override;
	char getTypeID() override;
	std::string getAction();
	std::string getRace();
};

class Vampire: public NonPlayer{


public:
	Vampire(Player* player);
	void absorb(int damage);
	void attack() override;
	char getTypeID() override;
	std::string getAction();
	std::string getRace();
};
#endif
