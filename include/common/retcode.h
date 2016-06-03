#ifndef _RETCODE_H_
#define _RETCODE_H_

#include <errno.h>

#define ERRCODE_SUCCESS		0
/*Sqlite3 part takes up at least 1 ~ - 65536*/
/*To take to the Sqlite3 return an error code, to return to directly use (0 - error code), get the return code of this system*/
#define ERRCODE_SQLITE               			-1000   /* SQLITE Return */


/*To take to the GCC errno, returned to directly use (RESULTCODE_ERROR_NORMAL - errno), get the return code of this system*/
#define ERRCODE_ERROR_NORMAL         (0-10000)             /* Must be smaller than the sqlite3-65565, defined here below from -100000 */
#define ERRCODE_NORMAL_EPERM                     (ERRCODE_ERROR_NORMAL-EPERM          )         /* Operation not permitted */
#define ERRCODE_NORMAL_ENOENT                    (ERRCODE_ERROR_NORMAL-ENOENT         )         /* No such file or directory */
#define ERRCODE_NORMAL_ESRCH                     (ERRCODE_ERROR_NORMAL-ESRCH          )         /* No such process */
#define ERRCODE_NORMAL_EINTR                     (ERRCODE_ERROR_NORMAL-EINTR          )         /* Interrupted system call */      
#define ERRCODE_NORMAL_EIO                       (ERRCODE_ERROR_NORMAL-EIO            )         /* I/O error */                    
#define ERRCODE_NORMAL_ENXIO                     (ERRCODE_ERROR_NORMAL-ENXIO          )         /* No such device or address */    
#define ERRCODE_NORMAL_E2BIG                     (ERRCODE_ERROR_NORMAL-E2BIG          )         /* Argument list too long */       
#define ERRCODE_NORMAL_ENOEXEC                   (ERRCODE_ERROR_NORMAL-ENOEXEC        )         /* Exec format error */            
#define ERRCODE_NORMAL_EBADF                     (ERRCODE_ERROR_NORMAL-EBADF          )         /* Bad file number */              
#define ERRCODE_NORMAL_ECHILD                    (ERRCODE_ERROR_NORMAL-ECHILD         )         /* No child processes */           
#define ERRCODE_NORMAL_EAGAIN                    (ERRCODE_ERROR_NORMAL-EAGAIN         )         /* Try again */                    
#define ERRCODE_NORMAL_ENOMEM                    (ERRCODE_ERROR_NORMAL-ENOMEM         )         /* Out of memory */                
#define ERRCODE_NORMAL_EACCES                    (ERRCODE_ERROR_NORMAL-EACCES         )         /* Permission denied */            
#define ERRCODE_NORMAL_EFAULT                    (ERRCODE_ERROR_NORMAL-EFAULT         )         /* Bad address */                  
#define ERRCODE_NORMAL_ENOTBLK                   (ERRCODE_ERROR_NORMAL-ENOTBLK        )         /* Block device required */        
#define ERRCODE_NORMAL_EBUSY                     (ERRCODE_ERROR_NORMAL-EBUSY          )         /* Device or resource busy */      
#define ERRCODE_NORMAL_EEXIST                    (ERRCODE_ERROR_NORMAL-EEXIST         )         /* File exists */                  
#define ERRCODE_NORMAL_EXDEV                     (ERRCODE_ERROR_NORMAL-EXDEV          )         /* Cross-device link */            
#define ERRCODE_NORMAL_ENODEV                    (ERRCODE_ERROR_NORMAL-ENODEV         )         /* No such device */               
#define ERRCODE_NORMAL_ENOTDIR                   (ERRCODE_ERROR_NORMAL-ENOTDIR        )         /* Not a directory */              
#define ERRCODE_NORMAL_EISDIR                    (ERRCODE_ERROR_NORMAL-EISDIR         )         /* Is a directory */               
#define ERRCODE_NORMAL_EINVAL                    (ERRCODE_ERROR_NORMAL-EINVAL         )         /* Invalid argument */             
#define ERRCODE_NORMAL_ENFILE                    (ERRCODE_ERROR_NORMAL-ENFILE         )         /* File table overflow */          
#define ERRCODE_NORMAL_EMFILE                    (ERRCODE_ERROR_NORMAL-EMFILE         )         /* Too many open files */          
#define ERRCODE_NORMAL_ENOTTY                    (ERRCODE_ERROR_NORMAL-ENOTTY         )         /* Not a typewriter */             
#define ERRCODE_NORMAL_ETXTBSY                   (ERRCODE_ERROR_NORMAL-ETXTBSY        )         /* Text file busy */               
#define ERRCODE_NORMAL_EFBIG                     (ERRCODE_ERROR_NORMAL-EFBIG          )         /* File too large */               
#define ERRCODE_NORMAL_ENOSPC                    (ERRCODE_ERROR_NORMAL-ENOSPC         )         /* No space left on device */      
#define ERRCODE_NORMAL_ESPIPE                    (ERRCODE_ERROR_NORMAL-ESPIPE         )         /* Illegal seek */                 
#define ERRCODE_NORMAL_EROFS                     (ERRCODE_ERROR_NORMAL-EROFS          )         /* Read-only file system */        
#define ERRCODE_NORMAL_EMLINK                    (ERRCODE_ERROR_NORMAL-EMLINK         )         /* Too many links */               
#define ERRCODE_NORMAL_EPIPE                     (ERRCODE_ERROR_NORMAL-EPIPE          )         /* Broken pipe */                  
#define ERRCODE_NORMAL_EDOM                      (ERRCODE_ERROR_NORMAL-EDOM           )         /* Math argument out of domain of func */
#define ERRCODE_NORMAL_ERANGE                    (ERRCODE_ERROR_NORMAL-ERANGE         )         /* Math result not representable */
#define ERRCODE_NORMAL_EDEADLK                   (ERRCODE_ERROR_NORMAL-EDEADLK        )     /* Resource deadlock would occur */
#define ERRCODE_NORMAL_ENAMETOOLONG              (ERRCODE_ERROR_NORMAL-ENAMETOOLONG   )     /* File name too long */
#define ERRCODE_NORMAL_ENOLCK                    (ERRCODE_ERROR_NORMAL-ENOLCK         )     /* No record locks available */
#define ERRCODE_NORMAL_ENOSYS                    (ERRCODE_ERROR_NORMAL-ENOSYS         )     /* Function not implemented */
#define ERRCODE_NORMAL_ENOTEMPTY                 (ERRCODE_ERROR_NORMAL-ENOTEMPTY      )     /* Directory not empty */
#define ERRCODE_NORMAL_ELOOP                     (ERRCODE_ERROR_NORMAL-ELOOP          )     /* Too many symbolic links encountered */
#define ERRCODE_NORMAL_EWOULDBLOCK               (ERRCODE_ERROR_NORMAL-EWOULDBLOCK    )     /* Operation would block */
#define ERRCODE_NORMAL_ENOMSG                    (ERRCODE_ERROR_NORMAL-ENOMSG         )     /* No message of desired type */
#define ERRCODE_NORMAL_EIDRM                     (ERRCODE_ERROR_NORMAL-EIDRM          )     /* Identifier removed */
#define ERRCODE_NORMAL_ECHRNG                    (ERRCODE_ERROR_NORMAL-ECHRNG         )     /* Channel number out of range */
#define ERRCODE_NORMAL_EL2NSYNC                  (ERRCODE_ERROR_NORMAL-EL2NSYNC       )     /* Level 2 not synchronized */
#define ERRCODE_NORMAL_EL3HLT                    (ERRCODE_ERROR_NORMAL-EL3HLT         )     /* Level 3 halted */
#define ERRCODE_NORMAL_EL3RST                    (ERRCODE_ERROR_NORMAL-EL3RST         )     /* Level 3 reset */
#define ERRCODE_NORMAL_ELNRNG                    (ERRCODE_ERROR_NORMAL-ELNRNG         )     /* Link number out of range */
#define ERRCODE_NORMAL_EUNATCH                   (ERRCODE_ERROR_NORMAL-EUNATCH        )     /* Protocol driver not attached */
#define ERRCODE_NORMAL_ENOCSI                    (ERRCODE_ERROR_NORMAL-ENOCSI         )     /* No CSI structure available */
#define ERRCODE_NORMAL_EL2HLT                    (ERRCODE_ERROR_NORMAL-EL2HLT         )     /* Level 2 halted */
#define ERRCODE_NORMAL_EBADE                     (ERRCODE_ERROR_NORMAL-EBADE          )     /* Invalid exchange */
#define ERRCODE_NORMAL_EBADR                     (ERRCODE_ERROR_NORMAL-EBADR          )     /* Invalid request descriptor */
#define ERRCODE_NORMAL_EXFULL                    (ERRCODE_ERROR_NORMAL-EXFULL         )     /* Exchange full */
#define ERRCODE_NORMAL_ENOANO                    (ERRCODE_ERROR_NORMAL-ENOANO         )     /* No anode */
#define ERRCODE_NORMAL_EBADRQC                   (ERRCODE_ERROR_NORMAL-EBADRQC        )     /* Invalid request code */
#define ERRCODE_NORMAL_EBADSLT                   (ERRCODE_ERROR_NORMAL-EBADSLT        )     /* Invalid slot */
#define ERRCODE_NORMAL_EDEADLOCK                 (ERRCODE_ERROR_NORMAL-EDEADLOCK      )     
#define ERRCODE_NORMAL_EBFONT                    (ERRCODE_ERROR_NORMAL-EBFONT         )     /* Bad font file format */
#define ERRCODE_NORMAL_ENOSTR                    (ERRCODE_ERROR_NORMAL-ENOSTR         )     /* Device not a stream */
#define ERRCODE_NORMAL_ENODATA                   (ERRCODE_ERROR_NORMAL-ENODATA        )     /* No data available */
#define ERRCODE_NORMAL_ETIME                     (ERRCODE_ERROR_NORMAL-ETIME          )     /* Timer expired */
#define ERRCODE_NORMAL_ENOSR                     (ERRCODE_ERROR_NORMAL-ENOSR          )     /* Out of streams resources */
#define ERRCODE_NORMAL_ENONET                    (ERRCODE_ERROR_NORMAL-ENONET         )     /* Machine is not on the network */
#define ERRCODE_NORMAL_ENOPKG                    (ERRCODE_ERROR_NORMAL-ENOPKG         )     /* Package not installed */
#define ERRCODE_NORMAL_EREMOTE                   (ERRCODE_ERROR_NORMAL-EREMOTE        )     /* Object is remote */
#define ERRCODE_NORMAL_ENOLINK                   (ERRCODE_ERROR_NORMAL-ENOLINK        )     /* Link has been severed */
#define ERRCODE_NORMAL_EADV                      (ERRCODE_ERROR_NORMAL-EADV           )     /* Advertise error */
#define ERRCODE_NORMAL_ESRMNT                    (ERRCODE_ERROR_NORMAL-ESRMNT         )     /* Srmount error */
#define ERRCODE_NORMAL_ECOMM                     (ERRCODE_ERROR_NORMAL-ECOMM          )     /* Communication error on send */
#define ERRCODE_NORMAL_EPROTO                    (ERRCODE_ERROR_NORMAL-EPROTO         )     /* Protocol error */
#define ERRCODE_NORMAL_EMULTIHOP                 (ERRCODE_ERROR_NORMAL-EMULTIHOP      )     /* Multihop attempted */
#define ERRCODE_NORMAL_EDOTDOT                   (ERRCODE_ERROR_NORMAL-EDOTDOT        )     /* RFS specific error */
#define ERRCODE_NORMAL_EBADMSG                   (ERRCODE_ERROR_NORMAL-EBADMSG        )     /* Not a data message */
#define ERRCODE_NORMAL_EOVERFLOW                 (ERRCODE_ERROR_NORMAL-EOVERFLOW      )     /* Value too large for defined data type */
#define ERRCODE_NORMAL_ENOTUNIQ                  (ERRCODE_ERROR_NORMAL-ENOTUNIQ       )     /* Name not unique on network */
#define ERRCODE_NORMAL_EBADFD                    (ERRCODE_ERROR_NORMAL-EBADFD         )     /* File descriptor in bad state */
#define ERRCODE_NORMAL_EREMCHG                   (ERRCODE_ERROR_NORMAL-EREMCHG        )     /* Remote address changed */
#define ERRCODE_NORMAL_ELIBACC                   (ERRCODE_ERROR_NORMAL-ELIBACC        )     /* Can not access a needed shared library */
#define ERRCODE_NORMAL_ELIBBAD                   (ERRCODE_ERROR_NORMAL-ELIBBAD        )     /* Accessing a corrupted shared library */
#define ERRCODE_NORMAL_ELIBSCN                   (ERRCODE_ERROR_NORMAL-ELIBSCN        )     /* .lib section in a.out corrupted */
#define ERRCODE_NORMAL_ELIBMAX                   (ERRCODE_ERROR_NORMAL-ELIBMAX        )     /* Attempting to link in too many shared libraries */
#define ERRCODE_NORMAL_ELIBEXEC                  (ERRCODE_ERROR_NORMAL-ELIBEXEC       )     /* Cannot exec a shared library directly */
#define ERRCODE_NORMAL_EILSEQ                    (ERRCODE_ERROR_NORMAL-EILSEQ         )     /* Illegal byte sequence */
#define ERRCODE_NORMAL_ERESTART                  (ERRCODE_ERROR_NORMAL-ERESTART       )     /* Interrupted system call should be restarted */
#define ERRCODE_NORMAL_ESTRPIPE                  (ERRCODE_ERROR_NORMAL-ESTRPIPE       )     /* Streams pipe error */
#define ERRCODE_NORMAL_EUSERS                    (ERRCODE_ERROR_NORMAL-EUSERS         )     /* Too many users */
#define ERRCODE_NORMAL_ENOTSOCK                  (ERRCODE_ERROR_NORMAL-ENOTSOCK       )     /* Socket operation on non-socket */
#define ERRCODE_NORMAL_EDESTADDRREQ              (ERRCODE_ERROR_NORMAL-EDESTADDRREQ   )     /* Destination address required */
#define ERRCODE_NORMAL_EMSGSIZE                  (ERRCODE_ERROR_NORMAL-EMSGSIZE       )     /* Message too long */
#define ERRCODE_NORMAL_EPROTOTYPE                (ERRCODE_ERROR_NORMAL-EPROTOTYPE     )     /* Protocol wrong type for socket */
#define ERRCODE_NORMAL_ENOPROTOOPT               (ERRCODE_ERROR_NORMAL-ENOPROTOOPT    )     /* Protocol not available */
#define ERRCODE_NORMAL_EPROTONOSUPPORT           (ERRCODE_ERROR_NORMAL-EPROTONOSUPPORT)     /* Protocol not supported */
#define ERRCODE_NORMAL_ESOCKTNOSUPPORT           (ERRCODE_ERROR_NORMAL-ESOCKTNOSUPPORT)     /* Socket type not supported */
#define ERRCODE_NORMAL_EOPNOTSUPP                (ERRCODE_ERROR_NORMAL-EOPNOTSUPP     )     /* Operation not supported on transport endpoint */
#define ERRCODE_NORMAL_EPFNOSUPPORT              (ERRCODE_ERROR_NORMAL-EPFNOSUPPORT   )     /* Protocol family not supported */
#define ERRCODE_NORMAL_EAFNOSUPPORT              (ERRCODE_ERROR_NORMAL-EAFNOSUPPORT   )     /* Address family not supported by protocol */
#define ERRCODE_NORMAL_EADDRINUSE                (ERRCODE_ERROR_NORMAL-EADDRINUSE     )     /* Address already in use */
#define ERRCODE_NORMAL_EADDRNOTAVAIL             (ERRCODE_ERROR_NORMAL-EADDRNOTAVAIL  )     /* Cannot assign requested address */
#define ERRCODE_NORMAL_ENETDOWN                  (ERRCODE_ERROR_NORMAL-ENETDOWN       )     /* Network is down */
#define ERRCODE_NORMAL_ENETUNREACH               (ERRCODE_ERROR_NORMAL-ENETUNREACH    )     /* Network is unreachable */
#define ERRCODE_NORMAL_ENETRESET                 (ERRCODE_ERROR_NORMAL-ENETRESET      )     /* Network dropped connection because of reset */
#define ERRCODE_NORMAL_ECONNABORTED              (ERRCODE_ERROR_NORMAL-ECONNABORTED   )     /* Software caused connection abort */
#define ERRCODE_NORMAL_ECONNRESET                (ERRCODE_ERROR_NORMAL-ECONNRESET     )     /* Connection reset by peer */
#define ERRCODE_NORMAL_ENOBUFS                   (ERRCODE_ERROR_NORMAL-ENOBUFS        )     /* No buffer space available */
#define ERRCODE_NORMAL_EISCONN                   (ERRCODE_ERROR_NORMAL-EISCONN        )     /* Transport endpoint is already connected */
#define ERRCODE_NORMAL_ENOTCONN                  (ERRCODE_ERROR_NORMAL-ENOTCONN       )     /* Transport endpoint is not connected */
#define ERRCODE_NORMAL_ESHUTDOWN                 (ERRCODE_ERROR_NORMAL-ESHUTDOWN      )     /* Cannot send after transport endpoint shutdown */
#define ERRCODE_NORMAL_ETOOMANYREFS              (ERRCODE_ERROR_NORMAL-ETOOMANYREFS   )     /* Too many references: cannot splice */
#define ERRCODE_NORMAL_ETIMEDOUT                 (ERRCODE_ERROR_NORMAL-ETIMEDOUT      )     /* Connection timed out */
#define ERRCODE_NORMAL_ECONNREFUSED              (ERRCODE_ERROR_NORMAL-ECONNREFUSED   )     /* Connection refused */
#define ERRCODE_NORMAL_EHOSTDOWN                 (ERRCODE_ERROR_NORMAL-EHOSTDOWN      )     /* Host is down */
#define ERRCODE_NORMAL_EHOSTUNREACH              (ERRCODE_ERROR_NORMAL-EHOSTUNREACH   )     /* No route to host */
#define ERRCODE_NORMAL_EALREADY                  (ERRCODE_ERROR_NORMAL-EALREADY       )     /* Operation already in progress */
#define ERRCODE_NORMAL_EINPROGRESS               (ERRCODE_ERROR_NORMAL-EINPROGRESS    )     /* Operation now in progress */
#define ERRCODE_NORMAL_ESTALE                    (ERRCODE_ERROR_NORMAL-ESTALE         )     /* Stale NFS file handle */
#define ERRCODE_NORMAL_EUCLEAN                   (ERRCODE_ERROR_NORMAL-EUCLEAN        )     /* Structure needs cleaning */
#define ERRCODE_NORMAL_ENOTNAM                   (ERRCODE_ERROR_NORMAL-ENOTNAM        )     /* Not a XENIX named type file */
#define ERRCODE_NORMAL_ENAVAIL                   (ERRCODE_ERROR_NORMAL-ENAVAIL        )     /* No XENIX semaphores available */
#define ERRCODE_NORMAL_EISNAM                    (ERRCODE_ERROR_NORMAL-EISNAM         )     /* Is a named type file */
#define ERRCODE_NORMAL_EREMOTEIO                 (ERRCODE_ERROR_NORMAL-EREMOTEIO      )     /* Remote I/O error */
#define ERRCODE_NORMAL_EDQUOT                    (ERRCODE_ERROR_NORMAL-EDQUOT         )     /* Quota exceeded */
#define ERRCODE_NORMAL_ENOMEDIUM                 (ERRCODE_ERROR_NORMAL-ENOMEDIUM      )     /* No medium found */
#define ERRCODE_NORMAL_EMEDIUMTYPE               (ERRCODE_ERROR_NORMAL-EMEDIUMTYPE    )     /* Wrong medium type */
#define ERRCODE_NORMAL_ECANCELED                 (ERRCODE_ERROR_NORMAL-ECANCELED      )     /* Operation Canceled */
#define ERRCODE_NORMAL_ENOKEY                    (ERRCODE_ERROR_NORMAL-ENOKEY         )     /* Required key not available */
#define ERRCODE_NORMAL_EKEYEXPIRED               (ERRCODE_ERROR_NORMAL-EKEYEXPIRED    )     /* Key has expired */
#define ERRCODE_NORMAL_EKEYREVOKED               (ERRCODE_ERROR_NORMAL-EKEYREVOKED    )     /* Key has been revoked */
#define ERRCODE_NORMAL_EKEYREJECTED              (ERRCODE_ERROR_NORMAL-EKEYREJECTED   )     /* Key was rejected by service */
#define ERRCODE_NORMAL_EOWNERDEAD                (ERRCODE_ERROR_NORMAL-EOWNERDEAD     )     /* Owner died */
#define ERRCODE_NORMAL_ENOTRECOVERABLE           (ERRCODE_ERROR_NORMAL-ENOTRECOVERABLE)     /* State not recoverable */


