//#pragma once
//#ifndef _RESOURCES_H_
//#define _RESOURCES_H_
//
//#include <map>
//#include <string_view>
//
//#include "../utils/SimpleHash.h"
//
//#include "../ext/gorilla/ga.h"
//#include "../ext/gorilla/gau.h"
//
//#include "../audio/Sound.h"
//
//namespace prx {
//
//	class Texture;
//	class Font;
//	class Shader;
//
//	static const char*			RESOURCES_DEFAULT_TEXTURE_PATH	= "res/textures/default.jpg";
//	static const char*			RESOURCES_DEFAULT_TEXTURE_NAME	= "parallax_default_texture";
//	static const unsigned int	RESOURCES_DEFAULT_TEXTURE_ID	= SimpleHash::hashString(RESOURCES_DEFAULT_TEXTURE_NAME);
//	
//	static const char*			RESOURCES_DEFAULT_FONT_NAME		= "parallax_default_font";
//	static const unsigned int	RESOURCES_DEFAULT_FONT_ID		= SimpleHash::hashString(RESOURCES_DEFAULT_FONT_NAME);
//	static const unsigned int	RESOURCES_DEFAULT_FONT_SIZE		= 30;
//
//	static const char*			UI_BUTTON_DEFAULT_TEXTURE_PRESSED_PATH = "res/textures/button_pressed.png";
//	static const unsigned int	UI_BUTTON_DEFAULT_TEXTURE_PRESSED_ID = SimpleHash::hashString(UI_BUTTON_DEFAULT_TEXTURE_PRESSED_PATH);
//	static const char*			UI_BUTTON_DEFAULT_TEXTURE_RELEASED_PATH = "res/textures/button_released.png";
//	static const unsigned int	UI_BUTTON_DEFAULT_TEXTURE_RELEASED_ID = SimpleHash::hashString(UI_BUTTON_DEFAULT_TEXTURE_RELEASED_PATH);
//
//	class Resources {
//	private:
//		static std::map<unsigned int, Font>		m_Fonts;
//		static std::map<unsigned int, Texture>	m_Textures;
//		static std::map<unsigned int, Sound>	m_Sounds;
//
//		// Gorilla-audio
//		static gau_Manager*		m_gaManager;
//		static ga_Mixer*		m_gaMixer;
//
//	public:
//		Resources() = delete;
//
//		static bool initAudioSystem();
//
//		static bool init();
//
//		// NEW FEATURES
//
//
//
//		//!
//
//		// FONTS
//		static unsigned int loadFont(std::string_view fontPath, unsigned int size, float scale = 1.0f);
//		
//		static Font* getFont(unsigned int id);
//		static Font* getDefaultFont();
//		
//		static void  deleteFont(unsigned int id);
//		static void clearFonts();
//
//		// TEXTURES
//		static unsigned int loadTexture(std::string_view path);
//
//		static Texture* getTexture(unsigned int id);
//		static Texture* getDefaultTexture();
//
//		static void  deleteTexture(unsigned int id);
//		// Deletes all fonts
//		static void clearTextures();
//
//		// SOUNDS
//		static unsigned int loadSound(std::string_view name, std::string_view path);
//
//		static Sound* getSound(std::string_view name);
//		static Sound* getSound(unsigned int id);
//
//		static void deleteSound(std::string_view name);
//		static void deleteSound(unsigned int id);
//
//		static void clearSounds();
//
//		// Delete all resources
//		static void clear();
//
//		// Delete all resources and terminate all resource systems
//		static void terminate();
//
//	private:
//		friend class Window;
//	};
//}
//#endif
