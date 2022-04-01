#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <math.h>
#include <glm/vec2.hpp>
#include <glm/ext/scalar_constants.hpp>

#include <data_tree.hpp>


class tree_parent_branch_info{
public:
    float end_width;//value in range [0, 1]
    float length_to_branch;//value in range [0, 1]  // length from start of tree root to branch end 
    float angle;//value in range [0, 1] //general angle of branch (makes smoother)
    int generation;//custom //can be used to create direct dependency between parent nad children branches 
};

class tree_child_branch_info{
public:
    float end_width;//value in range [0, 1] // width current branch axis end 
    float branch_length;//value in range [0, 1] // length from start of cuerrent branch to end of current branch
    float angle;//value in range [0, 1] //angle between parent and children branch
    int generation;//custom //can be used to create direct dependency between parent nad children branches 
};

class tree_branch{
public:
    float width_from;//value in range [0, 1] // width current branch axis start 
    float width_to;//value in range [0, 1] // width current branch axis end 
    float branch_length;//value in range [0, 1] // length from start of cuerrent branch to end of current branch
    float length_to_branch;//value in range [0, 1] // length from start of tree root to start of current branch 
    float angle;//value in range [0, 1] // angle of current branch axis 
    int generation;//custom //can be used to create direct dependency between parent nad children branches 
};

class tree{
public:
    tree(tree_branch root);
    void init();
    virtual std::vector<tree_child_branch_info> create_sub_branches(tree_parent_branch_info parent) const = 0;
    virtual std::vector<glm::vec2> triangulate_root() const;
    data_tree<tree_branch> root;

private:
    void init_branch(data_tree<tree_branch> *parent) const;
    void triangulate_branch(std::vector<glm::vec2> *lineVertices, const data_tree<tree_branch> *root_branch, 
        glm::vec2 pos, glm::vec2 root_bg_p1, glm::vec2 root_bg_p2) const;
    
};
