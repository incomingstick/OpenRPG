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
        int MAX = 6;
    public:
        Die();
        Die(int max);
        ~Die();
        int roll();
        int roll(int max);
};

#endif /* SRC_DIE_H_ */