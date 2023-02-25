#include <iostream>
#include "canvas.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   Canvas drawer(100, 100);
   // your code here

   //test Circle
   //int radius = 21;
   drawer.setRad(15);
   drawer.background(255, 255, 255);
   drawer.begin(CIRCLES);
   drawer.color(255, 0, 0);
   drawer.vertex(50, 50);
   drawer.end();
   drawer.save("circle.png");


   //draaws a rose?
   drawer.background(255, 255, 255);
   Vertex center = {50, 50, {255, 0, 0}};
   drawer.drawRose(center, 2, 50);
   drawer.save("rose.png");


   //draws a rectangle
   Canvas canvas(800, 600);
   canvas.background(255, 255, 255);
   canvas.color(255, 0, 0);
   canvas.drawRectangle(400, 300, 200, 100);
   canvas.save("rectangle.png");


   return 0;



}

