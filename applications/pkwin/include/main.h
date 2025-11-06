#pragma once

void cleanup_all(void);
__NORETURN void accept_loop(void);
void listen_loop(fd_t sock_fd);
