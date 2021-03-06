#
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#
--let $include_filename= uninstall_semisync.inc
--source include/begin_include_file.inc

--disable_query_log
--connection slave
--source include/stop_slave_io.inc

# Uninstall rpl_semi_sync_slave first
--disable_warnings
UNINSTALL PLUGIN rpl_semi_sync_slave;

--connection master
# After BUG#17638477 fix, uninstallation of rpl_semi_sync_master
#  is not allowed when there are semi sync slaves. Hence kill
#  all dump threads before uninstalling it.
SET GLOBAL rpl_semi_sync_master_enabled = OFF;
--source include/stop_dump_threads.inc
UNINSTALL PLUGIN rpl_semi_sync_master;
--enable_warnings

--connection slave
START SLAVE IO_THREAD;
--source include/wait_for_slave_io_to_start.inc
--enable_query_log

--source include/end_include_file.inc
