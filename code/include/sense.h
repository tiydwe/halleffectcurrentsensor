#ifndef SENSE_H
#define SENSE_H


void init_sensors();
void sensors_off();
long double read_pin(int pin);
// returns correctly scaled voltages (up to 5v)
long double read_OUT();
long double read_RAW_OUT();
long double read_REF_SIG();

#endif