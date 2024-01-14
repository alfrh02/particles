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
		void keyReleased(int key);

		bool ctrl = false;

		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		bool mouseCaptured = false;

		double deltaTime = 0;

		Particle* parseParticleType(ParticleType ptype, vec2 emitterPos);
		ParticleType ptype = bullet;

		enum Mode { view, emitter, box, areaEmitter };
		Mode mode = view;

		bool showHelp = true;
		stringstream helpText;
		stringstream aboutText;

		vector<Emitter*> emitters;
		vector<Particle*> particles;
		vector<Box*> boxes;
};
