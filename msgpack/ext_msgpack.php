<?hh

/**
 * serialize data to string using msgpack
 *
 *
 * @param mixed $data data to serialize(type: string, int, double, float, array, object)
 * @return string
 */
<<__Native>>
function msgpack_serialize(mixed $data): string;

/**
 * unserialize string data to real typed data using msgpack
 *
 *
 * @param string $data string to unserialize
 * @return mixed
 */
<<__Native>>
function msgpack_unserialize(string $data): mixed;

/**
 * pack data to string using msgpack
 *
 *
 * @param mixed $data data to pack(type: string, int, double, float, array, object)
 * @return string
 */
<<__Native>>
function msgpack_pack(mixed $data): string;

/**
 * unpack string data to real typed data using msgpack
 *
 *
 * @param string $data string to unpack
 * @return mixed
 */
<<__Native>>
function msgpack_unpack(string $data): mixed;