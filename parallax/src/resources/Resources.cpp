#include "Resources.h"
namespace prx {
	
	std::shared_ptr<Texture> Resources::m_DefaultTexture	= nullptr;
	std::shared_ptr<Font>	 Resources::m_DefaultFont		= nullptr;

	void Resources::init() {
		m_DefaultFont	 = std::make_shared<Font>(RESOURCES_DEFAULT_FONT_PATH, RESOURCES_DEFAULT_FONT_SIZE);
		m_DefaultTexture = std::make_shared<Texture>(RESOURCES_DEFAULT_TEXTURE_PATH);
	}

	std::shared_ptr<Texture> Resources::loadTexture(std::string_view path) {
		if (path.compare(RESOURCES_DEFAULT_TEXTURE_PATH) == 0)
			return m_DefaultTexture;
		return std::make_shared<Texture>(path);
	}

	std::shared_ptr<Font> Resources::loadFont(std::string_view path, unsigned int size) {
		if (path.compare(RESOURCES_DEFAULT_FONT_PATH) == 0 && size == RESOURCES_DEFAULT_FONT_SIZE)
			return m_DefaultFont;
		return std::make_shared<Font>(path, size);
	}

	std::shared_ptr<Shader> Resources::loadShader(std::string_view vertPath, std::string_view fragPath) {
		return std::make_shared<Shader>(vertPath, fragPath);
	}
}
