#include <iostream>
#include <petriNetwork.hpp>

bool petri::Network::operator()() {
  std::cout << "Start run ... " << std::endl;
  std::vector<unsigned int> available_transitions_idf;
  int i = 0;
  for(auto & value : transitions){
    if(value){
      available_transitions_idf.push_back(i);
    }
    i++;
  }
  if(available_transitions_idf.size() == 0){
    return false;
  }else{
	int rand_index;  
    rand_index = rand() % available_transitions_idf.size();
    transitions[available_transitions_idf[rand_index]]();
    return true;
  }
}

petri::poolIdf petri::Network::makePool(const std::string& pool_name, unsigned int nb_tokens) {
	pools.push_back(petri::Pool(pool_name, nb_tokens));
	std::cout << "Added pool: " << pool_name <<std::endl;
  return pools.size()-1;
}
    
petri::tranIdf petri::Network::makeTransition(const std::string& transition_name) {
	transitions.push_back(petri::Transition(transition_name, this));
	std::cout << "Added transition: " << transition_name << std::endl;
  return transitions.size()-1;
}

void petri::Network::linkIn(tranIdf      transition,
			    poolIdf      pool,
			    unsigned int nb_tokens_in) {
	transitions[transition].addInput(pool, nb_tokens_in);
	std::cout << transitions[transition].name << " - Added input pool " << pool<< " with required input tokens " << nb_tokens_in << std::endl;
}

void petri::Network::linkOut(tranIdf      transition,
			     poolIdf      pool,
			     unsigned int nb_tokens_out) {
  transitions[transition].addOutput(pool, nb_tokens_out);
	std::cout << transitions[transition].name << " - Added output pool " << pool << " with with required output tokens " << nb_tokens_out << std::endl;
}

// std::ofstream& petri::Network::operator<<(std::ofstream& of){
//   of << "digraph Petri {\n overlap=scale \n";
//   int i = 0;
//   for(auto& transition : transitions){
//     of << "transition"<< i << " [label=\"" << transition.name << "\", shape=box, color=red, style=bold]; \n";
//     ++i;
//   }
//   int j = 0;
//   for(auto& pool : pools){
//     of << "pool"<< j << " [label=\"" << pool.name << "\", color=blue, style=bold]; \n";
//     ++j;
//   }

//   of << "\n/* edges */";
  
//   int k = 0;
//   for(auto& transition : transitions){
//     for(auto& in : transition.input){
//       of << "pool" << in.first << " -> transition" << k <<" [label=\"" << in.second << "\"];";
//     }
//     for(auto& out : transition.output){
//       of << "transition" << k  << " -> pool" << out.first<<" [label=\"" << out.second << "\"];";
//     }

//     ++k;
//   }
  

//   of << "\n}";
// }
    
