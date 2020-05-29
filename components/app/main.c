/**
  ******************************************************************************
  * @file			main.c
  * @brief			main function
  * @author			Xli
  * @email			xieliyzh@163.com
  * @version		1.0.0
  * @date			2020-05-29
  * @copyright		2020, XIELI Co.,Ltd. All rights reserved
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "list.h"
#include "mutex.h"

/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/**
 * @brief 设备链表节点
 * 
 */
typedef struct {
    struct list_head list;
    uint8_t addr;
}device_node_t;

/* Private variables ---------------------------------------------------------*/
/* 链表头的next、prev分别指向链表中的第一个和最末一个节点 */
//static DEFINE_MUTEX(device_mutex);  /*!< 定义链表互斥锁 */
static mutex_t device_mutex;
static LIST_HEAD(device_list);  /*!< 定义链表(链表头) */

/* Private function ----------------------------------------------------------*/

/**=============================================================================
 * @brief           注册设备
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static int _device_register(uint8_t addr)
{
    int ret = 0;

    mutex_lock(&device_mutex);

    /* 查看是否已注册 */
    device_node_t *cur, *tmp;
    list_for_each_entry_safe(cur, tmp, &device_list, list)
    {
        if (cur->addr == addr)  /*!< 已注册 */
        {
            ret = -1;
            goto out;
        }
    }

    device_node_t *new_node = (device_node_t*)malloc(sizeof(device_node_t));
    if (new_node == NULL) 
    {
        ret = -1;
        goto out;
    }

    INIT_LIST_HEAD(&new_node->list);
    list_add_tail(&new_node->list, &device_list);
    new_node->addr = addr;
out:
    mutex_unlock(&device_mutex);

    return ret;
}

/**=============================================================================
 * @brief           销毁设备
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
static int _device_unregister(uint8_t addr)
{
    int ret = 0;

    device_node_t *cur, *tmp;
    
    mutex_lock(&device_mutex);
    list_for_each_entry_safe(cur, tmp, &device_list, list)
    {
        if (cur->addr == addr)  /*!< 找到地址 */
        {
            list_del(&cur->list);
            free(cur);
            goto out;
        }
    }
    ret = -1;
out:    
    mutex_unlock(&device_mutex);

    return ret;
}

/**=============================================================================
 * @brief           main
 *
 * @param[in]       none
 *
 * @return          none
 *============================================================================*/
int main(int argc, char *argv[])
{
    device_mutex = mutex_create();

    uint8_t addr = 0;
    while (1)
    {
        printf("register device addr[%d]->[%s]\n", addr, (_device_register(addr) == 0)?"success":"fail");
        printf("unregister device addr[%d]->[%s]\n", addr, (_device_unregister(addr) == 0)?"success":"fail");
        addr++;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    return 0;
}