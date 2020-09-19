#ifndef SEGMENT_H
#define SEGMENT_H
#include "rviz_visual_tools/headers/Tunnel.h"

class Segment:public Tunnel{
private:
    float length;
    float slope;
    float height;
    float width;
public:
    Segment();
    void setlength(float n);
    float getlength();
    void setheight(float n);
    void setwidth(float n);
    void setslope(float n);
    void printsegments();
};

#endif // SEGMENT_H
