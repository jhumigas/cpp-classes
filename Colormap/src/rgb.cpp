#include "rgb.h"

namespace colormap {
    
	rgb::rgb() : red_(0), green_(0), blue_(0) {}
	rgb::rgb(scalar_type red, scalar_type green, scalar_type blue) : red_(red), green_(green), blue_(blue) {}

	bool rgb::operator==(const rgb& other) const {
		return (red_ == other.red_) && (green_ == other.green_) && (blue_ == other.blue_);
	}

	bool rgb::operator<(const rgb& other) const {
		if(red_ < other.red_){
			return true;
		}else if(red_ == other.red_ && green_ < other.green_){
			return true;
		}else if(green_ == other.green_ && blue_ < other.blue_){
			return true;
		}else{
			return false;
		}
	}
};
