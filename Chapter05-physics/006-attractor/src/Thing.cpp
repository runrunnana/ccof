//
//  Thing.cpp
//  attractor
//
//  Created by Jeffrey Crouse on 10/27/17.
//

#include "Thing.hpp"


Thing::Thing() {
    max_vel = 10.0;
    mass = ofRandom(5.0, 10.5);
    bounce = .6;
    loc.x = ofRandomWidth();
    loc.y = ofRandomHeight();
    G = 0.9;
}

void Thing::update() {
    vel += acc;
    vel.x = ofClamp(vel.x, -max_vel, max_vel);
    vel.y = ofClamp(vel.y, -max_vel, max_vel);
    loc += vel;
    acc.set(0,0);
    
    if (loc.y > ofGetHeight()) {
        vel.y *= -bounce;
        loc.y = ofGetHeight();
    }
    if ((loc.x > ofGetWidth()) || (loc.x < 0)) {
        vel.x *= -bounce;
    }
    //if (loc.x < 0)     loc.x = ofGetWidth();
    //if (loc.x > ofGetWidth()) loc.x = 0;
    
}

// Renders a vector object 'v' as an arrow and a location 'loc'
void Thing::drawVector(float scayl) {
    
    float angle = (float)atan2(-vel.y, vel.x);
    float theta =  -1.0*angle;
    float heading2D = ofRadToDeg(theta);
    float mag = sqrt(vel.x*vel.x + vel.y*vel.y);
    
    ofSetHexColor(0x000000);
    ofNoFill();
    
    ofPushMatrix();
    float arrowsize = 4;
    // Translate to location to render vector
    ofTranslate(loc.x,loc.y);
    // Call vector heading function to get direction (note that pointing up is a heading of 0) and rotate
    ofRotate(heading2D);
    // Calculate length of vector & scale it to be bigger or smaller if necessary
    float len = mag*scayl;
    // Draw three lines to make an arrow (draw pointing up since we've rotate to the proper direction)
    ofLine(0,0,len,0);
    ofLine(len, 0, len-arrowsize, +arrowsize/2);
    ofLine(len, 0, len-arrowsize, -arrowsize/2);
    ofPopMatrix();
}

ofPoint Thing::calcGravForce(Thing* t) {
    ofPoint dir = t->loc - loc;                                // Calculate direction of force
    float d = ofDist(t->loc.x, t->loc.y, loc.x, loc.y);        // Distance between objects
    d = ofClamp(d, 20.0, 50.0);                                // Limiting the distance to eliminate "extreme" results for very close or very far objects
    dir /= d;                                                // Normalize vector (distance doesn't matter here, we just want this vector for direction)
    
    float force = (G * mass * t->mass) / (d * d);            // Calculate gravitional force magnitude
    dir *= force;                                            // Get force vector --> magnitude * direction
    
    
    return dir;
}



void Thing::applyForce(ofPoint force) {
    force /= mass;
    acc += force;
}

void Thing::draw() {
    ofFill();
    ofSetHexColor(0x999999);
    ofCircle(loc.x, loc.y, mass*5);
    drawVector(10);
}
