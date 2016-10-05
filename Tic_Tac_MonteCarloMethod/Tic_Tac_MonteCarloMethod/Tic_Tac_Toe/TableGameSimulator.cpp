//Include own header
#include "TableGameSimulator.h"


//STL headers includes
#include <algorithm>

using namespace std;

#include <ctime>

TableGameSimulator::TableGameSimulator( const string game_name, const unsigned dimension ):
TableHolder( game_name, dimension )
{ }

// Copy Constructor
TableGameSimulator::TableGameSimulator( const TableGameSimulator & rhs):
TableHolder( rhs.m_GameName, rhs.m_TableDim )
{ }

/* NOT NEEDED FOR THE MOMENT
/// Assignement operator	
TableGameSimulator & TableGameSimulator::operator=( const TableGameSimulator & rhs )
{
	......
	return *this;
}
*/

/// Inserts the table_val in the table for the current player
/// if the corresponding place is empty.
/// Then checks if the current player winns and returns 
/// TRUE if he does and FALSE otherwise.
bool TableGameSimulator::CheckPlayerWinner(  const unsigned		actual_position, 
												const TableValues	table_val )	
{
	const unsigned line = GetLine( actual_position );
	const unsigned col  = GetColumn( actual_position );

	if( CheckLineWinner( line, col ) )
	{
		return true;
	}
 	if( CheckColumnWinner( line, col ) )
	{
		return true;
	}
	if( CheckRightDiagonalWinner( line, col ) && line == col )
	{
		return true;
	}
	if( CheckLeftDiagonalWinner( line, col ) && line == (m_TableDim - col) )
	{
		return true;
	}
	
	return false;
}

unsigned TableGameSimulator::GetRandomPosition( const unsigned modul ) const
{
	const unsigned position_rand = rand() % ( modul );

	time_t now = time( 0 ); // as size_t -> similar to unsigned long
	// The position produced will depend on the current time
	const unsigned time_rand = static_cast<unsigned>( now % modul  );
	
	return (position_rand + time_rand) % ( modul );
}

unsigned TableGameSimulator::GetActualPosition( const unsigned relative_pos ) 
{
	size_t cnt_pos = 0;

	for( set<unsigned>::const_iterator it =  m_FreePositions.begin(); it != m_FreePositions.end(); ++it )
	{
		if( cnt_pos == relative_pos )
		{	
			return *it;
		}

		cnt_pos++;
	}// for
				

	m_OstrFile << "# WARNING: relative position in the free positions set is too big" << endl;
		
	return 0;
}

// Game simulation starting by the player table_value
/// Returns TRUE if some of the players wins
/// Otherwise, returns FALSE
TableValues TableGameSimulator::RandomGameSimulation( const TableValues table_value )
{		
	TableValues table_val = table_value;

	while( !IsTableFull() )
	{
		const unsigned relative_position = GetRandomPosition( m_FreePositions.size() );
		const unsigned actual_position   = GetActualPosition( relative_position );
		// actual_position is an empty position in the table!
		if( InsertValue( actual_position, table_val ) )
		{
			if( CheckPlayerWinner( actual_position, table_val ) )
			{
				const unsigned lin  = GetLine( actual_position );
				const unsigned col  = GetColumn( actual_position );
				const string player = TableHolder::s_TABLE_STRING[ m_TablePtr[lin][col] ];
			
				m_OstrFile << "####################" << endl; 
				m_OstrFile << "# Player (" << player << ") wins! #" << endl;
				m_OstrFile << "####################" << endl; 

				return table_val;
			}	

			switch(table_val)
			{
			case (TV_X):
				table_val = TV_0;
				break;

			case (TV_0):
				table_val = TV_X;
				break;
			} 
		}// if

	}// while

	if( IsTableFull() )
	{
		m_OstrFile << "##################################" << endl; 
		m_OstrFile << "# Table is full and nobody wins! #" << endl;
		m_OstrFile << "##################################" << endl;
	}

	return TV_EMPTY;

}


