#include "Image.h"

Image::Image()
: cs225::PNG()
{}
Image::Image(unsigned int width, unsigned int height)
: cs225::PNG(width, height)
{}

void Image::scale(double factor)
{
    if (factor == 1.0 || factor <= 0.0)
        return;
    Image tempImage(*this);                              //copies by reference the current image for reference
    unsigned int tempWidth = width(), tempHeight = height();
    resize(width()*factor, height()*factor);                    //resizes object
    //unsigned int width = width();
    //unsigned int height = height();
    //double percentX, percentY;

   for (unsigned x = 0; x < width(); x++) 
    {
        for (unsigned y = 0; y < height(); y++) 
        {
            //HSLAPixel & pixel = getPixel(x, y);
            //HSLAPixel & tempPixel = tempImage.getPixel((tempWidth*x)/width, (tempHeight*y)/height);
             getPixel(x, y) = tempImage.getPixel((tempWidth*x)/width(), (tempHeight*y)/height());   //copy value of pixel in approximate location on original image to new resolution image
        }
    }
}   

void Image::scale(unsigned w, unsigned h)
{
    if (((double)w/(double)width())*(double)height() < h )
    {
        double factor = (double)w/(double)width();
        std::cout << factor << std::endl;
        scale(factor);
    }
    else
    {
        double factor = (double)h/(double)height();
        std::cout << "test" << std::endl;
        std::cout << factor << std::endl;
        scale(factor);
    }
}
         