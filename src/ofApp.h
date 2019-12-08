#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxTemplateMatching.h"
#include "ofxCsv.h"
#include "Stage.hpp"
#include "Contours.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    Stage stage;
    
    Contours contour;
    
    //カメラを使うため
    ofVideoGrabber video;
    
    //カメラの縦と横
    int camWidth;
    int camHeight;
    
    //元のカラー画像とHSVに変換した後の画像
    ofxCvColorImage colorImg;
    ofxCvColorImage colorImgHSV;
    
    //グレースケール画像
    ofxCvGrayscaleImage grayImg;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    
    //色相、彩度、明度
    ofxCvGrayscaleImage hueImg;
    ofxCvGrayscaleImage satImg;
    ofxCvGrayscaleImage briImg;
    
    //色を追跡して輪郭を表示するための映像情報
    ofxCvGrayscaleImage white;
    
    bool saveImages;
    
    string saveFile;
    
    int count = 0;
    int patternCount = 0;
    //    //元の映像情報の明度と彩度が指定色に近いのかどうかに使う
    //    unsigned char * colorTrackedPixelsWhite;//現在未使用
    
    //二値画像
    ofTexture trackedTextureWhite;
    
    //輪郭線表示をするためのやつ
    ofxCvContourFinder contourfinder;
    
    bool LearnBackground;
    
    //シリアル通信用変数
    ofSerial serial;
    
    //画像の閾値
    int threshold;
    
    int confidenceMin;
    
    
 
    
    //
    ofxCsv csv;
    ofxCsvRow row;
    
    int buf = 0;
    bool getStart = false;
    
    int pat;
    int buffer_pattern;
    int get_pattern;
    
};

