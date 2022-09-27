#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// ��������� ��� �������� �� ������� ��������
	type = texType;
	// ������ ������, ������ � ����� �������� ������� �����������
	int widthImg, heightImg, numColCh;
	// �������������� ������������ ��� ��������
	stbi_set_flip_vertically_on_load(true);
	// ��������� ����������� �� ����� � ������ ��� � ������� ������
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// ���������� ������ �������� OpenGL
	glGenTextures(1, &ID);
	// ��������� �������� � ��������� ��������
	glActiveTexture(slot);
	// ����������� �������� � ������� �������� OpenGL
	glBindTexture(texType, ID);

	// ������������� ��� ��������� ������� ������������ ��� ��������������� �����������
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// ������������� ������ ���������� �������� (���� ��� ����������� �� �����������)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �������������� ������ ���� ����� ����� ������������ GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// ��������� ����������� � ������� ������ � ������� ������� OpenGL
	glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
	// ���������� MipMaps
	glGenerateMipmap(texType);

	// ������� ������ �����������, �.�. ��� ��� ��������� � ������� �������� OpenGL
	stbi_image_free(bytes);

	// ���������� ������ �������� OpenGL ����� ��� �������� �� ��������
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit)
{
	// �������� ������� ��������
	GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
	// ���������� ������������ ������ ����� ���������� �������� ��������
	shader.Activate();
	glUniform1i(tex0Uni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}