#ifndef BUTTON_H
#define BUTTON_H

#include "ui.h"

class Button : public UI {
public:
    Button();
    ~Button();

    void draw() override;
private:
    void init_data() override;
};

#endif