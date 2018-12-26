<?php
if (!extension_loaded('rocksdb')) {
	dl('rocksdb');
}

use RocksDB\RDB;

$connector = new RDB(); 
var_dump($connector);
$connector->connect();
var_dump($connector->enableBackup());
var_dump($connector->restoreLastBackup());
var_dump($connector->newBackup());
var_dump($connector->get("arr"));
var_dump($connector->delete("arr"));
var_dump($connector->put("arr", serialize(['1' => "Happy Birthday"])));
var_dump($connector->get("arr"));
