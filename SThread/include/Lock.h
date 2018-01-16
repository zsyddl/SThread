
#ifndef LOCK_H
#define LOCK_H

namespace SThread{

class CLock
{
public:
	CLock(void);
	virtual ~CLock(void);
	bool Lock();
	void Unlock();
	bool TryLock(long lTimeOut);

protected:

};
}


#endif