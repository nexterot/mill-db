#ifndef PROJECT_COLUMN_H
#define PROJECT_COLUMN_H

#include <string>
#include <iostream>
#include <map>
#include "DataType.h"

class Column {
public:
    Column(std::string name, DataType *type, bool pk);

    ~Column();

    std::string get_name();

    DataType *get_type();

    bool get_pk();

private:
    std::string name;
    DataType *type;
    bool pk;
};


#endif //PROJECT_COLUMN_H
