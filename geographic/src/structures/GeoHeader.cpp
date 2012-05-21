#include "GeoHeader.h"

#include <boost/filesystem.hpp>

#include <iostream>
using namespace std;

namespace fs = boost::filesystem;

namespace GEO{

GeoHeader_Info::GeoHeader_Info(){ 
    valid = false;
    pixeltype.set( PixelType::UNKNOWN );
}

GeoHeader_Info::~GeoHeader_Info(){

}

std::string GeoHeader_Info::get_image_filename()const{
    return image_filename;
}

void GeoHeader_Info::set_image_filename( std::string const& filename ){
    image_filename = filename;
}

bool GeoHeader_Info::image_filename_exists()const{

   if(fs::exists(fs::path(image_filename)) == true )
      return true;

   return false;
}

void GeoHeader_Info::set_pixel_type( PixelType const& pix){
   
    //copy pixel type
    pixeltype = pix;
    
}

PixelType GeoHeader_Info::get_pixel_type()const{
    
    return pixeltype;
}
      
bool GeoHeader_Info::isValid()const{
    return valid;
}

void GeoHeader_Info::setValid( const bool& flag ){
    valid = flag;
}

}//end of GEO namespace