#ifndef CIRCUITTRAVERSER_H
#define CIRCUITTRAVERSER_H
#include "Circuit.h"
//TODO: Finish this part
class CircuitTraverser
{
    //traverses the circuit in a depth-first search manner
    public:
        static const int TRAVERSER_LIMIT = 100;
        CircuitTraverser(Circuit *_circuit){
            this->circuit = _circuit;
            this->explorer = circuit->getRootComponent();
            this->excavationIndex = 0;
        };

        Component *getNext();
        int getCurrentIndex();
        Component *excavate();
        virtual ~CircuitTraverser();



    protected:

    private:
        int excavationIndex;
        Circuit *circuit;
        Component *explorer;
};

#endif // CIRCUITTRAVERSER_H
