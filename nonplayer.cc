#include "nonplayer.h"

class Player;

// NonPlayer Class
NonPlayer::NonPlayer(int health,int attack, int defence, Player* player, bool canBeMove):
	Character(health,attack,defence), player{player}, canBeMove{canBeMove} {} 

bool NonPlayer::getAttackPC() { return attackPC; }

bool NonPlayer::getCanBeMove() { return canBeMove; }

int NonPlayer::getHP() {return (HP < 0)? 0 : HP;}

void NonPlayer::death() { dead = true; player->pickGold(1);}

bool NonPlayer::isDone() { return dead; }

bool NonPlayer::canBeSteppedOn() { return false; }

std::string NonPlayer::getRace() { return "NonPlayer"; }

void NonPlayer::attack(){
	if (rand()%2 == 0)
		action = action + getRace()+ " deals "+ std::to_string(player->be_attacked (ATK)) + " to PC. ";
	else action = action + getRace() + " misses attack. ";
}

void NonPlayer::be_notified_nearby() { canBeMove = false; attackPC = true; }

void NonPlayer::be_notified_leave() { canBeMove = true; attackPC = false; }

// Dragon Class

Dragon::Dragon(Player* player): NonPlayer(150, 20, 20, player, false) {}

char Dragon::getTypeID (){ return 'D'; }

void Dragon::be_notified_leave() { attackPC = false; }

void Dragon::death(){
	dead = true;
	player->pickGold(2);
	observer->notice_dragon_dead();
	observer = nullptr;
}

void Dragon::setObserver (Observer* obs) {  this->observer = obs; }

std::string Dragon::getRace() { return "Dragon"; }

std::string Dragon::getAction(){
	std::string atemp = action;
	action = "";
	return atemp;
}

// Phoenix Class

Phoenix::Phoenix(Player* player): NonPlayer(50, 35, 20, player, true) {}

int Phoenix::be_attacked(int a){
	int damage = ceil((100.0 / (100.0 + DEF)) * a);
	HP -= damage;
	//std::cout << "P be attacked" << std::endl;
	if (HP <= 0 && life == 1) nirvana ();
	else if (HP <= 0 && life == 0) death();
	return damage;
}

void Phoenix::nirvana(){
	//std::cout << "nirvana" << std::endl;
	if (life == 0) return;
	HP = 100;
	ATK = 5;
	DEF = 10;
	life = 0;
	action = action + "Phoenix use Nirana!!! ";
}

std::string Phoenix::getRace() { return "Phoenix"; }

std::string Phoenix::getAction(){
	std::string atemp = action;
	action = "";
	return atemp;
}

char Phoenix::getTypeID () { return 'X'; }


// Merchant Class

bool Merchant::Hostile = false;

Merchant::Merchant (Player* player): NonPlayer(30, 70, 5, player,true) {}

void Merchant::attack(){
	if (Hostile){
		NonPlayer::attack();
	}
}
	

int Merchant::be_attacked(int a){
	if (!Hostile){
		Hostile = true;
		action = action + "Merchant becomes your enemy. ";
	}
	return Character::be_attacked(a);
}

void Merchant::death() { dead = true; }

char Merchant::getTypeID() { return 'M'; }

std::string Merchant::getRace() { return "Merchant"; }

std::string Merchant::getAction(){
	std::string atemp = action;
	action = "";
	return atemp;
}


// Goblin Class

Goblin::Goblin (Player * player): NonPlayer(70, 5, 10, player,true) {}

void Goblin::attack (){
  NonPlayer::attack();
  amountToSteal();
  //escape();
}

void Goblin::amountToSteal(){
	//srand(time(NULL));
	int aDetermine = rand() % 100;
	if (player->getPocket() == 0) return;
	if (aDetermine <= 60) return;
	else if (aDetermine <= 85){
		stealOne: 
		action = action + "Goblin steals PC 1 gold! ";
		player->beStolen(1);
		pocket += 1; }
	else{
		if (player->getPocket() == 1) goto stealOne;
		action = action + "Goblin steals PC 2 gold! "; 
		player->beStolen(2);
		pocket += 2; }
}
/*
void Goblin::escape(){
	int eDetermine = rand () % 5;
	if (eDetermine == 0){
		canBeMove = true; attackPC = false; ;
		action = action + " Goblin runs away...";
	}
}
*/
void Goblin::death() { dead = true; player->pickGold(2 + pocket);}
	

char Goblin::getTypeID() { return 'N'; }

std::string Goblin::getRace() { return "Goblin"; }

std::string Goblin::getAction(){
	std::string atemp = action;
	action = "";
	return atemp;
}


// Troll Class

Troll::Troll(Player* player): NonPlayer(120, 25, 15, player, true) {}

char Troll::getTypeID () { return 'T'; }

std::string Troll::getRace() { return "Troll"; }

std::string Troll::getAction(){
	std::string atemp = action;
	action = "";
	return atemp;
}


// Werewolf

Werewolf::Werewolf(Player* player): NonPlayer(120, 30, 5, player, true) {}

void Werewolf::wolfStatus(){
	if (0 < HP && HP < 25){
		ATK *= 2;
		DEF = 0;
		action = action +"Watch Out!! Werewolf becomes angry!! ";
	}
}

int Werewolf::be_attacked(int a){
	int damage = ceil((100.0 / (100.0 + DEF)) * a);////////////////////////
	HP -= damage;
	wolfStatus();
	if (HP <= 0 ) death();
	return damage;
}

char Werewolf::getTypeID() { return 'W'; }

std::string Werewolf::getRace() { return "Werewolf"; }

std::string Werewolf::getAction(){
	std::string atemp = action;
	action = "";
	return atemp;
}


// Vampire Class

Vampire::Vampire(Player* player): NonPlayer(50, 25, 25, player,true) {}

void Vampire::attack(){
	int damage = player->be_attacked(ATK);
	absorb(damage);
	action = action + "Vampire deals "+ std::to_string(damage) + " to PC. "; 
}

void Vampire::absorb(int damage){
	//srand (time(NULL));
	int tail = rand() % 3;
	if (tail == 0) return;
	int absorbAmount = ceil(damage * 0.2);
	HP = (HP > 50 - absorbAmount)? 50 : (HP + absorbAmount);
	action  = action + "Vampire absorb " + std::to_string(absorbAmount) + " from PC. ";
}

char Vampire::getTypeID() { return 'V'; }

std::string Vampire::getRace() { return "Vampire"; }

std::string Vampire::getAction(){
	std::string atemp = action;
	action = "";
	return atemp;
}
