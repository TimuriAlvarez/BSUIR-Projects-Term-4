#pragma once

#include "Lab4.h"
volatile sig_atomic_t print_flag = false;
typedef struct
{
    sig_atomic_t a;
    sig_atomic_t b;
} Structure;
Structure child_struct;

void handle_alarm(const int signal)
{
    if (signal == SIGALRM) if (print_flag)
        T_CLASS(TConsole, print)(kLog, "p_pid: %i; c_pid: %i; a: %i; b: %i\n", getppid(), getpid(), child_struct.a, child_struct.b);
    alarm(1);  // NOLINT(bugprone-signal-handler)
}
void handle_user_1(const int signal)
{
    if (signal == SIGUSR1)
        print_flag = false;
}
void handle_user_2(const int signal)
{
    if (signal == SIGUSR2)
        print_flag = true;
}

int child_function(void)
{
	//const struct timespec requested_time = { 0, 0 };
    static Structure const zeros = { 0,0 }, ones = { 1,1 };
    signal(SIGALRM, handle_alarm);  //
    signal(SIGUSR1, handle_user_1); //  Install handler first
    signal(SIGUSR2, handle_user_2); //
    alarm(1); // before scheduling it to be called.
	while (true)
	{
        child_struct.a = zeros.a;
        child_struct.b = zeros.b;
        child_struct.a = ones.a;
        child_struct.b = ones.b;
	}
}
