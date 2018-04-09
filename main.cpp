#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "orbit.h"

using namespace std;
using namespace sf;

#define max_iteration 1000
#define xMax 2000
#define yMax 1600

Vector2f getLocation(int total, int num)
{
	Vector2f start = Vector2f(30, 360);
	float rad = 3.1415926535 / 180;
	float radius = 300;
	float degree = 360.f / total;
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
		return Vector2f(630, 360);
	}
	float ylen = (hyp * sin(otherdeg * rad));
	float xlen = (hyp * sin((90 - otherdeg) * rad));
	if (xlen < 0)
	{
		xlen *= -1;
	}

	cout << num << ": " << degfrom << " " << 30 + xlen << " " << 360 - toplen << " " << hyp << endl;
	return Vector2f((30 + xlen), (360 - ylen));
}

float toDegrees(float radians)
{
    return radians * (180.f / M_PI);
}

float toRadians(float degrees)
{
    return degrees * (M_PI / 180.f);
}

RectangleShape connect(sf::CircleShape circle1, sf::CircleShape circle2, int col)
{
    Vector2f mid, size, angle;
    
    //calculate mid point
    mid.x = ((circle1.getGlobalBounds().left + circle1.getRadius()) - (circle2.getGlobalBounds().left + circle2.getRadius())) / 2;
    mid.y = ((circle1.getGlobalBounds().top + circle1.getRadius()) - (circle2.getGlobalBounds().top + circle2.getRadius())) / 2;
    
    //here we set angle because we can just take the arc tan of these values to get the angle necessary
    angle = mid;
    
    //pythagreans
    size.x = sqrt(((mid.x * 2) * (mid.x * 2)) + ((mid.y * 2) * (mid.y * 2)));
    size.y = 1;
    
    //the middle position can be referenced based on the position of what you are connecting to
    mid.x += circle2.getGlobalBounds().left + circle2.getRadius();
    mid.y += circle2.getGlobalBounds().top + circle2.getRadius();
    
    //make the rectangle
    RectangleShape toRet;
    toRet.setSize(size);
    toRet.setOrigin(size.x/2, size.y/2);
    toRet.setPosition(mid);

    toRet.setFillColor(sf::Color::White);

    toRet.setRotation(toDegrees(atan(angle.y/angle.x)));
    
    return toRet;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(xMax, yMax), "Wormhole");//720X720
	Clock clock;
	Time spawntime;

	srand(time(NULL));//I came to plant my seed
    
    //Pretty Neat
    //orbit outerOrbit(500,100,xMax,yMax);
    //orbit innerOrbit(300,30,xMax,yMax);
    
    //start shape
    //orbit outerOrbit(500,120,xMax,yMax);
    //orbit innerOrbit(200,70,xMax,yMax);
    
    //so perfect
    orbit outerOrbit(500,120,xMax,yMax);
    orbit innerOrbit(350,88,xMax,yMax);
    
    //orbit outerOrbit(600,120,xMax,yMax);
    //orbit innerOrbit(520,95,xMax,yMax);
    
    /*orbit outerOrbit2(300,120,2000,600);
    orbit innerOrbit2(250,95,2000,600);
    
    orbit outerOrbit3(300,120,1600,2000);
    orbit innerOrbit3(250,107,1600,2000);*/
    vector<RectangleShape> connectingRects, connectingRects2, connectingRects3;
	

	Clock myclock, outC;
	Time mytime;
	float sec;
    int colNum = 0;
    bool outGrow = true, inGrow = false;
    int curGrow = 0, maxGrow = 300, rectPoint = 0;
    
    //CircleShape *farCircle = farOrbit.getNextCircle();
    CircleShape *outCircle = outerOrbit.getNextCircle();
    CircleShape *inCircle = innerOrbit.getNextCircle();
    
    /*CircleShape *outCircle2 = outerOrbit2.getNextCircle();
    CircleShape *inCircle2 = innerOrbit2.getNextCircle();
    
    CircleShape *outCircle3 = outerOrbit3.getNextCircle();
    CircleShape *inCircle3 = innerOrbit3.getNextCircle();*/
    
    outCircle->setFillColor(Color::Red);
    inCircle->setFillColor(Color::Red);
    
    /*outCircle2->setFillColor(Color::Red);
    inCircle2->setFillColor(Color::Red);
    
    outCircle3->setFillColor(Color::Red);
    inCircle3->setFillColor(Color::Red);*/
    
    connectingRects.push_back(connect(*outCircle, *inCircle,colNum));
    //connectingRects2.push_back(connect(*outCircle2, *inCircle2,colNum));
    //connectingRects3.push_back(connect(*outCircle3, *inCircle3,colNum));
    colNum++;
    
	while (window.isOpen())
	{
		window.clear();
		mytime = myclock.getElapsedTime();
        sec = mytime.asMilliseconds();
		if (sec > 10)
		{
            
            
            /*if(curGrow >= maxGrow)
            {
                outGrow = false;
            }
            else if(curGrow < 0)
            {
                outGrow = true;
            }
            
            if(outGrow)
            {
                outerOrbit.changeRadius(-1.f);
                innerOrbit.changeRadius(1.f);
                curGrow++;
            }
            else
            {
                outerOrbit.changeRadius(1.f);
                innerOrbit.changeRadius(-1.f);
                curGrow--;
            }*/
			
            //farCircle = farOrbit.getNextCircle();
            outCircle = outerOrbit.getNextCircle();
            inCircle = innerOrbit.getNextCircle();
            
            /*outCircle2 = outerOrbit2.getNextCircle();
            inCircle2 = innerOrbit2.getNextCircle();
            
            outCircle3 = outerOrbit3.getNextCircle();
            inCircle3 = innerOrbit3.getNextCircle();
            
            outCircle2->setFillColor(Color::Red);
            inCircle2->setFillColor(Color::Red);
            
            outCircle3->setFillColor(Color::Red);
            inCircle3->setFillColor(Color::Red);*/
            
            //farCircle->setFillColor(Color::Red);
            outCircle->setFillColor(Color::Red);
            inCircle->setFillColor(Color::Red);
            if(connectingRects.size() == 10000)
            {
                connectingRects[rectPoint] = connect(*outCircle, *inCircle,colNum);
                //connectingRects2[rectPoint] = connect(*outCircle2, *inCircle2,colNum);
                //connectingRects3[rectPoint] = connect(*outCircle3, *inCircle3,colNum);
                rectPoint++;
                if(rectPoint == 10000)
                {
                    rectPoint = 0;
                }
            }
            else
            {
                connectingRects.push_back(connect(*outCircle, *inCircle,colNum));
                //connectingRects2.push_back(connect(*outCircle2, *inCircle2,colNum));
                //connectingRects3.push_back(connect(*outCircle3, *inCircle3,colNum));
            }
            //connectingRects.push_back(connect(*farCircle, *outCircle,colNum));
            
			myclock.restart();
		}
		/*for (auto cur : outerOrbit.orbitShapes)
		{
			window.draw(*cur);
		}
        
        for (auto cur : innerOrbit.orbitShapes)
        {
            window.draw(*cur);
        }*/
        
        //window.draw(*farCircle);
        window.draw(*outCircle);
        window.draw(*inCircle);
        
        for (auto cur : connectingRects)
        {
            window.draw(cur);
        }
        
        /*for (auto cur : connectingRects2)
        {
            window.draw(cur);
        }
        
        for (auto cur : connectingRects3)
        {
            window.draw(cur);
        }*/
        
		//window.draw(points);
		window.display();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();

			}

		}//checks if the window was closed, I should probably make this in a function somewhere
	}

	return 0;
}