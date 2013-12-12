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

#include <view/interface/tools/Context.h>

#include <view/interface/Interface.h>
#include <Tools.h>

#include <iostream>


// ___________________________________________________________________________________
// Constructores y Destructor:
Context::Context(const Interface& interface) {
	refInterface_ = &interface;
	logAction(LOG_INIT);
	compilerStateOK_ = GL_FALSE;
	linkerStateOK_ = GL_FALSE;
}

Context::~Context() {
	logAction(LOG_END);
	glDeleteBuffers(1, &bufferVertex_);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Context::init() {
	logAction(LOG_F_INIT);
	initShaders();
	initBuffers();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:
GLuint Context::getProgramGsl() const {
	return programGSL_;
}
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
	const char *fs_source = "#version 120           \n"
			"void main(void) {        "
			"  gl_FragColor[0] = 0.9; "
			"  gl_FragColor[1] = 0.4; "
			"  gl_FragColor[2] = 0.2; "
			"}";

	vertexShader_ = glCreateShader(GL_VERTEX_SHADER);  //Crear el vertex shader
	glShaderSource(vertexShader_, 1, &vs_source, NULL);
	glCompileShader(vertexShader_);  //Compilar el vertex shader
	glGetShaderiv(vertexShader_, GL_COMPILE_STATUS, &compilerStateOK_);

	if (compilerStateOK_ == 0) {
		logAction(LOG_ERROR);
		((Interface*) refInterface_)->stop();
	}

	fragmentShader_ = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_, 1, &fs_source, NULL);
	glCompileShader(fragmentShader_);
	glGetShaderiv(fragmentShader_, GL_COMPILE_STATUS, &compilerStateOK_);

	if (compilerStateOK_ == 0) {
		logAction(LOG_ERROR_1);
		((Interface*) refInterface_)->stop();
	}
	programGSL_ = glCreateProgram();
	glAttachShader(programGSL_, vertexShader_);
	glAttachShader(programGSL_, fragmentShader_);

	glLinkProgram(programGSL_);
	glGetProgramiv(programGSL_, GL_LINK_STATUS, &linkerStateOK_);

	if (linkerStateOK_ == 0) {
		logAction(LOG_ERROR_2);
		((Interface*) refInterface_)->stop();
	}
}

void Context::initBuffers() {
	glGenBuffers(1, &bufferVertex_);
	glBindBuffer(GL_ARRAY_BUFFER, bufferVertex_);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}
void Context::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
		case LOG_INIT:
			std::cout
					<< "------Generado la herramienta Context para la vista Interfaz"
					<< std::endl;
			break;
		case LOG_END:
			std::cout
					<< "------Destruyendo la herramienta Context para la vista Interfaz"
					<< std::endl;
			break;
		case LOG_F_INIT:
			std::cout << "------Iniciando el contexto OGL de la herramienta Context"
					<< std::endl;
			break;
		case LOG_ERROR:
			std::cout << "------ERROR!! Compilando el Vertex Shader" << 
std::endl;
			break;
		case LOG_ERROR_1:
			std::cout << "------ERROR!! Compilando el Fragment Shader" << 
std::endl;
			break;
		case LOG_ERROR_2:
			std::cout << "------ERROR!! Enlazando el programa GSL" << std::endl;
			break;
		default:
			break;
		}
	}
	if (ADVAN_LOG) {
		switch (index) {
		case LOG_INIT:
			dynamic_cast<Interface*>(
				const_cast<Interface*>(refInterface_))->log(
					"------Generado la herramienta Context para la vista Interfaz ");
			break;
		case LOG_END:
			dynamic_cast<Interface*>(
				const_cast<Interface*>(refInterface_))->log(
					"------Destruyendo la herramienta Context para la vista "
							"Interfaz ");
			break;
		case LOG_F_INIT:
			dynamic_cast<Interface*>(
				const_cast<Interface*>(refInterface_))->log(
					"------Iniciando el contexto OGL de la herramienta Context ");
			break;
		case LOG_ERROR:
			dynamic_cast<Interface*>(
				const_cast<Interface*>(refInterface_))->log(
					"------ERROR!! Compilando el Vertex Shader. ");
			break;
		case LOG_ERROR_1:
			dynamic_cast<Interface*>(
				const_cast<Interface*>(refInterface_))->log(
					"------ERROR!! Compilando el Fragment Shader. ");
			break;
		case LOG_ERROR_2:
			dynamic_cast<Interface*>(
				const_cast<Interface*>(refInterface_))->log(
					"------ERROR!! Enlazando el programa GSL. ");
			break;
		default:
			break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

