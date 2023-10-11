#include <cups/cups.h>
#include <vector>
#include <string>
#include <exception>

/**
* Static printerHelper class.
*
* It provides helpers to find and use network printers
* in a more "C++" way.
*/
class printerHelper {
private:
	printerHelper() = delete;
	~printerHelper() = delete;

public:
	static std::vector<std::string> getLocalPrinters();
	static std::string getPrinterWithURI(const std::string& uri);

	static bool print(const std::string& printername, const std::string& filepath) noexcept(false);

private:
	static const std::string documentname_;
};

/**
* printerException class to retrieve CUPS error
*
* Subclassed from std::exception, just use what()
* to get the last CUPS error string.
*/
struct printerException : public std::exception {
	virtual const char* what() const noexcept;
};
