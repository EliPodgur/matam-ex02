#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>


#include "challenge.h"

/* IMPLEMENT HERE ALL WHAT IS NEEDED */

// Initiates given challenge with the given parameters.
Result init_challenge(Challenge *challenge, int id, char *name, Level level) {
    if (challenge == NULL || name == NULL) {
        return NULL_PARAMETER;
    }
    challenge->id = id;
    challenge->level = level;
    // maybe need to free name
    challenge->name = malloc(sizeof(char) * (strlen(name)) + 1);
    if (challenge->name == NULL) {
        return MEMORY_PROBLEM;
    }
    strcpy(challenge->name, name);
    challenge->best_time = 0;
    challenge->num_visits = 0;
    return OK;
}

// reset the defaults for a given challenge.
Result reset_challenge(Challenge *challenge) {
    if (challenge == NULL) {
        return NULL_PARAMETER;
    }
    challenge->num_visits = 0;
    challenge->best_time = 0;
    free(challenge->name);
    challenge->name = NULL;
    challenge->level = 0;
    challenge->id = 0;
    return OK;
}

// change challenge name
Result change_name(Challenge *challenge, char *name) {
    if (challenge == NULL || name == NULL) {
        return NULL_PARAMETER;
    }
    free(challenge->name);
    challenge->name = malloc(sizeof(char) * (strlen(name)) + 1);
    if (challenge->name == NULL) {
        return MEMORY_PROBLEM;
    }
    strcpy(challenge->name, name);
    return OK;
}

// sets the given time as the challenge best time
Result set_best_time_of_challenge(Challenge *challenge, int time) {
    if (challenge == NULL) {
        return NULL_PARAMETER;
    }
    if (time < 0 || (time > challenge->best_time && challenge->best_time != 0)) {
        return ILLEGAL_PARAMETER;
    }
    challenge->best_time = time;
    return OK;
}

// return best time into time
Result best_time_of_challenge(Challenge *challenge, int *time) {
    if (challenge == NULL) {
        return NULL_PARAMETER;
    }
    *time = challenge->best_time;
    return OK;
}

// add 1 to challenge visit
Result inc_num_visits(Challenge *challenge) {
    if (challenge == NULL) {
        return NULL_PARAMETER;
    }
    challenge->num_visits += 1;
    return OK;
}

//return visits
Result num_visits(Challenge *challenge, int *visits) {
    if (challenge == NULL) {
        return NULL_PARAMETER;
    }
    *visits = challenge->num_visits;
    return OK;
}