#include <iostream>
#include <vector>
#include "Entity.h"

/*
 * *class to manage items
 * - add, remove items
 * - printout list
 * - can be displayed
 * - save to log
 *
 * */

class Inventory
{
    private:
        std::vector<std::pair<Entity *, int> > itemList;

    public:
        Inventory();
        ~Inventory();
        void add(Entity & e);
        void remove(Entity & e);
};
