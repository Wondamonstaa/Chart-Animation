
#include <iostream>

#include <algorithm>

#include <map>

#include "myrandom.h" // used in graders, do not remove

#include "bar.h"


using namespace std;


// Constants used for bar chart animation.  You will primarily

// use these in barchartanimate.h, but you might find some useful here.

const string BOX = "\u29C8";

const string CLEARCONSOLE = "\033[2J";

const string RESET("\033[0m");



//

// NOTE: COMMENT AND UNCOMMENT AS NEEDED BASED ON YOUR TERMINAL

//

// Color codes for light mode terminals

// const string RED("\033[1;36m");

// const string PURPLE("\033[1;32m");

// const string BLUE("\033[1;33m");

// const string CYAN("\033[1;31m");

// const string GREEN("\033[1;35m");

// const string GOLD("\033[1;34m");

// const string BLACK("\033[1;37m");

// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};


// Color codes for darker mode terminals

const string CYAN("\033[1;36m");

const string GREEN("\033[1;32m");

const string GOLD("\033[1;33m");

const string RED("\033[1;31m");

const string PURPLE("\033[1;35m");

const string BLUE("\033[1;34m");

const string WHITE("\033[1;37m");

const string BLACK("\033[1;37m");

//const string RESET("\033[0m");

const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE, BLACK};




//

// BarChart

//

class BarChart{

  

 //Step 0: declare private data members => DONE

 private:

    

    Bar* bars;  // pointer to a C-style array

    int capacity;

    int size;

    string frame;

    

 public:

    

    //Step 1: create the default constructor.

    BarChart() {

        

        //bars = new Bar[0];

        bars = nullptr;

        frame = "";

        capacity = 0;

        size = 0;

        

    }

    

    

    //Step 2: create the parameterized constructor => parameter passed in determines memory allocated for bars => DONE

    BarChart(int n) {

        

        bars = new Bar[n];

    

        this -> capacity = n;

        this -> size = 0;

        //bars = new Bar[capacity];

        this -> frame = "";

        

    }


    

    //Step 3: copy constructor => called automatically by C++ to create an BarChart that contains a copy of an existing BarChart => DONE

    BarChart(const BarChart& other) {

        

        this -> frame = other.frame;

        this -> bars = new Bar[other.capacity];

        

        //this -> bars = other.bars;

        this -> size = other.size;

        this -> capacity = other.capacity;

        

        int i = 0;

        

        do{

            this -> bars[i] = other.bars[i];

            ++i;

        }while(i < other.size);

        

    }

    

    

    //Step 4: copy operator => called when you assign one BarChart into another, i.e. this = other => DONE

    BarChart& operator=(const BarChart& other){

        

        BarChart bc;

        

        //cout << "Copy constructor called." << endl;

        

        if(this == &other){

            return *this;

        }

        

        delete [] bars;

        

        this -> bars = new Bar[other.capacity];

        this -> size = other.size;

        this -> frame = other.frame;

        this -> capacity = other.capacity;

        

        for(int i = 0; i < other.size; ++i){

            this -> bars[i] = other.bars[i];

        }

        

        return *this;

    }


    

    //Step 5: clear() =>frees memory and resets all private member variables to default values => DONE

    void clear(){

        

        while(bars != nullptr){

            delete[] bars;

        }

        

        bars = nullptr;

        size = 0;

        capacity = 4;

        frame = "";

        

        

        /*

        delete[] bars;

        

        //bars = new Bar[capacity]; //FIXME

        this -> bars = new Bar[this -> capacity];

        //this -> size = 0;

        //this -> capacity = 0;

        

        size = 0;

        frame = "";

        //bars = NULL;

        capacity = 0;*/

        

    }

    

    

    //Step 6: destructor => called automatically by C++ to free the memory associated by the BarChart => DONE

    virtual ~BarChart(){


        //cout << "Destructor called." << endl;

        

        if(bars != nullptr){

            delete[] bars;

        }

        //else{

            //cout << "The nullptr was reached." << endl;

        //}

    }

    

    

    //Step 7: setFrame() => DONE

    void setFrame(string frame) {

    

        this -> frame = frame;

    }

    

    

    //Step 8: getFrame() => returns the frame of the BarChart oboject => DONE

    string getFrame(){

        

        return this -> frame;

    }


    

    //Step 9: addBar() => adds a Bar to the BarChart => DONE

    bool addBar(string name, int value, string category){

        

        if(this -> size == this -> capacity){

            //int newCapacity = capacity * 2;

            //Bar*

            return false; //No room

        }

        else{

            Bar newBar = Bar(name, value, category);

            this -> bars[size] = newBar;

            this -> size++;

            return true; //Successfully added room

        }


        return false;

    }

    

    

    //Step 10: getSize() => returns the size (number of bars) of the BarChart object => DONE

    int getSize() const{

    

        return this -> size;

    }

    

    

    //Step 11: operator[] => returns Bar element in BarChart.

    Bar& operator[](int i){

        

        Bar b;

        if(i < 0 || i >= size){

            throw std::out_of_range ("BarChart: i is out of bounds");

        }

        

        //FIXME

        

        return this -> bars[i];

    }

    

    

    //Step 12: dump() => used for printing the BarChart object => DONE

    // Recommended for debugging purposes.  output is any stream (cout,

    // file stream, or string stream).

    // Format:

    // "frame: 1

    // aname 5 category1

    // bname 4 category2

    // cname 3 category3" <-newline here

    void dump(ostream &output){

        

        //FIXME

        sort(bars, bars + size, greater<Bar>());

        

        //cout << "Test." << endl;

        

        output << "frame: " << this -> getFrame() << endl;

        

        for(int i = 0; i < size; i++){

            output << bars[i].getName() << " " << bars[i].getValue() << " " << bars[i].getCategory() << endl;

        }

    }

    

    

    //Step 13: graph() => used for printing out the bar => DONE

    // output is any stream (cout, file stream, string stream)

    // colorMap maps category -> color

    // top is number of bars you'd like plotted on each frame (top 10? top 12?)

    void graph(ostream &output, map<string, string> &colorMap, int top){

        int lenMax = 60;  // this is number of BOXs that should be printed for the top bar (max value)

        int count = 0;

        

        sort(bars, bars + size, greater<Bar>());

        

        if(top > size){

            top = size;

        }

        else{

            top = top;

        }

        

        int i = 0;

        

        do{

            string holder = "";

            double numerator = double(this -> bars[i + 1].getValue());

            double denominator = double(this -> bars[0].getValue());

            string color = colorMap[this -> bars[i].getCategory()];

            /*string color = "\033[1;36m";  // you should get this from colorMap

            

            for (int i = 0; i < lenMax; i++) {

                holder += BOX;

            }

            output << color << holder << endl;*/


          //Print the growing boxes in lines

            int j = 0;

            do{

                holder += BOX;

                j++;

            }while(j < lenMax);

            

            output << color << holder << " " << this -> bars[i].getName() << " " << this -> bars[i].getValue() << endl;

            lenMax = (numerator/denominator) * 60;

            i++;

            count++;

            

        }while(i < top);

        

    }

    

};


