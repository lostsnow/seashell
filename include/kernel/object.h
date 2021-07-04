// __KERNEL_OBJECT_H__

#ifndef __KERNEL_OBJECT_H__
#define __KERNEL_OBJECT_H__

#ifndef K_MASTER_OB
#define K_MASTER_OB         KERNEL_DIR "sys/master"
#endif

#define K_SIMUL_EFUN_OB     KERNEL_DIR "sys/simul_efun"

#define K_LOGIN_OB          KERNEL_DIR "obj/user/login"

#ifndef MASTER_OB
#define MASTER_OB           K_MASTER_OB
#endif
#ifndef SIMUL_EFUN_OB
#define SIMUL_EFUN_OB       K_SIMUL_EFUN_OB
#endif

#ifndef LOGIN_OB
#define LOGIN_OB            K_LOGIN_OB
#endif

#endif // __KERNEL_OBJECT_H__