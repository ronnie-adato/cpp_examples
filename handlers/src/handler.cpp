#include "handler.hpp"
#include <ng-log/logging.h>

void Handler::handle(Message1 *msg)
{
    std::cout << get_type() << " handling " << msg->get_type() << " (default)" << std::endl;
}

void Handler::handle(Message2 *msg)
{
    std::cout << get_type() << " handling " << msg->get_type() << " (default)" << std::endl;
}

void Handler::handle(Message3 *msg)
{
    std::cout << get_type() << " not handling " << msg->get_type() << " (default)" << std::endl;
}

std::string Handler1::get_type() const
{
    return "Handler1";
}

void Handler1::handle(Message2 *msg)
{
    std::cout << get_type() << " handling " << msg->get_type() << " (" << get_type() << " specific)" << std::endl;
}

std::string Handler2::get_type() const
{
    return "Handler2";
}

void Handler2::handle(Message2 *msg)
{
    std::cout << get_type() << " handling " << msg->get_type() << " (" << get_type() << " specific)" << std::endl;
}

void Handler2::handle(Message3 *msg)
{
    std::cout << get_type() << " handling " << msg->get_type() << " (" << get_type() << " specific)" << std::endl;
}
