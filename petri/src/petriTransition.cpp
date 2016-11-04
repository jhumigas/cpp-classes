#include <petriTransition.hpp>
#include <petriNetwork.hpp>
#include <iostream>

petri::Transition::Transition(const std::string& name, Network* network)
  :name(name), net(network){}

void petri::Transition::addInput(poolIdf input_pool, unsigned int nb_token_required){
    input.push_back(std::make_pair(input_pool, nb_token_required));
}

void petri::Transition::addOutput(poolIdf output_pool, unsigned int nb_token_produced){
    input.push_back(std::make_pair(output_pool, nb_token_produced));
}

petri::Transition::operator bool()   const{
 for(auto & value: input ){
    if(this->net->pools[value.first].nbTokens >= value.second){
      return false;
    }
 }
 return true;
}
void petri::Transition::operator()() const{
    for(auto & value: input){
      this->net->pools[value.first].nbTokens-= value.second;
    }for(auto & value:output){
      this->net->pools[value.first].nbTokens+= value.second;
    }
    std::cout << "Executed transition:\"" << name << std::endl;
}