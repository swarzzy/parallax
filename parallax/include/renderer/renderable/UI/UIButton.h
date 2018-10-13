#pragma once
#ifndef _PARALLAX_RENDERER_UI_BUTTON_H_
#define _PARALLAX_RENDERER_UI_BUTTON_H_
#include "UIButtonBase.h"

namespace prx {
	class UIButton : public UIButtonBase {
	public:
		UIButton(const hpm::vec2& position, float size, std::string_view text);

		UIButton(const hpm::vec2& position, float size, std::string_view text, Font* customFont);

		UIButton(const hpm::vec2& position, float size, std::string_view text,
				 Texture* customTexPressed, Texture* customTexReleased);

		UIButton(const hpm::vec2& position, float size, std::string_view text, Font* customFont,
				 Texture* customTexPressed, Texture* customTexReleased);

		UIButton(const hpm::vec2& position, float size);

		UIButton(const hpm::vec2& position, float size,
				 Texture* customTexPressed, Texture* customTexReleased);
	};
}
#endif
