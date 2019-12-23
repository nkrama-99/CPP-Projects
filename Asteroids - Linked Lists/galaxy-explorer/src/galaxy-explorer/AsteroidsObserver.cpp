/*
 * This file was developed for the Fall 2018 instance of ECE244 at the University of Toronto.
 * Creator: Matthew J. P. Walker
 */

/*
 * NOTES:
 * Methods implemented must manipulate the AsteroidList pointed by asteroid_list
 */

#include <galaxy-explorer/AsteroidsObserver.hpp>

// called when a new asteroid appears - add asteroid at the back of the list
void AsteroidsObserver::onAsteroidInRange(Asteroid asteroid) {
    asteroid_list.insertAfter(asteroid_list.beforeEnd(), asteroid);
}

// called when asteroid has moved (use id to determine what asteroid to replace)
// asteroid ID does not change, but other info changes.
// so delete and add back the asteroid with updated info
void AsteroidsObserver::onAsteroidUpdate(Asteroid asteroid) {
    AsteroidListItem* updateItemAfter; //is the pointer which needs to be passed to eraseAfter
    AsteroidListItem* updateItem; //points to item which needs to be delete - in order to getdata() and compare id with asteroid

    for (updateItemAfter = asteroid_list.beforeBegin(); (*updateItemAfter).hasNext(); updateItemAfter = (*updateItemAfter).getNext()) {
        updateItem = (*updateItemAfter).getNext();
        if (((*updateItem).getData()).getID() == asteroid.getID()) { //invoke function if ID match & break loop
            asteroid_list.eraseAfter(updateItemAfter);
            asteroid_list.insertAfter(updateItemAfter, asteroid);
            break;
        }
    }
}

// called when asteroid leave field without destroyed - delete the item
void AsteroidsObserver::onAsteroidOutOfRange(Asteroid asteroid) {
    AsteroidListItem* deleteItemAfter; //is the pointer which needs to be passed to eraseAfter
    AsteroidListItem* deleteItem; //points to item which needs to be delete - in order to getdata() and compare id with asteroid

    for (deleteItemAfter = asteroid_list.beforeBegin(); (*deleteItemAfter).hasNext(); deleteItemAfter = (*deleteItemAfter).getNext()) {
        deleteItem = (*deleteItemAfter).getNext();
        if (((*deleteItem).getData()).getID() == asteroid.getID()) { //invoke function if ID match & break loop
            asteroid_list.eraseAfter(deleteItemAfter);
            break;
        }
    }
}

// called whenasteroid destroyed by shot - delete the item
void AsteroidsObserver::onAsteroidDestroy(Asteroid asteroid) {
    AsteroidListItem* deleteItemAfter; //is the pointer which needs to be passed to eraseAfter
    AsteroidListItem* deleteItem; //points to item which needs to be delete - in order to getdata() and compare id with asteroid

    for (deleteItemAfter = asteroid_list.beforeBegin(); (*deleteItemAfter).hasNext(); deleteItemAfter = (*deleteItemAfter).getNext()) {
        deleteItem = (*deleteItemAfter).getNext();
        if (((*deleteItem).getData()).getID() == asteroid.getID()) { //invoke function if ID match & break loop
            asteroid_list.eraseAfter(deleteItemAfter);
            break;
        }
    }
}
