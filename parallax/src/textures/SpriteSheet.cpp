#include <textures/SpriteSheet.h>
#include <resources/ImageLoader.h>

namespace prx {

	SpriteSheet::SpriteSheet(std::string_view path, unsigned int columns, unsigned int rows)
		: m_Path(path), m_Columns(columns), m_Rows(rows), m_Tiles(columns * rows),
		m_TexCoords(new TexCoords[m_Tiles]),m_TimePerState(1000 / m_Tiles), 
		m_CurrentState(0), m_TimeElapsed(0) {
		
		m_TexID = load();

		// Calculate tex coords
		unsigned int spriteWidth  = m_Width / m_Rows;
		unsigned int spriteHeight = m_Height / m_Columns;
		
		int coordCounter = (m_Columns * m_Rows) - 1;
		
		for (int i = 0; i  < m_Width; i+= spriteWidth) {
			for (int j = m_Height - spriteHeight; j >= 0; j-= spriteHeight) {
				float leftBottomX = static_cast<float>(j) / m_Width;
				float leftBottomY = static_cast<float>(i) / m_Height;
				
				m_TexCoords[coordCounter].lbX = leftBottomX;
				m_TexCoords[coordCounter].lbY = leftBottomY;

				m_TexCoords[coordCounter].ltX = leftBottomX;
				m_TexCoords[coordCounter].ltY = leftBottomY + static_cast<float>(spriteHeight) / m_Height;

				m_TexCoords[coordCounter].rtX = leftBottomX + static_cast<float>(spriteWidth) / m_Width;
				m_TexCoords[coordCounter].rtY = leftBottomY + static_cast<float>(spriteHeight) / m_Height;

				m_TexCoords[coordCounter].rbX = leftBottomX + static_cast<float>(spriteWidth) / m_Width;
				m_TexCoords[coordCounter].rbY = leftBottomY;
				coordCounter--;
			}
		}
	}

	SpriteSheet::~SpriteSheet() {
		GLCall(glDeleteTextures(1, &m_TexID));
		delete m_TexCoords;
	}

	const TexCoords& SpriteSheet::getTexCoords() const {
		auto currentTime = Application::getCurrentApplication().getTime();
		
		if (currentTime - m_TimeElapsed > m_TimePerState) {
			m_CurrentState == m_Tiles - 1 ? m_CurrentState = 0 : m_CurrentState++;
			m_TimeElapsed = currentTime;
		}
		return m_TexCoords[m_CurrentState];
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
