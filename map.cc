#include "map.h"
#include<fstream>
using namespace std;

Map::Map(int potionNo, int nonPlayerNo, int goldNo, string mapFile):
	realMap{nullptr}, PC{nullptr},potionNo{potionNo}, nonPlayerNo{nonPlayerNo}, goldNo{goldNo}, mapFile{mapFile}  {action.str("");}

Map::~Map(){
	clearMap();
	 for(int x=0; x<79;++x) for(int y=0; y<25;++y) delete realMap[x][y];
	delete PC;
}

// init part
void Map::setRoomNo(int x,int y,int n){
	if(realMap[x][y]->getRoomNo()!=0) return;
	realMap[x][y]->setRoomNo(n);
	Map::setRoomNo(x+1,y,n);
	Map::setRoomNo(x-1,y,n);
	Map::setRoomNo(x,y+1,n);
	Map::setRoomNo(x,y-1,n);
	Map::setRoomNo(x+1,y+1,n);
	Map::setRoomNo(x+1,y-1,n);
	Map::setRoomNo(x-1,y+1,n);
	Map::setRoomNo(x-1,y-1,n);
}

void Map::initMap (){
	for(int x=0; x<79;++x) for(int y=0; y<25;++y) delete realMap[x][y];
	ifstream file;
	file.open(mapFile,ios::in);
	char symbol;
	string line;
	int c = 0;
	int r = 0;
	int DragonGoldPos[2][10];
	int DragonGoldNum=0;
	for (int i = 0; i < linesbeRead; i++) getline(file,line);
	cout << linesbeRead << endl;
	while (getline(file,line) &&r != 25){
		stringstream ss (line);
		while (ss >> noskipws >> symbol){
			//cout << "symbol:" << symbol << endl;
			if (symbol == '-') realMap[c][r] = new Horizontal_Wall{};
			else if (symbol == '|') realMap[c][r] = new Vertical_Wall {};
			else if (symbol == '#') realMap[c][r] = new Path {};
			else if (symbol == '+') realMap[c][r] = new Door {};
			else if (symbol == ' ') realMap[c][r] = new Null {};
			else{
				realMap[c][r]=new Room;
				if(symbol == '@' ){PC_x=c; PC_y=r; if(!PC) PC=new Human;} //???????????????????????????????????????????
				else if(symbol == 'V' )
				{nonPlayerPosArray[0][gNo]=c; nonPlayerPosArray[1][gNo]=r; ++gNo; realMap[c][r]->setMapUnitStatus(NONPLAYER); realMap[c][r]->setObserver(new Vampire(PC));}
				else if(symbol == 'W' )
				{nonPlayerPosArray[0][gNo]=c; nonPlayerPosArray[1][gNo]=r; ++gNo; realMap[c][r]->setMapUnitStatus(NONPLAYER); realMap[c][r]->setObserver(new Werewolf(PC));}
				else if(symbol == 'N' )
				{nonPlayerPosArray[0][gNo]=c; nonPlayerPosArray[1][gNo]=r; ++gNo; realMap[c][r]->setMapUnitStatus(NONPLAYER); realMap[c][r]->setObserver(new Goblin(PC));}
				else if(symbol == 'M' )
				{nonPlayerPosArray[0][gNo]=c; nonPlayerPosArray[1][gNo]=r; ++gNo; realMap[c][r]->setMapUnitStatus(NONPLAYER); realMap[c][r]->setObserver(new Merchant(PC));}
				else if(symbol == 'X' )
				{nonPlayerPosArray[0][gNo]=c; nonPlayerPosArray[1][gNo]=r; ++gNo; realMap[c][r]->setMapUnitStatus(NONPLAYER); realMap[c][r]->setObserver(new Phoenix(PC));}
				else if(symbol == 'T' )
				{nonPlayerPosArray[0][gNo]=c; nonPlayerPosArray[1][gNo]=r; ++gNo; realMap[c][r]->setMapUnitStatus(NONPLAYER); realMap[c][r]->setObserver(new Troll(PC));}
				else if(symbol == 'D' )
				{nonPlayerPosArray[0][gNo]=c; nonPlayerPosArray[1][gNo]=r; ++gNo; realMap[c][r]->setMapUnitStatus(NONPLAYER); realMap[c][r]->setObserver(new Dragon(PC));}
				else if(symbol == '0' ){realMap[c][r]->setMapUnitStatus(POTION); realMap[c][r]->setObserver(new Potion{0});}
				else if(symbol == '1' ){realMap[c][r]->setMapUnitStatus(POTION); realMap[c][r]->setObserver(new Potion{1});}
				else if(symbol == '2' ){realMap[c][r]->setMapUnitStatus(POTION); realMap[c][r]->setObserver(new Potion{2});}
				else if(symbol == '3' ){realMap[c][r]->setMapUnitStatus(POTION); realMap[c][r]->setObserver(new Potion{3});}
				else if(symbol == '4' ){realMap[c][r]->setMapUnitStatus(POTION); realMap[c][r]->setObserver(new Potion{4});}
				else if(symbol == '5' ){realMap[c][r]->setMapUnitStatus(POTION); realMap[c][r]->setObserver(new Potion{5});}
				else if(symbol == '6' ){realMap[c][r]->setMapUnitStatus(GOLD); realMap[c][r]->setObserver(new Gold{nullptr,1});}
				else if(symbol == '7' ){realMap[c][r]->setMapUnitStatus(GOLD); realMap[c][r]->setObserver(new Gold{nullptr,2});}
				else if(symbol == '8' ){realMap[c][r]->setMapUnitStatus(GOLD); realMap[c][r]->setObserver(new Gold{nullptr,4});}
				else if(symbol == '9' ){realMap[c][r]->setMapUnitStatus(GOLD); DragonGoldPos[0][DragonGoldNum]=c;DragonGoldPos[1][DragonGoldNum]=r; ++DragonGoldNum;}
				else if(symbol == '\\' ){realMap[c][r]->setMapUnitStatus(STAIR); realMap[c][r]->setObserver(new Stair);}
				
			}
			//cout << realMap[c][r]->getTypeID() << c << " , " << r << endl;
			c++;
		}
		c = 0;
		linesbeRead++;
		r++;
	}
	for(;gNo<nonPlayerNo;++gNo){nonPlayerPosArray[0][gNo]=-1; nonPlayerPosArray[1][gNo]=-1;}
	gNo=0;
	// find dragon
	for(int i=0;i<DragonGoldNum;++i){
		Dragon *d=0;
		d = d? d : dynamic_cast<Dragon *>(realMap[ DragonGoldPos[0][i] +1] [DragonGoldPos[1][i] ] -> getObserver() );
		d = d? d : dynamic_cast<Dragon *>(realMap[ DragonGoldPos[0][i] -1] [DragonGoldPos[1][i] ] -> getObserver() ) ;
		d = d? d : dynamic_cast<Dragon *>(realMap[ DragonGoldPos[0][i] ] [DragonGoldPos[1][i] +1] -> getObserver() );
		d = d? d : dynamic_cast<Dragon *>(realMap[ DragonGoldPos[0][i] ] [DragonGoldPos[1][i] -1] -> getObserver() ) ;
		d = d? d : dynamic_cast<Dragon *>(realMap[ DragonGoldPos[0][i] +1] [DragonGoldPos[1][i] +1] -> getObserver() ); 
		d = d? d : dynamic_cast<Dragon *>(realMap[ DragonGoldPos[0][i] +1] [DragonGoldPos[1][i] -1] -> getObserver() );
		d = d? d : dynamic_cast<Dragon *>(realMap[ DragonGoldPos[0][i] -1] [DragonGoldPos[1][i] +1] -> getObserver() ) ;
		d = d? d : dynamic_cast<Dragon *>(realMap[ DragonGoldPos[0][i] -1] [DragonGoldPos[1][i] -1] -> getObserver() ) ;
		//cout << d <<endl;
		//cout << DragonGoldPos[0][i] << ',' << DragonGoldPos[1][i] <<endl;
		if(d){
			//cout << "dragggggggggononononononononon" << endl;
			realMap[DragonGoldPos[0][i]][DragonGoldPos[1][i]]->setObserver(new Gold{d, 6});
			d->setObserver(realMap[DragonGoldPos[0][i]][DragonGoldPos[1][i]]->getObserver());
		}
	}		
	DragonGoldNum = 0;
	int n=0;
	for(int c=0;c<79;++c) for(int r=0;r<25;++r) if(realMap[c][r]->getRoomNo()==0){ ++n; setRoomNo(c,r,n);}
	if (file.eof() && floorNo > 1 && floorNo < 5){ loaded = false; gotoNextFloor(); }
}

