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
      const HASH_INDEX_T powers[6] {1, 36, (HASH_INDEX_T)pow(36.0, 2), (HASH_INDEX_T)pow(36.0, 3), (HASH_INDEX_T)pow(36.0, 4), (HASH_INDEX_T)pow(36.0, 5)};

      /*
      failed attempt
      for (int index = 0; index < k.size() && index < 28; index++)
      {
          HASH_INDEX_T charVal = letterDigitToNumber(std::tolower(k[index]));
          HASH_INDEX_T rConstant = rValues[4 - (index / 6)];
          HASH_INDEX_T exConstant;
          if ((k.size() - 1) / 6 - index / 6 == 0) // if we are in the final group
          {
            rConstant = rValues[4 - ( (k.size() - 1) / 6 )];
            exConstant = powers[(k.size() - 1) % 6 - index % 6];
          }
          else
          {
            rConstant = rValues[4 - index / 6];
            exConstant = powers[5 - index % 6];
          }
       
          aggregate += (charVal * exConstant * rConstant);
      }*/
      for (int index = k.size() - 1; index >= 0; index--)
      {
        int distFromEnd = k.size() - index - 1;
        HASH_INDEX_T charVal = letterDigitToNumber(std::tolower(k[index]));
        HASH_INDEX_T rConst = rValues[4 - distFromEnd / 6];
        HASH_INDEX_T expConst = powers[distFromEnd % 6];

        aggregate = aggregate + (charVal * expConst * rConst);
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
