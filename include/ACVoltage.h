#ifndef ACVOLTAGE_H
#define ACVOLTAGE_H

#include "Component.h"



class ACVoltage : public Component
{
    public:
        static const char UNIT = 'V';
        static const int ID = 5;

        ACVoltage(double voltage): Component(voltage, ACVoltage::UNIT, ACVoltage::ID){};
        virtual ~ACVoltage();

    protected:

    private:
};
#endif // ACVOLTAGE_H
