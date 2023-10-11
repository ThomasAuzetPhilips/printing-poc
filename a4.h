#include "printing_module/printer_sheet.h"
#include <utility>
#include <vector>

class a4 : public printerSheet {
public:
	a4();
	~a4() = default;
	void set_font(const std::string& font_name, int font_size, bool bold = false);
	void set_left_margin(int left_margin) {left_margin_ = left_margin;}
	const char* get_page_handle() const;
	void write_text(const std::string& text);
	void plot(std::vector<std::pair<double,double>> points, double zoom = .0);
	void set_header_img(const std::string& filepath);

private:
	void advance(int y = -1);
	int current_height_pos_ {0};
	int left_margin_ {10};
	int font_size_ {10};
};
