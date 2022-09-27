#include"shaderClass.h"

// Читает текстовый файл и выводит текст (string) со всем содержимым файла
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Конструктор который создает Программу Шейдеров из 2 разных шейдеров
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Читает vertexFile и fragmentFile и хранит их содержимое (sting)
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Конвертирует строки исходника шейдера в массив символов
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Создает Объект Шейдера Вершин и получает его ссылку
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//  Присоединяет источник Шейдера Вершин к Объекту Шейдера Вершин
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Компилирует Шейдер Вершин в машинный код
	glCompileShader(vertexShader);
	// Проверяет успешно ли скомпилировались Шейдеры
	compileErrors(vertexShader, "VERTEX");

	// Создает Объект Шейдера Фрагмента и получает его ссылку
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Присоединяет источник Шейдера Фрагмента к Объекту Фрагмент Шейдера
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Компилирует Шейдер Вершин в машинный код
	glCompileShader(fragmentShader);
	// Проверяет успешно ли скомпилировались Шейдеры
	compileErrors(fragmentShader, "FRAGMENT");

	// Создает Объект Программы Шейдера и получает его ссылку
	ID = glCreateProgram();
	// Присоединяет Вершины и Шейдер Фрагмента к Программе Шейдера
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Связывает все шейдеры вместо в Программу Шейдеров
	glLinkProgram(ID);
	// Проверяет успешно ли внедрились Шейдеры в программу
	compileErrors(ID, "PROGRAM");

	// Удаляет уже не используемые Объекты Шейдеров Вершин и Фрагментов
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Активирует Програму Шейдеров
void Shader::Activate()
{
	glUseProgram(ID);
}

// Удаляет Программу Шейдеров
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}