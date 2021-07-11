// __KERNEL_DAEMON_H__

#ifndef __KERNEL_DAEMON_H__
#define __KERNEL_DAEMON_H__

#define K_CONFIG_D          KERNEL_DIR "sys/daemon/config"
#ifndef CONFIG_D
#define CONFIG_D            K_CONFIG_D
#endif

#define K_MSSP_D            KERNEL_DIR "sys/daemon/mssp"
#ifndef MSSP_D
#define MSSP_D              K_MSSP_D
#endif

#endif // __KERNEL_DAEMON_H__