#pragma once
#include_next <string>

class Message
{
    // Message class implementation
   public:
    Message() = default;
    virtual ~Message() = default;
    virtual std::string get_type() const = 0;
};

class Message1 : public Message
{
    // Message1 class implementation
   public:
    std::string get_type() const override
    {
        return "Message1";
    }
};

class Message2 : public Message
{
    // Message2 class implementation
   public:
    std::string get_type() const override
    {
        return "Message2";
    }
};

class Message3 : public Message
{
    // Message3 class implementation
   public:
    std::string get_type() const override
    {
        return "Message3";
    }
};
