#include <tree.hpp>

tree::tree():_frame(glm::vec2(0, -1)){

}

void tree::init(float height, const body_interpolator *interpolator){
    _height = height;
    init_frame(interpolator);
}

void tree::init_frame(const body_interpolator *interpolator){
    value val;
    for (float h = 0; h < _height; h+= 0.01){
        val = interpolator->get_value(val, h);
    }
    
}

data_tree<glm::vec2> tree::get_frame() const{
    return _frame;
}


default_body_interpolator::default_body_interpolator(value initValue){
    _initValue = _initValue;
}

value default_body_interpolator::get_value(value prev, float height) const{
    if(height == 0) return _initValue;

    value res = prev;

    res.branches_count = int(powf(height, 3) * 10);

    return res;
}


