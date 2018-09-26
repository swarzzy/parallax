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
			float			m_UVs[8];
			TextureBase*	m_Texture;
			bool			m_TransformationCache;
			// There is no way to calculate angle of renderable now. It stores
			// only the information about bottom - left vertex or renderable
			mutable hpm::vec3 m_WorldCoords;
	protected:
			Renderable2D();
	public:
			virtual ~Renderable2D() {};

			Renderable2D(const hpm::vec3& position, const hpm::vec2& size, unsigned int color, bool storeTransforomCache = false);
			Renderable2D(const hpm::vec3& position, const hpm::vec2& size, TextureBase* texture, bool storeTransforomCache = false);

			virtual void submit(Renderer2D* renderer) const;

			inline void	setColor	(unsigned int color) { if (m_Texture == nullptr) m_Color = color; };
			// Unsafe! Loose prev model transformation data of the renderable untill submit
			inline void	setPosition(const hpm::vec3& position) { m_Position = position; m_WorldCoords = position; };


			// Changes mubable m_WorldCoords
			inline void setWorldCoords(const hpm::vec3& coords) const { m_WorldCoords = coords; }

			inline bool hasTransformCache() const { return m_TransformationCache; }

			inline const hpm::vec3&	getPosition()	const { return m_Position; };
			inline const hpm::vec3&	getWorldCoords()	const { return m_WorldCoords; };
			inline const hpm::vec2&	getSize()		const { return m_Size; };
			inline unsigned int		getColor()		const { return m_Color; };
			inline const float*		getUVs()		const { return m_UVs; };
			
			inline unsigned int getTexID() const { return m_Texture == nullptr ? 0 : m_Texture->getID(); }
	private:
		void setDefaultUVs();
	};
}
#endif

