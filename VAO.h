#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ������ ID �� ������ ������� ������
	GLuint ID;
	// ����������� ������� ���������� VAO ID
	VAO();

	// �������� ��������� VBO ��� VAO ��������� ������������ �����
	void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// ��������� VAO
	void Bind();
	// ���������� VAO
	void Unbind();
	// ������� VAO
	void Delete();
};

#endif