#ifndef DCVOLTAGE_H
#define DCVOLTAGE_H

#include "Component.h"


class DCVoltage : public Component
{
    public:
        static const char UNIT = 'V';
        static const int ID = 4;

        DCVoltage(double voltage): Component(voltage, DCVoltage::UNIT, DCVoltage::ID){};
        virtual ~DCVoltage();

    protected:

    private:
};

#endif // DCVOLTAGE_H
