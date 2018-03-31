#include <unistd.h>  // sysconf() - get CPU count
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"
#include "src/rocksdb_connector.h"
#include <assert.h>


// Default DB path
const char DBPath[] = "/tmp/rocksdb";
const char DBBackupPath[] = "/tmp/rocksdb_backup";
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
}

PHP_METHOD(RocksDBConnector, connect)
{
  char *err = NULL;
  db = rocksdb_open(options, DBPath, &err);
  if (err) {
    RETURN_BOOL(false)
  } else {
    RETURN_ZVAL(getThis(), 0 , 0);
  }
}

static zend_function_entry rocksdb_connector_methods[] = {
    PHP_ME(RocksDBConnector, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(RocksDBConnector, connect, NULL, ZEND_ACC_PUBLIC)
    PHP_FE_END
};

PHP_ROCKSDB_STARTUP_FUNCTION(RocksDBConnector) {
    zend_class_entry rocksdb_connector_ce;
    INIT_CLASS_ENTRY(rocksdb_connector_ce, "RocksDB\\RDB", rocksdb_connector_methods);
    rc_ce = zend_register_internal_class(&rocksdb_connector_ce TSRMLS_CC);
    // declear elements
    zend_declare_property_null(rc_ce, ZEND_STRL("db"), ZEND_ACC_PRIVATE);
    zend_declare_property_null(rc_ce, ZEND_STRL("enableBackup"), ZEND_ACC_PRIVATE);
    zend_declare_property_null(rc_ce, ZEND_STRL("getWriteOptions"), ZEND_ACC_PRIVATE);
    zend_declare_property_null(rc_ce, ZEND_STRL("putOptions"), ZEND_ACC_PRIVATE);
    return SUCCESS;
}