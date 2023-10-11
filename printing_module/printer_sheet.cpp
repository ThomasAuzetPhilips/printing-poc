#include "printer_sheet.h"
#include "cairo-pdf.h"
#include "cairo.h"
#include <cstdlib>
#include <unistd.h>

/**
* Default constructor
*
* Meant to be subclassed so the sheet width and height are fixed.
* Will prepare the Cairo work surface and context for future calls
* as well as the PDF file.
*
* @param: w, the sheet width
* @param: h, the sheet height
*/
printerSheet::printerSheet(unsigned int w, unsigned int h)
: width_(w), height_(h) {
	// Generate a random file
	char name[] = "/tmp/philips_XXXXXX";
	int fd = mkstemp(name);
	if (fd >= 0)
		close(fd);

	surface_ = cairo_pdf_surface_create(name, w, h);
	context_ = cairo_create(surface_);
	filename_ = name;
}

printerSheet::~printerSheet() {
	releaseSheet();
}

/**
* Destroy Cairo contexes and release hold on the file
*
* @return: The PDF file path
*/
std::string printerSheet::releaseSheet() {
	if (!released_) {
		cairo_show_page(context_);
		cairo_destroy(context_);
		cairo_surface_flush(surface_);// This will release the lock on the file
		cairo_surface_destroy(surface_);// So it can be accessed
		released_ = true;
	}
	return filename_;
}
