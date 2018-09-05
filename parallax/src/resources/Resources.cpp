#include "Resources.h"
#include "../utils/SimpleHash.h"

namespace prx {

	std::map<unsigned int, Shader>	Resources::m_Shaders			= std::map<unsigned int, Shader>();
	std::map<unsigned int, Font>	Resources::m_Fonts				= std::map<unsigned int, Font>();
	Font*							Resources::m_DefaultFontPointer = nullptr;
	std::map<unsigned int, std::shared_ptr<Texture>> Resources::m_Textures = std::map<unsigned int, std::shared_ptr<Texture>>();

	std::map<unsigned int, bool> Resources::m_TextureStatus = std::map<unsigned int, bool>();

	bool Resources::init() {
		
		unsigned int id = SimpleHash::hashString(RESOURCES_DEFAULT_FONT_NAME);
		
		Font font(RESOURCES_DEFAULT_FONT_PATH, RESOURCES_DEFAULT_FONT_SIZE);
		// TODO: That needs exceptions or some error handling to check font load status
		
		auto result = m_Fonts.insert(std::pair<unsigned int, Font>(id, font));
		// TODO: Better error handling bacause this is almost meaningless
		m_DefaultFontPointer = &(result.first->second);
		
		return result.second;
	}

	 Shader* Resources::loadShader(std::string_view name, std::string_view vertexPath, std::string_view fragmentPath) {
		unsigned int id =  SimpleHash::hashString(name);
		auto element = m_Shaders.find(id);
		if (element != m_Shaders.end())
			return &element->second;

		auto result = m_Shaders.emplace(std::piecewise_construct, std::forward_as_tuple(id),
			std::forward_as_tuple(vertexPath, fragmentPath));
		return &result.first->second;
	}

	 Shader* Resources::getShader(std::string_view name) {
		auto element = m_Shaders.find( SimpleHash::hashString(name));
		if (element != m_Shaders.end())
			return &element->second;
		 Log::message("Resources: requested shader object does not exist",  LOG_WARNING);
		return nullptr;
	}

	Shader* Resources::getShader(unsigned hashName) {
		auto element = m_Shaders.find(hashName);
		if (element != m_Shaders.end())
			return &element->second;
		 Log::message("Resources: requested shaer object does not exist",  LOG_WARNING);
		return nullptr;
	}

	void Resources::deleteShader(std::string_view name) {
		m_Shaders.erase( SimpleHash::hashString(name));
	}

	void Resources::deleteShader(unsigned hashName) {
		m_Shaders.erase(hashName);
	}

	Font* Resources::loadFont(std::string_view name, std::string_view fontPath, unsigned int size) {
		unsigned int id = SimpleHash::hashString(name);

		auto font = m_Fonts.find(id);
		if (font != m_Fonts.end())
			return &(font->second);
		// TODO: Exceptions or smth to catch and handle font constructon errors
		auto result = m_Fonts.emplace(std::piecewise_construct, 
										std::forward_as_tuple(id), std::forward_as_tuple(fontPath, size));
		return &(result.first->second);
	}

	Font* Resources::getFont(std::string_view name) {
		unsigned int id = SimpleHash::hashString(name);

		auto font = m_Fonts.find(id);
		if (font != m_Fonts.end())
			return &(font->second);

		std::stringstream msg;
		msg << "RESOURCE MANAGER: Requested font: " << name << " doesn`t exist. Default font is loaded.";
		 Log::message(msg.str(), LOG_WARNING);

		return m_DefaultFontPointer;
	}

	Font* Resources::getFont(unsigned hashName) {
		auto font = m_Fonts.find(hashName);
		if (font != m_Fonts.end())
			return &(font->second);

		std::stringstream msg;
		msg << "RESOURCE MANAGER: Requested font with hashhed name: " << hashName << "doesn`t exist. Default font is loaded.";
		 Log::message(msg.str(), LOG_WARNING);

		return m_DefaultFontPointer;
	}

	void Resources::deleteFont(std::string_view name) {
		m_Fonts.erase(SimpleHash::hashString(name));
	}

	void Resources::deleteFont(unsigned hashName) {
		m_Fonts.erase(hashName);
	}

	std::shared_ptr<Texture> Resources::loadTexture(std::string_view name, std::string_view path) {
		
		unsigned int id = SimpleHash::hashString(name);

		if (m_TextureStatus[id] == false)
			return nullptr;

		auto texture = m_Textures.find(id);
		if (texture != m_Textures.end())
			return texture->second;

		auto result = m_Textures.insert(std::pair<unsigned int, std::shared_ptr<Texture>>(id, std::make_shared<Texture>(path)));
		m_TextureStatus[id] = true;
		return result.first->second;
	}

	void Resources::ternimate() {
		// TODO:: Maybe check for initialization in every method in debug mode;
		m_DefaultFontPointer = nullptr;
		m_Shaders.clear();
		m_Fonts.clear();
	}
}

