#include "ForwardRenderer2D.h"
#include "../utils/error_handling/GLErrorHandler.h"
#include "../Fonts/Font.h"
#include "../renderer/buffer/IndexBuffer.h"
#include "FrameBuffer2D.h"
#include "renderable/Renderable2D.h"
#include "../shading/ShaderManager.h"

namespace prx {
	prx::ForwardRenderer2D::ForwardRenderer2D(const hpm::mat4& projectionMatrix, RenderTarget rendertarget)
		: Renderer2D(rendertarget),
		  m_VAO(0),
		  m_VBO(0),
		  m_IBO(nullptr),
		  m_IndexCount(0),
		  m_Buffer(nullptr),
		  m_ShaderID(0),
		  m_Shader(nullptr),
		  m_ProjectionMatrix(projectionMatrix),
		  m_ProjMatrixNeedsUpdate(false),
		  m_Initialized(false)
	{}

	ForwardRenderer2D::~ForwardRenderer2D() {
		if (m_Initialized) {
			GLCall(glDeleteBuffers(1, &m_VAO));
			GLCall(glDeleteBuffers(1, &m_VBO));
			delete m_IBO;

			ShaderManager::deleteShader(m_ShaderID);

			delete m_Mask;

			m_Initialized = false;
		}
	}

	void ForwardRenderer2D::setProjectionMatrix(const hpm::mat4& projMatrix) {
		m_ProjectionMatrix = projMatrix;
		m_ProjMatrixNeedsUpdate = true;
	}

	void ForwardRenderer2D::init() {
		if (!m_Initialized) {
			m_Initialized = true;
			GLCall(glGenVertexArrays(1, &m_VAO));
			GLCall(glGenBuffers(1, &m_VBO));

			GLCall(glBindVertexArray(m_VAO));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
			GLCall(glBufferData(GL_ARRAY_BUFFER, BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW));

			GLCall(glEnableVertexAttribArray(SHADER_VERTEX_INDEX));
			GLCall(glEnableVertexAttribArray(SHADER_DEPTH_INDEX));
			GLCall(glEnableVertexAttribArray(SHADER_UV_INDEX));
			GLCall(glEnableVertexAttribArray(SHADER_TEXID_INDEX));
			GLCall(glEnableVertexAttribArray(SHADER_COLOR_INDEX));

			GLCall(glVertexAttribPointer(SHADER_VERTEX_INDEX, 2, GL_FLOAT, GL_FALSE,
				VERTEX_SIZE, static_cast<const void*>(NULL)));

			GLCall(glVertexAttribPointer(SHADER_DEPTH_INDEX, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
				reinterpret_cast<const void*>(offsetof(VertexData, VertexData::depth))));

			GLCall(glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
				reinterpret_cast<const void*>(offsetof(VertexData, VertexData::UVs))));

			GLCall(glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
				reinterpret_cast<const void*>(offsetof(VertexData, VertexData::texID))));

