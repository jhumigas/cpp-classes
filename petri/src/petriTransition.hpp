#pragma once

#include <string>
#include <vector>
#include <utility>

namespace petri {
    
    // Forward declaration to use Network as an attribute
    // Could have used in inclusion but this would have resulted in a mutual inclusion problem
    // i.e Network including petriNetwork.hpp and transition including the same file
    class Network;

    using tranIdf = unsigned int;

    class Transition {
        std::string name;
        std::vector<std::pair<unsigned int, unsigned int>> input;
        std::vector<std::pair<unsigned int, unsigned int>> output;
        Network* net;

        public:
          //Transition();
          Transition(const std::string& name, Network* network);
    };
}