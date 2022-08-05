#pragma once
#include "../include/glMath.h"

struct persArgs
{
    float fov;
    float sw;
    float sh;
    float nearZ;
    float farZ;
    persArgs(float f, float sw, float sh, float nz, float fz)
    {
        fov = f;
        this->sw = sw;
        this->sh = sh;
        nearZ = nz;
        farZ = fz;
    }
};

struct mouseArgs
{
    bool firstMouse;
    float yaw;	
    float pitch;
    float lastX;
    float lastY;
    mouseArgs(){}
    mouseArgs (bool first, float y, float p, float lX, float lY)
    {
       firstMouse = first;
       yaw = y;	
       pitch = p;
       lastX = lX;
       lastY = lY;
    }
    void create (bool first, float y, float p, float lX, float lY)
    {
       firstMouse = first;
       yaw = y;	
       pitch = p;
       lastX = lX;
       lastY = lY;
    }
};

struct cameraArgs
{
    glMath::vec3f cameraPos;
    glMath::vec3f cameraFront;
    glMath::vec3f cameraUp;
    cameraArgs(){}
    cameraArgs(glMath::vec3f cp, glMath::vec3f cf, glMath::vec3f cu) : cameraPos(cp), cameraFront(cf), cameraUp(cu) {}
    void create(glMath::vec3f cp, glMath::vec3f cf, glMath::vec3f cu) {
        cameraPos = cp;
        cameraFront = cf;
        cameraUp = cu;
    }
};