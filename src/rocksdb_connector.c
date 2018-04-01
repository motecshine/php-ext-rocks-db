#include <unistd.h>  // sysconf() - get CPU count
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"
#include "src/rocksdb_connector.h"
#include "rocksdb/c.h"


// Default DB path
const char DBPath[] = "/tmp/rocksdb";
const char DBBackupPath[] = "/tmp/rocksdb_backup";
rocksdb_t *db;
rocksdb_backup_engine_t *be;
rocksdb_options_t *options;
rocksdb_writeoptions_t *writeoptions;
rocksdb_readoptions_t *readoptions;
extern zend_class_entry *rc_ce;
#define THROW_ERROR()  if (err) {   \
    assert(!err);                   \
  } else {                          \
    RETURN_BOOL(true);              \
  }
  
ZEND_BEGIN_ARG_INFO(rocksdb_get_arg_info, 0)
   ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(rocksdb_put_arg_info, 0)
    ZEND_ARG_INFO(0, key)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()


PHP_METHOD(RocksDBConnector, __construct)
{
    if ((ZEND_NUM_ARGS() != 0)) {
        WRONG_PARAM_COUNT;
    }
    options = rocksdb_options_create();
    rocksdb_options_increase_parallelism(options, (int)(sysconf(_SC_NPROCESSORS_ONLN)));
    rocksdb_options_optimize_level_style_compaction(options, 0);
    rocksdb_options_set_create_if_missing(options, 1);
}

PHP_METHOD(RocksDBConnector, connect)
{
  char *err;
  db = rocksdb_open(options, DBPath, &err);
  THROW_ERROR()
}

PHP_METHOD(RocksDBConnector, enableBackup)
{
  char *err;
  be = rocksdb_backup_engine_open(options, DBBackupPath, &err);
  THROW_ERROR()
}


PHP_METHOD(RocksDBConnector, put)
{
  char *err, *c_key, *c_value;
  zend_string *key, *value;
  ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_STR(key)
    Z_PARAM_STR(value)
  ZEND_PARSE_PARAMETERS_END();

  c_key = ZSTR_VAL(key);
  c_value = ZSTR_VAL(value);
  writeoptions = rocksdb_writeoptions_create();
  rocksdb_put(db, writeoptions, c_key, strlen(c_key), c_value, strlen(c_value) + 1, &err);
  THROW_ERROR()
}

PHP_METHOD(RocksDBConnector, get)
{
  size_t len;
  char *err,  *c_key, *returned_value;
  zend_string *key;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STR(key)
  ZEND_PARSE_PARAMETERS_END();
  readoptions = rocksdb_readoptions_create();
  c_key = ZSTR_VAL(key);
  returned_value = rocksdb_get(db, readoptions, c_key, strlen(c_key), &len, &err);
  RETURN_STR(zend_string_init(returned_value, len, 0));
 
}


PHP_METHOD(RocksDBConnector, close)
{
  rocksdb_writeoptions_destroy(writeoptions);
  rocksdb_readoptions_destroy(readoptions);
  rocksdb_options_destroy(options);
  rocksdb_backup_engine_close(be); 
  rocksdb_close(db);
  RETURN_BOOL(true);
}

static zend_function_entry rocksdb_connector_methods[] = {
    PHP_ME(RocksDBConnector, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(RocksDBConnector, connect, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(RocksDBConnector, put, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(RocksDBConnector, get, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(RocksDBConnector, close, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(RocksDBConnector, enableBackup, NULL, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

PHP_ROCKSDB_STARTUP_FUNCTION(RocksDBConnector) {
    zend_class_entry rocksdb_connector_ce;
    INIT_CLASS_ENTRY(rocksdb_connector_ce, "RocksDB\\RDB", rocksdb_connector_methods);
    rc_ce = zend_register_internal_class(&rocksdb_connector_ce TSRMLS_CC);
    return SUCCESS;
}