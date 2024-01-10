#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){
    deltaTime += ofGetLastFrameTime();

    for (Emitter* e : emitters) {
        e->update(deltaTime);

        if (e->canSpawn()) {
            Particle* p = new Particle(e->getPosition(), vec2(sin(deltaTime), cos(deltaTime)) / 10, 1, 4, -1, COLORS.FOREGROUND);
            particles.push_back(p);

            e->addParticle(1);
        }
    }

    for (int i = 0; i < particles.size(); i++) {
        particles[i]->update(deltaTime);

        if (particles[i]->getIsDead()) {
            delete particles[i];
            particles.erase(particles.begin() + i);
            i--;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLORS.BACKGROUND);

    ofPushView();

        if (editMode) {
            for (Emitter* e : emitters) {
                e->drawEditMode();
            }
        }

        for (Particle* p : particles) {
            p->draw();
            if (editMode) {
                p->drawEditMode();
            }
        }

    ofPopView();

    stringstream s;

    if (editMode) {
        s << "Edit Mode: ON" << endl;
    } else {
        s << "Edit Mode: OFF" << endl;
    }

    s << to_string(ofGetFrameRate()) << " fps" << endl;
    s << to_string(deltaTime) << " seconds" << endl;
    s << to_string(particles.size()) << " particles" << endl;

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
    bool skipCapture = false;

    // uncapture any captured
    for (Emitter* e : emitters) {
        if (e->getCaptured()) {
            e->setCaptured(false);
            skipCapture = true;
            break;
        }
    }

    if (editMode && (button == 2 || button == 0) && !skipCapture) {
        for (int i = 0; i < emitters.size(); i++) {
            if (distance(vec2(x, y), emitters[i]->getPosition()) < emitters[i]->getSize()) {
                if (button == 2) { // right click
                    delete emitters[i];
                    emitters.erase(emitters.begin() + i);
                    i--;
                } else {           // left click
                    emitters[i]->setCaptured(true);
                }
                skipCapture = true;
                break;
            }
        }

        if (!skipCapture) {
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
