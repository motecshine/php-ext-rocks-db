#ifndef ROCKSDB_CONNECTOR_H
#define ROCKSDB_CONNECTOR_H
static zend_class_entry *rc_ce;
PHP_METHOD(RocksDB, __construct);
PHP_METHOD(RocksDB, put);
PHP_METHOD(RocksDB, get);
PHP_METHOD(RocksDB, enableBackup);
PHP_METHOD(RocksDB, newBackup);
PHP_METHOD(RocksDB, restoreLastBackup);
PHP_ROCKSDB_STARTUP_FUNCTION(RocksDB);
#endif