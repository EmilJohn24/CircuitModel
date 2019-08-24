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
        void newCircuit(char *filename);
        void loadCircuit(char *filename);
        void addComponentInMarkedPoint(Component *_component, int numberMarker);
        Component* adderExplorer(Component *_component, Component *_previousLayer, int numberMarker);
        void mainMenuChoiceHandler(int choice);
        void recentFileMenu();
        void changePropertyOfComponentAt(int index, double property);
        void adjustMenu();
        void adderMenu();
        void deleteMenu();
        void removeComponentAt(int index);
        virtual ~Manager();
        void everythingMenu();
        void runEverything(); //not a very good name but an endearing one


    protected:

    private:
        FILE *log;
        FILE *recentFile;
        int nodeTracker;
        Graphic *graphics;
        Circuit *circuit;
        CircuitFileParser *bridge; //bridge between a save file and the circuit
};

#endif // MANAGER_H
