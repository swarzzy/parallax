#include "FontManager.h"
#include "DefaultFont.h"
#include "Font.h"

namespace prx {

	const char* FontManager::DEFAULT_FONT_NAME = "SourceSansProLight";

	FontManager::FontManager(float scale) 
		: m_Scale(scale)
	{
		loadDefault();
	}

	FontManager::~FontManager() {
		for (auto font : m_Fonts)
			delete font.second;
	}

	void FontManager::reload(float scale) {
		m_Scale = scale;
		for (auto font : m_Fonts)
			font.second->reloadWithNewScale(m_Scale);
	}

	Font* FontManager::load(std::string_view filepath, std::string_view name, unsigned size) {
		prx_id_t key = hash_string(std::string(name) + std::to_string(size)); // NOTE: Might be better just add size to the hash
		auto result = m_Fonts.find(key);
		if (result != m_Fonts.end()) {
			PRX_WARN("FONT MANAGER: Trying to load already existing font./n-> NAME: ", name, "/n-> PATH: ", filepath);
			return result->second;
		}
		Font* font = new Font(filepath, name, size, m_Scale);
		auto empResult = m_Fonts.emplace(key, font);
		if (!empResult.second) {
			PRX_ERROR("FONT MANAGER: Failed to load font. \n-> PATH: ", filepath, "\n-> NAME: ", name, "\n-> SIZE: ", size);
			return nullptr;
		}
		return empResult.first->second;
	}

	Font* FontManager::get(std::string_view name, unsigned size) {
		prx_id_t key = hash_string(std::string(name) + std::to_string(size)); // NOTE: Might be better just add size to the hash
		auto result = m_Fonts.find(key);
		if (result == m_Fonts.end()) {
			PRX_ERROR("FONT MANAGER: The requersted font is not loaded yet:\n-> NAME: ", name, "\n-> SIZE: ", size);			
			return nullptr;
		}
		return result->second;
	}

	Font* FontManager::getDefault() {
		return m_DefaultFont;
	}

	Font* FontManager::getDefault(unsigned size) {
		if (size == DEFAULT_FONT_SIZE)
			return m_DefaultFont;

		auto key = hash_string(std::string(DEFAULT_FONT_NAME) + std::to_string(size));
		auto result = m_Fonts.find(key);
		if (result != m_Fonts.end())
			return result->second;

		Font* font = new Font(DEFAULT_FONT_NAME, internal::PARALLAX_DEFAULT_FONT_DATA, internal::PARALLAX_DEFAULT_FONT_DATA_SIZE, size, m_Scale);
		auto empResult = m_Fonts.emplace(key, font);
		if (!empResult.second) {
			PRX_ERROR("FONT MANAGER: Failed to load default font.");
			return nullptr;
		}

		return empResult.first->second;
	}

	void FontManager::clean() {
		for (auto font : m_Fonts)
			delete font.second;
		loadDefault();
	}

	void FontManager::loadDefault() {
		std::string name = std::string(DEFAULT_FONT_NAME);
		auto key = hash_string(name + std::to_string(DEFAULT_FONT_SIZE)); // NOTE: Might be better just add size to the hash
		Font* defaultFont = new Font(name,
			internal::PARALLAX_DEFAULT_FONT_DATA,
			internal::PARALLAX_DEFAULT_FONT_DATA_SIZE,
			DEFAULT_FONT_SIZE,
			m_Scale
		);
		m_DefaultFont = defaultFont;
		m_Fonts.emplace(key, defaultFont);
	}
}