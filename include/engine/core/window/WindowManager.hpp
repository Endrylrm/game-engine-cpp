#pragma once
#include <string>

class WindowManager
{
public:
    virtual ~WindowManager() = default;
    virtual bool onInit() = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual std::string getTitle() const = 0;
    virtual void *getWindowHandle() const = 0;
    virtual void quitGame() = 0;
};