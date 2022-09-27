#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// Ссылка ID на Объект Массива Вершин
	GLuint ID;
	// Конструктор который генерирует VAO ID
	VAO();

	// Передает аттрибуты VBO для VAO используя определенный макет
	void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Связывает VAO
	void Bind();
	// Отвязывает VAO
	void Unbind();
	// Удаляет VAO
	void Delete();
};

#endif