/* rocksdb extension for PHP */

#ifndef PHP_ROCKSDB_H
# define PHP_ROCKSDB_H

extern zend_module_entry rocksdb_module_entry;
# define phpext_rocksdb_ptr &rocksdb_module_entry

# define PHP_ROCKSDB_VERSION "0.1.0"


#define PHP_ROCKSDB_STARTUP(module)               ZEND_MODULE_STARTUP_N(php_rocksdb_##module)(INIT_FUNC_ARGS_PASSTHRU)
#define PHP_ROCKSDB_STARTUP_FUNCTION(module)      ZEND_MINIT_FUNCTION(php_rocksdb_##module)

# if defined(ZTS) && defined(COMPILE_DL_ROCKSDB)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#define PHP_ROCKSDB_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(php_rocksdb, v)

#endif	/* PHP_ROCKSDB_H */
