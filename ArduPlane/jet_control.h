
//  Nelder-Mead 
#pragma once
#include <stdint.h>

#define NUM_POINT_NM 5

class jet_control{

    public:

        uint16_t max_index;
        uint16_t min_index;
        uint8_t index=0;
        uint16_t second_max_index; 
        float action[NUM_POINT_NM];
        float reward[NUM_POINT_NM];
        void sort(void);
        float probe(void);
        void add_to_list(float f);
        float iteration(float now_reward);
    private:
        uint8_t state=0;
        
        float c=0;
        float pre_reward=0;//存储上上一轮迭代的结果(当下观测的)
        float pre_Cmiu=0;//存储上上一轮迭代的输出值
        float Cmiu=0;//存储上一轮迭代的输出值
        void shrink(); 
        
};