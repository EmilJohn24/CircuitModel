#include "CircuitTraverser.h"

Component *CircuitTraverser::excavate(){
    if (excavationIndex < explorer->getExitComponents().count){
            return explorer->getExitComponents().components[excavationIndex];
    }
    else return NULL;
}

CircuitTraverser::~CircuitTraverser()
{
    //dtor
}

Component *CircuitTraverser::getNext(){
    Component *tempNext = excavate();
    if (tempNext == NULL){
    }
    else return tempNext;
}

