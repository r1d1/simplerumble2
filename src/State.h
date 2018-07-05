#include <iostream>
#include <string>

#include "Entity.h"

class State
{
    public:
        std::string name_;

        virtual ~State(){}
        virtual void handleInput(input){}
        virtual void update(){}
        
};

class FiniteSM
{
    
    State * current_
};
