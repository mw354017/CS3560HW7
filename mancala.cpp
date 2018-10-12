#include "mancala.h"
#include <algorithm>  // Provides fill_n
#include <cassert>    // Provides assert macro
#include <cctype>     // Provides isdigit
#include <iomanip>    // Provides setw
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string> class
#include <string>     // Provides string
#include<sstream>


using namespace std;

namespace main_savitch_14
{
    mancala::mancala()
    {
        for(int i=0; i<14; i++){
            if(i==6 || i==13){
                stones[i]=0;
            }
            else{
                stones[i]=4;
            }
        }
    }

    mancala::~mancala()
    {
        //dtor
    }

    void mancala::display_status( ) const
    {
        std::cout<<B_BLACK<< "                                                       "<<RESET<<"\n";
        std::cout<<B_YELLOW<<"     ___    __    __    __    __    __    __   ___     "<<RESET<<"\n";
        std::cout<<B_YELLOW<<"    |   |  |"<<WHITE<<show_stones(12)<<BLACK<<"|  |"<<WHITE<<show_stones(11)<<BLACK<<"|  |"<<WHITE<<show_stones(10)<<BLACK<<"|  |"<<WHITE<<show_stones(9)<<BLACK<<"|  |"<<WHITE<<show_stones(8)<<BLACK<<"|  |"<<WHITE<<show_stones(7)<<BLACK<<"| |   |    "<<RESET<<"\n";
        std::cout<<B_YELLOW<<"    |   |  |__|  |__|  |__|  |__|  |__|  |__| |   |    "<<RESET<<"\n";
        std::cout<<B_YELLOW<<"    |   |                                     |   |    "<<RESET<<"\n";
        std::cout<<B_YELLOW<<"    |"<<WHITE<<show_stones(13)<<BLACK<<" |   1     2     3     4     5     6   |"<<WHITE<<show_stones(6)<<BLACK<<" |    "<<RESET<<"\n";
        std::cout<<B_YELLOW<<"    |   |   __    __    __    __    __    __  |   |    "<<RESET<<"\n";
        std::cout<<B_YELLOW<<"    |   |  |"<<WHITE<<show_stones(0)<<BLACK<<"|  |"<<WHITE<<show_stones(1)<<BLACK<<"|  |"<<WHITE<<show_stones(2)<<BLACK<<"|  |"<<WHITE<<show_stones(3)<<BLACK<<"|  |"<<WHITE<<show_stones(4)<<BLACK<<"|  |"<<WHITE<<show_stones(5)<<BLACK<<"| |   |    "<<RESET<<"\n";
        std::cout<<B_YELLOW<<"    |___|  |__|  |__|  |__|  |__|  |__|  |__| |___|    "<<RESET<<"\n";
        std::cout<<B_BLACK<< "                                                       "<<RESET<<"\n";
    }

    void mancala::make_move(const std::string& move)
    {
        int current;
        stringstream ss;
        ss<<move;
        ss>>current;
        int temp_stones;
        if(last_mover()==COMPUTER)
        {
            current--;
            int temp=current;
            temp_stones=stones[current];
            stones[current]=0;
            for(int i=temp_stones; i>0; i--)
            {
                temp++;
                if(temp==13)
                {
                    temp=0;
                }
                stones[temp]++;
            }
            if(stones[temp]==1 && temp>=0 && temp<6)
            {
                int opposite_cup=12-temp;
                temp_stones=stones[opposite_cup]+1;
                stones[temp]=0;
                stones[opposite_cup]=0;
                stones[6]+=temp_stones;
            }
            if(temp==6)
            {
                game::make_move(move);
            }
        }
        else
        {
            current=13-current;
            int temp=current;
            temp_stones=stones[current];
            stones[current]=0;
            for(int i=temp_stones; i>0; i--)
            {
                temp++;
                if(temp>13)
                {
                    temp=0;
                }
                if(temp==6)
                {
                    temp++;
                }
                stones[temp]++;
            }
            if(stones[temp]==1 && temp<13 && temp>6)
            {
                int opposite_cup=12-temp;
                temp_stones=stones[opposite_cup]+1;
                stones[temp]=0;
                stones[opposite_cup]=0;
                stones[13]+=temp_stones;
            }
            if(temp==13)
            {
                game::make_move(move);
            }
        }
        game::make_move(move);
    }

    std::string mancala::show_stones(int cup) const
    {
        std::string number;
        if(stones[cup]<10)
        {
            ostringstream convert;
            convert << stones[cup];
            number=" " + convert.str();
        }
        else
        {
            ostringstream convert;
            convert << stones[cup];
            number=convert.str();        }
        return number;
    }
    // Return a pointer to a copy of myself:
     game* mancala::clone( ) const
     {
        	return new mancala(*this);
     }

    // Compute all the moves that the next player can make:
     void mancala::compute_moves(std::queue<std::string>& moves) const
     {
        int temp;
        string number;
        for (int i = 1; i <= 6; i++)
        {
            temp=13-i;
            if (stones[i]>0)
            {
                ostringstream convert;
                convert << i;
                number=convert.str();
                moves.push(number);
            }
        }
     }

    // Evaluate a board position:
    // NOTE: positive values are good for the computer.
     int mancala::evaluate( ) const
     {
         int difference=stones[13]-stones[6];
        return difference;
     }
    // Return true if the current game is finished:
     bool mancala::is_game_over( )
     {
        int p1=0;
        int p2=0;
        for(int i=0; i<6; i++)
        {
            p1+=stones[i];
        }
        for(int i=7; i<13; i++)
        {
            p2+=stones[i];
        }
        if(p1==0 || p2==0)
        {
            for(int i=0; i<13; i++)
            {
                if(i!=6)
                {
                    stones[i]=0;
                }
            }
            stones[6]+=p1;
            stones[13]+=p2;
            return true;
        }
        else
        {
            return false;
        }
      }

    bool mancala::is_legal(const std::string& move) const
    {
        int current;
        stringstream ss;
        ss<<move;
        ss>>current;
        if(last_mover()==COMPUTER)
        {
            if(current>0 && current<=6 && stones[current-1]>0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(current>0 && current<=6 && stones[13-current]>0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    void mancala::restart( )
    {
         for(int i=0; i<14; i++){
            if(i==6 || i==13){
                stones[i]=0;
            }
            else{
                stones[i]=4;
            }
        }
        game::restart( );
    }

    game::who mancala::winning( ) const
    {
        if(stones[6]>stones[13])
        {
            return HUMAN;
        }
        else if(stones[6]<stones[13])
        {
            return COMPUTER;
        }
        else
        {
            return NEUTRAL;
        }
    }
}
