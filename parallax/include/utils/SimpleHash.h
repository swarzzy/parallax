#pragma once
#ifndef _SIMPLE_HASH_H_
#define _SIMPLE_HASH_H_

#include <string_view>

namespace prx {
	class SimpleHash {
	private:
		SimpleHash();
		static const unsigned int m_MULTIPLIER = 31;
	public:
		static inline unsigned int hashString(std::string_view string) {
			unsigned int hash = 0;

			for (auto& element : string)
				hash = m_MULTIPLIER * hash + static_cast<unsigned char>(element);
			hash = hash / string.size();
			return hash;
		}
	};
}

#endif
