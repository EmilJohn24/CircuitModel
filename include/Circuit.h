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
        void addComponent(Component* _component, int index, int adjacencyIndex);

    protected:

    private:
        Component *rootComponent; //tree structure
        Component **componentArray; //direct random-access array
};

#endif // CIRCUIT_H
