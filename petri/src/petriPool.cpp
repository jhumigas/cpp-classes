#include <petriPool.hpp>

petri::Pool::Pool(const std::string& name, unsigned int nbTokens)
  :name(name), nbTokens(nbTokens){}