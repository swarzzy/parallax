#include <renderer/BatchRenderer2D.h>
#include <utils/error_handling/GLErrorHandler.h>
#include <textures/Texture.h>

namespace prx {
	prx::BatchRenderer2D::BatchRenderer2D(RenderTarget rendertarget)
		: Renderer2D(rendertarget), m_IBO(nullptr), m_Buffer(nullptr)
	{
		init();
		defaultMask();
	}

	BatchRenderer2D::~BatchRenderer2D() {
		delete m_Mask;
		delete m_IBO;

		GLCall(glDeleteBuffers(1, &m_VBO));
	}

	void BatchRenderer2D::drawString(std::string_view text, hpm::vec3 position, const Font* font, unsigned int color) {

		auto&		 characters = font->getCharacters();
		unsigned int atlasID	= font->getFontAtlas().getID();
		float		 scale		= font->getScale();

		float cursor = 0.0;

		float ts = 0.0f;
		bool found = false;
		for (int i = 0; i < m_TextureSlots.size(); i++) {
			if (m_TextureSlots[i] == atlasID) {
				found = true;
				ts = static_cast<float>(i + 1);
				break;
			}
		}
		if (!found) {
			if (m_TextureSlots.size() >= BATCH_RENDERER_MAX_TEXTURE_SLOTS){
				end();
				flush();
				begin();
				m_TextureSlots.clear();
				//m_TextureSlots.resize(0);
				//m_TextureSlots.reserve(32);
			}

			m_TextureSlots.push_back(atlasID);
			ts = static_cast<float>(m_TextureSlots.size());
		}

		for (auto& character : text) {
			Character ch;
			// Try block may affects performance
			try {
				ch = characters.at(character);
			} 
			catch (std::out_of_range& e) {
				std::stringstream ss;
				ss << "RENDERER: Couldn`t find the character in the font: " << e.what();
				Log::message(LOG_LEVEL::LOG_ERROR, ss.str());
				return;
			}
			
			float xpos = (position.x + cursor + ch.Bearing.x) * scale;
			float ypos = (position.y - (ch.Size.y - ch.Bearing.y)) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;

			m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(xpos, ypos, position.z);
			m_Buffer->texCoords.x = ch.AtlasCoords.x / font->getFontAtlas().getWidth();
			m_Buffer->texCoords.y = ch.AtlasCoords.y / font->getFontAtlas().getHeight();
			m_Buffer->texID = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(xpos, ypos + h, position.z);
			m_Buffer->texCoords.x = ch.AtlasCoords.x / font->getFontAtlas().getWidth();
			m_Buffer->texCoords.y = (ch.AtlasCoords.y + ch.AtlasCoords.w) / font->getFontAtlas().getHeight();
			m_Buffer->texID = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(xpos + w, ypos + h, position.z);
			m_Buffer->texCoords.x = (ch.AtlasCoords.x + ch.AtlasCoords.z) / font->getFontAtlas().getWidth();
			m_Buffer->texCoords.y = (ch.AtlasCoords.y + ch.AtlasCoords.w) / font->getFontAtlas().getHeight();
			m_Buffer->texID = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(xpos + w, ypos, position.z);
			m_Buffer->texCoords.x = (ch.AtlasCoords.x + ch.AtlasCoords.z) / font->getFontAtlas().getWidth();
			m_Buffer->texCoords.y = ch.AtlasCoords.y / font->getFontAtlas().getHeight();
			m_Buffer->texID = ts;
			m_Buffer->color = color;
			m_Buffer++;

			m_IndexCount += 6;
			cursor += (ch.Advance >> 6);
		}
	}

