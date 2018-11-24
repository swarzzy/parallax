#include "Sprite.h"
#include "../Renderer2D.h"

namespace prx {

	Sprite::Sprite(const hpm::vec2& size, unsigned int color) 
		: Renderable2D(size, color) 
		, m_WrapMode(SpriteWrapMode::STRETCHING) 
	{
		switch (m_WrapMode) {
		case SpriteWrapMode::STRETCHING : {setUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING: {setQuadUV(); break; }
		default: {PRX_WARN("SPRITE: Unknown wrappint mode. Setting wrap mode to STRETCHING."); setUV(); }
		}
	}

	Sprite::Sprite(const hpm::vec2& size, TextureBase* texture)
		: Renderable2D(size, texture)
		, m_WrapMode(SpriteWrapMode::STRETCHING) 
	{
		switch (m_WrapMode) {
		case SpriteWrapMode::STRETCHING: {setUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING: {setQuadUV(); break; }
		default: {PRX_WARN("SPRITE: Unknown wrappint mode. Setting wrap mode to STRETCHING."); setUV(); }
		}
	}

	Sprite::Sprite(float width, float height, unsigned color) 
		: Renderable2D(width, height, color)
		, m_WrapMode(SpriteWrapMode::STRETCHING) 
	{
		switch (m_WrapMode) {
		case SpriteWrapMode::STRETCHING: {setUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING: {setQuadUV(); break; }
		default: {PRX_WARN("SPRITE: Unknown wrappint mode. Setting wrap mode to STRETCHING."); setUV(); }
		}
	}

	Sprite::Sprite(float width, float height, TextureBase* texture) 
		: Renderable2D(width, height, texture) 
		, m_WrapMode(SpriteWrapMode::STRETCHING) 
	{
		switch (m_WrapMode) {
		case SpriteWrapMode::STRETCHING: {setUV(); break; }
		case SpriteWrapMode::TEXTURE_WRAPPING: {setQuadUV(); break; }
		default: {PRX_WARN("SPRITE: Unknown wrappint mode. Setting wrap mode to STRETCHING."); setUV(); }
		}
	}

	void Sprite::setWrapMode(SpriteWrapMode mode) {
		if (mode == SpriteWrapMode::STRETCHING && m_WrapMode != SpriteWrapMode::STRETCHING)
			if (m_Reflected)
				setReflectedUV();
			else
				setUV();

		else if (mode == SpriteWrapMode::TEXTURE_WRAPPING && m_WrapMode != SpriteWrapMode::TEXTURE_WRAPPING)
			if (m_Reflected)
				setReflectedQuadUV();
			else
				setQuadUV();

		m_WrapMode = mode;
	}

	void Sprite::reflect(bool reflect) noexcept {
		if (m_Reflected && !reflect) {
			m_Reflected = false;
			switch (m_WrapMode) {
			case SpriteWrapMode::STRETCHING: {setUV(); break; }
			case SpriteWrapMode::TEXTURE_WRAPPING: {setQuadUV(); break; }
			default: {PRX_WARN("SPRITE: Unknown wrappint mode. Setting wrap mode to STRETCHING."); setUV(); }
			}
		}
		else if (!m_Reflected && reflect) {
			m_Reflected = true;
			switch (m_WrapMode) {
			case SpriteWrapMode::STRETCHING: {setReflectedUV(); break; }
			case SpriteWrapMode::TEXTURE_WRAPPING: {setReflectedQuadUV(); break; }
			default: {PRX_WARN("SPRITE: Unknown wrappint mode. Setting wrap mode to STRETCHING."); setReflectedUV(); }
			}
		}
	}

	void Sprite::setQuadUV() {
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

	void Sprite::setReflectedQuadUV() {
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
