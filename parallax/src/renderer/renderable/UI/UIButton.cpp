//#include <renderer/renderable/UI/UIButton.h>
//
//namespace prx {
//	UIButton::UIButton(const hpm::vec2& position, float size, std::string_view text)
//		: UIButtonBase(position,
//			hpm::vec2(size, size * 0.67f),
//			text,
//			Resources::getFont(RESOURCES_DEFAULT_FONT_ID),
//			Resources::getTexture(UI_BUTTON_DEFAULT_TEXTURE_PRESSED_ID),
//			Resources::getTexture(UI_BUTTON_DEFAULT_TEXTURE_RELEASED_ID)) {
//	}
//
//	UIButton::UIButton(const hpm::vec2& position, float size, std::string_view text, Font* customFont)
//		: UIButtonBase(position,
//			hpm::vec2(size, size * 0.67f),
//			text,
//			customFont,
//			Resources::getTexture(UI_BUTTON_DEFAULT_TEXTURE_PRESSED_ID),
//			Resources::getTexture(UI_BUTTON_DEFAULT_TEXTURE_RELEASED_ID)) {
//	}
//
//	UIButton::UIButton(const hpm::vec2& position, float size, std::string_view text,
//					   Texture* customTexPressed,Texture* customTexReleased) 
//		: UIButtonBase(position,
//			hpm::vec2(size, size * 0.67f),
//			text,
//			Resources::getFont(RESOURCES_DEFAULT_FONT_ID),
//			customTexPressed,
//			customTexReleased) {
//	}
//
//	UIButton::UIButton(const hpm::vec2& position, float size, std::string_view text, Font* custonFont,
//		Texture* customTexPressed, Texture* customTexReleased) 
//		: UIButtonBase(position,
//			hpm::vec2(size, size * 0.67f),
//			text,
//			custonFont,
//			customTexPressed,
//			customTexReleased) {
//	}
//
//	UIButton::UIButton(const hpm::vec2& position, float size)
//		: UIButtonBase(position,
//			hpm::vec2(size, size * 0.67f),
//			"",
//			Resources::getFont(RESOURCES_DEFAULT_FONT_ID),
//			Resources::getTexture(UI_BUTTON_DEFAULT_TEXTURE_PRESSED_ID),
//			Resources::getTexture(UI_BUTTON_DEFAULT_TEXTURE_RELEASED_ID)) {
//	}
//
//	UIButton::UIButton(const hpm::vec2& position, float size,
//					   Texture* customTexPressed, Texture* customTexReleased)
//		: UIButtonBase(position,
//			hpm::vec2(size, size * 0.67f),
//			"",
//			Resources::getFont(RESOURCES_DEFAULT_FONT_ID),
//			customTexPressed,
//			customTexReleased) {
//	}
//}
