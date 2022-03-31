#include <tree.hpp>


tree::tree(tree_branch root): root(root){
}

void tree::init_branch(data_tree<tree_branch> *parent) const{
    tree_branch branch = parent->get_value();
    float all_branch_len = branch.length_to_branch + branch.branch_length;
    std::vector<tree_child_branch_info> sub_branches = create_sub_branches(
        (tree_parent_branch_info){
            .end_widthwidth = branch.width_to,
            .length_to_branch = all_branch_len,
            .angle = branch.angle,
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
            }
        );

        if((all_branch_len + child_info.branch_length) > 1.0) continue;        

        init_branch(&child);
        parent->add_child(child);
    }
}

void tree::init(){
    init_branch(&root);
}