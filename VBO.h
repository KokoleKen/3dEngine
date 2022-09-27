#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
	public:
		// Ссылка ID на Объект Буффера Вершин
		GLuint ID;
		// Конструктор который генерирует Объект Буффера Вершин и передает ему вершины
		VBO(GLfloat* verices, GLsizeiptr size);

		// Связывает VBO
		void Bind();
		// Отвязывает VBO
		void Unbind();
		// Удаляет VBO
		void Delete();
};

#endif