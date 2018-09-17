#include <resources/Resources.h>
#include <utils/SimpleHash.h>

namespace prx {

	std::map<unsigned int, Shader>	Resources::m_Shaders	= std::map<unsigned int, Shader>();
	std::map<unsigned int, Font>	Resources::m_Fonts		= std::map<unsigned int, Font>();
	std::map<unsigned int, Texture> Resources::m_Textures	= std::map<unsigned int, Texture>();
	std::map<unsigned int, Sound>	Resources::m_Sounds		= std::map<unsigned int, Sound>();

	// Gorilla-audio
	gau_Manager*	Resources::m_gaManager	= nullptr;
	ga_Mixer*		Resources::m_gaMixer	= nullptr;

	bool Resources::initAudioSystem() {
		gc_result result = gc_initialize(NULL);
		m_gaManager = gau_manager_create_custom(GA_DEVICE_TYPE_DEFAULT, GAU_THREAD_POLICY_MULTI, 4, 512);
		m_gaMixer = gau_manager_mixer(m_gaManager);

		if (result == GC_ERROR_GENERIC || m_gaMixer == nullptr || m_gaManager == nullptr) {
			Log::message("RESOURCE MANAGER: Could not initialize audio system!", LOG_ERROR);
			return false;
		}
		return true;
	}

