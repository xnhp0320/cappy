#include <string>
#include <cstdint>
#include "gtest/gtest.h"
#include "absl/strings/str_split.h"
#include "absl/strings/str_format.h"
#include "eth.h"
#include <stdexcept>

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

TEST(ethaddr, inline_ethaddr) {
    EXPECT_EQ(eth_bcast.toStr(), "ff:ff:ff:ff:ff:ff");
}

TEST(ethaddr, ethaddr) {
    EthAddr addr;
    addr.fromStr("aa:bb:cc:dd:ee:ff");
    EXPECT_EQ(addr.toStr(), "aa:bb:cc:dd:ee:ff");

    EthAddr b;
    b.fromStr("ee:ff:ff:ff:ff:ff");
    EXPECT_TRUE(b != addr);
}

TEST(ethhdr, hdr) {
  EthHdr hdr;
  hdr.src = "ff:ff:ff:ff:ff:ff";
  EXPECT_EQ(hdr.src.toStr(), "ff:ff:ff:ff:ff:ff");
  hdr.dst = "aa:bb:cc:dd:ee:ff";
  EXPECT_EQ(hdr.dst.toStr(), "aa:bb:cc:dd:ee:ff");
  hdr.dl_type = 0x0800;
  EXPECT_EQ(hdr.dl_type, 0x0800);

  std::string mac = "11:22:33:44:55:66";
  hdr.src = mac;
  EXPECT_EQ(hdr.src.toStr(), "11:22:33:44:55:66");

  mac = "11:22";
  try {
    hdr.src = mac;
  } catch(const std::invalid_argument &w) {
    EXPECT_STREQ(w.what(), "invalid mac address: 11:22");
  }
}
