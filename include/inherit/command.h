// __COMMAND_H__

#ifndef __COMMAND_H__
#define __COMMAND_H__

#define MAX_ALIASES             50

#define CMD_DIR        "/cmds/"
#define K_CMD_DIR      KERNEL_DIR "cmds/"

#define K_CMD_DIR_STD           K_CMD_DIR "std/"
#define K_CMD_DIR_SKILL         K_CMD_DIR "skill/"
#define K_CMD_DIR_USR           K_CMD_DIR "usr/"
#define K_CMD_DIR_WIZ           K_CMD_DIR "wiz/"
#define K_CMD_DIR_ADM           K_CMD_DIR "adm/"

#define CMD_DIR_STD             CMD_DIR "std/"
#define CMD_DIR_SKILL           CMD_DIR "skill/"
#define CMD_DIR_USR             CMD_DIR "usr/"
#define CMD_DIR_WIZ             CMD_DIR "wiz/"
#define CMD_DIR_ADM             CMD_DIR "adm/"

#define CMD_PATH_NPC           ({ CMD_DIR_STD, K_CMD_DIR_STD, CMD_DIR_SKILL, K_CMD_DIR_SKILL })
#define CMD_PATH_PRISON        ({ CMD_DIR_STD, K_CMD_DIR_STD, CMD_DIR_USR, K_CMD_DIR_USR })
#define CMD_PATH_PLAYER        ({ CMD_DIR_USR, K_CMD_DIR_USR }) + CMD_PATH_NPC
#define CMD_PATH_WIZ           ({ CMD_DIR_WIZ, K_CMD_DIR_WIZ }) + CMD_PATH_PLAYER
#define CMD_PATH_ADM           ({ CMD_DIR_ADM, K_CMD_DIR_ADM }) + CMD_PATH_WIZ

#define CMD_PATH_EXCLUDE_CHATTER    ({ CMD_DIR_SKILL, K_CMD_DIR_SKILL, CMD_DIR_USR, K_CMD_DIR_USR });

#endif // __COMMAND_H__
