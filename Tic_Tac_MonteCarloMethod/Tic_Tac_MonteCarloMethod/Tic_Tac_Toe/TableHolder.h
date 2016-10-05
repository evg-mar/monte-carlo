#ifndef __TABLE_HOLDER__
#define __TABLE_HOLDER__


#include <fstream>

#include <set>

enum TableValues
{
	TV_EMPTY = 0,
	TV_0	 = 1,
	TV_X     = 2,

	TV_MAX   = 3
};


class TableHolder
{
public:
	TableHolder( const std::string game_name = "TicTacToe.txt", 
				 const unsigned dimension = 3);

	TableHolder( const TableHolder &rhs );
	
	virtual ~TableHolder();

	// Get member data --> Inline functions
	inline
	unsigned TableDim() const 
	{	return m_TableDim; }

	inline 
	unsigned TableSize() const 
	{ return m_TableDim * m_TableDim; }

	inline
	unsigned GetPosition( const unsigned lin, const unsigned col ) const 
	{ return TableSize()*lin + col; } 

	unsigned GetLine  ( const unsigned position ) const;
	unsigned GetColumn( const unsigned position ) const;
	
	// Overriding standard operators
	const TableValues* operator[]( const unsigned line ) const 
	{ return m_TablePtr[ line ]; } 

/*	NOT NEEDED FOR THE MOMENT
	TableHolder & operator=( const TableHolder &rhs );
*/
protected:

	void Init();

	void ReleaseTableHolder();

	void WriteEmptyPositions();
	void WriteCurrentTable();

	// Check if Winner --> Inline functions
	bool CheckLineWinner(		   const unsigned line, const unsigned column ) const;
	bool CheckColumnWinner(		   const unsigned line, const unsigned column ) const;
	bool CheckRightDiagonalWinner( const unsigned line, const unsigned column ) const;
	bool CheckLeftDiagonalWinner(  const unsigned line, const unsigned column ) const;


	bool InsertValue( const unsigned actual_position, const TableValues value );

	inline
	bool IsTableFull() const 
	{ return m_FreePositions.empty(); }
	
	inline
	bool IsEmpty( const unsigned position ) const 
	{ return ( m_FreePositions.count( position ) > 0 ); }

protected:

	unsigned			m_TableDim;  // Dimension of the Table 	
	TableValues**		m_TablePtr;  // Pointer to the Table content

	std::set<unsigned> m_FreePositions; // Set holder of the free positions in the table

	std::string			m_GameName;
	std::ofstream		m_OstrFile;  // Output stream for the file containing the game history 

	// Static member data
	static const  char * s_TABLE_STRING[ TV_MAX ];
};
	

///-------------------------------------
// Define some simple functions as inline

// Check if the line is Winner for the element m_TablePtr[line][column] 
inline
bool TableHolder::CheckLineWinner( const unsigned line, const unsigned column ) const
{
	if( m_TablePtr[line][column] == TV_EMPTY)
		return false;

	for( size_t it_col = 0; it_col < m_TableDim; it_col++ )
	{
		if( m_TablePtr[line][column] != m_TablePtr[line][it_col] )	
			return false;		
	}// for

	return true;
}

// Check if the column is Winner for the element m_TablePtr[line][column] 
inline
bool TableHolder::CheckColumnWinner( const unsigned line, const unsigned column ) const
{
	if( m_TablePtr[line][column] == TV_EMPTY)
		return false;

	for( size_t it_line = 0; it_line < m_TableDim; it_line++ )
	{
		if( m_TablePtr[line][column] != m_TablePtr[it_line][column] )
			return false;
	}// for

	return true;
}

// Chaeck if the right diagonal is Winner for the element in m_TablePtr[line][column]
inline
bool TableHolder::CheckRightDiagonalWinner( const unsigned line, const unsigned column ) const
{
	if( line != column || m_TablePtr[line][column] == TV_EMPTY)
		return false;

	for( size_t it_diag = 0; it_diag < m_TableDim; it_diag++ )
	{
		if( m_TablePtr[line][column] != m_TablePtr[it_diag][it_diag] )
			return false;
	}// for

	return true;
}

// Chaeck if the left diagonal is Winner for the element in m_TablePtr[line][column]
inline
bool TableHolder::CheckLeftDiagonalWinner( const unsigned line, const unsigned column ) const
{
	if( line != m_TableDim - column || m_TablePtr[line][column] == TV_EMPTY)
		return false;

	for( size_t it_diag = 0; it_diag < m_TableDim; it_diag++ )
	{
		if( m_TablePtr[line][column] != m_TablePtr[it_diag][m_TableDim - it_diag] )
			return false;
	}// for

	return true;
}


inline
unsigned TableHolder::GetLine( const unsigned position ) const
{
	// the searched line of the position should be within the range { 0, ..., TableDim x TableDim - 1 }
	unsigned actual_pos = position;

	if( position > (TableSize() - 1) && m_TableDim > 0 )
	{
		actual_pos = position % TableSize();
	}// if
	// integer division
	return (actual_pos / m_TableDim); 
}

inline
unsigned TableHolder::GetColumn( const unsigned position ) const
{
	// the searched line of the position should be within the range { 0, ..., TableDim x TableDim - 1 }
	unsigned actual_pos = position;

	if( position > (TableSize() - 1) && m_TableDim > 0 )
	{
		actual_pos = position % TableSize();
	}// if

	return (actual_pos % m_TableDim);  
}

#endif
