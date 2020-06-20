#ifndef H6AB49706_ADB6_11E9_9140_A45E60C4B579
#define H6AB49706_ADB6_11E9_9140_A45E60C4B579

#ifdef __cplusplus
extern "C" {
#endif

typedef int Status;

#define SUCCESS             (Status)0
#define FAILURE             (Status)-1

#define NULL_PTR            0

typedef unsigned int PortId;
typedef unsigned int PackageId;

typedef enum {
   CPU_PORT = 0, 
   FWD_PORT,
} PortType;

typedef struct Port {
    PortId   id;
    PortType type;
    unsigned int count_threshold;
    unsigned int bytes_threshold;
} Port;

typedef struct Chip {
    Port*  ports[12];
    unsigned int port_number;
} Chip;

typedef enum {
    DATA_PDU = 0,
    CTRL_CMD,
    HAND_SHAKE,
} PackageType;

typedef struct {
    PackageId    id;
    PackageType  type;
    unsigned int bytes;
    PortId       src_pid;
    PortId       tgt_pid;
} Package;

typedef struct {
    Package* elems[12];
    unsigned int number;
} Packages;

Status forward_ctrl(const Chip* chip, Packages* pkgs);

#ifdef __cplusplus
}
#endif

#endif
