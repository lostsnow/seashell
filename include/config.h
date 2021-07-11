// config.h read configuration in runtime_config and /etc/config.cfg

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <runtime_config.h>

#define LOCAL_MUD_NAME()            ((string) get_config(__MUD_NAME__))
#define LOCAL_MUD_PORT()            ((int) get_config(__MUD_PORT__))

#define DEFAULT_ERROR_MESSAGE()     ((string) get_config(__DEFAULT_ERROR_MESSAGE__))

#define CFG_HOSTNAME()              (CONFIG_D->query_string("hostname"))
#define CFG_AUTHOR()                (CONFIG_D->query_string("author"))
#define CFG_WEBSITE()               (CONFIG_D->query_string("website"))
#define CFG_ICON()                  (CONFIG_D->query_string("icon"))
#define CFG_LOCATION()              (CONFIG_D->query_string("location"))
#define CFG_LANGUAGE()              (CONFIG_D->query_string("language"))
#define CFG_CREATED()               (CONFIG_D->query_string("created"))

#define CFG_PTOTOCOL_MXP()          ((int) get_config(__RC_ENABLE_MXP__))
#define CFG_PTOTOCOL_GMCP()         ((int) get_config(__RC_ENABLE_GMCP__))

#define CFG_PORT_CHARSET(port)      (CONFIG_D->query_string("charset " + (port)))

#endif // __CONFIG_H__
