#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
	public:
		// ������ ID �� ������ ������� ���������
		GLuint ID;
		// ����������� ������� ���������� ������ ������� ��������� � �������� ��� ������� (indices)
		EBO(GLuint* indices, GLsizeiptr size);

		// ��������� EBO
		void Bind();
		// ���������� EBO
		void Unbind();
		//������� EBO
		void Delete();
};

#endif