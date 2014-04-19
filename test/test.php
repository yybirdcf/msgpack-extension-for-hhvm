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

class Person{
	private $a;

	public function getA(){
		return $this->a;
	}

	public function setA(){
		$this->a = "a";
	}
}
$p = new Person();
var_dump($p);
$p->setA();
$packId = msgpack_pack($p);
var_dump($packId);
$b = msgpack_unpack($packId);
var_dump($b->getA());

$a = array(
	'a' => 1,
	'b' => $p,
	'c' => array(
		'c1' => 1,
		'c2' => $p,
		'c3' => array(
			'c31' => 1,
		),
	),
	'd' => 3,
);
var_dump($a);
$packId = msgpack_pack($a);
var_dump($packId);
var_dump(msgpack_unpack($packId));
