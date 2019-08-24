#include "CircuitFileParser.h"

CircuitFileParser::CircuitFileParser(char *filename)
{
    //ctor
    circuitFile = fopen(filename, "r+");
    circuitFileName = (char*) malloc(sizeof(char) * 100);
    strcpy(circuitFileName, filename);
    if (circuitFile == NULL) throw "File not found\n";
    log = fopen("circuitParserLog.txt", "a");
}

CircuitFileParser::~CircuitFileParser()
{
    //dtor
    fclose(log);
    fclose(circuitFile);

}

void CircuitFileParser::updateFile(Circuit *currentCircuit){
    circuitFile = freopen(circuitFileName, "w", circuitFile);
    individualFileWrite(currentCircuit->getRootComponent(), 0);
    system("pause");
}

void CircuitFileParser::individualFileWrite(Component *current, int previousIndex){
    int counter = current->getExitComponents().count;
    //printf("%d****", counter);
    Component *next;
    int index, adjacencyIndex;
    char symbol;
    double measurement;
    index = current->getReferenceIndex();
    adjacencyIndex = previousIndex;
    symbol = getSymbolFromID(current->getModelID());
    measurement = current->getMainProperty();
    fprintf(circuitFile, "%d %c %lf %d\n", index, symbol, measurement, adjacencyIndex);
    //printf("Index:%d--Adjacent:%d %c %lf %d\n", index, previousIndex, symbol, measurement, adjacencyIndex);
    for (int i = 0; i != counter; i++){
        next = current->getExitComponents().components[i];
        individualFileWrite(next, index);
    }
}

Component *CircuitFileParser::createComponent(double property, char symbol){
    //creates a new component object based on the symbol given to it
    fprintf(log, "%lf %c\n", property, symbol);
    switch(symbol){
    case 'R':
        return new Resistance(property);
    case 'C':
        return new Capacitance(property);
    case 'I':
        return new Inductance(property);
    case 'V':
        return new DCVoltage(property);
    case 'A':
        return new ACVoltage(property);
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

void CircuitFileParser::put(Circuit *circuit){
    int index = 0;
    int adjacencyIndex = 0;
    double property;
    char componentSymbol;
    Component *explorer = circuit->getRootComponent();
}

char CircuitFileParser::getSymbolFromID(int id){
    if (id == Resistance::ID) return 'R';
    else if (id == Capacitance::ID) return 'C';
    else if(id == Inductance::ID) return 'I';
    else if(id == DCVoltage::ID) return 'V';
    else if(id == ACVoltage::ID) return 'A';
    else return 0;
}




