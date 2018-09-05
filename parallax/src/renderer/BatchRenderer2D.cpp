#include "BatchRenderer2D.h"

namespace prx {
	prx::BatchRenderer2D::BatchRenderer2D() 
		: Renderer2D() {
		
		init();
	}

	BatchRenderer2D::~BatchRenderer2D() {
		
		// Smart poiners care about heap allocted memory.
		
		GLCall(glDeleteBuffers(1, &m_VBO));
	}

	void BatchRenderer2D::drawString(std::string_view text, hpm::vec3 position, const Font& font, hpm::vec4 color) {

		auto characters = font.getCharacters();

		float cursor = 0.0;

		for (auto& character : text) {
			Character ch = characters[character];
			float ts = 0.0f;
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++) {
				if (m_TextureSlots[i] == ch.TexID) {
					found = true;
					ts = static_cast<float>(i + 1);
					break;
				}
			}
			if (!found) {
				if (m_TextureSlots.size() >= 32) {
					end();
					flush();
					begin();
					m_TextureSlots.clear();
					m_TextureSlots.resize(0);
				}

				m_TextureSlots.push_back(ch.TexID);
				ts = static_cast<float>(m_TextureSlots.size());
			}

			float xpos = position.x + cursor + ch.Bearing.x;
			float ypos = position.y - (ch.Size.y - ch.Bearing.y);

			float w = ch.Size.x;
			float h = ch.Size.y;

			int r = color.r * 255.0;
			int g = color.g * 255.0;
			int b = color.b * 255.0;
			int a = color.a * 255.0;
			
			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(xpos, ypos, 0.0);
			m_Buffer->texCoords.x = 0.0;
			m_Buffer->texCoords.y = 1.0;
			m_Buffer->texID = ts;
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(xpos, ypos + h, 0);
			m_Buffer->texCoords.x = 0.0;
			m_Buffer->texCoords.y = 0.0;
			m_Buffer->texID = ts;
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(xpos + w, ypos + h, 0);
			m_Buffer->texCoords.x = 1.0;
			m_Buffer->texCoords.y = 0.0;
			m_Buffer->texID = ts;
			m_Buffer->color = c;
			m_Buffer++;

			m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(xpos + w, ypos, 0);
			m_Buffer->texCoords.x = 1.0;
			m_Buffer->texCoords.y = 1.0;
			m_Buffer->texID = ts;
			m_Buffer->color = c;
			m_Buffer++;

			m_IndexCount += 6;
			cursor += (ch.Advance >> 6);
		}
	}

	void BatchRenderer2D::begin() {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
		GLCall(m_Buffer = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)));
	}

	void BatchRenderer2D::submit(const Renderable2D & renderable)
	{
		const hpm::vec3&	position	= renderable.getPosition();
		const hpm::vec2&	size		= renderable.getSize();
		const hpm::vec4&	color		= renderable.getColor();
		const float*		UVs			= renderable.getUVs();
		const unsigned int	texID		= renderable.getTexID();
		
		unsigned int c = 255 << 24 | 255 << 16 | 255 << 8 | 255;

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
				if(m_TextureSlots.size() >= 32) {
					end();
					flush();
					begin();
					m_TextureSlots.clear();
					m_TextureSlots.resize(0);
				}
				
				m_TextureSlots.push_back(texID);
				ts = static_cast<float>(m_TextureSlots.size());
			}
		} else {
			
			int r = color.r * 255.0;
			int g = color.g * 255.0;
			int b = color.b * 255.0;
			int a = color.a * 255.0;
			c = a << 24 | b << 16 | g << 8 | r;
		}



		m_Buffer->vertex = m_TransformationStackBack * position;
		m_Buffer->texCoords.x = UVs[0];
		m_Buffer->texCoords.y = UVs[1];
		m_Buffer->texID = ts;
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->texCoords.x = UVs[2];
		m_Buffer->texCoords.y = UVs[3];
		m_Buffer->texID = ts;
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->texCoords.x = UVs[4];
		m_Buffer->texCoords.y = UVs[5];
		m_Buffer->texID = ts;
		m_Buffer->color = c;
		m_Buffer++;

		m_Buffer->vertex = m_TransformationStackBack * hpm::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->texCoords.x = UVs[6];
		m_Buffer->texCoords.y = UVs[7];
		m_Buffer->texID = ts;
		m_Buffer->color = c;
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
		
		GLCall(glBindVertexArray(m_VAO));
		m_IBO->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL));

		m_IBO->Unbind();
		GLCall(glBindVertexArray(0));

		m_IndexCount = 0;
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

		m_IBO = std::make_unique<IndexBuffer>(indices, BATCH_RENDERER_INDICES_SIZE);

		delete[] indices;

		GLCall(glBindVertexArray(0));
	}
}
