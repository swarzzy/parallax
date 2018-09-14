#include "Resources.h"

namespace prx {
	
	std::shared_ptr<Texture> Resources::m_DefaultTexture	= nullptr;
	std::shared_ptr<Font>	 Resources::m_DefaultFont		= nullptr;

	gau_Manager*	Resources::m_gaManager	= nullptr;
	ga_Mixer*		Resources::m_gaMixer	= nullptr;

	void Resources::init() {
		m_DefaultFont	 = std::make_shared<Font>(RESOURCES_DEFAULT_FONT_PATH, RESOURCES_DEFAULT_FONT_SIZE);
		m_DefaultTexture = std::make_shared<Texture>(RESOURCES_DEFAULT_TEXTURE_PATH);

		gc_initialize(NULL);
		m_gaManager = gau_manager_create();
		m_gaMixer = gau_manager_mixer(m_gaManager);
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

	std::shared_ptr<Sound> Resources::loadSound(std::string_view path) {
		return std::make_shared<Sound>(path, m_gaMixer);
	}

	void Resources::terminate() {
		gau_manager_destroy(m_gaManager);
		gc_shutdown();
	}
}
