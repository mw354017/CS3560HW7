/*****************************************************
This is a sample of what the main should like for the second phase of
the Mancala game.The only change is that the game now announces a
winner.
	John Dolan	Ohio University		Spring 2018
*************************************************************/
#include<iostream>
#include "mancala.h"
using namespace std;
using namespace main_savitch_14;


int main(){
    mancala stonegame;
	mancala::who winner;
    winner=stonegame.play( );
	if (winner == mancala::HUMAN)
		std::cout<<"Player 1 Wins";
	else
		std::cout<<"Player 2 Wins";
return 0;
}
