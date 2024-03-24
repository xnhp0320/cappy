#include <string>
#include <cstdint>
#include "gtest/gtest.h"
#include "absl/strings/str_split.h"
#include "absl/strings/str_format.h"
#include "eth.h"

TEST(absl, StrSplit) {
    std::vector<std::string_view> str = absl::StrSplit("aabb", ":");
    EXPECT_EQ(str[0], "aabb");

    str = absl::StrSplit("aa:bb", ":");
    EXPECT_EQ(str.size(), 2);
    EXPECT_EQ(str[0], "aa");
    EXPECT_EQ(str[1], "bb");

    int byte = std::stoi(std::string(str[0]), nullptr, 16); 
    EXPECT_EQ(byte, 0xaa);

    byte = std::stoi(std::string(str[1]), nullptr, 16); 
    EXPECT_EQ(byte, 0xbb);

    std::string_view sv = "aa:bb"; 
    str = absl::StrSplit(sv, ":");

    byte = std::stoi(std::string(str[0]), nullptr, 16); 
    EXPECT_EQ(byte, 0xaa);

    byte = std::stoi(std::string(str[1]), nullptr, 16); 
    EXPECT_EQ(byte, 0xbb);

}

TEST(absl, StrFormat) {
    std::uint8_t a = 0xaa;
    auto s = absl::StrFormat("%02x", a);
    EXPECT_EQ(s, "aa");
}

TEST(ethaddr, ethaddr) {
    EXPECT_EQ(eth_bcast.toStr(), "ff:ff:ff:ff:ff:ff");
}
