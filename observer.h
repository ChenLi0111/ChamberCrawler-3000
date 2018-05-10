#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <string>

class Observer {
protected:
	std::string action = "";
public:
	Observer();
	virtual char getTypeID() = 0;
	virtual bool isDone() = 0;
	virtual void be_notified_nearby () = 0;
	virtual void notice_dragon_dead();
	virtual bool canBeSteppedOn() = 0;
	virtual std::string getAction() = 0;
	virtual void be_notified_leave () = 0;
	virtual ~Observer();
};

#endif
