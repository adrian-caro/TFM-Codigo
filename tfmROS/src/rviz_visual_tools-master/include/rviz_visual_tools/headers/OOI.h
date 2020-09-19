#ifndef OOI_H
#define OOI_H
#include <string>

class OOI
{
private:
    float position_longit;
    float position_deg;
    int ID;

public:
    OOI();
    void setID(int n);
    void setposition_longit(float n);
    void setposition_deg(float n);
    void printOOI();
    int getID();
};

#endif // OOI_H
