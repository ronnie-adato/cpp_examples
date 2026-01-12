#pragma once

#include <iostream>
#include <ostream>
#include "Message.hpp"

class Handler
{
    friend std::ostream &operator<<(std::ostream &stream, const Handler &ranges);

   public:
    Handler() = default;
    virtual ~Handler() = default;
    virtual std::string get_type() const = 0;
    // Default Message1 handler for all Handlers
    virtual void handle(Message1 *msg);
    // Default Message2 handler (can be overridden)
    virtual void handle(Message2 *msg);
    // Default Message3 handler (can be overridden)
    virtual void handle(Message3 *msg);
};

class Handler1 : public Handler
{
   public:
    Handler1() = default;
    ~Handler1() override = default;
    std::string get_type() const override;
    // Message1 handled by base
    void handle(Message2 *msg) override;
};

class Handler2 : public Handler
{
   public:
    Handler2() = default;
    ~Handler2() override = default;
    std::string get_type() const override;
    // Message1 handled by base
    void handle(Message2 *msg) override;
    void handle(Message3 *msg) override;
};