void Map::generatePotion(){
	//srand(time(NULL));
	for(int i = 1; i <= potionNo; i++){ // repeat to generate 10 potions
		//cout << "generate Potion " << i << endl;
		int x = rand()%79;
		int y = rand()%25;
		int rtg = i % 5 + 1;
		//cout << "rtg = " << rtg << endl;
		while(realMap[x][y]->getMapUnitStatus()!= EMPTY ||
		      realMap[x][y]->getRoomNo() != rtg)
		{ x = rand()%79; y = rand()%25; }
		//cout << "HereP" << endl;
		realMap[x][y]->setMapUnitStatus(POTION);
		realMap[x][y]->setObserver(new Potion{});
		//cout<< x << " , " << y<< ":" << realMap[x][y]->getTypeID() << endl;
	}
}

void Map::generateGold(){
	//srand(time(NULL) + 1);
	for(int i = 1; i <= goldNo; i++){ // repeat to generate 10 golds
		//cout << "generate gold " << i << endl;
		int probability = rand()%8;
		int x = rand()%79;
		int y = rand()%25;
		int rtg = i % 5 + 1;
		while(realMap[x][y]->getMapUnitStatus()!= EMPTY ||
		      realMap[x][y]->getRoomNo() != rtg)
		{ x = rand()%79; y = rand()%25; }
		//cout << "HereG" << endl;
		// dragon horde 1/8
		if (probability == 0){
			//cout << "DDDDDDDDDDDDDDDDDDDDDDDD" << endl;
			int dragonX = x;
			int dragonY = y;
			realMap[x][y]->setMapUnitStatus(GOLD);
			while(realMap[dragonX][dragonY]->getMapUnitStatus() != EMPTY){
				int dragonPosition = rand()%8;
				dragonX = x;
				dragonY = y;
				if (dragonPosition == 0) { dragonX = x - 1; dragonY = y - 1; } // north west
				else if (dragonPosition == 1) { dragonY = y - 1; } // north
				else if (dragonPosition == 2) { dragonX = x + 1; dragonY = y - 1; } // north east
				else if (dragonPosition == 3) { dragonX = x - 1; } // west
				else if (dragonPosition == 4) { dragonX = x + 1; } // east
				else if (dragonPosition == 5) { dragonX = x - 1; dragonY = y + 1; } // south west
				else if (dragonPosition == 6) { dragonY = y + 1; } // south
				else if (dragonPosition == 7) { dragonX = x + 1; dragonY = y + 1; } // south west
			} // end while
			realMap[dragonX][dragonY]->setMapUnitStatus(NONPLAYER);
			realMap[dragonX][dragonY]->setObserver(new Dragon{PC});
			nonPlayerPosArray[0][gNo] = dragonX; nonPlayerPosArray[1][gNo] = dragonY;
			gNo ++;
			realMap[x][y]->setObserver(new Gold{dynamic_cast<Dragon*> (realMap[dragonX][dragonY]->getObserver()), 6});
			(dynamic_cast<Dragon*> (realMap[dragonX][dragonY]->getObserver()))->setObserver(realMap[x][y]->getObserver());
		} // end if
		// small horde 1/4
		else if (probability <= 2){
			realMap[x][y]->setMapUnitStatus(GOLD);
			realMap[x][y]->setObserver(new Gold{nullptr,2});
		} // end else if
		//normal horde 5/8
		else{ 
			realMap[x][y]->setMapUnitStatus(GOLD);
			realMap[x][y]->setObserver(new Gold{nullptr,1});
		}// end else 
	}// end for
} // end generateGold function

