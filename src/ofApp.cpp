#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp(){
    for (Emitter* e : emitters) {
        delete e;
    }

    for (Particle* p : particles) {
        delete p;
    }

    for (Box* o : boxes) {
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
            Particle* p = parseParticleType(e->getParticleType(), e->getPosition());
            particles.push_back(p);

            e->addParticle(1);
        }
    }

    // -------- update particles
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->update(deltaTime);

        vec2 ppos = particles[i]->getPosition();
        for (Box* o : boxes) {
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

    // -------- update boxes
    for (Box* o : boxes) {
        o->update(deltaTime);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(COLORS.BACKGROUND);

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

    for (Box* o : boxes) {
        o->draw();
        if (mode != view) {
            o->drawEditMode();
        }
    }

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
            switch (ptype) {
                case spiral:
                    s << "Type: Spiral" << endl;
                    break;
                case smoke:
                    s << "Type: Smoke" << endl;
                    break;
            }
            break;
        case box:
            s << "Placing Box" << endl;
            break;
    }

    ofSetColor(COLORS.TEXT);
    ofDrawBitmapString(s.str().c_str(), vec2(8, 16));

    if (showHelp) {
        stringstream h;

        h << "       <Particle Simulator>       " << endl;
        h << " Use keys 1, 2 & 3 to switch mode " << endl;
        h << "" << endl;
        h << "     1:        View               " << endl;
        h << "     2:   Placing Emitter         " << endl;
        h << "     3: Placing Box/Obstacle      " << endl;
        h << "" << endl;
        h << "Left click to place/move an object" << endl;
        h << "       Right click to delete      " << endl;
        h << "" << endl;
        h << "  Press 'f' to toggle fullscreen  " << endl;
        h << " Press 'h' to toggle this message " << endl;
        h << "                ---               " << endl;
        h << "Particle systems are used in games" << endl;
        h << " and other forms of digital media " << endl;
        h << "to depict complex visuals such as " << endl;
        h << "  electricity, fire, smoke, and   " << endl;
        h << " other kinds of amorphous things. " << endl;
        h << "" << endl;
        h << " There are multiple aspects to a  " << endl;
        h << "   particle system. As the name   " << endl;
        h << "    suggests, an emitter emits    " << endl;
        h << " particles from itself. Particles " << endl;
        h << "  have a set behaviour to follow  " << endl;
        h << "     from equations simple as     " << endl;
        h << "     moving in one direction.     " << endl;

        ofDrawBitmapStringHighlight(h.str().c_str(), vec2(8, 128), COLORS.FOREGROUND, COLORS.BACKGROUND);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        // misc settings
        case 'f':
            ofToggleFullscreen();
            break;
        case 'h':
            showHelp = !showHelp;
            break;
        // changing mode
        case '1':
            mode = view;
            break;
        case '2':
            mode = emitter;
            break;
        case '3':
            mode = box;
            break;
        // changing particle type
        case 'q':
            ptype = spiral;
            break;
        case 'w':
            ptype = smoke;
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
    for (Box* o : boxes) {
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
                for (int i = 0; i < boxes.size(); i++) { // we dont want the user to be able to place emitters under boxes
                    if (boxes[i]->getBoundingBox().inside(vec2(x, y))) {
                        return;
                    }
                }
                if (button == 0) {
                    emitters.push_back(new Emitter(vec2(x, y), COLORS.FOREGROUND, 0.25, 1, ptype));
                }
                break;
            case box:
                for (int i = boxes.size() - 1; i >= 0; i--) { // iterate backwards so we are interacting with the box on top of the other boxes first
                    if (boxes[i]->getBoundingBox().inside(vec2(x, y))) {
                        switch (button) {
                            case 0:
                                boxes[i]->setCaptured(true);
                                mouseCaptured = true;
                                break;
                            case 2:
                                delete boxes[i];
                                boxes.erase(boxes.begin() + i);
                        }
                        return;
                    }
                }
                if (button == 0) {
                    boxes.push_back(new Box(vec2(x, y), 8, 8, COLORS.FOREGROUND));
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

    for (Box* o : boxes) {
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

//--------------------------------------------------------------
Particle* ofApp::parseParticleType(ParticleType ptype, vec2 emitterPos) {
    switch (ptype) {
        case spiral:
            return new Particle(emitterPos, SPIRAL.SPAWN_DIRECTION(deltaTime), SPIRAL.SIZE, SPIRAL.SPEED, SPIRAL.LIFETIME, SPIRAL.COLOR);
            break;
        case smoke:
            return new SmokeParticle(emitterPos, SMOKE.SPAWN_DIRECTION(deltaTime), SMOKE.SIZE(), SMOKE.SPEED, SMOKE.LIFETIME, SMOKE.COLOR());
            break;
    }
    return new Particle(emitterPos, SPIRAL.SPAWN_DIRECTION(deltaTime), SPIRAL.SIZE, SPIRAL.SPEED, SPIRAL.LIFETIME, COLORS.RED);
}