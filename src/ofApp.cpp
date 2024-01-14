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
    // -------- gui setup

    gui.setBackgroundColor(COLORS.FOREGROUND);
    gui.setDefaultTextColor(COLORS.BACKGROUND);
    gui.setTextColor(COLORS.BACKGROUND);

    gui.setup("Edit Emitter");
    gui.add(guiSpawnInterval.set("Spawn Interval", 0.25, 0, 30));
    gui.add(guiIsUsingRange.set("Using Range", false, 18, 18));
    gui.add(guiSpawnRange.set("Spawn Range", 0, 0, 30));
    gui.add(guiMaxParticles.set("Max Particles", -1, -1, 1024));
    gui.setPosition(ofGetWidth() - 256, 128);

    guiSpawnInterval.addListener(this, &ofApp::setSelectedSpawnInterval);
    guiIsUsingRange.addListener(this, &ofApp::setSelectedUsingRange);
    guiSpawnRange.addListener(this, &ofApp::setSelectedSpawnRangeEnd);
    guiMaxParticles.addListener(this, &ofApp::setSelectedMaxParticles);

    // -------- emitter presets
	smokePreset.ptype = smoke;

	firePreset.ptype  = fire;
    firePreset.spawnIntervalRangeBegin  = 0.1;
    firePreset.spawnIntervalRangeEnd    = 0.1;

	sparkPreset.ptype = spark;
    sparkPreset.spawnIntervalRangeBegin = 1;
    sparkPreset.spawnIntervalRangeEnd   = 3;

    rainPreset.ptype  = rain;
    rainPreset.spawnIntervalRangeBegin  = 0.01;
    rainPreset.spawnIntervalRangeEnd    = 0.05;

    rainPreset.ptype  = bubble;
    rainPreset.spawnIntervalRangeBegin  = 0;
    rainPreset.spawnIntervalRangeEnd    = 1;

    // -------- help text, about text
    helpText << "       <Particle Simulator>       " << endl;
    helpText << "" << endl;
    helpText << "Use keys 1-4 to switch mode.      " << endl;
    helpText << "" << endl;
    helpText << "     1: View                      " << endl;
    helpText << "     2: Placing Emitter           " << endl;
    helpText << "     3: Placing Area Emitter      " << endl;
    helpText << "     4: Placing Box/Obstacle      " << endl;
    helpText << "" << endl;
    helpText << "Left click to place/move an object" << endl;
    helpText << "Right click to delete             " << endl;
    helpText << "" << endl;
    helpText << "Emitters create particles. In this" << endl;
    helpText << "example, an emitter can either be " << endl;
    helpText << "one point in space, or be an area." << endl;
    helpText << "Area emitters will spawn particles" << endl;
    helpText << "in their given area, but regular  " << endl;
    helpText << "emitters will spawn particles only" << endl;
    helpText << "on their position. Some particle  " << endl;
    helpText << "types are intended for use with an" << endl;
    helpText << "area emitter." << endl;
    helpText << "" << endl;
    helpText << "When placing emitters use control " << endl;
    helpText << "and keys 1-5 to switch through    " << endl;
    helpText << "particle types." << endl;
    helpText << "" << endl;
    helpText << "     1: Bullet                    " << endl;
    helpText << "     2: Smoke                     " << endl;
    helpText << "     3: Fire                      " << endl;
    helpText << "     4: Spark                     " << endl;
    helpText << "     5: Rain                      " << endl;
    helpText << "     6: Bubble                    " << endl;
    helpText << "" << endl;
    helpText << "When in a 'placing' mode emitters " << endl;
    helpText << "will be visible and particles     " << endl;
    helpText << "will show their direction." << endl;
    helpText << "" << endl;
    helpText << "You can edit an emitter's settings" << endl;
    helpText << "with the 'Edit Emitter' GUI. The  " << endl;
    helpText << "Spawn Interval property controls  " << endl;
    helpText << "how often a particle will be      " << endl;
    helpText << "spawned (in seconds)."        << endl;
    helpText << "" << endl;
    helpText << "Emitters can also create particles" << endl;
    helpText << "with random spawn intervals.      " << endl;
    helpText << "To enable this, toggle the Using  " << endl;
    helpText << "Range property and set the Spawn  " << endl;
    helpText << "Range property to something below " << endl;
    helpText << "the Spawn Interval property.      " << endl;
    helpText << "For example, an Emitter with a    " << endl;
    helpText << "Spawn Interval of 1 and a Spawn   " << endl;
    helpText << "Range of 5 will spawn a particle  " << endl;
    helpText << "every 1-5 seconds." << endl;
    helpText << "" << endl;
    helpText << "Press 'f' to toggle fullscreen   " << endl;
    helpText << "Press 'h' to toggle this message " << endl;

    aboutText << "    <About Particle Systems>      " << endl;
    aboutText << "Particle systems are used in games" << endl;
    aboutText << "and other forms of digital media  " << endl;
    aboutText << "to depict complex visuals such as " << endl;
    aboutText << "electricity, fire, smoke, and     " << endl;
    aboutText << "other kinds of amorphous things.  " << endl;
    aboutText << "" << endl;
    aboutText << "A particle is a type of entity    " << endl;
    aboutText << "that is used to represent a small " << endl;
    aboutText << "object. Particles are kept very   " << endl;
    aboutText << "simple for computational reasons, " << endl;
    aboutText << "as many particles are often needed" << endl;
    aboutText << "to represent complex environments." << endl;
    aboutText << "" << endl;
    aboutText << "Particle emitters are points in   " << endl;
    aboutText << "space that are the staging point  " << endl;
    aboutText << "for particles to spawn at." << endl;
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
    ofSetColor(COLORS.FOREGROUND);

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

    ofDrawBitmapString(s.str().c_str(), vec2(8, 16));

    mouseText = "";
    switch (mode) {
        case view:
            mouseText = "View";
            break;
        case emitter:
            mouseText = "Placing Emitter";
            break;
        case areaEmitter:
            mouseText = "Placing Area Emitter";
            break;
        case box:
            mouseText = "Placing Box";
            break;
    }

    mouseText += "\n";

    if (mode == emitter || mode == areaEmitter) {
        switch (emitterType.ptype) {
            case bullet:
                mouseText += "Type: Bullet";
                break;
            case smoke:
                mouseText += "Type: Smoke";
                break;
            case spark:
                mouseText += "Type: Spark";
                break;
            case fire:
                mouseText += "Type: Fire";
                break;
            case rain:
                mouseText += "Type: Rain";
                break;
            case bubble:
                mouseText += "Type: Bubble";
                break;
        }
    }

    // each character is 8px wide & 11px tall
    if (showHelp) {
        ofDrawBitmapStringHighlight(helpText.str().c_str(), vec2(8, 16), COLORS.FOREGROUND, COLORS.BACKGROUND);
        // the max string length of a string within helpText is 34
        ofDrawBitmapStringHighlight(aboutText.str().c_str(), vec2(24 + (34*8), 16), COLORS.FOREGROUND, COLORS.BACKGROUND);
    }

    if (mode != view) {
        // centre text right under cursor so as to not obstruct the user's view
        ofDrawBitmapStringHighlight(mouseText, vec2(ofGetMouseX() - ((text.length() * 8) / 2), ofGetMouseY() + 44), COLORS.FOREGROUND, COLORS.BACKGROUND);
        gui.draw();
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
                emitterType = bulletPreset;
                break;
            case '2':
                emitterType = smokePreset;
                break;
            case '3':
                emitterType = firePreset;
                break;
            case '4':
                emitterType = sparkPreset;
                break;
            case '5':
                emitterType = rainPreset;
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
                            selectedEmitter = emitters[i];
                            updateGui(emitters[i]);
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

                Emitter* e;
                if (mode == emitter) { // if we are left-clicking we spawn a new emitter
                    e = new Emitter(vec2(x, y), emitterType.spawnIntervalRangeBegin, emitterType.spawnIntervalRangeEnd, emitterType.maxParticles, emitterType.ptype);
                } else {
                    e = new AreaEmitter(vec2(x, y), emitterType.spawnIntervalRangeBegin, emitterType.spawnIntervalRangeEnd, emitterType.maxParticles, emitterType.ptype);
                }
                emitters.push_back(e);
                selectedEmitter = emitters[emitters.size() - 1];
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
        case rain:
            p = new RainParticle(
                emitterPos,
                vec2(0.8, 1)
            );
            break;
        case bubble:
            p = new BubbleParticle(
                emitterPos,
                vec2(sin(deltaTime) / 4, ofClamp(cos(deltaTime), -0.01, -1))
            );
            break;
    }
    return p;
}

void ofApp::updateGui(Emitter* e) {
    guiSpawnInterval = e->getSpawnRangeBegin();
    guiIsUsingRange = e->getIsUsingRange();
    guiSpawnRange = e->getSpawnRangeEnd();
    guiMaxParticles = e->getMaxParticles();
    if (guiMaxParticles > 1024) {
        guiMaxParticles = -1;
    }
}

void ofApp::setSelectedSpawnInterval(float& spawnInterval) {
    selectedEmitter->setSpawnInterval(spawnInterval);
}

void ofApp::setSelectedUsingRange(bool& usingRange) {
    selectedEmitter->setUsingRange(usingRange);
}

void ofApp::setSelectedSpawnRangeEnd(float& spawnRange) {
    if (guiIsUsingRange) {
        selectedEmitter->setSpawnRangeEnd(spawnRange);
    }
}

void ofApp::setSelectedMaxParticles(int& maxParticles) {
    selectedEmitter->setMaxParticles(maxParticles);
}