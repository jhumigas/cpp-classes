
// Nécessaire pour importer la fonction assert().
#include <assert.h>

// On a besoin des déclarations de VectorBasedColorMap pour définir ses méthodes
#include "VectorBasedColorMap.h"

namespace colormap {

    VectorBasedColorMap::VectorBasedColorMap(int n) : colors_(std::vector<color_type>(n)){}

    void VectorBasedColorMap::clear(void){
        colors_.clear();
    }
    void VectorBasedColorMap::add(const VectorBasedColorMap::color_type& color){
        colors_.push_back(color);
    }

    VectorBasedColorMap::index_type VectorBasedColorMap::operator()(const VectorBasedColorMap::color_type& color) const{
        for(int i =0; i != colors_.size(); ++i){
            if( colors_.at(i) == color){
                return i;
            }
        }

        throw VectorBasedColorMap::MissingColor(color);
    }

    const VectorBasedColorMap::color_type& VectorBasedColorMap::operator()(VectorBasedColorMap::index_type index) const{
         return colors_.at(index);
    }
};
