#include <unistd.h>  // sysconf() - get CPU count
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"

#include "php_rocksdb.h"
#include "src/rocksdb_connector.h"



const char DBPath[] = "/tmp/rocksdb_simple_example";
const char DBBackupPath[] = "/tmp/rocksdb_simple_example_backup";

ZEND_BEGIN_ARG_INFO(init_db_arg_info, 0)
    ZEND_ARG_INFO(0, init_config)
ZEND_END_ARG_INFO()


PHP_METHOD(RocksDBConnector, __construct)
{

    options = rocksdb_options_create();
    long cpus = sysconf(_SC_NPROCESSORS_ONLN); 
    rocksdb_options_increase_parallelism(options, (int)(cpus));
    rocksdb_options_optimize_level_style_compaction(options, 0);

    rocksdb_options_set_create_if_missing(options, 1);

    char *err = NULL;
    db = rocksdb_open(options, DBPath, &err);
    assert(!err);
    // open Backup Engine that we will use for backing up our database
    be = rocksdb_backup_engine_open(options, DBBackupPath, &err);
    assert(!err);
}


static zend_function_entry rocksdb_connector_methods[] = {
    PHP_ME(RocksDBConnector, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
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