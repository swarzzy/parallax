#pragma once

#include "../Common.h"
#include "../utils/Singleton.h"

#include <unordered_map>

namespace prx {

	class Font;

	class FontManager final : public Singleton<FontManager> {
		PRX_DISALLOW_COPY_AND_MOVE(FontManager)
	public:
		friend class Singleton<FontManager>;

	private:

		static const unsigned	DEFAULT_FONT_SIZE = 30;
		static const char*		DEFAULT_FONT_NAME;

		std::unordered_map<prx_id_t, Font*> m_Fonts;
		Font*								m_DefaultFont;
		float								m_Scale;

		FontManager(float scale);

	public:
		~FontManager();

		void reload(float scale);
		inline float getScale() const noexcept;

		Font* load(std::string_view filepath, std::string_view name, unsigned size);
		Font* get(std::string_view name, unsigned size);

		Font* getDefault();
		Font* getDefault(unsigned size);

		void clean();

	private:
		void loadDefault();
	};

	inline float FontManager::getScale() const noexcept {
		return m_Scale;
	}
}