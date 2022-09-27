#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
	public:
		// Ссылка ID на Объект Буффера Элементов
		GLuint ID;
		// Конструктор который генерирует Объект Буффера Элементов и передает ему индексы (indices)
		EBO(GLuint* indices, GLsizeiptr size);

		// Связывает EBO
		void Bind();
		// Отвязывает EBO
		void Unbind();
		//Удаляет EBO
		void Delete();
};

#endif