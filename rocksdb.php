<?php
if (!extension_loaded('rocksdb')) {
	dl('rocksdb');
}

use RocksDB\RDB;

$connector = new RDB(); 

var_dump($connector->connect());