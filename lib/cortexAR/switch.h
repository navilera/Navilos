/*
 * switch.h
 *
 *  Created on: Jan 29, 2019
 *      Author: maanu
 */

#ifndef LIB_CORTEXM_SWITCH_H_
#define LIB_CORTEXM_SWITCH_H_

void Arch_start(void);
void Arch_context_switching(void);
void Arch_Restore_context(void);

#endif /* LIB_CORTEXM_SWITCH_H_ */
