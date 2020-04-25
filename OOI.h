#ifndef OOI_H
#define OOI_H
#include <string>

class OOI
{
private:
    float position_longit;
    float position_deg;
    std::string shape;
    std::string name;

public:
    OOI();
    void setname(std::string n);
    void setshape(std::string n);
    void setposition_longit(float n);
    void setposition_deg(float n);

    void printOOI();
};

#endif // OOI_H
