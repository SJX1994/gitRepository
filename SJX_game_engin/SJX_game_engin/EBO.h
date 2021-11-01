#ifndef EBO_CLASS_H 
#define EBO_CLASS_H 

#include <glad/glad.h>
//65429
class EBO
{
public:
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size); 

	void Bind();
	void UnBind();
	void Delete();
};


#endif
