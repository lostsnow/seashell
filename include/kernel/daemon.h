// __KERNEL_DAEMON_H__

#ifndef __KERNEL_DAEMON_H__
#define __KERNEL_DAEMON_H__

#define K_COMMAND_D         KERNEL_DIR "sys/daemon/command"
#ifndef COMMAND_D
#define COMMAND_D           K_COMMAND_D
#endif

#define K_CONFIG_D          KERNEL_DIR "sys/daemon/config"
#ifndef CONFIG_D
#define CONFIG_D            K_CONFIG_D
#endif

#define K_LOGIN_D           KERNEL_DIR "sys/daemon/login"
#ifndef LOGIN_D
#define LOGIN_D             K_LOGIN_D
#endif

#define K_MSSP_D            KERNEL_DIR "sys/daemon/mssp"
#ifndef MSSP_D
#define MSSP_D              K_MSSP_D
#endif

#define K_SECURITY_D        KERNEL_DIR "sys/daemon/security"
#ifndef SECURITY_D
#define SECURITY_D          K_SECURITY_D
#endif

#endif // __KERNEL_DAEMON_H__