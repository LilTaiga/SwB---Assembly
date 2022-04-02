#ifndef BASE_H
#define BASE_H

extern char buffer[1024];

int function_initialization();
void process_local_variables(int a);
void process_instructions();
void process_attribution();
void process_vector_getter();
void process_vector_setter();
void process_if(int current_if);
void process_return();
void call_function();
int read_line();
#endif