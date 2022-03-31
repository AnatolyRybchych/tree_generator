#pragma once

#include <functional>
#include <vector>
#include <math.h>
#include <glm/vec2.hpp>

#include <data_tree.hpp>


class tree_parent_branch_info{
public:
    float end_widthwidth;//value in range [0, 1]
    float length_to_branch;//value in range [0, 1]
    float angle;//value in range [0, 1]
};

class tree_child_branch_info{
public:
    float end_width;
    float branch_length;
    float angle;
};

class tree_branch{
public:
    float width_from;//value in range [0, 1]
    float width_to;//value in range [0, 1]
    float branch_length;//value in range [0, 1]
    float length_to_branch;//value in range [0, 1]
    float angle;//value in range [0, 1]
};

class tree{
public:
    tree(tree_branch root);
    void init();
    virtual std::vector<tree_child_branch_info> create_sub_branches(tree_parent_branch_info parent) const = 0;
    data_tree<tree_branch> get_root() const;

private:
    void init_branch(data_tree<tree_branch> *parent) const;
    data_tree<tree_branch> _root;
};
