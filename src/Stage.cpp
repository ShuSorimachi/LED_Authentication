//
//  Stage.cpp
//  Authentication
//
//  Created by Sorimachi Shu on 2018/09/14.
//

#include "Stage.hpp"

void Stage::init(){
    count = 0;
    cc = 0;
    c = false;
    fil = 76;
}

void Stage::update(){
    
}

void Stage::draw(){
    
}

//  マーカパタン画像をとれる
//fileNameとname()の中身を変えればrキーを押しただけでお好きな写真があなたのもとへ
// grabScreen(x座標,y座標,width,height)
void Stage::registration(){
    img.grabScreen(360,20,320,240);
    string fileName = name() +"_"+ "96-" + ofToString(fil) + ".jpg";
    img.save(fileName);
    count++;
    if(count % 4 ==  0 && count > 1){
        fil += 2;
    }
}

//  画像の名前を変えるためのやつ
string Stage::name(){
    cc++;
    if(cc%4 == 1){
        n = "770";
    }else if(cc % 4 == 2){
        n = "810";
    }else if(cc % 4 == 3){
        n = "870";
    }else if(cc % 4 == 0){
        n = "940";
    }
    
    return n;
}

void Stage::authentication(){
    
}


