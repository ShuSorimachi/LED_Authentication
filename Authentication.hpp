//
//  Authentication.hpp
//  Authentication
//
//  Created by Sorimachi Shu on 2019/06/26.
//

#ifndef Authentication_hpp
#define Authentication_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Contours.hpp"

class Authentication{
    
    void init(Contours _contours);
    void update();
    
    Contours contours;
    
    
    
}

#endif /* Authentication_hpp */
