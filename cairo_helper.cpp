#include "cairo_helper.h"
#include "cairo.h"
#include <bits/stdc++.h>

void cairoHelper::draw_graph(cairo_t *cr, int xoffset, int yoffset, const std::vector<std::pair<double,double>>& points) {
	double xmax = .0;
	double ymax = .0;
	cairo_move_to(cr, xoffset, yoffset);
	cairo_set_line_width(cr, .5);
	for (auto xy : points) {
		xmax = std::max(xmax, xy.first);
		ymax = std::max(ymax, xy.second);
		cairo_line_to(cr, xy.first+xoffset, -xy.second+yoffset);
		cairo_stroke(cr);
		cairo_move_to(cr, xy.first+xoffset, -xy.second+yoffset);
	}
	draw_graph_axis(cr, xoffset, yoffset, xmax, ymax);
}
void cairoHelper::draw_graph_axis(cairo_t *cr, int xoffset, int yoffset, int xlen, int ylen) {
	// Draw axis
	cairo_set_line_width(cr, 1.);
	cairo_move_to(cr, xoffset-5, yoffset);
	cairo_line_to(cr, xoffset+xlen+5, yoffset);
	cairo_stroke(cr);
	cairo_move_to(cr, xoffset, yoffset+5);
	cairo_line_to(cr, xoffset, yoffset-ylen-5);
	cairo_stroke(cr);

	// Write legend (demo numbers)
	cairo_set_font_size(cr, 5);
	cairo_move_to(cr, xoffset+2, yoffset+5);
	cairo_show_text(cr, "rpm");
	cairo_move_to(cr, xoffset-5, yoffset-2);
	cairo_show_text(cr, "0");
	cairo_move_to(cr, xoffset-8, yoffset-ylen);
	cairo_show_text(cr, "20");

	// Draw dots
	cairo_set_line_width(cr, .2);
	std::array<double, 2> d {.2,1.};
	cairo_set_dash(cr, d.data(), d.size(), 0.);
	for (int i = xoffset; i<xoffset+xlen; i+=10) {
		cairo_move_to(cr, i, yoffset);
		cairo_line_to(cr, i, yoffset-ylen);
		cairo_stroke(cr);
	}
	for (int i = yoffset-ylen; i<yoffset; i+=10) {
		cairo_move_to(cr, xoffset, i);
		cairo_line_to(cr, xoffset+xlen, i);
		cairo_stroke(cr);
	}
}
