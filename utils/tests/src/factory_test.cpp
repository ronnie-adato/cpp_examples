#include "factory_test_fixture.hpp"

using namespace utils;

struct Dummy {
    int x = 42;
};

TEST_F(FactoryTest, CreateWithoutRegisterReturnsNullptr) {
    auto p = factory.create<Dummy>();
    EXPECT_EQ(p, nullptr);
}

TEST_F(FactoryTest, RegisterAndCreateReturnsInstance) {
    factory.register_creator<Dummy>([](){ return std::make_shared<Dummy>(); });
    auto p = factory.create<Dummy>();
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->x, 42);
}

TEST_F(FactoryTest, MultipleTypesIndependent) {
    struct A { int a = 1; };
    struct B { int b = 2; };

    factory.register_creator<A>([](){ return std::make_shared<A>(); });
    factory.register_creator<B>([](){ return std::make_shared<B>(); });

    auto pa = factory.create<A>();
    auto pb = factory.create<B>();

    ASSERT_NE(pa, nullptr);
    ASSERT_NE(pb, nullptr);
    EXPECT_EQ(pa->a, 1);
    EXPECT_EQ(pb->b, 2);
}
