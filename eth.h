#include <array>
#include <cstddef>
#include <cstdint>
#include "absl/strings/str_split.h"
#include "absl/strings/str_format.h"


class EthAddr {
public:
    EthAddr() {}
    constexpr EthAddr(std::uint64_t hex) : addr{} {
        for (int i = 0; i < 6; ++i) {
            addr[i] = static_cast<std::byte>((hex >> (40 - 8 * i)) & 0xff);
        }
    }

    int fromStr(std::string_view str) {
        std::vector<std::string> hex = absl::StrSplit(str, ":"); 
        if (hex.size() != 6) {
            return -EINVAL;
        }

        for (int i = 0; i < 6; ++i) {
            int h = std::stoi(hex[i], nullptr, 16);
            addr[i] = static_cast<std::byte>(h);
        }
        return 0;
    }

    std::string toStr() const {
        return absl::StrFormat("%02x:%02x:%02x:%02x:%02x:%02x", addr[0],
                               addr[1], addr[2], addr[3], addr[4], addr[5]); 
    }

    std::array<std::byte, 6> addr;
};


constexpr inline EthAddr eth_bcast = 0xffffffffffffULL;
