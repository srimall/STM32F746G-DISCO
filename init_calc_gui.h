#ifndef INIT_CALC_GUI
#define INIT_CALC_GUI

#include <stdint.h>
#include "variables.h"
#include <string>
void init_calc_gui();
void write_to_field(const char * display_value);
void write_to_field_line(const char  display_value);
void write_to_field_char_array(const char * display_value);
void write_to_field_string(std::string num);
char  get_pressed(uint16_t x,uint16_t y);
bool is_digit(char value);
bool is_op(char value);
bool is_clear(char value);
bool is_equal(char value);
OP get_operation(char value);
std::string calculate(uint32_t num1, uint32_t num2, OP operation);


#endif