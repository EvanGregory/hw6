#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
      // Add your code here
      HASH_INDEX_T aggregate = 0;
      for (int index = 0; index < k.size() && index < 28; index++)
      {
          HASH_INDEX_T charVal = letterDigitToNumber(std::tolower(k[index]));
          HASH_INDEX_T rConstant = rValues[4 - (index / 6)];
          HASH_INDEX_T exConstant = (HASH_INDEX_T)pow(36.0, index % 6);
          aggregate += (charVal * exConstant * rConstant);
      }
      return aggregate;
    }

    // A likely helper function is to convert a-z,0-9 to an integer value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        size_t tempVal;
        if (letter >= 'a' && letter <= 'z')
            tempVal = (size_t)letter - 'a';
        else if (letter >= '0' && letter <= '9')
            tempVal = (size_t)letter - '0' + 26;
        else
            throw;
        return tempVal;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
