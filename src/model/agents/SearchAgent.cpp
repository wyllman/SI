/*
 * SearchAgent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/SearchAgent.h>

// ___________________________________________________________________________________
// Constructores y Destructor:
SearchAgent::SearchAgent(MainAgent* mainAgent, Map* theMap): Agent (theMap), refMainAgent_ (mainAgent) {
   setNameAgent(const_cast<char*>("SEARCH_AGENT"));
   initPointDistanceEXPL_ = -1;
   guideDirectionEXPL_ = ERROR_DIR;
   lastDirectionEXPL_ = ERROR_DIR;
}
SearchAgent::~SearchAgent() {
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Métodos públicos:
Package* SearchAgent::readFIPAPackage (Package* p) {
	Package* answer = new Package (getNameAgent(), p -> getSender(), NOT_UNDERSTOOD);
	// Comprobamos que el paquete es de la conversación actual
	if (p -> getIdComm() == getIdComm()) {
		// Comprobamos que el paquete va destinado al agente correcto
		if (p -> getReceiver() == getNameAgent()) {
			switch (p -> getType()) {
			case NOT_UNDERSTOOD:
				std::cout << "NOT_UNDERSTOOD: recibido paquete cuyo contenido no es entendible" << std::endl;
				return NULL;
				break;
			case CONFIRM:
				std::cout << "CONFIRM: Confirmada la operación." << std::endl;
				return NULL;
				break;
			case DIRECTION_SEARCH:
				//Realizar búsqueda dada esta dirección
				localDireccionalSearch(p -> getContent().at(0));
				break;
			case GO_LOCATION:
				followRoute(p -> getContent().at(0));
				setState(FOLLOWING_ROUTE);
				break;
			default:
				std::cout << "No se entiende el tipo del paquete recibido." << std::endl;
			}
		}
	}
	return answer;
}

void SearchAgent::localDireccionalSearch (std::string  d) {
	switch (atoi(d.c_str())) {
	case NORTH:
		std::cout << "Emprender búsqueda hacial el norte" << std::endl;
		break;
	case SOUTH:
		std::cout << "Emprender búsqueda hacial el sur" << std::endl;
		break;
	case EAST:
		std::cout << "Emprender búsqueda hacial el este" << std::endl;
		break;
	case WEST:
		std::cout << "Emprender búsqueda hacial el oeste" << std::endl;
		break;
	case NEAST:
		std::cout << "Emprender búsqueda hacial el noreste" << std::endl;
		break;
	case NWEST:
		std::cout << "Emprender búsqueda hacial el noroeste" << std::endl;
		break;
	case SEAST:
		std::cout << "Emprender búsqueda hacial el sureste" << std::endl;
		break;
	case SWEST:
		std::cout << "Emprender búsqueda hacial el suroeste" << std::endl;
		break;
	}
}


void SearchAgent::actDependingOfState () {
   switch (getState()) {
      case SEARCHING:

      break;
      case FOLLOWING_ROUTE:
         cout << "Tam: " << getRoutes().size() << endl;
         if (!routedMove()) {
            setState(AVAILABLE);
            getRefMainAgent() -> readFIPAPackage(new Package(getNameAgent(), getRefMainAgent() -> getNameAgent(), ARRIVED_GOAL));
         }
         break;
      default:
         break;
   }
}
void SearchAgent::followRoute(std::string route) {
	cout << "SEGUIR LA RUTA: " << route << endl;
	vector<Direction> camino;
	int posIni = route.find("[");
	int posCorchFin = route.find("]");
	cout << "Pos ini:" << posIni << " posFin: " << posCorchFin << endl;
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

		camino.push_back(translateRoute(dirTemp));

	}
	for (unsigned int i = 0; i < camino.size(); i++) {
		m_routes.push_back(camino[camino.size() - 1]);
	}
}

Direction SearchAgent::translateRoute (std::string dir) {
   if (strcmp(dir.c_str(), "NORTH") == 0) {
      return NORTH;
   } else if (strcmp(dir.c_str(), "SOUTH") == 0) {
      return SOUTH;
   } else if (strcmp(dir.c_str(), "EAST") == 0) {
      return EAST;
   } else if (strcmp(dir.c_str(), "WEST") == 0) {
      return WEST;
   } else if (strcmp(dir.c_str(), "NEAST") == 0) {
      return NEAST;
   } else if (strcmp(dir.c_str(), "NWEST") == 0) {
      return NWEST;
   } else if (strcmp(dir.c_str(), "SEAST") == 0) {
      return SEAST;
   } else if (strcmp(dir.c_str(), "SWEST") == 0) {
      return SWEST;
   }
}
void SearchAgent::initExplorationMove(Point initPos, Direction guideDir) {
   initPointEXPL_ = initPos;
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
   int limitRightSup = 0, limitLeftInf = 0;
   bool obstacleDetectec = false;
   Direction directionAct;
   // Realizar el primer paso.
   if (initPointDistanceEXPL_ == 1) {
      directionAct = ((Direction) (guideDirectionEXPL_ + 1));
   } else {
//      calculateExplorationLimits(limitRightSup, limitLeftInf);
      // TODO: Calcular la dirección preferente actual
      // TODO: Mover en la dirección preferente
      directionAct = calculatePreferedDirection();
      if (directionAct == ERROR_DIR) {
         directionAct = calculateFreeDirection();
      }

   }

   // TODO: Si (obstaclDetectec) calcular nueva direccion preferente
   return result;
}
void SearchAgent::calculateExplorationLimits(int& limRS, int& limLI) {
   if (guideDirectionEXPL_ == NORTH || guideDirectionEXPL_ == SOUTH) {
      limRS = initPointEXPL_.first + (initPointDistanceEXPL_ - 1);
      limLI = initPointEXPL_.first - (initPointDistanceEXPL_ - 1);
   } else {
      limRS = initPointEXPL_.second + (initPointDistanceEXPL_ - 1);
      limLI = initPointEXPL_.second - (initPointDistanceEXPL_ - 1);
   }
}
Direction SearchAgent::calculatePreferedDirection() {
   Direction result = ERROR_DIR;
   Direction tmpDirR = calculateRectilinearDirection ();
   Direction tmpDirA = calculateAngularDirection ();

   if ((tmpDirR == ERROR_DIR) && (tmpDirA == ERROR_DIR)) {
      return result;
   } else if (tmpDirR == ERROR_DIR) {
      result = tmpDirA;
   } else if (tmpDirA == ERROR_DIR) {
      result = tmpDirR;
   } else { // (tmpDirR != ERROR_DIR) && (tmpDirA != ERROR_DIR)
      if (lastDirectionEXPL_ == tmpDirR) {
         result = tmpDirA;
      } else {
         result = tmpDirR;
      }
   }
   return result;
}
Direction SearchAgent::calculateAngularDirection() {
   const int DISTANCE = (initPointDistanceEXPL_ - 1);
   Direction result = ERROR_DIR;
   switch (guideDirectionEXPL_) {
      case NORTH:
         if (m_position.first == (initPointEXPL_.first - DISTANCE)) {
            result = NWEST;
         } else if (m_position.first == (initPointEXPL_.first + DISTANCE)){
            result = NEAST;
         }
         break;
      case EAST:
         if (m_position.second == (initPointEXPL_.second - DISTANCE)) {
            result = SEAST;
         } else if (m_position.second == (initPointEXPL_.second + DISTANCE)){
            result = NEAST;
         }
         break;
      case SOUTH:
         if (m_position.first == (initPointEXPL_.first + DISTANCE)) {
            result = SWEST;
         } else if (m_position.first == (initPointEXPL_.first - DISTANCE)){
            result = SEAST;
         }
         break;
      case WEST:
         if (m_position.first == (initPointEXPL_.first - DISTANCE)) {
            result = SWEST;
         } else if (m_position.first == (initPointEXPL_.first + DISTANCE)){
            result = NWEST;
         }
         break;
      default:
         break;
   }
   return result;
}
Direction SearchAgent::calculateRectilinearDirection() {
   Direction result = ERROR_DIR;
   if ((initPointDistanceEXPL_ % 3) == 0) {
      switch (guideDirectionEXPL_) {
         case NORTH:
            if ((initPointDistanceEXPL_ % 2) == 0) {
               result = WEST;
            } else {
               result = EAST;
            }
            break;
         case EAST:
             if ((initPointDistanceEXPL_ % 2) == 0) {
                result = NORTH;
             } else {
                result = SOUTH;
             }
            break;
         case SOUTH:
             if ((initPointDistanceEXPL_ % 2) == 0) {
                result = EAST;
             } else {
                result = WEST;
             }
            break;
         case WEST:
             if ((initPointDistanceEXPL_ % 2) == 0) {
                result = SOUTH;
             } else {
                result = NORTH;
             }
            break;
         default:
            break;
      }
   }
   return result;
}

Direction SearchAgent::calculateFreeDirection() {
   Direction result = ERROR_DIR;
   Direction tmpDir;
   switch (guideDirectionEXPL_) {
      case NORTH:
         if (lastDirectionEXPL_ == WEST || lastDirectionEXPL_ == NWEST) {
            tmpDir = WEST;
            while ((tmpDir != EAST) && !(checkTerrain(tmpDir))) {
               tmpDir = calculateClockDirection (tmpDir, false);
            }
         } else {
            tmpDir = EAST;
            while ((tmpDir != WEST) && !(checkTerrain(tmpDir))) {
               tmpDir = calculateClockDirection (tmpDir, true);
            }
         }
         break;
      case EAST:
         if (lastDirectionEXPL_ == NORTH || lastDirectionEXPL_ == NEAST) {
            tmpDir = NORTH;
            while ((tmpDir != SOUTH) && !(checkTerrain(tmpDir))) {
               tmpDir = calculateClockDirection (tmpDir, false);
            }
         } else {
            tmpDir = SOUTH;
            while ((tmpDir != NORTH) && !(checkTerrain(tmpDir))) {
               tmpDir = calculateClockDirection (tmpDir, true);
            }
         }
         break;
      case SOUTH:
          if (lastDirectionEXPL_ == EAST || lastDirectionEXPL_ == SEAST) {
             tmpDir = EAST;
             while ((tmpDir != WEST) && !(checkTerrain(tmpDir))) {
                tmpDir = calculateClockDirection (tmpDir, false);
             }
          } else {
             tmpDir = WEST;
             while ((tmpDir != EAST) && !(checkTerrain(tmpDir))) {
                tmpDir = calculateClockDirection (tmpDir, true);
             }
          }
         break;
      case WEST:
          if (lastDirectionEXPL_ == SOUTH || lastDirectionEXPL_ == SWEST) {
             tmpDir = SOUTH;
             while ((tmpDir != NORTH) && !(checkTerrain(tmpDir))) {
                tmpDir = calculateClockDirection (tmpDir, false);
             }
          } else {
             tmpDir = NORTH;
             while ((tmpDir != SOUTH) && !(checkTerrain(tmpDir))) {
                tmpDir = calculateClockDirection (tmpDir, true);
             }
          }
         break;
      default:
         break;
   }
   if (checkTerrain(tmpDir)) {
      result = tmpDir;
   }
   return result;
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
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


