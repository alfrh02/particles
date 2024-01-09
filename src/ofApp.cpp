#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // img.load("particle.png");
}

//--------------------------------------------------------------
void ofApp::update(){
    deltaTime += ofGetLastFrameTime();
    ps.update(deltaTime);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor::gray, ofColor::black, OF_GRADIENT_CIRCULAR);

    camera.begin();

    ps.draw();

    // ofPushView();
    //     ofSetColor(255,128,64);
    //     vec3 pos = vec3(0, 0, 0) - vec3(img.getWidth() / 2, img.getHeight() / 2, 0);
    //     vec3 dir = normalize(pos - camera.getPosition());
    //     img.draw(pos * dir);
    // ofPopView();

    if (debugMode) {
        ofDrawGrid(5.0, 16, true, false, true, false);
    }

    camera.end();

    if (debugMode) {
        ofSetColor(0,255,0);
        ofDrawBitmapString(
            "            fps | " + to_string(ofGetFrameRate()),
            vec2(8, 16)
        );

        ofDrawBitmapString(
            "   time elapsed | " + to_string(deltaTime),
            vec2(8, 32)
        );

    //     // mouse coordinates
    //     ofDrawBitmapStringHighlight(
    //         to_string(ofGetMouseX()) + ", " + to_string(ofGetMouseY()),
    //         vec2(ofGetMouseX(), ofGetMouseY()),
    //         ofColor(0, 255, 0),
    //         ofColor(0)
    //     );
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << key << endl;
    switch (key) {
        case '`':
            debugMode = !debugMode;
            break;
        case 'f':
            ofToggleFullscreen();
            break;
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
