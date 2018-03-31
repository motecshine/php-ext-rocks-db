/* rocksdb extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_rocksdb.h"



/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(rocksdb)
{
#if defined(ZTS) && defined(COMPILE_DL_ROCKSDB)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(rocksdb)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "rocksdb support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ rocksdb_functions[]
 */
static const zend_function_entry rocksdb_functions[] = {
	
	PHP_FE_END
};
/* }}} */

/* {{{ rocksdb_module_entry
 */
zend_module_entry rocksdb_module_entry = {
	STANDARD_MODULE_HEADER,
	"rocksdb",					/* Extension name */
	rocksdb_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(rocksdb),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(rocksdb),			/* PHP_MINFO - Module info */
	PHP_ROCKSDB_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ROCKSDB
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(rocksdb)
#endif
