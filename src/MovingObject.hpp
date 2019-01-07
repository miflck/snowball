//
//  MovingObject.hpp
//  moving object
//
//  Created by Flückiger Michael on 08.05.18.
//

#ifndef MovingObject_hpp
#define MovingObject_hpp
#include "ofMain.h"
#include <stdio.h>



class MovingObject {
    
public:
    
    
    int screenWidth=1920;
    int screenHeight=1080;
    
    void setScreenDimensions(int width, int height);
    
    
    MovingObject();
    virtual ~MovingObject();
    
   virtual void setup();
   virtual void update();
   virtual void draw();
    
    
    void setPosition(int x, int y);
    void setPosition(ofVec2f _p);

    ofVec2f getPosition();
    ofVec2f getPositionBefore();
    ofVec2f getPositionDifference();
    
    bool isOnScreen();
    
    ofVec2f getDistance(ofVec2f _t);
    
    void setSpeed(int _x, int _y);
    void setSpeed(ofVec2f _s);
    ofVec2f getSpeed();
    ofVec2f getSpeedBefore();
    
    virtual void setRadius(int radius);
    int getRadius();
    
    
    virtual void setTarget(ofVec2f _target);
    virtual ofVec2f getTarget();

    
    void setMaxSpeed(float _m);
    void move();
    void applyForce(ofVec2f _force);
    void applyForce(ofVec2f _force,float _strength);

    
    ofVec2f seek(ofVec2f t, float f);
    ofVec2f arrive(ofVec2f t);
    float getArriveSpeed(ofVec2f t);


    bool bSeekTarget=true;
    bool bSeekMouse=false;
    
    void scaleTo(float _value);
    void scaleTo(float _value,float _duration);


    float easingInitTime;
    float radiusTarget;
    float actualRadius;
    float initRadius;

    float scaleDuration;
    
    
    void setSeekForce(float _f);
        
    void setSlowDown(bool _b);
    void setSlowDownDistance(int _d);
    
    
    int radius;

   // static bool shouldRemoveOffScreen();
    static bool shouldRemove(shared_ptr<MovingObject> shape);
    static bool shouldRemoveOffScreen(shared_ptr<MovingObject> shape);
    

    
    float wanderR=50;
    float wanderD=500.0f;
    float change=0.3f;
    float wanderforce=0.5;
    
    
    void setWanderForce(float f);
    void setOffscreenForce(float f);
    float offscreenforce;

    float wandertheta;
    bool bWander=false;
    
    void makeNewWanderTarget();
    ofVec3f wander(float f);

    bool bMovingMaxspeed=false;
    
    float initmaxspeed=50;
    float arriveMaxSpeed;

    bool getReached();
    void setReached(bool r);
    

    bool hasGravity();
    void setGravity(bool _b);
    void setGravityForce(ofVec2f f);
    void addForce(ofVec2f fv, float f);
    void addForce(ofVec2f fv);

    void bounceFromGround();
    void bounceFromTop();
    void bounceFromSides();
    
    void setBoundingBox(ofRectangle b);
    
    void setImage(ofImage *_img);
    void setNewImage(ofImage *_img, float _duration);

    
    void addRotation(float _s);
    
    void setDampingDuration(float _d);

private:
    
    
    float groundOffset;
    
    ofImage *image;
    ofImage *newimage;
    
    ofImage *fadeInImage;
    ofImage *fadeOutImage;

    
    float damping=0.9999;
    float dampingInit=0.9999;
    float dampingTarget=0.99;
    float dampDuration=10;
    float dampingInitTime;

    
    float fadeInit=0;
    float fadeTarget=255;
    float actualFade=0;
    float fadeDuration=5;
    float fadeInitTime;
    
    
    float rotationInit=10;
    float rotationTarget=0;
    float actualRotationSpeed=10;
    float rotateDuration=10;
    float rotationInitTime;
    
    
    float bounceDamping=0.01;
    float topDamping=0.5;
    bool bHasReached=true;
    bool bHasGravity=true;
    ofVec2f gravity;

    ofVec2f position;
    
    ofVec2f velocity;
    ofVec2f target;
    ofVec2f oldtarget;

   float maxspeed=50;
    ofVec2f acceleration;
    float seekforce=0.5;
    
    bool bSlowDown=true;
    int slowdowndistance=300;
    
    ofVec2f velocityBefore;
    ofVec2f positionDifference;
    ofVec2f posistionBefore;
    
    ofVec2f externalForceVector;
    float externalforce;
    
    ofRectangle boundingBox;
    
    
    float rotationspeed=0;
    float actualRotation=0;
    
    float maxLandingSpeed=3;
    
    
};


#endif /* MovingObject_hpp */
