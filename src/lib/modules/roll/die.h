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
        const int MAX;
    public:
        Die();
        Die(int max);
        ~Die();
        int roll();
};

#endif /* SRC_DIE_H_ */
