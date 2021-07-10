// __KERNEL_INHERIT_H__

#ifndef __KERNEL_INHERIT_H__
#define __KERNEL_INHERIT_H__

#define K_IH_NAME           KERNEL_DIR "inherit/base/name"
#define K_IH_PROPERTY       KERNEL_DIR "inherit/base/property"
#define K_IH_SAVE           KERNEL_DIR "inherit/base/save"

#ifndef IH_NAME
#define IH_NAME             K_IH_NAME
#endif
#ifndef IH_PROPERTY
#define IH_PROPERTY         K_IH_PROPERTY
#endif
#ifndef IH_SAVE
#define IH_SAVE             K_IH_SAVE
#endif

#endif // __KERNEL_INHERIT_H__