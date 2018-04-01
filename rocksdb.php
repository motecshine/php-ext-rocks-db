<?php
if (!extension_loaded('rocksdb')) {
	dl('rocksdb');
}

use RocksDB\RDB;

$connector = new RDB(); 
$connector->connect();
var_dump($connector->enableBackup());
var_dump($connector->restoreLastBackup());
var_dump($connector->get("arr"));
var_dump($connector->close());
