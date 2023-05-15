#include "../src/Options.hpp"

#include <gtest/gtest.h>
#include <memory>
 
TEST(OptionsParser, NotNull ) {
    std::unique_ptr<Options> parser = std::make_unique<Options>();
    EXPECT_NE(parser, nullptr);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}