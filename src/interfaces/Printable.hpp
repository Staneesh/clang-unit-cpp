#pragma once

class Printable
{
protected:
    virtual void print() const = 0;

public:
    virtual ~Printable() = default;
};