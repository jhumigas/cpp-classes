
// Nécessaire pour importer la fonction assert().
#include <assert.h>

// On a besoin des déclarations de ColorMap pour définir ses méthodes
#include "TreeBasedColorMap.h"

namespace colormap {
    TreeBasedColorMap::TreeBasedColorMap(int n) {
        colors_ = std::vector<TreeBasedColorMap::color_type>();
        inner_map_ = std::map<TreeBasedColorMap::color_type, TreeBasedColorMap::index_type>();
        // Used to eliminate reallocations if the number of elements is known beforehand
        colors_.reserve(n);
    }

    void TreeBasedColorMap::clear(void){
        colors_.clear();
        inner_map_.clear();
    }
    void TreeBasedColorMap::add(const TreeBasedColorMap::color_type& color){
        colors_.push_back(color);
        inner_map_[color] = colors_.size()-1;
    }

    TreeBasedColorMap::index_type TreeBasedColorMap::operator()(const TreeBasedColorMap::color_type& color){
        try{
            return inner_map_[color];
        }catch(std::exception& e){
            throw TreeBasedColorMap::MissingColor(color);
        }

        
    }

    const TreeBasedColorMap::color_type& TreeBasedColorMap::operator()(TreeBasedColorMap::index_type index) const{
         return colors_.at(index);
    }
};
