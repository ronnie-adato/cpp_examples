

#include <gtest/gtest.h>
#include "handler.hpp"
#include "Message.hpp"
#include <sstream>

template <typename T>
class HandlerTypedTest : public ::testing::Test {
protected:
	std::unique_ptr<Handler> rr;
	void SetUp() override {
		rr = std::make_unique<T>();
	}
};

typedef ::testing::Types<Handler1, Handler2> HandlerImplementations;
TYPED_TEST_SUITE(HandlerTypedTest, HandlerImplementations);

typedef ::testing::Types<Handler1, Handler2> HandlerImplementations;
TYPED_TEST_SUITE(HandlerTypedTest, HandlerImplementations);

TYPED_TEST(HandlerTypedTest, HandlesMessage1SameWay) {
	Message1 m1;
	std::stringstream ss;
	std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
	this->rr->handle(&m1);
	std::cout.rdbuf(old_cout);
	EXPECT_TRUE(ss.str().find("handling Message1") != std::string::npos);
}

TYPED_TEST(HandlerTypedTest, HandlesMessage2Differently) {
	Message2 m2;
	std::stringstream ss;
	std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
	this->rr->handle(&m2);
	std::cout.rdbuf(old_cout);
	if (this->rr->get_type() == "Handler1") {
		EXPECT_TRUE(ss.str().find("Handler1 handling Message2 (Handler1 specific)") != std::string::npos);
	} else {
		EXPECT_TRUE(ss.str().find("Handler2 handling Message2 (Handler2 specific)") != std::string::npos);
	}
}

TYPED_TEST(HandlerTypedTest, HandlesMessage3OnlyHandler2) {
	Message3 m3;
	std::stringstream ss;
	std::streambuf* old_cout = std::cout.rdbuf(ss.rdbuf());
	this->rr->handle(&m3);
	std::cout.rdbuf(old_cout);
       if (this->rr->get_type() == "Handler2") {
	       EXPECT_TRUE(ss.str().find("Handler2 handling Message3 (Handler2 specific)") != std::string::npos);
       } else {
	       EXPECT_TRUE(ss.str().find("not handling Message3") != std::string::npos);
       }
}


