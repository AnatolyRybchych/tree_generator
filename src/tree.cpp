#include <tree.hpp>


tree::tree(tree_branch root): _root(root){
}

void tree::init_branch(data_tree<tree_branch> *parent) const{
    tree_branch branch = parent->get_value();
    float all_branch_len = branch.length_to_branch + branch.branch_length;
    std::vector<tree_child_branch_info> sub_branches = create_sub_branches(
        (tree_parent_branch_info){
            .angle = branch.angle,
            .end_widthwidth = branch.width_to,
            .length_to_branch = all_branch_len,
        }
    );

    for(auto child_info:sub_branches){
        data_tree<tree_branch> child(
            (tree_branch){
                .angle = (branch.angle * child_info.branch_length) / (child_info.branch_length + all_branch_len)
                + (child_info.angle * all_branch_len) / (child_info.branch_length + all_branch_len),

                .branch_length = child_info.branch_length + all_branch_len,

                .length_to_branch = all_branch_len,

                .width_from = branch.width_to,

                .width_to = child_info.end_width,
            }
        );

        parent->add_child(child);

        init_branch(&child);
    }
}

void tree::init(){
    init_branch(&_root);
}


data_tree<tree_branch> tree::get_root() const{
    return _root;
}