void Map::generateNonPlayer(){
	//srand(time(NULL) + 2);
	int tilNow = nonPlayerNo - gNo;
	for (int i = 0; i <tilNow; ++i){ // repeat to generate NonPlayers
		//cout << "generate nonPlayer " << i << endl;
		int probability = rand()%18;
		int x = rand()%79;
		int y = rand()%25;
		int rtg = i % 5 + 1;
		while(realMap[x][y]->getMapUnitStatus()!= EMPTY ||
		      realMap[x][y]->getRoomNo() != rtg)
		{ x = rand()%79; y = rand()%25; }
		//cout << "HereN" << endl;
		realMap[x][y]->setMapUnitStatus(NONPLAYER);
		nonPlayerPosArray[0][gNo] = x; nonPlayerPosArray[1][gNo] = y;
		//cout << gNo << "ggggggggggggggggggg" << nonPlayerPosArray[0][gNo] << endl;
		gNo ++; 
		// Werewolf 2/9
		if (probability <= 3)
			realMap[x][y]->setObserver(new Werewolf(PC));
		// Vampire 3/18
		else if (probability <= 6)
			realMap[x][y]->setObserver(new Vampire(PC));
		// Goblin 5/18
		else if (probability <= 11)
			realMap[x][y]->setObserver(new Goblin(PC));
		// Troll 1/9
		else if (probability <= 13)
			realMap[x][y]->setObserver(new Troll(PC));
		// Phoenix 1/9
		else if (probability <= 15)
			realMap[x][y]->setObserver(new Phoenix(PC));
		// Merchant 1/9
		else if (probability <= 17)
			realMap[x][y]->setObserver(new Merchant(PC));
	}// end for
} // end generateNonPlayer function

