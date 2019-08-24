#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "console.h"
#include "components.h"
#include "Circuit.h"
class Graphic
{
    public:
        static const int NODE_WIRE_LENGTH = 10;
        static const int BRANCHING_DISTANCE = 5;
        char *WIRE_CHAR = "-";
        char *HORIZONTAL_WIRE_CHAR = "|";
        char *RESISTOR_HORIZONTAL = "\\/\\/\\/\\/";
        char *INDUCTOR_HORIZONTAL = ")()()()()(";
        char *DC_VOLTAGE_SOURCE = "(-+)";
        char *CAPACITOR_HORIZONTAL = "| |";
        //static const char *WIRE_CHAR = "-";

        Graphic(Circuit *_circuit, int _top, int _left): circuit(_circuit), top(_top), left(_left) {
            currentX = _left;
            currentY = _top;
            color = TLWHITE;
        };

        void loadCircuitGraphic();
        int loadNextComponent(Component *explorer, int *verticalDrop);
        virtual ~Graphic();

        void moveBrush(int dx, int dy){
            currentX += dx;
            currentY += dy;
        };

        void paint(char *c){
            putxy(currentX, currentY, color, c);
            moveBrush(strlen(c), 0);
        };

        void printNodeTrackerOnTopOfBrush(){
            char *trackerText = (char *) malloc(sizeof(char) * 10);
            sprintf(trackerText, "%d", nodeTracker);
            moveBrush(0, -1);
            paint(trackerText);
            moveBrush(-strlen(trackerText), 1);
        }
    protected:

    private:
        Circuit *circuit;
        int currentX;
        int currentY;
        int top;
        int color;
        int left;
        int nodeTracker;

};

#endif // GRAPHIC_H
