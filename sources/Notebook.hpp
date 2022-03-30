#include <iostream>
#include <vector>
#include <string>
#include "Direction.hpp"

using namespace std;
using ariel::Direction;


namespace ariel{
    class Notebook{
        private: 
        vector<vector<string>> pages; //Datastructure to hold the notebook
        uint maxCols = 100;
        public:
        Notebook(){ //Initilize the notebook
            uint pages = 100;
            uint rows = 100;
            for (int i = 0; i < pages; i++){
                vector<string> page;
                for (int j = 0; j < rows; j++){
                    string row;
                    for (int k = 0; k < maxCols; k++){
                        row += "_";
                    }
                    page.push_back(row);
                }
                this->pages.push_back(page);
            }
        }
        void update(uint page){ // Adding new row to the given page
            string row;
            for (int i = 0; i < maxCols; i++){
                row+= "_";
            }
            pages[(uint)page].push_back(row);
        }

        ~Notebook(){
            this->pages.clear();
        }
        void write(int page ,int row ,int col , ariel::Direction dir , string const &input);
        string read(int page ,int row , int col , ariel::Direction dir , int len);
        void erase(int page , int row , int col , ariel::Direction dir , int len);
        void show(int page);
    };
}
