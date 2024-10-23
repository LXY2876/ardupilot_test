

#include"Plane.h"
float jet_control::probe(void){
     
    if(index==NUM_POINT_NM){
        sort();
        Cmiu=2*c-action[max_index];
        return 2*c-action[max_index];
    }
        
    
    return index*10;

}
void jet_control::sort(void){
    uint8_t min_temp=reward[0];
    uint8_t max_temp=reward[0];
    min_index=0;
    max_index=0;
    for (uint8_t i=1;i<NUM_POINT_NM;i++){
        if (reward[i]<min_temp)
            {
                min_index=i;
                min_temp=reward[i];
            }
        else if(reward[i]>max_temp){
                max_index=i;
                max_temp=reward[i];
            }
    }
    uint8_t second_max_temp=0;
    second_max_index=0;
       for (uint8_t i=0;i<NUM_POINT_NM;i++){
        if (reward[i]>second_max_temp && i!=max_index)
            {
                second_max_index=i;
                second_max_temp=reward[i];
            }
    }
}
void jet_control::add_to_list(float f){


    action[index]=Cmiu;
    reward[index]=f;
    if(index==0)
        c=Cmiu;
    else{
        c=((index+1)*c+Cmiu)/(index+2);
    }
    index++;

}
float jet_control::iteration(float now_reward){
    float output;
    
    if(state==1){
        if(now_reward<reward[second_max_index] && now_reward>=reward[min_index])
            {
                c=c+(pre_Cmiu-action[max_index])/(index+1);
            }
        else if(now_reward<reward[min_index]){
                output=3*c-2*action[max_index];    
                state=2;
                pre_Cmiu=Cmiu;
                pre_reward=now_reward;
                Cmiu=output;
                return output;
        }else if(now_reward<reward[max_index] && now_reward>=reward[second_max_index])
        {
                output=c+0.5*(pre_Cmiu-c);
                state=3;
                pre_Cmiu=Cmiu;
                pre_reward=now_reward;
                Cmiu=output;
                return output;
        }else if(now_reward>=reward[max_index]){
                output=c+0.5*(action[max_index]-c);
                state=4;
                pre_Cmiu=Cmiu;
                pre_reward=now_reward;
                Cmiu=output;
                return output;
        }else{
             shrink();
        }
    }else if(state==2){
        if(now_reward<pre_reward)
        {
            c=c+(Cmiu-action[max_index])/(index+1);
            action[max_index]=Cmiu;
            reward[max_index]=now_reward;
        }else 
        {   
            c=c+(pre_Cmiu-action[max_index])/(index+1);
            action[max_index]=pre_Cmiu;
            reward[max_index]=pre_reward;
        }
    }
    else if (state==3){
        if(now_reward<pre_reward){
            c=c+(Cmiu-action[max_index])/(index+1);    
            action[max_index]=Cmiu;
            reward[max_index]=now_reward;
        }else{
            shrink();
        }
    }
    else if(state==4){
        if(now_reward<reward[max_index]){
            c=c+(Cmiu-action[max_index])/(index+1);    
            action[max_index]=Cmiu;
            reward[max_index]=now_reward;
        }  
    }
        

    output=constrain_float(2*c-action[max_index],0,100);
    pre_Cmiu=Cmiu;
    pre_reward=now_reward;
    Cmiu=output;
    state=1;
    return output;
}
void jet_control::shrink() {
    for (uint8_t i = 0; i < NUM_POINT_NM; i++) {
        action[i] = action[min_index] + 0.5 * (action[i] - action[min_index]);
    }
    c = 0.5 * (c + action[min_index]);
}