//#include <resources/Resources.h>
//
//#include <textures/Texture.h>
//#include <Fonts/Font.h>
//#include <shading/Shader.h>
//#include <audio/Sound.h>
//#include <utils/SimpleHash.h>
//
//#include <resources/DefaultFont.h>;
//
//namespace prx {
//
//	std::map<unsigned int, Font>	Resources::m_Fonts		= std::map<unsigned int, Font>();
//	std::map<unsigned int, Texture> Resources::m_Textures	= std::map<unsigned int, Texture>();
//	std::map<unsigned int, Sound>	Resources::m_Sounds		= std::map<unsigned int, Sound>();
//
//	// Gorilla-audio
//	gau_Manager*	Resources::m_gaManager	= nullptr;
//	ga_Mixer*		Resources::m_gaMixer	= nullptr;
//
//	bool Resources::initAudioSystem() {
//		return false;
//	}
//
//	bool Resources::init() {
//		m_Fonts.emplace(std::piecewise_construct, 
//						std::forward_as_tuple(RESOURCES_DEFAULT_FONT_ID), 
//						std::forward_as_tuple(internal::PARALLAX_DEFAULT_FONT_DATA, 
//											  internal::PARALLAX_DEFAULT_FONT_DATA_SIZE, 
//											  RESOURCES_DEFAULT_FONT_SIZE));
//
//		m_Textures.emplace(std::piecewise_construct, 
//						   std::forward_as_tuple(RESOURCES_DEFAULT_TEXTURE_ID), 
//						   std::forward_as_tuple(RESOURCES_DEFAULT_TEXTURE_PATH));
//
//		// UI Default textures
//		//m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(UI_BUTTON_DEFAULT_TEXTURE_PRESSED_ID),
//			//std::forward_as_tuple(UI_BUTTON_DEFAULT_TEXTURE_PRESSED_PATH));
//		//m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(UI_BUTTON_DEFAULT_TEXTURE_RELEASED_ID),
//			//std::forward_as_tuple(UI_BUTTON_DEFAULT_TEXTURE_RELEASED_PATH));
//
//		if (m_gaManager == nullptr) {
//			Log::message(LOG_LEVEL::LOG_FATAL, "RESOURCE MANAGER: Audio system is not initialized!");
//			return false;
//		}
//		return true;
//	}
//
//	unsigned int Resources::loadFont(std::string_view fontPath, unsigned int size, float scale) {
//		std::stringstream ss;
//		ss << fontPath << size;
//		unsigned int id = SimpleHash::hashString(ss.str());
//		auto font = m_Fonts.find(id);
//		if (font != m_Fonts.end()) {
//			std::stringstream ss;
//			ss << "RESOURCE MANAGER: Font: " << fontPath << " already exist!";
//			Log::message(LOG_LEVEL::LOG_WARN, ss.str());
//			return id;
//		}
//		//m_Fonts.emplace(id, fontPath, size);
//		m_Fonts.emplace(std::piecewise_construct, 
//							std::forward_as_tuple(id), std::forward_as_tuple(fontPath, size, scale));
//		return id;
//	}
//
//	Font* Resources::getFont(unsigned int id) {
//		auto font = m_Fonts.find(id);
//		if (font != m_Fonts.end())
//			return &(font->second);
//		std::stringstream ss;
//		ss << "RESOURCE MANAGER: Font (ID: " << id << " does not exist! Using default font.";
//		Log::message(LOG_LEVEL::LOG_WARN, ss.str());
//		return &m_Fonts[RESOURCES_DEFAULT_FONT_ID];
//	}
//
//	Font* Resources::getDefaultFont() {
//		return &m_Fonts[RESOURCES_DEFAULT_FONT_ID];
//	}
//
//	void Resources::deleteFont(unsigned int id) {
//		if (id == RESOURCES_DEFAULT_FONT_ID) {
//			Log::message(LOG_LEVEL::LOG_WARN, "RESOURCE MANAGER: Can not delete default font!");
//			return;
//		}
//		m_Fonts.erase(id);
//	}
//
//	void Resources::clearFonts() {
//		m_Fonts.clear();
//		m_Fonts.emplace(std::piecewise_construct,
//						std::forward_as_tuple(RESOURCES_DEFAULT_FONT_ID),
//						std::forward_as_tuple(internal::PARALLAX_DEFAULT_FONT_DATA,
//											  internal::PARALLAX_DEFAULT_FONT_DATA_SIZE,
//											  RESOURCES_DEFAULT_FONT_SIZE));
//	}
//
//	unsigned Resources::loadTexture(std::string_view path) {
//		unsigned int id = SimpleHash::hashString(path);
//		auto iterator = m_Textures.find(id);
//		if (iterator != m_Textures.end()) {
//			std::stringstream ss;
//			ss << "RESOURCE MANAGER: Texture: " << path << " already exist!";
//			Log::message(LOG_LEVEL::LOG_WARN, ss.str());
//			return id;
//		}
//		//m_Textures.emplace(id, path);
//		auto result = m_Textures.emplace(std::piecewise_construct, 
//										std::forward_as_tuple(id), std::forward_as_tuple(path));
//		return id;
//	}
//
//	Texture* Resources::getTexture(unsigned int id) {
//		auto texture = m_Textures.find(id);
//		if (texture != m_Textures.end())
//			return &(texture->second);
//		std::stringstream ss;
//		ss << "RESOURCE MANAGER: Texture (ID: " << id << " does not exist! Using default texture.";
//		Log::message(LOG_LEVEL::LOG_WARN, ss.str());
//		return &m_Textures[RESOURCES_DEFAULT_TEXTURE_ID];
//	}
//
//	Texture* Resources::getDefaultTexture() {
//		return &m_Textures[RESOURCES_DEFAULT_TEXTURE_ID];
//	}
//
//	void Resources::deleteTexture(unsigned int id) {
//		if (id == RESOURCES_DEFAULT_TEXTURE_ID) {
//			Log::message(LOG_LEVEL::LOG_WARN, "RESOURCE MANAGER: Can not delete default texture!");
//			return;
//		}
//		m_Textures.erase(id);
//	}
//
//	void Resources::clearTextures() {
//		m_Textures.clear();
//		m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(RESOURCES_DEFAULT_TEXTURE_ID),
//			std::forward_as_tuple(RESOURCES_DEFAULT_TEXTURE_PATH));
//	}
//
//	unsigned Resources::loadSound(std::string_view name, std::string_view path) {
//		unsigned int id = SimpleHash::hashString(name);
//		auto sound = m_Sounds.find(id);
//		if (sound != m_Sounds.end()) {
//			std::stringstream ss;
//			ss << "RESOURCE MANAGER: Sound: " << name << " already exist!";
//			Log::message(LOG_LEVEL::LOG_WARN, ss.str());
//			return id;
//		}
//		//m_Sounds.emplace(id, path);
//		///m_Sounds.emplace(std::piecewise_construct, std::forward_as_tuple(id),
//						//	std::forward_as_tuple(path, m_gaMixer));
//		return id;
//	}
//
//	Sound* Resources::getSound(std::string_view name) {
//		auto sound = m_Sounds.find(SimpleHash::hashString(name));
//		if (sound != m_Sounds.end())
//			return &sound->second;
//		std::stringstream ss;
//		ss << "RESOURCE MANAGER: Sound (name: " << name << " does not exist!";
//		Log::message(LOG_LEVEL::LOG_WARN, ss.str());
//		return nullptr;
//	}
//
//	Sound* Resources::getSound(unsigned id) {
//		auto sound = m_Sounds.find(id);
//		if (sound != m_Sounds.end())
//			return &(sound->second);
//		std::stringstream ss;
//		ss << "RESOURCE MANAGER: Sound (ID: " << id << " does not exist!";
//		Log::message(LOG_LEVEL::LOG_WARN, ss.str());
//		return nullptr;
//	}
//
//	void Resources::deleteSound(std::string_view name) {
//		m_Sounds.erase(SimpleHash::hashString(name));
//	}
//
//	void Resources::deleteSound(unsigned id) {
//		m_Sounds.erase(id);
//	}
//
//	void Resources::clearSounds() {
//		m_Sounds.clear();
//	}
//
//	void Resources::clear() {
//		//clearShaders();
//		clearFonts();
//		clearTextures();
//		clearSounds();
//	}
//
//	void Resources::terminate() {
//		//m_Shaders.clear();
//		m_Fonts.clear();
//		m_Textures.clear();
//		m_Sounds.clear();
//	}
//}
//
