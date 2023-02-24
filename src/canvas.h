/*-----------------------------------------------
 * Author: Jenifer Fabian Dubon
 * Date: Feb 17,2023
 * Description: Program that can draw lines and triangles
 ----------------------------------------------*/

#ifndef canvas_H_
#define canvas_H_

#include <string>
#include <vector>
#include "image.h"

namespace agl
{
   enum PrimitiveType {UNDEFINED, LINES, TRIANGLES, CIRCLES, RECTANGLES};
   
   struct Vertex{
      int x;   //column
      int y;   //row
      Pixel color;
   };

   
   class Canvas
   {
   public:
      Canvas(int w, int h);
      virtual ~Canvas();

      // Save to file
      void save(const std::string& filename);

      // Draw primitives with a given type (either LINES or TRIANGLES)
      // For example, the following draws a red line followed by a green line
      // begin(LINES);
      //    color(255,0,0);
      //    vertex(0,0);
      //    vertex(100,0);
      //    color(0,255,0);
      //    vertex(0, 0);
      //    vertex(0,100);
      // end();
      void begin(PrimitiveType type);
      void end();

      // Specifiy a vertex at raster position (x,y)
      // x corresponds to the column; y to the row
      void vertex(int x, int y);

      // Specify a color. Color components are in range [0,255]
      void color(unsigned char r, unsigned char g, unsigned char b);

      // Fill the canvas with the given background color
      void background(unsigned char r, unsigned char g, unsigned char b);


      //sets radius for circle
      void setRad(int radius);

      //draws Rose;
      void drawRose(Vertex center, int numPetals, int radius);




   private:
      Image _canvas; //image
      Pixel currentCol;
      PrimitiveType myPrimType;
      std:: vector<Vertex> myVertices;
      int _radius;
      /*
      int _width;
      int _height;
      */

   

      //draws the line from a to b
      void bresenhamLine(Vertex a, Vertex b);

      //function to draw high line
      void drawHighLine(Vertex a, Vertex);

      //function to draw low line
      void drawLowLine(Vertex a, Vertex b);

      //draw a triangle with the 3 vertices
      void drawTriangle(Vertex a, Vertex b, Vertex c);

      //draw a circle with given position and radius
      void drawCircle(Vertex x, int a);


   };
}

#endif


