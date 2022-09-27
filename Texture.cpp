#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// Назначает тип текстуры от объекта текстуры
	type = texType;
	// Хранит ширину, высоту и число цветовых каналов изображения
	int widthImg, heightImg, numColCh;
	// Переворачивает вертикальную ось текстуры
	stbi_set_flip_vertically_on_load(true);
	// Считывает изображение из файла и хранит его в массиве байтов
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// Генерирует объект текстуры OpenGL
	glGenTextures(1, &ID);
	// Применяет текстуру к элеменету текстуры
	glActiveTexture(slot);
	// Привязывает текстуру к объекту текстуры OpenGL
	glBindTexture(texType, ID);

	// Конфигурирует тип алгоритма который используется для масштабирования изображения
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Конфигурирует способ повторения текстуры (если она повторяется на поверхности)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Дополнительный способ если нужно будет использовать GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Назначает изображение в массиве байтов к объекту текстур OpenGL
	glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
	// Генерирует MipMaps
	glGenerateMipmap(texType);

	// Удаляет данные изображения, т.к. оно уже находится в объекте текстуры OpenGL
	stbi_image_free(bytes);

	// Отвязывает объект текстуры OpenGL чтобы его случайно не изменить
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit)
{
	// Получает позицию униформы
	GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
	// Необходимо активировать шейдер перед изменением значения униформы
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