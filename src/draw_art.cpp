#include <iostream>
#include "canvas.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   Canvas drawer(640, 380);
   // your code here
   //test Circle

   int radius = 21;
   drawer.background(0, 0, 0);
   drawer.begin(CIRCLES);
   drawer.color(255, 0, 255);
   drawer.vertex(10, 0);
   drawer.color(0, 255, 255);
   drawer.vertex(90, 50);
   drawer.color(255, 255, 0);
   drawer.vertex(10, 90);
   drawer.end();
   drawer.save("circle.png");
}

