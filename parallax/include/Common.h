#pragma once

// This macro disallow copy and move constructors and assign operators
#define PRX_DISALLOW_COPY_AND_MOVE(TypeName) \
	TypeName(const TypeName& other) = delete;\
	TypeName(const TypeName&& other) = delete;\
	TypeName(TypeName&& TypeName) = delete;\
	TypeName& operator=(const TypeName& other) = delete;\
	TypeName& operator=(const TypeName&& other) = delete;\
	TypeName& operator=(TypeName&& TypeName) = delete;

typedef unsigned int prx_id_t;

namespace prx {
	// Is an empty struct tag type used to disambiguate between overloaded functions
	struct texture_placeholder {};
	inline constexpr texture_placeholder texture = texture_placeholder();
}
