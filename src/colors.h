#pragma once
//--------------------------------------------------------------
const struct {
    ofColor WHITE = ofColor(128, 128, 128);
    ofColor GRAY = ofColor(32);
    ofColor DARK_GRAY = ofColor(96);
    ofColor BLACK = ofColor(0);

    ofColor RED = ofColor(255, 32, 32);
    ofColor GREEN = ofColor(0, 255, 0);
    ofColor YELLOW = ofColor(255, 255, 0);

    ofColor FOREGROUND = BLACK;
    ofColor BACKGROUND = WHITE;
    ofColor HIGHLIGHT = RED;

    ofColor EMITTER = BLACK;

    ofColor TEXT = BLACK;

    ofColor DIRECTION = BLACK;
    ofColor BOUNDING_BOX = RED;

    unsigned char SMOKE_ALPHA = 128;
    ofColor SMOKE[5] = {
        ofColor(24,  24,  24,  SMOKE_ALPHA),
        ofColor(48,  48,  48,  SMOKE_ALPHA),
        ofColor(72,  72,  72,  SMOKE_ALPHA),
        ofColor(96,  96,  96,  SMOKE_ALPHA),
        ofColor(120, 120, 120, SMOKE_ALPHA)
    };

    ofColor ELECTRIC = YELLOW;
} COLORS;