/*
 * BMP280.h
 *
 * Created: 11/29/2025 12:15:05 AM
 *  Author: felix
 */ 


#ifndef BMP280_H_
#define BMP280_H_

void temp_init(void);
void pres_init(void);
double get_temp(void);
double get_pres(void);



#endif /* BMP280_H_ */