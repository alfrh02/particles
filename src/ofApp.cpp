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
    helpText << "       <Particle Simulator>       " << endl;
    helpText << " Use keys q, w & e to switch mode " << endl;
    helpText << "" << endl;
    helpText << "     1:        View               " << endl;
    helpText << "     2:   Placing Emitter         " << endl;
    helpText << "     3: Placing Box/Obstacle      " << endl;
    helpText << "" << endl;
    helpText << "When placing emitters use keys 1-4" << endl;
    helpText << " to switch through particle types " << endl;
    helpText << "" << endl;
    helpText << "   When in placing mode Emitters  " << endl;
    helpText << "  be visible, and Particles will  " << endl;
    helpText << "       show their direction       " << endl;
    helpText << "" << endl;
    helpText << "Left click to place/move an object" << endl;
    helpText << "       Right click to delete      " << endl;
    helpText << "" << endl;
    helpText << "  Press 'f' to toggle fullscreen  " << endl;
    helpText << " Press 'h' to toggle this message " << endl;

    aboutText << "             <About>              " << endl;
    aboutText << "Particle systems are used in games" << endl;
    aboutText << " and other forms of digital media " << endl;
    aboutText << "to depict complex visuals such as " << endl;
    aboutText << "  electricity, fire, smoke, and   " << endl;
    aboutText << " other kinds of amorphous things. " << endl;
    aboutText << "" << endl;
    aboutText << " There are multiple aspects to a  " << endl;
    aboutText << "   particle system. As the name   " << endl;
    aboutText << "    suggests, an emitter emits    " << endl;
    aboutText << " particles from itself. Particles " << endl;
    aboutText << "  have a set behaviour to follow  " << endl;
    aboutText << "     from equations simple as     " << endl;
    aboutText << "     moving in one direction.     " << endl;
}

//--------------------------------------------------------------
void ofApp::update(){
    deltaTime += ofGetLastFrameTime();

    // -------- update emitters
    for (Emitter* e : emitters) {
        e->update(deltaTime);

        if (e->canSpawn()) {
            Particle* p = parseParticleType(e->getParticleType(), e->getSpawnPosition());
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
            break;
        case areaEmitter:
            s << "Placing Emitter (Area)" << endl;
            break;
        case box:
            s << "Placing Box" << endl;
            break;
    }

    if (mode == emitter || mode == areaEmitter) {
        switch (ptype) {
            case bullet:
                s << "Type: Bullet" << endl;
                break;
            case smoke:
                s << "Type: Smoke" << endl;
                break;
            case spark:
                s << "Type: Spark" << endl;
                break;
            case fire:
                s << "Type: Fire" << endl;
                break;
        }
    }

    ofSetColor(COLORS.FOREGROUND);
    ofDrawBitmapString(s.str().c_str(), vec2(8, 16));

    if (showHelp) {
        ofDrawBitmapStringHighlight(helpText.str().c_str(), vec2(8, 128), COLORS.FOREGROUND, COLORS.BACKGROUND);
        ofDrawBitmapStringHighlight(aboutText.str().c_str(), vec2(8, 512), COLORS.FOREGROUND, COLORS.BACKGROUND);
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
        case 3682:
            ctrl = true;
            break;
    }

    if (!ctrl) {
        switch (key) {
            case '1':
                mode = view;
                break;
            case '2':
                mode = emitter;
                break;
            case '3':
                mode = areaEmitter;
                break;
            case '4':
                mode = box;
                break;
        }
    } else {
        switch (key) {
            case '1':
                ptype = bullet;
                break;
            case '2':
                ptype = smoke;
                break;
            case '3':
                ptype = fire;
                break;
            case '4':
                ptype = spark;
                break;
        }
    }
}

void ofApp::keyReleased(int key) {
    if (key == 3682) {
        ctrl = false;
    }
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

    for (Emitter* e : emitters) {
        if (e->getCaptured()) {
            e->setCaptured(false);
            mouseCaptured = false;
            return;
        }
    }

    if (!mouseCaptured && mode != view) {
        // in each case we are looping through a vector, checking if our mouse's xy coordinates are over each object in the vector.
        // if we are clicking on an object, the function is prematurely ended via `return`
        // if we are not clicking on an object, the function will continue
        // this explains why we are adding new objects at the end of the for loop to the vector we just looped through
        // we generally do not want multiple actions to be happening for each click, as it becomes a confusing user experience
        switch (mode) {
            case emitter:
            case areaEmitter:
                // check if we are clicking inside a box
                // if we are, we return as we do not want the player to spawn emitters within a box or interact with emitters by accident
                for (int i = 0; i < boxes.size(); i++) {
                    if (boxes[i]->getBoundingBox().inside(vec2(x, y))) {
                        return;
                    }
                }
                // check if our mouse xy coordinates are within an emitter's bounding box
                for (int i = 0; i < emitters.size(); i++) {
                    if (emitters[i]->getBoundingBox().inside(vec2(x, y))) {
                        if (button == 0) {
                                emitters[i]->setCaptured(true);
                                mouseCaptured = true;
                        } else if (button == 2) {
                                delete emitters[i];
                                emitters.erase(emitters.begin() + i);
                        }
                        return; // we have interacted with an emitter if we reach the end of the above if statement, so we end prematurely
                    }
                }

                if (button != 0) {
                    return;
                }

                if (mode == emitter) { // if we are left-clicking we spawn a new emitter
                    if (ptype == spark) {
                        emitters.push_back(new Emitter(vec2(x, y), 1, 5, -1, ptype));
                    } else {
                        emitters.push_back(new Emitter(vec2(x, y), 0.25, -1, ptype));
                    }
                } else {
                    emitters.push_back(new AreaEmitter(vec2(x, y), 0.25, -1, ptype));
                }
                break;
            case box:
                // iterate backwards so we are interacting with the box on top of the other boxes first
                for (int i = boxes.size() - 1; i >= 0; i--) {
                    if (boxes[i]->getBoundingBox().inside(vec2(x, y))) {
                        if (button == 0) {
                                boxes[i]->setCaptured(true);
                                mouseCaptured = true;
                        } else if (button == 2) {
                                delete boxes[i];
                                boxes.erase(boxes.begin() + i);
                        }
                        return;
                    }
                }
                // create box
                if (button == 0) {
                    boxes.push_back(new Box(vec2(x, y)));
                    mouseCaptured = true; // when we spawn a box, our mouse is occupied with setting the box's width and height, so we set this to true
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
Particle* ofApp::parseParticleType(ParticleType ptype, vec2 emitterPos) {
    Particle* p;
    switch (ptype) {
        case bullet:
            p = new Particle(
                emitterPos,
                vec2(sin(deltaTime), cos(deltaTime))
            );
            break;
        case smoke:
            p = new SmokeParticle(
                emitterPos,
                vec2(sin(deltaTime) / 10, ofClamp(cos(deltaTime), -0.01, -1))
            );
            break;
        case fire:
            p = new FireParticle(
                emitterPos,
                vec2(sin(deltaTime) / 10, ofClamp(cos(deltaTime), -0.01, -1))
            );
            break;
        case spark:
            p = new SparkParticle(
                emitterPos,
                vec2(ofRandom(0.2) - 0.1, ofRandom(-1))
            );
            break;
    }
    return p;
}