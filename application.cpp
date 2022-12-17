
#include <iostream>

#include <fstream>

#include <sstream>

#include <map>

#include "barchartanimate.h"

using namespace std;



void displayCommands(){

    

    cout << "To quit press 'X' or 'x' " << endl;

    cout << "To begin press 'S' or 's'" << endl;

    cout << "To displya the commands press 'D' or 'd'" << endl;

    

}



void load(){

    

    ifstream userFile;

    string fileContents;

    string filename;

    

    cout << "Enter the filename with .txt at the end: " << endl;

  

    //Open the file

    userFile.open(filename.c_str());


    cout << "Loading your file..." << endl;

         

    //Here I check if the file is actually opened

    if(!userFile.is_open()){

        cout << "Error: unable to open '" << filename << "'" << endl;

        return;

    }

    else{

        string title;

        getline(userFile, title);

        string xlabel;

        getline(userFile, xlabel);

        string source;

        getline(userFile, source);


        BarChartAnimate bca(title, xlabel, source);

        

        while(!userFile.eof()){

            bca.addFrame(userFile);

        }

        

        bca.animate(cout, 12, -1);

        

    }

    

    

    //Closing the file

    userFile.close();

}



void trim(){

    

    //FIXME

}


//Done: command controller => choose option using switch() based on the input

void commands(){


    char choice;

    

    cout << "Choose your letter (Or 'D' to display the commands)" << endl;

    cin >> choice;

    

    switch(choice){

        case 'X':

            exit(0);

            break;

        case 'D':

            cout << endl;

            displayCommands();

            return;

        case 'S':

            load(); //Creates the new BCA

            return;

        case 'T':

            trim();

            return;

    }

}


int main(){

    

    /*

     Dear TA,

     

        My plan was to implement the controller

        which allows user to choose which function he/she wants to use.

        Using switch(), the program was supposed to execute the desired functions,

        including:

        1. load() => uploads the file => opens it => reads it => convert into BCA

        2. trim() => allows user to choose which period of time he/she wants to examine:

            a) int low => the lower bound

            b) int high => the upper bound

            c) int fragment = total - (from low to high) => what we need to use

            d) pass the fragment inside load()

            e) display the BCA with the desired fragment only

        

        Unfortunately, due to the lack of time + huge workload + family problems I couldn't manage my time to fully complete it.

     

        Thank you so much for your hard work, time, patience, and understanding!

     

     */

    

    

    string filename = "cities.txt";

    ifstream inFile(filename);

    string title;

    getline(inFile, title);

    string xlabel;

    getline(inFile, xlabel);

    string source;

    getline(inFile, source);


    BarChartAnimate bca(title, xlabel, source);

    

    while (!inFile.eof()) {

        bca.addFrame(inFile);

    }

    

    bca.animate(cout, 12, -1);

    

    


    //The engine of the commands() function

    

 /*

    bool playerAlive = false;

    

    

    do{

        playerAlive = true;

        commands();

        

    }while(playerAlive == true);*/

    


    return 0;

}
