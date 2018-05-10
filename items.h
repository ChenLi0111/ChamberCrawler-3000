#ifndef _ITEM_H_
#define _ITEM_H_
#include "observer.h"
#include "nonplayer.h"
#include <iostream> // for debug
#include <string>


class Gold: public Observer{
	Dragon * dragon;
	bool used = false;
	int value;
public:
	Gold(Dragon * dragon, int value);
	bool isDone() override; // for map
	int getAmount();
	bool canBeSteppedOn() override;
	void be_notified_nearby () override;
	void be_notified_leave () override;
	void notice_dragon_dead() override;
	char getTypeID() override;
	std::string getAction();
};

enum PotionType {HEALTH = 0, ATTACK, DEFENCE};

class Potion: public Observer{
	PotionType pt;
	int amount;
	bool used = false;
public:
	Potion();
	Potion(int);
	bool isDone() override; // for map
	char getTypeID() override;
	void be_notified_nearby () override;
	void be_notified_leave () override;
	bool canBeSteppedOn() override;
	int getPotionType();
	int getPotionAmount();
	std::string getAction();
};

	
class Stair: public Observer {
public: 
	Stair();
	char getTypeID() override;
	bool isDone() override;
	bool canBeSteppedOn() override;
	void be_notified_nearby() override;
	void be_notified_leave() override;
	std::string getAction();
};
	
#endif
