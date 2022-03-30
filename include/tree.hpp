#pragma once

#include <functional>
#include <vector>
#include <math.h>
#include <glm/vec2.hpp>


class tree;
class value;
class body_interpolator;
class default_body_interpolator;


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

class tree{
public:
    tree();
    void init(float height, const body_interpolator *interpolator);

    data_tree<glm::vec2> get_frame() const;
private:
    float _height;
    void init_frame(const body_interpolator *interpolator);
    data_tree<glm::vec2> _frame;
};

//height is value in range {0, 1}
//body_width is value in range {0, 1}
//branches_spread is value in range {0, 1}
class value{
public:
    int branches_count;
    float body_width;
    float branches_spread;
private:
};

class body_interpolator{
public:
    virtual value get_value(value prev, float height) const = 0;
};


class default_body_interpolator: public body_interpolator{
public:
    default_body_interpolator(value initValue);
    virtual value get_value(const value prev, float height) const;
private:
    value _initValue;
};