<?php
if (!extension_loaded('rocksdb')) {
	dl('rocksdb');
}

use RocksDB\RDB;

$connector = new RDB(); 
$rocksdbInstance = $connector->connect()->enableBackup();

var_dump($rocksdbInstance->get());
