#include <resources/FileReader.h>

#include <fstream>
#include <sstream>

#include <utils/log/Log.h>

namespace prx {

	std::optional<std::string> FileReader::readTextFile(std::string_view path)
	{
		std::ifstream file;
		std::stringstream ss;

		file.exceptions(std::ifstream::badbit);
		try {
			file.open(static_cast<std::string>(path));
			if (!file.is_open()) {
				prx::Log::message(LOG_LEVEL::LOG_ERROR, std::string("Can not open file: ") + static_cast<std::string>(path));
				return std::nullopt;
			}

			ss << file.rdbuf();

			file.close();
		}
		catch (std::ifstream::failure e) {
			prx::Log::message(LOG_LEVEL::LOG_ERROR, "File is not succsesfully read");
			return std::nullopt;
		}
		return ss.str();
	}
}

