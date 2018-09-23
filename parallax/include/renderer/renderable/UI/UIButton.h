#pragma once
#ifndef _PARALLAX_RENDERER_UI_BUTTON_H_
#define _PARALLAX_RENDERER_UI_BUTTON_H_
#include "UIButtonBase.h"

namespace prx {
	class UIButton : public UIButtonBase {
	public:
		UIButton(hpm::vec3 position, float size, std::string_view text);

		UIButton(hpm::vec3 position, float size, std::string_view text, Font* customFont);

		UIButton(hpm::vec3 position, float size, std::string_view text, 
				 Texture* customTexPressed, Texture* customTexReleased);

		UIButton(hpm::vec3 position, float size, std::string_view text, Font* custonFont, 
				 Texture* customTexPressed, Texture* customTexReleased);

		UIButton(hpm::vec3 position, float size);

		UIButton(hpm::vec3 position, float size,
				 Texture* customTexPressed, Texture* customTexReleased);
	};
}
#endif
