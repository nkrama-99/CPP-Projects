#include <galaxy-explorer/AsteroidList.hpp>


AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
	this->next = nullptr;
	this->data = new Asteroid(a.getID(), a.getMass(), a.getHealth(), a.getCurrentHitbox(), a.getVelocity()); //since data is a Asteroid ptr
}

AsteroidListItem::~AsteroidListItem() {
	if (data != nullptr) {
		delete data;
		data = nullptr;
		next = nullptr;
	}
}

AsteroidList::AsteroidList() { //creates an empty list
}

AsteroidList::AsteroidList(const AsteroidList& src)
{
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the destructor (because you should put all your constructors together).
	const AsteroidListItem* src_ptr;
	AsteroidListItem* new_ptr = nullptr;
	AsteroidListItem* last = nullptr;

	src_ptr = src.begin();

	while (src_ptr != nullptr) {
		new_ptr = new AsteroidListItem((*src_ptr).getData());
		if (last == nullptr) 
			head.setNext(new_ptr);
		else 
			(*last).setNext(new_ptr);
		
		src_ptr = (*src_ptr).getNext();
		last = new_ptr;
	}
}

AsteroidList::~AsteroidList() {
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
	clear();
}

void AsteroidList::pushFront(Asteroid e) {
	AsteroidListItem* temp = new AsteroidListItem(e); //dynamic variable temp

	(*temp).setNext(head.getNext()); //first, temp->next points to head->next
	head.setNext(temp); //then, head->next points to temp
}

Asteroid& AsteroidList::front() {
	AsteroidListItem* ptr = beforeBegin(); //ptr points to head
	if (head.hasNext()) { //if list is not empty
		ptr = (*ptr).getNext();
		return ((*ptr).getData()); //return data from first listItem
	} else { //if list is empty
		return *(Asteroid*)nullptr;
	}
}

const Asteroid& AsteroidList::front() const {
	const AsteroidListItem* ptr = beforeBegin(); //ptr points to head
	if (head.hasNext()) { //if list is not empty
		ptr = (*ptr).getNext();
		return ((*ptr).getData()); //return data from first listItem
	} else { //if list is empty
		return *(const Asteroid*)nullptr;
	}
}

bool AsteroidList::isEmpty() const {
	if (head.hasNext()) //if head->next is NOT pointing to null, meaning the list is NOT empty
		return false;
	else
		return true;
}

int AsteroidList::size() const {
	int counter = 0;
	const AsteroidListItem* ptr;
	for (ptr = beforeBegin(); (*ptr).hasNext(); ptr=(*ptr).getNext()) {
		counter++;
	}
	return counter;
}

// return item before first asteroid
AsteroidListItem* AsteroidList::beforeBegin() {
	return &head;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
	return &head;
}

// return item with first asteroid
AsteroidListItem* AsteroidList::begin() {
	return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
	return head.getNext();
}

// return item with last asteroid
AsteroidListItem* AsteroidList::beforeEnd() {
	AsteroidListItem* listItem_ptr = beforeBegin(); //initiate ptr with head->next

	while ((*listItem_ptr).hasNext()) { //traverse ptr: if ptr->next is null, exit loop 
		listItem_ptr = (*listItem_ptr).getNext();
	}

	return listItem_ptr;
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
	const AsteroidListItem* listItem_ptr = beforeBegin(); //initiate ptr with head->next

	while ((*listItem_ptr).hasNext()) { //traverse ptr: if ptr->next is null, exit loop 
		listItem_ptr = (*listItem_ptr).getNext();
	}

	return listItem_ptr;
}

// return item after last asteroid - which is NULL
AsteroidListItem* AsteroidList::end() {
	return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
	return nullptr;
}

// add listitem with asteroid e, after prev
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
	AsteroidListItem* newListItem = new AsteroidListItem(e); //dynamically allocate listitem with asteroid e

	(*newListItem).setNext((*prev).getNext()); //first, newitem->next points to prev->next
	(*prev).setNext(newListItem); //then, prev->next points to newitem

	return newListItem;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* insertion_point, const AsteroidList& others) {
	AsteroidList* listToAdd = new AsteroidList(others);
	
	AsteroidListItem* temp; //temp backs up what is after insertion_point
	AsteroidListItem* firstItem; //first item of others
	AsteroidListItem* lastItem; //last item of others

	temp = (*insertion_point).getNext();
	firstItem = (*listToAdd).begin();
	lastItem = (*listToAdd).beforeEnd();

	(*insertion_point).setNext(firstItem); //insert other list
	(*lastItem).setNext(temp); //insert backed up items
}

// erase the listitem after prev
AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
	if (!((*prev).hasNext())) //if after prev is nullptr
		return nullptr;

	AsteroidListItem* temp; //temp stores the next of the item to be deleted
	AsteroidListItem* itemToDelete; //item to be deleted
	itemToDelete = (*prev).getNext(); 
	temp = (*itemToDelete).getNext(); 

	delete itemToDelete; //DO I NEED TO DELETE data POINTER which is within item?
	(*prev).setNext(temp); //prev now points to temp(next of deleted item)
	
	return (*prev).getNext(); //return
}

void AsteroidList::clear() {
	AsteroidListItem* itemToDelete;
	itemToDelete = beforeBegin();
	
	while (head.hasNext()) {
		itemToDelete = head.getNext(); //mark item to delete
		head.setNext((*itemToDelete).getNext()); //connect head to next of item to delete
		delete itemToDelete;
	}

	head.setNext(nullptr);
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
	clear();
	
	const AsteroidListItem* src_ptr;
	AsteroidListItem* new_ptr = nullptr;
	AsteroidListItem* last = nullptr;

	src_ptr = src.begin();

	while (src_ptr != nullptr) {
		new_ptr = new AsteroidListItem((*src_ptr).getData());
		if (last == nullptr) 
			head.setNext(new_ptr);
		else 
			(*last).setNext(new_ptr);
		
		src_ptr = (*src_ptr).getNext();
		last = new_ptr;
	}

	return (*this);
}
