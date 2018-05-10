#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <math.h>
#include <string>

class Character {
protected:
	int HP;
	int ATK;
	int DEF;
public:
	Character(int health, int attack, int defence);
	virtual int be_attacked (int a);
	virtual void death() = 0;
};


#endif
