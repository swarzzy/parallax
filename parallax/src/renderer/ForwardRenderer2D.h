#pragma once

#include <vector>

#include "Renderer2D.h"

namespace prx {
	
	class IndexBuffer;
	class FrameBuffer2D;
	class Shader;

	class ForwardRenderer2D final : public Renderer2D {
		PRX_DISALLOW_COPY_AND_MOVE(ForwardRenderer2D)
	public:
		static const unsigned int	MAX_RENDERABLES		= 60000;
		static const unsigned int	VERTEX_SIZE			= sizeof(VertexData);
		static const unsigned int	RENDERABLE_SIZE		= VERTEX_SIZE * 4;
		static const unsigned int	INDEX_BUFFER_SIZE	= MAX_RENDERABLES * 6;
		static const unsigned int	BUFFER_SIZE			= RENDERABLE_SIZE * MAX_RENDERABLES;
		static const unsigned int	MAX_TEXTURE_SLOTS	= 32;

		static const unsigned int	SHADER_VERTEX_INDEX	= 0;
		static const unsigned int	SHADER_DEPTH_INDEX  = 1;
		static const unsigned int	SHADER_UV_INDEX		= 2;
		static const unsigned int	SHADER_TEXID_INDEX	= 3;
		static const unsigned int	SHADER_COLOR_INDEX	= 4;

	private:
// =========================================
// INSTANCE
		inline static ForwardRenderer2D* s_Instance = nullptr;
// =========================================

		inline static const float	 EMPTY_TEXTURE_SLOT	= 0.0f;

		unsigned int				m_VAO;
		unsigned int				m_VBO;
		IndexBuffer*				m_IBO;
		std::vector<unsigned int>	m_TextureSlots;
		int							m_IndexCount;
		VertexData*					m_Buffer;
		unsigned					m_ShaderID;
		std::shared_ptr<Shader>		m_Shader;
		hpm::mat4					m_ProjectionMatrix;
		bool						m_ProjMatrixNeedsUpdate;

		ForwardRenderer2D(const hpm::mat4& projectionMatrix);
	public:
// =========================================
// STATIC INTERFACE
		static void initialize(const hpm::mat4& projection);
		static ForwardRenderer2D* getInstance();
		static void destroy();
// STATIC INTERFACE
// =========================================

		~ForwardRenderer2D();

		void setProjectionMatrix(const hpm::mat4& projMatrix) override;

		// Forward renderer doesn`t support lightning
		void setAmbientLight(const std::shared_ptr<AmbientLight2D>& ambientLight) override {};
		void submitLight(const std::shared_ptr<Light2D>& light) override {};

		void begin() override;

		void drawRect(const hpm::vec2& position, float depth, const hpm::vec2& size, unsigned int color = 0xffffffff) override;
		void drawRect(const hpm::vec2& position, float depth, const hpm::vec2& size, const TextureBase* texture, bool reflect = false) override;
		void drawRect(const hpm::mat3& worldMat, float depth, float width, float height, unsigned int color = 0xffffffff) override;
		void drawRect(const hpm::mat3& worldMat, float depth, float width, float height, const TextureBase* texture, bool reflect = false) override;

		void drawRenderable(const hpm::mat3& worldMat, float depth, const Renderable2D* renderable) override;

		void drawString(std::string_view text, const hpm::mat3& worldMatrix, float depth, const Font* font, unsigned int color) override;
		//void drawString(const hpm::vec2& position, std::string_view text,  float depth, const Font* font, unsigned int color) override;
	
		void end() override;
		void flush() override;

	private:
		void init();
		float submitTexture(unsigned texID);
	};
}