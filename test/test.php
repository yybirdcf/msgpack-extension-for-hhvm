<?php

class Person
{
	private $name;
	private $brothers;

	function __construct($name)
	{
		$this->name = $name;
	}

	function getName()
	{
		return $this->name;
	}

	function setBrothers($brothers)
	{
		$this->brothers = $brothers;
	}

	function getBrothers()
	{
		return $this->brothers;
	}
}

$a = null;
$packId = msgpack_pack($a);
$b = msgpack_unpack($packId);
var_dump($a == $b);

$a = 1.25;
$packId = msgpack_pack($a);
$b = msgpack_unpack($packId);
var_dump($a == $b);

$a = 123;
$packId = msgpack_pack($a);
$b = msgpack_unpack($packId);
var_dump($a == $b);

$a = 'hello world';
$packId = msgpack_pack($a);
$b = msgpack_unpack($packId);
var_dump($a == $b);

$a = array('a' => 1, 'b' => 2);
$packId = msgpack_pack($a);
$b = msgpack_unpack($packId);
var_dump($a == $b);

$a = array(
	'a' => 1,
	'b' => array(
		'c' => 2,
	),
	'd' => 3
);
$packId = msgpack_pack($a);
$b = msgpack_unpack($packId);
var_dump($a == $b);

$a = new Person('Jim');
$packId = msgpack_pack($a);
$b = msgpack_unpack($packId);
var_dump($a->getName() == $b->getName());

$p = new Person('Jim');
$a = array(
	'a' => $p,
	'b' => array(
		'c' => 2,
	),
	'd' => 3
);
$packId = msgpack_pack($a);
$b = msgpack_unpack($packId);
var_dump($a['a']->getName() == $b['a']->getName());

$brothers = array('Mike', 'Perter');
$p = new Person('Jim');
$p->setBrothers($brothers);
$packId = msgpack_pack($p);
$b = msgpack_unpack($packId);
var_dump(in_array('Mike', $b->getBrothers()) && in_array('Perter', $b->getBrothers()));
