#include "canvas.h"
#include <cassert>
#include "image.h"
#include "math.h"

using namespace std;
using namespace agl;

Canvas::Canvas(int w, int h) : _canvas(w, h){
   Image image(w ,h);
   this->_canvas = image;
}

Canvas::~Canvas(){ 
}

void Canvas::save(const std::string& filename){
   _canvas.save(filename);
}

void Canvas::begin(PrimitiveType type){

  myPrimType = type;
  myVertices.clear();
}

void Canvas::end(){
   if(myPrimType== LINES && myVertices.size() % 2==0){
      for(int i=0; i< myVertices.size(); i += 2){
         bresenhamLine(myVertices[i], myVertices[i+1]);
      }
   }
   else if(myPrimType == TRIANGLES && myVertices.size() % 3 == 0){
      for(int i = 0; i < myVertices.size(); i += 3){
         drawTriangle(myVertices[i], myVertices[i + 1], myVertices[i + 2]);
      }
   }
   myPrimType = UNDEFINED;   
   myVertices.clear();          

}

void Canvas::vertex(int x, int y){
   Vertex vert = {x, y, currentCol};
   myVertices.push_back(vert);
}

void Canvas::color(unsigned char r, unsigned char g, unsigned char b){
   Pixel col;
   col.r = r;
   col.g = g;
   col.b = b;
   currentCol = col;
}

void Canvas::background(unsigned char r, unsigned char g, unsigned char b){
   Pixel backg;
   backg.r = r;
   backg.g = g;
   backg.b = g;
   _canvas.fill(backg);
}

void Canvas::bresenhamLine(Vertex a, Vertex b){
   
   int w = b.x - a.x;
   int h = b.y -a.y;

   if(abs(h) < abs(w)){
      if(a.x > b.x){
         drawLowLine(b,a);
      }
      else{
         drawLowLine(a,b);
      }
   }
   else{
      if(a.y > b.y){
         drawHighLine(b,a);
      }
      else{
         drawHighLine(a,b);
      }
   }

}

   
void Canvas::drawHighLine(Vertex a, Vertex b){  
   int x = a.x;
   int w = b.x -a.x;   
   int h = b.y -a.y;
   int dx = 1;

   if(w < 0){
      dx = -1;
      w *= -1 ;
   }

   int F = (2 * w) - h;

   for(int y = a.y; y <= b.y; y++){
      float t = sqrt(pow(myVertices[0].x - x, 2) + pow(myVertices[0].y - y, 2))/sqrt(pow(myVertices[1].x - x, 2) + pow(myVertices[1].y - myVertices[0].y, 2));
      Pixel temps; 
      temps.r = myVertices[0].color.r * (1 - t) + myVertices[1].color.r * t;
      temps.g = myVertices[0].color.g * (1 - t) + myVertices[1].color.g * t;
      temps.b = myVertices[0].color.b * (1 - t) + myVertices[1].color.b * t;
      _canvas.set(y,x,temps);

      if(F > 0){
         x += dx;
         F += 2 * (w - h);
      }
      else{
         F += 2 * w;
      }
   }
}

   void Canvas::drawLowLine(Vertex a, Vertex b){
   int y = a.y;
   int W = b.x - a.x;
   int H = b.y - a.y;
   int dy = 1;

   if(H < 0){
      dy = -1;
      H *=-1;
   }

   int F = (2 * H) - W;
   for(int x = a.x; x <= b.x; x++){
      float t = sqrt(pow(myVertices[0].x - x, 2) + pow(myVertices[0].y - y, 2))/sqrt(pow(myVertices[1].x - x, 2) + pow(myVertices[1].y - myVertices[0].y, 2));
      Pixel temps; 
      temps.r = myVertices[0].color.r * (1 - t) + myVertices[1].color.r * t;
      temps.g = myVertices[0].color.g * (1 - t) + myVertices[1].color.g * t;
      temps.b = myVertices[0].color.b * (1 - t) + myVertices[1].color.b * t;
      _canvas.set(y,x,temps);

      if(F > 0){
         y += dy;
         F += 2 * (H - W);
      }
      else {
         F += 2 * H;
      }
   }
}



void Canvas::drawTriangle(Vertex a, Vertex b, Vertex c) {
      int xMin = min(min(a.x, b.x), c.x);
    int xMax = max(max(a.x, b.x), c.x);
    int yMin = min(min(a.y, b.y), c.y);
    int yMax = max(max(a.y, b.y), c.y);

  for (int y = yMin; y < yMax; y++) {
    for (int x = xMin; x < xMax; x++) {
      float alpha = (float)((b.y - c.y) * x + (c.x - b.x) * y + (b.x * c.y) - (c.x * b.y)) / 
      (float)((b.y - c.y) * a.x + (c.x - b.x) * a.y + (b.x * c.y) - (c.x * b.y));
      
      float gamma = (float)((a.y - b.y) * x + (b.x - a.x) * y + (a.x * b.y) - (b.x * a.y)) /
      (float)((a.y - b.y) * c.x + (b.x - a.x) * c.y + (a.x * b.y) - (b.x * a.y));

      float beta = 1-alpha - gamma;

      if (alpha >= 0 && beta >= 0 && gamma >= 0) {
        Pixel pixel = {0, 0, 0};

        pixel.r = alpha * a.color.r + beta * b.color.r + gamma * c.color.r;
        pixel.g = alpha * a.color.g + beta * b.color.g + gamma * c.color.g;
        pixel.b = alpha * a.color.b + beta * b.color.b + gamma * c.color.b;

        _canvas.set(y, x, pixel);
      }
    }
  }
}



