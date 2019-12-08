//
//  Screen.hpp
//  Authentication
//
//  Created by Sorimachi Shu on 2019/06/06.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Contours.hpp"
class Screen{
    
public:
    
    void init();
    void update();
    void draw();
    
    ofImage square;
    ofImage secret;
    
    int pass[4];
    
    Contours contours;
    
    
    
    
};

#endif /* Screen_hpp */
