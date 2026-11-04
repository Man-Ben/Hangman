#include <iostream>
#include <vector>
#include <cstring>
#include <random>
#include <fstream>

using namespace std;

vector<string> gameData;

string generatedString;



void readGameData()
{
   ifstream config("GameData");
   
   string tmp;

   while(config >> tmp)
   {
      gameData.push_back(tmp);
   }

   config.close();
}

int getRandomIndex()
{
   int minValue = 0;
   int maxValue = gameData.size();

   random_device rd;
   mt19937 gen(rd());
   uniform_int_distribution<> distrib(minValue, maxValue);

   return distrib(gen);
}

string getRandomWord()
{
   int randomIndex = getRandomIndex();

   cout << gameData.at(randomIndex);

   return gameData.at(randomIndex);
}

void writeTable()
{

}

void start()
{
   readGameData();
   getRandomWord();
}

void update()
{

}

int main()
{

   start();


   return 0;
}