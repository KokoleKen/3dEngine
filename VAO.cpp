#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// ѕередает VBO к VAO использу€ определенный макет
void VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// —в€зывает VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// ќтв€зывает VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// ”дал€ет VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}