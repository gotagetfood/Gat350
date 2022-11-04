#include "Utilities.h" 
#include <algorithm> 

namespace neu
{
	std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		// convert string characters to lower case 
		transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper = str;
		// convert string characters to upper case 
		transform(upper.begin(), upper.end(), upper.begin(), ::toupper);

		return upper;
	}

	bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
	{
		// if string lengths don't match return false 
		if (str1.length() != str2.length()) {
			return false;
		}

		// returns false if string characters aren't equal 
		std::string lower = str1;
		std::string upper = str2;
		transform(lower.begin(), lower.end(), lower.begin(), ::toupper);
		transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
		if (!lower._Equal(upper)) {
			return false;
		}

		return true;
	}
}