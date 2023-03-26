#include "ComplexNumber.h"

bool compare_complex(ComplexNumber* num1, ComplexNumber* num2)
{
    int m1 = sqrt(pow(num1->getRp(), 2) + pow(num1->getIp(), 2));
    int m2 = sqrt(pow(num2->getRp(), 2) + pow(num2->getIp(), 2));

    if (m1 > m2)
        return true;
    else if (m1 < m2)
        return false;
    else if (m1 == m2) {
        if (num1->getRp() > num2->getRp())
            return true;
        else if (num1->getIp() < num2->getIp())
            return false;
        else
            return NULL;
    }

}
