#pragma once

#include <array>
#include <string>
#include <sstream>
#include <utility>
#include <iterator>
#include <iomanip>

#ifdef GUID_LIBUUID
#include <uuid/uuid.h>
#elif GUID_WINDOWS
#include <objbase.h>
#elif GUID_CFUUID
#include <CoreFoundation/CFUUID.h>
#elif GUID_RANDOM
#include <algorithm>
#include <functional>
#include <random>
#endif

/*
 * UUID class
 */

class uuid {
public:
  using value_t = unsigned char;
  using data_t = std::array<value_t, 16>;

  constexpr uuid() noexcept : data({}) {};

  uuid(const data_t& arr) noexcept {
    std::copy(std::begin(arr), std::end(arr), std::begin(data));
  }

  void swap(uuid& other) noexcept {
    data.swap(other.data);
  }

private:
  data_t data{{ 0 }};
  friend std::ostream &operator<<(std::ostream& s, const uuid& id);
};

std::ostream &operator<<(std::ostream &s, const uuid& id) {
  std::ios_base::fmtflags f(s.flags());
  s << std::hex << std::setfill('0')
    << std::setw(2) << static_cast<int>(id.data[0])
    << std::setw(2) << static_cast<int>(id.data[1])
    << std::setw(2) << static_cast<int>(id.data[2])
    << std::setw(2) << static_cast<int>(id.data[3])
    << '-'
    << std::setw(2) << static_cast<int>(id.data[4])
    << std::setw(2) << static_cast<int>(id.data[5])
    << '-'
    << std::setw(2) << static_cast<int>(id.data[6])
    << std::setw(2) << static_cast<int>(id.data[7])
    << '-'
    << std::setw(2) << static_cast<int>(id.data[8])
    << std::setw(2) << static_cast<int>(id.data[9])
    << '-'
    << std::setw(2) << static_cast<int>(id.data[10])
    << std::setw(2) << static_cast<int>(id.data[11])
    << std::setw(2) << static_cast<int>(id.data[12])
    << std::setw(2) << static_cast<int>(id.data[13])
    << std::setw(2) << static_cast<int>(id.data[14])
    << std::setw(2) << static_cast<int>(id.data[15]);
  s.flags(f);
  return s;
}

std::string to_string(const uuid& id) {
  std::stringstream ss;
  ss << id;
  return ss.str();
}

/*
 * UUID generator class
 */

class uuid_generator {
public:
  using value_t = unsigned char;
  using data_t = std::array<value_t, 16>;
  uuid operator()() {
#ifdef GUID_LIBUUID
  uuid_t id;
  uuid_generate(id);
  data_t res = {
    id[0],
    id[1],
    id[2],
    id[3],
    id[4],
    id[5],
    id[6],
    id[7],
    id[8],
    id[9],
    id[10],
    id[11],
    id[12],
    id[13],
    id[14],
    id[15]
  };
  return uuid{std::move(res)};

#elif GUID_WINDOWS
  GUID id;
  CoCreateGuid(&id);
  data_t res = {
    static_cast<unsigned char>(((id.Data1 >> 24) & 0xFF)),
    static_cast<unsigned char>(((id.Data1 >> 16) & 0xFF)),
    static_cast<unsigned char>(((id.Data1 >> 8) & 0xFF)),
    static_cast<unsigned char>(((id.Data1) & 0xff)),
    static_cast<unsigned char>(((id.Data2 >> 8) & 0xFF)),
    static_cast<unsigned char>(((id.Data2) & 0xff)),
    static_cast<unsigned char>(((id.Data3 >> 8) & 0xFF)),
    static_cast<unsigned char>(((id.Data3) & 0xFF)),
    static_cast<unsigned char>(id.Data4[0]),
    static_cast<unsigned char>(id.Data4[1]),
    static_cast<unsigned char>(id.Data4[2]),
    static_cast<unsigned char>(id.Data4[3]),
    static_cast<unsigned char>(id.Data4[4]),
    static_cast<unsigned char>(id.Data4[5]),
    static_cast<unsigned char>(id.Data4[6]),
    static_cast<unsigned char>(id.Data4[7])
  };
  return uuid{std::move(res)};

#elif GUID_CFUUID
  auto id = CFUUIDCreate(NULL);
  auto bytes = CFUUIDGetUUIDBytes(id);
  CFRelease(id);
  data_t res = {
    bytes.byte0,
    bytes.byte1,
    bytes.byte2,
    bytes.byte3,
    bytes.byte4,
    bytes.byte5,
    bytes.byte6,
    bytes.byte7,
    bytes.byte8,
    bytes.byte9,
    bytes.byte10,
    bytes.byte11,
    bytes.byte12,
    bytes.byte13,
    bytes.byte14,
    bytes.byte15
  };
  return uuid{std::move(res)};

#elif GUID_RANDOM
  std::uniform_int_distribution<uint32_t> distribution;
  std::random_device rd;
  auto seed_data = std::array<int, std::mt19937::state_size> {};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  std::mt19937 generator(seq);

  uint8_t bytes[16];
  for (int i = 0; i < 16; i += 4) {
      *reinterpret_cast<uint32_t*>(bytes + i) = distribution(generator);
  }
  // variant must be 10xxxxxx
  bytes[8] &= 0xBF;
  bytes[8] |= 0x80;
  // version must be 0100xxxx
  bytes[6] &= 0x4F;
  bytes[6] |= 0x40;

  data_t res = {
      bytes[0],
      bytes[1],
      bytes[2],
      bytes[3],
      bytes[4],
      bytes[5],
      bytes[6],
      bytes[7],
      bytes[8],
      bytes[9],
      bytes[10],
      bytes[11],
      bytes[12],
      bytes[13],
      bytes[14],
      bytes[15]
  };
  return uuid{std::move(res)};

#endif
  }
};
