#include "Manager.h"

Manager::Manager()
{
    //loads the log and recent files
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
    //creates a new circuit file with a default template
    FILE *tmp = fopen(filename, "w"); //creates the file
    fprintf(tmp, "1 V 5 0\n"); //default template
    fprintf(tmp, "2 R 100 1\n");
    fprintf(tmp, "3 R 100 2");
    fclose(tmp);
    loadCircuit(filename);  //reopens the file in read-mode
}

void Manager::loadCircuit(char *filename){
    //loads the circuit. If the file cannot be found, it catches the error
    //and returns to the main menu
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
    //main menu
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
    //handles the selected choice from the main menu by redirecting to the appropriate function
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
    //loads the graphics and runs everything
    graphics = new Graphic(circuit, 30, 30);
    graphics->loadCircuitGraphic();
    //test
    everythingMenu();

}

void Manager::everythingMenu(){
    //displays implented doable actions
    system("cls");
    graphics->loadCircuitGraphic();
    printf("Tool box: \n");
    printf("1. Add component in node\n");
    printf("2. Save circuit\n");
    printf("3. Adjust component property\n");
    printf("4. Delete component\n");
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
    case 3:
        adjustMenu();
        break;
    case 4:
        deleteMenu();
        break;
    case 'X':
        return;
    default:
        return;
    }

    everythingMenu();

}

void Manager::changePropertyOfComponentAt(int index, double property){
    circuit->getComponentAt(index)->setMainProperty(property);
}

void Manager::removeComponentAt(int index){
    circuit->removeComponentAt(index);

}

void Manager::deleteMenu(){
    printf("type the (yellow) number of the component you want to delete: ");
    int choice;
    scanf("%d", &choice);
    removeComponentAt(choice);
}

void Manager::adjustMenu(){
    printf("Type the (yellow) number of the component you want to adjust: ");
    int choice;
    scanf("%d", &choice);
    printf("Type the new value for that component: ");
    double property;
    scanf("%lf", &property);
    changePropertyOfComponentAt(choice, property);

}

void Manager::addComponentInMarkedPoint(Component *_component, int numberMarker){
    nodeTracker = 1;
    Component *adjacentComponent;
    if (numberMarker == 1) adjacentComponent = circuit->getRootComponent();
    else adjacentComponent = adderExplorer(_component, circuit->getRootComponent(), numberMarker);
    fprintf(log, "Adding to index %d\n", adjacentComponent->getReferenceIndex());
    circuit->addComponent(_component, adjacentComponent);
}

Component* Manager::adderExplorer(Component *_component, Component *_previousLayer, int numberMark){
    //this function explores the component tree until it finds the component node it is looking for (as marked by the numberMark variable)
    //it returns null if it has reached the end of a branch
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
    printf("5. AC Source\n");
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

