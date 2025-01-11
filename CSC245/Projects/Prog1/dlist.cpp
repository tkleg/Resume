#include <cstddef> 
#include <iostream>

using namespace std;

//double Average();

template<class ItemType>
struct NodeType
{
	ItemType info;
	NodeType<int>*	next;
	NodeType<int>*	back;
};

//template<class ItemType>
//typedef NodeType<int>* NodePtr;
/*template<class ItemType>
double DList<ItemType>::Average(){
	NodeType<int>* n = head;
	double total = 0;
	while( n != NULL ){
		total += n -> info;
		n = n -> next;
	}
	double average = total / lengthIs();
	return ( (int) (total * 100000 ) ) / 100000.0;
}*/ 

template <class ItemType>		
DList<ItemType>::DList()		// Class constructor
{
    length = 0;
    head = NULL;
}

template <class ItemType>
DList<ItemType>::~DList   ()		
{
/*	// Post: list is empty; All items have been deallocated.
        NodeType<int>*  n = head;
	if( n == NULL ){
		delete n;
		n = NULL;
		return;
	}	
	NodeType<int>* nextNode;
        while( n  != NULL ){
		nextNode = n -> next;
                delete n;
                n = NULL;
                n = nextNode;
        }
        head = NULL;	*/
}

template <class ItemType>
void DList<ItemType>::makeEmpty()
{
    // Post: List is empty; all items have been deallocated.
	length = 0;
	NodeType<int>*  n = head;
        if( n == NULL ){
                delete n;
                n = NULL;
                return;
        }
        NodeType<int>* nextNode;
        while( n  != NULL ){
                nextNode = n -> next;
                delete n;
                n = NULL;
                n = nextNode;
        }
        head = NULL;

}

template <class ItemType>
void DList<ItemType>::deleteItem (ItemType item)	
{
	//  Pre :  item to be deleted is passed in via parameter 
        // Post :  item is deleted if it exists in list 
	NodeType<int>* n = head;
	while( n != NULL ){
		if( n -> info == item ){
			if( n == head ){
				n -> next -> back = NULL;
				head = n -> next;
			}	
			else if( n == last() )
				n -> back -> next = NULL;
			else{
				n -> back -> next = n -> next;
				n -> next -> back = n -> back;
			}
			delete n;
			n = NULL;
			length--;
			return;
		}
		n = n -> next;
	}


}

template <class ItemType>
bool DList<ItemType>::inList (ItemType item) const
{
	//  Pre :  item to be located is passed in via parameter 
        // Post :  function returns bool value if item is found 
	NodeType<int>* n = last();
	while( n != NULL ){
		if( n -> info == item )
			return true;
		n = n -> back;
	}
	return false;


}

template <class ItemType>
bool DList<ItemType>::isEmpty() const		
{
	// Post : function returns true if list is empty, false otherwise
	return head == NULL;	
}

template <class ItemType>
void DList<ItemType>::print() const	
{
	// Pre  : List is not empty 
	// Post : Items in List have been printed to screen
	NodeType<int>* n = head;
	while( n != NULL ){
		cout << n -> info << "  ";
		n = n -> next;
	}
	cout << endl;	

}
	
template <class ItemType>
void DList<ItemType>::insertHead(ItemType item)	
{
	//  Pre : item to be inserted is passed in via parameter
        // Post : item is inserted at head of list;  Former first node is 
        //        linked back to this new one via double link;
        //        Length incremented;  Special case handled if list is empty 
	NodeType<int>* newNode = new NodeType<int>;
	newNode -> info = item;
	newNode -> back = NULL;
	length++;
	if( head == NULL )
		newNode -> next = NULL;	
	else{
		head -> back = newNode;
		newNode -> next = head;
	}
	head = newNode;
}

template <class ItemType>
void DList<ItemType>::appendTail(ItemType item)
{
	//  Pre :  item to be inserted is passed in via parameter
        // Post :  item is added to tail of list; Former last node
        //         is linked to this new one via double link 
	NodeType<int>* newNode = new NodeType<int>;
	newNode -> next = NULL;
	newNode -> info = item;
	length++;
	if( head == NULL ){
		head = newNode;
		newNode -> back = NULL;
	}
	else
		newNode -> back = last();
	if( newNode -> back != NULL )
		newNode -> back -> next = newNode;
}

template <class ItemType>
int DList<ItemType>::lengthIs() const	
{
	// Post : Function returns current length of list
	return length;  
}

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::location(ItemType item) const	
{
	//  Pre : item to be located is passed in via parameter 
        // Post : function returns address of item being searched for --
        //        if not found, NULL is returned  
	NodeType<int>* n = head;
	while( n != NULL )
		if( n -> info == item )
			return n;
	return NULL;	
}

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::last() const	
{
	// Post : Function returns location of current last item in list
	NodeType<int>* n = head;
	if( n == NULL )
		return n;
	while( n -> next != NULL )
		n = n -> next;
	return n;	
}

template <class ItemType>
void DList<ItemType>::deleteLocation (NodeType<ItemType>* delPtr)	
{

	//  Pre : Item to be deleted exits in list and its location
        //        is passed in via parameter
                   
	// Post : Location passed in is removed from list;  Length
        //        is decremented, and location is deallocated 

        // Special Cases Handled for Deleting Only One Item in List,
        // The Head Item of List, and the Tail Item of List
	NodeType<int>* n = head;
	while( n != NULL ){
		if( n == delPtr ){
      if( n == head ){
         n -> next -> back = NULL;
         head = n -> next;
      }
      else if( n == this.last() )
        n -> back -> next = NULL;
      else{
        n -> back -> next = NULL;
        n -> next -> back = NULL;
        }
        delete n;
        n = NULL;
        length++;
			return;
                }
                n = n -> next;

	}

}