void Map::generateElse(){
	int PC_roomNo = 0;
	if (PC_x == -1 && PC_y == -1)
		PC_roomNo = generatePC();
	else
		PC_roomNo = realMap[PC_x][PC_y]->getRoomNo();
	generateStair(PC_roomNo);
}

int Map::generatePC(){
	if (PC&&PC_x!=-1&&PC_y!=-1) return realMap[PC_x][PC_y]->getRoomNo();
	PC_x = rand() % 79;
	PC_y = rand() % 25;
	while (realMap[PC_x][PC_y]->getMapUnitStatus()!= EMPTY){
		PC_x = rand() % 79;
		PC_y = rand() % 25;
	}
	realMap[PC_x][PC_y]->setMapUnitStatus(PLAYER);
	return realMap[PC_x][PC_y]->getRoomNo();
}

void Map::generateStair(int PCroomNo){
	int Stair_x = rand() % 79;
	int Stair_y = rand() % 25;
	while (realMap[Stair_x][Stair_y]->getRoomNo() == PCroomNo 
		|| realMap[Stair_x][Stair_y]->getMapUnitStatus()!= EMPTY){
		Stair_x = rand() % 79;
		Stair_y = rand() % 25;
	}
	realMap[Stair_x][Stair_y]->setMapUnitStatus(STAIR);
	realMap[Stair_x][Stair_y]->setObserver(new Stair{});
}

bool Map::isLoad() { loaded = (PC!=nullptr); return loaded; }

bool Map::initPC (char c){
	if (PC) delete PC;
	if (c == 'h') PC = new Human{};
	else if (c == 'e') PC = new Elves{};
	else if (c == 'd') PC = new Dwarf{};
	else if (c == 'o') PC = new Orc{};
	else return false;
	gNo = 0;
	generateElse();
	generatePotion();
	generateGold();
	generateNonPlayer();
	setPlayerObservers();
	PC->notice_nearby();
	return true;
}

// print part 

void Map::printMap(ostream &out){
	if (PC)	action << PC->getAction();
	for(int i = 0; i < 25; ++i){
		for (int j = 0; j < 79; ++j){
			if (i == PC_y && j == PC_x)
				out << '@';
			else if (realMap[j][i]->getObserver()){
				if (realMap[j][i]->getObserver()->isDone()){
					realMap[j][i]->resetRoom();
					out << realMap[j][i]->getTypeID();
				} else { 
					//cout << "Here pppppppppppp" << endl;
					action << realMap[j][i]->getObserver()->getAction();
					out << realMap[j][i]->getObserver()->getTypeID(); }
			}
			else
				out << realMap[j][i]->getTypeID();
		}
		out << "\n";
	}
}

