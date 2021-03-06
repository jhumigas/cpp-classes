﻿#pragma once

#include <stdexcept>
#include <vector>
#include <map>

#include "rgb.h"

namespace colormap {
    class TreeBasedColorMap {
    public:
        typedef int index_type; 
        typedef rgb color_type;
    private:
        typedef std::vector<color_type> sequence_type;
        typedef std::map<color_type, index_type> map_type;
        sequence_type colors_;
        map_type inner_map_;
    public:

        class MissingColor : public std::runtime_error {
            color_type color_;
        public:
            MissingColor(const color_type& color) : std::runtime_error("Missing color"), color_(color) {}
            const color_type& color(void) { return color_;}
        };

        TreeBasedColorMap(int i);
        void clear(void);
        void add(const color_type& color);
        void place(int i,const color_type& color);

        index_type operator()(const color_type& color);

        const color_type& operator()(index_type index) const;
         
    };
};
