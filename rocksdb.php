<?php
if (!extension_loaded('rocksdb')) {
	dl('rocksdb');
}

use RocksDB\RDB;

$connector = new RDB(); 
$connector->connect();
$connector->enableBackup();

var_dump($connector->put("key", "zhu"));
var_dump($connector->get("key"));
var_dump($connector->close());
