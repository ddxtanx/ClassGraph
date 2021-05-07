/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
//#include "HSLAPixel.h"
#include "../cs225/PNG.h"


    class Image: public cs225::PNG
    {
        public:
        void scale(double factor);
        void scale(unsigned w, unsigned h);
        unsigned int xPos, yPos;
        private:


    };
