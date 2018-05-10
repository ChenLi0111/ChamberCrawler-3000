#include "items.h"

// Gold class

Gold::Gold(Dragon * dragon, int value): dragon{dragon}, value{value} {}

bool Gold::isDone () { return used; }

int Gold::getAmount () {
	used = true;
	return value;
}

bool Gold::canBeSteppedOn(){ 
	if (dragon){
		return false;
	}
	return true; }

void Gold::be_notified_nearby() {
	if (dragon) dragon->be_notified_nearby();
}

void Gold::be_notified_leave() {
	if (dragon) dragon->be_notified_leave();
}

void Gold::notice_dragon_dead() { dragon = nullptr; }

char Gold::getTypeID() { return 'G'; }

std::string Gold::getAction(){
	action = "";
	return action;
}

// Potion Class

Potion::Potion(){
	// srand(time(NULL));
	int probability = rand() % 6;
	if (probability == 0){
		pt = HEALTH;
		amount = rand() % 10 + 1;
	}
	else if (probability == 1){
		pt = HEALTH;
		amount = 0 - (rand() % 10 + 1);
	}
	else if (probability == 2){
		pt = ATTACK;
		amount = rand() % 10 + 1;
	}
	else if (probability == 3){
		pt = ATTACK;
		amount = 0 - (rand() % 10 + 1);
	}
	else if (probability == 4){
		pt = DEFENCE;
		amount = rand() % 10 + 1;
	}
	else if (probability == 5){
		pt = DEFENCE;
		amount = 0 - (rand() % 10 + 1);
	}
}

Potion::Potion(int p){
	if (p == 0){
		pt = HEALTH;
		amount = rand() % 10 + 1;
	}
	else if (p== 1){
		pt = HEALTH;
		amount = 0 - (rand() % 10 + 1);
	}
	else if (p == 2){
		pt = ATTACK;
		amount = rand() % 10 + 1;
	}
	else if (p == 3){
		pt = ATTACK;
		amount = 0 - (rand() % 10 + 1);
	}
	else if (p == 4){
		pt = DEFENCE;
		amount = rand() % 10 + 1;
	}
	else if (p == 5){
		pt = DEFENCE;
		amount = 0 - (rand() % 10 + 1);
	}
	
}

bool Potion::isDone() { return used; }

bool Potion::canBeSteppedOn() { return false; }

char Potion::getTypeID() { return 'P'; }

void Potion::be_notified_nearby () { action = "PC saw an Unknown Potion. "; }

void Potion::be_notified_leave() { action = ""; }

int Potion::getPotionType (){
	used = true;
	if (pt == HEALTH) return 0;
	if (pt == ATTACK) return 1;
	if (pt == DEFENCE) return 2;
	return 0;
}

int Potion::getPotionAmount() {
	used = true;
	return amount;
}

std::string Potion::getAction(){
	std::string atemp = action;
	action = "";
	return atemp;
}

//Stair Class

Stair::Stair(){};

void Stair::be_notified_nearby() {}

void Stair::be_notified_leave() {}

bool Stair::canBeSteppedOn() { return true; }

bool Stair::isDone() {return false; }

char Stair::getTypeID() { return '\\'; }

std::string Stair::getAction(){
	action = "";
	return action;
}
	
 
