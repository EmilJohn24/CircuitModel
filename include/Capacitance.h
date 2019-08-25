#ifndef CAPACITANCE_H
#define CAPACITANCE_H

#include "Component.h"


class Capacitance : public Component
{
    //capacitor
    public:
        static const char UNIT = 'C';
        static const int ID = 2;
        Capacitance(double capacitance): Component(capacitance, Capacitance::UNIT, Capacitance::ID){};
        virtual ~Capacitance();

    protected:

    private:
};

#endif // CAPACITANCE_H
