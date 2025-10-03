#ifndef UI_H
#define UI_H

class UI {
public:
    virtual ~UI();  // Add a virtual destructor
    virtual void draw() = 0; // Make pure virtual if abstract
protected:
    virtual void init_data() = 0; // same
    unsigned int VAO;
};

#endif