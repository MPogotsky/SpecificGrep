#include "Options.hpp"

#include <gtest/gtest.h>
#include <memory>

// Friend calss fixture to test private methods of Options class
class OptionsTest : public ::testing::Test
{
public:
    std::unique_ptr<Options> optionsObj;

protected:
    po::variables_map parseArgumentsTest(std::vector<std::string> arguments)
    {
        int argc = arguments.size();
        char** argv = strToCharArray(arguments);
        return optionsObj->parseArgumets(&argc, &argv);
        delete [] argv;
    }

    char** strToCharArray( std::vector<std::string> arguments)
    {
        size_t count = arguments.size();

        char** argv = new char* [count];
        for (int i = 0; i < count; i++)
        {
            argv[i] = const_cast<char*>(arguments.at(i).c_str());
        }
        return argv;
    }

    virtual void SetUp()
    {
        optionsObj = std::make_unique<Options>();
    }

    virtual void TearDown()
    {
    }
};

TEST_F(OptionsTest, OptionsNoOptionCheck)
{
    po::variables_map result = nullptr;
    std::vector<std::string> arguments;

    arguments = {};
    result = parseArgumentsTest(arguments);
    EXPECT_TRUE(result.empty());

    arguments = {"app"};
    result = parseArgumentsTest(arguments);
    EXPECT_TRUE(result.empty());
}

TEST_F(OptionsTest, OptionsHelpCheck)
{
    po::variables_map result = nullptr;
    std::vector<std::string> arguments;

    arguments = {"app", "--help"};
    result = parseArgumentsTest(arguments);
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(result.count("help"));
    EXPECT_FALSE(result.count("pattern"));
}

TEST_F(OptionsTest, OptionsBasicCheck)
{
    po::variables_map result = nullptr;
    std::vector<std::string> arguments;

    arguments = {"app", "search_pattern", "--threads=3"};
    result = parseArgumentsTest(arguments);
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(result.count("pattern"));
    EXPECT_EQ(result["pattern"].as<std::string>(), "search_pattern");
    EXPECT_EQ(result["threads"].as<int>(), 3);

    arguments = {"app", "--threads=3", "search_pattern"};
    result = parseArgumentsTest(arguments);
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(result.count("pattern"));
    EXPECT_EQ(result["pattern"].as<std::string>(), "search_pattern");
    EXPECT_EQ(result["threads"].as<int>(), 3);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
