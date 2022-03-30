#include <tree.hpp>

tree::tree(){

}

void tree::init(float height, body_interpolator *interpolator){

}




default_body_interpolator::default_body_interpolator(value initValue){
    _initValue = _initValue;
}

value default_body_interpolator::get_value(const value *prev){
    if(prev == NULL) return _initValue;

    return *prev;
}


