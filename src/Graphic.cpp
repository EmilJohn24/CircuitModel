#include "Graphic.h"



Graphic::~Graphic()
{
    //dtor
}


void Graphic::loadCircuitGraphic(){
    Component *explorer = circuit->getRootComponent();
    system("cls");
    currentX = left;
    currentY = top;
    loadNextComponent(explorer);

}

int Graphic::loadNextComponent(Component *explorer){
    int rightMovement = 0;
    for (int i = 0; i != NODE_WIRE_LENGTH; i++){
        paint(WIRE_CHAR);
        rightMovement += 1;
    }
    if (explorer->getModelID() == Resistance::ID){
        paint(RESISTOR_HORIZONTAL);
        rightMovement += strlen(RESISTOR_HORIZONTAL);
    }

    else if (explorer->getModelID() == Capacitance::ID){
        paint(CAPACITOR_HORIZONTAL);
        rightMovement += strlen(CAPACITOR_HORIZONTAL);
    }


    int size = explorer->getExitComponents().count;
    if (size == 0) return rightMovement;
    for (int i = 0; i != size; i++){
        printf("Component ID: %d - %d\n", explorer->getModelID(), i);
        int next = loadNextComponent(explorer->getExitComponents().components[i]);
        moveBrush(-next + 1, 0);
        for (int i = 0; i != NODE_WIRE_LENGTH; i++){
            paint(HORIZONTAL_WIRE_CHAR);
            moveBrush(-1, 1);
        }
    }
}
