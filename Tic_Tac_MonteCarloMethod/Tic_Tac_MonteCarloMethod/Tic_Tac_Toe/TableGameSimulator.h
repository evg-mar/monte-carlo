#ifndef __TABLE_GAME_SIMULATOR__
#define __TABLE_GAME_SIMULATOR__

#include "TableHolder.h"
#include <string>


class TableGameSimulator : public TableHolder
{
public:
	// Constructor
	TableGameSimulator( const std::string game_name = "", const unsigned    dimension = 3);

	// Copy Constructor
	TableGameSimulator( const TableGameSimulator & rhs);

	// Virtual destructor
	virtual ~TableGameSimulator() {};

	TableValues RandomGameSimulation( const TableValues table_val );
	
/*  NOT NEEDED FOR THE MOMENT
	TableGameSimulator & operator=( const TableGameSimulator & rhs );
*/
	
	

private:	
	bool CheckPlayerWinner( const unsigned position, const TableValues table_val );

	unsigned GetRandomPosition( const unsigned modul ) const;
	
	unsigned GetActualPosition( const unsigned relative_pos );
};

#endif

