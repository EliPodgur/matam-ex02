#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>


#include "visitor_room.h"
/*void copy_challenge(Challenge *dest,Challenge *source){
    dest->name=malloc(sizeof(source->name));
    strcpy(dest->name,source->name);
    dest->best_time=source->best_time;
    dest->num_visits=source->num_visits;
    dest->id=source->id;
    dest->level=source->level;
}*/


/* IMPLEMENT HERE ALL WHAT IS NEEDED */

// initiates challenge activity - new activity in room
Result init_challenge_activity(ChallengeActivity *activity, Challenge *challenge) {
    if (challenge == NULL || activity == NULL) {
        return NULL_PARAMETER;
    }
    activity->start_time = 0;
    activity->visitor = NULL;
    activity->challenge = challenge;
    return OK;
}

// reset challenge activity to default
Result reset_challenge_activity(ChallengeActivity *activity) {
    if (activity == NULL) {
        return NULL_PARAMETER;
    }
    activity->challenge = NULL;
    activity->visitor = NULL;
    activity->start_time = 0;
    return OK;
}

// initiates visitor
Result init_visitor(Visitor *visitor, char *name, int id) {
    if (visitor == NULL || name == NULL) {
        return NULL_PARAMETER;
    }
    // no free?
    visitor->visitor_name = malloc(sizeof(char) * strlen(name) + 1);
    if (visitor->visitor_name == NULL) {
        return MEMORY_PROBLEM;
    }
    strcpy(visitor->visitor_name, name);
    visitor->visitor_id = id;
    visitor->current_challenge = NULL;
    visitor->room_name = NULL;
    return OK;
}

// reset visitor to default
Result reset_visitor(Visitor *visitor) {
    if (visitor == NULL) {
        return NULL_PARAMETER;
    }
    free(visitor->visitor_name);
    visitor->visitor_name = NULL;
    free(visitor->room_name); // need this?
    visitor->room_name = NULL;
    visitor->current_challenge = NULL;
    visitor->visitor_id = 0;
    return OK;
}

// initiates room with given params
Result init_room(ChallengeRoom *room, char *name, int num_challenges) {
    if (room == NULL || name == NULL) {
        return NULL_PARAMETER;
    }
    if (num_challenges < 1) {
        return ILLEGAL_PARAMETER;
    }
    room->num_of_challenges = num_challenges;
    room->challenges = malloc(sizeof(ChallengeActivity) * num_challenges);
    if (room->challenges == NULL) {
        return MEMORY_PROBLEM;
    }
    for (int i = 0; i < num_challenges; i++) {
        //room->challenges[i] = NULL;
        reset_challenge_activity(room->challenges[i]);
    }
    room->name = malloc(sizeof(char) * strlen(name) + 1);
    if (room->name == NULL) {
        return MEMORY_PROBLEM;
    }
    strcpy(room->name, name);
    return OK;
}

// reset room to defaults
Result reset_room(ChallengeRoom *room) {
    if (room == NULL) {
        return NULL_PARAMETER;
    }
    free(room->name);
    room->name = NULL;
    free(room->challenges);
    room->challenges = NULL;
    room->num_of_challenges = 0;
    return OK;
}

// counts free places in challenges
Result num_of_free_places_for_level(ChallengeRoom *room, Level level, int *places) {
    if (room == NULL) {
        return NULL_PARAMETER;
    }
    int free_places = 0;
    for (int i = 0; i < room->num_of_challenges; i++) {
        if (room->challenges[i].visitor == NULL && ((room->challenges[i].challenge->level == level) || //. or ->
                                                    level == All_Levels)) {
            free_places++;
        }
    }
    *places = free_places;
    return OK;
}

// changes name
Result change_room_name(ChallengeRoom *room, char *new_name) {
    if (room == NULL || new_name == NULL) {
        return NULL_PARAMETER;
    }
    free(room->name);
    room->name = malloc(sizeof(char) * strlen(new_name) + 1);
    if (room->name == NULL) {
        return MEMORY_PROBLEM;
    }
    strcpy(room->name, new_name);
    return OK;
}

//  Returns the name of the room which the given visitor is in.
Result room_of_visitor(Visitor *visitor, char **room_name) {
    if (visitor == NULL || room_name == NULL) {
        return NULL_PARAMETER;
    }
    if (visitor->room_name == NULL) {
        return NOT_IN_ROOM;
    }
    *room_name = malloc(sizeof(char) * strlen(*(visitor->room_name)) + 1);
    if (*room_name == NULL) {
        return MEMORY_PROBLEM;
    }
    strcpy(*(visitor->room_name), *(room_name));
    return OK;
}


Result visitor_enter_room(ChallengeRoom room, Visitor visitor, Level level, int start_time) {
    if (room == NULL || visitor == NULL) {
        return NULL_PARAMETER;
    }
    if (visitor->current_challenge != NULL) {
        return ALREADY_IN_ROOM;
    }
    int challenge_numbers = room->num_of_challenges;
    ChallengeActivity *challenge_visitor = NULL;
    challenge_visitor = &(room->challenges[0]);
    for (int i = 0; i < challenge_numbers; i++) {
        if (strcmp(challenge_visitor->challenge->name, (room->challenges[i].challenge->name)) > 0
            && room->challenges[i].visitor == NULL &&
            (room->challenges[i].challenge->level == level || level == All_Levels)) {
            challenge_visitor = &(room->challenges[i]);
        }
    }
    if (challenge_visitor->visitor == NULL) {
        visitor->room_name = &(room->name);
        challenge_visitor->visitor = visitor;
        challenge_visitor->start_time = start_time;
    } else {
        return NO_AVAILABLE_CHALLENGES;
    }
    return OK;
}

// remove visitor from activity challenge and set best time if needed
Result visitor_quit_room(Visitor *visitor, int quit_time) {
    if (visitor == NULL) {
        return NULL_PARAMETER;
    }
    if (visitor->room_name == NULL) {
        return NOT_IN_ROOM;
    }
    int start_time = visitor->current_challenge->start_time;
    int total_time = quit_time - start_time;
    set_best_time_of_challenge(visitor->current_challenge, total_time);
    visitor->current_challenge=NULL;
    return reset_visitor(visitor);
}

/*
    activity->challenge->name=malloc(sizeof(challenge->name));
    strcpy(activity->challenge->name,challenge->name);
 */