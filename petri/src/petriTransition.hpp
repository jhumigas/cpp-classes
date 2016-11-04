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
    using poolIdf = unsigned int;

    class Transition {

        friend class Network;

        std::string name;
        std::vector<std::pair<poolIdf, unsigned int>> input;
        std::vector<std::pair<poolIdf, unsigned int>> output;
        Network* net;

        public:
          Transition(const std::string& name, Network* network);
          
          /**
           * Adds an input to the transition
           *
           */
          void addInput(poolIdf input_pool, unsigned int nb_token_required);
          
           /**
            * Adds an output to the transition
            *
            */
          void addOutput(poolIdf output_pool, unsigned int nb_token_produced);
     
          /**
           * Checks if a transition is executable
           *
           */
          operator bool()   const;

          /**
           * Executes a transition
           *
           */
          void operator()() const;

    };
}