#include "Options.hpp"

#include <gtest/gtest.h>
#include <memory>


// Friend calss fixture to test private methods of Options class
class OptionsTest : public ::testing::Test {
public:
    std::unique_ptr<Options> optionsObj;
protected:
    po::variables_map parseArgumentsTest(int *argc, char ***argv) {
        return optionsObj->parseArgumets(argc, argv);
    }

    virtual void SetUp()
    {
        optionsObj = std::make_unique<Options>();
    }

    virtual void TearDown()
    {
    }
};

TEST_F(OptionsTest, NullCheck ) {
    ASSERT_NE(optionsObj, nullptr);

    int argc = 1;
    char **argv = nullptr;
    po::variables_map result = parseArgumentsTest(&argc, &argv);
    EXPECT_TRUE(result.empty());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
