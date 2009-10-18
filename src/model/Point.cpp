#include "Point.h"
#include "Position.h"
/**
 * Constructors/Destructors
 */
CCP::Point::Point ( ):_pos(Position(0.0,0.0)), _demand(0.0){

}
CCP::Point::Point (double x, double y, double demand):_pos(Position( x,y)), _demand(demand){
  
}

/**
 * Methods
 */