void Map::printInfo(ostream &out){
	string race;	
	if (PC->getRace() == 'H')
		race = "Human";
	else if (PC->getRace () == 'E')
		race = "Elves";
	else if (PC->getRace () == 'O')
		race = "Orc";
	else
		race = "Dwarf";
	out << "Race: " << race;
	out << " Gold: " << PC->getPocket();
	string space ="                                 ";
	out << space << "Floor " << floorNo << endl;
	out << "HP: " << PC->getHP() << endl;
	out << "Atk: " << PC->getATK() << endl;
	out << "Def: " << PC->getDEF() << endl;
} 
	
void Map::printAction(ostream &out){
	out << "Action: ";
	out << action.str() << endl;
	action.str("");
}

// player part 

bool Map::player_move(Direction d){
	int new_x = PC_x;
	int new_y = PC_y;
	std::string moveAction = "PC moves to ";
	if (d == NO){ new_y -= 1; moveAction = moveAction + "North. "; }
	else if (d == SO) { new_y += 1; moveAction = moveAction + "South. "; }
	else if (d == EA) { new_x += 1; moveAction = moveAction + "East. "; }
	else if (d == WE) { new_x -= 1; moveAction = moveAction + "West. "; }
	else if (d == NW) { new_y -= 1; new_x -= 1; moveAction = moveAction + "North West."; }
	else if (d == NE) { new_y -= 1; new_x += 1; moveAction = moveAction + "North East."; }
	else if (d == SW) { new_y += 1; new_x -= 1; moveAction = moveAction + "South West."; }
	else if (d == SE) { new_y += 1; new_x += 1; moveAction = moveAction + "South East."; }
	if (realMap[new_x][new_y]->canBeSteppedOnByPlayer()){
			//cout << "MMMMMMMMMMMMMMMMMMM" << endl;
			if (realMap[new_x][new_y]->getMapUnitStatus() == GOLD)
				PC->pickGold((dynamic_cast<Gold *> 
						(realMap[new_x][new_y]->getObserver()))->getAmount());
			if (realMap[new_x][new_y]->getMapUnitStatus() == STAIR){
				floorNo += 1;
				realMap[PC_x][PC_y]->setMapUnitStatus(EMPTY);
				PC_x = new_x; PC_y = new_y;
				realMap[new_x][new_y]->setMapUnitStatus(PLAYER);
				gotoNextFloor();
				return true; } // generate map again	
			realMap[new_x][new_y]->resetRoom();
			realMap[new_x][new_y]->setMapUnitStatus(PLAYER);
			realMap[PC_x][PC_y]->setMapUnitStatus(realMap[PC_x][PC_y]->getOriginMUS());
			setPlayerObservers();
			PC_x = new_x; PC_y = new_y;
			PC->notice_leave();
			setPlayerObservers();
			PC->notice_nearby();
			NPC_action();
			setPlayerObservers();
			PC->notice_nearby();
			action << moveAction;
			return true;
	} return false;
}

