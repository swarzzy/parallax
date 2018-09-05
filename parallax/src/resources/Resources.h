#pragma once
#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include <map>
#include <string_view>

#include "../shading/Shader.h"
#include "../Fonts/Font.h"
#include "../shading/Texture.h"

namespace prx {
	// TODO: Do that actually needs constexpr?
	constexpr const char*			RESOURCES_DEFAULT_FONT_NAME = "parallax_default_font";
	constexpr const unsigned int	RESOURCES_DEFAULT_FONT_SIZE = 80;
	static constexpr const char*	RESOURCES_DEFAULT_FONT_PATH = "res/fonts/NotoSans-Regular.ttf";

	class

	class Resources {
	private:
		Resources();

		static std::map<unsigned int, Shader> m_Shaders;
		static std::map<unsigned int, Font> m_Fonts;
		static std::map<unsigned int, std::shared_ptr<Texture>> m_Textures;

		static std::map<unsigned int, bool> m_TextureStatus;

		static Font* m_DefaultFontPointer;


	public:
		static bool init();
		// SHADERS:
		// Creates shader if it`s doesn`t exist yet and returns pointer to new created shader or existing shader from map.
		static Shader* loadShader(std::string_view name, std::string_view vertexPath,
			std::string_view fragmentPath);
		// If shader exists returns pointer on it, otherwise returns nullptr
		static Shader* getShader(std::string_view name);
		static Shader* getShader(unsigned int hashName);

		static void deleteShader(std::string_view name);
		static void deleteShader(unsigned int hashName);

		// FONTS:
		static Font* loadFont(std::string_view name, std::string_view fontPath, unsigned int size);
		
		static Font* getFont(std::string_view name);
		static Font* getFont(unsigned int hashName);
		
		static void	 deleteFont(std::string_view name);
		static void  deleteFont(unsigned int hashName);

		// TEXTURES
		static std::shared_ptr<Texture> loadTexture(std::string_view name, std::string_view path);

		//static Texture* getTexture(std::string_view name);
		//static Texture* getTexture(unsigned int hashName);

		//static void deleteTexture(std::string_view name);
		//static void deleteTexture(unsigned int hashName);

		// Clear all resources, even defaults
		static void ternimate();
	};
}
#endif