	bool Resources::init() {
		m_Fonts.emplace(std::piecewise_construct, std::forward_as_tuple(RESOURCES_DEFAULT_FONT_ID), 
							std::forward_as_tuple(RESOURCES_DEFAULT_FONT_PATH, RESOURCES_DEFAULT_FONT_SIZE));
		m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(RESOURCES_DEFAULT_TEXTURE_ID), 
							std::forward_as_tuple(RESOURCES_DEFAULT_TEXTURE_PATH));
		if (m_gaManager == nullptr) {
			Log::message("RESOURCE MANAGER: Audio system is not initialized!", LOG_WARNING);
			return false;
		}
		return true;
	}

	 unsigned int Resources::loadShader(std::string_view name, std::string_view vertexPath, std::string_view fragmentPath) {
		unsigned int id =  SimpleHash::hashString(name);
		auto element = m_Shaders.find(id);
		if (element != m_Shaders.end()) {
			std::stringstream ss;
			ss << "RESOURCE MANAGER: Shader: " << name << " already exist!";
			Log::message(ss.str(), LOG_WARNING);
			return id;
		}
		//m_Shaders.emplace(id, vertexPath, fragmentPath);
		 m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(id),
			std::forward_as_tuple(vertexPath, fragmentPath));
		return id;
	}

	 Shader* Resources::getShader(std::string_view name) {
		auto element = m_Shaders.find( SimpleHash::hashString(name));
		if (element != m_Shaders.end())
			return &element->second;
		std::stringstream ss;
		ss << "RESOURCE MANAGER: Shader (name: " << name << " does not exist!";
		Log::message(ss.str(), LOG_WARNING);
		return nullptr;
	}

	Shader* Resources::getShader(unsigned id) {
		auto element = m_Shaders.find(id);
		if (element != m_Shaders.end())
			return &(element->second);
		std::stringstream ss;
		ss << "RESOURCE MANAGER: Shader (ID: " << id << " does not exist!";
		Log::message(ss.str(), LOG_WARNING);
		return nullptr;
	}

	void Resources::deleteShader(std::string_view name) {
		m_Shaders.erase( SimpleHash::hashString(name));
	}

	void Resources::deleteShader(unsigned int id) {
		m_Shaders.erase(id);
	}

	void Resources::clearShaders() {
		m_Shaders.clear();
	}

	unsigned int Resources::loadFont(std::string_view fontPath, unsigned int size) {
		std::stringstream ss;
		ss << fontPath << size;
		unsigned int id = SimpleHash::hashString(ss.str());
		auto font = m_Fonts.find(id);
		if (font != m_Fonts.end()) {
			std::stringstream ss;
			ss << "RESOURCE MANAGER: Font: " << fontPath << " already exist!";
			Log::message(ss.str(), LOG_WARNING);
			return id;
		}
		//m_Fonts.emplace(id, fontPath, size);
		m_Fonts.emplace(std::piecewise_construct, 
							std::forward_as_tuple(id), std::forward_as_tuple(fontPath, size));
		return id;
	}

	Font* Resources::getFont(unsigned int id) {
		auto font = m_Fonts.find(id);
		if (font != m_Fonts.end())
			return &(font->second);
		std::stringstream ss;
		ss << "RESOURCE MANAGER: Font (ID: " << id << " does not exist! Using default font.";
		Log::message(ss.str(), LOG_WARNING);
		return &m_Fonts[RESOURCES_DEFAULT_FONT_ID];
	}

	void Resources::deleteFont(unsigned int id) {
		if (id == RESOURCES_DEFAULT_FONT_ID) {
			Log::message("RESOURCE MANAGER: Can not delete default font!", LOG_WARNING);
			return;
		}
		m_Fonts.erase(id);
	}

	void Resources::clearFonts() {
		m_Fonts.clear();
		m_Fonts.emplace(std::piecewise_construct, std::forward_as_tuple(RESOURCES_DEFAULT_FONT_ID),
			std::forward_as_tuple(RESOURCES_DEFAULT_FONT_PATH, RESOURCES_DEFAULT_FONT_SIZE));
	}

	unsigned Resources::loadTexture(std::string_view path) {
		unsigned int id = SimpleHash::hashString(path);
		auto iterator = m_Textures.find(id);
		if (iterator != m_Textures.end()) {
			std::stringstream ss;
			ss << "RESOURCE MANAGER: Texture: " << path << " already exist!";
			Log::message(ss.str(), LOG_WARNING);
			return id;
		}
		//m_Textures.emplace(id, path);
		auto result = m_Textures.emplace(std::piecewise_construct, 
										std::forward_as_tuple(id), std::forward_as_tuple(path));
		return id;
	}

	Texture* Resources::getTexture(unsigned int id) {
		auto texture = m_Textures.find(id);
		if (texture != m_Textures.end())
			return &(texture->second);
		std::stringstream ss;
		ss << "RESOURCE MANAGER: Texture (ID: " << id << " does not exist! Using default texture.";
		Log::message(ss.str(), LOG_WARNING);
		return &m_Textures[RESOURCES_DEFAULT_TEXTURE_ID];
	}

	void Resources::deleteTexture(unsigned int id) {
		if (id == RESOURCES_DEFAULT_TEXTURE_ID) {
			Log::message("RESOURCE MANAGER: Can not delete default texture!", LOG_WARNING);
			return;
		}
		m_Textures.erase(id);
	}

	void Resources::clearTextures() {
		m_Textures.clear();
		m_Textures.emplace(std::piecewise_construct, std::forward_as_tuple(RESOURCES_DEFAULT_TEXTURE_ID),
			std::forward_as_tuple(RESOURCES_DEFAULT_TEXTURE_PATH));
	}

	unsigned Resources::loadSound(std::string_view name, std::string_view path) {
		unsigned int id = SimpleHash::hashString(name);
		auto sound = m_Sounds.find(id);
		if (sound != m_Sounds.end()) {
			std::stringstream ss;
			ss << "RESOURCE MANAGER: Sound: " << name << " already exist!";
			Log::message(ss.str(), LOG_WARNING);
			return id;
		}
		//m_Sounds.emplace(id, path);
		m_Sounds.emplace(std::piecewise_construct, std::forward_as_tuple(id),
							std::forward_as_tuple(path, m_gaMixer));
		return id;
	}

	Sound* Resources::getSound(std::string_view name) {
		auto sound = m_Sounds.find(SimpleHash::hashString(name));
		if (sound != m_Sounds.end())
			return &sound->second;
		std::stringstream ss;
		ss << "RESOURCE MANAGER: Sound (name: " << name << " does not exist!";
		Log::message(ss.str(), LOG_WARNING);
		return nullptr;
	}

	Sound* Resources::getSound(unsigned id) {
		auto sound = m_Sounds.find(id);
		if (sound != m_Sounds.end())
			return &(sound->second);
		std::stringstream ss;
		ss << "RESOURCE MANAGER: Sound (ID: " << id << " does not exist!";
		Log::message(ss.str(), LOG_WARNING);
		return nullptr;
	}

	void Resources::deleteSound(std::string_view name) {
		m_Sounds.erase(SimpleHash::hashString(name));
	}

	void Resources::deleteSound(unsigned id) {
		m_Sounds.erase(id);
	}

	void Resources::clearSounds() {
		m_Sounds.clear();
	}

	void Resources::clear() {
		clearShaders();
		clearFonts();
		clearTextures();
		clearSounds();
	}

	void Resources::terminate() {
		m_Shaders.clear();
		m_Fonts.clear();
		m_Textures.clear();
		m_Sounds.clear();
		
		// gorilla-audio terminate
		gau_manager_destroy(m_gaManager);
		gc_shutdown();
	}
}

