<?php

$str = null;
var_dump($str);
$packId = msgpack_pack($str);
var_dump($packId);
var_dump(msgpack_unpack($packId));

$str = 1.23;
var_dump($str);
$packId = msgpack_pack($str);
var_dump($packId);
var_dump(msgpack_unpack($packId));

$str = true;
var_dump($str);
$packId = msgpack_pack($str);
var_dump($packId);
var_dump(msgpack_unpack($packId));

$str = 'hello';
var_dump($str);
$packId = msgpack_pack($str);
var_dump($packId);
var_dump(msgpack_unpack($packId));

$str = array(
		'a' => 1,
		'b' => 2,
		'c' => array(
			'c1' => 1,
			'c2' => 2,
			'c3' => array(
				'c31' => 1,
			),
		),
		'd' => 3,
	);
var_dump($str);
$packId = msgpack_pack($str);
var_dump($packId);
var_dump(msgpack_unpack($packId));