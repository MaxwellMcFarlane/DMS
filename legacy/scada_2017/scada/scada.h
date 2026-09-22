#ifndef SCADA_H
#define SCADA_H

#include "../DMS/dms.h"
#include "../DMS/table.h"

class Scada
{
public:
    Scada ();
    Scada (string database_file);
};

#endif // SCADA_H
