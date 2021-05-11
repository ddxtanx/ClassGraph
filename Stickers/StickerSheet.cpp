#include "StickerSheet.h"



    StickerSheet::StickerSheet(const Image &picture, unsigned max) //: Images_(max)
    {
        index_ = 0;
        background_ = picture;                      //copies inputted picture into private var
    }
        
    StickerSheet::~StickerSheet()
    {
        for (auto i : Images_ )
        { delete i; }                            //deletes all stickers located at pointers held in vector
        Images_.clear();                         //clears vector
    }

    StickerSheet::StickerSheet(const StickerSheet &other) : background_(other.background_), index_(other.index_)      // 1. copies background image
    {
        unsigned j = 0;
        for (auto i : other.Images_ )
        {
            Image* temp = new Image(*i);  //probleeeeeem
            Images_.push_back(temp);
        }            // 2 deep copies all images from other to this
    }

    const StickerSheet & StickerSheet::operator= (const StickerSheet & other) 
    {
        if (this == &other) {return *this;}
        this->background_ = other.background_;
        this->index_ = other.index_;
        for (auto i : Images_ )
        {  delete i; }                             // 2. deletes all stickers located at pointers held in vector
        Images_.clear();                           //removes all pointers from vector

        unsigned j = 0;
        for (auto i : other.Images_ )
        {
            Image* temp = new Image(*i);  //probleeeeeem
            Images_.push_back(temp);
        }            // 2 deep copies all images from other to this
        return *this;
    }

    void StickerSheet::changeMaxStickers(unsigned max)
    {
        if (max < Images_.size())                   //let vector work with expanding array, but cut down manually
        Images_.resize(max);
    }

    int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
    {
        Image* stickerPtr = new Image(sticker);                 //allocates new image and copies input sticker, saving a pointer
        stickerPtr->xPos = x;                                   //adding location data
        stickerPtr->yPos = y;
        Images_.push_back(stickerPtr);
        index_++;
        return (int)index_ - 1;                       //calculates the index and returns it as int
    }

    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
    {
        if(index < Images_.size())          //checks to see if index is in range of current vector elements
        {
            Image* currSticker = Images_[index];
            currSticker->xPos = x;
            currSticker->yPos = y;
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void StickerSheet::removeSticker(unsigned index)
    {
        std::vector<Image*>::iterator itrDelete = Images_.begin();
        std::advance (itrDelete,index);
        Images_.erase(itrDelete);                 //should remove the proper index and reallocate, fingers crossed
        index_--;
    }

    Image* StickerSheet::getSticker(unsigned index)
    {
        if (index < index_)
        {return Images_[index];}
        else
        {
            return NULL;
        }
    }

    Image StickerSheet::render() const
    {
        Image output(background_);           //initializes the output image with the background
        std::cout << "# of images: " << Images_.size() << std::endl;
        std::cout << "background size: " << background_.width() << "," << background_.height() << std::endl;

        for (auto i : Images_ )
        {
            
            
            if (i == nullptr)
            { continue; }
            unsigned xPos = i->xPos;
            unsigned yPos = i->yPos;     //probably not the right de-reference blah blah, get offset dummy
            unsigned width = i->width();    //get size of sticker
            unsigned height = i->height();
            unsigned dx, dy;
            //std::cout << "Next Image of size: " << i->width() << "," << i->height() << "   @ " << xPos << "," << yPos << std::endl;

            if (xPos + width > output.width() || yPos + height > output.height())
            {
                
                std::cout << "Resizing -- xPos,yPos = " << xPos << "," << yPos << std::endl;
                dy = std::max(yPos + height, output.height());
                dx = std::max(xPos + width, output.width());
                output.resize(dx, dy);               //resize if sticker goes out of bounds
            }
            for (unsigned x = 0; x < i->width(); x++) 
            {
                for (unsigned y = 0; y < i->height(); y++) 
                {
                    cs225::HSLAPixel &stickerPixel = i->getPixel(x, y);
                    if(stickerPixel.a == 0)
                    {
                        continue;                                                       //accounts for transparent pixels
                    }
                    else
                    {
                        output.getPixel(xPos + x, yPos + y) = stickerPixel;             //copy pixel to offset value
                    }
                }
            }
        }                             
        return output;
    }





        //debug stuff
        //std::cout << "add" << std::endl;
        
        //std::cout << "-----------Vector (before add)-----------65" << std::endl;
        //for (Image* i : Images_ )
        //{     std::cout << i << std::endl;        }
        //std::cout << "index_ = " << index_ << std::endl;
        //std::cout << "itr_ before = " << *itr_ << std::endl;
        //std::cout << ".begin() = " << *(Images_.begin()) << std::endl;
        //std::cout << ".end() = " << *(Images_.end()) << std::endl;
        //std::cout << "itr_ = " << itr_ << std::endl;
        //std::cout << " " << std::endl;
        
        