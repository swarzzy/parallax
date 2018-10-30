//#include "Resources.h"
//
//namespace prx {
//	
//	Texture* Resources::m_DefaultTexture	= nullptr;
//	Font*	 Resources::m_DefaultFont		= nullptr;
//
//	gau_Manager*	Resources::m_gaManager	= nullptr;
//	ga_Mixer*		Resources::m_gaMixer	= nullptr;
//
//	
//	
//	void Resources::init() {
//		m_DefaultFont	 = new Font(RESOURCES_DEFAULT_FONT_PATH, RESOURCES_DEFAULT_FONT_SIZE);
//		m_DefaultTexture = new Texture(RESOURCES_DEFAULT_TEXTURE_PATH);
//	}
//
//	void Resources::initAudioSystem() {
//		gc_initialize(NULL);
//		//m_gaManager = gau_manager_create();
//		m_gaManager = gau_manager_create_custom(GA_DEVICE_TYPE_DEFAULT, GAU_THREAD_POLICY_MULTI, 4, 512);
//		m_gaMixer = gau_manager_mixer(m_gaManager);
//	}
//
//	Texture* Resources::loadTexture(std::string_view path) {
//		if (path.compare(RESOURCES_DEFAULT_TEXTURE_PATH) == 0)
//			return m_DefaultTexture;
//		return new Texture(path);
//	}
//
//	Font* Resources::loadFont(std::string_view path, unsigned int size) {
//		if (path.compare(RESOURCES_DEFAULT_FONT_PATH) == 0 && size == RESOURCES_DEFAULT_FONT_SIZE)
//			return m_DefaultFont;
//		return new Font(path, size);
//	}
//
//	Shader* Resources::loadShader(std::string_view vertPath, std::string_view fragPath) {
//		return new Shader(vertPath, fragPath);
//	}
//
//	Sound* Resources::loadSound(std::string_view path) {
//		return new Sound(path, m_gaMixer);
//	}
//
//	void Resources::terminate() {
//		
//		delete m_DefaultFont;
//		delete m_DefaultTexture;
//		
//		gau_manager_destroy(m_gaManager);
//		gc_shutdown();
//	}
//}
