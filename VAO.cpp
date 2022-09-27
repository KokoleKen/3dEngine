#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// �������� VBO � VAO ��������� ������������ �����
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// ��������� VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// ���������� VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// ������� VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}