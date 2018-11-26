#ifndef SELECT_H
#define SELECT_H

#include <QDialog>

namespace Ui {
class Select;
}

class Select : public QDialog
{
    Q_OBJECT

public:
    explicit Select(QWidget *parent = 0);

    int base_pos_x;
    int base_pos_y;

    int addtion_x;
    int addtion_y;

    bool need_show;

    ~Select();

private:
    Ui::Select *ui;
};

#endif // SELECT_H
