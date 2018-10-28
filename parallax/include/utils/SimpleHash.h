#pragma once
#ifndef _SIMPLE_HASH_H_
#define _SIMPLE_HASH_H_

#include "../Common.h"
#include <string_view>

namespace prx {

	// TODO: Make this just function
	class SimpleHash {
	private:
		SimpleHash();
		static const unsigned int m_MULTIPLIER = 31;
	public:
		static inline unsigned int hashString(std::string_view string) {
			if (string.size() == 0)
				return 0;
			unsigned int hash = 0;

			for (auto& element : string)
				hash = m_MULTIPLIER * hash + static_cast<unsigned char>(element);
			hash = hash / static_cast<unsigned int>(string.size());
			return hash;
		}
	};

	inline prx_id_t hash_string(std::string_view string) {
		return static_cast<prx_id_t>(SimpleHash::hashString(string));
	}
}

#endif
