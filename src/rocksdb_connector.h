#ifndef ROCKSDB_CONNECTOR_H
#define ROCKSDB_CONNECTOR_H
static zend_class_entry *rc_ce;

PHP_METHOD(RocksDBConnector, __construct);
PHP_METHOD(RocksDBConnector, put);
PHP_METHOD(RocksDBConnector, get);
PHP_METHOD(RocksDBConnector, enableBackup);
PHP_ROCKSDB_STARTUP_FUNCTION(RocksDBConnector);
#endif