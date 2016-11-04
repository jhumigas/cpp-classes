#include "rgb.h"

namespace colormap {

	rgb::rgb(scalar_type red, scalar_type green, scalar_type blue) : red_(red), green_(green), blue_(blue) {}

	bool rgb::operator==(const rgb& other) const {
		return (red_ == other.red_) && (green_ == other.green_) && (blue_ == other.blue_);
	}
};
