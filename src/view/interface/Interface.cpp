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

#include "../../../include/view/interface/Interface.h"

// ___________________________________________________________________________________
// Constructores y Destructor:
Interface::Interface(const Controller& controller) :
		View(&controller) {
	logAction(LOG_INIT);
	bureaucrat_ = 0;
	scenographer_ = 0;

	window_ = 0;
	context_ = 0;
	scene_ = 0;
}
Interface::~Interface() {
	logAction(LOG_END);
	stop();
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
void Interface::init() {
	logAction(LOG_F_INIT);
	bureaucrat_ = new Bureaucrat(this);

	window_ = new Window(this);
	context_ = new Context(this);

	scene_ = new Scene(this);
	scenographer_ = new Scenographer(this, scene_, ((Director*)refController_)->getMap());

	bureaucrat_->initSDL();
	window_->init(WIN_WIDTH, WIN_HEIGHT);

	bureaucrat_->initOGL();
	context_->init();

	scenographer_->init();

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
		FileLog* fileLogTmp =
				(FileLog*) (((Director*) refController_)->getRegAccErr());
		fileLogTmp->insertLine(line);
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:
const Scene* Interface::getScene() const {
	return scene_;
}
const Scenographer* Interface::getScenographer() const {
	return scenographer_;
}
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

	// Enviar la proyección al shader
	glUniformMatrix4fv(
			glGetUniformLocation(context_->getProgramGsl(),
					"projection_matrix"), 1, GL_FALSE,
			scene_->getProjectionMatrix());
	// Enviar la cámara al shader
	glUniformMatrix4fv(
			glGetUniformLocation(context_->getProgramGsl(), "modelview_matrix"),
			1, GL_FALSE, scene_->getModelviewMatrix());

	// Enviar el suelo al shader y pintarlo.
	//    Buffer de vertices
	glBindBuffer(GL_ARRAY_BUFFER, context_->getVboId()[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 100 * 100 * 3 * 4 * 5,
			scene_->getVertexFloor(), GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(context_->getProgramGsl(), "coord3d")
				, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//    Buffer de colores
	glBindBuffer(GL_ARRAY_BUFFER, context_->getVboId()[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 100 * 100 * 3 * 4 * 5,
				scene_->getVertexFloorColor(), GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(context_->getProgramGsl(), "colorRGB")
					, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(glGetAttribLocation(context_->getProgramGsl(), "coord3d"));
	glEnableVertexAttribArray(glGetAttribLocation(context_->getProgramGsl(), "colorRGB"));

	glDrawArrays(GL_QUADS, 0, 100 * 100 * 4 * 5);

	glDisableVertexAttribArray(glGetAttribLocation(context_->getProgramGsl(), "coord3d"));
	glDisableVertexAttribArray(glGetAttribLocation(context_->getProgramGsl(), "colorRGB"));
	glUseProgram(0);

	window_->update();
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
			cout << "---Llamano a la función init de la clase Interface."
					<< endl;
			break;
		case LOG_F_STOP:
			cout << "---Llamano a la función stop de la clase Interface."
					<< endl;
			break;
		default:
			break;
		}
	}
	if (ADVAN_LOG) {
		FileLog* fileLogTmp =
				(FileLog*) (((Director*) refController_)->getRegAccErr());
		switch (index) {
		case LOG_INIT:
			fileLogTmp->insertLine("---Generando la vista Interfaz ");
			break;
		case LOG_END:
			fileLogTmp->insertLine("---Destruyendo la vista Interfaz ");
			break;
		case LOG_F_INIT:
			fileLogTmp->insertLine(
					"---Llamano a la función init de la clase Interface.");
			break;
		case LOG_F_STOP:
			fileLogTmp->insertLine(
					"---Llamano a la función stop de la clase Interface.");
			break;
		default:
			break;
		}
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


