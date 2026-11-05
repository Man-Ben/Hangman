#include <iostream>
#include <vector>
#include <cstring>
#include <random>
#include <fstream>

using namespace std;

vector<string> gameData;
vector<char> usedChars;
vector<char> secretWord;

string generatedWord;

int generatedWordSize;
int findCharsNr;

string hangingTree[7][7] = 
{
   "[]", "=", "=", "=", "=", "@", " ",
   "[]", " ", " ", " ", " ", "|", " ",
   "[]", " ", " ", " ", " ", " ", " ",
   "[]", " ", " ", " ", " ", " ", " ",
   "[]", " ", " ", " ", " ", " ", " ",
   "[]", " ", " ", " ", " ", " ", " ",
   "[]", "~", "~", "~", "~", "~", "~",
};

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
   int maxValue = gameData.size() - 1;

   random_device rd;
   mt19937 gen(rd());
   uniform_int_distribution<> distrib(minValue, maxValue);

   return distrib(gen);
}

string getRandomWord()
{
   int randomIndex = getRandomIndex();

   return gameData.at(randomIndex);
}

void writeTable()
{
   for(int i = 0; i < 7; i++)
   {
      for(int j = 0; j < 7; j++)
         cout << hangingTree[i][j] << ' ';
      
      cout << "\n";
   }

   cout << "\n";
}

void writeGeneratedWord(char secretChar, int range)
{
   cout << "The secret word is: ";

   char converted[generatedWordSize + 1];
   
   strcpy(converted, generatedWord.c_str());

   for(int i = 0; i < range; i++)
   {      
      if(secretChar == '*')
         secretWord.push_back(secretChar);
      else
         if(toupper(secretChar) == toupper(converted[i]))
         {
            secretWord.at(i) = toupper(converted[i]);
            findCharsNr--;
         }

      cout << secretWord.at(i) << ' ';
   }
   
   cout << "\n";
}

void writeUsedChars()
{
   cout << "Used chararacters: ";

   for(int i = 0; i < usedChars.size(); i++)
      cout << usedChars.at(i) << ' ';

   cout << "\n";
}

bool isCharCorrect(char charToCheck)
{
   char converted[generatedWordSize + 1];
   
   strcpy(converted, generatedWord.c_str());
   
   for(int i = 0; i < generatedWordSize; i++)
      if(toupper(charToCheck) == toupper(converted[i]))
         return true;

   return false;
}

bool isCharUnused(char charToCheck)
{
   if(usedChars.empty())
      return true;

   for(int i = 0; i < usedChars.size(); i++)
      if(charToCheck == usedChars.at(i))
         return false;
         
   return true;
}

void drawHangman()
{
   if(hangingTree[2][5] == " ")
   {
      hangingTree[2][5] = "O";
      return;
   }

   if(hangingTree[3][4] == " ")
   {
      hangingTree[3][4] = "/";
      return;
   }

   if(hangingTree[3][5] == " ")
   {
      hangingTree[3][5] = "|";
      return;
   }

   if(hangingTree[3][6] == " ")
   {
      hangingTree[3][6] = "\\";
      return;
   }

   if(hangingTree[4][5] == " ")
   {
      hangingTree[4][5] = "|";
      return;
   }

   if(hangingTree[5][5] == " ")
   {
      hangingTree[5][5] = "/";
      return;
   }

   if(hangingTree[5][6] == " ")
   {
      hangingTree[5][6] = "\\";
      return;
   }

}

void resetTree()
{
   hangingTree[2][5] = " ";
   hangingTree[3][4] = " ";
   hangingTree[3][5] = " ";
   hangingTree[3][6] = " ";
   hangingTree[4][5] = " ";
   hangingTree[5][5] = " ";
   hangingTree[5][6] = " ";
}

bool restart()
{
   cout << "Do you want a replay? (yes/no) \n";
            
   string answer;

   cin >> answer;

   if(answer == "yes")
   {
      usedChars.clear();
      secretWord.clear();
      resetTree();
      return true;
   }

   return false;
}

void start()
{
   readGameData();

   cout << "\n\n" << "----Welcome to the Hangman!----" << "\n\n";
}

void update()
{
   generatedWord = getRandomWord();
   generatedWordSize = generatedWord.size();

   int chances = 7;
   findCharsNr = generatedWordSize;

   while(true)
   {
      writeTable();
      writeGeneratedWord('*', generatedWordSize);

      char playerInput;

      if(!usedChars.empty())
         writeUsedChars();

      if(chances < 7)
         cout << "Remaining chances: " << chances << "\n";
      
      cout << "Write a character: ";
      
      cin >> playerInput;

      if(isCharUnused(playerInput))
         usedChars.push_back(playerInput);

      if(isCharCorrect(playerInput))
      {
         writeGeneratedWord(playerInput, generatedWordSize);

         if(findCharsNr == 0)
         {            
            cout << "\nYou Won!\n";
            
            if(restart())
               update();

            return;
         }
      }
      else
      {
         chances--;
         drawHangman();         
   
         if(chances == 0)
         {
            cout << "\nYou lost!" << "\n";
            cout << "The secret word was: " << generatedWord << "\n";
            
            if(restart())
               update();
            
            return;
         }
      }
   }

}

int main()
{

   start();
   update();

   return 0;
}