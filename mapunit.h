#ifndef _MAPUNIT_H_
#define _MAPUNIT_H_

#include "observer.h"

enum MapUnitStatus {EMPTY, POTION, GOLD, SOLID, NONPLAYER, PLAYER, STAIR, DOP};

class MapUnit {
	Observer* obs;
	MapUnitStatus mus;
protected:
	int roomNo;
public:
	MapUnit(int roomNo, MapUnitStatus mus);
	Observer* getObserver ();
	int getRoomNo();
	void setObserver (Observer* obs);
	void setMapUnitStatus (MapUnitStatus mus);
	MapUnitStatus getMapUnitStatus ();
	bool canBeSteppedOnByPlayer();
	bool canBeSteppedOnByNonPlayer();
	void resetRoom();
	virtual void setRoomNo(int n);
	virtual char getTypeID() = 0;
	virtual MapUnitStatus getOriginMUS ();
	virtual ~MapUnit();
};

class Horizontal_Wall: public MapUnit {
public:
	Horizontal_Wall();
	char getTypeID() override;
};

class Vertical_Wall: public MapUnit {
public:
	Vertical_Wall();
	char getTypeID() override;
};

class Room: public MapUnit {
public:
	Room();
	void setRoomNo(int n) override;
	char getTypeID() override;
};

class Door: public MapUnit {
public:
	Door();
	MapUnitStatus getOriginMUS () override;
	char getTypeID() override;
};

class Path: public MapUnit {
public:
	Path();
	MapUnitStatus getOriginMUS () override;
	char getTypeID() override;
};

class Null: public MapUnit {
public:
	Null();
	char getTypeID() override;
};


#endif
