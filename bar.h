
#include <iostream>

#include <string>

#include "myrandom.h" // used in graders, do not remove

using namespace std;



//Step 1: declare the private data members => DONE

class Bar{

    

 private:

    

    string name;

    int value;

    string category;

    int count;


 public:


    //Step 2: create a default constructor => DONE

    Bar(){

        

        /*string name = "";

        int value = 0;

Instructor
| 11/20 at 11:20 pm
Grading comment:

you shouldn't create variables to overshadow data members

        string category = "";

        

        this -> value = 0;

        this -> category = "";

        this -> name = "";*/

        

        value = 0;

        name = "";

        category = "";

        

    }


    

    //Step 3: create a parameterized constructor => DONE

    Bar(string name, int value, string category){

        

        this -> name = name;

        this -> value = value;

        this -> category = category;

        

    }


    

    //Step 4: create a desctructor => DONE

    virtual ~Bar() {

        

        //cout << "Destroying the Bar Chart." << endl;

        this -> value = 0;

        this -> name = "";

        this -> category = "";

        //cout << "The end of the program." << endl;

        

    }


    

    //Step 5: create a getter getName => DONE

    string getName() const{

        

        return this -> name;

    }


    

    //Step 6: create a getter getValue => DONE

    int getValue() const{

    

        return this -> value;

    }


    

    //Step 7: create a getter getCategory => DONE

    string getCategory() const{

        

        return this -> category;

    }


    

    //Step 8: create the operators => DONE

    bool operator<(const Bar &other) const{

        

        if(this -> value < other.value){

            return true;

        }

        else{

            return false;

        }

        

        //return true;

    }


    

    bool operator<=(const Bar &other) const{

        

        if(this -> value <= other.value){

            return true;

        }

        else{

            return false;

        }

        

        //return true;

    }


    

    bool operator>(const Bar &other) const{

        

        if(this -> value > other.value){

            return true;

        }

        else{

            return false;

        }

        

        //return true;

    }


    

    bool operator>=(const Bar &other) const{

        

        if(this -> value >= other.value){

            return true;

        }

        else{

            return false;

        }

        

        

        //return true;

    }

};


