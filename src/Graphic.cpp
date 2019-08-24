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
    nodeTracker = 0;
    int firstVerticalDrop;
    loadNextComponent(explorer, &firstVerticalDrop);

}

int Graphic::loadNextComponent(Component *explorer, int *lastVerticalDrop){
    int rightMovement = 0;
    int componentMovement = 0;

    nodeTracker++;
    for (int i = 0; i != NODE_WIRE_LENGTH; i++){
        paint(WIRE_CHAR);
        if (i == NODE_WIRE_LENGTH / 2){
            printNodeTrackerOnTopOfBrush();
        }
        rightMovement += 1;
    }

    if (explorer->getModelID() == Resistance::ID){
        paint(RESISTOR_HORIZONTAL);
        componentMovement += strlen(RESISTOR_HORIZONTAL);
    }

    else if (explorer->getModelID() == Capacitance::ID){
        paint(CAPACITOR_HORIZONTAL);
        componentMovement += strlen(CAPACITOR_HORIZONTAL);
    }

    else if (explorer->getModelID() == Inductance::ID){
        paint(INDUCTOR_HORIZONTAL);
        componentMovement += strlen(INDUCTOR_HORIZONTAL);
    }

    else if (explorer->getModelID() == DCVoltage::ID){
        paint(DC_VOLTAGE_SOURCE);
        componentMovement += strlen(DC_VOLTAGE_SOURCE);
    }

    else if (explorer->getModelID() == ACVoltage::ID){
        paint(AC_VOLTAGE_SOURCE);
        componentMovement += strlen(AC_VOLTAGE_SOURCE);
    }

    moveBrush(0, -2);
    char *tmp = (char*)malloc(sizeof(char) * 10);
    sprintf(tmp, "%d", explorer->getReferenceIndex());
    setColor(TLYELLOW);
    paint(tmp);
    revertColor();
    moveBrush(strlen(tmp), 2);

    //paint measurement value
    //consider putting inside a function
    moveBrush(-componentMovement, -1);
    char *measurementStr = (char *) malloc(sizeof(char) * 20);
    sprintf(measurementStr, "%.2lf%c", explorer->getMainProperty(), explorer->getPropertyUnit());
    paint(measurementStr);
    moveBrush(componentMovement - strlen(measurementStr), 1);
    //end

    rightMovement += componentMovement;

    int size = explorer->getExitComponents().count;
    if (size == 0) return rightMovement;
    for (int i = 0; i != size; i++){
        //printf("%d. Component ID: %d - %d\n", nodeTracker, explorer->getModelID(), i);
        int verticalDrop = 0;
        int next = loadNextComponent(explorer->getExitComponents().components[i], &verticalDrop);
        //printf(" Vertical Drop: %d\n", verticalDrop);
        moveBrush(-next, -verticalDrop);
        for (int j = 0; j != NODE_WIRE_LENGTH; j++){
            paint(HORIZONTAL_WIRE_CHAR);
            moveBrush(-1, 1);
            *lastVerticalDrop = *lastVerticalDrop + 1;
        }

    }
    return rightMovement;
}
