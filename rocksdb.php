<?php
if (!extension_loaded('rocksdb')) {
	dl('rocksdb');
}

use RocksDB\Connector;

$connector = new Connector(); 
$connector->InitDB();