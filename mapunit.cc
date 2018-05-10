#include "mapunit.h"

MapUnit::MapUnit(int roomNo, MapUnitStatus mus):
	obs{nullptr}, mus{mus}, roomNo{roomNo}  {}

Observer* MapUnit::getObserver(){ return obs; }

void MapUnit::setObserver (Observer* obs){ this->obs = obs; }

void MapUnit::setMapUnitStatus (MapUnitStatus mus) { this->mus = mus; }

MapUnitStatus MapUnit::getOriginMUS() { return EMPTY; }

MapUnitStatus MapUnit::getMapUnitStatus () { return mus; }

bool MapUnit::canBeSteppedOnByPlayer(){
	if (mus == EMPTY || mus == DOP || mus == STAIR)
		return true;
	if (mus == GOLD)
		return (obs->canBeSteppedOn());
	return false;
}

bool MapUnit::canBeSteppedOnByNonPlayer(){
	return (mus == EMPTY);
}

void MapUnit::resetRoom(){
	if (mus != SOLID && mus != DOP && mus != PLAYER) mus = EMPTY;
	delete obs;
	obs = nullptr;
}

void MapUnit::setRoomNo(int n){}

int MapUnit::getRoomNo() { return roomNo; }

MapUnit::~MapUnit() { delete obs; };

// Horizontal_Wall class

Horizontal_Wall::Horizontal_Wall():
	MapUnit (-1,SOLID) {}

char Horizontal_Wall::getTypeID() { return '-'; }

// Vertical_Wall class

Vertical_Wall::Vertical_Wall():
	MapUnit (-1,SOLID) {}

char Vertical_Wall::getTypeID() { return '|'; }

// Room class

Room::Room(): MapUnit (0, EMPTY) {}

void Room::setRoomNo(int n){if(n>0) roomNo=n;}

char Room::getTypeID(){ return '.'; }

// Door class

Door::Door(): MapUnit(-1,DOP) {}

MapUnitStatus Door::getOriginMUS() { return DOP; }

char Door::getTypeID() { return '+'; }

// Path class

Path::Path(): MapUnit(-1,DOP) {}

MapUnitStatus Path::getOriginMUS() {return DOP; }

char Path::getTypeID() { return '#'; }

// Null class

Null::Null(): MapUnit(-1,SOLID) {}

char Null::getTypeID() { return ' '; }


	

