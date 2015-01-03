#ifndef _PB_UTIL_H_
#define _PB_UTIL_H_

/* Handly macro for suppressing unreferenced-parameter compiler warnings.  */
#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

/* Wire types. Library user needs these only in encoder callbacks. */
typedef enum {
  PB_uInt32 = 1,
  PB_int32  = 2,
  PB_sInt32 = 3,
  PB_float  = 4,
  PB_double = 5,
  PB_string = 6
} pb_wire_type_t;

/*Helper Function*/
int pb__get_type(const char *type);
int pb__get_constant_type(const char *type);

/* These macros are used for giving out error messages.
 * They are mostly a debugging aid; the main error information
 * is the true/false return value from functions.
 * Some code space can be saved by disabling the error
 * messages if not used.
 */
#ifdef PB_NO_ERRMSG
#define PB_RETURN_ERROR(stream,msg) return 0
#define PB_GET_ERROR(stream) "(errmsg disabled)"
#else
#define PB_RETURN_ERROR(stream,msg) \
  do {\
    if ((stream)->errmsg == NULL) \
      (stream)->errmsg = (msg); \
    return 0; \
  } while(0)
#define PB_GET_ERROR(stream) ((stream)->errmsg ? (stream)->errmsg : "(none)")
#endif

#endif

