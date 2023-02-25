#include <iostream>
#include "canvas.h"
#include "math.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   Canvas drawer(100, 100);
   // your code here

   //test Circle
   drawer.setRad(15);
   drawer.background(0, 0, 0);
   drawer.begin(CIRCLES);
   drawer.color(255, 0, 0);
   drawer.vertex(50, 50);
   drawer.vertex(10, 10);
   drawer.vertex(90, 50);
   drawer.color(140,229,158);

   //test triangle
   drawer.end();
   drawer.save("circle.png");

   drawer.background(0, 0, 0);
   drawer.begin(TRIANGLES);
   drawer.color(141,125,202);
   drawer.vertex(20, 45);
   drawer.color(142,220,228);
   drawer.vertex(90, 10);
   drawer.vertex(10, 90);
   drawer.end();
   drawer.save("triangle.png");


   //draaws a rose
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



   Canvas pic(800, 800);
    
    // Draw a sunset scene  (it didnt work :( )
   pic.background(255, 153, 51); 
   pic.begin(LINES); 
   pic.color(255, 255, 0); 
    
    // Draw sun rays
   for (int i = 0; i < 360; i+= 10) {
      pic.vertex(300, 300);
      pic.vertex(300 + 200 * cos(i), 300 + 200 * sin(i));
   }
   pic.end(); 
    
   pic.setRad(100); 
    
   // Draw clouds
   pic.color(255, 255, 255); 
   pic.begin(CIRCLES); 
   pic.vertex(100, 90);
   pic.vertex(250, 150);
   pic.vertex(200, 100);
   pic.vertex(150, 50);
   pic.vertex(100, 100);
   pic.end(); 
    
   pic.begin(CIRCLES); 
   pic.vertex(450, 150);
   pic.vertex(550, 150);
   pic.vertex(500, 100);
   pic.vertex(450, 50);
   pic.vertex(400, 100);
   pic.end(); 
    
    
   pic.color(51, 204, 51); 
   for(int i = 0; i < 360; i+= 10) {
    pic.drawRose({400, 200}, 5, 21);
   }
   pic.vertex(0, 500);
   pic.vertex(600, 600);
   pic.end(); 
    
   pic.save("sunset.png"); 


   Canvas nom(500, 500);
   nom.background(255, 255, 255);

   // Draw a grid of circles with random colors
   int gridSize = 10;
   int cellSize = 50;
   for (int i = 0; i < gridSize; i++) {
      for (int j = 0; j < gridSize; j++) {
      int r = rand() % 256;
      int g = rand() % 256;
      int b = rand() % 256;
      nom.color(r, g, b);
      nom.setRad(20);
      nom.begin(CIRCLES);
      int x = i * cellSize + cellSize / 2;
      int y = j * cellSize + cellSize / 2;
      nom.vertex(x, y);
      nom.end();
      }
   }

   int numLines = 20;
   for (int i = 0; i < numLines; i++) {
      float t = float(i) / float(numLines - 1);
      int r = 255 * t;
      int g = 255 * (1 - t);
      int b = 0;
      nom.color(r, g, b);
   }
   nom.save("my_image.png");


   Canvas sq(300, 300);

   int squareSize = 30;
   for (int i = 0; i < 300; i += squareSize) {
      for (int j = 0; j < 300; j += squareSize) {
         sq.color(i % 255, j % 255, (i + j) % 255);
         sq.drawRectangle(i, j, squareSize, squareSize);
         sq.drawCircle({20, 30}, 50);
      }
   }
   for (int i = 0; i < 150; i += squareSize) {
      for (int j = 0; j < 150; j += squareSize) {
         sq.color(i % 255, j % 255, (i + j) % 255);
         sq.drawRose({150, 150}, 8, 100);
           
      }
   }
   sq.save("squares.png");

   Canvas flo(800, 800);
   flo.background(255, 255, 255);

   srand(time(nullptr));

   int num_rows = 4;
   int num_cols = 4;
   int spacing = 200;
    

   for (int i = 0; i < num_rows; i++) {
      for (int j = 0; j < num_cols; j++) {
      int x = static_cast<int>((i + 0.5) * spacing);
      int y = static_cast<int>((j + 0.5) * spacing);
         Vertex center = {
               x,
               y,
               {static_cast<unsigned char>(rand() % 256), static_cast<unsigned char>(rand() % 256), static_cast<unsigned char>(rand() % 256)}
            };
            flo.drawRose(center, static_cast<unsigned char>(rand() % 5 + 1), static_cast<unsigned char>(rand() % 50 + 50));
        }
    }
    flo.save("flowers.png");


   
   srand(time(NULL));  // Seed random number generator

   Canvas abs(800, 600);
   abs.background(255, 255, 255);

   int num_shapes = 50;
   for (int i = 0; i < num_shapes; i++) {
      int shape_type = rand() % 2;
      int x = rand() % 800;
      int y = rand() % 600;
      int red = rand() % 256;
      int green = rand() % 256;
      int blue = rand() % 256;

      if (shape_type == 0) {
         int width = rand() % 100 + 50;
         int height = rand() % 100 + 50;
         abs.color(red, green, blue);
         abs.drawRectangle(x, y, width, height);
      } 
      else {
         int num_petals = rand() % 10 + 3;
         unsigned char uc_red = static_cast<unsigned char>(red);
         unsigned char uc_green = static_cast<unsigned char>(green);
         unsigned char uc_blue = static_cast<unsigned char>(blue);
         Vertex center = {x, y, { uc_red, uc_green, uc_blue}};
         abs.drawRose(center, num_petals, 300);
      }
    }

    abs.begin(CIRCLES);
    abs.color(147,169,164);
    for (int i = 0; i < 50; i++) {
      abs.vertex(rand() % 800, rand() % 600);
    }
    abs.end();

    abs.save("abstract.png");
   return 0;
}

