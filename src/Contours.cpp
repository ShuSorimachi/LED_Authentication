//
//  Contours.cpp
//  Authentication
//
//  Created by Sorimachi Shu on 2018/10/07.
//

#include "Contours.hpp"
#include "ofMain.h"

void Contours::init(int _width,int _height){
    width = _width;
    height = _height;
    
    gui.setup();
    gui.add(num.setup("number",4,0,4));
}

void Contours::update(ofxCvGrayscaleImage _img){
    img = _img;
    
    //contourfinder.findContours(どのやつに対して,とる最小値,とる最大値,いくつとるか,穴があいてるやつをとるか)
    contourfinder.findContours(img,500,(width*height)/4,num,true);
    
    //-------輪郭を抽出するところ
    //輪郭抽出数が0じゃなければこの処理に入る
    if(contourfinder.nBlobs != 0){
    //for文の中でcontourfinder.~を使う場合for文の条件文にcontourfinder.nBlobsを使わないといけない
    for (int i = 0; i < contourfinder.nBlobs; i++){
        for(int j = num; j > i; j--){
        //if(contourfinder.blobs[i].hole){
            //随時取得する輪郭中心部の座標
            Position[i][0] = contourfinder.blobs[i].boundingRect.getCenter().x;
            Position[i][1] = contourfinder.blobs[i].boundingRect.getCenter().y;
            Position[i][2] = contourfinder.blobs[i].area;
            //光っていないところの座標が残ってしまうのを防ぐための処理
            Position[j][0] = 0;
            Position[j][1] = 0;
            Position[j][2] = 0;
            if(contourfinder.nBlobs == 0){
                Position[0][0] = 0;
                Position[0][1] = 0;
                Position[0][2] = 0;
            }
        
        }
        
        //}
        }
    }else{
        for(int j = 0; j < num; j++){

        Position[j][0] = 0;
        Position[j][1] = 0;
        Position[j][2] = 0;
        }
    }
    //キャリブレーション用
    if(keep == true && first == true){
        for(int i = 0; i < num; i++){
            Kpos[i][0] = Position[i][0];
            Kpos[i][1] = Position[i][1];
            Kpos[i][2] = Position[i][2];
        }
//        printf("前\n");
//        printf("(%f,%f,%f),\n",Kpos[0][0],Kpos[0][1],Kpos[0][2]);
//        printf("(%f,%f,%f),\n",Kpos[1][0],Kpos[1][1],Kpos[1][2]);
//        printf("(%f,%f,%f),\n",Kpos[2][0],Kpos[2][1],Kpos[2][2]);
//        printf("(%f,%f,%f)\n",Kpos[3][0],Kpos[3][1],Kpos[3][2]);
        //キャリブレーション部分はソートを行う
        sort(num,Kpos);
        
//        printf("後\n");
//        printf("(%f,%f,%f),\n",Kpos[0][0],Kpos[0][1],Kpos[0][2]);
//        printf("(%f,%f,%f),\n",Kpos[1][0],Kpos[1][1],Kpos[1][2]);
//        printf("(%f,%f,%f),\n",Kpos[2][0],Kpos[2][1],Kpos[2][2]);
//        printf("(%f,%f,%f)\n",Kpos[3][0],Kpos[3][1],Kpos[3][2]);
        
    }
    //フラグ
    if(keep == false){
        first == false;
    }
    
    
    
    
}

void Contours::draw(){
    //GUIを表示する
    gui.draw();
    //輪郭をとる個数の最大値の分だけ配列を確保4つ分だと4~8程度必要だと思われる
    
    for(int i = 0; i < contourfinder.nBlobs; i++){
        contourfinder.blobs[i].draw(360,20);
        ofSetColor(255);
    }
    for(int i = 0; i < num; i++){
//        ofDrawBitmapString(ofToString(i+1),
//                           Kpos[i][0] + 20, Kpos[i][1] + 280);
        
        ofDrawBitmapString(ofToString(i+1),
                           Position[i][0] + 20, Position[i][1] + 280);
    }
    
    
    
}

void Contours::position(){
    keep = false;
}

void Contours::reset(){
    keep = true;
    first = true;
}

int Contours::marker(){//マーカパタンをおくるためのやつ
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
            distance[i][0] = abs(Kpos[i][0] - Position[j][0]);//設定した中心位置との差をとってるここはx座標
            distance[i][1] = abs(Kpos[i][1] - Position[j][1]);//ここはy座標
            
            if(distance[i][0] < 10 &&  distance[i][1] < 10 && Kpos[i][2] > 2000){//距離とその大きさによって光っているか否かの判定をする
                light[i] = true;
                break;
            }else{
                light[i] = false;
            }
            
        }

    }

    //どこが光ってるのかを判定するゴリ押しコード
    if(light[0] == true && light[1] == false && light[2] == false && light[3] == false){
        pattern = 1;
    }else if(light[0] == false && light[1] == true && light[2] == false && light[3] == false){
        pattern = 2;
    }else if(light[0] == false && light[1] == false && light[2] == true && light[3] == false){
        pattern = 3;
    }else if(light[0] == false && light[1] == false && light[2] == false && light[3] == true){
        pattern = 4;
    }else if(light[0] == true && light[1] == true && light[2] == false && light[3] == false){
        pattern = 5;
    }else if(light[0] == true && light[1] == false && light[2] == true && light[3] == false){
        pattern = 6;
    }else if(light[0] == true && light[1] == false && light[2] == false && light[3] == true){
        pattern = 7;
    }else if(light[0] == false && light[1] == true && light[2] == true && light[3] == false){
        pattern = 8;
    }else if(light[0] == false && light[1] == true && light[2] == false && light[3] == true){
        pattern = 9;
    }else if(light[0] == false && light[1] == false && light[2] == true && light[3] == true){
        pattern = 10;
    }else if(light[0] == true && light[1] == true && light[2] == true && light[3] == false){
        pattern = 11;
    }else if(light[0] == true && light[1] == true && light[2] == false && light[3] == true){
        pattern = 12;
    }else if(light[0] == true && light[1] == false && light[2] == true && light[3] == true){
        pattern = 13;
    }else if(light[0] == false && light[1] == true && light[2] == true && light[3] == true){
        pattern = 14;
    }else if(light[0] == true && light[1] == true && light[2] == true && light[3] == true){
        pattern = 15;
    }else if(light[0] == false && light[1] == false && light[2] == false && light[3] == false){
        pattern = 0;
    }
    
    return pattern;
}

void Contours::sort(int NUM,float pos[16][3]){//ポジションソートのメソッドy座標のソートに伴ってx座標をソートそのあとにx座標ソートをするその時一緒にy座標もソート
    float buffer,buffer2,buffer3;
    int i,j;

    for(i = 0; i < NUM; i++){
        for(j = NUM-1; j > i; j--){
            if(pos[j][1] < pos[j-1][1]){
                buffer = pos[j][1];
                buffer2 = pos[j][0];
                buffer3 = pos[j][2];
                pos[j][1] = pos[j-1][1];
                pos[j][0] = pos[j-1][0];
                pos[j][2] = pos[j-1][2];
                pos[j-1][1] = buffer;
                pos[j-1][0] = buffer2;
                pos[j-1][2] = buffer3;
            }
        }
    }
    
    if(pos[1][0] < pos[0][0]){
        buffer = pos[1][0];
        pos[1][0] = pos[0][0];
        pos[0][0] = buffer;
    }
    if(pos[3][0] < pos[2][0]){
        buffer = pos[3][0];
        pos[3][0] = pos[2][0];
        pos[2][0] = buffer;
    }
    
    
}



