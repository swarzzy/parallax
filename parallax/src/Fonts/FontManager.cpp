#include <Fonts/FontManager.h>
#include <Fonts/DefaultFont.h>
#include <Fonts/Font.h>

namespace prx {
	FontManager::FontManager(float scale) 
		: m_Scale(scale)
	{
		m_DefaultFonts.emplace(m_DefaultFonts.begin(), 
							   std::string("SourceSansProLight-") + std::to_string(DEFAULT_FONT_SIZE),
							   internal::PARALLAX_DEFAULT_FONT_DATA,
							   internal::PARALLAX_DEFAULT_FONT_DATA_SIZE,
							   DEFAULT_FONT_SIZE,
							   m_Scale);
	}

	FontManager::~FontManager() {
		m_Fonts.clear();
		m_DefaultFonts.clear();
	}

	void FontManager::reload(float scale) {
		m_Scale = scale;
		std::vector<Font> tmp;
		for (int i = 0; i < m_DefaultFonts.size(); i++) {
			std::string name = m_DefaultFonts[i].getName();
			unsigned size = m_DefaultFonts[i].getSize();
			tmp.emplace_back(name,
							 internal::PARALLAX_DEFAULT_FONT_DATA,
							 internal::PARALLAX_DEFAULT_FONT_DATA_SIZE,
							 size,
							 m_Scale);
		}
		m_DefaultFonts.swap(tmp);
		tmp.clear();

		for (int i = 0; i < m_Fonts.size(); i++) {
			std::string name = m_Fonts[i].getName();
			unsigned size = m_Fonts[i].getSize();
			std::string path = m_Fonts[i].getFilePath();
			tmp.emplace_back(path, name, size, m_Scale);
		}
		m_DefaultFonts.swap(tmp);
		tmp.clear();
	}

	Font* FontManager::load(std::string_view filepath, std::string_view name, unsigned size) {
		for (auto& font : m_Fonts) {
			if (font.getName() == name && font.getSize() == size) {
				PRX_WARN("FONT MANAGER: Trying to load already existing font./n-> NAME: ", name, "/n-> PATH: ", filepath);
				return &font;
			}
		}
		return &m_Fonts.emplace_back(filepath, name, size, m_Scale);
	}

	Font* FontManager::get(std::string_view name, unsigned size) {
		for (auto& font : m_Fonts)
			if (font.getName() == name && font.getSize() == size)
				return &font;
		
		PRX_ERROR("FONT MANAGER: The requersted font is not loaded yet:/n-> NAME: ", name, "/n-> SIZE: ", size);
		return nullptr;
	}

	Font* FontManager::getDefault() {
		return &(*m_DefaultFonts.begin());
	}

	Font* FontManager::getDefault(unsigned size) {
		if (size == DEFAULT_FONT_SIZE)
			return &(*m_DefaultFonts.begin());
		
		for (auto& font : m_DefaultFonts)
			if (font.getSize() == size)
				return &font;

		return &m_DefaultFonts.emplace_back(std::string("SourceSansProLight-") + std::to_string(size),
											internal::PARALLAX_DEFAULT_FONT_DATA,
											internal::PARALLAX_DEFAULT_FONT_DATA_SIZE,
											size,
											m_Scale);
	}

	void FontManager::clean() {
		m_Fonts.clear();
		m_DefaultFonts.clear();
	}
}
