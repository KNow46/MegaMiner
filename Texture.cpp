#include "Texture.h"
#include <iostream>
#include "src/vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	: m_FilePath(path), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	//GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	//GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		std::cout << "\nError: Failed to load texture" << std::endl;
		//std::cout << stbi_failure_reason() << std::endl;
		//__debugbreak();
	}

}

Texture::Texture()
{

}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot))
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::Texture(const Texture& other)
	: m_FilePath(other.m_FilePath), m_LocalBuffer(nullptr),
	m_Width(other.m_Width), m_Height(other.m_Height), m_BPP(other.m_BPP)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	//GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	if (m_LocalBuffer)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		std::cout << "\nError: Failed to load texture with path: " << m_FilePath << std::endl;
		std::cout << stbi_failure_reason() << std::endl;
		__debugbreak();
	}
}
//Texture& Texture::operator=(const Texture& other)
//{
//	m_FilePath =  other.m_FilePath;
//	m_LocalBuffer = nullptr,
//	m_Width = other.m_Width; 
//	m_Height = other.m_Height;
//	m_BPP = other.m_BPP;
//
//	stbi_set_flip_vertically_on_load(1);
//	m_LocalBuffer = stbi_load(other.m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
//
//	GLCall(glGenTextures(1, &m_RendererID));
//	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
//
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
//	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
//
//	if (m_LocalBuffer)
//	{
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
//		glBindTexture(GL_TEXTURE_2D, 0);
//		stbi_image_free(m_LocalBuffer);
//	}
//	else
//	{
//		std::cout << "\nError: Failed to load texture" << std::endl;
//		std::cout << stbi_failure_reason() << std::endl;
//		__debugbreak();
//	}
//	return *this;
//}