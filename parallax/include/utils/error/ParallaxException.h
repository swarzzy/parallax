#pragma once
#include <exception>

namespace prx {
	class ParallaxException : public std::exception {
	protected:
		std::string m_Message;
		ParallaxException(const char* message) {
			m_Message = std::string(message);
		}
	
	public:
		const char* what() const noexcept override {
			return m_Message.c_str();
		}
	};
}
