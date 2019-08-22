#include "Circuit.h"

Circuit::Circuit()
{
    //ctor
    componentArray = (Component **) malloc(sizeof(Component*) * COMPONENT_LIMIT);
}

Circuit::~Circuit()
{
    //dtor
}

void Circuit::addComponent(Component* _component, int index, int adjacencyIndex){
    if (index == 1) rootComponent = _component;
    Component *explorer = rootComponent;
    componentArray[index] = _component;
    if (adjacencyIndex != 0){
        Component *adjacentComponent = componentArray[adjacencyIndex];
        adjacentComponent->connectComponentToExit(_component);
        _component->connectComponentToEntry(adjacentComponent);
    }

};
