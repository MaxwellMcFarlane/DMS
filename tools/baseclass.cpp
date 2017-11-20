#include "baseclass.h"

// Initialize the static variable that tracks
// number of objects created.
int baseclass::idCnt = 0;

baseclass::baseclass()
{
    // Uniquely identify the object.
    id = idCnt;

    // Increment the created object count.
    idCnt++;

}
