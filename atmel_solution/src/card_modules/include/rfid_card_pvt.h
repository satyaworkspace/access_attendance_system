#ifndef __rfid_card_pvt_h__
#define __rfid_card_pvt_h__


#include <datatypes.h>
#include <rfid_card.h>


typedef union rfid_module_cfg RFID_MODULE_CFG;
typedef struct rfid_module RFID_MODULE;
typedef struct cmd_handling CMD_HANDLING;

typedef RFID_STATUS (*GET_CMD) (void *user_buffer);
typedef void (*PUT_CMD) (RFID_MODULE *module, void *cmd);
typedef void (*CLEAR_CMD) (void);
typedef RFID_STATUS (*VERIFY_CMD) (void *cmd);
typedef RFID_STATUS (*SEND_CMD) (void *cmd);
typedef void (*REGISTER_CALLBACKS) (void );


union rfid_module_cfg {
    struct {
        void *module;
        u32 baudrate;
        REGISTER_CALLBACKS register_callback;
    }uart_cfg;
};

struct cmd_handling {
    u8 get_pointer;         // from here we get received command
    u8 put_pointer;         // at here need to put newly received command
    u8 *buffer;             // buffer to store received commands
    u32 buffer_size;        // buffer size
    GET_CMD get;            // function to get received command
    PUT_CMD put;            // function to store received command
    CLEAR_CMD clear;        // function to clear buffer
    VERIFY_CMD verify;      // to verify command
    SEND_CMD send;          // send command
};

struct rfid_module {
    RFID_MODULE_CFG hal_cfg;
    CMD_HANDLING cmd;
    RFID_MODULE_OPS ops;
};


#endif
