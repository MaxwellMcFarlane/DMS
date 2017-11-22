#ifndef DMSWD_H
#define DMSWD_H
#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <vector>
#include "table.h"
/**
 * @brief The DMSWD class:This class is a watchdog class that watches the amount of accesses into a specifed table
 * then according to a flag will perform an action onto a specified database table.
 */
class DMSWD
{
public:
    DMSWD();
};

#endif // DMSWD_H
