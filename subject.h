#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "observer.h"

class Subject {
	int objNo;
protected:
	Observer* observer_nearby[8];
public:
	Subject();
	void setObserver(Observer* obs);
	int getObjNo();
	void resetObjNo();
	virtual void notice_nearby() = 0;
	virtual void notice_leave() = 0;
};
#endif
