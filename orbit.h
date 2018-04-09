//
//  orbit.h
//  planetOrbit
//
//  Created by Matthew Green on 4/6/18.
//  Copyright (c) 2018 AppsVerde. All rights reserved.
//

#ifndef planetOrbit_orbit_h
#define planetOrbit_orbit_h

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;
using namespace sf;

class orbit
{
private:
    float radius;
    int totalCircles;
    int xSize;
    int ySize;
    int curCircle;
    
    Vector2f getLocation(int num)
    {
        Vector2f start = Vector2f((xSize / 2) - radius, ySize / 2);
        float rad = 3.1415926535 / 180;
        float degree = 360.f / (float)totalCircles;
        float degfrom = degree * (float)num;
        float otherdeg = (180 - degfrom) / 2;
        // (A / sin(a)) * sin(b) = B
        float test = sin(otherdeg * rad);
        float hyp = (radius / sin(otherdeg * rad)) * sin(degfrom * rad);
        float newdeg = 90 - otherdeg;
        float toplen = hyp * sin(newdeg * rad);
        
        if (test < 0)
        {
            toplen *= -1;
        }
        
        if (num == 0)
        {
            return start;
        }
        if (degfrom == 180)
        {
            return Vector2f((xSize / 2) + radius, (ySize / 2));
        }
        float ylen = (hyp * sin(otherdeg * rad));
        float xlen = (hyp * sin((90 - otherdeg) * rad));
        if (xlen < 0)
        {
            xlen *= -1;
        }
        
        //cout << num << ": " << degfrom << " " << 30 + xlen << " " << 360 - toplen << " " << hyp << endl;
        return Vector2f(((xSize / 2) - radius + xlen), ((ySize / 2) - ylen));
    }
    
    
public:
    vector< CircleShape* > orbitShapes;
    
    orbit(float orbitRadius, int numCircles, int windowX, int windowY)
    {
        radius = orbitRadius;
        totalCircles = numCircles;
        xSize = windowX;
        ySize = windowY;
        curCircle = 0;
        
        for(int i = 0; i < totalCircles; i++)
        {
            CircleShape *newCircle = new CircleShape();
            newCircle->setPosition(this->getLocation(i));
            newCircle->setRadius(10.f);
            newCircle->setFillColor(sf::Color::Blue);
            orbitShapes.push_back(newCircle);
        }
    }
    
    CircleShape *getNextCircle()
    {
        CircleShape *toRet = orbitShapes[curCircle];
        
        curCircle++;
        
        if(curCircle == totalCircles)
        {
            curCircle = 0;
        }
        
        return toRet;
    }
    
    void changeRadius(float alterSize)
    {
        radius += alterSize;
        if(radius < 1)
        {
            radius = 1;
        }
        for(int i = 0; i < totalCircles; i++)
        {
            orbitShapes[i]->setPosition(getLocation(i));
        }
    }
};


#endif
