/*
 * SearchAgent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/SearchAgent.h>
#include <model/bdi/BeliefSet.h>

using namespace std;

// ___________________________________________________________________________________
// Constructores y Destructor:
SearchAgent::SearchAgent(MainAgent* mainAgent, Map* theMap) :
	Agent(theMap), refMainAgent_(mainAgent) {
	setNameAgent(const_cast<char*>("SEARCH_AGENT"));
	initPointDistanceEXPL_ = -1;
	guideDirectionEXPL_ = ERROR_DIR;
	lastDirectionEXPL_ = ERROR_DIR;
	finalMovemnts_ = false;
	finalDirecton_ = ERROR_DIR;
	countLoopSteps_ = 0;
	m_lastLocalDirection = ERROR_DIR;
}
SearchAgent::~SearchAgent() {
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
Package* SearchAgent::readFIPAPackage(Package* p) {
	Package* answer;

	// Comprobamos que el paquete es de la conversación actual
	if (p->getIdComm() == getIdComm()) {
		// Comprobamos que el paquete va destinado al agente correcto
		if (p->getReceiver() == getNameAgent()) {
			switch (p->getType()) {
			case NOT_UNDERSTOOD:
				cout
					<< "NOT_UNDERSTOOD: recibido paquete cuyo contenido no es entendible"
					<< endl;
				break;
			case CONFIRM:
				cout << "CONFIRM: Confirmada la operación." << endl;
				break;
			case DIRECTION_SEARCH:
				//Realizar búsqueda dada esta dirección
				setNameAgent(const_cast<char*>(p->getContent() [0].c_str()));
				localDireccionalSearch(p->getContent().at(0));
				break;
			case GO_LOCATION:
				followRoute(p->getContent().at(0));
				setState(FOLLOWING_ROUTE);
				answer = new Package(getNameAgent(), p->getSender(), CONFIRM);
				break;
			case GO_SEARCHING_LOCATION:
				followRoute(p->getContent().at(0));
				setState(FOLLOWING_SEARCH_ROUTE);
				answer = new Package(getNameAgent(), p->getSender(), CONFIRM);
				break;
			case COME_BACK:
				followRoute(p -> getContent().at(0));
				answer = new Package (getNameAgent(), p -> getSender(), CONFIRM);
				setState(FOLLOWING_RET_ROUTE);
				break;
			default:
				cout << "SA No se entiende el tipo del paquete recibido."
					<< endl;
				break;
			}
		}
	}

	return answer;
}

void SearchAgent::localDireccionalSearch(string d) {
	initExplorationMove(m_position.first, m_position.second,
			static_cast<Direction>(strToDirectionEnum(d.c_str())));
	setState(SEARCHING);
}

void SearchAgent::actDependingOfState() {
	switch (getState()) {
	case SEARCHING:
		if (!explorationMove()) {
			setState(AVAILABLE);
			getRefMainAgent()->readFIPAPackage(
					new Package(getNameAgent(),
							getRefMainAgent()->getNameAgent(), COME_BACK, this));
		} else {
			sensor();
		}
		break;
	case SECOND_SEARCHING:
		cout << "COMENZANDO EXPLORACION SECUNDARIA" << endl;
		break;
	case FOLLOWING_ROUTE:
		cout << "Tam: " << getRoutes().size() << endl;

		if (!routedMove()) {
			setState(AVAILABLE);
			getRefMainAgent()->readFIPAPackage(
					new Package(getNameAgent(),
							getRefMainAgent()->getNameAgent(), ARRIVED_GOAL));
		} else {
			sensor();
		}
		break;
	case FOLLOWING_SEARCH_ROUTE:
		cout << "CAMINANDO AL PUNTO DE BUSQUEDA" << endl;

		if (!routedMove()) {
			setState(SECOND_SEARCHING);
			getRefMainAgent()->readFIPAPackage(
					new Package(getNameAgent(),
							getRefMainAgent()->getNameAgent(), ARRIVED_GOAL));
		} else {
			sensor();
		}
		break;
	case FOLLOWING_RET_ROUTE:
		cout << "Tam: " << getRoutes().size() << endl;
		if (!routedMove()) {
			setState(AVAILABLE);
			getRefMainAgent()->readFIPAPackage(
					new Package(getNameAgent(),
							getRefMainAgent()->getNameAgent(), ARRIVED_GOAL));
		} else {
			sensor();
		}
		break;
	default:
		break;
	}
}
void SearchAgent::followRoute(string route) {
	//cout << "SEGUIR LA RUTA: " << route << endl;
	vector<Direction> camino;
	int posIni = route.find("[");
	int posCorchFin = route.find("]");
	//cout << "Pos ini:" << posIni << " posFin: " << posCorchFin
	//	<< endl;
	route = route.substr(1, route.length());
	int posComa = 0;
	bool stop = false;
	string dirTemp;

	while (!stop) {
		posComa = route.find(",");

		if (posComa == -1) {
			stop = true;
			dirTemp = route.substr(0, route.length() - 1);
		} else {
			dirTemp = route.substr(0, posComa);
			route = route.substr(posComa + 1, route.length());
		}
		camino.push_back(strToDirectionEnum(dirTemp));
	}

	for (unsigned int i = 0; i < camino.size(); i++) {
		m_routes.push_back(camino[camino.size() - i]);
	}
}

void SearchAgent::initExplorationMove(int row, int col, Direction guideDir) {
	initPointEXPL_.first = row;
	initPointEXPL_.second = col;
	guideDirectionEXPL_ = guideDir;
	initPointDistanceEXPL_ = 1;
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:
vector<Direction>& SearchAgent::getRoutes() {
	return m_routes;
}
void SearchAgent::setRoutes(const vector<Direction>& routes) {
	m_routes = routes;
}
MainAgent* SearchAgent::getRefMainAgent() {
	return refMainAgent_;
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos privados:
bool SearchAgent::explorationMove() {
	bool result = false;
	bool outPreferedRoute = false;
	bool obstacleDetectec = false;
	bool outOfLimits = false;
	Direction directionAct = ERROR_DIR;
	Direction tempDir = ERROR_DIR;

	if (countLoopSteps_ >= 50) {
		return false;
	}

	// Realizar el primer paso.
	if (initPointDistanceEXPL_ == 1) {
		directionAct = ((Direction)(guideDirectionEXPL_ + 1));
		obstacleDetectec = !controledMove(directionAct);

		if (!obstacleDetectec) {
			lastDirectionEXPL_ = directionAct;
			lastMoveDirEXPL_ = directionAct;
			updateDistance(directionAct);
			result = true;
		}
	} else if (initPointDistanceEXPL_ != -1) {
		if (finalMovemnts_) {
			directionAct = calculateFinalDir(finalDirecton_);

			if (directionAct != ERROR_DIR) {
				if (controledMove(directionAct)) {
					updateDistance(directionAct);
					lastMoveDirEXPL_ = directionAct;
					result = true;
				}
			} else {
				cout << "FIN CAMINO CORRECTO" << endl;
			}
		} else {
			if (onLimits()) {
				if (onRoute()) {
					directionAct = calculateRouteDir();
				} else {
					directionAct = calculateOutRouteDir();
					outPreferedRoute = true;
				}
			} else {
				cout << "ERROR AGENTE FUERA DE LIMITES" << endl;
				directionAct = calculateReturnDir();
				outOfLimits = true;
			}

			if (directionAct != ERROR_DIR) {
				obstacleDetectec = !controledMove(directionAct);

				if (obstacleDetectec) {
					tempDir = calculateObstaclDir(directionAct);

					if (tempDir != ERROR_DIR) {
						directionAct = tempDir;
						controledMove(directionAct);
						updateDistance(directionAct);
						lastMoveDirEXPL_ = directionAct;
						result = true;


					} else {
						finalDirecton_ = directionAct;
						finalMovemnts_ = true;
						directionAct = calculateFinalDir(finalDirecton_);

						if (directionAct != ERROR_DIR) {
							if (controledMove(directionAct)) {
								updateDistance(directionAct);
								lastMoveDirEXPL_ = directionAct;
								result = true;
							}
						} else {
							cout << "ERROR FIN CAMINO" << endl;
						}
					}
				} else {
					updateDistance(directionAct);
					lastMoveDirEXPL_ = directionAct;
					result = true;
				}
			} else {
				cout << "ERROR, NO SE DEBE ACCEDER A ESTE PUNTO"
						<< endl;
			}
		}
	}

	return result;
}

bool SearchAgent::swipeMove(const Point& start, const Point& end) {
	bool hasMoved;
	hasMoved = false;
	Point nextPosition;

	if (m_lastLocalDirection == ERROR_DIR) {
		nextPosition = m_position;
		if (start.first > end.first) {
			if (start.second > end.second) {
				--nextPosition.second;
			} else {
				--nextPosition.second;
			}
		} else {
			if (start.second > end.second) {
				++nextPosition.second;
			} else {
				++nextPosition.second;
			}
		}
		if (refMainAgent_->getKnownMap()[nextPosition.first][nextPosition.second] &&
		    ((*refMap_)(nextPosition.first, nextPosition.second) & MASK_TERRAIN) == TERRAIN_GROUND
		   ) {
			hasMoved = true;
		}
	}
	return hasMoved;
}

Direction SearchAgent::calculateClockDirection(Direction theDirection,
		bool inverse) {
	Direction result = ERROR_DIR;

	if (inverse) {
		if (theDirection == NORTH) {
			result = NWEST;
		} else {
			result = ((Direction)(theDirection - 1));
		}
	} else {
		if (theDirection == NWEST) {
			result = NORTH;
		} else {
			result = ((Direction)(theDirection + 1));
		}
	}
	return result;
}
Direction SearchAgent::calculateInverseDirection(Direction theDirection) {
	Direction result = ERROR_DIR;
	result = calculateClockDirection(theDirection, false);
	result = calculateClockDirection(result, false);
	result = calculateClockDirection(result, false);
	result = calculateClockDirection(result, false);
	return result;
}
void SearchAgent::updateDistance(Direction theDirection) {
	switch (guideDirectionEXPL_) {
		case NORTH:
			if (theDirection == NORTH || theDirection == NEAST
					|| theDirection == NWEST) {
				++initPointDistanceEXPL_;
			} else if (theDirection == SOUTH || theDirection == SEAST
					|| theDirection == SWEST) {
				--initPointDistanceEXPL_;
			}
			break;
		case EAST:
			if (theDirection == EAST || theDirection == NEAST
					|| theDirection == SEAST) {
				++initPointDistanceEXPL_;
			} else if (theDirection == WEST || theDirection == SWEST
					|| theDirection == NWEST) {
				--initPointDistanceEXPL_;
			}
			break;
		case SOUTH:
			if (theDirection == SOUTH || theDirection == SEAST
					|| theDirection == SWEST) {
				++initPointDistanceEXPL_;
			} else if (theDirection == NORTH || theDirection == NEAST
					|| theDirection == NWEST) {
				--initPointDistanceEXPL_;
			}
			break;
		case WEST:
			if (theDirection == WEST || theDirection == NWEST
					|| theDirection == SWEST) {
				++initPointDistanceEXPL_;
			} else if (theDirection == EAST || theDirection == SEAST
					|| theDirection == NEAST) {
				--initPointDistanceEXPL_;
			}
			break;
		default:
			break;
	}
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

bool SearchAgent::onLimits() {
	const int DISTANCE = (initPointDistanceEXPL_ - 1);
	bool result = false;

	switch (guideDirectionEXPL_) {
		case NORTH:
		case SOUTH:
			if ((m_position.second >= (initPointEXPL_.second - DISTANCE))
					&& (m_position.second <= (initPointEXPL_.second + DISTANCE))) {
				result = true;
			}
			break;
		case EAST:
		case WEST:
			if ((m_position.first >= (initPointEXPL_.first - DISTANCE))
					&& (m_position.first <= (initPointEXPL_.first + DISTANCE))) {
				result = true;
			}
			break;
	}
	return result;
}
bool SearchAgent::onLineLimits() {
	const int DISTANCE = (initPointDistanceEXPL_ - 1);
	bool result = false;

	switch (guideDirectionEXPL_) {
		case NORTH:
		case SOUTH:
			if ((m_position.second == (initPointEXPL_.second - DISTANCE))
					|| (m_position.second == (initPointEXPL_.second + DISTANCE))) {
				result = true;
			}
			break;
		case EAST:
		case WEST:
			if ((m_position.first == (initPointEXPL_.first - DISTANCE))
					|| (m_position.first == (initPointEXPL_.first + DISTANCE))) {
				result = true;
			}
			break;
	}
	return result;
}
bool SearchAgent::onRoute() {
	const int DISTANCE = (initPointDistanceEXPL_ - 1);
	const int DIAMET_VIEW = 3;
	const int MOD_DISTANCE = DISTANCE / DIAMET_VIEW;
	const bool EVEN = ((MOD_DISTANCE % 2) == 0);
	bool result = false;

	if ((DISTANCE % DIAMET_VIEW) == 0) {
		result = true;
	} else if (onLineLimits()) {
		switch (guideDirectionEXPL_) {
			case NORTH:
				if (EVEN) {
					if (m_position.second > initPointEXPL_.second) {
						result = true;
					}
				} else if (m_position.second < initPointEXPL_.second) {
					result = true;
				}
				break;
			case EAST:
				if (EVEN) {
					if (m_position.first > initPointEXPL_.first) {
						result = true;
					}
				} else if (m_position.first < initPointEXPL_.first) {
					result = true;
				}
				break;
			case SOUTH:
				if (EVEN) {
					if (m_position.second < initPointEXPL_.second) {
						result = true;
					}
				} else if (m_position.second > initPointEXPL_.second) {
					result = true;
				}
				break;
			case WEST:
				if (EVEN) {
					if (m_position.first < initPointEXPL_.first) {
						result = true;
					}
				} else if (m_position.first > initPointEXPL_.first) {
					result = true;
				}
				break;
			default:
				break;
		}
	}
	return result;
}

Direction SearchAgent::calculateRouteDir() {
	const int DISTANCE = (initPointDistanceEXPL_ - 1);
	const int DIAMET_VIEW = 3;
	const bool ON_RECT = ((DISTANCE % DIAMET_VIEW) == 0);
	const bool EVEN = ((initPointDistanceEXPL_ % 2) == 0);
	Direction result = ERROR_DIR;

	// if (onRoute()) {...codigo siguiente...};

	switch (guideDirectionEXPL_) {
		case NORTH:
			if (ON_RECT) {
				if (m_position.second == initPointEXPL_.second + DISTANCE) {
					if (EVEN) {
						result = WEST;
					} else {
						result = NEAST;
					}
				} else if (m_position.second == initPointEXPL_.second - DISTANCE) {
					if (EVEN) {
						result = NWEST;
					} else {
						result = EAST;
					}
				} else {
					if (EVEN) {
						result = WEST;
					} else {
						result = EAST;
					}
				}
			} else {
				if (m_position.second > initPointEXPL_.second) {
					result = NEAST;
				} else {
					result = NWEST;
				}
			}
			break;
		case EAST:
			if (ON_RECT) {
				if (m_position.first == initPointEXPL_.first + DISTANCE) {
					if (EVEN) {
						result = NORTH;
					} else {
						result = SEAST;
					}
				} else if (m_position.first == initPointEXPL_.first - DISTANCE) {
					if (EVEN) {
						result = NEAST;
					} else {
						result = SOUTH;
					}
				} else {
					if (EVEN) {
						result = NORTH;
					} else {
						result = SOUTH;
					}
				}
			} else {
				if (m_position.first > initPointEXPL_.first) {
					result = SEAST;
				} else {
					result = NEAST;
				}
			}
			break;
		case SOUTH:
			if (ON_RECT) {
				if (m_position.second == initPointEXPL_.second + DISTANCE) {
					if (EVEN) {
						result = SEAST;
					} else {
						result = WEST;
					}
				} else if (m_position.second == initPointEXPL_.second - DISTANCE) {
					if (EVEN) {
						result = EAST;
					} else {
						result = SWEST;
					}
				} else {
					if (EVEN) {
						result = EAST;
					} else {
						result = WEST;
					}
				}
			} else {
				if (m_position.second > initPointEXPL_.second) {
					result = SEAST;
				} else {
					result = SWEST;
				}
			}
			break;
		case WEST:
			if (ON_RECT) {
				if (m_position.first == initPointEXPL_.first + DISTANCE) {
					if (EVEN) {
						result = SWEST;
					} else {
						result = NORTH;
					}
				} else if (m_position.first == initPointEXPL_.first - DISTANCE) {
					if (EVEN) {
						result = SOUTH;
					} else {
						result = NWEST;
					}
				} else {
					if (EVEN) {
						result = SOUTH;
					} else {
						result = NORTH;
					}
				}
			} else {
				if (m_position.first > initPointEXPL_.first) {
					result = SWEST;
				} else {
					result = NWEST;
				}
			}
			break;
		default:
			break;
	}
	return result;
}
Direction SearchAgent::calculateReturnDir() {
	Direction result = ERROR_DIR;

	if (!onLimits()) {
		result = calculateInverseDirection(lastMoveDirEXPL_);
	}

	return result;
}
Direction SearchAgent::calculateOutRouteDir() {
	const int DISTANCE = (initPointDistanceEXPL_ - 1);
	const int DIAMET_VIEW = 3;
	// Espacio Par
	const bool ON_EVEN = (((DISTANCE / DIAMET_VIEW) % 2) == 0);
	Direction result = ERROR_DIR;

	// if (!onRoute()) {...codigo siguiente...}

	switch (guideDirectionEXPL_) {
	case NORTH:
		if (ON_EVEN) {
			result = EAST;
		} else {
			result = WEST;
		}

		break;

	case EAST:
		if (ON_EVEN) {
			result = SOUTH;
		} else {
			result = NORTH;
		}

		break;

	case SOUTH:
		if (ON_EVEN) {
			result = WEST;
		} else {
			result = EAST;
		}

		break;

	case WEST:
		if (ON_EVEN) {
			result = NORTH;
		} else {
			result = SOUTH;
		}

		break;

	default:
		break;
	}

	return result;
}
Direction SearchAgent::calculateObstaclDir(Direction theDirection) {
	const Direction LAST_MOVE = lastMoveDirEXPL_;
	const bool ON_ROUTE = onRoute();
	Direction result = ERROR_DIR;
	Direction tmpDir;

	switch (guideDirectionEXPL_) {
	case NORTH:
		if (ON_ROUTE) {
			// Si estamos en ruta, realizar la busqueda de dos movimientos
			// posibles calculándolos usando el sentido de las agujas de un
			// reloj y su inverso segun la dirección de choque(theDirection).
			switch (theDirection) {
			case NWEST:
			case WEST:
				tmpDir = calculateClockDirection(theDirection, false);

				if (checkTerrain(tmpDir)) {
					result = tmpDir;
				} else {
					tmpDir = calculateClockDirection(tmpDir, false);

					if (checkTerrain(tmpDir)) {
						result = tmpDir;
					}
				}

				break;

			case NEAST:
			case EAST:
				tmpDir = calculateClockDirection(theDirection, true);

				if (checkTerrain(tmpDir)) {
					result = tmpDir;
				} else {
					tmpDir = calculateClockDirection(tmpDir, true);

					if (checkTerrain(tmpDir)) {
						result = tmpDir;
					}
				}

				break;
			}
		} else { // Si no estamos en ruta, realizar movimiento recto par/impar
			if (theDirection == EAST) {
				if (checkTerrain(NEAST)) {
					result = NEAST;
				} else if (checkTerrain(NORTH)) {
					result = NORTH;
				} else if (checkTerrain(NWEST)) {
					result = NWEST;
				}
			} else if (theDirection == WEST) {
				if (checkTerrain(NWEST)) {
					result = NWEST;
				} else if (checkTerrain(NORTH)) {
					result = NORTH;
				} else if (checkTerrain(NEAST)) {
					result = NEAST;
				}
			}
		}

		break;

	case EAST:
		if (ON_ROUTE) {
			// Si estamos en ruta, realizar la busqueda de dos movimientos
			// posibles calculándolos usando el sentido de las agujas de un
			// reloj y su inverso segun la dirección de choque(theDirection).
			switch (theDirection) {
			case NEAST:
			case NORTH:
				tmpDir = calculateClockDirection(theDirection, false);

				if (checkTerrain(tmpDir)) {
					result = tmpDir;
				} else {
					tmpDir = calculateClockDirection(tmpDir, false);

					if (checkTerrain(tmpDir)) {
						result = tmpDir;
					}
				}

				break;

			case SEAST:
			case SOUTH:
				tmpDir = calculateClockDirection(theDirection, true);

				if (checkTerrain(tmpDir)) {
					result = tmpDir;
				} else {
					tmpDir = calculateClockDirection(tmpDir, true);

					if (checkTerrain(tmpDir)) {
						result = tmpDir;
					}
				}

				break;
			}
		} else { // Si no estamos en ruta, realzar mov. rect. par/impar
			if (theDirection == SOUTH) {
				if (checkTerrain(SEAST)) {
					result = SEAST;
				} else if (checkTerrain(EAST)) {
					result = EAST;
				} else if (checkTerrain(NEAST)) {
					result = NEAST;
				}
			} else if (theDirection == NORTH) {
				if (checkTerrain(NEAST)) {
					result = NEAST;
				} else if (checkTerrain(EAST)) {
					result = EAST;
				} else if (checkTerrain(SEAST)) {
					result = SEAST;
				}
			}
		}

		break;

	case SOUTH:
		if (ON_ROUTE) {
			// Si estamos en ruta, realizar la busqueda de dos movimientos
			// posibles calculándolos usando el sentido de las agujas de un
			// reloj y su inverso segun la dirección de choque(theDirection).
			switch (theDirection) {
			case SEAST:
			case EAST:
				tmpDir = calculateClockDirection(theDirection, false);

				if (checkTerrain(tmpDir)) {
					result = tmpDir;
				} else {
					tmpDir = calculateClockDirection(tmpDir, false);

					if (checkTerrain(tmpDir)) {
						result = tmpDir;
					}
				}

				break;

			case SWEST:
			case WEST:
				tmpDir = calculateClockDirection(theDirection, true);

				if (checkTerrain(tmpDir)) {
					result = tmpDir;
				} else {
					tmpDir = calculateClockDirection(tmpDir, true);

					if (checkTerrain(tmpDir)) {
						result = tmpDir;
					}
				}

				break;
			}
		} else { // Si no estamos en ruta, realizar movimiento recto par/impar
			if (theDirection == EAST) {
				if (checkTerrain(SEAST)) {
					result = SEAST;
				} else if (checkTerrain(SOUTH)) {
					result = SOUTH;
				} else if (checkTerrain(SWEST)) {
					result = SWEST;
				}
			} else if (theDirection == WEST) {
				if (checkTerrain(SWEST)) {
					result = SWEST;
				} else if (checkTerrain(SOUTH)) {
					result = SOUTH;
				} else if (checkTerrain(SEAST)) {
					result = SEAST;
				}
			}
		}

		break;

	case WEST:
		if (ON_ROUTE) {
			// Si estamos en ruta, realizar la busqueda de dos movimientos
			// posibles calculándolos usando el sentido de las agujas de un
			// reloj y su inverso segun la dirección de choque(theDirection).
			switch (theDirection) {
			case NWEST:
			case NORTH:
				tmpDir = calculateClockDirection(theDirection, true);

				if (checkTerrain(tmpDir)) {
					result = tmpDir;
				} else {
					tmpDir = calculateClockDirection(tmpDir, true);

					if (checkTerrain(tmpDir)) {
						result = tmpDir;
					}
				}

				break;

			case SWEST:
			case SOUTH:
				tmpDir = calculateClockDirection(theDirection, false);

				if (checkTerrain(tmpDir)) {
					result = tmpDir;
				} else {
					tmpDir = calculateClockDirection(tmpDir, false);

					if (checkTerrain(tmpDir)) {
						result = tmpDir;
					}
				}

				break;
			}
		} else { // Si no estamos en ruta, realzar mov. rect. par/impar
			if (theDirection == SOUTH) {
				if (checkTerrain(SWEST)) {
					result = SWEST;
				} else if (checkTerrain(WEST)) {
					result = WEST;
				} else if (checkTerrain(NWEST)) {
					result = NWEST;
				}
			} else if (theDirection == NORTH) {
				if (checkTerrain(NWEST)) {
					result = NWEST;
				} else if (checkTerrain(WEST)) {
					result = WEST;
				} else if (checkTerrain(SWEST)) {
					result = SWEST;
				}
			}
		}

		break;

	default:
		break;
	}

	return result;
}

Direction SearchAgent::calculateFinalDir(Direction theDirection) {
	const int DISTANCE = (initPointDistanceEXPL_ - 1);
	Direction result = ERROR_DIR;

	switch (guideDirectionEXPL_) {
	case NORTH:
		if ((theDirection == WEST) || theDirection == NWEST) {
			if (checkTerrain(NEAST)) {
				result = NEAST;
				finalMovemnts_ = false;
			} else if (m_position.second <= initPointEXPL_.second + DISTANCE) {
				if (checkTerrain(EAST)) {
					result = EAST;
				} else if (checkTerrain(SEAST)) {
					result = SEAST;
				} else if (checkTerrain(SOUTH)) {
					result = SOUTH;
				}
			}
		} else if ((theDirection == EAST) || theDirection == NEAST) {
			if (checkTerrain(NWEST)) {
				result = NWEST;
				finalMovemnts_ = false;
			} else if (m_position.second >= initPointEXPL_.second - DISTANCE) {
				if (checkTerrain(WEST)) {
					result = WEST;
				} else if (checkTerrain(SWEST)) {
					result = SWEST;
				} else if (checkTerrain(SOUTH)) {
					result = SOUTH;
				}
			}
		} else if (theDirection == NORTH) {
			cout << "ERROR CALCULO DIR FINAL (NORTH)" << endl;
		} else if (theDirection == ERROR_DIR) {
			cout << "ERROR CALCULO DIR FINAL (ERROR_DIR)" << endl;
		} else {
			cout << "ERROR CALCULO DIR FINAL (OTROS)" << endl;
		}

		break;

	case EAST:
		if ((theDirection == NORTH) || theDirection == NEAST) {
			if (checkTerrain(SEAST)) {
				result = SEAST;
				finalMovemnts_ = false;
			} else if (m_position.first <= initPointEXPL_.first + DISTANCE) {
				if (checkTerrain(SOUTH)) {
					result = SOUTH;
				} else if (checkTerrain(SWEST)) {
					result = SWEST;
				} else if (checkTerrain(WEST)) {
					result = WEST;
				}
			}
		} else if ((theDirection == SOUTH) || theDirection == SEAST) {
			if (checkTerrain(NEAST)) {
				result = NEAST;
				finalMovemnts_ = false;
			} else if (m_position.first >= initPointEXPL_.first - DISTANCE) {
				if (checkTerrain(NORTH)) {
					result = NORTH;
				} else if (checkTerrain(NWEST)) {
					result = NWEST;
				} else if (checkTerrain(WEST)) {
					result = WEST;
				}
			}
		} else if (theDirection == EAST) {
			cout << "ERROR CALCULO DIR FINAL (EAST)" << endl;
		} else if (theDirection == ERROR_DIR) {
			cout << "ERROR CALCULO DIR FINAL (ERROR_DIR)" << endl;
		} else {
			cout << "ERROR CALCULO DIR FINAL (OTROS)" << endl;
		}

		break;

	case SOUTH:
		if ((theDirection == WEST) || theDirection == SWEST) {
			if (checkTerrain(SEAST)) {
				result = SEAST;
				finalMovemnts_ = false;
			} else if (m_position.second <= initPointEXPL_.second + DISTANCE) {
				if (checkTerrain(EAST)) {
					result = EAST;
				} else if (checkTerrain(NEAST)) {
					result = NEAST;
				} else if (checkTerrain(NORTH)) {
					result = NORTH;
				}
			}
		} else if ((theDirection == EAST) || theDirection == SEAST) {
			if (checkTerrain(SWEST)) {
				result = SWEST;
				finalMovemnts_ = false;
			} else if (m_position.second >= initPointEXPL_.second - DISTANCE) {
				if (checkTerrain(WEST)) {
					result = WEST;
				} else if (checkTerrain(NWEST)) {
					result = NWEST;
				} else if (checkTerrain(NORTH)) {
					result = NORTH;
				}
			}
		} else if (theDirection == SOUTH) {
			cout << "ERROR CALCULO DIR FINAL (SOUTH)" << endl;
		} else if (theDirection == ERROR_DIR) {
			cout << "ERROR CALCULO DIR FINAL (ERROR_DIR)" << endl;
		} else {
			cout << "ERROR CALCULO DIR FINAL (OTROS)" << endl;
		}

		break;

	case WEST:
		if ((theDirection == NORTH) || theDirection == NWEST) {
			if (checkTerrain(SWEST)) {
				result = SWEST;
				finalMovemnts_ = false;
			} else if (m_position.first <= initPointEXPL_.first + DISTANCE) {
				if (checkTerrain(SOUTH)) {
					result = SOUTH;
				} else if (checkTerrain(SEAST)) {
					result = SEAST;
				} else if (checkTerrain(EAST)) {
					result = EAST;
				}
			}
		} else if ((theDirection == SOUTH) || theDirection == SWEST) {
			if (checkTerrain(NWEST)) {
				result = NWEST;
				finalMovemnts_ = false;
			} else if (m_position.first >= initPointEXPL_.first - DISTANCE) {
				if (checkTerrain(NORTH)) {
					result = NORTH;
				} else if (checkTerrain(NEAST)) {
					result = NEAST;
				} else if (checkTerrain(EAST)) {
					result = EAST;
				}
			}
		} else if (theDirection == WEST) {
			cout << "ERROR CALCULO DIR FINAL (WEST)" << endl;
		} else if (theDirection == ERROR_DIR) {
			cout << "ERROR CALCULO DIR FINAL (ERROR_DIR)" << endl;
		} else {
			cout << "ERROR CALCULO DIR FINAL (OTROS)" << endl;
		}

		break;

	default:
		break;
	}

	return result;
}

void SearchAgent::sensor() {
	const int width = 3;
	int switchedCells = 0;

	++countLoopSteps_;

	for (int32_t i = m_position.first - width; i <= m_position.first + width;
	     ++i) {
		for (int32_t j = m_position.second - width;
		     j <= m_position.second + width; ++j) {
			if ((i >= 0 && i < MAP_WIDTH) && (j >= 0 && j < MAP_WIDTH)) {
				if (sqrt(
				            pow((i - m_position.first), 2)
				            + pow((j - m_position.second), 2))
				    <= (width * 1.0)) {
					if (!refMainAgent_->knownMapPosition(i, j)) {
						countLoopSteps_ = 0;
						refMainAgent_->setKnownMapPosition(i, j, true);
						++switchedCells;
						refMainAgent_->updatedKnownMap();
					}
				}
			}
		}
	}

	refMainAgent_->checkedCells(switchedCells);
}

