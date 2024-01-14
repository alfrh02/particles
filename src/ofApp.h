#pragma once

#include <vector>
#include "ofMain.h"
#include "ofxGui.h"

#include "particle.h"
#include "smokeParticle.h"
#include "sparkParticle.h"
#include "fireParticle.h"
#include "rainParticle.h"
#include "bubbleParticle.h"

#include "emitter.h"
#include "areaEmitter.h"
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

		Particle* parseParticleType(ParticleType ptype, vec2 emitterPos);

		double deltaTime = 0;

		enum Mode { view, emitter, box, areaEmitter };
		Mode mode = view;

		bool showHelp = true;
		stringstream helpText;
		stringstream aboutText;

		struct EmitterPreset {
			float spawnIntervalRangeBegin = 0.25;
			float spawnIntervalRangeEnd = 0.25;
			unsigned short maxParticles = -1;
			ParticleType ptype = bullet;
		};

		EmitterPreset bulletPreset;
		EmitterPreset smokePreset;
		EmitterPreset firePreset;
		EmitterPreset sparkPreset;
		EmitterPreset rainPreset;
		EmitterPreset bubblePreset;

		EmitterPreset emitterType = bulletPreset;

		vector<Emitter*>  emitters;
		vector<Particle*> particles;
		vector<Box*>      boxes;
};
