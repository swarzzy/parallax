#pragma once
#ifndef _RENDERABLE2D_H_
#define _RENDERABLE2D_H_

#include <hypermath.h>;

#include "../../textures/TextureBase.h"

namespace prx {

	class Renderer2D;

	struct VertexData {
		hpm::vec3		vertex;
		hpm::vec2		texCoords;
		float			texID;
		unsigned int	color;
	};

	class Renderable2D {
	protected:
		hpm::vec3		m_Position;
		hpm::vec2		m_Size;
		unsigned int	m_Color;
		mutable float	m_UVs[8];
		TextureBase*	m_Texture;
		bool			m_Reflected;

	protected:
		Renderable2D();

	public:
		virtual ~Renderable2D() {};

		Renderable2D(const hpm::vec3& position, const hpm::vec2& size, unsigned int color, bool reflected = false);
		Renderable2D(const hpm::vec3& position, const hpm::vec2& size, TextureBase* texture, bool reflected = false);

		virtual void submit(Renderer2D* renderer) const;

		inline void	setColor	(unsigned int color) { if (m_Texture == nullptr) m_Color = color; };
		inline void	setPosition	(hpm::vec3 position) { m_Position = position; };

		inline virtual void reflect(bool reflect);

		inline const hpm::vec3&		getPosition()	const { return m_Position;  };
		inline const hpm::vec2&		getSize()		const { return m_Size;		};
		inline unsigned int			getColor()		const { return m_Color;		};
		inline virtual const float*	getUVs()		const { return m_UVs;		};
		
		inline unsigned int getTexID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }

	private:
		void setDefaultUVs();
		void setReflectDefaultUVs();
	};
	void Renderable2D::reflect(bool reflect) {
		if (m_Reflected && !reflect) {
			m_Reflected = false;
			setDefaultUVs();
		} else if (!m_Reflected && reflect) {
			m_Reflected = true;
			setReflectDefaultUVs();
		}
	};
}
#endif

