#ifndef RESISTANCE_H
#define RESISTANCE_H

#include "Component.h"


class Resistance : public Component
{
    public:
        static const char UNIT = 234;
        static const int ID = 1;

        Resistance(double resistance): Component(resistance, Resistance::UNIT, Resistance::ID){};
        virtual ~Resistance();

    protected:

    private:
};

#endif // RESISTANCE_H
