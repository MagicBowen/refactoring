#include <gtest/gtest.h>
#include "sdk/fwd_ctrl.h"

struct SDK_TEST : testing::Test
{
protected:
    Chip chip{.port_number = 0};
    Packages pkgs{.number = 0};
};

TEST_F(SDK_TEST, should_fail_when_none_chip_or_none_package)
{
    ASSERT_EQ(FAILURE, forward_ctrl(NULL_PTR, NULL_PTR));
    ASSERT_EQ(FAILURE, forward_ctrl(NULL_PTR, &pkgs));
    ASSERT_EQ(FAILURE, forward_ctrl(&chip, NULL_PTR));
}

TEST_F(SDK_TEST, should_not_forward_data_pdu_to_none_port)
{
    Package pkg{.id = 1, .type = DATA_PDU, .bytes = 1024};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(0, pkg.bytes);
    ASSERT_EQ(DATA_PDU, pkg.type);
}

TEST_F(SDK_TEST, should_not_forward_data_pdu_whose_src_port_is_not_exist)
{
    Package pkg{.id = 1, .type = DATA_PDU, .bytes = 1024, .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port port{.id = 3, .type = CPU_PORT, .count_threshold = 1, .bytes_threshold = 1500};
    chip.ports[0] = &port;
    chip.port_number = 1;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(0, pkg.bytes);
    ASSERT_EQ(DATA_PDU, pkg.type);
}

TEST_F(SDK_TEST, should_not_forward_data_pdu_to_cpu_port)
{
    Package pkg{.id = 1, .type = DATA_PDU, .bytes = 1024,  .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port src_port{.id = 1};
    Port tgt_port{.id = 3, .type = CPU_PORT, .count_threshold = 1, .bytes_threshold = 1500};
    chip.ports[0] = &src_port;
    chip.ports[1] = &tgt_port;
    chip.port_number = 2;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(0, pkg.bytes);
}

TEST_F(SDK_TEST, should_forward_data_pdu_to_fwd_port_when_under_bytes_and_count_threshold)
{
    Package pkg{.id = 1, .type = DATA_PDU, .bytes = 1024,  .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port src_port{.id = 1};
    Port tgt_port{.id = 3, .type = FWD_PORT, .count_threshold = 1, .bytes_threshold = 1500};
    chip.ports[0] = &src_port;
    chip.ports[1] = &tgt_port;
    chip.port_number = 2;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(1024, pkg.bytes);
    ASSERT_EQ(DATA_PDU, pkg.type);    
    ASSERT_EQ(1, pkg.src_pid);    
    ASSERT_EQ(3, pkg.tgt_pid);    
}

TEST_F(SDK_TEST, should_forward_data_pdu_to_fwd_port_but_exceed_bytes_threshold)
{
    Package pkg{.id = 1, .type = DATA_PDU, .bytes = 1024,  .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port src_port{.id = 1};
    Port tgt_port{.id = 3, .type = FWD_PORT, .count_threshold = 1, .bytes_threshold = 1000};
    chip.ports[0] = &src_port;
    chip.ports[1] = &tgt_port;
    chip.port_number = 2;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(1000, pkg.bytes);
    ASSERT_EQ(DATA_PDU, pkg.type);    
    ASSERT_EQ(1, pkg.src_pid);    
    ASSERT_EQ(3, pkg.tgt_pid);    
}

TEST_F(SDK_TEST, should_not_forward_data_pdu_to_fwd_port_when_exceed_count_threshold)
{
    Package pkg{.id = 1, .type = DATA_PDU, .bytes = 1024,  .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port src_port{.id = 1};
    Port tgt_port{.id = 3, .type = FWD_PORT, .count_threshold = 0, .bytes_threshold = 1500};
    chip.ports[0] = &src_port;
    chip.ports[1] = &tgt_port;
    chip.port_number = 2;    

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(0, pkg.bytes);
    ASSERT_EQ(DATA_PDU, pkg.type);    
    ASSERT_EQ(1, pkg.src_pid);    
    ASSERT_EQ(3, pkg.tgt_pid);    
}

TEST_F(SDK_TEST, should_forward_multi_data_pdu_to_fwd_port_which_not_exceed_count_threshold_but_exceed_bytes_threshold)
{
    Package pkg1{.id = 1, .type = DATA_PDU, .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    Package pkg2{.id = 2, .type = DATA_PDU, .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    Package pkg3{.id = 3, .type = DATA_PDU, .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg1;
    pkgs.elems[1] = &pkg2;
    pkgs.elems[2] = &pkg3;
    pkgs.number = 3;

    Port src_port{.id = 1};
    Port tgt_port{.id = 3, .type = FWD_PORT, .count_threshold = 3, .bytes_threshold = 2500};
    chip.ports[0] = &src_port;
    chip.ports[1] = &tgt_port;
    chip.port_number = 2;    

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg1.id);
    ASSERT_EQ(1000, pkg1.bytes);
    ASSERT_EQ(DATA_PDU, pkg1.type);    
    ASSERT_EQ(1, pkg1.src_pid);    
    ASSERT_EQ(3, pkg1.tgt_pid);    

    ASSERT_EQ(2, pkg2.id);
    ASSERT_EQ(1000, pkg2.bytes);
    ASSERT_EQ(DATA_PDU, pkg2.type);    
    ASSERT_EQ(1, pkg2.src_pid);    
    ASSERT_EQ(3, pkg2.tgt_pid);    

    ASSERT_EQ(3, pkg3.id);
    ASSERT_EQ(500, pkg3.bytes);
    ASSERT_EQ(DATA_PDU, pkg3.type);    
    ASSERT_EQ(1, pkg3.src_pid);    
    ASSERT_EQ(3, pkg3.tgt_pid);    
}

TEST_F(SDK_TEST, should_forward_multi_data_pdu_to_fwd_port_which_not_exceed_bytes_threshold_but_exceed_count_threshold)
{
    Package pkg1{.id = 1, .type = DATA_PDU, .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    Package pkg2{.id = 2, .type = DATA_PDU, .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    Package pkg3{.id = 3, .type = DATA_PDU, .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg1;
    pkgs.elems[1] = &pkg2;
    pkgs.elems[2] = &pkg3;
    pkgs.number = 3;

    Port src_port{.id = 1};
    Port tgt_port{.id = 3, .type = FWD_PORT, .count_threshold = 2, .bytes_threshold = 2500};
    chip.ports[0] = &src_port;
    chip.ports[1] = &tgt_port;
    chip.port_number = 2;    

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg1.id);
    ASSERT_EQ(1000, pkg1.bytes);
    ASSERT_EQ(DATA_PDU, pkg1.type);    
    ASSERT_EQ(1, pkg1.src_pid);    
    ASSERT_EQ(3, pkg1.tgt_pid);    

    ASSERT_EQ(2, pkg2.id);
    ASSERT_EQ(1000, pkg2.bytes);
    ASSERT_EQ(DATA_PDU, pkg2.type);    
    ASSERT_EQ(1, pkg2.src_pid);    
    ASSERT_EQ(3, pkg2.tgt_pid);    

    ASSERT_EQ(3, pkg3.id);
    ASSERT_EQ(0, pkg3.bytes);
    ASSERT_EQ(DATA_PDU, pkg3.type);    
    ASSERT_EQ(1, pkg3.src_pid);    
    ASSERT_EQ(3, pkg3.tgt_pid);    
}

TEST_F(SDK_TEST, should_not_forward_ctrl_cmd_package_whose_src_port_is_not_exist)
{
    Package pkg{.id = 1, .type = CTRL_CMD, .bytes = 1000, .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port port{.id = 3, .type = CPU_PORT, .count_threshold = 1, .bytes_threshold = 2000};
    chip.ports[0] = &port;
    chip.port_number = 1;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(0, pkg.bytes);
    ASSERT_EQ(CTRL_CMD, pkg.type);
}

TEST_F(SDK_TEST, should_forward_ctrl_cmd_package_to_cpu_port_when_not_exceed_count_threshold_but_exceed_bytes_threshold)
{
    Package pkg{.id = 1, .type = CTRL_CMD, .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port src_port{.id = 1};
    Port tgt_port{.id = 3, .type = CPU_PORT, .count_threshold = 1, .bytes_threshold = 0};
    chip.ports[0] = &src_port;
    chip.ports[1] = &tgt_port;
    chip.port_number = 2; 

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(1000, pkg.bytes);
    ASSERT_EQ(CTRL_CMD, pkg.type);
    ASSERT_EQ(1, pkg.src_pid);
    ASSERT_EQ(3, pkg.tgt_pid);
}

TEST_F(SDK_TEST, should_forward_ctrl_cmd_package_to_fwd_port_when_not_exceed_bytes_threshold_but_exceed_count_threshold)
{
    Package pkg{.id = 1, .type = CTRL_CMD, .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port src_port{.id = 1};
    Port tgt_port{.id = 3, .type = FWD_PORT, .count_threshold = 0, .bytes_threshold = 400};
    chip.ports[0] = &src_port;
    chip.ports[1] = &tgt_port;
    chip.port_number = 2; 

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(400, pkg.bytes);
    ASSERT_EQ(CTRL_CMD, pkg.type);
    ASSERT_EQ(1, pkg.src_pid);
    ASSERT_EQ(3, pkg.tgt_pid);
}

TEST_F(SDK_TEST, should_forward_multi_ctrl_cmd_packages_to_cpu_port_and_fwd_port)
{
    Package pkg1{.id = 1, .type = CTRL_CMD, .bytes = 1000,  .src_pid = 1, .tgt_pid = 2};
    Package pkg2{.id = 2, .type = CTRL_CMD, .bytes = 1000,  .src_pid = 2, .tgt_pid = 1};
    Package pkg3{.id = 3, .type = CTRL_CMD, .bytes = 1000,  .src_pid = 1, .tgt_pid = 2};
    pkgs.elems[0] = &pkg1;
    pkgs.elems[1] = &pkg2;
    pkgs.elems[2] = &pkg3;
    pkgs.number = 3;

    Port port1{.id = 1, .type = CPU_PORT, .count_threshold = 1, .bytes_threshold = 400};
    Port port2{.id = 2, .type = FWD_PORT, .count_threshold = 0, .bytes_threshold = 1400};
    chip.ports[0] = &port1;
    chip.ports[1] = &port2;
    chip.port_number = 2;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg1.id);
    ASSERT_EQ(1000, pkg1.bytes);
    ASSERT_EQ(CTRL_CMD, pkg1.type);
    ASSERT_EQ(1, pkg1.src_pid);
    ASSERT_EQ(2, pkg1.tgt_pid);

    ASSERT_EQ(2, pkg2.id);
    ASSERT_EQ(1000, pkg2.bytes);
    ASSERT_EQ(CTRL_CMD, pkg2.type);
    ASSERT_EQ(2, pkg2.src_pid);
    ASSERT_EQ(1, pkg2.tgt_pid);

    ASSERT_EQ(3, pkg3.id);
    ASSERT_EQ(400, pkg3.bytes);
    ASSERT_EQ(CTRL_CMD, pkg3.type);
    ASSERT_EQ(1, pkg3.src_pid);
    ASSERT_EQ(2, pkg3.tgt_pid);
}

TEST_F(SDK_TEST, should_not_forward_hand_shake_package_whose_src_port_is_not_exist)
{
    Package pkg{.id = 1, .type = HAND_SHAKE, .bytes = 1024, .src_pid = 1, .tgt_pid = 3};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port port{.id = 3, .type = CPU_PORT, .count_threshold = 1, .bytes_threshold = 2000};
    chip.ports[0] = &port;
    chip.port_number = 1;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(0, pkg.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg.type);
}

TEST_F(SDK_TEST, should_not_forward_hand_shake_package_to_cpu_port_when_exceed_count_threshold)
{
    Package pkg{.id = 1, .type = HAND_SHAKE, .bytes = 1000, .src_pid = 1};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port port{.id = 1, .type = CPU_PORT, .count_threshold = 0, .bytes_threshold = 2000};
    chip.ports[0] = &port;
    chip.port_number = 1;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(0, pkg.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg.type);
}

TEST_F(SDK_TEST, should_not_forward_hand_shake_package_to_fwd_port_when_exceed_count_threshold)
{
    Package pkg{.id = 1, .type = HAND_SHAKE, .bytes = 1000,  .src_pid = 1};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port port{.id = 1, .type = FWD_PORT, .count_threshold = 0, .bytes_threshold = 2000};
    chip.ports[0] = &port;
    chip.port_number = 1;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(0, pkg.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg.type);
}

TEST_F(SDK_TEST, should_forward_whole_hand_shake_package_to_cpu_port_when_not_exceed_count_threshold)
{
    Package pkg{.id = 1, .type = HAND_SHAKE, .bytes = 1000,  .src_pid = 1};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port port{.id = 1, .type = CPU_PORT, .count_threshold = 1, .bytes_threshold = 400};
    chip.ports[0] = &port;
    chip.port_number = 1;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(1000, pkg.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg.type);
    ASSERT_EQ(1, pkg.src_pid);
    ASSERT_EQ(1, pkg.tgt_pid);
}

TEST_F(SDK_TEST, should_forward_whole_hand_shake_package_to_fwd_port_when_not_exceed_count_threshold)
{
    Package pkg{.id = 1, .type = HAND_SHAKE, .bytes = 1000,  .src_pid = 1};
    pkgs.elems[0] = &pkg;
    pkgs.number = 1;

    Port port{.id = 1, .type = FWD_PORT, .count_threshold = 1, .bytes_threshold = 400};
    chip.ports[0] = &port;
    chip.port_number = 1;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg.id);
    ASSERT_EQ(1000, pkg.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg.type);
    ASSERT_EQ(1, pkg.src_pid);
    ASSERT_EQ(1, pkg.tgt_pid);
}

TEST_F(SDK_TEST, should_forward_all_whole_hand_shake_packages_to_fwd_port_when_exceed_bytes_threshold)
{
    Package pkg1{.id = 1, .type = HAND_SHAKE, .bytes = 1000,  .src_pid = 1};
    Package pkg2{.id = 2, .type = HAND_SHAKE, .bytes = 1000,  .src_pid = 1};
    pkgs.elems[0] = &pkg1;
    pkgs.elems[1] = &pkg2;
    pkgs.number = 2;

    Port port{.id = 1, .type = FWD_PORT, .count_threshold = 2, .bytes_threshold = 400};
    chip.ports[0] = &port;
    chip.port_number = 1;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg1.id);
    ASSERT_EQ(1000, pkg1.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg1.type);
    ASSERT_EQ(1, pkg1.src_pid);
    ASSERT_EQ(1, pkg1.tgt_pid);

    ASSERT_EQ(2, pkg2.id);
    ASSERT_EQ(1000, pkg2.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg2.type);
    ASSERT_EQ(1, pkg2.src_pid);
    ASSERT_EQ(1, pkg2.tgt_pid);
}

TEST_F(SDK_TEST, should_forward_all_whole_hand_shake_packages_but_other_packages_according_bytes_threshold)
{
    Package pkg1{.id = 1, .type = HAND_SHAKE, .bytes = 1000,  .src_pid = 3};
    Package pkg2{.id = 2, .type = CTRL_CMD  , .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    Package pkg3{.id = 3, .type = DATA_PDU  , .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    Package pkg4{.id = 4, .type = HAND_SHAKE, .bytes = 1000,  .src_pid = 3};
    pkgs.elems[0] = &pkg1;
    pkgs.elems[1] = &pkg2;
    pkgs.elems[2] = &pkg3;
    pkgs.elems[3] = &pkg4;
    pkgs.number = 4;

    Port src_port{.id = 1};
    Port tgt_port{.id = 3, .type = FWD_PORT, .count_threshold = 4, .bytes_threshold = 2500};
    chip.ports[0] = &src_port;
    chip.ports[1] = &tgt_port;
    chip.port_number = 2;    

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg1.id);
    ASSERT_EQ(1000, pkg1.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg1.type);    
    ASSERT_EQ(3, pkg1.src_pid);    
    ASSERT_EQ(3, pkg1.tgt_pid);    

    ASSERT_EQ(2, pkg2.id);
    ASSERT_EQ(1000, pkg2.bytes);
    ASSERT_EQ(CTRL_CMD, pkg2.type);    
    ASSERT_EQ(1, pkg2.src_pid);    
    ASSERT_EQ(3, pkg2.tgt_pid);    

    ASSERT_EQ(3, pkg3.id);
    ASSERT_EQ(500, pkg3.bytes);
    ASSERT_EQ(DATA_PDU, pkg3.type);    
    ASSERT_EQ(1, pkg3.src_pid);    
    ASSERT_EQ(3, pkg3.tgt_pid);    

    ASSERT_EQ(4, pkg4.id);
    ASSERT_EQ(1000, pkg4.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg4.type);    
    ASSERT_EQ(3, pkg4.src_pid);    
    ASSERT_EQ(3, pkg4.tgt_pid);    
}

TEST_F(SDK_TEST, should_forward_multi_packages_to_multi_ports_according_forward_rules)
{
    Package pkg1{.id = 1, .type = HAND_SHAKE, .bytes = 1000,  .src_pid = 1};
    Package pkg2{.id = 2, .type = CTRL_CMD  , .bytes = 1000,  .src_pid = 2, .tgt_pid = 1};
    Package pkg3{.id = 3, .type = DATA_PDU  , .bytes = 1000,  .src_pid = 1, .tgt_pid = 2};
    Package pkg4{.id = 4, .type = HAND_SHAKE, .bytes = 1000,  .src_pid = 2};
    Package pkg5{.id = 5, .type = DATA_PDU  , .bytes = 1000,  .src_pid = 3, .tgt_pid = 2};
    Package pkg6{.id = 6, .type = DATA_PDU  , .bytes = 1000,  .src_pid = 1, .tgt_pid = 3};
    Package pkg7{.id = 7, .type = CTRL_CMD  , .bytes = 2000,  .src_pid = 2, .tgt_pid = 3};
    Package pkg8{.id = 8, .type = HAND_SHAKE, .bytes = 2000,  .src_pid = 4};
    pkgs.elems[0] = &pkg1;
    pkgs.elems[1] = &pkg2;
    pkgs.elems[2] = &pkg3;
    pkgs.elems[3] = &pkg4;
    pkgs.elems[4] = &pkg5;
    pkgs.elems[5] = &pkg6;
    pkgs.elems[6] = &pkg7;
    pkgs.elems[7] = &pkg8;
    pkgs.number = 8;

    Port port1{.id = 1, .type = FWD_PORT, .count_threshold = 1, .bytes_threshold = 1500};
    Port port2{.id = 2, .type = FWD_PORT, .count_threshold = 2, .bytes_threshold = 1500};
    Port port3{.id = 3, .type = CPU_PORT, .count_threshold = 1, .bytes_threshold = 1500};
    Port port4{.id = 4, .type = CPU_PORT, .count_threshold = 3, .bytes_threshold = 1500};
    chip.ports[0] = &port1;
    chip.ports[1] = &port2;
    chip.ports[2] = &port3;
    chip.ports[3] = &port4;
    chip.port_number = 4;

    ASSERT_EQ(SUCCESS, forward_ctrl(&chip, &pkgs));

    ASSERT_EQ(1, pkg1.id);
    ASSERT_EQ(1000, pkg1.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg1.type);    
    ASSERT_EQ(1, pkg1.src_pid);    
    ASSERT_EQ(1, pkg1.tgt_pid);   

    ASSERT_EQ(2, pkg2.id);
    ASSERT_EQ(500, pkg2.bytes);
    ASSERT_EQ(CTRL_CMD, pkg2.type);    
    ASSERT_EQ(2, pkg2.src_pid);    
    ASSERT_EQ(1, pkg2.tgt_pid);       

    ASSERT_EQ(3, pkg3.id);
    ASSERT_EQ(1000, pkg3.bytes);
    ASSERT_EQ(DATA_PDU, pkg3.type);    
    ASSERT_EQ(1, pkg3.src_pid);    
    ASSERT_EQ(2, pkg3.tgt_pid);       

    ASSERT_EQ(4, pkg4.id);
    ASSERT_EQ(1000, pkg4.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg4.type);    
    ASSERT_EQ(2, pkg4.src_pid);    
    ASSERT_EQ(2, pkg4.tgt_pid);       

    ASSERT_EQ(5, pkg5.id);
    ASSERT_EQ(0, pkg5.bytes);
    ASSERT_EQ(DATA_PDU, pkg5.type);    
    ASSERT_EQ(3, pkg5.src_pid);    
    ASSERT_EQ(2, pkg5.tgt_pid);       

    ASSERT_EQ(6, pkg6.id);
    ASSERT_EQ(0, pkg6.bytes);
    ASSERT_EQ(DATA_PDU, pkg6.type);    
    ASSERT_EQ(1, pkg6.src_pid);    
    ASSERT_EQ(3, pkg6.tgt_pid);       

    ASSERT_EQ(7, pkg7.id);
    ASSERT_EQ(2000, pkg7.bytes);
    ASSERT_EQ(CTRL_CMD, pkg7.type);    
    ASSERT_EQ(2, pkg7.src_pid);    
    ASSERT_EQ(3, pkg7.tgt_pid);       

    ASSERT_EQ(8, pkg8.id);
    ASSERT_EQ(2000, pkg8.bytes);
    ASSERT_EQ(HAND_SHAKE, pkg8.type);    
    ASSERT_EQ(4, pkg8.src_pid);    
    ASSERT_EQ(4, pkg8.tgt_pid);       
}