#ifndef INDUCTANCE_H
#define INDUCTANCE_H

#include "Component.h"


class Inductance : public Component
{
    public:
        virtual ~Inductance();
        static const char UNIT = 'L';
        static const int ID = 3;

        Inductance(double inductance): Component(inductance, Inductance::UNIT, Inductance::ID){};
    protected:

    private:
};


#endif // INDUCTANCE_H
