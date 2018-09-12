//#include "Color.h"
//#include <iostream>
//#include <sstream>
//
//#include "log/Log.h"
//
//namespace prx {
//
//	hpm::vec3 Color::RGBtoGLVec(unsigned int r, unsigned int g, unsigned int b) {
//		return hpm::vec3(r / 255.0, g / 255.0, b / 255.0);
//	}
//
//	hpm::vec4 Color::RGBAtoGLVec(unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
//		return hpm::vec4(r / 255.0, g / 255.0, b / 255.0, a);
//	}
//
//	hpm::vec3 Color::HEXtoGLVec(std::string_view hex)
//	{
//		if (hex[0] != '#' || hex.length() != 7) {
//			Log::message("Invalid hex color code", LOG_WARNING);
//			std::cout << "Invalid color" << std::endl;
//			return hpm::vec3(0.0, 0.0, 0.0);
//		}
//
//		int r = std::stoi(static_cast<std::string>(hex.substr(1, 2)), nullptr, 16);
//		int g = std::stoi(static_cast<std::string>(hex.substr(3, 2)), nullptr, 16);
//		int b = std::stoi(static_cast<std::string>(hex.substr(5, 2)), nullptr, 16);
//
//		return hpm::vec3(r / 255.0, g / 255.0, b / 255.0);
//	}
//}
