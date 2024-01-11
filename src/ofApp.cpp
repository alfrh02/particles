#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp(){
    for (Emitter* e : emitters) {
        delete e;
    }

    for (Particle* p : particles) {
        delete p;
    }

    for (SceneObject* o : sceneObjects) {
        delete o;
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
}

//--------------------------------------------------------------
void ofApp::update(){
    deltaTime += ofGetLastFrameTime();

    // -------- update emitters
    for (Emitter* e : emitters) {
        e->update(deltaTime);

        if (e->canSpawn()) {
            Particle* p = new Particle(e->getPosition(), vec2(sin(deltaTime), cos(deltaTime)), 1, 0.1, -1, COLORS.FOREGROUND);
            particles.push_back(p);

            e->addParticle(1);
        }
    }

    // -------- update particles
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->update(deltaTime);

        vec2 ppos = particles[i]->getPosition();
        for (SceneObject* o : sceneObjects) {
            if (o->getBoundingBox().inside(ppos.x, ppos.y)) {
                particles[i]->onCollision(o->getBoundingBox());
            }
        }

        if (particles[i]->getIsDead()) {
            delete particles[i];
            particles.erase(particles.begin() + i);
            i--;
        }
    }

    // -------- update sceneObjects
    for (SceneObject* o : sceneObjects) {
        o->update(deltaTime);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLORS.BACKGROUND);

    ofPushView();

        if (mode != view) {
            for (Emitter* e : emitters) {
                e->drawEditMode();
            }
        }

        for (Particle* p : particles) {
            p->draw();
            if (mode != view) {
                p->drawEditMode();
            }
        }

        for (SceneObject* o : sceneObjects) {
            o->draw();
            if (mode != view) {
                o->drawEditMode();
            }
        }

    ofPopView();

    stringstream s;

    s << to_string(ofGetFrameRate()) << " fps" << endl;
    s << to_string(deltaTime) << " seconds" << endl;
    s << to_string(particles.size()) << " particles" << endl;
    s << to_string(ofGetMouseX()) << ", " << to_string(ofGetMouseY()) << endl;
    s << "\nCurrent Mode: ";

    switch (mode) {
        case view:
            s << "View" << endl;
            break;
        case emitter:
            s << "Placing Emitter" << endl;
            break;
        case box:
            s << "Placing Box" << endl;
            break;
    }

    ofSetColor(COLORS.TEXT);
    ofDrawBitmapString(s.str().c_str(), vec2(8, 16));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case '1':
            mode = view;
            break;
        case '2':
            mode = emitter;
            break;
        case '3':
            mode = box;
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
    // for `button`:
    // 0 == left click, 1 == middle click, 2 == right click

    // when we are editing a box's width and height, we need to left click to stop editing
    // we return the function prematurely to stop more behaviour from being calculated
    for (SceneObject* o : sceneObjects) {
        if (o->getCaptured()) {
            o->setCaptured(false);
            mouseCaptured = false;
            return;
        }
    }

    if (!mouseCaptured && mode != view) {
        // in each case we are looping through a vector, checking if our mouse's xy coordinates are over each object in the vector.
        // if we are clicking on an object, the function is prematured ended via `return`
        // if we are not clicking on an object, the function will continue
        // this explains why we are adding new objects at the end of the for loop to the vector we just looped through
        switch (mode) {
            case emitter:
                for (int i = 0; i < emitters.size(); i++) {
                    if (distance(vec2(x, y), emitters[i]->getPosition()) < emitters[i]->getSize()) {
                        switch (button) {
                            case 0:
                                emitters[i]->setCaptured(true);
                                mouseCaptured = true;
                                break;
                            case 2:
                                delete emitters[i];
                                emitters.erase(emitters.begin() + i);
                        }
                        return;
                    }
                }
                if (button == 0) {
                    emitters.push_back(new Emitter(vec2(x, y), COLORS.FOREGROUND, 0.25, -1));
                }
                break;
            case box:
                for (int i = 0; i < sceneObjects.size(); i++) {
                    if (sceneObjects[i]->getBoundingBox().inside(vec2(x, y))) {
                        switch (button) {
                            case 0:
                                sceneObjects[i]->setCaptured(true);
                                mouseCaptured = true;
                                break;
                            case 2:
                                delete sceneObjects[i];
                                sceneObjects.erase(sceneObjects.begin() + i);
                        }
                        return;
                    }
                }
                if (button == 0) {
                    sceneObjects.push_back(new Box(vec2(x, y), 8, 8, COLORS.FOREGROUND));
                    mouseCaptured = true;
                }
                break;
        }

    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for (Emitter* e : emitters) {
        if (e->getCaptured()) {
            e->setCaptured(false);
            mouseCaptured = false;
            break;
        }
    }

    for (SceneObject* o : sceneObjects) {
        if (o->getCaptured()) {
            o->setCaptured(false);
            mouseCaptured = false;
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
