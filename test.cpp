#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

//global variable main 8 allergies
bool Milk = false;
bool Eggs = false;
bool Fish = false;
bool Shellfish = false;
bool Treenuts = false;
bool Peanuts = false;
bool Wheat = false;
bool Soybean = false;
bool Sesame = false;

void userSetup(){
  string userName;
  cout << "Hi, welcome to Allergen Pal!\nWhat's your name?\n";
  cin >> userName;
  cout << "Nice to meet you "+userName+"!\n";
  cout << "Which of the following food allergies do you have?\n";
  cout << "Milk\nEggs\nFish\nShellfish\nTreenuts\nPeanuts\nWheat\nSoybean\nSesame\n";
  cout << "Input directly as displayed\n";
  string allergies;
  getline(cin, allergies);
  
  getline(cin, allergies);
  
  const char *allergens[9] = { "Milk", "Eggs","Fish", "Shellfish","Treenuts", "Peanuts", "Wheat", "Soybean", "Sesame"};
                             
  for (int i = 0; i<9;i++)
  {
    if (allergies.find(allergens[i]) != string::npos){
      if(i==0){Milk=true;}
      else if(i==1){Eggs=true;}
      else if(i==2){Fish=true;}
      else if(i==3){Shellfish=true;}
      else if(i==4){Treenuts=true;}
      else if(i==5){Peanuts=true;}
      else if(i==6){Wheat=true;}
      else if(i==7){Soybean=true;}
      else if(i==8){Sesame=true;}
    }
  }

  /*cout << Milk<< Eggs << Fish<< Shellfish<< Treenuts<< Peanuts<< Wheat<< Soybean<< Sesame<<"\n";*/

  return;
}

void checkComp(std::string allergen){
  bool safety=true;
  
  if(Milk){
      if(allergen[0]=='1'){
        safety=false;
      cout << "May contain traces of Milk\n\n";}
      else if(allergen[0]=='2')
      {safety=false;
        cout << "Contains Milk\n\n";}
    }

 if(Eggs){
  if(allergen[1]=='1')
      {safety=false;
      cout << "May contain traces of Eggs\n\n";}
      else if(allergen[1]=='2')
      {safety=false;
      cout << "Contains Eggs\n\n";}
  }

 if(Fish){
  if(allergen[2]=='1')
      {safety=false;
      cout << "May contain traces of Fish\n\n";}
      else if(allergen[2]=='2')
      {safety=false;
      cout << "Contains Fish\n\n";}
  }
  
 if(Shellfish){
  if(allergen[3]=='1')
      {safety=false;
      cout << "May contain traces of Shellfish\n\n";}
      else if(allergen[3]=='2')
      {safety=false;
      cout << "Contains Shellfish\n\n";}
      }

 if(Treenuts){
  if(allergen[4]=='1')
      {safety=false;
      cout << "May contain traces of Treenuts\n\n";}
      else if(allergen[4]=='2')
      {safety=false;
        cout << "Contains Treenuts\n\n";}
      }

 if(Peanuts){
  if(allergen[5]=='1')
      {safety=false;
      cout << "May contain traces of Peanuts\n\n";}
      else if(allergen[5]=='2')
      {cout << "Contains Peanuts\n\n";}
      }

 if(Wheat){
  if(allergen[6]=='1')
      {safety=false;
      cout << "May contain traces of Wheat \n\n";}
      else if(allergen[6]=='2')
      {cout << "Contains Wheat \n\n";}
      }

 if(Soybean){
  if(allergen[7]=='1')
      {safety=false;
      cout << "May contain traces of Soybean\n\n";}
      else if(allergen[7]=='2')
      {cout << "Contains Soybean\n\n";}
      }

 if(Sesame){
  if(allergen[8]=='1')
      {safety=false;
      cout << "May contain traces of Sesame\n\n";}
      else if(allergen[8]=='2')
      {cout << "Contains Sesame\n\n";}
  }

  if (safety){
    cout << "Congrats, that's safe to eat\n";
  }
  else {
    cout << "Unfortunately, we cannot recommend eating this\n";
  }
}


static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
ofstream file;
file.open("file.txt");
   for(i = 0; i<argc; i++){
      file << argv[i] ? argv[i] : "NULL";
   }
   file.close();
   return 0;
}

int main(int argc, char* argv[]) {
   //Declarations
   string allergies;
   char *choice = new char[40];
   string allergyList;
   int outorin;

   //Getting data from user
   userSetup();

   cout << "Which would you like to eat" << endl
        <<  "1. At a restaurant" << endl
        <<  "2. A snack" << endl;
   cin >> outorin;

if (outorin == 2){
   cout << "What would you like to eat today? " << endl
        << "1. Snickers" << endl
        << "2. Doritos" << endl
        << "3. Lucky Charms" << endl
        << "4. Kitkat" << endl
        << "5. Takis" << endl
        << "6. Cheezit" << endl
        << "7. Cheetos" << endl
        << "8. Pringles" << endl
        << "9. Peanut Butter" << endl
        << "10. Oreos" << endl;

   cin >> choice;





   //Getting data from database
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";
   char *statement = choice; //Need to change to input
   /* Open database */
   rc = sqlite3_open("Food.db", &db);

   /* Create SQL statement */
   sql = "SELECT * from food where Name = '";
   char *tmp = new char[100];
   strcpy(tmp,sql);
   strcat(tmp,statement);
   strcat(tmp,"'");
   /* Execute SQL statement */
   rc = sqlite3_exec(db,tmp, callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
//      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
//      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);

   string allergen="";
   //Getting data from file
   string fromFile;
   ifstream file;
   file.open("file.txt");
   file >> fromFile;
   file.close();
   for (int i = fromFile.size() - 9; i < fromFile.size(); i++){
      if(isdigit(fromFile[i])){
          allergen.append(1,fromFile[i]);
      }
   }
   checkComp(allergen);
return 0;
}
else{
   string restaurant;
   cout << "Where would you like to eat today?" << endl
        << "1. Sushi101" << endl
        << "2. Chickfila" << endl;
   cin >> restaurant;
   if (restaurant == "Sushi101"){
   cout << "What would you like to eat there?" << endl
        << "1. Shrimp Fried Rice" << endl
        << "2. California Roll" << endl
        << "3. Philadelphia Roll" << endl;
        cin >> choice;
   }
   else if (restaurant == "Chickfila"){
      cout << "What would you like to eat there?" << endl
           << "1. Chickfila Sandwich" << endl
           << "2. Grilled Chicken Sandwich" << endl
           << "3. Nuggets" << endl;
      cin >> choice;
   }

   

   //Getting data from database
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";
   char *statement = choice; //Need to change to input
   /* Open database */
   rc = sqlite3_open("Restaurants.db", &db);

   /* Create SQL statement */
   if (restaurant == "Sushi101"){
      sql = "SELECT * from Sushi101 where Name = '";
   }
   else if(restaurant == "Chickfila"){
      sql = "SELECT * from Chickfila where Name = '";
   }
   
   char *tmp = new char[100];
   strcpy(tmp,sql);
   strcat(tmp,statement);
   strcat(tmp,"'");
   /* Execute SQL statement */
   rc = sqlite3_exec(db,tmp, callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
//      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
//      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);

   string allergen="";
   //Getting data from file
   string fromFile;
   ifstream file;
   file.open("file.txt");
   file >> fromFile;
   file.close();
   for (int i = fromFile.size() - 9; i < fromFile.size(); i++){
      if(isdigit(fromFile[i])){
          allergen.append(1,fromFile[i]);
      }
   }
   checkComp(allergen);
return 0;
}
   
}

