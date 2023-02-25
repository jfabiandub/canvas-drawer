// Copyright 2021, Aline Normoyle, alinen

#include "image.h"

#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

/**
 * The main driver program for Assignment 2
 * 
 * This program implemetns a class for loading and saving image files 
 * It also implement multiple operations and filter for these images 
 * such as: flipping the image horizontally, rezising the image, 
 * using the gamma correction to correct images, using grayscale to make an image gray
 * blending two images together, creating asubimage of an image and r
 * eplacing a block of pixels in a image
 * 
 * @author: Jenifer Fabian Dubon
 * @version: Feb 10, 2023
 * 
**/


namespace agl {

Image::Image() {
   myHeight =0;
   myWidth = 0;
   numChannels= 3;
   myData = NULL;
}

Image::Image(int width, int height)  {
   myWidth = width;
   myHeight = height;
   numChannels = 3;
   myData = new  Pixel[width * height];
   isloaded = false;
  // myData = NULL;
}

Image::Image(const Image& orig) {
   myWidth = orig.myWidth;
   myHeight = orig.myHeight;
   numChannels= orig.numChannels; 
   myData = new Pixel[myWidth * myHeight];
   memcpy(myData, orig.myData, sizeof(Pixel)* myWidth * myHeight);
   isloaded = false;

}

Image& Image::operator=(const Image& orig) {
  if (&orig == this) {
    return *this;
  }
  if(myData !=NULL){
   cleanUp();
  }
   myData =  orig.myData;
   myWidth = orig.width();
   myHeight = orig.height();
   numChannels = orig.numChannels;
   myData = new struct Pixel[myWidth * myHeight];
   memcpy(myData, orig.myData, sizeof(Pixel)* myWidth * myHeight);
   isloaded = false;

  return *this;
}

Image::~Image() {
 //free existing memory 
 cleanUp();
 
}


int Image::width() const { 
   return myWidth;
}


int Image::height() const {
   return myHeight;
}


char* Image::data() const {
   return (char*)myData;
}


void Image::set(int width, int height, unsigned char* data) {
   myWidth = width;
   myHeight = height;
   if(myData !=NULL){
      cleanUp();
   }
   myData = new struct Pixel[myWidth * myHeight];
   memcpy(myData, (Pixel *) data, sizeof(Pixel)* myWidth * myHeight);
}


void Image::cleanUp(){
 if(isloaded == true){
   stbi_image_free(myData);
 }
 else {
   delete[] myData;
 }
 isloaded = false;
 myData=NULL;
}


bool Image::load(const std::string& filename, bool flip) {
   int x;
   int y;

   myData = (Pixel *) (stbi_load(filename.c_str(), &x , &y, &numChannels, 3));
   if(myData !=NULL){
       myWidth = x;
       myHeight = y;
       isloaded = true;
      return true;
   }
   else{
   return false;
   }
   isloaded = true;
}


bool Image::save(const std::string& filename, bool flip) const {
   if (myData !=NULL){
      stbi_write_png(filename.c_str(), myWidth, myHeight, numChannels, myData, sizeof(struct Pixel)*myWidth);  //saves the file as some name.
      return true;
   }
   else{
      return false;
   }
}


Pixel Image::get(int row, int col) const {
   Pixel tempData =  myData[row* myWidth + col];  
   return tempData;
   
}


void Image::set(int row, int col, const Pixel& color) {
   myData[row * myWidth + col]= color; 
}


Pixel Image::get(int i) const{
   return myData[i];
}


void Image::set(int i, const Pixel& c){
   myData[i] = c;
}


Image Image::resize(int w, int h) const {
   Image result(w, h);
   for(int i = 0; i<h; i++){ 
      for(int j = 0; j < w; j++){
         float rowProp = (float)i / (h-1); //calculates row proportion
         float colProp = (float)j/ (w-1);   //calculates col proportion
            
         int r1 = floor(rowProp * (myHeight-1)); 
         int c1 = floor(colProp * (myWidth-1));
      
         result.set(i, j, get(r1, c1));
      }
   }
   return result;
}


Image Image::flipHorizontal() const {
   Image result(myWidth, myHeight);
   
   for(int i= 0 ; i<myHeight; i++){  //iiterates over the rows of the image
      for(int j = 0; j< myWidth; j++){  //iterates over columns
         result.set(myHeight - 1 -i, j, get(i * myWidth + j)); // assigns each pixel  from og image to its corresponding position
                                                   //in the flipped image and then resturns the flipped imagee
      }
   }
   return result;\
}


Image Image::flipVertical() const {
   Image result(myWidth, myHeight);

   for(int i = 0; i<myHeight; i++){
      for (int j= 0; j<myWidth; j++){
         result.set(i, myWidth - 1 -j, get(i, j)); //row of pixels is flipped vertically
      }
   }
   return result;
}


Image Image::rotate90() const {
   Image result(myWidth, myHeight);
  
   for(int i = 0; i<myHeight; i++){
      for (int j= 0; j<myWidth; j++){
         result.set( myWidth - 1 -j,i, get(i,j));
      }
   }
   return result;
}


Image Image::subimage(int startx, int starty, int w, int h) const {
   Image sub(w, h);

   for(int i = 0; i< h; i++){
      for(int j =0; j<w; j++){
         sub.set(i, j, get(startx +i, starty +j)); //sets the value at (i,j) in the new subimage to the value in the og image.
      }
   }
   return sub;
}


void Image::replace(const Image& image, int startx, int starty) {
   for(int i=0; i<image.height(); i++){
      for(int j = 0; j< image.width(); j++){
         set(startx + i, starty +j, image.get(i,j));
      }
   }
}


Image Image::swirl() const {
   Image result(myWidth, myHeight);
   for(int i = 0; i<myHeight; i++){
      for (int j= 0; j<myWidth; j++){

         Pixel pix = get(i,j);
         pix = {
         pix.g,
         pix.b,
         pix.r,
         };

         result.set(i,j, pix);
      }
   }
   return result;
}


Image Image::add(const Image& other) const {
   Image result(0, 0);
  
   return result;
}


Image Image::subtract(const Image& other) const {
   Image result(0, 0);
   
   return result;
}


Image Image::multiply(const Image& other) const {
   Image result(0, 0);
   
   
   return result;
}


Image Image::difference(const Image& other) const {
   Image result(0, 0);
  
   return result;
}


Image Image::lightest(const Image& other) const {
   Image result(myWidth, myHeight);
   for(int i = 0; i<myHeight; i++){
      for (int j= 0; j<myWidth; j++){
         
         Pixel currImage=this->get(i, j);  //or without this.
         Pixel newImage = other.get(i,j);
         
         if((newImage.r + newImage.g + newImage.b) > (currImage.r + currImage.g +currImage.b)){
            currImage.r = newImage.r;
            currImage.g = newImage.g;
            currImage.b = newImage.b;

         }
         result.set(i, j, currImage);
      }
   }
   return result;
}


Image Image::darkest(const Image& other) const {
   Image result(myWidth, myHeight);
  
    for(int i = 0; i<myHeight; i++){
      for (int j= 0; j<myWidth; j++){
         
         Pixel currImage=this->get(i, j);  //or without this.
         Pixel newImage = other.get(i,j);
         
         if((newImage.r + newImage.g + newImage.b) < (currImage.r + currImage.g +currImage.b)){
            currImage.r = newImage.r;
            currImage.g = newImage.g;
            currImage.b = newImage.b;
         }
         result.set(i, j, currImage);

      }
   }
   return result;
}


Image Image::gammaCorrect(float gamma) const { 
   Image result(myWidth, myHeight);

   float invGamma = 1.0/gamma;

   for(int i=0; i<myHeight; i++){
       for(int j = 0; j< myWidth; j++){

         Pixel pix = get(i, j);

         //calculate the gamma correction for each color
         float redCol = pow(((float)pix.r / 255), invGamma);  
         float blueCol = pow(((float)pix.b / 255), invGamma);
         float greenCol = pow(((float)pix.g / 255), invGamma);

         //scales the corrected color back to 0-255 range
         pix.r = redCol * 255;
         pix.b = blueCol * 255;
         pix.g = greenCol * 255;

         result.set(i,j, pix);

       }
   }
   return result;
}


Image Image::alphaBlend(const Image& other, float alpha) const {
   Image result(myWidth, myHeight);

      for(int i=0; i<myHeight; i++){
       for(int j = 0; j< myWidth; j++){

         Pixel currImage = get(i, j);
         Pixel newImage = other.get(i, j);
         Pixel blendedPixels; //creates new pixel that stores the blended pixels
         blendedPixels.r =currImage.r *(1- alpha) + newImage.r * alpha; //blends the rgb values of the pixels using alpha values
         blendedPixels.g =currImage.g *(1- alpha) + newImage.g * alpha;
         blendedPixels.b =currImage.b * (1- alpha) + newImage.b * alpha;

         result.set(i,j, blendedPixels); //sets blended pixels

         }
      }
   return result;
}


Image Image::invert() const {
   Image image(myWidth, myHeight);

    for(int i = 0; i<myHeight; i++){
      for (int j= 0; j<myWidth; j++){
         Pixel pix = get(i,j);
         Pixel inverts;
         inverts.r = 255 - pix.r;
         inverts.g = 255- pix.g;
         inverts.b = 255- pix.b;

         image.set(i, j, inverts);
      }
    }
   return image;
}

/*  Returns a copy of the image as a grayscale image */
Image Image::grayscale() const {
   Image result(myWidth, myHeight);

   for(int i=0; i<myHeight; i++){
       for(int j = 0; j< myWidth; j++){
         Pixel pix = get(i, j);
         float avg = (pix.r + pix.g + pix.b) /3.0;  //gets the average of the rgb values
         pix.r = avg;
         pix.g = avg;
         pix.b = avg;
         result.set(i, j, pix); //sets the pixels in the result image
       }
   }
   
   return result;
}

Image Image::colorJitter(int size) const {
   Image image(myWidth, myHeight);
   for(int i=0; i<myHeight; i++){
       for(int j = 0; j< myWidth; j++){
         Pixel pix = get(i,j);

         pix.r = (pix.r - size) + (rand() % size * 2);
         pix.g = (pix.g - size) + (rand() % size * 2);
         pix.b = (pix.b - size) + (rand() % size * 2);

         image.set(i,j, pix);
       }
   }

   return image;
}

Image Image::bitmap(int size) const {
   Image image(0, 0);
   
   return image;
}

void Image::fill(const Pixel& c) {
   for(int i=0; i<myHeight; i++){
      for(int j = 0; j< myWidth; j++){
         set(i,j,c);
      }
   }
}

Image Image::extract() const{
   Image image(myWidth, myHeight);

      for(int i=0; i<myWidth; i++){
         for(int j = 0; j< myHeight; j++){

            Pixel pix = get(i,j);
            pix.g = 0;
            pix.b = 0;
            
            image.set(i, j, pix);
         }
      }
   return image;
}


}  // namespace agl

