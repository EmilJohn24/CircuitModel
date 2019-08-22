#ifndef GRAPHIC_H
#define GRAPHIC_H
#include <stdio.h>
#include "console.h"
#include "components.h"
#include "Circuit.h"
class Graphic
{
    public:
        static const int NODE_WIRE_LENGTH = 5;
        static const int BRANCHING_DISTANCE = 4;
        char *WIRE_CHAR = "-";
        char *HORIZONTAL_WIRE_CHAR = "|";
        char *RESISTOR_HORIZONTAL = "\\/\\/\\/\\/";
        char *CAPACITOR_HORIZONTAL = "| |";
        //static const char *WIRE_CHAR = "-";

        Graphic(Circuit *_circuit, int _top, int _left): circuit(_circuit), top(_top), left(_left) {
            currentX = _left;
            currentY = _top;
            color = TLWHITE;
        };

        void loadCircuitGraphic();
        int loadNextComponent(Component *explorer);
        virtual ~Graphic();
        void moveBrush(int dx, int dy){
            currentX += dx;
            currentY += dy;
        };

        void paint(char *c){
            putxy(currentX, currentY, color, c);
            moveBrush(strlen(c), 0);
        };


    protected:

    private:
        Circuit *circuit;
        int currentX;
        int currentY;
        int top;
        int color;
        int left;

};

#endif // GRAPHIC_H
