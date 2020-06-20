#include <stdio.h>
#include "sdk/fwd_ctrl.h"

Status forward_ctrl(const Chip* chip, Packages* pkgs) {
    unsigned int port_bytes[12] = {0};
    unsigned int port_count[12] = {0};
    int pkg_index = 0;
    int port_index = 0;
    unsigned int bytes_left = 0;

    if (chip == NULL_PTR || pkgs == NULL_PTR) {
        printf("[ERROR]: exist null ptr, chip = %p, pkgs = %p!\n", chip, pkgs);
        return FAILURE;
    }

    for(pkg_index = 0; pkg_index < pkgs->number && pkg_index < 12; pkg_index++) {
        for (port_index = 0; port_index < chip->port_number && port_index < 12; port_index++) {
            if (chip->ports[port_index]->id == pkgs->elems[pkg_index]->src_pid) {
                break;
            }
        }
        if (port_index >= chip->port_number || port_index >= 12) {
            pkgs->elems[pkg_index]->bytes = 0;
            printf("[ERROR]: src port %d not found of package %d!\n", pkgs->elems[pkg_index]->src_pid, pkgs->elems[pkg_index]->id);
            continue;
        }
        switch (pkgs->elems[pkg_index]->type) {
        case DATA_PDU:
            for (port_index = 0; port_index < chip->port_number && port_index < 12; port_index++) {
                if (chip->ports[port_index]->id == pkgs->elems[pkg_index]->tgt_pid) {
                    if (port_count[port_index] < chip->ports[port_index]->count_threshold) {
                        if (chip->ports[port_index]->type == FWD_PORT) {
                            if (chip->ports[port_index]->bytes_threshold > port_bytes[port_index])
                            {
                                bytes_left = chip->ports[port_index]->bytes_threshold - port_bytes[port_index];
                                if (bytes_left < pkgs->elems[pkg_index]->bytes) {
                                    pkgs->elems[pkg_index]->bytes = bytes_left;
                                    port_bytes[port_index] += pkgs->elems[pkg_index]->bytes;
                                }
                                port_bytes[port_index] += pkgs->elems[pkg_index]->bytes;
                                port_count[port_index]++;
                            } else {
                                pkgs->elems[pkg_index]->bytes = 0;
                                printf("[WARN]: package %d\n meets the bytes threshold of target port %d!\n", pkgs->elems[pkg_index]->id, pkgs->elems[pkg_index]->tgt_pid);
                            }
                        } else {
                            pkgs->elems[pkg_index]->bytes = 0;
                            printf("[WARN]: cpu port %d does not receive data pdu package %d!\n", pkgs->elems[pkg_index]->tgt_pid, pkgs->elems[pkg_index]->id);
                        }
                    } else {
                        pkgs->elems[pkg_index]->bytes = 0;
                        printf("[WARN]: package %d meets the count threshold of target port %d!\n", pkgs->elems[pkg_index]->id, pkgs->elems[pkg_index]->tgt_pid);
                    }
                    break;
                }
            }
            if (port_index >= chip->port_number || port_index >= 12) {
                pkgs->elems[pkg_index]->bytes = 0;
                printf("[ERROR]: target port %d not found of package %d!\n", pkgs->elems[pkg_index]->tgt_pid, pkgs->elems[pkg_index]->id);
            }
            break;
        case CTRL_CMD:
            for (port_index = 0; port_index < chip->port_number && port_index < 12; port_index++) {
                if (chip->ports[port_index]->id == pkgs->elems[pkg_index]->tgt_pid) {
                    if (chip->ports[port_index]->type == CPU_PORT) {
                        if (port_count[port_index] < chip->ports[port_index]->count_threshold) {
                            port_count[port_index]++;

                        } else {
                            pkgs->elems[pkg_index]->bytes = 0;
                            printf("[WARN]: package %d meets the count threshold of target cpu port %d!\n", pkgs->elems[pkg_index]->id, pkgs->elems[pkg_index]->tgt_pid);
                        }
                    } else {
                        if (chip->ports[port_index]->bytes_threshold > port_bytes[port_index])
                        {
                            bytes_left = chip->ports[port_index]->bytes_threshold - port_bytes[port_index];
                            if (bytes_left < pkgs->elems[pkg_index]->bytes) {
                                pkgs->elems[pkg_index]->bytes = bytes_left;
                                port_bytes[port_index] += pkgs->elems[pkg_index]->bytes;
                            }
                            port_bytes[port_index] += pkgs->elems[pkg_index]->bytes;
                            port_count[port_index]++;
                        } else {
                            pkgs->elems[pkg_index]->bytes = 0;
                            printf("[WARN]: package %d meets the bytes threshold of target fwd port %d!\n", pkgs->elems[pkg_index]->id, pkgs->elems[pkg_index]->tgt_pid);
                        }
                    }
                    break;
                }
            }    
            if (port_index >= chip->port_number || port_index >= 12) {
                pkgs->elems[pkg_index]->bytes = 0;
                printf("[ERROR]: target port %d not found of package %d!\n", pkgs->elems[pkg_index]->tgt_pid, pkgs->elems[pkg_index]->id);
            }          
            break;
        case HAND_SHAKE:
            for (port_index = 0; port_index < chip->port_number && port_index < 12; port_index++) {
                if (chip->ports[port_index]->id == pkgs->elems[pkg_index]->src_pid) {
                    if (port_count[port_index] < chip->ports[port_index]->count_threshold) {
                        if (chip->ports[port_index]->type == CPU_PORT) {
                            pkgs->elems[pkg_index]->tgt_pid = pkgs->elems[pkg_index]->src_pid;
                            port_count[port_index]++;
                        } else {
                            pkgs->elems[pkg_index]->tgt_pid = pkgs->elems[pkg_index]->src_pid;
                            port_bytes[port_index] += pkgs->elems[pkg_index]->bytes;
                            port_count[port_index]++;
                        } 
                    } else {
                        pkgs->elems[pkg_index]->bytes = 0;
                        printf("[WARN]: package %d meets the count threshold of target fwd port %d!\n", pkgs->elems[pkg_index]->id, pkgs->elems[pkg_index]->tgt_pid);
                    }
                    break;
                }
            }    
            if (port_index >= chip->port_number || port_index >= 12) {
                pkgs->elems[pkg_index]->bytes = 0;
                printf("[ERROR]: target port %d not found of package %d!\n", pkgs->elems[pkg_index]->tgt_pid, pkgs->elems[pkg_index]->id);
            }            
            break;
        default:
            break;
        }
    }
    return SUCCESS;
}
