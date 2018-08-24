#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include<GL/glew.h>
#include <string_view>

namespace prx {
	
	class Texture {
	private:
		std::string m_Path;
		unsigned int m_TexID;
		unsigned int m_Width, m_Height;
	public:
		Texture(std::string_view path);
		~Texture();

		void bind() const;
		void unbind() const;

		inline const unsigned int getWidth()	const { return m_Width; }
		inline const unsigned int getHeight()	const { return m_Height; }
		inline const unsigned int getID()		const { return m_TexID; }
	private:
		unsigned int load();
	};

}
#endif