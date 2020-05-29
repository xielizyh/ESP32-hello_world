/**
  ******************************************************************************
  * @file			mutex.h
  * @brief			mutex header file
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-03-02
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MUTEX_H_
#define __MUTEX_H_

/* Includes ------------------------------------------------------------------*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#ifndef __MUTEX_H_
extern "C"{
#endif

typedef xSemaphoreHandle mutex_t;

#ifdef __MUTEX_INITIALIZER
/**
 * @brief 定义Mutex
 * 
 */
#define DEFINE_MUTEX(mutexname) \
    mutex_t mutexname = __MUTEX_INITIALIZER(mutexname)
#else
    #define mutex_create() xSemaphoreCreateMutex()
#endif

// /**
//  * @brief 创建Mutex
//  * 
//  */
// static inline void mutex_create(mutex_t *mutexname)
// {
//     *mutexname = xSemaphoreCreateMutex();
// }

/**
 * @brief Mutex上锁
 * 
 */
static inline void mutex_lock(mutex_t *lock)
{
	xSemaphoreTake(*lock, portMAX_DELAY);
}

/**
 * @brief Mutex解锁
 * 
 */
static inline void mutex_unlock(mutex_t *lock)
{
	xSemaphoreGive(*lock);
}

#ifdef __cplusplus
}
#endif

#endif  /* __MUTEX_H_ */