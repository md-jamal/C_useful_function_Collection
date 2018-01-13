# Send Event Signal

Through this code can learn how to send message to control other thing.

## Build Event Signal Package

### Build
```bash
make
```

## Architecture of Event Signal Package

```
User_Space_APP_send_signal +-------> Kernel_EventMgr <--------> User_Space_Daemon_wait_for_signal

                           Send Event

```

User_Space_APP_send_signal will send event to Kernel_EventMgr. User_Space_Daemon_wait_for_signal will detect Kernel_EventMgr.
When User_Space_APP_send_signal send event to Kernel_EventMgr, User_Space_Daemon_wait_for_signal will receive signal and do next activate.


## Execute 
### Kernel_EventMgr
```bash
sudo insmod eventmgr.ko
```

### User_Space_Daemon_wait_for_signal as Daemon
```bash
sudo ./User_Space_Daemon_wait_for_signal
```

### User_Space_APP_send_signal 
Start to send event signal.
```bash
sudo ./User_Space_APP_send_signal