#define ERRCODE_DB_ERROR             (ERRCODE_ERROR_NORMAL-1000)
#define ERRCODE_DB_ERROR_OPEN                    (ERRCODE_DB_ERROR-1)
#define ERRCODE_DB_ERROR_PREPARE_TIMEOUT         (ERRCODE_DB_ERROR-2)
#define ERRCODE_DB_ERROR_STEP_TIMEOUT            (ERRCODE_DB_ERROR-3)


#define ERRCODE_SOCKET_ERROR         (ERRCODE_ERROR_NORMAL-2000)
#define ERRCODE_SOCKET_ERROR_CREATE              (ERRCODE_SOCKET_ERROR-1)
#define ERRCODE_SOCKET_ERROR_BIND                (ERRCODE_SOCKET_ERROR-2)
#define ERRCODE_SOCKET_ERROR_CONNECT             (ERRCODE_SOCKET_ERROR-3)
#define ERRCODE_SOCKET_ERROR_SEND                (ERRCODE_SOCKET_ERROR-4)


/* The following is the error code of the software system of the company, according to the system needs to postpone */
#define ERRCODE_CCT       	(ERRCODE_ERROR_NORMAL-3000)
#define ERRCODE_CCT_NORS232               	(ERRCODE_CCT-1)
#define ERRCODE_CCT_NOACK                 	(ERRCODE_CCT-2)
#define ERRCODE_CCT_ACKERROR              	(ERRCODE_CCT-3)
#define ERRCODE_CCT_INVALIDPARA				(ERRCODE_CCT-4)
#define ERRCODE_CCT_INVALIDLOGINUSER		(ERRCODE_CCT-5)
#define ERRCODE_CCT_INVALIDLOGINPASSWD		(ERRCODE_CCT-6)
#define ERRCODE_CCT_DBHAVENODATA			(ERRCODE_CCT-7)
#define ERRCODE_CCT_MALLOC_FAIL				(ERRCODE_CCT-8)


#define ERRCODE_JSON   		(ERRCODE_ERROR_NORMAL-4000)
#define ERRCODE_JSON_PARAM_ERR   			(ERRCODE_JSON-1) //  parameter error
#define ERRCODE_JSON_KEYNAME_NOEXIT   		(ERRCODE_JSON-2) //  name of  key doesn't exit 
#define ERRCODE_JSON_FORMAT_ERR   			(ERRCODE_JSON-3) //  format error


#define ERRCODE_HTTP   		(ERRCODE_ERROR_NORMAL-5000)
#define ERRCODE_HTTP_OVERFLOW   			(ERRCODE_HTTP-1) //  parameter error


#endif
