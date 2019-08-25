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
        CircuitFileParser(char *filename); //loads the file
        virtual ~CircuitFileParser();
        Circuit *parse(); //returns a Circuit object parsed from the circuit file
        void updateFile(Circuit *currentCircuit); //rewrites the file to match the current state of the circuit
        void individualFileWrite(Component *current, int previousIndex); //writes a component as a single line in the circuit file
        void put(Circuit *circuit); //unused function for loading a new circuit into the parser
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
