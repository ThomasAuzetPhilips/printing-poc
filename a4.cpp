#include <algorithm>
#include <bits/stdc++.h>
#include <functional>
#include <cstdio>
#include <unistd.h>
#include "a4.h"
#include "cairo_helper.h"
#include "cairo-pdf.h"
#include "cairo.h"

a4::a4() {
	{std::ofstream (filename_.c_str());}// Create empty file for Cairo
	surface_ = cairo_pdf_surface_create(filename_.c_str(), width_, height_);
	context_ = cairo_create(surface_);
}

a4::~a4() {// Cleanup
	cairo_destroy(context_);
	cairo_surface_flush(surface_);
	cairo_surface_destroy(surface_);
}

void a4::set_font(const std::string& font_name, int font_size, bool bold) {
	cairo_select_font_face(context_, font_name.c_str(), CAIRO_FONT_SLANT_NORMAL,
						bold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);
	font_size_ = font_size;// Store font size for later
}

void a4::write_text(const std::string& text) {
	advance();// Move down the paper to avoid writing on itself
	cairo_set_font_size(context_, font_size_);// Set font size before writing
	cairo_show_text(context_, text.c_str());// Write text
}

void a4::plot(std::vector<std::pair<double,double>> points, double zoom) {
	advance(height_/3);
	std::transform(points.begin(), points.end(), points.begin(),
				[&zoom](auto& v) -> std::pair<double, double> {return {v.first*zoom,v.second*zoom};});
	cairoHelper::draw_graph(context_, left_margin_+10, current_height_pos_, points);
}

void a4::set_header_img(const std::string& filepath) {
	cairo_surface_t* img = cairo_image_surface_create_from_png(filepath.c_str());
	cairo_save(context_);// Next call will cause surface restriction that we don't want to keep
	cairo_set_source_surface(context_, img, width_/2., 5);
	cairo_paint(context_);
	cairo_surface_finish(img);
	cairo_surface_destroy(img);
	cairo_restore(context_);// Back to original surface
}

void a4::advance(int y) {
	if (y < 0)
		y = font_size_+1;
	current_height_pos_ += y;
	if (current_height_pos_+height_/10 > height_) { // Switch to right column
		left_margin_+= width_/2;
		current_height_pos_ = height_/10;// Leave space for eventual image header
	}
	cairo_move_to(context_, left_margin_, current_height_pos_);
}

const char* a4::get_page_handle() const {
	cairo_show_page(context_);
	return filename_.c_str();
}
