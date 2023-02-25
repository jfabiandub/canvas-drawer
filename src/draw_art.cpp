#include <iostream>
#include "canvas.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   Canvas drawer(800, 600);
   // your code here

   //test Circle
   //int radius = 21;
   drawer.setRad(15);
   drawer.background(0, 0, 0);
   drawer.begin(CIRCLES);
   drawer.color(255, 0, 0);
   drawer.vertex(50, 50);
   drawer.vertex(10, 10);
   drawer.vertex(90, 50);
   drawer.color(140,229,158);

   drawer.end();
   drawer.save("circle.png");

/*
   //draaws a rose, outlined 
   drawer.background(255, 255, 255);
   Vertex center = {400, 300};
   int numPetals = 6;
   int rad = 150;
   bool fill = false;
   drawer.drawRose(center, numPetals, rad, fill);
   drawer.save("rose.png");
*/
   
   Canvas j(800, 800);
   j.background(255, 255, 255);
j.color(255, 0, 0);
j.drawRoses(400, 400, 200, 8, true); // Draw a filled rose with 8 petals
j.color(0, 0, 255);
j.drawRoses(400, 400, 200, 5, false); // Draw an outlined rose with 5 petals
j.save("roses.png");







   //draws a rectangle
   Canvas canvas(800, 600);
   canvas.background(255, 255, 255);
   canvas.color(255, 0, 0);
   canvas.drawRectangle(400, 300, 200, 100);
   canvas.save("rectangle.png");

   
   

   return 0;
}

