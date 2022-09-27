#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		// Ссылка ID на Программу Шейдеров
		GLuint ID;
		// Конструктор который создает Программу Шейдеров из 2 разных шейдеров
		Shader(const char* vertexFile, const char* fragmentFile);

		// Активирует Программу Шейдеров
		void Activate();
		// Удаляет Программу Шейдеров
		void Delete();
	private:
		// Проверяет правильно ли скомпилировались разные шейдеры
		void compileErrors(unsigned int shader, const char* type);
};


#endif