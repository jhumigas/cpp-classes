
// Nécessaire pour importer la fonction assert().
#include <assert.h>

// On a besoin des déclarations de ListBasedColorMap pour définir ses méthodes
#include "ListBasedColorMap.h"

namespace colormap {

	// Constructeur
	ListBasedColorMap::ListBasedColorMap(void) {
	}

	void ListBasedColorMap::clear(void) {
	}

	void ListBasedColorMap::add(const ListBasedColorMap::color_type& color) {
	}
	ListBasedColorMap::index_type ListBasedColorMap::operator()(const ListBasedColorMap::color_type& color) const {
	}

	const ListBasedColorMap::color_type& ListBasedColorMap::operator()(ListBasedColorMap::index_type index) const {
	}
};
