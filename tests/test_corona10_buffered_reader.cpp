#include <fstream>

#include "gtest/gtest.h"

#include "corona10/buffered_reader.hpp"

class BufferedReaderTest : public ::testing::Test {
    protected:
    virtual void SetUp() {
        std::ofstream ofs("./test.txt");
        ofs << "HelloWorld\nNewWorld";
        ofs.close();

        std::ofstream ofs2("./test2.txt");
        for(int i = 0; i < 10000; i++) {
            ofs2 << "HelloWorld";
            if (i % 30 == 0) {
                ofs2 << "\n";
            }
        }
        ofs2.close();
    }

    virtual void TearDown() {
        remove("./test.txt");
        remove("./test2.txt");
    }
};

TEST_F(BufferedReaderTest, Test1) {
    const char* fname = "./test.txt";
    corona10::Reader *reader = new corona10::BufferedReader(new corona10::FileReader(fname));
    char* buffer = new char[1024];
    memset(buffer, 0, sizeof(char)*1024);
    int rbyte = reader->read(buffer, 0, 4);
    ASSERT_STREQ(buffer, "Hell");
    ASSERT_EQ(rbyte, 4);
    rbyte = reader->read(buffer, 0, 4);
    ASSERT_STREQ(buffer, "oWor");
    ASSERT_EQ(rbyte, 4);
    rbyte = reader->read(buffer, 0, 100);
    ASSERT_STREQ(buffer, "ld\nNewWorld");
    ASSERT_EQ(rbyte, 11);
    delete reader;
    delete []buffer;
}

TEST_F(BufferedReaderTest, Test2) {
    const char* fname = "./test.txt";
    corona10::Reader *reader = new corona10::BufferedReader(new corona10::FileReader(fname));
    char buffer[4096] = {0,};
    int rbyte = reader->read(buffer, 0, 4);
    ASSERT_STREQ(buffer, "Hell");
    ASSERT_EQ(rbyte, 4);
    rbyte = reader->read(buffer, rbyte, 10);
    ASSERT_STREQ(buffer, "HelloWorld\nNew");
    ASSERT_EQ(rbyte, 10);
    rbyte = reader->read(buffer, 14, 10);
    ASSERT_STREQ(buffer, "HelloWorld\nNewWorld");
    ASSERT_EQ(rbyte, 5);
    delete reader;
}

TEST_F(BufferedReaderTest, LargerThanBufferSize) {
    const char* fname = "./test2.txt";
    corona10::Reader *reader = new corona10::BufferedReader(new corona10::FileReader(fname));
    char buffer[54321] = {0,};
    int rbyte = reader->read(buffer, 0, 54321);
    ASSERT_EQ(rbyte, 54321);
    rbyte = reader->read(buffer, 0, 54321);
    ASSERT_EQ(rbyte, 54321);
    delete reader;
}