bool Map::player_use (Direction d){
	int new_x = PC_x;
	int new_y = PC_y;	
	if (d == NO){ new_y -= 1; }
	else if (d == SO) { new_y += 1; }
	else if (d == EA) { new_x += 1; }
	else if (d == WE) { new_x -= 1; }
	else if (d == NW) { new_y -= 1; new_x -= 1; }
	else if (d == NE) { new_y -= 1; new_x += 1; }
	else if (d == SW) { new_y += 1; new_x -= 1; }
	else if (d == SE) { new_y += 1; new_x += 1; }
	if (realMap[new_x][new_y]->getMapUnitStatus() == POTION){
		int type = (dynamic_cast<Potion *> (realMap[new_x][new_y]->getObserver()))->getPotionType();
		int amount = (dynamic_cast<Potion *> (realMap[new_x][new_y]->getObserver()))->getPotionAmount();
		PC->usePotion(type,amount);
		setPlayerObservers();
		PC->notice_nearby();
		NPC_action();
		return true;
	}
	return false;
}


		
bool Map::player_attack (Direction d){
	int new_x = PC_x;
	int new_y = PC_y;	
	if (d == NO){ new_y -= 1; }
	else if (d == SO) { new_y += 1; }
	else if (d == EA) { new_x += 1; }
	else if (d == WE) { new_x -= 1; }
	else if (d == NW) { new_y -= 1; new_x -= 1; }
	else if (d == NE) { new_y -= 1; new_x += 1; }
	else if (d == SW) { new_y += 1; new_x -= 1; }
	else if (d == SE) { new_y += 1; new_x += 1; }
	if (realMap[new_x][new_y]->getMapUnitStatus() == NONPLAYER){
		PC->attack(dynamic_cast<NonPlayer *>(realMap[new_x][new_y]->getObserver()));
		setPlayerObservers();
		PC->notice_nearby();
		NPC_action();
		return true;
	} return false;
}


void Map::setPlayerObservers(){
	PC->resetObjNo();
	PC->setObserver(realMap[PC_x + 1][PC_y]->getObserver());
	PC->setObserver(realMap[PC_x - 1][PC_y]->getObserver());
	PC->setObserver(realMap[PC_x][PC_y + 1]->getObserver());
	PC->setObserver(realMap[PC_x][PC_y - 1]->getObserver());
	PC->setObserver(realMap[PC_x + 1][PC_y - 1]->getObserver());
	PC->setObserver(realMap[PC_x + 1][PC_y + 1]->getObserver());
	PC->setObserver(realMap[PC_x - 1][PC_y - 1]->getObserver());
	PC->setObserver(realMap[PC_x - 1][PC_y + 1]->getObserver());
}

bool Map::isPCDead() { if (PC->isDead()){ floorNo = 1; linesbeRead = 0; return true;} else return false; }

// NPC part

void Map::sortPosArray() {
	for (int i = 0; i < nonPlayerNo; ++i){
		for (int j = 0; j < nonPlayerNo - 1; ++j){
			if (nonPlayerPosArray[1][j] > nonPlayerPosArray[1][j+1]){
				int tempX = nonPlayerPosArray[0][j];
				int tempY = nonPlayerPosArray[1][j];
				nonPlayerPosArray[0][j] = nonPlayerPosArray[0][j + 1];
				nonPlayerPosArray[1][j] = nonPlayerPosArray[1][j + 1];
				nonPlayerPosArray[0][j + 1] = tempX;
				nonPlayerPosArray[1][j + 1] = tempY;
			}
		}
	}
	for (int i = 0; i < nonPlayerNo; ++i){
		for (int j = 0; j < nonPlayerNo - 1; ++j){
			if (nonPlayerPosArray[1][j] == nonPlayerPosArray[1][j + 1]){
				if (nonPlayerPosArray[0][j] > nonPlayerPosArray[0][j + 1]){
					int tempX = nonPlayerPosArray[0][j];
					int tempY = nonPlayerPosArray[1][j];
					nonPlayerPosArray[0][j] = nonPlayerPosArray[0][j + 1];
					nonPlayerPosArray[1][j] = nonPlayerPosArray[1][j + 1];
					nonPlayerPosArray[0][j + 1] = tempX;
					nonPlayerPosArray[1][j + 1] = tempY;
				}
			}
		}
	}
}


int Map::moveDirection (int x, int y){
	//srand(time(NULL) + x);
	int new_x,new_y;
	int d = 0;
	do{
		new_x = x;
		new_y = y;
		d = rand() % 9;
		if (d == 0){ new_y -= 1; }
		else if (d == 1) { new_y += 1; }
		else if (d == 2) { new_x += 1; }
		else if (d == 3) { new_x -= 1; }
		else if (d == 4) { new_y -= 1; new_x -= 1; }
		else if (d == 5) { new_y -= 1; new_x += 1; }
		else if (d == 6) { new_y += 1; new_x -= 1; }
		else if (d == 7) { new_y += 1; new_x += 1; }
		else if (d == 8) { break; }
	}while (!realMap[new_x][new_y]->canBeSteppedOnByNonPlayer());
	//cout << realMap[new_x][new_y]->canBeSteppedOnByNonPlayer() << endl;
	return d;
}

