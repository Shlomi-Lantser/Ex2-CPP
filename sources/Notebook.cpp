#include "Notebook.hpp"
#include <iostream>
#include "Direction.hpp"

using namespace std;
using namespace ariel;
uint extra = 1; //Extra space for the last row or column
const int minChar = 32; //Min char in ascii table
const int maxChar = 125;//Max char in ascii table

void Notebook::write(int page, int row, int col, ariel::Direction dir, string const &input)
{
    //Checking bad inputs and throws exception.
     if (page < 0)
    {
        throw "Error: page index out of range";
    }
    if (row < 0)
    {
        throw "Error: row index out of range";
    }
    if (col < 0 )
    {
        throw "Error: col index out of range";
    }
    if( col >= this->maxCols){
        throw "Error: col index out of range";
    }
    if (input.size() + (uint)col > this->maxCols && dir == Direction::Horizontal)
    {
        throw "Error: input is too long";
    }
   
    if (page > this->pages.size())
    {
        this->pages.resize((uint)page + 1); //Adding new page for the datastructor if needed
        for (int i = 0; i < input.size() + extra; i++) 
        {
            update((uint)page); //Adding the needed rows to the given page
        }
    }
    if ((uint)row + input.size() > pages[(uint)page].size() && dir == Direction::Vertical)
    {
        for (int i = 0; i < input.size() + extra; i++)
        {
            update((uint)page); //Adding the needed rows to the given page
        }
    }

    if (dir == Direction::Horizontal)
    {
        for (uint i = 0; i < input.size(); i++)
        {
            if (input[i] < minChar || input[i] > maxChar) //Checking if the input is valid and printable.
            {
                throw "Error: input contains invalid character";
            }
            if (pages[(uint)page][(uint)row][(uint)(col)+i] == '_') //Checking if the given cell is empty.
            {
                this->pages[(uint)page][(uint)row][(uint)(col)+i] = input[i];
            }
            else
            {
                throw "Error: already filled";
            }
        }
    }
    else if (dir == Direction::Vertical)
    {
        for (uint i = 0; i < input.size(); i++)
        {
            if (input[i] < minChar || input[i] > maxChar) //Checking if the input is valid and printable.
            {
                throw "Error: input contains invalid character";
            }
            if (pages[(uint)page][(uint)(row)+i][(uint)(col)] == '_') //Checking if the given cell is empty.
            {
                this->pages[(uint)page][(uint)(row)+i][(uint)(col)] = input[i];
            }
            else
            {
                throw "Error: already filled";
            }
        }
    }
}

string Notebook::read(int page, int row, int col, ariel::Direction dir, int len)
{

    //Checking bad inputs and throws exception.
    if(len < 0){
        throw "Error: length is negative";
    }
    if (page < 0)
    {
        throw "Error: page index out of range";
    }
    if (row < 0)
    {
        throw "Error: row index out of range";
    }
    if (col < 0 || col >= this->pages[(uint)page][(uint)row].size())
    {
        throw "Error: col index out of range";
    }

    if (len == 0)
    {
        return "";
    }
    string output; //Output string.

    if (len + col > maxCols && dir == Direction::Horizontal) //Checking if the given length is valid.
    {
        throw "Error: len is too long";
    }

    if (dir == Direction::Horizontal)
    {
        for (int i = 0; i < len; i++)
        {
            output += this->pages[(uint)page][(uint)row][(uint)(col + i)]; //Adding read chars to the output string.
        }
    }
    else if (dir == Direction::Vertical)
    {
        if ((uint)(row + len) > this->pages[(uint)page].size())//Checking if extra rows are needed.
        {
            for (int i = 0; i < (uint)len + extra; i++)
            {
                update((uint)page);//Adding the needed rows to the given page.
            }
        }
        for (int i = 0; i < len; i++)
        {
            output += this->pages[(uint)page][(uint)(row + i)][(uint)col]; //Adding read chars to the output string.
        }
    }
    return output;
}
void Notebook::erase(int page, int row, int col, ariel::Direction dir, int len)
{

    //Checking bad inputs and throws exception.

    if(len < 0){
        throw "Error: length is negative";
    }
    if (page < 0)
    {
        throw "Error: page index out of range";
    }
    if (row < 0)
    {
        throw "Error: row index out of range";
    }
    if (col < 0 || col >= this->pages[(uint)page][(uint)row].size()) //Checking if the given col is valid.
    {
        throw "Error: col index out of range";
    }
    if (len == 0)
    {
        return;
    }
    if (len + col > this->maxCols && dir == Direction::Horizontal)//Checking if the given length is valid.
    {
        throw "Error: len is too long";
    }
    if (dir == Direction::Horizontal)
    {
        for (int i = 0; i < len; i++)
        {
            this->pages[(uint)page][(uint)row][(uint)(col + i)] = '~'; //Erasing the given chars.
        }
    }
    else if (dir == Direction::Vertical)
    {
        for (int i = 0; i < len; i++)
        {
            this->pages[(uint)page][(uint)(row + i)][(uint)col] = '~'; //Easing the given chars.
        }
    }
}
void Notebook::show(int page)
{
    //Checking bad inputs and throws exception.

    if (page < 0)
    {
        throw "Error: page index out of range";
    }
    if (page > this->pages.size())
    {
        throw "Error: page index out of range";
    }
    for (uint i = 0; i < this->pages[(uint)page].size(); i++) //Printing the given page.
    {
        for (uint j = 0; j < this->pages[(uint)page][i].size(); j++)
        {
            cout << this->pages[(uint)page][i][j]; 
        }
        cout << endl;
    }
}
