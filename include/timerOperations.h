/**
 * @file timerOperations.h
 * @author Talha Cetin (talhacetin96@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _TIMER_OPERATIONS_H_
#define _TIMER_OPERATIONS_H_

void InitTimer(void);

extern bool updateMotorsParameters;
extern bool sendRemoteStartMessage;
extern bool checkMessageTimeoutFlag;

#endif /* _TIMER_OPERATIONS_H_ */