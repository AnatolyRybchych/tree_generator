#include <tree.hpp>


tree::tree(tree_branch root): root(root){
}

std::vector<glm::vec2> tree::triangulate_root(){
    std::vector<glm::vec2> res;
    float root_top_width = root.get_value().width_from;
    triangulate_branch(&res, &root, glm::vec2(0, 0), 
        glm::vec2(-root_top_width * 0.5, 0), glm::vec2(root_top_width * 0.5, 0));
    return res; 
}

void tree::triangulate_branch(std::vector<glm::vec2> *lineVertices, data_tree<tree_branch> *root_branch, 
glm::vec2 pos, glm::vec2 root_bg_p1, glm::vec2 root_bg_p2) const{
    auto root = root_branch->get_value();
    for (size_t i = 0; i < root_branch->get_length(); i++){
        auto child_branch = (*root_branch)[i];
        auto child = child_branch.get_value();

        float axis_direction_x = sinf(glm::pi<float>() * child.angle);
        float axis_direction_y = cosf(glm::pi<float>() * child.angle);

        float axis_perpendicular_direction_x = sinf(glm::pi<float>() * child.angle + glm::pi<float>() * 0.5);
        float axis_perpendicular_direction_y = cosf(glm::pi<float>() * child.angle + glm::pi<float>() * 0.5);

        glm::vec2 branch_axis_end_offset(
            child.branch_length * axis_direction_x,
            child.branch_length * axis_direction_y
        );

        glm::vec2 branch_axis_end = pos + branch_axis_end_offset;

        glm::vec2 p3 = branch_axis_end + glm::vec2(
            -child.width_to * 0.5 * axis_perpendicular_direction_x,
            -child.width_to * 0.5 * axis_perpendicular_direction_y
        );

        glm::vec2 p4 = branch_axis_end + glm::vec2(
            child.width_to * 0.5 * axis_perpendicular_direction_x,
            child.width_to * 0.5 * axis_perpendicular_direction_y
        );

        lineVertices->push_back(root_bg_p1);
        lineVertices->push_back(root_bg_p2);
        lineVertices->push_back(p3);
        lineVertices->push_back(root_bg_p2);
        lineVertices->push_back(p3);
        lineVertices->push_back(p4);


        triangulate_branch(lineVertices, &child_branch, branch_axis_end, p3, p4);
    }
}

void tree::init_branch(data_tree<tree_branch> *parent) const{
    tree_branch branch = parent->get_value();
    float all_branch_len = branch.length_to_branch + branch.branch_length;
    std::vector<tree_child_branch_info> sub_branches = create_sub_branches(
        (tree_parent_branch_info){
            .end_width = branch.width_to,
            .length_to_branch = all_branch_len,
            .angle = branch.angle,
            .generation = branch.generation,
        } 
    );

    for(auto child_info:sub_branches){
        data_tree<tree_branch> child(
            (tree_branch){
                .width_from = branch.width_to,
                .width_to = child_info.end_width,
                .branch_length = child_info.branch_length,
                .length_to_branch = all_branch_len,
                .angle = (branch.angle * child_info.branch_length) / (child_info.branch_length + all_branch_len)
                + (child_info.angle * all_branch_len) / (child_info.branch_length + all_branch_len),
                .generation = child_info.generation,
            }
        );

        if((all_branch_len + child_info.branch_length) > 1.0) {
            child.get_value().width_to = 0;
            parent->add_child(child);
            continue; 
        }
               

        init_branch(&child);
        parent->add_child(child);
    }
}

void tree::init(){
    init_branch(&root);
}