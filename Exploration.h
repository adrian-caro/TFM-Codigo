#ifndef EXPLORATION_H
#define EXPLORATION_H


class Exploration
{
private:
    float dH,dC,dAlpha,dBeta;
    float P;
    float K;

public:
    Exploration();
    void explorationalgorithm();
};

#endif // EXPLORATION_H
