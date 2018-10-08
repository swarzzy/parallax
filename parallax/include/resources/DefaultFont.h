#pragma once
#ifndef _PARALLAX_RESOURCES_DEFAULT_FONT_H_
#define _PARALLAX_RESOURCES_DEFAULT_FONT_H_

namespace prx::internal {

	unsigned char PARALLAX_DEFAULT_FONT_BINARY[] = {
#include "../../src/resources/embedded/SourceSansPro-Light.binary"
	};

	unsigned char* PARALLAX_DEFAULT_FONT_DATA = PARALLAX_DEFAULT_FONT_BINARY;
	size_t PARALLAX_DEFAULT_FONT_DATA_SIZE = sizeof(PARALLAX_DEFAULT_FONT_BINARY);
}
#endif