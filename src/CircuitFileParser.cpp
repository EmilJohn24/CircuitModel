#include "CircuitFileParser.h"

CircuitFileParser::CircuitFileParser(char *filename)
{
    //ctor
    circuitFile = fopen(filename, "r+");
    log = fopen("circuitParserLog.txt", "a");
}

CircuitFileParser::~CircuitFileParser()
{
    //dtor
    fclose(log);
    fclose(circuitFile);

}


Component *CircuitFileParser::createComponent(double property, char symbol){
    fprintf(log, "%lf %c\n", property, symbol);
    switch(symbol){
    case 'R':
        return new Resistance(property);
    case 'C':
        return new Capacitance(property);
    default:
        return NULL;

    }

}
Circuit *CircuitFileParser::parse(){
    Circuit *newCircuit = new Circuit();
    int index, adjacencyIndex;
    double property;
    char componentSymbol;
    while (!feof(circuitFile)){
        fscanf(circuitFile, "%d %c %lf %d", &index, &componentSymbol, &property, &adjacencyIndex);
        Component *newComponent = createComponent(property, componentSymbol);
        if (newComponent != NULL) newCircuit->addComponent(newComponent, index, adjacencyIndex);
    }
    return newCircuit;
}

void *CircuitFileParser::put(Circuit *circuit){
    int index = 0;
    int adjacencyIndex = 0;
    double property;
    char componentSymbol;
    Component *explorer = circuit->getRootComponent();


}

char CircuitFileParser::getSymbolFromID(int id){
    if (id == Resistance::ID) return 'R';
    else if (id == Capacitance::ID) return 'C';
    else return 0;


}




