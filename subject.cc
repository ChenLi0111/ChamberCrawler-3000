#include "subject.h"

Subject::Subject(): objNo{0} {}

void Subject::setObserver(Observer* obs){
	if(obs){
		observer_nearby[objNo] = obs;
		objNo++;
	}
}

int Subject::getObjNo() { return objNo; }

void Subject::resetObjNo() { objNo = 0; }
