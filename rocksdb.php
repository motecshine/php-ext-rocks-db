<?php
if (!extension_loaded('rocksdb')) {
	dl('rocksdb');
}

use RocksDB\RDB;

$connector = new RDB(); 
$connector->connect();
$connector->enableBackup();

var_dump($connector->get());
var_dump($connector->close());