	void BatchRenderer2D::begin() {
		m_IndexCount = 0;
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
		GLCall(m_Buffer = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)));
		// NOTE: Is that actually faster to clear slots?
		m_TextureSlots.clear();
	}

	void BatchRenderer2D::submit(const Renderable2D & renderable)
	{
		const hpm::vec3&	position	= renderable.getPosition();
		const hpm::vec2&	size		= renderable.getSize();
		unsigned int		color		= renderable.getColor();
		const float*		UVs			= renderable.getUVs();
		unsigned int		texID		= renderable.getTexID();

		float ts = 0.0f;
		if (texID > 0) {
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++) {
				if (m_TextureSlots[i] == texID) {
					found = true;
					ts = static_cast<float>(i + 1);
					break;
				}
			}
			if(!found) {
				if(m_TextureSlots.size() >= BATCH_RENDERER_MAX_TEXTURE_SLOTS) {
					end();
					flush();
					begin();
					m_TextureSlots.clear();
					//m_TextureSlots.resize(0);
				}
				
				m_TextureSlots.push_back(texID);
				ts = static_cast<float>(m_TextureSlots.size());
			}
		}

		m_Buffer->vertex = m_TransformationStackBack * position;
		m_Buffer->texCoords.x = UVs[0];
		m_Buffer->texCoords.y = UVs[1];
		m_Buffer->texID = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->texCoords.x = UVs[2];
		m_Buffer->texCoords.y = UVs[3];
		m_Buffer->texID = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->texCoords.x = UVs[4];
		m_Buffer->texCoords.y = UVs[5];
		m_Buffer->texID = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->texCoords.x = UVs[6];
		m_Buffer->texCoords.y = UVs[7];
		m_Buffer->texID = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void BatchRenderer2D::end() {
		GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void BatchRenderer2D::flush() {
		for (int i = 0; i < m_TextureSlots.size(); i++) {
			GLCall(glActiveTexture(GL_TEXTURE0 + i));
			GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]));
		}
		GLCall(glActiveTexture(GL_TEXTURE31));
		m_Mask->bind();
		
		GLCall(glBindVertexArray(m_VAO));
		m_IBO->Bind();

		if (m_RenderTarget == RenderTarget::BUFFER) {
			m_FrameBuffer->bind();
			//m_FrameBuffer->clear();

			GLCall(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL));

			m_FrameBuffer->unbind();
		} 
		else
			GLCall(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL));


		m_IBO->Unbind();
		GLCall(glBindVertexArray(0));

		// Moved this to begin while developing framebuffers
		//m_IndexCount = 0;
	}

	void BatchRenderer2D::setFrameBuffer(FrameBuffer2D* framebuffer) {
		if (framebuffer->validate()) {
			m_FrameBuffer = framebuffer;
			return;
		}
		PRX_ERROR("(Renderer): Failed to set framebuffer. Framebuffer is incomplte.");
		// TODO: exceptions
	}

	void BatchRenderer2D::setRenderTarget(RenderTarget target) {
		if (target == RenderTarget::BUFFER) {
			PRX_ASSERT(m_FrameBuffer, "(Renderer): Trying no set render target as a buffer. Buffer is not set.");
			// TODO: Exceptions and all that stuff to handle it properly
		}
		m_RenderTarget = target;
	}

	void BatchRenderer2D::init() {
		GLCall(glGenVertexArrays(1, &m_VAO));
		GLCall(glGenBuffers(1, &m_VBO));

		GLCall(glBindVertexArray(m_VAO));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, BATCH_RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW));
		
		GLCall(glEnableVertexAttribArray(BATCH_RENDERER_SHADER_VERTEX_INDEX));
		GLCall(glEnableVertexAttribArray(BATCH_RENDERER_SHADER_UV_INDEX));
		GLCall(glEnableVertexAttribArray(BATCH_RENDERER_SHADER_TEXID_INDEX));
		GLCall(glEnableVertexAttribArray(BATCH_RENDERER_SHADER_COLOR_INDEX));

		GLCall(glVertexAttribPointer(BATCH_RENDERER_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE,
			BATCH_RENDERER_VERTEX_SIZE, static_cast<const void*>(0)));

		GLCall(glVertexAttribPointer(BATCH_RENDERER_SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE,
			BATCH_RENDERER_VERTEX_SIZE, reinterpret_cast<const void*>(offsetof(VertexData, VertexData::texCoords))));

		GLCall(glVertexAttribPointer(BATCH_RENDERER_SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE,
			BATCH_RENDERER_VERTEX_SIZE, reinterpret_cast<const void*>(offsetof(VertexData, VertexData::texID))));

		GLCall(glVertexAttribPointer(BATCH_RENDERER_SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE,
			BATCH_RENDERER_VERTEX_SIZE, reinterpret_cast<const void*>(offsetof(VertexData, VertexData::color))));
		
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

		
		unsigned int* indices = new unsigned int[BATCH_RENDERER_INDICES_SIZE];

		unsigned int offset = 0;
		for (unsigned int i = 0; i < BATCH_RENDERER_INDICES_SIZE; i += 6) {
			indices[  i  ] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_IBO = new IndexBuffer(indices, BATCH_RENDERER_INDICES_SIZE);

		delete[] indices;

		GLCall(glBindVertexArray(0));
	}
}
