#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //    //シリアル通信
    serial.setup("/dev/cu.usbmodem1411",9600);
    
    //フレームレート
    ofSetFrameRate(60);
    
    //カメラの横幅と縦幅
    camWidth = 320;
    camHeight = 240;
    
    //動画を取得するための設定
    video.setVerbose(true);
    video.listDevices();
    video.setDeviceID(0);
    
    video.initGrabber(camWidth, camHeight);
    
    //画像のための設定
    colorImg.allocate(camWidth,camHeight);
    colorImgHSV.allocate(camWidth,camHeight);
    grayImage.allocate(camWidth,camHeight);
    grayBg.allocate(camWidth,camHeight);
    grayDiff.allocate(camWidth,camHeight);
    grayImg.allocate(camWidth,camHeight);
   
    confidenceMin = 70;
    
    stage.init();
    contour.init(camWidth,camHeight);
    
    //閾値の設定
    threshold = 100;
    //背景の学習の初期値
    LearnBackground = false;

}

//--------------------------------------------------------------
void ofApp::update(){
    //時間計測用
    count++;
    //  キャプチャを更新
    video.update();
    
    if(video.isFrameNew()){//   ちゃんと新しいフレームが読み込まれているか
        colorImg.setFromPixels(video.getPixels().getData(),camWidth,camHeight);
        colorImgHSV = colorImg;
        grayImage = colorImg;
        grayImg = colorImg;
        colorImgHSV.convertRgbToHsv();
        if(LearnBackground){
            grayBg = grayImage;
            LearnBackground = false;
        }
        
        grayDiff.absDiff(grayBg,grayImage);
        grayDiff.threshold(threshold);
        grayImg.threshold(threshold);
        
        //Contoursクラスのupdateの呼び出し（グレースケール画像を使う）
        contour.update(grayImg);
    }
    
  
    //csv形式に保存するためのやつ 前のフレームと違うかつ始まってから1秒以上かつ，特定のキーが押されて入ればif文に入る
    if(buf != get_pattern && count > 60 && getStart == true){
        buf = get_pattern;
        row.setInt(0,buf);
        csv.addRow(row);
        csv.save("recordData6.csv");
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    colorImg.draw(20,20);
    grayImage.draw(360,20);
    grayBg.draw(20,280);
    grayDiff.draw(360,280);
    grayImg.draw(20,540);
    
    //輪郭の表示
    contour.draw();
    //ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 360, 540);
    
    //ここから下で，一定時間同じパターンが入ってたらそのパターンは正しいですよって判断するところ
    pat = contour.marker();
    if(buffer_pattern == pat){
        patternCount++;
    }else{
        patternCount = 0;
    }
    if(patternCount == 10){
        get_pattern = pat;
        patternCount = 0;
    }
    
    buffer_pattern = pat;
    //パターンを表示
    ofDrawBitmapString(ofToString(get_pattern),360,600);
   
    //---------
   
//    if(saveImages){
//        saveImages = false;
//    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1'){
        serial.writeByte('1');
        //getStart = true;
    }else if(key == '2'){
        serial.writeByte('2');
        getStart = true;
    }else if(key == '3'){
        serial.writeByte('3');
        getStart = true;
    }
    //----二値化する時の閾値----
    if(key == '+'){
        threshold += 1;
        //serial.writeByte('+');
    }
    if(key == '-'){
        threshold -= 1;
        //serial.writeByte('-');
    }
    //-----------------------
    
    //画像保存
    if (key == 's'){
        saveImages = true;
        LearnBackground = true;
        
    }
    if(key == 'r'){
        stage.registration();
    }
    if(key == 'p'){
        //csv.save("recourdeData.csv");
        contour.position();
//        for(int i = 0; i < 5; i++){
//        if(csv.load("recordeData"+ofToString(i)+".csv"))
//        csv.save("recordeData" + ofToString(i + 1) + ".csv");
//        }
    }
    if(key == 'x'){
        contour.reset();
        
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}


