#include <cairo.h>
#include <vector>

class cairoHelper {
private:
	cairoHelper() = delete;
	~cairoHelper() = delete;
public:
	static void draw_graph(cairo_t *cr, int xoffset, int yoffset, const std::vector<std::pair<double,double>>& points);
	static void draw_graph_axis(cairo_t *cr, int xoffset, int yoffset, int xlen, int ylen);
};

