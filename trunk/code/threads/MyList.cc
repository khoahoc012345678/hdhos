 
 #include "copyright.h"
 #include "MyList.h"
 void* MyList::GetElement (int index)
 {
	 void *thing;
	 if (IsEmpty()) 
		 return NULL;
	 
	 ListElement *element = this->Getfirst();
	 thing = element->item;
	 
	 for (int i = 0; i < index; i++)
	 {
		 element = element->next;
		 if (element != NULL)
			 thing = element->item;	
	 }
	 if (element == NULL)
		 return NULL;
	 //delete element;
	 return thing;
 }
 void* MyList::RemoveIndex (int index)
 {
	 if (IsEmpty()) 
		 return NULL;
	 
	 void *thing;
	 ListElement *element = this->Getfirst();
	 ListElement *q = NULL;
	 
	 for (int i = 0; i < index; i++)
	 {
		 if (element != NULL)
		 {
			 q = element;
			 element = element->next;
		 }
	 }
	 if (element == NULL)
		 return NULL;
	 if (q != NULL)
	 {
		 thing = element->item;
		 if (element == this->Getlast())
			 this->Setlast(q);
		 q->next = element->next;		
		 delete element; 
	 }
	 else
	 {
		 thing = element->item;
		 this->Setfirst(element->next);
		 if (this->Getfirst() == NULL)
			 this->Setlast (NULL);
	 }
	 
	 return thing;
 }
 