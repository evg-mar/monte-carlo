// Tic_Tac_Toe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "TableGameSimulator.h"

#include <iostream>
#include <ostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void WriteVectorToFile(ostream & result_file, const vector<unsigned>& vect_won_games);

void GameResultsHandler( const unsigned dimension, 
						 const unsigned number_games, 
						 const string game_name );


int _tmain(int argc, _TCHAR* argv[])
{
	unsigned dimension = 0;

	do {
		cout << "Enter a positive integer for the dimension of the table: ";	
		cin >> dimension;
	}while( dimension == 0 || dimension > 10 );

	unsigned number_games = 0;
	
	do {
		cout << "Enter a positive integer for the number of games: ";	
		cin >> number_games;
	}while( number_games == 0 );

	string game_name = "";

	do {
		cout << "Enter a name for the game: ";	
		cin >> game_name;
	}while( game_name == " " );

	GameResultsHandler( dimension, number_games, game_name );

	/*
	TableGameSimulator game_simulator( "TicTacSimulation.txt", dimension );

	game_simulator.RandomGameSimulation( TV_X );
	*/
	
	string stat = "";
	do {
		cout << "Enter EXIT to exit the program: ";	
		cin >> stat;
		std::transform( stat.begin(), stat.end(), stat.begin(), ::toupper);
	}while( stat != "EXIT" );
	
	return 0;
}


void WriteVectorToFile(ostream & result_file, const vector<unsigned>& vect_won_games)
{
	result_file << "### " ;
	if( vect_won_games.size() > 0 )
	{
		for( size_t cnt = 0; cnt < vect_won_games.size() -1 ; cnt++ )
		{
			result_file << vect_won_games[ cnt ] << ", " ;
		}
		result_file << vect_won_games[ vect_won_games.size() - 1 ];
	}
	result_file <<  endl;
	result_file << "########################################################################"  << endl;

}

void GameResultsHandler( const unsigned dimension, 
						 const unsigned number_games, 
						 const string game_name )
{
	size_t win_X	  = 0,
		   win_0	  = 0,
		   win_nobody = 0;
	map<TableValues, vector<unsigned>> winner_statistic_map;


	TableValues player_start = TV_X;

	for( size_t it = 0; it < number_games; it++ )
	{
	
		const string str_it = std::to_string( static_cast<_ULonglong>( it + 1 ) );

		TableGameSimulator game_simulator( game_name + "_" + str_it + ".txt", dimension );
		
		const TableValues table_value = game_simulator.RandomGameSimulation( player_start );
	
		switch( table_value )
		{
		case (TV_EMPTY):
			win_nobody++;
			winner_statistic_map[TV_EMPTY].push_back( it + 1);
			break;

		case (TV_X):
			win_X++;
			winner_statistic_map[TV_X].push_back( it + 1);
			break;

		case (TV_0):
			win_0++;
			winner_statistic_map[TV_0].push_back( it + 1);
			break;
		}

		switch(player_start)
		{
		case (TV_X):
			player_start = TV_0;
			break;

		case (TV_0):
			player_start = TV_X;
			break;
		}// switch

	}// for

	ofstream result_file( game_name + "_results.txt", ios::trunc );

	result_file << "##########################################" << endl;
	result_file << "### Game name: " << game_name << endl;
	result_file << "##########################################" << endl;

	result_file << "##########################################" << endl;
	result_file << "### Number of Games: " <<number_games<<", Table dimension: "<<dimension<<"x"<<dimension<< endl;
	result_file << "##########################################" << endl;

	result_file << "########################################################################" << endl;
	result_file << "### Remi: " << win_nobody << " games."<< endl;
	result_file << "###" << endl;
	//	result_file << "################################" << endl;

	WriteVectorToFile( result_file, winner_statistic_map[TV_EMPTY] );

	result_file << "########################################################################"  << endl;
	result_file << "### (X) wins: " << win_X << " games."<< endl;
	result_file << "###" << endl;
	//	result_file << "################################"  << endl;

	WriteVectorToFile( result_file, winner_statistic_map[TV_X] );

	result_file << "########################################################################"  << endl;
	result_file << "### (0) wins: " << win_0 << " games."<<endl;
	result_file << "###" << endl;
	//	result_file << "################################"  << endl;

	WriteVectorToFile( result_file, winner_statistic_map[TV_0] );


	result_file.close();
}
