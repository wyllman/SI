/*
 *      Nombre: Interface.cpp
 *
 *   Creado en: 02/12/2013
 *     Versión: v0.0
 *     Autores: Tinguaro Cubas Saiz
 *              Juan Henández Hernández
 *              Miguel Pérez Bello
 *              Guillermo Rodríguez Pardo
 *
 * Descripción: Vista específica para la ejecución del simulador. Lleva el control de la
 *              ejecución y creación de la ventana y el contexto (SDL y OGL). Renderizar
 *              la escena, animar los objetos, etc...
 *
 */

#include "../../../headers/view/interface/Interface.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Interface::Interface(const Controller* controller):View(controller) {
	logAction(LOG_INIT);
	bureaucrat_ = 0;
	scenographer_ = 0;

	window_ = 0;
	context_ = 0;
	scene_ = 0;
}
Interface::~Interface() {
	logAction(LOG_END);
	stop ();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Interface::init() {
	logAction(LOG_F_INIT);
	bureaucrat_ = new Bureaucrat (this);
	scenographer_ = new Scenographer (this);

	window_ = new Window (this);
	context_ = new Context (this);
	scene_ = new Scene (this);

	bureaucrat_->initSDL();
	bureaucrat_->initOGL();

	window_->init(500, 500);
	context_->init();

	render();
}
void Interface::stop() {
	logAction(LOG_F_STOP);
	if (bureaucrat_ != 0) {
		delete (bureaucrat_);
		bureaucrat_ = 0;
	}
	if (scenographer_ != 0) {
		delete (scenographer_);
		scenographer_ = 0;
	}
	if (window_ != 0) {
		delete (window_);
		window_ = 0;
	}
	if (context_ != 0) {
		delete (context_);
		context_ = 0;
	}
	if (scene_ != 0) {
		delete (scene_);
		scene_ = 0;
	}
}
void Interface::log(const char* line) {
	if (ADVAN_LOG) {
		FileLog* fileLogTmp = (FileLog*)(((Director*)refController_)->getRegAccErr());
		fileLogTmp->insertLine(line);
	}
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
void Interface::render() {
	// Clear the background as white
	glClearColor(1.0, 1.0, 0.9, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(context_->getProgramGsl());

	float ratio = 500 / 500;
	float near = 1;
	float far = 1000;

	GLfloat modelviewMatrix[16];
	GLfloat projectionMatrix[16];

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(45.0, ratio, near, far);
	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);

	glMatrixMode( GL_MODELVIEW );
	gluLookAt(0,0,0,    0, 0,1,    0,1,0);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
	glMatrixMode(0);

	glUniformMatrix4fv(glGetUniformLocation(context_->getProgramGsl(),  "projection_matrix"),
						1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(glGetUniformLocation(context_->getProgramGsl(),  "modelview_matrix"),
						1, GL_FALSE, modelviewMatrix);
	glEnableVertexAttribArray(0);

	createFloor(1000, 1000);

	glDisableVertexAttribArray(0);
	glUseProgram(0);

	window_->update();
}
void Interface::createFloor(int width, int height) {
	float vertexFloor[width * height * 2];

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			vertexFloor[((i * width) + j) * 2] = (i - (width / 2)) / 100.0;
			vertexFloor[((i * width) + j) * 2 + 1] = (j - (width / 2)) / 100.0;
		}
	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * width * height * 2
					, vertexFloor, GL_STATIC_DRAW);
	glDrawArrays(GL_POINTS, 0, width * height);
}
void Interface::logAction(int index) {
	if (BASIC_LOG) {
		switch (index) {
			case LOG_INIT:
				cout << "---Generado la vista Interfaz " << endl;
				break;
			case LOG_END:
				cout << "---Destruyendo la vista Interfaz " << endl;
				break;
			case LOG_F_INIT:
				cout << "---Llamano a la función init de la clase Interface." << endl;
				break;
			case LOG_F_STOP:
				cout << "---Llamano a la función stop de la clase Interface." << endl;
				break;
			default:
				break;
		}
	}
	if(ADVAN_LOG) {
		FileLog* fileLogTmp = (FileLog*)(((Director*)refController_)->getRegAccErr());
		switch (index) {
			case LOG_INIT:
				fileLogTmp->insertLine("---Generando la vista Interfaz ");
				break;
			case LOG_END:
				fileLogTmp->insertLine("---Destruyendo la vista Interfaz ");
				break;
			case LOG_F_INIT:
				fileLogTmp->insertLine("---Llamano a la función init de la clase Interface.");
				break;
			case LOG_F_STOP:
				fileLogTmp->insertLine("---Llamano a la función stop de la clase Interface.");
				break;
			default:
				break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


