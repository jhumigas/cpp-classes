#include <iostream>
#include <petriNetwork.hpp>

bool petri::Network::operator()() {
  std::cerr << "petri::Network::operator()() : to be done" << std::endl;
  return false;
}

petri::poolIdf petri::Network::makePool(const std::string& pool_name, unsigned int nb_tokens) {
  std::cerr << "petri::Network::makePool(\"" << pool_name
	    << "\", " << nb_tokens << ") : to be done" << std::endl;
  return 0;
}
    
petri::tranIdf petri::Network::makeTransition(const std::string& transition_name) {
  std::cerr << "petri::Network::makeTransition(\"" << transition_name
	    << "\") : to be done" << std::endl;
  return 0;
}

void petri::Network::linkIn(tranIdf      transition,
			    poolIdf      pool,
			    unsigned int nb_tokens_in) {
  std::cerr << "petri::Network::linkIn (" << transition
	    << ", " << pool
	    << ", " << nb_tokens_in
	    << ") : to be done" << std::endl;
}

void petri::Network::linkOut(tranIdf      transition,
			     poolIdf      pool,
			     unsigned int nb_tokens_out) {
  std::cerr << "petri::Network::linkOut(" << transition
	    << ", " << pool
	    << ", " << nb_tokens_out
	    << ") : to be done" << std::endl;
}

    
