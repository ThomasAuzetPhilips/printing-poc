#include <cairo.h>
#include <string>

/**
* printerSheet class. Represents a sheet work surface.
*
* This class is taking care of allocating and freeing 
* Cairo resources. It is meant to be subclassed to
* better address specific sheet needs and implement
* drawing functions.
*/
class printerSheet {
public:
	printerSheet() = delete;
	printerSheet(unsigned int w, unsigned int h);
	virtual ~printerSheet();

	std::string releaseSheet();

protected:
	cairo_t* context_ {nullptr};
	cairo_surface_t* surface_ {nullptr};
	unsigned int width_;
	unsigned int height_;

private:
	std::string filename_;
	bool released_ {false};
};
