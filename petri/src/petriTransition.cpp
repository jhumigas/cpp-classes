#include <petriTransition.hpp>
#include <petriNetwork.hpp>

petri::Transition::Transition(const std::string& name, Network* network)
  :name(name), net(network){}