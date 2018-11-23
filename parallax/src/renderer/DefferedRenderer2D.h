#pragma once

#include <bitset>
#include "Renderer2D.h"
#include "DefferedRenderer2D_Properties.h"

// TODO:
// Make index buffers unsighed short (light buffer)
// handle viewport changing and proj matrix changing

namespace prx::API {
	class UniformBuffer;
}

namespace prx {

	// Forward declarations
	class FrameBuffer;
	class VertexBuffer;
	class IndexBuffer;
	class VertexBufferLayout;
	class Shader;
	class Texture;
	class Light2D;
	class AmbientLight2D;

	class DefferedRenderer2D final : public Renderer2D{
		PRX_DISALLOW_COPY_AND_MOVE(DefferedRenderer2D)
	
	private:
		// CONSTANTS
		static const size_t			VERTEX_SIZE;
		static const size_t			RENDERABLE_SIZE;
		static const size_t			INDEX_BUFFER_SIZE;
		static const size_t			VERTEX_BUFFER_SIZE;
		static const size_t			MAX_TEXTURE_SLOTS;
		static const float			EMPTY_TEXTURE_SLOT;

		static const size_t			SCREEN_QUAD_BUFFER_SIZE;
		static const unsigned int	SCREEN_QUAD_TEXTURE_SLOT;
		static const unsigned int	DEPTH_MAP_TEXTURE_SLOT;
															
		static const size_t			MAX_LIGHT_VOLUME_VERTICES;
		static const size_t			LIGHT_VOLUME_VERTEX_SIZE;
		static const size_t			LIGHT_VERTEX_BUFFER_SIZE;
		static const size_t			LIGHT_INDEX_BUFFER_SIZE;
		static const size_t			LIGHT_UNIFORM_BUFFER_SIZE;

// MEMBERS
// =========================================
// INSTANCE
// =========================================

		inline static DefferedRenderer2D* s_Instance = nullptr;

// =========================================
// BUFFERS
// =========================================
		struct {
			VertexBuffer*		GPVertexBuffer;
			VertexBuffer*		APVertexBuffer;
			VertexBuffer*		LPVertexBuffer;
			IndexBuffer*		GPIndexBuffer;
			IndexBuffer*		LPIndexBuffer;
			FrameBuffer*		GBuffer;
			API::UniformBuffer*	LPUniformBuffer;

			internal::DFR2D::DFR2DVertex* GPVertexBufferPointer;
			size_t	GPIndexCount;
			size_t	LPIndexCount;
		} m_Buffers;

// =========================================
// SHADERS
// =========================================
		struct {
			std::shared_ptr<Shader>	GPShader;
			std::shared_ptr<Shader>	LPShader;
			std::shared_ptr<Shader>	APShader;
#ifdef PARALLAX_DEBUG
			std::shared_ptr<Shader>	LPShaderDebug;
#endif
		} m_Shaders;

// =========================================
// RENDER TARGETS
// =========================================
		struct {
			std::shared_ptr<Texture>	colorBuffer;
			std::shared_ptr<Texture>	depthBuffer;
		} m_RenderTargets;

// =========================================
// LIGHTNING
// =========================================
		struct {
			std::vector<internal::DFR2D::DFR2DLightInfo>	lightsData;
			std::vector<hpm::vec2>							lightsGeometry; // layout of this array retrieves DFRLightVertex structure
			std::shared_ptr<AmbientLight2D>					ambientLightSource;
		} m_Lightning;

// =========================================
// FLAGS
// =========================================
		// 0 - bit: projection matrix update
		// 1 - bit: debug mode
		std::bitset<2> m_Flags;

// =========================================
	
		std::vector<unsigned int>	m_TextureSlots;
		hpm::mat4					m_ProjectionMatrix;

		DefferedRenderer2D(const hpm::mat4& projectionMatrix);
	
		public:
// =========================================
// STATIC INTERFACE
		static void initialize(const hpm::mat4& projection);
		static DefferedRenderer2D* getInstance();
		static void destroy();
// STATIC INTERFACE
// =========================================

		~DefferedRenderer2D();

		void debugLights(bool enable);

		void setProjectionMatrix(const hpm::mat4& projMatrix) override;

		void setAmbientLight(const std::shared_ptr<AmbientLight2D>& ambientLight);
		void submitLight(const std::shared_ptr<Light2D>& light);

		void begin() override;

		// TODO: Implement this
		void drawRect(const hpm::vec2& position, float depth, const hpm::vec2& size, unsigned int color = 0xffffffff) override {};
		void drawRect(const hpm::vec2& position, float depth, const hpm::vec2& size, const TextureBase* texture, bool reflect = false) override {};
		void drawRect(const hpm::mat3& worldMat, float depth, float width, float height, unsigned int color = 0xffffffff) override {};
		void drawRect(const hpm::mat3& worldMat, float depth, float width, float height, const TextureBase* texture, bool reflect = false) override {};
		// EndTODO

		void drawRenderable(const hpm::mat3& worldMat, float depth, const Renderable2D* renderable) override;

		//void drawString(const hpm::vec2& position, std::string_view text, float depth, const Font* font, unsigned int color) override;
		void drawString(std::string_view text, const hpm::mat3& worldMatrix, float depth, const Font* font, unsigned int color) override;

		void end() override;
		
		void flush() override;

	private:
		void init();
		void initVertexBuffers();
		void initIndexBuffers();
		void initGBuffer();
		void initUniformBuffers();
		void initShaders();

		float submitTexture(unsigned texID);

		void genLightVolumeInternal(const hpm::vec2& position, float radius);
		
		void fillLightBuffers();

		void geometryPass();
		void ambientPass();
		void lightningPass();

		hpm::vec3 convertColorToVec(color_t color);
	};
}