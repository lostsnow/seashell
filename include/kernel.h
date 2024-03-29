// __KERNEL_H__

#ifndef __KERNEL_H__
#define __KERNEL_H__

#ifndef KERNEL_DIR
#define KERNEL_DIR          "/kernel/"
#endif

// Important directories
#ifndef DATA_DIR
#define DATA_DIR            "/data/"
#endif
#ifndef LOG_DIR
#define LOG_DIR             "/log/"
#endif
#ifndef CONFIG_DIR
#define CONFIG_DIR          "/etc/"
#endif
#ifndef DOMAIN_DIR
#define DOMAIN_DIR          "/d/"
#endif
#ifndef USER_DIR
#define USER_DIR            "/u/"
#endif
#ifndef HELP_DIR
#define HELP_DIR            "/doc/help/"
#endif
#ifndef HELP_DIRS
#define HELP_DIRS            ({ HELP_DIR })
#endif

// Config files
#define PRELOAD_CFG         "preload.cfg"
#define WELCOME_CFG         "welcome.cfg"
#define LIB_CFG             "lib.cfg"
#define WIZLIST_CFG         "wizlist.cfg"

// User IDs
#define ROOT_UID            "Root"
#define BACKBONE_UID        "Backbone"

// User Levels
#define USER_LEVEL_NAME_PLAYER      "(player)"
#define USER_LEVEL_NAME_WIZARD      "(wizard)"
#define USER_LEVEL_NAME_ADMIN       "(admin)"

#include <kernel/daemon.h>
#include <kernel/inherit.h>
#include <kernel/object.h>

// Debug level
#define DEBUG_LEVEL_ERROR   1
#define DEBUG_LEVEL_WARN    2
#define DEBUG_LEVEL_INFO    4
#define DEBUG_LEVEL_DEBUG   8
#define DEBUG_LEVEL_TRACE   16

#define DEBUG_LEVEL()       ((int) MASTER_OB->debug_level())

#endif // __KERNEL_H__