void Map::NPC_action(){
	for (int i = 0; i < nonPlayerNo; i++){
		//cout << i << "sssssssssssssss" << endl;
		int x = nonPlayerPosArray[0][i];
		int y = nonPlayerPosArray[1][i];
		if (x == -1 && y == -1) continue;
		if ((dynamic_cast<NonPlayer *> (realMap[x][y]->getObserver()))->isDone()){
			if (dynamic_cast<Merchant *> (realMap[x][y]->getObserver())){
				realMap[x][y]->resetRoom();
				realMap[x][y]->setObserver(new Gold{nullptr, 4});
				realMap[x][y]->setMapUnitStatus(GOLD);
			} else
				realMap[x][y]->resetRoom();
			nonPlayerPosArray[0][i] = -1;
			nonPlayerPosArray[1][i] = -1;
			continue;
		}
		bool canBeMove = (dynamic_cast<NonPlayer *> (realMap[x][y]->getObserver()))->getCanBeMove();
		bool attackPC = (dynamic_cast<NonPlayer *> (realMap[x][y]->getObserver()))->getAttackPC();
		if (attackPC){
			(dynamic_cast<NonPlayer *> (realMap[x][y]->getObserver()))->attack();}
		else if (canBeMove){
			int d = moveDirection(x,y);
			int new_x = x;
 			int new_y = y;
			if (d == 0){ new_y -= 1; }
			else if (d == 1) { new_y += 1; }
			else if (d == 2) { new_x += 1; }
			else if (d == 3) { new_x -= 1; }
			else if (d == 4) { new_y -= 1; new_x -= 1; }
			else if (d == 5) { new_y -= 1; new_x += 1; }
			else if (d == 6) { new_y += 1; new_x -= 1; }
			else if (d == 7) { new_y += 1; new_x += 1; }
			realMap[new_x][new_y]->setObserver(realMap[x][y]->getObserver());
			realMap[x][y]->setMapUnitStatus(EMPTY);
			if(d!=8) realMap[x][y]->setObserver(nullptr);
			realMap[new_x][new_y]->setMapUnitStatus(NONPLAYER);
			nonPlayerPosArray[0][i] = new_x; 
			nonPlayerPosArray[1][i] = new_y;
		}
	}
}

// floor part
void Map::clearMap(){
	for (int i = 0; i < 25; i++){
		for (int j = 0; j < 79; j++){
			realMap[j][i]->resetRoom();
		}
	}
}
			
void Map::gotoNextFloor (){
	if (floorNo == 6) return;
	gNo = 0;
	clearMap ();
	PC->pickGold(5);
	if (loaded) {initMap(); return;}	
	// action : congrats you come to the xth floor
	generateElse();
	generatePotion();
	generateGold();
	generateNonPlayer();
}
	
bool Map::isWin() { if (floorNo == 6){ floorNo = 1; linesbeRead = 0; return true;} return false; }

// summary part

void Map::deadMsg(std::ostream& out){
	out << "Ha Ha Ha, you are too weak" << endl;
	out << "                      ----- an anonymous monster from the 5 floor"  << std::endl;
	out << "So your total score is ..." << endl;
	out << "Segmentation fault (core dumped)..." << endl;
	usleep(5000000);
	int score = PC->getPocket();
	if (PC->getRace() == 'H') score *= 1.5;
	out << "I am kidding, your score is: " << score << std::endl;
}

void Map::winMsg(std::ostream& out){
	out << "Finally, you win!" << std::endl;
	out << "So your total score is ..." << std::endl;
	out << "Segmentation fault (core dumped)..." << std::endl;
	usleep(5000000);
	int score = PC->getPocket();
	if (PC->getRace() == 'H') score *= 1.5;
	out << "I am kidding, your score is: " << score << std::endl;
}

