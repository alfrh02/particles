#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){
    deltaTime += ofGetLastFrameTime();

    for (Emitter* e : emitters) {
        e->update(deltaTime);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLORS.BACKGROUND);

    ofPushView();

        for (Emitter* e : emitters) {
            e->draw();
            if (editMode) {
                e->drawEditMode();
            }
        }

    ofPopView();

    unsigned int particleNum = 0;
    for (Emitter* e : emitters) {
        particleNum += e->getParticleAmount();
    }

    stringstream s;

    if (editMode) {
        s << "Edit Mode: ON" << endl;
    } else {
        s << "Edit Mode: OFF" << endl;
    }

    s << to_string(ofGetFrameRate()) << " fps" << endl;
    s << to_string(deltaTime) << " seconds" << endl;
    s << to_string(particleNum) << " particles" << endl;

    ofSetColor(COLORS.TEXT);
    ofDrawBitmapString(s.str().c_str(), vec2(8, 16));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'e':
            editMode = !editMode;
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
    if (editMode && (button == 2 || button == 0)) {
        bool captured = false;

        for (int i = 0; i < emitters.size(); i++) {
            if (distance(vec2(x, y), emitters[i]->getPosition()) < emitters[i]->getSize()) {
                if (button == 2) {
                    delete emitters[i];
                    emitters.erase(emitters.begin() + i);
                    i--;
                } else {
                    emitters[i]->setCaptured(true);
                }
                captured = true;
                break;
            }
        }

        if (!captured) {
            emitters.push_back(new Emitter(vec2(x, y), 0.25, -1));
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for (Emitter* e : emitters) {
        if (e->getCaptured()) {
            e->setCaptured(false);
            break;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {

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
