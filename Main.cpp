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
{ //     КООРДИНАТЫ      /	   	   ЦВЕТА	    / КООРД. ТЕКСТУР
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f,  0.0f, 	   0.0f, 0.0f,	// Нижний левый угол
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,  0.0f, 	   0.0f, 1.0f,	// Верхний левый угол
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f,  1.0f,	   1.0f, 1.0f,	// Верхний правый угол
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f,  1.0f,	   1.0f, 0.0f	// Нижний правый угол
};

GLuint indices[] =
{
	0, 2, 1, // Верхний треугольник
	0, 3, 2  // Нижний треугольник
};

int main()
{
	// Инициализация GLFW
	glfwInit();

	// Информация для  GLFW какую версию OpenGL мы используем
	// Здесь указана OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Информация для GLFW что мы используем профиль CORE
	// Это означает, что у нас есть только современные функции
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Создание объекта GLFWwindow размером 800 на 800 пикселей с названием "3dEngine"
	GLFWwindow* window = glfwCreateWindow(800, 800, "3dEngine", NULL, NULL);
	// Проверка на случай, если при создании окна случится ошибка
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Введение понятия окна в текущий контекст
	glfwMakeContextCurrent(window);

	// Загрузка GLAD который настраивает OpenGL
	gladLoadGL();

	// Указание вывода изображения OpenGL в окно
	// Указывает viewport с x = 0, y = 0, до x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Создает Объект Шейдера используя шейдеры default.vert и default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Генерирует Объект Массива Вершин и связывает его
	VAO VAO1;
	VAO1.Bind();
	
	// Генерирует Объект Буффера Вершин и связывает его с вершинами
	VBO VBO1(vertices, sizeof(vertices));
	// Генерирует Объект Буффера Элементов и связывает его с индексами (indices)
	EBO EBO1(indices, sizeof(indices));

	// Передает аттрибуты VBO для VAO, такие как координаты и цвета
	VAO1.LinkAttrib(VBO1, 0,  3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Отвязывает все модули чтобы избежать их случайного изменения
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Получает ID униформы называемой "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture cat("cat2.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	cat.texUnit(shaderProgram, "tex0", 0);

	// Указывает цвет заднего фона
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Очищает бэк буфер и применяет к нему новый цвет
	glClear(GL_COLOR_BUFFER_BIT);
	// Меняет местами бэк буффер с фронт буффером
	glfwSwapBuffers(window);

	// Основной while цикл
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Сообщает OpenGL какую Программу Шейдеров мы хотим использовать
		shaderProgram.Activate();
		// Применяет значение к униформе; ЗАМЕЧАНИЕ: Должно быть всегда выполнено после активации Программы Шейдеров
		glUniform1f(uniID, 0.5f);
		// Связывает текстуру чтобы она появлялась в рендере
		cat.Bind();
		// Связывает VAO так что OpenGL знает как это использовать
		VAO1.Bind();
		// Рисует примитивы, используя: тип примитива, число индексов вершин, тип данных индексов вершин, индекс индексов вершин
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		// Обрабатывает все GLFW события
		glfwPollEvents();
	}

	// Удаляет все объекты что были созданы
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	cat.Delete();
	shaderProgram.Delete();
	// Удаляет окно перед выходом из программы
	glfwDestroyWindow(window);
	// Прекращает работу GLFW перед завершением программы
	glfwTerminate();
	return 0;
}