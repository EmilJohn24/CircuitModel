#ifndef CIRCUIT_H
#define CIRCUIT_H
#include "Component.h"

class Circuit
{
    public:
        static const int COMPONENT_LIMIT = 100;
        Circuit();
        virtual ~Circuit();
        Component *getRootComponent(){ return rootComponent; };
        Component **getComponentArray() { return componentArray; };
        Component *getComponentAt(int index) { return componentArray[index]; };
        void addComponent(Component* _component, int index, int adjacencyIndex);
        void addComponent(Component* _component, Component* adjacentComponent);
        void removeComponentAt(int index);

    protected:

    private:
        Component *rootComponent; //tree structure
        Component **componentArray; //direct random-access array
        int maxIndex; //stores the highest index stored
};

#endif // CIRCUIT_H
