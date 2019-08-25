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
        //some text designs for circuit components
        char *WIRE_CHAR = "-";
        char *HORIZONTAL_WIRE_CHAR = "|";
        char *RESISTOR_HORIZONTAL = "\\/\\/\\/\\/";
        char *INDUCTOR_HORIZONTAL = ")()()()()(";
        char *DC_VOLTAGE_SOURCE = "(-+)";
        char *CAPACITOR_HORIZONTAL = "| |";
        char *AC_VOLTAGE_SOURCE = "(~)";
        //static const char *WIRE_CHAR = "-";

        Graphic(Circuit *_circuit, int _top, int _left): circuit(_circuit), top(_top), left(_left) {
            currentX = _left;
            currentY = _top;
            color = TLWHITE;
        };
        void setColor(int _color){ color = _color; };
        void revertColor() { color = TLWHITE; };

        void loadCircuitGraphic();
        int loadNextComponent(Component *explorer, int *verticalDrop); //loads the next component into the console recursively
        virtual ~Graphic();

        void moveBrush(int dx, int dy){
            //moves the brush by a certain displacement
            currentX += dx;
            currentY += dy;
        };

        void paint(char *c){
            //paints the passed string unto the console and moves the brush
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
        int currentX; //brush x-coord
        int currentY; //brush y-coord
        int top;
        int color;
        int left;
        int nodeTracker;

};

#endif // GRAPHIC_H
