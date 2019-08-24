#include "Manager.h"

Manager::Manager()
{
    log = fopen("manager.log", "w+");
    recentFile = fopen("recent.log", "a");
    //ctor
}

Manager::~Manager()
{
    //dtor
    fclose(log);
}

void Manager::newCircuit(char *filename){
    FILE *tmp = fopen(filename, "w"); //creates the file
    fprintf(tmp, "1 V 5 0\n"); //default template
    fprintf(tmp, "2 R 100 1\n");
    fclose(tmp);
    loadCircuit(filename);
}

void Manager::loadCircuit(char *filename){
    try{
        this->bridge = new CircuitFileParser(filename);
        fprintf(recentFile, "%s\n", filename);
        circuit = bridge->parse();
        graphics = new Graphic(circuit, 20, 20);
    }
    catch (const char* errorMsg){
        printf("%s", errorMsg);
        mainMenu();
    }
}

void Manager::mainMenu(){
    printf("Welcome to Emil's circuit diagram maker.\n");
    printf("1. Create new diagram\n");
    printf("2. Load existing diagram\n");
    printf("3. Recently opened diagrams\n");
    int choice;
    printf("Choose: ");
    scanf("%d", &choice);
    mainMenuChoiceHandler(choice);
}

void Manager::recentFileMenu(){
    //An extremely messy function that loads the recent file menu
    printf("Recent files: \n");
    FILE *tmpRecentFileAccessor = fopen("recent.log", "r");
    char *latestRecentFile = (char*) malloc(sizeof(char) * 100);
    int i = 1;
    while (!feof(tmpRecentFileAccessor)){
        fscanf(tmpRecentFileAccessor, "%s", latestRecentFile);
        printf("%d. %s\n", i, latestRecentFile);
        i++;
    }
    int choice;
    printf("Choice: ");
    scanf("%d", &choice);

    if (i == 1){
        printf("No recent files. \n");
        mainMenu();
    }

    fseek(tmpRecentFileAccessor, 0, 0);
    for (int j = 0; j != choice; j++){
        fscanf(tmpRecentFileAccessor, "%s\n", latestRecentFile);
    }
    fclose(tmpRecentFileAccessor);
    loadCircuit(latestRecentFile);

}
void Manager::mainMenuChoiceHandler(int choice){
    char *filename = (char*) malloc(sizeof(char) * 100);
    switch(choice){
    case 1:
        printf("New file directory and name: ");
        scanf("%s", filename);
        newCircuit(filename);
        break;
    case 2:
        printf("Type file directory: ");
        scanf("%s", filename);
        loadCircuit(filename);
        break;
    case 3:
        recentFileMenu();

    }
    //at this point, everything should have been set up
    if (circuit != NULL && graphics != NULL) runEverything();
    else{
        fprintf(stderr, "ERROR: A random error occurred. Try again.\n");
        fprintf(stderr, "Status report:\n");
        fprintf(stderr, "Circuit Pointer: %p\n", circuit);
        fprintf(stderr, "Graphics Pointer: %p\n", graphics);
        printf("\n");
        mainMenu();
    }

}

void Manager::runEverything(){

    graphics = new Graphic(circuit, 30, 30);
    graphics->loadCircuitGraphic();
    //test
    everythingMenu();

}

void Manager::everythingMenu(){
    system("cls");
    graphics->loadCircuitGraphic();
    printf("Tool box: \n");
    printf("1. Add component in node\n");
    printf("2. Save circuit\n");
    printf("X. Exit\n");
    printf("What do you want to do? ");
    int choice;
    scanf("%d", &choice);

    switch(choice){
    case 1:
        adderMenu();
        break;
    case 2:
        bridge->updateFile(circuit);
        break;
    case 'X':
        return;
    default:
        return;
    }

    everythingMenu();

}


void Manager::addComponentInMarkedPoint(Component *_component, int numberMarker){
    nodeTracker = 1;
    Component *adjacentComponent = adderExplorer(_component, circuit->getRootComponent(), numberMarker);
    fprintf(log, "Adding to index %d\n", adjacentComponent->getReferenceIndex());
    circuit->addComponent(_component, adjacentComponent);
}

Component* Manager::adderExplorer(Component *_component, Component *_previousLayer, int numberMark){
    nodeTracker++;
    if (nodeTracker == numberMark) return _previousLayer;
    int size = _previousLayer->getExitComponents().count;
    if (size == 0) return NULL;
    for (int i = 0; i != size; i++){
        fprintf(log, "%d. Component ID: %d - %d\n", numberMark, _previousLayer->getModelID(), i);
        Component* finder = adderExplorer(_component, _previousLayer->getExitComponents().components[i], numberMark);
        if (finder != NULL) return finder;
    }
    return NULL;

    //return rightMovement;
}

void Manager::adderMenu(){
    gotoxy(0,0);
    system("cls");
    graphics->loadCircuitGraphic();
    printf("Where would you like to add a component? ");
    int marker;
    scanf("%d", &marker);
    printf("Which component would you like added?\n");
    printf("1. Resistor\n");
    printf("2. Capacitor\n");
    printf("3. Inductor\n");
    printf("4. DC Source\n");
    printf("Choose: ");
    int choice;
    scanf("%d", &choice);
    char symbol = CircuitFileParser::getSymbolFromID(choice);
    double property;
    printf("Value of component: ");
    scanf("%lf" , &property);
    addComponentInMarkedPoint(bridge->createComponent(property, symbol), marker);
    graphics->loadCircuitGraphic();//reload
}

