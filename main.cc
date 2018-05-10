#include "map.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;


Direction to_direction(string str){
	if(str.compare("no")==0){
		return NO;
	}else if(str.compare("so")==0){
		return SO;
	}else if(str.compare("ea")==0){
		return EA;
	}else if(str.compare("we")==0){
		return WE;
	}else if(str.compare("nw")==0){
		return NW;
	}else if(str.compare("ne")==0){
		return NE;
	}else if(str.compare("sw")==0){
		return SW;
	}else if(str.compare("se")==0){
		return SE;
	}
	throw 1;
}

int main(int argc,char *argv[]){
	if(argc>2){cerr<<"invalid usage" << endl; return 1;}
	Map *game_ptr=0;
	string str;
	char c;

	do{	
		if(argc==2){game_ptr=new Map(10,20,10,argv[1]);}
		else{game_ptr=new Map(10,20,10,"initmap.txt");}
		Map &game=*game_ptr;
		srand(3); //time(NULL)
		game.initMap();
		game.printMap(cout);
		if(!game.isLoad()){
			cout << endl << "Choose from following: (h,o,d,e)" << endl;
			cout << "Human:  | Dwarf:  | Elves:  | Orc: " << endl;
			cout << "HP: 140 | HP: 100 | HP: 140 | HP: 180" << endl;
			cout << "ATK: 20 | ATK: 20 | ATK: 30 | ATK: 30" << endl;
			cout << "DEF: 20 | DEF: 30 | DEF: 10 | DEF: 25" << endl;
			cout << "============================================" << endl;
			while(cin.good()){
				cin >> c;
				getline(cin,str);
				if(c=='h'||c=='o'||c=='d'||c=='e'){
					game.initPC(c);
					cout << endl;
					break;
				}
				cout << "invalid. Choose a race(h,o,d,e): " << endl;		
			}
			game.printMap(cout);
		}
			
		game.printInfo(cout);
		cout << "Action: PC is spawned" << endl;
		while(cin.good()){
			if (game.isPCDead()){ game.deadMsg(cout); break; }
			if (game.isWin()){ game.winMsg(cout); break; }
			cout << "Direction: no, so, ea, we, nw, sw, ne, se." << endl;
			cout << "Enter a command (move: Direction,attack: a Direction,use: u Direction,restart: r, quit: q):"<<endl;
			cin >> str;
			if (str.compare ("q") ==0 ) {
				cout<< "do you want to quit the game?(y/n):";
				while(cin.good()){
					cin >> c;
					getline(cin,str);
					if(c=='n'||c=='N'||c=='Y'||c=='y') break;
					cout << "invalid. " << endl <<"do you want to quit the game?(y/n):";
				}
				if(c=='y'||c=='Y') goto quitGame;
			}else if(str.compare("r")==0){
				cout<< "do you want to restart the game?(y/n):";
				while(cin.good()){
					cin >> c;
					getline(cin,str);
					if(c=='n'||c=='N'||c=='Y'||c=='y') break;
					cout << "invalid. " << endl <<"do you want to restart the game?(y/n):";
				}
				if(c=='y'||c=='Y') break;
			}else if(str.compare("a")==0){
				cin >> str;
				try{ if(!game.player_attack(to_direction(str))) throw 1;
					game.printMap(cout);
					game.printInfo(cout);
					game.printAction(cout); }
				catch(...){ cout<<"invalid."<<endl;}
			}else if(str.compare("u")==0){
				cin >> str;
				try{ if(!game.player_use(to_direction(str))) throw 1;
					game.printMap(cout);
					game.printInfo(cout);
					game.printAction(cout); }
				catch(...){ cout<<"invalid."<<endl;}
			}else{
				try{ if(!game.player_move(to_direction(str))) throw 1;
					game.printMap(cout);
					game.printInfo(cout);
					game.printAction(cout); }
				catch(...){ cout<<"invalid."<<endl;}
			}
			//getline(cin,str);
		}
		delete game_ptr;game_ptr=0;
		if(!cin.good()) break;
		cout<< "do you want to play again?(y/n):";
		while(cin.good()){
			cin >> c;
			getline(cin,str);
			if(c=='n'||c=='N'||c=='Y'||c=='y') break;
			cout << "invalid. " << endl <<"do you want to play again?(y/n):";
		}
		if(c=='n'||c=='N') break;
		
	}while(1);
	quitGame: 
	delete game_ptr;
	
}
