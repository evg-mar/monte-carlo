// Include own header
#include "TableHolder.h"

// STL Includes
#include <string>
#include <iomanip>

using namespace std;

static const size_t WIDTH_TABLE_VAL = 4;

const  char * TableHolder::s_TABLE_STRING[ TV_MAX ] = {
	"E", 
	"0", 
	"X" };

/// Default Constructor -> dimension = 3
/// Otherwise the dimension given as argument
TableHolder::TableHolder( const string game_name,		// << Name of the Game
						  const unsigned dimension		// << Dimension of the Table
						  ):
m_TableDim( dimension ),
m_GameName( game_name )
{
	Init();
}

// Copy constructor
TableHolder::TableHolder( const TableHolder &rhs ):
m_TableDim( rhs.m_TableDim ),
m_GameName( rhs.m_GameName )
{
	Init();
}

/// Initialize the m_TablePtr and open the Output stream file.
/// Note that m_GameName and m_TableDim should have been initialized in the assignement list
/// of the constructors or assignement operator.
/// To be called by the constructors and the assignement operator=, as well.
void TableHolder::Init()
{
//	m_TableState = TableHolder::TS_ACTIVE;

	m_OstrFile.open( m_GameName.c_str(), std::ios::trunc );
	
	m_OstrFile << "# File containing the results of Tic Tac Toe!" << endl;
	m_OstrFile << "#" << endl;
	m_OstrFile << "# Table dimension: " <<  m_TableDim << "x" << m_TableDim << endl;

	// All the m_TableDim * m_TableDim positions in the table are free at the start
	for( unsigned pos = 0; pos < TableSize(); pos++ )
	{
		m_FreePositions.insert( pos );
	}// for

	if( m_TableDim > 0 )
	{
		m_TablePtr = new TableValues*[ m_TableDim ];
		
		for( size_t it_line = 0; it_line < m_TableDim; it_line++ )
		{
			m_TablePtr[ it_line ] = new TableValues[ m_TableDim ];

			memset( m_TablePtr[ it_line ], TV_EMPTY, sizeof(TableValues) * m_TableDim );
		}// for
	}// if

	WriteCurrentTable();
}


/// Virtual destructor
TableHolder::~TableHolder()
{
	ReleaseTableHolder();
}

/// Releases the the dymanimic memeber data and closes the Output stream file
/// To be used in the Destructor and the assignement operator =, as well
void TableHolder::ReleaseTableHolder()
{
	m_OstrFile << "#" << endl;
	m_OstrFile << "# End of File!" << endl;
	
	m_OstrFile.close();

	if( m_TableDim > 0 )
	{
		for( size_t it_line = 0; it_line < m_TableDim; it_line++ )
		{// Delete the current line
			delete [] m_TablePtr[ it_line ] ;
		}// for

		// Delete the pointers to the lines
		delete [] m_TablePtr;
	}// if
}

/* NOT NEEDED FOR THE MOMENT
TableHolder & TableHolder::operator=( const TableHolder &rhs )
{
	// Release the dynamic member data and close the output stream file
	ReleaseTableHolder();

	m_TableDim = rhs.m_TableDim;
	m_GameName = rhs.m_GameName;
	.............
	............
	return *this;
}
*/

/// Inserts a value in the corresponding position of the Table
/// Returns true iff the position is empty and the value is inserted
/// Otherwise, returns false if the position has already a value
bool TableHolder::InsertValue( const unsigned	 actual_position,		// << the position
							   const TableValues value )		// << the value to be inserted
{
	if( value == TV_EMPTY )
	{
		m_OstrFile << "# WARNING: empty value (E) shouldn't be inserted in the table!" << endl;

		return false;
	}

	if( IsEmpty( actual_position ) )
	{
		m_TablePtr[GetLine(actual_position)][GetColumn(actual_position)] = value;
		
		m_FreePositions.erase( actual_position );

		WriteEmptyPositions();
		WriteCurrentTable();
		
		return true;
	}// if
	else  // if m_TablePtr[l][c] is not empty 
	{
		m_OstrFile << "# WARNING: position "<< actual_position << " is not empty!" << endl;

		return false;
	}//else
}

/// Write the current state of the empty positions in the file
void TableHolder::WriteEmptyPositions()
{
	m_OstrFile << "##########" << endl;

	for( set<unsigned>::const_iterator it = m_FreePositions.begin(); it != m_FreePositions.end(); ++it )
	{
		m_OstrFile << setw(WIDTH_TABLE_VAL) << *it;
	}// for

	m_OstrFile << endl;
}

/// Write the current state of the table in the file
void TableHolder::WriteCurrentTable()
{
	m_OstrFile << "#---------" << endl;

	for( size_t it_lin = 0; it_lin < m_TableDim; it_lin++ )
	{
		for( size_t it_col = 0; it_col < m_TableDim; it_col++ )
		{
			m_OstrFile << setw(WIDTH_TABLE_VAL) << TableHolder::s_TABLE_STRING[ m_TablePtr[it_lin][it_col] ];
		}// for

		m_OstrFile << endl;
	
	}// for
}

