#include <iostream>
// Nécessaire pour importer la fonction assert().
#include <assert.h>

// On a besoin des déclarations de VectorBasedColorMap pour définir ses méthodes
#include "VectorBasedColorMap.h"

namespace colormap {

    VectorBasedColorMap::VectorBasedColorMap(int n) {
        colors_ = std::vector<VectorBasedColorMap::color_type>();
        // Used to eliminate reallocations if the number of elements is known beforehand
        colors_.reserve(n);
    }

    void VectorBasedColorMap::clear(void){
        colors_.clear();
    }
    void VectorBasedColorMap::add(const VectorBasedColorMap::color_type& color){
        colors_.push_back(color);
    }
    void VectorBasedColorMap::place(int i, const VectorBasedColorMap::color_type& color){
        //colors_[i] = color;
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
