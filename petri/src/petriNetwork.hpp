#pragma once

#include <string>
#include <vector>
#include <petriPool.hpp>
#include <petriTransition.hpp>

namespace petri {

  using poolIdf = unsigned int;
  
  class Network  {
    friend class Pool;
    friend class Transition;
  private:
    std::vector<Pool> pools;
    std::vector<Transition> transitions;
    
  public:
    Network()                          = default;
    Network(const Network&)            = delete;
    Network& operator=(const Network&) = delete;

    /** 
     * Selects randomly one executable transition (if any) and
     * executes it.  
     *
     * @return true if an executable transition was found, false otherwise.
     */
    bool operator()();

    /**
     * Builds up a pool in the network.
     *
     * @param nb_tokens the number of token initially set in the pool.
     * @return an identifier of the created pool for further use.
     */
    poolIdf makePool(const std::string& pool_name, unsigned int nb_tokens);
    
    /**
     * Builds up a transition in the network.
     *
     * @return an identifier of the created transition for further use.
     */
    tranIdf makeTransition(const std::string& transition_name);
    
    /**
     * This connects a transition to one input pool.
     */
    void linkIn(tranIdf      transition,
		poolIdf      pool,
		unsigned int nb_tokens_in);

    /**
     * This connects a transition to one output pool.
     */
    void linkOut(tranIdf      transition,
		 poolIdf      pool,
		 unsigned int nb_tokens_out);
  };
    
}
