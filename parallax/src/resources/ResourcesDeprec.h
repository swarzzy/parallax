//#pragma once
//#ifndef _PARALLAX_RESOURCES_RESOURCES_H_
//#define _PARALLAX_RESOURCES_RESOURCES_H_
//#include <memory>
//
//#include "../utils/log/Log.h"
//
//#include "../shading/Texture.h"
//#include "../Fonts/Font.h"
//#include "../shading/Shader.h"
//#include "../audio/Sound.h"
//
//#include <gorilla-audio/ga.h>
//#include <gorilla-audio/gau.h>
//
//namespace prx {
//
//	static const char*			RESOURCES_DEFAULT_TEXTURE_PATH	= "res/textures/default.jpg";
//	static const char*			RESOURCES_DEFAULT_FONT_PATH		= "res/fonts/NotoSans-Regular.ttf";
//	static const unsigned int	RESOURCES_DEFAULT_FONT_SIZE		= 30;
//
//	class Resources {
//	private:
//		static Texture*	 m_DefaultTexture;
//		static Font*		m_DefaultFont;
//
//		static gau_Manager*		m_gaManager;
//		static ga_Mixer*		m_gaMixer;
//
//	public:
//		Resources() = delete;
//
//		static void init();
//		static void initAudioSystem();
//
//		static Texture* loadTexture	(std::string_view path = RESOURCES_DEFAULT_TEXTURE_PATH);
//		static Font*	loadFont	(std::string_view path = RESOURCES_DEFAULT_FONT_PATH, unsigned int size = RESOURCES_DEFAULT_FONT_SIZE);
//		static Shader*	loadShader	(std::string_view vertPath, std::string_view fragPath);
//		static Sound*	loadSound	(std::string_view path);
//
//		static void terminate();
//
//	private:
//		friend class Window;
//	};
//}
//#endif
