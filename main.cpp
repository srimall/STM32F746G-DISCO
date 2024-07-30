#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
#include "init_calc_gui.h"
#include <cstdint>
#include "variables.h"
#include "string"

//typedef enum {ADD,SUB,MULT,DIV} OP;
int main()
{
    TS_StateTypeDef TS_State;
    uint16_t x, y;
    uint8_t text[30];
    uint8_t status;
    uint8_t idx;
    uint8_t cleared = 0;
    uint8_t prev_nb_touches = 0;
    char pressed;
    uint32_t num1,num2,result;

   

    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

    //BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN DEMO", CENTER_MODE);
    HAL_Delay(1000);

    status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
    if (status != TS_OK) {
        BSP_LCD_Clear(LCD_COLOR_RED);
        BSP_LCD_SetBackColor(LCD_COLOR_RED);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN INIT FAIL", CENTER_MODE);
    } else {
        BSP_LCD_Clear(LCD_COLOR_GREEN);
        BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        //BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"TOUCHSCREEN INIT OK", CENTER_MODE);
    }

    HAL_Delay(1000);
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    //BSP_LCD_SetFont(&Font12);
   // BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
   // BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    init_calc_gui();
    uint8_t counter = 5;
    //char number1[7]="      ";
    //char number2[7]="      ";
    string number1;
    string number2;
    string res;
    NUMBER which_num = NUM1;
    OP operation = ZERO; // Default value
    while(1) {
        BSP_TS_GetState(&TS_State);
        if (TS_State.touchDetected) {
            x = TS_State.touchX[idx];
            y = TS_State.touchY[idx];
            pressed = get_pressed(x,y);
            if (is_digit(pressed)) {
                if (which_num == NUM1) {
                    number1 += pressed; 
                    write_to_field_string(number1);
                } else if (which_num == NUM2) {                    
                    number2 += pressed;                   
                    write_to_field_string(number2);
                }           
            } else if (is_op(pressed)) {
                operation = get_operation(pressed);
                which_num = NUM2;
                BSP_LCD_ClearStringLine(1);
            } else if (is_clear(pressed)) {
                BSP_LCD_ClearStringLine(1);
                which_num = NUM1;
                number1.clear();
                number2.clear();
                //counter = 5;
            } else if (is_equal(pressed)) {
                num1 = stoi(number1);
                num2 = stoi(number2);
                which_num = NUM1;
                res = calculate(num1, num2, operation);
                write_to_field_string(res);

                
                
                
            }

            //write_to_field_line(pressed);
        }
        BSP_TS_ResetTouchData(&TS_State);
        HAL_Delay(100);

    }


    while(0) {

        BSP_TS_GetState(&TS_State);
        if (TS_State.touchDetected) {
            // Clear lines corresponding to old touches coordinates
            if (TS_State.touchDetected < prev_nb_touches) {
                for (idx = (TS_State.touchDetected + 1); idx <= 5; idx++) {
                    BSP_LCD_ClearStringLine(idx);
                }
            }
            prev_nb_touches = TS_State.touchDetected;

            cleared = 0;

            sprintf((char*)text, "Touches: %d", TS_State.touchDetected);
            BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);

            for (idx = 0; idx < TS_State.touchDetected; idx++) {
                x = TS_State.touchX[idx];
                y = TS_State.touchY[idx];
                sprintf((char*)text, "Touch %d: x=%d y=%d    ", idx+1, x, y);
                BSP_LCD_DisplayStringAt(0, LINE(idx+1), (uint8_t *)&text, LEFT_MODE);
            }

            BSP_LCD_DrawPixel(TS_State.touchX[0], TS_State.touchY[0], LCD_COLOR_ORANGE);
        } else {
            if (!cleared) {
                BSP_LCD_Clear(LCD_COLOR_BLUE);
                sprintf((char*)text, "Touches: 0");
                BSP_LCD_DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);
                cleared = 1;
            }
        }
    }
}
