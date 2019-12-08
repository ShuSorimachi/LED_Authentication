//
//  Contours.hpp
//  Authentication
//
//  Created by Sorimachi Shu on 2018/10/07.
//

#ifndef Contours_hpp
#define Contours_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"

class Contours{
public:
    void init(int _width,int _height);  //コンストラクタ
    void update(ofxCvGrayscaleImage _img);//計算処理用のところ引数はグレースケール画像
    void draw();
    void position();
    void reset();//キャリブレーションをミスした時に中心設定を解除できるようにするメソッド
    
    int marker();//どのマーカかを判定し，送信するメソッド
    
     ofxCvContourFinder contourfinder;//輪郭抽出
     ofxCvGrayscaleImage img;
    
    int width,height;//映像の大きさ
    
    
    bool light[4];//4箇所のどこが光っているのかの判定
    bool match;
    int pattern;//パターンの番号
    
    float area[16];//面積
    int buf;//バッファー
    float max = 0;//使ってるかわからん
    
    float Kpos[16][3];//x座標，y座標，面積を入れるやつ
    float Position[16][3];//同じ

    float buffer,buffer2;
    
    bool keep = true;
    bool first = true;
    
    ofxPanel gui;
    ofxIntSlider num;
    
     float distance[16][2];//中心との距離
    
     int count = 0;
     int falsecount= 0;
//     int getpattern = 16;
//     int bufpattern = 1;

    
private:
    void sort(int NUM,float pos[16][3]);
};

#endif /* Contours_hpp */
