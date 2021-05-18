#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


//�摜�ǂݍ��݊֐�
FrameWork::TextureData FrameWork::LoadTexture(const char* fileName)
{
	FrameWork::TextureData data;
	data.fileData = NULL;

	data.fileData = stbi_load(fileName, &data.size.x, &data.size.y, &data.channel, 0);

	assert(data.fileData && "�摜�t�@�C��������܂���B");

	return data;
}
