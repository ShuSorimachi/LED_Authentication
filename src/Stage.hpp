//
//  Stage.hpp
//  Authentication
//
//  Created by Sorimachi Shu on 2018/09/14.
//

#ifndef Stage_hpp
#define Stage_hpp

#include <stdio.h>
#include "ofMain.h"

class Stage{
    
public:
    
    void init();
    void update();
    void draw();
    void registration();
    void authentication();
    string name();
    bool call();
    
    ofImage img;
    
    ofTrueTypeFont cooper;
    
    int count;
    string n;
    
    bool c;
    int cc;
    int fil;
    
    
    
};

#endif /* Stage_hpp */

