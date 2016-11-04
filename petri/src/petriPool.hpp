#pragma once

#include <string>

namespace petri {

    class Pool {
        friend class Transition;
        friend class Network;

        std::string name;
        unsigned int nbTokens;

        public:
          //Pool();
          Pool(const std::string& name, unsigned int nbTokens);
          
    };
}