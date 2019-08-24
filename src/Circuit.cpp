#include "Circuit.h"
#include <stdio.h>
Circuit::Circuit()
{
    //ctor
    componentArray = (Component **) malloc(sizeof(Component*) * COMPONENT_LIMIT);
    maxIndex = 0;
}

Circuit::~Circuit()
{
    //dtor
}

void Circuit::addComponent(Component* _component, Component* adjacentComponent){
    printf("%d::::", maxIndex + 1);
    addComponent(_component, maxIndex + 1, adjacentComponent->getReferenceIndex());
}

void Circuit::addComponent(Component* _component, int index, int adjacencyIndex){
    if (index == 1) rootComponent = _component;
    Component *explorer = rootComponent;
    componentArray[index] = _component;
    _component ->setReferenceIndex(index);
    if (index > maxIndex) maxIndex = index;
    if (adjacencyIndex != 0){
        Component *adjacentComponent = componentArray[adjacencyIndex];
        adjacentComponent->connectComponentToExit(_component);
        _component->connectComponentToEntry(adjacentComponent);
    }

};
