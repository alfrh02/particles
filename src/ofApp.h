#pragma once

#include <vector>
#include "ofMain.h"
#include "ofxGui.h"

#include "particle.h"
#include "smokeParticle.h"
#include "sparkParticle.h"
#include "fireParticle.h"

#include "emitter.h"
#include "box.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		~ofApp();

		void setup();
		void update();
		void draw();

		void keyPressed(int key);

		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		Particle* parseParticleType(ParticleType ptype, vec2 emitterPos);
		ParticleType ptype = spiral;

		double deltaTime = 0;

		enum Mode { view, emitter, box };
		Mode mode = view;

		bool showHelp = true;
		bool mouseCaptured = false;

		stringstream helpText;

		vector<Emitter*> emitters;
		vector<Particle*> particles;
		vector<Box*> boxes;
};
