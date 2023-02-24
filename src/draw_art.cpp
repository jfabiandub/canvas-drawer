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
   //drawer.setRad(100);
   drawer.color(255, 0, 0);
   drawer.vertex(50, 50);
  // drawer.color(0, 255, 255);
   //drawer.vertex(90, 50);
  // drawer.color(255, 255, 0);
   //drawer.vertex(10, 90);
   drawer.end();
   drawer.save("circle.png");


   //draaws a rose?
   drawer.background(255, 255, 255);
   Vertex center = {50, 50, {255, 0, 0}};
   drawer.drawRose(center, 2, 50);
   drawer.save("rose.png");
   return 0;


}

