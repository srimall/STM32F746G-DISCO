
#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include <cstdint>
#include <string>
#include "variables.h"

void init_calc_gui() {

BSP_LCD_SetFont(&Font16);
    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

    // Calculator Display
    BSP_LCD_DrawRect(10, 10, 420, 50);

    // Number Boxes
    BSP_LCD_DrawRect(10, 100, 100, 50); //1
    BSP_LCD_DrawRect(10, 152, 100, 50); //2
    BSP_LCD_DrawRect(10, 204, 100, 50); //3

    BSP_LCD_DrawRect(112, 100, 100, 50); //4
    BSP_LCD_DrawRect(112, 152, 100, 50); //5
    BSP_LCD_DrawRect(112, 204, 100, 50); //6

    BSP_LCD_DrawRect(214, 100, 100, 50); //7
    BSP_LCD_DrawRect(214, 152, 100, 50); //8
    BSP_LCD_DrawRect(214, 204, 100, 50); //9

    BSP_LCD_DrawRect(326, 100, 50, 50);
    BSP_LCD_DrawRect(326, 152, 50, 50);
    BSP_LCD_DrawRect(326, 204, 50, 50);

    BSP_LCD_DrawRect(378, 100, 50, 50);
    BSP_LCD_DrawRect(378, 152, 50, 50);
    BSP_LCD_DrawRect(378, 204, 50, 50);

    //BSP_LCD_DrawRect(430, 100, 45, 50);
   // BSP_LCD_DrawRect(430, 152, 45, 50);
   // BSP_LCD_DrawRect(430, 204, 45, 50);

    BSP_LCD_DisplayStringAt(50,120, (uint8_t *)"1",LEFT_MODE);
    BSP_LCD_DisplayStringAt(50,172, (uint8_t *)"2",LEFT_MODE);
    BSP_LCD_DisplayStringAt(50,224, (uint8_t *)"3",LEFT_MODE);

    BSP_LCD_DisplayStringAt(152,120, (uint8_t *)"4",LEFT_MODE);
    BSP_LCD_DisplayStringAt(152,172, (uint8_t *)"5",LEFT_MODE);
    BSP_LCD_DisplayStringAt(152,224, (uint8_t *)"6",LEFT_MODE);

    BSP_LCD_DisplayStringAt(254,120, (uint8_t *)"7",LEFT_MODE);
    BSP_LCD_DisplayStringAt(254,172, (uint8_t *)"8",LEFT_MODE);
    BSP_LCD_DisplayStringAt(254,224, (uint8_t *)"9",LEFT_MODE);

    BSP_LCD_DisplayStringAt(346,120, (uint8_t *)"+",LEFT_MODE);
    BSP_LCD_DisplayStringAt(346,172, (uint8_t *)"-",LEFT_MODE);
    BSP_LCD_DisplayStringAt(346,224, (uint8_t *)"*",LEFT_MODE);

    BSP_LCD_DisplayStringAt(398,120, (uint8_t *)"/",LEFT_MODE);
    BSP_LCD_DisplayStringAt(398,172, (uint8_t *)"=",LEFT_MODE);
    BSP_LCD_DisplayStringAt(398,224, (uint8_t *)"c",LEFT_MODE);

}


void write_to_field(const char * display_value) {
    BSP_LCD_DisplayStringAt(30,25, (uint8_t *)display_value,LEFT_MODE);
   // BSP_LCD_DisplayStringAt(398,224, (uint8_t *)"C",LEFT_MODE);

}

void write_to_field_line(const char display_value) {
    uint8_t text[30];
    BSP_LCD_ClearStringLine(LINE(1));
    uint8_t idx = 0;

    sprintf((char*)text, "%c",display_value);
    //for (idx =0; idx <= 4; idx++) {
    //                BSP_LCD_ClearStringLine(idx);
   //             }
    BSP_LCD_DisplayStringAt(30,LINE(1), (uint8_t *)&text,LEFT_MODE);
   // BSP_LCD_DisplayStringAt(398,224, (uint8_t *)"C",LEFT_MODE);

}

void write_to_field_char_array(const char * display_value) {
    BSP_LCD_ClearStringLine(1);
    uint8_t text[30];
    sprintf((char*)text, "%s",display_value);
    BSP_LCD_DisplayStringAt(10, LINE(1), (uint8_t *)&text, LEFT_MODE);
}

void write_to_field_string(string num) {
    string temp = num + '\0';
    BSP_LCD_ClearStringLine(1);
    uint8_t text[30];
    sprintf((char*)text, "%s",temp.c_str());
    BSP_LCD_DisplayStringAt(10, LINE(1), (uint8_t *)text, LEFT_MODE);

}


char get_pressed(uint16_t x, uint16_t y) {
    if ( 10 < x & x < 110 ) {
        if ( 100 < y & y < 152)       return '1';
        else if ( 152 < y & y < 204 ) return '2';
        else if ( 204 < y & y < 254 ) return '3';

    } else if ( 110 < x & x < 212 ) {
        if ( 100 < y & y < 152)       return '4';
        else if ( 152 < y & y < 204 ) return '5';
        else if ( 204 < y & y < 254 ) return '6';
    } else if ( 214 < x & x < 326 ) {
        if ( 100 < y & y < 152)       return '7';
        else if ( 152 < y & y < 204 ) return '8';
        else if ( 204 < y & y < 254 ) return '9';
    } else if ( 326 < x & x < 378 ) {
        if ( 100 < y & y < 152)       return '+';
        else if ( 152 < y & y < 204 ) return '-';
        else if ( 204 < y & y < 254 ) return '*';
    } else if ( 378 < x & x < 400 ) {
        if ( 100 < y & y < 152)       return '/';
        else if ( 152 < y & y < 204 ) return '=';
        else if ( 204 < y & y < 254 ) return 'c';
    } else  {
        return ' ';
    }
    return ' ';
}

bool is_digit(char value) {
    if ( (value == '1' ) | (value == '2') | value == '3'| (value == '4') | (value == '5') | (value == '6') | (value=='7') | (value=='8') | (value=='9') | (value=='0') ) {
        return true;
    } else  return false;
}

bool is_op(char value) {
    if ( (value == '+' ) | (value == '-') | value == '*'| (value == '/') ) {
        return true;
    } else  return false;
}

bool is_clear(char value) {
    if ( value == 'c' ) {
        return true;
    } else  return false;
}

OP get_operation(char value) {
    if( value == '+') return ADD;
    else if ( value == '-') return SUB;
    else if ( value == '*') return MULT;
    else if ( value == '/') return DIV;
    else return ZERO ;
}

bool is_equal(char value) {
    if (value == '=') return true;
    else return false;
}

string calculate(uint32_t num1, uint32_t num2, OP operation) {
    if(operation == ADD) return to_string(num1 + num2);
    else if(operation == SUB) return to_string(num1 - num2);
    else if(operation == MULT) return to_string(num1 * num2);
    else if(operation == DIV) return to_string(num1 / num2);
    else return NULL;
    
}
