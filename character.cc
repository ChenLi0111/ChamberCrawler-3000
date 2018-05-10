#include "character.h"


Character::Character(int health, int attack, int defence): 
	HP{health}, ATK{attack}, DEF{defence} {}

int Character::be_attacked (int a){
	int damage = ceil((100.0/(100.0+DEF)) * a);
	HP -= damage;
	if(HP <= 0) death();
	return damage;
}
	
	
