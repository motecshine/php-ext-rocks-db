#ifndef ROCKSDB_CONNECTOR_H
#define ROCKSDB_CONNECTOR_H
#include "rocksdb/c.h"
static zend_class_entry *rc_ce;
static rocksdb_t *db;
static rocksdb_backup_engine_t *be;
static rocksdb_options_t *options;
PHP_METHOD(RocksDBConnector, __construct);
PHP_METHOD(RocksDBConnector, put);
PHP_METHOD(RocksDBConnector, get);
PHP_METHOD(RocksDBConnector, newBackup);
PHP_ROCKSDB_STARTUP_FUNCTION(RocksDBConnector);
#endif