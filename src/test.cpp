#include "CircuitFileParser.h"
#include "Circuit.h"
#include "Graphic.h"
int main(){
    CircuitFileParser *parser = new CircuitFileParser("test.txt");
    Circuit *cir = parser->parse();
    Component* explorer = cir->getRootComponent();
    Graphic *graphicManager = new Graphic(cir, 30, 30);
    graphicManager->loadCircuitGraphic();
    //Manager *overseer = new Manager();
}
