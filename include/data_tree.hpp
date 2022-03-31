#pragma once

template <typename T>
class data_tree{
private:
    T _value;
    std::vector<data_tree> _child;
public:
    data_tree(T root_value){
        _value = root_value;
    }

    void add_child(data_tree<T> child){
        _child.push_back(child);
    }

    T get_value(){
        return _value;
    }

    size_t get_length(){
        return _child.size();
    }
    
    data_tree<T> operator[] (size_t index){
        return _child[index];
    }
};