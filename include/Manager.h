#ifndef MANAGER_H
#define MANAGER_H
#include <stdio.h>
#include "components.h"
#include "Circuit.h"
#include "Graphic.h"
#include "CircuitFileParser.h"
class Manager
{
    public:
        Manager();
        void mainMenu();
        virtual ~Manager();


    protected:

    private:
        Graphic *graphics;
        Circuit *circuit;
        CircuitFileParser *bridge; //bridge between a save file and the circuit
};

#endif // MANAGER_H
