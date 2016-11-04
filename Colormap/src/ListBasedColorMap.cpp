
// Nécessaire pour importer la fonction assert().
#include <assert.h>

// On a besoin des déclarations de ListBasedColorMap pour définir ses méthodes
#include "ListBasedColorMap.h"
#include <stdexcept>

namespace colormap {

	// Constructeur
	ListBasedColorMap::ListBasedColorMap(void) {
	}

	void ListBasedColorMap::clear(void) {
		colors_.clear();
	}

	void ListBasedColorMap::add(const ListBasedColorMap::color_type& color) {
		colors_.push_back(color);
	}
	ListBasedColorMap::index_type ListBasedColorMap::operator()(const ListBasedColorMap::color_type& color) const {
		int i = 0;
		for(std::list<ListBasedColorMap::color_type>::const_iterator it = this->colors_.begin(); it != this->colors_.end(); ++it, ++i){
            if(*it == color){
				return i;
			}
		}
	    throw ListBasedColorMap::MissingColor(color);
		return 0;
	}

	const ListBasedColorMap::color_type& ListBasedColorMap::operator()(ListBasedColorMap::index_type index) const {
        ListBasedColorMap::index_type i = 0;
		for(std::list<ListBasedColorMap::color_type>::const_iterator it = this->colors_.begin(); it != this->colors_.end(); ++it, ++i){
            if(i == index){
				return *it;
			}
		}
		throw std::runtime_error("Index out of bounds.");
	}
};
