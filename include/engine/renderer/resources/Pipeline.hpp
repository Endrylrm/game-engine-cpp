#pragma once

class Pipeline
{
public:
    virtual ~Pipeline() = default;

    virtual bool isValid() const = 0;
};
