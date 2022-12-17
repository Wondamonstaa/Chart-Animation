
#include <iostream>

#include <fstream>

#include <sstream>

#include <string>

#include <algorithm>

#include <map>

#include <vector>

#include <unistd.h>

#include "myrandom.h" // used by graders, do not remove

#include "barchart.h"

  

using namespace std;



class BarChartAnimate{


//Step 1: declare the private data members => DONE

 private:

    

    BarChart* barcharts;

    int size;

    int capacity;

    string title, xlabel, source;

    int idx;

    map<string, string> colorMap;


 public:


  //Step 2: parameterized constructor => DONE

  BarChartAnimate(string title, string xlabel, string source){

    

    this -> capacity = 4;

    size = 0;

    idx = 0;

    barcharts = new BarChart[capacity];

    this -> title = title;

    this -> xlabel = xlabel;

    this -> source = source;

  }


    

  //Step 3: create the destructor => DONE

  virtual ~BarChartAnimate(){

    

    do{

      delete[] barcharts;

      barcharts = nullptr;

    }while(barcharts != nullptr);

  }


    

  //Step 4: addFrame() => adds a new BarChart to the BarChartAnimate object from the file stream => DONE

  void addFrame(ifstream &file){

    

    int sum;

    int doubled = 0;

    string frame, city, country, value, category;

    

    getline(file, frame);

    file >> sum;

    BarChart chart(sum);


    if(!file.is_open() || !file.good()){

      return;

    }


    for(int n = 0; n < 1; n++){

      if(file.is_open()){

        //cout << "The file was open successfully." << endl;

      }

      else{

        //cout << "The file was not open. Try again." << endl;

      }

      n++;

    }


    if(this -> size == this -> capacity){

      //cout << "Doubling the capacity." << endl;

      //doubled = capacity * 2;

      doubled = pow(capacity, 2);

      

      //Declare the new object with doubled capacity

      BarChart *newBar = new BarChart[doubled];


      int i = 0;

      while(i < size){

        newBar[i] = barcharts[i];

        i++;

      }

      

      delete[] barcharts;

      capacity = doubled;

      barcharts = newBar;

      newBar = nullptr;

    }

  

    int i = 0;

    do{

      if(file.good() && !file.eof()){

        if(idx == COLORS.size()){

          idx = 0;

        }

        /*string title;

          getline(inFile, title);

          string xlabel;

          getline(inFile, xlabel);

          string source;

          getline(inFile, source);*/

        

        getline(file, frame, ',');

        string city;

        getline(file, city, ',');

        string country;

        getline(file, country, ',');

        string value;

        getline(file, value, ',');

        string category;

        getline(file, category);


        //If true, leave everything like it is now

        if(colorMap.count(category) != 0){

          idx = idx;

        }

        //Use count to see if the category is inside the map (Will return 1 if it is inside)

        else if(colorMap.count(category) == 0){

          colorMap[category] = COLORS[idx];

          idx++;

        }

        else{

          cout << "Error: try again!" << endl;

        }

        

        int numVal = stoi(value);

        chart.addBar(city, numVal, category);

        chart.setFrame(frame);

      }


      i++;

    }while(i < sum);

  

    barcharts[size] = chart;

    size++;

  }


    

  //Step 5: animate => plays each frame stored in barcharts => DONE

  void animate(ostream &output, int top, int endIter){

    

    unsigned int microsecond = 50000;

    int i = 0;

    bool engine = false;


    if(endIter == -1){

      cout << "The value is incorrect." << endl << "Fixing it now." << endl;

      engine = true;

      endIter = size;

    }

    

    do{

      usleep(3 * microsecond); //Pause between displaying the results

      for(int i = 0; i < 1; i++){

        output << CLEARCONSOLE;

        output << WHITE << title << endl;

        output << WHITE << source << endl;

      }

      

      barcharts[i].graph(output, colorMap, top);

      output << WHITE << xlabel << endl;

      output << "Frame: " << barcharts[i].getFrame() << endl;

      i++;

    }while(i < endIter);

  }



  //Step 6: getSize() => returns the size of the BarChartAnimate object => DONE

  int getSize(){

    return size;

  }



  //Step 7: returns BarChart element in BarChartAnimate => DONE

  BarChart &operator[](int i){

    

    BarChart bc;

    if(i > size){

      throw out_of_range("BarChartAnimate: i out of bounds");

    }

    else if(i < 0){

      throw out_of_range("BarChartAnimate: i out of bounds");

    }

    else{

      //cout << "All clear." << endl;

    }


    return barcharts[i];

  }

};
