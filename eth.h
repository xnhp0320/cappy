#include <array>
#include <cstddef>
#include <cstdint>
#include "absl/strings/str_split.h"
#include "absl/strings/str_format.h"
#include <stdexcept>


class EthAddr {
public:
    EthAddr() {}

    constexpr EthAddr(std::uint64_t hex) : addr{} {
      for (int i = 0; i < 6; ++i) {
        addr[i] = static_cast<std::uint8_t>((hex >> (40 - 8 * i)) & 0xff);
      }
    }

    EthAddr(const std::string_view str) {
      int err = fromStr(str);
      if (err) {
        auto warn = absl::StrFormat("invalid mac address: %s", str);
        throw std::invalid_argument(warn);
      }
    }

    EthAddr& operator=(const std::string_view str) {
      EthAddr temp{str};
      std::swap(*this, temp);
      return *this;
    }

    bool operator==(const EthAddr &other) {
      return addr == other.addr;
    }

    bool operator!=(const EthAddr &other) {
      return !(*this == other);
    }

    int fromStr(const std::string_view str) {
        std::vector<std::string> hex = absl::StrSplit(str, ":"); 
        if (hex.size() != 6) {
            return -EINVAL;
        }

        for (int i = 0; i < 6; ++i) {
            addr[i] = std::stoi(hex[i], nullptr, 16);
        }
        return 0;
    }

    std::string toStr() const {
        return absl::StrFormat("%02x:%02x:%02x:%02x:%02x:%02x", addr[0],
                               addr[1], addr[2], addr[3], addr[4], addr[5]); 
    }

    std::array<std::uint8_t, 6> addr;
};

constexpr inline EthAddr eth_bcast = 0xffffffffffffULL;

class EthHdr {
public:
  EthAddr src;
  EthAddr dst;
  std::uint16_t dl_type;
  EthHdr() {}
};
