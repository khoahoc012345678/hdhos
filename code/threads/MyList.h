
#ifndef MYLIST_H
#define MYLIST_H

#include "copyright.h"
#include "utility.h"
#include "list.h"

class MyList :public List{
public:
	
	void* GetElement (int index);
	void* RemoveIndex (int index);
	
};

#endif // LIST_H