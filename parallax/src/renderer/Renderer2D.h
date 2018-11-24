#pragma once

#include <hypermath.h>
#include "../textures/Texture.h"
#include "../utils/Singleton.h"

namespace prx {
	
	// Forward declarations
	class Renderable2D;
	class FrameBuffer2D;
	class Font;
	class Light2DBase;
	class AmbientLight2D;

	struct VertexData {
		hpm::vec2		vertex;
		float			depth;
		hpm::vec2		UVs;
		float			texID;
		unsigned int	color;
	};

	enum class RenderTarget {
		SCREEN,
		BUFFER
	};

	class Renderer2D {
		PRX_DISALLOW_COPY_AND_MOVE(Renderer2D)
	public:
		inline static const float	 QUAD_DEFAULT_POSITION_X = 0.0f;
		inline static const float	 QUAD_DEFAULT_POSITION_Y = 0.0f;
		inline static const unsigned NULL_COLOR = 0xffffffff;

		inline static const hpm::mat4 DEFAULT_PROJECTION_MATRIX = hpm::mat4::ortho(0.0f, 800.0f, 600.0f, 0.0f, -10.0f, 10.0f);
	protected:
		Renderer2D() noexcept {};

	public:
		virtual ~Renderer2D() noexcept {};

		virtual void setProjectionMatrix(const hpm::mat4& projMatrix) = 0;

		virtual void setAmbientLight(const std::shared_ptr<AmbientLight2D>& ambientLight) = 0;
		virtual void submitLight(const std::shared_ptr<Light2DBase>& light) = 0;
		
		virtual void begin() {};

		virtual void drawRect(const hpm::vec2& position, float depth, const hpm::vec2& size, unsigned int color = 0xffffffff) = 0;
		virtual void drawRect(const hpm::vec2& position, float depth, const hpm::vec2& size, const TextureBase* texture, bool reflect = false) = 0;
		virtual void drawRect(const hpm::mat3& worldMat, float depth, float width, float height, unsigned int color = 0xffffffff) = 0;
		virtual void drawRect(const hpm::mat3& worldMat, float depth, float width, float height, const TextureBase* texture, bool reflect = false) = 0;

		virtual void drawRenderable(const hpm::mat3& worldMat, float depth, const Renderable2D* renderable) = 0;

		virtual void drawString(std::string_view text, const hpm::mat3& worldMatrix, float depth, const Font* font, unsigned int color) = 0;
		//virtual void drawString(const hpm::vec2& position, std::string_view text, float depth, const Font* font, unsigned int color) = 0;

		virtual void end() {};
		virtual void flush() = 0;
	};
}
