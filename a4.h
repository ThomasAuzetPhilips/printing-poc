#include <string>
#include <cairo.h>
#include <utility>
#include <vector>

class a4 {
public:
	a4();
	~a4();
	void set_font(const std::string& font_name, int font_size, bool bold = false);
	void set_left_margin(int left_margin) {left_margin_ = left_margin;}
	const char* get_page_handle() const;
	void write_text(const std::string& text);
	void plot(std::vector<std::pair<double,double>> points, double zoom = .0);
	void set_header_img(const std::string& filepath);
	void show() const;

private:
	void advance(int y = -1);
	const std::string filename_ {"cairo_doc.pdf"};
	cairo_t* context_ {nullptr};
	cairo_surface_t* surface_ {nullptr};
	int current_height_pos_ {0};
	int left_margin_ {10};
	int font_size_ {10};
	static const int width_ {595};
	static const int height_ {842};
};
