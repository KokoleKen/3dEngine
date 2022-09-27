#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
	public:
		// ������ ID �� ������ ������� ������
		GLuint ID;
		// ����������� ������� ���������� ������ ������� ������ � �������� ��� �������
		VBO(GLfloat* verices, GLsizeiptr size);

		// ��������� VBO
		void Bind();
		// ���������� VBO
		void Unbind();
		// ������� VBO
		void Delete();
};

#endif