//defines what each screen needs
#pragma once

class Screen {
public:
    virtual void draw() = 0;
    virtual void update() {}
    virtual ~Screen() {}
};