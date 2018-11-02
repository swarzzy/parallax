#pragma once

#include "../Common.h"
#include "../utils/Singleton.h"
#include <vector>

namespace prx {

	class Font;

	class FontManager final : public Singleton<FontManager> {
		PRX_DISALLOW_COPY_AND_MOVE(FontManager)
	public:
		friend class Singleton<FontManager>;

	private:

		static const unsigned DEFAULT_FONT_SIZE = 30;

		std::vector<Font> m_Fonts;
		std::vector<Font> m_DefaultFonts;
		float m_Scale;

		FontManager(float scale);

	public:
		~FontManager();

		// !!!Makes all pointers invalid
		void reload(float scale);
		inline float getScale() const noexcept;

		Font* load(std::string_view filepath, std::string_view name, unsigned size);
		Font* get(std::string_view name, unsigned size);

		Font* getDefault();
		Font* getDefault(unsigned size);

		void clean();
	};

	inline float FontManager::getScale() const noexcept {
		return m_Scale;
	}
}