			GLCall(glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, VERTEX_SIZE,
				reinterpret_cast<const void*>(offsetof(VertexData, VertexData::color))));

			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));


			unsigned int* indices = new unsigned int[INDEX_BUFFER_SIZE];

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

			m_IBO = new IndexBuffer(indices, INDEX_BUFFER_SIZE);
			m_IBO->Bind();

			delete[] indices;

			GLCall(glBindVertexArray(0));

			m_ShaderID = ShaderManager::loadShader(ShaderType::FORWARD_RENDERER_DEFAULT);
			m_Shader = ShaderManager::getShader(m_ShaderID);

			int samplerIndices[32];
			for (int i = 0; i < 32; i++)
				samplerIndices[i] = i;

			m_Shader->bind();
			m_Shader->setUniform("u_textures[0]", samplerIndices, 32);
			m_Shader->setUniform("u_ProjectionMatrix", m_ProjectionMatrix);
			m_Shader->unbind();

			defaultMask();
		}
	}

	void ForwardRenderer2D::destroy() {
		if (m_Initialized) {
			GLCall(glDeleteBuffers(1, &m_VAO));
			GLCall(glDeleteBuffers(1, &m_VBO));
			delete m_IBO;

			ShaderManager::deleteShader(m_ShaderID);

			delete m_Mask;

			m_Initialized = false;
		}
	}

	void ForwardRenderer2D::begin() {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
		GLCall(m_Buffer = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)));
		m_TextureSlots.clear();
	}

	void ForwardRenderer2D::drawRect(const hpm::vec2& position, float depth, const hpm::vec2& size, unsigned color) {
		
		m_Buffer->vertex = position;
		m_Buffer->depth  = depth;
		m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
		m_Buffer->color  = color;
		m_Buffer++;

		m_Buffer->vertex = hpm::vec2(position.x, position.y + size.y);
		m_Buffer->depth = depth;
		m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
		m_Buffer->color  = color;
		m_Buffer++;

		m_Buffer->vertex = position + size;
		m_Buffer->depth  = depth;
		m_Buffer->texID	 = EMPTY_TEXTURE_SLOT;
		m_Buffer->color  = color;
		m_Buffer++;

		m_Buffer->vertex = hpm::vec2(position.x + size.x, position.y);
		m_Buffer->depth  = depth;
		m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
		m_Buffer->color  = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void ForwardRenderer2D::drawRect(const hpm::vec2& position, float depth, const hpm::vec2& size, const TextureBase* texture, bool reflect) {
		unsigned int texID = texture->getID();
		const float* UVs;

		if (reflect)
			UVs = TextureBase::reflectDefaultUV();
		else
			UVs = TextureBase::defaultUV();

		float ts = submitTexture(texID);

		m_Buffer->vertex = position;
		m_Buffer->depth  = depth;
		m_Buffer->UVs.x  = UVs[0];
		m_Buffer->UVs.y  = UVs[1];
		m_Buffer->texID  = ts;
		m_Buffer->color  = NULL_COLOR;
		m_Buffer++;

		m_Buffer->vertex = hpm::vec2(position.x, position.y + size.y);
		m_Buffer->depth  = depth;
		m_Buffer->UVs.x  = UVs[2];
		m_Buffer->UVs.y  = UVs[3];
		m_Buffer->texID  = ts;
		m_Buffer->color  = NULL_COLOR;
		m_Buffer++;

		m_Buffer->vertex = position + size;
		m_Buffer->depth  = depth;
		m_Buffer->UVs.x  = UVs[4];
		m_Buffer->UVs.y  = UVs[5];
		m_Buffer->texID  = ts;
		m_Buffer->color  = NULL_COLOR;
		m_Buffer++;

		m_Buffer->vertex = hpm::vec2(position.x + size.x, position.y);
		m_Buffer->depth  = depth;
		m_Buffer->UVs.x  = UVs[6];
		m_Buffer->UVs.y  = UVs[7];
		m_Buffer->texID  = ts;
		m_Buffer->color  = NULL_COLOR;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void ForwardRenderer2D::drawRect(const hpm::mat3& worldMat, float depth, float width, float height, unsigned color) {
		
		m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y);
		m_Buffer->depth  = depth;
		m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
		m_Buffer->color  = color;
		m_Buffer++;

		m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y + height);
		m_Buffer->depth  = depth;
		m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
		m_Buffer->color  = color;
		m_Buffer++;

		m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y + height);
		m_Buffer->depth  = depth;
		m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
		m_Buffer->color  = color;
		m_Buffer++;

		m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y);
		m_Buffer->depth  = depth;
		m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
		m_Buffer->color  = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void ForwardRenderer2D::drawRect(const hpm::mat3& worldMat, float depth, float width, float height, const TextureBase* texture, bool reflect) {

		unsigned int texID = texture->getID();
		const float* UVs;
		
		if (reflect)
			UVs = TextureBase::reflectDefaultUV();
		else
			UVs = TextureBase::defaultUV();

		float ts = submitTexture(texID);

		m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y);
		m_Buffer->depth  = depth;
		m_Buffer->UVs.x  = UVs[0];
		m_Buffer->UVs.y  = UVs[1];
		m_Buffer->texID  = ts;
		m_Buffer->color  = NULL_COLOR;
		m_Buffer++;

		m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y + height);
		m_Buffer->depth  = depth;
		m_Buffer->UVs.x  = UVs[2];
		m_Buffer->UVs.y  = UVs[3];
		m_Buffer->texID  = ts;
		m_Buffer->color  = NULL_COLOR;
		m_Buffer++;

		m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y + height);
		m_Buffer->depth = depth;
		m_Buffer->UVs.x  = UVs[4];
		m_Buffer->UVs.y  = UVs[5];
		m_Buffer->texID  = ts;
		m_Buffer->color  = NULL_COLOR;
		m_Buffer++;

		m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y);
		m_Buffer->depth  = depth;
		m_Buffer->UVs.x  = UVs[6];
		m_Buffer->UVs.y  = UVs[7];
		m_Buffer->texID  = ts;
		m_Buffer->color  = NULL_COLOR;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void ForwardRenderer2D::drawRenderable(const hpm::mat3& worldMat, float depth, const Renderable2D* renderable) {
		
		float width = renderable->getWidth();
		float height = renderable->getHeight();
		unsigned int color = renderable->getColor();
		
		unsigned int texID = renderable->getTexID();
		if (texID != 0) {
			const float* UVs = renderable->getUVs();
			float ts = submitTexture(texID);

			m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y);
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = UVs[0];
			m_Buffer->UVs.y  = UVs[1];
			m_Buffer->texID  = ts;
			m_Buffer->color  = NULL_COLOR;
			m_Buffer++;

			m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y + height);
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = UVs[2];
			m_Buffer->UVs.y  = UVs[3];
			m_Buffer->texID  = ts;
			m_Buffer->color  = NULL_COLOR;
			m_Buffer++;

			m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y + height);\
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = UVs[4];
			m_Buffer->UVs.y  = UVs[5];
			m_Buffer->texID  = ts;
			m_Buffer->color  = NULL_COLOR;
			m_Buffer++;

			m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y);
			m_Buffer->UVs.x  = UVs[6];
			m_Buffer->UVs.y  = UVs[7];
			m_Buffer->texID  = ts;
			m_Buffer->color  = NULL_COLOR;
			m_Buffer++;

		} else {
			
			m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y);
			m_Buffer->depth  = depth;
			m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
			m_Buffer->color  = color;
			m_Buffer++;

			m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X, QUAD_DEFAULT_POSITION_Y + height);
			m_Buffer->depth  = depth;
			m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
			m_Buffer->color  = color;
			m_Buffer++;

			m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y + height);
			m_Buffer->depth  = depth;
			m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
			m_Buffer->color  = color;
			m_Buffer++;

			m_Buffer->vertex = worldMat * hpm::vec2(QUAD_DEFAULT_POSITION_X + width, QUAD_DEFAULT_POSITION_Y);
			m_Buffer->depth  = depth;
			m_Buffer->texID  = EMPTY_TEXTURE_SLOT;
			m_Buffer->color  = color;
			m_Buffer++;
		}
		m_IndexCount += 6;
	}

	void ForwardRenderer2D::drawString(std::string_view text, const hpm::mat3& worldMatrix, float depth, const Font* font, unsigned int color) {

		auto&		 characters = font->getCharacters();
		unsigned int atlasID	= font->getFontAtlas().getID();
		float		 scale		= font->getScale();

		float cursor = 0.0;

		float ts = submitTexture(atlasID);
		
		for (auto& character : text) {
			Character ch;
			try {
				ch = characters.at(character);
			} 
			catch (std::out_of_range& e) {
				PRX_ERROR("Renderer2D: Couldn`t find character in font atlas./n-> EXCEPTION: ", e.what());
				return;
			}
			
			float xpos = (QUAD_DEFAULT_POSITION_X + cursor + ch.Bearing.x) * scale;
			float ypos = (QUAD_DEFAULT_POSITION_Y - (ch.Size.y - ch.Bearing.y)) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;

			m_Buffer->vertex = worldMatrix * hpm::vec2(xpos, ypos);
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = ch.AtlasCoords.x / font->getFontAtlas().getWidth();
			m_Buffer->UVs.y  = ch.AtlasCoords.y / font->getFontAtlas().getHeight();
			m_Buffer->texID  = ts;
			m_Buffer->color  = color;
			m_Buffer++;

			m_Buffer->vertex = worldMatrix * hpm::vec2(xpos, ypos + h);
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = ch.AtlasCoords.x / font->getFontAtlas().getWidth();
			m_Buffer->UVs.y  = (ch.AtlasCoords.y + ch.AtlasCoords.w) / font->getFontAtlas().getHeight();
			m_Buffer->texID  = ts;
			m_Buffer->color  = color;
			m_Buffer++;

			m_Buffer->vertex = worldMatrix * hpm::vec2(xpos + w, ypos + h);
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = (ch.AtlasCoords.x + ch.AtlasCoords.z) / font->getFontAtlas().getWidth();
			m_Buffer->UVs.y  = (ch.AtlasCoords.y + ch.AtlasCoords.w) / font->getFontAtlas().getHeight();
			m_Buffer->texID  = ts;
			m_Buffer->color  = color;
			m_Buffer++;

			m_Buffer->vertex = worldMatrix * hpm::vec2(xpos + w, ypos);
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = (ch.AtlasCoords.x + ch.AtlasCoords.z) / font->getFontAtlas().getWidth();
			m_Buffer->UVs.y  = ch.AtlasCoords.y / font->getFontAtlas().getHeight();
			m_Buffer->texID  = ts;
			m_Buffer->color  = color;
			m_Buffer++;

			m_IndexCount += 6;
			cursor += (ch.Advance >> 6);
		}
	}

	void ForwardRenderer2D::drawString(std::string_view text, const hpm::vec2& position, float depth, const Font* font, unsigned color) {
		auto&		 characters = font->getCharacters();
		unsigned int atlasID = font->getFontAtlas().getID();
		float		 scale = font->getScale();

		float cursor = 0.0;

		float ts = submitTexture(atlasID);

		for (auto& character : text) {
			Character ch;
			try {
				ch = characters.at(character);
			}
			catch (std::out_of_range& e) {
				PRX_ERROR("Renderer2D: Couldn`t find character in font atlas./n-> EXCEPTION: ", e.what());
				return;
			}

			float xpos = (position.x + cursor + ch.Bearing.x) * scale;
			float ypos = (position.y - (ch.Size.y - ch.Bearing.y)) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;

			m_Buffer->vertex = hpm::vec2(xpos, ypos);
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = ch.AtlasCoords.x / font->getFontAtlas().getWidth();
			m_Buffer->UVs.y  = ch.AtlasCoords.y / font->getFontAtlas().getHeight();
			m_Buffer->texID  = ts;
			m_Buffer->color  = color;
			m_Buffer++;

			m_Buffer->vertex = hpm::vec2(xpos, ypos + h);
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = ch.AtlasCoords.x / font->getFontAtlas().getWidth();
			m_Buffer->UVs.y  = (ch.AtlasCoords.y + ch.AtlasCoords.w) / font->getFontAtlas().getHeight();
			m_Buffer->texID  = ts;
			m_Buffer->color  = color;
			m_Buffer++;

			m_Buffer->vertex = hpm::vec2(xpos + w, ypos + h);
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = (ch.AtlasCoords.x + ch.AtlasCoords.z) / font->getFontAtlas().getWidth();
			m_Buffer->UVs.y  = (ch.AtlasCoords.y + ch.AtlasCoords.w) / font->getFontAtlas().getHeight();
			m_Buffer->texID  = ts;
			m_Buffer->color  = color;
			m_Buffer++;

			m_Buffer->vertex = hpm::vec2(xpos + w, ypos);
			m_Buffer->depth  = depth;
			m_Buffer->UVs.x  = (ch.AtlasCoords.x + ch.AtlasCoords.z) / font->getFontAtlas().getWidth();
			m_Buffer->UVs.y  = ch.AtlasCoords.y / font->getFontAtlas().getHeight();
			m_Buffer->texID  = ts;
			m_Buffer->color  = color;
			m_Buffer++;

			m_IndexCount += 6;
			cursor += (ch.Advance >> 6);
		}
	}

	float ForwardRenderer2D::submitTexture(unsigned texID) {
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

	void ForwardRenderer2D::end() {
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void ForwardRenderer2D::flush() {
		for (int i = 0; i < m_TextureSlots.size(); i++) {
			GLCall(glActiveTexture(GL_TEXTURE0 + i));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]));
		}
		GLCall(glActiveTexture(GL_TEXTURE31));
		m_Mask->bind();
		
		GLCall(glBindVertexArray(m_VAO));
		m_IBO->Bind();

		m_Shader->bind();
		if (m_ProjMatrixNeedsUpdate) {
			m_Shader->setUniform("u_ProjectionMatrix", m_ProjectionMatrix);
			m_ProjMatrixNeedsUpdate = false;
		}

		if (m_RenderTarget == RenderTarget::BUFFER) {
			m_FrameBuffer->bind();
			//m_FrameBuffer->clear();

			GLCall(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL));

			m_FrameBuffer->unbind();
		} 
		else {
			GLCall(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL));
		}
		
		m_Shader->unbind();

		m_IBO->Unbind();
		GLCall(glBindVertexArray(0));

		m_IndexCount = 0;
	}

	void ForwardRenderer2D::setFrameBuffer(FrameBuffer2D* framebuffer) {
		if (framebuffer->validate()) {
			m_FrameBuffer = framebuffer;
			return;
		}
		PRX_ERROR("RENDERER: Failed to set framebuffer. Framebuffer is incomplete.");
	}

	void ForwardRenderer2D::setRenderTarget(RenderTarget target) {
		if (target == RenderTarget::BUFFER && m_FrameBuffer == nullptr) {
			PRX_ERROR("RENDERER: Failed to set buffer as render target. Buffer was nullptr");
		}
		m_RenderTarget = target;
	}
}
