/*
 * SearchAgent.cpp
 *
 *  Created on: 12/11/2013
 *      Author: manwe
 */

#include <model/agents/SearchAgent.h>
#include <model/bdi/BeliefSet.h>

#include <cstring>
#include <cmath>

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
         if (!explorationMove()) {
            setState(AVAILABLE);
         } else {
             sensor();
         }
      break;
      case FOLLOWING_ROUTE:
         std::cout << "Tam: " << getRoutes().size() << std::endl;
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
    std::cout << "SEGUIR LA RUTA: " << route << std::endl;
    std::vector<Direction> camino;
	int posIni = route.find("[");
	int posCorchFin = route.find("]");
    std::cout << "Pos ini:" << posIni << " posFin: " << posCorchFin << std::endl;
	route = route.substr(1, route.length());
	int posComa = 0;
	bool stop = false;
    std::string dirTemp;
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
void SearchAgent::initExplorationMove(int row, int col, Direction guideDir) {
   initPointEXPL_ .first = row;
   initPointEXPL_.second = col;
   guideDirectionEXPL_ = guideDir;
   initPointDistanceEXPL_ = 1;
}
// FIN -------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ___________________________________________________________________________________
// Manejadores públicos:
std::vector<Direction>& SearchAgent::getRoutes() {
   return m_routes;
}
void SearchAgent::setRoutes(const std::vector<Direction>& routes) {
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
   Direction directionAct = ERROR_DIR;

   // Realizar el primer paso.
   if (initPointDistanceEXPL_ == 1) {
      directionAct = ((Direction) (guideDirectionEXPL_ + 1));
      obstacleDetectec = !controledMove(directionAct);
      if (!obstacleDetectec) {
        lastDirectionEXPL_ = directionAct;
        lastMoveDirEXPL_ = directionAct;
        updateDistance(directionAct);
        result = true;
      }
   } else if (initPointDistanceEXPL_ != -1) {
//      calculateExplorationLimits(limitRightSup, limitLeftInf);
      std::cout << "PASO DE LA EXPLORACION" << std::endl;
      directionAct = calculatePreferedDirection();
      if (directionAct == ERROR_DIR) {
         directionAct = calculateFreeDirection(false);
         outPreferedRoute = true;
      }

      if (directionAct != ERROR_DIR) {
         obstacleDetectec = !controledMove(directionAct);
         if (obstacleDetectec) {
            directionAct = calculateFreeDirection(true);
            if (directionAct != ERROR_DIR) {
               obstacleDetectec = !controledMove(directionAct);
            }
         }
         if (!obstacleDetectec) {
            if (!outPreferedRoute) {
               lastDirectionEXPL_ = directionAct;
            }
            lastMoveDirEXPL_ = directionAct;
            updateDistance(directionAct);
            result = true;
         }
      }
   }


   return result;
}

