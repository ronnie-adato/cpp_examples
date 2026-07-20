#pragma once

#include <iostream>
#include <ostream>
#include "Message.hpp"

class Handler
{
    friend std::ostream& operator<<(std::ostream& stream, const Handler& ranges);

   public:
    Handler() = default;
    virtual ~Handler() = default;
    virtual std::string get_type() const = 0;
    // Default handlers provide the fallback behavior for derived handlers.
    virtual void handle(Message1* msg);
    virtual void handle(Message2* msg);
    virtual void handle(Message3* msg);
};

class Handler1 : public Handler
{
   public:
    Handler1() = default;
    ~Handler1() override = default;
    std::string get_type() const override;
    // Handler1 customizes Message2 and inherits the other fallbacks.
    void handle(Message2* msg) override;
};

class Handler2 : public Handler
{
   public:
    Handler2() = default;
    ~Handler2() override = default;
    std::string get_type() const override;
    // Handler2 customizes two message types and inherits Message1 handling.
    void handle(Message2* msg) override;
    void handle(Message3* msg) override;
};
