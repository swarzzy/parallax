#include "DefferedRenderer2D.h"
#include "../utils/Utils.h"
#include "../scene/Director.h"
#include "API/VertexBuffer.h"
#include "API/IndexBuffer.h"
#include "API/FrameBuffer.h"
#include "API/UniformBuffer.h"
#include "../../shading/ShaderManager.h"
#include "../../shading/sources/PXDFR_GP_Shader.h"
#include "../../shading/sources/PXDFR_LP_Shader.h"
#include "renderable/Renderable2D.h"
#include "../Fonts/Font.h"
#include "../textures/Texture.h"
#include "light/Light2D.h"
#include "light/AmbientLight2D.h"

namespace prx {

	const size_t		DefferedRenderer2D::VERTEX_SIZE					= sizeof(internal::DFR2D::DFR2DVertex);
	const size_t		DefferedRenderer2D::RENDERABLE_SIZE				= VERTEX_SIZE * 4;
	const size_t		DefferedRenderer2D::INDEX_BUFFER_SIZE			= DFR2D::MAX_SPRITES * 6;
	const size_t		DefferedRenderer2D::VERTEX_BUFFER_SIZE			= RENDERABLE_SIZE * DFR2D::MAX_SPRITES;
	const size_t		DefferedRenderer2D::MAX_TEXTURE_SLOTS			= 32;
	const float			DefferedRenderer2D::EMPTY_TEXTURE_SLOT			= 0.0f;

	const size_t		DefferedRenderer2D::SCREEN_QUAD_BUFFER_SIZE		= (sizeof(hpm::vec2) + sizeof(hpm::vec2)) * 6;
	const unsigned int	DefferedRenderer2D::SCREEN_QUAD_TEXTURE_SLOT	= 0;
	const unsigned int	DefferedRenderer2D::DEPTH_MAP_TEXTURE_SLOT		= 1;

	const size_t		DefferedRenderer2D::MAX_LIGHT_VOLUME_VERTICES	= DFR2D::MAX_LIGHTS * (360 / DFR2D::LIGHT_VOLUME_CIRCLE_STEP);
	const size_t		DefferedRenderer2D::LIGHT_VOLUME_VERTEX_SIZE	= sizeof(internal::DFR2D::DFR2DLightVertex);
	const size_t		DefferedRenderer2D::LIGHT_VERTEX_BUFFER_SIZE	= LIGHT_VOLUME_VERTEX_SIZE * MAX_LIGHT_VOLUME_VERTICES;
	const size_t		DefferedRenderer2D::LIGHT_INDEX_BUFFER_SIZE		= MAX_LIGHT_VOLUME_VERTICES;
	const size_t		DefferedRenderer2D::LIGHT_UNIFORM_BUFFER_SIZE	= DFR2D::MAX_LIGHTS * sizeof(internal::DFR2D::DFR2DLightProperties);

	DefferedRenderer2D::DefferedRenderer2D(const hpm::mat4& projectionMatrix)
		: m_Buffers({ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 0, 0 })
#ifdef PARALLAX_DEBUG
		, m_Shaders({nullptr, nullptr, nullptr, nullptr})
#else
		, m_Shaders({nullptr, nullptr, nullptr})
#endif
		, m_RenderTargets({nullptr, nullptr})
		, m_ProjectionMatrix(projectionMatrix)
	{
		init();
		m_Lightning.lightsGeometry.reserve(DefferedRenderer2D::LIGHT_VERTEX_BUFFER_SIZE);
		m_Lightning.lightsData.reserve(LIGHT_UNIFORM_BUFFER_SIZE);
		m_TextureSlots.reserve(MAX_TEXTURE_SLOTS);
	}

	void DefferedRenderer2D::initialize(const hpm::mat4& projection) {
		if (s_Instance != nullptr)
			PRX_ERROR("DEFFERED RENDERER: Renderer already initialized");
		else
			s_Instance = new DefferedRenderer2D(projection);
	}

	DefferedRenderer2D* DefferedRenderer2D::getInstance() {
		PRX_ASSERT(s_Instance, "DEFFERERD RENDERER: Trying to use uninitialized renderer.");
		return s_Instance;
	}

