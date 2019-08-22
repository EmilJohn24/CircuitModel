#ifndef COMPONENT_H
#define COMPONENT_H
#include <stdlib.h>

class Component; //forward declaration for ComponentGroup
typedef struct cpg{
    Component **components;
    int count;
} ComponentGroup;

class Component
{
    public:

        static const int COMPONENT_LIMIT = 100;
        Component(double property, char unit, int id){
            mainProperty = property;
            propertyUnit = unit;
            modelID = id;
            entry.components = (Component**) malloc(sizeof(Component*) * COMPONENT_LIMIT);
            exit.components = (Component**) malloc(sizeof(Component*) * COMPONENT_LIMIT);
            entry.count = 0;
            exit.count = 0;
        };
        virtual ~Component();

        void connectComponentToEntry(Component *_component){
            entry.components[entry.count++] = _component;
        };

        void connectComponentToExit(Component *_component){
            exit.components[exit.count++] = _component;
        };

        ComponentGroup getEntryComponents(){
            return entry;
        };

        ComponentGroup getExitComponents(){
            return exit;
        };


        virtual int getModelID() { return modelID; };
        virtual char getPropertyUnit() { return propertyUnit; };
        virtual double getMainProperty() { return mainProperty; };
        void setMainProperty(double _amount) { mainProperty = _amount; };



    protected:

    private:
        double mainProperty;
        char propertyUnit;
        int modelID; //model ID to be used by graphics class for design reference
        ComponentGroup entry; //array of components connected from the entry point of this component
        ComponentGroup exit;  //array of components connected from the exit point of this component
};

#endif // COMPONENT_H
