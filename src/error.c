#include <error.h>
#ifdef CONFIG_ERRORS

#ifdef CONFIG_EH_LED
#include "ioport.h"
#endif /* CONFIG_EH_LED */

#ifdef CONFIG_ERROR_MESSAGES
void _error(enum ErrorCodes ec, const char *msg) {
#ifdef CONFIG_ERROR_CALLBACK
	error_callback(ec, msg);
#endif
#else /* CONFIG_ERROR_MESSAGES */
void _error(enum ErrorCodes ec) {
#ifdef CONFIG_ERROR_CALLBACK
	error_callback(ec);
#endif
#endif /* CONFIG_ERROR_MESSAGES */

	// OK error code means no error.
	if (ec == EC_OK)
		return;

#ifdef CONFIG_EH_LED
	// Set led
	io_setout(CONFIG_EH_LED_IOPIN);
	io_hight(CONFIG_EH_LED_IOPIN);
#endif /* CONFIG_EH_LED */

#ifdef CONFIG_EH_HANGS
	// TODO
#endif /* CONFIG_EH_HANGS */

#ifdef CONFIG_EH_RESTART
	// TODO
#endif /* CONFIG_EH_RESTART */
}


#endif /* CONFIG_ERRORS */
