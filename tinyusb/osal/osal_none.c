#include "tusb_option.h"
#include "common/tusb_common.h"

#if CFG_TUSB_OS == OPT_OS_NONE

#include "osal.h"


static int next_available_sem = 0;
static osal_semaphore_def_t sem_list[16] = {0};

osal_semaphore_t osal_semaphore_create()
{
	osal_semaphore_def_t* semdef = &sem_list[next_available_sem++];
	semdef->count     = 0;
	semdef->max_count = 1;
	return semdef;
}


static int next_available_mutex = 0;
static osal_mutex_value_t mutex_list[16] = {0};

osal_mutex_t osal_mutex_create(void)
{
	return &mutex_list[next_available_mutex++];
}

bool osal_mutex_release(osal_mutex_t mutex_hdl)
{
	mutex_hdl->count = 0;
	return true;
}

void osal_mutex_reset(osal_mutex_t mutex_hdl)
{
	mutex_hdl->count = 0;
}

void osal_mutex_wait(osal_mutex_t mutex_hdl, uint32_t msec, tusb_error_t *p_error)
{
	uint32_t startTime;
	do {
		startTime = tusb_hal_millis();
		if (!mutex_hdl->count) {
			mutex_hdl->count = 1;
			*p_error = TUSB_ERROR_NONE;
			return;
		}
		if ( (msec != OSAL_TIMEOUT_WAIT_FOREVER) && (tusb_hal_millis() - startTime >= msec) ) {
			*p_error = TUSB_ERROR_OSAL_TIMEOUT;
			return;
		}
	} while (1);
}


#endif
