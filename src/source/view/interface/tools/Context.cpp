/*
 *      Nombre: Context.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Clase encargada de gestionar e inicializar la libreria de openGL.
 *
 */

#include "../../../../headers/view/interface/tools/Context.h"
#include "../../../../headers/Tools.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Context::Context(const Interface* interface) {
	if (BASIC_LOG) {
		cout << "------Generado la herramienta Context para la vista Interfaz " << endl;
	}
	refInterface_ = interface;
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
				->log("------Generado la herramienta Context para la vista Interfaz ");
	}
	compilerStateOK_ = GL_FALSE;
	linkerStateOK_ = GL_FALSE;
}

Context::~Context() {
	if (BASIC_LOG) {
		cout << "------Destruyendo la herramienta Context para la vista Interfaz " << endl;
	}
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
				->log("------Destruyendo la herramienta Context para la vista Interfaz ");
	}
	glDeleteBuffers(1, &bufferVertex_);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Context::init() {
	if (ADVAN_LOG) {
		((Interface*)refInterface_)
			->log("------Iniciando el contexto OGL de la herramienta Context ");
	}
	initShaders();
	initBuffers();

}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:

// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
void Context::initShaders() {
	const char *vs_source =
		#ifdef GL_ES_VERSION_2_0
			"#version 100\n"  // OpenGL ES 2.0
		#else
			"#version 120\n"  // OpenGL 2.1
		#endif
			"  uniform      mat4 modelview_matrix;    "
			"  uniform      mat4 projection_matrix;   "
			"attribute vec2 coord2d;                  "
			"void main(void) {                        "
			"  vec4 pos = modelview_matrix * vec4(coord2d[0], -0.5 , coord2d[1], 1.0); "
			"  gl_Position = projection_matrix * pos; "
			"}";
	const char *fs_source =
			"#version 120           \n"
			"void main(void) {        "
			"  gl_FragColor[0] = 0.9; "
			"  gl_FragColor[1] = 0.4; "
			"  gl_FragColor[2] = 0.2; "
			"}";
	//const char* attribute_name = "coord2d"; //Nombre de la variable global instanciada en el vertex shader

	vertexShader_ = glCreateShader(GL_VERTEX_SHADER);  //Crear el vertex shader
	glShaderSource(vertexShader_, 1, &vs_source, NULL);
	glCompileShader(vertexShader_);  //Compilar el vertex shader
	glGetShaderiv(vertexShader_, GL_COMPILE_STATUS, &compilerStateOK_);

	if (0 == compilerStateOK_) {  // Comprobar si la compilacion ha finalizado satisfactoriamente
		if (ADVAN_LOG) {
			((Interface*)refInterface_)
				->log("------ERROR!! Compilando el Vertex Shader. ");
		}
		((Interface*)refInterface_)->stop();
	}

	fragmentShader_ = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_, 1, &fs_source, NULL);
	glCompileShader(fragmentShader_);
	glGetShaderiv(fragmentShader_, GL_COMPILE_STATUS, &compilerStateOK_);

	if (0 == compilerStateOK_) {
		if (ADVAN_LOG) {
			((Interface*)refInterface_)
				->log("------ERROR!! Compilando el Fragment Shader. ");
		}
		((Interface*)refInterface_)->stop();
	}

	//setElProgramaGlsl(glCreateProgram());
	programGSL_ = glCreateProgram();
	glAttachShader(programGSL_, vertexShader_);
	glAttachShader(programGSL_, fragmentShader_);

	glLinkProgram(programGSL_);  //Enlazar el programa creado con OpenGL
	glGetProgramiv(programGSL_, GL_LINK_STATUS, &linkerStateOK_);

	if (0 == linkerStateOK_) {   // Comprobar el correcto enlazado del programa a openGL
		if (ADVAN_LOG) {
			((Interface*)refInterface_)
				->log("------ERROR!! Enlazando el programa GSL. ");
		}
		((Interface*)refInterface_)->stop();
	}
}

GLuint Context::getProgramGsl() const {
	return programGSL_;
}

void Context::initBuffers() {
	glGenBuffers(1, &bufferVertex_);
	glBindBuffer(GL_ARRAY_BUFFER, bufferVertex_);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


