/*
 * die.h
 *
 *  Created on: Jan 8, 2017
 *      Author: Nick Gaulke
 */

#ifndef SRC_DIE_H_
#define SRC_GENERATOR_H_

class Die {
    private:
        int min = 1;
        int max = 6;
    public:
        Die();
        Die(int min, int max);
        ~Die();
        int roll();
        int roll(int min, int max);
};

#endif /* SRC_DIE_H_ */