	void DefferedRenderer2D::destroy() {
		delete s_Instance;
		s_Instance = nullptr;
	}

	DefferedRenderer2D::~DefferedRenderer2D() {
		delete m_Buffers.GPVertexBuffer;
		delete m_Buffers.APVertexBuffer;
		delete m_Buffers.LPVertexBuffer;
		delete m_Buffers.GPIndexBuffer;
		delete m_Buffers.LPIndexBuffer;
		delete m_Buffers.GBuffer;
		delete m_Buffers.LPUniformBuffer;

		// TODO: Solve this problem with shader deletion
		//ShaderManager::getInstance()->deleteUnused();
	}

	void DefferedRenderer2D::debugLights(bool enable) {
		m_Flags.set(1, enable);
	}

	void DefferedRenderer2D::setProjectionMatrix(const hpm::mat4& projMatrix) {
		m_ProjectionMatrix = projMatrix;
		m_Flags.set(0, true); // Setting up projection update flag as true
	}

	void DefferedRenderer2D::setAmbientLight(const std::shared_ptr<AmbientLight2D>& ambientLight) {
		m_Lightning.ambientLightProperties = ambientLight->getLightProperties();
	}

	void DefferedRenderer2D::submitLight(const std::shared_ptr<Light2DBase>& light) {
		m_Lightning.lightsData.push_back(light->getLightProperties());
		m_Lightning.lightsData.back().depth = (m_ProjectionMatrix * hpm::vec4(0.0, 0.0, m_Lightning.lightsData.back().depth, 1.0)).z;
		genLightVolumeInternal(light->getLightVolumeProperties());
	}

	void DefferedRenderer2D::begin() {
		m_Buffers.GPVertexBuffer->bind();
		m_Buffers.GPVertexBufferPointer = static_cast<internal::DFR2D::DFR2DVertex*>(m_Buffers.GPVertexBuffer->getPointer());
		m_TextureSlots.clear();
	}

	void DefferedRenderer2D::drawRenderable(const hpm::mat3& worldMat, float depth, const Renderable2D* renderable) {

		float width = renderable->getWidth();
		float height = renderable->getHeight();
		unsigned int color = renderable->getColor();

		unsigned int texID = renderable->getTexID();
		if (texID != 0) {
			const float* UVs = renderable->getUVs();
			float ts = submitTexture(texID);

			m_Buffers.GPVertexBufferPointer->coords = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->UVs.x = UVs[0];
			m_Buffers.GPVertexBufferPointer->UVs.y = UVs[1];
			m_Buffers.GPVertexBufferPointer->texID = ts;
			m_Buffers.GPVertexBufferPointer->color = NULL_COLOR;
			m_Buffers.GPVertexBufferPointer++;

			m_Buffers.GPVertexBufferPointer->coords = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y + height);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->UVs.x = UVs[2];
			m_Buffers.GPVertexBufferPointer->UVs.y = UVs[3];
			m_Buffers.GPVertexBufferPointer->texID = ts;
			m_Buffers.GPVertexBufferPointer->color = NULL_COLOR;
			m_Buffers.GPVertexBufferPointer++;

			m_Buffers.GPVertexBufferPointer->coords = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y + height); 
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->UVs.x = UVs[4];
			m_Buffers.GPVertexBufferPointer->UVs.y = UVs[5];
			m_Buffers.GPVertexBufferPointer->texID = ts;
			m_Buffers.GPVertexBufferPointer->color = NULL_COLOR;
			m_Buffers.GPVertexBufferPointer++;

