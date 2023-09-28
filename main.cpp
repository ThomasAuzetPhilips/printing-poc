#include <bits/stdc++.h>
#include <cups/cups.h>
#include <exception>
#include <regex>
#include <random>
#include <vector>
#include "a4.h"

void generate_random_points(std::vector<std::pair<double, double>>& vec, size_t vec_size) {
	vec.resize(vec_size);
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(8.0, 20.0);
	for (size_t i = 0; i < vec_size; ++i)
		vec[i] = {i, dist(mt)};
}

int main(int ac, char* av[]) {
	// Provide printer selection
	std::cout << "Select a printer: " << std::endl;
	cups_dest_t* dests;
	const int n = cupsGetDests2(CUPS_HTTP_DEFAULT, &dests);
	for (int i = 0; i < n; ++i) {
		std::cout << i+1 << ". " << dests[i].name << std::endl;
	}
	std::cout << n+1 << ". PDF only" << std::endl;
	std::cout << "Input a number (1 to " << n+1 << "):";
	int user_choice = 0;
	std::cin >> user_choice;
	if (user_choice < 1 || user_choice > n+1) {
		std::cerr << "Wrong printer index" << std::endl;
		cupsFreeDests(n, dests);
		return 1;
	}

	//Make page
	const char* file;
	{// Scope this because Cairo prevents CUPS from opening the file
		a4 current_page;
		current_page.set_header_img("philips.png");
		current_page.set_font("Arial Black", 30, true);
		current_page.write_text("EarlyVue");
		current_page.set_font("Arial Black", 30, false);
		current_page.write_text("VS30");
		current_page.write_text(" ");
		current_page.write_text(" ");
		current_page.set_font("Arial Black", 12, false);
		current_page.write_text("2023/09/28");
		current_page.write_text("11:40:24");
		current_page.write_text("CN82290072");
		current_page.write_text("Adult");
		current_page.write_text("SpO2 99%");
		current_page.write_text("NBP(S) 120 mmHg");
		current_page.write_text("NBP(D) 80 mmHg");
		current_page.write_text("NBP(M) 93 mmHg");
		current_page.write_text("Pulse 83(SpO2) bpm");
		current_page.write_text("etCO2 42 mmHg");
		current_page.write_text("imCO2 4 mmHg");
		current_page.write_text("IPI 10");
		current_page.write_text("Temp 36.6(M) C");
		current_page.write_text("Resp 22(awRR) rmp");
		std::vector<std::pair<double, double>> dummy_data;
		generate_random_points(dummy_data, 100);
		current_page.plot(dummy_data, 5.);
		file = current_page.get_page_handle();
	}

	if (user_choice == n+1) {
		// Save to PDF only
		std::cout << "Saved to " << file << std::endl;
	} else {
		//Print
		std::cout << "Printing " << file << std::endl;
		if (!cupsPrintFile(dests[user_choice-1].name, file, "Cairo PS", 0, nullptr)) {
			std::cerr << cupsLastError() << " : " << cupsLastErrorString() << std::endl;
		}
	}
	cupsFreeDests(n, dests);
	return 0;
}
