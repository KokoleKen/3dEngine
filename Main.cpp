#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"Texture.h"
#include"shaderClass.h"
#include"VBO.h"
#include"EBO.h"
#include"VAO.h"

GLfloat vertices[] =
{ //     ����������      /	   	   �����	    / �����. �������
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f,  0.0f, 	   0.0f, 0.0f,	// ������ ����� ����
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,  0.0f, 	   0.0f, 1.0f,	// ������� ����� ����
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,  1.0f,	   1.0f, 1.0f,	// ������� ������ ����
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f,  1.0f,	   1.0f, 0.0f	// ������ ������ ����
};

GLuint indices[] =
{
	0, 2, 1, // ������� �����������
	0, 3, 2  // ������ �����������
};

int main()
{
	// ������������� GLFW
	glfwInit();

	// ���������� ���  GLFW ����� ������ OpenGL �� ����������
	// ����� ������� OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// ���������� ��� GLFW ��� �� ���������� ������� CORE
	// ��� ��������, ��� � ��� ���� ������ ����������� �������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// �������� ������� GLFWwindow �������� 800 �� 800 �������� � ��������� "3dEngine"
	GLFWwindow* window = glfwCreateWindow(800, 800, "3dEngine", NULL, NULL);
	// �������� �� ������, ���� ��� �������� ���� �������� ������
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// �������� ������� ���� � ������� ��������
	glfwMakeContextCurrent(window);

	// �������� GLAD ������� ����������� OpenGL
	gladLoadGL();

	// �������� ������ ����������� OpenGL � ����
	// ��������� viewport � x = 0, y = 0, �� x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// ������� ������ ������� ��������� ������� default.vert � default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// ���������� ������ ������� ������ � ��������� ���
	VAO VAO1;
	VAO1.Bind();
	
	// ���������� ������ ������� ������ � ��������� ��� � ���������
	VBO VBO1(vertices, sizeof(vertices));
	// ���������� ������ ������� ��������� � ��������� ��� � ��������� (indices)
	EBO EBO1(indices, sizeof(indices));

	// �������� ��������� VBO ��� VAO, ����� ��� ���������� � �����
	VAO1.LinkAttrib(VBO1, 0,  3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// ���������� ��� ������ ����� �������� �� ���������� ���������
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// �������� ID �������� ���������� "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture cat("cat2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	cat.texUnit(shaderProgram, "tex0", 0);

	// ��������� ���� ������� ����
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// ������� ��� ����� � ��������� � ���� ����� ����
	glClear(GL_COLOR_BUFFER_BIT);
	// ������ ������� ��� ������ � ����� ��������
	glfwSwapBuffers(window);

	// �������� while ����
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// �������� OpenGL ����� ��������� �������� �� ����� ������������
		shaderProgram.Activate();
		// ��������� �������� � ��������; ���������: ������ ���� ������ ��������� ����� ��������� ��������� ��������
		glUniform1f(uniID, 0.5f);
		// ��������� �������� ����� ��� ���������� � �������
		cat.Bind();
		// ��������� VAO ��� ��� OpenGL ����� ��� ��� ������������
		VAO1.Bind();
		// ������ ���������, ���������: ��� ���������, ����� �������� ������, ��� ������ �������� ������, ������ �������� ������
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// ������������ ��� GLFW �������
		glfwPollEvents();
	}

	// ������� ��� ������� ��� ���� �������
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	cat.Delete();
	shaderProgram.Delete();
	// ������� ���� ����� ������� �� ���������
	glfwDestroyWindow(window);
	// ���������� ������ GLFW ����� ����������� ���������
	glfwTerminate();
	return 0;
}