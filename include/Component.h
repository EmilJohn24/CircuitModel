#ifndef COMPONENT_H
#define COMPONENT_H
#include <stdlib.h>
#include <string.h>
class Component; //forward declaration for ComponentGroup
typedef struct cpg{
    Component **components;
    int count;
} ComponentGroup

class Component
{
    public:

        static const int COMPONENT_LIMIT = 100;
        static const int NAME_LIMIT = 100;
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

        void disconnectComponentFromExit(Component *_component){
            int count = this->exit.count;
            Component **components = this->exit.components;
            for (int i = 0; i != count; i++){
                if (_component == components[i]){
                    for (int j = i; j != count - 1; j++){
                        components[j] = components[j + 1];
                    }
                    this->exit.count--;

                    break;
                }
            }

        };

        void disconnectComponentFromEntry(Component *_component){
            int count = this->entry.count;
            Component **components = this->entry.components;
            for (int i = 0; i != count; i++){
                if (_component == components[i]){
                    for (int j = i; j != count - 1; j++){
                        components[j] = components[j + 1];
                    }
                    this->entry.count--;

                    break;
                }
            }


        };

        void connectComponentToEntry(Component *_component){
            entry.components[entry.count] = _component;
            entry.count++;
        };

        void connectComponentToExit(Component *_component){
            exit.components[exit.count] = _component;
            exit.count++;
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
        void setReferenceIndex(int index){referenceIndex = index;};
        int getReferenceIndex(){ return referenceIndex; };



    protected:

    private:
        int referenceIndex;
        double mainProperty;
        char propertyUnit;
        int modelID; //model ID to be used by graphics class for design reference
        ComponentGroup entry; //array of components connected from the entry point of this component
        ComponentGroup exit;  //array of components connected from the exit point of this component
};

#endif // COMPONENT_H
