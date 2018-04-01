<?php
if (!extension_loaded('rocksdb')) {
	dl('rocksdb');
}

use RocksDB\RDB;

$connector = new RDB(); 
$connector->connect();
//$connector->restoreLastBackup();
var_dump($connector->get("key2"));
var_dump($connector->close());
