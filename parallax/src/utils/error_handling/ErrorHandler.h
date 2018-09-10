#pragma once
#ifndef _PARALLAX_UTILS_ERROR_HANDLER_H_
#define _PARALLAX_UTILS_ERROR_HANDLER_H_
// Define PARALLAX_DEBUG to enable debug macros

#define ASSERT(x) if (!(x)) __debugbreak();


#endif
