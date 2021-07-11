// __KERNEL_OBJECT_H__

#ifndef __KERNEL_OBJECT_H__
#define __KERNEL_OBJECT_H__

#define K_MASTER_OB         KERNEL_DIR "sys/master"
#ifndef MASTER_OB
#define MASTER_OB           K_MASTER_OB
#endif

#define K_SIMUL_EFUN_OB     KERNEL_DIR "sys/simul_efun"
#ifndef SIMUL_EFUN_OB
#define SIMUL_EFUN_OB       K_SIMUL_EFUN_OB
#endif

#define K_LOGIN_OB          KERNEL_DIR "obj/user/login"
#ifndef LOGIN_OB
#define LOGIN_OB            K_LOGIN_OB
#endif

#define K_USER_OB           KERNEL_DIR "obj/user/user"
#ifndef USER_OB
#define USER_OB             K_USER_OB
#endif

#endif // __KERNEL_OBJECT_H__