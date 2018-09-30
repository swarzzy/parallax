#include <textures/SpriteSheet.h>
#include <resources/ImageLoader.h>

namespace prx {

	SpriteSheet::SpriteSheet(std::string_view path, unsigned int columns, unsigned int rows, bool reflected)
		: m_Path(path), m_Columns(columns), m_Rows(rows), m_Tiles(columns * rows),
		m_TexCoords(new TexCoords[m_Tiles]),
		m_ReflectedTexCoords(new TexCoords[m_Tiles]),
		m_Reflected(reflected),
		m_CurrentUVBuffer(m_TexCoords),
		m_CurrentApplication(&Application::getCurrentApplication()) {
		
		m_TexID = load();

		// Calculate tex coords
		unsigned int spriteWidth  = m_Width / m_Columns;
		unsigned int spriteHeight = m_Height / m_Rows;
		
		int coordCounter = m_Tiles;
		
			for (int j = m_Height - spriteHeight; j >= 0; j-= spriteHeight) {
		for (int i = 0; i  < m_Width; i+= spriteWidth) {
				float leftBottomX = static_cast<float>(i) / m_Width;
				float leftBottomY = static_cast<float>(j) / m_Height;
				
				m_TexCoords[m_Tiles - coordCounter].lbX = leftBottomX;
				m_TexCoords[m_Tiles - coordCounter].lbY = leftBottomY;
				m_ReflectedTexCoords[m_Tiles - coordCounter].rbX = leftBottomX;
				m_ReflectedTexCoords[m_Tiles - coordCounter].rbY = leftBottomY;


				m_TexCoords[m_Tiles - coordCounter].ltX = leftBottomX;
				m_TexCoords[m_Tiles - coordCounter].ltY = leftBottomY + static_cast<float>(spriteHeight) / m_Height;
				m_ReflectedTexCoords[m_Tiles - coordCounter].rtX = leftBottomX;
				m_ReflectedTexCoords[m_Tiles - coordCounter].rtY = leftBottomY + static_cast<float>(spriteHeight) / m_Height;

				m_TexCoords[m_Tiles - coordCounter].rtX = leftBottomX + static_cast<float>(spriteWidth) / m_Width;
				m_TexCoords[m_Tiles - coordCounter].rtY = leftBottomY + static_cast<float>(spriteHeight) / m_Height;
				m_ReflectedTexCoords[m_Tiles - coordCounter].ltX = leftBottomX + static_cast<float>(spriteWidth) / m_Width;
				m_ReflectedTexCoords[m_Tiles - coordCounter].ltY = leftBottomY + static_cast<float>(spriteHeight) / m_Height;

				m_TexCoords[m_Tiles - coordCounter].rbX = leftBottomX + static_cast<float>(spriteWidth) / m_Width;
				m_TexCoords[m_Tiles - coordCounter].rbY = leftBottomY;
				m_ReflectedTexCoords[m_Tiles - coordCounter].lbX = leftBottomX + static_cast<float>(spriteWidth) / m_Width;
				m_ReflectedTexCoords[m_Tiles - coordCounter].lbY = leftBottomY;
				
			coordCounter--;
			}
		}
	}

	SpriteSheet::~SpriteSheet() {
		GLCall(glDeleteTextures(1, &m_TexID));
		delete[] m_TexCoords;
		delete[] m_ReflectedTexCoords;
	}

	unsigned int SpriteSheet::addAnimation(std::string_view name, const std::vector<unsigned int>& mask) {
		if (mask.size() > m_Tiles) {
			std::stringstream ss;
			ss << "SPRITE SHEET: Mask size mismatch. Texture: " << m_Path;
			Log::message(ss.str(), LOG_ERROR);
			ASSERT(mask.size() <= m_Tiles)
		}
		m_Animations.emplace_back(name, mask.size(), mask);
		return m_Animations.size() - 1;
	}

	const TexCoords& SpriteSheet::getTexCoords(unsigned int animationID) const {
		auto currentTime = m_CurrentApplication->getTime();
		// TODO: handle error when passed id of not existing object
		const Animation& animation = m_Animations[animationID];

		if (currentTime - animation.timeElapsed > animation.timePerState) {
			animation.currentState == animation.framesNumber - 1 ? 
										animation.currentState= 0 : animation.currentState++;
			animation.timeElapsed = currentTime;
		}
		return m_CurrentUVBuffer[animation.UVIndices[animation.currentState]];
	}

	void SpriteSheet::resetAnimations() {
		for (auto& animation : m_Animations)
			animation.currentState = 0;
	}

	void SpriteSheet::reflect(bool reflect) {
		if (m_Reflected && !reflect) {
			m_Reflected = false;
			m_CurrentUVBuffer = m_TexCoords;
		} else if (!m_Reflected && reflect) {
			m_Reflected = true;
			m_CurrentUVBuffer = m_ReflectedTexCoords;
		}
	}

	unsigned SpriteSheet::load() {
		Image* image = ImageLoader::loadImage(m_Path);

		m_Width = image->getWigth();
		m_Height = image->getHeight();

		unsigned int result;
		GLCall(glGenTextures(1, &result));

		GLCall(glBindTexture(GL_TEXTURE_2D, result));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

		GLenum internalFormat;
		if (image->getFormat() == GL_RGB) {
			internalFormat = GL_RGB8;
			m_Format = TextureFormat::RGB;
		}
		else if (image->getFormat() == GL_RGBA) {
			internalFormat = GL_RGBA8;
			m_Format = TextureFormat::RGBA;
		}
		else {
			Log::message("TEXTURE: Could not create texture. Incorrect data format", LOG_ERROR);
			ASSERT(false);
		}

		//GLCall(glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, m_Width, m_Height));
		//GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, image->getFormat(), GL_UNSIGNED_BYTE, image->getPixels()));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, image->getFormat(), GL_UNSIGNED_BYTE, image->getPixels()));
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		delete image;

		return result;
	}
}