			m_Buffers.GPVertexBufferPointer->coords = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->UVs.x = UVs[6];
			m_Buffers.GPVertexBufferPointer->UVs.y = UVs[7];
			m_Buffers.GPVertexBufferPointer->texID = ts;
			m_Buffers.GPVertexBufferPointer->color = NULL_COLOR;
			m_Buffers.GPVertexBufferPointer++;

		}
		else {

			m_Buffers.GPVertexBufferPointer->coords = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->texID = EMPTY_TEXTURE_SLOT;
			m_Buffers.GPVertexBufferPointer->color = color;
			m_Buffers.GPVertexBufferPointer++;

			m_Buffers.GPVertexBufferPointer->coords = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y + height);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->texID = EMPTY_TEXTURE_SLOT;
			m_Buffers.GPVertexBufferPointer->color = color;
			m_Buffers.GPVertexBufferPointer++;

			m_Buffers.GPVertexBufferPointer->coords = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y + height);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->texID = EMPTY_TEXTURE_SLOT;
			m_Buffers.GPVertexBufferPointer->color = color;
			m_Buffers.GPVertexBufferPointer++;

			m_Buffers.GPVertexBufferPointer->coords = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->texID = EMPTY_TEXTURE_SLOT;
			m_Buffers.GPVertexBufferPointer->color = color;
			m_Buffers.GPVertexBufferPointer++;
		}
		m_Buffers.GPIndexCount += 6;
	}

	void DefferedRenderer2D::drawString(std::string_view text, const hpm::mat3& worldMatrix, float depth, const Font* font, unsigned int color) {

		auto&		 characters = font->getCharacters();
		unsigned int atlasID = font->getFontAtlas().getID();
		float		 scale = font->getScale();

		float cursor = 0.0;

		float ts = submitTexture(atlasID);

		for (auto& character : text) {
			Character ch;
			// TODO: Catching exception here might be slow
			try {
				ch = characters.at(character);
			}
			catch (std::out_of_range& e) {
				PRX_ERROR("Renderer2D: Couldn`t find character in font atlas.\n-> EXCEPTION: ", e.what());
				return;
			}

			float xpos = (QUAD_DEFAULT_POSITION_X + cursor + ch.Bearing.x);// *scale;
			float ypos = (QUAD_DEFAULT_POSITION_Y - (ch.Size.y - ch.Bearing.y));// *scale;

			float w = ch.Size.x;// *scale;
			float h = ch.Size.y;// *scale;

			m_Buffers.GPVertexBufferPointer->coords = worldMatrix * hpm::vec2(xpos, ypos);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->UVs.x = ch.AtlasCoords.x / font->getFontAtlas().getWidth();
			m_Buffers.GPVertexBufferPointer->UVs.y = ch.AtlasCoords.y / font->getFontAtlas().getHeight();
			m_Buffers.GPVertexBufferPointer->texID = ts;
			m_Buffers.GPVertexBufferPointer->color = color;
			m_Buffers.GPVertexBufferPointer++;

			m_Buffers.GPVertexBufferPointer->coords = worldMatrix * hpm::vec2(xpos, ypos + h);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->UVs.x = ch.AtlasCoords.x / font->getFontAtlas().getWidth();
			m_Buffers.GPVertexBufferPointer->UVs.y = (ch.AtlasCoords.y + ch.AtlasCoords.w) / font->getFontAtlas().getHeight();
			m_Buffers.GPVertexBufferPointer->texID = ts;
			m_Buffers.GPVertexBufferPointer->color = color;
			m_Buffers.GPVertexBufferPointer++;

			m_Buffers.GPVertexBufferPointer->coords = worldMatrix * hpm::vec2(xpos + w, ypos + h);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->UVs.x = (ch.AtlasCoords.x + ch.AtlasCoords.z) / font->getFontAtlas().getWidth();
			m_Buffers.GPVertexBufferPointer->UVs.y = (ch.AtlasCoords.y + ch.AtlasCoords.w) / font->getFontAtlas().getHeight();
			m_Buffers.GPVertexBufferPointer->texID = ts;
			m_Buffers.GPVertexBufferPointer->color = color;
			m_Buffers.GPVertexBufferPointer++;

			m_Buffers.GPVertexBufferPointer->coords = worldMatrix * hpm::vec2(xpos + w, ypos);
			m_Buffers.GPVertexBufferPointer->depth = depth;
			m_Buffers.GPVertexBufferPointer->UVs.x = (ch.AtlasCoords.x + ch.AtlasCoords.z) / font->getFontAtlas().getWidth();
			m_Buffers.GPVertexBufferPointer->UVs.y = ch.AtlasCoords.y / font->getFontAtlas().getHeight();
			m_Buffers.GPVertexBufferPointer->texID = ts;
			m_Buffers.GPVertexBufferPointer->color = color;
			m_Buffers.GPVertexBufferPointer++;

			m_Buffers.GPIndexCount += 6;
			cursor += (ch.Advance >> 6);
		}
	}

	//void DefferedRenderer2D::drawString(const hpm::vec2& position, std::string_view text, float depth, const Font* font, unsigned color) {
	//	auto&		 characters = font->getCharacters();
	//	unsigned int atlasID = font->getFontAtlas().getID();
	//	float		 scale = font->getScale();

	//	float cursor = 0.0;

	//	float ts = submitTexture(atlasID);

	//	// TODO: Catch exceptions here might be slow
	//	for (auto& character : text) {
	//		Character ch;
	//		try {
	//			ch = characters.at(character);
	//		}
	//		catch (std::out_of_range& e) {
	//			PRX_ERROR("Renderer2D: Couldn`t find character in font atlas.\n-> EXCEPTION: ", e.what());
	//			return;
	//		}

	//		float xpos = (position.x + cursor + ch.Bearing.x) * scale;
	//		float ypos = (position.y - (ch.Size.y - ch.Bearing.y)) * scale;

	//		float w = ch.Size.x * scale;
	//		float h = ch.Size.y * scale;

	//		m_Buffers.GPVertexBufferPointer->coords = hpm::vec2(xpos, ypos);
	//		m_Buffers.GPVertexBufferPointer->depth = depth;
	//		m_Buffers.GPVertexBufferPointer->UVs.x = ch.AtlasCoords.x / font->getFontAtlas().getWidth();
	//		m_Buffers.GPVertexBufferPointer->UVs.y = ch.AtlasCoords.y / font->getFontAtlas().getHeight();
	//		m_Buffers.GPVertexBufferPointer->texID = ts;
	//		m_Buffers.GPVertexBufferPointer->color = color;
	//		m_Buffers.GPVertexBufferPointer++;

	//		m_Buffers.GPVertexBufferPointer->coords = hpm::vec2(xpos, ypos + h);
	//		m_Buffers.GPVertexBufferPointer->depth = depth;
	//		m_Buffers.GPVertexBufferPointer->UVs.x = ch.AtlasCoords.x / font->getFontAtlas().getWidth();
	//		m_Buffers.GPVertexBufferPointer->UVs.y = (ch.AtlasCoords.y + ch.AtlasCoords.w) / font->getFontAtlas().getHeight();
	//		m_Buffers.GPVertexBufferPointer->texID = ts;
	//		m_Buffers.GPVertexBufferPointer->color = color;
	//		m_Buffers.GPVertexBufferPointer++;

	//		m_Buffers.GPVertexBufferPointer->coords = hpm::vec2(xpos + w, ypos + h);
	//		m_Buffers.GPVertexBufferPointer->depth = depth;
	//		m_Buffers.GPVertexBufferPointer->UVs.x = (ch.AtlasCoords.x + ch.AtlasCoords.z) / font->getFontAtlas().getWidth();
	//		m_Buffers.GPVertexBufferPointer->UVs.y = (ch.AtlasCoords.y + ch.AtlasCoords.w) / font->getFontAtlas().getHeight();
	//		m_Buffers.GPVertexBufferPointer->texID = ts;
	//		m_Buffers.GPVertexBufferPointer->color = color;
	//		m_Buffers.GPVertexBufferPointer++;

	//		m_Buffers.GPVertexBufferPointer->coords = hpm::vec2(xpos + w, ypos);
	//		m_Buffers.GPVertexBufferPointer->depth = depth;
	//		m_Buffers.GPVertexBufferPointer->UVs.x = (ch.AtlasCoords.x + ch.AtlasCoords.z) / font->getFontAtlas().getWidth();
	//		m_Buffers.GPVertexBufferPointer->UVs.y = ch.AtlasCoords.y / font->getFontAtlas().getHeight();
	//		m_Buffers.GPVertexBufferPointer->texID = ts;
	//		m_Buffers.GPVertexBufferPointer->color = color;
	//		m_Buffers.GPVertexBufferPointer++;

	//		m_Buffers.GPIndexCount += 6;
	//		cursor += (ch.Advance >> 6);
	//	}
	//}

	void DefferedRenderer2D::end() {
		m_Buffers.GPVertexBuffer->releasePointer();
		// Not unbind vertex buffer might be faster 
		m_Buffers.GPVertexBuffer->unbind();
	}

	void DefferedRenderer2D::flush() {
		geometryPass();
		ambientPass();
		fillLightBuffers();
		lightningPass();
		m_Flags.reset(0); // Setting projection update flag to false
	}

	void DefferedRenderer2D::init() {
		// Default ambient light source
		m_Lightning.ambientLightProperties = { color_to_vec3(0xffffffff), 0.0f, hpm::vec2(0.0f, 0.0f), 0.0f, 0.0f };
		
		initVertexBuffers();
		initIndexBuffers();
		initGBuffer();
		initShaders();
		initUniformBuffers();
	}

	void DefferedRenderer2D::initVertexBuffers() {
		// -----------------------------------------------------------
		// GEOMETRY PASS VERTEX BUFFER
		m_Buffers.GPVertexBuffer = new VertexBuffer(BufferType::DYNAMIC_DRAW);
		m_Buffers.GPVertexBuffer->bind();

		m_Buffers.GPVertexBuffer->resize(VERTEX_BUFFER_SIZE);

		auto GPVertexBufferLayout = VertexBufferLayout();
		GPVertexBufferLayout.push<float>(2); // Coords
		GPVertexBufferLayout.push<float>(1); // Depth
		GPVertexBufferLayout.push<float>(2); // UV
		GPVertexBufferLayout.push<float>(1); // TexID
		GPVertexBufferLayout.push<byte>(4);  // Color

		m_Buffers.GPVertexBuffer->setLayout(GPVertexBufferLayout);

		m_Buffers.GPVertexBuffer->unbind();
		// -----------------------------------------------------------
		// AMBIENT PASS VERTEX BUFFER
							// Coords		// UV
		float APVBData[] = {-1.0f, -1.0f,	0.0f, 0.0f,
							-1.0f,  1.0f,	0.0f, 1.0f,
							 1.0f,  1.0f,	1.0f, 1.0f,
							 1.0f,  1.0f,	1.0f, 1.0f,
							 1.0f, -1.0f,	1.0f, 0.0f,
							-1.0f, -1.0f,	0.0f, 0.0f
		};

		m_Buffers.APVertexBuffer = new VertexBuffer(BufferType::STATIC_DRAW);
		m_Buffers.APVertexBuffer->bind();
		m_Buffers.APVertexBuffer->resize(SCREEN_QUAD_BUFFER_SIZE);
		m_Buffers.APVertexBuffer->setData(SCREEN_QUAD_BUFFER_SIZE, static_cast<void*>(APVBData));

		auto APVertexBufferLayout = VertexBufferLayout();
		APVertexBufferLayout.push<float>(2); // Coords
		APVertexBufferLayout.push<float>(2); // UV

		m_Buffers.APVertexBuffer->setLayout(APVertexBufferLayout);

		m_Buffers.APVertexBuffer->unbind();

		// -----------------------------------------------------------
		// LIGHT PASS VERTEX BUFFER
		m_Buffers.LPVertexBuffer = new VertexBuffer(BufferType::DYNAMIC_DRAW);
		m_Buffers.LPVertexBuffer->bind();
		m_Buffers.LPVertexBuffer->resize(LIGHT_VERTEX_BUFFER_SIZE);

		auto LPVertexBufferLayout = VertexBufferLayout();
		LPVertexBufferLayout.push<float>(2); // Coords

		m_Buffers.LPVertexBuffer->setLayout(LPVertexBufferLayout);

		m_Buffers.LPVertexBuffer->unbind();
	}

	void DefferedRenderer2D::initIndexBuffers() {
		// -----------------------------------------------------------
		// GEOMETRY PASS INDEX BUFFER
		auto* indices = new unsigned int[INDEX_BUFFER_SIZE];

		unsigned int offset = 0;
		for (unsigned int i = 0; i < INDEX_BUFFER_SIZE; i += 6) {
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_Buffers.GPIndexBuffer = new IndexBuffer(indices, INDEX_BUFFER_SIZE);

		delete[] indices;

		// -----------------------------------------------------------
		// LIGHT PASS INDEX BUFFER
		unsigned int lightIndices[LIGHT_INDEX_BUFFER_SIZE];

		unsigned int first = 0;
		offset = 0;
		unsigned int primitive = 0;
		unsigned int verticesNum = static_cast<unsigned int>(360.0f / DFR2D::LIGHT_VOLUME_CIRCLE_STEP);
		for (unsigned int i = 0; i < MAX_LIGHT_VOLUME_VERTICES; i += 3) {
			lightIndices[i] = first;
			lightIndices[i + 1] = offset + 2;
			lightIndices[i + 2] = offset + 1;
			offset++;
			primitive++;
			if (primitive % verticesNum == 0 && primitive != 0) {
				lightIndices[i + 1] = first + 1;
				first += verticesNum + 1;
				offset++;
			}
		}

		m_Buffers.LPIndexBuffer = new IndexBuffer(lightIndices, LIGHT_INDEX_BUFFER_SIZE);
	}

	void DefferedRenderer2D::initGBuffer() {
		// -----------------------------------------------------------
		// G BUFFER INITIALIZATION
		// TODO: Update framebuffer when viewport changed
		// TODO: get viewport from director somehow
		hpm::vec2 viewport = hpm::vec2(Window::getInstance()->getWidth(), Window::getInstance()->getHeight());

		m_RenderTargets.colorBuffer = std::make_shared<Texture>(viewport.x, viewport.y, TextureFormat::RGB);
		// TODO: 2-channel texture for position
		m_RenderTargets.depthBuffer = std::make_shared<Texture>(viewport.x, viewport.y, TextureFormat::DEPTH);

		m_Buffers.GBuffer = new FrameBuffer(viewport.x, viewport.y, DepthStencilType::TEXTURE, DepthStencilFormat::DEPTH_ONLY);
		m_Buffers.GBuffer->init();

		m_Buffers.GBuffer->attachColorTexture(m_RenderTargets.colorBuffer, 0);	// Color target at location 0
		m_Buffers.GBuffer->attachDepthStencilTexture(m_RenderTargets.depthBuffer);

		PRX_ASSERT(m_Buffers.GBuffer->validate(), "DEFFERED RENDERER: Failed to create framebuffer.");

		m_Buffers.GBuffer->unbind();
	}

	void DefferedRenderer2D::initUniformBuffers() {
		// -----------------------------------------------------------
		// LIGHT PASS UNIFORM BUFFER
		m_Buffers.LPUniformBuffer = new API::UniformBuffer(m_Shaders.LPShader, API::PXDFR_LP_Shader::lightsUBBindingPoint(), API::PXDFR_LP_Shader::uniformBlockLights(), BufferType::DYNAMIC_DRAW);
		m_Buffers.LPUniformBuffer->resize(LIGHT_UNIFORM_BUFFER_SIZE);
	}

	void DefferedRenderer2D::initShaders() {
		// -----------------------------------------------------------
		// GEOMETRY PASS SHADER
		unsigned gpID = ShaderManager::getInstance()->loadShader(ShaderType::DEFFERED_RENDERER_GEOMETRY_PASS_DEFAULT);
		m_Shaders.GPShader = ShaderManager::getInstance()->getShader(gpID);

		int samplerIndices[32];
		for (int i = 0; i < 32; i++)
			samplerIndices[i] = i;

		m_Shaders.GPShader->bind();
		m_Shaders.GPShader->setUniform(API::PXDFR_GP_Shader::uniformSysTexturesBegin(), samplerIndices, 32);
		m_Shaders.GPShader->setUniform(API::PXDFR_GP_Shader::uniformSysProjMat(), m_ProjectionMatrix);
		m_Shaders.GPShader->unbind();

		// -----------------------------------------------------------
		// LIGHT PASS SHADER
		unsigned lpID = ShaderManager::getInstance()->loadShader(ShaderType::DEFFERED_RENDERER_LIGHTNING_PASS_DEFAULT);
		m_Shaders.LPShader = ShaderManager::getInstance()->getShader(lpID);

		m_Shaders.LPShader->bind();

		m_Shaders.LPShader->setUniform(API::PXDFR_LP_Shader::uniformSysTexture(), SCREEN_QUAD_TEXTURE_SLOT);
		m_Shaders.LPShader->setUniform("sys_DepthTexture", DEPTH_MAP_TEXTURE_SLOT);
		// TODO: Get viewport from opengl
		m_Shaders.LPShader->setUniform("sys_ViewportSize",hpm::vec2(Window::getInstance()->getWidth(), Window::getInstance()->getHeight()));

		m_Shaders.LPShader->unbind();

		// -----------------------------------------------------------
		// LIGHT PASS DEBUG SHADER
#ifdef PARALLAX_DEBUG
		unsigned lpdID = ShaderManager::getInstance()->loadShader(ShaderType::DEFFERED_RENDERER_LIGHTNING_PASS_DEFAULT_DBG);
		m_Shaders.LPShaderDebug = ShaderManager::getInstance()->getShader(lpdID);
		m_Shaders.LPShaderDebug->bind();
		m_Shaders.LPShaderDebug->setUniform(API::PXDFR_LP_Shader::uniformSysProjMat(), m_ProjectionMatrix);
		m_Shaders.LPShaderDebug->unbind();
#endif
		// -----------------------------------------------------------
		// AMBIENT PASS SHADER
		unsigned apID = ShaderManager::getInstance()->loadShader(ShaderType::DEFFERED_RENDERER_AMBIENT_PASS_DEFAULT);
		m_Shaders.APShader = ShaderManager::getInstance()->getShader(apID);

		m_Shaders.APShader->bind();
		m_Shaders.APShader->setUniform("sys_Texture", 0);
		// TODO: Uniform defenitions
		m_Shaders.APShader->unbind();
	}

	float DefferedRenderer2D::submitTexture(unsigned texID) {
		float ts = 0.0f;
		bool found = false;

		for (int i = 0; i < m_TextureSlots.size(); i++) {
			if (m_TextureSlots[i] == texID) {
				found = true;
				ts = static_cast<float>(i + 1);
				break;
			}
		}
		if (!found) {
			if (m_TextureSlots.size() >= MAX_TEXTURE_SLOTS) {
				end();
				flush();
				begin();
				m_TextureSlots.clear();
			}

			m_TextureSlots.push_back(texID);
			ts = static_cast<float>(m_TextureSlots.size());
		}
		return ts;
	}

	void DefferedRenderer2D::genLightVolumeInternal(const internal::DFR2D::DFR2DLightVolumeProperties& properties) {
		m_Lightning.lightsGeometry.push_back(properties.position);
		int c = 0;
		for (float i = 0.0f; i < 360.0f; i += DFR2D::LIGHT_VOLUME_CIRCLE_STEP) {
			c++;
			m_Lightning.lightsGeometry.emplace_back(properties.position.x + properties.radius * std::cos(hpm::radians(i)), properties.position.y + properties.radius * std::sin(hpm::radians(i)));
		}

		m_Buffers.LPIndexCount += (360.0f / DFR2D::LIGHT_VOLUME_CIRCLE_STEP) * 3 + 1;
	}

	void DefferedRenderer2D::fillLightBuffers() {
		m_Buffers.LPUniformBuffer->setData(m_Lightning.lightsData.size() * sizeof(internal::DFR2D::DFR2DLightProperties), m_Lightning.lightsData.data());
		m_Buffers.LPVertexBuffer->setData(m_Lightning.lightsGeometry.size() * sizeof(internal::DFR2D::DFR2DLightVertex), m_Lightning.lightsGeometry.data());
	}

	void DefferedRenderer2D::geometryPass() {
		// BIND TEXTURES
		// TODO: Look for glBindTextures
		for (unsigned i = 0; i < m_TextureSlots.size(); i++) {
			GLCall(glActiveTexture(GL_TEXTURE0 + i));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]));
		}

		// BIND SHADER
		m_Shaders.GPShader->bind();
		if (m_Flags[1])
			m_Shaders.GPShader->setUniform(API::PXDFR_GP_Shader::uniformSysProjMat(), m_ProjectionMatrix);

		// BIND BUFFERS
		m_Buffers.GPVertexBuffer->bind();
		m_Buffers.GPIndexBuffer->bind();

		// BIND G-BUFFER
		m_Buffers.GBuffer->bind();
		// TODO: Move it from here
		m_Buffers.GBuffer->clear();

		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_ALWAYS));
		GLCall(glDrawElements(GL_TRIANGLES, m_Buffers.GPIndexCount, GL_UNSIGNED_INT, NULL));
		GLCall(glDisable(GL_DEPTH_TEST));

		m_Buffers.GBuffer->unbind();
		m_Buffers.GPIndexBuffer->unbind();
		m_Buffers.GPVertexBuffer->unbind();
		m_Shaders.GPShader->unbind();

		m_Buffers.GPIndexCount = 0;
	}

	void DefferedRenderer2D::ambientPass() {
		// TODO: This may conflict with texture submission in geometry pass
		GLCall(glActiveTexture(GL_TEXTURE0));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderTargets.colorBuffer->getID()));

		m_Shaders.APShader->bind();
		m_Shaders.APShader->setUniform("u_AmbientColor", m_Lightning.ambientLightProperties.color);
		m_Shaders.APShader->setUniform("u_AmbientIntensity", m_Lightning.ambientLightProperties.intensity);
		m_Buffers.APVertexBuffer->bind();

		//glDepthMask(GL_FALSE);
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
		

		m_Buffers.APVertexBuffer->unbind();
		m_Shaders.APShader->unbind();
	}

	void DefferedRenderer2D::lightningPass() {
		GLCall(glActiveTexture(GL_TEXTURE1));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderTargets.depthBuffer->getID()));

		m_Shaders.LPShader->bind();
		if (m_Flags[0])
			m_Shaders.LPShader->setUniform(API::PXDFR_LP_Shader::uniformSysProjMat(), m_ProjectionMatrix);
	
		// Draw lightning
		m_Buffers.LPVertexBuffer->bind();
		m_Buffers.LPIndexBuffer->bind();

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_ONE, GL_ONE));
		GLCall(glBlendEquation(GL_FUNC_ADD));

		GLCall(glDrawElements(GL_TRIANGLES, m_Buffers.LPIndexCount, GL_UNSIGNED_INT, nullptr));
		GLCall(glDisable(GL_BLEND));
		//glDepthMask(GL_TRUE);
		// Draw debug geometry
#ifdef PARALLAX_DEBUG
		if (m_Flags[1]) { // Debug mode flag
			m_Shaders.LPShaderDebug->bind();
			if (m_Flags[0])
				m_Shaders.LPShaderDebug->setUniform(API::PXDFR_LP_Shader::uniformSysProjMat(), m_ProjectionMatrix);
			GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
			GLCall(glDrawElements(GL_TRIANGLES, m_Buffers.LPIndexCount, GL_UNSIGNED_INT, nullptr));
			GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
			m_Shaders.LPShaderDebug->unbind();
		}
#else		
		m_Buffers.LPIndexBuffer->unbind();
#endif
		
		m_Buffers.LPVertexBuffer->unbind();
		m_Shaders.LPShader->unbind();

		m_Lightning.lightsGeometry.clear();
		m_Lightning.lightsData.clear();

		m_Buffers.LPIndexCount = 0;
	}
}