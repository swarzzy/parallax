#include "Sprite.h"
#include "../Renderer2D.h"

namespace prx {

	Sprite::Sprite(const hpm::vec2& size, unsigned int color) 
		: Renderable2D(size, color) 
		, m_WrapMode(SpriteWrapMode::STRETCHING) 
	{
		switch (m_WrapMode) {
		case SpriteWrapMode::STRETCHING : {setUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL: {setWrapHorizontalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL: {setWrapVerticalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR: {setWrapBothDirUV(); break; }
		default: {PRX_WARN("SPRITE: Unknown wrapping mode. Setting wrap mode to STRETCHING."); setUV(); }
		}
	}

	Sprite::Sprite(const hpm::vec2& size, TextureBase* texture)
		: Renderable2D(size, texture)
		, m_WrapMode(SpriteWrapMode::STRETCHING) 
	{
		switch (m_WrapMode) {
		case SpriteWrapMode::STRETCHING: {setUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL: {setWrapHorizontalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL: {setWrapVerticalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR: {setWrapBothDirUV(); break; }
		default: {PRX_WARN("SPRITE: Unknown wrapping mode. Setting wrap mode to STRETCHING."); setUV(); }
		}
	}

	Sprite::Sprite(const hpm::vec2& size, TextureBase* texture, TextureBase* normalMap) 
		: Renderable2D(size, texture, normalMap)
		, m_WrapMode(SpriteWrapMode::STRETCHING)
	{
		switch (m_WrapMode) {
		case SpriteWrapMode::STRETCHING: {setUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL: {setWrapHorizontalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL: {setWrapVerticalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR: {setWrapBothDirUV(); break; }
		default: {PRX_WARN("SPRITE: Unknown wrapping mode. Setting wrap mode to STRETCHING."); setUV(); }
		}
	}
	

	Sprite::Sprite(float width, float height, unsigned color) 
		: Renderable2D(width, height, color)
		, m_WrapMode(SpriteWrapMode::STRETCHING) 
	{
		switch (m_WrapMode) {
		case SpriteWrapMode::STRETCHING: {setUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL: {setWrapHorizontalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL: {setWrapVerticalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR: {setWrapBothDirUV(); break; }
		default: {PRX_WARN("SPRITE: Unknown wrapping mode. Setting wrap mode to STRETCHING."); setUV(); }
		}
	}

	Sprite::Sprite(float width, float height, TextureBase* texture) 
		: Renderable2D(width, height, texture) 
		, m_WrapMode(SpriteWrapMode::STRETCHING) 
	{
		switch (m_WrapMode) {
		case SpriteWrapMode::STRETCHING: {setUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL: {setWrapHorizontalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL: {setWrapVerticalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR: {setWrapBothDirUV(); break; }
		default: {PRX_WARN("SPRITE: Unknown wrapping mode. Setting wrap mode to STRETCHING."); setUV(); }
		}
	}

	Sprite::Sprite(float width, float height, TextureBase* texture, TextureBase* normalMap)
		: Renderable2D({ width, height }, texture, normalMap)
		, m_WrapMode(SpriteWrapMode::STRETCHING)
	{
		switch (m_WrapMode) {
		case SpriteWrapMode::STRETCHING: {setUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL: {setWrapHorizontalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL: {setWrapVerticalUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR: {setWrapBothDirUV(); break; }
		default: {PRX_WARN("SPRITE: Unknown wrapping mode. Setting wrap mode to STRETCHING."); setUV(); }
		}
	}

	void Sprite::setWrapMode(SpriteWrapMode mode) {
		if (mode == SpriteWrapMode::STRETCHING && m_WrapMode != SpriteWrapMode::STRETCHING) {
			if (m_Reflected)
				setReflectedUV();
			else
				setUV();
		}
		else if (mode == SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL && m_WrapMode != SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL) {
			if (m_Reflected)
				setReflectedWrapHorizontalUV();
			else
				setWrapHorizontalUV();
		}
		else if (mode == SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL && m_WrapMode != SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL) {
			if (m_Reflected)
				setReflectedWrapVerticalUV();
			else
				setWrapVerticalUV();
		}

		else if (mode == SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR && m_WrapMode != SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR) {
			if (m_Reflected)
				setReflectedWrapBothDirUV();
			else
				setWrapBothDirUV();
		}

		m_WrapMode = mode;
	}

	void Sprite::reflect(bool reflect) noexcept {
		if (m_Reflected && !reflect) {
			m_Reflected = false;
			switch (m_WrapMode) {
			case SpriteWrapMode::STRETCHING: {setUV(); break; }
			case SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL: {setWrapHorizontalUV(); break; }
			case SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL: {setWrapVerticalUV(); break; }
			case SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR: {setWrapBothDirUV(); break; }
			default: {PRX_WARN("SPRITE: Unknown wrapping mode. Setting wrap mode to STRETCHING."); setUV(); }
			}
		}
		else if (!m_Reflected && reflect) {
			m_Reflected = true;
			switch (m_WrapMode) {
			case SpriteWrapMode::STRETCHING: {setReflectedUV(); break; }
			case SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL: {setReflectedWrapHorizontalUV(); break; }
			case SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL: {setReflectedWrapVerticalUV(); break; }
			case SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR: {setReflectedWrapBothDirUV(); break; }
			default: {PRX_WARN("SPRITE: Unknown wrapping mode. Setting wrap mode to STRETCHING."); setReflectedUV(); }
			}
		}
	}

	void Sprite::setWrapHorizontalUV() {
		float aspectRatio = m_Width / m_Height;
		m_UVs[0] = 0.0f;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 0.0f;
		m_UVs[3] = 1.0f;

		m_UVs[4] = 1.0f * aspectRatio;
		m_UVs[5] = 1.0f;

		m_UVs[6] = 1.0f * aspectRatio;
		m_UVs[7] = 0.0f;
	}

	void Sprite::setReflectedWrapHorizontalUV() {
		float aspectRatio = m_Width / m_Height;
		m_UVs[0] = 1.0f * aspectRatio;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 1.0f * aspectRatio;
		m_UVs[3] = 1.0f;

		m_UVs[4] = 0.0f;
		m_UVs[5] = 1.0f;

		m_UVs[6] = 0.0f;
		m_UVs[7] = 0.0f;
	}

	void Sprite::setWrapVerticalUV() {
		float aspectRatio = m_Height / m_Width;
		m_UVs[0] = 0.0f;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 0.0f;
		m_UVs[3] = 1.0f * aspectRatio;

		m_UVs[4] = 1.0f;
		m_UVs[5] = 1.0f * aspectRatio;

		m_UVs[6] = 1.0f;
		m_UVs[7] = 0.0f;
	}

	void Sprite::setReflectedWrapVerticalUV() {
		float aspectRatio = m_Height / m_Width;
		m_UVs[0] = 1.0f;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 1.0f;
		m_UVs[3] = 1.0f * aspectRatio;

		m_UVs[4] = 0.0f;
		m_UVs[5] = 1.0f * aspectRatio;

		m_UVs[6] = 0.0f;
		m_UVs[7] = 0.0f;
	}

	void Sprite::setWrapBothDirUV() {
		float aspectRatioV;
		float aspectRatioH;
		if (m_Texture != nullptr) {
			if (!m_Texture->isInitialized())
				// NOTE: This initialization might broke whole stupid concept of initialization
				m_Texture->init();
			aspectRatioH = m_Width / m_Texture->getWidth() ;
			aspectRatioV = m_Height / m_Texture->getHeight();
		} else {
			aspectRatioH = 1.0f;
			aspectRatioV = 0.0f;
		}
		m_UVs[0] = 0.0f;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 0.0f;
		m_UVs[3] = 1.0f * aspectRatioV;

		m_UVs[4] = 1.0f * aspectRatioH;
		m_UVs[5] = 1.0f * aspectRatioV;

		m_UVs[6] = 1.0f *aspectRatioH;
		m_UVs[7] = 0.0f;
	}

	void Sprite::setReflectedWrapBothDirUV() {
		float aspectRatioV = m_Height / m_Width;
		float aspectRatioH = m_Width / m_Height;
		m_UVs[0] = 1.0f * aspectRatioH;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 1.0f * aspectRatioH;
		m_UVs[3] = 1.0f * aspectRatioV;

		m_UVs[4] = 0.0f;
		m_UVs[5] = 1.0f * aspectRatioV;

		m_UVs[6] = 0.0f;
		m_UVs[7] = 0.0f;
	}

	void Sprite::submit(Renderer2D* renderer, const hpm::mat3& worldMatrix, float depth) {
		renderer->drawRenderable(worldMatrix, depth, this);
	}

	void Sprite::setUV() {
		m_UVs[0] = 0.0f;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 0.0f;
		m_UVs[3] = 1.0f;

		m_UVs[4] = 1.0f;
		m_UVs[5] = 1.0f;

		m_UVs[6] = 1.0f;
		m_UVs[7] = 0.0f;
	}

	void Sprite::setReflectedUV() {
		m_UVs[0] = 1.0f;
		m_UVs[1] = 0.0f;

		m_UVs[2] = 1.0f;
		m_UVs[3] = 1.0f;

		m_UVs[4] = 0.0f;
		m_UVs[5] = 1.0f;

		m_UVs[6] = 0.0f;
		m_UVs[7] = 0.0f;
	}
}