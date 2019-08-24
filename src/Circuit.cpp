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
    //printf("%d::::", maxIndex + 1);
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


void Circuit::removeComponentAt(int index){
    //requires a smooth transfer of component connections
    Component *tmp = getComponentAt(index);
    int exitCount = tmp->getExitComponents().count;
    int entryCount = tmp->getEntryComponents().count;
    Component **oldExitConnectors = tmp->getExitComponents().components;
    Component **oldEntryConnectors = tmp->getEntryComponents().components;
    for (int i = 0; i != exitCount; i++){
        oldExitConnectors[i]->disconnectComponentFromEntry(tmp);
        for (int j = 0; j != entryCount; j++){
            oldEntryConnectors[j]->disconnectComponentFromExit(tmp);
            oldEntryConnectors[j]->connectComponentToExit(oldExitConnectors[i]);
            oldExitConnectors[i]->connectComponentToEntry(oldEntryConnectors[j]);
        }
    }

    delete tmp;
}
