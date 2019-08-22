#ifndef CIRCUITFILEPARSER_H
#define CIRCUITFILEPARSER_H
#include <stdlib.h>
#include <stdio.h>
#include "Circuit.h"
#include "components.h"
class CircuitFileParser
{
    public:
        CircuitFileParser(char *filename);
        virtual ~CircuitFileParser();
        Circuit *parse();
        void *put(Circuit *circuit);
        Component *createComponent(double property, char symbol);
        static char getSymbolFromID(int id);
        char symbolToUnit(char symbol);
    protected:

    private:
        FILE *circuitFile;
};

#endif // CIRCUITFILEPARSER_H
