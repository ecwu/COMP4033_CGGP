#include "utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;


void init_texture(GLuint *textures, int type_num) {
	glGenTextures(type_num, textures);
}

void set_texture(GLuint* textures, int index, char* filename) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 4);

	glBindTexture(GL_TEXTURE_2D, textures[index]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEnable(GL_TEXTURE_2D);
}

void clear_texture(GLuint* textures, int type_num) {
	glDeleteTextures(type_num, textures);
}
