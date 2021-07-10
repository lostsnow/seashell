// config.h read configuration in runtime_config and /etc/config.cfg

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <runtime_config.h>

#define LOCAL_MUD_NAME()            ((string) get_config(__MUD_NAME__))
#define LOCAL_MUD_PORT()            ((int) get_config(__MUD_PORT__))

#define DEFAULT_ERROR_MESSAGE()     ((string) get_config(__DEFAULT_ERROR_MESSAGE__))

#endif // __CONFIG_H__
