#include "printer_interface.h"
#include <cups/cups.h>

// Name that will apear on the printer job
const std::string printerHelper::documentname_  { "Philips document" };

/**
* Get printer list
*
* The list will containt previously added/used printers
* as well as IPP printers availables on the network.
*
* @return: String list of printer names.
*/
std::vector<std::string> printerHelper::getLocalPrinters() {
	cups_dest_t* dests;
	int n = cupsGetDests2(CUPS_HTTP_DEFAULT, &dests);
	if (!n)
		return {};
	std::vector<std::string> result(n);
	for (int i = 0; i < n; ++i)
		result.at(i) = dests[i].name;
	cupsFreeDests(n, dests);
	return result;
}

/**
* Find a printer with its URI
*
* @return: Printer name if found
*/
std::string printerHelper::getPrinterWithURI(const std::string& uri) {
	cups_dest_t* dest = cupsGetDestWithURI(nullptr, uri.c_str());
	if (!dest)
		return {};
	std::string result = dest->name;
	cupsFreeDests(1, dest);
	return result;
}

/**
* Print file
*
* @param printername: Name of the printer to print on 
* @param filepath: File to print (PDF or PS)
* @throw printerException: CUPS error
*/
bool printerHelper::print(const std::string& printername, const std::string& filepath) noexcept(false) {
	if (!cupsPrintFile(printername.c_str(), filepath.c_str(), documentname_.c_str(), 0, nullptr)) {
		throw printerException();
		return false;
	}
	return true;
}

const char* printerException::what() const noexcept {
	return cupsLastErrorString();
}
