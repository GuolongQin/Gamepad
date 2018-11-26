#ifndef SELECT_CONTROL_H
#define SELECT_CONTROL_H

#include <select.h>

typedef enum{
    MODE_SELECT_ADDTIONAL,
    MODE_SELECT_WORD,
    MODE_SELECT_DIRECTION,
    MODE_SELECT_OTHER
}SELECT_MODE;

class select_control
{
public:
    select_control();
    void Set_Mode(SELECT_MODE arg);

private:
    SELECT_MODE select_mode;
    QVector<Select*> store;
    void Fresh_Mode();
};

#endif // SELECT_CONTROL_H
