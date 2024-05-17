//
// Created by Hazem on 5/9/2024.
//

#ifndef PROJECTS_PROGRAM_TIMER_H
#define PROJECTS_PROGRAM_TIMER_H
#include <time.h>
#include <stdio.h>
extern void dummy_function();
extern void __attribute__((constructor)) program_start();
extern void __attribute__((destructor)) program_end();
#endif //PROJECTS_PROGRAM_TIMER_H