#include "stdafx.h"
#include "Headers\Renderer.h"
#include <fstream>
#include <sstream>

Renderer* Renderer::instance = nullptr;

Renderer::Renderer(void){}
Renderer::~Renderer(void){}

Renderer* Renderer::GetInstance(){
	if(!instance)
		instance = new Renderer;
	return instance;
}
Renderer& Renderer::GetReference(){
	if(!instance)
		instance = new Renderer;
	return *instance;
}

void Renderer::Initialize(){
	glewInit();


	shaderProgram = LoadShaderPairFromFile("../Resources/Shaders/Shader.vp","../Resources/Shaders/Shader.fp");
	uniformColor = glGetUniformLocation(shaderProgram,"vColor");

	GLfloat testBufferData[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f,  0.5f
	};

	glGenVertexArrays(1,&VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1,&testBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,testBuffer);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(GLfloat),testBufferData,GL_STATIC_DRAW);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);
}

void Renderer::Draw(Entities entity,GLfloat posX, GLfloat posY){
	float triPoints[6] = {
		posX,      posY+0.03f,
		posX+0.01f,posY-0.03f,
		posX-0.01f,posY-0.03f,
	};

	float triPoints1[6] = {
		posX,      posY+0.013f,
		posX+0.0060f,posY-0.025f,
		posX-0.0060f,posY-0.025f
	};

	glUseProgram(shaderProgram);

	glBindVertexArray(VertexArrayID);

	glBindBuffer(GL_ARRAY_BUFFER,testBuffer);
	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(float),triPoints,GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);
	glUniform4f(uniformColor,0.0f,0.0f,0.0f,1.0f);
	glDrawArrays(GL_TRIANGLES,0,3);

	glBufferData(GL_ARRAY_BUFFER,6 * sizeof(float),triPoints1,GL_STATIC_DRAW);
	glUniform4f(uniformColor,0.5f,0.5f,0.5f,0.5f);
	//glUniform4f(uniformColor,0.0f,1.0f,0.0f,1.0f);
	glDrawArrays(GL_TRIANGLES,0,3);

	glBindVertexArray(NULL);



}

void Renderer::Render(){
	glClearColor(0.5f,0.2f,0.8f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Shutdown(){
	glDeleteProgram(shaderProgram);
}



GLuint Renderer::LoadShaderPairFromFile(char* vertexProg,char* fragmentProg)
{
	GLuint hVertexShader,hFragmentShader,hShader;
	GLint testVal;

	hVertexShader = glCreateShader(GL_VERTEX_SHADER);
	hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	GLchar* vertexShader = GetShaderFile(vertexProg,hVertexShader);
	GLchar* fragmentShader = GetShaderFile(fragmentProg,hFragmentShader);

	if(vertexShader == nullptr ||  fragmentShader == nullptr){
		glDeleteShader(hVertexShader);
		glDeleteShader(hFragmentShader);
		return (GLuint)NULL;
	}

	glCompileShader(hVertexShader);
	glCompileShader(hFragmentShader);

	glGetShaderiv(hVertexShader, GL_COMPILE_STATUS,&testVal);
	if(testVal == GL_FALSE){
		char infoLog[1024];
		glGetShaderInfoLog(hVertexShader,1024,NULL,infoLog);
		std::wstringstream wss;
		wss << "The shader at " << vertexProg << " failed to compile with the following error:\n" << infoLog << "\n";
		MessageBox(NULL,wss.str().c_str(),L"SHADER COMPILE ERROR",MB_ICONERROR);
		glDeleteShader(hVertexShader);
		glDeleteShader(hFragmentShader);
		return (GLuint)NULL;
	}

	glGetShaderiv(hFragmentShader,GL_COMPILE_STATUS,&testVal);
	if(testVal == GL_FALSE){
		char infoLog[1024];
		glGetShaderInfoLog(hFragmentShader,1024,NULL,infoLog);
		std::wstringstream wss;
		wss << "The shader at " << fragmentProg << " failed to compile with the following error:\n" << infoLog << "\n";
		MessageBox(NULL,wss.str().c_str(),L"SHADER COMPILE ERROR",MB_ICONERROR);
		glDeleteShader(hVertexShader);
		glDeleteShader(hFragmentShader);
		return (GLuint)NULL;
	}

	hShader = glCreateProgram(); 
	glAttachShader(hShader,hVertexShader);
	glAttachShader(hShader,hFragmentShader);

	glBindAttribLocation(hShader,0,"vVertexPos");

	glLinkProgram(hShader);

	glDeleteShader(hVertexShader);
	glDeleteShader(hFragmentShader);

	glGetProgramiv(hShader,GL_LINK_STATUS,&testVal);
	if(testVal == GL_FALSE){
		char infoLog[1024];
		glGetProgramInfoLog(hShader,1024,NULL,infoLog);
		std::wstringstream wss;
		wss << "The program " << vertexProg << " and " << fragmentProg << " failed to link with the following error:\n" << infoLog << "\n";
		MessageBox(NULL,wss.str().c_str(),L"SHADER COMPILE ERROR",MB_ICONERROR);
		glDeleteProgram(hShader);
		return (GLuint)NULL;
	}

	return hShader;
}

GLchar* Renderer::GetShaderFile(const char* shaderProg,GLuint shader)
{
	GLint srcLength = 0;
	GLchar* shaderSrc;
	std::ifstream ifs;

	ifs.open(shaderProg,std::ios::in);

	if(ifs.is_open()){
		//Get Size of file
		ifs.seekg(0,std::ios::end);
		srcLength = (GLint)ifs.tellg();
		ifs.seekg(0,std::ios::beg);
		shaderSrc = new GLchar[srcLength+1];
		shaderSrc[srcLength] = 0;

		/*ifs.read(shaderSrc,srcLength);*/
		unsigned int i = 0;
		while(ifs.good()){
			shaderSrc[i] = ifs.get();
			if(!ifs.eof())
				i++;
		}
		shaderSrc[i] = 0;
		ifs.close();
	}
	else{
		std::wstringstream wss;
		wss << "ERROR: Problem loading/finding " << shaderProg << std::endl;
		MessageBox(NULL,wss.str().c_str(),L"ERROR LOADING VERTEX PROGRAM",MB_ICONERROR);
		return nullptr;
	}
	glShaderSource(shader,1,(const GLchar**)&shaderSrc,NULL);

	return shaderSrc;
}
