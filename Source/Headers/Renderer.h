#pragma once
class Renderer
{
	static Renderer* instance;

	Renderer(void);
	Renderer(const Renderer&);
	Renderer& operator=(const Renderer&);

	GLchar* GetShaderFile(const char* file,GLuint shader);
	GLuint LoadShaderPairFromFile(char* vertexProg,char* fragmentProg);
	
	GLuint shaderProgram;
	GLint uniformColor;
	GLuint testBuffer;
	GLuint VertexArrayID;
	

public:
	enum Entities{PLAYER,ZOMBIE,NPC,NUM_ENTITIES};
	static Renderer* GetInstance();
	static Renderer& GetReference();
	void Initialize();
	void Draw(Entities entity,GLfloat posX,GLfloat posY);
	void Render();
	void Shutdown();
	~Renderer(void);


};

