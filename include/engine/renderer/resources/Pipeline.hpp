#pragma once

class Pipeline
{
public:
    virtual ~Pipeline() = default;

    virtual bool is_valid() const = 0;
};
