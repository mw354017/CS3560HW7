// File: connect4.h (part of the namespace main_savitch_14)
#ifndef MAIN_SAVITCH_MANCALA
#define MAIN_SAVITCH_MANCALA
#include <queue>    // Provides queue<string>
#include <string>   // Provides string
#include<sstream>
#include "colors.h"
#include "game.h"   // Provides the game base class



namespace main_savitch_14
{
    class mancala : public game
    {
        public:
            mancala();
            std::string show_stones(int cup) const;
            //enum who { HUMAN, NEUTRAL, COMPUTER }; // Possible game outcomes
        // PUBLIC MEMBER FUNCTIONS
        // The play function should not be overridden. It plays one game,
        // with the human player moving first and the computer second.
        // The computer uses an alpha-beta look ahead algorithm to select its
        // moves. The return value is the winner of the game (or NEUTRAL for
        // a tie).
             ~mancala();
        protected:
             // *******************************************************************
        // VIRTUAL FUNCTIONS (these are overridden from the game base class)
        // *******************************************************************
        // Return a pointer to a copy of myself:
        virtual game* clone( ) const;
            // Compute all the moves that the next player can make:
        virtual void compute_moves(std::queue<std::string>& moves) const;
        // Display the status of the current game:
        virtual void display_status( ) const;
        // Evaluate the current board position.
        // NOTE: Positive values are good for the computer.
        virtual int evaluate( ) const;
        // Return true if the current game is finished:
        virtual bool is_game_over( );
        // Return true if the given move is legal for the next player:
        virtual bool is_legal(const std::string& move) const;
        // Have the next player make a specified move:
        virtual void make_move(const std::string& move);
        // Restart the game from the beginning:
        virtual void restart( );
        virtual game::who winning( ) const;


        private:
            int stones[14];
            int move_number;                     // Number of moves made so far
        // STATIC MEMBER CONSTANT
        static const int SEARCH_LEVELS = 4;  // Levels for look-ahead evaluation
    };
}
#endif // MANCALA_H
