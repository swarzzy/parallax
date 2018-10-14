#pragma once
#ifndef _PARALLAX_RENDERER_RENDERABLE2D_H_
#define _PARALLAX_RENDERER_RENDERABLE2D_H_

#include <hypermath.h>;
#include "../../textures/TextureBase.h"

namespace prx {

	class Renderer2D;

	class Renderable2D {
	protected:
		float				m_Width;
		float				m_Height;
		unsigned int		m_Color;
		mutable float		m_UVs[8];
		const TextureBase*	m_Texture;
		bool				m_Reflected;

	protected:
		Renderable2D() noexcept;
		Renderable2D(const hpm::vec2& size, unsigned int color, bool reflected = false) noexcept;
		Renderable2D(float width, float height, unsigned int color, bool reflected = false) noexcept;
		Renderable2D(const hpm::vec2& size, const TextureBase* texture, bool reflected = false) noexcept;
		Renderable2D(float width, float height, const TextureBase* texture, bool reflected = false) noexcept;

	public:
		virtual ~Renderable2D() = default;

		virtual void submit(Renderer2D* renderer, const hpm::mat3& worldMatrix = hpm::mat3(1.0f)) = 0;

		inline void	setColor(unsigned int color) noexcept;
		inline void setSize(hpm::vec2 size) noexcept;
		inline void setTexture(TextureBase* texture) noexcept;

		inline virtual void reflect(bool reflect) noexcept;

		inline float getWidth() const noexcept;
		inline float getHeight() const noexcept;
		inline unsigned int	getColor() const noexcept;
		inline virtual const float*	getUVs() const noexcept;
		inline const TextureBase* getTexture() const noexcept;
		
		inline unsigned int getTexID() const noexcept;

	private:
		virtual void setDefaultUVs() noexcept;
		virtual void setReflectDefaultUVs() noexcept;

	public:
		Renderable2D(const Renderable2D& other) = delete;
		Renderable2D(const Renderable2D&& other) = delete;
		Renderable2D(Renderable2D&& other) = delete;
		const Renderable2D& operator=(const Renderable2D& other) = delete;
		const Renderable2D& operator=(const Renderable2D&& other) = delete;
		const Renderable2D& operator=(Renderable2D&& other) = delete;
	};
	
	void Renderable2D::reflect(bool reflect) noexcept {
		if (m_Reflected && !reflect) {
			m_Reflected = false;
			setDefaultUVs();
		} else if (!m_Reflected && reflect) {
			m_Reflected = true;
			setReflectDefaultUVs();
		}
	};

	inline void Renderable2D::setColor(unsigned color) noexcept {
		if (m_Texture == nullptr)
			m_Color = color;
		else
			PRX_WARN("(Renderable): Seting a color for a renderable that has a texture is not allowed");
	}

	inline void Renderable2D::setSize(hpm::vec2 size) noexcept {
		m_Width = size.x;
		m_Height = size.y;
	}

	inline void Renderable2D::setTexture(TextureBase* texture) noexcept {
		if (m_Texture != nullptr)
			m_Texture = texture;
		else
			PRX_WARN("(Renderable): Setting a texture to a non-textured rectangle is not allowed");
	}

	inline float Renderable2D::getWidth() const noexcept {
		return m_Width;
	}

	inline float Renderable2D::getHeight() const noexcept {
		return m_Height;
	}

	inline unsigned Renderable2D::getColor() const noexcept {
		return m_Color;
	}

	inline const float* Renderable2D::getUVs() const noexcept {
		return m_UVs;
	}

	inline const TextureBase* Renderable2D::getTexture() const noexcept {
		return m_Texture;
	}

	inline unsigned Renderable2D::getTexID() const noexcept {
		return m_Texture == nullptr ? 0 : m_Texture->getID();
	}
}
#endif

