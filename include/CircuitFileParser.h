#ifndef CIRCUITFILEPARSER_H
#define CIRCUITFILEPARSER_H
#include <stdlib.h>
#include <stdio.h>
#include "Circuit.h"
#include "components.h"
#include <exception>
//some notes on parsing
//adding a component requires adding stuff to too many places
class CircuitFileParser
{
    public:
        CircuitFileParser(char *filename);
        virtual ~CircuitFileParser();
        Circuit *parse();
        void updateFile(Circuit *currentCircuit);
        void individualFileWrite(Component *current, int previousIndex);
        void put(Circuit *circuit);
        Component *createComponent(double property, char symbol);
        static char getSymbolFromID(int id);
        char symbolToUnit(char symbol);
    protected:

    private:
        FILE *circuitFile;
        FILE *log;
        char *circuitFileName;
};

#endif // CIRCUITFILEPARSER_H
