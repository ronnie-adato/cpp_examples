#pragma once
#include_next <string>

class Message
{
   public:
    Message() = default;
    virtual ~Message() = default;
    // Gives handlers a printable dynamic message type.
    virtual std::string get_type() const = 0;
};

class Message1 : public Message
{
   public:
    std::string get_type() const override
    {
        return "Message1";
    }
};

class Message2 : public Message
{
   public:
    std::string get_type() const override
    {
        return "Message2";
    }
};

class Message3 : public Message
{
   public:
    std::string get_type() const override
    {
        return "Message3";
    }
};
