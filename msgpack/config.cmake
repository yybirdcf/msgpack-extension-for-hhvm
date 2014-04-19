FIND_PATH(MSGPACK_INCLUDE_DIR NAMES msgpack.hpp PATHS /usr/include /usr/local/include)
FIND_LIBRARY(MSGPACK_LIBRARY NAMES msgpack PATHS /lib /usr/lib /usr/local/lib)

include_directories(${MSGPACK_INCLUDE_DIR})

HHVM_EXTENSION(msgpack ext_msgpack.cpp)
HHVM_SYSTEMLIB(msgpack ext_msgpack.php)

target_link_libraries(msgpack ${MSGPACK_LIBRARY})