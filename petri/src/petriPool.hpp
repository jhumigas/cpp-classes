#pragma once

#include <string>

namespace petri {

    class Pool {

        std::string name;
        unsigned int nbTokens;

        public:
          //Pool();
          Pool(const std::string& name, unsigned int nbTokens);
          
    };
}