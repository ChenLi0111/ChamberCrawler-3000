#include "player.h"

Player::Player (int health, int attack, int defence, int maxHealth):
	Character (health, attack,defence), maxHealth{maxHealth}, pocket{0} {}

Player::~Player(){}

void Player::usePotion (int field, int amount) {
	if (getRace() == 'E') amount = (amount > 0)? amount: 0-amount;
	action = "PC uses ";	
	if (field == 0){
		if (amount >= 0){
			action = action + "RH, HP increased by " + std::to_string (amount) + ". ";
			HP = (HP + amount > maxHealth)? maxHealth : HP + amount;
		} else {
			amount = 0 - amount;
			action = action + "PH, HP decreased by " + std::to_string(amount)+ ". ";
			if (HP - amount < 0){
				death();
				std::cout << "PC is killed by Potion. " << std::endl;
			}
			else HP -= amount;
		}
	} else if (field == 1) {
		if (amount >= 0){
			action = action + "BA, ATK increased by " + std::to_string (amount)+ ". ";
			ATK += amount;
		} else {
			amount = 0 - amount;
			action = action + "WA, ATK decrease by " + std::to_string (amount)+ ". ";
			ATK = (ATK - amount < 0)? amount : ATK - amount;
		}
	} else {
		if (amount >= 0) {
			action = action + "BD, DEF increased by " + std::to_string (amount)+ ". ";
			DEF += amount;
		} else {
			amount = 0 - amount;
			action = action + "WD, DEF decreased by " + std::to_string (amount)+ ". ";
			DEF = (DEF - amount < 0)? amount : DEF - amount;
		}
	}
}

int Player::getHP () { return HP; }

int Player::getATK () { return ATK; }

int Player::getDEF () { return DEF; }

int Player::getPocket() { return pocket; }

void Player::beStolen (int amount){
	pocket = (pocket - amount < 0) ? 0 : pocket - amount;
}

void Player::pickGold (int amount) { 
	pocket += amount;
	action = action + "PC got " + std::to_string(amount) +" gold. ";
}

void Player::attack (NonPlayer *defender){
	std::string damage = std::to_string(defender->be_attacked (ATK));
	action = "PC deals " + damage + " to " + defender->getRace() +"("+
		 std::to_string(defender->getHP()) + "HP" + ")"+ ". " + action;
}

void Player::notice_nearby(){
	for (int i = 0; i < getObjNo(); ++i)
		observer_nearby[i]->be_notified_nearby();
}

void Player::notice_leave(){
	for (int i = 0; i < getObjNo(); ++i){
		observer_nearby[i]->be_notified_leave();
		observer_nearby[i] = nullptr;
	}
	resetObjNo();
}

void Player::death () { dead = true; }

bool Player::isDead () { return dead; }

std::string Player::getAction(){
	std::string atemp = action;
	action = "";
	return atemp;
}


// Human Class

Human::Human(): Player(140, 20, 20, 140) {} 

char Human::getRace() { return 'H'; }


// Dwarf Class

Dwarf::Dwarf(): Player(100, 20, 30, 100) {}

char Dwarf::getRace() { return 'D'; }


// Elves Class

Elves::Elves(): Player(140, 30, 10, 140) {}

char Elves::getRace() { return 'E'; }


// Orc Class

Orc::Orc(): Player(180, 30, 25, 180) {}

char Orc::getRace() { return 'O'; }


