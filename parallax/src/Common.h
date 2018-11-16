#pragma once

// This macro disallows copy and move constructors and assign operators
#define PRX_DISALLOW_COPY_AND_MOVE(TypeName) \
	TypeName(const TypeName& other) = delete;\
	TypeName(const TypeName&& other) = delete;\
	TypeName(TypeName&& TypeName) = delete;\
	TypeName& operator=(const TypeName& other) = delete;\
	TypeName& operator=(const TypeName&& other) = delete;\
	TypeName& operator=(TypeName&& TypeName) = delete;


// Typedefs
typedef unsigned int  prx_id_t;
typedef unsigned char byte;
typedef unsigned int  color_t;

#define PRX_DEPRECATED [[deprecated]]
