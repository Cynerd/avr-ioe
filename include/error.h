#include <stdlib.h>
#include <stdint.h>

#ifndef _IOE_ERROR_H_
#define _IOE_ERROR_H_
#ifdef CONFIG_ERRORS

enum ErrorCodes {
	EC_OK = 0, // This is not really error code. It triggers error callback but the error function returns
	EC_FUNC_ARG, // Invalid argument passed to function
	EC_INVALID_PORT, // IO error, requested port is not on your CPU
	EC_BUFFER_FULL, // If configured so, full buffer causes this error
	_EC_LAST = 128 // Not really error code. This reserver error range for library. User can define its error codes by adding
};

#ifdef CONFIG_ERROR_MESSAGES

void _error(enum ErrorCodes ec, const char *msg);
#define error(EC, MSG) _error(EC, MSG)

#ifdef CONFIG_ERROR_CALLBACK
void error_callback(enum ErrorCodes ec, const char *msg);
#endif /* CONFIG_ERROR_CALLBACK */

#else /* CONFIG_ERROR_MESSAGES*/

void _error(enum ErrorCodes ec);
#define error(EC, MSG) _error(EC)

#ifdef CONFIG_ERROR_CALLBACK
void error_callback(enum ErrorCodes ec);
#endif /* CONFIG_ERROR_CALLBACK */

#endif /* CONFIG_ERROR_MESSAGES */


#else /* CONFIG_ERRORS */

// Just dummy definition to suppress all errors
#define error(EC, MSG)

#endif /*  CONFIG_ERRORS */
#endif /* _IOE_ERROR_H_ */
