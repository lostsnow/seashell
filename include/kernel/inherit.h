// __KERNEL_INHERIT_H__

#ifndef __KERNEL_INHERIT_H__
#define __KERNEL_INHERIT_H__

// base
#define K_IH_CLEAN_UP       KERNEL_DIR "inherit/base/clean_up"
#ifndef IH_CLEAN_UP
#define IH_CLEAN_UP         K_IH_CLEAN_UP
#endif

#define K_IH_COMMAND        KERNEL_DIR "inherit/base/command"
#ifndef IH_COMMAND
#define IH_COMMAND          K_IH_COMMAND
#endif

#define K_IH_MOVE           KERNEL_DIR "inherit/base/move"
#ifndef IH_MOVE
#define IH_MOVE             K_IH_MOVE
#endif

#define K_IH_NAME           KERNEL_DIR "inherit/base/name"
#ifndef IH_NAME
#define IH_NAME             K_IH_NAME
#endif

#define K_IH_PROPERTY       KERNEL_DIR "inherit/base/property"
#ifndef IH_PROPERTY
#define IH_PROPERTY         K_IH_PROPERTY
#endif

#define K_IH_SAVE           KERNEL_DIR "inherit/base/save"
#ifndef IH_SAVE
#define IH_SAVE             K_IH_SAVE
#endif

// char
#define K_IH_CHAR           KERNEL_DIR "inherit/char/char"
#ifndef IH_CHAR
#define IH_CHAR             K_IH_CHAR
#endif

// message
#define K_IH_MESSAGE        KERNEL_DIR "inherit/message/message"
#ifndef IH_MESSAGE
#define IH_MESSAGE          K_IH_MESSAGE
#endif

#define K_IH_MORE           KERNEL_DIR "inherit/message/more"
#ifndef IH_MORE
#define IH_MORE             K_IH_MORE
#endif

// room
#define K_IH_ROOM           KERNEL_DIR "inherit/room/room"
#ifndef IH_ROOM
#define IH_ROOM             K_IH_ROOM
#endif

#endif // __KERNEL_INHERIT_H__