#include "select_control.h"

select_control::select_control()
{
    Select* tmp;
    for(int i =0;i<8;i++){
        this->store.push_back(new Select());
    }
    this->select_mode = MODE_SELECT_ADDTIONAL;
    tmp = this->store.at(0);
    tmp->addtion_x = -50;
    tmp->addtion_y = -50;
    tmp = this->store.at(1);
    tmp->addtion_x = 0;
    tmp->addtion_y = -50;
    tmp = this->store.at(2);
    tmp->addtion_x = 50;
    tmp->addtion_y = -50;
    tmp = this->store.at(3);
    tmp->addtion_x = -50;
    tmp->addtion_y = 0;
    tmp = this->store.at(4);
    tmp->addtion_x = 50;
    tmp->addtion_y = 0;
    tmp = this->store.at(5);
    tmp->addtion_x = -50;
    tmp->addtion_y = 50;
    tmp = this->store.at(6);
    tmp->addtion_x = 0;
    tmp->addtion_y = 50;
    tmp = this->store.at(7);
    tmp->addtion_x = 50;
    tmp->addtion_y = 50;
    this->Fresh_Mode();

}


void select_control::Set_Mode(SELECT_MODE arg){

}
void select_control::Fresh_Mode(){

    Select* tmp;

    switch(this->select_mode){

    case MODE_SELECT_ADDTIONAL:
        tmp = this->store.at(0);
        tmp->need_show = false;
        tmp = this->store.at(1);
        tmp->need_show = true;
        tmp = this->store.at(2);
        tmp->need_show = false;
        tmp = this->store.at(3);
        tmp->need_show = true;
        tmp = this->store.at(4);
        tmp->need_show = true;
        tmp = this->store.at(5);
        tmp->need_show = false;
        tmp = this->store.at(6);
        tmp->need_show = true;
        tmp = this->store.at(7);
        tmp->need_show = false;
        break;
    default:
        break;

    }
}
