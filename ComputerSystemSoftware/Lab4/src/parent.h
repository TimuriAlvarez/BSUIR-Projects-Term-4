#pragma once

#include "tlib.h"

TBool vector_is_empty(T_CONTAINER(TVector, pid_t, Container) const container);
void print_hint(void);
void top_bar(T_CONTAINER(TVector, pid_t, Container) const container);
void kill_last(T_CONTAINER(TVector, pid_t, Container) const container, const TBool message);
void kill_selected(T_CONTAINER(TVector, pid_t, Container) const container, const int index);
void kill_all(T_CONTAINER(TVector, pid_t, Container) const container);
int ParseIntFromEnd(TMessage line);
int find_pid(T_CONTAINER(TVector, pid_t, Container) const container, const pid_t pid);
pid_t get_pid(T_CONTAINER(TVector, pid_t, Container) const container, TString message);
void parent_handler(const int signal);
