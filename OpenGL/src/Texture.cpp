#include "Texture.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string & path): m_RendererID(0) ,m_FilePath(path), 
											m_LocalBuffer(nullptr), m_Height(0), m_Width(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);      //it will write the width & height & BPP. 4 is the channel - RGBA

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	//Min filter - Minification filter: This is how our texture can actually be resampled down if it needs to be rendered smaller
	//Linear because we want to render linearly

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Magnification Filter - which kinda renders our texture on an area that is larger in pixel than the actual texture size so need to scale it up

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//Wrap_S: Horizontal wrap ... clamp: which means we want to NOT extend the area (other option is tilling)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//Wrap_T: Vertical... S&T is like axes for texture. 

	//Need to specify ALL these 4 params !!!

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	//for this func: internalFormat is how OpenGL will store a texture; whereas the format is the format of the data you're providing OpenGL with

	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);

}

void Texture::bind(unsigned int slot /*=0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot); //the slot we use. Default is Texture0
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
