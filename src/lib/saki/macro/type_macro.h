/**
* @file type_macro.h
* @brief element_type,value_type,pointer,reference‚ğ©“®’è‹`
* @author ÎR —I
* @date 2018/12/13
*/
#pragma once
#ifndef SAKI_TYPE_MACRO_2018_12_13
#define SAKI_TYPE_MACRO_2018_12_13
#include <type_traits> //for remove_cv_t

#ifndef SAKI_TYPE_MACRO
#define SAKI_TYPE_MACRO(T)				\
using element_type = T;					\
using value_type = std::remove_cv_t<T>;	\
using pointer = T*;						\
using reference = T&;					\

#endif //SAKI_TYPE_MACRO

#endif //SAKI_TYPE_MACRO_2018_12_13