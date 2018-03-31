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
static rocksdb_t *db;
static rocksdb_backup_engine_t *be;
static rocksdb_options_t *options;
static rocksdb_writeoptions_t *writeoptions;
static rocksdb_readoptions_t *readoptions;
#define THROW_ERROR()  if (err)     \
  {                                 \
    RETURN_STRING(err);             \
  } else {                          \
    RETURN_ZVAL(getThis(), 0 , 0);  \
  }

ZEND_BEGIN_ARG_INFO(init_db_arg_info, 0)
    ZEND_ARG_INFO(0, init_config)
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
    // default enable backup
}

PHP_METHOD(RocksDBConnector, connect)
{
  char *err = NULL;
  db = rocksdb_open(options, DBPath, &err);
  THROW_ERROR()
}

PHP_METHOD(RocksDBConnector, enableBackup)
{
  char *err = NULL;
  be = rocksdb_backup_engine_open(options, DBBackupPath, &err);
  THROW_ERROR()
}


PHP_METHOD(RocksDBConnector, put)
{
  char *err = NULL;
  const char key[] = "key";
  const char *value = "value";
  writeoptions = rocksdb_writeoptions_create();
  rocksdb_put(db, writeoptions, key, strlen(key), value, strlen(value) + 1, &err);
 
}

PHP_METHOD(RocksDBConnector, get)
{
  size_t len;
  char *err = NULL;
  const char key[] = "key";
  readoptions = rocksdb_readoptions_create();

  char *returned_value = rocksdb_get(db, readoptions, key, strlen(key), &len, &err);
  RETURN_STR(zend_string_init(returned_value, len, 0));
  THROW_ERROR()
}

static zend_function_entry rocksdb_connector_methods[] = {
    PHP_ME(RocksDBConnector, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(RocksDBConnector, connect, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(RocksDBConnector, put, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(RocksDBConnector, get, NULL, ZEND_ACC_PUBLIC)
    PHP_ME(RocksDBConnector, enableBackup, NULL, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

PHP_ROCKSDB_STARTUP_FUNCTION(RocksDBConnector) {
    zend_class_entry rocksdb_connector_ce;
    INIT_CLASS_ENTRY(rocksdb_connector_ce, "RocksDB\\RDB", rocksdb_connector_methods);
    rc_ce = zend_register_internal_class(&rocksdb_connector_ce TSRMLS_CC);
    return SUCCESS;
}