Direction SearchAgent::calculatePreferedDirection() {
   Direction result = ERROR_DIR;
   Direction tmpDirR = calculateRectilinearDirection ();
   Direction tmpDirA = calculateAngularDirection ();

   std::cout << "RECT DIR: " << tmpDirR << std::endl;
   std::cout << "ANG DIR: " << tmpDirA << std::endl;

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
         if (m_position.second == (initPointEXPL_.second - DISTANCE)) {
            result = NWEST;
         } else if (m_position.second == (initPointEXPL_.second + DISTANCE)){
            result = NEAST;
         }
         break;
      case EAST:
         if (m_position.first == (initPointEXPL_.first - DISTANCE)) {
            result = SEAST;
         } else if (m_position.first == (initPointEXPL_.first+ DISTANCE)){
            result = NEAST;
         }
         break;
      case SOUTH:
         if (m_position.second == (initPointEXPL_.second + DISTANCE)) {
            result = SWEST;
         } else if (m_position.second == (initPointEXPL_.second - DISTANCE)){
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
   const int DISTANCE = (initPointDistanceEXPL_ - 1);
   Direction result = ERROR_DIR;
   if (((initPointDistanceEXPL_ - 1) % 3) == 0
         && (initPointDistanceEXPL_ != 2)) {
      switch (guideDirectionEXPL_) {
         case NORTH:
            if ((m_position.second >= (initPointEXPL_.second - DISTANCE))
                  && (m_position.second <= (initPointEXPL_.second + DISTANCE))) {
               if ((initPointDistanceEXPL_ % 2) == 0) {
                  result = WEST;
               } else {
                  result = EAST;
               }
            } else if (m_position.second < (initPointEXPL_.second - DISTANCE)) {
               result = EAST;
            } else if ((m_position.second > (initPointEXPL_.second + DISTANCE))) {
               result = WEST;
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
   if (result == calculateInverseDirection(lastMoveDirEXPL_)) {
      result = ERROR_DIR;
   }
   return result;
}

Direction SearchAgent::calculateFreeDirection(bool obstacle) {
   const int DISTANCE = (initPointDistanceEXPL_ - 1);
   Direction result = ERROR_DIR;
   Direction tmpDir;
   Direction tmpDir2;
   switch (guideDirectionEXPL_) {
      case NORTH:
         if ((m_position.second >= (initPointEXPL_.second - DISTANCE))
                           && (m_position.second <= (initPointEXPL_.second + DISTANCE))) {
            if (lastDirectionEXPL_ == WEST || lastDirectionEXPL_ == NWEST) {
               tmpDir = WEST;
               tmpDir2 = EAST;
               if (lastDirectionEXPL_ == NWEST) {
                  tmpDir2 = SEAST;
               }

               do {
                  //tmpDir = calculateClockDirection (tmpDir, false);
                  if (!checkTerrain(tmpDir)) {
                    tmpDir = calculateClockDirection (tmpDir, false);
                  }
                  if (!obstacle && tmpDir == calculateInverseDirection(lastMoveDirEXPL_)) {
                     tmpDir = calculateClockDirection (tmpDir, false);
                  }

               } while ((tmpDir != tmpDir2) && !(checkTerrain(tmpDir)));
            } else {
               tmpDir = EAST;
               tmpDir2 = WEST;
               if (lastDirectionEXPL_ == NEAST) {
                  tmpDir2 = SWEST;
               }
               do {
                  //tmpDir = calculateClockDirection (tmpDir, true);
                  if (!checkTerrain(tmpDir)) {
                    tmpDir = calculateClockDirection (tmpDir, true);
                  }
                  if (!obstacle && tmpDir == calculateInverseDirection(lastMoveDirEXPL_)) {
                     tmpDir = calculateClockDirection (tmpDir, true);
                  }
               } while ((tmpDir != tmpDir2) && !(checkTerrain(tmpDir)));
            }
         }else if (m_position.second < (initPointEXPL_.second - DISTANCE)) {
             result = EAST;
         } else if ((m_position.second > (initPointEXPL_.second + DISTANCE))) {
            result = WEST;
         }
         break;
      case EAST:
         if (lastDirectionEXPL_ == NORTH || lastDirectionEXPL_ == NEAST) {
            tmpDir = NORTH;
            tmpDir2 = SOUTH;
            if (lastDirectionEXPL_ == NEAST) {
               tmpDir2 = SWEST;
            }
            do {
               tmpDir = calculateClockDirection (tmpDir, false);
               if (!obstacle && tmpDir == calculateInverseDirection(lastMoveDirEXPL_)) {
                  tmpDir = calculateClockDirection (tmpDir, false);
               }
            } while ((tmpDir != tmpDir2) && !(checkTerrain(tmpDir)));
         } else {
            tmpDir = SOUTH;
            tmpDir2 = NORTH;
            if (lastDirectionEXPL_ == SEAST) {
               tmpDir2 = NWEST;
            }
            do {
               tmpDir = calculateClockDirection (tmpDir, true);
               if (!obstacle && tmpDir == calculateInverseDirection(lastMoveDirEXPL_)) {
                  tmpDir = calculateClockDirection (tmpDir, false);
               }
            } while ((tmpDir != tmpDir2) && !(checkTerrain(tmpDir)));
         }
         break;
      case SOUTH:
          if (lastDirectionEXPL_ == EAST || lastDirectionEXPL_ == SEAST) {
             tmpDir = EAST;
             tmpDir2 = WEST;
             if (lastDirectionEXPL_ == SEAST) {
                tmpDir2 = NWEST;
             }
             do {
                tmpDir = calculateClockDirection (tmpDir, false);
                if (!obstacle && tmpDir == calculateInverseDirection(lastMoveDirEXPL_)) {
                   tmpDir = calculateClockDirection (tmpDir, false);
                }
             } while ((tmpDir != tmpDir2) && !(checkTerrain(tmpDir)));
          } else {
             tmpDir = WEST;
             tmpDir2 = EAST;
             if (lastDirectionEXPL_ == SWEST) {
                tmpDir2 = NEAST;
             }
             do {
                tmpDir = calculateClockDirection (tmpDir, true);
                if (!obstacle && tmpDir == calculateInverseDirection(lastMoveDirEXPL_)) {
                   tmpDir = calculateClockDirection (tmpDir, false);
                }
             }while ((tmpDir != tmpDir2) && !(checkTerrain(tmpDir)));
          }
         break;
      case WEST:
          if (lastDirectionEXPL_ == SOUTH || lastDirectionEXPL_ == SWEST) {
             tmpDir = SOUTH;
             tmpDir2 = NORTH;
             if (lastDirectionEXPL_ == SWEST) {
                tmpDir2 = NEAST;
             }
             while ((tmpDir != tmpDir2) && !(checkTerrain(tmpDir))) {
                tmpDir = calculateClockDirection (tmpDir, false);
                if (!obstacle && tmpDir == calculateInverseDirection(lastMoveDirEXPL_)) {
                   tmpDir = calculateClockDirection (tmpDir, false);
                }
             }
          } else {
             tmpDir = NORTH;
             tmpDir2 = SOUTH;
             if (lastDirectionEXPL_ == NWEST) {
                tmpDir2 = SEAST;
             }
             while ((tmpDir != tmpDir2) && !(checkTerrain(tmpDir))) {
                tmpDir = calculateClockDirection (tmpDir, true);
                if (!obstacle && tmpDir == calculateInverseDirection(lastMoveDirEXPL_)) {
                   tmpDir = calculateClockDirection (tmpDir, false);
                }
             }
          }
         break;
      default:
         break;
   }
   if (checkTerrain(tmpDir)) {
      result = tmpDir;
   }
   std::cout << "FREE DIR: " << result << std::endl;
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
        if (theDirection == NORTH || theDirection == NEAST || theDirection == NWEST) {
           initPointDistanceEXPL_++;
        } else if (theDirection == SOUTH || theDirection == SEAST || theDirection == SWEST) {
           initPointDistanceEXPL_--;
        }
         break;
      case EAST:
         if (theDirection == EAST || theDirection == NEAST || theDirection == SEAST) {
            initPointDistanceEXPL_++;
         } else if (theDirection == WEST || theDirection == SWEST || theDirection == NWEST) {
             initPointDistanceEXPL_--;
          }
         break;
      case SOUTH:
          if (theDirection == SOUTH || theDirection == SEAST || theDirection == SWEST) {
             initPointDistanceEXPL_++;
          } else if (theDirection == NORTH || theDirection == NEAST || theDirection == NWEST) {
              initPointDistanceEXPL_--;
           }
         break;
      case WEST:
          if (theDirection == WEST || theDirection == NWEST || theDirection == SWEST) {
             initPointDistanceEXPL_++;
          } else if (theDirection == EAST || theDirection == SEAST || theDirection == NEAST) {
              initPointDistanceEXPL_--;
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
      case NORTH: case SOUTH:
         if ((m_position.second >= (initPointEXPL_.second - DISTANCE))
            && (m_position.second <= (initPointEXPL_.second + DISTANCE))) {
            result = true;
         }
         break;
      case EAST: case WEST:
         if ((m_position.first >= (initPointEXPL_.first - DISTANCE))
            && (m_position.first <= (initPointEXPL_.first+ DISTANCE))) {
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
      case NORTH: case SOUTH:
         if ((m_position.second == (initPointEXPL_.second - DISTANCE))
            || (m_position.second == (initPointEXPL_.second + DISTANCE))) {
            result = true;
         }
         break;
      case EAST: case WEST:
         if ((m_position.first == (initPointEXPL_.first - DISTANCE))
            || (m_position.first == (initPointEXPL_.first+ DISTANCE))) {
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
bool result = false;


   if ((DISTANCE % DIAMET_VIEW) == 0) {
      result = true;
   } else if (onLineLimits()){
      switch (guideDirectionEXPL_) {
         case NORTH:
            if ((MOD_DISTANCE % 2) == 0 ) {
               if (m_position.second > initPointEXPL_.second) {
                  result = true;
               }
            } else if (m_position.second < initPointEXPL_.second) {
               result = true;
            }
            break;
         case EAST:

            break;
         case SOUTH:

            break;
         case WEST:

            break;
         default:
            break;
      }
   }

   return result;
}

Direction SearchAgent::calculateRouteDir() {
   Direction result = ERROR_DIR;

   switch (guideDirectionEXPL_) {
      case NORTH:

         break;
      case EAST:

         break;
      case SOUTH:

         break;
      case WEST:

         break;
      default:
         break;
   }

   return result;
}
Direction SearchAgent::calculateReturnDir() {
   Direction result = ERROR_DIR;

   switch (guideDirectionEXPL_) {
      case NORTH:

         break;
      case EAST:

         break;
      case SOUTH:

         break;
      case WEST:

         break;
      default:
         break;
   }

   return result;
}
Direction SearchAgent::calculateObstaclDir() {
   Direction result = ERROR_DIR;

   switch (guideDirectionEXPL_) {
      case NORTH:

         break;
      case EAST:

         break;
      case SOUTH:

         break;
      case WEST:

         break;
      default:
         break;
   }

   return result;
}

int SearchAgent::sensor() {
    int switchedCells = 0;
    for (uint32_t i = m_position.first - 4; i < m_position.first + 4; ++i) {
        for (uint32_t j = m_position.second - 4; j < m_position.second + 4; ++j) {
            if (std::abs(sqrt(pow(i, 2) + pow(j, 2))
                - sqrt(pow(m_position.first, 2)
                + pow(m_position.second, 2))) <= 4) {
                if(!refMainAgent_->knownMapPosition(i, j)) {
                    refMainAgent_->setKnownMapPosition(i, j, true);
                    ++switchedCells;
                }
            }
        }
    }
    return switchedCells;
}
